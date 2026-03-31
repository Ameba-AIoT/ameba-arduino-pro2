/**************************************************************************//**
 * @file      hal_eddsa.c
 * @brief     This EdDSA secure and non-secure HAL API functions.
 * @version   V1.00
 * @date      2021-06-04
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
 * limitations under the License. *
 *
 ******************************************************************************/
#include "platform_conf.h"
#include "cmsis.h"
#include "rtl8735b_eddsa.h"
#include "rtl8735b_eddsa_type.h"
#include "rtl8735b_eddsa_ctrl.h"
#include "hal.h"
#include "hal_eddsa.h"
#include "hal_sys_ctrl.h"
#if defined(CONFIG_BUILD_NONSECURE) && (CONFIG_BUILD_NONSECURE == 1)
#include "hal_sys_ctrl_nsc.h"
#endif

#if CONFIG_EDDSA_EN

/**
 * @addtogroup hs_hal_crypto CRYPTO
 * @{
 */

hal_crypto_eddsa_t cryptoEDDSA_obj;
extern hal_eddsa_func_stubs_t hal_eddsa_stubs;

/** @} */ /* End of group hs_hal_crypto */

/**
 * @addtogroup hs_hal_crypto CRYPTO
 * @{
 */

#if defined(CONFIG_BUILD_NONSECURE) && (CONFIG_BUILD_NONSECURE == 1)
#undef EDDSA_MODULE
#define EDDSA_MODULE (EDDSA_NS_MODULE)

#undef EDDSA_REG_BASE
#define EDDSA_REG_BASE (EDDSA_NS_BASE)

#else

#undef EDDSA_MODULE
#define EDDSA_MODULE (EDDSA_S_MODULE)

#undef EDDSA_REG_BASE
#define EDDSA_REG_BASE (EDDSA_S_BASE)
#endif

#if IS_CUT_TEST(CONFIG_CHIP_VER)
int hal_eddsa_engine_init(uint32_t hash_callback, uint32_t decompress_pbk_callback)
{
	hal_crypto_eddsa_t *peddsa_adapter = &cryptoEDDSA_obj;
	int ret = SUCCESS;
	DBG_EDDSA_INFO("hash_callbcak = 0x%x, decompress_pbk_callback = 0x%x\r\n", hash_callback, decompress_pbk_callback);
	memset(peddsa_adapter, 0x0, sizeof(hal_crypto_eddsa_t));
	peddsa_adapter->base_addr = EDDSA_MODULE;
	//peddsa_adapter->hash_exec_func = hal_eddsa_hash_sha512;
	peddsa_adapter->hash_exec_func = (void *)hash_callback;
	//peddsa_adapter->decompress_exec_func = hal_eddsa_decompress_pbk;
	peddsa_adapter->decompress_exec_func = (void *)decompress_pbk_callback;
	peddsa_adapter->clk_func_en = hal_sys_peripheral_en;
	peddsa_adapter->clk_func_id = EDDSA_SYS;
	peddsa_adapter->clk_func_en(peddsa_adapter->clk_func_id, 1);
	// TODO
	// Use systemctl-enable engine?

	return ret;
}

#else
int hal_eddsa_engine_init(uint8_t hash_crypto_sel)
{
	int ret = SUCCESS;
	int32_t cryp_ret;
	hal_crypto_eddsa_t *peddsa_adtr = &cryptoEDDSA_obj;
	memset(peddsa_adtr, 0x0, sizeof(hal_crypto_eddsa_t));
	peddsa_adtr->base_addr = EDDSA_MODULE;
	peddsa_adtr->isMemDump = DISABLE;

	if (EDDSA_HASH_CRYPTO_HW_SEL_EN == hash_crypto_sel) {
		// init ceypto engine
		cryp_ret = hal_crypto_engine_chk_init();
		if (TRUE != cryp_ret) {
			cryp_ret = hal_crypto_engine_init();
			if (cryp_ret != SUCCESS) {
				DBG_EDDSA_ERR("hkdf: HW Crypto init fail!\r\n");
				return HAL_ERR_HW;
			} else {
				peddsa_adtr->isHWCrypto_Init = TRUE;
				peddsa_adtr->pcrypto_adtr = NULL;
			}
		} else {
			peddsa_adtr->isHWCrypto_Init = TRUE;
			peddsa_adtr->pcrypto_adtr = NULL;
		}
	}
	peddsa_adtr->hash_crypto_sel = hash_crypto_sel;
	hal_sys_peripheral_en(EDDSA_SYS, ENABLE);
	peddsa_adtr->isInit = _TRUE;
	ret = hal_eddsa_hook_hash_op_f(&hal_eddsa_sha2_512_init, &hal_eddsa_sha2_512_update, &hal_eddsa_sha2_512_final);
	hal_eddsa_stubs.hal_eddsa_hook_sign_vrf_hash_op_f(peddsa_adtr, NULL);

	//peddsa_adtr->decompress_exec_func = (void *)decompress_pbk_callback;
	peddsa_adtr->decompress_exec_func = NULL;
	return ret;
}

int hal_eddsa_hook_hash_op_f(eddsa_hash_init_func_t hash_init_f,
							 eddsa_hash_update_func_t hash_update_f, eddsa_hash_final_func_t hash_final_f)
{
	int ret = SUCCESS;
	hal_crypto_eddsa_t *peddsa_adtr = &cryptoEDDSA_obj;
	if (peddsa_adtr->isInit != _TRUE) {
		return HAL_NOT_READY; // not init yet
	}

	hal_eddsa_stubs.hal_eddsa_hash_init_hook(peddsa_adtr, hash_init_f);
	hal_eddsa_stubs.hal_eddsa_hash_update_hook(peddsa_adtr, hash_update_f);
	hal_eddsa_stubs.hal_eddsa_hash_final_hook(peddsa_adtr, hash_final_f);

	return ret;
}

void hal_eddsa_hook_sign_vrf_hash_op_f(eddsa_sign_vrf_hash_op sign_vrf_hash_f)
{

	hal_crypto_eddsa_t *peddsa_adtr = &cryptoEDDSA_obj;
	if (peddsa_adtr->isInit != _TRUE) {
		return; // not init yet
	}
	hal_eddsa_stubs.hal_eddsa_hook_sign_vrf_hash_op_f(peddsa_adtr, sign_vrf_hash_f);
}

int hal_eddsa_sha2_512_init(void *arg)
{
	hal_crypto_eddsa_t *peddsa_adtr = (hal_crypto_eddsa_t *)arg;
	int ret = SUCCESS;
	if (NULL == peddsa_adtr) {
		return HAL_ERR_PARA;
	}
	if (EDDSA_HASH_CRYPTO_HW_SEL_EN == peddsa_adtr->hash_crypto_sel) {
		if (TRUE != peddsa_adtr->isHWCrypto_Init) {
			ret = _ERRNO_EDDSA_CRYPTO_NULL_POINTER;
			return ret;
		}
		ret = hal_crypto_sha2_512_init();
	} else {
		ret = _ERRNO_EDDSA_CRYPTO_SW_NOT_READY;
	}
	return ret;
}

int hal_eddsa_sha2_512_update(void *arg, const uint8_t *message, const uint32_t msglen)
{
	hal_crypto_eddsa_t *peddsa_adtr = (hal_crypto_eddsa_t *)arg;
	int ret = SUCCESS;
	if (NULL == peddsa_adtr) {
		return HAL_ERR_PARA;
	}
	if (EDDSA_HASH_CRYPTO_HW_SEL_EN == peddsa_adtr->hash_crypto_sel) {
		if (TRUE != peddsa_adtr->isHWCrypto_Init) {
			ret = _ERRNO_EDDSA_CRYPTO_NULL_POINTER;
			return ret;
		}
		ret = hal_crypto_sha2_512_update(message, msglen);
	} else {
		ret = _ERRNO_EDDSA_CRYPTO_SW_NOT_READY;
	}
	return ret;
}

int hal_eddsa_sha2_512_final(void *arg, uint8_t *pDigest)
{
	hal_crypto_eddsa_t *peddsa_adtr = (hal_crypto_eddsa_t *)arg;
	int ret = SUCCESS;
	if (NULL == peddsa_adtr) {
		return HAL_ERR_PARA;
	}
	if (EDDSA_HASH_CRYPTO_HW_SEL_EN == peddsa_adtr->hash_crypto_sel) {
		if (TRUE != peddsa_adtr->isHWCrypto_Init) {
			ret = _ERRNO_EDDSA_CRYPTO_NULL_POINTER;
			return ret;
		}
		ret = hal_crypto_sha2_512_final(pDigest);
	} else {
		ret = _ERRNO_EDDSA_CRYPTO_SW_NOT_READY;
	}
	return ret;
}
#endif

int hal_eddsa_sign_verify(const unsigned char *sig, const unsigned char *msg,
						  const unsigned char *pk, const uint32_t msglen,
						  unsigned char mode_sel, unsigned char recover_en)
{
	hal_crypto_eddsa_t *peddsa_adapter = &cryptoEDDSA_obj;
	int ret;

	peddsa_adapter->p_pbk = (uint8_t *) pk;
	peddsa_adapter->p_signature = (uint8_t *) sig;
	peddsa_adapter->p_msg = (uint8_t *) msg;
	peddsa_adapter->msglen = msglen;

	DBG_EDDSA_INFO("p_pbk = 0x%x\r\n", peddsa_adapter->p_pbk);
	DBG_EDDSA_INFO("p_sig = 0x%x\r\n", peddsa_adapter->p_signature);
	DBG_EDDSA_INFO("p_msg = 0x%x\r\n", peddsa_adapter->p_msg);
	DBG_EDDSA_INFO("msglen = %d\r\n", peddsa_adapter->msglen);


	// Whether turn-on recover
	peddsa_adapter->point_recover_en = recover_en;

	// select
	peddsa_adapter->sB_write_out_en = 1;

	// select
	peddsa_adapter->kA_write_out_en = 1;

	// auto-step select[Depend on what kinds of autoflow step(all or partial)]
	peddsa_adapter->flow_mode = mode_sel;

	//peddsa_adapter->isMemDump = 1;
#if IS_CUT_TEST(CONFIG_CHIP_VER)
	ret = hal_eddsa_stubs.hal_eddsa_sign_verify(peddsa_adapter);
#else
	ret = hal_eddsa_stubs.hal_eddsa_sign_verify_core(peddsa_adapter);
#endif
	return ret;
}

#endif  // end of "#if CONFIG_CRYPTO_EN"
