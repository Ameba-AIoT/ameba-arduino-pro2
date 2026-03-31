/**************************************************************************//**
 * @file     hal_rsa.c
 * @brief    This TIMER HAL API functions.
 *
 * @version  V1.00
 * @date     2021-03-26
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

#include "hal_rsa.h"
#include "hal_rsa_nsc.h"
#if CONFIG_RSA_EN //CONFIG_RSA_EN

hal_rsa_adapter_t HAL_RSA_ADAPTER;


int hal_rsa_set_key_size(RSA_KEY_SEL_TYPE type)
{
	int ret;
	hal_rsa_adapter_t *prsa_adapter = &HAL_RSA_ADAPTER;

	prsa_adapter->key_type = type;
	ret = hal_rsa_stubs.hal_rsa_set_key_size(prsa_adapter);

	return ret;
}

int hal_rsa_set_byte_swap(RSA_ENDIAN_TYPE byte_endian)
{
	int ret;
	hal_rsa_adapter_t *prsa_adapter = &HAL_RSA_ADAPTER;

	prsa_adapter->byte_endian = byte_endian;
	ret = hal_rsa_stubs.hal_rsa_set_byte_swap(prsa_adapter);

	return ret;
}

int hal_rsa_set_endian(RSA_ENDIAN_TYPE endian)
{
	int ret;
	hal_rsa_adapter_t *prsa_adapter = &HAL_RSA_ADAPTER;

	prsa_adapter->endian = endian;
	ret = hal_rsa_stubs.hal_rsa_set_endian(prsa_adapter);

	return ret;
}

void hal_rsa_set_operands(uint32_t *M, uint32_t *e, uint32_t *N, uint32_t exp_word_cnt)
{
	hal_rsa_adapter_t *prsa_adapter = &HAL_RSA_ADAPTER;

	prsa_adapter->Message = M;
	prsa_adapter->Modulus = N;
	prsa_adapter->Exponent = e;
	prsa_adapter->exp_word_cnt = exp_word_cnt;
	hal_rsa_stubs.hal_rsa_set_operands(prsa_adapter);
}

RSA_ERR_CODE hal_rsa_check_status(void)
{
	int ret;
	hal_rsa_adapter_t *prsa_adapter = &HAL_RSA_ADAPTER;

	ret = hal_rsa_stubs.hal_rsa_check_status(prsa_adapter);

	return ret;
}

RSA_ERR_CODE hal_rsa_compute(uint32_t *result)
{
	int ret;
	hal_rsa_adapter_t *prsa_adapter = &HAL_RSA_ADAPTER;

	ret = hal_rsa_stubs.hal_rsa_compute(prsa_adapter, result);

	return ret;
}

int hal_rsa_config(RSA_KEY_SEL_TYPE type, RSA_ENDIAN_TYPE byte_endian, RSA_ENDIAN_TYPE endian,
				   uint32_t *M, uint32_t *e, uint32_t *N, uint32_t exp_word_cnt)
{
	int ret;
	hal_rsa_adapter_t *prsa_adapter = &HAL_RSA_ADAPTER;

	ret = hal_rsa_stubs.hal_rsa_config(prsa_adapter, type, byte_endian, endian, M, e, N, exp_word_cnt);

	return ret;
}


int hal_rsa_process(uint32_t *result)
{
	int ret;
	hal_rsa_adapter_t *prsa_adapter = &HAL_RSA_ADAPTER;

	ret = hal_rsa_stubs.hal_rsa_process(prsa_adapter, result);

	return ret;
}

void hal_rsa_clock_init(int en)
{
#if defined(CONFIG_BUILD_NONSECURE)
	hal_rsa_clock_init_nsc(en);
#else
	hal_rsa_stubs.hal_rsa_clock_init(en);
#endif

}



#endif  // end of "#if CONFIG_RSA_EN"

