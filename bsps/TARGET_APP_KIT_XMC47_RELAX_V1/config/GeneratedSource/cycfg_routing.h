/*******************************************************************************
* File Name: cycfg_routing.h
*
* Description:
* Establishes all necessary connections between hardware elements.
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

#if !defined(CYCFG_ROUTING_H)
#define CYCFG_ROUTING_H

#if defined(__cplusplus)
extern "C" {
#endif

#include "cycfg_notices.h"

static inline void init_cycfg_routing(void) {}

#define ioss_0_port_0_pin_4_INPUT XMC_GPIO_MODE_INPUT_TRISTATE
#define ioss_0_port_0_pin_5_INPUT XMC_GPIO_MODE_INPUT_TRISTATE
#define ioss_0_port_1_pin_4_INPUT XMC_GPIO_MODE_INPUT_TRISTATE
#define ioss_0_port_1_pin_5_ALT XMC_GPIO_MODE_OUTPUT_ALT2
#define ioss_0_port_2_pin_14_ALT XMC_GPIO_MODE_OUTPUT_ALT2

#define SBUS_DMA_HDLR_src_per_0_TRIGGER_OUT 5
#define SBUS_UART_sr0_0_TRIGGER_IN 11

#define ERU1_EXS3A XMC_ERU_ETL_INPUT_A0
#define USIC0_CH0_DX0CR_DSEL_VALUE 1
#define USIC1_CH0_DX0CR_DSEL_VALUE 0
#define XMC_GPDMA0_CH0_SRC_PER 5

#if defined(__cplusplus)
}
#endif


#endif /* CYCFG_ROUTING_H */
