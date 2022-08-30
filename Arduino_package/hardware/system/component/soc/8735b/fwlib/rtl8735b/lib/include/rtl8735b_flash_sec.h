/**************************************************************************//**
 * @file     rtl8735b_flash_sec.h
 * @brief    This file defines the functions of flash sec rom code.
 * @version  1.0.0
 * @date     2021-07-13
 *
 * @note
 *
 *******************************************************************************
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

#ifndef RTL8735B_FLASH_SEC_H
#define RTL8735B_FLASH_SEC_H

#include "rtl8735b_flash_sec_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#define FLASH_SEC_REMAP_REGION_MAX          (4)
#define FLASH_SEC_DECRYPT_REGION_MAX        (8)


// FIXME how to determine PAGE_SIZE
#define PAGE_SHIFT                      12
#define PAGE_SIZE                       (((u32)0x01) << PAGE_SHIFT)
#define PAGE_OFFSET_MASK                (PAGE_SIZE - 1)
#define PAGE_ALIGN_MASK                (~(PAGE_OFFSET_MASK))
#define GET_PAGE(addr)                  (addr >> PAGE_SHIFT)

// FIXME get me with rubust way
#define FLASH_ADDR_SPACE                ((u32) 0x010000000)
// First page should not be touched, keep calibration data
//#define FLASH_ACCESS_BASE               ((u32) 0x008002000)
#define FLASH_ACCESS_BASE               ((u32) 0x08000000)
// 256 MB
#define FLASH_OFFSET_MASK               (FLASH_ADDR_SPACE - 1)
#define FLASH_BASE                      ((u32) 0x08000000)
#define FLASH_MAX_END                   ((u32) 0x10000000)


// TODO doxygen
// add reserved

// cipher mode
enum {
	FLASH_SEC_CIPHER_GCM = 0,
	FLASH_SEC_CIPHER_CTR = 1,
	FLASH_SEC_CIPHER_MIX = 2,

	FLASH_SEC_CIPHER_MAX = 3
};

// tag size (byte)
enum {
	FLASH_SEC_TAG_4 = 4,
	FLASH_SEC_TAG_8 = 8,
	FLASH_SEC_TAG_16 = 16
};

// key len in bits = (byte)
enum {
	FLASH_SEC_KEY_128 = 16,
	FLASH_SEC_KEY_192 = 24,
	FLASH_SEC_KEY_256 = 32
};

// cache line size (byte)
enum {
	FLASH_SEC_CACHE_16 = 16,
	FLASH_SEC_CACHE_32 = 32,
	FLASH_SEC_CACHE_64 = 64,
	FLASH_SEC_CACHE_128 = 128
};

typedef struct {
	u8 idle;
	u8 key_init_done;
	u8 intr_err_tag;
	u8 intr_err_resp;
	u8 intr_err_apb;
	u8 intr_err_init;
	u8 remap_region_error;
	u8 remap_addr_error;
} hal_flash_sec_status_t;


#if IS_CUT_TEST(CONFIG_CHIP_VER)
typedef struct {
	u8 iv_sel;
	u8 decrypt_region_sel;
	u8 remap_region_sel;

	u8 decrypt_region_enable;
	u8 remap_region_enable;

	u8 cipher;

	// FIXME separate decrypt region base?
	u32 va_base;
	u32 pa_base;

	u32 decrypt_region_size; //!< Byte count of region, 4KB align
	u32 remap_region_size; //!< Byte count of region, 4KB align

	u32 iv_low;
	u32 iv_high;

	// Control regs
	u32 tag_size;
	u8 axi_byte_swap;
	u8 axi_word_swap;
	u32 key_size;
	u8 line_buffer_icg_dis; //icg_ctrl_0;
	u8 fetch_unit_icg_dis; //icg_ctrl_1;
	u8 apb_ctrl_icg_dis;    //icg_ctrl_2;
	u8 key_reg_icg_dis;     //icg_ctrl_3;

	u32 reserved[3];
} hal_flash_sec_adapter_t;
#else
typedef struct {
	u8 iv_sel;
	u8 decrypt_region_sel;
	u8 remap_region_sel;
	u8 resv1;

	u8 decrypt_region_enable;
	u8 remap_region_enable;
	u8 cipher;
	u8 resv2;

	u32 va_base;
	u32 pa_base;
	u32 dec_base;

	u32 decrypt_region_size; //!< Byte count of region, 4KB align
	u32 remap_region_size; //!< Byte count of region, 4KB align

	u32 iv_low;
	u32 iv_high;

	// Control regs
	u32 tag_size;
	u32 key_size;
	u32 cache_line_size;

	u8 axi_byte_swap;
	u8 axi_word_swap;
	u8 resv3[2];

	u8 line_buffer_icg_dis; //icg_ctrl_0;
	u8 fetch_unit_icg_dis; //icg_ctrl_1;
	u8 apb_ctrl_icg_dis;    //icg_ctrl_2;
	u8 key_reg_icg_dis;     //icg_ctrl_3;

	hal_flash_sec_status_t sec_status;

	u32 reserved[3];
} hal_flash_sec_adapter_t;
#endif

// TODO read status after rom code

typedef struct {
	u8 decrypt_region_num;
	u8 iv_num;
	u8 support_ctr;
	u8 support_mix;
	u8 support_gcm;
	u8 key_source;
	u8 cache_line_size; // In byte
} hal_flash_sec_cid_t;

typedef struct {
	void (*hal_flash_sec_get_status)(hal_flash_sec_status_t *status);
	void (*hal_flash_sec_get_cid)(hal_flash_sec_cid_t *cid);
	u32(*hal_flash_sec_get_err_addr)(void);
	void (*hal_flash_sec_aes_enable)(void);
	void (*hal_flash_sec_aes_disable)(void);
	void (*hal_flash_sec_clr_intr)(void);
	hal_status_t (*hal_flash_sec_set_ctrl)(hal_flash_sec_adapter_t *adtr);
	void (*hal_flash_sec_gcm_key_init)(void);
	void (*hal_flash_sec_dec_key_init)(void);
	void (*hal_flash_sec_clean_cache)(void);
	void (*hal_flash_sec_lock)(void);
	void (*hal_flash_sec_set_tag_base)(u32 tag_base_addr);

	hal_status_t (*hal_flash_sec_remap_region)(hal_flash_sec_adapter_t *adtr);
	hal_status_t (*hal_flash_sec_disable_remap_region)(hal_flash_sec_adapter_t *adtr);

	hal_status_t (*hal_flash_sec_set_iv)(hal_flash_sec_adapter_t *adtr);

	hal_status_t (*hal_flash_sec_decrypt_region)(hal_flash_sec_adapter_t *adtr);
	hal_status_t (*hal_flash_sec_disable_decrypt_region)(hal_flash_sec_adapter_t *adtr);

	hal_status_t (*hal_flash_sec_get_remap_region)(hal_flash_sec_adapter_t *adtr);
	hal_status_t (*hal_flash_sec_get_decrypt_region)(hal_flash_sec_adapter_t *adtr);
	hal_status_t (*hal_flash_sec_get_iv)(hal_flash_sec_adapter_t *adtr);
	void (*hal_flash_sec_get_tag_base)(u32 *tag_base);
	u32 reserved[3];
} hal_flash_sec_func_stubs_t ;

typedef struct {
	hal_status_t (*hal_flash_sec_enable_remap_region)(hal_flash_sec_adapter_t *adtr, uint8_t rmp_region_sel,
			uint32_t va_base, uint32_t pa_base, uint32_t region_size);
	hal_status_t (*hal_flash_sec_calculate_tag_base)(uint32_t cache_line_size, uint32_t tag_size,
			uint32_t flash_addr, uint32_t region_size, uint32_t tag_region_addr,
			uint32_t *tag_base, uint32_t *tag_region_size);
	hal_status_t (*hal_flash_sec_decrypt_init)(hal_flash_sec_adapter_t *adtr, const uint8_t key_sel, uint32_t key_size,
			uint32_t cache_line_size, uint32_t tag_size);
	hal_status_t (*hal_flash_sec_decrypt_region_init)(hal_flash_sec_adapter_t *adtr, const uint32_t iv_low_ptn, const uint32_t iv_high_ptn,
			uint8_t dec_region_sel);
	hal_status_t (*hal_flash_sec_decrypt_region_enable)(hal_flash_sec_adapter_t *adtr, const uint8_t cipher_sel,
			uint32_t dec_base, uint32_t dec_size, uint32_t tag_base);
	uint32_t (*hal_flash_sec_set_word_from_byte_bigen)(const unsigned char *s_value);

	uint32_t reserved[13];  // reserved space for next ROM code version function table extending.
} hal_flash_sec_extend_func_stubs_t;


extern const hal_flash_sec_func_stubs_t hal_flash_sec_stubs;
extern const hal_flash_sec_extend_func_stubs_t hal_flash_sec_ext_stubs;

void hal_rtl_flash_sec_get_status(hal_flash_sec_status_t *status);
void hal_rtl_flash_sec_get_cid(hal_flash_sec_cid_t *cid);
u32 hal_rtl_flash_sec_get_err_addr(void);
void hal_rtl_flash_sec_aes_enable(void);
void hal_rtl_flash_sec_aes_disable(void);
void hal_rtl_flash_sec_clr_intr(void);
hal_status_t hal_rtl_flash_sec_set_ctrl(hal_flash_sec_adapter_t *adtr);
void hal_rtl_flash_sec_gcm_key_init(void);
void hal_rtl_flash_sec_dec_key_init(void);
void hal_rtl_flash_sec_clean_cache(void);
void hal_rtl_flash_sec_lock(void);
void hal_rtl_flash_sec_set_tag_base(u32 tag_base_addr);
hal_status_t hal_rtl_flash_sec_remap_region(hal_flash_sec_adapter_t *adtr);
hal_status_t hal_rtl_flash_sec_disable_remap_region(hal_flash_sec_adapter_t *adtr);

hal_status_t hal_rtl_flash_sec_set_iv(hal_flash_sec_adapter_t *adtr);

hal_status_t hal_rtl_flash_sec_decrypt_region(hal_flash_sec_adapter_t *adtr);
hal_status_t hal_rtl_flash_sec_disable_decrypt_region(hal_flash_sec_adapter_t *adtr);

hal_status_t hal_rtl_flash_sec_get_remap_region(hal_flash_sec_adapter_t *adtr);
hal_status_t hal_rtl_flash_sec_get_decrypt_region(hal_flash_sec_adapter_t *adtr);
hal_status_t hal_rtl_flash_sec_get_iv(hal_flash_sec_adapter_t *adtr);
void hal_rtl_flash_sec_get_tag_base(u32 *tag_base);

#if IS_AFTER_CUT_A(CONFIG_CHIP_VER)
uint8_t hal_rtl_flash_sec_check_addr_region(uint32_t base, uint32_t size);
hal_status_t hal_rtl_flash_sec_check_rom_error(hal_flash_sec_adapter_t *adtr);
hal_status_t hal_rtl_flash_sec_enable_remap_region(hal_flash_sec_adapter_t *adtr, uint8_t rmp_region_sel,
		uint32_t va_base, uint32_t pa_base, uint32_t region_size);
hal_status_t hal_rtl_flash_sec_decrypt_key_sel(hal_flash_sec_adapter_t *adtr, uint8_t key_sel);
hal_status_t hal_rtl_flash_sec_decrypt_init(hal_flash_sec_adapter_t *adtr, const uint8_t key_sel, uint32_t key_size,
		uint32_t cache_line_size, uint32_t tag_size);
hal_status_t hal_rtl_flash_sec_default_decrypt_init(hal_flash_sec_adapter_t *adtr, const uint8_t key_sel);
hal_status_t hal_rtl_flash_sec_decrypt_region_init(hal_flash_sec_adapter_t *adtr, const uint32_t iv_low_ptn, const uint32_t iv_high_ptn,
		uint8_t dec_region_sel);
hal_status_t hal_rtl_flash_sec_decrypt_region_enable(hal_flash_sec_adapter_t *adtr, const uint8_t cipher_sel,
		uint32_t dec_base, uint32_t dec_size, uint32_t tag_base);
uint32_t hal_rtl_flash_sec_set_word_from_byte_bigen(const unsigned char *s_value);
hal_status_t hal_rtl_flash_sec_disable_rmp_region(hal_flash_sec_adapter_t *adtr, uint8_t rmp_region_sel);
hal_status_t hal_rtl_flash_sec_calculate_tag_base(uint32_t cache_line_size, uint32_t tag_size,
		uint32_t flash_addr, uint32_t region_size, uint32_t tag_region_addr,
		uint32_t *tag_base, uint32_t *tag_region_size);
hal_status_t hal_rtl_flash_sec_default_calculate_tag_base(uint32_t flash_addr, uint32_t region_size,
		uint32_t tag_region_addr, uint32_t *tag_base,
		uint32_t *tag_region_size);
hal_status_t hal_rtl_flash_sec_disable_dec_region(hal_flash_sec_adapter_t *adtr, uint8_t dec_region_sel);

#endif

#ifdef __cplusplus
}
#endif

#endif /* RTL8735B_FLASH_SEC_H */
