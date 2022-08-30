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
 * @addtogroup hal_sdhost HAL SDHOST
 * @{
 *
 *  The SD Host HAL RAM APIs for user application to control the SD Host hardware.
 *
 */


/**
  \brief  Defines SD CID register content (check SD spec for detail).
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
 *  @brief To reg irq of the SD host controller.
 *
 *  @param[in]  irq_handler The SD host irq handler
 *
 *  @returns    void.
 */
__STATIC_FORCEINLINE
void hal_sdhost_irq_reg(irq_handler_t irq_handler)
{
	hal_sdhost_stubs.hal_sdhost_irq_reg(irq_handler);
}


/**
 *  @brief To unreg irq of the SD host controller.
 *
 *  @returns    void.
 */
__STATIC_FORCEINLINE
void hal_sdhost_irq_unreg(void)
{
	hal_sdhost_stubs.hal_sdhost_irq_unreg();
}

/**
 *  @brief To read data from the SD card.
 *
 *  @param[in]  psdhost_adapter The SD host HAL adapter.
 *  @param[in]  sd_blk_idx The start address to begin reading from the card.
 *  @param[in]  blk_cnt The block count.
 *  @param[in]  rbuf_32align The buffer to read data blocks (must be 32-Byte alignment).
 *
 *  @returns    The result.
 */
__STATIC_FORCEINLINE
hal_status_t hal_sdhost_read_data(hal_sdhost_adapter_t *psdhost_adapter, u32 sd_blk_idx, u16 blk_cnt, u8 *rbuf_32align)
{
	return hal_sdhost_stubs.hal_sdhost_read_data(psdhost_adapter, sd_blk_idx, blk_cnt, rbuf_32align);
}

/**
 *  @brief To write data to the SD card.
 *
 *  @param[in]  psdhost_adapter The SD host HAL adapter.
 *  @param[in]  sd_blk_idx The start address to begin writing to the card.
 *  @param[in]  blk_cnt The block count.
 *  @param[in]  wbuf_32align The buffer to write data blocks (must be 32-Byte alignment).
 *
 *  @returns    The result.
 */
__STATIC_FORCEINLINE
hal_status_t hal_sdhost_write_data(hal_sdhost_adapter_t *psdhost_adapter, u32 sd_blk_idx, u16 blk_cnt, const u8 *wbuf_32align)
{
	return hal_sdhost_stubs.hal_sdhost_write_data(psdhost_adapter, sd_blk_idx, blk_cnt, wbuf_32align);
}

/**
 *  @brief To erase data in the SD card.
 *
 *  @param[in]  psdhost_adapter The SD host HAL adapter.
 *  @param[in]  start_blk_idx The start block to erase.
 *  @param[in]  end_blk_idx The end block to erase.
 *
 *  @returns    The result.
 */
__STATIC_FORCEINLINE
hal_status_t hal_sdhost_erase(hal_sdhost_adapter_t *psdhost_adapter, u32 start_blk_idx, u32 end_blk_idx)
{
	return hal_sdhost_stubs.hal_sdhost_erase(psdhost_adapter, start_blk_idx, end_blk_idx);
}


/**
 *  @brief To stop the SD bus transmission.
 *
 *  @param[in]  psdhost_adapter The SD host HAL adapter.
 *
 *  @returns    The result.
 */
__STATIC_FORCEINLINE
hal_status_t hal_sdhost_stop_transmission(hal_sdhost_adapter_t *psdhost_adapter)
{
	return hal_sdhost_stubs.hal_sdhost_stop_transmission(psdhost_adapter);
}



/**
 *  @brief To get the current state of the SD card.
 *
 *  @param[in]  psdhost_adapter The SD host HAL adapter.
 *  @param[out] status_buf Return card status register if not NULL.
 *
 *  @returns    The result.
 */
__STATIC_FORCEINLINE
hal_status_t hal_sdhost_get_card_status(hal_sdhost_adapter_t *psdhost_adapter,
										hal_sdhost_card_stat_t *status_buf)
{
	return hal_sdhost_stubs.hal_sdhost_get_card_status(psdhost_adapter, status_buf);
}


/**
 *  @brief To get the SD status from the SD card.
 *
 *  @param[in]  psdhost_adapter The SD host HAL adapter.
 *  @param[out]  sd_stat Return the SD status if not NULL.
 *
 *  @returns    The result.
 */
__STATIC_FORCEINLINE
hal_status_t hal_sdhost_get_sd_status(hal_sdhost_adapter_t *psdhost_adapter, hal_sdhost_sd_stat_t *sd_stat)
{
	return hal_sdhost_stubs.hal_sdhost_get_sd_status(psdhost_adapter, sd_stat);
}


/**
 *  @brief To get the SCR register from the SD card.
 *
 *  @param[in]  psdhost_adapter The SD host HAL adapter.
 *  @param[out] scr Return the SCR content if not NULL.
 *
 *  @returns    The result.
 */
__STATIC_FORCEINLINE
hal_status_t hal_sdhost_get_scr(hal_sdhost_adapter_t *psdhost_adapter, hal_sdhost_scr_t *scr)
{
	return hal_sdhost_stubs.hal_sdhost_get_scr(psdhost_adapter, scr);
}


/**
 *  @brief To get the current signaling level.
 *
 *  @param[in]  psdhost_adapter The SD host HAL adapter.
 *
 *  @returns    The signaling level (1: 1.8V, 0: 3.3V).
 */
__STATIC_FORCEINLINE
u8 hal_sdhost_get_curr_signal_level(hal_sdhost_adapter_t *psdhost_adapter)
{
	return hal_sdhost_stubs.hal_sdhost_get_curr_signal_level(psdhost_adapter);
}


/**
 *  @brief To get the speed mode supported by the card.
 *
 *  @param[in]  psdhost_adapter The SD host HAL adapter.
 *  @param[out] speeds Bitwise-OR result of every supported mode in current signal level.
 *
 *  @returns    The result.
 */
__STATIC_FORCEINLINE
hal_status_t hal_sdhost_get_supported_speed(hal_sdhost_adapter_t *psdhost_adapter, hal_sdhost_speed_t *speeds)
{
	return hal_sdhost_stubs.hal_sdhost_get_supported_speed(psdhost_adapter, speeds);
}


/**
 *  @brief To hook a callback function for SD card insertion interrupt.
 *
 *  @param[in]  psdhost_adapter The SD host HAL adapter.
 *  @param[in]  pcallback The callback function.
 *  @param[in]  pdata The argument of the callback function.
 *
 *  @returns    void.
 */
__STATIC_FORCEINLINE
void hal_sdhost_card_insert_hook(hal_sdhost_adapter_t *psdhost_adapter, sdhost_para_cb_t pcallback, void *pdata)
{
	hal_sdhost_stubs.hal_sdhost_card_insert_hook(psdhost_adapter, pcallback, pdata);
}


/**
 *  @brief To hook a callback function for SD card removal interrupt.
 *
 *  @param[in]  psdhost_adapter The SD host HAL adapter.
 *  @param[in]  pcallback The callback function.
 *  @param[in]  pdata The argument of the callback function.
 *
 *  @returns    void.
 */
__STATIC_FORCEINLINE
void hal_sdhost_card_remove_hook(hal_sdhost_adapter_t *psdhost_adapter, sdhost_para_cb_t pcallback, void *pdata)
{
	hal_sdhost_stubs.hal_sdhost_card_remove_hook(psdhost_adapter, pcallback, pdata);
}


/**
 *  @brief To hook a callback function that will be called while waiting for card busy read/write.
 *         Use hal_sdhost_transfer_done_int_hook() to get informed when read/write finish
 *
 *  @param[in]  psdhost_adapter The SD host HAL adapter.
 *  @param[in]  task_yield The callback function.
 *  @param[in]  pdata The argument for callback function.
 *
 *  @returns    void.
 */
__STATIC_FORCEINLINE
void hal_sdhost_task_yield_hook(hal_sdhost_adapter_t *psdhost_adapter, sdhost_para_cb_t task_yield, void *pdata)
{
	hal_sdhost_stubs.hal_sdhost_task_yield_hook(psdhost_adapter, task_yield, pdata);
}

/**
 *  @brief To hook a callback function when read/write finish.
 *
 *  @param[in]  psdhost_adapter The SD host HAL adapter.
 *  @param[in]  pcallback The callback function.
 *  @param[in]  pdata The argument for callback function.
 *
 *  @returns    void.
 */
__STATIC_FORCEINLINE
void hal_sdhost_transfer_done_int_hook(hal_sdhost_adapter_t *psdhost_adapter, sdhost_para_cb_t pcallback, void *pdata)
{
	hal_sdhost_stubs.hal_sdhost_transfer_done_int_hook(psdhost_adapter, pcallback, pdata);
}

/**
 *  @brief To force card identification with 3.3V.
 *         This should be used before hal_sdhost_init_card().
 *
 *  @param[in]  adpt The SD host HAL adapter.
 *
 *  @returns    void.
 */
__STATIC_FORCEINLINE
void hal_sdhost_force33v(hal_sdhost_adapter_t *adpt)
{
	adpt->force_33v = 1;
}

/**
 *  @brief To initialize the SD host controller and the adapter.
 *         This should be called before any other API.
 *
 *  @param[in]  psdhost_adapter The SD host HAL adapter.
 *
 *  @returns    The result.
 */
hal_status_t hal_sdhost_init_host(hal_sdhost_adapter_t *psdhost_adapter);


/**
 *  @brief To initialize the SD memory card.
 *
 *  @param[in]  psdhost_adapter The SD host HAL adapter.
 *
 *  @returns    The result.
 */
__STATIC_FORCEINLINE
hal_status_t hal_sdhost_init_card(hal_sdhost_adapter_t *psdhost_adapter)
{
	return hal_sdhost_stubs.hal_sdhost_init_card(psdhost_adapter);
}


/**
 *  @brief To switch the SD bus speed.
 *
 *  @param[in]  psdhost_adapter The SD host HAL adapter.
 *  @param[in]  speed The specified bus speed.
 *
 *  @returns    The result.
 */
__STATIC_FORCEINLINE
hal_status_t hal_sdhost_switch_bus_speed(hal_sdhost_adapter_t *psdhost_adapter, hal_sdhost_speed_t speed)
{
	return hal_sdhost_stubs.hal_sdhost_switch_bus_speed(psdhost_adapter, speed);
}

/**
 *  @brief To de-initialize the SD host controller.
 *
 *  @param[in]  psdhost_adapter The SD host HAL adapter.
 *
 *  @returns    void.
 */
__STATIC_FORCEINLINE
void hal_sdhost_deinit(hal_sdhost_adapter_t *psdhost_adapter)
{
	return hal_sdhost_stubs.hal_sdhost_deinit(psdhost_adapter);
}

/**
 *  @brief To tune best clock phase for SDR50.
 *
 *  @param[in]  adpt The SD host HAL adapter.
 *  @param[in]  buf_3blk_32align The buffer to store temprary data, required at least 3 block size and 32-byte aligned.
 *  @param[in]  buf_size The size of buf_3blk_32align.
 *  @param[in]  tuning_blk SD block address will be used for tuning (data might lost).
 *
 *  @returns    The result.
 */
__STATIC_FORCEINLINE
hal_status_t hal_sdhost_clk_finetune(hal_sdhost_adapter_t *adpt, u8 *buf_3blk_32align, u32 buf_size, u32 tuning_blk)
{
	return hal_sdhost_stubs.hal_sdhost_clk_finetune(adpt, buf_3blk_32align, buf_size, tuning_blk);
}

/**
 *  @brief To get CSD register content from the SD card.
 *
 *  @param[in]  adpt The SD host HAL adapter.
 *  @param[out] csd The buffer to store output.
 *
 *  @returns    The result.
 */
hal_status_t hal_sdhost_get_csd(hal_sdhost_adapter_t *adpt, hal_sdhost_csd_t *csd);


/**
 *  @brief To get CID register content from the SD card.
 *
 *  @param[in]  adpt The SD host HAL adapter.
 *  @param[out] cid The buffer to store output.
 *
 *  @returns    The result.
 */
hal_status_t hal_sdhost_get_cid(hal_sdhost_adapter_t *adpt, hal_sdhost_cid_t *cid);

/** @} */ /* End of group hs_hal_sdhost_ */

#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_SDHOST_H_"

