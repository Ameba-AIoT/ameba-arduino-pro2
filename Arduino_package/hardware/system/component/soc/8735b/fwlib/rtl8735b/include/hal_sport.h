/**************************************************************************//**
 * @file     hal_sport.h
 * @brief    The HAL API implementation for the SPORT device.
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

#ifndef _HAL_SPORT_H_
#define _HAL_SPORT_H_
#include "cmsis.h"

#include "rtl8735b_sport.h"

#ifdef  __cplusplus
extern "C"
{
#endif

/**
  * @brief The stubs functions table to exports SPORT HAL functions in ROM.
  */
extern const hal_sport_func_stubs_t hal_sport_stubs;

void hal_sport_irqhandler_ram(void);
void hal_sport_irq_reg(void);
void hal_sport_irq_unreg(void);
HAL_Status hal_sport_init(hal_sport_adapter_t *psport_adapter);
HAL_Status hal_sport_deinit(hal_sport_adapter_t *psport_adapter);
void hal_sport_reset(hal_sport_adapter_t *psport_adapter);
void hal_sport_reset_tx_fifo(hal_sport_adapter_t *psport_adapter);
void hal_sport_reset_rx_fifo(hal_sport_adapter_t *psport_adapter);
void hal_sport_bclk_reset(hal_sport_adapter_t *psport_adapter);
void hal_sport_dma_reset(hal_sport_adapter_t *psport_adapter);
void hal_sport_clean_tx_page_own(hal_sport_adapter_t *psport_adapter);
void hal_sport_clean_rx_page_own(hal_sport_adapter_t *psport_adapter);
void hal_sport_set_master(hal_sport_adapter_t *psport_adapter, sport_dev_mode_t dev_mode);
void hal_sport_set_loopback(hal_sport_adapter_t *psport_adapter, BOOL loopback_en);
void hal_sport_mode(hal_sport_adapter_t *psport_adapter, sport_wk_mode_t wk_mode);
void hal_sport_tx_ch(hal_sport_adapter_t *psport_adapter, sport_sel_ch_t sport_sel_ch);
void hal_sport_rx_ch(hal_sport_adapter_t *psport_adapter, sport_sel_ch_t sport_sel_ch);
void hal_sport_format(hal_sport_adapter_t *psport_adapter, sport_format_t sport_format);
void hal_sport_rx_same_format(hal_sport_adapter_t *psport_adapter, BOOL rx_en);
void hal_sport_rx_format(hal_sport_adapter_t *psport_adapter, sport_format_t sport_format);
void hal_sport_tx0_mono(hal_sport_adapter_t *psport_adapter, BOOL type_sel);
void hal_sport_tx1_mono(hal_sport_adapter_t *psport_adapter, BOOL type_sel);
void hal_sport_rx_same_mono_stereo(hal_sport_adapter_t *psport_adapter, BOOL rx_en);
void hal_sport_rx0_mono(hal_sport_adapter_t *psport_adapter, BOOL type_sel);
void hal_sport_rx1_mono(hal_sport_adapter_t *psport_adapter, BOOL type_sel);
void hal_sport_tx0_data_length(hal_sport_adapter_t *psport_adapter, sport_dl_t dl);
void hal_sport_tx1_data_length(hal_sport_adapter_t *psport_adapter, sport_dl_t dl);
void hal_sport_rx_same_data_length(hal_sport_adapter_t *psport_adapter, BOOL rx_en);
void hal_sport_rx0_data_length(hal_sport_adapter_t *psport_adapter, sport_dl_t dl);
void hal_sport_rx1_data_length(hal_sport_adapter_t *psport_adapter, sport_dl_t dl);
void hal_sport_tx_channel_length(hal_sport_adapter_t *psport_adapter, sport_cl_t cl);
void hal_sport_rx_same_channel_length(hal_sport_adapter_t *psport_adapter, BOOL rx_en);
void hal_sport_rx_channel_length(hal_sport_adapter_t *psport_adapter, sport_cl_t cl);
void hal_sport_tx_rate(hal_sport_adapter_t *psport_adapter, sport_rate_t sport_sample_rate);
void hal_sport_rx_rate(hal_sport_adapter_t *psport_adapter, sport_rate_t sport_sample_rate);
void hal_sport_tx_data_dir(hal_sport_adapter_t *psport_adapter, sport_ml_t tx0_ml, sport_ml_t tx1_ml);
void hal_sport_rx_data_dir(hal_sport_adapter_t *psport_adapter, sport_ml_t rx0_ml, sport_ml_t rx1_ml);
void hal_sport_tx_lr_swap(hal_sport_adapter_t *psport_adapter, BOOL tx0_en, BOOL tx1_en);
void hal_sport_rx_lr_swap(hal_sport_adapter_t *psport_adapter, BOOL rx0_en, BOOL rx1_en);
void hal_sport_tx_byte_swap(hal_sport_adapter_t *psport_adapter, BOOL tx0_en, BOOL tx1_en);
void hal_sport_rx_byte_swap(hal_sport_adapter_t *psport_adapter, BOOL rx0_en, BOOL rx1_en);
void hal_sport_bclk_inverse(hal_sport_adapter_t *psport_adapter, BOOL inverse_en);
void hal_sport_set_mclk(hal_sport_adapter_t *psport_adapter, sport_mclk_t sport_mclk, BOOL mclk_en);
void hal_sport_sel_tx_tdm(hal_sport_adapter_t *psport_adapter, sport_tdm_t sport_tdm);
void hal_sport_sel_rx_tdm(hal_sport_adapter_t *psport_adapter, sport_tdm_t sport_tdm);
void hal_sport_set_tx0_consum(hal_sport_adapter_t *psport_adapter, u8 sport_layer);
void hal_sport_set_tx1_consum(hal_sport_adapter_t *psport_adapter, u8 sport_layer);
void hal_sport_set_rx0_consum(hal_sport_adapter_t *psport_adapter, u8 sport_layer);
void hal_sport_set_rx1_consum(hal_sport_adapter_t *psport_adapter, u8 sport_layer);
void hal_sport_tx_fifo_0(hal_sport_adapter_t *psport_adapter, BOOL ch1ch0_en, BOOL ch2ch3_en);
void hal_sport_tx_fifo_1(hal_sport_adapter_t *psport_adapter, BOOL ch4ch5_en, BOOL ch6ch7_en);
void hal_sport_rx_fifo_0(hal_sport_adapter_t *psport_adapter, BOOL ch1ch0_en, BOOL ch2ch3_en);
void hal_sport_rx_fifo_1(hal_sport_adapter_t *psport_adapter, BOOL ch4ch5_en, BOOL ch6ch7_en);
void hal_sport_set_tx_lrck(hal_sport_adapter_t *psport_adapter, u8 bclk_cnt);
void hal_sport_set_rx_lrck(hal_sport_adapter_t *psport_adapter, u8 bclk_cnt);
void hal_sport_tx_params(hal_sport_adapter_t *psport_adapter, hal_sport_tx_params_t *psport_tx_params);
void hal_sport_rx_params(hal_sport_adapter_t *psport_adapter, hal_sport_rx_params_t *psport_rx_params);
void hal_sport_tx_fifo_th(hal_sport_adapter_t *psport_adapter, u8 tx_th);
void hal_sport_rx_fifo_th(hal_sport_adapter_t *psport_adapter, u8 rx_th);
void hal_sport_set_dma_burst(hal_sport_adapter_t *psport_adapter, sport_burst_size_t burst_size);
void hal_sport_autoload_dma_burst(hal_sport_adapter_t *psport_adapter);
void hal_sport_set_dma_intr(hal_sport_adapter_t *psport_adapter, sport_trx_t trx, hal_sport_page_intr_t *ppage_intr);
void hal_sport_set_tx_fifo_intr(hal_sport_adapter_t *psport_adapter, hal_sport_tx_fifo_intr_t *ptx_fifo_intr);
void hal_sport_set_rx_fifo_intr(hal_sport_adapter_t *psport_adapter, hal_sport_rx_fifo_intr_t *prx_fifo_intr);
void hal_sport_dma_params(hal_sport_adapter_t *psport_adapter, u16 page_size, sport_page_num page_num);
void hal_sport_tx_start(hal_sport_adapter_t *psport_adapter, BOOL en);
void hal_sport_rx_start(hal_sport_adapter_t *psport_adapter, BOOL en);
void hal_sport_tx_dma_start(hal_sport_adapter_t *psport_adapter, BOOL en);
u32 hal_sport_get_tx_dma_start_sta(hal_sport_adapter_t *psport_adapter);
void hal_sport_rx_dma_start(hal_sport_adapter_t *psport_adapter, BOOL en);
u32 hal_sport_get_rx_dma_start_sta(hal_sport_adapter_t *psport_adapter);
void hal_sport_dma_buffer(hal_sport_adapter_t *psport_adapter, hal_sport_buf_params_t *pbuf_params);
int *hal_sport_get_tx0_page(hal_sport_adapter_t *psport_adapter);
int *hal_sport_get_tx1_page(hal_sport_adapter_t *psport_adapter);
void hal_sport_tx0_page_send(hal_sport_adapter_t *psport_adapter, u32 *pbuf);
void hal_sport_tx1_page_send(hal_sport_adapter_t *psport_adapter, u32 *pbuf);
u32 hal_sport_rx0_page_recv(hal_sport_adapter_t *psport_adapter);
u32 hal_sport_rx1_page_recv(hal_sport_adapter_t *psport_adapter);
u32 hal_sport_get_tx_fifo_err(hal_sport_adapter_t *psport_adapter);
u32 hal_sport_get_rx_fifo_err(hal_sport_adapter_t *psport_adapter);
void hal_sport_clr_tx_fifo_err(hal_sport_adapter_t *psport_adapter);
void hal_sport_clr_rx_fifo_err(hal_sport_adapter_t *psport_adapter);
void hal_sport_fifo_cb_handler(hal_sport_adapter_t *psport_adapter, sport_irq_user_cb_t callback, u32 *arg);
void hal_sport_tx0_dma_cb_handler(hal_sport_adapter_t *psport_adapter, sport_irq_user_cb_t callback, u32 *arg);
void hal_sport_tx1_dma_cb_handler(hal_sport_adapter_t *psport_adapter, sport_irq_user_cb_t callback, u32 *arg);
void hal_sport_rx0_dma_cb_handler(hal_sport_adapter_t *psport_adapter, sport_irq_user_cb_t callback, u32 *arg);
void hal_sport_rx1_dma_cb_handler(hal_sport_adapter_t *psport_adapter, sport_irq_user_cb_t callback, u32 *arg);
void hal_sport_dma_err_cb_handler(hal_sport_adapter_t *psport_adapter, sport_irq_user_cb_t callback, u32 *arg);
void hal_sport_fixed_bclk(hal_sport_adapter_t *psport_adapter, BOOL fixed_en, sport_fixed_bclk_t fixed_bclk_sel);
void hal_sport_rx_same_fs(hal_sport_adapter_t *psport_adapter, BOOL en);

#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_SPORT_H_"

