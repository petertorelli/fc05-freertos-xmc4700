#include "task_rx.h"

/**
@startuml
    STARTUP --> WAITING_FOR_FIRST_EDGE : Switch to INT mode
    WAITING_FOR_FIRST_EDGE --> WAITING_FOR_FIRST_EDGE
    WAITING_FOR_FIRST_EDGE --> WATCHING_EDGES : First INT
    WATCHING_EDGES --> WATCHING_EDGES
    WATCHING_EDGES --> WAITING_FOR_FIRST_DMA : Switch to DMA Mode
    WAITING_FOR_FIRST_DMA --> WAITING_FOR_FIRST_DMA
    WAITING_FOR_FIRST_DMA --> DMA_FLOWING : First DMA complete
    DMA_FLOWING --> DMA_FLOWING : Decoding
    DMA_FLOWING --> WAITING_FOR_DMA_HALT : Decode Error
    WAITING_FOR_DMA_HALT --> WAITING_FOR_DMA_HALT
    WAITING_FOR_DMA_HALT --> DMA_HALTED : Final DMA IRQ
    DMA_HALTED --> WAITING_FOR_FIRST_EDGE : Switch to INT mode
@enduml
*/

/**
 * TODO:
 * If the link is lost, Rx will continue sending packets with fsafe = 0x08.
 * Study this. What other failsafes are there?  What does this have to do with
 * the TX failsafe option?
 */

// double buffer to prevent shearing during DMA update, blocking DMA loses sync
static uint8_t g_sbus_raw_a[25];
static uint8_t g_sbus_raw_b[25];

// For edge-detect mode ISR:
static volatile TickType_t g_last_tick = 0;

// For the DMA-mode ISR:
static volatile uint8_t *g_sbus_ready_raw_ptr = g_sbus_raw_b;

// Used in generated code's DMA reload function
volatile void *g_sbus_raw_dst_ptr = (void *)&(g_sbus_raw_a[0]);
volatile void *g_sbus_src_ptr     = (void *)&(SBUS_UART_HW->RBUF);

static sbus_data_t g_sbus_data;
volatile state_t   g_state = STATE_STARTUP;

SemaphoreHandle_t sem_rx_packet_rdy = NULL;

/**
 * @brief Change the state, and preserve the last state for debugging.
 *
 * Note: this may be called from within an interrupt; so don't overload it.
 *
 * @param nstate - The new state to change to
 */
static void
rx_change_state(state_t nstate)
{
    static state_t last_state = STATE_NONE;
    last_state                = g_state;
    g_state                   = nstate;
}

void
RX_SBUS_EDGE_MODE_ISR(void)
{
    g_last_tick = xTaskGetTickCount();
    g_state     = STATE_WATCHING_EDGES;
}

/* This should fire every 10ms = FrSky XM+ Rx. */
void
RX_SBUS_DMA_MODE_ISR(void)
{
    XMC_DMA_CH_ClearEventStatus(
        SBUS_DMA_HDLR_HW, SBUS_DMA_HDLR_NUM, SBUS_DMA_HDLR_events);
    /* Don't swap buffers is a task is reading the other one */
    if (xSemaphoreTakeFromISR(sem_rx_packet_rdy, NULL))
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
        xSemaphoreGiveFromISR(sem_rx_packet_rdy, NULL);
    }
    /* Is it bad style to be changing state in the ISR? */
    switch (g_state)
    {
        case STATE_WAITING_FOR_DMA_HALT:
            rx_change_state(STATE_DMA_HALTED);
            break;
        case STATE_DMA_FLOWING:
        case STATE_WAITING_FOR_FIRST_DMA:
            SBUS_DMA_HDLR_reload();
            XMC_DMA_CH_Enable(SBUS_DMA_HDLR_HW, SBUS_DMA_HDLR_NUM);
            rx_change_state(STATE_DMA_FLOWING);
            break;
        default:
            /* These should be the only three valid states to be here! */
            while (1)
            {
            }
            break;
    }
}

/* The point of this is to stop the UART and then reroute the DX input to pin
 * P0[5], but the configuratore won't let us do this b/c we also use for the ERU
 * sync interrupt. Ready... Set... but don't Go! */
static void
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

static void
rx_read_and_decode(void)
{
    bool       err = false;
    TickType_t t   = xTaskGetTickCount();
    if (xSemaphoreTake(sem_rx_packet_rdy, 0))
    {
        err = decode_sbus(g_sbus_ready_raw_ptr, &g_sbus_data);
        xSemaphoreGive(sem_rx_packet_rdy);
        if (err)
        {
            /* Force a resync */
            rx_change_state(STATE_WAITING_FOR_DMA_HALT);
        }
        else
        {
            printf("%10lu %5lu %5lu %5lu %5lu\n",
                   t,
                   g_sbus_data.ch[0],
                   g_sbus_data.ch[1],
                   g_sbus_data.ch[2],
                   g_sbus_data.ch[3]);
        }
    }
}

/* This function assumes we've entered the SBUS idle window. */
static void
rx_switch_to_dma_mode(void)
{
    NVIC_DisableIRQ(SBUS_SYNC_IRQN);
    XMC_UART_CH_Start(SBUS_UART_HW);
    SBUS_DMA_HDLR_reload();
    rx_change_state(STATE_WAITING_FOR_FIRST_DMA);
    XMC_DMA_CH_Enable(SBUS_DMA_HDLR_HW, SBUS_DMA_HDLR_NUM);
}

/* This function assumes we've already stopped the DMA engine. */
static void
rx_switch_to_edge_detect_mode(void)
{
    rx_uart_ready_set();
    rx_change_state(STATE_WAITING_FOR_FIRST_EDGE);
    NVIC_EnableIRQ(SBUS_SYNC_IRQN);
}

void
rx_task(void *pvParameters)
{
    XMC_UNUSED_ARG(pvParameters);
    static TickType_t delay = FC_CFG_RX_UPDATE_DELAY_MS;
    TickType_t        dt;

    for (;;)
    {
        switch (g_state)
        {
            case STATE_STARTUP:
            case STATE_DMA_HALTED:
                rx_switch_to_edge_detect_mode();
                break;
            case STATE_WAITING_FOR_FIRST_EDGE:
                /* Task runs at 1ms when edge-detecting. */
                delay = FC_CFG_RX_EDGE_DELAY_MS;
                break;
            case STATE_WATCHING_EDGES: {
                dt = xTaskGetTickCount() - g_last_tick;
                if (dt > FC_FCG_RX_SYNC_WINDOW_MS)
                {
                    rx_switch_to_dma_mode();
                    delay = FC_CFG_RX_UPDATE_DELAY_MS;
                }
                break;
            }
            case STATE_DMA_FLOWING:
                rx_read_and_decode();
                break;
            case STATE_WAITING_FOR_DMA_HALT:
            case STATE_WAITING_FOR_FIRST_DMA:
                break;
            default:
                while (1)
                {
                }; // TODO: Error handling in state machine
                break;
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

    // TODO: Can't recall why this is needed HERE, but it is needed.
    rx_uart_ready_set();

    sem_rx_packet_rdy = xSemaphoreCreateMutex();
    if (!sem_rx_packet_rdy)
    {
        /* TODO: ERROR HANDLER */
        while (1)
        {
        }
    }

    /* Setup the DMA interrupt, but don't start it until we sync */
    NVIC_SetPriority(GPDMA0_IRQN,
                     NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 63, 0));
    NVIC_EnableIRQ(GPDMA0_IRQN);

    /* Start the GPIO interrupt handler on P0[5], we'll stop it on sync */
    NVIC_SetPriority(SBUS_SYNC_IRQN,
                     NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 63, 0));
    NVIC_EnableIRQ(SBUS_SYNC_IRQN);
}

uint32_t
rx_get_sbus_steering(void)
{
    // TODO: Depends on transmitter configuration!
    return g_sbus_data.ch[1];
}
