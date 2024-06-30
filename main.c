
#include "FreeRTOS.h"
#include "task.h"

#include "cybsp.h"
#include "cy_utils.h"
#include "cy_retarget_io.h"

#include <stdlib.h>

#define FC_CFG_RX_UPDATE_DELAY_MS 50u
#define FC_FCG_RX_SYNC_DELAY_MS   3u
#define FC_FCG_RX_SYNC_MAX_MS     6u

//------------------------------

// double buffer to prevent shearing during DMA update, blocking DMA loses sync
uint8_t g_rx_sbus_raw_a[25];
uint8_t g_rx_sbus_raw_b[25];
bool    g_rx_synced       = false;
bool    g_rx_in_sync_mode = true;

// For the RX pin's interrupt ISR:
volatile TickType_t g_rx_last_tick     = 0;
volatile bool       g_rx_got_last_tick = false;

// For the DMA ISR:
volatile bool     g_rx_got_first_dma       = false;
volatile bool     g_stop_dma_req           = false;
volatile bool     g_stop_dma_ack           = false;
volatile void    *g_rx_sbus_src_ptr        = (void *)&(SBUS_UART_HW->RBUF);
volatile void    *g_rx_sbus_raw_dst_ptr    = (void *)&(g_rx_sbus_raw_a[0]);
volatile uint8_t *g_rx_sbus_ready_raw_ptr  = g_rx_sbus_raw_b;
volatile bool     g_rx_sbus_read_raw_fence = false;

#define SBUS_SYNC_IRQN    eru_1_ogu_3_IRQN
#define SBUS_SYNC_HANDLER eru_1_ogu_3_INTERRUPT_HANDLER

void
rx_force_resync(void)
{
    g_rx_synced        = false;
    g_rx_in_sync_mode  = false;
    g_rx_got_last_tick = false;
    g_rx_got_first_dma = false;
}

void
SBUS_SYNC_HANDLER(void)
{
    g_rx_last_tick     = xTaskGetTickCount();
    g_rx_got_last_tick = true;
}

/* This should fire every 10ms = FrSky XM+ Rx. */
void
GPDMA0_INTERRUPT_HANDLER(void)
{
    g_rx_got_first_dma = true;
    XMC_DMA_CH_ClearEventStatus(
        SBUS_DMA_HDLR_HW, SBUS_DMA_HDLR_NUM, SBUS_DMA_HDLR_events);
    // Don't swap buffers is a task is reading the other one
    if (!g_rx_sbus_read_raw_fence)
    {
        if (g_rx_sbus_raw_dst_ptr == (void *)&(g_rx_sbus_raw_a[0]))
        {
            g_rx_sbus_ready_raw_ptr = g_rx_sbus_raw_a;
            g_rx_sbus_raw_dst_ptr   = (void *)&(g_rx_sbus_raw_b[0]);
        }
        else
        {
            g_rx_sbus_ready_raw_ptr = g_rx_sbus_raw_b;
            g_rx_sbus_raw_dst_ptr   = (void *)&(g_rx_sbus_raw_a[0]);
        }
    }
    // The re-synch requires not restarting the DMA
    if (g_stop_dma_req)
    {
        g_stop_dma_ack = true;
    }
    else
    {
        SBUS_DMA_HDLR_reload();
        XMC_DMA_CH_Enable(SBUS_DMA_HDLR_HW, SBUS_DMA_HDLR_NUM);
    }
}

/* The point of this is to stop the UART and then reroute the DX input to pin
 * P0[5], but the configuratore won't let us do this b/c we also use for the ERU
 * sync interrupt. Ready... Set... but don't Go! */
void
rx_uart_ready_set(void)
{
    /* Invert polarity, FrSky receiver requirement */
    /* Note there's a bug in the personality, so use [0] raw index */
    SBUS_UART_HW->DXCR[0] |= USIC_CH_DXCR_DPOL_Msk;

    // Undo generated code's _Start()
    XMC_UART_CH_Stop(SBUS_UART_HW);
    XMC_UART_CH_InitEx(SBUS_UART_HW, &SBUS_UART_config, false);
    /* Switch to P0[5] for DX0, P0[5] = 1 */
    XMC_UART_CH_SetInputSource(
        SBUS_UART_HW, (XMC_UART_CH_INPUT_t)XMC_USIC_CH_INPUT_DX0, 1U);
    XMC_UART_CH_SetSamplePoint(SBUS_UART_HW, 8U);
    XMC_USIC_CH_SetFractionalDivider(
        SBUS_UART_HW, XMC_USIC_CH_BRG_CLOCK_DIVIDER_MODE_FRACTIONAL, 1023U);
    XMC_USIC_CH_SetBaudrateDivider(SBUS_UART_HW,
                                   XMC_USIC_CH_BRG_CLOCK_SOURCE_DIVIDER,
                                   false,
                                   89U,
                                   XMC_USIC_CH_BRG_CTQSEL_PDIV,
                                   0U,
                                   15U);
    XMC_USIC_CH_SetInterruptNodePointer(
        SBUS_UART_HW, XMC_USIC_CH_INTERRUPT_NODE_POINTER_RECEIVE, 0U);
    /* Interestingly, we need STANDARD receive, and not START RECEIVE when using
     * this for DMA. Using START receive causes it to read on the wrong byte. */
    XMC_UART_CH_EnableEvent(SBUS_UART_HW, XMC_UART_CH_EVENT_STANDARD_RECEIVE);

    /* Don't start the UART yet! */
}

__NO_RETURN static void
rx_task(void *pvParameters)
{
    XMC_UNUSED_ARG(pvParameters);
    for (;;)
    {
        if (g_rx_synced)
        {
            /* Prevent reading all zeroes or bogus data if DMA hasn't completed
             * a fill at least once */
            if (g_rx_got_first_dma)
            {
                TickType_t t = xTaskGetTickCount();
                /* Prevent DMA interrupt from corrupting the current buffer */
                g_rx_sbus_read_raw_fence = true;
/// decode(g_rx_sbus_ready_raw_ptr, ...)
                printf("%08lu : ", t);
                for (int i = 0; i < 25; ++i)
                {
                    printf("%02x", g_rx_sbus_ready_raw_ptr[i]);
                }
                printf("\n");
                if (g_rx_sbus_ready_raw_ptr[0] != 0x0f)
                {
                    printf("---------- Failed at %lu\n", t);
                    rx_force_resync();
                    // TODO: resync count threshold exceed = fail?
                }
                g_rx_sbus_read_raw_fence = false;
                vTaskDelay(FC_CFG_RX_UPDATE_DELAY_MS);
            }
        }
        else
        {
            /* Need to reset UART and DMA if entering sync mode */
            if (!g_rx_in_sync_mode)
            {
                /* You can't just disable the DMA (Sec. 5.2.8), you have to let
                 * it complete it's last transaction, hence the REQ/ACK. */
                g_stop_dma_req = true;
                if (g_stop_dma_ack)
                {
                    g_stop_dma_ack = false;
                    rx_uart_ready_set();
                    g_rx_got_last_tick = false;
                    g_rx_got_first_dma = false;
                    g_rx_in_sync_mode  = true;
                    /* Start listening for RX interrupts */
                    NVIC_EnableIRQ(SBUS_SYNC_IRQN);
                }
            }
            else
            {
                /* We can't trust the raw value in g_rx_last_tick */
                if (g_rx_got_last_tick)
                {
                    TickType_t dt = xTaskGetTickCount() - g_rx_last_tick;
                    if (dt > FC_FCG_RX_SYNC_DELAY_MS)
                    {
                        NVIC_DisableIRQ(SBUS_SYNC_IRQN);
                        XMC_UART_CH_Start(SBUS_UART_HW);
                        SBUS_DMA_HDLR_reload();
                        g_stop_dma_req = false;
                        XMC_DMA_CH_Enable(SBUS_DMA_HDLR_HW, SBUS_DMA_HDLR_NUM);
                        g_rx_synced = true;
                    }
                }
            }
            vTaskDelay(1);
        }
    }
}

//------------------------------

#ifdef UNIT_TEST_01_JAM_RX
__NO_RETURN static void
main_task(void *pvParameters)
{
    XMC_UNUSED_ARG(pvParameters);

    for (;;)
    {
        vTaskDelay(100);
        float frand = (float)rand() / (float)RAND_MAX;
        if (frand < 0.10)
        {
            printf("jamming...\n");
            // if (g_rx_synced)
            {
                rx_force_resync();
            }
        }
    }
}
#endif

int
main(void)
{
    BaseType_t retval;

    if (CY_RSLT_SUCCESS != cybsp_init())
    {
        CY_ASSERT(0);
    }

    if (CY_RSLT_SUCCESS != cy_retarget_io_init(CYBSP_DEBUG_UART_HW))
    {
        CY_ASSERT(0);
    }

#ifdef UNIT_TEST_01_JAM_RX
    retval = xTaskCreate(main_task,
                         "main",
                         configMINIMAL_STACK_SIZE,
                         NULL,
                         tskIDLE_PRIORITY + 1,
                         NULL);
    if (retval != pdPASS)
    {
        CY_ASSERT(0);
    }
#endif

    retval = xTaskCreate(rx_task,
                         "rx",
                         configMINIMAL_STACK_SIZE,
                         NULL,
                         tskIDLE_PRIORITY + 2,
                         NULL);
    if (retval != pdPASS)
    {
        CY_ASSERT(0);
    }

    rx_uart_ready_set();

    /* Setup the DMA interrupt, but don't start it until we sync */
    NVIC_SetPriority(GPDMA0_IRQN,
                     NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 63, 0));
    NVIC_EnableIRQ(GPDMA0_IRQN);

    /* Start the GPIO interrupt handler on P0[5], we'll stop it on sync */
    NVIC_SetPriority(SBUS_SYNC_IRQN,
                     NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 63, 0));
    NVIC_EnableIRQ(SBUS_SYNC_IRQN);

    printf("\n\nStarting task scheduler\n");

    vTaskStartScheduler();

    for (;;)
    {
    }
}
