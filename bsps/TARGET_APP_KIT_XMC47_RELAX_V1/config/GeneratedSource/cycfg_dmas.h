/*******************************************************************************
* File Name: cycfg_dmas.h
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

#if !defined(CYCFG_DMAS_H)
#define CYCFG_DMAS_H

#include "cycfg_notices.h"
#include "xmc_dma.h"
#include "cycfg_routing.h"

#if defined(__cplusplus)
extern "C" {
#endif

#define GPDMA0_INTERRUPT_HANDLER GPDMA0_0_IRQHandler
#define GPDMA0_IRQN GPDMA0_0_IRQn
#define SBUS_DMA_HDLR_ENABLED 1U
#define SBUS_DMA_HDLR_NUM 0U
#define SBUS_DMA_HDLR_HW XMC_DMA0

extern const uint32_t SBUS_DMA_HDLR_events;
extern const XMC_DMA_CH_CONFIG_t SBUS_DMA_HDLR_config;

void SBUS_DMA_HDLR_reload(void);

void init_cycfg_dmas(void);

#if defined(__cplusplus)
}
#endif


#endif /* CYCFG_DMAS_H */
