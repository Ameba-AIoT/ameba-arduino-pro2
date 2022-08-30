/**************************************************************************//**
 * @file     hal_pinmux.h
 * @brief    The HAL API implementation for the pin mux managemment.
 * @version  V1.00
 * @date     2022-02-15
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2020 Realtek Corporation. All rights reserved.
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

#ifndef _HAL_MISC_CTRL_H_
#define _HAL_MISC_CTRL_H_
#include "cmsis.h"
#include "hal_dev_load.h"

#ifdef  __cplusplus
extern "C"
{
#endif

#define HAL_MISC_UNKNOWN_BOOT_MODE      (0x10)
#define HAL_MISC_PARA_ERR               (0x11)
#define HAL_MISC_NULL_POINTER           (0x12)

int hal_misc_load_data_from_flash(dev_load_type_t *pmem_ld, uint32_t src_offset, uint32_t ld_assign_size, void *pdest);


#ifdef  __cplusplus
}
#endif

#endif  // end of "#define _HAL_PINMUX_H_"


