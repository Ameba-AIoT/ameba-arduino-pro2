/** mbed Microcontroller Library
  ******************************************************************************
  * @file    ecdsa_api.h
  * @author
  * @version V1.0.0
  * @brief   This file provides following mbed ECDSA API
  ******************************************************************************
  * @attention
  *
  * Copyright(c) 2006 - 2022 Realtek Corporation. All rights reserved.
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
  ******************************************************************************
  */

#ifndef MBED_EXT_ECDSA_API_EXT_H
#define MBED_EXT_ECDSA_API_EXT_H

#include "device.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup ecdsa ECDSA
 *  @ingroup    hal
 *  @brief      ecdsa functions
 *  @{
 */


/**
  \brief  Define the ECDSA bit length.
*/
typedef enum {
	ECDSA_L_256 = ECDSA_256_BIT,
	ECDSA_L_224 = ECDSA_224_BIT,
	ECDSA_L_192 = ECDSA_192_BIT,
	ECDSA_L_160 = ECDSA_160_BIT,
	ECDSA_L_128 = ECDSA_128_BIT,
	ECDSA_L_112 = ECDSA_112_BIT,
	ECDSA_L_232 = ECDSA_232_BIT,
	ECDSA_L_200 = ECDSA_200_BIT,
	ECDSA_L_168 = ECDSA_168_BIT,
	ECDSA_L_136 = ECDSA_136_BIT,
	ECDSA_L_120 = ECDSA_120_BIT
} ecdsa_bit_num;

/**
  \brief  Define the ECDSA Curve.
*/
typedef enum {
	CURVE_SPEC256K1     =   ECDSA_SPEC256K1,
	CURVE_P256          =   ECDSA_P256,
	CURVE_CURVE25519_W  =   ECDSA_CURVE25519_W,
	OTHER_CURVE         =   ECDSA_OTHERS
} ecdsa_curve;

/**
  \brief  Define the private key of ECDSA.
*/
typedef enum {
	INPUT_PRK = ECDSA_INPUT_PRK,
	OTP_PRK_1 = ECDSA_OTP_PRK_1,
	OTP_PRK_2 = ECDSA_OTP_PRK_2
} ecdsa_sel_prk;

typedef void (*ecdsa_irq_handler)(void *);

typedef struct ecdsa_s ecdsa_t;

/**
  \brief Describe ECDSA curve parameter
*/
typedef struct ecdsa_curve_para_s {
	u32 *ppoint_x;          /*!< Base point x address  */
	u32 *ppoint_y;          /*!< Base point y addres  */
	u32 *pa_adr;            /*!< Curve cor_a addres */
	u32 *pprime;            /*!< Prime addres */
	u32 *porder_n;          /*!< Order_n addres */
	ecdsa_bit_num bit_num;  /*!< Bit length */
	ecdsa_curve curve;      /*!< Curve */
} ecdsa_curve_para_t, *pecdsa_curve_para_t;

/**
  * @brief  Initialize the ECDSA hardware and turn on the ECDSA
  * @param  obj: ECDSA object define in application software.
  * @retval none
  */
void ecdsa_init(ecdsa_t *obj);

/**
  * @brief  Register the ECDSA callback function and argument.
  * @param  obj: ECDSA object define in application software.
  * @param  handler: The callback function.
  * @param  parg: The callback argument.
  * @retval none
  */
void ecdsa_cb_irq_handler(ecdsa_t *obj, ecdsa_irq_handler handler, void *parg);

/**
  * @brief  Set the ECDSA curve.
  * @param  obj: ECDSA object define in application software.
  * @param  pecdsa_curve_para: Set curve parameters.
  * @retval none
  */
void ecdsa_set_curve(ecdsa_t *obj, ecdsa_curve_para_t *pecdsa_curve_para);

/**
  * @brief  Generate the ECDSA signature.
  * @param  obj: ECDSA object define in application software.
  * @param  pprivate_key: Set private key.
  * @param  prandom_k: Set random k.
  * @retval none
  */
void ecdsa_signature(ecdsa_t *obj, u32 *pprivate_key, u32 *prandom_k);

/**
  * @brief  Make the ECDSA verificaion.
  * @param  obj: ECDSA object define in application software.
  * @param  pprivate_key: Set private key.
  * @param  prandom_k: Set random k.
  * @retval none
  */
void ecdsa_verificaion(ecdsa_t *obj, u32 *ppublic_key_x, u32 *ppublic_key_y, u32 *pr, u32 *ps);

/**
  * @brief  Set the ECDSA hash.
  * @param  obj: ECDSA object define in application software.
  * @param  phash: Set hash.
  * @retval none
  */
void ecdsa_hash(ecdsa_t *obj, u32 *phash);

/**
  * @brief  De-initialize of the ECDSA hardware and turn off the ECDSA.
  * @retval none
  */
void ecdsa_deinit(ecdsa_t *obj);

/**
  * @brief  Get the result of using ECDSA HW to check error status.
  * @param  obj: ECDSA object define in application software.
  * @retval Error Status
  */
u32 ecdsa_get_err_sta(ecdsa_t *obj);

/**
  * @brief  Get the pubic key of the signature.
  * @param  obj: ECDSA object define in application software.
  * @param  ppub_key_x: Set the pointer to get the pubic key x.
  * @param  ppub_key_y: Set the pointer to get the pubic key y.
  * @retval none
  */
void ecdsa_get_pbk(ecdsa_t *obj, u32 *ppub_key_x, u32 *ppub_key_y);

/**
  * @brief  Get signature R and S.
  * @param  obj: ECDSA object define in application software.
  * @param  pr_adr: Set the pointer to get R.
  * @param  ps_adr: Set the pointer to get S.
  * @retval none
  */
void ecdsa_get_rs(ecdsa_t *obj, u32 *pr_adr, u32 *ps_adr);

/**
  * @brief  Get verificaion X and Y.
  * @param  obj: ECDSA object define in application software.
  * @param  prx_adr: Set the pointer to get X.
  * @param  pry_adr: Set the pointer to get Y.
  * @retval none
  */
void ecdsa_get_result_x_y(ecdsa_t *obj, u32 *prx_adr, u32 *pry_adr);

/**
  * @brief  Get verificaion result.
  * @param  obj: ECDSA object define in application software.
  * @retval Verificaion result. 0: Pass
  */
u32 ecdsa_get_veri_result(ecdsa_t *obj);

/**
  * @brief  Generate public key.
  * @param  obj: ECDSA object define in application software.
  * @param  ppriv_key: Set private key.
  * @param  ppoint_x: Set the base point x.
  * @param  ppoint_y: Set the base point y.
  * @retval none
  */
void ecdsa_gen_public_key(ecdsa_t *obj, uint32_t *ppriv_key, uint32_t *ppoint_x, uint32_t *ppoint_y);

/**
  * @brief  Select private key.
  * @param  obj: ECDSA object define in application software.
  * @param  sel_private_key: Select private key. INPUT_PRK: need to set key, OTP_PRK_1: OTP private key 1, OTP_PRK_2: OTP private key 1.
  * @retval none
  */
void ecdsa_select_prk(ecdsa_t *obj, ecdsa_sel_prk sel_private_key);

/*\@}*/

#ifdef __cplusplus
}
#endif

#endif

