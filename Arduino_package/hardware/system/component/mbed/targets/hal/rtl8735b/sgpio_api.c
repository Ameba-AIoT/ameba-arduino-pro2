
/**************************************************************************//**
 * @file     sgpio_api.c
 * @brief    This file implements the SGPIO Mbed HAL API functions.
 *
 * @version  V1.00
 * @date     2017-05-03
 *
 * @note
 *
 ******************************************************************************
 * @attention
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
 ******************************************************************************
 */
#include "objects.h"
#include "sgpio_api.h"
#include "hal_sgpio.h"

void sgpio_init(sgpio_t *obj, PinName tx, PinName bi_dir_rx)
{
	hal_sgpio_adapter_t *psgpio_adapter = &obj->sgpio_adapter;
	HAL_Status ret;
#if IS_CUT_TEST(CONFIG_CHIP_VER)
	uint32_t sgpio_s0[3] = {PF_15, PF_1, PF_14};
#else
	uint32_t sgpio_s0[3] = {PF_15, PF_9, PF_14};
#endif
	u8 ip_en = 0;

	if (tx == sgpio_s0[0]) {
		ret = hal_pinmux_register(sgpio_s0[0], PID_SGPIO);
		if (ret != HAL_OK) {
			DBG_SGPIO_ERR("sgpio_init : PIN_F15 is invalid. \r\n");
		} else {
			ip_en |= 1;
		}
	}

	if (bi_dir_rx == sgpio_s0[1]) {
		ret = hal_pinmux_register(sgpio_s0[1], PID_SGPIO);
		if (ret != HAL_OK) {
			DBG_SGPIO_ERR("sgpio_init : PIN_F1 is invalid. \r\n");
		} else {
			ip_en |= 1;
		}
	} else if (bi_dir_rx == sgpio_s0[2]) {
		ret = hal_pinmux_register(sgpio_s0[2], PID_SGPIO);
		if (ret != HAL_OK) {
			DBG_SGPIO_ERR("sgpio_init : PIN_F14 is invalid. \r\n");
		} else {
			ip_en |= 1;
		}
	}

	if (ip_en == 1) {
		psgpio_adapter->sgpio_index = Sgpio0_Sel;
		hal_sgpio_init(psgpio_adapter, psgpio_adapter->sgpio_index);
		psgpio_adapter->dcache_memory_en = 1;
		psgpio_adapter->sgpio_sclk_ns = 10.0f; //ASIC
	} else {
		DBG_SGPIO_ERR("sgpio_init : SGPIO pins are invalid \r\n");
	}

}

void sgpio_rxtc_timer_mode(sgpio_t *obj, BOOL timer_once_en, sgpio_time_unit time_unit,
						   u32 match_time1, sgpio_irq_handler match_time1_cb, void *pmatch_time1_arg,
						   u32 match_time2, sgpio_irq_handler match_time2_cb, void *pmatch_time2_arg,
						   u32 match_time_reset, sgpio_irq_handler time_reset_cb, void *ptime_reset_arg)
{
	hal_sgpio_adapter_t *psgpio_adapter = &obj->sgpio_adapter;
	hal_sgpio_rxtc_timer_mode_t rxtc_timer_mode;

	hal_sgpio_reset_rxtc_ctrl(psgpio_adapter);

	rxtc_timer_mode.timer_once_en = timer_once_en;
	rxtc_timer_mode.time_unit = time_unit;

	rxtc_timer_mode.match_value1_time = match_time1;
	rxtc_timer_mode.match_value1_cb = match_time1_cb;
	rxtc_timer_mode.pmatch_value1_arg = pmatch_time1_arg;

	rxtc_timer_mode.match_value2_time = match_time2;
	rxtc_timer_mode.match_value2_cb = match_time2_cb;
	rxtc_timer_mode.pmatch_value2_arg = pmatch_time2_arg;

	rxtc_timer_mode.match_reset_value_time = match_time_reset;
	rxtc_timer_mode.reset_value_cb = time_reset_cb;
	rxtc_timer_mode.preset_value_arg = ptime_reset_arg;

	hal_sgpio_rxtc_timer_mode(psgpio_adapter, &rxtc_timer_mode);

}

void sgpio_multc_timer_mode(sgpio_t *obj, BOOL timer_once_en, sgpio_time_unit time_unit,
							u32 match_time_reset, sgpio_irq_handler time_reset_cb, void *ptime_reset_arg)
{
	hal_sgpio_adapter_t *psgpio_adapter = &obj->sgpio_adapter;
	hal_sgpio_multc_timer_mode_t multc_timer_mode;

	hal_sgpio_reset_multc_ctrl(psgpio_adapter);

	multc_timer_mode.timer_once_en = timer_once_en;
	multc_timer_mode.time_unit = time_unit;

	multc_timer_mode.match_reset_value_time = match_time_reset;
	multc_timer_mode.reset_value_cb = time_reset_cb;
	multc_timer_mode.preset_value_arg = ptime_reset_arg;

	hal_sgpio_multc_timer_mode(psgpio_adapter, &multc_timer_mode);
}

void sgpio_multc_counter_mode(sgpio_t *obj, BOOL counter_en, sgpio_counter_edge input_edge, u16 match_value,
							  sgpio_irq_handler match_cb, void *pmatch_arg, sgpio_multc_ctrl multc_ctrl,
							  sgpio_time_unit timeout_unit, u32 counter_timeout, sgpio_irq_handler timeout_cb, void *ptimeout_arg)
{
	hal_sgpio_adapter_t *psgpio_adapter = &obj->sgpio_adapter;
	hal_sgpio_multc_counter_mode_t multc_counter;
	hal_sgpio_set_irq_t sgpio_set_irq;

	hal_sgpio_reset_multc_ctrl(psgpio_adapter);

	multc_counter.counter_en = counter_en;
	multc_counter.input_edge = input_edge;
	multc_counter.match_counter_value = match_value;
	multc_counter.match_counter_cb = match_cb;
	multc_counter.pmatch_counter_arg = pmatch_arg;

	multc_counter.match_counter_reset_en = 0;
	multc_counter.match_counter_disable_en = 0;
	if (multc_ctrl == MULTC_RESET) {
		multc_counter.match_counter_reset_en = 1;
	} else if (multc_ctrl == MULTC_STOP) {
		multc_counter.match_counter_disable_en = 1;
	} else if (multc_ctrl == MULTC_RESET_STOP) {
		multc_counter.match_counter_reset_en = 1;
		multc_counter.match_counter_disable_en = 1;
	}

	multc_counter.time_unit = timeout_unit;
	multc_counter.counter_reset_timeout_value = counter_timeout;

	hal_sgpio_multc_counter_mode(psgpio_adapter, &multc_counter);

	sgpio_set_irq.imr_en = 0;
	if ((counter_timeout != 0x00) && (timeout_cb != NULL)) {
		sgpio_set_irq.int_en = 1;
		sgpio_set_irq.callback_reg_en = 1;
		sgpio_set_irq.callback = timeout_cb;
		sgpio_set_irq.arg = ptimeout_arg;
	} else {
		sgpio_set_irq.int_en = 0;
		sgpio_set_irq.callback_reg_en = 0;
	}
	hal_sgpio_set_rxtc_int(psgpio_adapter, Rxtc_MatchEvent0, &sgpio_set_irq);

}

void sgpio_rxtc_timer_match_output(sgpio_t *obj, sgpio_external_output match_time1_output, sgpio_external_output match_time2_output,
								   sgpio_external_output match_reset_time_output)
{
	hal_sgpio_adapter_t *psgpio_adapter = &obj->sgpio_adapter;
	hal_sgpio_rxtc_timer_match_output_t rxtc_match_output;

	hal_sgpio_reset_rxtc_ext_match(psgpio_adapter);

	rxtc_match_output.match_value1_output = match_time1_output;
	rxtc_match_output.match_value2_output = match_time2_output;
	rxtc_match_output.match_reset_value_output = match_reset_time_output;

	hal_sgpio_rxtc_timer_match_output(psgpio_adapter, &rxtc_match_output);
}

void sgpio_multc_timer_counter_match_output(sgpio_t *obj, sgpio_source_unit source_unit,
		sgpio_external_output match_value1_output, u32 match_value1,
		sgpio_external_output match_value2_output, u32 match_value2,
		sgpio_external_output match_value3_output, u32 match_value3)
{
	hal_sgpio_adapter_t *psgpio_adapter = &obj->sgpio_adapter;
	hal_sgpio_multc_timer_counter_match_output_t multc_timer_counter_match_output;

	hal_sgpio_reset_multc_ext_match(psgpio_adapter);

	multc_timer_counter_match_output.source_unit = source_unit;
	multc_timer_counter_match_output.match_value1_output = match_value1_output;
	multc_timer_counter_match_output.match_value1 = match_value1;
	multc_timer_counter_match_output.match_value2_output = match_value2_output;
	multc_timer_counter_match_output.match_value2 = match_value2;
	multc_timer_counter_match_output.match_value3_output = match_value3_output;
	multc_timer_counter_match_output.match_value3 = match_value3;

	hal_sgpio_multc_timer_counter_match_output(psgpio_adapter, &multc_timer_counter_match_output);
}

void sgpio_rxtc_capture_mode(sgpio_t *obj, BOOL capture_en, sgpio_rxtc_input_start start_timer_edge, sgpio_capture_type input_capture_edge,
							 sgpio_rxtc_ctrl rxtc_ctrl, u32 max_capture_range_us, sgpio_irq_handler capture_cb, void *pcapture_arg)
{
	hal_sgpio_adapter_t *psgpio_adapter = &obj->sgpio_adapter;
	hal_sgpio_rxtc_capture_mode_t rxtc_capture_mode;

	hal_sgpio_reset_rxtc_ctrl(psgpio_adapter);

	rxtc_capture_mode.capture_en = capture_en;
	rxtc_capture_mode.start_timer_edge = start_timer_edge;
	rxtc_capture_mode.input_capture_edge = input_capture_edge;

	rxtc_capture_mode.capture_timer_reset_en = 0;
	rxtc_capture_mode.capture_timer_disable_en = 0;
	if (rxtc_ctrl == RXTC_RESET) {
		rxtc_capture_mode.capture_timer_reset_en = 1;
	} else if (rxtc_ctrl == RXTC_STOP) {
		rxtc_capture_mode.capture_timer_disable_en = 1;
	} else if (rxtc_ctrl == RXTC_RESET_STOP) {
		rxtc_capture_mode.capture_timer_reset_en = 1;
		rxtc_capture_mode.capture_timer_disable_en = 1;
	}

	rxtc_capture_mode.max_capture_range_us = max_capture_range_us;
	rxtc_capture_mode.capture_cb = capture_cb;
	rxtc_capture_mode.pcapture_arg = pcapture_arg;

	hal_sgpio_rxtc_capture_mode(psgpio_adapter, &rxtc_capture_mode);
}

void sgpio_rxtc_capture_timeout(sgpio_t *obj, BOOL capture_timeout_en, sgpio_rxtc_ctrl rxtc_ctrl,
								sgpio_time_unit time_unit, u32 timeout_value, sgpio_irq_handler capture_timeout_cb, void *pcapture_timeout_arg)
{
	hal_sgpio_adapter_t *psgpio_adapter = &obj->sgpio_adapter;
	hal_sgpio_rxtc_capture_timeout_t rxtc_capture_timeout;

	rxtc_capture_timeout.capture_timeout_en = capture_timeout_en;

	rxtc_capture_timeout.capture_timer_reset_en = 0;
	rxtc_capture_timeout.capture_timer_disable_en = 0;
	if (rxtc_ctrl == RXTC_RESET) {
		rxtc_capture_timeout.capture_timer_reset_en = 1;
	} else if (rxtc_ctrl == RXTC_STOP) {
		rxtc_capture_timeout.capture_timer_disable_en = 1;
	} else if (rxtc_ctrl == RXTC_RESET_STOP) {
		rxtc_capture_timeout.capture_timer_reset_en = 1;
		rxtc_capture_timeout.capture_timer_disable_en = 1;
	}

	rxtc_capture_timeout.time_unit = time_unit;
	rxtc_capture_timeout.timeout_value = timeout_value;
	rxtc_capture_timeout.capture_timeout_cb = capture_timeout_cb;
	rxtc_capture_timeout.pcapture_timeout_arg = pcapture_timeout_arg;

	hal_sgpio_rxtc_capture_timeout(psgpio_adapter, &rxtc_capture_timeout);
}

void sgpio_rxtc_capture_monitor(sgpio_t *obj, BOOL capture_monitor_en, sgpio_time_unit time_unit, u32 monitor_time, u8 monitor_count,
								sgpio_irq_handler capture_monitor_cb, void *pcapture_monitor_arg)
{
	hal_sgpio_adapter_t *psgpio_adapter = &obj->sgpio_adapter;
	hal_sgpio_rxtc_capture_monitor_t rxtc_capture_monitor;

	hal_sgpio_reset_rxdata(psgpio_adapter);

	rxtc_capture_monitor.capture_monitor_en = capture_monitor_en;
	rxtc_capture_monitor.time_unit = time_unit;
	rxtc_capture_monitor.monitor_time = monitor_time;
	rxtc_capture_monitor.monitor_count = monitor_count;
	rxtc_capture_monitor.capture_monitor_cb = capture_monitor_cb;
	rxtc_capture_monitor.pcapture_monitor_arg = pcapture_monitor_arg;

	hal_sgpio_rxtc_capture_monitor(psgpio_adapter, &rxtc_capture_monitor);
}

u32 sgpio_get_rxtc_capture_time(sgpio_t *obj, sgpio_time_unit time_unit)
{
	hal_sgpio_adapter_t *psgpio_adapter = &obj->sgpio_adapter;

	return hal_sgpio_get_rxtc_capture_time(psgpio_adapter, time_unit);
}

void sgpio_sampling_rxdata(sgpio_t *obj, BOOL sampling_en, sgpio_rxtc_input_start start_timer_edge, sgpio_time_unit time_unit,
						   u32 sampling_time1, u32 sampling_time2, u32 sampling_end_time, u8 sampling_bit_length,
						   sgpio_first_msb_or_lsb first_msb_or_lsb, sgpio_irq_handler sampling_finish_cb, void *psampling_finish_arg)
{
	hal_sgpio_adapter_t *psgpio_adapter = &obj->sgpio_adapter;
	hal_sgpio_sampling_rxdata_t sampling_rxdata;
	sgpio_rxtc_input_start start_timer_edge_temp;

	hal_sgpio_reset_rxtc_ctrl(psgpio_adapter);

	if (start_timer_edge == RXTC_ACTIVE) {
		start_timer_edge_temp = RXTC_NO_TRIGGER;
	} else {
		start_timer_edge_temp = start_timer_edge;
	}

	sampling_rxdata.sampling_en = sampling_en;
	sampling_rxdata.start_timer_edge = start_timer_edge_temp;
	sampling_rxdata.time_unit = time_unit;
	sampling_rxdata.sampling_time1_time = sampling_time1;
	sampling_rxdata.sampling_time2_time = sampling_time2;
	sampling_rxdata.sampling_time_end_time = sampling_end_time;
	sampling_rxdata.sampling_bit_length = sampling_bit_length;
	sampling_rxdata.first_msb_or_lsb = first_msb_or_lsb;
	sampling_rxdata.sampling_finish_cb = sampling_finish_cb;
	sampling_rxdata.psampling_finish_arg = psampling_finish_arg;

	hal_sgpio_sampling_rxdata(psgpio_adapter, &sampling_rxdata);

	if ((start_timer_edge == RXTC_ACTIVE) && (sampling_en == ENABLE)) {
		sgpio_rxtc_start_en(obj, ENABLE);
	}

}

void sgpio_capture_compare_rxdata(sgpio_t *obj, BOOL capture_en, sgpio_rxtc_input_start start_timer_edge, sgpio_capture_type input_capture_edge,
								  u32 max_capture_range_us, sgpio_time_unit time_unit, u32 capture_compare_value_time, sgpio_cmp_result_bit compare_result_bit,
								  u8 compare_bit_length, sgpio_first_msb_or_lsb first_msb_or_lsb, sgpio_irq_handler compare_finish_cb, void *pcompare_finish_arg)
{
	hal_sgpio_adapter_t *psgpio_adapter = &obj->sgpio_adapter;
	hal_sgpio_capture_compare_rxdata_t capture_compare_rxdata;

	hal_sgpio_reset_rxtc_ctrl(psgpio_adapter);

	capture_compare_rxdata.capture_en = capture_en;
	capture_compare_rxdata.start_timer_edge = start_timer_edge;
	capture_compare_rxdata.input_capture_edge = input_capture_edge;
	capture_compare_rxdata.max_capture_range_us = max_capture_range_us;
	capture_compare_rxdata.time_unit = time_unit;
	capture_compare_rxdata.capture_compare_value_time = capture_compare_value_time;
	capture_compare_rxdata.compare_result_bit = compare_result_bit;
	capture_compare_rxdata.compare_bit_length = compare_bit_length;
	capture_compare_rxdata.first_msb_or_lsb = first_msb_or_lsb;
	capture_compare_rxdata.compare_finish_cb = compare_finish_cb;
	capture_compare_rxdata.pcompare_finish_arg = pcompare_finish_arg;

	hal_sgpio_capture_compare_rxdata(psgpio_adapter, &capture_compare_rxdata);
}

u32 sgpio_get_input_rxdata(sgpio_t *obj)
{
	hal_sgpio_adapter_t *psgpio_adapter = &obj->sgpio_adapter;

	return hal_sgpio_get_input_rxdata(psgpio_adapter);
}

void sgpio_set_bit_symbol_of_txdata(sgpio_t *obj, sgpio_output_value_t initial_output_value, sgpio_time_unit time_unit,
									u32 bit0_middle_change_time, u32 bit0_duration_time,
									u32 bit1_middle_change_time, u32 bit1_duration_time)
{
	hal_sgpio_adapter_t *psgpio_adapter = &obj->sgpio_adapter;
	hal_sgpio_txdata_bit_symbol_t txdata_bit_symbol;
	u8 error_temp = 0;

	hal_sgpio_reset_multc_ctrl(psgpio_adapter);
	hal_sgpio_reset_multc_ext_match(psgpio_adapter);

	txdata_bit_symbol.initial_output_value = initial_output_value;
	txdata_bit_symbol.time_unit = time_unit;

	if (bit0_duration_time < bit0_middle_change_time) {
		dbg_printf("bit0_duration_time needs bigger than bit0_middle_change_time \r\n");
		error_temp = 1;
	} else {
		txdata_bit_symbol.bit0_middle_change_time = bit0_middle_change_time;
		txdata_bit_symbol.bit0_duration_time = bit0_duration_time;
	}

	if (bit1_duration_time <  bit1_middle_change_time) {
		dbg_printf("bit1_duration_time needs bigger than bit1_middle_change_time \r\n");
		error_temp = 1;
	} else {
		txdata_bit_symbol.bit1_middle_change_time = bit1_middle_change_time;
		txdata_bit_symbol.bit1_duration_time = bit1_duration_time;
	}

	if (error_temp == 0x00) {
		hal_sgpio_txdata_bit_symbol(psgpio_adapter, &txdata_bit_symbol);
	}
}

void sgpio_set_txdata(sgpio_t *obj, BOOL txdata_en, BOOL rx_output_en, u16 output_bit_counts, u32 *ptxdata_pointer,
					  sgpio_irq_handler txdata_finish_cb, void *ptxdata_finish_arg)
{
	hal_sgpio_adapter_t *psgpio_adapter = &obj->sgpio_adapter;
	hal_sgpio_txdata_t sgpio_txdata;

	sgpio_txdata.txdata_en = txdata_en;
	sgpio_txdata.rx_direction_output_en = rx_output_en;
	sgpio_txdata.output_bit_counts = output_bit_counts;
	sgpio_txdata.ptxdata_pointer = ptxdata_pointer;
	sgpio_txdata.txdata_finish_cb = txdata_finish_cb;
	sgpio_txdata.ptxdata_finish_arg = ptxdata_finish_arg;

	hal_sgpio_txdata(psgpio_adapter, &sgpio_txdata);
}

void sgpio_start_send_txdata(sgpio_t *obj)
{
	hal_sgpio_adapter_t *psgpio_adapter = &obj->sgpio_adapter;

	hal_sgpio_send_txdata(psgpio_adapter);
}

void sgpio_disable_rxdata_monitor(sgpio_t *obj)
{
	hal_sgpio_adapter_t *psgpio_adapter = &obj->sgpio_adapter;

	hal_sgpio_disable_rxdata_match(psgpio_adapter);
}

void sgpio_set_rxdata_monitor(sgpio_t *obj, BOOL monitor_en, u32 monitor_data, u32 monitor_input_data_mask,
							  sgpio_irq_handler monitor_rxdata_cb, void *pmonitor_rxdata_arg)
{
	hal_sgpio_adapter_t *psgpio_adapter = &obj->sgpio_adapter;
	hal_sgpio_monitor_rxdata_t monitor_rxdata;

	monitor_rxdata.monitor_en = monitor_en;
	monitor_rxdata.monitor_data = monitor_data;
	monitor_rxdata.monitor_input_data_mask = monitor_input_data_mask;
	monitor_rxdata.monitor_rxdata_cb = monitor_rxdata_cb;
	monitor_rxdata.pmonitor_rxdata_arg = pmonitor_rxdata_arg;
	hal_sgpio_monitor_rxdata(psgpio_adapter, &monitor_rxdata);
}

void sgpio_reset_receive_rxdata(sgpio_t *obj)
{
	hal_sgpio_adapter_t *psgpio_adapter = &obj->sgpio_adapter;

	hal_sgpio_reset_receive_rxdata(psgpio_adapter);
}

void sgpio_init_dma_match_output(sgpio_t *obj, u16 *pmatch_value_ptr, u8 reset_time_num, sgpio_time_unit time_unit,
								 sgpio_external_output match_time1_output, sgpio_external_output match_time2_output, sgpio_external_output match_time3_output,
								 sgpio_irq_handler counter_finish_cb, void *pcounter_finish_arg)
{
	hal_sgpio_adapter_t *psgpio_adapter = &obj->sgpio_adapter;
	hal_sgpio_dma_match_output_t dma_match_output;

	hal_sgpio_reset_multc_ctrl(psgpio_adapter);
	hal_sgpio_reset_multc_ext_match(psgpio_adapter);

	hal_sgpio_dma_time_to_multc(psgpio_adapter, pmatch_value_ptr, reset_time_num, time_unit);

	dma_match_output.match_value1_output = match_time1_output;
	dma_match_output.match_value2_output = match_time2_output;
	dma_match_output.match_value3_output = match_time3_output;
	dma_match_output.pmatch_value_ptr = pmatch_value_ptr;
	dma_match_output.match_reset_counter = reset_time_num;
	dma_match_output.counter_finish_cb = counter_finish_cb;
	dma_match_output.pcounter_finish_arg = pcounter_finish_arg;
	hal_sgpio_dma_match_output_init(psgpio_adapter, &obj->gdma_adaptor, &dma_match_output);
}

void sgpio_deinit_dma_match_output(sgpio_t *obj)
{
	hal_sgpio_adapter_t *psgpio_adapter = &obj->sgpio_adapter;

	hal_sgpio_dma_match_output_deinit(psgpio_adapter);
}

void sgpio_start_dma(sgpio_t *obj)
{
	hal_sgpio_adapter_t *psgpio_adapter = &obj->sgpio_adapter;

	hal_sgpio_dma_send_start(psgpio_adapter);
}

void sgpio_rxtc_start_en(sgpio_t *obj, BOOL start_en)
{
	hal_sgpio_adapter_t *psgpio_adapter = &obj->sgpio_adapter;

	hal_sgpio_set_rxtc_start_en(psgpio_adapter, start_en);
}

void sgpio_multc_start_en(sgpio_t *obj, BOOL start_en)
{
	hal_sgpio_adapter_t *psgpio_adapter = &obj->sgpio_adapter;

	hal_sgpio_set_multc_start_en(psgpio_adapter, start_en);
}

void sgpio_set_output_value(sgpio_t *obj, sgpio_output_value value)
{
	hal_sgpio_adapter_t *psgpio_adapter = &obj->sgpio_adapter;

	hal_sgpio_set_output_value(psgpio_adapter, value);
}

void sgpio_set_inverse_output(sgpio_t *obj)
{
	hal_sgpio_adapter_t *psgpio_adapter = &obj->sgpio_adapter;

	hal_sgpio_set_output_inverse(psgpio_adapter);
}

void sgpio_deinit(sgpio_t *obj)
{
	hal_sgpio_adapter_t *psgpio_adapter = &obj->sgpio_adapter;

	hal_sgpio_deinit(psgpio_adapter);
}

void sgpio_pin_free(sgpio_t *obj)
{
	hal_sgpio_adapter_t *psgpio_adapter = &obj->sgpio_adapter;

	hal_sgpio_pin_free(psgpio_adapter);
}

u16 sgpio_get_rxtc_value(sgpio_t *obj)
{
	hal_sgpio_adapter_t *psgpio_adapter = &obj->sgpio_adapter;

	return hal_sgpio_get_rxtc_value(psgpio_adapter);
}

void sgpio_reset_rxtc(sgpio_t *obj)
{
	hal_sgpio_adapter_t *psgpio_adapter = &obj->sgpio_adapter;

	hal_sgpio_set_rxtc_rst(psgpio_adapter);
}

u16 sgpio_get_multc_value(sgpio_t *obj)
{
	hal_sgpio_adapter_t *psgpio_adapter = &obj->sgpio_adapter;

	return hal_sgpio_get_multc_value(psgpio_adapter);
}

void sgpio_reset_multc(sgpio_t *obj)
{
	hal_sgpio_adapter_t *psgpio_adapter = &obj->sgpio_adapter;

	hal_sgpio_set_multc_rst(psgpio_adapter);
}

void sgpio_reset(sgpio_t *obj)
{
	hal_sgpio_adapter_t *psgpio_adapter = &obj->sgpio_adapter;

	hal_sgpio_reset(psgpio_adapter);
}

void sgpio_set_rx_in_out_ctrl(sgpio_t *obj, sgpio_rx_inoutput rx_in_out)
{
	hal_sgpio_adapter_t *psgpio_adapter = &obj->sgpio_adapter;

	hal_sgpio_set_rx_in_out_ctrl(psgpio_adapter, rx_in_out);
}

