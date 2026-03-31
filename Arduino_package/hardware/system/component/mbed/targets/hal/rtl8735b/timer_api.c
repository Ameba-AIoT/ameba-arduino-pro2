/**************************************************************************//**
 * @file     timer_api.c
 * @brief    This file implements the mbed HAL API for timer function.
 *
 * @version  V1.00
 * @date     2017-07-25
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
#include "hal_timer.h"
#include "timer_api.h"
static hal_timer_group_adapter_t _timer_group0;
u8 init = 0, clk_sel = 0;
/**
  * @brief  Initializes the timer device, include timer registers and interrupt.
  * @param  obj: timer object define in application software.
  * @param  tid: general timer ID, 0xFF will auto allocate free general timer ID
  * @retval none
  */
void gtimer_init(gtimer_t *obj, uint32_t tid)
{
	hal_status_t ret;
	timer_id_t located_tid;
	uint8_t tmr_list[2];

	tmr_list[0] = tid;
	tmr_list[1] = 0xFF; // end of list
	if (init == 0) {
		if (clk_sel == 0) {
			hal_sys_peripheral_en(TIMER0_SYS, ENABLE);   // Enable TIMER clock and power on PON
			hal_timer_group_init(&_timer_group0, 0);  // time group 0
			//hal_osc4m_cal();
			hal_timer_group_sclk_sel(&_timer_group0, GTimerSClk_40M);    // Group1 Sclk:40M
			init = 1;
		} else {
			hal_sys_peripheral_en(TIMER0_SYS, ENABLE);   // Enable TIMER clock and power on PON
			hal_timer_group_init(&_timer_group0, 0);  // time group 0
			//hal_osc4m_cal();
			hal_timer_group_sclk_sel(&_timer_group0, GTimerSClk_4M);    // Group1 Sclk:4M
			init = 1;
		}
	}
	if (tid == 0xFF) {
		located_tid = hal_timer_allocate(NULL);
	} else {
		located_tid = hal_timer_allocate(tmr_list);
	}

	if (located_tid >= MaxGTimerNum) {
		DBG_TIMER_WARN("gtimer_init: Timer%u is in use\r\n", tid);
		return;
	}
	ret = hal_timer_init(&obj->timer_adp, (timer_id_t)located_tid);
	if (ret != HAL_OK) {
		DBG_TIMER_WARN("gtimer_init: init err (0x%x)\r\n", ret);
	} else {
		DBG_TIMER_INFO("gtimer_init: Timer %u init was succeed\r\n", located_tid);
	}
}

/**
  * @brief  Deinitializes the timer device, include timer function and interrupt.
  * @param  obj: timer object define in application software.
  * @retval none
  */
void gtimer_deinit(gtimer_t *obj)
{
	hal_timer_deinit(&obj->timer_adp);
}

/**
  * @brief  Get counter value of the specified timer.
  * @param  obj: timer object define in application software.
  * @retval value: counter value
  */
uint32_t gtimer_read_tick(gtimer_t *obj)
{
	return hal_timer_indir_read(&obj->timer_adp);
}

/**
  * @brief  Get count value in microseconds of the specified timer.
  * @param  obj: timer object define in application software.
  * @retval value: count value in microseconds.
  */
uint64_t gtimer_read_us(gtimer_t *obj)
{
#if 0
	// u64 version
	return hal_timer_read_us64(&obj->timer_adp);
#else
	// u32 version
	return (uint64_t)hal_timer_read_us(&obj->timer_adp);
#endif
}

/**
  * @brief  Change period of the specified timer.
  * @param  obj: timer object define in application software.
  * @param  duration_us: the new period to be set in microseconds.
  * @retval none
  */
void gtimer_reload(gtimer_t *obj, uint32_t duration_us)
{
	uint32_t act_us;

	act_us = hal_timer_set_timeout(&obj->timer_adp, duration_us, 1);
	DBG_TIMER_INFO("gtimer_reload: actual timeout=%lu\n", act_us);
}

/**
  * @brief  Start the specified timer and enable update interrupt.
  * @param  obj: timer object define in application software.
  * @retval none
  */
void gtimer_start(gtimer_t *obj)
{
	hal_timer_enable(&obj->timer_adp);
}

/**
  * @brief Start the specified timer in one-shot mode with specified period and interrupt handler.
  * @param  obj: timer object define in application software.
  * @param  duration_us: the new period to be set in microseconds.
  * @param  handler: user defined IRQ callback function
  * @param  hid: user defined IRQ callback parameter
  * @retval none
  * @note This function set the timer into one-shot mode which stops after the first time the counter overflows.
  */
void gtimer_start_one_shout(gtimer_t *obj, uint32_t duration_us, void *handler, uint32_t hid)
{
	hal_timer_start_one_shot(&obj->timer_adp, duration_us, (timer_callback_t)handler, (void *)hid);
}

/**
  * @brief Start the specified timer in periodical mode with specified period and interrupt handler.
  * @param  obj: timer object define in application software.
  * @param  duration_us: the new period to be set in microseconds.
  * @param  handler: user defined IRQ callback function
  * @param  hid: user defined IRQ callback parameter
  * @retval none
  * @note This functon set the timer into periodical mode which will restart to count from 0 each time the counter overflows.
  */
void gtimer_start_periodical(gtimer_t *obj, uint32_t duration_us, void *handler, uint32_t hid)
{
	hal_timer_start_periodical(&obj->timer_adp, duration_us, (timer_callback_t) handler, (void *)hid);
}

/**
  * @brief Disable the specified timer peripheral.
  * @param  obj: timer object define in application software.
  * @retval none
  */
void gtimer_stop(gtimer_t *obj)
{
	hal_timer_disable(&obj->timer_adp);
}

/**
  * @brief Enable a G-timer alarm.
  * @param  obj: timer object define in application software.
  * @param  almid: The ID of the alarm to be enabled. A timer has 4 alarm, so the valid ID is 0 ~ 3.
  * @param  time_us: The time period of the alarm, which is start when the timer is enabled.
  * @param  handler: The call-back function for the alarm is expired.
  * @param  hid: The argument of the call-back function.
  * @retval none
  */
void gtimer_enable_alarm(gtimer_t *obj, alarmid_t almid, uint32_t time_us, void *handler, uint32_t hid)
{
	hal_timer_reg_meirq(&obj->timer_adp, almid, (timer_callback_t)handler, (void *)hid);
	hal_timer_enable_match_event(&obj->timer_adp, (timer_match_event_t)almid, time_us);
}

/**
  * @brief To disable a G-timer alarm.
  * @param  obj: timer object define in application software.
  * @param  almid: The ID of the alarm to be disabled.
  * @retval none
  */
void gtimer_disable_alarm(gtimer_t *obj, alarmid_t almid)
{
	hal_timer_me_ctrl(&obj->timer_adp, (timer_match_event_t)almid, 0);
}

/**
  * @brief To select a G-timer0 clock source.
  * @param  clock_sel: 0:40MHz,1:4MHz
  * @retval none
  */
void gtimer_clock_sel(u8 clock_sel)
{
	clk_sel = clock_sel;
}

#ifdef ARDUINO_SDK
void gtimer_init_arduino(gtimer_t *obj, uint32_t tid, u8 arduino_pm_clk_sel)
{
	hal_status_t ret;
	timer_id_t located_tid;
	uint8_t tmr_list[2];

	tmr_list[0] = tid;
	tmr_list[1] = 0xFF; // end of list
	if (init == 0) {
		if (arduino_pm_clk_sel == 0) {
			hal_sys_peripheral_en(TIMER0_SYS, ENABLE);   // Enable TIMER clock and power on PON
			hal_timer_group_init(&_timer_group0, 0);  // time group 0
			//hal_osc4m_cal();
			hal_timer_group_sclk_sel(&_timer_group0, GTimerSClk_40M);    // Group1 Sclk:40M
			init = 1;
		} else {
			hal_sys_peripheral_en(TIMER0_SYS, ENABLE);   // Enable TIMER clock and power on PON
			hal_timer_group_init(&_timer_group0, 0);  // time group 0
			//hal_osc4m_cal();
			hal_timer_group_sclk_sel(&_timer_group0, GTimerSClk_4M);    // Group1 Sclk:4M
			init = 1;
		}
	}
	if (tid == 0xFF) {
		located_tid = hal_timer_allocate(NULL);
	} else {
		located_tid = hal_timer_allocate(tmr_list);
	}

	if (located_tid >= MaxGTimerNum) {
		DBG_TIMER_WARN("gtimer_init: Timer%u is in use\r\n", tid);
		return;
	}
	ret = hal_timer_init(&obj->timer_adp, (timer_id_t)located_tid);
	if (ret != HAL_OK) {
		DBG_TIMER_WARN("gtimer_init: init err (0x%x)\r\n", ret);
	} else {
		DBG_TIMER_INFO("gtimer_init: Timer %u init was succeed\r\n", located_tid);
	}
}
#endif

