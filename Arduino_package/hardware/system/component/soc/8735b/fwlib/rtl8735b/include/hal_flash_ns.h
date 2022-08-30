/**************************************************************************//**
 * @file     hal_flash_ns.h
 * @brief    The header file of hal_flash_ns.c.
 * @version  1.00
 * @date     2017-08-22
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

#ifndef _HAL_FLASH_NS_H_
#define _HAL_FLASH_NS_H_

/**

        \addtogroup hal_flash FLASH
        \ingroup 8735b_hal
        \brief The Flash commands and information of the HS platform.
        @{
*/

/// @cond DOXYGEN_ROM_HAL_API

/**

        \addtogroup hal_flash_ns_func FLASH HAL ROM APIs
        @{
*/
#if defined(CONFIG_BUILD_NONSECURE)

void flash_ns_read_unique_id(void *adaptor, uint8_t *buf, uint8_t len);
hal_status_t flash_ns_read_id(void *adaptor);
void flash_ns_set_write_enable(void *adaptor);
void flash_ns_set_status(void *adaptor, u8 cmd, u8 data);
void flash_ns_set_status_no_check(void *adaptor, u8 cmd, u8 data);
void flash_ns_set_status_with_addr(void *adaptor, u8 cmd, u8 addr, u8 data);
void flash_ns_set_extended_addr(void *adaptor, u8 data);
void flash_ns_set_write_protect_mode(void *adaptor, u8 mode);
u8 flash_ns_get_status(void *adaptor, u8 cmd);
u8 flash_ns_get_status_with_addr(void *adaptor, u8 cmd, u8 addr);
u8 flash_ns_get_extended_addr(void *adaptor);
void flash_ns_wait_ready(void *adaptor);
void flash_ns_chip_erase(void *adaptor);
void flash_ns_64k_block_erase(void *adaptor, u32 address);
void flash_ns_32k_block_erase(void *adaptor, u32 address);
void flash_ns_sector_erase(void *adaptor, u32 address);
u8 flash_ns_query_sector_protect_state(void *adaptor, u32 address);
void flash_ns_protect_sector(void *adaptor, u32 address);
void flash_ns_unprotect_sector(void *adaptor, u32 address);
void flash_ns_global_lock(void *adaptor);
void flash_ns_global_unlock(void *adaptor);
void flash_ns_set_dummy_cycle(void *adaptor);
void flash_ns_set_quad_enable(void *adaptor);
void flash_ns_unset_quad_enable(void *adaptor);
void flash_ns_enable_qpi(void *adaptor);
void flash_ns_return_spi(void *adaptor);
void flash_ns_return_str(void *adaptor);
hal_status_t flash_ns_enter_power_down(void *adaptor);
hal_status_t flash_ns_release_from_power_down(void *adaptor);
void flash_ns_stream_read(void *adaptor, u32 length, u32 addr, u8 *data);
void flash_ns_stream_write(void *adaptor, u32 length, u32 addr, u8 *data);
void flash_ns_burst_read(void *adaptor, u32 length, u32 addr, u8 *data);
void flash_ns_burst_write(void *adaptor, u32 length, u32 addr, u8 *data);
void flash_ns_page_program(void *adaptor, u32 length, u32 addr, u8 *data);
void flash_ns_reset_to_spi(void *adaptor);
#endif
/** *@} */ /* End of group hal_flash_ns_func */

/// @endcond /* End of condition DOXYGEN_ROM_HAL_API */

/** *@} */ /* End of group hal_flash */


#endif


