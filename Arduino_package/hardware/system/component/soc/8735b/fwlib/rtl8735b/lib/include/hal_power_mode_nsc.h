/**************************************************************************//**
 * @file     hal_power_mode_nsc.h
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

#ifndef _HAL_POWER_MODE_NSC_H_
#define _HAL_POWER_MODE_NSC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "cmsis.h"
#include <arm_cmse.h>   /* Use CMSE intrinsics */
/**
 * @addtogroup hal_power_mode_nsc POWER MODE HAL NSC APIs.
 * @ingroup 8735b_hal
 * @{
 * @brief The POWER MODE HAL module of the AmebaProII platform.
 */
#if defined(CONFIG_BUILD_SECURE)

void NS_ENTRY hal_DeepSleep_nsc(u8 Option, u32 SDuration, u8 Clock);
void NS_ENTRY hal_SleepCG_nsc(u16 Option, u32 SDuration, u8 Clock, u8 SramOption);
u32 NS_ENTRY hal_SleepPG_nsc(u16 Option, u32 SDuration, u8 Clock, u8 SramOption);
u8   NS_ENTRY hal_power_lib_version_nsc(void);
void NS_ENTRY hal_syspll_peripll_spread_spectrum_en_nsc(u8 syspll_en, u8 peripll_en);
u32  NS_ENTRY  hal_get_wake_reason_nsc(void);
void NS_ENTRY hal_aon_timer_clear_nsc(void);

/** @} */ /* End of group hal_power_mode_nsc_api */
#endif // end of "#if defined(CONFIG_BUILD_SECURE)"

#if defined(CONFIG_BUILD_NONSECURE)
void  hal_DeepSleep_nsc(u8 Option, u32 SDuration, u8 Clock);
void  hal_SleepCG_nsc(u16 Option, u32 SDuration, u8 Clock, u8 SramOption);
u32  hal_SleepPG_nsc(u16 Option, u32 SDuration, u8 Clock, u8 SramOption);
u8    hal_power_lib_version_nsc(void);
void  hal_syspll_peripll_spread_spectrum_en_nsc(u8 syspll_en, u8 peripll_en);
u32   hal_get_wake_reason_nsc(void);
void  hal_aon_timer_clear_nsc(void);

#define hal_DeepSleep                               hal_DeepSleep_nsc
#define hal_SleepCG                                 hal_SleepCG_nsc
#define hal_SleepPG                                 hal_SleepPG_nsc
#define hal_power_lib_version                       hal_power_lib_version_nsc
#define hal_syspll_peripll_spread_spectrum_en       hal_syspll_peripll_spread_spectrum_en_nsc
#define hal_get_wake_reason                         hal_get_wake_reason_nsc
#define hal_aon_timer_clear                         hal_aon_timer_clear_nsc
#endif  // end of "#if defined(CONFIG_BUILD_NONSECURE)"

/** @} */ /* End of group hal_power_mode_nsc */

#ifdef __cplusplus
}
#endif

#endif  // #ifndef _RTL_8735B_POWER_MODE_H_

