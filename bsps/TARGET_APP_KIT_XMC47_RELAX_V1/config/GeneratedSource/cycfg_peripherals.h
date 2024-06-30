/*******************************************************************************
* File Name: cycfg_peripherals.h
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

#if !defined(CYCFG_PERIPHERALS_H)
#define CYCFG_PERIPHERALS_H

#include "cycfg_notices.h"
#include "xmc_eru.h"
#include "cycfg_routing.h"
#include "xmc_uart.h"

#if defined(__cplusplus)
extern "C" {
#endif

#define eru_1_ers_3_ENABLED 1U
#define XMC_ERU1_ETL3 XMC_ERU_ETL_SOURCE_A
#define eru_1_etl_3_ENABLED 1U
#define eru_1_etl_3_NUM 3U
#define eru_1_etl_3_HW ERU1_ETL3
#define eru_1_ogu_3_ENABLED 1U
#define eru_1_ogu_3_NUM 3U
#define eru_1_ogu_3_HW ERU1_OGU3
#define eru_1_ogu_3_INTERRUPT_HANDLER ERU1_3_IRQHandler
#define eru_1_ogu_3_IRQN ERU1_3_IRQn
#define CYBSP_DEBUG_UART_ENABLED 1U
#define CYBSP_DEBUG_UART_NUM 0U
#define CYBSP_DEBUG_UART_HW XMC_UART0_CH0
#define CYBSP_DEBUG_UART_DX0_INPUT USIC0_CH0_DX0CR_DSEL_VALUE
#define CYBSP_DEBUG_UART_RECEIVE_EVENT_HANDLER USIC0_0_IRQHandler
#define CYBSP_DEBUG_UART_RECEIVE_EVENT_IRQN USIC0_0_IRQn
#define SBUS_UART_ENABLED 1U
#define SBUS_UART_NUM 0U
#define SBUS_UART_HW XMC_UART1_CH0
#define SBUS_UART_DX0_INPUT USIC1_CH0_DX0CR_DSEL_VALUE
#define SBUS_UART_RECEIVE_EVENT_HANDLER USIC1_0_IRQHandler
#define SBUS_UART_RECEIVE_EVENT_IRQN USIC1_0_IRQn

extern const XMC_ERU_ETL_CONFIG_t eru_1_etl_3_config;
extern const XMC_ERU_OGU_CONFIG_t eru_1_ogu_3_config;
extern const XMC_UART_CH_CONFIG_t CYBSP_DEBUG_UART_config;
extern const XMC_UART_CH_CONFIG_t SBUS_UART_config;

void init_cycfg_peripherals(void);

#if defined(__cplusplus)
}
#endif


#endif /* CYCFG_PERIPHERALS_H */
