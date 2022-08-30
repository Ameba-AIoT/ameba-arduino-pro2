/**************************************************************************//**
* @file        hal_uart_nsc.h
* @brief       The HAL Non-secure callable API implementation for the EFUSE
*
* @version     V1.00
* @date        2018-07-26
*
* @note
*
******************************************************************************
*
* Copyright(c) 2007 - 2017 Realtek Corporation. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the License); you may
* not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an AS IS BASIS, WITHOUT
* WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
******************************************************************************/



#ifndef _HAL_UART_NSC_H_
#define _HAL_UART_NSC_H_
#include "cmsis.h"
#include <arm_cmse.h>   /* Use CMSE intrinsics */

#ifdef  __cplusplus
extern "C"
{
#endif

#if defined(CONFIG_BUILD_SECURE)
//hal_status_t NS_ENTRY hal_uart_lp_sclk_select_nsc(phal_uart_adapter_t puart_adapter, uint8_t sclk_sel);
void NS_ENTRY hal_uart_en_ctrl_nsc(uint8_t uart_idx, BOOL en);
#endif  // end of "#if defined(CONFIG_BUILD_SECURE)"


#if defined(CONFIG_BUILD_NONSECURE)
//hal_status_t hal_uart_lp_sclk_select_nsc(phal_uart_adapter_t puart_adapter, uint8_t sclk_sel);
void hal_uart_en_ctrl_nsc(uint8_t uart_idx, BOOL en);

//#define hal_uart_lp_sclk_select              hal_uart_lp_sclk_select_nsc
#if !defined(ENABLE_SECCALL_PATCH)
#define hal_uart_en_ctrl                     hal_uart_en_ctrl_nsc
#else
void __wrap_hal_uart_en_ctrl(uint8_t uart_idx, BOOL en);
#define hal_uart_en_ctrl                     __wrap_hal_uart_en_ctrl
#endif
#endif  // end of "#if defined(CONFIG_BUILD_NONSECURE)"


#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_UART_NSC_H_"
