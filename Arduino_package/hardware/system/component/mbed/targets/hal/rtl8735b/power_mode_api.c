/**************************************************************************//**
 * @file     power_mode_api.c
 * @brief    This file implements the mbed HAL API for POWER MODE function.
 *
 * @version  V1.00
 * @date     2018-06-25
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2022 Realtek Corporation. All rights reserved.
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

#include "objects.h"
#include "hal_power_mode.h"
#include "hal_power_mode_nsc.h"
#include "power_mode_api.h"
#include "pinmap.h"
#include "gpio_irq_api.h"
#include "gpio_irq_ex_api.h"

//extern void sys_interrupt_enable(void);
//extern void sys_interrupt_disable(void);
/**
  * @brief The stubs functions table to exports POWER MODE HAL functions in ROM.
  */

//extern const hal_power_mode_func_stubs_t hal_power_mode_stubs;

/**
 *  @brief The function for ls deep sleep mode.
 *
 *  @param[in]  Option, To slect AON Timer and GPIO...etc
 *                - bit[3]: the COMP as a Wake up event.
 *                - bit[2]: the RTC Wake up event.
 *                - bit[1]: the AON GPIO as a Wake up event.
 *                - bit[0]: the AON Timer Wake up event.
 *  @param[in]  SDuration, wake up after SDuration value. Uint: us
 *  @param[in]  Clock, 1: 4MHz, 0: 100kHz.
 *
 *  @returns void
 */
void DeepSleep(u8 Option, u32 SDuration, u8 Clock)
{
	hal_DeepSleep(Option, SDuration, Clock);
}


/**
 *  @brief The function for sleep mode.
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
 *  @param[in]  GpioOption, Select GPIO pin as a wake up trigger.
 *
 *  @returns void
 */
void SleepCG(u16 Option, u32 SDuration, u8 Clock, u8 SramOption)
{
	//sys_interrupt_disable();
	//hal_gpio_pull_ctrl(PA_1, Pin_PullDown);
	hal_SleepCG(Option, SDuration, Clock, SramOption);
	//sys_interrupt_enable();
}

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
 *  @returns
 *                - wake reason.
 */
u32 Standby(u16 Option, u32 SDuration, u8 Clock, u8 SramOption)
{
	//hal_gpio_pull_ctrl(PA_1, Pin_PullDown);
	return hal_SleepPG(Option, SDuration, Clock, SramOption);
}

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
 *                - bit[4]: the WLAN RX status.
 *                - bit[3]: the WLAN Wake up status.
 *                - bit[2]: NA.
 *                - bit[1]: the PON GPIO Wake up status.
 *                - bit[0]: the GTimer0 Wake up status.
 */
u32 Get_wake_reason(void)
{
	return hal_get_wake_reason();
}

/**
*  @brief The function will clear AON Timer ISR.
*  @param[in]  none
*  @returns void
*/
void Aon_timer_clear(void)
{
	hal_aon_timer_clear();
}

