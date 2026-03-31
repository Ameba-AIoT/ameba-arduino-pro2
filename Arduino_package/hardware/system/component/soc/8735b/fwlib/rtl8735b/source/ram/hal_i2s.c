/**************************************************************************//**
 * @file     hal_i2s.c
 * @brief    This I2S HAL API functions.
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
#include "hal_i2s.h"

#if CONFIG_I2S_EN

extern void hal_syson_i2s_98m_pll_ctrl(BOOL en);
extern void hal_syson_i2s_45m_pll_ctrl(BOOL en);


/**
 * @addtogroup hs_hal_i2s I2S
 * @{
 */


/**
 *  @brief The I2S interrupt handler. It process all interrupt events.
 *
 *  @param[in]  hid The handler ID, it should be the I2S adapter.
 *
 *  @returns void
 */
void hal_i2s_irq_handler(void *hid)
{
	hal_i2s_stubs.hal_i2s_irq_handler(hid);
}

/**
 *  @brief To register a IRQ handler for I2S.
 *
 *  @returns void
 */
void hal_i2s_irq_reg(hal_i2s_adapter_t *pi2s_adapter)
{
	hal_i2s_stubs.hal_i2s_irq_reg(pi2s_adapter);
}

/**
 *  @brief To un-register the I2S IRQ handler.
 *
 *  @param[in]  pi2s_adapter The I2S adapter.
 *
 *  @returns void
 */
void hal_i2s_irq_unreg(hal_i2s_adapter_t *pi2s_adapter)
{
	hal_i2s_stubs.hal_i2s_irq_unreg(pi2s_adapter);
}

/**
 *  @brief To enable or disable I2S for the platform.
 *
 *  @param[in] index_sel The I2S index. It can be 0 or 1.
 *  @param[in] en  Enable control: 0 is disable, 1 is enable.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_i2s_en(i2s_index_sel_t index_sel, BOOL en)
{
	return hal_i2s_stubs.hal_i2s_en(index_sel, en);
}

/**
 *  @brief To enable/disable the bus clock for I2S.
 *
 *  @param[in] index_sel The I2S index. It can be 0 or 1.
 *  @param[in] en  Enable control: 0 is disable, 1 is enable.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_i2s_clk_ctrl(i2s_index_sel_t index_sel, BOOL en)
{
	return hal_i2s_stubs.hal_i2s_clk_ctrl(index_sel, en);
}

/**
 *  @brief To enable/disable the mclk output.
 *
 *  @param[in] index_sel The I2S index. It can be 0 or 1.
 *  @param[in] en  Enable control: 0 is disable, 1 is enable.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_i2s_mclk_ctrl(i2s_index_sel_t index_sel, BOOL en)
{
	return hal_i2s_stubs.hal_i2s_mclk_ctrl(index_sel, en);
}

/**
 *  @brief To enable or disable I2S rx pin.
 *
 *  @param[in] index_sel The I2S index. It can be 0 or 1.
 *  @param[in] en  Enable control: 0 is disable, 1 is enable.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_i2s_rx_pin_ctrl(i2s_index_sel_t index_sel, BOOL en)
{
	return hal_i2s_stubs.hal_i2s_rx_pin_ctrl(index_sel, en);
}

/**
 *  @brief To enable or disable I2S tx1 and tx2 pin.
 *
 *  @param[in] index_sel The I2S index. It can be 0 or 1.
 *  @param[in] en  Enable control: 0 is disable, 1 is enable.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_i2s_5p1_pin_ctrl(i2s_index_sel_t index_sel, BOOL en)
{
	return hal_i2s_stubs.hal_i2s_5p1_pin_ctrl(index_sel, en);
}

/**
 *  @brief Set the I2S pin mux for the application.
 *
 *  @param[in]  pi2s_adapter The I2S adapter.
 *
 *  @returns void
 */
void hal_i2s_app_pin_ctrl(hal_i2s_adapter_t *pi2s_adapter)
{
	hal_i2s_stubs.hal_i2s_app_pin_ctrl(pi2s_adapter);
}

/**
 *  @brief Control the I2S bus and hardware clock.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] i2s_func_en  Enable control: 0 is disable, 1 is enable.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_i2s_func_ctrl(hal_i2s_adapter_t *pi2s_adapter, BOOL i2s_func_en)
{
	return hal_i2s_stubs.hal_i2s_func_ctrl(pi2s_adapter, i2s_func_en);
}

/**
 *  @brief Initialize the I2S hardware and turn on the I2S.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_i2s_init(hal_i2s_adapter_t *pi2s_adapter)
{
	pi2s_adapter->dcache_clean_by_addr = hal_cache_stubs.dcache_clean_by_addr;
	pi2s_adapter->dcache_invalidate_by_addr = hal_cache_stubs.dcache_invalidate_by_addr;

	return hal_i2s_stubs.hal_i2s_init(pi2s_adapter);
}

/**
 *  @brief De-initialize of the I2S hardware and turn off the I2S.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *
 *  @returns void
 */
void hal_i2s_deinit(hal_i2s_adapter_t *pi2s_adapter)
{
	hal_i2s_stubs.hal_i2s_deinit(pi2s_adapter);
}

/**
 *  @brief To enter a critical section of code, mainly it
 *         disable I2S interrupt to prevent race condition.
 *
 *  @returns void
 */
void hal_i2s_enter_critical(void)
{
	hal_i2s_stubs.hal_i2s_enter_critical();
}

/**
 *  @brief To exit a critical code section, it will re-enable the I2S interrupt
 *         only when the exiting critical section is the top level.
 *
 *  @returns void
 */
void hal_i2s_exit_critical(void)
{
	hal_i2s_stubs.hal_i2s_exit_critical();
}

/**
 *  @brief Set the I2S parameter.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] psetting The I2S parameter.
 *                      i2s_burst_size - Burst Size for DMA.
 *                      i2s_master - Master or Slave mode.
 *                      i2s_word_len - Word length 16 or 24bits.
 *                      i2s_ch_num - Channel number mono or stereo.
 *                      i2s_page_num - Page number 2~4.
 *                      i2s_page_size - Page Size 1~4096 word.
 *                      i2s_rate - Sample rate.
 *                      i2s_trx_act - Conrtol the tx and rx.
 *                      i2s_byte_swap - Make the data do the byte switch.
 *                      i2s_sck_inv - Invert SCK.
 *                      i2s_ws_swap - Control whether the data appear in "right" or "left" phase of WS clock.
 *                      i2s_format - Interface format.
 *                      i2s_loop_back - Control the loopback mode.
 *                      i2s_edge_sw - Chose to send data at the negative edge or positive edge of SCK.
 *                      i2s_tx_intr_msk - Tx interrupt mask.
 *                      i2s_rx_intr_msk - Rx interrupt mask.
 *
 *  @returns void
 */
void hal_i2s_set_parameter(hal_i2s_adapter_t *pi2s_adapter, hal_i2s_def_setting_t *psetting)
{
	hal_i2s_stubs.hal_i2s_set_parameter(pi2s_adapter, psetting);
}

/**
 *  @brief Set the I2S sample rate.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] i2s_sample_rate Sample rate.
 *
 *  @returns void
 */
void hal_i2s_set_rate(hal_i2s_adapter_t *pi2s_adapter, i2s_sample_rate_t i2s_sample_rate)
{
	hal_i2s_stubs.hal_i2s_set_rate(pi2s_adapter, i2s_sample_rate);
}

/**
 *  @brief Set the I2S buffer.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] i2s_page_size This parameter must be set to a value in the 4~16384 bytes range.
 *  @param[in] i2s_page_num This parameter must be set to a value in the 2~4 range.
 *
 *  @returns void
 */
void hal_i2s_set_dma_buf(hal_i2s_adapter_t *pi2s_adapter, u16 i2s_page_size, i2s_page_num_t i2s_page_num)
{
	hal_i2s_stubs.hal_i2s_set_dma_buf(pi2s_adapter, i2s_page_size, i2s_page_num);
}

/**
 *  @brief Get the current tx page address.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *
 *  @returns The address of current tx page or NULL.
 */
u8 hal_i2s_get_tx_page(hal_i2s_adapter_t *pi2s_adapter)
{
	return hal_i2s_stubs.hal_i2s_get_tx_page(pi2s_adapter);
}

/**
 *  @brief Get the current rx page address.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *
 *  @returns The address of current rx page or NULL.
 */
u8 hal_i2s_get_rx_page(hal_i2s_adapter_t *pi2s_adapter)
{
	return hal_i2s_stubs.hal_i2s_get_rx_page(pi2s_adapter);
}

/**
 *  @brief Set the current tx page own.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] page_idx The page index.
 *
 *  @returns void
 */
void hal_i2s_page_send(hal_i2s_adapter_t *pi2s_adapter, u8 page_idx)
{
	hal_i2s_stubs.hal_i2s_page_send(pi2s_adapter, page_idx);
}

/**
 *  @brief Set the current rx page own.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *
 *  @return     HAL_NOT_READY
 *  @return     HAL_OK
 */
HAL_Status hal_i2s_page_recv(hal_i2s_adapter_t *pi2s_adapter)
{
	return hal_i2s_stubs.hal_i2s_page_recv(pi2s_adapter);
}

/**
 *  @brief Clean all page own of tx and rx.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *
 *  @returns void
 */
void hal_i2s_clear_all_own_bit(hal_i2s_adapter_t *pi2s_adapter)
{
	hal_i2s_stubs.hal_i2s_clear_all_own_bit(pi2s_adapter);
}

/**
 *  @brief Reset the I2S.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *
 *  @returns void
 */
void hal_i2s_reset(hal_i2s_adapter_t *pi2s_adapter)
{
	hal_i2s_stubs.hal_i2s_reset(pi2s_adapter);
}

/**
 *  @brief Reset and disable the I2S.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *
 *  @returns void
 */
void hal_i2s_reset_and_disable(hal_i2s_adapter_t *pi2s_adapter)
{
	hal_i2s_stubs.hal_i2s_reset_and_disable(pi2s_adapter);
}

/**
 *  @brief Enable or disable the I2S.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_i2s_en_ctrl(hal_i2s_adapter_t *pi2s_adapter, BOOL en)
{
	hal_i2s_stubs.hal_i2s_en_ctrl(pi2s_adapter, en);
}

/**
 *  @brief Clean the I2S interrupt status of enabling the interrupt.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *
 *  @returns void
 */
void hal_i2s_clr_intr(hal_i2s_adapter_t *pi2s_adapter)
{
	hal_i2s_stubs.hal_i2s_clr_intr(pi2s_adapter);
}

/**
 *  @brief Clean all I2S interrupt status.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *
 *  @returns void
 */
void hal_i2s_clr_all_intr(hal_i2s_adapter_t *pi2s_adapter)
{
	hal_i2s_stubs.hal_i2s_clr_all_intr(pi2s_adapter);
}

/**
 *  @brief Control the I2S interupt event by tx and rx mask.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] i2s_tx_intr_msk Tx interrupt mask.
 *  @param[in] i2s_rx_intr_msk Rx interrupt mask.
 *
 *  @returns void
 */
void hal_i2s_intr_ctrl(hal_i2s_adapter_t *pi2s_adapter, i2s_tx_imr_t i2s_tx_intr_msk, i2s_rx_imr_t i2s_rx_intr_msk)
{
	hal_i2s_stubs.hal_i2s_intr_ctrl(pi2s_adapter, i2s_tx_intr_msk, i2s_rx_intr_msk);
}

/**
 *  @brief Make the rx memory invalidate D-Cache.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *
 *  @returns void
 */
void hal_i2s_read_memory_cache_invalidate(hal_i2s_adapter_t *pi2s_adapter)
{
	hal_i2s_stubs.hal_i2s_read_memory_cache_invalidate(pi2s_adapter);
}

/** @} */ /* End of group hs_hal_i2s */

#endif

