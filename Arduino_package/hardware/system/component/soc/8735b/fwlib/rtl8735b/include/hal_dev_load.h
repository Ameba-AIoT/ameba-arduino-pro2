/**************************************************************************//**
 * @file     hal_dev_load.h
 * @brief    This file implements the entry functions of the Flash Booting
 *           API ROM functions.
 *
 * @version  V1.00
 * @date     2022-02-17
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

#ifndef _HAL_DEV_LOAD_H_
#define _HAL_DEV_LOAD_H_
#include "cmsis.h"
#include "fw_snand_boot.h"
#include "hal_snand.h"

#ifdef  __cplusplus
extern "C"
{
#endif

typedef struct dev_nor_part_record_ld_s {
	uint32_t start_addr;        /*!< The start address of the image partition, it should be 4K-bytes aligned */
	uint32_t length;            /*!< The size of the image, it should be times of 4K-bytes */
	uint16_t type_id;           /*!< the image type of the partition */
	uint16_t resv1;
	uint32_t resv2[5];
} dev_nor_part_record_ld_t, *pdev_nor_part_record_ld_t;

typedef struct dev_nand_part_record_ld_s {
	snand_part_entry_t entry;     /*!< partition record (36 byte) */
} dev_nand_part_record_ld_t, *pdev_nand_part_record_ld_t;

typedef union dev_part_record_ld_s {
	dev_nor_part_record_ld_t nor_rd;
	dev_nand_part_record_ld_t nand_rd;
} dev_part_record_ld_t;

typedef struct dev_nor_load_type_s {
	hal_spic_adaptor_t *p_spic_adtr;
	uint32_t size;
	uint32_t addr;
	uint32_t resv;
} dev_nor_load_type_t, *pdev_nor_load_type_t;

// Defines a range of linear data on NAND flash
typedef struct dev_nand_load_type_s {
	hal_snand_part_adpt_t part_adpt;        // NAND flash partition adapter
	uint32_t part_ofst;                     // offset of the range inside the partition
	uint32_t size;                          // size of the range
} dev_nand_load_type_t, *pdev_nand_load_type_t;

typedef union dev_load_type_s {
	dev_nor_load_type_t  nor_ld;
	dev_nand_load_type_t nand_ld;
} dev_load_type_t;


#ifdef  __cplusplus
}
#endif

#endif  // end of "#define _HAL_PINMUX_H_"

