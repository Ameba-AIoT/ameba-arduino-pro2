/**************************************************************************//**
 * @file     hal_hkdf.h
 * @brief    The HAL API implementation for HKDF.
 * @version  V1.00
 * @date     2022-04-11
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

#ifndef _HAL_HKDF_H_
#define _HAL_HKDF_H_
#include "cmsis.h"
#include "rtl8735b_hkdf.h"

#ifdef __cplusplus
extern "C" {
#endif

//
// Error index
//
#define _ERRNO_HKDF_CRYPTO_SW_NOT_READY                        -10
#define _ERRNO_HKDF_CRYPTO_HW_NOT_INIT                         -11


extern const hal_hkdf_func_stubs_t hal_hkdf_stubs;
#if IS_AFTER_CUT_A(CONFIG_CHIP_VER)
extern const hal_hkdf_extend_func_stubs_t hal_hkdf_ext_stubs;

hal_status_t hal_hkdf_hmac_sha256_secure_init(const u8 crypto_sel);
hal_status_t hal_hkdf_hmac_init(const u8 crypto_sel, const u8 hmac_alg_sel);
hal_status_t hal_hkdf_init(hal_hkdf_adapter_t *phkdf_adtr, const u32 crypto_cfg, const u8 ori_en);
hal_status_t hal_hkdf_deinit(void);
hal_status_t hal_hkdf_hook_operate_f(hkdf_hmac_init_func_t hmac_init_f, hkdf_hmac_update_func_t hmac_update_f, hkdf_hmac_final_func_t hmac_final_f);
hal_status_t hal_hkdf_extract(const u8 *salt, const u32 salt_len,
							  const u8 *ikm, const u32 ikm_len, u8 *prk);
hal_status_t hal_hkdf_expand_register_info_extend(const u8 *info, const u32 info_len, const u8 info_role);
hal_status_t hal_hkdf_expand_unregister_info_extend(const u8 info_role);
hal_status_t hal_hkdf_expand(const u8 *prk, const u8 *nonce, const u32 nonce_len, u8 *okm, u32 okm_len);
hal_status_t hal_hkdf_extract_secure_set_cfg(const u8 sk_sel, const u8 sk_idx,
		const u8 wb_sel, const u8 wb_idx);
hal_status_t hal_hkdf_extract_secure(const u8 *key_buf, const u8 *msg_buf,
									 const u32 msg_len, u8 *pkm_buf);
hal_status_t hal_hkdf_expand_secure_set_cfg(const u8 sk_sel, const u8 sk_idx,
		const u8 wb_sel, const u8 wb_idx);
hal_status_t hal_hkdf_expand_secure(const u8 *prk, const u8 *nonce,
									const u32 nonce_len, u8 *okm, u32 okm_len);
hal_status_t hal_hkdf_extract_secure_all(const u8 sk_idx, const u8 wb_idx, const u8 *msg_buf);
hal_status_t hal_hkdf_expand_secure_all(const u8 sk_idx, const u8 wb_idx, const u8 *nonce);
hal_status_t hal_hkdf_extract_engine(const u8 *key_buf, const u8 *msg_buf, const u32 msg_len, u8 *pkm_buf);
hal_status_t hal_hkdf_expand_engine(const u8 *key_buf, const u8 *msg_buf, const u32 msg_len, u8 *okm_buf);
#endif

hal_status_t hal_hkdf_derive(hal_hkdf_adapter_t *adtr);

#ifdef  __cplusplus
}
#endif

#endif // end of _HAL_HKDF_H_
