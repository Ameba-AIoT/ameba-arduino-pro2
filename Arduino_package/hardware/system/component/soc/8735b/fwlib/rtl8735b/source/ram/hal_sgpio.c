/**************************************************************************//**
 * @file     hal_sgpio.c
 * @brief    This SGPIO HAL API functions.
 *
 * @version  V1.00
 * @date     2016-09-19
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

#include "hal_cache.h"
#include "hal_pinmux.h"
#include "hal_sgpio.h"
#include "hal_gdma.h"

#if CONFIG_SGPIO_EN

extern void hal_syson_sgpio_rst(uint32_t sgpio_index);


/**
 * @addtogroup hs_hal_sgpio SGPIO
 * @{
 */

/**
 *  @brief The SGPIO interrupt handler.
 *
 *  @param[in]  hid The handler ID, it should be the SGPIO adapter.
 *
 *  @returns void
 */
void hal_sgpio_irq_handler(void *hid)
{
	hal_sgpio_stubs.hal_sgpio_irq_handler(hid);
}

/**
 *  @brief To register a IRQ handler for the SGPIO.
 *
 *  @returns void
 */
void hal_sgpio_irq_reg(void)
{
	hal_sgpio_stubs.hal_sgpio_irq_reg();
}

/**
 *  @brief To un-register the SGPIO IRQ handler.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *
 *  @returns void
 */
void hal_sgpio_unreg(hal_sgpio_adapter_t *psgpio_adp)
{
	hal_sgpio_stubs.hal_sgpio_unreg(psgpio_adp);
}

/**
 *  @brief Register the callback function and argument of the interrupt event.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  callback The callback function.
 *  @param[in]  arg The callback argument.
 *  @param[in]  irq_shift The interrupt event number.
 *
 *  @returns void
 */
void hal_sgpio_reg_cb(hal_sgpio_adapter_t *psgpio_adp, sgpio_irq_user_cb_t callback, void *arg, sgpio_irq_shift_t irq_shift)
{
	hal_sgpio_stubs.hal_sgpio_reg_cb(psgpio_adp, callback, arg, irq_shift);
}

/**
 *  @brief Cancel the callback function and argument of the interrupt event.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  irq_shift The interrupt event number.
 *
 *  @returns void
 */
void hal_sgpio_unreg_cb(hal_sgpio_adapter_t *psgpio_adp, sgpio_irq_shift_t irq_shift)
{
	hal_sgpio_stubs.hal_sgpio_unreg_cb(psgpio_adp, irq_shift);
}

/**
 *  @brief To enable or disable SGPIO for the platform.
 *
 *  @param[in] sgpio_index The SGPIO index. It can be 0 .. 2.
 *  @param[in] en  Enable control: 0: disable, 1: enable.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_sgpio_en_ctrl(sgpio_index_sel_t sgpio_index, BOOL en)
{
	return hal_sgpio_stubs.hal_sgpio_en_ctrl(sgpio_index, en);
}

/**
 *  @brief Initialize the sgpio hardware and turn on the SGPIO
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  sgpio_index The SGPIO index. It can be 0 .. 2.
 *  @param[in]  pin_sel sgpio pin mux.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_sgpio_init(hal_sgpio_adapter_t *psgpio_adp, sgpio_index_sel_t sgpio_index)
{
	return hal_sgpio_stubs.hal_sgpio_init(psgpio_adp, sgpio_index);
}

/**
 *  @brief De-initialize of the sgpio hardware and turn off the SGPIO.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *
 *  @returns void
 */
void hal_sgpio_deinit(hal_sgpio_adapter_t *psgpio_adp)
{
	hal_sgpio_stubs.hal_sgpio_deinit(psgpio_adp);

	hal_sgpio_pin_free(psgpio_adp);
}

/**
 *  @brief Be able to release the SGPIO pins from the pin mux after initializes the SGPIO device.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *
 *  @returns void
 */
void hal_sgpio_pin_free(hal_sgpio_adapter_t *psgpio_adp)
{
	hal_pinmux_unregister(PIN_F1, PID_SGPIO);
	hal_pinmux_unregister(PIN_F14, PID_SGPIO);
	hal_pinmux_unregister(PIN_F15, PID_SGPIO);
}

/**
 *  @brief Reset the SGPIO and registers.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *
 *  @returns void
 */
void hal_sgpio_reset(hal_sgpio_adapter_t *psgpio_adp)
{
	hal_syson_sgpio_rst(psgpio_adp->sgpio_index);
}

/**
*  @brief To enter a critical code section, mainly it
*         disable the SGPIO interrupt to prevent race condition.
*
*  @returns void
*/
void hal_sgpio_enter_critical(void)
{
	hal_sgpio_stubs.hal_sgpio_enter_critical();
}

/**
 *  @brief To exit a critical code section, it will re-enable the SGPIO interrupt
 *         only when the exiting critical section is the top level.
 *
 *  @returns void
 */
void hal_sgpio_exit_critical(void)
{
	hal_sgpio_stubs.hal_sgpio_exit_critical();
}

/**
 *  @brief  Set the stop events to make the rxtc timer stop.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  prxtc_event The stop events. 0: disable, 1: enable.
 *                      rxtc_match_event0 - This event is that the rx timer value matches rx match register 0.
 *                      rxtc_match_event1 - This event is that the rx timer value matches rx match register 1.
 *                      rxtc_match_event2 - This event is that the rx timer value matches rx match register 2.
 *                      multc_match_event0 - This event is that the multc timer value matches Multiple Match Register 0.
 *                      rx_postc_zero - This event is that the rxpostc register becomes 0.
 *                      capture_event - This event is that happen the capture.
 *
 *  @returns void
 */
void hal_sgpio_set_rxtc_stop_ctrl(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_event_t *prxtc_event)
{
	hal_sgpio_stubs.hal_sgpio_set_rxtc_stop_ctrl(psgpio_adp, prxtc_event);
}

/**
 *  @brief  Update the rxtc stop events of the SGPIO adapter according to the SGPIO registers.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  prxtc_event The stop events.
 *
 *  @returns void
 */
void hal_sgpio_get_rxtc_stop_ctrl(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_event_t *prxtc_event)
{
	hal_sgpio_stubs.hal_sgpio_get_rxtc_stop_ctrl(psgpio_adp, prxtc_event);
}

/**
 *  @brief  Set the reset events to make the rxtc timer reset.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  prxtc_event The reset events. 0: disable, 1: enable.
 *                      rxtc_match_event0 - This event is that the rx timer value matches rx match register 0.
 *                      rxtc_match_event1 - This event is that the rx timer value matches rx match register 1.
 *                      rxtc_match_event2 - This event is that the rx timer value matches rx match register 2.
 *                      multc_match_event0 - This event is that the multc timer value matches Multiple Match Register 0.
 *                      rx_postc_zero - This event is that the rxpostc register becomes 0.
 *                      capture_event - This event is that happen the capture.
 *
 *  @returns void
 */
void hal_sgpio_set_rxtc_reset_ctrl(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_event_t *prxtc_event)
{
	hal_sgpio_stubs.hal_sgpio_set_rxtc_reset_ctrl(psgpio_adp, prxtc_event);
}

/**
 *  @brief  Update the rxtc reset events of the SGPIO adapter according to the SGPIO registers.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  prxtc_event The reset events.
 *
 *  @returns void
 */
void hal_sgpio_get_rxtc_reset_ctrl(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_event_t *prxtc_event)
{
	hal_sgpio_stubs.hal_sgpio_get_rxtc_reset_ctrl(psgpio_adp, prxtc_event);
}

/**
 *  @brief  Set the register value of the rxtc match event.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  match_event Select the rxtc match event.
 *  @param[in]  match_value The match value of the register value.
 *
 *  @returns void
 */
void hal_sgpio_set_rxtc_match_value(hal_sgpio_adapter_t *psgpio_adp, sgpio_rxtc_match_event_t match_event, u16 match_value)
{
	hal_sgpio_stubs.hal_sgpio_set_rxtc_match_value(psgpio_adp, match_event, match_value);
}

/**
 *  @brief  Set the interrupt control of the rxtc match event.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  match_event Select the rxtc match event.
 *  @param[in]  psgpio_set_irq The parameter structure is for initializing the interrupt event.
 *                      int_en - 0: disbale this event interrupt, 1: enable.
 *                      imr_en - 0: disbale mask event interrupt, 1: enable.
 *                      callback_reg_en - 0: don't register this callback function, 1: register this callback function.
 *                      callback - The callback function.
 *                      arg - The callback argument.
 *
 *  @returns void
 */
void hal_sgpio_set_rxtc_int(hal_sgpio_adapter_t *psgpio_adp,  sgpio_rxtc_match_event_t match_event, hal_sgpio_set_irq_t *psgpio_set_irq)
{
	hal_sgpio_stubs.hal_sgpio_set_rxtc_int(psgpio_adp, match_event, psgpio_set_irq);
}

/**
 *  @brief  Set the capture event control.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  capture_type Select the capture event.
 *  @param[in]  cap_en Enable or Disable the capture function
 *
 *  @returns void
 */
void hal_sgpio_set_capture_ctrl(hal_sgpio_adapter_t *psgpio_adp, sgpio_capture_type_t capture_type, BOOL cap_en)
{
	hal_sgpio_stubs.hal_sgpio_set_capture_ctrl(psgpio_adp, capture_type, cap_en);
}

/**
 *  @brief  Translate the capture value into "0" or "1" according to the result of the comparison.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  cap_cmpval_sel Set that the rxdata register receives value 0 or 1 when the capture value is bigger than cap_cmpval.
 *  @param[in]  cap_cmpval The compare value.
 *
 *  @returns void
 */
void hal_sgpio_set_capture_compare(hal_sgpio_adapter_t *psgpio_adp, u8 cap_cmpval_sel, u16 cap_cmpval)
{
	hal_sgpio_stubs.hal_sgpio_set_capture_compare(psgpio_adp, cap_cmpval_sel, cap_cmpval);
}

/**
 *  @brief  Set the interrupt control of the capture event.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  psgpio_set_irq The parameter structure is for initializing the interrupt event.
 *                      int_en - 0: disbale this event interrupt, 1: enable.
 *                      imr_en - 0: disbale mask event interrupt, 1: enable.
 *                      callback_reg_en - 0: don't register this callback function, 1: register this callback function.
 *                      callback - The callback function.
 *                      arg - The callback argument.
 *
 *  @returns void
 */
void hal_sgpio_set_capture_int(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_set_irq_t *psgpio_set_irq)
{
	hal_sgpio_stubs.hal_sgpio_set_capture_int(psgpio_adp, psgpio_set_irq);
}

/**
 *  @brief  Set the stop events to make the multc timer stop.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  pmultc_event The stop events. 0: disable, 1: enable.
 *                      multc_match_event0 - This event is that the multc timer value matches multiple match register 0.
 *                      rxtc_match_event0 - This event is that the rx timer value matches rx match register 0.
 *                      multc_mcnt_zero - This event is that the mul_mcnt register becomes 0.
 *
 *  @returns void
 */
void hal_sgpio_set_multc_stop_ctrl(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_multc_event_t *pmultc_event)
{
	hal_sgpio_stubs.hal_sgpio_set_multc_stop_ctrl(psgpio_adp, pmultc_event);
}

/**
 *  @brief  Update the multc stop events of the SGPIO adapter according to the SGPIO registers.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  pmultc_event The stop events.
 *
 *  @returns void
 */
void hal_sgpio_get_multc_stop_ctrl(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_multc_event_t *pmultc_event)
{
	hal_sgpio_stubs.hal_sgpio_get_multc_stop_ctrl(psgpio_adp, pmultc_event);
}

/**
 *  @brief  Set the reset events to make the multc timer reset.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  pmultc_event The reset events. 0: disable, 1: enable.
 *                      multc_match_event0 - This event is that the multc timer value matches multiple match register 0.
 *                      rxtc_match_event0 - This event is that the rx timer value matches rx match register 0.
 *                      multc_mcnt_zero - This event is that the mul_mcnt register becomes 0.
 *
 *  @returns void
 */
void hal_sgpio_set_multc_reset_ctrl(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_multc_event_t *pmultc_event)
{
	hal_sgpio_stubs.hal_sgpio_set_multc_reset_ctrl(psgpio_adp, pmultc_event);
}

/**
 *  @brief  Update the multc reset events of the SGPIO adapter according to the SGPIO registers.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  pmultc_event The reset events.
 *
 *  @returns void
 */
void hal_sgpio_get_multc_reset_ctrl(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_multc_event_t *pmultc_event)
{
	hal_sgpio_stubs.hal_sgpio_get_multc_reset_ctrl(psgpio_adp, pmultc_event);
}

/**
 *  @brief  Set the register value of the multc match event.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  match_group Select the group of the multc match event.
 *  @param[in]  match_event Select the multc match event.
 *  @param[in]  match_value The match value of the register value.
 *
 *  @returns void
 */
void hal_sgpio_set_multc_match_value(hal_sgpio_adapter_t *psgpio_adp, sgpio_multc_match_group_t match_group, sgpio_multc_match_event_t match_event,
									 u16 match_value)
{
	hal_sgpio_stubs.hal_sgpio_set_multc_match_value(psgpio_adp, match_group, match_event, match_value);
}

/**
 *  @brief  Set the interrupt control of the multc match event 0.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  psgpio_set_irq The parameter structure is for initializing the interrupt event.
 *                      int_en - 0: disbale this event interrupt, 1: enable.
 *                      imr_en - 0: disbale mask event interrupt, 1: enable.
 *                      callback_reg_en - 0: don't register this callback function, 1: register this callback function.
 *                      callback - The callback function.
 *                      arg - The callback argument.
 *
 *  @returns void
 */
void hal_sgpio_set_multc_match_event0_int(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_set_irq_t *psgpio_set_irq)
{
	hal_sgpio_stubs.hal_sgpio_set_multc_match_event0_int(psgpio_adp, psgpio_set_irq);
}

/**
 *  @brief  Select the group of the multc match event.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  match_group The group of the multc match event.
 *
 *  @returns void
 */
void hal_sgpio_set_multc_match_group(hal_sgpio_adapter_t *psgpio_adp, sgpio_multc_match_group_t match_group)
{
	hal_sgpio_stubs.hal_sgpio_set_multc_match_group(psgpio_adp, match_group);
}

/**
 *  @brief  Set the register value of the multc match event by using the FIFO mode.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  pfifo_value The multc match event when use the FIFO mode.
 *
 *  @returns void
 */
void hal_sgpio_set_multc_fifo_value(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_fifo_value_t *pfifo_value)
{
	hal_sgpio_stubs.hal_sgpio_set_multc_fifo_value(psgpio_adp, pfifo_value);
}

/**
 *  @brief  Set the external output for the rxtc match event.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  match_event Select the rxtc match event.
 *  @param[in]  external_output Set the output state when happen the rxtc match event.
 *
 *  @returns void
 */
void hal_sgpio_set_rxtc_external_match(hal_sgpio_adapter_t *psgpio_adp, sgpio_rxtc_match_event_t match_event, sgpio_external_output_t external_output)
{
	hal_sgpio_stubs.hal_sgpio_set_rxtc_external_match(psgpio_adp, match_event, external_output);
}

/**
 *  @brief  Set the external output for the multc match event.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  match_event Select the multc match event.
 *  @param[in]  external_output Set the output state when happen the multc match event.
 *
 *  @returns void
 */
void hal_sgpio_set_multc_external_match(hal_sgpio_adapter_t *psgpio_adp, sgpio_multc_match_event_t match_event, sgpio_external_output_t external_output)
{
	hal_sgpio_stubs.hal_sgpio_set_multc_external_match(psgpio_adp, match_event, external_output);
}

/**
 *  @brief  Set the control and interrupt for counting multc match event 0.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  match_cnt_en Enable or Disable to count the multc match event 0.
 *  @param[in]  match_down_cnt Set the countdown value. When match_down_cnt is zero, make the interrupt.
 *  @param[in]  psgpio_set_irq The parameter structure is for initializing the interrupt event.
 *                      int_en - 0: disbale this event interrupt, 1: enable.
 *                      imr_en - 0: disbale mask event interrupt, 1: enable.
 *                      callback_reg_en - 0: don't register this callback function, 1: register this callback function.
 *                      callback - The callback function.
 *                      arg - The callback argument.
 *
 *  @returns void
 */
void hal_sgpio_set_multc_match_event0_cnt_int(hal_sgpio_adapter_t *psgpio_adp, BOOL match_cnt_en, u8 match_down_cnt, hal_sgpio_set_irq_t *psgpio_set_irq)
{
	hal_sgpio_stubs.hal_sgpio_set_multc_match_event0_cnt_int(psgpio_adp, match_cnt_en, match_down_cnt, psgpio_set_irq);
}

/**
 *  @brief  Set the control for counting multc match event 0.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  match_cnt_en Enable or Disable to count the multc match event 0.
 *  @param[in]  match_down_cnt Set the countdown value. When match_down_cnt is zero, make the interrupt.
 *
 *  @returns void
 */
void hal_sgpio_set_multc_match_event0_cnt(hal_sgpio_adapter_t *psgpio_adp, BOOL match_cnt_en, u8 match_down_cnt)
{
	hal_sgpio_stubs.hal_sgpio_set_multc_match_event0_cnt(psgpio_adp, match_cnt_en, match_down_cnt);
}

/**
 *  @brief  Set the smapling event for rxdata.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  psampling_event The smapling events. 0: disable, 1: enable.
 *                      rxtc_match_event0 - This event is that the rx timer value matches rx match register 0.
 *                      rxtc_match_event1 - This event is that the rx timer value matches rx match register 1.
 *                      rxtc_match_event2 - This event is that the rx timer value matches rx match register 2.
 *
 *  @returns void
 */
void hal_sgpio_init_rxdata_time_sampling(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_sampling_event_t *psampling_event)
{
	hal_sgpio_stubs.hal_sgpio_init_rxdata_time_sampling(psgpio_adp, psampling_event);
}

/**
 *  @brief  Disable the smapling event for rxdata.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *
 *  @returns void
 */
void hal_sgpio_deinit_rxdata_time_sampling(hal_sgpio_adapter_t *psgpio_adp)
{
	hal_sgpio_stubs.hal_sgpio_deinit_rxdata_time_sampling(psgpio_adp);
}

/**
 *  @brief  Initialize that the rxdata source is the capture compare result.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  cmp_result_bit Set that the rxdata register receives value 0 or 1 when the capture value is bigger than cap_cmpval.
 *  @param[in]  cap_cmpval The compare value. This unit is count.
 *
 *  @returns void
 */
void hal_sgpio_init_rxdata_capture_compare(hal_sgpio_adapter_t *psgpio_adp, sgpio_cmp_result_bit_t cmp_result_bit, u16 cap_cmpval)
{
	hal_sgpio_stubs.hal_sgpio_init_rxdata_capture_compare(psgpio_adp, cmp_result_bit, cap_cmpval);
}

/**
 *  @brief  De-initialize that the rxdata source is the capture compare result.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *
 *  @returns void
 */
void hal_sgpio_deinit_rxdata_capture_compare(hal_sgpio_adapter_t *psgpio_adp)
{
	hal_sgpio_stubs.hal_sgpio_deinit_rxdata_capture_compare(psgpio_adp);
}

/**
 *  @brief  Set the rxdata sampling length and interrupt. When reach the length to be received, generate the interrupt.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  bit_length The sampling bit length.
 *  @param[in]  psgpio_set_irq The parameter structure is for initializing the interrupt event.
 *                      int_en - 0: disbale this event interrupt, 1: enable.
 *                      imr_en - 0: disbale mask event interrupt, 1: enable.
 *                      callback_reg_en - 0: don't register this callback function, 1: register this callback function.
 *                      callback - The callback function.
 *                      arg - The callback argument.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_sgpio_set_rxdata_load_int(hal_sgpio_adapter_t *psgpio_adp, u8 bit_length, hal_sgpio_set_irq_t *psgpio_set_irq)
{
	return hal_sgpio_stubs.hal_sgpio_set_rxdata_load_int(psgpio_adp, bit_length, psgpio_set_irq);
}

/**
 *  @brief  Control the interrupt when happen the bit shift of rxdata.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  psgpio_set_irq The parameter structure is for initializing the interrupt event.
 *                      int_en - 0: disbale this event interrupt, 1: enable.
 *                      imr_en - 0: disbale mask event interrupt, 1: enable.
 *                      callback_reg_en - 0: don't register this callback function, 1: register this callback function.
 *                      callback - The callback function.
 *                      arg - The callback argument.
 *
 *  @returns void
 */
void hal_sgpio_set_rxdata_prebuf_bit_shift_int(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_set_irq_t *psgpio_set_irq)
{
	hal_sgpio_stubs.hal_sgpio_set_rxdata_prebuf_bit_shift_int(psgpio_adp, psgpio_set_irq);
}

/**
 *  @brief  Reset the rxdata.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *
 *  @returns void
 */
void hal_sgpio_reset_rxdata(hal_sgpio_adapter_t *psgpio_adp)
{
	hal_sgpio_stubs.hal_sgpio_reset_rxdata(psgpio_adp);
}

/**
 *  @brief  Set the control and interrupt for the rxdata match event.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  rxdata_match_en Enable or Disable to the rxdata match function.
 *  @param[in]  match_value Set the match value of rxdata.
 *  @param[in]  psgpio_set_irq The parameter structure is for initializing the interrupt event.
 *                      int_en - 0: disbale this event interrupt, 1: enable.
 *                      imr_en - 0: disbale mask event interrupt, 1: enable.
 *                      callback_reg_en - 0: don't register this callback function, 1: register this callback function.
 *                      callback - The callback function.
 *                      arg - The callback argument.
 *
 *  @returns void
 */
void hal_sgpio_set_rxdata_match_int(hal_sgpio_adapter_t *psgpio_adp, BOOL rxdata_match_en, u32 match_value, hal_sgpio_set_irq_t *psgpio_set_irq)
{
	hal_sgpio_stubs.hal_sgpio_set_rxdata_match_int(psgpio_adp, rxdata_match_en, match_value, psgpio_set_irq);
}

/**
 *  @brief  Set the txdata output length and interrupt. When reach the length to be sent, generate the interrupt.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  bit_length The output bit length.
 *  @param[in]  psgpio_set_irq The parameter structure is for initializing the interrupt event.
 *                      int_en - 0: disbale this event interrupt, 1: enable.
 *                      imr_en - 0: disbale mask event interrupt, 1: enable.
 *                      callback_reg_en - 0: don't register this callback function, 1: register this callback function.
 *                      callback - The callback function.
 *                      arg - The callback argument.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_sgpio_set_txdata_bit_length_int(hal_sgpio_adapter_t *psgpio_adp, u8 bit_length, hal_sgpio_set_irq_t *psgpio_set_irq)
{
	return hal_sgpio_stubs.hal_sgpio_set_txdata_bit_length_int(psgpio_adp, bit_length, psgpio_set_irq);
}

/**
 *  @brief  Control the interrupt when happen the bit shift of txdata.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  psgpio_set_irq The parameter structure is for initializing the interrupt event.
 *                      int_en - 0: disbale this event interrupt, 1: enable.
 *                      imr_en - 0: disbale mask event interrupt, 1: enable.
 *                      callback_reg_en - 0: don't register this callback function, 1: register this callback function.
 *                      callback - The callback function.
 *                      arg - The callback argument.
 *
 *  @returns void
 */
void hal_sgpio_set_txdata_prebuf_bit_shift_int(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_set_irq_t *psgpio_set_irq)
{
	hal_sgpio_stubs.hal_sgpio_set_txdata_prebuf_bit_shift_int(psgpio_adp, psgpio_set_irq);
}

/**
 *  @brief  Reset the txdata.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *
 *  @returns void
 */
void hal_sgpio_reset_txdata(hal_sgpio_adapter_t *psgpio_adp)
{
	hal_sgpio_stubs.hal_sgpio_reset_txdata(psgpio_adp);
}

/**
 *  @brief  Get the rxtc match value of the count unit. Change the unit from time to count.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  time_unit Select the time unit us or ns.
 *  @param[in]  time_value The time value.
 *
 *  @returns The rxtc match value.
 */
u32 hal_sgpio_set_time_to_rxtc(hal_sgpio_adapter_t *psgpio_adp, sgpio_time_unit_t time_unit, u32 time_value)
{
	return hal_sgpio_stubs.hal_sgpio_set_time_to_rxtc(psgpio_adp, time_unit, time_value);
}

/**
 *  @brief  Get the multc match value of the count unit. Change the unit from time to count.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  time_unit Select the time unit us or ns.
 *  @param[in]  time_value The time value.
 *
 *  @returns The multc match value.
 */
u32 hal_sgpio_set_time_to_multc(hal_sgpio_adapter_t *psgpio_adp, sgpio_time_unit_t time_unit, u32 time_value)
{
	return hal_sgpio_stubs.hal_sgpio_set_time_to_multc(psgpio_adp, time_unit, time_value);
}

/**
 *  @brief  Get the rxtc match value of the time unit. Change the unit from count to time.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  rxtc_unit The count value.
 *  @param[in]  time_unit Select the time unit us or ns.
 *
 *  @returns The rxtc match value.
 */
u32 hal_sgpio_set_rxtc_to_time(hal_sgpio_adapter_t *psgpio_adp, u16 rxtc_unit, sgpio_time_unit_t time_unit)
{
	return hal_sgpio_stubs.hal_sgpio_set_rxtc_to_time(psgpio_adp, rxtc_unit, time_unit);
}

/**
 *  @brief  Get the multc match value of the time unit. Change the unit from count to time.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  multc_unit The count value.
 *  @param[in]  time_unit Select the time unit us or ns.
 *
 *  @returns The multc match value.
 */
u32 hal_sgpio_set_multc_to_time(hal_sgpio_adapter_t *psgpio_adp, u16 multc_unit, sgpio_time_unit_t time_unit)
{
	return hal_sgpio_stubs.hal_sgpio_set_multc_to_time(psgpio_adp, multc_unit, time_unit);
}

/**
 *  @brief  Clean the SGPIO interrupt status.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  sgpio_is The interrupt event.
 *
 *  @returns void
 */
void hal_sgpio_clean_status(hal_sgpio_adapter_t *psgpio_adp, u32 sgpio_is)
{
	hal_sgpio_stubs.hal_sgpio_clean_status(psgpio_adp, sgpio_is);
}

/**
 *  @brief  Upate the rxtc match value because the prescaler value is changed.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  match_event Select the rxtc match event.
 *  @param[in]  old_prescale The old prescaler value.
 *
 *  @returns void
 */
void hal_sgpio_update_rxtcmr(hal_sgpio_adapter_t *psgpio_adp, sgpio_rxtc_match_event_t match_event, u16 old_prescale)
{
	hal_sgpio_stubs.hal_sgpio_update_rxtcmr(psgpio_adp, match_event, old_prescale);
}

/**
 *  @brief  Upate the multc match value because the prescaler value is changed.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  match_group Select the multc match group.
 *  @param[in]  match_event Select the multc match event.
 *  @param[in]  old_prescale The old prescaler value.
 *
 *  @returns void
 */
void hal_sgpio_update_multcmr(hal_sgpio_adapter_t *psgpio_adp, sgpio_multc_match_group_t match_group, sgpio_multc_match_event_t match_event, u16 old_prescale)
{
	hal_sgpio_stubs.hal_sgpio_update_multcmr(psgpio_adp, match_group, match_event, old_prescale);
}

/**
 *  @brief Configure SGPIO to become the rxtc timer.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  psgpio_rxtc_timer_mode The parameter structure is for initializing the rxtc timer mode.
 *                      timer_once_en - Enable that matching event is executed once.
 *                      time_unit - Select the time unit.
 *                      match_time1 - Matching this time 1 generates the interrupt.
 *                      match_time1_cb - User defined IRQ callback function. Using "NULL" will not generate this interrupt.
 *                      pmatch_time1_arg - User defined IRQ callback parameter.
 *                      match_time2 - Matching this time 2 generates the interrupt.
 *                      match_time2_cb - User defined IRQ callback function. Using "NULL" will not generate this interrupt.
 *                      pmatch_time2_arg - User defined IRQ callback parameter.
 *                      match_time_reset - This match time is able to make the timer reset and stop.
 *                      time_reset_cb - User defined IRQ callback function. Using "NULL" will not generate this interrupt.
 *                      ptime_reset_arg - User defined IRQ callback parameter.
 *
 *  @returns void
 */
void hal_sgpio_rxtc_timer_mode(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_timer_mode_t *psgpio_rxtc_timer_mode)
{
	hal_sgpio_stubs.hal_sgpio_rxtc_timer_mode(psgpio_adp, psgpio_rxtc_timer_mode);
}

/**
 *  @brief Configure SGPIO to become the multc timer.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  psgpio_multc_timer_mode The parameter structure is for initializing the multc timer mode.
 *                      timer_once_en - Enable that matching event is executed once.
 *                      time_unit - Select the time unit.
 *                      match_time_reset - This match time is able to make the timer reset and stop.
 *                      time_reset_cb - User defined IRQ callback function. Using "NULL" will not generate this interrupt.
 *                      ptime_reset_arg - User defined IRQ callback parameter.
 *
 *  @returns void
 */
void hal_sgpio_multc_timer_mode(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_multc_timer_mode_t *psgpio_multc_timer_mode)
{
	hal_sgpio_stubs.hal_sgpio_multc_timer_mode(psgpio_adp, psgpio_multc_timer_mode);
}

/**
 *  @brief Configure SGPIO to count input triggers.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  psgpio_multc_counter_mode The parameter structure is for initializing the multc counter mode.
 *                      counter_en - To enable or disable.
 *                      input_edge - Select the edge of the trigger event.
 *                      match_value - When the counter value is equal to match_value, generate an interrupt.
 *                      match_cb - User defined IRQ callback function. Using "NULL" will not generate this interrupt.
 *                      pmatch_arg - User defined IRQ callback parameter.
 *                      match_reset_en - When the counter value is equal to match_value, reset the counter.
 *                      match_disable_en - When the counter value is equal to match_value, make counter_en become disable(0).
 *                      timeout_unit -Select the time unit.
 *                      counter_reset_timeout -Set the monitor period.
 *
 *  @returns void
 */
void hal_sgpio_multc_counter_mode(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_multc_counter_mode_t *psgpio_multc_counter_mode)
{
	hal_sgpio_stubs.hal_sgpio_multc_counter_mode(psgpio_adp, psgpio_multc_counter_mode);
}

/**
 *  @brief Generate the external output when happen the match events of the rxtc timer.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  psgpio_rxtc_timer_match_output The parameter structure is for initializing the rxtc timer match output.
 *                      match_time1_output - Set the output value when match the time 1.
 *                      match_time2_output - Set the output value when match the time 2.
 *                      match_reset_time_output - Set the output value when match the reset time.
 *
 *  @returns void
 */
void hal_sgpio_rxtc_timer_match_output(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_timer_match_output_t *psgpio_rxtc_timer_match_output)
{
	hal_sgpio_stubs.hal_sgpio_rxtc_timer_match_output(psgpio_adp, psgpio_rxtc_timer_match_output);
}

/**
 *  @brief Generate the external output when happen the match events of the multc timer counter.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  psgpio_multc_timer_counter_match_output The parameter structure is for initializing the multc timer match output.
 *                      source_unit - Select the time unit.
 *                      match_value1_output - Set the output value when happen the multc match event 1.
 *                      match_value1 - The match value 1 of the multc timer counter.
 *                      match_value2_output - Set the output value when happen the multc match event 2.
 *                      match_value2 - The match value 2 of the multc timer counter.
 *                      match_value3_output - Set the output value when happen the multc match event 3.
 *                      match_value3 - The match value 3 of the multc timer counter.
 *
 *  @returns void
 */
void hal_sgpio_multc_timer_counter_match_output(hal_sgpio_adapter_t *psgpio_adp,
		hal_sgpio_multc_timer_counter_match_output_t *psgpio_multc_timer_counter_match_output)
{
	hal_sgpio_stubs.hal_sgpio_multc_timer_counter_match_output(psgpio_adp, psgpio_multc_timer_counter_match_output);
}

/**
 *  @brief Configure SGPIO to become the capture mode for measuring the pulse width.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  psgpio_rxtc_capture_mode The parameter structure is for initializing the rxtc capture mode.
 *                      capture_en - To enable or disable.
 *                      start_timer_edge - Select the trigger edge for starting the rxtc timer.
 *                      input_capture_edge - Select the capture edge for capturing the time.
 *                      capture_timer_reset_en - When happen the capture event, reset the rxtc timer.
 *                      capture_timer_disable_en - When happen the capture event, stop the rxtc timer.
 *                      max_capture_range_us - Set the maximum possible measurement value for making the prescale of the timer automatically.
 *                      capture_cb - User defined IRQ callback function. Using "NULL" will not generate this interrupt.
 *                      pcapture_arg - User defined IRQ callback parameter.
 *
 *  @returns void
 */
void hal_sgpio_rxtc_capture_mode(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_capture_mode_t *psgpio_rxtc_capture_mode)
{
	hal_sgpio_stubs.hal_sgpio_rxtc_capture_mode(psgpio_adp, psgpio_rxtc_capture_mode);
}

/**
 *  @brief Make the capture timer reset and stop in the capture mode when the timer value is equal to timeout_value.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  psgpio_rxtc_capture_mode The parameter structure is for initializing the rxtc capture timeout.
 *                      capture_timeout_en - To enable or disable.
 *                      capture_timer_reset_en - Reset the capture timer when the timer value is equal to timeout_value.
 *                      capture_timer_disable_en - Stop the capture timer when the timer value is equal to timeout_value.
 *                      time_unit - Select the time unit.
 *                      timeout_value - Matching this timeout value generates the interrupt.
 *                      capture_timeout_cb - User defined IRQ callback function. Using "NULL" will not generate this interrupt.
 *                      pcapture_timeout_arg - User defined IRQ callback parameter.
 *
 *  @returns void
 */
void hal_sgpio_rxtc_capture_timeout(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_capture_timeout_t *psgpio_rxtc_capture_timeout)
{
	hal_sgpio_stubs.hal_sgpio_rxtc_capture_timeout(psgpio_adp, psgpio_rxtc_capture_timeout);
}

/**
 *  @brief Monitor the capture value. When the capture value is bigger than monitor time, generate the interrupt.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  psgpio_rxtc_capture_monitor The parameter structure is for initializing the rxtc capture monitor.
 *                      capture_monitor_en - To enable or disable.
 *                      time_unit - Select the time unit.
 *                      monitor_time - The monitor value.
 *                      monitor_count - Set the continuous numbers of the successful condition. Value: 1 ~ 32, 0: do nothing.
 *                      capture_monitor_cb - User defined IRQ callback function. Using "NULL" will not generate this interrupt.
 *                      pcapture_monitor_arg - User defined IRQ callback parameter.
 *
 *  @returns void
 */
void hal_sgpio_rxtc_capture_monitor(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_capture_monitor_t *psgpio_rxtc_capture_monitor)
{
	hal_sgpio_stubs.hal_sgpio_rxtc_capture_monitor(psgpio_adp, psgpio_rxtc_capture_monitor);
}

/**
 *  @brief Get the capture value.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  time_unit Select the time unit.
 *
 *  @returns The capture value.
 */
u32 hal_sgpio_get_rxtc_capture_time(hal_sgpio_adapter_t *psgpio_adp, sgpio_time_unit_t time_unit)
{
	u32 ns_unit;

	ns_unit = (u32)psgpio_adp->base_addr->capr_b.capr;

	if (ns_unit != 0x00) {
		ns_unit = (ns_unit + 1) * (u32)(psgpio_adp->base_addr->rxprval_b.rxprval + 1);
		ns_unit = (u32)((float)ns_unit * psgpio_adp->sgpio_sclk_ns);
	}

	if (time_unit == Time_unit_us) {
		ns_unit = ns_unit / 1000;
	}

	return ns_unit;

	//return hal_sgpio_stubs.hal_sgpio_get_rxtc_capture_time (psgpio_adp, time_unit);
}

/**
 *  @brief  Initialize that the rxdata source is the capture compare result.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  cmp_result_bit Set that the rxdata register receives value 0 or 1 when the capture value is bigger than cap_cmpval.
 *  @param[in]  time_unit Select the time unit.
 *  @param[in]  cap_cmpval_time The compare value. This unit is time.
 *
 *  @returns void
 */
void hal_sgpio_init_rxdata_capture_compare_time(hal_sgpio_adapter_t *psgpio_adp, sgpio_cmp_result_bit_t cmp_result_bit, sgpio_time_unit_t time_unit,
		u32 cap_cmpval_time)
{
	hal_sgpio_stubs.hal_sgpio_init_rxdata_capture_compare_time(psgpio_adp, cmp_result_bit, time_unit, cap_cmpval_time);
}

/**
 *  @brief Set the trigger edge to start the timer, and sample the input value according to the sampling time.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  psgpio_sampling_data The parameter structure is for initializing the sampling rxdata.
 *                      sampling_en - To enable or disable.
 *                      start_timer_edge - Select the trigger edge for starting the rxtc timer.
 *                      time_unit - Select the time unit.
 *                      sampling_time1 - The sampling time 1 needs less than the sampling end time. Set to 0 when not in use.
 *                      sampling_time2 - The sampling time 2 needs less than the sampling end time. Set to 0 when not in use.
 *                      sampling_end_time - The sampling end time. Matching this time is to make the timer reset and stop.
 *                      sampling_bit_length - Set the bit length generated the interrupt. Value: 1 ~ 32, 0: do nothing.
 *                      first_msb_or_lsb - Putting in the register is LSB or MSB.
 *                      sampling_finish_cb - User defined IRQ callback function. Using "NULL" will not generate this interrupt.
 *                      psampling_finish_arg - User defined IRQ callback parameter.
 *
 *  @returns void
 */
void hal_sgpio_sampling_rxdata(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_sampling_rxdata_t *psgpio_sampling_data)
{
	hal_sgpio_stubs.hal_sgpio_sampling_rxdata(psgpio_adp, psgpio_sampling_data);
}

/**
 *  @brief Get the register of the rxdata by sample or capture.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *
 *  @returns The result register.
 */
u32 hal_sgpio_get_input_rxdata(hal_sgpio_adapter_t *psgpio_adp)
{
	return hal_sgpio_stubs.hal_sgpio_get_input_rxdata(psgpio_adp);
}

/**
 *  @brief Get the mask and arrange rxdata.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  rxdata_tp The rxdata value.
 *
 *  @returns The rxdata result.
 */
u32 hal_sgpio_get_arrange_rxdata(hal_sgpio_adapter_t *psgpio_adp, u32 rxdata_tp)
{
	return hal_sgpio_stubs.hal_sgpio_get_arrange_rxdata(psgpio_adp, rxdata_tp);
}

/**
 *  @brief Set the trigger edge to start the timer, and translate the capture time into "0" or "1" according to the result of the comparison.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  psgpio_compare_data The parameter structure is for initializing the capture compare rxdata.
 *                      sampling_en - To enable or disable.
 *                      capture_en - Select the trigger edge for starting the rxtc timer.
 *                      input_capture_edge - Select the capture edge for capturing the time.
 *                      max_capture_range_us - Set the maximum possible measurement value for making the prescale of the timer automatically.
 *                      time_unit - Select the time unit.
 *                      capture_compare_value_time - Set the compare time.
 *                      compare_result_bit - Deciding the value of the result bit is "0" or "1".
 *                      compare_bit_length - Set the bit length generated the interrupt. Value: 1 ~ 32, 0: do nothing.
 *                      first_msb_or_lsb - Putting in the register is LSB or MSB.
 *                      sampling_finish_cb - User defined IRQ callback function. Using "NULL" will not generate this interrupt.
 *                      psampling_finish_arg - User defined IRQ callback parameter.
 *
 *  @returns void
 */
void hal_sgpio_capture_compare_rxdata(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_capture_compare_rxdata_t *psgpio_compare_data)
{
	hal_sgpio_stubs.hal_sgpio_capture_compare_rxdata(psgpio_adp, psgpio_compare_data);
}

/**
 *  @brief Configure the waveforms of the bit 0 and bit 1 for the output.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  psgpio_txdata_bit_symbol The parameter structure is for initializing the txdata bit symbol.
 *                      initial_output_value - Set the initial output value.
 *                      time_unit - Select the time unit.
 *                      bit0_middle_change_time - The time is to change the output value for the bit 0.
 *                      bit0_duration_time - The duration of the bit 0.
 *                      bit1_middle_change_time - The time is to change the output value for the bit 1.
 *                      bit1_duration_time - The duration of the bit 1.
 *
 *  @returns void
 */
void hal_sgpio_txdata_bit_symbol(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_txdata_bit_symbol_t *psgpio_txdata_bit_symbol)
{
	hal_sgpio_stubs.hal_sgpio_txdata_bit_symbol(psgpio_adp, psgpio_txdata_bit_symbol);
}

/**
 *  @brief Set the output data according to the waveforms of the bit 0 and bit 1.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  psgpio_txdata The parameter structure is for initializing the txdata.
 *                      txdata_en - To enable or disable.
 *                      rx_output_en - Control the output behavior of the bidirectional Rx.
 *                      output_bit_counts - Set the output bit number.
 *                      ptxdata_pointer - Set the output data pointer.
 *                      txdata_finish_cb - When finish the TX output, generate the interrupt.
 *                      ptxdata_finish_arg - User defined IRQ callback parameter.
 *
 *  @returns void
 */
void hal_sgpio_txdata(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_txdata_t *psgpio_txdata)
{
	hal_sgpio_stubs.hal_sgpio_txdata(psgpio_adp, psgpio_txdata);
}

/**
 *  @brief Process txdata in the interrupt handler
 *
 *  @param[in]  data Set the SGPIO adapter.
 *
 *  @returns void
 */
void hal_sgpio_txdata_bit_length_irq(void *data)
{
	hal_sgpio_stubs.hal_sgpio_txdata_bit_length_irq(data);
}

/**
 *  @brief Start to output the TX data.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *
 *  @returns void
 */
void hal_sgpio_send_txdata(hal_sgpio_adapter_t *psgpio_adp)
{
	hal_sgpio_stubs.hal_sgpio_send_txdata(psgpio_adp);
}

/**
 *  @brief Reset the register of the RX data.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *
 *  @returns void
 */
void hal_sgpio_reset_receive_rxdata(hal_sgpio_adapter_t *psgpio_adp)
{
	hal_sgpio_stubs.hal_sgpio_reset_receive_rxdata(psgpio_adp);
}

/**
 *  @brief Disable the monitor mode.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *
 *  @returns void
 */
void hal_sgpio_disable_rxdata_match(hal_sgpio_adapter_t *psgpio_adp)
{
	hal_sgpio_stubs.hal_sgpio_disable_rxdata_match(psgpio_adp);
}

/**
 *  @brief Monitor the register of the sample or capture data. When the register value is equal to the monitor data, generate the interrupt.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  pmonitor_rxdata The parameter structure is for initializing the monitor rxdata.
 *                      monitor_en - To enable or disable.
 *                      monitor_data - Set the monitor data.
 *                      monitor_input_data_mask - Set the bit mask of the monitor data.
 *                      monitor_rxdata_cb -User defined IRQ callback function. Using "NULL" will not generate this interrupt.
 *                      pmonitor_rxdata_arg - User defined IRQ callback parameter.
 *
 *  @returns void
 */
void hal_sgpio_monitor_rxdata(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_monitor_rxdata_t *pmonitor_rxdata)
{
	hal_sgpio_stubs.hal_sgpio_monitor_rxdata(psgpio_adp, pmonitor_rxdata);
}

/**
 *  @brief Reset the multc FIFO.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *
 *  @returns void
 */
void hal_sgpio_multc_fifo_reset(hal_sgpio_adapter_t *psgpio_adp)
{
	hal_sgpio_stubs.hal_sgpio_multc_fifo_reset(psgpio_adp);
}

/**
 *  @brief Set the interrupt handler for the dma match output
 *
 *  @param[in]  data Set the SGPIO adapter.
 *
 *  @returns void
 */
void hal_sgpio_dma_match_output_irq_handle(void *data)
{
	hal_sgpio_stubs.hal_sgpio_dma_match_output_irq_handle(data);
}

/**
 *  @brief Init GDMA for the dma match output
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  pgdma_adaptor The GDMA adapter.
 *  @param[in]  pdma_match_output The parameter structure is for initializing the SGPIO dma output.
 *                      match_value1_output - Set the output value when match value 1.
 *                      match_value2_output - Set the output value when match value 2.
 *                      match_value3_output - Set the output value when match value 3.
 *                      pmatch_value_ptr -The pointer is the memory address of setting the match time.
 *                      match_reset_counter - Set the number of reset times. An interrupt will be generated when the number of times is reached.
 *                      counter_finish_cb -User defined IRQ callback function. Using "NULL" will not generate this interrupt.
 *                      pcounter_finish_arg - User defined IRQ callback parameter.
 *
 *  @returns Always return HAL_OK
 */
HAL_Status hal_sgpio_dma_match_output_init(hal_sgpio_adapter_t *psgpio_adp, hal_gdma_adaptor_t *pgdma_adaptor, hal_sgpio_dma_match_output_t *pdma_match_output)
{
	hal_status_t ret;

	ret = hal_gdma_chnl_alloc(pgdma_adaptor, MultiBlkDis);     // default no-multiple block support

	if (ret == HAL_OK) {
		ret = hal_sgpio_stubs.hal_sgpio_dma_match_output_init(psgpio_adp, pgdma_adaptor, pdma_match_output);
		if (ret == HAL_OK) {
			hal_gdma_chnl_init(pgdma_adaptor);
		} else {
			dbg_printf("hal_sgpio_dma_match_output_init: GDMA init failed(%d)\r\n", ret);
			hal_gdma_chnl_free(pgdma_adaptor);
		}
	} else {
		dbg_printf("hal_sgpio_dma_match_output_init: GDMA channel allocate failed(%d)\r\n", ret);
	}

	return ret;

}

/**
 *  @brief De-initialize GDMA for the dma match output
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *
 *  @returns Always return HAL_OK
 */
HAL_Status hal_sgpio_dma_match_output_deinit(hal_sgpio_adapter_t *psgpio_adp)
{
	hal_gdma_chnl_free(psgpio_adp->phal_gdma_adaptor);
	return hal_sgpio_stubs.hal_sgpio_dma_match_output_deinit(psgpio_adp);
}

/**
 *  @brief Init the handshake for SGPIO and GDMA.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  pdma_match_output The parameter structure is for initializing the SGPIO dma output.
 *                      match_value1_output - Set the output value when match value 1.
 *                      match_value2_output - Set the output value when match value 2.
 *                      match_value3_output - Set the output value when match value 3.
 *                      pmatch_value_ptr -The pointer is the memory address of setting the match time.
 *                      match_reset_counter - Set the number of reset times. An interrupt will be generated when the number of times is reached.
 *                      counter_finish_cb -User defined IRQ callback function. Using "NULL" will not generate this interrupt.
 *                      pcounter_finish_arg - User defined IRQ callback parameter.
 *
 *  @returns void
 */
void hal_sgpio_dma_handshake_init(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_dma_match_output_t *pdma_match_output)
{
	hal_sgpio_stubs.hal_sgpio_dma_handshake_init(psgpio_adp, pdma_match_output);
}

/**
 *  @brief Preload the data to the buffer for starting GDMA.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *
 *  @returns void
 */
void hal_sgpio_dma_preload_data(hal_sgpio_adapter_t *psgpio_adp)
{
	hal_sgpio_stubs.hal_sgpio_dma_preload_data(psgpio_adp);
}

/**
 *  @brief Start the GDMA to send the TX waveform.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *
 *  @returns void
 */
void hal_sgpio_dma_send_start(hal_sgpio_adapter_t *psgpio_adp)
{
	hal_sgpio_stubs.hal_sgpio_dma_send_start(psgpio_adp);
}

/**
 *  @brief Change the memory data from the time unit to the count unit.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  pmemory_addr The pointer is the memory address of setting the match time.
 *  @param[in]  reset_cnt Set the number of reset times. An interrupt will be generated when the number of times is reached.
 *  @param[in]  time_unit Select the time unit.
 *
 *  @returns void
 */
void hal_sgpio_dma_time_to_multc(hal_sgpio_adapter_t *psgpio_adp, u16 *pmemory_addr, u8 reset_cnt, sgpio_time_unit_t time_unit)
{
	hal_sgpio_stubs.hal_sgpio_dma_time_to_multc(psgpio_adp, pmemory_addr, reset_cnt, time_unit);
}

/**
 *  @brief Reset all control registers of rxtc.
 *
 *  @returns void
 */
void hal_sgpio_reset_rxtc_ctrl(hal_sgpio_adapter_t *psgpio_adp)
{
	psgpio_adp->base_addr->rxtmr_ctrl_b.rxtmr_cen = 0;
	psgpio_adp->base_addr->rxtmr_ctrl_b.rxtmredge_sel = 0;
	psgpio_adp->base_addr->rxtmr_ctrl_b.rxtmr_crst = 1;
	psgpio_adp->base_addr->rxprval_b.rxprval = 0;
	psgpio_adp->base_addr->rxmc = 0x00;
	psgpio_adp->base_addr->rxmr0 = 0x00;
	psgpio_adp->base_addr->rxmr1 = 0x00;
	psgpio_adp->base_addr->rxmr2 = 0x00;
	psgpio_adp->base_addr->cap_ctrl = 0x00;
}

/**
 *  @brief Reset all control registers of rxtc.
 *
 *  @returns void
 */
void hal_sgpio_reset_multc_ctrl(hal_sgpio_adapter_t *psgpio_adp)
{
	psgpio_adp->base_addr->multmr_ctrl_b.multmr_cen = 0;
	psgpio_adp->base_addr->multmr_ctrl_b.multmr_crst = 1;
	psgpio_adp->base_addr->mulprval_b.mulprval = 0;
	psgpio_adp->base_addr->mulmc = 0x00;
	psgpio_adp->base_addr->mulmr01gp0 = 0x00;
	psgpio_adp->base_addr->mulmr23gp0 = 0x00;
	psgpio_adp->base_addr->mulmr01gp1 = 0x00;
	psgpio_adp->base_addr->mulmr23gp1 = 0x00;
}

/**
 *  @brief Reset external match registers of rxtc.
 *
 *  @returns void
 */
void hal_sgpio_reset_rxtc_ext_match(hal_sgpio_adapter_t *psgpio_adp)
{
	psgpio_adp->base_addr->mulemr = psgpio_adp->base_addr->mulemr & 0xFFFFF03F;
}

/**
 *  @brief Reset external match registers of multc.
 *
 *  @returns void
 */
void hal_sgpio_reset_multc_ext_match(hal_sgpio_adapter_t *psgpio_adp)
{
	psgpio_adp->base_addr->mulemr = psgpio_adp->base_addr->mulemr & 0xFFFFFFC0;
}

/** @} */ /* End of group hs_hal_sgpio */

#endif

