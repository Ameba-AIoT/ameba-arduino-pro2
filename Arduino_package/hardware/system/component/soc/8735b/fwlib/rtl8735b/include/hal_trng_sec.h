/**************************************************************************//**
 * @file     hal_trng_sec.h
 * @brief    The HAL API implementation for the TRNG secure device.
 * @version  V1.00
 * @date     2023-11-10
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

#ifndef _HAL_TRNG_SEC_H_
#define _HAL_TRNG_SEC_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "cmsis.h"

hal_status_t hal_trng_sec_init(void);
hal_status_t hal_trng_sec_deinit(void);
hal_status_t hal_trng_sec_set_clk(uint8_t sel_val);
hal_status_t hal_trng_sec_swrst_en(void);
uint32_t hal_trng_sec_get_rand(void);
hal_status_t hal_trng_sec_set_normal_ctrl(uint8_t rng_mode, uint8_t rbc_sel, uint8_t hspeed_sel);
hal_status_t hal_trng_sec_set_lfsr_ctrl(uint8_t lfsr_mod, uint32_t poly_lsb, uint32_t poly_msb);
hal_status_t hal_trng_sec_set_selft_ctrl(uint8_t selft_en, uint8_t cmp_rep_mode, uint8_t cmp_adpt_mode, uint8_t adpt1_window_sel, uint8_t adpt2_window_sel);
hal_status_t hal_trng_sec_load_default_setting(uint8_t selft_en);
hal_status_t hal_trng_sec_get_rand_seed(uint8_t *seed_buf, uint32_t seed_size);
#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_TRNG_SEC_H_"
