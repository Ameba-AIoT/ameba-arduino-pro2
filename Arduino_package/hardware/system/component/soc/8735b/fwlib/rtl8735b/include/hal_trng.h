/**************************************************************************//**
 * @file     hal_trng.h
 * @brief    The HAL API implementation for the TRNG device.
 * @version  V1.00
 * @date     2016-07-15
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

#ifndef _HAL_TRNG_H_
#define _HAL_TRNG_H_
#include "cmsis.h"

#ifdef  __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup ls_hal_trng TRNG
 * @ingroup rtl8735b
 * @{
 * @brief The TRNG HAL module of the LS platform.
 */

/**
  * @brief The stubs functions table to exports TRNG HAL functions in ROM.
  */

extern hal_trng_func_stubs_t hal_trng_stubs;

hal_status_t hal_trng_init(hal_trng_sec_adapter_t *ptrng_adp) ;
hal_status_t hal_trng_deinit(hal_trng_sec_adapter_t *ptrng_adp);
u32 hal_trng_get_rand(hal_trng_sec_adapter_t *ptrng_adp);

/** @} */ /* End of group ls_hal_trng */

#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_TRNG_H_"
