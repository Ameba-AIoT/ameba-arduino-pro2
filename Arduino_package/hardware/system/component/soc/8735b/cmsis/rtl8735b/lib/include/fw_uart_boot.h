/**************************************************************************//**
 * @file     fw_uart_boot.h
 * @brief    Define the data structure for UART Boot functions.
 * @version  V1.00
 * @date     2021-07-25
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2023 Realtek Corporation. All rights reserved.
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
 *
 ******************************************************************************/

#ifndef _FW_UART_BOOT_H_
#define _FW_UART_BOOT_H_
#include "cmsis.h"

#ifdef  __cplusplus
extern "C"
{
#endif

enum uart_boot_frame_process_state_e {
	UART_BOOT_STATE_KEY_GEN             = 0,
	UART_BOOT_STATE_IMG_HDR             = 1,
	UART_BOOT_STATE_SECTION_HDR         = 2,
	UART_BOOT_STATE_IMG_DATA            = 3,
	UART_BOOT_STATE_W4_SUBIMG_HDR       = 4,
	UART_BOOT_STATE_W4_SECTION_HDR      = 5,

	UART_BOOT_STATE_W_DISCON            = 6,

	UART_BOOT_STATE_ERR                 = 0x0F
};

enum uart_boot_tlv_frame_process_state_e {
	UART_BOOT_TLV_STATE_IMG_MANIF           = 0,
	UART_BOOT_TLV_STATE_IMG_HDR             = 1,
	UART_BOOT_TLV_STATE_SECTION_HDR         = 2,
	UART_BOOT_TLV_STATE_IMG_DATA            = 3,
	UART_BOOT_TLV_STATE_W4_SUBIMG_HDR       = 4,
	UART_BOOT_TLV_STATE_W4_SECTION_HDR      = 5,

	UART_BOOT_TLV_STATE_W_DISCON            = 6,

	UART_BOOT_TLV_STATE_ERR                 = 0x0F
};

typedef int (*crypto_hmac_hash_init)(IN const u8 *key, IN const u32 keylen);
typedef int (*crypto_hash_init)(void);
typedef int (*crypto_hash_update)(IN const u8 *message, IN const u32 msglen);
typedef int (*crypto_hash_final)(OUT u8 *pDigest);
typedef int (*crypto_aes_init)(IN const u8 *key, IN const u32 keylen);
typedef int (*crypto_aes_decrypt)(IN const u8 *message, IN const u32 msglen, \
								  IN const u8 *iv, IN const u32 ivlen, OUT u8 *pResult);

typedef struct uart_boot_xm_frame_handler_s {
	uint8_t state;
	uint8_t secure_lock;
	uint8_t got_1st_frame;  // is the 1st frame of the XModem transfer
	uint8_t need_iv;  // is need decryption IV
	uint32_t tmp_buf_offset;   // the temp buffer offset to write
	uint32_t next_img_offset;
	uint32_t next_section_offset;
	uint32_t offset_2_next_img;
	uint32_t offset_2_next_section;
	uint32_t ram_img_start_addr;
	uint32_t ram_img_size;
	uint32_t ram_img_offset;
	uint32_t ram_start_tbl;
	//crypto_aes_init func_aes_init;
	//crypto_aes_decrypt func_aes_decrypt;
	uint8_t skip_sub_img_load;
	uint8_t sce_switch_rd_mode;
} uboot_xm_frame_handler_t, *puboot_xm_frame_handler_t;

#ifdef  __cplusplus
}
#endif

#endif  // end of "#define _FW_UART_BOOT_H_"

