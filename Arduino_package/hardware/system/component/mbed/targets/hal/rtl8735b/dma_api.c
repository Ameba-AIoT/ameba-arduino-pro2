/**************************************************************************//**
 * @file     dma_api.c
 * @brief    This file implements the DMA Mbed HAL API functions.
 *
 * @version  V1.00
 * @date     2017-05-04
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

#include "dma_api.h"
#include "cmsis.h"

/**
 *  @brief   Initial the GDMA
 *
 *  @param   dma_obj: the GDMA object
 *           handler: the callback function for a DMA transfer complete.
 *           id: the argument of the callback function.
 *  @return  None
 *
 */

void dma_memcpy_init(gdma_t *dma_obj, dma_irq_handler handler, uint32_t id)
{
	phal_gdma_adaptor_t phal_gdma_adaptor = &(dma_obj->hal_gdma_adaptor);

	hal_gdma_memcpy_init(phal_gdma_adaptor);
	hal_gdma_memcpy_irq_hook(phal_gdma_adaptor, (gdma_callback_t) handler, phal_gdma_adaptor);
}

/**
 *  @brief   De-Initial the GDMA
 *
 *  @param   dma_obj: the GDMA object
 *  @return  None
 *
 */
void dma_memcpy_deinit(gdma_t *dma_obj)
{
	phal_gdma_adaptor_t phal_gdma_adaptor = &(dma_obj->hal_gdma_adaptor);
	hal_gdma_memcpy_deinit(phal_gdma_adaptor);
}

/**
 *  @brief   To do a memory copy by DMA
 *
 *  @param   None
 *  @return  None
 *
 */
void dma_memcpy(gdma_t *dma_obj, void *dst, void *src, uint32_t len)
{
	phal_gdma_adaptor_t phal_gdma_adaptor = &(dma_obj->hal_gdma_adaptor);
	hal_gdma_memcpy(phal_gdma_adaptor, dst, src, len);
}

/**
 *  @brief   To do a memory copy with multiple blocks by DMA
 *
 *  @param   None
 *  @return  None
 *
 */
void dma_multiblk_memcpy(gdma_t *dma_obj, phal_gdma_block_t phal_gdma_block, u8 block_num)
{
	phal_gdma_adaptor_t phal_gdma_adaptor = &(dma_obj->hal_gdma_adaptor);
	hal_gdma_multiblk_memcpy(phal_gdma_adaptor, phal_gdma_block, block_num);
}
