/**************************************************************************//**
 * @file     spi_api.c
 * @brief    This file implements the DMA Mbed HAL API functions.
 *
 * @version  V1.00
 * @date     2017-05-31
 *
 * @note
 *
 ******************************************************************************
 * @attention
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
 ******************************************************************************
 */
#include "cmsis.h"

#if CONFIG_SPI_EN

#include "objects.h"
#include "spi_api.h"
#include "spi_ex_api.h"
#include "PinNames.h"
#include "hal_ssi.h"
#include "string.h"

void spi_tx_done_callback(VOID *obj);
void spi_rx_done_callback(VOID *obj);
void spi_bus_tx_done_callback(VOID *obj);

volatile u8 format_is_set[4];

void spi_init(spi_t *obj, PinName mosi, PinName miso, PinName sclk, PinName ssel)
{
	phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);
	spi_pin_sel_t spi_pin;

	memset((void *)obj, 0, sizeof(spi_t));
	obj->state = 0;

	format_is_set[0] = 0;
	format_is_set[1] = 0;
	format_is_set[2] = 0;
	format_is_set[3] = 0;

	spi_pin.spi_cs_pin = ssel;
	spi_pin.spi_clk_pin = sclk;
	spi_pin.spi_miso_pin = miso;
	spi_pin.spi_mosi_pin = mosi;
	phal_ssi_adaptor->spi_pin = spi_pin;

	DBG_SSI_INFO("mosi: %d, miso: %d, sclk: %d, ssel: %d\n", mosi, miso, sclk, ssel);

#ifdef CONFIG_GDMA_EN
	phal_ssi_adaptor->ptx_gdma_adaptor = &obj->spi_gdma_adp_tx;
	phal_ssi_adaptor->prx_gdma_adaptor = &obj->spi_gdma_adp_rx;
	obj->dma_en = 0;
#endif
}

void spi_free(spi_t *obj)
{
	phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);

	hal_ssi_deinit(phal_ssi_adaptor);
	obj->dma_en = 0;
}

/*
 * mode | POL PHA
 * -----+--------
 *   0  |  0   0
 *   1  |  0   1
 *   2  |  1   0
 *   3  |  1   1
 *
 * SCPOL_INACTIVE_IS_LOW  = 0,
 * SCPOL_INACTIVE_IS_HIGH = 1
 *
 * SCPH_TOGGLES_IN_MIDDLE = 0,
 * SCPH_TOGGLES_AT_START  = 1
 */
void spi_format(spi_t *obj, int bits, int mode, int slave)
{
	phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);
	u32 clk_pin = (phal_ssi_adaptor->spi_pin).spi_clk_pin;

#if IS_CUT_TEST(CONFIG_CHIP_VER)
	if (slave) {
		if (clk_pin == PIN_E5) {
			phal_ssi_adaptor->index = 2;
		} else if (clk_pin == PIN_F8) {
			phal_ssi_adaptor->index = 3;
		} else {
			DBG_SSI_ERR(ANSI_COLOR_RED"spi_format(): Invalid Pin seleciton %x.\n"ANSI_COLOR_RESET, clk_pin);
		}
	} else {
		if (clk_pin == PIN_E5) {
			phal_ssi_adaptor->index = 0;
		} else if (clk_pin == PIN_F8) {
			phal_ssi_adaptor->index = 1;
		} else {
			DBG_SSI_ERR(ANSI_COLOR_RED"spi_format(): Invalid Pin seleciton %x.\n"ANSI_COLOR_RESET, clk_pin);
		}
	}
#else
	if (slave) {
		if (clk_pin == PIN_E1) {
			phal_ssi_adaptor->index = 2;
		} else if (clk_pin == PIN_F6) {
			phal_ssi_adaptor->index = 3;
		} else {
			DBG_SSI_ERR(ANSI_COLOR_RED"spi_format(): Invalid Pin seleciton %x.\n"ANSI_COLOR_RESET, clk_pin);
		}
	} else {
		if (clk_pin == PIN_E1) {
			phal_ssi_adaptor->index = 0;
		} else if (clk_pin == PIN_F6) {
			phal_ssi_adaptor->index = 1;
		} else {
			DBG_SSI_ERR(ANSI_COLOR_RED"spi_format(): Invalid Pin seleciton %x.\n"ANSI_COLOR_RESET, clk_pin);
		}
	}
#endif
	if ((hal_ssi_init(phal_ssi_adaptor)) != HAL_OK) {
		DBG_SSI_ERR(ANSI_COLOR_RED"spi_format(): SPI %x init fails.\n"ANSI_COLOR_RESET, phal_ssi_adaptor->index);
		return;
	}

	phal_ssi_adaptor->tx_done_callback = spi_tx_done_callback;
	phal_ssi_adaptor->tx_done_cb_para = (void *)obj;
	phal_ssi_adaptor->rx_done_callback = spi_rx_done_callback;
	phal_ssi_adaptor->rx_done_cb_para = (void *)obj;
	phal_ssi_adaptor->tx_idle_callback = spi_bus_tx_done_callback;
	phal_ssi_adaptor->tx_idle_cb_para = (void *)obj;

	/*Initialize ISR setting to prevent from inadvert effects*/
	hal_ssi_set_interrupt_mask(phal_ssi_adaptor, 0);

	if (slave) {
		hal_ssi_set_device_role(phal_ssi_adaptor, SsiSlave);
	} else {
		hal_ssi_set_device_role(phal_ssi_adaptor, SsiMaster);
	}

	hal_spi_format(phal_ssi_adaptor, bits - 1, mode);

	if (slave) {
		if (phal_ssi_adaptor->sclk_polarity == ScpolInactiveIsLow) {
			hal_gpio_pull_ctrl((u32)clk_pin, Pin_PullDown);
		} else {
			hal_gpio_pull_ctrl((u32)clk_pin, Pin_PullUp);
		}
	}

	format_is_set[phal_ssi_adaptor->index] = 1;

}

void spi_frequency(spi_t *obj, int hz)
{
	phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);

	if (format_is_set[phal_ssi_adaptor->index] == 0) {
		DBG_SSI_ERR("Please initialize SPI format first!\r\n");
	}

	hal_ssi_set_sclk(phal_ssi_adaptor, hz);
}

static inline void ssi_write(spi_t *obj, int value)
{
	phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);

	while (!hal_ssi_writable(phal_ssi_adaptor));
	hal_ssi_write(phal_ssi_adaptor, value);
}

static inline int ssi_read(spi_t *obj)
{
	phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);

	while (!hal_ssi_readable(phal_ssi_adaptor));
	return (int)hal_ssi_read(phal_ssi_adaptor);
}

int spi_master_write(spi_t *obj, int value)
{
	ssi_write(obj, value);
	return ssi_read(obj);
}

int spi_slave_receive(spi_t *obj)
{
	phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);
	int readable;
	int busy;

	readable = hal_ssi_readable(phal_ssi_adaptor);
	busy = hal_ssi_get_busy(phal_ssi_adaptor);
	return ((readable && !busy) ? 1 : 0);
}

int spi_slave_read(spi_t *obj)
{
	return ssi_read(obj);
}

void spi_slave_write(spi_t *obj, int value)
{
	ssi_write(obj, value);
}

int spi_busy(spi_t *obj)
{
	phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);

	return (int)hal_ssi_get_busy(phal_ssi_adaptor);
}

//Discard data in the rx fifo, SPI bus can observe these data
void spi_flush_rx_fifo(spi_t *obj)
{
	phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);
	u32 rx_fifo_level;
	u32 i;

	while (hal_ssi_readable(phal_ssi_adaptor)) {
		rx_fifo_level = hal_ssi_get_rxfifo_level(phal_ssi_adaptor);
		for (i = 0; i < rx_fifo_level; i++) {
			hal_ssi_read(phal_ssi_adaptor);
		}
	}
}

//This function is only for the slave device to flush tx fifo
//It will discard all data in both tx fifo and rx fifo, then reset the state of slave tx.
//Data in the tx & rx fifo will be dropped without being able to be observed from SPI bus
void spi_slave_flush_fifo(spi_t *obj)
{
	phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);
	u8 role;

	role = phal_ssi_adaptor->role;

	if (role != SsiSlave) {
		DBG_SSI_ERR("The SPI is not a slave\n");
	}

	hal_ssi_disable(phal_ssi_adaptor);
	hal_ssi_enable(phal_ssi_adaptor);
	obj->state &= ~SPI_STATE_TX_BUSY;
}

// Bus Idle: Real TX done, TX FIFO empty and bus shift all data out already
void spi_bus_tx_done_callback(VOID *obj)
{
	spi_t *spi_obj = (spi_t *)obj;
	spi_irq_handler handler;

	if (spi_obj->bus_tx_done_handler) {
		handler = (spi_irq_handler)spi_obj->bus_tx_done_handler;
		handler(spi_obj->bus_tx_done_irq_id, (SpiIrq)0);
	}
}

void spi_tx_done_callback(VOID *obj)
{
	spi_t *spi_obj = (spi_t *)obj;
	spi_irq_handler handler;

	if (spi_obj->state & SPI_STATE_TX_BUSY) {
		spi_obj->state &= ~SPI_STATE_TX_BUSY;
		if (spi_obj->irq_handler) {
			handler = (spi_irq_handler)spi_obj->irq_handler;
			handler(spi_obj->irq_id, SpiTxIrq);
		}
	}
}

void spi_rx_done_callback(VOID *obj)
{
	spi_t *spi_obj = (spi_t *)obj;
	spi_irq_handler handler;

	spi_obj->state &= ~SPI_STATE_RX_BUSY;
	if (spi_obj->irq_handler) {
		handler = (spi_irq_handler)spi_obj->irq_handler;
		handler(spi_obj->irq_id, SpiRxIrq);
	}
}

void spi_irq_hook(spi_t *obj, spi_irq_handler handler, uint32_t id)
{
	obj->irq_handler = (u32)handler;
	obj->irq_id = (u32)id;
}

void spi_bus_tx_done_irq_hook(spi_t *obj, spi_irq_handler handler, uint32_t id)
{
	obj->bus_tx_done_handler = (u32)handler;
	obj->bus_tx_done_irq_id = (u32)id;
}

void spi_enable(spi_t *obj)
{
	phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);

	hal_ssi_enable(phal_ssi_adaptor);
}

void spi_disable(spi_t *obj)
{
	phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);

	hal_ssi_disable(phal_ssi_adaptor);
}

// Slave mode read a sequence of data by interrupt mode
int32_t spi_slave_read_stream(spi_t *obj, char *rx_buffer, uint32_t length)
{
	phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);
	int32_t ret;

	if (obj->state & SPI_STATE_RX_BUSY) {
		DBG_SSI_WARN("spi_slave_read_stream: state(0x%x) is not ready\r\n",
					 obj->state);
		return HAL_BUSY;
	}

	DBG_SSI_INFO("rx_buffer addr: %X, length: %d\n", rx_buffer, length);
	obj->state |= SPI_STATE_RX_BUSY;

	if ((ret = hal_ssi_interrupt_init_read(phal_ssi_adaptor, rx_buffer, length)) != HAL_OK) {
		obj->state &= ~SPI_STATE_RX_BUSY;
	}

	return ret;
}

void spi_set_master_rxdelay(spi_t *obj, u32 rx_delay)
{
	phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);
	SSI_TypeDef *spi_dev = (SSI_TypeDef *) phal_ssi_adaptor->spi_dev;

	hal_ssi_disable(phal_ssi_adaptor);
	spi_dev->SSI_RX_SAMPLE_DLY = rx_delay;
	hal_ssi_enable(phal_ssi_adaptor);
}

// Slave mode write a sequence of data by interrupt mode
int32_t spi_slave_write_stream(spi_t *obj, char *tx_buffer, uint32_t length)
{
	phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);
	int32_t ret;

	if (obj->state & SPI_STATE_TX_BUSY) {
		DBG_SSI_WARN("spi_slave_write_stream: state(0x%x) is not ready\r\n",
					 obj->state);
		return HAL_BUSY;
	}

	obj->state |= SPI_STATE_TX_BUSY;

	if ((ret = hal_ssi_interrupt_init_write(phal_ssi_adaptor, tx_buffer, length)) != HAL_OK) {
		obj->state &= ~SPI_STATE_TX_BUSY;
	}

	return ret;
}

// Master mode read a sequence of data by interrupt mode
// The length unit is byte, for both 16-bits and 8-bits mode
int32_t spi_master_read_stream(spi_t *obj, char *rx_buffer, uint32_t length)
{
	phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);
	int32_t ret;

	if (obj->state & SPI_STATE_RX_BUSY) {
		DBG_SSI_WARN("spi_master_read_stream: state(0x%x) is not ready\r\n",
					 obj->state);
		return HAL_BUSY;
	}

	// wait bus idle
	while (hal_ssi_get_busy(phal_ssi_adaptor));

	obj->state |= SPI_STATE_RX_BUSY;
	if ((ret = hal_ssi_interrupt_init_read(phal_ssi_adaptor, rx_buffer, length)) == HAL_OK) {
		/* as Master mode, it need to push data to TX FIFO to generate clock out
		   then the slave can transmit data out */
		// send some dummy data out
		if ((ret = hal_ssi_interrupt_init_write(phal_ssi_adaptor, NULL, length)) != HAL_OK) {
			obj->state &= ~SPI_STATE_RX_BUSY;
		}
	} else {
		obj->state &= ~SPI_STATE_RX_BUSY;
	}

	return ret;
}

// Master mode write a sequence of data by interrupt mode
// The length unit is byte, for both 16-bits and 8-bits mode
int32_t spi_master_write_stream(spi_t *obj, char *tx_buffer, uint32_t length)
{
	phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);
	int32_t ret;

	if (obj->state & SPI_STATE_TX_BUSY) {
		DBG_SSI_WARN("spi_master_write_stream: state(0x%x) is not ready\r\n",
					 obj->state);
		return HAL_BUSY;
	}

	obj->state |= SPI_STATE_TX_BUSY;

	/* as Master mode, sending data will receive data at sametime, so we need to
	   drop those received dummy data */
	if ((ret = hal_ssi_interrupt_init_write(phal_ssi_adaptor, tx_buffer, length)) != HAL_OK) {
		obj->state &= ~SPI_STATE_TX_BUSY;
	}

	return ret;
}

// Master mode write a sequence of data by interrupt mode
// The length unit is byte, for both 16-bits and 8-bits mode
int32_t spi_master_write_read_stream(spi_t *obj, char *tx_buffer,
									 char *rx_buffer, uint32_t length)
{
	phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);
	int32_t ret;

	if (obj->state & (SPI_STATE_RX_BUSY | SPI_STATE_TX_BUSY)) {
		DBG_SSI_WARN("spi_master_write_and_read_stream: state(0x%x) is not ready\r\n",
					 obj->state);
		return HAL_BUSY;
	}

	// wait bus idle
	while (hal_ssi_get_busy(phal_ssi_adaptor));

	obj->state |= SPI_STATE_RX_BUSY;
	/* as Master mode, sending data will receive data at sametime */
	if ((ret = hal_ssi_interrupt_init_read(phal_ssi_adaptor, rx_buffer, length)) == HAL_OK) {
		obj->state |= SPI_STATE_TX_BUSY;
		if ((ret = hal_ssi_interrupt_init_write(phal_ssi_adaptor, tx_buffer, length)) != HAL_OK) {
			obj->state &= ~(SPI_STATE_RX_BUSY | SPI_STATE_TX_BUSY);
		}
	} else {
		obj->state &= ~(SPI_STATE_RX_BUSY);
	}

	return ret;
}

int32_t spi_slave_read_stream_timeout(spi_t *obj, char *rx_buffer, uint32_t length, uint32_t timeout_ms)
{
	phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);
	int ret, timeout = 0;
	u32 start_us;

	if (obj->state & SPI_STATE_RX_BUSY) {
		DBG_SSI_WARN("spi_slave_read_stream: state(0x%x) is not ready\r\n",
					 obj->state);
		return HAL_BUSY;
	}

	obj->state |= SPI_STATE_RX_BUSY;

	hal_ssi_enter_critical(phal_ssi_adaptor);
	if ((ret = hal_ssi_interrupt_init_read(phal_ssi_adaptor, rx_buffer, length)) != HAL_OK) {
		obj->state &= ~SPI_STATE_RX_BUSY;
	}
	hal_ssi_exit_critical(phal_ssi_adaptor);

	if ((ret == HAL_OK) && (timeout_ms > 0)) {
		start_us = hal_read_cur_time();
		while (obj->state & SPI_STATE_RX_BUSY) {
			if (hal_is_timeout(start_us, timeout_ms * 1000)) {
				if (hal_ssi_stop_recv(phal_ssi_adaptor) == HAL_OK) {
					obj->state &= ~ SPI_STATE_RX_BUSY;
					timeout = 1;
					DBG_SSI_INFO("Slave is timeout\n");
					break;
				} else {
					DBG_SSI_ERR("Slave cannot stop\n");
				}
			}
		}

		if (phal_ssi_adaptor->data_frame_size == DfsSixteenBits) {
			phal_ssi_adaptor->rx_length <<= 1;
		}

		if (timeout) {
			return (length - phal_ssi_adaptor->rx_length);
		} else {
			return length;
		}
	} else {
		return (-ret);
	}
}

int32_t spi_slave_read_stream_terminate(spi_t *obj, char *rx_buffer, uint32_t length)
{
	phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);
	volatile u8 cs_stop;

	cs_stop = 0;
	if (obj->state & SPI_STATE_RX_BUSY) {
		DBG_SSI_WARN("spi_slave_read_stream_dma: state(0x%x) is not ready\r\n",
					 obj->state);
		return HAL_BUSY;
	}

	obj->state |= SPI_STATE_RX_BUSY;
	hal_ssi_enter_critical(phal_ssi_adaptor);
	if (hal_ssi_interrupt_init_read(phal_ssi_adaptor, rx_buffer, length) != HAL_OK) {
		obj->state &= ~SPI_STATE_RX_BUSY;
	}
	hal_ssi_exit_critical(phal_ssi_adaptor);

	while (obj->state & SPI_STATE_RX_BUSY) {
		while (hal_ssi_get_busy(phal_ssi_adaptor)) {

			/*Transfer is complete*/
			if ((obj->state & SPI_STATE_RX_BUSY) == 0) {
				cs_stop = 0;
				break;
			}

			/*Transfer is not complete, but the SPI de-select the slave to cancel the transfer*/
			if (hal_ssi_get_busy(phal_ssi_adaptor) == 0) {
				hal_ssi_stop_recv(phal_ssi_adaptor);
				goto EndOfCS;
			}
		}
	}
EndOfCS:
	if ((obj->state & SPI_STATE_RX_BUSY) != 0) {
		cs_stop = 1;
		obj->state &= ~ SPI_STATE_RX_BUSY;
	}

	if (phal_ssi_adaptor->data_frame_size == DfsSixteenBits) {
		phal_ssi_adaptor->rx_length <<= 1;
	}

	if (cs_stop == 1) {
		return (length - phal_ssi_adaptor->rx_length);
	} else {
		return length;
	}
}

int32_t spi_slave_read_stream_unfix_size(spi_t *obj, char *rx_buffer, uint32_t length)
{
	phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);
	int32_t ret;

	if (obj->state & SPI_STATE_RX_BUSY) {
		DBG_SSI_WARN("spi_slave_read_stream: state(0x%x) is not ready\r\n",
					 obj->state);
		return HAL_BUSY;
	}

	hal_ssi_set_rxfifo_threshold(phal_ssi_adaptor, 0);
	phal_ssi_adaptor->unfix_read_en |= 0x01;

	DBG_SSI_INFO("rx_buffer addr: %X, length: %d\n", rx_buffer, length);
	obj->state |= SPI_STATE_RX_BUSY;

	if ((ret = hal_ssi_interrupt_init_read(phal_ssi_adaptor, rx_buffer, length)) != HAL_OK) {
		obj->state &= ~SPI_STATE_RX_BUSY;
	}

	return ret;
}


#ifdef CONFIG_GDMA_EN
int32_t spi_slave_read_stream_dma(spi_t *obj, char *rx_buffer, uint32_t length)
{
	phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);
	int32_t ret;

	if (obj->state & SPI_STATE_RX_BUSY) {
		DBG_SSI_WARN("spi_slave_read_stream_dma: state(0x%x) is not ready\r\n",
					 obj->state);
		return HAL_BUSY;
	}

	if ((obj->dma_en & SPI_DMA_RX_EN) == 0) {
		if (HAL_OK == hal_ssi_rx_gdma_init(phal_ssi_adaptor, phal_ssi_adaptor->prx_gdma_adaptor)) {
			obj->dma_en |= SPI_DMA_RX_EN;
		} else {
			return HAL_BUSY;
		}
	}

	obj->state |= SPI_STATE_RX_BUSY;
	ret = hal_ssi_dma_recv(phal_ssi_adaptor, (u8 *)rx_buffer, length);

	if (ret != HAL_OK) {
		obj->state &= ~SPI_STATE_RX_BUSY;
	}

	return (ret);
}

int32_t spi_slave_write_stream_dma(spi_t *obj, char *tx_buffer, uint32_t length)
{
	phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);
	int32_t ret;

	if (obj->state & SPI_STATE_TX_BUSY) {
		DBG_SSI_WARN("spi_slave_write_stream_dma: state(0x%x) is not ready\r\n",
					 obj->state);
		return HAL_BUSY;
	}

	if ((obj->dma_en & SPI_DMA_TX_EN) == 0) {
		if (HAL_OK == hal_ssi_tx_gdma_init(phal_ssi_adaptor, phal_ssi_adaptor->ptx_gdma_adaptor)) {
			obj->dma_en |= SPI_DMA_TX_EN;
		} else {
			return HAL_BUSY;
		}
	}

	obj->state |= SPI_STATE_TX_BUSY;
	ret = hal_ssi_dma_send(phal_ssi_adaptor, (u8 *)tx_buffer, length);

	if (ret != HAL_OK) {
		obj->state &= ~SPI_STATE_TX_BUSY;
	}

	return (ret);
}

int32_t spi_master_read_stream_dma(spi_t *obj, char *rx_buffer, uint32_t length)
{
	return spi_master_write_read_stream_dma(obj, rx_buffer, rx_buffer, length);
}

int32_t spi_master_write_stream_dma(spi_t *obj, char *tx_buffer, uint32_t length)
{
	phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);
	int32_t ret;

	if (obj->state & SPI_STATE_TX_BUSY) {
		DBG_SSI_WARN("spi_master_write_stream_dma: state(0x%x) is not ready\r\n",
					 obj->state);
		return HAL_BUSY;
	}

	if ((obj->dma_en & SPI_DMA_TX_EN) == 0) {
		if (HAL_OK == hal_ssi_tx_gdma_init(phal_ssi_adaptor, phal_ssi_adaptor->ptx_gdma_adaptor)) {
			obj->dma_en |= SPI_DMA_TX_EN;
		} else {
			return HAL_BUSY;
		}
	}

	obj->state |= SPI_STATE_TX_BUSY;
	ret = hal_ssi_dma_send(phal_ssi_adaptor, (u8 *)tx_buffer, length);

	if (ret != HAL_OK) {
		obj->state &= ~SPI_STATE_TX_BUSY;
	}

	return ret;
}

int32_t spi_master_write_read_stream_dma(spi_t *obj, char *tx_buffer, char *rx_buffer, uint32_t length)
{
	phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);
	int32_t ret;

	if (obj->state & (SPI_STATE_RX_BUSY | SPI_STATE_TX_BUSY)) {
		DBG_SSI_WARN("spi_master_write_and_read_stream: state(0x%x) is not ready\r\n",
					 obj->state);
		return HAL_BUSY;
	}

	if ((obj->dma_en & SPI_DMA_TX_EN) == 0) {
		if (HAL_OK == hal_ssi_tx_gdma_init(phal_ssi_adaptor, phal_ssi_adaptor->ptx_gdma_adaptor)) {
			obj->dma_en |= SPI_DMA_TX_EN;
		} else {
			return HAL_BUSY;
		}
	}

	if ((obj->dma_en & SPI_DMA_RX_EN) == 0) {
		if (HAL_OK == hal_ssi_rx_gdma_init(phal_ssi_adaptor, phal_ssi_adaptor->prx_gdma_adaptor)) {
			obj->dma_en |= SPI_DMA_RX_EN;
		} else {
			return HAL_BUSY;
		}
	}

	obj->state |= SPI_STATE_RX_BUSY;
	/* as Master mode, sending data will receive data at sametime */
	if ((ret = hal_ssi_dma_recv(phal_ssi_adaptor, (u8 *)rx_buffer, length)) == HAL_OK) {
		obj->state |= SPI_STATE_TX_BUSY;
		if ((ret = hal_ssi_dma_send(phal_ssi_adaptor, (u8 *)tx_buffer, length)) != HAL_OK) {
			obj->state &= ~(SPI_STATE_RX_BUSY | SPI_STATE_TX_BUSY);
		}
	} else {
		obj->state &= ~(SPI_STATE_RX_BUSY);
	}

	return ret;
}

int32_t spi_slave_read_stream_dma_timeout(spi_t *obj, char *rx_buffer, uint32_t length, uint32_t timeout_ms)
{
	int ret, timeout = 0;
	u32 start_us;
	phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);

	if (obj->state & SPI_STATE_RX_BUSY) {
		DBG_SSI_WARN("spi_slave_read_stream_dma: state(0x%x) is not ready\r\n",
					 obj->state);
		return HAL_BUSY;
	}

	if ((obj->dma_en & SPI_DMA_RX_EN) == 0) {
		if (HAL_OK == hal_ssi_rx_gdma_init(phal_ssi_adaptor, phal_ssi_adaptor->prx_gdma_adaptor)) {
			obj->dma_en |= SPI_DMA_RX_EN;
		} else {
			return HAL_BUSY;
		}
	}

	obj->state |= SPI_STATE_RX_BUSY;

	hal_ssi_enter_critical(phal_ssi_adaptor);
	ret = hal_ssi_dma_recv(phal_ssi_adaptor, (u8 *)rx_buffer, length);
	hal_ssi_exit_critical(phal_ssi_adaptor);

	if ((ret == HAL_OK) && (timeout_ms > 0)) {
		start_us = hal_read_cur_time();
		while (obj->state & SPI_STATE_RX_BUSY) {
			if (hal_is_timeout(start_us, timeout_ms * 1000)) {
				if (hal_ssi_stop_recv(phal_ssi_adaptor) == HAL_OK) {
					obj->state &= ~ SPI_STATE_RX_BUSY;
					timeout = 1;
					DBG_SSI_INFO("Slave is timeout\n");
					break;
				} else {
					DBG_SSI_ERR("Slave cannot stop\n");
				}
			}
		}

		if (timeout) {
			return (length - phal_ssi_adaptor->rx_length);
		} else {
			return length;
		}

	} else {
		obj->state &= ~ SPI_STATE_RX_BUSY;
		return (-ret);
	}
}

int32_t spi_slave_read_stream_dma_terminate(spi_t *obj, char *rx_buffer, uint32_t length)
{
	phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);
	volatile u8 cs_stop;

	cs_stop = 0;
	if (obj->state & SPI_STATE_RX_BUSY) {
		DBG_SSI_WARN("spi_slave_read_stream_dma: state(0x%x) is not ready\r\n",
					 obj->state);
		return HAL_BUSY;
	}

	if ((obj->dma_en & SPI_DMA_RX_EN) == 0) {
		if (HAL_OK == hal_ssi_rx_gdma_init(phal_ssi_adaptor, phal_ssi_adaptor->prx_gdma_adaptor)) {
			obj->dma_en |= SPI_DMA_RX_EN;
		} else {
			return HAL_BUSY;
		}
	}

	obj->state |= SPI_STATE_RX_BUSY;
	hal_ssi_enter_critical(phal_ssi_adaptor);
	if (hal_ssi_dma_recv(phal_ssi_adaptor, (u8 *)rx_buffer, length) != HAL_OK) {
		obj->state &= ~ SPI_STATE_RX_BUSY;
	}
	hal_ssi_exit_critical(phal_ssi_adaptor);

	while (obj->state & SPI_STATE_RX_BUSY) {
		while (hal_ssi_get_busy(phal_ssi_adaptor)) {
			if ((obj->state & SPI_STATE_RX_BUSY) == 0) {
				cs_stop = 0;
				break;
			}

			if (hal_ssi_get_busy(phal_ssi_adaptor) == 0) {
				hal_ssi_stop_recv(phal_ssi_adaptor);
				goto EndOfDMACS;
			}
		}
	}
EndOfDMACS:
	if ((obj->state & SPI_STATE_RX_BUSY) != 0) {
		cs_stop = 1;
		obj->state &= ~ SPI_STATE_RX_BUSY;
	}

	if (cs_stop == 1) {
		return (length - phal_ssi_adaptor->rx_length);
	} else {
		return length;
	}
}

#endif  // end of "#ifdef CONFIG_GDMA_EN"
#endif  // end of "#if CONFIG_SPI_EN"
