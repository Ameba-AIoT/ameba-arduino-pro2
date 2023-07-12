/**************************************************************************//**
* @file        hal_wdtl.h
* @brief       The HAL API implementation for the WDT
*
* @version     V1.00
* @date        2021-01-04
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



#ifndef _HAL_WDT_H_
#define _HAL_WDT_H_
#include "cmsis.h"

#ifdef  __cplusplus
extern "C"
{
#endif

/**
* @addtogroup N/A
* @{
*/



void hal_wdt_set_timeout(uint32_t time_us);
void hal_wdt_init(uint32_t time_us);
void hal_wdt_enable(void);
void hal_wdt_disable(void);
void hal_wdt_refresh(void);
void hal_wdt_reg_irq(irq_handler_t handler, void *arg);
void hal_wdt_unreg_irq(void);
void hal_wdt_reset(u8 reset);
void hal_wdt_aon_enable(void);
void hal_wdt_aon_disable(void);
void hal_wdt_all_enable(void);
void hal_wdt_all_disable(void);
uint8_t hal_wdt_check_wdt_en(const uint8_t wdt_obj);
uint8_t hal_wdt_check_wdt_aon_reboot(void);
void hal_wdt_aon_clear(void);

/** @} */ /* End of group hal_wdt*/

#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_SYS_CTRL_H_"
