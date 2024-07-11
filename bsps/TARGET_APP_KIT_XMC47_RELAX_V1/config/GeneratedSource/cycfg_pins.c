/*******************************************************************************
* File Name: cycfg_pins.c
*
* Description:
* Pin configuration
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

#include "cycfg_pins.h"

const XMC_GPIO_CONFIG_t ioss_0_port_0_pin_4_config = 
{
    .mode = (XMC_GPIO_MODE_t)ioss_0_port_0_pin_4_MODE,
};
const XMC_GPIO_CONFIG_t ioss_0_port_0_pin_5_config = 
{
    .mode = (XMC_GPIO_MODE_t)ioss_0_port_0_pin_5_MODE,
};
const XMC_GPIO_CONFIG_t CYBSP_USER_BTN2_config = 
{
    .mode = (XMC_GPIO_MODE_t)CYBSP_USER_BTN2_MODE,
};
const XMC_GPIO_CONFIG_t CYBSP_USER_BTN_config = 
{
    .mode = (XMC_GPIO_MODE_t)CYBSP_USER_BTN_MODE,
};
const XMC_GPIO_CONFIG_t CYBSP_DEBUG_UART_RX_config = 
{
    .mode = (XMC_GPIO_MODE_t)CYBSP_DEBUG_UART_RX_MODE,
};
const XMC_GPIO_CONFIG_t CYBSP_DEBUG_UART_TX_config = 
{
    .mode = (XMC_GPIO_MODE_t)CYBSP_DEBUG_UART_TX_MODE,
    .output_level = XMC_GPIO_OUTPUT_LEVEL_LOW,
};
const XMC_GPIO_CONFIG_t ioss_0_port_2_pin_14_config = 
{
    .mode = (XMC_GPIO_MODE_t)ioss_0_port_2_pin_14_MODE,
    .output_level = XMC_GPIO_OUTPUT_LEVEL_LOW,
};
const XMC_GPIO_CONFIG_t ioss_0_port_3_pin_0_config = 
{
    .mode = (XMC_GPIO_MODE_t)ioss_0_port_3_pin_0_MODE,
    .output_level = XMC_GPIO_OUTPUT_LEVEL_LOW,
};
const XMC_GPIO_CONFIG_t ioss_0_port_3_pin_12_config = 
{
    .mode = (XMC_GPIO_MODE_t)ioss_0_port_3_pin_12_MODE,
    .output_level = XMC_GPIO_OUTPUT_LEVEL_LOW,
};
const XMC_GPIO_CONFIG_t ioss_0_port_3_pin_13_config = 
{
    .mode = (XMC_GPIO_MODE_t)ioss_0_port_3_pin_13_MODE,
    .output_level = XMC_GPIO_OUTPUT_LEVEL_LOW,
};
const XMC_GPIO_CONFIG_t ioss_0_port_3_pin_3_config = 
{
    .mode = (XMC_GPIO_MODE_t)ioss_0_port_3_pin_3_MODE,
    .output_level = XMC_GPIO_OUTPUT_LEVEL_LOW,
};
const XMC_GPIO_CONFIG_t CYBSP_USER_LED2_config = 
{
    .mode = (XMC_GPIO_MODE_t)CYBSP_USER_LED2_MODE,
    .output_level = XMC_GPIO_OUTPUT_LEVEL_LOW,
};
const XMC_GPIO_CONFIG_t CYBSP_USER_LED_config = 
{
    .mode = (XMC_GPIO_MODE_t)CYBSP_USER_LED_MODE,
    .output_level = XMC_GPIO_OUTPUT_LEVEL_LOW,
};


void init_cycfg_pins(void)
{
    XMC_GPIO_Init(ioss_0_port_0_pin_4_PORT, ioss_0_port_0_pin_4_PIN, &ioss_0_port_0_pin_4_config);
    XMC_GPIO_SetHardwareControl(ioss_0_port_0_pin_4_PORT, ioss_0_port_0_pin_4_PIN, ioss_0_port_0_pin_4_HWO);
    XMC_GPIO_Init(ioss_0_port_0_pin_5_PORT, ioss_0_port_0_pin_5_PIN, &ioss_0_port_0_pin_5_config);
    XMC_GPIO_SetHardwareControl(ioss_0_port_0_pin_5_PORT, ioss_0_port_0_pin_5_PIN, ioss_0_port_0_pin_5_HWO);
    XMC_GPIO_Init(CYBSP_USER_BTN2_PORT, CYBSP_USER_BTN2_PIN, &CYBSP_USER_BTN2_config);
    XMC_GPIO_SetHardwareControl(CYBSP_USER_BTN2_PORT, CYBSP_USER_BTN2_PIN, CYBSP_USER_BTN2_HWO);
    XMC_GPIO_Init(CYBSP_USER_BTN_PORT, CYBSP_USER_BTN_PIN, &CYBSP_USER_BTN_config);
    XMC_GPIO_SetHardwareControl(CYBSP_USER_BTN_PORT, CYBSP_USER_BTN_PIN, CYBSP_USER_BTN_HWO);
    XMC_GPIO_Init(CYBSP_DEBUG_UART_RX_PORT, CYBSP_DEBUG_UART_RX_PIN, &CYBSP_DEBUG_UART_RX_config);
    XMC_GPIO_SetHardwareControl(CYBSP_DEBUG_UART_RX_PORT, CYBSP_DEBUG_UART_RX_PIN, CYBSP_DEBUG_UART_RX_HWO);
    XMC_GPIO_Init(CYBSP_DEBUG_UART_TX_PORT, CYBSP_DEBUG_UART_TX_PIN, &CYBSP_DEBUG_UART_TX_config);
    XMC_GPIO_SetHardwareControl(CYBSP_DEBUG_UART_TX_PORT, CYBSP_DEBUG_UART_TX_PIN, CYBSP_DEBUG_UART_TX_HWO);
    XMC_GPIO_Init(ioss_0_port_2_pin_14_PORT, ioss_0_port_2_pin_14_PIN, &ioss_0_port_2_pin_14_config);
    XMC_GPIO_SetHardwareControl(ioss_0_port_2_pin_14_PORT, ioss_0_port_2_pin_14_PIN, ioss_0_port_2_pin_14_HWO);
    XMC_GPIO_Init(ioss_0_port_3_pin_0_PORT, ioss_0_port_3_pin_0_PIN, &ioss_0_port_3_pin_0_config);
    XMC_GPIO_SetHardwareControl(ioss_0_port_3_pin_0_PORT, ioss_0_port_3_pin_0_PIN, ioss_0_port_3_pin_0_HWO);
    XMC_GPIO_Init(ioss_0_port_3_pin_12_PORT, ioss_0_port_3_pin_12_PIN, &ioss_0_port_3_pin_12_config);
    XMC_GPIO_SetHardwareControl(ioss_0_port_3_pin_12_PORT, ioss_0_port_3_pin_12_PIN, ioss_0_port_3_pin_12_HWO);
    XMC_GPIO_Init(ioss_0_port_3_pin_13_PORT, ioss_0_port_3_pin_13_PIN, &ioss_0_port_3_pin_13_config);
    XMC_GPIO_SetHardwareControl(ioss_0_port_3_pin_13_PORT, ioss_0_port_3_pin_13_PIN, ioss_0_port_3_pin_13_HWO);
    XMC_GPIO_Init(ioss_0_port_3_pin_3_PORT, ioss_0_port_3_pin_3_PIN, &ioss_0_port_3_pin_3_config);
    XMC_GPIO_SetHardwareControl(ioss_0_port_3_pin_3_PORT, ioss_0_port_3_pin_3_PIN, ioss_0_port_3_pin_3_HWO);
    XMC_GPIO_Init(CYBSP_USER_LED2_PORT, CYBSP_USER_LED2_PIN, &CYBSP_USER_LED2_config);
    XMC_GPIO_SetHardwareControl(CYBSP_USER_LED2_PORT, CYBSP_USER_LED2_PIN, CYBSP_USER_LED2_HWO);
    XMC_GPIO_Init(CYBSP_USER_LED_PORT, CYBSP_USER_LED_PIN, &CYBSP_USER_LED_config);
    XMC_GPIO_SetHardwareControl(CYBSP_USER_LED_PORT, CYBSP_USER_LED_PIN, CYBSP_USER_LED_HWO);
}
