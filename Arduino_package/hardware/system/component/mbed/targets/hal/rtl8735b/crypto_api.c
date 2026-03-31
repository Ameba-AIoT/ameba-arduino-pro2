/**************************************************************************//**
 * @file     crypto_api.c
 * @brief    This file implements the CRYPTO Mbed HAL API functions.
 *
 * @version  V1.00
 * @date     2019-08-28
 *
 * @note
 *
 ******************************************************************************
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
 ******************************************************************************/
#include <string.h>
#include "hal_crypto.h"
#include "hal_trng_sec.h"
//#include "hal_sce.h"
#include "crypto_api.h"
#include "platform_conf.h"

#if CONFIG_CRYPTO_EN

#ifdef  __cplusplus
extern "C" {
#endif

#define XIP_REMAPPED_START_ADDR              (0x98000000)
#define XIP_REMAPPED_END_ADDR                (0x9C000000)
#define XIP_ENCRYPTED                        (1)

int crypto_init(void)
{
	int ret;

	ret = hal_crypto_engine_init();
	return ret;
}

int crypto_deinit(void)
{
	int ret;

	ret = hal_crypto_engine_deinit();
	return ret;
}

#if defined(CONFIG_FLASH_XIP_EN) && (CONFIG_FLASH_XIP_EN == 1)
int xip_flash_remap_check(const uint8_t *ori_addr, u32 *remap_addr, const uint32_t buf_len)
{
	u32 xip_phy_addr;
	u8 pis_enc;
	int ret = SUCCESS;

	if (((u32)ori_addr >= XIP_REMAPPED_START_ADDR) && ((u32)ori_addr < XIP_REMAPPED_END_ADDR)) {
		// in the range of Flash
		if (HAL_OK == hal_xip_get_phy_addr((u32)ori_addr, &xip_phy_addr, (u32 *)&pis_enc)) {
			// in the range of XIP remapping
			if (pis_enc == XIP_ENCRYPTED) {
				return _ERRNO_CRYPTO_XIP_FLASH_REMAP_FAIL;
			}
			*remap_addr = xip_phy_addr;
		} else {
			// not in the range of remapping
			*remap_addr = (u32)ori_addr;
		}
	} else {
		// not in the range of Flash
		*remap_addr = (u32)ori_addr;
	}
	return ret;
}
#else
int xip_flash_remap_check(const uint8_t *ori_addr, u32 *remap_addr, const uint32_t buf_len)
{
	int ret = SUCCESS;
	*remap_addr = (u32)ori_addr;
	return ret;
}
#endif

//Auth md5
int crypto_md5(const uint8_t *message, const uint32_t msglen, uint8_t *pDigest)
{
	int ret;
	u32 msg_addr;

	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_md5_end;
	}
	ret = hal_crypto_md5((u8 *)msg_addr, msglen, pDigest);
crypto_md5_end:
	return ret;
}

int crypto_md5_init(void)
{
	int ret;

	ret = hal_crypto_md5_init();
	return ret;
}

int crypto_md5_process(const uint8_t *message, const uint32_t msglen, uint8_t *pDigest)
{
	int ret;
	u32 msg_addr;
	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_md5_process_end;
	}
	ret = hal_crypto_md5_process((u8 *)msg_addr, msglen, pDigest);
crypto_md5_process_end:
	return ret;
}

int crypto_md5_update(const uint8_t *message, const uint32_t msglen)
{
	int ret;
	u32 msg_addr;
	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_md5_update_end;
	}
	ret = hal_crypto_md5_update((u8 *)msg_addr, msglen);
crypto_md5_update_end:
	return ret;
}

int crypto_md5_final(uint8_t *pDigest)
{
	int ret;

	ret = hal_crypto_md5_final(pDigest);
	return ret;
}

//Auth SHA1
int crypto_sha1(const uint8_t *message, const uint32_t msglen, uint8_t *pDigest)
{
	int ret;
	u32 msg_addr;
	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_sha1_end;
	}
	ret = hal_crypto_sha1((u8 *)msg_addr, msglen, pDigest);
crypto_sha1_end:
	return ret;
}

int crypto_sha1_init(void)
{
	int ret;

	ret = hal_crypto_sha1_init();
	return ret;
}

int crypto_sha1_process(const uint8_t *message, const uint32_t msglen, uint8_t *pDigest)
{
	int ret;
	u32 msg_addr;
	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_sha1_process_end;
	}
	ret = hal_crypto_sha1_process((u8 *)msg_addr, msglen, pDigest);
crypto_sha1_process_end:
	return ret;
}

int crypto_sha1_update(const uint8_t *message, const uint32_t msglen)
{
	int ret;
	u32 msg_addr;
	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_sha1_update_end;
	}
	ret = hal_crypto_sha1_update((u8 *)msg_addr, msglen);
crypto_sha1_update_end:
	return ret;
}

int crypto_sha1_final(uint8_t *pDigest)
{
	int ret;

	ret = hal_crypto_sha1_final(pDigest);
	return ret;
}

//Auth SHA2_224
int crypto_sha2_224(const uint8_t *message, const uint32_t msglen, uint8_t *pDigest)
{
	int ret;
	u32 msg_addr;
	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_sha2_224_end;
	}
	ret = hal_crypto_sha2_224((u8 *)msg_addr, msglen, pDigest);
crypto_sha2_224_end:
	return ret;
}

int crypto_sha2_224_init(void)
{
	int ret;

	ret = hal_crypto_sha2_224_init();
	return ret;
}

int crypto_sha2_224_process(const uint8_t *message, const uint32_t msglen, uint8_t *pDigest)
{
	int ret;
	u32 msg_addr;
	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_sha2_224_process_end;
	}
	ret = hal_crypto_sha2_224_process((u8 *)msg_addr, msglen, pDigest);
crypto_sha2_224_process_end:
	return ret;
}

int crypto_sha2_224_update(const uint8_t *message, const uint32_t msglen)
{
	int ret;
	u32 msg_addr;
	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_sha2_224_update_end;
	}
	ret = hal_crypto_sha2_224_update((u8 *)msg_addr, msglen);
crypto_sha2_224_update_end:
	return ret;
}

int crypto_sha2_224_final(uint8_t *pDigest)
{
	int ret;

	ret = hal_crypto_sha2_224_final(pDigest);
	return ret;
}

//Auth SHA2_256
int crypto_sha2_256(const uint8_t *message, const uint32_t msglen, uint8_t *pDigest)
{
	int ret;
	u32 msg_addr;
	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_sha2_256_end;
	}
	ret = hal_crypto_sha2_256((u8 *)msg_addr, msglen, pDigest);
crypto_sha2_256_end:
	return ret;
}

int crypto_sha2_256_init(void)
{
	int ret;

	ret = hal_crypto_sha2_256_init();
	return ret;
}

int crypto_sha2_256_process(const uint8_t *message, const uint32_t msglen, uint8_t *pDigest)
{
	int ret;
	u32 msg_addr;
	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_sha2_256_process_end;
	}
	ret = hal_crypto_sha2_256_process((u8 *)msg_addr, msglen, pDigest);
crypto_sha2_256_process_end:
	return ret;
}

int crypto_sha2_256_update(const uint8_t *message, const uint32_t msglen)
{
	int ret;
	u32 msg_addr;
	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_sha2_256_update_end;
	}
	ret = hal_crypto_sha2_256_update((u8 *)msg_addr, msglen);
crypto_sha2_256_update_end:
	return ret;
}

int crypto_sha2_256_final(uint8_t *pDigest)
{
	int ret;

	ret = hal_crypto_sha2_256_final(pDigest);
	return ret;
}

//Auth HMAC_MD5
int crypto_hmac_md5(const uint8_t *message, const uint32_t msglen,
					const uint8_t *key, const uint32_t keylen, uint8_t *pDigest)
{
	int ret;
	u32 msg_addr, key_addr;

	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_hmac_md5_end;
	}
	ret = xip_flash_remap_check(key, &key_addr, keylen);
	if (ret != SUCCESS) {
		goto crypto_hmac_md5_end;
	}
	ret = hal_crypto_hmac_md5((u8 *)msg_addr, msglen, (u8 *)key_addr, keylen, pDigest);
crypto_hmac_md5_end:
	return ret;
}

int crypto_hmac_md5_init(const uint8_t *key, const uint32_t keylen)
{
	int ret;
	u32 key_addr;

	ret = xip_flash_remap_check(key, &key_addr, keylen);
	if (ret != SUCCESS) {
		goto crypto_hmac_md5_init_end;
	}
	ret = hal_crypto_hmac_md5_init((u8 *)key_addr, keylen);
crypto_hmac_md5_init_end:
	return ret;
}

int crypto_hmac_md5_process(const uint8_t *message, const uint32_t msglen, uint8_t *pDigest)
{
	int ret;
	u32 msg_addr;

	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_hmac_md5_process_end;
	}
	ret = hal_crypto_hmac_md5_process((u8 *)msg_addr, msglen, pDigest);
crypto_hmac_md5_process_end:
	return ret;
}

int crypto_hmac_md5_update(const uint8_t *message, const uint32_t msglen)
{
	int ret;
	u32 msg_addr;

	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_hmac_md5_update_end;
	}
	ret = hal_crypto_hmac_md5_update((u8 *)msg_addr, msglen);
crypto_hmac_md5_update_end:
	return ret;
}

int crypto_hmac_md5_final(uint8_t *pDigest)
{
	int ret;

	ret = hal_crypto_hmac_md5_final(pDigest);
	return ret;
}

//Auth HMAC_SHA1
int crypto_hmac_sha1(const uint8_t *message, const uint32_t msglen,
					 const uint8_t *key, const uint32_t keylen, uint8_t *pDigest)
{
	int ret;
	u32 msg_addr, key_addr;

	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_hmac_sha1_end;
	}
	ret = xip_flash_remap_check(key, &key_addr, keylen);
	if (ret != SUCCESS) {
		goto crypto_hmac_sha1_end;
	}
	ret = hal_crypto_hmac_sha1((u8 *)msg_addr, msglen, (u8 *)key_addr, keylen, pDigest);
crypto_hmac_sha1_end:
	return ret;
}

int crypto_hmac_sha1_init(const uint8_t *key, const uint32_t keylen)
{
	int ret;
	u32 key_addr;

	ret = xip_flash_remap_check(key, &key_addr, keylen);
	if (ret != SUCCESS) {
		goto crypto_hmac_sha1_init_end;
	}
	ret = hal_crypto_hmac_sha1_init((u8 *)key_addr, keylen);
crypto_hmac_sha1_init_end:
	return ret;
}

int crypto_hmac_sha1_process(const uint8_t *message, const uint32_t msglen, uint8_t *pDigest)
{
	int ret;
	u32 msg_addr;

	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_hmac_sha1_process_end;
	}
	ret = hal_crypto_hmac_sha1_process((u8 *)msg_addr, msglen, pDigest);
crypto_hmac_sha1_process_end:
	return ret;
}

int crypto_hmac_sha1_update(const uint8_t *message, const uint32_t msglen)
{
	int ret;
	u32 msg_addr;

	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_hmac_sha1_update_end;
	}
	ret = hal_crypto_hmac_sha1_update((u8 *)msg_addr, msglen);
crypto_hmac_sha1_update_end:
	return ret;
}

int crypto_hmac_sha1_final(uint8_t *pDigest)
{
	int ret;

	ret = hal_crypto_hmac_sha1_final(pDigest);
	return ret;
}

//Auth HMAC_SHA2_224
int crypto_hmac_sha2_224(const uint8_t *message, const uint32_t msglen,
						 const uint8_t *key, const uint32_t keylen, uint8_t *pDigest)
{
	int ret;
	u32 msg_addr, key_addr;

	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_hmac_sha2_224_end;
	}
	ret = xip_flash_remap_check(key, &key_addr, keylen);
	if (ret != SUCCESS) {
		goto crypto_hmac_sha2_224_end;
	}
	ret = hal_crypto_hmac_sha2_224((u8 *)msg_addr, msglen, (u8 *)key_addr, keylen, pDigest);
crypto_hmac_sha2_224_end:
	return ret;
}

int crypto_hmac_sha2_224_init(const uint8_t *key, const uint32_t keylen)
{
	int ret;
	u32 key_addr;

	ret = xip_flash_remap_check(key, &key_addr, keylen);
	if (ret != SUCCESS) {
		goto crypto_hmac_sha2_224_init_end;
	}
	ret = hal_crypto_hmac_sha2_224_init((u8 *)key_addr, keylen);
crypto_hmac_sha2_224_init_end:
	return ret;
}

int crypto_hmac_sha2_224_process(const uint8_t *message, const uint32_t msglen, uint8_t *pDigest)
{
	int ret;
	u32 msg_addr;

	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_hmac_sha2_224_process_end;
	}
	ret = hal_crypto_hmac_sha2_224_process((u8 *)msg_addr, msglen, pDigest);
crypto_hmac_sha2_224_process_end:
	return ret;
}

int crypto_hmac_sha2_224_update(const uint8_t *message, const uint32_t msglen)
{
	int ret;
	u32 msg_addr;

	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_hmac_sha2_224_update_end;
	}
	ret = hal_crypto_hmac_sha2_224_update((u8 *)msg_addr, msglen);
crypto_hmac_sha2_224_update_end:
	return ret;
}

int crypto_hmac_sha2_224_final(uint8_t *pDigest)
{
	int ret;

	ret = hal_crypto_hmac_sha2_224_final(pDigest);
	return ret;
}

//Auth HMAC_SHA2_256
int crypto_hmac_sha2_256(const uint8_t *message, const uint32_t msglen,
						 const uint8_t *key, const uint32_t keylen, uint8_t *pDigest)
{
	int ret;
	u32 msg_addr, key_addr;

	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_hmac_sha2_256_end;
	}
	ret = xip_flash_remap_check(key, &key_addr, keylen);
	if (ret != SUCCESS) {
		goto crypto_hmac_sha2_256_end;
	}

	ret = hal_crypto_hmac_sha2_256((u8 *)msg_addr, msglen, (u8 *)key_addr, keylen, pDigest);
crypto_hmac_sha2_256_end:
	return ret;
}

int crypto_hmac_sha2_256_init(const uint8_t *key, const uint32_t keylen)
{
	int ret;
	u32 key_addr;

	ret = xip_flash_remap_check(key, &key_addr, keylen);
	if (ret != SUCCESS) {
		goto crypto_hmac_sha2_256_init_end;
	}
	ret = hal_crypto_hmac_sha2_256_init((u8 *)key_addr, keylen);
crypto_hmac_sha2_256_init_end:
	return ret;
}

int crypto_hmac_sha2_256_process(const uint8_t *message, const uint32_t msglen, uint8_t *pDigest)
{
	int ret;
	u32 msg_addr;

	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_hmac_sha2_256_process_end;
	}
	ret = hal_crypto_hmac_sha2_256_process((u8 *)msg_addr, msglen, pDigest);
crypto_hmac_sha2_256_process_end:
	return ret;
}

int crypto_hmac_sha2_256_update(const uint8_t *message, const uint32_t msglen)
{
	int ret;
	u32 msg_addr;

	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_hmac_sha2_256_update_end;
	}
	ret = hal_crypto_hmac_sha2_256_update((u8 *)msg_addr, msglen);
crypto_hmac_sha2_256_update_end:
	return ret;
}

int crypto_hmac_sha2_256_final(uint8_t *pDigest)
{
	int ret;

	ret = hal_crypto_hmac_sha2_256_final(pDigest);
	return ret;
}

// AES-ECB
int crypto_aes_ecb_init(const uint8_t *key, const uint32_t keylen)
{
	int ret;
	u32 key_addr;

	ret = xip_flash_remap_check(key, &key_addr, keylen);
	if (ret != SUCCESS) {
		goto crypto_aes_ecb_init_end;
	}
	ret = hal_crypto_aes_ecb_init((u8 *)key_addr, keylen);
crypto_aes_ecb_init_end:
	return ret;
}

int crypto_aes_ecb_encrypt(const uint8_t *message, const uint32_t msglen,
						   const uint8_t *iv, const uint32_t ivlen, uint8_t *pResult)
{
	int ret;
	u32 msg_addr, iv_addr;

	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_aes_ecb_encrypt_end;
	}
	ret = xip_flash_remap_check(iv, &iv_addr, ivlen);
	if (ret != SUCCESS) {
		goto crypto_aes_ecb_encrypt_end;
	}
	ret = hal_crypto_aes_ecb_encrypt((u8 *)msg_addr, msglen, (u8 *)iv_addr, ivlen, pResult);
crypto_aes_ecb_encrypt_end:
	return ret;
}

int crypto_aes_ecb_decrypt(const uint8_t *message, const uint32_t msglen,
						   const uint8_t *iv, const uint32_t ivlen, uint8_t *pResult)
{
	int ret;
	u32 msg_addr, iv_addr;

	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_aes_ecb_decrypt_end;
	}
	ret = xip_flash_remap_check(iv, &iv_addr, ivlen);
	if (ret != SUCCESS) {
		goto crypto_aes_ecb_decrypt_end;
	}
	ret = hal_crypto_aes_ecb_decrypt((u8 *)msg_addr, msglen, (u8 *)iv_addr, ivlen, pResult);
crypto_aes_ecb_decrypt_end:
	return ret;
}

// AES-CBC
int crypto_aes_cbc_init(const uint8_t *key, const uint32_t keylen)
{
	int ret;
	u32 key_addr;

	ret = xip_flash_remap_check(key, &key_addr, keylen);
	if (ret != SUCCESS) {
		goto crypto_aes_cbc_init_end;
	}
	ret = hal_crypto_aes_cbc_init((u8 *)key_addr, keylen);
crypto_aes_cbc_init_end:
	return ret;
}

int crypto_aes_cbc_encrypt(const uint8_t *message, const uint32_t msglen,
						   const uint8_t *iv, const uint32_t ivlen, uint8_t *pResult)
{
	int ret;
	u32 msg_addr, iv_addr;

	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_aes_cbc_encrypt_end;
	}
	ret = xip_flash_remap_check(iv, &iv_addr, ivlen);
	if (ret != SUCCESS) {
		goto crypto_aes_cbc_encrypt_end;
	}
	ret = hal_crypto_aes_cbc_encrypt((u8 *)msg_addr, msglen, (u8 *)iv_addr, ivlen, pResult);
crypto_aes_cbc_encrypt_end:
	return ret;
}

int crypto_aes_cbc_decrypt(const uint8_t *message, const uint32_t msglen,
						   const uint8_t *iv, const uint32_t ivlen, uint8_t *pResult)
{
	int ret;
	u32 msg_addr, iv_addr;

	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_aes_cbc_decrypt_end;
	}
	ret = xip_flash_remap_check(iv, &iv_addr, ivlen);
	if (ret != SUCCESS) {
		goto crypto_aes_cbc_decrypt_end;
	}
	ret = hal_crypto_aes_cbc_decrypt((u8 *)msg_addr, msglen, (u8 *)iv_addr, ivlen, pResult);
crypto_aes_cbc_decrypt_end:
	return ret;
}

// AES-CTR
int crypto_aes_ctr_init(const uint8_t *key, const uint32_t keylen)
{
	int ret;
	u32 key_addr;

	ret = xip_flash_remap_check(key, &key_addr, keylen);
	if (ret != SUCCESS) {
		goto crypto_aes_ctr_init_end;
	}
	ret = hal_crypto_aes_ctr_init((u8 *)key_addr, keylen);
crypto_aes_ctr_init_end:
	return ret;
}

int crypto_aes_ctr_encrypt(const uint8_t *message, const uint32_t msglen,
						   const uint8_t *iv, const uint32_t ivlen, uint8_t *pResult)
{
	int ret;
	u32 msg_addr, iv_addr;

	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_aes_ctr_encrypt_end;
	}
	ret = xip_flash_remap_check(iv, &iv_addr, ivlen);
	if (ret != SUCCESS) {
		goto crypto_aes_ctr_encrypt_end;
	}
	ret = hal_crypto_aes_ctr_encrypt((u8 *)msg_addr, msglen, (u8 *)iv_addr, ivlen, pResult);
crypto_aes_ctr_encrypt_end:
	return ret;
}

int crypto_aes_ctr_decrypt(const uint8_t *message, const uint32_t msglen,
						   const uint8_t *iv, const uint32_t ivlen, uint8_t *pResult)
{
	int ret;
	u32 msg_addr, iv_addr;

	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_aes_ctr_decrypt_end;
	}
	ret = xip_flash_remap_check(iv, &iv_addr, ivlen);
	if (ret != SUCCESS) {
		goto crypto_aes_ctr_decrypt_end;
	}
	ret = hal_crypto_aes_ctr_decrypt((u8 *)msg_addr, msglen, (u8 *)iv_addr, ivlen, pResult);
crypto_aes_ctr_decrypt_end:
	return ret;
}

// AES-CFB
int crypto_aes_cfb_init(const uint8_t *key, const uint32_t keylen)
{
	int ret;
	u32 key_addr;

	ret = xip_flash_remap_check(key, &key_addr, keylen);
	if (ret != SUCCESS) {
		goto crypto_aes_cfb_init_end;
	}
	ret = hal_crypto_aes_cfb_init((u8 *)key_addr, keylen);
crypto_aes_cfb_init_end:
	return ret;
}

int crypto_aes_cfb_encrypt(const uint8_t *message, const uint32_t msglen,
						   const uint8_t *iv, const uint32_t ivlen, uint8_t *pResult)
{
	int ret;
	u32 msg_addr, iv_addr;

	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_aes_cfb_encrypt_end;
	}
	ret = xip_flash_remap_check(iv, &iv_addr, ivlen);
	if (ret != SUCCESS) {
		goto crypto_aes_cfb_encrypt_end;
	}
	ret = hal_crypto_aes_cfb_encrypt((u8 *)msg_addr, msglen, (u8 *)iv_addr, ivlen, pResult);
crypto_aes_cfb_encrypt_end:
	return ret;
}

int crypto_aes_cfb_decrypt(const uint8_t *message, const uint32_t msglen,
						   const uint8_t *iv, const uint32_t ivlen, uint8_t *pResult)
{
	int ret;
	u32 msg_addr, iv_addr;

	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_aes_cfb_decrypt_end;
	}
	ret = xip_flash_remap_check(iv, &iv_addr, ivlen);
	if (ret != SUCCESS) {
		goto crypto_aes_cfb_decrypt_end;
	}
	ret = hal_crypto_aes_cfb_decrypt((u8 *)msg_addr, msglen, (u8 *)iv_addr, ivlen, pResult);
crypto_aes_cfb_decrypt_end:
	return ret;
}

// AES-OFB
int crypto_aes_ofb_init(const uint8_t *key, const uint32_t keylen)
{
	int ret;
	u32 key_addr;

	ret = xip_flash_remap_check(key, &key_addr, keylen);
	if (ret != SUCCESS) {
		goto crypto_aes_ofb_init_end;
	}
	ret = hal_crypto_aes_ofb_init((u8 *)key_addr, keylen);
crypto_aes_ofb_init_end:
	return ret;
}

int crypto_aes_ofb_encrypt(const uint8_t *message, const uint32_t msglen,
						   const uint8_t *iv, const uint32_t ivlen, uint8_t *pResult)
{
	int ret;
	u32 msg_addr, iv_addr;

	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_aes_ofb_encrypt_end;
	}
	ret = xip_flash_remap_check(iv, &iv_addr, ivlen);
	if (ret != SUCCESS) {
		goto crypto_aes_ofb_encrypt_end;
	}
	ret = hal_crypto_aes_ofb_encrypt((u8 *)msg_addr, msglen, (u8 *)iv_addr, ivlen, pResult);
crypto_aes_ofb_encrypt_end:
	return ret;
}

int crypto_aes_ofb_decrypt(const uint8_t *message, const uint32_t msglen,
						   const uint8_t *iv, const uint32_t ivlen, uint8_t *pResult)
{
	int ret;
	u32 msg_addr, iv_addr;

	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_aes_ofb_decrypt_end;
	}
	ret = xip_flash_remap_check(iv, &iv_addr, ivlen);
	if (ret != SUCCESS) {
		goto crypto_aes_ofb_decrypt_end;
	}
	ret = hal_crypto_aes_ofb_decrypt((u8 *)msg_addr, msglen, (u8 *)iv_addr, ivlen, pResult);
crypto_aes_ofb_decrypt_end:
	return ret;
}

// AES-GHASH
int crypto_aes_ghash(const uint8_t *message, const uint32_t msglen,
					 const uint8_t *key, const uint32_t keylen, uint8_t *pDigest)
{
	int ret;
	u32 msg_addr, key_addr;

	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_aes_ghash_end;
	}
	ret = xip_flash_remap_check(key, &key_addr, keylen);
	if (ret != SUCCESS) {
		goto crypto_aes_ghash_end;
	}
	ret = hal_crypto_aes_ghash((u8 *)msg_addr, msglen, (u8 *)key_addr, keylen, pDigest);
crypto_aes_ghash_end:
	return ret;
}

int crypto_aes_ghash_init(const uint8_t *key, const uint32_t keylen)
{
	int ret;
	u32 key_addr;

	ret = xip_flash_remap_check(key, &key_addr, keylen);
	if (ret != SUCCESS) {
		goto crypto_aes_ghash_init_end;
	}
	ret = hal_crypto_aes_ghash_init((u8 *)key_addr, keylen);
crypto_aes_ghash_init_end:
	return ret;
}

int crypto_aes_ghash_process(const uint8_t *message, const uint32_t msglen, uint8_t *pDigest)
{
	int ret;
	u32 msg_addr;

	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_aes_ghash_process_end;
	}
	ret = hal_crypto_aes_ghash_process((u8 *)msg_addr, msglen, pDigest);
crypto_aes_ghash_process_end:
	return ret;
}

// AES-GMAC
int crypto_aes_gmac(
	const uint8_t *message, const uint32_t msglen,
	const uint8_t *key, const uint32_t keylen,
	const uint8_t *iv,
	const uint8_t *aad, const uint32_t aadlen, uint8_t *pTag)
{
	int ret;
	u32 msg_addr, key_addr, iv_addr, aad_addr;

	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_aes_gmac_end;
	}
	ret = xip_flash_remap_check(key, &key_addr, keylen);
	if (ret != SUCCESS) {
		goto crypto_aes_gmac_end;
	}
	ret = xip_flash_remap_check(iv, &iv_addr, 12);
	if (ret != SUCCESS) {
		goto crypto_aes_gmac_end;
	}
	ret = xip_flash_remap_check(aad, &aad_addr, aadlen);
	if (ret != SUCCESS) {
		goto crypto_aes_gmac_end;
	}
	ret = hal_crypto_aes_gmac((u8 *)msg_addr, msglen, (u8 *)key_addr, keylen, (u8 *)iv_addr, (u8 *)aad_addr, aadlen, pTag);
crypto_aes_gmac_end:
	return ret;
}

int crypto_aes_gmac_init(const uint8_t *key, const uint32_t keylen)
{
	int ret;
	u32 key_addr;

	ret = xip_flash_remap_check(key, &key_addr, keylen);
	if (ret != SUCCESS) {
		goto crypto_aes_gmac_init_end;
	}
	ret = hal_crypto_aes_gmac_init((u8 *)key_addr, keylen);
crypto_aes_gmac_init_end:
	return ret;
}

int crypto_aes_gmac_process(
	const uint8_t *message, const uint32_t msglen,
	const uint8_t *iv, const uint8_t *aad, const uint32_t aadlen, uint8_t *pTag)
{
	int ret;
	u32 msg_addr, iv_addr, aad_addr;

	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_aes_gmac_process_end;
	}
	ret = xip_flash_remap_check(iv, &iv_addr, 12);
	if (ret != SUCCESS) {
		goto crypto_aes_gmac_process_end;
	}
	ret = xip_flash_remap_check(aad, &aad_addr, aadlen);
	if (ret != SUCCESS) {
		goto crypto_aes_gmac_process_end;
	}
	ret = hal_crypto_aes_gmac_process((u8 *)msg_addr, msglen, (u8 *)iv_addr, (u8 *)aad_addr, aadlen, pTag);
crypto_aes_gmac_process_end:
	return ret;
}

//AES-GCTR
int crypto_aes_gctr_init(const uint8_t *key, const uint32_t keylen)
{
	int ret;
	u32 key_addr;

	ret = xip_flash_remap_check(key, &key_addr, keylen);
	if (ret != SUCCESS) {
		goto crypto_aes_gctr_init_end;
	}
	ret = hal_crypto_aes_gctr_init((u8 *)key_addr, keylen);
crypto_aes_gctr_init_end:
	return ret;
}

int crypto_aes_gctr_encrypt(
	const uint8_t *message, const uint32_t msglen,
	const uint8_t *iv, uint8_t *pResult)
{
	int ret;
	u32 msg_addr, iv_addr;

	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_aes_gctr_encrypt_end;
	}
	ret = xip_flash_remap_check(iv, &iv_addr, 12);
	if (ret != SUCCESS) {
		goto crypto_aes_gctr_encrypt_end;
	}
	ret = hal_crypto_aes_gctr_encrypt((u8 *)msg_addr, msglen, (u8 *)iv_addr, pResult);
crypto_aes_gctr_encrypt_end:
	return ret;
}

int crypto_aes_gctr_decrypt(
	const uint8_t *message, const uint32_t msglen,
	const uint8_t *iv, uint8_t *pResult)
{
	int ret;
	u32 msg_addr, iv_addr;

	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_aes_gctr_decrypt_end;
	}
	ret = xip_flash_remap_check(iv, &iv_addr, 12);
	if (ret != SUCCESS) {
		goto crypto_aes_gctr_decrypt_end;
	}
	ret = hal_crypto_aes_gctr_decrypt((u8 *)msg_addr, msglen, (u8 *)iv_addr, pResult);
crypto_aes_gctr_decrypt_end:
	return ret;
}

// AES-GCM
int crypto_aes_gcm_init(const uint8_t *key, const uint32_t keylen)
{
	int ret;
	u32 key_addr;

	ret = xip_flash_remap_check(key, &key_addr, keylen);
	if (ret != SUCCESS) {
		goto crypto_aes_gcm_init_end;
	}
	ret = hal_crypto_aes_gcm_init((u8 *)key_addr, keylen);
crypto_aes_gcm_init_end:
	return ret;
}

int crypto_aes_gcm_encrypt(const uint8_t *message, const uint32_t msglen, const uint8_t *iv,
						   const uint8_t *aad, const uint32_t aadlen, uint8_t *pResult, uint8_t *pTag)
{
	int ret;
	u32 msg_addr, iv_addr, aad_addr;

	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_aes_gcm_encrypt_end;
	}
	ret = xip_flash_remap_check(iv, &iv_addr, 12);
	if (ret != SUCCESS) {
		goto crypto_aes_gcm_encrypt_end;
	}
	ret = xip_flash_remap_check(aad, &aad_addr, aadlen);
	if (ret != SUCCESS) {
		goto crypto_aes_gcm_encrypt_end;
	}
	ret = hal_crypto_aes_gcm_encrypt((u8 *)msg_addr, msglen, (u8 *)iv_addr, (u8 *)aad_addr, aadlen, pResult, pTag);
crypto_aes_gcm_encrypt_end:
	return ret;
}

int crypto_aes_gcm_decrypt(const uint8_t *message, const uint32_t msglen, const uint8_t *iv,
						   const uint8_t *aad, const uint32_t aadlen, uint8_t *pResult, uint8_t *pTag)
{
	int ret;
	u32 msg_addr, iv_addr, aad_addr;

	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_aes_gcm_decrypt_end;
	}
	ret = xip_flash_remap_check(iv, &iv_addr, 12);
	if (ret != SUCCESS) {
		goto crypto_aes_gcm_decrypt_end;
	}
	ret = xip_flash_remap_check(aad, &aad_addr, aadlen);
	if (ret != SUCCESS) {
		goto crypto_aes_gcm_decrypt_end;
	}
	ret = hal_crypto_aes_gcm_decrypt((u8 *)msg_addr, msglen, (u8 *)iv_addr, (u8 *)aad_addr, aadlen, pResult, pTag);
crypto_aes_gcm_decrypt_end:
	return ret;
}

// CHACHA20
int crypto_chacha_init(const uint8_t *key)
{
	int ret;

	ret = hal_crypto_chacha_init(key);
	return ret;
}

int crypto_chacha_encrypt(const uint8_t *message, const uint32_t msglen,
						  const uint8_t *iv, const uint32_t count, uint8_t *pResult)
{
	int ret;

	ret = hal_crypto_chacha_encrypt(message, msglen, iv, count, pResult);
	return ret;
}

int crypto_chacha_decrypt(const uint8_t *message, const uint32_t msglen,
						  const uint8_t *iv, const uint32_t count, uint8_t *pResult)
{
	int ret;

	ret = hal_crypto_chacha_decrypt(message, msglen, iv, count, pResult);
	return ret;
}


int crypto_poly1305(const uint8_t *message, const uint32_t msglen, const uint8_t *key, uint8_t *pDigest)
{
	int ret;

	ret = hal_crypto_poly1305(message, msglen, key, pDigest);
	return ret;
}

int crypto_poly1305_init(const uint8_t *key)
{
	int ret;

	ret = hal_crypto_poly1305_init(key);
	return ret;
}

int crypto_poly1305_process(const uint8_t *message, const uint32_t msglen, uint8_t *pDigest)
{
	int ret;

	ret = hal_crypto_poly1305_process(message, msglen, pDigest);
	return ret;
}

// CHACHA+POLY1305
int crypto_chacha_poly1305_init(const uint8_t *key)
{
	int ret;

	ret = hal_crypto_chacha_poly1305_init(key);
	return ret;
}

int crypto_chacha_poly1305_encrypt(const uint8_t *message, const uint32_t msglen, const uint8_t *nonce,
								   const uint8_t *aad, const uint32_t aadlen, uint8_t *pResult, uint8_t *pTag)
{
	int ret;

	ret = hal_crypto_chacha_poly1305_encrypt(message, msglen, nonce, aad, aadlen, pResult, pTag);
	return ret;
}

int crypto_chacha_poly1305_decrypt(const uint8_t *message, const uint32_t msglen, const uint8_t *nonce,
								   const uint8_t *aad, const uint32_t aadlen, uint8_t *pResult, uint8_t *pTag)
{
	int ret;

	ret = hal_crypto_chacha_poly1305_decrypt(message, msglen, nonce, aad, aadlen, pResult, pTag);
	return ret;
}

// crc
int crypto_crc32_cmd(const uint8_t *message, const uint32_t msglen, uint32_t *pCrc)
{
	int ret;

	ret = hal_crypto_crc32_cmd(message, msglen, pCrc);
	return ret;
}

int crypto_crc32_dma(const uint8_t *message, const uint32_t msglen, uint32_t *pCrc)
{
	int ret;
	u32 msg_addr;
	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_crc32_dma_end;
	}
	ret = hal_crypto_crc32_dma((u8 *)msg_addr, msglen, pCrc);
crypto_crc32_dma_end:
	return ret;
}

int crypto_crc_setting(int order, unsigned long polynom, unsigned long crcinit,
					   unsigned long crcxor, int refin, int refout)
{
	int ret;

	ret = hal_crypto_crc_setting(order, polynom, crcinit, crcxor, refin, refout);
	return ret;
}

int crypto_crc_cmd(const uint8_t *message, const uint32_t msglen, uint32_t *pCrc)
{
	int ret;

	ret = hal_crypto_crc_cmd(message, msglen, pCrc);
	return ret;
}

int crypto_crc_dma(const uint8_t *message, const uint32_t msglen, uint32_t *pCrc)
{
	int ret;
	u32 msg_addr;
	ret = xip_flash_remap_check(message, &msg_addr, msglen);
	if (ret != SUCCESS) {
		goto crypto_crc_dma_end;
	}
	ret = hal_crypto_crc_dma((u8 *)msg_addr, msglen, pCrc);
crypto_crc_dma_end:
	return ret;
}

#if !defined(CONFIG_BUILD_NONSECURE)

static int crypto_hkdf_extract(const uint8_t *salt, size_t salt_len, const uint8_t *ikm, size_t ikm_len, uint8_t *prk)
{
	uint8_t null_salt[64];
	int ret;

	if (salt == NULL) {
		salt = (uint8_t *)(((((uint32_t)null_salt - 1) >> 5) + 1) << 5);   // make salt always is a 32-byte aligned address
		salt_len = 32;
		memset((void *)salt, 0, salt_len);
	}

	// salt = key, salt_len = key_len
	ret = crypto_hmac_sha2_256_init(salt, salt_len);
	if (ret != SUCCESS) {
		goto __hkdf_extract_exit;
	}

	ret = crypto_hmac_sha2_256_update(ikm, ikm_len);
	if (ret != SUCCESS) {
		goto __hkdf_extract_exit;
	}

	ret = crypto_hmac_sha2_256_final(prk);

__hkdf_extract_exit:
	return (ret);
}

static int crypto_hkdf_expand(const uint8_t *prk, size_t prk_len, const uint8_t *info, size_t info_len,
							  uint8_t *okm, size_t okm_len)
{
	const size_t hash_len = 32;
	size_t where = 0;
	size_t n;
	size_t t_len = 0;
	size_t i;
	int32_t ret = 0;
	uint8_t t_buf[64];
	uint8_t *t;
	const size_t t_buf_len = 32;

	t = (uint8_t *)(((((uint32_t)t_buf - 1) >> 5) + 1) << 5);   // make t always is a 32-byte aligned address

	if (info == NULL) {
		info = (const unsigned char *) "";
		info_len = 0;
	}

	n = okm_len / hash_len;

	if ((okm_len % hash_len) != 0) {
		n++;
	}

	/*
	 * Per RFC 5869 Section 2.3, okm_len must not exceed
	 * 255 times the hash length
	 */
	if (n > 255) {
		ret =  -HAL_ERR_PARA;
		goto __hkdf_expand_exit;
	}

	/*
	 * Compute T = T(1) | T(2) | T(3) | ... | T(N)
	 * Where T(N) is defined in RFC 5869 Section 2.3
	 */
	for (i = 1; i <= n; i++) {
		size_t num_to_copy;
		unsigned char c = i & 0xff;

		ret = crypto_hmac_sha2_256_init(prk, prk_len);
		if (ret != SUCCESS) {
			goto __hkdf_expand_exit;
		}

		if (t_len > 0) {
			ret = crypto_hmac_sha2_256_update(t, t_len);
			if (ret != SUCCESS) {
				goto __hkdf_expand_exit;
			}
		}

		ret = crypto_hmac_sha2_256_update(info, info_len);
		if (ret != SUCCESS) {
			goto __hkdf_expand_exit;
		}

		/* The constant concatenated to the end of each T(n) is a single octet.
		 * */
		ret = crypto_hmac_sha2_256_update(&c, 1);
		if (ret != SUCCESS) {
			goto __hkdf_expand_exit;
		}

		ret = crypto_hmac_sha2_256_final(t);
		if (ret != SUCCESS) {
			goto __hkdf_expand_exit;
		}

		num_to_copy = i != n ? hash_len : okm_len - where;
		memcpy(okm + where, t, num_to_copy);
		where += hash_len;
		t_len = hash_len;
	}

__hkdf_expand_exit:
	memset(t, 0, t_buf_len);

	return (ret);
}

int crypto_hkdf_derive(const uint8_t *salt, size_t salt_len, const uint8_t *ikm, size_t ikm_len,
					   const uint8_t *info, size_t info_len, uint8_t *okm, size_t okm_len)
{
	int32_t ret;
	uint8_t prk_buf[64];
	uint8_t *prk;
	const size_t prk_len = 32;

	prk = (uint8_t *)(((((uint32_t)prk_buf - 1) >> 5) + 1) << 5);   // make prk always is a 32-byte aligned address
	ret = crypto_hkdf_extract(salt, salt_len, ikm, ikm_len, prk);

	if (ret == SUCCESS) {
		ret = crypto_hkdf_expand(prk, 32, info, info_len, okm, okm_len);
	}

	memset(prk, 0, prk_len);

	return (ret);
}

int crypto_random_seed(uint8_t *seed_buf, uint32_t seed_size)
{
	hal_status_t ret = SUCCESS;
	if ((seed_size == 0) || (seed_buf == NULL)) {
		return -30;
	} else {
		ret = hal_trng_sec_get_rand_seed(seed_buf, seed_size);
		if (ret == HAL_OK) {
			ret = SUCCESS;
		}
	}
	return ret;
}

int crypto_random_generate(uint8_t *rn_buf, uint32_t rn_size)
{
#define RNG_KEY_LEN         32
#define RNG_NONCE_LEN       16
#define RNG_SALT_LEN        32

	int ret;
	uint8_t key_buf[RNG_KEY_LEN + 31];
	uint8_t nonce[RNG_NONCE_LEN + 31];
#if (RNG_SALT_LEN > 0)
	uint8_t salt[RNG_SALT_LEN + 31];
#endif
	uint8_t *pkey_buf;
	uint8_t *pnonce;
	uint8_t *psalt;
	pkey_buf = (uint8_t *)(((((uint32_t)key_buf - 1) >> 5) + 1) << 5);
	pnonce = (uint8_t *)(((((uint32_t)nonce - 1) >> 5) + 1) << 5);
	ret = crypto_random_seed(pkey_buf, RNG_KEY_LEN);
	if ((ret != SUCCESS) || ret != HAL_OK) {
		goto __random_generate_exit;
	}
	ret = crypto_random_seed(pnonce, RNG_NONCE_LEN);
	if ((ret != SUCCESS) || ret != HAL_OK) {
		goto __random_generate_exit;
	}
#if (RNG_SALT_LEN > 0)
	psalt = (uint8_t *)(((((uint32_t)salt - 1) >> 5) + 1) << 5);
	ret = crypto_random_seed(psalt, RNG_SALT_LEN);
	if ((ret != SUCCESS) || ret != HAL_OK) {
		goto __random_generate_exit;
	}
#else
	psalt = NULL;
#endif
	ret = crypto_hkdf_derive(psalt, RNG_SALT_LEN, pkey_buf, RNG_KEY_LEN, pnonce, RNG_NONCE_LEN, rn_buf, rn_size);
	if (ret != SUCCESS) {
		goto __random_generate_exit;
	}
__random_generate_exit:

	memset(key_buf, 0, RNG_KEY_LEN + 31);
	memset(nonce, 0, RNG_NONCE_LEN + 31);
#if (RNG_SALT_LEN > 0)
	memset(salt, 0, RNG_SALT_LEN + 31);
#endif
	return ret;
}

#endif      // end of "#if !defined(CONFIG_BUILD_NONSECURE)"

#if defined(CONFIG_BUILD_SECURE)

SECTION_NS_ENTRY_FUNC
int NS_ENTRY crypto_random_generate_nsc(uint8_t *rn_buf, uint32_t rn_size)
{
	static uint32_t crypto_inited = 0;
	int ret;
	if (crypto_inited == 0) {
		ret = crypto_init();
		if (ret != SUCCESS) {
			goto __random_generate_nsc_exit;
		} else {
			crypto_inited = 1;
		}
	}

	ret = crypto_random_generate(rn_buf, rn_size);
__random_generate_nsc_exit:

	return ret;
}  // end of "#if defined(CONFIG_BUILD_SECURE)"
#elif defined(CONFIG_BUILD_NONSECURE)

int crypto_random_generate(uint8_t *rn_buf, uint32_t rn_size)
{
	int ret = crypto_random_generate_nsc(rn_buf, rn_size);
	return ret;
}
#endif  // end of "#if defined(CONFIG_BUILD_NONSECURE)"


#ifdef  __cplusplus
}
#endif

#endif
