/**************************************************************************//**
 * @file     rtl8710c_eddsa_ctrl.h
 * @brief    This file defines adapter,rom stubs structure and other related common MACRO_VARs for EdDSA.
 * @version  v1.00
 * @date     2022/07/19
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

/**
 * @addtogroup hs_hal_crypto CRYPTO
 * @ingroup 8710c_hal
 * @{
 */

#ifndef RTL8735B_EDDSA_CTRL_H
#define RTL8735B_EDDSA_CTRL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "rtl8735b_eddsa_type.h"

#define EDDSA_HASH_CRYPTO_HW_SEL_EN           (0x0)
#define EDDSA_HASH_CRYPTO_SW_SEL_EN           (0x1)

#define SIGNATURE_OFFSET_S      (32)
#define POINT_AXIS_VAL_SIZE     (32)
#define POINT_DATA_VAL_OFFSET   (4)

//
// Error index
//
#define _ERRNO_EDDSA_CRYPTO_SW_NOT_READY                        -10
#define _ERRNO_EDDSA_CRYPTO_NULL_POINTER                        -11

enum  EDDSA_MODE_SEL {
	EDDSA_MODE0             = 0,
	EDDSA_MODE1             = 1,
	EDDSA_MODE2             = 2,
	EDDSA_MODE3             = 3,

	EDDSA_MaxMODENum        = 4
};

enum  EDDSA_FUN_SEL {
	EDDSA_FUN_DECP_ADDP_SUB_MOD         = 0,
	EDDSA_FUN_DIV_MOD                   = 1,
	EDDSA_FUN_ADD_MOD                   = 2,
	EDDSA_FUN_MULT_MOD_HASH_MOD         = 3,

	EDDSA_MaxFUNNum                     = 4
};

enum EDDSA_FLOW {
	EDDSA_FLOW_STEPS            = 0,
	EDDSA_FLOW_SEMIAUTO         = 1,
	EDDSA_FLOW_AUTOFLOW         = 2
};

/**
  \brief  HKDF HMAC init function pointer type.
*/
typedef int (*eddsa_hash_init_func_t)(void *arg);

/**
  \brief  HKDF HMAC update function pointer type.
*/
typedef int (*eddsa_hash_update_func_t)(void *arg, const u8 *msg, const u32 msg_len);

/**
  \brief  HKDF HMAC final function pointer type.
*/
typedef int (*eddsa_hash_final_func_t)(void *arg, u8 *digest);

typedef int (*eddsa_sign_vrf_hash_op)(void *arg);

#if IS_CUT_TEST(CONFIG_CHIP_VER)
/* Data Struct for eddsa adapter */
/**
 *  \brief Define data struct for eddsa adapter.
 */
typedef struct hal_eddsa_adapter_s {
	EDDSA_TypeDef *base_addr;      //!< The eddsa register base address
	uint8_t     clk_func_id;
	uint8_t     isInit;                 //!< eddsa engine init state: 1=Init, 0=Not init
	uint8_t     isMemDump;              //!< eddsa memory dump control state: 1=Enable, 0=Disable. related \ref __dbg_mem_dump
	uint8_t     isHashok;               //!< eddsa engine get hash digest result: 1=Already get, 0=Not get
	uint8_t     isDecompress_pbk_ok;    //!< eddsa engine get decompress public key result: 1=Already get, 0=Not get
	uint8_t     *p_msg;                 //!< The message pointer
	uint8_t     *p_signature;           //!< The signature pointer
	uint8_t     *p_pbk;                 //!< The public key pointer
	uint32_t    msglen;                 //!< The message length

	uint8_t     sha512_digest[64] __attribute__((aligned(32)));             //!< The HASH SHA512 digest buffer
	uint8_t     dec_pbk[2][32] __attribute__((aligned(32)));                //!< The Decompress public key buffer

	uint8_t     point_recover_en;        //!< SW recover enable control
	// NOTE removed volatile to remove compiler warning
	// V
	uint8_t  point_recover[2][32] __attribute__((aligned(32)));    //!< Encode point recover (x,y)

	uint8_t     sB_write_out_en;        //!< SW sxB write out enable control
	// V
	uint8_t  sB_point[2][32] __attribute__((aligned(32)));         //!< sxB point (x,y)

	uint8_t     kA_write_out_en;        //!< SW kxA write out enable control
	// V
	uint8_t  kA_point[2][32] __attribute__((aligned(32)));         //!< sxB point (x,y)

	// V
	uint8_t  rcheck_point[2][32] __attribute__((aligned(32)));     //!< rcheck point (x,y)
	// V
	uint8_t  rcheck_enc[32] __attribute__((aligned(32)));

	uint8_t  flow_mode; //!< eddsa engine flowm, check enum EDDSA_FLOW

	int (*hash_exec_func)(void *arg);
	int (*decompress_exec_func)(void *arg);
	void (*clk_func_en)(uint8_t id, uint8_t en);

	uint32_t reserved5[11];             //!<  Reserve
} hal_crypto_eddsa_t, *phal_crypto_eddsa_t ;
#else
/* Data Struct for eddsa adapter */
/**
 *  \brief Define data struct for eddsa adapter.
 */
typedef struct hal_eddsa_adapter_s {
	EDDSA_TypeDef *base_addr;      //!< The eddsa register base address
	hal_crypto_adapter_t *pcrypto_adtr;
	uint8_t     isInit;                 //!< eddsa engine init state: 1=Init, 0=Not init
	uint8_t     isHWCrypto_Init;        // HW Crypto init state: 1=Init, 0=Not init
	uint8_t     hash_crypto_sel;
	uint8_t     resv1;

	uint8_t     isMemDump;              //!< eddsa memory dump control state: 1=Enable, 0=Disable. related \ref __dbg_mem_dump
	uint8_t     isHashok;               //!< eddsa engine get hash digest result: 1=Already get, 0=Not get
	uint8_t     isDecompress_pbk_ok;    //!< eddsa engine get decompress public key result: 1=Already get, 0=Not get
	uint8_t     resv2;

	uint8_t     *p_msg;                 //!< The message pointer
	uint8_t     *p_signature;           //!< The signature pointer
	uint8_t     *p_pbk;                 //!< The public key pointer
	uint32_t    msglen;                 //!< The message length

	uint8_t     sha512_digest[64] __attribute__((aligned(32)));             //!< The HASH SHA512 digest buffer
	uint8_t     dec_pbk[2][32] __attribute__((aligned(32)));                //!< The Decompress public key buffer

	uint8_t     point_recover_en;        //!< SW recover enable control
	uint8_t     sB_write_out_en;        //!< SW sxB write out enable control
	uint8_t     kA_write_out_en;        //!< SW kxA write out enable control
	uint8_t     flow_mode; //!< eddsa engine flowm, check enum EDDSA_FLOW

	uint8_t     resv3[4];

	// NOTE removed volatile to remove compiler warning
	// V
	uint8_t  point_recover[2][32] __attribute__((aligned(32)));    //!< Encode point recover (x,y)

	// V
	uint8_t  sB_point[2][32] __attribute__((aligned(32)));         //!< sxB point (x,y)

	// V
	uint8_t  kA_point[2][32] __attribute__((aligned(32)));         //!< sxB point (x,y)

	// V
	uint8_t  rcheck_point[2][32] __attribute__((aligned(32)));     //!< rcheck point (x,y)
	// V
	uint8_t  rcheck_enc[32] __attribute__((aligned(32)));

	eddsa_hash_init_func_t      hash_init_f;
	eddsa_hash_update_func_t    hash_update_f;
	eddsa_hash_final_func_t     hash_final_f;
	eddsa_sign_vrf_hash_op      sign_vrf_hash_f;
	int (*decompress_exec_func)(void *arg);

	uint32_t reserved5[15];             //!<  Reserve
} hal_crypto_eddsa_t, *phal_crypto_eddsa_t ;
#endif

//
// stub
//

/**
 *   \brief  The data structure of the stubs functions of the EdDSA HAL functions in ROM
 *
 */
typedef struct {
#if IS_CUT_TEST(CONFIG_CHIP_VER)
	int (*hal_eddsa_init)(phal_crypto_eddsa_t peddsa_adapter);
	int (*hal_eddsa_deinit)(phal_crypto_eddsa_t peddsa_adapter);
	int (*hal_eddsa_sign_verify)(phal_crypto_eddsa_t peddsa_adapter);
#else
	int (*hal_eddsa_init)(phal_crypto_eddsa_t peddsa_adtr, hal_crypto_adapter_t *pcrypto_adapter, uint8_t hash_crypto_sel);
	int (*hal_eddsa_deinit)(phal_crypto_eddsa_t peddsa_adapter);
	int (*hal_eddsa_sign_verify)(phal_crypto_eddsa_t peddsa_adtr,
								 const unsigned char *sig, const unsigned char *msg,
								 const unsigned char *pk, const uint32_t msglen,
								 unsigned char mode_sel, unsigned char recover_en);
#endif
	int (*hal_eddsa_sign_verify_autoflow)(phal_crypto_eddsa_t peddsa_adapter);
	int (*hal_eddsa_sign_verify_semi_auto)(phal_crypto_eddsa_t peddsa_adapter);
	int (*hal_eddsa_sign_verify_steps)(phal_crypto_eddsa_t peddsa_adapter);

	void (*hal_eddsa_get_enc_Rplus)(const uint32_t base_addr, unsigned char *s_value);
	void (*hal_eddsa_get_Rplus)(const uint32_t base_addr, unsigned char *s_x_value, unsigned char *s_y_value);

	void (*hal_eddsa_get_kA)(const uint32_t base_addr, unsigned char *s_x_value, unsigned char *s_y_value);
	void (*hal_eddsa_get_sB)(const uint32_t base_addr, unsigned char *s_x_value, unsigned char *s_y_value);
	void (*hal_eddsa_get_recover_pbk)(const uint32_t base_addr, unsigned char *s_x_value, unsigned char *s_y_value);
	void (*hal_eddsa_set_hash_digest)(const uint32_t base_addr, const unsigned char *s_x_value, const unsigned char *s_y_value, uint8_t bypass_en);
	void (*hal_eddsa_set_recover_pbk)(const uint32_t base_addr, const unsigned char *s_x_value, const unsigned char *s_y_value);
	void (*hal_eddsa_set_encode_pbk)(const uint32_t base_addr, const unsigned char *s_value);
	void (*hal_eddsa_set_signature_s)(const uint32_t base_addr, const unsigned char *s_value);
	uint32_t (*hal_eddsa_set_word_from_byte)(const unsigned char *s_value);
	void (*hal_eddsa_get_byte_from_word)(const uint32_t reg_val, unsigned char *s_value);
	void (*hal_eddsa_set_x1_in_val)(const uint32_t base_addr, const unsigned char *s_value);
	void (*hal_eddsa_set_y1_in_val)(const uint32_t base_addr, const unsigned char *s_value);
	void (*hal_eddsa_set_x2_in_val)(const uint32_t base_addr, const unsigned char *s_value);
	void (*hal_eddsa_set_y2_in_val)(const uint32_t base_addr, const unsigned char *s_value);
	void (*hal_eddsa_get_x1_out_val)(const uint32_t base_addr, unsigned char *s_value);
	void (*hal_eddsa_get_y1_out_val)(const uint32_t base_addr, unsigned char *s_value);
	void (*hal_eddsa_get_x2_out_val)(const uint32_t base_addr, unsigned char *s_value);
	void (*hal_eddsa_get_y2_out_val)(const uint32_t base_addr, unsigned char *s_value);
	int (*hal_eddsa_verify_32)(const unsigned char *new_v, const unsigned char *old_v);
#if IS_CUT_TEST(CONFIG_CHIP_VER)
	uint32_t reserved[14];  // reserved space for next ROM code version function table extending.
#else
	int (*hal_eddsa_sign_verify_core)(phal_crypto_eddsa_t peddsa_adapter);
	int (*hal_eddsa_hook_hash_op_f)(hal_crypto_eddsa_t *peddsa_adtr, eddsa_hash_init_func_t hash_init_f,
									eddsa_hash_update_func_t hash_update_f, eddsa_hash_final_func_t hash_final_f);
	void (*hal_eddsa_hash_init_hook)(hal_crypto_eddsa_t *peddsa_adtr, eddsa_hash_init_func_t hash_init_f);
	void (*hal_eddsa_hash_update_hook)(hal_crypto_eddsa_t *peddsa_adtr, eddsa_hash_update_func_t hash_update_f);
	void (*hal_eddsa_hash_final_hook)(hal_crypto_eddsa_t *peddsa_adtr, eddsa_hash_final_func_t hash_final_f);
	void (*hal_eddsa_hook_sign_vrf_hash_op_f)(hal_crypto_eddsa_t *peddsa_adtr, eddsa_sign_vrf_hash_op sign_vrf_hash_f);
	uint32_t reserved[8];  // reserved space for next ROM code version function table extending.
#endif
} hal_eddsa_func_stubs_t;

/** @} */ /* End of group hs_hal_crypto */
#if IS_CUT_TEST(CONFIG_CHIP_VER)
int hal_rtl_eddsa_sign_verify(phal_crypto_eddsa_t peddsa_adapter);
int hal_rtl_eddsa_init(phal_crypto_eddsa_t adtr);
#else
int hal_rtl_eddsa_sign_verify(phal_crypto_eddsa_t peddsa_adtr,
							  const unsigned char *sig, const unsigned char *msg,
							  const unsigned char *pk, const uint32_t msglen,
							  unsigned char mode_sel, unsigned char recover_en);
int hal_rtl_eddsa_init(phal_crypto_eddsa_t peddsa_adtr, hal_crypto_adapter_t *pcrypto_adapter, uint8_t hash_crypto_sel);
int hal_rtl_eddsa_sign_verify_core(phal_crypto_eddsa_t peddsa_adapter);
int hal_rtl_eddsa_hook_hash_op_f(hal_crypto_eddsa_t *peddsa_adtr, eddsa_hash_init_func_t hash_init_f,
								 eddsa_hash_update_func_t hash_update_f, eddsa_hash_final_func_t hash_final_f);
void hal_rtl_eddsa_hash_init_hook(hal_crypto_eddsa_t *peddsa_adtr, eddsa_hash_init_func_t hash_init_f);
void hal_rtl_eddsa_hash_update_hook(hal_crypto_eddsa_t *peddsa_adtr, eddsa_hash_update_func_t hash_update_f);
void hal_rtl_eddsa_hash_final_hook(hal_crypto_eddsa_t *peddsa_adtr, eddsa_hash_final_func_t hash_final_f);
void hal_rtl_eddsa_hook_sign_vrf_hash_op_f(hal_crypto_eddsa_t *peddsa_adtr, eddsa_sign_vrf_hash_op sign_vrf_hash_f);
#endif

int hal_rtl_eddsa_sign_verify_autoflow(phal_crypto_eddsa_t peddsa_adapter);
int hal_rtl_eddsa_sign_verify_semi_auto(phal_crypto_eddsa_t peddsa_adapter);
int hal_rtl_eddsa_sign_verify_steps(phal_crypto_eddsa_t peddsa_adapter);
int hal_rtl_eddsa_deinit(phal_crypto_eddsa_t peddsa_adtr);
void hal_rtl_eddsa_get_enc_Rplus(const uint32_t base_addr, unsigned char *s_value);
void hal_rtl_eddsa_get_Rplus(const uint32_t base_addr, unsigned char *s_x_value, unsigned char *s_y_value);

void hal_rtl_eddsa_get_kA(const uint32_t base_addr, unsigned char *s_x_value, unsigned char *s_y_value);
void hal_rtl_eddsa_get_sB(const uint32_t base_addr, unsigned char *s_x_value, unsigned char *s_y_value);
void hal_rtl_eddsa_get_recover_pbk(const uint32_t base_addr, unsigned char *s_x_value, unsigned char *s_y_value);
void hal_rtl_eddsa_set_hash_digest(const uint32_t base_addr, const unsigned char *s_x_value, const unsigned char *s_y_value, uint8_t bypass_en);
void hal_rtl_eddsa_set_recover_pbk(const uint32_t base_addr, const unsigned char *s_x_value, const unsigned char *s_y_value);
void hal_rtl_eddsa_set_encode_pbk(const uint32_t base_addr, const unsigned char *s_value);
void hal_rtl_eddsa_set_signature_s(const uint32_t base_addr, const unsigned char *s_value);
uint32_t hal_rtl_eddsa_set_word_from_byte(const unsigned char *s_value);
void hal_rtl_eddsa_get_byte_from_word(const uint32_t reg_val, unsigned char *s_value);
void hal_rtl_eddsa_set_x1_in_val(const uint32_t base_addr, const unsigned char *s_value);
void hal_rtl_eddsa_set_y1_in_val(const uint32_t base_addr, const unsigned char *s_value);
void hal_rtl_eddsa_set_x2_in_val(const uint32_t base_addr, const unsigned char *s_value);
void hal_rtl_eddsa_set_y2_in_val(const uint32_t base_addr, const unsigned char *s_value);
void hal_rtl_eddsa_get_x1_out_val(const uint32_t base_addr, unsigned char *s_value);
void hal_rtl_eddsa_get_y1_out_val(const uint32_t base_addr, unsigned char *s_value);
void hal_rtl_eddsa_get_x2_out_val(const uint32_t base_addr, unsigned char *s_value);
void hal_rtl_eddsa_get_y2_out_val(const uint32_t base_addr, unsigned char *s_value);
int hal_rtl_eddsa_verify_32(const unsigned char *new_v, const unsigned char *old_v);

#ifdef __cplusplus
}
#endif

#endif /* RTL8735B_EDDSA_CTRL_H */
