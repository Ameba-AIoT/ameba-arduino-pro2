/**************************************************************************//**
* @file        hal_crypto_nsc.h
* @brief       The HAL Non-secure callable API implementation for the crypto
*
* @version     V1.00
* @date        2022-03-22
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



#ifndef _HAL_CRYPTO_NSC_H_
#define _HAL_CRYPTO_NSC_H_
#include "cmsis.h"
#include <arm_cmse.h>   /* Use CMSE intrinsics */

#ifdef  __cplusplus
extern "C"
{
#endif



#if defined(CONFIG_BUILD_SECURE)
int NS_ENTRY hal_crypto_engine_init_nsc(void);
int NS_ENTRY hal_crypto_engine_deinit_nsc(void);
int NS_ENTRY hal_crypto_crc32_cmd_nsc(IN const u8 *message, IN const u32 msglen, OUT u32 *pCrc);
int NS_ENTRY hal_crypto_crc32_dma_nsc(IN const u8 *message, IN const u32 msglen, OUT u32 *pCrc);
int NS_ENTRY hal_crypto_crc_division_core_nsc(const uint8_t op_crc_type, IN uint8_t *message, IN uint32_t msglen, OUT uint32_t *Result);
#endif

#if defined(CONFIG_BUILD_NONSECURE)
int hal_crypto_engine_init_nsc(void);
int hal_crypto_engine_deinit_nsc(void);
int hal_crypto_crc32_cmd_nsc(IN const u8 *message, IN const u32 msglen, OUT u32 *pCrc);
int hal_crypto_crc32_dma_nsc(IN const u8 *message, IN const u32 msglen, OUT u32 *pCrc);
int hal_crypto_crc_division_core_nsc(const uint8_t op_crc_type, IN uint8_t *message, IN uint32_t msglen, OUT uint32_t *Result);
#endif  // end of "#if defined(CONFIG_BUILD_NONSECURE)"


#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_CRYPTO_NSC_H_"
