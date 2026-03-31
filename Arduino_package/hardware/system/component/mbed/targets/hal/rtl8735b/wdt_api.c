/**************************************************************************//**
 * @file     wdt_api.c
 * @brief    This file implements the watch dog timer Mbed HAL API functions.
 *
 * @version  V1.00
 * @date     2017-11-10
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2022 Realtek Corporation. All rights reserved.
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
#include "wdt_api.h"
#include "hal_wdt.h"
#include "hal_wdt_nsc.h"
#include "hal_sys_ctrl.h"
#include "hal_sys_ctrl_nsc.h"

#ifdef ARDUINO_SDK
uint32_t* AON_WDT;

void watchdog_init_arduino(uint32_t timeout_ms, uint32_t arduino_AON_sel)
{
	AON_WDT = (uint32_t *)malloc(sizeof(uint32_t));
	AON_WDT = arduino_AON_sel;

	if (AON_WDT) {
		hal_aon_wdt_enable(0, timeout_ms);
	} else {
		hal_wdt_reset(0x17);
		hal_wdt_init((timeout_ms * 1000));
	}
}

#else
#define AON_WDT     1
#endif

/**
 *  @brief   Initial the watch dog time setting
 *
 *  @param   timeout_ms: the watch-dog timer timeout value, in ms.(Min Value 1000 and Max value 65535)
 *           default action of timeout is to reset the whole system.
 *  @return  None
 *
 */
void watchdog_init(uint32_t timeout_ms)
{
	if (AON_WDT) {
		hal_aon_wdt_enable(0, timeout_ms);
	} else {
		hal_wdt_reset(0x17);
		hal_wdt_init((timeout_ms * 1000));
	}
}

/**
 *  @brief   Start the watchdog counting
 *
 *  @param   None
 *  @return  None
 *
 */
void watchdog_start(void)
{
	if (AON_WDT) {
		hal_wdt_aon_enable();
	} else {
		hal_wdt_enable();
	}
}

/**
 *  @brief   Stop the watchdog counting
 *
 *  @param   None
 *  @return  None
 *
 */
void watchdog_stop(void)
{
	if (AON_WDT) {
		hal_wdt_aon_disable();
	} else {
		hal_wdt_disable();
	}
}

/**
 *  @brief   Refresh the watchdog counting to prevent WDT timeout
 *
 *  @param   None
 *  @return  None
 *
 */
void watchdog_refresh(void)
{
	if (AON_WDT) {
		hal_wdt_aon_disable();
		hal_wdt_aon_enable();
	} else {
		hal_wdt_refresh();
	}
}

/**
*  @brief   Switch the watchdog timer to interrupt mode and
*           register a watchdog timer timeout interrupt handler.
*           The interrupt handler will be called when the watch-dog
*           timer is timeout.
*
*  @param   handler: the callback function for WDT timeout interrupt.
*           id: the parameter for the callback function
*  @return  None
*
*/
void watchdog_irq_init(wdt_irq_handler handler, uint32_t id)
{
	if (AON_WDT) {
		dbg_printf("\r\nThe AON WDT dosen't supprt IRQ Mode\r\n");
	} else {
		hal_wdt_reg_irq((irq_handler_t)handler, (void *)id);
	}
}

/**
*  @brief   Check reboot reason was AON WDT or not
*
*  @param   None
*  @return  1:Reboot reason was AON WDT
*	    0:Reboot reason wasn't AON WDT
*
*/
uint8_t watchdog_aon_reboot_check(void)
{
	return hal_wdt_check_wdt_aon_reboot();
}

/**
*  @brief   Clear AON WDT boot reason
*
*  @param   None
*  @return  None
*
*/
void watchdog_aon_clear(void)
{
	hal_wdt_aon_clear();
}


