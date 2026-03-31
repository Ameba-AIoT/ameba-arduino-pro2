/**************************************************************************//**
 * @file     rtc_api.c
 * @brief    This file implements the RTC Mbed HAL API functions.
 *
 * @version  V1.00
 * @date     2017-05-25
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

#include "rtc_api.h"
#include "hal_rtc_nsc.h"
#include "hal_rtc.h"
#if DEVICE_RTC
#include <time.h>
#include "timer_api.h"      // software-RTC: use a g-timer for the tick of the RTC

//#define SW_RTC_TIMER_ID        TIMER4

//static gtimer_t sw_rtc;
static struct tm rtc_timeinfo;
volatile hal_rtc_adapter_t sw_rtc;
static hal_tm_reg_t rtc_reg;
static hal_rtc_alarm_t rtc_alarm;
volatile hal_rtc_alarm_t prtc_alarm;
static int sw_rtc_en;
static u32 year_now;
volatile hal_rtc_adapter_t  rtc_veri_adpt;

//const static u8 dim[14] = {
//	31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 31, 28 };

static inline bool is_leap_year(unsigned int year)
{
	return (!(year % 4) && (year % 100)) || !(year % 400);
}




void rtc_init(void)
{
	uint32_t cali;
	// Enable RTC function
	hal_xtal_divider_enable(1);
	hal_32k_s1_sel(2);
	hal_rtc_init(&rtc_veri_adpt); // gianni nsc developemnet
	sw_rtc_en = 1;
	hal_rtc_set_comp(&rtc_veri_adpt, 1);
}
void rtc_free(void)
{
	// Disable RTC function
	sw_rtc_en = 0;
	//hal_rtc_deinit(&sw_rtc);
	hal_rtc_deinit(&rtc_veri_adpt);
}

int rtc_isenabled(void)
{
	return sw_rtc_en;
}

time_t rtc_read(void)
{

	uint32_t ret, buff;
	uint32_t i, year, mon, date;
	uint32_t day, hour, min, sec;
	uint32_t *src;
	time_t seconds;
	struct tm *timeinfo;
	uint32_t rtc_status;
	time_t t;

	hal_rtc_read_time((hal_rtc_adapter_t *) &rtc_veri_adpt);

	rtc_timeinfo.tm_sec = ((rtc_veri_adpt.rtc_reg.RTC_TYPE_REG_RTC_TIM0 & BIT_MASK_RTC_SEC) >> BIT_SHIFT_RTC_SEC);        /* seconds,  range 0 to 59          */
	rtc_timeinfo.tm_min = ((rtc_veri_adpt.rtc_reg.RTC_TYPE_REG_RTC_TIM0 & BIT_MASK_RTC_MIN) >> BIT_SHIFT_RTC_MIN);        /* minutes, range 0 to 59           */
	rtc_timeinfo.tm_hour = ((rtc_veri_adpt.rtc_reg.RTC_TYPE_REG_RTC_TIM0 & BIT_MASK_RTC_HRS) >> BIT_SHIFT_RTC_HRS);       /* hours, range 0 to 23             */
	rtc_timeinfo.tm_mday = ((rtc_veri_adpt.rtc_reg.RTC_TYPE_REG_RTC_TIM1 & BIT_MASK_RTC_DOM) >> BIT_SHIFT_RTC_DOM);       /* day of the month, range 1 to 31  */
	rtc_timeinfo.tm_wday = ((rtc_veri_adpt.rtc_reg.RTC_TYPE_REG_RTC_TIM0 & BIT_MASK_RTC_DOW) >> BIT_SHIFT_RTC_DOW);       /* day of the week, range 0 to 6    */
	rtc_timeinfo.tm_yday = ((rtc_veri_adpt.rtc_reg.RTC_TYPE_REG_RTC_TIM2 & BIT_MASK_RTC_DOY) >> BIT_SHIFT_RTC_DOY) - 1;       /* day in the year, range 0 to 365  */
	rtc_timeinfo.tm_mon = ((rtc_veri_adpt.rtc_reg.RTC_TYPE_REG_RTC_TIM1 & BIT_MASK_RTC_MON) >> BIT_SHIFT_RTC_MON) - 1;        /* month, range 0 to 11             */
	rtc_timeinfo.tm_year = ((rtc_veri_adpt.rtc_reg.RTC_TYPE_REG_RTC_TIM1 & BIT_MASK_RTC_YEAR) >> BIT_SHIFT_RTC_YEAR) - 1900;  /* The number of years since 1900   */
	// Convert to timestamp
	t = mktime(&rtc_timeinfo);
	//  dbg_printf("!!!!!!hal_rtc_set_time_rtl8735b: prtc_adp->rtc_reg.RTC_TYPE_REG_RTC_TIM2 %x \r\n", rtc_veri_adpt.rtc_reg.RTC_TYPE_REG_RTC_TIM2); // gianni

	return t;
}


void rtc_write(time_t t)
{
	// Convert the time in to a tm
	struct tm *timeinfo = localtime(&t); // When time_t is 32bit, it will overflow after 18 Jan 2038.
	u8 leap_year = 0;   // 1: Leap Year
	//struct tm *timeinfo = gmtime(&t);

	if (timeinfo == NULL) {
		// Error
		return;
	}
	leap_year = is_leap_year(timeinfo->tm_year + 1900);
	year_now = timeinfo->tm_year + 1900;
	// Set the RTC
	rtc_reg.sec  = timeinfo->tm_sec;
	rtc_reg.min  = timeinfo->tm_min;
	rtc_reg.hour = timeinfo->tm_hour;
	rtc_reg.mday = timeinfo->tm_mday;
	rtc_reg.wday = timeinfo->tm_wday;
	rtc_reg.yday = timeinfo->tm_yday;
	rtc_reg.mon  = timeinfo->tm_mon;
	rtc_reg.year = timeinfo->tm_year;
	if (hal_rtc_set_time(&sw_rtc, &rtc_reg, leap_year) != HAL_OK) {
		return;
	}
	dbg_printf("year_Day %d\r\n", timeinfo->tm_yday);
	dbg_printf("Current local time and date: %s\r\n", asctime(timeinfo));

}

/**
  * @brief  Set the specified RTC Alarm and interrupt.
  * @param  alarm: alarm object define in application software.
  * @param  alarmHandler:  alarm interrupt callback function.
  * @retval   status:
  *            - 1: success
  *            - Others: failure
  */
u32 rtc_set_alarm(alarm_t *alrm, alarm_irq_handler alarmHandler)
{
	//rtc_alarm_handler = alarmHandler;

	/* set alarm */
	prtc_alarm.sec  = alrm->sec;
	prtc_alarm.min  = alrm->min;
	prtc_alarm.hour = alrm->hour;
	prtc_alarm.yday = alrm->yday;
	hal_rtc_reg_alarm_irq(&rtc_veri_adpt, (rtc_alarm_callback_t)alarmHandler, (void *)0);
	if (hal_rtc_set_alarm(&rtc_veri_adpt, &prtc_alarm) != HAL_OK) {
		return _FALSE;
	}

	return _TRUE;
}
void rtc_set_alarm_time(time_t t, alarm_irq_handler alarmHandler)
//void rtc_alarm_test(time_t t)
{

	struct tm *timeinfo = localtime(&t);
	uint32_t i, year, mon, date;
	uint32_t day, hour, min, sec;

	prtc_alarm.sec  = timeinfo->tm_sec;
	prtc_alarm.min  = timeinfo->tm_min;
	prtc_alarm.hour = timeinfo->tm_hour;
	prtc_alarm.yday = timeinfo->tm_yday + 1;

	timeinfo->tm_isdst = -1;
	hal_rtc_reg_alarm_irq(&rtc_veri_adpt, (rtc_alarm_callback_t)alarmHandler, (void *)0);
	//hal_rtc_reg_alarm_irq(&sw_rtc, (rtc_alarm_callback_t)rtc_handler, (void *)0);
	hal_rtc_set_alarm((hal_rtc_adapter_t *)&rtc_veri_adpt, (hal_rtc_alarm_t *)&prtc_alarm);
}

/**
  * @brief  Disable RTC Alarm and function.
  * @param  none
  * @retval   none
  */
void rtc_disable_alarm(void)
{
	hal_rtc_unreg_alarm_irq(&sw_rtc);
	//rtc_alarm_handler = NULL;
}

/**
  * @brief  To set the compensation value of the RTC CLK.
  * @param  func_en The RTC compensation function enable. 1: Enable; 0:Disable
  * @retval   status:
  *            - 1: success
  *            - Others: failure
  */
u32 rtc_set_comp(u8 func_en)
{
	if (hal_rtc_set_comp(&sw_rtc, func_en) != HAL_OK) {
		return _FALSE;
	}
	return _TRUE;
}

#endif  // endof "#if DEVICE_RTC"
