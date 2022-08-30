/**************************************************************************//**
 * @file     hal_sgpio.h
 * @brief    The HAL API implementation for the SGPIO device.
 * @version  V1.00
 * @date     2016-12-14
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

#ifndef _HAL_SGPIO_H_
#define _HAL_SGPIO_H_

#include "cmsis.h"

#ifdef  __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup hs_hal_sgpio SGPIO
 * @ingroup 8195bh_hal
 * @{
 * @brief The SGPIO HAL module of the HS platform.
 */

/**
  * @brief The stubs functions table to exports SGPIO HAL functions in ROM.
  */
extern const hal_sgpio_func_stubs_t hal_sgpio_stubs;

/**
 *  @brief  Rxtc and rxprtc are synchronously reset.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_sgpio_set_rxtc_rst(hal_sgpio_adapter_t *psgpio_adp)
{
	psgpio_adp->base_addr->rxtmr_ctrl_b.rxtmr_crst = 1;
}

/**
 *  @brief  Set the rx timer counter value.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *  @param[in] rxtc_value Rx timer counter value.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_sgpio_set_rxtc_value(hal_sgpio_adapter_t *psgpio_adp, u16 rxtc_value)
{
	psgpio_adp->base_addr->rxtc_b.rxtc = rxtc_value;
}

/**
 *  @brief  Get the rx timer counter value.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *
 *  @returns Rx timer counter value.
 */
__STATIC_INLINE
u16 hal_sgpio_get_rxtc_value(hal_sgpio_adapter_t *psgpio_adp)
{
	u16 temp;

	temp = (u16)psgpio_adp->base_addr->rxtc_b.rxtc;
	return temp;
}

/**
 *  @brief  Set the maximum value of the rx prescale counter.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *  @param[in] prescale Maximum value.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_sgpio_set_rxtc_prescale(hal_sgpio_adapter_t *psgpio_adp, u16 prescale)
{
	psgpio_adp->base_addr->rxprval_b.rxprval = prescale;
}

/**
 *  @brief  Get the maximum value of the rx prescale counter.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *
 *  @returns Rx timer counter value.
 */
__STATIC_INLINE
u16 hal_sgpio_get_rxtc_prescale(hal_sgpio_adapter_t *psgpio_adp)
{
	u16 temp;

	temp = (u16)psgpio_adp->base_addr->rxprval_b.rxprval;
	return temp;
}

/**
 *  @brief  Set the rx prescale counter value.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *  @param[in] prerxtc_value Rx prescale counter value.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_sgpio_set_prerxtc_value(hal_sgpio_adapter_t *psgpio_adp, u16 prerxtc_value)
{
	psgpio_adp->base_addr->rxprtc_b.rxprtc = prerxtc_value;
}

/**
 *  @brief  Get the rx prescale counter value.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *
 *  @returns Rx prescale counter value.
 */
__STATIC_INLINE
u16 hal_sgpio_get_prerxtc_value(hal_sgpio_adapter_t *psgpio_adp)
{
	u16 temp;

	temp = (u16)psgpio_adp->base_addr->rxprtc_b.rxprtc;
	return temp;
}

/**
 *  @brief  Control the capture function.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *  @param[in] cap_en To enable or disable.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_sgpio_set_capture_en(hal_sgpio_adapter_t *psgpio_adp, BOOL cap_en)
{
	psgpio_adp->base_addr->cap_ctrl_b.cap_en = cap_en;
}

/**
 *  @brief  Get the capture value.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *
 *  @returns The capture value.
 */
__STATIC_INLINE
u16 hal_sgpio_get_capture_value(hal_sgpio_adapter_t *psgpio_adp)
{
	u16 temp;

	temp = (u16)psgpio_adp->base_addr->capr_b.capr;
	return temp;
}

/**
 *  @brief  Control the rxtc timer counter.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *  @param[in] start_en To start(1) or stop(0).
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_sgpio_set_rxtc_start_en(hal_sgpio_adapter_t *psgpio_adp, BOOL start_en)
{
	psgpio_adp->base_addr->rxtmr_ctrl_b.rxtmr_cen = start_en;
}

/**
 *  @brief  Control the input methold to start rx timer counter.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *  @param[in] rxtc_input_start Select the input methold.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_sgpio_set_rxtc_input_start_ctrl(hal_sgpio_adapter_t *psgpio_adp, sgpio_rxtc_input_start_t rxtc_input_start)
{
	psgpio_adp->base_addr->rxtmr_ctrl_b.rxtmredge_sel = rxtc_input_start;
}

/**
 *  @brief  Multc and mulprtc are synchronously reset.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_sgpio_set_multc_rst(hal_sgpio_adapter_t *psgpio_adp)
{
	psgpio_adp->base_addr->multmr_ctrl_b.multmr_crst = 1;
}

/**
 *  @brief  Set the multiple timer counter value.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *  @param[in] multc_value Multiple timer counter value.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_sgpio_set_multc_value(hal_sgpio_adapter_t *psgpio_adp, u16 multc_value)
{
	psgpio_adp->base_addr->multc_b.multc = multc_value;
}

/**
 *  @brief  Get the multiple timer counter value.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *
 *  @returns Multiple timer counter value.
 */
__STATIC_INLINE
u16 hal_sgpio_get_multc_value(hal_sgpio_adapter_t *psgpio_adp)
{
	u16 temp;

	temp = (u16)psgpio_adp->base_addr->multc_b.multc;
	return temp;
}

/**
 *  @brief  Set the maximum value of the multiple prescale counter.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *  @param[in] prescale Maximum value.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_sgpio_set_multc_prescale(hal_sgpio_adapter_t *psgpio_adp, u16 prescale)
{
	psgpio_adp->base_addr->mulprval_b.mulprval = prescale;
}

/**
 *  @brief  Get the maximum value of the multiple prescale counter.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *
 *  @returns Multiple timer counter value.
 */
__STATIC_INLINE
u16 hal_sgpio_get_multc_prescale(hal_sgpio_adapter_t *psgpio_adp)
{
	u16 temp;

	temp = (u16)psgpio_adp->base_addr->mulprval_b.mulprval;
	return temp;
}

/**
 *  @brief  Set the multiple prescale counter value.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *  @param[in] premultc_value Multiple prescale counter value.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_sgpio_set_premultc_value(hal_sgpio_adapter_t *psgpio_adp, u16 prerxtc_value)
{
	psgpio_adp->base_addr->mulprtc_b.mulprtc = prerxtc_value;
}

/**
 *  @brief  Get the multiple prescale counter value.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *
 *  @returns Multiple prescale counter value.
 */
__STATIC_INLINE
u16 hal_sgpio_get_premultc_value(hal_sgpio_adapter_t *psgpio_adp)
{
	u16 temp;

	temp = (u16)psgpio_adp->base_addr->mulprtc_b.mulprtc;
	return temp;
}

/**
 *  @brief  Control the multiple timer counter.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *  @param[in] start_en To start(1) or stop(0).
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_sgpio_set_multc_start_en(hal_sgpio_adapter_t *psgpio_adp, BOOL start_en)
{
	psgpio_adp->base_addr->multmr_ctrl_b.multmr_cen = start_en;
}

/**
 *  @brief  Select the mode of the multiple timer counter.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *  @param[in] multc_mode Select timer or counter mode.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_sgpio_set_multc_mode_ctrl(hal_sgpio_adapter_t *psgpio_adp, sgpio_multc_mode_t multc_mode)
{
	psgpio_adp->base_addr->multmr_ctrl_b.mulmode_en = multc_mode;
}

/**
 *  @brief  Control the multiple timer counter to use the FIFO mode.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *  @param[in] fifo_mode_en To start(1) or stop(0).
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_sgpio_set_multc_fifo_mode(hal_sgpio_adapter_t *psgpio_adp, BOOL fifo_mode_en)
{
	psgpio_adp->base_addr->mulmc_b.mul_fmode_en = fifo_mode_en;
}

/**
 *  @brief  Get the countdown counter value for counting the multc match event0.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *
 *  @returns The countdown counter value.
 */
__STATIC_INLINE
u8 hal_sgpio_get_multc_match_event0_cnt_value(hal_sgpio_adapter_t *psgpio_adp)
{
	u8 temp;

	temp = (u8)(psgpio_adp->base_addr->mul_mcnt_b.mul_mcnt + 1);
	return temp;
}

/**
 *  @brief  Get the rxdata value.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *
 *  @returns The rxdata value.
 */
__STATIC_INLINE
u32 hal_sgpio_get_rxdata(hal_sgpio_adapter_t *psgpio_adp)
{
	u32 temp;

	temp = psgpio_adp->base_addr->rxdata_dp;
	return temp;
}

/**
 *  @brief  Get the rxdata value being processed.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *
 *  @returns The rxdata value being processed.
 */
__STATIC_INLINE
u32 hal_sgpio_get_rxdata_prebuf(hal_sgpio_adapter_t *psgpio_adp)
{
	u32 temp;

	temp = psgpio_adp->base_addr->rxdata;
	return temp;
}

/**
 *  @brief  Mask the match pattern for monitoring rxdata.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *  @param[in] match_mask The bit mask.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_sgpio_set_rxdata_match_mask(hal_sgpio_adapter_t *psgpio_adp, u32 match_mask)
{
	psgpio_adp->base_addr->rxdatamask = match_mask;
}

/**
 *  @brief  Get the mask value.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *
 *  @returns The mask value.
 */
__STATIC_INLINE
u32 hal_sgpio_get_rxdata_match_mask(hal_sgpio_adapter_t *psgpio_adp)
{
	u32 temp;

	temp = psgpio_adp->base_addr->rxdatamask;
	return temp;
}

/**
 *  @brief  Select the input direction of the rxdata.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *  @param[in] direction Select the input is MSB or LSB.
 *                      -0: input data from msb.
 *                      -1: input data from lsb.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_sgpio_set_rxdata_direction(hal_sgpio_adapter_t *psgpio_adp, u8 direction)
{
	psgpio_adp->base_addr->data_ctrl_b.rxdata_dir = direction;
}

/**
 *  @brief  Control the rx to become the bi-direction.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *  @param[in] inoutput Select the input or bi-direction.
 *                      -0: Only input.
 *                      -1: Bi-direction.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_sgpio_set_rx_in_out_ctrl(hal_sgpio_adapter_t *psgpio_adp, sgpio_rx_inoutput_t inoutput)
{
	psgpio_adp->base_addr->mulemr_b.biout_en = inoutput;
}

/**
 *  @brief  Control the txdata to work
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *  @param[in] txdata_en To start(1) or stop(0).
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_sgpio_init_txdata_en(hal_sgpio_adapter_t *psgpio_adp, BOOL txdata_en)
{
	psgpio_adp->base_addr->mulmc_b.mul_mr0sclk_en = txdata_en;
}

/**
 *  @brief  Set the txdata value.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *  @param[in] txdata The txdata value.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_sgpio_set_txdata(hal_sgpio_adapter_t *psgpio_adp, u32 txdata)
{
	psgpio_adp->base_addr->muldata_dp = txdata;
}

/**
 *  @brief  Set the txdata value being processed.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *  @param[in] txdata The txdata value being processed.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_sgpio_set_txdata_prebuf(hal_sgpio_adapter_t *psgpio_adp, u32 txdata)
{
	psgpio_adp->base_addr->muldata = txdata;
}

/**
 *  @brief  Get the txdata value.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *
 *  @returns The txdata value.
 */
__STATIC_INLINE
u32 hal_sgpio_get_txdata(hal_sgpio_adapter_t *psgpio_adp)
{
	u32 temp;

	temp = psgpio_adp->base_addr->muldata_dp;
	return temp;
}

/**
 *  @brief  Get the txdata value being processed.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *
 *  @returns The txdata value being processed.
 */
__STATIC_INLINE
u32 hal_sgpio_get_txdata_prebuf(hal_sgpio_adapter_t *psgpio_adp)
{
	u32 temp;

	temp = psgpio_adp->base_addr->muldata;
	return temp;
}

/**
 *  @brief  Select the output direction of the txdata.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *  @param[in] direction Select the output is MSB or LSB.
 *                      -0: output data from msb.
 *                      -1: output data from lsb.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_sgpio_set_txdata_direction(hal_sgpio_adapter_t *psgpio_adp, u8 direction)
{
	psgpio_adp->base_addr->data_ctrl_b.txdata_dir = direction;
}

/**
 *  @brief  Control to drive the output state by setting this bit.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *  @param[in] value Set the output is low or high.
 *                      -0: output is low.
 *                      -1: output is high.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_sgpio_set_output_value(hal_sgpio_adapter_t *psgpio_adp, sgpio_output_value_t value)
{
	psgpio_adp->base_addr->output_b.output = value;
}

/**
 *  @brief  Get the output state.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *
 *  @returns The output state.
 */
__STATIC_INLINE
u32 hal_sgpio_get_output_value(hal_sgpio_adapter_t *psgpio_adp)
{
	u32 temp;

	temp = psgpio_adp->base_addr->output_b.output;
	return temp;
}

/**
 *  @brief  Make the output state inverse.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_sgpio_set_output_inverse(hal_sgpio_adapter_t *psgpio_adp)
{
	psgpio_adp->base_addr->output_b.output = ~psgpio_adp->base_addr->output_b.output;
}

/**
 *  @brief  Get the SGPIO interrupt status.
 *
 *  @param[in] psgpio_adp The SGPIO adapter.
 *
 *  @returns The interrupt status.
 */
__STATIC_INLINE
u32 hal_sgpio_get_status(hal_sgpio_adapter_t *psgpio_adp)
{
	u32 temp;

	temp = psgpio_adp->base_addr->is;
	return temp;
}

/** @} */ /* End of group hs_hal_sgpio */

void hal_sgpio_irq_handler(void *hid);
void hal_sgpio_irq_reg(void);
void hal_sgpio_unreg(hal_sgpio_adapter_t *psgpio_adp);
void hal_sgpio_reg_cb(hal_sgpio_adapter_t *psgpio_adp, sgpio_irq_user_cb_t callback, void *arg, sgpio_irq_shift_t irq_shift);
void hal_sgpio_unreg_cb(hal_sgpio_adapter_t *psgpio_adp, sgpio_irq_shift_t irq_shift);
HAL_Status hal_sgpio_en_ctrl(sgpio_index_sel_t sgpio_index, BOOL en);
HAL_Status hal_sgpio_init(hal_sgpio_adapter_t *psgpio_adp, sgpio_index_sel_t sgpio_index);
void hal_sgpio_deinit(hal_sgpio_adapter_t *psgpio_adp);
void hal_sgpio_pin_free(hal_sgpio_adapter_t *psgpio_adp);
void hal_sgpio_reset(hal_sgpio_adapter_t *psgpio_adp);
void hal_sgpio_enter_critical(void);
void hal_sgpio_exit_critical(void);
void hal_sgpio_set_rxtc_stop_ctrl(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_event_t *prxtc_event);
void hal_sgpio_get_rxtc_stop_ctrl(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_event_t *prxtc_event);
void hal_sgpio_set_rxtc_reset_ctrl(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_event_t *prxtc_event);
void hal_sgpio_get_rxtc_reset_ctrl(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_event_t *prxtc_event);
void hal_sgpio_set_rxtc_match_value(hal_sgpio_adapter_t *psgpio_adp, sgpio_rxtc_match_event_t match_event, u16 match_value);
void hal_sgpio_set_rxtc_int(hal_sgpio_adapter_t *psgpio_adp,  sgpio_rxtc_match_event_t match_event, hal_sgpio_set_irq_t *psgpio_set_irq);
void hal_sgpio_set_capture_ctrl(hal_sgpio_adapter_t *psgpio_adp, sgpio_capture_type_t capture_type, BOOL cap_en);
void hal_sgpio_set_capture_compare(hal_sgpio_adapter_t *psgpio_adp, u8 cap_cmpval_sel, u16 cap_cmpval);
void hal_sgpio_set_capture_int(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_set_irq_t *psgpio_set_irq);
void hal_sgpio_set_multc_stop_ctrl(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_multc_event_t *pmultc_event);
void hal_sgpio_get_multc_stop_ctrl(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_multc_event_t *pmultc_event);
void hal_sgpio_set_multc_reset_ctrl(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_multc_event_t *pmultc_event);
void hal_sgpio_get_multc_reset_ctrl(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_multc_event_t *pmultc_event);
void hal_sgpio_set_multc_match_value(hal_sgpio_adapter_t *psgpio_adp, sgpio_multc_match_group_t match_group, sgpio_multc_match_event_t match_event,
									 u16 match_value);
void hal_sgpio_set_multc_match_event0_int(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_set_irq_t *psgpio_set_irq);
void hal_sgpio_set_multc_match_group(hal_sgpio_adapter_t *psgpio_adp, sgpio_multc_match_group_t match_group);
void hal_sgpio_set_multc_fifo_value(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_fifo_value_t *pfifo_value);
void hal_sgpio_set_rxtc_external_match(hal_sgpio_adapter_t *psgpio_adp, sgpio_rxtc_match_event_t match_event, sgpio_external_output_t external_output);
void hal_sgpio_set_multc_external_match(hal_sgpio_adapter_t *psgpio_adp, sgpio_multc_match_event_t match_event, sgpio_external_output_t external_output);
void hal_sgpio_set_multc_match_event0_cnt_int(hal_sgpio_adapter_t *psgpio_adp, BOOL match_cnt_en, u8 match_down_cnt, hal_sgpio_set_irq_t *psgpio_set_irq);
void hal_sgpio_set_multc_match_event0_cnt(hal_sgpio_adapter_t *psgpio_adp, BOOL match_cnt_en, u8 match_down_cnt);
void hal_sgpio_init_rxdata_time_sampling(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_sampling_event_t *psampling_event);
void hal_sgpio_deinit_rxdata_time_sampling(hal_sgpio_adapter_t *psgpio_adp);
void hal_sgpio_init_rxdata_capture_compare(hal_sgpio_adapter_t *psgpio_adp, sgpio_cmp_result_bit_t cmp_result_bit, u16 cap_cmpval);
void hal_sgpio_deinit_rxdata_capture_compare(hal_sgpio_adapter_t *psgpio_adp);
HAL_Status hal_sgpio_set_rxdata_load_int(hal_sgpio_adapter_t *psgpio_adp, u8 bit_length, hal_sgpio_set_irq_t *psgpio_set_irq);
void hal_sgpio_set_rxdata_prebuf_bit_shift_int(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_set_irq_t *psgpio_set_irq);
void hal_sgpio_reset_rxdata(hal_sgpio_adapter_t *psgpio_adp);
void hal_sgpio_set_rxdata_match_int(hal_sgpio_adapter_t *psgpio_adp, BOOL rxdata_match_en, u32 match_value, hal_sgpio_set_irq_t *psgpio_set_irq);
HAL_Status hal_sgpio_set_txdata_bit_length_int(hal_sgpio_adapter_t *psgpio_adp, u8 bit_length, hal_sgpio_set_irq_t *psgpio_set_irq);
void hal_sgpio_set_txdata_prebuf_bit_shift_int(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_set_irq_t *psgpio_set_irq);
void hal_sgpio_reset_txdata(hal_sgpio_adapter_t *psgpio_adp);
u32 hal_sgpio_set_time_to_rxtc(hal_sgpio_adapter_t *psgpio_adp, sgpio_time_unit_t time_unit, u32 time_value);
u32 hal_sgpio_set_time_to_multc(hal_sgpio_adapter_t *psgpio_adp, sgpio_time_unit_t time_unit, u32 time_value);
u32 hal_sgpio_set_rxtc_to_time(hal_sgpio_adapter_t *psgpio_adp, u16 rxtc_unit, sgpio_time_unit_t time_unit);
u32 hal_sgpio_set_multc_to_time(hal_sgpio_adapter_t *psgpio_adp, u16 multc_unit, sgpio_time_unit_t time_unit);
void hal_sgpio_clean_status(hal_sgpio_adapter_t *psgpio_adp, u32 sgpio_is);
void hal_sgpio_update_rxtcmr(hal_sgpio_adapter_t *psgpio_adp, sgpio_rxtc_match_event_t match_event, u16 old_prescale);
void hal_sgpio_update_multcmr(hal_sgpio_adapter_t *psgpio_adp, sgpio_multc_match_group_t match_group, sgpio_multc_match_event_t match_event, u16 old_prescale);
void hal_sgpio_rxtc_timer_mode(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_timer_mode_t *psgpio_rxtc_timer_mode);
void hal_sgpio_multc_timer_mode(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_multc_timer_mode_t *psgpio_multc_timer_mode);
void hal_sgpio_multc_counter_mode(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_multc_counter_mode_t *psgpio_multc_counter_mode);
void hal_sgpio_rxtc_timer_match_output(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_timer_match_output_t *psgpio_rxtc_timer_match_output);
void hal_sgpio_multc_timer_counter_match_output(hal_sgpio_adapter_t *psgpio_adp,
		hal_sgpio_multc_timer_counter_match_output_t *psgpio_multc_timer_counter_match_output);
void hal_sgpio_rxtc_capture_mode(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_capture_mode_t *psgpio_rxtc_capture_mode);
void hal_sgpio_rxtc_capture_timeout(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_capture_timeout_t *psgpio_rxtc_capture_timeout);
void hal_sgpio_rxtc_capture_monitor(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_capture_monitor_t *psgpio_rxtc_capture_monitor);
u32 hal_sgpio_get_rxtc_capture_time(hal_sgpio_adapter_t *psgpio_adp, sgpio_time_unit_t time_unit);
void hal_sgpio_init_rxdata_capture_compare_time(hal_sgpio_adapter_t *psgpio_adp, sgpio_cmp_result_bit_t cmp_result_bit, sgpio_time_unit_t time_unit,
		u32 cap_cmpval_time);
void hal_sgpio_sampling_rxdata(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_sampling_rxdata_t *psgpio_sampling_data);
u32 hal_sgpio_get_input_rxdata(hal_sgpio_adapter_t *psgpio_adp);
u32 hal_sgpio_get_arrange_rxdata(hal_sgpio_adapter_t *psgpio_adp, u32 rxdata_tp);
void hal_sgpio_capture_compare_rxdata(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_capture_compare_rxdata_t *psgpio_compare_data);
void hal_sgpio_txdata_bit_symbol(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_txdata_bit_symbol_t *psgpio_txdata_bit_symbol);
void hal_sgpio_txdata(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_txdata_t *psgpio_txdata);
void hal_sgpio_txdata_bit_length_irq(void *data);
void hal_sgpio_send_txdata(hal_sgpio_adapter_t *psgpio_adp);
void hal_sgpio_reset_receive_rxdata(hal_sgpio_adapter_t *psgpio_adp);
void hal_sgpio_disable_rxdata_match(hal_sgpio_adapter_t *psgpio_adp);
void hal_sgpio_monitor_rxdata(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_monitor_rxdata_t *pmonitor_rxdata);
void hal_sgpio_multc_fifo_reset(hal_sgpio_adapter_t *psgpio_adp);
void hal_sgpio_dma_match_output_irq_handle(void *data);
HAL_Status hal_sgpio_dma_match_output_init(hal_sgpio_adapter_t *psgpio_adp, hal_gdma_adaptor_t *pgdma_adaptor, hal_sgpio_dma_match_output_t *pdma_match_output);
HAL_Status hal_sgpio_dma_match_output_deinit(hal_sgpio_adapter_t *psgpio_adp);
void hal_sgpio_dma_handshake_init(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_dma_match_output_t *pdma_match_output);
void hal_sgpio_dma_preload_data(hal_sgpio_adapter_t *psgpio_adp);
void hal_sgpio_dma_send_start(hal_sgpio_adapter_t *psgpio_adp);
void hal_sgpio_dma_time_to_multc(hal_sgpio_adapter_t *psgpio_adp, u16 *pmemory_addr, u8 reset_cnt, sgpio_time_unit_t time_unit);
void hal_sgpio_reset_rxtc_ctrl(hal_sgpio_adapter_t *psgpio_adp);
void hal_sgpio_reset_multc_ctrl(hal_sgpio_adapter_t *psgpio_adp);
void hal_sgpio_reset_rxtc_ext_match(hal_sgpio_adapter_t *psgpio_adp);
void hal_sgpio_reset_multc_ext_match(hal_sgpio_adapter_t *psgpio_adp);


#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_SGPIO_H_"

