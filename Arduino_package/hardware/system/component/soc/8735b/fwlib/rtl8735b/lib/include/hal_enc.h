/**************************************************************************//**
 * @file     hal_enc.h
 * @brief    The HAL API implementation for the Encoder device.
 * @version  V1.00
 * @date     2016-12-14
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


#ifndef _HAL_ENC_H_
#define _HAL_ENC_H_

#include "cmsis.h"

#ifdef  __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup hal_enc Encoder
 * @ingroup 8735b_hal
 * @{
 * @brief The Encoder HAL module.
 */

/*  Macros for Encoder module system related configuration  */
/** @defgroup GROUP_ENC_MODULE_SYSTEM_CONFIGURATION ENC SYSTEM CONFIGURATION
 *  enc system related configuration
 *  @{
 */

/** @} */ // end of GROUP_ENC_MODULE_SYSTEM_CONFIGURATION


//hal_status_t hal_enc_init (unsigned int enc_isr);
hal_status_t hal_enc_set_clk(unsigned int enc_clk);
unsigned int hal_enc_get_clk(void);


/** @} */ /* End of group hal_enc */

#ifdef  __cplusplus
}
#endif

#endif  // end of "#define _HAL_ENC_H_"

