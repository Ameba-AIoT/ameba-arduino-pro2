/**************************************************************************//**
 * @file     i2s_api.c
 * @brief    This file implements the I2S Mbed HAL API functions.
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
//#include "objects.h"
//#include "pinmap.h"
#include "i2s_api.h"
#include "hal_i2s.h"


hal_i2s_def_setting_t i2s_def_setting = {

	.i2s_format = I2S_FORMAT_I2S,
	.i2s_master = I2S_MASTER_MODE,
	.i2s_ch_num = I2S_CH_STEREO,
	.i2s_page_num = I2S_4PAGE,
	.i2s_trx_act = I2S_TXRX,
	.i2s_word_len = I2S_WL_16,
	.i2s_page_size = 1320,
	.i2s_rate = I2S_SR_7p35KHZ,
	.i2s_burst_size = I2S_BURST16,
	.i2s_byte_swap = DISABLE,
	.i2s_sck_inv = ENABLE,
	.i2s_ws_swap = I2S_LEFT_PHASE,
	.i2s_loop_back = DISABLE,
	.i2s_edge_sw = I2S_NEGATIVE_EDGE,

	.i2s_tx_intr_msk = I2S_TX_INT_PAGE0_OK | I2S_TX_INT_PAGE1_OK | \
	I2S_TX_INT_PAGE2_OK | I2S_TX_INT_PAGE3_OK,
	.i2s_rx_intr_msk = I2S_RX_INT_PAGE0_OK | I2S_RX_INT_PAGE1_OK | \
	I2S_RX_INT_PAGE2_OK | I2S_RX_INT_PAGE3_OK
};


extern hal_i2s_def_setting_t i2s_def_setting;

void i2s_sw_reset(i2s_t *obj)
{
	hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;

	hal_i2s_reset(pi2s_adapter);
}

void i2s_init(i2s_t *obj, PinName sck, PinName ws, PinName sd_tx0, PinName sd_rx, PinName mck)
{
	hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;
	HAL_Status ret;
	uint32_t I2S_S0[5] = {PF_13, PF_15, PF_14, PF_12, PF_11};
#if IS_CUT_TEST(CONFIG_CHIP_VER)
	uint32_t I2S_S1[5] = {PE_0, PE_3, PE_1, PE_4, PE_2};
#else
	uint32_t I2S_S1[5] = {PD_14, PD_17, PD_15, PD_18, PD_16};
#endif
	uint32_t pin_id  = 0;
	uint32_t check_temp = 0;
	uint8_t i;

	if ((sck == I2S_S0[0]) && (ws == I2S_S0[1])) {
		pi2s_adapter->dev_num = I2s0_Sel;
		pin_id = PID_I2S0;
	} else if ((sck == I2S_S1[0]) && (ws == I2S_S1[1])) {
		pi2s_adapter->dev_num = I2s1_Sel;
		pin_id = PID_I2S1;
	} else {
		DBG_I2S_ERR("i2s_init : i2s pin is invalid. Need to select sck and ws \r\n");
		obj->i2s_initialized = 0;
		return;
	}

	if (pin_id != 0) {
		for (i = 0; i < 5; i++) {

			if (pin_id == PID_I2S0) {
				ret = hal_pinmux_register(I2S_S0[i], pin_id);
			}

			if (pin_id == PID_I2S1) {
				ret = hal_pinmux_register(I2S_S1[i], pin_id);
			}

			check_temp |= ret;
			if (ret != HAL_OK) {
				DBG_I2S_ERR("i2s_init : i2s pin[%d] is invalid. \r\n", i);
				obj->i2s_initialized = 0;
				return;
			}
		}

		if (check_temp == HAL_OK) {
			ret = hal_i2s_init(pi2s_adapter);
			if (ret != HAL_OK) {
				DBG_I2S_ERR("i2s_init is failure\r\n");
				obj->i2s_initialized = 0;
				return;
			} else {
				pi2s_adapter->dcache_memory_en = 1;
				hal_i2s_set_parameter(pi2s_adapter, &i2s_def_setting);
			}
		} else {
			DBG_I2S_ERR("i2s_init is failure because I2S pins is invalid. \r\n");
			obj->i2s_initialized = 0;
			return;
		}
	}
	obj->i2s_initialized = 1;
}

void i2s_set_dma_buffer(i2s_t *obj, char *tx_buf, char *rx_buf,
						u32 page_num, u32 page_size)
{
	hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;
	u32 i;

	if ((page_num < 2) || (page_num > 4) || (page_size < 8)) {
		dbg_printf("PageNum(%d) valid value is 2~4; PageSize(%d must > 8)\r\n", page_num, page_size);
		return;
	}

	pi2s_adapter->init_dat.i2s_tx_data = (u8 *)tx_buf;
	pi2s_adapter->init_dat.i2s_rx_data = (u8 *)rx_buf;

	hal_i2s_set_dma_buf(pi2s_adapter, (page_size / 4 - 1), page_num);

	for (i = 0; i < page_num; i++) {
		pi2s_adapter->ptx_page_list[i] = (u32 *)(tx_buf + ((page_size) * i));
		pi2s_adapter->prx_page_list[i] = (u32 *)(rx_buf + ((page_size) * i));
	}

}

void i2s_tx_irq_handler(i2s_t *obj, i2s_irq_handler handler, u32 id)
{
	hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;

	pi2s_adapter->user_cb.tx_ccb = handler;
	pi2s_adapter->user_cb.tx_cbid = id;
}

void i2s_rx_irq_handler(i2s_t *obj, i2s_irq_handler handler, u32 id)
{
	hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;

	pi2s_adapter->user_cb.rx_ccb = handler;
	pi2s_adapter->user_cb.rx_cbid = id;
}

void i2s_set_direction(i2s_t *obj, int trx_type)
{
	hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;

	hal_i2s_set_direction(pi2s_adapter, (uint8_t)trx_type);
	if (trx_type == I2S_DIR_TX) {
		hal_i2s_set_loopback(pi2s_adapter, 1);
	} else {
		hal_i2s_set_loopback(pi2s_adapter, 0);
	}
}

uint32_t i2s_get_direction(i2s_t *obj)
{
	hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;

	uint32_t temp_reg = 0;

	temp_reg |= pi2s_adapter->base_addr->ctrl_b.tx_act;

	return temp_reg;
}

void i2s_set_param(i2s_t *obj, int channel_num, int rate, int word_len)
{
	hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;

	hal_i2s_set_ch_num(pi2s_adapter, (uint8_t)channel_num);
	hal_i2s_set_rate(pi2s_adapter, (uint8_t)rate);
	hal_i2s_set_word_len(pi2s_adapter, (uint8_t)word_len);
}

void i2s_deinit(i2s_t *obj)
{
	hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;

#if IS_CUT_TEST(CONFIG_CHIP_VER)
	uint32_t I2S_S1[5] = {PE_0, PE_3, PE_1, PE_4, PE_2};
#else
	uint32_t I2S_S1[5] = {PD_14, PD_17, PD_15, PD_18, PD_16};
#endif
	if (obj->i2s_initialized) {
		hal_i2s_deinit(pi2s_adapter);

		if (pi2s_adapter->dev_num == I2s0_Sel) {
			hal_pinmux_unregister(PF_11, PID_I2S0);
			hal_pinmux_unregister(PF_12, PID_I2S0);
			hal_pinmux_unregister(PF_13, PID_I2S0);
			hal_pinmux_unregister(PF_14, PID_I2S0);
			hal_pinmux_unregister(PF_15, PID_I2S0);
		}

		if (pi2s_adapter->dev_num == I2s1_Sel) {
			hal_pinmux_unregister(I2S_S1[0], PID_I2S1);
			hal_pinmux_unregister(I2S_S1[1], PID_I2S1);
			hal_pinmux_unregister(I2S_S1[2], PID_I2S1);
			hal_pinmux_unregister(I2S_S1[3], PID_I2S1);
			hal_pinmux_unregister(I2S_S1[4], PID_I2S1);
		}
		obj->i2s_initialized = 0;
	}
}

int *i2s_get_tx_page(i2s_t *obj)
{
	hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;
	u8 page_idx;

	page_idx = hal_i2s_get_tx_page(pi2s_adapter);

	if (page_idx <= pi2s_adapter->base_addr->page_size_rate_b.page_num) {
		return ((int *)pi2s_adapter->ptx_page_list[page_idx]);
	} else {
		dbg_printf("Tx_page is busy: \r\n");
		dbg_printf("page_idx: %d, I2SPageNum: %d \r\n", page_idx, pi2s_adapter->base_addr->page_size_rate_b.page_num);
		return NULL;
	}
}

void i2s_send_page(i2s_t *obj, u32 *pbuf)
{
	hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;
	u32 page_num, i;

	page_num = pi2s_adapter->base_addr->page_size_rate_b.page_num + 1;
	for (i = 0; i < page_num; i++) {

		if (pi2s_adapter->ptx_page_list[i] == pbuf) {
			hal_i2s_page_send(pi2s_adapter, i);
			break;  // break the for loop
		}
	}

	if (i == page_num) {
		dbg_printf("i2s_send_page: the pbuf(0x%x) is not a DMA buffer\r\n", pbuf);
	}
}

void i2s_recv_page(i2s_t *obj)
{
	hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;

	hal_i2s_page_recv(pi2s_adapter);
}

void i2s_enable(i2s_t *obj)
{
	hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;

	hal_i2s_en_ctrl(pi2s_adapter, 1);
}

void i2s_disable(i2s_t *obj)
{
	hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;

	hal_i2s_en_ctrl(pi2s_adapter, 0);

	hal_i2s_reset(pi2s_adapter);
}

void i2s_set_format(i2s_t *obj, i2s_format format)
{
	hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;

	hal_i2s_set_format(pi2s_adapter, format);
}

void i2s_set_master(i2s_t *obj, i2s_ms_mode ms_mode)
{
	hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;

	hal_i2s_set_master(pi2s_adapter, ms_mode);
}

void i2s_set_dma_burst_size(i2s_t *obj, i2s_burst_size burst_size)
{
	hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;

	hal_i2s_set_lxbus_burst_size(pi2s_adapter, burst_size);
}

void i2s_set_byte_swap(i2s_t *obj, BOOL byte_swap_en)
{
	hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;

	hal_i2s_set_byte_swap(pi2s_adapter, byte_swap_en);
}

void i2s_set_sck_inv(i2s_t *obj, BOOL sck_inv_en)
{
	hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;

	hal_i2s_set_sck_inv(pi2s_adapter, sck_inv_en);
}

void i2s_set_ws_swap(i2s_t *obj, i2s_ws_swap ws_swap)
{
	hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;

	hal_i2s_set_ws_swap(pi2s_adapter, ws_swap);
}

void i2s_set_loopback(i2s_t *obj, BOOL loopback_en)
{
	hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;

	hal_i2s_set_loopback(pi2s_adapter, loopback_en);
	if (loopback_en == 1) {
		hal_i2s_set_direction(pi2s_adapter, (uint8_t)I2S_DIR_TX);
	} else if (i2s_get_direction(obj) == I2S_DIR_TX) {
		hal_i2s_set_direction(pi2s_adapter, (uint8_t)I2S_DIR_TXRX);
	}
}

void i2s_set_data_start_edge(i2s_t *obj, i2s_edge_sw edge_sw)
{
	hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;

	hal_i2s_set_data_start_edge(pi2s_adapter, edge_sw);
}

void i2s_set_mute(i2s_t *obj, BOOL mute_en)
{
	hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;

	hal_i2s_set_mute(pi2s_adapter, mute_en);
}
