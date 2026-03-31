/**************************************************************************//**
 * @file     serial_api.c
 * @brief    This file implements the UART serial port Mbed HAL API functions.
 *
 * @version  V1.00
 * @date     2017-07-26
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
#include "objects.h"
//#include "pinmap.h"
#include "hal_uart.h"
//#include "mbed_assert.h"
#include "serial_api.h"
#include "serial_ex_api.h"
#include "string.h"

#if CONFIG_UART_EN
#include "pinmap.h"
#include <string.h>

#define UART_NUM (5)
#define SERIAL_TX_IRQ_EN        0x01
#define SERIAL_RX_IRQ_EN        0x02
#define SERIAL_TX_DMA_EN        0x01
#define SERIAL_RX_DMA_EN        0x02
#define DRAM_ADDR_OFFSET        (24)
#define DRAM_HIGH_ADDR          (0x7)

#ifdef CONFIG_GDMA_EN
static uint8_t serial_dma_init[UART_NUM] = {0, 0, 0, 0, 0};
#endif

//#ifdef CONFIG_MBED_ENABLED
//int stdio_uart_inited;
//serial_t stdio_uart;
//#endif

void serial_init(serial_t *obj, PinName tx, PinName rx)
{
	uint32_t uart_tx, uart_rx;
	hal_status_t ret;

	uart_tx = tx;
	uart_rx = rx;
	ret = hal_uart_init(&obj->uart_adp, (uint8_t)uart_tx, (uint8_t)uart_rx, NULL);

	if (ret != HAL_OK) {
		DBG_UART_ERR("serial_init err (0x%x)\n", ret);
	}
//#ifdef CONFIG_MBED_ENABLED
//    // For stdio management
//    if (uart_idx == STDIO_UART) {
//        stdio_uart_inited = 1;
//        memcpy(&stdio_uart, obj, sizeof(serial_t));
//    }
//#endif
}

void serial_free(serial_t *obj)
{
	uint8_t uart_idx;

	uart_idx = obj->uart_adp.uart_idx;
	if ((serial_dma_init[uart_idx] & SERIAL_RX_DMA_EN) != 0) {
		hal_uart_rx_gdma_deinit(&obj->uart_adp);
		serial_dma_init[uart_idx] &= ~SERIAL_RX_DMA_EN;
	}
	if ((serial_dma_init[uart_idx] & SERIAL_TX_DMA_EN) != 0) {
		hal_uart_tx_gdma_deinit(&obj->uart_adp);
		serial_dma_init[uart_idx] &= ~SERIAL_TX_DMA_EN;
	}
	hal_uart_deinit(&obj->uart_adp);
}

void serial_baud(serial_t *obj, int baudrate)
{
	hal_uart_set_baudrate(&obj->uart_adp, (uint32_t)baudrate);
}

void serial_format(serial_t *obj, int data_bits, SerialParity parity, int stop_bits)
{
	hal_uart_set_format(&obj->uart_adp, data_bits, parity, stop_bits);
}

/******************************************************************************
 * INTERRUPTS HANDLING
 ******************************************************************************/
static void _serial_tx_irq_handler(uint32_t id, SerialIrq event)
{
	serial_t *obj = (serial_t *)id;
	uart_irq_callback_t irq_callback;

	obj->uart_adp.base_addr->ier_b.etbei = 0;
	if (obj->tx_irq_handler != NULL) {
		irq_callback = (uart_irq_callback_t)obj->tx_irq_handler;
		irq_callback(obj->tx_irq_id, TxIrq);
	}
}

void serial_irq_handler(serial_t *obj, uart_irq_handler handler, uint32_t id)
{
//    hal_uart_enter_critical();
//    hal_uart_txtd_hook (&obj->uart_adp, (uart_irq_callback_t)handler, id, TxIrq);
	obj->tx_irq_handler = (void *)handler;
	obj->tx_irq_id = id;
	hal_uart_txtd_hook(&obj->uart_adp, (uart_irq_callback_t)_serial_tx_irq_handler, (uint32_t)obj, TxIrq);
	hal_uart_rxind_hook(&obj->uart_adp, (uart_irq_callback_t)handler, id, RxIrq);
//    hal_uart_exit_critical();
}

void serial_irq_set(serial_t *obj, SerialIrq irq, uint32_t enable)
{
	if (enable) {
		if (irq == RxIrq) {
			obj->irq_en |= SERIAL_RX_IRQ_EN;
			obj->uart_adp.base_addr->ier_b.erbi = 1;
		} else if (irq == TxIrq) {
			obj->irq_en |= SERIAL_TX_IRQ_EN;
//            obj->uart_adp.base_addr->ier_b.etbei = 1;
		}
	} else { // disable
		if (irq == RxIrq) {
			obj->uart_adp.base_addr->ier_b.erbi = 0;
			obj->irq_en &= ~SERIAL_RX_IRQ_EN;
		} else if (irq == TxIrq) {
			obj->uart_adp.base_addr->ier_b.etbei = 0;
			obj->irq_en &= ~SERIAL_TX_IRQ_EN;
		}
	}
}

/******************************************************************************
 * READ/WRITE
 ******************************************************************************/

int serial_getc(serial_t *obj)
{
	while (!serial_readable(obj));
	return (int)(hal_uart_getc(&obj->uart_adp));
}

void serial_putc(serial_t *obj, int c)
{
	while (!serial_writable(obj));
	hal_uart_putc(&obj->uart_adp, (u8)c);
	if ((obj->irq_en & SERIAL_TX_IRQ_EN) != 0) {
		obj->uart_adp.base_addr->ier_b.etbei = 1;
	}
}

int serial_readable(serial_t *obj)
{
	if (obj->uart_adp.base_addr->rflvr_b.rx_fifo_lv > 0) {
		return 1;
	} else {
		return 0;
	}
}

int serial_writable(serial_t *obj)
{
	if (obj->uart_adp.base_addr->tflvr_b.tx_fifo_lv < Uart_Tx_FIFO_Size) {
		return 1;
	} else {
		return 0;
	}
}

void serial_clear(serial_t *obj)
{
	/* clear TX fifo */
	obj->uart_adp.base_addr->fcr_b.clear_txfifo = 1;

	/* clear RX FIFO and reset receiver */
	hal_uart_reset_rx_fifo(&obj->uart_adp);
}

void serial_clear_tx(serial_t *obj)
{
	/* clear TX fifo */
	obj->uart_adp.base_addr->fcr_b.clear_txfifo = 1;
	__NOP();
	__NOP();
	while (obj->uart_adp.base_addr->lsr_b.txfifo_empty != 1);
}

void serial_clear_rx(serial_t *obj)
{
	/* clear RX FIFO and reset receiver */
	hal_uart_reset_rx_fifo(&obj->uart_adp);
}

void serial_pinout_tx(PinName tx)
{
	// do nothing for our peripheral devices
	// the IO pin direction is auto configured by HW when a peripheral device function is enabled
	//pinmap_pinout(tx, NULL);
}

void serial_break_set(serial_t *obj)
{
	obj->uart_adp.base_addr->lcr_b.break_ctrl = 1;
}

void serial_break_clear(serial_t *obj)
{
	obj->uart_adp.base_addr->lcr_b.break_ctrl = 0;
}

void serial_send_comp_handler(serial_t *obj, void *handler, uint32_t id)
{
	hal_uart_txdone_hook(&obj->uart_adp, (uart_callback_t) handler, (void *)id);
}

void serial_recv_comp_handler(serial_t *obj, void *handler, uint32_t id)
{
	hal_uart_rxdone_hook(&obj->uart_adp, (uart_callback_t)handler, (void *)id);
}

void serial_set_flow_control(serial_t *obj, FlowControl type, PinName rxflow, PinName txflow)
{
	hal_uart_set_flow_control(&obj->uart_adp, (uint32_t)type);
}

void serial_rts_control(serial_t *obj, BOOLEAN rts_state)
{
	hal_uart_set_rts(&obj->uart_adp, rts_state);
}

// Blocked(busy wait) receive, return received bytes count
int32_t serial_recv_blocked(serial_t *obj, char *prxbuf, uint32_t len, uint32_t timeout_ms)
{
	int32_t rx_bytes;

	rx_bytes = hal_uart_recv(&obj->uart_adp, (uint8_t *)prxbuf, len, timeout_ms);
	if (obj->uart_adp.rx_status != HAL_UART_STATUS_OK) {
		DBG_UART_WARN("serial_recv_blocked: status(%d)\n", obj->uart_adp.rx_status);
	}

	return rx_bytes;
}

// Blocked(busy wait) send, return transmitted bytes count
int32_t serial_send_blocked(serial_t *obj, char *ptxbuf, uint32_t len, uint32_t timeout_ms)
{
	int32_t tx_bytes;

	tx_bytes = hal_uart_send(&obj->uart_adp, (uint8_t *)ptxbuf, len, timeout_ms);
	if (obj->uart_adp.tx_status != HAL_UART_STATUS_OK) {
		DBG_UART_WARN("serial_send_blocked: status(%d)\n", obj->uart_adp.tx_status);
	}

	return tx_bytes;
}

int32_t serial_recv_stream(serial_t *obj, char *prxbuf, uint32_t len)
{
	hal_status_t ret;

	ret = hal_uart_int_recv(&obj->uart_adp, (uint8_t *)prxbuf, len);

	return (ret);
}

int32_t serial_send_stream(serial_t *obj, char *ptxbuf, uint32_t len)
{
	hal_status_t ret;

	ret = hal_uart_int_send(&obj->uart_adp, (uint8_t *)ptxbuf, len);

	return (ret);
}

#ifdef CONFIG_GDMA_EN

static hal_status_t _serial_recv_dma_enable(serial_t *obj)
{
	uint8_t  uart_idx = obj->uart_adp.uart_idx;
	hal_status_t ret;

	if ((serial_dma_init[uart_idx] & SERIAL_RX_DMA_EN) != 0) {
		return HAL_OK;
	} else {
		ret = hal_uart_rx_gdma_init(&obj->uart_adp, &obj->rx_gdma);
		if (ret != HAL_OK) {
			DBG_UART_ERR("serial_init: RX GDMA init err(0x%x)\n", ret);
			return ret;
		} else {
			serial_dma_init[uart_idx] |= SERIAL_RX_DMA_EN;
		}
	}

	return ret;
}

int32_t serial_recv_stream_dma(serial_t *obj, char *prxbuf, uint32_t len)
{
	hal_status_t ret;

	ret = _serial_recv_dma_enable(obj);
	if (ret != HAL_OK) {
		return ret;
	}

	//Checks DRAM misalignment
	if (is_dcache_enabled() && (((uint32_t)(prxbuf)) >> DRAM_ADDR_OFFSET) == DRAM_HIGH_ADDR) {
		if (((uint32_t)(prxbuf) & 0x1F) != 0x0) {
			DBG_UART_ERR("PSRAM Buffer must be 32B aligned\r\n");
			return HAL_ERR_MEM;
		}
	}

	ret = hal_uart_dma_recv(&obj->uart_adp, (uint8_t *)prxbuf, len);
	return ret;
}

int32_t serial_send_stream_dma(serial_t *obj, char *ptxbuf, uint32_t len)
{
	uint8_t  uart_idx = obj->uart_adp.uart_idx;
	hal_status_t ret;

	//Checks DRAM misalignment
	if (is_dcache_enabled() && (((uint32_t)(ptxbuf)) >> DRAM_ADDR_OFFSET) == DRAM_HIGH_ADDR) {
		if (((uint32_t)(ptxbuf) & 0x1F) != 0x0) {
			DBG_UART_ERR("PSRAM Buffer must be 32B aligned\r\n");
			return HAL_ERR_MEM;
		}
	}

	if ((serial_dma_init[uart_idx] & SERIAL_TX_DMA_EN) == 0) {
		ret = hal_uart_tx_gdma_init(&obj->uart_adp, &obj->tx_gdma);
		if (ret != HAL_OK) {
			DBG_UART_ERR("serial_init: TX GDMA init err(0x%x)\n", ret);
		} else {
			serial_dma_init[uart_idx] |= SERIAL_TX_DMA_EN;
		}
	}

	ret = hal_uart_dma_send(&obj->uart_adp, (uint8_t *)ptxbuf, len);
	return ret;
}

int32_t serial_recv_stream_dma_timeout(serial_t *obj, char *prxbuf, uint32_t len, uint32_t timeout_ms, void *force_cs)
{
	hal_status_t ret;
	uint32_t start_us;
	uint32_t rx_bytes = len;
	void (*task_yield)(void);

	ret = _serial_recv_dma_enable(obj);
	if (ret != HAL_OK) {
		return -ret;
	}

	//Checks DRAM misalignment
	if (is_dcache_enabled() && (((uint32_t)(prxbuf)) >> DRAM_ADDR_OFFSET) == DRAM_HIGH_ADDR) {
		if (((uint32_t)(prxbuf) & 0x1F) != 0x0) {
			DBG_UART_ERR("PSRAM Buffer must be 32B aligned\r\n");
			return HAL_ERR_MEM;
		}
	}

	ret = hal_uart_dma_recv(&obj->uart_adp, (uint8_t *)prxbuf, len);
	if ((ret == HAL_OK) && (timeout_ms > 0)) {
		start_us = hal_read_curtime_us();
		task_yield = (void (*)(void))force_cs;

		while (obj->uart_adp.state & HAL_UART_STATE_DMARX_BUSY) {
			// check timeout
			if ((timeout_ms != UART_WAIT_FOREVER)) {
				if (hal_is_timeout(start_us, timeout_ms * 1000)) {
					rx_bytes = hal_uart_recv_abort(&obj->uart_adp);
					obj->uart_adp.rx_status = HAL_TIMEOUT;
					DBG_UART_WARN("serial_recv_stream_dma_timeout: Timeout\n");
					break;
				}
			}

			if (task_yield != NULL) {
				task_yield();
			}
		}
		return rx_bytes;
	} else {
		return -ret;
	}
}


#endif  // end of "#ifdef CONFIG_GDMA_EN"

int32_t serial_send_stream_abort(serial_t *obj)
{
	return (int32_t)hal_uart_send_abort(&obj->uart_adp);
}

int32_t serial_recv_stream_abort(serial_t *obj)
{
	return hal_uart_recv_abort(&obj->uart_adp);
}

void serial_disable(serial_t *obj)
{
	hal_uart_en_ctrl(obj->uart_adp.uart_idx, 0);
}

void serial_enable(serial_t *obj)
{
	hal_uart_en_ctrl(obj->uart_adp.uart_idx, 1);
}

// return the byte count received before timeout, or error(<0)
int32_t serial_recv_stream_timeout(serial_t *obj, char *prxbuf, uint32_t len, uint32_t timeout_ms, void *force_cs)
{
	hal_status_t ret;
	uint32_t start_us;
	uint32_t rx_bytes = len;
	void (*task_yield)(void);

	ret = hal_uart_int_recv(&obj->uart_adp, (uint8_t *)prxbuf, len);
	if ((ret == HAL_OK) && (timeout_ms > 0)) {
		start_us = hal_read_curtime_us();
		task_yield = (void (*)(void))force_cs;

		while (obj->uart_adp.state & HAL_UART_STATE_RX_BUSY) {
			// check timeout
			if ((timeout_ms != UART_WAIT_FOREVER)) {
				if (hal_is_timeout(start_us, timeout_ms * 1000)) {
					rx_bytes = hal_uart_recv_abort(&obj->uart_adp);
					obj->uart_adp.rx_status = HAL_TIMEOUT;
					DBG_UART_WARN("serial_recv_stream_timeout: Timeout\n");
					break;
				}
			}

			if (task_yield != NULL) {
				task_yield();
			}
		}
		return rx_bytes;
	} else {
		return -ret;
	}
}

// to hook lock/unlock function for multiple-thread application
void serial_hook_lock(serial_t *obj, void *lock, void *unlock, uint32_t id)
{
}

// to read Line-Status register
// Bit 0: RX Data Ready
// Bit 1: Overrun Error
// Bit 2: Parity Error
// Bit 3: Framing Error
// Bit 4: Break Interrupt (received data input is held in 0 state for a longer than a full word tx time)
// Bit 5: TX FIFO empty (THR empty)
// Bit 6: Reserved
// Bit 7: RX Error (parity error, framing error or break indication)
uint8_t serial_raed_lsr(serial_t *obj)
{
	return obj->uart_adp.base_addr->lsr;
}

// to read Modem-Status register
// Bit 0: DCTS, The CTS line has changed its state
// Bit 1: DDSR, The DSR line has changed its state
// Bit 2: TERI, RI line has changed its state from low to high state
// Bit 3: DDCD, DCD line has changed its state
// Bit 4: Complement of the CTS input
// Bit 5: Complement of the DSR input
// Bit 6: Complement of the RI input
// Bit 7: Complement of the DCD input
uint8_t serial_read_msr(serial_t *obj)
{
	return obj->uart_adp.base_addr->msr;
}

// to set the RX FIFO level to trigger RX interrupt/RTS de-assert
// FifoLv:
//     0: 1-Byte
//     1: 8-Byte
//     2: 16-Byte
//     3: 30-Byte
void serial_rx_fifo_level(serial_t *obj, SerialFifoLevel FifoLv)
{
	obj->uart_adp.base_addr->fcr_b.rxfifo_trigger_level = FifoLv;
}

#ifdef ARDUINO_SDK
void serial_init_arduino(serial_t *obj, PinName tx, PinName rx, uint8_t arduino_uart0_clk_sel)
{
	uint32_t uart_tx, uart_rx;
	hal_status_t ret;

	obj->uart_adp.reserv1 = arduino_uart0_clk_sel;

	uart_tx = tx;
	uart_rx = rx;
	ret = hal_uart_init(&obj->uart_adp, (uint8_t)uart_tx, (uint8_t)uart_rx, NULL);

	if (ret != HAL_OK) {
		DBG_UART_ERR("serial_init err (0x%x)\n", ret);
	}
}
#endif

#endif

