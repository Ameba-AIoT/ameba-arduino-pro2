/**************************************************************************//**
 * @file     hal_pinmux_nsc.c
 * @brief    The entry functions of Pin Mux HAL API functions for Non-secure.
 *
 * @version  V1.00
 * @date     2020-12-17
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

#include "hal_pinmux.h"



#if defined(CONFIG_BUILD_SECURE) && !defined(CONFIG_BUILD_BOOT)

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
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY hal_pinmux_register_nsc(uint32_t pin_name, uint32_t periphl_id)
{
	return hal_pinmux_register(pin_name, periphl_id);
}


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
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY hal_pinmux_unregister_nsc(uint32_t pin_name, uint32_t periphl_id)
{
	return hal_pinmux_unregister(pin_name, periphl_id);
}


#endif // end of "#if defined(CONFIG_BUILD_SECURE) && !defined(CONFIG_BUILD_BOOT)"


