/**************************************************************************//**
 * @file     hal_power_mode.h
 * @brief    The HAL API implementation for the POWER MODE device.
 * @version  V1.00
 * @date     2021-03-26
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

#ifndef _HAL_POWER_MODE_H_
#define _HAL_POWER_MODE_H_
#include "cmsis.h"
#include "rtl8735b_aon_type.h"
#include "hal_power_mode_nsc.h"
//#define VNDR_S      ((VNDR_S_TYPE_TypeDef*)         0x50002C00)
#define AON         ((AON_TypeDef*)            AON_BASE)

#ifdef  __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup hal_power_mode POWER MODE
 * @ingroup 8735_hal
 * @{
 * @brief The POWER MODE HAL module of the platform.
 */

#define     SLP_AON_TIMER   BIT0
#define     SLP_AON_GPIO    BIT1
#define     SLP_RTC         BIT2
#define     SLP_COMP        BIT3
#define     SLP_PON_GPIO    BIT4
#define     SLP_PWM         BIT5
#define     SLP_UART        BIT6
#define     SLP_GTIMER      BIT7
#define     SLP_WLAN        BIT8

//DSTBY
#define     DSTBY_AON_TIMER BIT0
#define     DSTBY_AON_GPIO  BIT1
#define     DSTBY_RTC       BIT2
#define     DSTBY_COMP      BIT3
#define     DSTBY_PON_GPIO  BIT4
#define     DSTBY_PWM       BIT5
#define     DSTBY_UART      BIT6
#define     DSTBY_GTIMER    BIT7
#define     DSTBY_WLAN      BIT8

//DS wake event
#define     DS_AON_TIMER    BIT0
#define     DS_AON_GPIO     BIT1
#define     DS_RTC          BIT2
#define     DS_COMP         BIT3


enum clk_idx {
	CLK_100K = 0,
	CLK_4M = 1,
};

void hal_sys_reg_irq(VOID);

/**
  * @brief The stubs functions table to exports POWER MODE HAL functions in ROM.
  */

//extern const hal_chg_func_stubs_t hal_chg_stubs;

/**
 *  @brief The function for ls deep sleep mode.
 *
 *  @param[in]  Option, To slect AON Timerand GPIO.
 *                - bit[3]: the COMPWake up event.
 *                - bit[2]: the RTC Wake up event.
 *                - bit[1]: the GPIO Wake up event.
 *                - bit[0]: the AON Timer Wake up event.
 *  @param[in]  SDuration, wake up after SDuration value. Uint: us
 *  @param[in]  Clock, 1: 4MHz, 0: 100kHz.
 *
 *  @returns void
 */
void hal_DeepSleep(u8  Option, u32 SDuration, u8 Clock);

/**
 *  @brief The function for SLeep CG mode.
 *
 *  @param[in]  Option, To slect GTimer, GPIO and PWM...etc
 *                - bit[8]: the WLAN Wake up event.
 *                - bit[7]: the GTIMER0 Wake up event.
 *                - bit[6]: the UART Wake up event.
 *                - bit[5]: the PWM Wake up event.
 *                - bit[4]: the PON GPIO Wake up event.
 *                - bit[3]: the COMPWake up event.
 *                - bit[2]: the RTC Wake up event.
 *                - bit[1]: the AON GPIO Wake up event.
 *                - bit[0]: the AON Timer Wake up event.
 *  @param[in]  SDuration, wake up after SDuration value. Uint: us
 *  @param[in]  Clock, 1: 4MHz, 0: 100kHz.
 *  @param[in]  SramOption, Select SRAM1~SRAM2 state.
 *                - 0: shutdown mode.
 *                - 1: retention mode.
 *                - 2: Normal mode.
 *  @returns void
 */
void hal_SleepCG(u16 Option, u32 SDuration, u8 Clock, u8 SramOption);

/**
 *  @brief The function for Standby mode.
 *
 *  @param[in]  Option, To slect GTimer, GPIO and PWM...etc
 *                - bit[8]: the WLAN Wake up event.
 *                - bit[7]: the GTIMER0 Wake up event.
 *                - bit[6]: the UART Wake up event.
 *                - bit[5]: the PWM Wake up event.
 *                - bit[4]: the PON GPIO Wake up event.
 *                - bit[3]: the COMPWake up event.
 *                - bit[2]: the RTC Wake up event.
 *                - bit[1]: the AON GPIO Wake up event.
 *                - bit[0]: the AON Timer Wake up event.
 *  @param[in]  SDuration, wake up after SDuration value. Uint: us
 *  @param[in]  Clock, 1: 4MHz, 0: 100kHz.
 *  @param[in]  SramOption, Select SRAM1~SRAM2 state.
 *                - 0: shutdown mode.
 *                - 1: retention mode.
 *                - 2: Normal mode.
 *  @returns void
 */
void hal_SleepPG(u16 Option, u32 SDuration, u8 Clock, u8 SramOption);

/**
 *  @brief The function for power lib version.
 *
 *
 *  @returns version
 */
u8 hal_power_lib_version(void);

/**
 *  @brief The function for get wake up reason.
 *  @returns wake up status
 *   wake up status:
 *                - bit[12]: the AON GPIO3 Wake up status.
 *                - bit[11]: the AON GPIO2 Wake up status.
 *                - bit[10]: the AON GPIO1 Wake up status.
 *                - bit[9]: the AON GPIO0 Wake up status.
 *                - bit[8]: the RTC Wake up status.
 *                - bit[7]: the COMP Wake up status.
 *                - bit[6]: the AON TIMER Wake up status.
 *                - bit[5]: the UART Wake up status.
 *                - bit[4]: NA.
 *                - bit[3]: the WLAN Wake up status.
 *                - bit[2]: NA.
 *                - bit[1]: the PON GPIO Wake up status.
 *                - bit[0]: the GTimer0 Wake up status.
 */
u32 hal_get_wake_reason(void);

/**
 *  @brief The function for syspll and peripll spread spectrum.
 *  @param[in]  syspll_en, 1: Enable SYSPLL spread spectrum function,
 *                        0: Disable SYSPLL spread spectrum function
 *  @param[in]  peripll_en, 1: Enable PERIPLL spread spectrum function,
 *                        0: Disable PERIPLL spread spectrum function
 *  @returns void
 */
void hal_syspll_peripll_spread_spectrum_en(u8 syspll_en, u8 peripll_en);

#ifdef  __cplusplus
}
#endif

/** @} */ /* End of group ls_hal_power_mode */

#endif  // end of "#define _HAL_POWER MODE_H_"
