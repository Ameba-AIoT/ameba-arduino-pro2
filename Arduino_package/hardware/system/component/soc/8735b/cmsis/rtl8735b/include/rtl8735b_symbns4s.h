/**************************************************************************//**
 * @file     rtl8195bhp_symbns4s.h
 * @brief    The ROM code symbols exportted by NS region and will be
 *           referenced by S region code.
 * @version  V1.00
 * @date     2020-12-28
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2016 Realtek Corporation. All rights reserved.
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


#ifndef _RTL8735B_SYMBNS4S_H_
#define _RTL8735B_SYMBNS4S_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "shell.h"

// NS4S SYMBOL STUBS ADDR
#define NS_SYMBOL_STUBS_ADDR                    0x100BFF00

typedef struct symb_ns4s_s {
	const cmd_shell_func_stubs_t *pcmd_shell_stubs;
	const hal_gpio_func_stubs_t *phal_gpio_stubs;
	const hal_spic_func_stubs_t *phal_spic_stubs;
	const hal_flash_func_stubs_t *phal_flash_stubs;
	phal_timer_adapter_t *ppsystem_timer;
	void (*startup_ns)(void);
	void (*stdio_port_init_ns)(void *adapter, stdio_putc_t putc, stdio_getc_t getc);
	uint32_t reserved[20];
} symb_ns4s_t;



#ifdef __cplusplus
}

#endif

#endif  // #ifndef _RTL8735B_SYMBNS4S_H_

