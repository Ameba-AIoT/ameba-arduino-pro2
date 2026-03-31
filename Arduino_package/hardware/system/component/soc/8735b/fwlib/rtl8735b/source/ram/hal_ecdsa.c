/**************************************************************************//**
 * @file      hal_ecdsa.c
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
#include "rtl8735b_ecdsa.h"
#include "rtl8735b_ecdsa_type.h"
#include "hal_ecdsa.h"
#if defined(CONFIG_BUILD_NONSECURE) && (CONFIG_BUILD_NONSECURE == 1)
#include "hal_sys_ctrl_nsc.h"
#endif


#if CONFIG_ECDSA_EN

/**
 * @addtogroup hs_hal_ecdsa ECDSA
 * @{
 */

/**
 *  @brief To register a IRQ handler for ECDSA.
 *
 *  @returns void
 */
void hal_ecdsa_irq_reg(void)
{
	hal_ecdsa_stubs.hal_ecdsa_irq_reg();
}

/**
 *  @brief To un-register the ECDSA IRQ handler.
 *
 *  @param[in]  pecdsa_adapter The ECDSA adapter.
 *
 *  @returns void
 */
void hal_ecdsa_irq_unreg(void)
{
	hal_ecdsa_stubs.hal_ecdsa_irq_unreg();
}

/**
 *  @brief Init ECDSA clock control.
 *
 *  @param[in]  pecdsa_adapter The ECDSA adapter.
 *
 *  @returns void
 */
void hal_ecdsa_init_clk_ctrl(hal_ecdsa_adapter_t *pecdsa_adapter)
{
	hal_ecdsa_stubs.hal_ecdsa_init_clk_ctrl(pecdsa_adapter);
}

/**
 *  @brief De-init ECDSA clock control.
 *
 *  @param[in]  pecdsa_adapter The ECDSA adapter.
 *
 *  @returns void
 */
void hal_ecdsa_deinit_clk_ctrl(hal_ecdsa_adapter_t *pecdsa_adapter)
{
	hal_ecdsa_stubs.hal_ecdsa_deinit_clk_ctrl(pecdsa_adapter);
}

/**
 *  @brief Initialize the ECDSA hardware and turn on the ECDSA
 *
 *  @param[in] pecdsa_adapter The ECDSA adapter.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_ecdsa_init(hal_ecdsa_adapter_t *pecdsa_adapter)
{
	return hal_ecdsa_stubs.hal_ecdsa_init(pecdsa_adapter);
}

/**
 *  @brief De-initialize of the ECDSA hardware and turn off the ECDSA.
 *
 *  @param[in] pecdsa_adapter The ECDSA adapter.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_ecdsa_deinit(hal_ecdsa_adapter_t *pecdsa_adapter)
{
	return hal_ecdsa_stubs.hal_ecdsa_deinit(pecdsa_adapter);
}

/**
 *  @brief Reset the ECDSA.
 *
 *  @param[in] pecdsa_adapter The ECDSA adapter.
 *
 *  @returns void
 */
void hal_ecdsa_reset(hal_ecdsa_adapter_t *pecdsa_adapter)
{
	hal_ecdsa_stubs.hal_ecdsa_reset(pecdsa_adapter);
}

/**
 *  @brief Clear the finish interrupt of ECDSA
 *
 *  @returns void
 */
void hal_ecdsa_clr_finish_int(hal_ecdsa_adapter_t *pecdsa_adapter)
{
	hal_ecdsa_stubs.hal_ecdsa_clr_finish_int(pecdsa_adapter);
}

/**
 *  @brief Mask the finish interrupt of ECDSA
 *
 *  @returns void
 */
void hal_ecdsa_mask_finish_int(hal_ecdsa_adapter_t *pecdsa_adapter, uint8_t enable)
{
	hal_ecdsa_stubs.hal_ecdsa_mask_finish_int(pecdsa_adapter, enable);
}

/**
 *  @brief Set the ECDSA curve.
 *
 *  @param[in] pecdsa_adapter The ECDSA adapter.
 *  @param[in] curve Select an elliptic curve.
 *  @param[in] pcurve_table Set the curve table address.
 *  @param[in] bit_num Select the bit length.
 *
 *  @returns void
 */
void hal_ecdsa_set_curve(hal_ecdsa_adapter_t *pecdsa_adapter, ecdsa_curve_t curve, hal_ecdsa_curve_table_t *pcurve_table, ecdsa_bit_num_t bit_num)
{
	hal_ecdsa_stubs.hal_ecdsa_set_curve(pecdsa_adapter, curve, pcurve_table, bit_num);
}

/**
 *  @brief Set the ECDSA mode.
 *
 *  @param[in] pecdsa_adapter The ECDSA adapter.
 *  @param[in] mode Select an operation mode.
 *  @param[in] func If the operating mode is ECDSA_BASIC_FUNC, need to set this operation unit.
 *
 *  @returns void
 */
void hal_ecdsa_set_mode(hal_ecdsa_adapter_t *pecdsa_adapter, ecdsa_mode_t mode, ecdsa_basic_func_t func)
{
	hal_ecdsa_stubs.hal_ecdsa_set_mode(pecdsa_adapter, mode, func);
}

/**
 *  @brief Set the basic function of ECDSA.
 *
 *  @param[in] pecdsa_adapter The ECDSA adapter.
 *  @param[in] bit_num Select the bit length.
 *
 *  @returns void
 */
void hal_ecdsa_set_bit_num(hal_ecdsa_adapter_t *pecdsa_adapter, ecdsa_bit_num_t bit_num)
{
	hal_ecdsa_stubs.hal_ecdsa_set_bit_num(pecdsa_adapter, bit_num);
}

/**
 *  @brief To enable or disable the ECDSA engine.
 *
 *  @param[in] pecdsa_adapter The ECDSA adapter.
 *  @param[in] enable Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_ecdsa_start_en(hal_ecdsa_adapter_t *pecdsa_adapter, uint8_t enable)
{
	hal_ecdsa_stubs.hal_ecdsa_start_en(pecdsa_adapter, enable);
}

/**
 *  @brief To enable or disable the ECDSA hask ok.
 *
 *  @param[in] pecdsa_adapter The ECDSA adapter.
 *  @param[in] enable Enable control: 0 is that hash is ready, 1 is that hash is not ready.
 *
 *  @returns void
 */
void hal_ecdsa_hash_en(hal_ecdsa_adapter_t *pecdsa_adapter, uint8_t enable)
{
	hal_ecdsa_stubs.hal_ecdsa_hash_en(pecdsa_adapter, enable);
}

/**
 *  @brief Force the hash length is 256 bits, and seed up the operation.
 *
 *  @param[in] pecdsa_adapter The ECDSA adapter.
 *  @param[in] enable Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_ecdsa_hash_256_en(hal_ecdsa_adapter_t *pecdsa_adapter, uint8_t enable)
{
	hal_ecdsa_stubs.hal_ecdsa_hash_256_en(pecdsa_adapter, enable);
}

/**
 *  @brief Select the private key of ECDSA.
 *
 *  @param[in] pecdsa_adapter The ECDSA adapter.
 *  @param[in] sel_prk Select the private key.
 *
 *  @returns void
 */
void hal_ecdsa_select_prk(hal_ecdsa_adapter_t *pecdsa_adapter, ecdsa_sel_prk_t sel_prk)
{
	hal_ecdsa_stubs.hal_ecdsa_select_prk(pecdsa_adapter, sel_prk);
}

/**
 *  @brief Set the private key of ECDSA.
 *
 *  @param[in] pecdsa_adapter The ECDSA adapter.
 *  @param[in] ppriv_key Set the private key.
 *
 *  @returns void
 */
void hal_ecdsa_set_prk(hal_ecdsa_adapter_t *pecdsa_adapter, uint32_t *ppriv_key)
{
	hal_ecdsa_stubs.hal_ecdsa_set_prk(pecdsa_adapter, ppriv_key);
}

/**
 *  @brief Set the random k of ECDSA.
 *
 *  @param[in] pecdsa_adapter The ECDSA adapter.
 *  @param[in] prdk Set the random k.
 *
 *  @returns void
 */
void hal_ecdsa_set_random_k(hal_ecdsa_adapter_t *pecdsa_adapter, uint32_t *prdk)
{
	hal_ecdsa_stubs.hal_ecdsa_set_random_k(pecdsa_adapter, prdk);
}

/**
 *  @brief Set the public key of ECDSA.
 *
 *  @param[in] pecdsa_adapter The ECDSA adapter.
 *  @param[in] ppub_key_x Set the public key x.
 *  @param[in] ppub_key_y Set the public key y.
 *
 *  @returns void
 */
void hal_ecdsa_set_pbk(hal_ecdsa_adapter_t *pecdsa_adapter, uint32_t *ppub_key_x, uint32_t *ppub_key_y)
{
	hal_ecdsa_stubs.hal_ecdsa_set_pbk(pecdsa_adapter, ppub_key_x, ppub_key_y);
}

/**
 *  @brief Set the hash of ECDSA.
 *
 *  @param[in] pecdsa_adapter The ECDSA adapter.
 *  @param[in] phash Set the hash.
 *
 *  @returns void
 */
void hal_ecdsa_set_hash(hal_ecdsa_adapter_t *pecdsa_adapter, uint32_t *phash)
{
	hal_ecdsa_stubs.hal_ecdsa_set_hash(pecdsa_adapter, phash);
}

/**
 *  @brief Set the R and S of ECDSA.
 *
 *  @param[in] pecdsa_adapter The ECDSA adapter.
 *  @param[in] pr_adr Set the R.
 *  @param[in] ps_adr Set the S.
 *
 *  @returns void
 */
void hal_ecdsa_set_rs(hal_ecdsa_adapter_t *pecdsa_adapter, uint32_t *pr_adr, uint32_t *ps_adr)
{
	hal_ecdsa_stubs.hal_ecdsa_set_rs(pecdsa_adapter, pr_adr, ps_adr);
}

/**
 *  @brief Set the base point of ECDSA.
 *
 *  @param[in] pecdsa_adapter The ECDSA adapter.
 *  @param[in] ppoint_x Set the base point X.
 *  @param[in] ppoint_y Set the base point y.
 *
 *  @returns void
 */
void hal_ecdsa_set_base_point(hal_ecdsa_adapter_t *pecdsa_adapter, uint32_t *ppoint_x, uint32_t *ppoint_y)
{
	hal_ecdsa_stubs.hal_ecdsa_set_base_point(pecdsa_adapter, ppoint_x, ppoint_y);
}

/**
 *  @brief Set the base point 2 of ECDSA for the basic mode.
 *
 *  @param[in] pecdsa_adapter The ECDSA adapter.
 *  @param[in] ppoint_x Set the base point2 X.
 *  @param[in] ppoint_y Set the base point2 y.
 *
 *  @returns void
 */
void hal_ecdsa_set_base_point_2(hal_ecdsa_adapter_t *pecdsa_adapter, uint32_t *ppoint_x, uint32_t *ppoint_y)
{
	hal_ecdsa_stubs.hal_ecdsa_set_base_point_2(pecdsa_adapter, ppoint_x, ppoint_y);
}

/**
 *  @brief Set the "a" parameter of ECDSA.
 *
 *  @param[in] pecdsa_adapter The ECDSA adapter.
 *  @param[in] pa_adr Set the "a" parameter.
 *
 *  @returns void
 */
void hal_ecdsa_set_cor_a(hal_ecdsa_adapter_t *pecdsa_adapter, uint32_t *pa_adr)
{
	hal_ecdsa_stubs.hal_ecdsa_set_cor_a(pecdsa_adapter, pa_adr);
}

/**
 *  @brief Set the prime of ECDSA.
 *
 *  @param[in] pecdsa_adapter The ECDSA adapter.
 *  @param[in] phash Set the prime.
 *
 *  @returns void
 */
void hal_ecdsa_set_prime(hal_ecdsa_adapter_t *pecdsa_adapter, uint32_t *pprime)
{
	hal_ecdsa_stubs.hal_ecdsa_set_prime(pecdsa_adapter, pprime);
}

/**
 *  @brief Set the order_n of ECDSA.
 *
 *  @param[in] pecdsa_adapter The ECDSA adapter.
 *  @param[in] phash Set the order_n.
 *
 *  @returns void
 */
void hal_ecdsa_set_order_n(hal_ecdsa_adapter_t *pecdsa_adapter, uint32_t *porder_n)
{
	hal_ecdsa_stubs.hal_ecdsa_set_order_n(pecdsa_adapter, porder_n);
}

/**
 *  @brief Get the result x and y of ECDSA.
 *
 *  @param[in] pecdsa_adapter The ECDSA adapter.
 *  @param[in] prx_adr Get the result x.
 *  @param[in] pry_adr Get the result y.
 *
 *  @returns void
 */
void hal_ecdsa_get_result_x_y(hal_ecdsa_adapter_t *pecdsa_adapter, uint32_t *prx_adr, uint32_t *pry_adr)
{
	hal_ecdsa_stubs.hal_ecdsa_get_result_x_y(pecdsa_adapter, prx_adr, pry_adr);
}

/**
 *  @brief Get the verification result of ECDSA.
 *
 *  @param[in] pecdsa_adapter The ECDSA adapter.
 *
 *  @returns The verification result
 */
uint32_t hal_ecdsa_get_veri_result(hal_ecdsa_adapter_t *pecdsa_adapter)
{
	return hal_ecdsa_stubs.hal_ecdsa_get_veri_result(pecdsa_adapter);
}

/**
 *  @brief Get the verification error status of ECDSA.
 *
 *  @param[in] pecdsa_adapter The ECDSA adapter.
 *
 *  @returns The verification error status
 */
uint32_t hal_ecdsa_get_veri_err_sta(hal_ecdsa_adapter_t *pecdsa_adapter)
{
	return hal_ecdsa_stubs.hal_ecdsa_get_veri_err_sta(pecdsa_adapter);
}

/**
 *  @brief Get the infinity error status of ECDSA.
 *
 *  @param[in] pecdsa_adapter The ECDSA adapter.
 *
 *  @returns The infinity error status
 */
uint32_t hal_ecdsa_get_inf_err_sta(hal_ecdsa_adapter_t *pecdsa_adapter)
{
	return hal_ecdsa_stubs.hal_ecdsa_get_inf_err_sta(pecdsa_adapter);
}

/**
 *  @brief Get the finish status of ECDSA.
 *
 *  @param[in] pecdsa_adapter The ECDSA adapter.
 *
 *  @returns The finish status
 */
uint32_t hal_ecdsa_get_finish_sta(hal_ecdsa_adapter_t *pecdsa_adapter)
{
	return hal_ecdsa_stubs.hal_ecdsa_get_finish_sta(pecdsa_adapter);
}

/**
 *  @brief Get the public key of ECDSA.
 *
 *  @param[in] pecdsa_adapter The ECDSA adapter.
 *  @param[in] ppub_key_x Get the public key x.
 *  @param[in] ppub_key_y Get the public key y.
 *
 *  @returns void
 */
void hal_ecdsa_get_pbk(hal_ecdsa_adapter_t *pecdsa_adapter, uint32_t *ppub_key_x, uint32_t *ppub_key_y)
{
	hal_ecdsa_stubs.hal_ecdsa_get_pbk(pecdsa_adapter, ppub_key_x, ppub_key_y);
}

/**
 *  @brief Get the R and S of ECDSA.
 *
 *  @param[in] pecdsa_adapter The ECDSA adapter.
 *  @param[in] pr_adr Get the R.
 *  @param[in] ps_adr Get the S.
 *
 *  @returns void
 */
void hal_ecdsa_get_rs(hal_ecdsa_adapter_t *pecdsa_adapter, uint32_t *pr_adr, uint32_t *ps_adr)
{
	hal_ecdsa_stubs.hal_ecdsa_get_rs(pecdsa_adapter, pr_adr, ps_adr);
}

/**
 *  @brief Get the signature error status of ECDSA.
 *
 *  @param[in] pecdsa_adapter The ECDSA adapter.
 *
 *  @returns The signature error status
 */
uint32_t hal_ecdsa_get_sign_err_sta(hal_ecdsa_adapter_t *pecdsa_adapter)
{
	return hal_ecdsa_stubs.hal_ecdsa_get_sign_err_sta(pecdsa_adapter);
}

/**
 *  @brief Get the scalar multiplication error status of ECDSA.
 *
 *  @param[in] pecdsa_adapter The ECDSA adapter.
 *
 *  @returns The scalar multiplication error status
 */
uint32_t hal_ecdsa_get_scal_mul_err_sta(hal_ecdsa_adapter_t *pecdsa_adapter)
{
	return hal_ecdsa_stubs.hal_ecdsa_get_scal_mul_err_sta(pecdsa_adapter);
}

/**
 *  @brief Get the error status of ECDSA according to different modes.
 *
 *  @param[in] pecdsa_adapter The ECDSA adapter.
 *
 *  @returns The error status
 */
uint32_t hal_ecdsa_get_err_sta(hal_ecdsa_adapter_t *pecdsa_adapter)
{
	return hal_ecdsa_stubs.hal_ecdsa_get_err_sta(pecdsa_adapter);
}

/**
 *  @brief Get the error status of ECDSA according to different modes.
 *
 *  @param[in] pecdsa_adapter The ECDSA adapter.
 *
 *  @returns The idle status
 */
uint32_t hal_ecdsa_get_idle_sta(hal_ecdsa_adapter_t *pecdsa_adapter)
{
	return hal_ecdsa_stubs.hal_ecdsa_get_idel_sta(pecdsa_adapter);
}

/**
 *  @brief Excute the verification of ECDSA.
 *
 *  @param[in] pecdsa_adapter The ECDSA adapter.
 *  @param[in] pveri_input Set verification inputs.
 *
 *  @returns void
 */
void hal_ecdsa_verify(hal_ecdsa_adapter_t *pecdsa_adapter, hal_ecdsa_veri_input_t *pveri_input)
{
	hal_ecdsa_stubs.hal_ecdsa_verify(pecdsa_adapter, pveri_input);
}

/**
 *  @brief Excute the signature of ECDSA.
 *
 *  @param[in] pecdsa_adapter The ECDSA adapter.
 *  @param[in] ppriv_key Set the private key.
 *  @param[in] prdk Set the random k.
 *
 *  @returns void
 */
void hal_ecdsa_signature(hal_ecdsa_adapter_t *pecdsa_adapter, uint32_t *ppriv_key, uint32_t *prdk)
{
	hal_ecdsa_stubs.hal_ecdsa_signature(pecdsa_adapter, ppriv_key, prdk);
}

/**
 *  @brief Set the hash is ready.
 *
 *  @param[in] pecdsa_adapter The ECDSA adapter.
 *  @param[in] phash Set the hash.
 *
 *  @returns void
 */
void hal_ecdsa_hash(hal_ecdsa_adapter_t *pecdsa_adapter, uint32_t *phash)
{
	hal_ecdsa_stubs.hal_ecdsa_hash(pecdsa_adapter, phash);
}

/**
 *  @brief Generate the public key of ECDSA.
 *
 *  @param[in] pecdsa_adapter The ECDSA adapter.
 *  @param[in] ppriv_key Set the private key.
 *  @param[in] ppoint_x Set the base point X.
 *  @param[in] ppoint_y Set the base point y.
 *
 *  @returns void
 */
void hal_ecdsa_gen_public_key(hal_ecdsa_adapter_t *pecdsa_adapter, uint32_t *ppriv_key, uint32_t *ppoint_x, uint32_t *ppoint_y)
{
	hal_ecdsa_stubs.hal_ecdsa_gen_public_key(pecdsa_adapter, ppriv_key, ppoint_x, ppoint_y);
}

/**
 *  @brief Register the ECDSA callback function and argument.
 *
 *  @param[in] pecdsa_adapter The ECDSA adapter.
 *  @param[in]  callback The callback function.
 *  @param[in]  arg The callback argument.
 *  @returns void
 */
void hal_ecdsa_cb_handler(hal_ecdsa_adapter_t *pecdsa_adapter, ecdsa_irq_user_cb_t callback, void *arg)
{
	hal_ecdsa_stubs.hal_ecdsa_cb_handler(pecdsa_adapter, callback, arg);
}



/** @} */ /* End of group hs_hal_ecdsa */


#endif  // end of "#if CONFIG_ECDSA_EN"
