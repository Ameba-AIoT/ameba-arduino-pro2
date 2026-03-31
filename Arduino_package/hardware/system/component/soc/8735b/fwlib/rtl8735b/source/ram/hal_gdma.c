/**************************************************************************//**
 * @file     hal_gdma.c
 * @brief    The GDMA RAM code function, including channel allocation functions.
 * @version  1.00
 * @date     2017-08-22
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

#include "hal.h"
#include "memory.h"

/**
 *   \addtogroup hal_gdma GDMA
 *   @{
 */

/**
 *   \brief The GDMA channel options, idle channels can be allocated to new transfers.
 */
const hal_gdma_chnl_t gdma_chnl_option[] = {
	{0, 0},
	{1, 0},
	{0, 1},
	{1, 1},
	{0, 2},
	{1, 2},
	{0, 3},
	{1, 3},
	{0, 4},
	{1, 4},
	{0, 5},
	{1, 5},
	{0xff, 0}   // end
};

/**
 *   \brief The GDMA channel options for multi-block transfer, idle channels can be allocated to new transfers.
 */
const hal_gdma_chnl_t gdma_multi_block_chnl_option[] = {
	{0, 4},
	{1, 4},
	{0, 5},
	{1, 5},
	{0xff, 0}   // end
};

/**
 *   \brief The GDMA multi-block transfer adaptors.
 *          The array contains four adaptors because only four channels support multi-block mode.
 */
multi_blk_adaptor_t multi_blk_adaptor[2][2] __ALIGNED(32);

/**
 *   \addtogroup hal_gdma_ram_func GDMA HAL RAM APIs
 *   \ingroup hal_gdma
 *   \brief The GDMA HAL APIs. Functions across secure and non-secure domains are implemented here.
 *   The rest of functions become an interface between API functions and ROM codes.
 *@{
 */


/** \brief Description of hal_gdma_memcpy_init
 *
 *    hal_gdma_memcpy_init is used to initial GDMA before initiating memory copy transfer by GDMA.
 *
 *   \param phal_gdma_adaptor_t phal_gdma_adaptor:      The pointer of GDMA adaptor.
 *
 *   \return BOOL: TRUE: Initialization succeeds, False: Initialization fails.
 */
BOOL hal_gdma_memcpy_init(phal_gdma_adaptor_t phal_gdma_adaptor)
{
	memset((void *)phal_gdma_adaptor, 0, sizeof(hal_gdma_adaptor_t));

	phal_gdma_adaptor->gdma_ctl.tt_fc = TTFCMemToMem;
	phal_gdma_adaptor->gdma_isr_type = (TransferType | ErrType);
	phal_gdma_adaptor->gdma_ctl.int_en      = 1;
	phal_gdma_adaptor->gdma_ctl.sinc = IncType;
	phal_gdma_adaptor->gdma_ctl.dinc = IncType;
	phal_gdma_adaptor->busy = 0;
	phal_gdma_adaptor->have_chnl = 0;

	if (hal_gdma_chnl_alloc(phal_gdma_adaptor, MultiBlkDis) != HAL_OK) {
		DBG_GDMA_ERR("Cannot Allocate Channel !\n");
		return _FALSE;
	} else {
		hal_gdma_chnl_init(phal_gdma_adaptor);
	}

	hal_gdma_irq_reg(phal_gdma_adaptor, (irq_handler_t) hal_gdma_stubs.hal_gdma_memcpy_irq_handler, phal_gdma_adaptor);
	return _TRUE;
}

/** \brief Description of hal_gdma_memcpy_deinit
 *
 *    hal_gdma_memcpy_deinit is used to de-initialize GDMA after transfer is complete.
 *
 *   \param phal_gdma_adaptor_t phal_gdma_adaptor:      The pointer of GDMA adaptor.
 *
 *   \return void.
 */
void hal_gdma_memcpy_deinit(phal_gdma_adaptor_t phal_gdma_adaptor)
{
	phal_gdma_adaptor->pgdma_ch_lli = NULL;
	hal_gdma_chnl_free(phal_gdma_adaptor);
}

/** \brief Description of hal_gdma_memcpy
 *
 *    hal_gdma_memcpy is used to start memory copy by GDMA.
 *
 *   \param phal_gdma_adaptor_t phal_gdma_adaptor:      The pointer of GDMA adaptor.
 *   \param void *pdest     :      The destination address.
 *   \param void *psrc      :      The source address.
 *   \param u32 len         :      The transfer length, the unit is byte.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_gdma_memcpy(phal_gdma_adaptor_t phal_gdma_adaptor, void *pdest, void *psrc, u32 len)
{
	u8 multi_block_en = MultiBlkDis;

	if (phal_gdma_adaptor->busy) {
		DBG_GDMA_ERR("hal_gdma_memcpy : GDMA is busy\r\n");
		return HAL_ERR_PARA;
	}

	hal_gdma_memcpy_config(phal_gdma_adaptor, pdest, psrc, len);

	if (phal_gdma_adaptor->gdma_ctl.block_size > MAX_DMA_BLOCK_SIZE) {
		multi_block_en = MultiBlkEn;
		if (phal_gdma_adaptor->ch_num < MIN_MULTI_CHNL_NUM) {
			if (hal_gdma_chnl_alloc(phal_gdma_adaptor, multi_block_en) != HAL_OK) {
				DBG_GDMA_ERR("Cannot Allocate Channel !\n");
				return HAL_ERR_HW;
			} else {
				hal_gdma_chnl_init(phal_gdma_adaptor);
			}

			hal_gdma_irq_reg(phal_gdma_adaptor, (irq_handler_t) hal_gdma_stubs.hal_gdma_memcpy_irq_handler,
							 phal_gdma_adaptor);
		}
	}

	if (phal_gdma_adaptor->dcache_clean_by_addr != NULL) {
		phal_gdma_adaptor->dcache_clean_by_addr((uint32_t *) psrc, (int32_t) len);
	}

	hal_gdma_transfer_start(phal_gdma_adaptor, multi_block_en);

	return HAL_OK;
}

hal_status_t hal_gdma_hs_memcpy(phal_gdma_adaptor_t phal_gdma_adaptor, void *pdest, void *psrc, u32 len)
{
	u8 multi_block_en = MultiBlkDis;
	u8 hs_gdma_index = 0x0;
	u8 hs_gdma_chnl = 0x5;
	u8 multi_blk_index = 0;
	u8 multi_blk_chnl = 0;

	if (phal_gdma_adaptor->busy) {
		DBG_GDMA_ERR("hal_gdma_hs_memcpy : GDMA is busy\r\n");
		return HAL_ERR_PARA;
	}

	hal_gdma_memcpy_config(phal_gdma_adaptor, pdest, psrc, len);
	if (((phal_gdma_adaptor->gdma_index == hs_gdma_index) && (phal_gdma_adaptor->ch_num != hs_gdma_chnl))
		|| (phal_gdma_adaptor->gdma_index != hs_gdma_index)) {

		/*Check hs-channel is available*/
		if (hal_gdma_chnl_register(hs_gdma_index, hs_gdma_chnl) == HAL_OK) {

			/*Release old channel*/
			hal_gdma_chnl_free(phal_gdma_adaptor);
			phal_gdma_adaptor->gdma_index = hs_gdma_index;
			phal_gdma_adaptor->ch_num = hs_gdma_chnl;

			/*Initialize new channel*/
			hal_gdma_chnl_init(phal_gdma_adaptor);
			phal_gdma_adaptor->have_chnl = 1;

			hal_gdma_irq_reg(phal_gdma_adaptor, (irq_handler_t) hal_gdma_stubs.hal_gdma_memcpy_irq_handler,
							 phal_gdma_adaptor);
		} else {
			DBG_GDMA_ERR("Cannot Allocate HS Channel,  Use Original Channel to Transfer!\n");
		}
	}
	if (phal_gdma_adaptor->gdma_ctl.block_size > MAX_DMA_BLOCK_SIZE) {
		multi_block_en = MultiBlkEn;
		multi_blk_index = phal_gdma_adaptor->gdma_index;
		multi_blk_chnl = phal_gdma_adaptor->ch_num - MIN_MULTI_CHNL_NUM;
		phal_gdma_adaptor->pgdma_ch_lli = (pgdma_ch_lli_t)&multi_blk_adaptor[multi_blk_index][multi_blk_chnl];
	}

	if (phal_gdma_adaptor->dcache_clean_by_addr != NULL) {
		phal_gdma_adaptor->dcache_clean_by_addr((uint32_t *) psrc, (int32_t) len);
	}

	hal_gdma_transfer_start(phal_gdma_adaptor, multi_block_en);

	return HAL_OK;
}


/** \brief Description of hal_gdma_multiblk_memcpy
 *
 *    hal_gdma_multiblk_memcpy is used to initiate GDMA multi-block transfer.
 *    The maximum block number is 16, users can assign addresses & lengths for each block.
 *
 *   \param phal_gdma_adaptor_t phal_gdma_adaptor   :      The pointer of GDMA adaptor.
 *   \param phal_gdma_block_t phal_gdma_block       :      The pointer of gdma block struct.
 *   \param u8 block_num       :      Total block number.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_gdma_multiblk_memcpy(phal_gdma_adaptor_t phal_gdma_adaptor,
									  phal_gdma_block_t phal_gdma_block,
									  u8 block_num)
{
	u32 sync_len;

	if (phal_gdma_adaptor->busy) {
		DBG_GDMA_ERR("hal_gdma_multiblk_memcpy : GDMA is busy\r\n");
		return HAL_ERR_PARA;
	}

	sync_len = phal_gdma_block[block_num - 1].src_addr - phal_gdma_block[0].src_addr
			   + phal_gdma_block[block_num - 1].block_length;

	if (phal_gdma_adaptor->dcache_clean_by_addr != NULL) {
		phal_gdma_adaptor->dcache_clean_by_addr((uint32_t *) phal_gdma_block,
												(int32_t)(block_num * sizeof(hal_gdma_block_t)));
	}

	if (phal_gdma_adaptor->ch_num < MIN_MULTI_CHNL_NUM) {
		if (hal_gdma_chnl_alloc(phal_gdma_adaptor, MultiBlkEn) != HAL_OK) {
			DBG_GDMA_ERR("Cannot Allocate Channel !\n");
			return HAL_ERR_HW;
		} else {
			hal_gdma_chnl_init(phal_gdma_adaptor);
		}

		hal_gdma_irq_reg(phal_gdma_adaptor, (irq_handler_t) hal_gdma_stubs.hal_gdma_memcpy_irq_handler,
						 phal_gdma_adaptor);
	}
	hal_gdma_linked_list_block_config(phal_gdma_adaptor, phal_gdma_block, block_num);

	if (phal_gdma_adaptor->dcache_clean_by_addr != NULL) {
		phal_gdma_adaptor->dcache_clean_by_addr((uint32_t *) phal_gdma_block[0].src_addr, (int32_t) sync_len);
		phal_gdma_adaptor->dcache_clean_by_addr((uint32_t *) phal_gdma_block[0].dst_addr, (int32_t) sync_len);
	}

	hal_gdma_isr_en(phal_gdma_adaptor);
	hal_gdma_chnl_block_setting(phal_gdma_adaptor);
	hal_gdma_chnl_en(phal_gdma_adaptor);

	return HAL_OK;
}

/** *@} */ /* End of group hs_hal_gdma_ram_func */

#if defined (CONFIG_BUILD_SECURE) && !defined(CONFIG_BUILD_BOOT)
/**
 *   \addtogroup hs_hal_gdma_nsc_api GDMA HAL NSC APIs
 *   \ingroup hs_hal_gdma
 *   \brief The GDMA HAL NSC (Non-Secure Callable) APIs.
 *          Non-secure domain is allowed to access secure functions through NSC APIs.
 *   @{
 */


/** \brief Description of Non-secure callable function hal_gdma_chnl_register_ns
 *
 *    hal_gdma_chnl_register_ns is used to manage and register GDMA channel.
 *    It will check the viability of the target channel.
 *    If no one occupies this channel, the target channel is registered so that others cannot use this one.
 *    The GDMA clock is enabled and the reset is released if target GDMA has not been used before(GDMA is off).
 *
 *   \param u8 gdma_index:      The target GDMA, could be GDMA0 or GDMA1.
 *   \param u8 chnl_num:      The target GDMA channel, could be 0~5.
 *
 *   \return hal_status_t.
 */
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY hal_gdma_chnl_register_ns(u8 gdma_index, u8 chnl_num)
{
	return hal_gdma_chnl_register(gdma_index, chnl_num);
}


/** \brief Description of Non-secure callable function hal_gdma_chnl_unregister_ns
 *
 *    hal_gdma_chnl_unregister_ns is used to manage and unregister GDMA channel.
 *    When the transfer is complete and the channel is no long used, we can release this channel by unregistering it.
 *    The GDMA clock is disabled if no one uses this GDMA.
 *
 *   \param phal_gdma_adaptor_t phal_gdma_adaptor:      The pointer of GDMA adaptor.
 *
 *   \return hal_status_t.
 */
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY hal_gdma_chnl_unregister_ns(phal_gdma_adaptor_t phal_gdma_adaptor)
{
	return hal_gdma_chnl_unregister(phal_gdma_adaptor);
}

/** *@} */ /* End of group hs_hal_gdma_nsc_api */


#endif

/**
 *   \addtogroup hs_hal_gdma_ram_func GDMA HAL RAM APIs
 *   @{
 */


/** \brief Description of hal_gdma_chnl_alloc
 *
 *    hal_gdma_chnl_alloc is used to allocate a channel for the current GDMA transfer.
 *
 *   \param phal_gdma_adaptor_t phal_gdma_adaptor:      The pointer of GDMA adaptor.
 *   \param u8 multi_blk_en:      A control bit to determine whether this transfer
 *                                requires a channel supporting multiblock mode.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_gdma_chnl_alloc(phal_gdma_adaptor_t phal_gdma_adaptor, u8 multi_blk_en)
{
	phal_gdma_chnl_t pgdma_chnl;
	u8 multi_blk_index = 0;
	u8 multi_blk_chnl = 0;

	if (phal_gdma_adaptor->have_chnl == 1) {
		if (multi_blk_en && (phal_gdma_adaptor->ch_num < MIN_MULTI_CHNL_NUM)) {
			hal_gdma_chnl_free(phal_gdma_adaptor);
		}
	}

	if (phal_gdma_adaptor->have_chnl == 0) {
		if (multi_blk_en) {
			pgdma_chnl = (phal_gdma_chnl_t)(&gdma_multi_block_chnl_option[0]);
		} else {
			pgdma_chnl = (phal_gdma_chnl_t)(&gdma_chnl_option[0]);
		}

		while (pgdma_chnl->gdma_indx <= MAX_GDMA_INDX) {
			if (hal_gdma_chnl_register(pgdma_chnl->gdma_indx, pgdma_chnl->gdma_chnl) == HAL_OK) {
				phal_gdma_adaptor->gdma_index = pgdma_chnl->gdma_indx;
				phal_gdma_adaptor->ch_num = pgdma_chnl->gdma_chnl;
				phal_gdma_adaptor->have_chnl = 1;
				DBG_GDMA_INFO("GDMA Index = %d, Channel = %d\n",
							  phal_gdma_adaptor->gdma_index, phal_gdma_adaptor->ch_num);
				// this gdma channel is available
				break;
			}
			pgdma_chnl += 1;
		}

		if (pgdma_chnl->gdma_indx > MAX_GDMA_INDX) {
			return HAL_ERR_PARA;
		}

		if (multi_blk_en) {
			multi_blk_index = phal_gdma_adaptor->gdma_index;
			multi_blk_chnl = phal_gdma_adaptor->ch_num - MIN_MULTI_CHNL_NUM;
			phal_gdma_adaptor->pgdma_ch_lli = (pgdma_ch_lli_t)&multi_blk_adaptor[multi_blk_index][multi_blk_chnl];
		}
	}

	phal_gdma_adaptor->dcache_invalidate_by_addr = dcache_invalidate_by_addr;
	phal_gdma_adaptor->dcache_clean_by_addr = dcache_clean_by_addr;

	return HAL_OK;
}

/** \brief Description of hal_gdma_chnl_free
 *
 *    hal_gdma_chnl_free is used to release the channel after transfer is complete.
 *    That channel then becomes available for other peripherals.
 *
 *   \param phal_gdma_adaptor_t phal_gdma_adaptor:      The pointer of GDMA adaptor.
 *
 *   \return void.
 */
void hal_gdma_chnl_free(phal_gdma_adaptor_t phal_gdma_adaptor)
{
	/*Mask the corresponding ISR bits of the cahnnel*/
	hal_gdma_isr_dis(phal_gdma_adaptor);

	/*Return the channel*/
	hal_gdma_chnl_unregister(phal_gdma_adaptor);

	hal_gdma_chnl_irq_free(phal_gdma_adaptor);

	phal_gdma_adaptor->have_chnl = 0;
}

/** *@} */ /* End of group hal_gdma_ram_func */

/** *@} */ /* End of group hal_gdma */

