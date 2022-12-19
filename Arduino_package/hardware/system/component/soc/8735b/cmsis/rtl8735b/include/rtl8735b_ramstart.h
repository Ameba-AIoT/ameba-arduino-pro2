/**************************************************************************//**
 * @file     rtl8195bhp_ramstart.h
 * @brief    The data type definition for RAM code entry functions.
 * @version  V1.00
 * @date     2022-11-16
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2016 Realtek Corporation. All rights reserved.
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
#ifndef _RTL8735B_RAMSTART_H_
#define _RTL8735B_RAMSTART_H_

#ifdef  __cplusplus
extern "C"
{
#endif
#include "fw_img.h"



#define BL4FW_STR_SIGN_MAX_SIZE         16
#define BL4VOE_STR_SIGN_MAX_SIZE        16
#define BL4VOE_PERI_STR_SIGN_MAX_SIZE   16
#define BL4VOE_INFO_HDR_MAX_SIZE        32
#define BL4VOE_INFO_DATA_MAX_SIZE       ((2*1024) - BL4VOE_INFO_HDR_MAX_SIZE)

enum {
	BL4VOE_SHARE        =   0x1,
	BL4FW_SHARE         =   0x2,
	BL4VOE_PERI_SHARE   =   0x3,
	BL4VOE_LDINFO_SHARE =   0x4
};

typedef struct _RAM_START_FUNCTION_ {
	void (*RamStartFun)(void);
} RAM_START_FUNCTION, *PRAM_START_FUNCTION;

/**
  \brief Flags to indicates the initialization status of HW in boot loader.
*/
typedef union {
	uint8_t w;                         /*!< all flags in byte                                  */

	struct {
		uint8_t lpddr_inited    : 1;            /*!< [0..0] the LPDDR controller is initialed */
		uint8_t psram_inited    : 1;            /*!< [1..1] the PSRAM controller is initialed */
		uint8_t flash_inited    : 1;            /*!< [2..2] the SPIC Flash controller is initialed */
		uint8_t wdt_disabled    : 1;            /*!< [3..3] the VNDR WDT is disabled */
		uint8_t xip_img_enable  : 1;            /*!< [4..4] the XIP IMG is enabled */
		uint8_t nor_flh_bit_mode: 3;            /*!< [7..5] the nor flash bit mode select */
	} b;                                        /*!< bit fields for flags */
} boot_init_flags_t, *pboot_init_flags_t;

typedef union {
	__IOM uint8_t byte;

	struct {
		__IOM uint8_t fast_boot_hash_key      : 1;       /*!< [0..0] key valid for fast boot hash calculation  */
		__IOM uint8_t fast_boot               : 1;       /*!< [1..1] is boot with fast boot  */
		__IOM uint8_t : 6;
	} bit;
} boot_status_t, *pboot_status_t;

/* Table for image entry, must keep the table size is 16*N for fast boot image hash calculation */
typedef struct _RAM_FUNCTION_START_TABLE_ {
	unsigned char *Signature;
	void (*RamStartFun)(void);
	void (*RamWakeupFun)(void);
	void (*RamPatchFun0)(void);
	void (*RamPatchFun1)(void);
	void *sys_cp_fw_info;           // Co-Processor firmware information
	void *pbl_peri_buf;
	void *pxip_sce_restore;         // buffer to store SCE configuration of XIP
	uint32_t entry_start;           // hash protected code start
	uint32_t entry_end;             // hash protected code end
	uint8_t *hash_data;             // the buffer to store the protected code hash result at boot time
	uint32_t ddr_hash_start1;       // hash protected LPDDR/PSRAM code start (for S region)
	uint32_t ddr_hash_end1;         // hash protected LPDDR/PSRAM code end (for S region)
	uint32_t ddr_hash_start2;       // hash protected LPDDR/PSRAM code start (for NS region)
	uint32_t ddr_hash_end2;         // hash protected LPDDR/PSRAM code end (for NS region)
	uint8_t *ddr_hash_data;         // the buffer to store the LPDDR/PSRAM code hash result at boot time
	uint32_t boot_cfg_w;            // to store the boot configure of ROM code
	uint32_t msp_start;             /*!< the start address of the MSP */
	uint32_t msp_limit;             /*!< the end address of the MSP */
	uint32_t start_tbl_size;
	void *phal_spic_adaptor;        // the SPI flash control adapter
	uint32_t flash_user_data_offset;    // the address offset of user data on flash
	uint32_t flash_user_data_len;       // the length of user data on flash
	void *pbl_shared_buf;

	boot_init_flags_t init_flags;   // the flags to indicates the HW initialization status of boot loader
	boot_status_t boot_status;
	uint8_t reserved1;
	uint8_t sys_tmr_id;             // the system timer ID which is assigned by Secure world

	void *pfw_image_info;      // the buffer for boot loader to pass Image2 information;
	void *pbl_ld_voe_info;
	///!!! Keep the table size = 16 * N !!!
	void *pSnand_layout_info;
	uint32_t reserved2[4];
} RAM_FUNCTION_START_TABLE, *PRAM_FUNCTION_START_TABLE;

STATIC_ASSERT(sizeof(RAM_FUNCTION_START_TABLE) % 16 == 0, ram_fn_sz);

/* Table for system customer initialization image entry */
typedef struct _CINIT_FUNCTION_START_TABLE_ {
	void (*entry_func)(void);
	void *sys_cp_fw_info;           // Co-Processor firmware information
	void *psystimer;
	boot_init_flags_t init_flags;   // the flags to indicates the HW initialization status of boot loader

	uint8_t reserved1[3];
	// Keep the table size = 16 * N
} CINIT_FUNCTION_START_TABLE, *PCINIT_FUNCTION_START_TABLE;

#ifdef  __cplusplus
}
#endif

#endif  // end of "#define _RTL8735B_RAMSTART_H_"

