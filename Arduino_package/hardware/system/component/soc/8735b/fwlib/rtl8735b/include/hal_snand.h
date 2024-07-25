
/**************************************************************************//**
 * @file     hal_snand.h
 * @brief    The header file of hal_snand.c.
 * @version  1.00
 * @date     2022-02-18
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2020 Realtek Corporation. All rights reserved.
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
#ifndef _HAL_SNAND_H_
#define _HAL_SNAND_H_
#include "cmsis.h"
#include "fw_snand_boot.h"
#ifdef  __cplusplus
extern "C"
{
#endif
#define HAL_NAND_PAGE_PER_BLK           0x40
/// Page index of calibration page inside NAND control info block
#define HAL_NAND_CALIBR_PTN_PAGE        0x1
/**
        \addtogroup hs_hal_snand Serial-NAND FLASH
        @{
*/
/**
        \addtogroup hs_hal_snand_ram_func Serial-NAND FLASH HAL RAM APIs
        \ingroup hs_hal_snand
        @{
*/
/// Adapter to use partition related API
typedef struct hal_snand_part_adpt {
	hal_snafc_adaptor_t *adpt;          ///< SNAFC adapter
	snand_vmap_t vmap;                  ///< Partition virtual map
} hal_snand_part_adpt_t;
/// The NAND flash infomation
typedef struct hal_snand_layout_info {
	snand_ctrl_info_t ctrl_info;        ///< NAND control info
	snand_partition_tbl_t part_tbl;     ///< NAND partition table
	BOOL inited;                        ///< Whether this object is initialized
} hal_snand_layout_info_t;
void hal_snand_init(hal_snafc_adaptor_t *pAdaptor);
void hal_snand_deinit(hal_snafc_adaptor_t *pAdaptor);
void hal_snand_adtr_reset(hal_snafc_adaptor_t *pSnafcAdaptor);
void hal_snand_clk_sel(hal_snafc_adaptor_t *snafc_adpt, snafc_clk_sel_t sel);
uint32_t hal_snand_reset_to_spi(hal_snafc_adaptor_t *pAdaptor);
uint32_t hal_snand_read_id(hal_snafc_adaptor_t *pAdaptor);
void hal_snand_set_quad_enable(hal_snafc_adaptor_t *pAdaptor);
void hal_snand_unset_quad_enable(hal_snafc_adaptor_t *pAdaptor);
void hal_snand_set_status(hal_snafc_adaptor_t *pAdaptor, uint8_t cmd, uint8_t data);
void hal_snand_set_status_no_check(hal_snafc_adaptor_t *pAdaptor, uint8_t cmd, uint8_t data);
uint32_t hal_snand_get_status(hal_snafc_adaptor_t *pAdaptor, uint8_t cmd);
uint32_t hal_snand_wait_ready(hal_snafc_adaptor_t *pAdaptor);
void hal_snand_set_write_enable(hal_snafc_adaptor_t *pAdaptor);
void hal_snand_set_write_disable(hal_snafc_adaptor_t *pAdaptor);
uint32_t hal_snand_block_erase(hal_snafc_adaptor_t *pAdaptor, uint32_t blkPageAddr);
uint32_t hal_snand_page_program(hal_snafc_adaptor_t *pAdaptor, uint32_t blkPageAddr);
uint32_t hal_snand_pio_read(hal_snafc_adaptor_t *pAdaptor, void *memAddr, uint32_t dataLens, uint32_t blkPageAddr);
uint32_t hal_snand_pio_write(hal_snafc_adaptor_t *pAdaptor, void *memAddr, uint32_t dataLens, uint32_t blkPageAddr);
uint32_t hal_snand_dma_read(hal_snafc_adaptor_t *pAdaptor, void *memAddr, uint32_t dataLens, uint32_t blkPageAddr);
uint32_t hal_snand_dma_write(hal_snafc_adaptor_t *pAdaptor, void *memAddr, uint32_t dataLens, uint32_t blkPageAddr);
uint32_t hal_snand_page_read(hal_snafc_adaptor_t *pAdaptor, void *memAddr, uint32_t dataLens, uint32_t blkPageAddr);
int32_t hal_snand_bus_calibr(hal_snafc_adaptor_t *snafc_adpt);
void hal_snand_io_mode_sel(hal_snafc_adaptor_t *snafc_adpt, snafcBusTypeMode_t mode);
// Partition related function
s32 hal_snand_load_from_part(hal_snand_part_adpt_t *adpt, void *dest, const u32 partition_offset, const u32 size);
s32 hal_snand_part_adpt_init(hal_snand_part_adpt_t *part_adpt, hal_snafc_adaptor_t *adpt, const snand_part_entry_t *data);
void hal_snand_addr_ofst(snand_addr_t *snand_addr, u32 offset);
s32 hal_snand_addr_cpy(hal_snafc_adaptor_t *adpt, void *dest, const snand_addr_t *addr, u32 size);
s32 hal_snand_init_ctrl_info(void);
s32 hal_snand_otp_clk_sel(hal_snafc_adaptor_t *adpt);
s32 hal_snand_ofst_2_addr(hal_snand_part_adpt_t *part_adpt, const u32 part_ofst, u32 *ret_addr);
// Flash device vendor-specific implementation
uint32_t hal_snand_dma_cont_read(hal_snafc_adaptor_t *pAdaptor, void *memAddr, uint32_t dataLens, uint32_t blkPageAddr);
#ifdef CONFIG_BUILD_NONSECURE
// This info should be inited by S ram_start, then copied to above structs
extern hal_snand_layout_info_t hal_snand_layout_info_ns;
#endif
/** *@} */ /* End of group hs_hal_snand_ram_func */
/** *@} */ /* End of group hs_hal_snand */
#ifdef  __cplusplus
}
#endif
#endif  // end of "#define _HAL_SNAND_H_"
