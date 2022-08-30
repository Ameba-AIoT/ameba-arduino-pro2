/**************************************************************************//**
 * @file     hal_flash_sec.h
 * @brief    The HAL API implementation for the Flash SEC.
 * @version  V1.00
 * @date     2021-07-13
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

#ifndef _HAL_FLASH_SEC_H_
#define _HAL_FLASH_SEC_H_
#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

extern hal_flash_sec_status_t _flash_sec_status;

void hal_flash_sec_get_status(hal_flash_sec_status_t *status);
void hal_flash_sec_get_cid(hal_flash_sec_cid_t *cid);
u32 hal_flash_sec_get_err_addr(void);
hal_status_t hal_flash_sec_aes_enable(void);
void hal_flash_sec_aes_disable(void);
void hal_flash_sec_clr_intr(void);
hal_status_t hal_flash_sec_set_ctrl(hal_flash_sec_adapter_t *adtr);
void hal_flash_sec_gcm_key_init(void);
void hal_flash_sec_dec_key_init(void);
void hal_flash_sec_clean_cache(void);
void hal_flash_sec_lock(void);
void hal_flash_sec_set_tag_base(u32 tag_base_addr);

hal_status_t hal_flash_sec_init(hal_flash_sec_adapter_t *adtr, u8 key_sel);
hal_status_t hal_flash_sec_enable_remap_region(hal_flash_sec_adapter_t *adtr);
hal_status_t hal_flash_sec_disable_remap_region(hal_flash_sec_adapter_t *adtr);

hal_status_t hal_flash_sec_set_iv(hal_flash_sec_adapter_t *adtr);

hal_status_t hal_flash_sec_disable_decrypt_region(hal_flash_sec_adapter_t *adtr);
hal_status_t hal_flash_sec_enable_decrypt_region(hal_flash_sec_adapter_t *adtr);

hal_status_t hal_flash_sec_get_remap_region(hal_flash_sec_adapter_t *adtr);
hal_status_t hal_flash_sec_get_decrypt_region(hal_flash_sec_adapter_t *adtr);
hal_status_t hal_flash_sec_get_iv(hal_flash_sec_adapter_t *adtr);
void hal_flash_sec_get_tag_base(u32 *tag_base);

hal_status_t hal_flash_sec_enable_rmp_region(uint8_t rmp_region_sel, uint32_t va_base, uint32_t pa_base, uint32_t region_size);
uint32_t hal_flash_sec_set_word_from_byte_bigen(const unsigned char *s_value);
hal_status_t hal_flash_sec_calculate_tag_base(uint32_t cache_line_size, uint32_t tag_size,
		uint32_t flash_addr, uint32_t region_size, uint32_t tag_region_addr,
		uint32_t *tag_base, uint32_t *tag_region_size);
hal_status_t hal_flash_sec_default_calculate_tag_base(uint32_t flash_addr, uint32_t region_size,
		uint32_t tag_region_addr, uint32_t *tag_base,
		uint32_t *tag_region_size);
hal_status_t hal_flash_sec_decrypt_init(hal_flash_sec_adapter_t *adtr, const uint8_t key_sel, uint32_t key_size,
										uint32_t cache_line_size, uint32_t tag_size);
hal_status_t hal_flash_sec_decrypt_region(hal_flash_sec_adapter_t *adtr);
hal_status_t hal_flash_sec_default_decrypt_init(const uint8_t key_sel);
hal_status_t hal_flash_sec_decrypt_region_init(const uint32_t iv_low_ptn, const uint32_t iv_high_ptn, uint8_t dec_region_sel);
hal_status_t hal_flash_sec_decrypt_region_enable(const uint8_t cipher_sel, uint32_t dec_base, uint32_t dec_size, uint32_t tag_base);
hal_status_t hal_flash_sec_disable_dec_region(uint8_t dec_region_sel);
hal_status_t hal_flash_sec_disable_rmp_region(uint8_t rmp_region_sel);


#ifdef  __cplusplus
}
#endif

#endif
