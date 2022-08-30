/**************************************************************************//**
 * @file     rtl8735b_comp.h
 * @brief    The HAL related definition and macros for the UART device.
 *           Includes Registers and data type definition.
 * @version  V1.00
 * @date     2020-03-10
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

#ifndef _RTL_8735B_COMP_H_
#define _RTL_8735B_COMP_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "cmsis.h"
#include "rtl8735b_comp_type.h"
#include "rtl8735b_aon_type.h"
//#define VNDR_S      ((VNDR_S_TYPE_TypeDef*)         0x50002C00)
#define AON         ((AON_TypeDef*)            AON_BASE)
/**
 * @addtogroup hal_comp COMP
 * @ingroup 8735b_hal
 * @{
 * @brief The COMP HAL module of the AmebaProII platform.
 */

typedef struct hal_comp_adapter_s {
	irq_handler_t comp_handler;  /*!< the call-back function for the comp event */
	void *comp_arg;              /*!< the application data will be back to the application
                                     with the WDT event callback function */
	uint8_t comp_init;            /*!< the register to indicated is the comparator initialize */
	uint8_t comp_mode;            /*!< the register to indicated is the comparator operating mode */
	uint8_t vref0_0;            /*!< the register to indicated is the channel 0 vref0 */
	uint8_t vref1_0;            /*!< the register to indicated is the channel 0 vref1 */
	uint8_t vref0_1;            /*!< the register to indicated is the channel 1 vref0 */
	uint8_t vref1_1;            /*!< the register to indicated is the channel 1 vref1 */
	uint8_t vref0_2;            /*!< the register to indicated is the channel 2 vref0 */
	uint8_t vref1_2;            /*!< the register to indicated is the channel 2 vref1 */
	uint8_t vref0_3;            /*!< the register to indicated is the channel 3 vref0 */
	uint8_t vref1_3;            /*!< the register to indicated is the channel 3 vref1 */

//    uint32_t reserved[20];  // reserved for RAM code extension
} hal_comp_adapter_t, *phal_comp_adapter_t;

void hal_comp_init(void);
void hal_comp_deinit(void);
void hal_comp_auto_switch(void);
void hal_comp_sw_trigger(void);
void hal_comp_ext_timer(u8 timer_sel);
void hal_comp_write(u8 addr, u32 value);
u32 hal_comp_read(u8 addr);
void hal_comp_set_vref(u8 ch_num, u8 ref0, u8 ref1);
u32 hal_comp_read_intr(void);
void hal_comp_set_itemlist(u8 *array, u8 length);
void hal_comp_set_intr_ctrl(u8 ch_num, u8 en, u8 ctrl);
void hal_comp_reg_irq(irq_handler_t handler, void *arg);
void hal_comp_unreg_irq(void);

#if 0
typedef struct hal_comp_func_stubs_s {
	void (*wdt_set_timeout)(uint32_t time_us);
	void (*wdt_init)(uint32_t time_us);
	void (*wdt_enable)(void);
	void (*wdt_disable)(void);
	void (*wdt_refresh)(void);
	void (*wdt_reg_irq)(irq_handler_t handler, void *arg);
	void (*wdt_reset)(u8 reset);
	uint32_t reserved[7];  // reserved space for next ROM code version function table extending.
} hal_comp_func_stubs_t;
#endif

/** @} */ /* End of group hal_comp */

#ifdef __cplusplus
}
#endif

#endif  // #ifndef _RTL_8735B_COMP_H_

