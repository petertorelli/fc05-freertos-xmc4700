/*******************************************************************************
* File Name: cycfg_peripherals.c
*
* Description:
* Peripheral Hardware Block configuration
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

#include "cycfg_peripherals.h"

const XMC_ERU_ETL_CONFIG_t eru_1_etl_3_config = 
{
    .input_a = ERU1_EXS3A,
    .enable_output_trigger = 1,
    .output_trigger_channel = XMC_ERU_ETL_OUTPUT_TRIGGER_CHANNEL3,
    .status_flag_mode = XMC_ERU_ETL_STATUS_FLAG_MODE_SWCTRL,
    .source = XMC_ERU1_ETL3,
    .edge_detection = XMC_ERU_ETL_EDGE_DETECTION_FALLING,
};
const XMC_ERU_OGU_CONFIG_t eru_1_ogu_3_config = 
{
    .enable_pattern_detection = 1,
    .service_request = XMC_ERU_OGU_SERVICE_REQUEST_ON_TRIGGER,
    .pattern_detection_input = XMC_ERU_OGU_PATTERN_DETECTION_INPUT3,
};
const XMC_UART_CH_CONFIG_t CYBSP_DEBUG_UART_config = 
{
    .baudrate = 115200UL,
    .normal_divider_mode = false,
    .data_bits = 8U,
    .frame_length = 8U,
    .stop_bits = 1U,
    .oversampling = 16U,
    .parity_mode = XMC_USIC_CH_PARITY_MODE_NONE,
};
const XMC_UART_CH_CONFIG_t SBUS_UART_config = 
{
    .baudrate = 100000UL,
    .normal_divider_mode = false,
    .data_bits = 8U,
    .frame_length = 8U,
    .stop_bits = 2U,
    .oversampling = 16U,
    .parity_mode = XMC_USIC_CH_PARITY_MODE_EVEN,
};


void init_cycfg_peripherals(void)
{
    XMC_ERU_ETL_Init(eru_1_etl_3_HW, &eru_1_etl_3_config);
    XMC_ERU_OGU_Init(eru_1_ogu_3_HW, &eru_1_ogu_3_config);
    XMC_UART_CH_InitEx(CYBSP_DEBUG_UART_HW, &CYBSP_DEBUG_UART_config, false);
    XMC_UART_CH_SetInputSource(CYBSP_DEBUG_UART_HW, (XMC_UART_CH_INPUT_t)XMC_USIC_CH_INPUT_DX0, CYBSP_DEBUG_UART_DX0_INPUT);
    XMC_UART_CH_SetSamplePoint(CYBSP_DEBUG_UART_HW, 8U);
    XMC_USIC_CH_SetFractionalDivider(CYBSP_DEBUG_UART_HW, XMC_USIC_CH_BRG_CLOCK_DIVIDER_MODE_FRACTIONAL, 851U);
    XMC_USIC_CH_SetBaudrateDivider(CYBSP_DEBUG_UART_HW, XMC_USIC_CH_BRG_CLOCK_SOURCE_DIVIDER, false, 64U, XMC_USIC_CH_BRG_CTQSEL_PDIV, 0U, 15U);
    XMC_USIC_CH_SetInterruptNodePointer(CYBSP_DEBUG_UART_HW, XMC_USIC_CH_INTERRUPT_NODE_POINTER_RECEIVE, 0U);
    XMC_UART_CH_EnableEvent(CYBSP_DEBUG_UART_HW, XMC_UART_CH_EVENT_STANDARD_RECEIVE);
    XMC_UART_CH_Start(CYBSP_DEBUG_UART_HW);
    XMC_UART_CH_InitEx(SBUS_UART_HW, &SBUS_UART_config, false);
    XMC_UART_CH_SetInputSource(SBUS_UART_HW, (XMC_UART_CH_INPUT_t)XMC_USIC_CH_INPUT_DX0, SBUS_UART_DX0_INPUT);
    XMC_UART_CH_SetSamplePoint(SBUS_UART_HW, 8U);
    XMC_USIC_CH_SetFractionalDivider(SBUS_UART_HW, XMC_USIC_CH_BRG_CLOCK_DIVIDER_MODE_FRACTIONAL, 1023U);
    XMC_USIC_CH_SetBaudrateDivider(SBUS_UART_HW, XMC_USIC_CH_BRG_CLOCK_SOURCE_DIVIDER, false, 89U, XMC_USIC_CH_BRG_CTQSEL_PDIV, 0U, 15U);
    XMC_USIC_CH_SetInterruptNodePointer(SBUS_UART_HW, XMC_USIC_CH_INTERRUPT_NODE_POINTER_RECEIVE, 0U);
    XMC_UART_CH_EnableEvent(SBUS_UART_HW, XMC_UART_CH_EVENT_STANDARD_RECEIVE);
    XMC_UART_CH_Start(SBUS_UART_HW);
}
