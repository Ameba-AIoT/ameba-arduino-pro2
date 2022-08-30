/**************************************************************************//**
 * @file     hal_rsa.h
 * @brief    The HAL API implementation for the RSA.
 * @version  V1.00
 * @date     2020-11-12
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2016 Realtek Corporation. All rights reserved.
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

#ifndef _HAL_RSA_H_
#define _HAL_RSA_H_
#include "cmsis.h"
#include "rtl8735b_rsa.h"

#ifdef  __cplusplus
extern "C"
{
#endif

extern const hal_rsa_func_stubs_t hal_rsa_stubs;



int hal_rsa_set_key_size(RSA_KEY_SEL_TYPE type);

int hal_rsa_set_byte_swap(RSA_ENDIAN_TYPE byte_endian);

int hal_rsa_set_endian(RSA_ENDIAN_TYPE endian);

void hal_rsa_set_operands(uint32_t *M, uint32_t *e, uint32_t *N, uint32_t exp_word_cnt);

RSA_ERR_CODE hal_rsa_check_status(void);

RSA_ERR_CODE hal_rsa_compute(uint32_t *result);

int hal_rsa_config(RSA_KEY_SEL_TYPE type, RSA_ENDIAN_TYPE byte_endian, RSA_ENDIAN_TYPE endian,
				   uint32_t *M, uint32_t *e, uint32_t *N, uint32_t exp_word_cnt);

int hal_rsa_process(uint32_t *result);

void hal_rsa_clock_init(int en);


#endif  // end of "#define _HAL_RSA_H_"

