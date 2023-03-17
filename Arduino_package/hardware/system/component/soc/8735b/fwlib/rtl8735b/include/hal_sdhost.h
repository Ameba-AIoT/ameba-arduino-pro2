/**************************************************************************//**
 * @file    hal_sdhost.h
 * @brief   The HAL API declaration for SD Host controller
 * @version V1.00
 * @date    2021-10-21
 *
 * @note
 *
 ******************************************************************************
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
 ******************************************************************************/
#ifndef _HAL_SDHOST_H_
#define _HAL_SDHOST_H_
#include "cmsis.h"
#include "static_assert.h"

#ifdef  __cplusplus
extern "C"
{
#endif

/**
 * @defgroup hal_sdhost SD HOST
 * @ingroup 8735b_hal
 * @brief The SD Host HAL APIs for user application to control the SD Host hardware.
 */

/**
 * @addtogroup hal_sdhost
 * @{
 */

/**
  \brief  Defines the CMD/DATA output timing for SD2.0 mode.
*/
enum sdhost_sd20_tx_timing_e {
	SD20_TX_TIMING_DEFAULT      = 0,
	SD20_TX_TIMING_SHIFT        = 1
};

/**
  \brief  Defines SD CID (Card IDentification) register format.
*/
typedef struct hal_sdhost_cid {
	u8 crc;                 ///< CRC7 checksum of reset of the struct
	u8 manufact_date[2];    ///< Manufacturing date
	u8 serial_num[4];       ///< Serial number
	u8 revision[1];         ///< Revision
	u8 product_name[5];     ///< Product Name
	u8 oem_id[2];           ///< OEM/Application ID
	u8 manufact_id[1];      ///< Manufacturing ID
} hal_sdhost_cid_t;

/// @cond _
STATIC_ASSERT(sizeof(hal_sdhost_cid_t) == SD_CID_LEN, sd_cid_sz);
/// @endcond

/**
 *  @brief Register IRQ of the SD host controller.
 *
 *  @param[in]  irq_handler The SD host irq handler
 *
 *  @returns    void.
 */
static inline
void hal_sdhost_irq_reg(irq_handler_t irq_handler)
{
	hal_sdhost_stubs.hal_sdhost_irq_reg(irq_handler);
}


/**
 *  @brief Unregister IRQ of the SD host controller.
 *
 *  @returns    void.
 */
static inline
void hal_sdhost_irq_unreg(void)
{
	hal_sdhost_stubs.hal_sdhost_irq_unreg();
}

/**
 *  @brief Read data from the SD card.
 *
 *  @param[in]  psdhost_adapter The SD host HAL adapter.
 *  @param[in]  sd_blk_idx The start block address to begin reading.
 *  @param[in]  blk_cnt Data size in blocks.
 *  @param[in]  rbuf_32align The buffer to store data (must be 32-byte alignment).
 *
 *  @returns    The result status.
 */
static inline
hal_status_t hal_sdhost_read_data(hal_sdhost_adapter_t *psdhost_adapter, u32 sd_blk_idx, u16 blk_cnt, u8 *rbuf_32align)
{
	return hal_sdhost_stubs.hal_sdhost_read_data(psdhost_adapter, sd_blk_idx, blk_cnt, rbuf_32align);
}

/**
 *  @brief Write data to the SD card.
 *
 *  @param[in]  psdhost_adapter The SD host HAL adapter.
 *  @param[in]  sd_blk_idx The start block address to begin writing.
 *  @param[in]  blk_cnt Data size in blocks.
 *  @param[in]  wbuf_32align The buffer stored data (must be 32-byte alignment).
 *
 *  @returns    The result status.
 */
static inline
hal_status_t hal_sdhost_write_data(hal_sdhost_adapter_t *psdhost_adapter, u32 sd_blk_idx, u16 blk_cnt, const u8 *wbuf_32align)
{
	return hal_sdhost_stubs.hal_sdhost_write_data(psdhost_adapter, sd_blk_idx, blk_cnt, wbuf_32align);
}

/**
 *  @brief Erase data blocks in the SD card.
 *
 *  @param[in]  psdhost_adapter The SD host HAL adapter.
 *  @param[in]  start_blk_idx The start block address to be erased.
 *  @param[in]  end_blk_idx The last block to be erased (Included).
 *
 *  @returns    The result status.
 */
static inline
hal_status_t hal_sdhost_erase(hal_sdhost_adapter_t *psdhost_adapter, u32 start_blk_idx, u32 end_blk_idx)
{
	return hal_sdhost_stubs.hal_sdhost_erase(psdhost_adapter, start_blk_idx, end_blk_idx);
}


/**
 *  @brief Stop the SD bus transmission.
 *
 *  @param[in]  psdhost_adapter The SD host HAL adapter.
 *
 *  @returns    The result status.
 */
static inline
hal_status_t hal_sdhost_stop_transmission(hal_sdhost_adapter_t *psdhost_adapter)
{
	return hal_sdhost_stubs.hal_sdhost_stop_transmission(psdhost_adapter);
}



/**
 *  @brief Get the card status of the SD card.
 *
 *  @param[in]  psdhost_adapter The SD host HAL adapter.
 *  @param[out] status_buf Return card status if not NULL.
 *
 *  @returns    The result status.
 */
static inline
hal_status_t hal_sdhost_get_card_status(hal_sdhost_adapter_t *psdhost_adapter,
										hal_sdhost_card_stat_t *status_buf)
{
	return hal_sdhost_stubs.hal_sdhost_get_card_status(psdhost_adapter, status_buf);
}


/**
 *  @brief Get the SD status from the SD card.
 *
 *  @param[in]  psdhost_adapter The SD host HAL adapter.
 *  @param[out]  sd_stat Return the SD status if not NULL.
 *
 *  @returns    The result status.
 */
static inline
hal_status_t hal_sdhost_get_sd_status(hal_sdhost_adapter_t *psdhost_adapter, hal_sdhost_sd_stat_t *sd_stat)
{
	return hal_sdhost_stubs.hal_sdhost_get_sd_status(psdhost_adapter, sd_stat);
}


/**
 *  @brief Get the SCR (Card Configuration Register) from the SD card.
 *
 *  @param[in]  psdhost_adapter The SD host HAL adapter.
 *  @param[out] scr Return the SCR content if not NULL.
 *
 *  @returns    The result status.
 */
static inline
hal_status_t hal_sdhost_get_scr(hal_sdhost_adapter_t *psdhost_adapter, hal_sdhost_scr_t *scr)
{
	return hal_sdhost_stubs.hal_sdhost_get_scr(psdhost_adapter, scr);
}


/**
 *  @brief Get the current signal voltage level.
 *
 *  @param[in]  psdhost_adapter The SD host HAL adapter.
 *
 *  @returns    The signal voltage level (1: 1.8V, 0: 3.3V).
 */
static inline
u8 hal_sdhost_get_curr_signal_level(hal_sdhost_adapter_t *psdhost_adapter)
{
	return hal_sdhost_stubs.hal_sdhost_get_curr_signal_level(psdhost_adapter);
}


/**
 *  @brief Get the speed modes supported by the card.
 *
 *  @param[in]  psdhost_adapter The SD host HAL adapter.
 *  @param[out] speeds Bitwise-OR result of every supported mode.
 *
 *  @returns    The result status.
 */
static inline
hal_status_t hal_sdhost_get_supported_speed(hal_sdhost_adapter_t *psdhost_adapter, hal_sdhost_speed_t *speeds)
{
	return hal_sdhost_stubs.hal_sdhost_get_supported_speed(psdhost_adapter, speeds);
}


/**
 *  @brief Hook a callback function for SD card insertion interrupt.
 *
 *  @param[in]  psdhost_adapter The SD host HAL adapter.
 *  @param[in]  pcallback The callback function.
 *  @param[in]  pdata The argument of the callback function.
 *
 *  @returns    void.
 */
static inline
void hal_sdhost_card_insert_hook(hal_sdhost_adapter_t *psdhost_adapter, sdhost_para_cb_t pcallback, void *pdata)
{
	hal_sdhost_stubs.hal_sdhost_card_insert_hook(psdhost_adapter, pcallback, pdata);
}


/**
 *  @brief Hook a callback function for SD card removal interrupt.
 *
 *  @param[in]  psdhost_adapter The SD host HAL adapter.
 *  @param[in]  pcallback The callback function.
 *  @param[in]  pdata The argument of the callback function.
 *
 *  @returns    void.
 */
static inline
void hal_sdhost_card_remove_hook(hal_sdhost_adapter_t *psdhost_adapter, sdhost_para_cb_t pcallback, void *pdata)
{
	hal_sdhost_stubs.hal_sdhost_card_remove_hook(psdhost_adapter, pcallback, pdata);
}


/**
 *  @brief Hook a callback function that will be called while waiting for card starts busy read/write.
 *         Use hal_sdhost_transfer_done_int_hook() to get informed when the operation finish.
 *
 *  @param[in]  psdhost_adapter The SD host HAL adapter.
 *  @param[in]  task_yield The callback function.
 *  @param[in]  pdata The argument for callback function.
 *
 *  @returns    void.
 */
static inline
void hal_sdhost_task_yield_hook(hal_sdhost_adapter_t *psdhost_adapter, sdhost_para_cb_t task_yield, void *pdata)
{
	hal_sdhost_stubs.hal_sdhost_task_yield_hook(psdhost_adapter, task_yield, pdata);
}

/**
 *  @brief Hook a callback function when read/write finish.
 *
 *  @param[in]  psdhost_adapter The SD host HAL adapter.
 *  @param[in]  pcallback The callback function.
 *  @param[in]  pdata The argument for callback function.
 *
 *  @returns    void.
 */
static inline
void hal_sdhost_transfer_done_int_hook(hal_sdhost_adapter_t *psdhost_adapter, sdhost_para_cb_t pcallback, void *pdata)
{
	hal_sdhost_stubs.hal_sdhost_transfer_done_int_hook(psdhost_adapter, pcallback, pdata);
}

/**
 *  @brief Force card identification keep in 3.3V signal.
 *         This should be used before hal_sdhost_init_card().
 *
 *  @param[in]  adpt The SD host HAL adapter.
 *
 *  @returns    void.
 */
static inline
void hal_sdhost_force33v(hal_sdhost_adapter_t *adpt)
{
	adpt->force_33v = 1;
}

/**
 *  @brief Initialize the SD host controller and the adapter.
 *         This should be called before any other SDHOST APIs.
 *
 *  @param[in]  psdhost_adapter The SD host HAL adapter.
 *
 *  @returns    The result status.
 */
hal_status_t hal_sdhost_init_host(hal_sdhost_adapter_t *psdhost_adapter);


/**
 *  @brief Initialize and identify the SD memory card.
 *
 *  @param[in]  psdhost_adapter The SD host HAL adapter.
 *
 *  @returns    The result status.
 */
static inline
hal_status_t hal_sdhost_init_card(hal_sdhost_adapter_t *psdhost_adapter)
{
	return hal_sdhost_stubs.hal_sdhost_init_card(psdhost_adapter);
}


/**
 *  @brief Switch the current SD bus speed to the specified one.
 *
 *  @param[in]  psdhost_adapter The SD host HAL adapter.
 *  @param[in]  speed The specified bus speed.
 *
 *  @returns    The result status.
 */
static inline
hal_status_t hal_sdhost_switch_bus_speed(hal_sdhost_adapter_t *psdhost_adapter, hal_sdhost_speed_t speed)
{
	return hal_sdhost_stubs.hal_sdhost_switch_bus_speed(psdhost_adapter, speed);
}

/**
 *  @brief De-initialize the SD host controller and the adapter.
 *
 *  @param[in]  psdhost_adapter The SD host HAL adapter.
 *
 *  @returns    void.
 */
static inline
void hal_sdhost_deinit(hal_sdhost_adapter_t *psdhost_adapter)
{
	return hal_sdhost_stubs.hal_sdhost_deinit(psdhost_adapter);
}

/**
 *  @brief Tune the clock phase shift to the best phase (only for SDR50 mode).
 *         High speed mode requires decent clock phases to tolerate transfer error.
 *         To test read/write golden pattern, one block should be used for tuning.
 *         The data will be saved and restored.
 *
 *  @param[in]  adpt The SD host HAL adapter.
 *  @param[in]  buf_3blk_32align The buffer to store backup data, required at least 3 block size and 32-byte aligned.
 *  @param[in]  buf_size The size of the backup data buffer.
 *  @param[in]  tuning_blk SD block address will be used for tuning (at risk of data lost).
 *
 *  @returns    The result status.
 */
static inline
hal_status_t hal_sdhost_clk_finetune(hal_sdhost_adapter_t *adpt, u8 *buf_3blk_32align, u32 buf_size, u32 tuning_blk)
{
	return hal_sdhost_stubs.hal_sdhost_clk_finetune(adpt, buf_3blk_32align, buf_size, tuning_blk);
}

/**
 *  @brief Get the CSD (Card Specific Data) register content from the SD card.
 *
 *  @param[in]  adpt The SD host HAL adapter.
 *  @param[out] csd The buffer to store output.
 *
 *  @returns    The result.
 */
hal_status_t hal_sdhost_get_csd(hal_sdhost_adapter_t *adpt, hal_sdhost_csd_t *csd);


/**
 *  @brief Get CID (Card IDentification) register content from the SD card.
 *
 *  @param[in]  adpt The SD host HAL adapter.
 *  @param[out] cid The buffer to store output.
 *
 *  @returns    The result.
 */
hal_status_t hal_sdhost_get_cid(hal_sdhost_adapter_t *adpt, hal_sdhost_cid_t *cid);


static inline
hal_status_t hal_sdhost_switch_freq(hal_sdhost_adapter_t *adpt, hal_sdhost_freq_t freq)
{
	return hal_sdhost_stubs.hal_sdhost_switch_freq(adpt, freq);
}


/**
 *  @brief Adjust the CMD/DATA output timing for SD2.0 mode.
 *
 *  @param[in]  psdhost_adapter The SD host HAL adapter.
 *  @param[in]  timing SD20_TX_TIMING_DEFAULT: output at falling edge of SDCLK
 *                                 SD20_TX_TIMING_SHIFT: output is ahead by 1/4 SDCLK
 *
 *  @returns    The result status.
 */
hal_status_t hal_sdhost_adj_sd20_tx_timing(hal_sdhost_adapter_t *psdhost_adapter, u8 timing);


/** @} */ /* End of group hal_sdhost */

#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_SDHOST_H_"

