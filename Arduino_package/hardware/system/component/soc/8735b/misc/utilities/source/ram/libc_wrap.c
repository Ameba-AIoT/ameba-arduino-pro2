/**************************************************************************//**
 * @file     libc_wrap.c
 * @brief    The wraper functions of ROM code to replace some of utility
 *           functions in Compiler's Library.
 * @version  V1.00
 * @date     2022-08-03
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
#if defined(CONFIG_PLATFORM_8195BHP) \
	|| defined(CONFIG_PLATFORM_8195BLP) \
	|| defined(CONFIG_PLATFORM_8710C) \
	|| defined(CONFIG_PLATFORM_8735B)
#include "platform_conf.h"
#endif
#include "basic_types.h"

__attribute__((weak)) void *__dso_handle = 0;

#if defined(CONFIG_CMSIS_FREERTOS_EN) && (CONFIG_CMSIS_FREERTOS_EN != 0)
/**************************************************
 * FreeRTOS memory management functions's wrapper to replace
 * malloc/free/realloc of GCC Lib.
 **************************************************/
//#include "FreeRTOS.h"
// pvPortReAlloc currently not defined in portalbe.h
extern void *pvPortReAlloc(void *pv,  size_t xWantedSize);
extern void *pvPortMalloc(size_t xWantedSize);
extern void *pvPortCalloc(size_t xWantedCnt, size_t xWantedSize);
extern void vPortFree(void *pv);

static void clean_memory(void *buf, int size)
{
	uint8_t *dst = (uint8_t *)buf;
	for (int i = 0; i < size; i++) {
		dst[i] = 0;
	}
}

void *__wrap_malloc(size_t size)
{
	return pvPortMalloc(size);
}

void *__wrap_realloc(void *p, size_t size)
{
	return (void *)pvPortReAlloc(p, size);
}

void *__wrap_calloc(size_t cnt, size_t size)
{
	void *pbuf;
	uint32_t total_size;

	total_size = cnt * size;
	pbuf = pvPortMalloc(total_size);
	if (pbuf) {
		//memset(pbuf, 0, total_size);
		clean_memory(pbuf, total_size);
	}

	return pbuf;
//	return (void*)pvPortCalloc(cnt, size);
}

void __wrap_free(void *p)
{
	vPortFree(p);
}

void *__wrap__malloc_r(void *rent, size_t size)
{
	(void)rent;
	return pvPortMalloc(size);
}

void *__wrap__realloc_r(void *rent, void *p, size_t size)
{
	(void)rent;
	return (void *)pvPortReAlloc(p, size);
}

void *__wrap__calloc_r(void *rent, size_t cnt, size_t size)
{
	void *pbuf;
	uint32_t total_size;

	(void)rent;

	total_size = cnt * size;
	pbuf = pvPortMalloc(total_size);
	if (pbuf) {
		//memset(pbuf, 0, total_size);
		clean_memory(pbuf, total_size);
	}

	return pbuf;
//    return (void*)pvPortCalloc(cnt, size);
}

void __wrap__free_r(void *rent, void *p)
{
	(void)rent;
	vPortFree(p);
}
#endif  //  #if defined(CONFIG_CMSIS_FREERTOS_EN) && (CONFIG_CMSIS_FREERTOS_EN != 0)

/**************************************************
 * string and memory api wrap for compiler
 *
 **************************************************/

#if defined(CONFIG_PLATFORM_8195BHP) || defined(CONFIG_PLATFORM_8195BLP) || defined(CONFIG_PLATFORM_8710C)\
	|| defined(CONFIG_PLATFORM_8735B)
#include "stdio_port.h"
#include "rt_printf.h"


int __wrap_puts(const char *str)
{
	while (*str != '\0') {
		stdio_printf_stubs.stdio_port_putc(*str++);
		if (*str == '\n') {
			stdio_printf_stubs.stdio_port_putc('\r');
		}
	}
	// converter LF --> CRLF
	stdio_printf_stubs.stdio_port_putc('\r');
	stdio_printf_stubs.stdio_port_putc('\n');
	return 0;
}

static int __wrap_stdio_port_sputc(void *arg, char c)
{
	stdio_printf_stubs.stdio_port_putc(c);
	if (c == '\n') {
		stdio_printf_stubs.stdio_port_putc('\r');
	}
	return 0;
}

int __wrap_printf(const char *fmt, ...)
{
	int count;
	va_list list;
	va_start(list, fmt);
#if defined(CONFIG_BUILD_SECURE)
	count = stdio_printf_stubs.printf_corel(__wrap_stdio_port_sputc, (void *)NULL, fmt, list);
#else
	count = stdio_printf_stubs.printf_core(__wrap_stdio_port_sputc, (void *)NULL, fmt, list);
#endif
	va_end(list);
	return count;
}

int __wrap_vprintf(const char *fmt, va_list args)
{
	int count;
#if defined(CONFIG_BUILD_SECURE)
	count = stdio_printf_stubs.printf_corel(__wrap_stdio_port_sputc, (void *)NULL, fmt, args);
#else
	count = stdio_printf_stubs.printf_core(__wrap_stdio_port_sputc, (void *)NULL, fmt, args);
#endif
	return count;
}

int __wrap_sprintf(char *buf, const char *fmt, ...)
{
	int count;
	va_list list;
	stdio_buf_t pnt_buf;

	pnt_buf.pbuf = buf;
	pnt_buf.pbuf_lim = 0;

	va_start(list, fmt);
#if defined(CONFIG_BUILD_SECURE)
	count = stdio_printf_stubs.printf_corel(stdio_printf_stubs.stdio_port_bufputc, (void *)&pnt_buf, fmt, list);
#else
	count = stdio_printf_stubs.printf_core(stdio_printf_stubs.stdio_port_bufputc, (void *)&pnt_buf, fmt, list);
#endif
	*(pnt_buf.pbuf) = 0;
	va_end(list);
	(void)list;

	return count;
}

int __wrap_snprintf(char *buf, size_t size, const char *fmt, ...)
{
	int count;
	va_list list;
	stdio_buf_t pnt_buf;

	pnt_buf.pbuf = buf;
	pnt_buf.pbuf_lim = buf + size - 1;  // reserve 1 byte for 'end of string'

	va_start(list, fmt);
#if defined(CONFIG_BUILD_SECURE)
	count = stdio_printf_stubs.printf_corel(stdio_printf_stubs.stdio_port_bufputc, (void *)&pnt_buf, fmt, list);
#else
	count = stdio_printf_stubs.printf_core(stdio_printf_stubs.stdio_port_bufputc, (void *)&pnt_buf, fmt, list);
#endif
	*(pnt_buf.pbuf) = 0;
	va_end(list);
	(void)list;

	return count;
}

int __wrap_vsnprintf(char *buf, size_t size, const char *fmt, va_list args)
{
	int count;
	stdio_buf_t pnt_buf;

	pnt_buf.pbuf = buf;
	pnt_buf.pbuf_lim = buf + size - 1;  // reserve 1 byte for 'end of string'
#if defined(CONFIG_BUILD_SECURE)
	count = stdio_printf_stubs.printf_corel(stdio_printf_stubs.stdio_port_bufputc, (void *)&pnt_buf, fmt, args);
#else
	count = stdio_printf_stubs.printf_core(stdio_printf_stubs.stdio_port_bufputc, (void *)&pnt_buf, fmt, args);
#endif
	*(pnt_buf.pbuf) = 0;

	return count;
}


// define in AmebaPro utilites/include/memory.h
#include "memory.h"
int __wrap_memcmp(const void *av, const void *bv, size_t len)
{
	return rt_memcmp(av, bv, len);
}

void *__wrap_memcpy(void *s1, const void *s2, size_t n)
{
	return rt_memcpy(s1, s2, n);
}

void *__wrap_memmove(void *destaddr, const void *sourceaddr, unsigned length)
{
	return rt_memmove(destaddr, sourceaddr, length);
}

void *__wrap_memset(void *dst0, int val, size_t length)
{
	return rt_memset(dst0, val, length);
}
// define in AmebaPro utilites/include/strporc.h
// replace by linking command
#include "strproc.h"
char *__wrap_strcat(char *dest,  char const *src)
{
	return strcat(dest, src);
}

char *__wrap_strchr(const char *s, int c)
{
	return strchr(s, c);
}

int __wrap_strcmp(char const *cs, char const *ct)
{
	return strcmp(cs, ct);
}

int __wrap_strncmp(char const *cs, char const *ct, size_t count)
{
	return strncmp(cs, ct, count);
}

int __wrap_strnicmp(char const *s1, char const *s2, size_t len)
{
	return strnicmp(s1, s2, len);
}


char *__wrap_strcpy(char *dest, char const *src)
{
	return strcpy(dest, src);
}


char *__wrap_strncpy(char *dest, char const *src, size_t count)
{
	return strncpy(dest, src, count);
}


size_t __wrap_strlcpy(char *dst, char const *src, size_t s)
{
	return strlcpy(dst, src, s);
}


size_t __wrap_strlen(char const *s)
{
	return strlen(s);
}


size_t __wrap_strnlen(char const *s, size_t count)
{
	return strnlen(s, count);
}


char *__wrap_strncat(char *dest, char const *src, size_t count)
{
	return strncat(dest, src, count);
}

char *__wrap_strpbrk(char const *cs, char const *ct)
{
	return strpbrk(cs, ct);
}


size_t __wrap_strspn(char const *s, char const *accept)
{
	return strspn(s, accept);
}


char *__wrap_strstr(char const *s1, char const *s2)
{
	return strstr(s1, s2);
}


char *__wrap_strtok(char *s, char const *ct)
{
	return strtok(s, ct);
}


size_t __wrap_strxfrm(char *dest, const char *src, size_t n)
{
	return strxfrm(dest, src, n);
}

char *__wrap_strsep(char **s, const char *ct)
{
	return strsep(s, ct);
}

double __wrap_strtod(const char *str, char **endptr)
{
	return strtod(str, endptr);
}

float __wrap_strtof(const char *str, char **endptr)
{
	return strtof(str, endptr);
}


long double __wrap_strtold(const char *str, char **endptr)
{
	return strtold(str, endptr);
}

long __wrap_strtol(const char *nptr, char **endptr, int base)
{
	return strtol(nptr, endptr, base);
}


long long __wrap_strtoll(const char *nptr, char **endptr, int base)
{
	return strtoll(nptr, endptr, base);
}


unsigned long __wrap_strtoul(const char *nptr, char **endptr, int base)
{
	return strtoul(nptr, endptr, base);
}


unsigned long long __wrap_strtoull(const char *nptr, char **endptr, int base)
{
	return strtoull(nptr, endptr, base);
}

int __wrap_atoi(const char *num)
{
	return atoi(num);
}

unsigned int __wrap_atoui(const char *num)
{
	return atoui(num);
}

long __wrap_atol(const char *num)
{
	return atol(num);
}

unsigned long __wrap_atoul(const char *num)
{
	return atoul(num);
}


unsigned long long __wrap_atoull(const char *num)
{
	return atoull(num);
}


double __wrap_atof(const char *str)
{
	return atof(str);
}

__weak void abort_handler(void) {}

void __wrap_abort(void)
{
	__wrap_printf("\n\rabort execution\n\r");
	abort_handler();
	// stop OS and IRQ, watchdog may reset
	__disable_irq();
	while (1);
}

#if defined(__GNUC__)
#include <errno.h>

static int gnu_errno;
volatile int *__aeabi_errno_addr(void)
{
	return &gnu_errno;
}
#endif

#endif // #if defined(CONFIG_PLATFORM_8195BHP) || defined(CONFIG_PLATFORM_8195BLP) || defined(CONFIG_PLATFORM_8710C) || defined(CONFIG_PLATFORM_8715B)
