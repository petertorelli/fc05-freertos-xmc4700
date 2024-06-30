/*******************************************************************************
* File Name: cycfg_dmas.c
*
* Description:
* DMA configuration
* This file was automatically generated and should not be modified.
* Configurator Backend 3.10.0
* device-db 4.16.0.6098
* mtb-xmclib-cat3 4.4.0.4715
*
********************************************************************************
* Copyright 2024 Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
********************************************************************************/

#include "cycfg_dmas.h"

extern void * g_sbus_src_ptr;
extern void * g_sbus_raw_dst_ptr;

const uint32_t SBUS_DMA_HDLR_events = 0U | XMC_DMA_CH_EVENT_BLOCK_TRANSFER_COMPLETE | 0U | 0U | 0U;
const XMC_DMA_CH_CONFIG_t SBUS_DMA_HDLR_config = 
{
    .enable_interrupt = true,
    .dst_transfer_width = XMC_DMA_CH_TRANSFER_WIDTH_8,
    .src_transfer_width = XMC_DMA_CH_TRANSFER_WIDTH_8,
    .dst_address_count_mode = XMC_DMA_CH_ADDRESS_COUNT_MODE_INCREMENT,
    .src_address_count_mode = XMC_DMA_CH_ADDRESS_COUNT_MODE_NO_CHANGE,
    .dst_burst_length = XMC_DMA_CH_BURST_LENGTH_1,
    .src_burst_length = XMC_DMA_CH_BURST_LENGTH_1,
    .enable_src_gather = 0U,
    .enable_dst_scatter = 0U,
    .transfer_flow = XMC_DMA_CH_TRANSFER_FLOW_P2M_DMA,
    .block_size = 25U,
    .transfer_type = XMC_DMA_CH_TRANSFER_TYPE_SINGLE_BLOCK,
    .priority = XMC_DMA_CH_PRIORITY_7,
    .src_handshaking = XMC_DMA_CH_SRC_HANDSHAKING_HARDWARE,
    .src_peripheral_request = DMA_PERIPHERAL_REQUEST(XMC_GPDMA0_CH0_SRC_PER, SBUS_UART_sr0_0_TRIGGER_IN),
};

void SBUS_DMA_HDLR_reload(void)
{
    XMC_DMA_CH_SetBlockSize(SBUS_DMA_HDLR_HW, SBUS_DMA_HDLR_NUM, 25U);    XMC_DMA_CH_SetSourceAddress(SBUS_DMA_HDLR_HW, SBUS_DMA_HDLR_NUM, (uint32_t)g_sbus_src_ptr);    XMC_DMA_CH_SetDestinationAddress(SBUS_DMA_HDLR_HW, SBUS_DMA_HDLR_NUM, (uint32_t)g_sbus_raw_dst_ptr);
}


void init_cycfg_dmas(void)
{
    XMC_DMA_Init(XMC_DMA0);
    XMC_DMA_CH_Init(SBUS_DMA_HDLR_HW, SBUS_DMA_HDLR_NUM, &SBUS_DMA_HDLR_config);
    XMC_DMA_CH_EnableEvent(SBUS_DMA_HDLR_HW, SBUS_DMA_HDLR_NUM, SBUS_DMA_HDLR_events);
    XMC_DMA_CH_SetEventHandler(SBUS_DMA_HDLR_HW, SBUS_DMA_HDLR_NUM, NULL);
    SBUS_DMA_HDLR_reload();
}
