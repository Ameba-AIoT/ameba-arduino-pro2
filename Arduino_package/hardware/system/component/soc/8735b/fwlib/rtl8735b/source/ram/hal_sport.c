/**************************************************************************//**
 * @file     hal_sport.c
 * @brief    This SPORT HAL API functions.
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
//#include "hal_pinmux.h"
#include "hal_sport.h"

#if CONFIG_SPORT_EN

/**
 * @addtogroup hs_hal_sport SPORT
 * @{
 */

void hal_sport_irqhandler_ram(void)
{
	hal_sport_stubs.hal_sport_irqhandler_ram();
}

void hal_sport_irq_reg(void)
{
	hal_sport_stubs.hal_sport_irq_reg();
}

void hal_sport_irq_unreg(void)
{
	hal_sport_stubs.hal_sport_irq_unreg();
}

HAL_Status hal_sport_init(hal_sport_adapter_t *psport_adapter)
{
	return hal_sport_stubs.hal_sport_init(psport_adapter);
}

HAL_Status hal_sport_deinit(hal_sport_adapter_t *psport_adapter)
{
	return hal_sport_stubs.hal_sport_deinit(psport_adapter);
}

void hal_sport_reset(hal_sport_adapter_t *psport_adapter)
{
	hal_sport_stubs.hal_sport_reset(psport_adapter);
}

void hal_sport_reset_tx_fifo(hal_sport_adapter_t *psport_adapter)
{
	hal_sport_stubs.hal_sport_reset_tx_fifo(psport_adapter);
}

void hal_sport_reset_rx_fifo(hal_sport_adapter_t *psport_adapter)
{
	hal_sport_stubs.hal_sport_reset_rx_fifo(psport_adapter);
}

void hal_sport_bclk_reset(hal_sport_adapter_t *psport_adapter)
{
	hal_sport_stubs.hal_sport_bclk_reset(psport_adapter);
}

void hal_sport_dma_reset(hal_sport_adapter_t *psport_adapter)
{
	hal_sport_stubs.hal_sport_dma_reset(psport_adapter);
}

void hal_sport_clean_tx_page_own(hal_sport_adapter_t *psport_adapter)
{
	hal_sport_stubs.hal_sport_clean_tx_page_own(psport_adapter);
}

void hal_sport_clean_rx_page_own(hal_sport_adapter_t *psport_adapter)
{
	hal_sport_stubs.hal_sport_clean_rx_page_own(psport_adapter);
}

void hal_sport_set_master(hal_sport_adapter_t *psport_adapter, sport_dev_mode_t dev_mode)
{
	hal_sport_stubs.hal_sport_set_master(psport_adapter, dev_mode);
}

void hal_sport_set_loopback(hal_sport_adapter_t *psport_adapter, BOOL loopback_en)
{
	hal_sport_stubs.hal_sport_set_loopback(psport_adapter, loopback_en);
}

void hal_sport_mode(hal_sport_adapter_t *psport_adapter, sport_wk_mode_t wk_mode)
{
	hal_sport_stubs.hal_sport_mode(psport_adapter, wk_mode);
}

void hal_sport_tx_ch(hal_sport_adapter_t *psport_adapter, sport_sel_ch_t sport_sel_ch)
{
	hal_sport_stubs.hal_sport_tx_ch(psport_adapter, sport_sel_ch);
}

void hal_sport_rx_ch(hal_sport_adapter_t *psport_adapter, sport_sel_ch_t sport_sel_ch)
{
	hal_sport_stubs.hal_sport_rx_ch(psport_adapter, sport_sel_ch);
}

void hal_sport_format(hal_sport_adapter_t *psport_adapter, sport_format_t sport_format)
{
	hal_sport_stubs.hal_sport_format(psport_adapter, sport_format);
}

void hal_sport_rx_same_format(hal_sport_adapter_t *psport_adapter, BOOL rx_en)
{
	hal_sport_stubs.hal_sport_rx_same_format(psport_adapter, rx_en);
}

void hal_sport_rx_format(hal_sport_adapter_t *psport_adapter, sport_format_t sport_format)
{
	hal_sport_stubs.hal_sport_rx_format(psport_adapter, sport_format);
}

void hal_sport_tx0_mono(hal_sport_adapter_t *psport_adapter, BOOL type_sel)
{
	hal_sport_stubs.hal_sport_tx0_mono(psport_adapter, type_sel);
}

void hal_sport_tx1_mono(hal_sport_adapter_t *psport_adapter, BOOL type_sel)
{
	hal_sport_stubs.hal_sport_tx1_mono(psport_adapter, type_sel);
}

void hal_sport_rx_same_mono_stereo(hal_sport_adapter_t *psport_adapter, BOOL rx_en)
{
	hal_sport_stubs.hal_sport_rx_same_mono_stereo(psport_adapter, rx_en);
}

void hal_sport_rx0_mono(hal_sport_adapter_t *psport_adapter, BOOL type_sel)
{
	hal_sport_stubs.hal_sport_rx0_mono(psport_adapter, type_sel);
}

void hal_sport_rx1_mono(hal_sport_adapter_t *psport_adapter, BOOL type_sel)
{
	hal_sport_stubs.hal_sport_rx1_mono(psport_adapter, type_sel);
}

void hal_sport_tx0_data_length(hal_sport_adapter_t *psport_adapter, sport_dl_t dl)
{
	hal_sport_stubs.hal_sport_tx0_data_length(psport_adapter, dl);
}

void hal_sport_tx1_data_length(hal_sport_adapter_t *psport_adapter, sport_dl_t dl)
{
	hal_sport_stubs.hal_sport_tx1_data_length(psport_adapter, dl);
}

void hal_sport_rx_same_data_length(hal_sport_adapter_t *psport_adapter, BOOL rx_en)
{
	hal_sport_stubs.hal_sport_rx_same_data_length(psport_adapter, rx_en);
}

void hal_sport_rx0_data_length(hal_sport_adapter_t *psport_adapter, sport_dl_t dl)
{
	hal_sport_stubs.hal_sport_rx0_data_length(psport_adapter, dl);
}
void hal_sport_rx1_data_length(hal_sport_adapter_t *psport_adapter, sport_dl_t dl)
{
	hal_sport_stubs.hal_sport_rx1_data_length(psport_adapter, dl);
}

void hal_sport_tx_channel_length(hal_sport_adapter_t *psport_adapter, sport_cl_t cl)
{
	hal_sport_stubs.hal_sport_tx_channel_length(psport_adapter, cl);
}

void hal_sport_rx_same_channel_length(hal_sport_adapter_t *psport_adapter, BOOL rx_en)
{
	hal_sport_stubs.hal_sport_rx_same_channel_length(psport_adapter, rx_en);
}

void hal_sport_rx_channel_length(hal_sport_adapter_t *psport_adapter, sport_cl_t cl)
{
	hal_sport_stubs.hal_sport_rx_channel_length(psport_adapter, cl);
}

void hal_sport_tx_rate(hal_sport_adapter_t *psport_adapter, sport_rate_t sport_sample_rate)
{
	hal_sport_stubs.hal_sport_tx_rate(psport_adapter, sport_sample_rate);
}

void hal_sport_rx_rate(hal_sport_adapter_t *psport_adapter, sport_rate_t sport_sample_rate)
{
	hal_sport_stubs.hal_sport_rx_rate(psport_adapter, sport_sample_rate);
}

void hal_sport_tx_data_dir(hal_sport_adapter_t *psport_adapter, sport_ml_t tx0_ml, sport_ml_t tx1_ml)
{
	hal_sport_stubs.hal_sport_tx_data_dir(psport_adapter, tx0_ml, tx1_ml);
}

void hal_sport_rx_data_dir(hal_sport_adapter_t *psport_adapter, sport_ml_t rx0_ml, sport_ml_t rx1_ml)
{
	hal_sport_stubs.hal_sport_rx_data_dir(psport_adapter, rx0_ml, rx1_ml);
}

void hal_sport_tx_lr_swap(hal_sport_adapter_t *psport_adapter, BOOL tx0_en, BOOL tx1_en)
{
	hal_sport_stubs.hal_sport_tx_lr_swap(psport_adapter, tx0_en, tx1_en);
}
void hal_sport_rx_lr_swap(hal_sport_adapter_t *psport_adapter, BOOL rx0_en, BOOL rx1_en)
{
	hal_sport_stubs.hal_sport_rx_lr_swap(psport_adapter, rx0_en, rx1_en);
}
void hal_sport_tx_byte_swap(hal_sport_adapter_t *psport_adapter, BOOL tx0_en, BOOL tx1_en)
{
	hal_sport_stubs.hal_sport_tx_byte_swap(psport_adapter, tx0_en, tx1_en);
}

void hal_sport_rx_byte_swap(hal_sport_adapter_t *psport_adapter, BOOL rx0_en, BOOL rx1_en)
{
	hal_sport_stubs.hal_sport_rx_byte_swap(psport_adapter, rx0_en, rx1_en);
}

void hal_sport_bclk_inverse(hal_sport_adapter_t *psport_adapter, BOOL inverse_en)
{
	hal_sport_stubs.hal_sport_bclk_inverse(psport_adapter, inverse_en);
}

void hal_sport_set_mclk(hal_sport_adapter_t *psport_adapter, sport_mclk_t sport_mclk, BOOL mclk_en)
{
	hal_sport_stubs.hal_sport_set_mclk(psport_adapter, sport_mclk, mclk_en);
}

void hal_sport_sel_tx_tdm(hal_sport_adapter_t *psport_adapter, sport_tdm_t sport_tdm)
{
	hal_sport_stubs.hal_sport_sel_tx_tdm(psport_adapter, sport_tdm);
}

void hal_sport_sel_rx_tdm(hal_sport_adapter_t *psport_adapter, sport_tdm_t sport_tdm)
{
	hal_sport_stubs.hal_sport_sel_rx_tdm(psport_adapter, sport_tdm);
}

void hal_sport_set_tx0_consum(hal_sport_adapter_t *psport_adapter, u8 sport_layer)
{
	hal_sport_stubs.hal_sport_set_tx0_consum(psport_adapter, sport_layer);
}

void hal_sport_set_tx1_consum(hal_sport_adapter_t *psport_adapter, u8 sport_layer)
{
	hal_sport_stubs.hal_sport_set_tx1_consum(psport_adapter, sport_layer);
}

void hal_sport_set_rx0_consum(hal_sport_adapter_t *psport_adapter, u8 sport_layer)
{
	hal_sport_stubs.hal_sport_set_rx0_consum(psport_adapter, sport_layer);
}

void hal_sport_set_rx1_consum(hal_sport_adapter_t *psport_adapter, u8 sport_layer)
{
	hal_sport_stubs.hal_sport_set_rx1_consum(psport_adapter, sport_layer);
}

void hal_sport_tx_fifo_0(hal_sport_adapter_t *psport_adapter, BOOL ch1ch0_en, BOOL ch2ch3_en)
{
	hal_sport_stubs.hal_sport_tx_fifo_0(psport_adapter, ch1ch0_en, ch2ch3_en);
}

void hal_sport_tx_fifo_1(hal_sport_adapter_t *psport_adapter, BOOL ch4ch5_en, BOOL ch6ch7_en)
{
	hal_sport_stubs.hal_sport_tx_fifo_1(psport_adapter, ch4ch5_en, ch6ch7_en);
}

void hal_sport_rx_fifo_0(hal_sport_adapter_t *psport_adapter, BOOL ch1ch0_en, BOOL ch2ch3_en)
{
	hal_sport_stubs.hal_sport_rx_fifo_0(psport_adapter, ch1ch0_en, ch2ch3_en);
}

void hal_sport_rx_fifo_1(hal_sport_adapter_t *psport_adapter, BOOL ch4ch5_en, BOOL ch6ch7_en)
{
	hal_sport_stubs.hal_sport_rx_fifo_1(psport_adapter, ch4ch5_en, ch6ch7_en);
}

void hal_sport_set_tx_lrck(hal_sport_adapter_t *psport_adapter, u8 bclk_cnt)
{
	hal_sport_stubs.hal_sport_set_tx_lrck(psport_adapter, bclk_cnt);
}

void hal_sport_set_rx_lrck(hal_sport_adapter_t *psport_adapter, u8 bclk_cnt)
{
	hal_sport_stubs.hal_sport_set_rx_lrck(psport_adapter, bclk_cnt);
}

void hal_sport_tx_params(hal_sport_adapter_t *psport_adapter, hal_sport_tx_params_t *psport_tx_params)
{
	hal_sport_stubs.hal_sport_tx_params(psport_adapter, psport_tx_params);
}

void hal_sport_rx_params(hal_sport_adapter_t *psport_adapter, hal_sport_rx_params_t *psport_rx_params)
{
	hal_sport_stubs.hal_sport_rx_params(psport_adapter, psport_rx_params);
}

void hal_sport_tx_fifo_th(hal_sport_adapter_t *psport_adapter, u8 tx_th)
{
	hal_sport_stubs.hal_sport_tx_fifo_th(psport_adapter, tx_th);
}

void hal_sport_rx_fifo_th(hal_sport_adapter_t *psport_adapter, u8 rx_th)
{
	hal_sport_stubs.hal_sport_rx_fifo_th(psport_adapter, rx_th);
}

void hal_sport_set_dma_burst(hal_sport_adapter_t *psport_adapter, sport_burst_size_t burst_size)
{
	hal_sport_stubs.hal_sport_set_dma_burst(psport_adapter, burst_size);
}

void hal_sport_autoload_dma_burst(hal_sport_adapter_t *psport_adapter)
{
	hal_sport_stubs.hal_sport_autoload_dma_burst(psport_adapter);
}

void hal_sport_set_dma_intr(hal_sport_adapter_t *psport_adapter, sport_trx_t trx, hal_sport_page_intr_t *ppage_intr)
{
	hal_sport_stubs.hal_sport_set_dma_intr(psport_adapter, trx, ppage_intr);
}

void hal_sport_set_tx_fifo_intr(hal_sport_adapter_t *psport_adapter, hal_sport_tx_fifo_intr_t *ptx_fifo_intr)
{
	hal_sport_stubs.hal_sport_set_tx_fifo_intr(psport_adapter, ptx_fifo_intr);
}

void hal_sport_set_rx_fifo_intr(hal_sport_adapter_t *psport_adapter, hal_sport_rx_fifo_intr_t *prx_fifo_intr)
{
	hal_sport_stubs.hal_sport_set_rx_fifo_intr(psport_adapter, prx_fifo_intr);
}

void hal_sport_dma_params(hal_sport_adapter_t *psport_adapter, u16 page_size, sport_page_num page_num)
{
	hal_sport_stubs.hal_sport_dma_params(psport_adapter, page_size, page_num);
}

void hal_sport_tx_start(hal_sport_adapter_t *psport_adapter, BOOL en)
{
	hal_sport_stubs.hal_sport_tx_start(psport_adapter, en);
}

void hal_sport_rx_start(hal_sport_adapter_t *psport_adapter, BOOL en)
{
	hal_sport_stubs.hal_sport_rx_start(psport_adapter, en);
}

void hal_sport_tx_dma_start(hal_sport_adapter_t *psport_adapter, BOOL en)
{
	hal_sport_stubs.hal_sport_tx_dma_start(psport_adapter, en);
}

u32 hal_sport_get_tx_dma_start_sta(hal_sport_adapter_t *psport_adapter)
{
	return hal_sport_stubs.hal_sport_get_tx_dma_start_sta(psport_adapter);
}

void hal_sport_rx_dma_start(hal_sport_adapter_t *psport_adapter, BOOL en)
{
	hal_sport_stubs.hal_sport_rx_dma_start(psport_adapter, en);
}

u32 hal_sport_get_rx_dma_start_sta(hal_sport_adapter_t *psport_adapter)
{
	return hal_sport_stubs.hal_sport_get_rx_dma_start_sta(psport_adapter);
}

void hal_sport_dma_buffer(hal_sport_adapter_t *psport_adapter, hal_sport_buf_params_t *pbuf_params)
{
	hal_sport_stubs.hal_sport_dma_buffer(psport_adapter, pbuf_params);
}

int *hal_sport_get_tx0_page(hal_sport_adapter_t *psport_adapter)
{
	return hal_sport_stubs.hal_sport_get_tx0_page(psport_adapter);
}

int *hal_sport_get_tx1_page(hal_sport_adapter_t *psport_adapter)
{
	return hal_sport_stubs.hal_sport_get_tx1_page(psport_adapter);
}

void hal_sport_tx0_page_send(hal_sport_adapter_t *psport_adapter, u32 *pbuf)
{
	hal_sport_stubs.hal_sport_tx0_page_send(psport_adapter, pbuf);
}

void hal_sport_tx1_page_send(hal_sport_adapter_t *psport_adapter, u32 *pbuf)
{
	hal_sport_stubs.hal_sport_tx1_page_send(psport_adapter, pbuf);
}

u32 hal_sport_rx0_page_recv(hal_sport_adapter_t *psport_adapter)
{
	return hal_sport_stubs.hal_sport_rx0_page_recv(psport_adapter);
}

u32 hal_sport_rx1_page_recv(hal_sport_adapter_t *psport_adapter)
{
	return hal_sport_stubs.hal_sport_rx1_page_recv(psport_adapter);
}

u32 hal_sport_get_tx_fifo_err(hal_sport_adapter_t *psport_adapter)
{
	return hal_sport_stubs.hal_sport_get_tx_fifo_err(psport_adapter);
}

u32 hal_sport_get_rx_fifo_err(hal_sport_adapter_t *psport_adapter)
{
	return hal_sport_stubs.hal_sport_get_rx_fifo_err(psport_adapter);
}

void hal_sport_clr_tx_fifo_err(hal_sport_adapter_t *psport_adapter)
{
	hal_sport_stubs.hal_sport_clr_tx_fifo_err(psport_adapter);
}

void hal_sport_clr_rx_fifo_err(hal_sport_adapter_t *psport_adapter)
{
	hal_sport_stubs.hal_sport_clr_rx_fifo_err(psport_adapter);
}
void hal_sport_fifo_cb_handler(hal_sport_adapter_t *psport_adapter, sport_irq_user_cb_t callback, u32 *arg)
{
	hal_sport_stubs.hal_sport_fifo_cb_handler(psport_adapter, callback, arg);
}

void hal_sport_tx0_dma_cb_handler(hal_sport_adapter_t *psport_adapter, sport_irq_user_cb_t callback, u32 *arg)
{
	hal_sport_stubs.hal_sport_tx0_dma_cb_handler(psport_adapter, callback, arg);
}

void hal_sport_tx1_dma_cb_handler(hal_sport_adapter_t *psport_adapter, sport_irq_user_cb_t callback, u32 *arg)
{
	hal_sport_stubs.hal_sport_tx1_dma_cb_handler(psport_adapter, callback, arg);
}

void hal_sport_rx0_dma_cb_handler(hal_sport_adapter_t *psport_adapter, sport_irq_user_cb_t callback, u32 *arg)
{
	hal_sport_stubs.hal_sport_rx0_dma_cb_handler(psport_adapter, callback, arg);
}

void hal_sport_rx1_dma_cb_handler(hal_sport_adapter_t *psport_adapter, sport_irq_user_cb_t callback, u32 *arg)
{
	hal_sport_stubs.hal_sport_rx1_dma_cb_handler(psport_adapter, callback, arg);
}

void hal_sport_dma_err_cb_handler(hal_sport_adapter_t *psport_adapter, sport_irq_user_cb_t callback, u32 *arg)
{
	hal_sport_stubs.hal_sport_dma_err_cb_handler(psport_adapter, callback, arg);
}

void hal_sport_fixed_bclk(hal_sport_adapter_t *psport_adapter, BOOL fixed_en, sport_fixed_bclk_t fixed_bclk_sel)
{
	hal_sport_stubs.hal_sport_fixed_bclk(psport_adapter, fixed_en, fixed_bclk_sel);
}

void hal_sport_rx_same_fs(hal_sport_adapter_t *psport_adapter, BOOL en)
{
	hal_sport_stubs.hal_sport_rx_same_fs(psport_adapter, en);
}


/** @} */ /* End of group hs_hal_sport */

#endif

