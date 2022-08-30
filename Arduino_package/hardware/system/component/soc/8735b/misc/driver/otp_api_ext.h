/**************************************************************************//**
* @file        otp_api_ext.h
* @brief       This file implements the OTP Mbed HAL API functions.
*
* @version     V1.00
* @date        2019-01-15
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

#ifndef MBED_EXT_OTP_API_EXT_H
#define MBED_EXT_OTP_API_EXT_H

#include "device.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief  Write user's content to otp on logical map
  * @param  addr: address on logical map
  * @param  cnts: how many bytes of data
  * @param  data: data need to be written
  * @retval 0: success <0: failure
  */
int otp_logical_write(u16 addr, u16 cnts, u8 *data);

/**
  * @brief  Read otp content on logical map
  * @param  laddr: address on logical map
  * @param  size: size of wanted data
  * @param  pbuf: buffer of read data
  * @retval : return number of used bytes
  */
int otp_logical_read(u16 laddr, u16 size, u8 *pbuf);

int otp_logical_remain(void);

u8 otp_byte_write(u32 addr, u8 data);

u8 otp_byte_read(u32 addr);

#ifdef __cplusplus
}
#endif

#endif