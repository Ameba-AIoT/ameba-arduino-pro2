/**************************************************************************//**
 * @file     rtl8735b_hkdf.h
 * @brief    This file defines the functions of hkdf rom code.
 * @version  1.0.0
 * @date     2021-07-22
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

#ifndef RTL8735B_HKDF_H
#define RTL8735B_HKDF_H

#ifdef __cplusplus
extern "C" {
#endif

#define HKDF_KEY_STG_IDX_NALL   (0xFF)

#define HKDF_ORI_SEL_EN                 (_TRUE)
#define HKDF_ORI_SEL_DIS                (_FALSE)

#define HKDF_CRYPTO_HW_SEL_EN           (0x0)
#define HKDF_CRYPTO_SW_SEL_EN           (0x1)

#define HKDF_CRYPTO_HW_KEYSTG_IN_EN     (0x1 << 0)
#define HKDF_CRYPTO_HW_KEYSTG_IN_DIS    (0x0 << 0)
#define HKDF_CRYPTO_HW_KEYSTG_OUT_EN    (0x1 << 16)
#define HKDF_CRYPTO_HW_KEYSTG_OUT_DIS   (0x0 << 16)

#define HKDF_CRYPTO_HW_KEYSTG_DIS                 (HKDF_CRYPTO_HW_KEYSTG_IN_DIS | HKDF_CRYPTO_HW_KEYSTG_OUT_DIS)
#define HKDF_CRYPTO_HW_KEYSTG_IN_EN_OUT_DIS       (HKDF_CRYPTO_HW_KEYSTG_IN_EN | HKDF_CRYPTO_HW_KEYSTG_OUT_DIS)
#define HKDF_CRYPTO_HW_KEYSTG_IN_DIS_OUT_EN       (HKDF_CRYPTO_HW_KEYSTG_IN_DIS | HKDF_CRYPTO_HW_KEYSTG_OUT_EN)
#define HKDF_CRYPTO_HW_KEYSTG_IN_EN_OUT_EN        (HKDF_CRYPTO_HW_KEYSTG_IN_EN | HKDF_CRYPTO_HW_KEYSTG_OUT_EN)

#define HKDF_SHA2_256_HASH_SIZE             (256/8)
#define HKDF_SHA2_384_HASH_SIZE             (384/8)
#define HKDF_SHA2_512_HASH_SIZE             (512/8)

#define HKDF_SHA256_KEY_LENGTH          (32)

#define HKDF_KEY_STG_SKCFG_NONE         (0x0)

#define HKDF_USE_KEY_STG_EN              (1)
#define HKDF_USE_KEY_STG_DIS             (0)

#define HKDF_CRYPOT_KEY_STG_LD_SK_EN     (1)
#define HKDF_CRYPOT_KEY_STG_LD_SK_DIS    (0)

#define HKDF_EXPAND_INFO2                (2)
#define HKDF_EXPAND_INFO3                (3)

#define hkdf_set_low_2byte(ie_val)          ((ie_val & 0xFFFF) << 0)
#define hkdf_set_high_2byte(ie_val)         ((ie_val & 0xFFFF) << 16)
#define hkdf_get_low_2byte(ie_val)          ((ie_val >> 0) & 0xFFFF)
#define hkdf_get_high_2byte(ie_val)         ((ie_val >> 16) & 0xFFFF)

#define hkdf_set_crypto_cfg(crypto_sel, hmac_alg_sel) (hkdf_set_low_2byte(hmac_alg_sel) | hkdf_set_high_2byte(crypto_sel))

enum  hkdf_alg_e {
	HKDF_HMAC_SHA256  = 0x0,
	HKDF_HMAC_SHA384  = 0x1,
	HKDF_HMAC_SHA512  = 0x2
};

enum hkdf_key_storage_e {
	HKDF_KEY_STG_IDX_1  = 0x1,
	HKDF_KEY_STG_IDX_HUK1  = 0x1,
	HKDF_KEY_STG_IDX_2  = 0x2,
	HKDF_KEY_STG_IDX_HUK2  = 0x2,
	HKDF_KEY_STG_IDX_3  = 0x3,
	HKDF_KEY_STG_IDX_4  = 0x4,
	HKDF_KEY_STG_IDX_5  = 0x5,
	HKDF_KEY_STG_IDX_6  = 0x6,
	HKDF_KEY_STG_IDX_7  = 0x7,
	HKDF_KEY_STG_IDX_8  = 0x8
};

// TODO doxygen
/**
  \brief  HKDF HMAC init function pointer type.
*/
typedef int (*hkdf_hmac_init_func_t)(void *arg, const u8 *key, const u32 key_len);

/**
  \brief  HKDF HMAC update function pointer type.
*/
typedef int (*hkdf_hmac_update_func_t)(void *arg, const u8 *msg, const u32 msg_len);

/**
  \brief  HKDF HMAC final function pointer type.
*/
typedef int (*hkdf_hmac_final_func_t)(void *arg, u8 *digest);

// TODO doxygen
#if IS_CUT_TEST(CONFIG_CHIP_VER)
typedef struct {
	const u8 *salt;
	u32  salt_len;

	const u8 *ikm;
	u32  ikm_len;

	const u8 *nonce;
	u32 nonce_len;

	u8 *okm;
	u32 okm_len;

	u8 *prk;
	u32 prk_len;

	int (*hmac_func_init)(const u8 *key, const u32 key_len);
	int (*hmac_func_update)(const u8 *msg, const u32 msg_len);
	int (*hmac_func_final)(u8 *digest);
} hal_hkdf_adapter_t;

typedef struct {
	hal_status_t (*hal_hkdf_derive)(hal_hkdf_adapter_t *adtr);
	hal_status_t (*hal_hkdf_expand)(hal_hkdf_adapter_t *adtr);
	hal_status_t (*hal_hkdf_extract)(hal_hkdf_adapter_t *adtr);
	u32 reserved[13];  // reserved space for next ROM code version function table extending.
} hal_hkdf_func_stubs_t;

hal_status_t hal_rtl_hkdf_derive(hal_hkdf_adapter_t *adtr);
hal_status_t hal_rtl_hkdf_extract(hal_hkdf_adapter_t *adtr);
hal_status_t hal_rtl_hkdf_expand(hal_hkdf_adapter_t *adtr);
#else

typedef struct {
	u8 isInit;          // HKDF init state: 1=Init, 0=Not init
	u8 isHWCrypto_Init; // HW Crypto init state: 1=Init, 0=Not init
	u8 ori_en;
	u8 resv1[1];

	u16 crypto_sel;      // hw or sw
	u16 hmac_alg_sel;    // sha256,384?,512?

	hal_crypto_adapter_t *pcrypto_adtr;
	u32 sk_cfg;

	u8 use_key_stg;
	u8 resv2[3];
	u8 resv3[4];

	u8 key_extract_sk_sel;
	u8 key_extract_stg_wb_sel;
	u8 key_expand_sk_sel;
	u8 key_expand_stg_wb_sel;

	u8 extract_sk_idx;
	u8 extract_wb_idx;
	u8 expand_sk_idx;
	u8 expand_wb_idx;

	u32 extract_key_len;
	u32 expand_key_len;

	u8 *info2;
	u32 info2_len;

	u8 *info3;
	u32 info3_len;

	u32 okm_len;

	hkdf_hmac_init_func_t   hmac_init_f;
	hkdf_hmac_update_func_t hmac_update_f;
	hkdf_hmac_final_func_t  hmac_final_f;

	u32 seq_hkdf_buf_len;
	u32 digest_len;
	u32 resv4[2];
	/**
	 * 32 bytes aligned buffer that store 32 bytes input key material buffer  !!
	 */
	volatile u8  ikm_buf[64] __attribute__((aligned(32)));

	/**
	 * 32 bytes aligned buffer that store 32 bytes pseudorandom key buffer  !!
	 */
	volatile u8  prk_buf[64] __attribute__((aligned(32)));

	/**
	 * 32 bytes aligned buffer that store 32 bytes sequential hkdf buffer  !!
	 */
	volatile u8  seq_hkdf_buf[64] __attribute__((aligned(32)));
} hal_hkdf_adapter_t, *phal_hkdf_adapter_t;

typedef struct {
	hal_status_t (*hal_hkdf_init)(hal_hkdf_adapter_t *phkdf_adtr, hal_crypto_adapter_t *pcrypto_adapter, const u32 crypto_cfg, const u8 ori_en);
	hal_status_t (*hal_hkdf_deinit)(hal_hkdf_adapter_t *phkdf_adtr);
	hal_status_t (*hal_hkdf_hook_operate_f)(hal_hkdf_adapter_t *phkdf_adtr, hkdf_hmac_init_func_t hmac_init_f,
											hkdf_hmac_update_func_t hmac_update_f, hkdf_hmac_final_func_t hmac_final_f);
	hal_status_t (*hal_hkdf_extract)(hal_hkdf_adapter_t *phkdf_adtr, const u8 *salt, const u32 salt_len,
									 const u8 *ikm, const u32 ikm_len, u8 *prk);
	hal_status_t (*hal_hkdf_extract_engine)(hal_hkdf_adapter_t *phkdf_adtr, const u8 *key_buf, const u8 *msg_buf, const u32 msg_len,
											u8 *pkm_buf);
	hal_status_t (*hal_hkdf_expand)(hal_hkdf_adapter_t *phkdf_adtr, const u8 *prk,
									const u8 *nonce, const u32 nonce_len, u8 *okm, u32 okm_len);
	hal_status_t (*hal_hkdf_expand_engine)(hal_hkdf_adapter_t *phkdf_adtr, const u8 *key_buf, const u8 *msg_buf, const u32 msg_len,
										   u8 *okm_buf);
	hal_status_t (*hal_hkdf_secure_set_cfg)(hal_hkdf_adapter_t *phkdf_adtr, const u8 sk_sel, const u8 sk_idx,
											const u8 wb_sel, const u8 wb_idx);
	hal_status_t (*hal_hkdf_extract_secure_set_cfg)(hal_hkdf_adapter_t *phkdf_adtr, const u8 sk_sel, const u8 sk_idx,
			const u8 wb_sel, const u8 wb_idx);
	hal_status_t (*hal_hkdf_expand_secure_set_cfg)(hal_hkdf_adapter_t *phkdf_adtr, const u8 sk_sel, const u8 sk_idx,
			const u8 wb_sel, const u8 wb_idx);
	hal_status_t (*hal_hkdf_extract_secure)(hal_hkdf_adapter_t *phkdf_adtr, const u8 *key_buf, const u8 *msg_buf,
											const u32 msg_len, u8 *pkm_buf);
	hal_status_t (*hal_hkdf_expand_secure)(hal_hkdf_adapter_t *phkdf_adtr, const u8 *prk, const u8 *nonce,
										   const u32 nonce_len, u8 *okm, u32 okm_len);
	hal_status_t (*hal_hkdf_expand_register_info_extend)(hal_hkdf_adapter_t *phkdf_adtr, const u8 *info, const u32 info_len, const u8 info_role);
	hal_status_t (*hal_hkdf_expand_unregister_info_extend)(hal_hkdf_adapter_t *phkdf_adtr, const u8 info_role);

	u32 reserved[2];  // reserved space for next ROM code version function table extending.
} hal_hkdf_func_stubs_t;

typedef struct {
	void (*hal_hkdf_hmac_init_hook)(hal_hkdf_adapter_t *phkdf_adtr, hkdf_hmac_init_func_t hmac_init_f);
	void (*hal_hkdf_hmac_update_hook)(hal_hkdf_adapter_t *phkdf_adtr, hkdf_hmac_update_func_t hmac_update_f);
	void (*hal_hkdf_hmac_final_hook)(hal_hkdf_adapter_t *phkdf_adtr, hkdf_hmac_final_func_t hmac_final_f);
	hal_status_t (*hal_hkdf_extract_secure_all)(hal_hkdf_adapter_t *phkdf_adtr, const u8 sk_idx, const u8 wb_idx, const u8 *msg_buf);
	hal_status_t (*hal_hkdf_expand_secure_all)(hal_hkdf_adapter_t *phkdf_adtr, const u8 sk_idx, const u8 wb_idx, const u8 *nonce);
	u32 reserved[11];  // reserved space for next ROM code version function table extending.
} hal_hkdf_extend_func_stubs_t;

hal_status_t hal_rtl_hkdf_hmac_sha256_secure_init(hal_hkdf_adapter_t *phkdf_adtr, hal_crypto_adapter_t *pcrypto_adapter, const u8 crypto_sel);
hal_status_t hal_rtl_hkdf_hmac_init(hal_hkdf_adapter_t *phkdf_adtr, hal_crypto_adapter_t *pcrypto_adapter,
									const u8 crypto_sel, const u8 hmac_alg_sel);
hal_status_t hal_rtl_hkdf_init(hal_hkdf_adapter_t *phkdf_adtr, hal_crypto_adapter_t *pcrypto_adapter, const u32 crypto_cfg, const u8 ori_en);
hal_status_t hal_rtl_hkdf_deinit(hal_hkdf_adapter_t *phkdf_adtr);
hal_status_t hal_rtl_hkdf_hook_operate_f(hal_hkdf_adapter_t *phkdf_adtr, hkdf_hmac_init_func_t hmac_init_f,
		hkdf_hmac_update_func_t hmac_update_f, hkdf_hmac_final_func_t hmac_final_f);
hal_status_t hal_rtl_hkdf_derive(hal_hkdf_adapter_t *phkdf_adtr);
hal_status_t hal_rtl_hkdf_extract(hal_hkdf_adapter_t *phkdf_adtr, const u8 *salt, const u32 salt_len,
								  const u8 *ikm, const u32 ikm_len, u8 *prk);
hal_status_t hal_rtl_hkdf_extract_engine(hal_hkdf_adapter_t *phkdf_adtr, const u8 *key_buf, const u8 *msg_buf, const u32 msg_len,
		u8 *pkm_buf);
hal_status_t hal_rtl_hkdf_expand(hal_hkdf_adapter_t *phkdf_adtr, const u8 *prk,
								 const u8 *nonce, const u32 nonce_len, u8 *okm, u32 okm_len);
hal_status_t hal_rtl_hkdf_expand_engine(hal_hkdf_adapter_t *phkdf_adtr, const u8 *key_buf, const u8 *msg_buf, const u32 msg_len,
										u8 *okm_buf);
hal_status_t hal_rtl_hkdf_secure_set_cfg(hal_hkdf_adapter_t *phkdf_adtr, const u8 sk_sel, const u8 sk_idx,
		const u8 wb_sel, const u8 wb_idx);
hal_status_t hal_rtl_hkdf_extract_secure_set_cfg(hal_hkdf_adapter_t *phkdf_adtr, const u8 sk_sel, const u8 sk_idx,
		const u8 wb_sel, const u8 wb_idx);
hal_status_t hal_rtl_hkdf_expand_secure_set_cfg(hal_hkdf_adapter_t *phkdf_adtr, const u8 sk_sel, const u8 sk_idx,
		const u8 wb_sel, const u8 wb_idx);
hal_status_t hal_rtl_hkdf_extract_secure(hal_hkdf_adapter_t *phkdf_adtr, const u8 *key_buf, const u8 *msg_buf,
		const u32 msg_len, u8 *pkm_buf);
hal_status_t hal_rtl_hkdf_expand_secure(hal_hkdf_adapter_t *phkdf_adtr, const u8 *prk, const u8 *nonce,
										const u32 nonce_len, u8 *okm, u32 okm_len);
hal_status_t hal_rtl_hkdf_extract_secure_all(hal_hkdf_adapter_t *phkdf_adtr, const u8 sk_idx, const u8 wb_idx, const u8 *msg_buf);
hal_status_t hal_rtl_hkdf_expand_secure_all(hal_hkdf_adapter_t *phkdf_adtr, const u8 sk_idx, const u8 wb_idx, const u8 *nonce);

hal_status_t hal_rtl_hkdf_expand_register_info_extend(hal_hkdf_adapter_t *phkdf_adtr, const u8 *info, const u32 info_len, const u8 info_role);
hal_status_t hal_rtl_hkdf_expand_unregister_info_extend(hal_hkdf_adapter_t *phkdf_adtr, const u8 info_role);

void hal_rtl_hkdf_hmac_init_hook(hal_hkdf_adapter_t *phkdf_adtr, hkdf_hmac_init_func_t hmac_init_f);
void hal_rtl_hkdf_hmac_update_hook(hal_hkdf_adapter_t *phkdf_adtr, hkdf_hmac_update_func_t hmac_update_f);
void hal_rtl_hkdf_hmac_final_hook(hal_hkdf_adapter_t *phkdf_adtr, hkdf_hmac_final_func_t hmac_final_f);

#endif

#ifdef __cplusplus
}
#endif

#endif /* RTL8735B_FLASH_SEC_H */
