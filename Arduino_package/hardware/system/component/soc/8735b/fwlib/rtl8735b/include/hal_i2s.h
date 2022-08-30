/**************************************************************************//**
 * @file     hal_i2s.h
 * @brief    The HAL API implementation for the I2S device.
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

#ifndef _HAL_I2S_H_
#define _HAL_I2S_H_
#include "cmsis.h"

#include "rtl8735b_i2s.h"


#ifdef  __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup hs_hal_i2s I2S
 * @ingroup 8195bh_hal
 * @{
 * @brief The I2S HAL module of the HS platform.
 */

/**
  * @brief The stubs functions table to exports I2S HAL functions in ROM.
  */
extern const hal_i2s_func_stubs_t hal_i2s_stubs;


/**
 *  @brief  Set the word length.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] i2s_word_len The word length.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_i2s_set_word_len(hal_i2s_adapter_t *pi2s_adapter, i2s_word_len_t i2s_word_len)
{
	pi2s_adapter->base_addr->ctrl_b.wl = i2s_word_len;
}

/**
 *  @brief  Set the channel nunber.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] i2s_ch_num The channel nunber.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_i2s_set_ch_num(hal_i2s_adapter_t *pi2s_adapter, i2s_ch_num_t i2s_ch_num)
{
	pi2s_adapter->base_addr->ctrl_b.audio_mono = i2s_ch_num;
}

/**
 *  @brief  Set the page nunber.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] i2s_ch_num The page nunber.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_i2s_set_page_num(hal_i2s_adapter_t *pi2s_adapter, i2s_page_num_t i2s_page_num)
{
	pi2s_adapter->base_addr->page_size_rate_b.page_num = i2s_page_num - 1;
}

/**
 *  @brief  Set the page size.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] i2s_ch_num The page size.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_i2s_set_page_size(hal_i2s_adapter_t *pi2s_adapter, u16 i2s_page_size)
{
	pi2s_adapter->base_addr->page_size_rate_b.page_size = i2s_page_size;
}

/**
 *  @brief  Conrtol the tx and rx.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] i2s_trx_act Select the direction of the transmission.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_i2s_set_direction(hal_i2s_adapter_t *pi2s_adapter, i2s_direction_t i2s_trx_act)
{
	pi2s_adapter->base_addr->ctrl_b.tx_act = i2s_trx_act;
}

/**
 *  @brief  Conrtol the interface format.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] format Select the interface format.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_i2s_set_format(hal_i2s_adapter_t *pi2s_adapter, i2s_format_t format)
{
	pi2s_adapter->base_addr->ctrl_b.format = format;
}

/**
 *  @brief  Set the master or slave mode.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] dev_mode Select the master or slave mode.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_i2s_set_master(hal_i2s_adapter_t *pi2s_adapter, i2s_dev_mode_t dev_mode)
{
	pi2s_adapter->base_addr->ctrl_b.slave_mode = dev_mode;
}

/**
 *  @brief  Set the I2S burst size.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] burst_size Burst size for DMA.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_i2s_set_lxbus_burst_size(hal_i2s_adapter_t *pi2s_adapter, i2s_burst_size_t burst_size)
{
	pi2s_adapter->base_addr->ctrl_b.burst_size = burst_size;
}

/**
 *  @brief  Make the data do the byte switch.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] byte_swap Enable control.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_i2s_set_byte_swap(hal_i2s_adapter_t *pi2s_adapter, i2s_byte_swap_t byte_swap)
{
	pi2s_adapter->base_addr->ctrl_b.byte_swap = byte_swap;
}

/**
 *  @brief  Invert I2S SCK.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] sck_inv Enable control.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_i2s_set_sck_inv(hal_i2s_adapter_t *pi2s_adapter, i2s_sck_inv_t sck_inv)
{
	pi2s_adapter->base_addr->ctrl_b.sck_swap = sck_inv;
}

/**
 *  @brief  Control whether the data appear in "right" or "left" phase of WS clock.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] ws_swap Enable control.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_i2s_set_ws_swap(hal_i2s_adapter_t *pi2s_adapter, i2s_ws_swap_t ws_swap)
{
	pi2s_adapter->base_addr->ctrl_b.lr_swap = ws_swap;
}

/**
 *  @brief Set the I2S loopback mode.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] loopback Enable control.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_i2s_set_loopback(hal_i2s_adapter_t *pi2s_adapter, i2s_loopback_t loopback)
{
	pi2s_adapter->base_addr->ctrl_b.loop_back = loopback;
}

/**
 *  @brief Chose to send data at the negative edge or positive edge of SCK.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] edge_sw Select the negative edge or positive edge.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_i2s_set_data_start_edge(hal_i2s_adapter_t *pi2s_adapter, i2s_edge_sw_t edge_sw)
{
	pi2s_adapter->base_addr->ctrl_b.edge_sw = edge_sw;
}

/**
 *  @brief Control the I2S mute.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] mute Enable control.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_i2s_set_mute(hal_i2s_adapter_t *pi2s_adapter, i2s_mute_t mute)
{
	pi2s_adapter->base_addr->ctrl_b.mute = mute;
}

/**
 *  @brief Enable or disable the I2S.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] dma_en Enable control.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_i2s_dma_en(hal_i2s_adapter_t *pi2s_adapter, BOOL dma_en)
{
	pi2s_adapter->base_addr->ctrl_b.iis_en = dma_en;
}

/** @} */ /* End of group hs_hal_i2s */


void hal_i2s_irq_handler(void *hid);
void hal_i2s_irq_reg(hal_i2s_adapter_t *pi2s_adapter);
void hal_i2s_irq_unreg(hal_i2s_adapter_t *pi2s_adapter);
HAL_Status hal_i2s_en(i2s_index_sel_t index_sel, BOOL en);
HAL_Status hal_i2s_clk_ctrl(i2s_index_sel_t index_sel, BOOL en);
HAL_Status hal_i2s_mclk_ctrl(i2s_index_sel_t index_sel, BOOL en);
HAL_Status hal_i2s_rx_pin_ctrl(i2s_index_sel_t index_sel, BOOL en);
HAL_Status hal_i2s_5p1_pin_ctrl(i2s_index_sel_t index_sel, BOOL en);
void hal_i2s_app_pin_ctrl(hal_i2s_adapter_t *pi2s_adapter);
HAL_Status hal_i2s_func_ctrl(hal_i2s_adapter_t *pi2s_adapter, BOOL i2s_func_en);
HAL_Status hal_i2s_init(hal_i2s_adapter_t *pi2s_adapter);
void hal_i2s_deinit(hal_i2s_adapter_t *pi2s_adapter);
void hal_i2s_enter_critical(void);
void hal_i2s_exit_critical(void);
void hal_i2s_set_parameter(hal_i2s_adapter_t *pi2s_adapter, hal_i2s_def_setting_t *psetting);
void hal_i2s_set_rate(hal_i2s_adapter_t *pi2s_adapter, i2s_sample_rate_t i2s_sample_rate);
void hal_i2s_set_dma_buf(hal_i2s_adapter_t *pi2s_adapter, u16 i2s_page_size, i2s_page_num_t i2s_page_num);
u8 hal_i2s_get_tx_page(hal_i2s_adapter_t *pi2s_adapter);
u8 hal_i2s_get_rx_page(hal_i2s_adapter_t *pi2s_adapter);
void hal_i2s_page_send(hal_i2s_adapter_t *pi2s_adapter, u8 page_idx);
HAL_Status hal_i2s_page_recv(hal_i2s_adapter_t *pi2s_adapter);
void hal_i2s_clear_all_own_bit(hal_i2s_adapter_t *pi2s_adapter);
void hal_i2s_reset(hal_i2s_adapter_t *pi2s_adapter);
void hal_i2s_reset_and_disable(hal_i2s_adapter_t *pi2s_adapter);
void hal_i2s_en_ctrl(hal_i2s_adapter_t *pi2s_adapter, BOOL en);
void hal_i2s_clr_intr(hal_i2s_adapter_t *pi2s_adapter);
void hal_i2s_clr_all_intr(hal_i2s_adapter_t *pi2s_adapter);
void hal_i2s_intr_ctrl(hal_i2s_adapter_t *pi2s_adapter, i2s_tx_imr_t i2s_tx_intr_msk, i2s_rx_imr_t i2s_rx_intr_msk);
void hal_i2s_read_memory_cache_invalidate(hal_i2s_adapter_t *pi2s_adapter);


#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_I2S_H_"

