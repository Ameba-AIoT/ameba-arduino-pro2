/**************************************************************************//**
 * @file     rtl8735b_wdt.h
 * @brief    The HAL related definition and macros for the UART device.
 *           Includes Registers and data type definition.
 * @version  V1.00
 * @date     2021-06-07
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

#ifndef _RTL_8735B_WDT_H_
#define _RTL_8735B_WDT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "rtl8735b_vndr_s_type.h"
#include "rtl8735b_pon_type.h"

enum {
	WDT_AON_CTRL = 0x11,
	WDT_VNDR_CTRL = 0x12
};

/**
 * @addtogroup hs_hal_wdt WDT
 * @ingroup 8735b_hal
 * @{
 * @brief The WDT HAL module of the AmebaProII platform.
 */

typedef struct hal_wdt_adapter_s {
	irq_handler_t nmi_handler;  /*!< the callback function for NMI IRQ */
	void *nmi_arg;              /*!< the application data will be back to the application
                                     with the NMI IRQ callback function */
	irq_handler_t wdt_handler;  /*!< the call-back function for the WDT timeout event */
	void *wdt_arg;              /*!< the application data will be back to the application
                                     with the WDT event callback function */

	// B-Cut & after
	irq_handler_t wdt_user_handler; /*!< the user's call-back function for the WDT timeout event */
	uint32_t wdt_timeout_us;        /*!< the WDT timeout period, in us */
	uint8_t wdt_expired;            /*!< the flag to indicated is the WDT is expired ever */

//    uint32_t reserved[20];  // reserved for RAM code extension
} hal_wdt_adapter_t, *phal_wdt_adapter_t;

void hal_rtl_wdt_set_timeout(uint32_t time_us);
void hal_rtl_wdt_init(uint32_t time_us);
void hal_rtl_wdt_enable(void);
void hal_rtl_wdt_disable(void);
void hal_rtl_wdt_refresh(void);
void hal_rtl_wdt_reg_irq(irq_handler_t handler, void *arg);
void hal_rtl_wdt_unreg_irq(void);
void hal_rtl_wdt_reset(u8 reset);

void hal_rtl_wdt_ctrl_aon_enable(void);
void hal_rtl_wdt_ctrl_aon_disable(void);
void hal_rtl_wdt_ctrl_all_enable(void);
void hal_rtl_wdt_ctrl_all_disable(void);
uint8_t hal_rtl_wdt_check_wdt_en(const uint8_t wdt_obj);

typedef struct hal_wdt_func_stubs_s {
	void (*wdt_set_timeout)(uint32_t time_us);
	void (*wdt_init)(uint32_t time_us);
	void (*wdt_enable)(void);
	void (*wdt_disable)(void);
	void (*wdt_refresh)(void);
	void (*wdt_reg_irq)(irq_handler_t handler, void *arg);
	void (*wdt_unreg_irq)(void);
	void (*wdt_reset)(u8 reset);
	void (*wdt_ctrl_aon_enable)(void);
	void (*wdt_ctrl_aon_disable)(void);
	void (*wdt_ctrl_all_enable)(void);
	void (*wdt_ctrl_all_disable)(void);
	uint32_t reserved[12];  // reserved space for next ROM code version function table extending.
} hal_wdt_func_stubs_t;


/** @} */ /* End of group hs_hal_wdt */

#ifdef __cplusplus
}
#endif

#endif  // #ifndef _RTL_8735B_WDT_H_

