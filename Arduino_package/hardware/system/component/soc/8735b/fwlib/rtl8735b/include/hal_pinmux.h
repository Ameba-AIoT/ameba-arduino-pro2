/**************************************************************************//**
 * @file     hal_pinmux.h
 * @brief    The HAL API implementation for the pin mux managemment.
 * @version  V1.00
 * @date     2021-07-29
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

#ifndef _HAL_PINMUX_H_
#define _HAL_PINMUX_H_
#include "cmsis.h"

#ifdef  __cplusplus
extern "C"
{
#endif

void hal_pinmux_rom_info_manage(hal_pin_mux_mang_t *pinmux_manag, uint8_t op, uint8_t obj_id);
void hal_pinmux_manager_init(hal_pin_mux_mang_t *pinmux_manag);

/**
 *  @brief To register a IO pin to the pin mux magagement.
 *         The pin mux management will do the checking of pin conflict and pin valid.
 *         And then power up the IO pad.
 *
 *  @param[in]  pin_name  The IO pin.
 *  @param[in]  periphl_id  The ID of the peripheral will use this pin.
 *
 *  @return     HAL_OK:  Pin register OK.
 *  @return     HAL_ERR_CONFLICT:  Pin conflict. This pin is occupied by other peripheral device.
 *  @return     HAL_ERR_HW: This pin is invalid for this IC.
 */
hal_status_t hal_pinmux_register(uint32_t pin_name, uint32_t periphl_id);

/**
 *  @brief Unregister a IO pin from the pin mux management.
 *         The pin mux management will power down the IO pad.
 *
 *  @param[in]  pin_name  The IO pin.
 *  @param[in]  periphl_id  The ID of the peripheral own these pins.
 *
 *  @return     HAL_OK:  Pin unregister OK.
 *  @return     HAL_ERR_PARA: The peripheral doesn't own this pin.
 */
hal_status_t hal_pinmux_unregister(uint32_t pin_name, uint32_t periphl_id);

#if defined(CONFIG_BUILD_NONSECURE)
// Build for Non-Secure
hal_status_t hal_pinmux_register_nsc(uint32_t pin_name, uint32_t periphl_id);
hal_status_t hal_pinmux_unregister_nsc(uint32_t pin_name, uint32_t periphl_id);
#endif

#ifdef  __cplusplus
}
#endif

#endif  // end of "#define _HAL_PINMUX_H_"


