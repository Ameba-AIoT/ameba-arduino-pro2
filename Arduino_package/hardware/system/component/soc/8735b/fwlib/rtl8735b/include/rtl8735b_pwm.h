/**************************************************************************//**
 * @file     rtl8195bhp_pwm.h
 * @brief    The HAL related definition and macros for the PWM device.
 *           Includes Registers and data type definition.
 * @version  V1.00
 * @date     2016-07-22
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

#ifndef _RTL8735B_PWM_H_
#define _RTL8735B_PWM_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "rtl8735b_timer.h"
#include "rtl8735b_pwm_comm_type.h"
#include "rtl8735b_pwm_type.h"


/**
 * @addtogroup hs_hal_pwm PWM
 * @{
 */

/**
  * \brief define PWM ID
**/
enum  pwm_id_e {
	Pwm0           = 0, //!< PWM0
	Pwm1           = 1, //!< PWM1
	Pwm2           = 2, //!< PWM2
	Pwm3           = 3, //!< PWM3
	Pwm4           = 4, //!< PWM4
	pwm5           = 5, //!< PWM5
	pwm6           = 6, //!< PWM6
	pwm7           = 7, //!< PWM7
	Pwm8           = 8, //!< PWM4
	pwm9           = 9, //!< PWM5
	pwm10          = 10, //!< PWM6
	pwm11          = 11, //!< PWM7

	MaxPwmNum      = 12  //!< MAX_PWM_NUM
};
typedef uint8_t pwm_id_t;

#define Pro2 1


/**
  * \brief define PWM Limit Interrupt direction
**/
enum  pwm_limit_dir_e {
	PwmDownLimitInt      = 0,   //!< Interrupt triggered by duty ratio = down limit
	PwmUpLimitInt        = 1    //!< Interrupt triggered by duty ratio = up limit
};
typedef uint8_t pwm_limit_dir_t;

/**
  * \brief define PWM tick source selection, as the PWM control register definition
**/
enum  pwm_clk_sel_e {
	PwmClkSrc_Tm0       = GTimer0,    //!< Tick source from G-Timer 8
	PwmClkSrc_Tm1       = GTimer1,    //!< Tick source from G-Timer 9
	PwmClkSrc_Tm2      = GTimer2,   //!< Tick source from G-Timer 10
	PwmClkSrc_Tm3      = GTimer3,   //!< Tick source from G-Timer 11
	PwmClkSrc_Tm4      = GTimer4,   //!< Tick source from G-Timer 12
	PwmClkSrc_Tm5      = GTimer5,   //!< Tick source from G-Timer 13
	PwmClkSrc_Tm6      = GTimer6,   //!< Tick source from G-Timer 14
	PwmClkSrc_Tm7      = GTimer7,   //!< Tick source from G-Timer 15
	PwmClkSrc_SClk      = 16,         //!< Tick source from SCLK

	PwmClkSrc_None      = 0xFF //!< Not assign yet
};
typedef uint8_t pwm_clk_sel_t;

/**
  * \brief define PWM duty auto-adjustment direction
**/
enum  pwm_duty_adj_dir_e {
	PwmDutyAdj_Decrease     = 0,        //!< Increase the duty
	PwmDutyAdj_Increase     = 1         //!< decrease the duty
};
typedef uint8_t pwm_duty_adj_dir_t;

/**
  * \brief define PWM Interrupt ID
**/
enum  pwm_adj_int_e {
	PwmAdjIntDnLim = 1, //!< Interrupt ID = down limit
	PwmAdjIntUpLim = 2, //!< Interrupt ID = up limit
};

/**
  * \brief define PWM Duty Auto-Adjustment loop mode
**/
enum  pwm_duty_loop_mode_e {
	PwmDutyLoopOff = 0,     //!< Interrupt loop mode = loop off
	PwmDutyLoopCnt = 1,     //!< Interrupt ID = loop cnt
	PwmDutyLoopForever = 2  //!< Interrupt ID = loop forever
};

/**
  * \brief define PWM Interrupt clock source
**/
enum  pwm_int_clk_e {
	PWM_IntClk_APB      = 0,    //!< APB
	PWM_IntClk_32K      = 1     //!< 32k
};
typedef uint8_t pwm_int_clk_t;

#define PWM_CURRENT_DUTY            0xFFFFFFFF
//#define UNIFY_PWM 1
#define PWM_Sclk_32k 0
#define PWM_Sclk_4M  1
#define PWM_Sclk_40M 2



/*! define PWM interrupt call back function */
typedef void (*pwm_lim_callback_t)(void *, pwm_limit_dir_t dir);
typedef void (*pwm_lo_callback_t)(void *);
typedef void (*pwm_period_callback_t)(void *);

/**
  * \brief  The data structure to control the PWM duty auto adjstment.
*/
typedef struct hal_pwm_auto_duty_adj_s {
	u32 init_duty_us;   /*!< The initial duty size of the PWM to start a duty auto-adjustment, in us */
	u32 max_duty_us;   /*!< The maximum duty size of the duty auto-adjustment, in us */
	u32 min_duty_us;   /*!< The minium duty size of the duty auto-adjustment, in us */
	u32 duty_inc_step_us;   /*!< The step size for the duty auto-adjustment increasing, in us */
	u32 duty_dec_step_us;   /*!< The step size for the duty auto-adjustment decreasing, in us */
	u32 step_period_cnt;   /*!< The number of PWM period to perform a duty auto-adjustment */
	u8 init_dir;    /*!< The initial duty auto-adjustment direction */
	u8 loop_mode;   /*!< Is enable the duty auto-adjustment loop mode */
} hal_pwm_auto_duty_adj_t, *phal_pwm_auto_duty_adj_t;

/**
  * \brief  The data structure to handle a PWM device, it includes the configuration, register base address
          and interrupt call back functions.
*/
typedef struct hal_pwm_adapter_s {
	PWM_TypeDef *base_addr;      /*!< The PWM registers base address */
	pwm_id_t pwm_id;   /*! The PWM device index, 0 ~ 11 */
	u8 pin_sel;  /*! IO pin selection for this PWM */
	pwm_clk_sel_t pwm_clk_sel;  /*! The PWM tick source selection, 0 ~ 8 */
	u8 adj_int_en;       /*! The duty ratio auto adjustment interrupt enable control */
	u16 duty_res_us;     /*! minimum resolution for the PWM duty, in us */
	u32 adj_loop_count;    /*! The duty ratio auto adjustment loop count */
	u32 tick_p5us;    /*! The tick time of this PWM, the unit of tick time is 0.5us */
	u32 period_us;    /*! The period time of current PWM cycle, in us */
	u32 duty_us;      /*! The duty time of current PWM cycle, in us */
	hal_pwm_auto_duty_adj_t duty_adj; /*! The data structure to control the PWM duty auto adjstment. */

	pwm_lim_callback_t bound_callback;      /*! User callback function for duty ratio reachs the boundary limit */
	void *bound_cb_para;   /*! the argument for user duty size reachs the limit callback function */
	pwm_lo_callback_t loopout_callback;      /*! User callback function for duty ratio auto adjustment loop count down to 0 */
	void *lo_cb_para;   /*! the argument for duty auto-adj loopout callback function */
	pwm_period_callback_t period_callback;      /*! User callback function for PWM period time end */
	void *pe_cb_para;   /*! the argument for PWM period end callback function */
	void (*enter_critical)(void);   /*! the function for entering timer critical state */
	void (*exit_critical)(void);    /*! the function for exit timer critical state */
	hal_gdma_adaptor_t *ptx_gdma;           /*!< The GDMA channel handler for the PWM TX */
	hal_gdma_adaptor_t *prx_gdma;           /*!< The GDMA channel handler for the PWM RX */
	void (*dcache_invalidate_by_addr)(uint32_t *addr, int32_t dsize);   /*!< callback function to do the D-cache invalidate  */
	void (*dcache_clean_by_addr)(uint32_t *addr, int32_t dsize);        /*!< callback function to do the D-cache clean  */
	uint32_t reserved[7];
} hal_pwm_adapter_t, *phal_pwm_adapter_t;

/**
  \brief  The data structure to handle PWM devices common part, includes the base address of common registers
          and PWM adapters for interrupt process.
*/
typedef struct hal_pwm_comm_adapter_s {
	PWM_COMM_TypeDef *base_addr;      /*!< The PWM common register base address */
	hal_pwm_adapter_t *pwm_adapter[MaxPwmNum];   /*!< All the PWM adapters share the same interrupt IRQ */
	uint8_t *timer_list;    /*!< the list of avaliable timer as the PWM tick source, keep NULL for no assign */
	uint32_t reserved[10];
} hal_pwm_comm_adapter_t, *phal_pwm_comm_adapter_t;

/**
  \brief  The data structure of the stubs function for the PWM HAL functions in ROM
*/
typedef struct hal_pwm_func_stubs_s {
	phal_pwm_comm_adapter_t *pppwm_comm_adp;
	//io_pin_t *pwm_pin_table;
	u32 *pwm_pin_table;
	void (*hal_pwm_irq_handler)(void);
	void (*hal_pwm_comm_irq_reg)(irq_handler_t irq_handler);
	void (*hal_pwm_comm_irq_unreg)(void);
	void (*hal_pwm_comm_init)(hal_pwm_comm_adapter_t *ppwm_com_adp);
	void (*hal_pwm_comm_deinit)(void);
	void (*hal_pwm_comm_tick_source_list)(uint8_t *timer_list);
	hal_status_t (*hal_pwm_init)(hal_pwm_adapter_t *ppwm_adp, u8 pwm_id, u8 pin_sel, u16 duty_res_us);

	BOOLEAN(*hal_pwm_enable_sts)(hal_pwm_adapter_t *ppwm_adp);
	void (*hal_pwm_comm_enable)(u32 en_ctrl);
	void (*hal_pwm_comm_disable)(u32 dis_ctrl);
	void (*hal_pwm_enable)(hal_pwm_adapter_t *ppwm_adp);
	void (*hal_pwm_disable)(hal_pwm_adapter_t *ppwm_adp);
	void (*hal_pwm_deinit)(hal_pwm_adapter_t *ppwm_adp);
	void (*hal_pwm_set_clk_sel)(hal_pwm_adapter_t *ppwm_adp, pwm_clk_sel_t clk_sel);
	void (*hal_pwm_wait_ctrl_ready)(hal_pwm_adapter_t *ppwm_adp);
	hal_status_t (*hal_pwm_set_tick_time)(hal_pwm_adapter_t *ppwm_adp, u32 tick_p5us);
	hal_status_t (*hal_pwm_set_duty)(hal_pwm_adapter_t *ppwm_adp, u32 period_us, \
									 u32 duty_us, u32 start_offset_us);
	u32(*hal_pwm_read_duty)(hal_pwm_adapter_t *ppwm_adp);
	void (*hal_pwm_change_duty)(hal_pwm_adapter_t *ppwm_adp, u32 duty_us);
	hal_status_t (*hal_pwm_set_duty_limit)(hal_pwm_adapter_t *ppwm_adp, u32 max_duty_us, u32 min_duty_us);
	void (*hal_pwm_set_auto_duty_adj)(hal_pwm_adapter_t *ppwm_adp, hal_pwm_auto_duty_adj_t *pauto_duty);
	void (*hal_pwm_auto_duty_en)(hal_pwm_adapter_t *ppwm_adp, BOOLEAN enable);
	hal_status_t (*hal_pwm_set_auto_duty_inc)(hal_pwm_adapter_t *ppwm_adp, u32 max_duty_us, \
			u32 step_sz_us, u32 step_period_cnt);
	hal_status_t (*hal_pwm_set_auto_duty_dec)(hal_pwm_adapter_t *ppwm_adp, u32 min_duty_us, \
			u32 step_sz_us, u32 step_period_cnt);
	hal_status_t (*hal_pwm_set_auto_duty_loop)(hal_pwm_adapter_t *ppwm_adp, u8 ini_dir, u32 loop_cnt);
	void (*hal_pwm_set_period_int)(hal_pwm_adapter_t *ppwm_adp, pwm_period_callback_t callback, void *arg, u8 int_en);
	void (*hal_pwm_set_autoadj_int)(hal_pwm_adapter_t *ppwm_adp, pwm_lim_callback_t callback, void *arg, u8 int_en);
	void (*hal_pwm_set_autoadj_loop_int)(hal_pwm_adapter_t *ppwm_adp, pwm_lo_callback_t callback, void *arg);
	hal_status_t (*hal_pwm_auto_duty_inc)(hal_pwm_adapter_t *ppwm_adp, u32 max_duty_us, u32 step_sz_us, \
										  u32 step_period_cnt);
	hal_status_t (*hal_pwm_auto_duty_dec)(hal_pwm_adapter_t *ppwm_adp, u32 min_duty_us, \
										  u32 step_sz_us, u32 step_period_cnt);
	hal_status_t (*hal_pwm_auto_duty_loop)(hal_pwm_adapter_t *ppwm_adp, u32 ini_duty_us, u8 ini_dir, u32 loop_cnt);
	void (*hal_pwm_stop_duty_loop)(hal_pwm_adapter_t *ppwm_adp, u8 stop_now);
	hal_status_t (*hal_pwm_set_duty_ns)(hal_pwm_adapter_t *ppwm_adp, u32 period_ns, u32 duty_ns, u32 start_offset_ns);
	hal_status_t (*hal_pwm_auto_duty_ns_inc)(hal_pwm_adapter_t *ppwm_adp, u32 max_duty_ns, u32 step_sz_ns, u32 step_period_cnt);
	hal_status_t (*hal_pwm_auto_duty_ns_dec)(hal_pwm_adapter_t *ppwm_adp, u32 min_duty_ns, u32 step_sz_ns, u32 step_period_cnt);
	u32(*hal_pwm_read_duty_ns)(hal_pwm_adapter_t *ppwm_adp);
	hal_status_t (*hal_pwm_dma_init)(hal_pwm_adapter_t *ppwm_adp, phal_gdma_adaptor_t pgdma_chnl, int mode);
	hal_status_t (*hal_pwm_dma_send)(hal_pwm_adapter_t *ppwm_adp, uint8_t *ptx_buf, uint32_t len);
	hal_status_t (*hal_pwm_cache)(phal_pwm_adapter_t ppwm_adp, void *dcache_clean_function, void *dcache_invalidate_function);
	void (*hal_pwm_clk_sel)(int Sclk);
	void (*hal_pwm_clock_init)(int en);
	hal_status_t (*hal_pwm_complementary)(phal_pwm_adapter_t ppwm_adp, uint8_t group, uint8_t DB_value, bool en);
	uint32_t reserved[7];  // reserved space for next ROM code version function table extending.
} hal_pwm_func_stubs_t;

/// @cond DOXYGEN_ROM_HAL_API

/**
 * @addtogroup hs_hal_pwm_rom_func PWM HAL ROM APIs.
 * @{
 */

/**
 *  \brief To read the PWM devives enable status
 *
 *  \param[in] ppwm_com_adp The PWM devices common adapter.
 *
 *  \returns The PWM devices enable status, bit 0 ~ 11 map to PWM0 ~ PWM11.
 */
__STATIC_INLINE
u32 hal_rtl_pwm_comm_enable_sts(hal_pwm_comm_adapter_t *ppwm_com_adp)
{
	PWM_COMM_TypeDef *PWM_COMM_OBJ = (PWM_COMM_TypeDef *)(ppwm_com_adp->base_addr);
	return PWM_COMM_OBJ->PWM_COMM_ENABLE_STATUS;
}

/**
 *  \brief To update a new PWM timing setting to HW register.
 *
 *  \param[in] ppwm_adp The PWM device adapter.
 *
 *  \returns void
 */
__STATIC_INLINE
void hal_rtl_pwm_update_ctrl(hal_pwm_adapter_t *ppwm_adp)
{
	// assert the ctrl_set bit to trigger the HW to fetch the new setting,
	// HW will clear this ctrl_set bit when the update is done
	PWM_TypeDef *PWM_OBJ = (PWM_TypeDef *)(ppwm_adp->base_addr);
	PWM_OBJ->PWM_CTRL = PWM_OBJ->PWM_CTRL | PWM_BIT_CTRL_SET;

}

/**
 *  \brief To set the period time of the PWM on duty.
 *
 *  \param[in] ppwm_adp The PWM device adapter.
 *  \param[in] duty_ticks The number of ticks: the time period of the on duty.
 *
 *  \returns void
 */
__STATIC_INLINE
void hal_rtl_pwm_set_duty_size(hal_pwm_adapter_t *ppwm_adp, u32 duty_ticks)
{
	PWM_TypeDef *PWM_OBJ = (PWM_TypeDef *)(ppwm_adp->base_addr);
	u32 DUTY;
	DUTY = duty_ticks & PWM_MASK_DUTY;
	PWM_OBJ->PWM_CTRL = PWM_OBJ->PWM_CTRL & (~PWM_MASK_DUTY);
	PWM_OBJ->PWM_CTRL = PWM_OBJ->PWM_CTRL | DUTY;
}

/**
 *  \brief To set the start offset of the PWM on duty.
 *
 *  \param[in] ppwm_adp The PWM device adapter.
 *  \param[in] start_ticks The on duty start offset time, in ticks.
 *
 *  \returns void
 */
__STATIC_INLINE
void hal_rtl_pwm_set_onduty_start(hal_pwm_adapter_t *ppwm_adp, u32 start_ticks)
{
	//start_ticks = 0x7cf;
	PWM_TypeDef *PWM_OBJ = (PWM_TypeDef *)(ppwm_adp->base_addr);
	u32 duty_start;
	duty_start = 0;
	duty_start = (start_ticks << 16) & PWM_MASK_DUTY_START;
	PWM_OBJ->PWM_TIMING_CTRL = PWM_OBJ->PWM_TIMING_CTRL & (~PWM_MASK_DUTY_START);
	PWM_OBJ->PWM_TIMING_CTRL = PWM_OBJ->PWM_TIMING_CTRL | duty_start;
}

/**
 *  \brief To set the period time of a PWM cycle.
 *
 *  \param[in] ppwm_adp The PWM device adapter.
 *  \param[in] period_ticks The period time of the PWM cycle.
 *
 *  \returns void
 */
__STATIC_INLINE
void hal_rtl_pwm_set_period(hal_pwm_adapter_t *ppwm_adp, u32 period_ticks)
{
	PWM_TypeDef *PWM_OBJ = (PWM_TypeDef *)(ppwm_adp->base_addr);
	u32 period;
	period = period_ticks & PWM_MASK_PERIOD;
	PWM_OBJ->PWM_TIMING_CTRL = PWM_OBJ->PWM_TIMING_CTRL & (~PWM_MASK_PERIOD);
	PWM_OBJ->PWM_TIMING_CTRL = PWM_OBJ->PWM_TIMING_CTRL | period;
}

/**
 *  \brief To pause a PWM out. When pausing a PWM, the PWM HW will stop at the end of
 *         current period.
 *
 *  \param[in] ppwm_adp The PWM device adapter.
 *  \param[in] pause_ctrl The pause control, 0: un-pause the PWM, 1: pause the PWM.
 *
 *  \returns void
 */
__STATIC_INLINE
void hal_rtl_pwm_pause(hal_pwm_adapter_t *ppwm_adp, BOOL pause_ctrl)
{
	PWM_TypeDef *PWM_OBJ = (PWM_TypeDef *)(ppwm_adp->base_addr);

	BOOL PAUSE;
	PAUSE = pause_ctrl;
	if (PAUSE) {
		PWM_OBJ->PWM_TIMING_CTRL = PWM_OBJ->PWM_TIMING_CTRL | (PWM_SHIFT_PAUSE);
	} else {
		PWM_OBJ->PWM_TIMING_CTRL = PWM_OBJ->PWM_TIMING_CTRL & ~(PWM_SHIFT_PAUSE);
	}
}

/**
 *  \brief To get the status of the PWM pause state.
 *
 *  \param[in] ppwm_adp The PWM device adapter.
 *
 *  \return     0:  PWM is paused.
 *  \return     1:  PWM still is running.
 */
__STATIC_INLINE
u8 hal_rtl_pwm_get_run_sts(hal_pwm_adapter_t *ppwm_adp)
{
	PWM_TypeDef *PWM_OBJ = (PWM_TypeDef *)(ppwm_adp->base_addr);

	return ((PWM_OBJ->PWM_TIMING_CTRL & (PWM_BIT_RUN_STS)) >> PWM_SHIFT_RUN_STS);

}

/**
 *  \brief To enable or disable the PWM period end interrupt.
 *
 *  \param[in] ppwm_adp The PWM device adapter.
 *  \param[in] int_en The interrupt enable control, disable (0) / enable (1).
 *
 *  \returns void
 */
__STATIC_INLINE
void hal_rtl_pwm_set_period_ie(hal_pwm_adapter_t *ppwm_adp, BOOL int_en)
{
	PWM_TypeDef *PWM_OBJ = (PWM_TypeDef *)(ppwm_adp->base_addr);

	if (int_en) {
		PWM_OBJ->PWM_CTRL |= (PWM_BIT_PERIOD_IE);
	} else {
		PWM_OBJ->PWM_CTRL &= ~(PWM_BIT_PERIOD_IE);
	}
}

/**
 *  \brief To set the duty size up-limit of the duty auto-adjustment.
 *
 *  \param[in] ppwm_adp The PWM device adapter.
 *  \param[in] max_duty_tick The up-limit duty size, in number of ticks.
 *
 *  \returns void
 */
__STATIC_INLINE
void hal_rtl_pwm_set_max_duty(hal_pwm_adapter_t *ppwm_adp, u32 max_duty_tick)
{
	PWM_TypeDef *PWM_OBJ = (PWM_TypeDef *)(ppwm_adp->base_addr);
	PWM_OBJ->PWM_AUTO_ADJ_LIMIT = max_duty_tick & (PWM_MASK_DUTY_ADJ_UP_LIM);
}

/**
 *  \brief To set the duty size down-limit of the duty auto-adjustment.
 *
 *  \param[in] ppwm_adp The PWM device adapter.
 *  \param[in] min_duty_tick The down-limit duty size, in number of ticks.
 *
 *  \returns void
 */
__STATIC_INLINE
void hal_rtl_pwm_set_min_duty(hal_pwm_adapter_t *ppwm_adp, u32 min_duty_tick)
{
	PWM_TypeDef *PWM_OBJ = (PWM_TypeDef *)(ppwm_adp->base_addr);
	PWM_OBJ->PWM_AUTO_ADJ_LIMIT = min_duty_tick & (PWM_MASK_DUTY_ADJ_DN_LIM);
}

/**
 *  \brief To set the increasing step size of the PWM duty auto-adjustment.
 *
 *  \param[in] ppwm_adp The PWM device adapter.
 *  \param[in] inc_step_ticks The step size to increase on every duty auto-adjustment, in ticks
 *
 *  \returns void
 */
__STATIC_INLINE
void hal_rtl_pwm_set_duty_inc_step(hal_pwm_adapter_t *ppwm_adp, u32 inc_step_ticks)
{
	PWM_TypeDef *PWM_OBJ = (PWM_TypeDef *)(ppwm_adp->base_addr);
	PWM_OBJ->PWM_AUTO_ADJ_CTRL = inc_step_ticks & (PWM_MASK_DUTY_INC_STEP);
}

/**
 *  \brief To set the decreasing step size of the PWM duty auto-adjustment.
 *
 *  \param[in] ppwm_adp The PWM device adapter.
 *  \param[in] dec_step_ticks The step size to decrease on every duty auto-adjustment, in ticks
 *
 *  \returns void
 */
__STATIC_INLINE
void hal_rtl_pwm_set_duty_dec_step(hal_pwm_adapter_t *ppwm_adp, u32 dec_step_ticks)
{
	PWM_TypeDef *PWM_OBJ = (PWM_TypeDef *)(ppwm_adp->base_addr);
	PWM_OBJ->PWM_AUTO_ADJ_CTRL = dec_step_ticks & (PWM_MASK_DUTY_DEC_STEP);
}

/**
 *  \brief To set the time period (number of PWM period) to do a PWM duty auto-adjustment
 *
 *  \param[in] ppwm_adp The PWM device adapter.
 *  \param[in] cycle_cnt The number of PWM period.
 *
 *  \returns void
 */
__STATIC_INLINE
void hal_rtl_pwm_set_duty_adj_cycle(hal_pwm_adapter_t *ppwm_adp, u32 cycle_cnt)
{
	PWM_TypeDef *PWM_OBJ = (PWM_TypeDef *)(ppwm_adp->base_addr);
	PWM_OBJ->PWM_AUTO_ADJ_CYCLE = cycle_cnt & (PWM_MASK_ADJ_CYCLES);
}

/**
 *  \brief To enable or disable the PWM duty auto-adjustment HW.
 *
 *  \param[in] ppwm_adp The PWM device adapter.
 *  \param[in] enable The duty auto-adjustment enable control (0: disable, 1: enable)
 *
 *  \returns void
 */
__STATIC_INLINE
void hal_rtl_pwm_set_duty_adj_en(hal_pwm_adapter_t *ppwm_adp, BOOLEAN enable)
{
	PWM_TypeDef *PWM_OBJ = (PWM_TypeDef *)(ppwm_adp->base_addr);
	if (enable) {
		PWM_OBJ->PWM_AUTO_ADJ_CTRL |= PWM_BIT_ADJ_EN;
	} else {
		PWM_OBJ->PWM_AUTO_ADJ_CTRL &= (~PWM_BIT_ADJ_EN);
	}
}

/**
 *  \brief To set the PWM duty auto-adjustment direction, increase or decreas.
 *
 *  \param[in] ppwm_adp The PWM device adapter.
 *  \param[in] dir The duty adjustment direction, 0: decrease, 1: encrease.
 *
 *  \returns void
 */
__STATIC_INLINE
void hal_rtl_pwm_set_duty_adj_dir(hal_pwm_adapter_t *ppwm_adp, pwm_duty_adj_dir_t dir)
{
	PWM_TypeDef *PWM_OBJ = (PWM_TypeDef *)(ppwm_adp->base_addr);
	if (dir) {
		PWM_OBJ->PWM_AUTO_ADJ_CTRL |= PWM_BIT_ADJ_DIR;
	} else {
		PWM_OBJ->PWM_AUTO_ADJ_CTRL &= (~PWM_BIT_ADJ_DIR);
	}
}

/**
 *  \brief To set the PWM duty auto-adjustment loop mode.
 *
 *  \param[in] ppwm_adp The PWM device adapter.
 *  \param[in] loop_en The duty auto-adjustment loop mode enable, 0: disable, 1: enable.
 *
 *  \returns void
 */
__STATIC_INLINE
void hal_rtl_pwm_set_duty_loop_mode(hal_pwm_adapter_t *ppwm_adp, u8 loop_en)
{
	PWM_TypeDef *PWM_OBJ = (PWM_TypeDef *)(ppwm_adp->base_addr);
	if (loop_en) {
		PWM_OBJ->PWM_AUTO_ADJ_CTRL |= PWM_BIT_ADJ_LOOP_EN;
	} else {
		PWM_OBJ->PWM_AUTO_ADJ_CTRL &= (~PWM_BIT_ADJ_LOOP_EN);
	}
}

/**
 *  \brief To enable or disable the interrupt of the adjusted duty meet the up-limit.
 *
 *  \param[in] ppwm_adp The PWM device adapter.
 *  \param[in] int_en The interrupt enable, 0: disable, 1: enable.
 *
 *  \returns void
 */
__STATIC_INLINE
void hal_rtl_pwm_set_max_duty_int(hal_pwm_adapter_t *ppwm_adp, u8 int_en)
{
	PWM_TypeDef *PWM_OBJ = (PWM_TypeDef *)(ppwm_adp->base_addr);
	if (int_en) {
		PWM_OBJ->PWM_AUTO_ADJ_CTRL |= PWM_BIT_DUTY_UP_LIM_IE;
	} else {
		PWM_OBJ->PWM_AUTO_ADJ_CTRL &= (~PWM_BIT_DUTY_UP_LIM_IE);
	}
}

/**
 *  \brief To enable or disable the interrupt of the adjusted duty meet the down-limit.
 *
 *  \param[in] ppwm_adp The PWM device adapter.
 *  \param[in] int_en The interrupt enable, 0: disable, 1: enable.
 *
 *  \returns void
 */
__STATIC_INLINE
void hal_rtl_pwm_set_min_duty_int(hal_pwm_adapter_t *ppwm_adp, u8 int_en)
{
	PWM_TypeDef *PWM_OBJ = (PWM_TypeDef *)(ppwm_adp->base_addr);
	if (int_en) {
		PWM_OBJ->PWM_AUTO_ADJ_CTRL |= PWM_BIT_DUTY_DN_LIM_IE;
	} else {
		PWM_OBJ->PWM_AUTO_ADJ_CTRL &= (~PWM_BIT_DUTY_DN_LIM_IE);
	}
}

void hal_rtl_pwm_comm_irq_reg(irq_handler_t irq_handler);
void hal_rtl_pwm_comm_irq_unreg(void);
void hal_pwm_limirq_reg_rtl8195bhp(hal_pwm_adapter_t *ppwm_adp, pwm_lim_callback_t callback, void *phid);
void hal_pwm_limirq_unreg_rtl8195bhp(hal_pwm_adapter_t *ppwm_adp);
void hal_rtl_pwm_comm_init(hal_pwm_comm_adapter_t *ppwm_com_adp);
void hal_rtl_pwm_comm_deinit(void);
void hal_rtl_pwm_comm_tick_source_list(uint8_t *timer_list);
hal_status_t hal_rtl_pwm_init(hal_pwm_adapter_t *ppwm_adp, u8 pwm_id, u8 pin_sel, u16 duty_res_us);
BOOLEAN hal_rtl_pwm_enable_sts(hal_pwm_adapter_t *ppwm_adp);
void hal_rtl_pwm_comm_enable(u32 en_ctrl);
void hal_rtl_pwm_comm_disable(u32 dis_ctrl);
void hal_rtl_pwm_enable(hal_pwm_adapter_t *ppwm_adp);
void hal_rtl_pwm_disable(hal_pwm_adapter_t *ppwm_adp);
void hal_rtl_pwm_deinit(hal_pwm_adapter_t *ppwm_adp);
void hal_rtl_pwm_set_clk_sel(hal_pwm_adapter_t *ppwm_adp, pwm_clk_sel_t clk_sel);
void hal_rtl_pwm_wait_ctrl_ready(hal_pwm_adapter_t *ppwm_adp);
hal_status_t hal_rtl_pwm_set_tick_time(hal_pwm_adapter_t *ppwm_adp, u32 tick_p5us);
hal_status_t hal_rtl_pwm_set_duty(hal_pwm_adapter_t *ppwm_adp, u32 period_us,
								  u32 duty_us, u32 start_offset_us);
u32 hal_rtl_pwm_read_duty(hal_pwm_adapter_t *ppwm_adp);
void hal_rtl_pwm_change_duty(hal_pwm_adapter_t *ppwm_adp, u32 duty_us);
hal_status_t hal_rtl_pwm_set_duty_limit(hal_pwm_adapter_t *ppwm_adp, u32 max_duty_us, u32 min_duty_us);
void hal_rtl_pwm_set_auto_duty_adj(hal_pwm_adapter_t *ppwm_adp, hal_pwm_auto_duty_adj_t *pauto_duty);
void hal_rtl_pwm_auto_duty_en(hal_pwm_adapter_t *ppwm_adp, BOOLEAN enable);
hal_status_t hal_rtl_pwm_set_auto_duty_inc(hal_pwm_adapter_t *ppwm_adp, u32 max_duty_us,
		u32 step_sz_us, u32 step_period_cnt);
hal_status_t hal_rtl_pwm_set_auto_duty_dec(hal_pwm_adapter_t *ppwm_adp, u32 min_duty_us,
		u32 step_sz_us, u32 step_period_cnt);
hal_status_t hal_rtl_pwm_set_auto_duty_loop(hal_pwm_adapter_t *ppwm_adp, u8 ini_dir, u32 loop_cnt);
void hal_rtl_pwm_set_period_int(hal_pwm_adapter_t *ppwm_adp, pwm_period_callback_t callback, \
								void *arg, u8 int_en);
void hal_rtl_pwm_set_autoadj_int(hal_pwm_adapter_t *ppwm_adp, pwm_lim_callback_t callback, \
								 void *arg, u8 int_en);
void hal_rtl_pwm_set_autoadj_loop_int(hal_pwm_adapter_t *ppwm_adp, pwm_lo_callback_t callback, void *arg);

hal_status_t hal_rtl_pwm_auto_duty_inc(hal_pwm_adapter_t *ppwm_adp, u32 max_duty_us,
									   u32 step_sz_us, u32 step_period_cnt);
hal_status_t hal_rtl_pwm_auto_duty_dec(hal_pwm_adapter_t *ppwm_adp, u32 min_duty_us,
									   u32 step_sz_us, u32 step_period_cnt);
hal_status_t hal_rtl_pwm_auto_duty_loop(hal_pwm_adapter_t *ppwm_adp, u32 ini_duty_us, u8 ini_dir, u32 loop_cnt);
void hal_rtl_pwm_stop_duty_loop(hal_pwm_adapter_t *ppwm_adp, u8 stop_now);
hal_status_t hal_rtl_pwm_set_duty_ns(hal_pwm_adapter_t *ppwm_adp, u32 period_ns,
									 u32 duty_ns, u32 start_offset_ns);
hal_status_t hal_rtl_pwm_auto_duty_ns_inc(hal_pwm_adapter_t *ppwm_adp, u32 max_duty_ns,
		u32 step_sz_ns, u32 step_period_cnt);
hal_status_t hal_rtl_pwm_auto_duty_ns_dec(hal_pwm_adapter_t *ppwm_adp, u32 min_duty_ns,
		u32 step_sz_ns, u32 step_period_cnt);
u32 hal_rtl_pwm_read_duty_ns(hal_pwm_adapter_t *ppwm_adp);

hal_status_t hal_rtl_pwm_dma_init(hal_pwm_adapter_t *ppwm_adp, phal_gdma_adaptor_t pgdma_chnl, int mode);

hal_status_t hal_rtl_pwm_dma_send(hal_pwm_adapter_t *ppwm_adp, uint8_t *ptx_buf, uint32_t len);
hal_status_t hal_rtl_pwm_cache(phal_pwm_adapter_t ppwm_adp, void *dcache_clean_function, void *dcache_invalidate_function);
void hal_rtl_pwm_clk_sel(int Sclk);
void hal_rtl_pwm_clock_init(int en);
hal_status_t hal_rtl_pwm_complementary(hal_pwm_adapter_t *ppwm_adp, uint8_t group, uint8_t DB_value, bool en);

/** @} */ /* End of group hs_hal_pwm_rom_func */

/// @endcond /* End of condition DOXYGEN_ROM_HAL_API */

#ifdef  __cplusplus
}
#endif

/** @} */ /* End of group hs_hal_pwm */

#endif  // end of "#define _RTL8195BH_PWM_H_"

