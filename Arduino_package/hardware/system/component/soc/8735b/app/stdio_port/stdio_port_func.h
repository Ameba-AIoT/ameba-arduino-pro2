/**************************************************************************//**
 * @file     stdio_port_func.h
 * @brief    Declares UART STDIO function prototype.
 * @version  v1.00
 * @date     2020/11/27
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
#ifndef _STDIO_PORT_FUNC_H_
#define _STDIO_PORT_FUNC_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#if !defined(ROM_REGION)

#include "rt_printf.h"

extern const stdio_printf_func_stubs_t __rom_stubs_stdprintf_s;     // symbol from linker script
extern const stdio_printf_func_stubs_t __rom_stubs_stdprintf_ns;     // symbol from linker script
extern const stdio_printf_func_stubs_t stdio_printf_stubs;     // symbol from linker script

#if defined(CONFIG_PLATFORM_8735B)
#if !defined(CONFIG_BUILD_NONSECURE) || defined (CONFIG_BUILD_RAM)
__STATIC_INLINE
void stdio_port_init_s(void *adapter, stdio_putc_t putc, stdio_getc_t getc)
{
	__rom_stubs_stdprintf_s.stdio_port_init(adapter, putc, getc);
}

__STATIC_INLINE
void stdio_port_deinit_s(void)
{
	__rom_stubs_stdprintf_s.stdio_port_deinit();
}
#endif

#if !defined(CONFIG_BUILD_SECURE) || defined (CONFIG_BUILD_RAM)
__STATIC_INLINE
void stdio_port_init_ns(void *adapter, stdio_putc_t putc, stdio_getc_t getc)
{
	__rom_stubs_stdprintf_ns.stdio_port_init(adapter, putc, getc);
}

__STATIC_INLINE
void stdio_port_deinit_ns(void)
{
	__rom_stubs_stdprintf_ns.stdio_port_deinit();
}
#endif

#endif  // end of "#if defined(CONFIG_PLATFORM_8195BHP) || defined(CONFIG_PLATFORM_8710C)"

__STATIC_INLINE
void stdio_port_init(void *adapter, stdio_putc_t putc, stdio_getc_t getc)
{
	stdio_printf_stubs.stdio_port_init(adapter, putc, getc);
}

__STATIC_INLINE
void stdio_port_deinit(void)
{
	stdio_printf_stubs.stdio_port_deinit();
}

__STATIC_INLINE
int stdio_port_putc(char c)
{
	return stdio_printf_stubs.stdio_port_putc(c);
}

__STATIC_INLINE
int stdio_port_sputc(void *arg, char c)
{
	return stdio_printf_stubs.stdio_port_sputc(arg, c);
}

__STATIC_INLINE
void stdio_port_bufputc(void *buf, char c)
{
	stdio_printf_stubs.stdio_port_bufputc(buf, c);
}

__STATIC_INLINE
int stdio_port_getc(char *data)
{
	return stdio_printf_stubs.stdio_port_getc(data);
}

#endif  // end of "#if !defined(ROM_REGION)"

#ifdef  __cplusplus
}
#endif

#endif  // #ifndef _STDIO_PORT_FUNC_H_

