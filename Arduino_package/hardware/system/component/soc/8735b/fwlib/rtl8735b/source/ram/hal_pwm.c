/**************************************************************************//**
 * @file     hal_pwm.c
 * @brief    This PWM HAL API functions.
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

#include "hal_pwm.h"
#include "hal_pinmux.h"
#include "hal_timer.h"
#include "hal_cache.h"
#include "hal_gdma.h"




#if CONFIG_PWM_EN && CONFIG_GTIMER_EN

extern hal_status_t hal_pwm_set_duty_rtl8195bhp_patch(hal_pwm_adapter_t *ppwm_adp, u32 period_us,
		u32 duty_us, u32 start_offset_us);
extern void hal_pwm_deinit_rtl8195bhp_patch(hal_pwm_adapter_t *ppwm_adp);

extern hal_status_t hal_pwm_auto_duty_ns_dec_rtl8195bhp_patch(hal_pwm_adapter_t *ppwm_adp, u32 min_duty_ns,
		u32 step_sz_ns, u32 step_period_cnt);
extern hal_status_t hal_pwm_auto_duty_ns_inc_rtl8195bhp_patch(hal_pwm_adapter_t *ppwm_adp, u32 max_duty_ns,
		u32 step_sz_ns, u32 step_period_cnt);
extern hal_status_t hal_pwm_set_duty_ns_rtl8195bhp_patch(hal_pwm_adapter_t *ppwm_adp, u32 period_ns,
		u32 duty_ns, u32 start_offset_ns);
extern u32 hal_pwm_read_duty_ns_rtl8195bhp_patch(hal_pwm_adapter_t *ppwm_adp);

/**
 * @addtogroup hs_hal_pwm PWM
 * @{
 */

/**
 *  @brief To register a IRQ handler for the PWM common interrupt.
 *
 *  @param[in] irq_handler The IRQ handler.
 *
 *  @returns void
 */
void hal_pwm_comm_irq_reg(irq_handler_t irq_handler)
{
	hal_pwm_stubs.hal_pwm_comm_irq_reg(irq_handler);
}

/**
 *  @brief To un-register the PWM common IRQ handler.
 *
 *  @param void
 *
 *  @returns void
 */
void hal_pwm_comm_irq_unreg(void)
{
	hal_pwm_stubs.hal_pwm_comm_irq_unreg();
}

/**
 *  @brief To initial the PWM devices common adapter. This function must be called first, before call
 *         any other PWM functions.
 *
 *  @param[in] ppwm_com_adp The PWM devices common adapter.
 *
 *  @returns void
 */
void hal_pwm_comm_init(hal_pwm_comm_adapter_t *ppwm_com_adp)
{
	hal_pwm_stubs.hal_pwm_comm_init(ppwm_com_adp);
}

/**
 *  @brief To de-initial the PWM devices common adapter.
 *         The whole will be disabled and the clock will be gated.
 *
 *  @returns void
 */
void hal_pwm_comm_deinit(void)
{
	hal_pwm_stubs.hal_pwm_comm_deinit();
}

/**
 *  @brief To give a list of g-timer ID as the tick source of PWM devices.
 *         The list should end with 0xFF
 *
 *  @param[in] timer_list The timer ID list those can be used as the PWM tick source.
 *
 *  @returns void
 */
void hal_pwm_comm_tick_source_list(uint8_t *timer_list)
{
	hal_pwm_stubs.hal_pwm_comm_tick_source_list(timer_list);
}

/**
 *  @brief To initial a PWM devices adapter. This is the first function must be called
 *         before to do any operation to the PWM devices.
 *
 *  @param[in] ppwm_adp The PWM devices adapter.
 *  @param[in] pwm_id The PWM devices index, valid value is 0 ~ (MaxPwmNum - 1).
 *  @param[in] duty_res_us The resolution for the duty duration setting, in us.
 *                     The value 0 means the duty resolution will be 1/4000 of PWM period.
 *
 *  @return     HAL_OK:  Setting succeed.
 *  @return     HAL_ERR_PARA:  Input arguments are invalid.
 *  @return     HAL_NOT_READY: Error with data not ready.
 */
hal_status_t hal_pwm_init(hal_pwm_adapter_t *ppwm_adp, u8 pwm_id, u8 pin_sel, u16 duty_res_us)
{
	//io_pin_t *pwm_pin_table;
	//io_pin_t pin_list[2];
	hal_status_t ret;

	if (pin_sel > (PWM_sel_group - 1)) {
		DBG_PWM_ERR("hal_pwm_init: Invalid PWM index\r\n");
		return HAL_ERR_PARA;
	}

#if 1
	u32 *pwm_pin_table;
	u32 pin_name;
	/* validate pin mux selection and register pin */
	pwm_pin_table = hal_pwm_stubs.pwm_pin_table;
	pin_name = pwm_pin_table[pin_sel * MaxPwmNum + pwm_id];

	ret = hal_pinmux_register(pin_name, PID_PWM0 + pwm_id);
	if (ret != HAL_OK) {
		DBG_PWM_ERR("hal_pwm_init: Pin Reg Failed(0x%x)\r\n", ret);
		return ret;
	}
#endif

	return hal_pwm_stubs.hal_pwm_init(ppwm_adp, pwm_id, pin_sel, duty_res_us);
}

/**
 *  @brief To disable and de-initial a PWM devices adapter.
 *
 *  @param[in] ppwm_adp The PWM devices adapter.
 *
 *  @returns void
 */
void hal_pwm_deinit(hal_pwm_adapter_t *ppwm_adp)
{
	//io_pin_t *pwm_pin_table;
	u8 pwm_id;
	u8 pin_sel;
	//io_pin_t pin_list[2];

	hal_pwm_stubs.hal_pwm_deinit(ppwm_adp);

	u32 *pwm_pin_table;
	u32 pin_name;
	pwm_id = ppwm_adp->pwm_id;
	pin_sel = ppwm_adp->pin_sel;
	pwm_pin_table = hal_pwm_stubs.pwm_pin_table;
	pin_name = pwm_pin_table[pin_sel * MaxPwmNum + pwm_id];

//    pwm_pin_table = hal_pwm_stubs.pwm_pin_table;
//    pin_list[0] = pwm_pin_table[pin_sel*MaxPwmNum+pwm_id];
//    pin_list[1].pin_name = PIN_LIST_END;

	hal_pinmux_unregister(pin_name, PID_PWM0 + pwm_id);

#if 0

	pwm_id = ppwm_adp->pwm_id;
	pin_sel = ppwm_adp->pin_sel;
	pwm_pin_table = hal_pwm_stubs.pwm_pin_table;
	pin_list[0] = pwm_pin_table[pin_sel * MaxPwmNum + pwm_id];
	pin_list[1].pin_name = PIN_LIST_END;

	hal_pinmux_unregister((io_pin_t *)&pin_list[0], PID_PWM0 + pwm_id);

#endif

}

/**
 *  @brief To read a PWM devive enable status
 *
 *  @param[in] ppwm_adp The PWM device adapter.
 *
 *  @returns 1: Enable.
 *  @returns 0: Disable.
 */
BOOLEAN hal_pwm_enable_sts(hal_pwm_adapter_t *ppwm_adp)
{
	return hal_pwm_stubs.hal_pwm_enable_sts(ppwm_adp);
}

/**
 *  @brief To enable multiple PWM devive simultaneously. If multiple PWM need to
 *         keep the phase offset, then they should be enabled simultaneously.
 *
 *  @param[in] en_ctrl The bit map for the PWM enable control. Bit [0 .. 7] map to PWM 0 .. 7.
 *
 *  @returns void
 */
void hal_pwm_comm_enable(u32 en_ctrl)
{
	hal_pwm_stubs.hal_pwm_comm_enable(en_ctrl);
}

/**
 *  @brief To disable multiple PWM devive simultaneously.
 *
 *  @param[in] dis_ctrl The bit map for the PWM disable control. Bit [0 .. 7] map to PWM 0 .. 7.
 *
 *  @returns void
 */
void hal_pwm_comm_disable(u32 dis_ctrl)
{
	hal_pwm_stubs.hal_pwm_comm_disable(dis_ctrl);
}

/**
 *  @brief To enable a PWM devive.
 *
 *  @param[in] ppwm_adp The PWM device adapter.
 *
 *  @returns void
 */
void hal_pwm_enable(hal_pwm_adapter_t *ppwm_adp)
{
	hal_pwm_stubs.hal_pwm_enable(ppwm_adp);
}

/**
 *  @brief To disable a PWM devive.
 *
 *  @param[in] ppwm_adp The PWM device adapter.
 *
 *  @returns void
 */
void hal_pwm_disable(hal_pwm_adapter_t *ppwm_adp)
{
	hal_pwm_stubs.hal_pwm_disable(ppwm_adp);
}

/**
 *  @brief To set the PWM tick source selection.
 *
 *  @param[in] ppwm_adp The PWM device adapter.
 *  @param[in] clk_sel The PWM tick source selection
 *
 *  @returns void
 */
void hal_pwm_set_clk_sel(hal_pwm_adapter_t *ppwm_adp, pwm_clk_sel_t clk_sel)
{
	hal_pwm_stubs.hal_pwm_set_clk_sel(ppwm_adp, clk_sel);
}

/**
 *  @brief To wait the PWM HW ready to set new PWM period/duty/offset.
 *
 *  @param[in] ppwm_adp The PWM device adapter.
 *
 *  @returns void
 */
void hal_pwm_wait_ctrl_ready(hal_pwm_adapter_t *ppwm_adp)
{
	hal_pwm_stubs.hal_pwm_wait_ctrl_ready(ppwm_adp);
}

/**
 *  @brief To set the tick time (resolution) of a PWM device.
 *
 *  @param[in] ppwm_adp The PWM device adapter.
 *  @param[in] tick_p5us The PWM tick time, unit is 500ns. It should be a even number.
 *
 *  @returns HAL_OK: Setting succeed.
 *  @returns HAL_BUSY: Busy.
 *  @returns HAL_NOT_READY: Error with data not ready.
 */
hal_status_t hal_pwm_set_tick_time(hal_pwm_adapter_t *ppwm_adp, u32 tick_p5us)
{
	return hal_pwm_stubs.hal_pwm_set_tick_time(ppwm_adp, tick_p5us);
}

/**
 *  @brief To set the duty ratio of the PWM
 *
 *  @param[in] ppwm_adp The PWM device adapter.
 *  @param[in] period_us The PWM cycle period, unit is us
 *  @param[in] duty_us The PWM on duty duration, unit is us
 *  @param[in] start_offset_us The on duty start timing offset from the start of the PWM periodof, unit is us
 *
 *  @returns HAL_OK: Setting succeed.
 *  @returns HAL_NOT_READY: Error with data not ready.
 */
hal_status_t hal_pwm_set_duty(hal_pwm_adapter_t *ppwm_adp, u32 period_us,
							  u32 duty_us, u32 start_offset_us)
{
	return hal_pwm_stubs.hal_pwm_set_duty(ppwm_adp, period_us, duty_us, start_offset_us);
}

/**
 *  @brief To set the duty_ns ratio of the PWM
 *
 *  @param[in] ppwm_adp The PWM device adapter.
 *  @param[in] period_ns The PWM cycle period, unit is ns
 *  @param[in] duty_ns The PWM on duty duration, unit is ns
 *  @param[in] start_offset_ns The on duty start timing offset from the start of the PWM periodof, unit is ns
 *
 *  @returns HAL_OK: Setting succeed.
 *  @returns HAL_NOT_READY: Error with data not ready.
 */
hal_status_t hal_pwm_set_duty_ns(hal_pwm_adapter_t *ppwm_adp, u32 period_ns,
								 u32 duty_ns, u32 start_offset_ns)
{
	u32 ticks_25ns; // how many 0.5us of 1 tick
	u8 pwm_enabled;
	//pwm_ctrl_t pwm_ctrl;
	ticks_25ns = 25;
	if ((HAL_READ32(0x40009800, 0x2C) & 0xC0000) == 0x80000) {
		if (period_ns > 102375) {
			DBG_PWM_ERR("hal_rtl_pwm_set_duty_ns: The period_ns can't be larger than 102375ns\r\n");
			return HAL_NOT_READY;
		} else if (period_ns < 50) {
			DBG_PWM_ERR("hal_rtl_pwm_set_duty_ns: The period_ns can't be less than 50ns\r\n");
			return HAL_NOT_READY;
		} else {
			hal_pwm_set_clk_sel(ppwm_adp, 8);  // Assign SCLK
			PWM_TypeDef *PWM_OBJ = (PWM_TypeDef *)(ppwm_adp->base_addr);
			u32 PWM_CTRL;
			PWM_CTRL = PWM_OBJ->PWM_CTRL;
			//pwm_ctrl.w = ppwm_adp->base_addr->ctrl;
			pwm_enabled = hal_pwm_enable_sts(ppwm_adp);
			if (pwm_enabled) {
				hal_pwm_wait_ctrl_ready(ppwm_adp);
			}
			hal_pwm_set_period(ppwm_adp, (((period_ns) / ticks_25ns) - 1));
			hal_pwm_set_onduty_start(ppwm_adp, ((start_offset_ns) / ticks_25ns));
			PWM_CTRL &= (~PWM_MASK_DUTY);
			PWM_CTRL |= (duty_ns) / ticks_25ns;
			//pwm_ctrl.b.duty = (duty_ns) / ticks_50ns;
			//DBG_PWM_ERR ("Duty: %d\r\n",pwm_ctrl.b.duty);

			if (pwm_enabled) {
				PWM_CTRL |= (PWM_BIT_CTRL_SET);
				//pwm_ctrl.b.ctrl_set = 1;
			}
			ppwm_adp->tick_p5us = ticks_25ns / 5000;
			PWM_OBJ->PWM_CTRL = PWM_CTRL;
			//ppwm_adp->base_addr->ctrl = pwm_ctrl.w;
			ppwm_adp->period_us = period_ns / 1000;
			ppwm_adp->duty_us = duty_ns / 1000;
		}
	} else {
		DBG_PWM_ERR("hal_rtl_pwm_set_duty_ns: The timer group1 should be set 40MHz\r\n");
		return HAL_NOT_READY;
	}

	return HAL_OK;
	//return hal_pwm_stubs.hal_pwm_set_duty_ns(ppwm_adp, period_ns, duty_ns, start_offset_ns);
}

/**
 *  @brief To read the time period of current duty of the PWM
 *
 *  @param[in] ppwm_adp The PWM device adapter.
 *
 *  @returns The PWM on duty duration, unit is us
 */
u32 hal_pwm_read_duty(hal_pwm_adapter_t *ppwm_adp)
{
	return hal_pwm_stubs.hal_pwm_read_duty(ppwm_adp);
}

/**
 *  @brief To change the duty ratio of the PWM only and keep other setting.
 *
 *  @param[in] ppwm_adp The PWM device adapter.
 *  @param[in] duty_us The PWM on duty duration, unit is us
 *
 *  @returns void
 */
void hal_pwm_change_duty(hal_pwm_adapter_t *ppwm_adp, u32 duty_us)
{
	hal_pwm_stubs.hal_pwm_change_duty(ppwm_adp, duty_us);
}

/**
 *  @brief To set the PWM on duty boundary (up limit / down limit) of the duty
 *         auto-adjustment.
 *
 *  @param[in] ppwm_adp The PWM device adapter.
 *  @param[in] max_duty_us The up limit of the duty time, in us.
 *  @param[in] min_duty_us The down limit of the duty time, in us.
 *
 *  @returns HAL_OK: Setting succeed.
 *  @returns HAL_ERR_PARA: Error with invaild parameters.
 */
hal_status_t hal_pwm_set_duty_limit(hal_pwm_adapter_t *ppwm_adp, u32 max_duty_us, u32 min_duty_us)
{
	return hal_pwm_stubs.hal_pwm_set_duty_limit(ppwm_adp, max_duty_us, min_duty_us);
}

/**
 *  @brief To setup the PWM duty auto-adjustment registers.
 *
 *  @param[in] ppwm_adp The PWM device adapter.
 *  @param[in] pauto_duty The duty auto-adjustment configuration. Includes maximum / minum duty size, duty
 *                    increasing / decreasing step size, adjustment period and the callback function for
 *                    the adjustment done indication.
 *  @returns void
 */
void hal_pwm_set_auto_duty_adj(hal_pwm_adapter_t *ppwm_adp, hal_pwm_auto_duty_adj_t *pauto_duty)
{
	hal_pwm_stubs.hal_pwm_set_auto_duty_adj(ppwm_adp, pauto_duty);
}

/**
 *  @brief To enable or disable the PWM duty auto-adjustment HW.
 *
 *  @param[in] ppwm_adp The PWM device adapter.
 *  @param[in] enable The duty auto-adjustment enable control (0: disable, 1: enable)
 *
 *  @returns void
 */
void hal_pwm_auto_duty_en(hal_pwm_adapter_t *ppwm_adp, BOOLEAN enable)
{
	hal_pwm_stubs.hal_pwm_auto_duty_en(ppwm_adp, enable);
}

/**
 *  @brief To configure the PWM duty auto-adjustment for duty duration increasing.
 *
 *  @param[in] ppwm_adp The PWM device adapter.
 *  @param[in] max_duty_us The up limit of the duty duration, in us.
 *  @param[in] step_sz_us The step size of each duty duration increasing, in us.
 *  @param[in] step_period_cnt The stay time of each duty duration increasing step, uint is PWM period.
 *
 *  @return     HAL_OK:  Setting succeed.
 *  @return     HAL_ERR_PARA:  Error with invaild parameters.
 */
hal_status_t hal_pwm_set_auto_duty_inc(hal_pwm_adapter_t *ppwm_adp, u32 max_duty_us,
									   u32 step_sz_us, u32 step_period_cnt)
{
	return hal_pwm_stubs.hal_pwm_set_auto_duty_inc(ppwm_adp, max_duty_us, step_sz_us, step_period_cnt);
}

/**
 *  @brief To configure the PWM duty auto-adjustment for duty duration increasing.
 *
 *  @param[in] ppwm_adp The PWM device adapter.
 *  @param[in] max_duty_us The up limit of the duty duration, in us.
 *  @param[in] step_sz_us The step size of each duty duration increasing, in us.
 *  @param[in] step_period_cnt The stay time of each duty duration increasing step, uint is PWM period.
 *
 *  @return     HAL_OK:  Setting succeed.
 *  @return     HAL_ERR_PARA:  Error with invaild parameters.
 */
hal_status_t hal_pwm_set_auto_duty_dec(hal_pwm_adapter_t *ppwm_adp, u32 min_duty_us,
									   u32 step_sz_us, u32 step_period_cnt)
{
	return hal_pwm_stubs.hal_pwm_set_auto_duty_dec(ppwm_adp, min_duty_us, step_sz_us, step_period_cnt);
}

/**
 *  @brief To configure the PWM duty auto-adjustment loop mode.
 *
 *  @param[in] ppwm_adp The PWM device adapter.
 *  @param[in] ini_dir The initial direction for the duty-adjustment loop. 1 -> duty increasing, 0 -> duty decreasing.
 *  @param[in] loop_cnt The number of duty-adjustment loop to run. 1 loop means from min duty to max duty
 *                  or from max duty to min duty.
 *
 *  @return     HAL_OK:  Setting succeed.
 *  @return     HAL_ERR_PARA:  Error with invaild parameters.
 */
hal_status_t hal_pwm_set_auto_duty_loop(hal_pwm_adapter_t *ppwm_adp, u8 ini_dir, u32 loop_cnt)
{
	return hal_pwm_stubs.hal_pwm_set_auto_duty_loop(ppwm_adp, ini_dir, loop_cnt);
}

/**
 *  @brief To enable the PWM period end interrupt.
 *
 *  @param[in] ppwm_adp The PWM device adapter.
 *  @param[in] callback The callback function. It will be called when the interrupt is accurred.
 *  @param[in] arg The argument of the callback function.
 *  @param[in] int_en To enable(1) or disable(0) the interrupt. For interrupt disable, the arguments
 *                'callback' & 'arg' are ignored.
 *
 *  @returns void
 */
void hal_pwm_set_period_int(hal_pwm_adapter_t *ppwm_adp, pwm_period_callback_t callback, void *arg, u8 int_en)
{
	hal_pwm_stubs.hal_pwm_set_period_int(ppwm_adp, callback, arg, int_en);
}

/**
 *  @brief To setup the PWM duty auto adjustment interrupt.
 *
 *  @param[in] ppwm_adp The PWM device adapter.
 *  @param[in] callback The callback function. It will be called when the interrupt is accurred.
 *  @param[in] arg The argument of the callback function.
 *  @param[in] int_en The bit map to enable/disable the interrupt. Bit 0 control the interrupt of duty duration
 *                reachs the up limit. Bit 1 control the interrupt of duty duration reachs the down limit.
 *
 *  @returns void
 */
void hal_pwm_set_autoadj_int(hal_pwm_adapter_t *ppwm_adp, pwm_lim_callback_t callback,
							 void *arg, u8 int_en)
{
	hal_pwm_stubs.hal_pwm_set_autoadj_int(ppwm_adp, callback, arg, int_en);
}


/**
 *  @brief To setup the PWM duty auto adjustment interrupt callback for loop mode.
 *
 *  @param[in] ppwm_adp The PWM device adapter.
 *  @param[in] callback The callback function. It will be called when the duty adjustment loop count down to 0.
 *  @param[in] arg The argument of the callback function.
 *
 *  @returns void
 */
void hal_pwm_set_autoadj_loop_int(hal_pwm_adapter_t *ppwm_adp, pwm_lo_callback_t callback, void *arg)
{
	hal_pwm_stubs.hal_pwm_set_autoadj_loop_int(ppwm_adp, callback, arg);
}

/**
 *  @brief To start the PWM duty auto-adjustment for duty duration increasing.
 *
 *  @param[in] ppwm_adp The PWM device adapter.
 *  @param[in] max_duty_us The up limit of the duty duration, in us.
 *  @param[in] step_sz_us The step size of each duty duration increasing, in us.
 *  @param[in] step_period_cnt The stay time of each duty duration increasing step, uint is PWM period.
 *
 *  @return     HAL_OK:  Setting succeed.
 *  @return     HAL_BUSY:  BUSY.
 */
hal_status_t hal_pwm_auto_duty_inc(hal_pwm_adapter_t *ppwm_adp, u32 max_duty_us,
								   u32 step_sz_us, u32 step_period_cnt)
{
	PWM_TypeDef *PWM_OBJ = (PWM_TypeDef *)(ppwm_adp->base_addr);
	u32 PWM_ADJ_LIM, PWM_ADJ_CTRL;
	hal_pwm_stubs.hal_pwm_auto_duty_inc(ppwm_adp, max_duty_us, step_sz_us, step_period_cnt);
	PWM_ADJ_LIM = PWM_ADJ_LIM | (PWM_MASK_DUTY_ADJ_UP_LIM & (((max_duty_us << 1) / ppwm_adp->tick_p5us) << PWM_SHIFT_DUTY_ADJ_UP_LIM));
	PWM_OBJ->PWM_AUTO_ADJ_LIMIT = PWM_ADJ_LIM;

	return HAL_OK;
}

/**
 *  @brief To start the PWM duty auto-adjustment for duty duration increasing.
 *
 *  @param[in] ppwm_adp The PWM device adapter.
 *  @param[in] max_duty_us The up limit of the duty duration, in us.
 *  @param[in] step_sz_us The step size of each duty duration increasing, in us.
 *  @param[in] step_period_cnt The stay time of each duty duration increasing step, uint is PWM period.
 *
 *  @return     HAL_OK:  Setting succeed.
 *  @return     HAL_BUSY:  BUSY.
 */
hal_status_t hal_pwm_auto_duty_dec(hal_pwm_adapter_t *ppwm_adp, u32 min_duty_us,
								   u32 step_sz_us, u32 step_period_cnt)
{
	return hal_pwm_stubs.hal_pwm_auto_duty_dec(ppwm_adp, min_duty_us, step_sz_us, step_period_cnt);
}

/**
 *  @brief To start the PWM duty auto-adjustment loop mode.
 *
 *  @param[in] ppwm_adp The PWM device adapter.
 *  @param[in] ini_duty_us The initial value for the loop-mode auto duty adjustment. If this value is 0xFFFFFFFF
 *                       it means use current duty as the initial duty.
 *  @param[in] ini_dir The initial direction for the duty-adjustment loop. 1 -> duty increasing, 0 -> duty decreasing.
 *  @param[in] loop_cnt The number of duty-adjustment loop to run. 1 loop means from min duty to max duty
 *                  or from max duty to min duty.
 *
 *  @return     HAL_OK:  Setting succeed.
 *  @return     HAL_BUSY:  BUSY.
 */
hal_status_t hal_pwm_auto_duty_loop(hal_pwm_adapter_t *ppwm_adp, u32 ini_duty_us, u8 ini_dir, u32 loop_cnt)
{
	return hal_pwm_stubs.hal_pwm_auto_duty_loop(ppwm_adp, ini_duty_us, ini_dir, loop_cnt);
}

/**
 *  @brief To stop the PWM duty auto-adjustment loop mode.
 *
 *  @param[in] ppwm_adp The PWM device adapter.
 *  @param[in] stop_now Is stop the PWM auto duty loop immediately(1) or stop at the next duty limit(0).
 *
 *  @returns void
 */
void hal_pwm_stop_duty_loop(hal_pwm_adapter_t *ppwm_adp, u8 stop_now)
{
	hal_pwm_stubs.hal_pwm_stop_duty_loop(ppwm_adp, stop_now);
}

/**
 *  @brief To start the PWM duty auto-adjustment for duty duration increasing.
 *
 *  @param[in] ppwm_adp The PWM device adapter.
 *  @param[in] max_duty_ns The up limit of the duty duration, in ns.
 *  @param[in] step_sz_ns The step size of each duty duration increasing, in ns.
 *  @param[in] step_period_cnt The stay time of each duty duration increasing step, uint is PWM period.
 *
 *  @return     HAL_OK:  Setting succeed.
 *  @return     HAL_BUSY:  BUSY.
 */
hal_status_t hal_pwm_auto_duty_ns_inc(hal_pwm_adapter_t *ppwm_adp, u32 max_duty_ns,
									  u32 step_sz_ns, u32 step_period_cnt)
{
	return hal_pwm_stubs.hal_pwm_auto_duty_ns_inc(ppwm_adp, max_duty_ns, step_sz_ns, step_period_cnt);
}

/**
 *  @brief To start the PWM duty auto-adjustment for duty duration increasing.
 *
 *  @param[in] ppwm_adp The PWM device adapter.
 *  @param[in] max_duty_ns The up limit of the duty duration, in ns.
 *  @param[in] step_sz_ns The step size of each duty duration increasing, in ns.
 *  @param[in] step_period_cnt The stay time of each duty duration increasing step, uint is PWM period.
 *
 *  @return     HAL_OK:  Setting succeed.
 *  @return     HAL_BUSY:  BUSY.
 */
hal_status_t hal_pwm_auto_duty_ns_dec(hal_pwm_adapter_t *ppwm_adp, u32 min_duty_ns,
									  u32 step_sz_ns, u32 step_period_cnt)
{
	return hal_pwm_stubs.hal_pwm_auto_duty_ns_dec(ppwm_adp, min_duty_ns, step_sz_ns, step_period_cnt);
}
/**
 *  \brief To read the time period of current duty of the PWM
 *
 *  \param[in] ppwm_adp The PWM device adapter.
 *
 *  \returns u32: The PWM on duty duration, unit is ns
 */
u32 hal_pwm_read_duty_ns(hal_pwm_adapter_t *ppwm_adp)
{
	return hal_pwm_stubs.hal_pwm_read_duty_ns(ppwm_adp);
}

/**
 *  @brief To initial a GDMA channel for the PWM DMA mode transfer.
 *
 *  @param[in]  ppwm_adp  The PWM adapter.
 *  @param[in]  pgdma_chnl The GDMA channel adapter. It is use to control
 *              the GDMA channel transfer.
 *  @param[in]  mode: Different dma mode, 5: only change duty, 6: only change period, 7: change duty and period simultaneously.
 *  @param[in]  irq  The callback function.
 *
 *  @return     HAL_ERR_PARA:  Input arguments are invalid.
 *  @return     HAL_OK:  GDMA channel initialization OK.
 */

hal_status_t hal_pwm_dma_init(hal_pwm_adapter_t *ppwm_adp, phal_gdma_adaptor_t pgdma_chnl, int mode, pwm_period_callback_t irq)
{
	hal_status_t ret;
	u8 gdma_index;

	memset((void *)pgdma_chnl, 0, sizeof(hal_gdma_adaptor_t));
	gdma_index = pgdma_chnl->gdma_index;
	ret = hal_gdma_chnl_alloc(pgdma_chnl, 0);     // default no-multiple block support

	if (ret == HAL_OK) {
		ret = hal_pwm_stubs.hal_pwm_dma_init(ppwm_adp, pgdma_chnl, mode);
		if (ret == HAL_OK) {
			ret = hal_pwm_stubs.hal_pwm_cache(ppwm_adp, NULL, NULL);
			hal_gdma_chnl_init(pgdma_chnl);
			if (gdma_index != pgdma_chnl->gdma_index) {
				//DBG_PWM_INFO("gdma hand shake %x\r\n", pgdma_chnl->gdma_cfg.dest_per);
				hal_gdma_handshake_init(pgdma_chnl, pgdma_chnl->gdma_cfg.dest_per);
			}
			hal_gdma_irq_reg(pgdma_chnl, (irq_handler_t) irq, NULL);
		} else {
			DBG_PWM_ERR("hal_pwm_gdma_init: GDMA init failed(%d)\r\n", ret);
			hal_gdma_chnl_free(pgdma_chnl);
		}
	} else {
		DBG_PWM_ERR("hal_pwm_gdma_init: GDMA channel allocate failed(%d)\r\n", ret);
	}

	return ret;
}

/**
 *  @brief To send a block of data by the DMA transmission mode.
 *
 *  @param[in]  ppwm_adp  The PWM adapter.
 *  @param[in]  ptx_buf  The buffer of data to be transmitted.
 *  @param[in]  len  The length of data in bytes to be transmitted.
 *
 *  @return     HAL_OK: function execution OK.
 *  @return     HAL_BUSY: UART TX is in busy state, previous transmission is not finished yet.
 *  @return     HAL_ERR_PARA: Input arguments are invalid.
 *  @return     HAL_NO_RESOURCE: Multiple-block DMA channel allocation failed.
 */
hal_status_t hal_pwm_dma_send(hal_pwm_adapter_t *ppwm_adp, uint8_t *ptx_buf, uint32_t len)
{

	hal_gdma_adaptor_t *pgdma_chnl = ppwm_adp->ptx_gdma;
	uint32_t block_size;

	if (pgdma_chnl == NULL) {
		DBG_PWM_ERR("hal_pwm_dma_send: No GDMA Chnl\r\n");
		return HAL_NO_RESOURCE;
	}

	if (((len & 0x03) == 0) && (((uint32_t)(ptx_buf) & 0x03) == 0)) {
		// 4-bytes aligned, move 4 bytes each transfer
		block_size = len >> 2;
	} else {
		block_size = len;
	}

	if (block_size > MAX_DMA_BLOCK_SIZE) {
		{
			DBG_PWM_ERR("hal_pwm_dma_send: Err: TX length too big(%lu)\r\n", len);
			return HAL_ERR_PARA;
		}
	}

	return hal_pwm_stubs.hal_pwm_dma_send(ppwm_adp, ptx_buf, len);
	//return hal_rom_pwm_dma_send(ppwm_adp, ptx_buf, len);
}

/**
 *  @brief Enable pwm complementary mode, while setting DandBand value.
 *
 *  @param[in]  ppwm_adp  The PWM adapter.
 *  @param[in]  group chose pwm pair to be complementary.
 *  @param[in]  DB_value The value to set rising and falling edge delay time, the delay time will be (1/sclk)*DB_value.
 *  @param[in]  en To enable or disable pwm dma mode in chosen pwm pair.
 *
 *  @return     HAL_OK: function execution OK.
 *  @return     HAL_BUSY: UART TX is in busy state, previous transmission is not finished yet.
 *  @return     HAL_ERR_PARA: Input arguments are invalid.
 *  @return     HAL_NO_RESOURCE: Multiple-block DMA channel allocation failed.
 */


hal_status_t hal_pwm_complementary(hal_pwm_adapter_t *ppwm_adp, uint8_t group, uint8_t DB_value, bool en)
{
	return hal_pwm_stubs.hal_pwm_complementary(ppwm_adp, group, DB_value, en);
}




/** @} */ /* End of group hs_hal_pwm */

#endif  // end of "#if CONFIG_PWM_EN && CONFIG_GTIMER_EN"

