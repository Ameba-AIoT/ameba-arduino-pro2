/**
 * Copyright (c) 2015, Realsil Semiconductor Corporation. All rights reserved.
 *
 */

#include <stdio.h>
#include <stdarg.h>
#include "trace_uart.h"
#include "hci_dbg.h"
#include "serial_api.h"
#include "serial_ex_api.h"

#define TRACE_TX PE_1
#define TRACE_RX PE_2
#define TRACE_UART_BAUDRATE 1500000

typedef struct _TraceUartInfo {
	bool tx_switch;
} TRACE_UART_INFO;

static TRACE_UART_INFO g_uart_obj;
serial_t trace_sobj;

bool trace_uart_init(void)
{
	if (!CHECK_CFG_SW(CFG_SW_BT_TRACE_LOG)) {
		printf("trace_uart_init: TRACE LOG OPEN\r\n");
		hal_pinmux_unregister(TRACE_TX, 0x01 << 4);
		hal_pinmux_unregister(TRACE_RX, 0x01 << 4);
		hal_gpio_pull_ctrl(TRACE_TX, 0);
		hal_gpio_pull_ctrl(TRACE_RX, 0);

		serial_init(&trace_sobj, TRACE_TX, TRACE_RX);

		serial_baud(&trace_sobj, TRACE_UART_BAUDRATE);

		serial_format(&trace_sobj, 8, ParityNone, 1);

		g_uart_obj.tx_switch = true;
	} else {
		g_uart_obj.tx_switch = false;
	}
	return true;
}

bool trace_uart_deinit(void)
{
	if (!CHECK_CFG_SW(CFG_SW_BT_TRACE_LOG)) {
		if (g_uart_obj.tx_switch == true) {
			serial_free(&trace_sobj);
			g_uart_obj.tx_switch = false;
			return true;
		} else {
			printf("trace_uart_deinit: no need\r\n");
			return false;
		}
	}
	return true;
}

bool trace_uart_tx(uint8_t *pstr, uint16_t len, UART_TX_CB tx_cb)
{
	if (g_uart_obj.tx_switch == false) {
		if (tx_cb) {
			tx_cb();
		}
		return true;
	}

	serial_send_blocked(&trace_sobj, (char *)pstr, len, len);

	if (tx_cb) {
		tx_cb();
	}

	return true;
}

