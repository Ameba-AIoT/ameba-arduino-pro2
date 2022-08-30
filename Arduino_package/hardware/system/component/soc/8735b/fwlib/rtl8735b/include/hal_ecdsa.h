/**************************************************************************//**
 * @file      hal_ecdsa.h
 * @brief     The HAL API implementation for the EdDSA device.
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

#ifndef __HAL_ECDSA_H__
#define __HAL_ECDSA_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "basic_types.h"
#include "cmsis.h"
#include "rtl8735b_ecdsa.h"

/**
  * @brief The stubs functions table to exports ECDSA HAL functions in ROM.
  */
extern const hal_ecdsa_func_stubs_t hal_ecdsa_stubs;

void hal_ecdsa_irq_reg(void);
void hal_ecdsa_irq_unreg(void);
void hal_ecdsa_init_clk_ctrl(hal_ecdsa_adapter_t *pecdsa_adapter);
void hal_ecdsa_deinit_clk_ctrl(hal_ecdsa_adapter_t *pecdsa_adapter);
HAL_Status hal_ecdsa_init(hal_ecdsa_adapter_t *pecdsa_adapter);
HAL_Status hal_ecdsa_deinit(hal_ecdsa_adapter_t *pecdsa_adapter);
void hal_ecdsa_reset(hal_ecdsa_adapter_t *pecdsa_adapter);
void hal_ecdsa_clr_finish_int(hal_ecdsa_adapter_t *pecdsa_adapter);
void hal_ecdsa_mask_finish_int(hal_ecdsa_adapter_t *pecdsa_adapter, uint8_t enable);
void hal_ecdsa_set_curve(hal_ecdsa_adapter_t *pecdsa_adapter, ecdsa_curve_t curve, hal_ecdsa_curve_table_t *pcurve_table, ecdsa_bit_num_t bit_num);
void hal_ecdsa_set_mode(hal_ecdsa_adapter_t *pecdsa_adapter, ecdsa_mode_t mode, ecdsa_basic_func_t func);
void hal_ecdsa_set_bit_num(hal_ecdsa_adapter_t *pecdsa_adapter, ecdsa_bit_num_t bit_num);
void hal_ecdsa_start_en(hal_ecdsa_adapter_t *pecdsa_adapter, uint8_t enable);
void hal_ecdsa_hash_en(hal_ecdsa_adapter_t *pecdsa_adapter, uint8_t enable);
void hal_ecdsa_hash_256_en(hal_ecdsa_adapter_t *pecdsa_adapter, uint8_t enable);
void hal_ecdsa_select_prk(hal_ecdsa_adapter_t *pecdsa_adapter, ecdsa_sel_prk_t sel_prk);
void hal_ecdsa_set_prk(hal_ecdsa_adapter_t *pecdsa_adapter, uint32_t *ppriv_key);
void hal_ecdsa_set_random_k(hal_ecdsa_adapter_t *pecdsa_adapter, uint32_t *prdk);
void hal_ecdsa_set_pbk(hal_ecdsa_adapter_t *pecdsa_adapter, uint32_t *ppub_key_x, uint32_t *ppub_key_y);
void hal_ecdsa_set_hash(hal_ecdsa_adapter_t *pecdsa_adapter, uint32_t *phash);
void hal_ecdsa_set_rs(hal_ecdsa_adapter_t *pecdsa_adapter, uint32_t *pr_adr, uint32_t *ps_adr);
void hal_ecdsa_set_base_point(hal_ecdsa_adapter_t *pecdsa_adapter, uint32_t *ppoint_x, uint32_t *ppoint_y);
void hal_ecdsa_set_base_point_2(hal_ecdsa_adapter_t *pecdsa_adapter, uint32_t *ppoint_x, uint32_t *ppoint_y);
void hal_ecdsa_set_cor_a(hal_ecdsa_adapter_t *pecdsa_adapter, uint32_t *pa_adr);
void hal_ecdsa_set_prime(hal_ecdsa_adapter_t *pecdsa_adapter, uint32_t *pprime);
void hal_ecdsa_set_order_n(hal_ecdsa_adapter_t *pecdsa_adapter, uint32_t *porder_n);
void hal_ecdsa_get_result_x_y(hal_ecdsa_adapter_t *pecdsa_adapter, uint32_t *prx_adr, uint32_t *pry_adr);
uint32_t hal_ecdsa_get_veri_result(hal_ecdsa_adapter_t *pecdsa_adapter);
uint32_t hal_ecdsa_get_veri_err_sta(hal_ecdsa_adapter_t *pecdsa_adapter);
uint32_t hal_ecdsa_get_inf_err_sta(hal_ecdsa_adapter_t *pecdsa_adapter);
uint32_t hal_ecdsa_get_finish_sta(hal_ecdsa_adapter_t *pecdsa_adapter);
void hal_ecdsa_get_pbk(hal_ecdsa_adapter_t *pecdsa_adapter, uint32_t *ppub_key_x, uint32_t *ppub_key_y);
void hal_ecdsa_get_rs(hal_ecdsa_adapter_t *pecdsa_adapter, uint32_t *pr_adr, uint32_t *ps_adr);
uint32_t hal_ecdsa_get_sign_err_sta(hal_ecdsa_adapter_t *pecdsa_adapter);
uint32_t hal_ecdsa_get_scal_mul_err_sta(hal_ecdsa_adapter_t *pecdsa_adapter);
uint32_t hal_ecdsa_get_err_sta(hal_ecdsa_adapter_t *pecdsa_adapter);
uint32_t hal_ecdsa_get_idle_sta(hal_ecdsa_adapter_t *pecdsa_adapter);
void hal_ecdsa_verify(hal_ecdsa_adapter_t *pecdsa_adapter, hal_ecdsa_veri_input_t *pveri_input);
void hal_ecdsa_signature(hal_ecdsa_adapter_t *pecdsa_adapter, uint32_t *ppriv_key, uint32_t *prdk);
void hal_ecdsa_hash(hal_ecdsa_adapter_t *pecdsa_adapter, uint32_t *phash);
void hal_ecdsa_gen_public_key(hal_ecdsa_adapter_t *pecdsa_adapter, uint32_t *ppriv_key, uint32_t *ppoint_x, uint32_t *ppoint_y);
void hal_ecdsa_cb_handler(hal_ecdsa_adapter_t *pecdsa_adapter, ecdsa_irq_user_cb_t callback, void *arg);

#ifdef __cplusplus
}
#endif


#endif // __HAL_CRYPTO_H__

