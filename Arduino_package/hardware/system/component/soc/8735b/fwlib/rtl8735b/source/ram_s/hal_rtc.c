/**************************************************************************//**
 * @file     hal_rtc.c
 * @brief    This RTC HAL API functions.
 *
 * @version  V1.00
 * @date     2016-07-15
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

#include "hal_rtc.h"


#if CONFIG_RTC_EN

/**
 * @addtogroup ls_hal_rtc RTC
 * @{
 */

/**
 *  @brief To initial a RTC devices adapter.
 *
 *  @param[in] ppwm_adp The RTC devices adapter.
 *
 *  @returns HAL_OK: Initial succeed.
 */
hal_status_t hal_rtc_init(hal_rtc_adapter_t *prtc_adp)
{

	//dbg_printf ("!!!hal_rtc_init !!!\n\r");

	return hal_rtc_stubs.hal_rtc_init(prtc_adp);


}

/**
 *  @brief To deinitial a RTC devices adapter.
 *
 *  @param[in] ppwm_adp The RTC devices adapter.
 *
 *  @returns HAL_OK: Initial succeed.
 */
hal_status_t hal_rtc_deinit(hal_rtc_adapter_t *prtc_adp)
{
	return hal_rtc_stubs.hal_rtc_deinit(prtc_adp);
}

/**
 *  @brief To enable a RTC devive.
 *
 *  @param[in] prtc_adp The RTC device adapter.
 *
 *  @returns void
 */
void hal_rtc_enable(hal_rtc_adapter_t *prtc_adp)
{
	hal_rtc_stubs.hal_rtc_enable(prtc_adp);
}

/**
 *  @brief To disable a RTC devive.
 *
 *  @param[in] prtc_adp The RTC device adapter.
 *
 *  @returns void
 */
void hal_rtc_disable(hal_rtc_adapter_t *prtc_adp)
{
	hal_rtc_stubs.hal_rtc_disable(prtc_adp);
}

/**
 *  @brief To wait the PWM HW ready to set new RTC register.
 *
 *  @param[in] prtc_adp The RTC device adapter.
 *
 *  @returns void
 */
void hal_rtc_wait_ctrl_ready(hal_rtc_adapter_t *prtc_adp)
{
	hal_rtc_stubs.hal_rtc_wait_ctrl_ready(prtc_adp);
}

/**
 *  @brief To Write a RTC register.
 *
 *  @param[in] prtc_adp The RTC device adapter.
 *  @param[in] addr The RTC Reg base address.
 *  @param[in] data The RTC Write Data.
 *
 *  @returns void
 */
void hal_rtc_write(hal_rtc_adapter_t *prtc_adp, u16 addr, u32 data)
{
	hal_rtc_stubs.hal_rtc_write(prtc_adp, addr, data);
}

/**
 *  @brief To Read a RTC register.
 *
 *  @param[in] prtc_adp The RTC device adapter.
 *  @param[in] addr The RTC Reg base address.
 *
 *  @returns HAL_ERR_PARA: Input arguments are invalid.
 *  @returns u32: RTC Data.
 */
u32 hal_rtc_read(hal_rtc_adapter_t *prtc_adp, u16 addr)
{
	return hal_rtc_stubs.hal_rtc_read(prtc_adp, addr);
}

/**
 *  @brief To set the time of the RTC
 *
 *  @param[in] prtc_adp The RTC device adapter.
 *  @param[in] ptm_reg The tm structure information.
 *  @param[in] leap_year, Is Leap Year. 1: leap year
 *
 *  @returns     HAL_OK:  Setting succeed.
 *  @returns     HAL_ERR_PARA:  Input arguments are invalid.
 */

hal_status_t hal_rtc_set_time(hal_rtc_adapter_t *prtc_adp, hal_tm_reg_t *ptm_reg, u16 leap_year)
{
	return hal_rtc_stubs.hal_rtc_set_time(prtc_adp, ptm_reg, leap_year);
}

/**
 *  @brief To set RTC Alarm
 *
 *  @param[in] prtc_adp The RTC device adapter.
 *
 *  @returns     HAL_OK:  Setting succeed.
 */
u32 hal_rtc_read_time(hal_rtc_adapter_t *prtc_adp)
{
	return hal_rtc_stubs.hal_rtc_read_time(prtc_adp);
}

/**
 *  @brief To set RTC Alarm
 *
 *  @param[in] prtc_adp The RTC device adapter.
 *  @param[in] prtc_alarm The RTC alarm adapter.
 *
 *  @returns     HAL_OK:  Setting succeed.
 *  @returns     HAL_ERR_PARA:  Input arguments are invalid.
 */

hal_status_t hal_rtc_set_alarm(hal_rtc_adapter_t *prtc_adp, hal_rtc_alarm_t *prtc_alarm)
{
	return hal_rtc_stubs.hal_rtc_set_alarm(prtc_adp, prtc_alarm);
}

/**
 *  @brief To read the current time of RTC
 *
 *  @param[in] prtc_adp The RTC device adapter.
 *
 *  @returns     HAL_OK:  Setting succeed.
 */
u32 hal_rtc_read_alarm(hal_rtc_adapter_t *prtc_adp)
{
	return hal_rtc_stubs.hal_rtc_read_alarm(prtc_adp);
}

/**
 *  @brief To register the RTC interrupt.
 *
 *  @param[in] prtc_adp The RTC device adapter.
 *  @param[in] callback The callback function. It will be called when the interrupt is occurred.
 *  @param[in] arg The argument of the callback function.
 *
 *  @returns void
 */
void hal_rtc_reg_alarm_irq(hal_rtc_adapter_t *prtc_adp, rtc_alarm_callback_t callback, void *arg)
{
	hal_rtc_stubs.hal_rtc_reg_alarm_irq(prtc_adp, callback, arg);
}

/**
 *  @brief To un-register the RTC interrupt.
 *
 *  @param[in] prtc_adp The RTC device adapter.
 *
 *  @returns void
 */
void hal_rtc_unreg_alarm_irq(hal_rtc_adapter_t *prtc_adp)
{
	hal_rtc_stubs.hal_rtc_unreg_alarm_irq(prtc_adp);
}

/**
 *  @brief To set RTC Cnt Alarm
 *
 *  @param[in] prtc_adp The RTC device adapter.
 *  @param[in] cnt_alarm The RTC alarm paramter. bit 0 -> sec, bit 1 -> min, bit 2 -> hrs, bit 3 -> dow..bit 7 -> doy
 *
 *  @returns     HAL_OK:  Setting succeed.
 *  @returns     HAL_ERR_PARA:  Input arguments are invalid.
 */
hal_status_t hal_rtc_set_cnt_alarm(hal_rtc_adapter_t *prtc_adp, u8 cnt_alarm)
{
	return hal_rtc_stubs.hal_rtc_set_cnt_alarm(prtc_adp, cnt_alarm);
}

/**
 *  @brief To set the compensation value of the RTC CLK
 *
 *  @param[in] prtc_adp The RTC device adapter.
 *  @param[in] func_en The RTC compensation function enable. 1: Enable; 0:Disable
 *
 *  @returns     HAL_OK:  Setting succeed.
 *  @returns     HAL_ERR_PARA:  Input arguments are invalid.
 */
hal_status_t hal_rtc_set_comp(hal_rtc_adapter_t *prtc_adp, u8 func_en)
{
	return hal_rtc_stubs.hal_rtc_set_comp(prtc_adp, func_en);
}

/**
 *  @brief This function is to set  RTC leap year register.
 *
 *  @param[in] prtc_adp The RTC device adapter.
 *
 *  @returns void
 */
void hal_rtc_set_leap_year(hal_rtc_adapter_t *prtc_adp)
{
	AON_TypeDef *aon = AON;
	aon->AON_REG_AON_LSFIF_RWD = prtc_adp->rtc_reg.RTC_TYPE_REG_RTC_TIM2 ; // LSF(low speed function) write*/
	aon->AON_REG_AON_LSFIF_CMD |= 0x28;     // REG_RTC_TIM2
	aon->AON_REG_AON_LSFIF_CMD |= 0xF << AON_SHIFT_AON_LSFIF_WE; // LSF register byte write enable
	aon->AON_REG_AON_LSFIF_CMD |= AON_BIT_AON_LSFIF_WR; // 1: LSF register write transfer, 0: LSF register read transfer
	aon->AON_REG_AON_LSFIF_CMD |=
		AON_BIT_AON_LSFIF_POLL; // Set this bit to do LSF register read or write transfer depend on BIT_AON_LSFIF_WR. When transfer done, this bit will be clear by HW

	// wait rtc ready
	while ((((aon->AON_REG_AON_LSFIF_CMD) & AON_BIT_AON_LSFIF_POLL) >> AON_SHIFT_AON_LSFIF_POLL) == 1) {
		;
	}

}


#endif
