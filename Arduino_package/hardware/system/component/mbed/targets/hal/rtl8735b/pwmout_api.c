/**************************************************************************//**
 * @file     pwmout_api.c
 * @brief    This file implements the PWM API functions.
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

#include "device.h"
#include "objects.h"
#include "pinmap.h"
#include "string.h"
#include "rtl8735b_pin_name.h"
#include "PinNames.h"

#if DEVICE_PWMOUT

#ifdef CONFIG_PWM_EN
#include "pwmout_api.h"
#include "pwmout_ex_api.h"
#include "hal_timer.h"
#include "hal_pwm.h"

//#define PinSel0 0
//#define PinSel1 1

//#define RTL_PIN_PERI(FUN, IDX, SEL)     ((int)(((FUN) << 8) | ((IDX)<<4) | (SEL)))
//#define RTL_PIN_FUNC(FUN, SEL)          ((int)(((FUN) << 7) | (SEL)))


#if 0

static const PinMap PinMap_PWM[] = {
	{PF_6,   RTL_PIN_PERI(PID_PWM0,  0, PinSel0),  RTL_PIN_FUNC(PID_PWM0,   PinSel0)},
	{PF_7,   RTL_PIN_PERI(PID_PWM1,  1, PinSel0),  RTL_PIN_FUNC(PID_PWM1,   PinSel0)},
	{PF_8,   RTL_PIN_PERI(PID_PWM2,  2, PinSel0),  RTL_PIN_FUNC(PID_PWM2,   PinSel0)},
	{PF_9,   RTL_PIN_PERI(PID_PWM3,  3, PinSel0),  RTL_PIN_FUNC(PID_PWM3,   PinSel0)},
	{PF_10,  RTL_PIN_PERI(PID_PWM4,  4, PinSel0),  RTL_PIN_FUNC(PID_PWM4,   PinSel0)},
	{PF_11,  RTL_PIN_PERI(PID_PWM5,  5, PinSel0),  RTL_PIN_FUNC(PID_PWM5,   PinSel0)},
	{PF_12,  RTL_PIN_PERI(PID_PWM6,  6, PinSel0),  RTL_PIN_FUNC(PID_PWM6,   PinSel0)},
	{PF_13,  RTL_PIN_PERI(PID_PWM7,  7, PinSel0),  RTL_PIN_FUNC(PID_PWM7,   PinSel0)},
	{PF_14,  RTL_PIN_PERI(PID_PWM8,  8, PinSel0),  RTL_PIN_FUNC(PID_PWM8,   PinSel0)},
	{PF_15,  RTL_PIN_PERI(PID_PWM9,  9, PinSel0),  RTL_PIN_FUNC(PID_PWM9,   PinSel0)},
	{PF_16,  RTL_PIN_PERI(PID_PWM10, 10, PinSel0), RTL_PIN_FUNC(PID_PWM10,  PinSel0)},
	{PF_17,  RTL_PIN_PERI(PID_PWM11, 11, PinSel0), RTL_PIN_FUNC(PID_PWM11,  PinSel0)},

	{PS_1,   RTL_PIN_PERI(PID_PWM8,  8, PinSel1),  RTL_PIN_FUNC(PID_PWM8,   PinSel1)},
	{PS_4,   RTL_PIN_PERI(PID_PWM9,  9, PinSel1),  RTL_PIN_FUNC(PID_PWM9,   PinSel1)},
	{PS_5,   RTL_PIN_PERI(PID_PWM10, 10, PinSel1),  RTL_PIN_FUNC(PID_PWM10,  PinSel1)},
	{PS_6,   RTL_PIN_PERI(PID_PWM11, 11, PinSel1),  RTL_PIN_FUNC(PID_PWM11,  PinSel1)},

	{NC,    NC,     0}
};

#endif
static u32 pwm_pin_table_mbed[2 * MaxPwmNum] = {
	PIN_F6, PIN_F7, PIN_F8, PIN_F9, PIN_F10, PIN_F11, PIN_F12, PIN_F13, PIN_F14, PIN_F15, PIN_F16, PIN_F17,  // S0
	PIN_NC, PIN_NC, PIN_NC, PIN_NC, PIN_NC,  PIN_NC,  PIN_NC,  PIN_NC,  PIN_S1,  PIN_S4,  PIN_S5,  PIN_S6   // S1

};
static u8 timer_for_pwm_temp[] = {GTimer0, GTimer1, GTimer2, GTimer3, GTimer4, GTimer5, GTimer6, GTimer7, 0xff};  // the timer ID list those can be used as PWM tick source
//static u8 timer_for_pwm[] = {GTimer8, GTimer9, GTimer10, GTimer11, GTimer12, GTimer13, GTimer14, GTimer15, 0xff};  // the timer ID list those can be used as PWM tick source
static hal_pwm_comm_adapter_t pwm_com_handler;
static hal_timer_group_adapter_t _timer_group0;
//static hal_timer_group_adapter_t _timer_group2;
//static phal_gdma_adaptor_t gdma1;
extern u8 init, clk_sel;

void pwmout_init(pwmout_t *obj, PinName pin)
{
	//uint32_t peripheral;
	//u32 pwm_idx;
	//u32 pin_sel;
	u16 duty_res = 0;
	static u8 pwm_com_initialed;
	//#define pinmux_ready 0

	if (!pwm_com_initialed) {
		if (init == 0) {
			if (clk_sel == 0) {
				hal_timer_clock_init(0, ENABLE);
				hal_timer_group_init(&_timer_group0, 0);  // Initialize timer group 2 for PWM module
				//hal_osc4m_cal();
				hal_timer_group_sclk_sel(&_timer_group0, GTimerSClk_40M);  // Default 40MHz
				hal_pwm_clk_sel(PWM_Sclk_40M);
				init = 1;
			} else {
				hal_timer_clock_init(0, ENABLE);
				hal_timer_group_init(&_timer_group0, 0);  // Initialize timer group 2 for PWM module
				hal_timer_group_sclk_sel(&_timer_group0, GTimerSClk_4M);  // Default 4MHz
				hal_pwm_clk_sel(PWM_Sclk_4M);
				init = 1;
			}
		} else {
			if (clk_sel == 0) {
				hal_pwm_clk_sel(PWM_Sclk_40M);
			} else {
				hal_pwm_clk_sel(PWM_Sclk_4M);
			}
		}
		hal_pwm_clock_init(ENABLE);
		hal_pwm_comm_init(&pwm_com_handler);
		hal_pwm_comm_tick_source_list(timer_for_pwm_temp);
		pwm_com_initialed = 1;
	}

	// 以上ok //

	DBG_PWM_INFO("%s: Init PWM for pin(0x%x)\n", __func__, pin);
	// Get the peripheral name from the pin and assign it to the object

#if 1
	u8 index, sel_number, sel, id;
	id = 0;
	for (sel_number = 0; sel_number < PWM_sel_group; sel_number++) {
		for (index = 0; index < MaxPwmNum; index++) {
			if (pin == pwm_pin_table_mbed[sel_number * MaxPwmNum + index]) {
				id = index;
				sel = sel_number;
				break;
			}
		}
	}
#endif

#if 1

	obj->pwm_idx = id; // pin // id
	obj->pin_sel = sel;

#endif
	obj->period = 0;
	obj->is_init = 0;
	obj->pulse = 0;
	obj->offset_us = 0;
	obj->polarity = 1;
	memset((void *)&obj->pwm_hal_adp, 0, sizeof(hal_pwm_adapter_t));
	memset((void *)&obj->pwm_gdma_adp, 0, sizeof(hal_gdma_adaptor_t));

	if (hal_pwm_init(&obj->pwm_hal_adp, obj->pwm_idx, obj->pin_sel, duty_res) != HAL_OK) {
		DBG_PWM_ERR("pwmout_init Err!\n");
		return;
	}
	obj->is_init = 1; // Initialize Success
	pwmout_period_us(obj, 20000); // 20 ms per default
	//dbg_printf("10\r\n");
	hal_pwm_enable((&obj->pwm_hal_adp));
}

void pwmout_free(pwmout_t *obj)
{
	hal_pwm_deinit(&obj->pwm_hal_adp);
}

void pwmout_write(pwmout_t *obj, float percent)
{
	if (percent < (float)0.0) {
		percent = 0.0;
	} else if (percent > (float)1.0) {
		percent = 1.0;
	}

	obj->pulse = (uint32_t)((float)obj->period * percent);
	if (obj->polarity == 0) {
		obj->offset_us = obj->period - obj->pulse;
	}
	//DBG_PWM_ERR("obj->period! %d\n", obj->period);
	hal_pwm_set_duty(&obj->pwm_hal_adp, obj->period, obj->pulse, obj->offset_us);
	//dbg_printf("9\r\n");
}

float pwmout_read(pwmout_t *obj)
{
	float value = 0;

	if (obj->period > 0) {
		value = (float)(obj->pulse) / (float)(obj->period);
	}
	return ((value > (float)1.0) ? (float)(1.0) : (value));
}

void pwmout_period(pwmout_t *obj, float seconds)
{
	pwmout_period_us(obj, (int)(seconds * 1000000.0f));
}

void pwmout_period_ms(pwmout_t *obj, int ms)
{
	pwmout_period_us(obj, (int)(ms * 1000));
}

void pwmout_period_us(pwmout_t *obj, int us)
{
	float dc = pwmout_read(obj);

	if (us == 0) {
		DBG_PWM_ERR("The period register Cannot be set zero value\n");
	} else {
		obj->period = us;
		// Set duty cycle again
		pwmout_write(obj, dc);
	}
}

void pwmout_pulsewidth(pwmout_t *obj, float seconds)
{
	pwmout_pulsewidth_us(obj, (int)(seconds * 1000000.0f));
}

void pwmout_pulsewidth_ms(pwmout_t *obj, int ms)
{
	pwmout_pulsewidth_us(obj, ms * 1000);
}

void pwmout_pulsewidth_us(pwmout_t *obj, int us)
{
	float value = (float)us / (float)obj->period;

	pwmout_write(obj, value);
}

void pwmout_startoffset(pwmout_t *obj, float seconds)
{
	pwmout_startoffset_us(obj, (int)(seconds * 1000000.0f));
}

void pwmout_startoffset_ms(pwmout_t *obj, int ms)
{
	pwmout_startoffset_us(obj, ms * 1000);
}

void pwmout_startoffset_us(pwmout_t *obj, int us)
{
	float dc = pwmout_read(obj);

	obj->offset_us = us;
	pwmout_write(obj, dc);
}

void pwmout_period_int(pwmout_t *obj, pwm_period_callback_t callback, u8 enable)
{
	DBG_PWM_INFO("%s: Init PWM Interrupt\n", __func__);
	if (enable) {
		hal_pwm_set_period_int(&obj->pwm_hal_adp, (pwm_period_callback_t)callback, (void *)&obj->pwm_hal_adp, 1);
	} else {
		hal_pwm_set_period_int(&obj->pwm_hal_adp, 0, 0, 0);
	}
}

void pwmout_autoadj_int(pwmout_t *obj, pwm_lim_callback_t callback, u8 direction, u8 enable)
{
	DBG_PWM_INFO("%s: Init PWM duty adjustment Interrupt\n", __func__);
	if (enable) {
		if (direction == PwmAdjIntDnLim) {
			hal_pwm_set_autoadj_int(&obj->pwm_hal_adp, (pwm_lim_callback_t)callback, (void *)&obj->pwm_hal_adp, PwmAdjIntDnLim);
		} else if (direction == PwmAdjIntUpLim) {
			hal_pwm_set_autoadj_int(&obj->pwm_hal_adp, (pwm_lim_callback_t)callback, (void *)&obj->pwm_hal_adp, PwmAdjIntUpLim);
		} else {
			DBG_PWM_ERR("%s: The int_en parameter out of range\n", __func__);
		}
	} else {
		hal_pwm_set_autoadj_int(&obj->pwm_hal_adp, 0, 0, 0);
	}
}

void pwmout_autoadj_inc(pwmout_t *obj, u32 max_duty_us, u32 step_sz_us, u32 step_period_cnt)
{
	hal_pwm_auto_duty_inc(&obj->pwm_hal_adp, max_duty_us, step_sz_us, step_period_cnt);
}

void pwmout_autoadj_dec(pwmout_t *obj, u32 min_duty_us, u32 step_sz_us, u32 step_period_cnt)
{
	hal_pwm_auto_duty_dec(&obj->pwm_hal_adp, min_duty_us, step_sz_us, step_period_cnt);
}

void pwmout_start(pwmout_t *obj)
{
	hal_pwm_enable((&obj->pwm_hal_adp));
}

void pwmout_stop(pwmout_t *obj)
{
	hal_pwm_disable((&obj->pwm_hal_adp));
}

void pwmout_multi_start(u8 pin_ctrl)
{
	hal_pwm_comm_disable(pin_ctrl);
	hal_pwm_comm_enable(pin_ctrl);
}

void pwmout_set_polarity(pwmout_t *obj, int polarity)
{
	if (0 == polarity) {
		obj->polarity = 0;
	} else {
		obj->polarity = 1;
		obj->offset_us = 0;
	}
}

void pwmout_dma(pwmout_t *obj, uint8_t *ptx_buf, uint32_t len, int mode, pwm_dma_callback_t callback)
{
	hal_pwm_dma_init(&obj->pwm_hal_adp, &obj->pwm_gdma_adp, mode, callback);
	hal_pwm_dma_send(&obj->pwm_hal_adp, ptx_buf, len);

}

void pwmout_complementary(pwmout_t *obj, uint8_t group, uint8_t DB_value, bool en)
{
	hal_pwm_complementary(&obj->pwm_hal_adp, group, DB_value, en);
}



#endif // #ifdef CONFIG_PWM_EN
#endif

