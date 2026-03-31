/**************************************************************************//**
 * @file     hal_hkdf.c
 * @brief    Implement HKDF RAM code functions.
 *
 * @version  V1.00
 * @date     2021-07-22
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

#include "cmsis.h"
#include "hal_hkdf.h"
#include "hal_crypto.h"
#include "rtl8735b_hkdf.h"
#include "rtl8735b_crypto_ctrl.h"

#if CONFIG_HKDF_EN

#if IS_CUT_TEST(CONFIG_CHIP_VER)
// For Test-chip

// TODO add doxygen
/**
  \brief todo
*/

hal_status_t hal_hkdf_derive(hal_hkdf_adapter_t *adtr)
{
	return hal_hkdf_stubs.hal_hkdf_derive(adtr);
}
#else
// After A-cut

hal_hkdf_adapter_t hkdf_obj;

int hal_hkdf_hmac_sha2_256_init(void *arg, const u8 *key, const u32 keylen)
{
	hal_hkdf_adapter_t *phkdf_adtr = (hal_hkdf_adapter_t *)arg;
	int ret = SUCCESS;
	if (NULL == phkdf_adtr) {
		return HAL_ERR_PARA;
	}
	if (HKDF_CRYPTO_HW_SEL_EN == phkdf_adtr->crypto_sel) {
		if (TRUE != phkdf_adtr->isHWCrypto_Init) {
			ret = _ERRNO_HKDF_CRYPTO_HW_NOT_INIT;
			return ret;
		}
		if (HKDF_KEY_STG_SKCFG_NONE == phkdf_adtr->sk_cfg) {
			ret = hal_crypto_hmac_sha2_256_init(key, keylen);
		} else {
			ret = hal_crypto_hmac_sha2_256_sk_init(key, (phkdf_adtr->sk_cfg));
		}
	} else {
		ret = _ERRNO_HKDF_CRYPTO_SW_NOT_READY;
	}
	return ret;
}

int hal_hkdf_hmac_sha2_256_update(void *arg, const u8 *message, const u32 msglen)
{
	hal_hkdf_adapter_t *phkdf_adtr = (hal_hkdf_adapter_t *)arg;
	int ret = SUCCESS;
	if (NULL == phkdf_adtr) {
		return HAL_ERR_PARA;
	}
	if (HKDF_CRYPTO_HW_SEL_EN == phkdf_adtr->crypto_sel) {
		if (TRUE != phkdf_adtr->isHWCrypto_Init) {
			ret = _ERRNO_HKDF_CRYPTO_HW_NOT_INIT;
			return ret;
		}
		ret = hal_crypto_hmac_sha2_256_update(message, msglen);
	} else {
		ret = _ERRNO_HKDF_CRYPTO_SW_NOT_READY;
	}
	return ret;
}

int hal_hkdf_hmac_sha2_256_final(void *arg, u8 *pDigest)
{
	hal_hkdf_adapter_t *phkdf_adtr = (hal_hkdf_adapter_t *)arg;
	int ret = SUCCESS;
	if (NULL == phkdf_adtr) {
		return HAL_ERR_PARA;
	}
	if (HKDF_CRYPTO_HW_SEL_EN == phkdf_adtr->crypto_sel) {
		if (TRUE != phkdf_adtr->isHWCrypto_Init) {
			ret = _ERRNO_HKDF_CRYPTO_HW_NOT_INIT;
			return ret;
		}
		if (HKDF_KEY_STG_SKCFG_NONE == phkdf_adtr->sk_cfg) {
			ret = hal_crypto_hmac_sha2_256_final(pDigest);
		} else {
			ret = hal_crypto_hmac_sha2_256_sk_final(pDigest);
		}
	} else {
		ret = _ERRNO_HKDF_CRYPTO_SW_NOT_READY;
	}
	return ret;
}

hal_status_t hal_hkdf_hmac_sha256_secure_init(const u8 crypto_sel)
{
	hal_status_t  ret = HAL_OK;
	ret = hal_hkdf_hmac_init(crypto_sel, HKDF_HMAC_SHA256);
	return ret;
}

hal_status_t hal_hkdf_hmac_init(const u8 crypto_sel, const u8 hmac_alg_sel)
{
	hal_status_t  ret = HAL_OK;
	hal_hkdf_adapter_t *phkdf_adtr = &hkdf_obj;
	u32 crypto_cfg;
	crypto_cfg = hkdf_set_crypto_cfg(crypto_sel, hmac_alg_sel);
	ret = hal_hkdf_init(phkdf_adtr, crypto_cfg, HKDF_ORI_SEL_DIS);
	return ret;
}

hal_status_t hal_hkdf_init(hal_hkdf_adapter_t *phkdf_adtr, const u32 crypto_cfg, const u8 ori_en)
{
	hal_status_t  ret = HAL_OK;
	int32_t cryp_ret;
	u16 crypto_sel = 0, hmac_alg_sel = 0;
	if (NULL == phkdf_adtr) {
		return HAL_ERR_PARA;
	}

	memset(phkdf_adtr, 0x0, sizeof(hal_hkdf_adapter_t));
	hmac_alg_sel = hkdf_get_low_2byte(crypto_cfg);
	crypto_sel = hkdf_get_high_2byte(crypto_cfg);

	if (HKDF_CRYPTO_HW_SEL_EN == crypto_sel) {
		// init crypto engine
		cryp_ret = hal_crypto_engine_chk_init();
		if (TRUE != cryp_ret) {
			cryp_ret = hal_crypto_engine_init();
			if (cryp_ret != SUCCESS) {
				dbg_printf("hkdf: HW Crypto init fail!\r\n");
				return HAL_ERR_HW;
			} else {
				phkdf_adtr->isHWCrypto_Init = TRUE;
				phkdf_adtr->pcrypto_adtr = NULL;
			}
		} else {
			phkdf_adtr->isHWCrypto_Init = TRUE;
			phkdf_adtr->pcrypto_adtr = NULL;
		}
	}

	phkdf_adtr->crypto_sel = crypto_sel;
	switch (hmac_alg_sel) {
	case HKDF_HMAC_SHA256:
		phkdf_adtr->digest_len = HKDF_SHA2_256_HASH_SIZE;
		phkdf_adtr->extract_key_len = HKDF_SHA256_KEY_LENGTH;
		phkdf_adtr->expand_key_len = HKDF_SHA256_KEY_LENGTH;
		phkdf_adtr->seq_hkdf_buf_len = HKDF_SHA2_256_HASH_SIZE;
		break;
	case HKDF_HMAC_SHA384:
		break;
	case HKDF_HMAC_SHA512:
		break;
	default:
		hmac_alg_sel = HKDF_HMAC_SHA256;
		phkdf_adtr->digest_len = HKDF_SHA2_256_HASH_SIZE;
		phkdf_adtr->extract_key_len = HKDF_SHA256_KEY_LENGTH;
		phkdf_adtr->expand_key_len = HKDF_SHA256_KEY_LENGTH;
		phkdf_adtr->seq_hkdf_buf_len = HKDF_SHA2_256_HASH_SIZE;
		break;
	}
	phkdf_adtr->hmac_alg_sel = hmac_alg_sel;
	phkdf_adtr->ori_en = ori_en;
	phkdf_adtr->isInit = TRUE;
	ret = hal_hkdf_hook_operate_f(&hal_hkdf_hmac_sha2_256_init, &hal_hkdf_hmac_sha2_256_update, &hal_hkdf_hmac_sha2_256_final);
	return ret;
}

hal_status_t hal_hkdf_deinit(void)
{
	hal_status_t  ret = HAL_OK;
	hal_hkdf_adapter_t *phkdf_adtr = &hkdf_obj;
	ret = hal_hkdf_stubs.hal_hkdf_deinit(phkdf_adtr);
	return ret;
}

hal_status_t hal_hkdf_hook_operate_f(hkdf_hmac_init_func_t hmac_init_f, hkdf_hmac_update_func_t hmac_update_f, hkdf_hmac_final_func_t hmac_final_f)
{
	hal_status_t  ret = HAL_OK;
	hal_hkdf_adapter_t *phkdf_adtr = &hkdf_obj;
	if (phkdf_adtr->isInit != _TRUE) {
		return HAL_NOT_READY; // not init yet
	}
	hal_hkdf_ext_stubs.hal_hkdf_hmac_init_hook(phkdf_adtr, hmac_init_f);
	hal_hkdf_ext_stubs.hal_hkdf_hmac_update_hook(phkdf_adtr, hmac_update_f);
	hal_hkdf_ext_stubs.hal_hkdf_hmac_final_hook(phkdf_adtr, hmac_final_f);

	return ret;
}

hal_status_t hal_hkdf_extract(const u8 *salt, const u32 salt_len,
							  const u8 *ikm, const u32 ikm_len, u8 *prk)
{
	hal_status_t  ret = HAL_OK;
	hal_hkdf_adapter_t *phkdf_adtr = &hkdf_obj;
	ret = hal_hkdf_stubs.hal_hkdf_extract(phkdf_adtr, salt, salt_len, ikm, ikm_len, prk);
	return ret;
}

hal_status_t hal_hkdf_expand_register_info_extend(const u8 *info, const u32 info_len, const u8 info_role)
{
	hal_status_t  ret = HAL_OK;
	hal_hkdf_adapter_t *phkdf_adtr = &hkdf_obj;
	ret = hal_hkdf_stubs.hal_hkdf_expand_register_info_extend(phkdf_adtr, info, info_len, info_role);
	return ret;
}

hal_status_t hal_hkdf_expand_unregister_info_extend(const u8 info_role)
{
	hal_status_t  ret = HAL_OK;
	hal_hkdf_adapter_t *phkdf_adtr = &hkdf_obj;
	ret = hal_hkdf_stubs.hal_hkdf_expand_unregister_info_extend(phkdf_adtr, info_role);
	return ret;
}

hal_status_t hal_hkdf_expand(const u8 *prk, const u8 *nonce, const u32 nonce_len, u8 *okm, u32 okm_len)
{
	hal_status_t  ret = HAL_OK;
	hal_hkdf_adapter_t *phkdf_adtr = &hkdf_obj;
	ret = hal_hkdf_stubs.hal_hkdf_expand(phkdf_adtr, prk, nonce, nonce_len, okm, okm_len);
	return ret;
}

hal_status_t hal_hkdf_extract_secure_set_cfg(const u8 sk_sel, const u8 sk_idx,
		const u8 wb_sel, const u8 wb_idx)
{
	hal_status_t  ret = HAL_OK;
	hal_hkdf_adapter_t *phkdf_adtr = &hkdf_obj;
	ret = hal_hkdf_stubs.hal_hkdf_extract_secure_set_cfg(phkdf_adtr, sk_sel, sk_idx, wb_sel, wb_idx);
	return ret;
}

hal_status_t hal_hkdf_extract_secure(const u8 *key_buf, const u8 *msg_buf,
									 const u32 msg_len, u8 *pkm_buf)
{
	hal_status_t  ret = HAL_OK;
	hal_hkdf_adapter_t *phkdf_adtr = &hkdf_obj;
	ret = hal_hkdf_stubs.hal_hkdf_extract_secure(phkdf_adtr, key_buf, msg_buf, msg_len, pkm_buf);
	return ret;
}

hal_status_t hal_hkdf_extract_secure_all(const u8 sk_idx, const u8 wb_idx, const u8 *msg_buf)
{
	hal_status_t  ret = HAL_OK;
	hal_hkdf_adapter_t *phkdf_adtr = &hkdf_obj;
	uint8_t *p_hshks = NULL;
	if (msg_buf == NULL) {
		return HAL_ERR_PARA;
	} else {
		p_hshks = (uint8_t *)msg_buf;
	}

	ret = hal_hkdf_ext_stubs.hal_hkdf_extract_secure_all(phkdf_adtr, sk_idx, wb_idx, p_hshks);
	return ret;
}

hal_status_t hal_hkdf_expand_secure_set_cfg(const u8 sk_sel, const u8 sk_idx,
		const u8 wb_sel, const u8 wb_idx)
{
	hal_status_t  ret = HAL_OK;
	hal_hkdf_adapter_t *phkdf_adtr = &hkdf_obj;
	ret = hal_hkdf_stubs.hal_hkdf_expand_secure_set_cfg(phkdf_adtr, sk_sel, sk_idx, wb_sel, wb_idx);
	return ret;
}

hal_status_t hal_hkdf_expand_secure(const u8 *prk, const u8 *nonce,
									const u32 nonce_len, u8 *okm, u32 okm_len)
{
	hal_status_t  ret = HAL_OK;
	hal_hkdf_adapter_t *phkdf_adtr = &hkdf_obj;
	ret = hal_hkdf_stubs.hal_hkdf_expand_secure(phkdf_adtr, prk, nonce, nonce_len, okm, okm_len);
	return ret;
}

hal_status_t hal_hkdf_expand_secure_all(const u8 sk_idx, const u8 wb_idx, const u8 *nonce)
{
	hal_status_t  ret = HAL_OK;
	hal_hkdf_adapter_t *phkdf_adtr = &hkdf_obj;
	uint8_t *p_hshkn = NULL;
	if (nonce == NULL) {
		return HAL_ERR_PARA;
	} else {
		p_hshkn = (uint8_t *)nonce;
	}

	ret = hal_hkdf_ext_stubs.hal_hkdf_expand_secure_all(phkdf_adtr, sk_idx, wb_idx, p_hshkn);
	return ret;
}

hal_status_t hal_hkdf_extract_engine(const u8 *key_buf, const u8 *msg_buf, const u32 msg_len, u8 *pkm_buf)
{
	hal_status_t  ret = HAL_OK;
	hal_hkdf_adapter_t *phkdf_adtr = &hkdf_obj;
	ret = hal_hkdf_stubs.hal_hkdf_extract_engine(phkdf_adtr, key_buf, msg_buf, msg_len, pkm_buf);
	return ret;
}

hal_status_t hal_hkdf_expand_engine(const u8 *key_buf, const u8 *msg_buf, const u32 msg_len, u8 *okm_buf)
{
	hal_status_t  ret = HAL_OK;
	hal_hkdf_adapter_t *phkdf_adtr = &hkdf_obj;
	ret = hal_hkdf_stubs.hal_hkdf_expand_engine(phkdf_adtr, key_buf, msg_buf, msg_len, okm_buf);
	return ret;
}
#endif

#endif
