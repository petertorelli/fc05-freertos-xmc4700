#pragma once

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "cybsp.h"
#include <stdio.h>

#define FC_CFG_RX_UPDATE_DELAY_MS 50u
#define FC_FCG_RX_SYNC_DELAY_MS   3u
#define FC_FCG_RX_SYNC_MAX_MS     6u
#define SBUS_SYNC_IRQN            eru_1_ogu_3_IRQN
#define SBUS_SYNC_HANDLER         eru_1_ogu_3_INTERRUPT_HANDLER
#define SBUS_HEADER               0x0f
#define SBUS_FOOTER               0x00
#define SBUS_FOOTER2              0x04

typedef struct sbus_data
{
    uint32_t ch[18]; // 32-bit for fixed-point math
    uint8_t  lost_frame;
    uint8_t  failsafe;
} sbus_data_t;

void rx_uart_ready_set(void);
void rx_task(void *pvParameters);
void rx_setup(void);
