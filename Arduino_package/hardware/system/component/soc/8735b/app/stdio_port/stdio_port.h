/**************************************************************************//**
 * @file     stdio_port.h
 * @brief    The header file of the UART STDIO functions.
 *
 * @version  V1.00
 * @date     2016-09-22
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2016 Realtek Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 ******************************************************************************/

#ifndef _STDIO_PORT_H_
#define _STDIO_PORT_H_

#ifdef  __cplusplus
extern "C"
{
#endif

/**
  \brief  Type of UART STDIO functions.
 */
typedef void (*stdio_putc_t)(void *apapter, const char);
typedef int (*stdio_getc_t)(void *adapter, char *);
typedef int (*printf_putc_t)(void *arg, const char);


/**
  \brief  Type of the UART STDIO adapter.
 */
typedef struct _stdio_port {
	void *adapter;
	stdio_putc_t putc;
	stdio_getc_t getc;
} stdio_port_t, *pstdio_port_t;

/**
  \brief  Type of the UART STDIO adapter.
 */
typedef struct _stdio_buf_s {
	char *pbuf;
	char *pbuf_lim;
} stdio_buf_t, *pstdio_buf_t;

#if defined(ROM_REGION)

void _stdio_port_init(void *adapter, stdio_putc_t putc, stdio_getc_t getc);
void _stdio_port_deinit(void);
int _stdio_port_putc(char c);
int _stdio_port_sputc(void *arg, char c);
int _stdio_port_bufputc(void *buf, char c);
int _stdio_port_getc(char *data);

#endif  // end of "#if defined(ROM_REGION)"

#ifdef  __cplusplus
}
#endif

#endif  // #ifndef _STDIO_PORT_H_

