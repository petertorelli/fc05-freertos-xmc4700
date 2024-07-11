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

const XMC_CCU4_SLICE_COMPARE_CONFIG_t PWM1_compare_config = 
{
    .timer_mode = XMC_CCU4_SLICE_TIMER_COUNT_MODE_EA,
    .monoshot = XMC_CCU4_SLICE_TIMER_REPEAT_MODE_REPEAT,
    .shadow_xfer_clear = false,
    .dither_timer_period = false,
    .dither_duty_cycle = false,
    .prescaler_mode = XMC_CCU4_SLICE_PRESCALER_MODE_NORMAL,
    .mcm_enable = false,
    .prescaler_initval = XMC_CCU4_SLICE_PRESCALER_32,
    .float_limit = XMC_CCU4_SLICE_PRESCALER_32768,
    .dither_limit = 0U,
    .passive_level = XMC_CCU4_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
    .timer_concatenation = false,
};
const XMC_CCU4_SLICE_EVENT_CONFIG_t PWM1_event0_config = 
{
    .edge = XMC_CCU4_SLICE_EVENT_EDGE_SENSITIVITY_NONE,
    .level = XMC_CCU4_SLICE_EVENT_LEVEL_SENSITIVITY_ACTIVE_HIGH,
    .duration = XMC_CCU4_SLICE_EVENT_FILTER_DISABLED,
};
const XMC_CCU4_SLICE_EVENT_CONFIG_t PWM1_event1_config = 
{
    .edge = XMC_CCU4_SLICE_EVENT_EDGE_SENSITIVITY_NONE,
    .level = XMC_CCU4_SLICE_EVENT_LEVEL_SENSITIVITY_ACTIVE_HIGH,
    .duration = XMC_CCU4_SLICE_EVENT_FILTER_DISABLED,
};
const XMC_CCU4_SLICE_EVENT_CONFIG_t PWM1_event2_config = 
{
    .edge = XMC_CCU4_SLICE_EVENT_EDGE_SENSITIVITY_NONE,
    .level = XMC_CCU4_SLICE_EVENT_LEVEL_SENSITIVITY_ACTIVE_HIGH,
    .duration = XMC_CCU4_SLICE_EVENT_FILTER_DISABLED,
};
const XMC_CCU4_SLICE_COMPARE_CONFIG_t PWM2_compare_config = 
{
    .timer_mode = XMC_CCU4_SLICE_TIMER_COUNT_MODE_EA,
    .monoshot = XMC_CCU4_SLICE_TIMER_REPEAT_MODE_REPEAT,
    .shadow_xfer_clear = false,
    .dither_timer_period = false,
    .dither_duty_cycle = false,
    .prescaler_mode = XMC_CCU4_SLICE_PRESCALER_MODE_NORMAL,
    .mcm_enable = false,
    .prescaler_initval = XMC_CCU4_SLICE_PRESCALER_32,
    .float_limit = XMC_CCU4_SLICE_PRESCALER_32768,
    .dither_limit = 0U,
    .passive_level = XMC_CCU4_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
    .timer_concatenation = false,
};
const XMC_CCU4_SLICE_EVENT_CONFIG_t PWM2_event0_config = 
{
    .edge = XMC_CCU4_SLICE_EVENT_EDGE_SENSITIVITY_NONE,
    .level = XMC_CCU4_SLICE_EVENT_LEVEL_SENSITIVITY_ACTIVE_HIGH,
    .duration = XMC_CCU4_SLICE_EVENT_FILTER_DISABLED,
};
const XMC_CCU4_SLICE_EVENT_CONFIG_t PWM2_event1_config = 
{
    .edge = XMC_CCU4_SLICE_EVENT_EDGE_SENSITIVITY_NONE,
    .level = XMC_CCU4_SLICE_EVENT_LEVEL_SENSITIVITY_ACTIVE_HIGH,
    .duration = XMC_CCU4_SLICE_EVENT_FILTER_DISABLED,
};
const XMC_CCU4_SLICE_EVENT_CONFIG_t PWM2_event2_config = 
{
    .edge = XMC_CCU4_SLICE_EVENT_EDGE_SENSITIVITY_NONE,
    .level = XMC_CCU4_SLICE_EVENT_LEVEL_SENSITIVITY_ACTIVE_HIGH,
    .duration = XMC_CCU4_SLICE_EVENT_FILTER_DISABLED,
};
const XMC_CCU4_SLICE_COMPARE_CONFIG_t PWM3_compare_config = 
{
    .timer_mode = XMC_CCU4_SLICE_TIMER_COUNT_MODE_EA,
    .monoshot = XMC_CCU4_SLICE_TIMER_REPEAT_MODE_REPEAT,
    .shadow_xfer_clear = false,
    .dither_timer_period = false,
    .dither_duty_cycle = false,
    .prescaler_mode = XMC_CCU4_SLICE_PRESCALER_MODE_NORMAL,
    .mcm_enable = false,
    .prescaler_initval = XMC_CCU4_SLICE_PRESCALER_32,
    .float_limit = XMC_CCU4_SLICE_PRESCALER_32768,
    .dither_limit = 0U,
    .passive_level = XMC_CCU4_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
    .timer_concatenation = false,
};
const XMC_CCU4_SLICE_EVENT_CONFIG_t PWM3_event0_config = 
{
    .edge = XMC_CCU4_SLICE_EVENT_EDGE_SENSITIVITY_NONE,
    .level = XMC_CCU4_SLICE_EVENT_LEVEL_SENSITIVITY_ACTIVE_HIGH,
    .duration = XMC_CCU4_SLICE_EVENT_FILTER_DISABLED,
};
const XMC_CCU4_SLICE_EVENT_CONFIG_t PWM3_event1_config = 
{
    .edge = XMC_CCU4_SLICE_EVENT_EDGE_SENSITIVITY_NONE,
    .level = XMC_CCU4_SLICE_EVENT_LEVEL_SENSITIVITY_ACTIVE_HIGH,
    .duration = XMC_CCU4_SLICE_EVENT_FILTER_DISABLED,
};
const XMC_CCU4_SLICE_EVENT_CONFIG_t PWM3_event2_config = 
{
    .edge = XMC_CCU4_SLICE_EVENT_EDGE_SENSITIVITY_NONE,
    .level = XMC_CCU4_SLICE_EVENT_LEVEL_SENSITIVITY_ACTIVE_HIGH,
    .duration = XMC_CCU4_SLICE_EVENT_FILTER_DISABLED,
};
const XMC_CCU4_SLICE_COMPARE_CONFIG_t PWM4_compare_config = 
{
    .timer_mode = XMC_CCU4_SLICE_TIMER_COUNT_MODE_EA,
    .monoshot = XMC_CCU4_SLICE_TIMER_REPEAT_MODE_REPEAT,
    .shadow_xfer_clear = false,
    .dither_timer_period = false,
    .dither_duty_cycle = false,
    .prescaler_mode = XMC_CCU4_SLICE_PRESCALER_MODE_NORMAL,
    .mcm_enable = false,
    .prescaler_initval = XMC_CCU4_SLICE_PRESCALER_32,
    .float_limit = XMC_CCU4_SLICE_PRESCALER_32768,
    .dither_limit = 0U,
    .passive_level = XMC_CCU4_SLICE_OUTPUT_PASSIVE_LEVEL_LOW,
    .timer_concatenation = false,
};
const XMC_CCU4_SLICE_EVENT_CONFIG_t PWM4_event0_config = 
{
    .edge = XMC_CCU4_SLICE_EVENT_EDGE_SENSITIVITY_NONE,
    .level = XMC_CCU4_SLICE_EVENT_LEVEL_SENSITIVITY_ACTIVE_HIGH,
    .duration = XMC_CCU4_SLICE_EVENT_FILTER_DISABLED,
};
const XMC_CCU4_SLICE_EVENT_CONFIG_t PWM4_event1_config = 
{
    .edge = XMC_CCU4_SLICE_EVENT_EDGE_SENSITIVITY_NONE,
    .level = XMC_CCU4_SLICE_EVENT_LEVEL_SENSITIVITY_ACTIVE_HIGH,
    .duration = XMC_CCU4_SLICE_EVENT_FILTER_DISABLED,
};
const XMC_CCU4_SLICE_EVENT_CONFIG_t PWM4_event2_config = 
{
    .edge = XMC_CCU4_SLICE_EVENT_EDGE_SENSITIVITY_NONE,
    .level = XMC_CCU4_SLICE_EVENT_LEVEL_SENSITIVITY_ACTIVE_HIGH,
    .duration = XMC_CCU4_SLICE_EVENT_FILTER_DISABLED,
};
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
    XMC_CCU4_Init(ccu4_2_HW, XMC_CCU4_SLICE_MCMS_ACTION_TRANSFER_PR_CR);
    XMC_CCU4_StartPrescaler(ccu4_2_HW);
    XMC_CCU4_SLICE_CompareInit(PWM1_HW, &PWM1_compare_config);
    XMC_CCU4_SLICE_SetTimerCompareMatch(PWM1_HW, 49500U);
    XMC_CCU4_SLICE_SetTimerPeriodMatch(PWM1_HW, 56249U);
    XMC_CCU4_SetMultiChannelShadowTransferMode(ccu4_2_HW, XMC_CCU4_MULTI_CHANNEL_SHADOW_TRANSFER_SW_SLICE0);
    XMC_CCU4_EnableShadowTransfer(ccu4_2_HW,
        XMC_CCU4_SHADOW_TRANSFER_SLICE_0 |
        XMC_CCU4_SHADOW_TRANSFER_DITHER_SLICE_0 |
        XMC_CCU4_SHADOW_TRANSFER_PRESCALER_SLICE_0 );
    XMC_CCU4_SLICE_ConfigureEvent(PWM1_HW, XMC_CCU4_SLICE_EVENT_0, &PWM1_event0_config);
    XMC_CCU4_SLICE_ConfigureEvent(PWM1_HW, XMC_CCU4_SLICE_EVENT_1, &PWM1_event1_config);
    XMC_CCU4_SLICE_ConfigureEvent(PWM1_HW, XMC_CCU4_SLICE_EVENT_2, &PWM1_event2_config);
    XMC_CCU4_EnableClock(ccu4_2_HW, PWM1_NUM);
    XMC_CCU4_SLICE_SetTimerValue(PWM1_HW, 0U);
    XMC_CCU4_SLICE_StartTimer(PWM1_HW);
    XMC_CCU4_SLICE_CompareInit(PWM2_HW, &PWM2_compare_config);
    XMC_CCU4_SLICE_SetTimerCompareMatch(PWM2_HW, 49500U);
    XMC_CCU4_SLICE_SetTimerPeriodMatch(PWM2_HW, 56249U);
    XMC_CCU4_SetMultiChannelShadowTransferMode(ccu4_2_HW, XMC_CCU4_MULTI_CHANNEL_SHADOW_TRANSFER_SW_SLICE1);
    XMC_CCU4_EnableShadowTransfer(ccu4_2_HW,
        XMC_CCU4_SHADOW_TRANSFER_SLICE_1 |
        XMC_CCU4_SHADOW_TRANSFER_DITHER_SLICE_1 |
        XMC_CCU4_SHADOW_TRANSFER_PRESCALER_SLICE_1 );
    XMC_CCU4_SLICE_ConfigureEvent(PWM2_HW, XMC_CCU4_SLICE_EVENT_0, &PWM2_event0_config);
    XMC_CCU4_SLICE_ConfigureEvent(PWM2_HW, XMC_CCU4_SLICE_EVENT_1, &PWM2_event1_config);
    XMC_CCU4_SLICE_ConfigureEvent(PWM2_HW, XMC_CCU4_SLICE_EVENT_2, &PWM2_event2_config);
    XMC_CCU4_EnableClock(ccu4_2_HW, PWM2_NUM);
    XMC_CCU4_SLICE_SetTimerValue(PWM2_HW, 0U);
    XMC_CCU4_SLICE_StartTimer(PWM2_HW);
    XMC_CCU4_SLICE_CompareInit(PWM3_HW, &PWM3_compare_config);
    XMC_CCU4_SLICE_SetTimerCompareMatch(PWM3_HW, 49500U);
    XMC_CCU4_SLICE_SetTimerPeriodMatch(PWM3_HW, 56249U);
    XMC_CCU4_SetMultiChannelShadowTransferMode(ccu4_2_HW, XMC_CCU4_MULTI_CHANNEL_SHADOW_TRANSFER_SW_SLICE2);
    XMC_CCU4_EnableShadowTransfer(ccu4_2_HW,
        XMC_CCU4_SHADOW_TRANSFER_SLICE_2 |
        XMC_CCU4_SHADOW_TRANSFER_DITHER_SLICE_2 |
        XMC_CCU4_SHADOW_TRANSFER_PRESCALER_SLICE_2 );
    XMC_CCU4_SLICE_ConfigureEvent(PWM3_HW, XMC_CCU4_SLICE_EVENT_0, &PWM3_event0_config);
    XMC_CCU4_SLICE_ConfigureEvent(PWM3_HW, XMC_CCU4_SLICE_EVENT_1, &PWM3_event1_config);
    XMC_CCU4_SLICE_ConfigureEvent(PWM3_HW, XMC_CCU4_SLICE_EVENT_2, &PWM3_event2_config);
    XMC_CCU4_EnableClock(ccu4_2_HW, PWM3_NUM);
    XMC_CCU4_SLICE_SetTimerValue(PWM3_HW, 0U);
    XMC_CCU4_SLICE_StartTimer(PWM3_HW);
    XMC_CCU4_SLICE_CompareInit(PWM4_HW, &PWM4_compare_config);
    XMC_CCU4_SLICE_SetTimerCompareMatch(PWM4_HW, 49500U);
    XMC_CCU4_SLICE_SetTimerPeriodMatch(PWM4_HW, 56249U);
    XMC_CCU4_SetMultiChannelShadowTransferMode(ccu4_2_HW, XMC_CCU4_MULTI_CHANNEL_SHADOW_TRANSFER_SW_SLICE3);
    XMC_CCU4_EnableShadowTransfer(ccu4_2_HW,
        XMC_CCU4_SHADOW_TRANSFER_SLICE_3 |
        XMC_CCU4_SHADOW_TRANSFER_DITHER_SLICE_3 |
        XMC_CCU4_SHADOW_TRANSFER_PRESCALER_SLICE_3 );
    XMC_CCU4_SLICE_ConfigureEvent(PWM4_HW, XMC_CCU4_SLICE_EVENT_0, &PWM4_event0_config);
    XMC_CCU4_SLICE_ConfigureEvent(PWM4_HW, XMC_CCU4_SLICE_EVENT_1, &PWM4_event1_config);
    XMC_CCU4_SLICE_ConfigureEvent(PWM4_HW, XMC_CCU4_SLICE_EVENT_2, &PWM4_event2_config);
    XMC_CCU4_EnableClock(ccu4_2_HW, PWM4_NUM);
    XMC_CCU4_SLICE_SetTimerValue(PWM4_HW, 0U);
    XMC_CCU4_SLICE_StartTimer(PWM4_HW);
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
