/**************************************************************************//**
 * @file     hal_wdt_nsc.h
 * @brief    The HAL related definition and macros for the WDT device.
 *           Includes Registers and data type definition.
 * @version  V1.00
 * @date     2020-03-10
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

#ifndef _HAL_WDT_NSC_H_
#define _HAL_WDT_NSC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "cmsis.h"
#include <arm_cmse.h>   /* Use CMSE intrinsics */
/**
 * @addtogroup hs_hal_wdt WDT HAL NSC APIs.
 * @ingroup 8735b_hal
 * @{
 * @brief The WDT HAL module of the AmebaProII platform.
 */
#if defined(CONFIG_BUILD_SECURE)

void NS_ENTRY hal_wdt_set_timeout_nsc(uint32_t time_us);
void NS_ENTRY hal_wdt_init_nsc(uint32_t time_us);
void NS_ENTRY hal_wdt_enable_nsc(void);
void NS_ENTRY hal_wdt_disable_nsc(void);
void NS_ENTRY hal_wdt_refresh_nsc(void);
void NS_ENTRY hal_wdt_reg_irq_nsc(irq_handler_t handler, void *arg);
void NS_ENTRY hal_wdt_unreg_irq_nsc(void);
void NS_ENTRY hal_wdt_reset_nsc(u8 reset);
/** @} */ /* End of group hal_wdt__nsc_api */
#endif // end of "#if defined(CONFIG_BUILD_SECURE)"

#if defined(CONFIG_BUILD_NONSECURE)
void  hal_wdt_set_timeout_nsc(uint32_t time_us);
void  hal_wdt_init_nsc(uint32_t time_us);
void  hal_wdt_enable_nsc(void);
void  hal_wdt_disable_nsc(void);
void  hal_wdt_refresh_nsc(void);
void  hal_wdt_reg_irq_nsc(irq_handler_t handler, void *arg);
void  hal_wdt_unreg_irq_nsc(void);
void  hal_wdt_reset_nsc(u8 reset);

#define hal_wdt_set_timeout     hal_wdt_set_timeout_nsc
#define hal_wdt_init            hal_wdt_init_nsc
#define hal_wdt_enable          hal_wdt_enable_nsc
#define hal_wdt_disable         hal_wdt_disable_nsc
#define hal_wdt_refresh         hal_wdt_refresh_nsc
#define hal_wdt_reg_irq         hal_wdt_reg_irq_nsc
#define hal_wdt_unreg_irq       hal_wdt_unreg_irq_nsc
#define hal_wdt_reset           hal_wdt_reset_nsc
#endif  // end of "#if defined(CONFIG_BUILD_NONSECURE)"

/** @} */ /* End of group hal_wdt_nsc */

#ifdef __cplusplus
}
#endif

#endif  // #ifndef _RTL_8735B_WDT_H_

