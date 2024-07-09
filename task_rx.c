#include "task_rx.h"

/**
 * Since this task is the "Keeper of the SBUS DMA", there's no queues or
 * semaphores: just globals. The SBUS data comes in at 10 ms intervals,
 * which is faster that the PID filters that consume the data can adjust, so
 * there's really no need to notify every time a DMA completes. The sole task
 * here just updates a structure (and provides access to it) less frequently
 * than it is updated by the reciever UART.
 */

/* TODO: Response to FAILSAFE and LOST_FRAME */
/**
 * @brief Failsafe note
 *
 * If the link is lost, Rx will continue sending packets with fsafe = 0x08.
 * Study this. What other failsafes are there?  What does this have to do with
 * the TX failsafe option?
 */

// double buffer to prevent shearing during DMA update, blocking DMA loses sync
static uint8_t g_sbus_raw_a[25];
static uint8_t g_sbus_raw_b[25];
static bool    g_synced       = false;
static bool    g_in_sync_mode = true;

// For the RX pin's interrupt ISR:
static volatile TickType_t g_last_tick     = 0;
static volatile bool       g_got_last_tick = false;

// For the DMA ISR:
static volatile bool     g_got_first_dma       = false;
static volatile bool     g_stop_dma_req        = false;
static volatile bool     g_stop_dma_ack        = false;
static volatile uint8_t *g_sbus_ready_raw_ptr  = g_sbus_raw_b;
static volatile bool     g_sbus_read_raw_fence = false;

// Used in generated code's DMA reload function
volatile void *g_sbus_raw_dst_ptr = (void *)&(g_sbus_raw_a[0]);
volatile void *g_sbus_src_ptr     = (void *)&(SBUS_UART_HW->RBUF);

static sbus_data_t g_sbus_data;

void
rx_force_resync(void)
{
    if (g_synced == true)
    {
        g_synced        = false;
        g_in_sync_mode  = false;
        g_got_last_tick = false;
        g_got_first_dma = false;
    }
}

void
SBUS_SYNC_HANDLER(void)
{
    g_last_tick     = xTaskGetTickCount();
    g_got_last_tick = true;
}

/* This should fire every 10ms = FrSky XM+ Rx. */
void
GPDMA0_INTERRUPT_HANDLER(void)
{
    g_got_first_dma = true;
    XMC_DMA_CH_ClearEventStatus(
        SBUS_DMA_HDLR_HW, SBUS_DMA_HDLR_NUM, SBUS_DMA_HDLR_events);
    // Don't swap buffers is a task is reading the other one
    if (!g_sbus_read_raw_fence)
    {
        if (g_sbus_raw_dst_ptr == (void *)&(g_sbus_raw_a[0]))
        {
            g_sbus_ready_raw_ptr = g_sbus_raw_a;
            g_sbus_raw_dst_ptr   = (void *)&(g_sbus_raw_b[0]);
        }
        else
        {
            g_sbus_ready_raw_ptr = g_sbus_raw_b;
            g_sbus_raw_dst_ptr   = (void *)&(g_sbus_raw_a[0]);
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

/* TODO: Proper error codes */
static bool
decode_sbus(volatile uint8_t *raw, sbus_data_t *ptr)
{
    if (raw[0] != SBUS_HEADER)
    {
        return true;
    }
    if (raw[24] != SBUS_FOOTER && raw[24] != SBUS_FOOTER2)
    {
        return true;
    }
    /* clang-format off */
    ptr->ch[ 0]     =  (raw[ 1]       | ((raw[ 2] << 8) & 0x07FF));
    ptr->ch[ 1]     = ((raw[ 2] >> 3) | ((raw[ 3] << 5) & 0x07FF));
    ptr->ch[ 2]     = ((raw[ 3] >> 6) |  (raw[ 4] << 2)             | ((raw[ 5] << 10) & 0x07FF));
    ptr->ch[ 3]     = ((raw[ 5] >> 1) | ((raw[ 6] << 7) & 0x07FF));
    ptr->ch[ 4]     = ((raw[ 6] >> 4) | ((raw[ 7] << 4) & 0x07FF));
    ptr->ch[ 5]     = ((raw[ 7] >> 7) |  (raw[ 8] << 1)             | ((raw[ 9] <<  9) & 0x07FF));
    ptr->ch[ 6]     = ((raw[ 9] >> 2) | ((raw[10] << 6) & 0x07FF));
    ptr->ch[ 7]     = ((raw[10] >> 5) | ((raw[11] << 3) & 0x07FF));
    ptr->ch[ 8]     =  (raw[12]       | ((raw[13] << 8) & 0x07FF));
    ptr->ch[ 9]     = ((raw[13] >> 3) | ((raw[14] << 5) & 0x07FF));
    ptr->ch[10]     = ((raw[14] >> 6) |  (raw[15] << 2)             | ((raw[16] << 10) & 0x07FF));
    ptr->ch[11]     = ((raw[16] >> 1) | ((raw[17] << 7) & 0x07FF));
    ptr->ch[12]     = ((raw[17] >> 4) | ((raw[18] << 4) & 0x07FF));
    ptr->ch[13]     = ((raw[18] >> 7) |  (raw[19] << 1)             | ((raw[20] <<  9) & 0x07FF));
    ptr->ch[14]     = ((raw[20] >> 2) | ((raw[21] << 6) & 0x07FF));
    ptr->ch[15]     = ((raw[21] >> 5) | ((raw[22] << 3) & 0x07FF));
    ptr->ch[16]     = raw[23] & 0x01;
    ptr->ch[17]     = raw[23] & 0x02;
    ptr->lost_frame = raw[23] & 0x04;
    ptr->failsafe   = raw[23] & 0x08;
    /* clang-format on */
    return false;
}

/**
 * @brief The Rx state machine task.
 * 
 * The two main states are SYNCED and NOT SYNCED. This refers to the alignment
 * of the DMA packet. We want to make sure the DMA starts in the quiet period
 * of the 10 ms SBUS packets. SYNCED means the DMA engine is in synch with the
 * transmission. NOT SYNCED means it is searching for a sync.
 * 
 * 1. SYNCED
 * 
 * When synced, make sure at least one DMA transfer has completed, otherwise
 * there will be garbage in the buffer. The "g_got_first_dma" flag is set
 * by the DMA completion interrupt. Once the 1st DMA has completed, the task
 * will decode it into the global "g_sbus_data" variable. However, the decoder
 * is fenced by "g_sbus_read_raw_fence", which prevents the DMA interrupt from
 * swapping buffers. We don't want an interrupt to corrupt the raw data while
 * the decoder is decoding.
 * 
 * 2. NOT-SYNCED
 * 
 * If the DMA is not starting in the quiet region, then the RX pin is switched
 * to be a GPIO input interrupt generation line. Every time the ISR fires, it
 * means a falling edge was detected. If there has been at least 3ms since the
 * last falling edge, it means the quiet zone has started and GPIO can be
 * switched back to the Rx function, and the DMA engine is started.
 * 
 * If sync is lost after DMA is running, the DMA must complete first before
 * disabling it and taking over the Rx pin. This is done with the REQ/ACK 
 * signals "g_stop_dma_req" and "g_stop_dma_ack". Any further DMA interrupts
 * will be ignored since it is not restarted, and we can stop the UART and swap
 * the Rx pin function.
 * 
 * @param pvParameters 
 */
void
rx_task(void *pvParameters)
{
    XMC_UNUSED_ARG(pvParameters);
    TickType_t delay = FC_CFG_RX_UPDATE_DELAY_MS;

    for (;;)
    {
        if (g_synced)
        {
            /* Contents of the DMA buffer are bogus until first completion. */
            if (g_got_first_dma)
            {
                bool       err = false;
                TickType_t t   = xTaskGetTickCount();
                /* Prevent DMA interrupt from corrupting the current buffer */
                g_sbus_read_raw_fence = true;
                err = decode_sbus(g_sbus_ready_raw_ptr, &g_sbus_data);
                g_sbus_read_raw_fence = false;
                if (err)
                {
                    rx_force_resync();
                }
            }
            delay = FC_CFG_RX_UPDATE_DELAY_MS;
        }
        else /* g_synced == false */
        {
            /* Need to reset UART and DMA if entering sync mode */
            if (!g_in_sync_mode)
            {
                /* You can't just disable the DMA (Sec. 5.2.8), you have to let
                 * it complete it's last transaction, hence the REQ/ACK. */
                g_stop_dma_req = true;
                if (g_stop_dma_ack)
                {
                    g_stop_dma_ack = false;
                    rx_uart_ready_set();
                    g_got_last_tick = false;
                    g_got_first_dma = false;
                    g_in_sync_mode  = true;
                    /* Start listening for RX interrupts */
                    NVIC_EnableIRQ(SBUS_SYNC_IRQN);
                }
            }
            else /* g_in_sync_mode == true*/
            {
                /* We can't trust the raw value in g_last_tick */
                if (g_got_last_tick)
                {
                    TickType_t dt = xTaskGetTickCount() - g_last_tick;
                    if (dt > FC_FCG_RX_SYNC_DELAY_MS)
                    {
                        NVIC_DisableIRQ(SBUS_SYNC_IRQN);
                        XMC_UART_CH_Start(SBUS_UART_HW);
                        SBUS_DMA_HDLR_reload();
                        g_stop_dma_req = false;
                        XMC_DMA_CH_Enable(SBUS_DMA_HDLR_HW, SBUS_DMA_HDLR_NUM);
                        g_synced = true;
                    }
                }
            }
            // Let's speed things up a little
            delay = 1;
        }
        vTaskDelay(delay);
    }
}

void
rx_setup(void)
{
    BaseType_t retval;

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
}

static int32_t
map32s(int32_t x, int32_t imin, int32_t imax, int32_t omin, int32_t omax)
{
    return (x - imin) * (omax - omin) / (imax - imin) + omin;
}

/**
 * @brief Returns the left-right axis as an int16, from -1000 to 1000,
 * where the range is fixed point percentage with one sigdigit, e.g.,
 * -100.0% to 100.0%. This range is mapped from the standard SBUS range
 * of 172 to 1811 (midpoint of 992).
 *
 * @return uint32_t
 */
int32_t
rx_lri32(void)
{
    return map32s(g_sbus_data.ch[1], SBUS_MIN, SBUS_MAX, -1000, 1000);
}

uint32_t
rx_get_sbus_steering(void)
{
    // TODO: Depends on transmitter configuration!
    return g_sbus_data.ch[1];
}
