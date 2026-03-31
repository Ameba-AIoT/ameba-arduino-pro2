/**************************************************************************//**
 * @file     us_ticker.c
 * @brief    This file implements the us ticker function for Mbed us ticker API functions.
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
#include <stddef.h>
#include "us_ticker_api.h"

#define USE_SYSTIME_AS_US_TICKER    1       // is share to use the system timer as the us-ticker
#define US_TICKER_ME_ID             0       // the Timer match event ID for the time stamp interrupt event

#if !USE_SYSTIME_AS_US_TICKER
static hal_timer_adapter_t us_ticker_adp;
static int us_ticker_inited;

void _us_ticker_irq_handler(void *Data)
{
	hal_timer_me_ctrl(&us_ticker_adp, US_TICKER_ME_ID, 0);
	us_ticker_irq_handler();
}

void us_ticker_init(void)
{
	timer_id_t tid;

	if (us_ticker_inited) {
		return;
	}

	tid = hal_timer_allocate(NULL);

	if (tid >= MaxGTimerNum) {
		DBG_MISC_ERR("us_ticker_init: No free G-Timer\n");
		return;
	}

	hal_timer_init_free_run(&us_ticker_adp, tid, GTimerCountUp, 1);
	hal_timer_reg_meirq(&us_ticker_adp, US_TICKER_ME_ID, _us_ticker_irq_handler, NULL);
	us_ticker_inited = 1;
}

uint32_t us_ticker_read(void)
{
	return hal_timer_read_us(&us_ticker_adp);
}

void us_ticker_set_interrupt(timestamp_t timestamp)
{
	uint64_t cur_time_us;
	uint32_t cur_tick;
	uint64_t duration_us;
	uint64_t timer_tick;
	uint8_t sclk_idx;

	cur_tick = hal_timer_indir_read(&us_ticker_adp);
	sclk_idx = us_ticker_adp.ptg_adp->sclk_idx;
	cur_time_us = hal_timer_read_us64(&us_ticker_adp);
	duration_us = timestamp - cur_time_us;
	timer_tick = hal_timer_convert_us_to_ticks64(duration_us, sclk_idx);
	timer_tick += cur_tick;
	timer_tick &= 0xFFFFFFFF;   // convert to 32-bits
	hal_timer_set_me_counter(&us_ticker_adp, US_TICKER_ME_ID, (uint32_t) timer_tick);
	hal_timer_me_ctrl(&us_ticker_adp, US_TICKER_ME_ID, 1);
}

#else

extern hal_timer_adapter_t system_timer;
static int us_ticker_inited;

void _us_ticker_irq_handler(void *Data)
{
	hal_timer_me_ctrl(&system_timer, US_TICKER_ME_ID, 0);
	us_ticker_irq_handler();
}

void us_ticker_init(void)
{
	if (us_ticker_inited) {
		return;
	}

	hal_timer_reg_meirq(&system_timer, US_TICKER_ME_ID, _us_ticker_irq_handler, NULL);
	us_ticker_inited = 1;
}

uint32_t us_ticker_read(void)
{
	return hal_read_curtime_us();
}

void us_ticker_set_interrupt(timestamp_t timestamp)
{
	uint64_t cur_time_us;
	uint32_t cur_tick;
	uint64_t duration_us;
	uint32_t timer_tick;
	uint8_t sclk_idx;

	cur_tick = hal_timer_indir_read(&system_timer);
	sclk_idx = system_timer.ptg_adp->sclk_idx;
	cur_time_us = hal_read_systime_us();
	duration_us = timestamp - cur_time_us;
	timer_tick = hal_timer_convert_us_to_ticks((uint32_t)duration_us, sclk_idx);
	timer_tick += cur_tick;
	hal_timer_set_me_counter(&system_timer, US_TICKER_ME_ID, (uint32_t) timer_tick);
	hal_timer_me_ctrl(&system_timer, US_TICKER_ME_ID, 1);
}

#endif

void us_ticker_disable_interrupt(void)
{
	__NOP();
}

void us_ticker_clear_interrupt(void)
{
	__NOP();
}


