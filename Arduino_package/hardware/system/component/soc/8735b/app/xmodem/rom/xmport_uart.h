/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */

#ifndef _XMPORT_UART_H_
#define _XMPORT_UART_H_

#include "xmodem.h"

#define XM_BUF_SIZE     2060

typedef struct xmodem_uart_port_handler_s {
	hal_uart_adapter_t *pxm_uart_adp;
	u8 *pxm_uart_rx_buf;
	u32 xm_uart_rx_buf_sz;
	volatile u32 xm_uart_rx_buf_in;
	volatile u32 xm_uart_rx_buf_out;
	volatile u32 xm_uart_rx_buf_len;
} xmodem_uart_port_handler_t, *pxmodem_uart_port_handler_t;

typedef struct stdio_port_backup_s {
	uint32_t cfg_err;
	uint32_t cfg_info;
	uint32_t cfg_warn;
	uint32_t baud_rate;
	uint8_t  parity;
	uint8_t  flow_ctrl;
	uint8_t  is_inited;
} stdio_port_backup_t, *pstdio_port_backup_t;

void xmodem_uart_init(xmodem_uart_port_handler_t *pxm_uart_port, hal_uart_adapter_t *puart_adp,
					  u8 *prx_buf, u32 rx_buf_sz);
void xmodem_uart_deinit(xmodem_uart_port_handler_t *pxm_uart_port);
void xmodem_uart_func_hook(XMODEM_COM_PORT *pXComPort, xmodem_uart_port_handler_t *pxm_uart_port);
char xmodem_uart_getc(void *pxm_port);
void xmodem_uart_putc(void *pxm_port, char c);

#endif  // end of "#define _XMPORT_UART_H_"

