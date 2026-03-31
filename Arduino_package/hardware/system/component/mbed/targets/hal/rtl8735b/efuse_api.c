/**************************************************************************//**
* @file        efuse_api.c
* @brief       This file implements the Efuse Mbed HAL API functions.
*
* @version     V1.00
* @date        2019-01-03
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
#include "hal_otp.h"
#include "hal_otp_nsc.h"
#include "efuse_api.h"
#include "hal.h"
#include "memory.h"

#if CONFIG_OTP_EN


int efuse_otp_read(u8 offset, u8 len, u8 *buf)
{
	int ret_val = 0;

	ret_val = hal_user_otp_get(offset, len, buf);
	return ret_val;
}

int efuse_otp_write(u8 offset, u8 len, u8 *buf)
{
	int ret_val = 0;

	ret_val = hal_user_otp_set(offset, len, buf);
	return ret_val;

}

int efuse_s_jtag_key_write(u8 *buf, u8 key_num)
{
	return hal_otp_s_jtag_key_write(buf, key_num);
}

int efuse_ns_jtag_key_write(u8 *buf, u8 key_num)
{
	return hal_otp_ns_jtag_key_write(buf, key_num);
}

int efuse_crypto_key_get(uint8_t *pkey, uint8_t key_num)
{
	return hal_otp_crypto_key_get(pkey, key_num);
}

int efuse_crypto_key_write(uint8_t *pkey, uint8_t key_num, uint8_t w_lock_en)
{
	return hal_otp_crypto_key_write(pkey, key_num, w_lock_en);
}

int efuse_ecdsa_key_get(uint8_t *pkey, uint8_t key_num)
{
	return hal_otp_ecdsa_key_get(pkey, key_num);
}

int efuse_ecdsa_key_write(uint8_t *pkey, uint8_t key_num, uint8_t w_lock_en)
{
	return hal_otp_ecdsa_key_write(pkey, key_num, w_lock_en);
}

#endif
