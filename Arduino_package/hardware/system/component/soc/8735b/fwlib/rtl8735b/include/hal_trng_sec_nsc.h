/**************************************************************************//**
* @file        hal_trng_nsc.h
* @brief       The HAL Non-secure callable API implementation for GPIO
*
* @version     V1.00
* @date        2020-11-12
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



#ifndef _HAL_TRNG_NSC_H_
#define _HAL_TRNG_NSC_H_
#include "cmsis.h"

#ifdef  __cplusplus
extern "C"
{
#endif


#if defined(CONFIG_BUILD_SECURE)
hal_status_t NS_ENTRY hal_trng_sec_init_nsc(void);
hal_status_t  NS_ENTRY hal_trng_sec_deinit_nsc(void);
u32  NS_ENTRY hal_trng_sec_get_rand_nsc(void);
#endif // end of #if defined(CONFIG_BUILD_SECURE)



#if defined(CONFIG_BUILD_NONSECURE)
hal_status_t   hal_trng_init_sec_nsc(void);
hal_status_t  hal_trng_deinit_sec_nsc(void);
u32  hal_trng_sec_get_rand_nsc(void);

#define hal_trng_sec_init           hal_trng_sec_init_nsc
#define hal_trng_sec_deinit         hal_trng_sec_deinit_nsc
#define hal_trng_sec_get_rand       hal_trng_sec_get_rand_nsc
#endif  // end of "#if defined(CONFIG_BUILD_NONSECURE)"


#ifdef  __cplusplus
}
#endif

#endif  // end of "#define _HAL_TRNG_NSC_H_"
