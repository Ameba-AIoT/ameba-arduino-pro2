/**************************************************************************//**
 * @file      hal_eddsa.h
 * @brief     The HAL API implementation for the EdDSA device.
 * @version   V1.00
 * @date      2022-04-11
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

#ifndef __HAL_EDDSA_H__
#define __HAL_EDDSA_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "basic_types.h"
#include "cmsis.h"
#include <arm_cmse.h>   /* Use CMSE intrinsics */
#include "rtl8735b_eddsa_ctrl.h"

#if IS_CUT_TEST(CONFIG_CHIP_VER)
int hal_eddsa_engine_init(uint32_t hash_callback, uint32_t decompress_pbk_callback);
#else
int hal_eddsa_engine_init(uint8_t hash_crypto_sel);

int hal_eddsa_hook_hash_op_f(eddsa_hash_init_func_t hash_init_f,
							 eddsa_hash_update_func_t hash_update_f, eddsa_hash_final_func_t hash_final_f);
void hal_eddsa_hook_sign_vrf_hash_op_f(eddsa_sign_vrf_hash_op sign_vrf_hash_f);
int hal_eddsa_sha2_512_init(void *arg);
int hal_eddsa_sha2_512_update(void *arg, const uint8_t *message, const uint32_t msglen);
int hal_eddsa_sha2_512_final(void *arg, uint8_t *pDigest);
#endif

int hal_eddsa_sign_verify(const unsigned char *sig, const unsigned char *msg,
						  const unsigned char *pk, const uint32_t msglen,
						  unsigned char flow_mode, unsigned char recover_en);
#ifdef __cplusplus
}
#endif


#endif // __HAL_CRYPTO_H__

