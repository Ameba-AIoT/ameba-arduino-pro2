/**************************************************************************//**
 * @file     hal_timer.c
 * @brief    This TIMER HAL API functions.
 *
 * @version  V1.00
 * @date     2020-11-12
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

#include "hal_timer.h"

#if CONFIG_GTIMER_EN //CONFIG_GTIMER_EN

/**
 * @addtogroup hs_hal_timer TIMER
 * @{
 */

/**
 *  @brief Reads the count of the system timer. It return the counter register value directly.
 *
 *  @returns    Current tick count of the system time, in us. This count value will be reset to 0
 *              when ever the counter register is overflowed.
 */
uint32_t hal_read_curtime_us(void)
{
#if 0
#define TG_B 0x4000B400

	uint32_t i;
	HAL_WRITE32(TG_B, 8, 0x80);
	for (i = 0; i < 100000; i++) {
		if ((HAL_READ32(TG_B, 8) & 0x80) == 0) {
			break;
		} else {
			__NOP();
		}
	}
	if ((CONFIG_TIMER_SCLK_FREQ == 32000) || (CONFIG_TIMER_SCLK_FREQ == 32768)) {
		return (HAL_READ32(TG_B, 0xC) << 5);
	} else {
		return HAL_READ32(TG_B, 0xC);
	}
#endif
	return hal_gtimer_stubs.hal_read_curtime();

}

/**
 *  @brief Makes a delay.
 *
 *  @param[in]  time_us  The delay period in micro-second.
 *
 *  @returns    void
 */
void hal_delay_us(uint32_t time_us)
{
#if 0
	uint32_t start = hal_read_curtime_us();
	while ((hal_read_curtime_us() - start) < time_us);
#endif
	uint32_t start = hal_gtimer_stubs.hal_read_curtime();
	while ((hal_gtimer_stubs.hal_read_curtime() - start) < time_us);

	//hal_gtimer_stubs.hal_delay_us (time_us);
}

/**
 *  @brief To check if current time is latter than the given expire time.
 *         The expired time is calculated by a start time plus a timeout period.
 *
 *  @param[in]  start_us  The start time of the timeout period, in us.
 *  @param[in]  timeout_us The timeout period, in us. The expire time is start_us + timeout_us.
 *
 *  @returns    Current time is expired or not.
 *                  - true: It is expired.
 *                  - false: It's not expire yet.
 */
BOOLEAN hal_is_timeout(u32 start_us, u32 timeout_us)
{
	u32 past_time;
	u32 cur_time;

	cur_time = hal_read_curtime_us();
	if (cur_time >= start_us) {
		past_time = cur_time - start_us;
	} else {
		// timer wrapped
		// 0xFFFFFFFF tick -> 0xFDF3B644 us
		past_time = 0xFDF3B644 - start_us + cur_time;
	}

	if (timeout_us > past_time) {
		return FALSE;
	} else {
		return TRUE;
	}
}


/** @} */ /* End of group hs_hal_timer */

#endif  // end of "#if CONFIG_GTIMER_EN"

