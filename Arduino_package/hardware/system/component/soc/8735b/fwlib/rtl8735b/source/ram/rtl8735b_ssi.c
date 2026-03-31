/**************************************************************************//**
 * @file     rtl8195bhp_ssi.c
 * @brief    Implement SSI HAL ROM code functions.
 * @version  1.00
 * @date     2017-08-22
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
#include "cmsis.h"
#include "hal.h"
#include "hal_sys_ctrl.h"
#include "hal_sys_ctrl_nsc.h"

void SPI0_IRQHandler_ram(void);
void SPI1_IRQHandler_ram(void);
void SPI2_IRQHandler_ram(void);
void SPI3_IRQHandler_ram(void);

/**

        \addtogroup hal_ssi SPI
        @{
*/



/**
  \brief The global common data structure to store and manage common resources for all SPI adaptors.
*/
hal_ssi_group_t hal_ssi_group;

/// @cond DOXYGEN_ROM_HAL_API

/**

        \addtogroup hal_ssi_rom_func SPI HAL ROM APIs
        \ingroup hal_ssi
        \brief SPI HAL ROM API. SPI functions to control SPI and initiate SPI transfer.
               The user application(in RAM space) should not call these APIs directly.
               There is another set of SPI HAL APIs in the RAM space is provided for the user application.
        @{
*/


/**
  \brief The stubs functions table to exports SPI HAL functions in ROM.
*/
const hal_ssi_func_stubs_t hal_ssi_stubs = {
	.phal_ssi_group = &hal_ssi_group,
	.hal_ssi_clock_ctl = hal_rtl_ssi_clock_ctl,
	.hal_ssi_enable = hal_rtl_ssi_enable,
	.hal_ssi_disable = hal_rtl_ssi_disable,
	.hal_ssi_init_setting = hal_rtl_ssi_init_setting,
	.hal_ssi_deinit_setting = hal_rtl_ssi_deinit_setting,
	.hal_ssi_read_interrupt = hal_rtl_ssi_read_interrupt,
	.hal_ssi_read_unfix_size_interrupt = hal_rtl_ssi_read_unfix_size_interrupt,
	.hal_ssi_write_interrupt = hal_rtl_ssi_write_interrupt,
	.hal_ssi_irq_handle = hal_rtl_ssi_irq_handle,
	.hal_ssi_interrupt_enable = hal_rtl_ssi_interrupt_enable,
	.hal_ssi_interrupt_disable = hal_rtl_ssi_interrupt_disable,
	.hal_ssi_interrupt_init_read = hal_rtl_ssi_interrupt_init_read,
	.hal_ssi_interrupt_init_write = hal_rtl_ssi_interrupt_init_write,
	.hal_ssi_set_sclk = hal_rtl_ssi_set_sclk,
	.hal_ssi_set_format = hal_rtl_ssi_set_format,
	.hal_ssi_set_microwire = hal_rtl_ssi_set_microwire,
	.hal_ssi_set_sclk_polarity = hal_rtl_ssi_set_sclk_polarity,
	.hal_ssi_set_sclk_phase = hal_rtl_ssi_set_sclk_phase,
	.hal_ssi_set_data_frame_number = hal_rtl_ssi_set_data_frame_number,
	.hal_ssi_set_interrupt_mask = hal_rtl_ssi_set_interrupt_mask,
	.hal_ssi_set_device_role = hal_rtl_ssi_set_device_role,
	.hal_ssi_set_txfifo_threshold = hal_rtl_ssi_set_txfifo_threshold,
	.hal_ssi_set_rxfifo_threshold = hal_rtl_ssi_set_rxfifo_threshold,
	.hal_ssi_set_slave_enable = hal_rtl_ssi_set_slave_enable,
	.hal_ssi_get_rxfifo_level = hal_rtl_ssi_get_rxfifo_level,
	.hal_ssi_get_txfifo_level = hal_rtl_ssi_get_txfifo_level,
	.hal_ssi_get_status = hal_rtl_ssi_get_status,
	.hal_ssi_get_busy = hal_rtl_ssi_get_busy,
	.hal_ssi_get_interrupt_mask = hal_rtl_ssi_get_interrupt_mask,
	.hal_ssi_get_interrupt_status = hal_rtl_ssi_get_interrupt_status,
	.hal_ssi_get_raw_interrupt_status = hal_rtl_ssi_get_raw_interrupt_status,
	.hal_ssi_get_slave_enable_register = hal_rtl_ssi_get_slave_enable_register,
	.hal_ssi_writable = hal_rtl_ssi_writable,
	.hal_ssi_readable = hal_rtl_ssi_readable,
	.hal_ssi_write = hal_rtl_ssi_write,
	.hal_ssi_read = hal_rtl_ssi_read,
	.hal_ssi_stop_recv = hal_rtl_ssi_stop_recv,
	.hal_ssi_enter_critical = hal_rtl_ssi_enter_critical,
	.hal_ssi_exit_critical = hal_rtl_ssi_exit_critical,
	.hal_ssi_tx_gdma_irq_handle = hal_rtl_ssi_tx_gdma_irq_handle,
	.hal_ssi_rx_gdma_irq_handle = hal_rtl_ssi_rx_gdma_irq_handle,
	.hal_ssi_tx_gdma_init_setting = hal_rtl_ssi_tx_gdma_init_setting,
	.hal_ssi_rx_gdma_init_setting = hal_rtl_ssi_rx_gdma_init_setting,
	.hal_ssi_dma_send_init = hal_rtl_ssi_dma_send_init,
	.hal_ssi_dma_recv_init = hal_rtl_ssi_dma_recv_init
};

/** \brief Description of hal_rtl_ssi_clock_ctl
 *
 *    hal_rtl_ssi_clock_ctl is used to enable IP and turn on the clock for the target SPI device.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *   \param u8 ctl:      A control bit to decide to enable or disable the device.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_rtl_ssi_clock_ctl(phal_ssi_adaptor_t phal_ssi_adaptor, u8 ctl)
{
	u8 index = phal_ssi_adaptor->index;

	switch (index) {
	case 0:
		hal_sys_peripheral_en(SPI0_SYS, ctl);
		return HAL_OK;
		break;

	case 1:
		hal_sys_peripheral_en(SPI1_SYS, ctl);
		return HAL_OK;
		break;

	case 2:
		hal_sys_peripheral_en(HS_SPI0_SYS, ctl);
		return HAL_OK;
		break;

	case 3:
		hal_sys_peripheral_en(HS_SPI1_SYS, ctl);
		return HAL_OK;
		break;

	default:
		DBG_SSI_ERR("Invalid SSI Index %d!\n", index);
		return HAL_ERR_PARA;
		break;
	}
}

/** \brief Description of hal_rtl_ssi_enable
 *
 *    hal_rtl_ssi_enable is used to enable the target SPI device.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_rtl_ssi_enable(phal_ssi_adaptor_t phal_ssi_adaptor)
{
	DBG_SSI_INFO("hal_rtl_ssi_enable()\n");

	SSI_TypeDef *spi_dev = (SSI_TypeDef *) phal_ssi_adaptor->spi_dev;
	hal_status_t result;

	spi_dev->SSI_SSIENR = ENABLE;

	DBG_SSI_INFO("SSI%d REG_DW_SSI_SSIENR(%X) = %X\n", phal_ssi_adaptor->index, spi_dev->SSI_SSIENR);

	result = HAL_OK;
	return result;
}

/** \brief Description of hal_rtl_ssi_disable
 *
 *    hal_rtl_ssi_disable is used to disable the target SPI device.
 *    Data in SPI FIFO will be cleared when the device is disabled.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_rtl_ssi_disable(phal_ssi_adaptor_t phal_ssi_adaptor)
{
	DBG_SSI_INFO("hal_rtl_ssi_disable()\n");

	SSI_TypeDef *spi_dev = (SSI_TypeDef *) phal_ssi_adaptor->spi_dev;
	hal_status_t result;

	spi_dev->SSI_SSIENR = DISABLE;

	DBG_SSI_INFO("SSI%d REG_DW_SSI_SSIENR(%X) = %X\n", phal_ssi_adaptor->index, spi_dev->SSI_SSIENR);

	result = HAL_OK;
	return result;
}

/** \brief Description of hal_rtl_ssi_init_setting
 *
 *    hal_rtl_ssi_init_setting is used to initialize SPI device.
 *    It includes register base, clock, enable control and IRQ parameter initialization.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_rtl_ssi_init_setting(phal_ssi_adaptor_t phal_ssi_adaptor)
{
	DBG_SSI_INFO("hal_ssi_init_setting()\n");
	SSI_TypeDef *spi_dev;
	u8  index = phal_ssi_adaptor->index;

	switch (index) {
	case 0:
		/*Synopsys Master 0*/
		spi_dev = (SSI_TypeDef *)SSI0_BASE;
		phal_ssi_adaptor->irq_handle.irq_num = SPI0_IRQn;
		phal_ssi_adaptor->irq_handle.irq_fun = (irq_handler_t)SPI0_IRQHandler_ram;
		phal_ssi_adaptor->irq_handle.priority = SPI0_IRQPri;
		break;

	case 1:
		/*Synopsys Master 1*/
		spi_dev = (SSI_TypeDef *)SSI1_BASE;
		phal_ssi_adaptor->irq_handle.irq_num = SPI1_IRQn;
		phal_ssi_adaptor->irq_handle.irq_fun = (irq_handler_t)SPI1_IRQHandler_ram;
		phal_ssi_adaptor->irq_handle.priority = SPI1_IRQPri;
		break;

	case 2:
		/*RTK HS-Slave 0*/
		spi_dev = (SSI_TypeDef *)SSI2_BASE;
		phal_ssi_adaptor->irq_handle.irq_num = HSPI0_IRQn;
		phal_ssi_adaptor->irq_handle.irq_fun = (irq_handler_t)SPI2_IRQHandler_ram;
		phal_ssi_adaptor->irq_handle.priority = HSPI0_IRQPri;
		break;

	case 3:
		/*RTK HS-Slave 1*/
		spi_dev = (SSI_TypeDef *)SSI3_BASE;
		phal_ssi_adaptor->irq_handle.irq_num = HSPI1_IRQn;
		phal_ssi_adaptor->irq_handle.irq_fun = (irq_handler_t)SPI3_IRQHandler_ram;
		phal_ssi_adaptor->irq_handle.priority = HSPI1_IRQPri;
		break;

	default:
		DBG_SSI_ERR("hal_rtl_ssi_init: Invalid SSI Idx %d\r\n", index);
		return HAL_ERR_PARA;
	}

	hal_ssi_group.phal_ssi_adaptor[index] = phal_ssi_adaptor;

	DBG_SSI_INFO("spi_dev = %x\n", spi_dev);
	phal_ssi_adaptor->spi_dev = (SSI_TypeDef *)spi_dev;

	hal_rtl_ssi_clock_ctl(phal_ssi_adaptor, ENABLE);

	/*Set default slave to 0*/
	phal_ssi_adaptor->slave_select_enable = 0;

	/*Set default interrupt setting*/
	hal_rtl_ssi_set_txfifo_threshold(phal_ssi_adaptor, 8);
	hal_rtl_ssi_set_rxfifo_threshold(phal_ssi_adaptor, 7);

	phal_ssi_adaptor->rx_done_callback = NULL;
	phal_ssi_adaptor->rx_done_cb_para = NULL;
	phal_ssi_adaptor->rx_data = NULL;
	phal_ssi_adaptor->tx_done_callback = NULL;
	phal_ssi_adaptor->tx_done_cb_para = NULL;
	phal_ssi_adaptor->tx_data = NULL;
	phal_ssi_adaptor->tx_idle_callback = NULL;
	phal_ssi_adaptor->tx_idle_cb_para = NULL;

	return HAL_OK;
}

/** \brief Description of hal_rtl_ssi_deinit_setting
 *
 *    hal_rtl_ssi_deinit_setting is used to deinitialize the target SPI device after this SPI is no longer needed.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_rtl_ssi_deinit_setting(phal_ssi_adaptor_t phal_ssi_adaptor)
{
	SSI_TypeDef *spi_dev = (SSI_TypeDef *) phal_ssi_adaptor->spi_dev;
	u8 index = phal_ssi_adaptor->index;
	volatile hal_status_t result;

	if (index > 3) {
		DBG_SSI_ERR("Invalid SSI Index %d!\n", index);
		return HAL_ERR_PARA;
	}

	spi_dev->SSI_SSIENR = DISABLE;
	result = hal_rtl_ssi_clock_ctl(phal_ssi_adaptor, DISABLE);

	if (HAL_OK == result) {
		hal_rtl_ssi_interrupt_disable(phal_ssi_adaptor);
	}

	return result;
}

/** \brief Description of hal_rtl_ssi_read_interrupt
 *
 *    hal_rtl_ssi_read_interrupt is used to handle a interrupt when the receive FIFO threshold has reached in receive mode.
 *    As soon as CPU enters this handler function, it identifies the number of data frames in the receive FIFO.
 *    These data then are moved from the receive FIFO to memory.
 *    A SPI master still pushes new data into the receive FIFO at the same time, but these new data won't be handled in this interrupt.
 *    After all data have been received and handled properly by this interrupt handler, the interrupt handler jumps to a callback function assigned by users.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *
 *   \return void.
 */
void hal_rtl_ssi_read_interrupt(phal_ssi_adaptor_t phal_ssi_adaptor)
{
	DBG_SSI_INFO("hal_rtl_ssi_read_interrupt()\n");
	SSI_TypeDef *spi_dev = (SSI_TypeDef *) phal_ssi_adaptor->spi_dev;
	volatile u32 receive_level;
	volatile u32 readable;

	readable = spi_dev->SSI_SR & SSI_BIT_RFNE;

	if (readable) {
		receive_level = spi_dev->SSI_RXFLR;

		while (receive_level--) {
			if (phal_ssi_adaptor->rx_data != NULL) {
				if (phal_ssi_adaptor->data_frame_size == DfsSixteenBits) {
					// 16~9 bits mode
					*((u16 *)(phal_ssi_adaptor->rx_data)) = HAL_READ16((u32)&spi_dev->SSI_DR, 0);
					phal_ssi_adaptor->rx_data = (void *)(((u16 *)phal_ssi_adaptor->rx_data) + 1);
				} else {
					// 8~4 bits mode
					*((u8 *)(phal_ssi_adaptor->rx_data)) = HAL_READ8((u32)&spi_dev->SSI_DR, 0);
					phal_ssi_adaptor->rx_data = (void *)(((u8 *)phal_ssi_adaptor->rx_data) + 1);
				}
			} else {
				// for master mode, doing tx also will got rx data, so drop the dummy data
				spi_dev->SSI_DR;
			}

			if (phal_ssi_adaptor->rx_length > 0) {
				phal_ssi_adaptor->rx_length--;
			}

			if (phal_ssi_adaptor->rx_length == 0) {
				break;
			}
		}

		if (((phal_ssi_adaptor->interrupt_mask & SSI_BIT_TXEIM) != 0)
			&& (phal_ssi_adaptor->tx_length > 0)) {
			hal_rtl_ssi_write_interrupt(phal_ssi_adaptor);
		}
	}

	if ((phal_ssi_adaptor->rx_length > 0)
		&& (phal_ssi_adaptor->rx_length < ((spi_dev->SSI_RXFTLR) + 1))) {
		DBG_SSI_INFO("Setting Rx FIFO Threshold Level to 1\n");
		spi_dev->SSI_RXFTLR = 0;
	}

	if (phal_ssi_adaptor->rx_length == 0) {
		DBG_SSI_INFO("hal_ssi_read_interrupt: RX_Done\r\n");
		phal_ssi_adaptor->interrupt_mask &= ~(SSI_BIT_RXFIM | SSI_BIT_RXOIM | SSI_BIT_RXUIM);
		spi_dev->SSI_IMR = phal_ssi_adaptor->interrupt_mask;

		if (phal_ssi_adaptor->rx_done_callback != NULL) {
			phal_ssi_adaptor->rx_done_callback(phal_ssi_adaptor->rx_done_cb_para);
		}
	}
}

/** \brief Description of hal_rtl_ssi_read_interrupt
 *
 *    hal_rtl_ssi_read_interrupt is used to handle a interrupt when the receive FIFO threshold has reached in receive mode.
 *    As soon as CPU enters this handler function, it identifies the number of data frames in the receive FIFO.
 *    These data then are moved from the receive FIFO to memory.
 *    A SPI master still pushes new data into the receive FIFO at the same time, but these new data won't be handled in this interrupt.
 *    After all data have been received and handled properly by this interrupt handler, the interrupt handler jumps to a callback function assigned by users.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *
 *   \return void.
 */
void hal_rtl_ssi_read_unfix_size_interrupt(phal_ssi_adaptor_t phal_ssi_adaptor)
{
	DBG_SSI_INFO("hal_rtl_ssi_read_unfix_size_interrupt()\n");
	SSI_TypeDef *spi_dev = (SSI_TypeDef *) phal_ssi_adaptor->spi_dev;
	volatile u32 receive_level;
	volatile u32 readable;

	readable = spi_dev->SSI_SR & SSI_BIT_RFNE;

	if (readable) {
		receive_level = spi_dev->SSI_RXFLR;

		while (receive_level--) {
			if (phal_ssi_adaptor->rx_data != NULL) {
				if (phal_ssi_adaptor->data_frame_size == DfsSixteenBits) {
					// 16~9 bits mode
					*((u16 *)(phal_ssi_adaptor->rx_data)) = HAL_READ16((u32)&spi_dev->SSI_DR, 0);
					phal_ssi_adaptor->rx_data = (void *)(((u16 *)phal_ssi_adaptor->rx_data) + 1);
				} else {
					// 8~4 bits mode
					*((u8 *)(phal_ssi_adaptor->rx_data)) = HAL_READ8((u32)&spi_dev->SSI_DR, 0);
					phal_ssi_adaptor->rx_data = (void *)(((u8 *)phal_ssi_adaptor->rx_data) + 1);
				}
			} else {
				// for master mode, doing tx also will got rx data, so drop the dummy data
				spi_dev->SSI_DR;
			}

			if (phal_ssi_adaptor->rx_length > 0) {
				phal_ssi_adaptor->rx_length--;
			}

			if (phal_ssi_adaptor->rx_length == 0) {
				break;
			}
		}

		if (((phal_ssi_adaptor->interrupt_mask & SSI_BIT_TXEIM) != 0)
			&& (phal_ssi_adaptor->tx_length > 0)) {
			hal_rtl_ssi_write_interrupt(phal_ssi_adaptor);
		}
	}

	if ((phal_ssi_adaptor->rx_length > 0)
		&& (phal_ssi_adaptor->rx_length < ((spi_dev->SSI_RXFTLR) + 1))) {
		DBG_SSI_INFO("Setting Rx FIFO Threshold Level to 1\n");
		spi_dev->SSI_RXFTLR = 0;
	}

	if (phal_ssi_adaptor->rx_length == 0) {
		DBG_SSI_INFO("hal_ssi_read_interrupt: RX_Done\r\n");
		phal_ssi_adaptor->interrupt_mask &= ~(SSI_BIT_RXFIM | SSI_BIT_RXOIM | SSI_BIT_RXUIM);
		spi_dev->SSI_IMR = phal_ssi_adaptor->interrupt_mask;

		if (phal_ssi_adaptor->rx_done_callback != NULL) {
			phal_ssi_adaptor->rx_done_callback(phal_ssi_adaptor->rx_done_cb_para);
		}
	}

	if ((spi_dev->SSI_SR & SSI_BIT_BUSY) == 0) {
		if ((spi_dev->SSI_SR & SSI_BIT_RFNE) == 0) {
			phal_ssi_adaptor->interrupt_mask &= ~(SSI_BIT_RXFIM | SSI_BIT_RXOIM | SSI_BIT_RXUIM);
			spi_dev->SSI_IMR = phal_ssi_adaptor->interrupt_mask;
			phal_ssi_adaptor->unfix_read_en &= ~0x01;
			hal_rtl_ssi_set_rxfifo_threshold(phal_ssi_adaptor, 7);

			if (phal_ssi_adaptor->rx_done_callback != NULL) {
				phal_ssi_adaptor->rx_done_callback(phal_ssi_adaptor->rx_done_cb_para);
			}
		}
	}
}


/** \brief Description of hal_rtl_ssi_write_interrupt
 *
 *    hal_rtl_ssi_write_interrupt is used to handle a interrupt when the transmit FIFO threshold has reached in transmit mode.
 *    CPU will move data to the transmit FIFO, then the SPI device pops data out of its FIFO.
 *    After all data have been transmitted and handled properly by this interrupt handler, the interrupt handler jumps to a callback function assigned by users.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *
 *   \return hal_status_t.
 */
void hal_rtl_ssi_write_interrupt(phal_ssi_adaptor_t phal_ssi_adaptor)
{
	DBG_SSI_INFO("hal_rtl_ssi_write_interrupt()\n");
	SSI_TypeDef *spi_dev = (SSI_TypeDef *) phal_ssi_adaptor->spi_dev;
	volatile u32 writeable;
	volatile u32 tx_write_max;
	u32 i;

	writeable = spi_dev->SSI_SR & SSI_BIT_TFNF;

	if (phal_ssi_adaptor->tx_length == 0) {
		phal_ssi_adaptor->interrupt_mask &= ~(SSI_BIT_TXEIM);
		spi_dev->SSI_IMR = phal_ssi_adaptor->interrupt_mask;

		for (i = 0; i < 1000000; i++) {
			if (!(spi_dev->SSI_SR & SSI_BIT_BUSY)) {
				break;  // break the for loop
			}
		}

		// if it's not a dummy tx for master read spi, then call the tx_done callback
		if (phal_ssi_adaptor->tx_data != NULL) {
			if (phal_ssi_adaptor->tx_idle_callback != NULL) {
				phal_ssi_adaptor->tx_idle_callback(phal_ssi_adaptor->tx_idle_cb_para);
			}
		}

		return;
	}

	if (writeable) {
		tx_write_max = SSI_TX_FIFO_DEPTH - spi_dev->SSI_TXFLR;
		/* disable tx fifo empty irq */
		phal_ssi_adaptor->interrupt_mask &= ~ SSI_BIT_TXEIM;
		spi_dev->SSI_IMR = phal_ssi_adaptor->interrupt_mask;
		//clear rx fifo first, to prevent rx overflow
		if ((phal_ssi_adaptor->rx_length > 0) && (phal_ssi_adaptor->tx_data != NULL)) {
			hal_rtl_ssi_read_interrupt(phal_ssi_adaptor);
		}

		while (tx_write_max--) {
			if (phal_ssi_adaptor->data_frame_size == DfsSixteenBits) {
				// 16~9 bits mode
				if (phal_ssi_adaptor->tx_data != NULL) {
					HAL_WRITE16((u32)&spi_dev->SSI_DR, 0x0, *((u16 *)(phal_ssi_adaptor->tx_data)));
					phal_ssi_adaptor->tx_data = (void *)(((u16 *)phal_ssi_adaptor->tx_data) + 1);
				} else {
					// for master mode: push a dummy to tx fifo for read
					if (phal_ssi_adaptor->role == SsiMaster) {
						HAL_WRITE16((u32)&spi_dev->SSI_DR, 0x0, (u16)SSI_DUMMY_DATA);
					}
				}
			} else {
				// 8~4 bits mode
				if (phal_ssi_adaptor->tx_data != NULL) {
					HAL_WRITE8((u32)&spi_dev->SSI_DR, 0x0, *((u8 *)(phal_ssi_adaptor->tx_data)));
					phal_ssi_adaptor->tx_data = (void *)(((u8 *)phal_ssi_adaptor->tx_data) + 1);
				} else {
					// for master mode: push a dummy to tx fifo for read
					if (phal_ssi_adaptor->role == SsiMaster) {
						HAL_WRITE8((u32)&spi_dev->SSI_DR, 0x0, (u8)SSI_DUMMY_DATA);
					}
				}
			}

			phal_ssi_adaptor->tx_length--;

			if (phal_ssi_adaptor->tx_length == 0) {
				break;
			}
		}

		/* enable tx fifo empty irq */
		phal_ssi_adaptor->interrupt_mask |= SSI_BIT_TXEIM;
		spi_dev->SSI_IMR = phal_ssi_adaptor->interrupt_mask;
	}

	if (phal_ssi_adaptor->tx_length == 0) {
		DBG_SSI_INFO("hal_rtl_ssi_write_interrupt: TX_Done\r\n");
		spi_dev->SSI_TXFTLR = 0;    // trigger tx interrupt when tx fifo is totally empty
		phal_ssi_adaptor->interrupt_mask &= ~(SSI_BIT_TXOIM);
		spi_dev->SSI_IMR = phal_ssi_adaptor->interrupt_mask;
		// if it's not a dummy tx for master read spi, then call the tx_done callback
		if (phal_ssi_adaptor->tx_data != NULL) {
			if (phal_ssi_adaptor->tx_done_callback != NULL) {
				phal_ssi_adaptor->tx_done_callback(phal_ssi_adaptor->tx_done_cb_para);
			}
		}
	}
}

/** \brief Description of SPI_IRQHandler
 *
 *    SPI_IRQHandler is used to handle the interrupt signal before identifying which SPI devices trigger this interrupt.
 *    It will clear the pending interrupt on CPU side, then search and jump to the target SPI which triggers the interrupt.
 *
 *   \param void.
 *
 *   \return void.
 */
void SPI0_IRQHandler_ram(void)
{
	phal_ssi_adaptor_t phal_ssi_adaptor;

	hal_irq_clear_pending(SPI0_IRQn);
	phal_ssi_adaptor = hal_ssi_group.phal_ssi_adaptor[0];
	hal_rtl_ssi_irq_handle(phal_ssi_adaptor);
}

/** \brief Description of SPI_IRQHandler
 *
 *    SPI_IRQHandler is used to handle the interrupt signal before identifying which SPI devices trigger this interrupt.
 *    It will clear the pending interrupt on CPU side, then search and jump to the target SPI which triggers the interrupt.
 *
 *   \param void.
 *
 *   \return void.
 */
void SPI1_IRQHandler_ram(void)
{
	phal_ssi_adaptor_t phal_ssi_adaptor;

	hal_irq_clear_pending(SPI1_IRQn);
	phal_ssi_adaptor = hal_ssi_group.phal_ssi_adaptor[1];
	hal_rtl_ssi_irq_handle(phal_ssi_adaptor);
}

/** \brief Description of SPI_IRQHandler
 *
 *    SPI_IRQHandler is used to handle the interrupt signal before identifying which SPI devices trigger this interrupt.
 *    It will clear the pending interrupt on CPU side, then search and jump to the target SPI which triggers the interrupt.
 *
 *   \param void.
 *
 *   \return void.
 */
void SPI2_IRQHandler_ram(void)
{
	phal_ssi_adaptor_t phal_ssi_adaptor;

	hal_irq_clear_pending(HSPI0_IRQn);
	phal_ssi_adaptor = hal_ssi_group.phal_ssi_adaptor[2];
	hal_rtl_ssi_irq_handle(phal_ssi_adaptor);
}

/** \brief Description of SPI_IRQHandler
 *
 *    SPI_IRQHandler is used to handle the interrupt signal before identifying which SPI devices trigger this interrupt.
 *    It will clear the pending interrupt on CPU side, then search and jump to the target SPI which triggers the interrupt.
 *
 *   \param void.
 *
 *   \return void.
 */
void SPI3_IRQHandler_ram(void)
{
	phal_ssi_adaptor_t phal_ssi_adaptor;

	hal_irq_clear_pending(HSPI1_IRQn);
	phal_ssi_adaptor = hal_ssi_group.phal_ssi_adaptor[3];
	hal_rtl_ssi_irq_handle(phal_ssi_adaptor);
}

/** \brief Description of hal_rtl_ssi_irq_handle
 *
 *    hal_rtl_ssi_irq_handle is used to handle interrupt from the SPI side after identifying the SPI device triggering the interrupt.
 *    Each type of interrupt will be handled according to the circuit design.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *
 *   \return void.
 */
void hal_rtl_ssi_irq_handle(phal_ssi_adaptor_t phal_ssi_adaptor)
{
	SSI_TypeDef *spi_dev = (SSI_TypeDef *) phal_ssi_adaptor->spi_dev;
	u32 isr;
	u8  index = phal_ssi_adaptor->index;
	u8  role = phal_ssi_adaptor->role;

	isr = spi_dev->SSI_ISR;

	if (isr & SSI_BIT_TXOIS) {
		DBG_SSI_ERR("[INT][SSI%d] Transmit FIFO Overflow Interrupt\n", index);
		spi_dev->SSI_TXOICR;
	}

	if (isr & SSI_BIT_RXUIS) {
		DBG_SSI_INFO("[INT][SSI%d] Receive FIFO Underflow Interrupt\n", index);
		spi_dev->SSI_RXUICR;
	}

	if (isr & SSI_BIT_RXOIS) {
		DBG_SSI_ERR("[INT][SSI%d] Receive FIFO Overflow Interrupt\n", index);
		spi_dev->SSI_RXOICR;
	}

	if (isr & SSI_BIT_MSTIS) {
		if (role == SsiMaster) {
			DBG_SSI_ERR("[INT][SSI%d] Multi-Master Contention Interrupt\n", index);
		} else {
			DBG_SSI_ERR("[INT][SSI%d] Frame Alignment Error Interrupt\n", index);
		}

		spi_dev->SSI_MSTICR;
	}

	if (isr & SSI_BIT_TXUIS) {
		DBG_SSI_ERR("[INT][SSI%d] Transmit FIFO Under Flow Interrupt\n", index);
		spi_dev->SSI_TXUICR;
	}

	/*Need to handle this interrupt*/
	if (isr & SSI_BIT_SSRIS) {
		DBG_SSI_ERR("[INT][SSI%d] SS_N Rising Edge Detect Interrupt\n", index);
		spi_dev->SSI_SSRICR;
	}

	if (isr & SSI_BIT_TXOIS) {
		DBG_SSI_ERR("[INT][SSI%d] Transmit FIFO Overflow Interrupt\n", index);
		spi_dev->SSI_TXOICR;
	}

	if (isr & SSI_BIT_RXFIS) {
		DBG_SSI_INFO("[INT][SSI%d] Receive FIFO Full Interrupt\n", index);

		if (phal_ssi_adaptor->unfix_read_en & 0x01) {
			hal_rtl_ssi_read_unfix_size_interrupt(phal_ssi_adaptor);
		} else {
			hal_rtl_ssi_read_interrupt(phal_ssi_adaptor);
		}
	}

	if (isr & SSI_BIT_TXEIS ||
		(((phal_ssi_adaptor->interrupt_mask & SSI_BIT_TXEIM) != 0) && (phal_ssi_adaptor->tx_length > 0))) {
		/* tx fifo is empty, need to transfer data */
		DBG_SSI_INFO("[INT][SSI%d] Transmit FIFO Empty Interrupt\n", index);
		hal_rtl_ssi_write_interrupt(phal_ssi_adaptor);
	}
}

/** \brief Description of hal_rtl_ssi_interrupt_enable
 *
 *    hal_rtl_ssi_interrupt_enable is used to enable interrupt for all SPI devices.
 *    Note that all SPI devices share the same interrupt signal.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_rtl_ssi_interrupt_enable(phal_ssi_adaptor_t phal_ssi_adaptor)
{
	irq_config_t *pirq_cfg;
	u8 ssi_idx;

	pirq_cfg = &(phal_ssi_adaptor->irq_handle);
	ssi_idx = phal_ssi_adaptor->index;

	DBG_SSI_INFO("hal_rtl_ssi_interrupt_enable()\n");
	DBG_SSI_INFO("SSI%d IrqHandle instance ptr: %X\n", ssi_idx, pirq_cfg);
	DBG_SSI_INFO("SSI%d IrqHandle.IrqNum    : %d\n", ssi_idx, pirq_cfg->irq_num);
	DBG_SSI_INFO("SSI%d IrqHandle.IrqFun    : %x\n", ssi_idx, pirq_cfg->irq_fun);
	DBG_SSI_INFO("SSI%d IrqHandle.Priority  : 0x%x\n", ssi_idx, pirq_cfg->priority);
	DBG_SSI_INFO("hal_ssi_adaptor->irq_en      : 0x%x\n", phal_ssi_adaptor->irq_en);

	// IRQ vector may has been registered, disable and re-register it
	hal_irq_disable(pirq_cfg->irq_num);
	__ISB();

	hal_irq_set_vector(pirq_cfg->irq_num, (uint32_t)(pirq_cfg->irq_fun));
	hal_irq_enable(pirq_cfg->irq_num);

	return HAL_OK;
}

/** \brief Description of hal_rtl_ssi_interrupt_disable
 *
 *    hal_rtl_ssi_interrupt_disable is used to disable interrupt for all SPI devices.
 *    Note that all SPI devices share the same interrupt signal. Once it is disabled, interrupts from every SPI devices will not be handled.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_rtl_ssi_interrupt_disable(phal_ssi_adaptor_t phal_ssi_adaptor)
{
	irq_config_t *pirq_cfg;
	u8 ssi_idx;

	pirq_cfg = &(phal_ssi_adaptor->irq_handle);
	ssi_idx = phal_ssi_adaptor->index;

	DBG_SSI_INFO("hal_rtl_ssi_interrupt_disable()\n");
	DBG_SSI_INFO("SSI%d IrqHandle instance ptr: %X\n", ssi_idx, pirq_cfg);
	DBG_SSI_INFO("SSI%d IrqHandle.IrqNum  : %d\n", ssi_idx, pirq_cfg->irq_num);
	DBG_SSI_INFO("SSI%d IrqHandle.IrqFun    : %x\n", ssi_idx, pirq_cfg->irq_fun);
	DBG_SSI_INFO("SSI%d IrqHandle.Priority  : 0x%x\n", ssi_idx, pirq_cfg->priority);
	DBG_SSI_INFO("hal_ssi_adaptor->irq_en      : 0x%x\n", phal_ssi_adaptor->irq_en);

	hal_irq_unreg(pirq_cfg->irq_num);
	phal_ssi_adaptor->irq_en = 0;

	return HAL_OK;
}

/** \brief Description of hal_rtl_ssi_interrupt_init_read
 *
 *    hal_rtl_ssi_interrupt_init_read is used to configure relevant interrupt settings for receive mode.
 *    After the SPI device receives data from a SPI master, it triggers an interrupt once the receive FIFO threshold is reached.
 *    CPU will move data from the receive FIFO to the memory address(*rx_data) in the IRQ handler function.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *   \param void *rx_data:      The destination address of data. Data will be moved from the the SPI FIFO to the destination address by CPU.
 *   \param u32 length:      Total transfer length.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_rtl_ssi_interrupt_init_read(phal_ssi_adaptor_t phal_ssi_adaptor, void *rx_data, u32 length)
{
	DBG_SSI_INFO("hal_rtl_ssi_interrupt_init_read()\n");

	SSI_TypeDef *spi_dev = (SSI_TypeDef *) phal_ssi_adaptor->spi_dev;
	u8  index = phal_ssi_adaptor->index;
	u32 rx_fifo_threshold_level = phal_ssi_adaptor->rx_threshold_level;
	irq_config_t *pirq_cfg = &(phal_ssi_adaptor->irq_handle);

	hal_rtl_ssi_set_rxfifo_threshold(phal_ssi_adaptor, rx_fifo_threshold_level);
	DBG_SSI_INFO("hal_rtl_ssi_interrupt_init_read: index = %d, rx_data = 0x%x, len = 0x%x\r\n", index, rx_data, length);

	if (length == 0) {
		DBG_SSI_ERR("SSI%d rx_data addr: 0x%X, Length: %d\n", index, rx_data, length);
		return HAL_ERR_PARA;
	}

	if (phal_ssi_adaptor->data_frame_size == DfsSixteenBits) {
		// 16~9 bits mode
		phal_ssi_adaptor->rx_length = length >> 1; // 2 bytes(16 bit) every transfer
	} else {
		// 8~4 bits mode
		phal_ssi_adaptor->rx_length = length; // 1 byte(8 bit) every transfer
	}

	if (phal_ssi_adaptor->rx_length <= rx_fifo_threshold_level) {
		spi_dev->SSI_RXFTLR = 0;
		DBG_SSI_INFO("Setting Rx FIFO Threshold Level to 1\n");
	}

	phal_ssi_adaptor->rx_data = rx_data;

	DBG_SSI_INFO("SSI%d rx_data addr: 0x%X, Length: %d\n", index,
				 phal_ssi_adaptor->rx_data, phal_ssi_adaptor->rx_length);

	phal_ssi_adaptor->interrupt_mask |= SSI_BIT_RXFIM | SSI_BIT_RXOIM | SSI_BIT_RXUIM;
	spi_dev->SSI_IMR = phal_ssi_adaptor->interrupt_mask;

	if (phal_ssi_adaptor->irq_en == 0) {
		hal_rtl_ssi_interrupt_enable(phal_ssi_adaptor);
		hal_irq_set_priority(pirq_cfg->irq_num, pirq_cfg->priority);
		phal_ssi_adaptor->irq_en = 1;
	}

	return HAL_OK;
}


/** \brief Description of hal_rtl_ssi_interrupt_init_write
 *
 *    hal_rtl_ssi_interrupt_init_write is used to configure relevant interrupt settings for transmit mode.
 *    When the SPI device transmits data out of its transmit FIFO,
 *    it will triggers an interrupt to ask for more data as long as an transmit FIFO threshold is reached.
 *    CPU then moves data from the memory address(tx_data) to the transmit FIFO in the IRQ handler function.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *   \param void *tx_data:      The source address of data. Data will be moved from the source address to the SPI FIFO.
 *   \param u32 length:      Total transfer length.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_rtl_ssi_interrupt_init_write(phal_ssi_adaptor_t phal_ssi_adaptor, void *tx_data, u32 length)
{
	DBG_SSI_INFO("hal_rtl_ssi_interrupt_init_write()\n");

	SSI_TypeDef *spi_dev = (SSI_TypeDef *) phal_ssi_adaptor->spi_dev;
	u8  index = phal_ssi_adaptor->index;
	irq_config_t *pirq_cfg = &(phal_ssi_adaptor->irq_handle);

	hal_rtl_ssi_set_txfifo_threshold(phal_ssi_adaptor, phal_ssi_adaptor->tx_threshold_level);
	DBG_SSI_INFO("hal_rtl_ssi_interrupt_init_write: idx=%d, tx_data=0x%x, len=0x%x\r\n", index, tx_data, length);

	if (length == 0) {
		DBG_SSI_ERR("SSI%d tx_data addr: 0x%X, Length: %d\n", index, tx_data, length);
		return HAL_ERR_PARA;
	}

	if (phal_ssi_adaptor->data_frame_size == DfsSixteenBits) {
		// 16~9 bits mode
		phal_ssi_adaptor->tx_length = length >> 1; // 2 bytes(16 bit) every transfer
	} else {
		// 8~4 bits mode
		phal_ssi_adaptor->tx_length = length; // 1 byte(8 bit) every transfer
	}

	spi_dev->SSI_TXFTLR = phal_ssi_adaptor->tx_threshold_level;
	phal_ssi_adaptor->tx_data = (void *)tx_data;
	phal_ssi_adaptor->interrupt_mask |= SSI_BIT_TXOIM | SSI_BIT_TXEIM;
	spi_dev->SSI_IMR = phal_ssi_adaptor->interrupt_mask;

	DBG_SSI_INFO("SSI%d tx_data addr: 0x%X, Length: %d\n", index,
				 phal_ssi_adaptor->tx_data, phal_ssi_adaptor->tx_length);

	if (phal_ssi_adaptor->irq_en == 0) {
		hal_rtl_ssi_interrupt_enable(phal_ssi_adaptor);
		hal_irq_set_priority(pirq_cfg->irq_num, pirq_cfg->priority);
		phal_ssi_adaptor->irq_en = 1;
	}

	return HAL_OK;
}

/**

        \addtogroup hs_hal_spic_ram_func Flash Controller HAL RAM APIs
        \ingroup hs_hal_spic
        \brief The flash controller HAL APIs. Functions become an interface between API functions and ROM codes.
        @{
*/

/** \brief Description of hal_rtl_ssi_set_sclk
 *
 *    hal_rtl_ssi_set_sclk is used to set operting frequency of the SPI device.
 *    The operating frequency is determined by the SPI master device, but the SPI slave device still has a constraint for its speed.
 *    We list the maximum speed supported by different SPI devices below.
 *    SPI 0 Master : 31.25MHz
 *    SPI 1 Master : 31.25MHz
 *    SPI 2 Slave : 62.5MHz
 *    SPI 3 Slave : 62.5MHz
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *   \param u32 clk_rate:      The target speed of the SPI device. For the slave device, this parameter can be used to check if it is valid.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_rtl_ssi_set_sclk(phal_ssi_adaptor_t phal_ssi_adaptor, u32 clk_rate)
{
	SSI_TypeDef *spi_dev = (SSI_TypeDef *) phal_ssi_adaptor->spi_dev;
	u32 max_ssi_clk;
	u32 bus_clk;
	u16 clock_divider;
	u8  index = phal_ssi_adaptor->index;

	if (index == 0 || index == 1) {
		bus_clk = 62500000;
	} else {
		bus_clk = 125000000;
	}

	max_ssi_clk = bus_clk >> 1;
	clock_divider = 2;

	if (phal_ssi_adaptor->role == SsiMaster) {
		if (clk_rate > max_ssi_clk) {
			DBG_SSI_WARN("hal_rtl_ssi_set_sclk: freq %d is too high, set to available highest freq=%d\r\n", clk_rate, max_ssi_clk);
		} else {
			clock_divider = (bus_clk / clk_rate);

			if (clock_divider & 1) {
				clock_divider ++;
			} else {
				if (bus_clk % clk_rate) {
					clock_divider += 2;
				}
			}
		}

		phal_ssi_adaptor->clock_divider = clock_divider;

		spi_dev->SSI_SSIENR = DISABLE;
		spi_dev->SSI_BAUDR = (phal_ssi_adaptor->clock_divider & 0xFFFE);
		spi_dev->SSI_SSIENR = ENABLE;

		DBG_SSI_INFO("hal_rtl_ssi_set_sclk: baudr = %d, effective freq = %d\n", clock_divider, bus_clk / clock_divider);
	} else {
		if (clk_rate > (bus_clk / 2)) {
			DBG_SSI_ERR("hal_rtl_ssi_set_sclk: freq %d is too high, available highest freq=%d\r\n", clk_rate, (bus_clk / 2));
			return HAL_ERR_PARA;
		}
	}

	return HAL_OK;
}

/** \brief Description of hal_rtl_ssi_set_format
 *
 *    hal_rtl_ssi_set_format is used to set SPI mode, transfer mode, frame format and frame size.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_rtl_ssi_set_format(phal_ssi_adaptor_t phal_ssi_adaptor)
{
	DBG_SSI_INFO("hal_rtl_ssi_set_format()\n");

	SSI_TypeDef *spi_dev = (SSI_TypeDef *) phal_ssi_adaptor->spi_dev;
	u32 ctrlr0 = 0;
	spi_frame_format_t data_frame_format = phal_ssi_adaptor->data_frame_format;
	u8  index = phal_ssi_adaptor->index;

	if (index > 3) {
		DBG_SSI_ERR("SSI%d is an Invalid Index\r\n", index);
		return HAL_ERR_PARA;
	}

	spi_dev->SSI_SSIENR = DISABLE;
	/// REG_DW_SSI_CTRLR0
	ctrlr0 |= (phal_ssi_adaptor->data_frame_size << SSI_SHIFT_DFS)
			  | (phal_ssi_adaptor->data_frame_format << SSI_SHIFT_FRF)
			  | (phal_ssi_adaptor->sclk_phase << SSI_SHIFT_SCPH)
			  | (phal_ssi_adaptor->sclk_polarity << SSI_SHIFT_SCPOL)
			  | (phal_ssi_adaptor->transfer_mode << SSI_SHIFT_TMOD);

	DBG_SSI_INFO("[1] Set SSI%d REG_DW_SSI_CTRLR0 Value: %X\n", index, ctrlr0);
	spi_dev->SSI_CTRLR0 = ctrlr0;
	DBG_SSI_INFO("[2] SSI%d REG_DW_SSI_CTRLR0(0x00) = %X\n", index, spi_dev->SSI_CTRLR0);

	///Microwire Register Configuration
	if (FrfNsMicrowire == data_frame_format) {
		hal_rtl_ssi_set_microwire(phal_ssi_adaptor);
	}

	spi_dev->SSI_SSIENR = ENABLE;
	return HAL_OK;
}

/** \brief Description of hal_rtl_ssi_set_microwire
 *
 *    hal_rtl_ssi_set_microwire is used to set parameters for Microwire protocol.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_rtl_ssi_set_microwire(phal_ssi_adaptor_t phal_ssi_adaptor)
{
	SSI_TypeDef *spi_dev = (SSI_TypeDef *) phal_ssi_adaptor->spi_dev;
	u8 index = phal_ssi_adaptor->index;
	u8 role = phal_ssi_adaptor->role;
	u32 mwcr = 0;

	spi_dev->SSI_SSIENR = DISABLE;
	spi_dev->SSI_CTRLR0 &= ~SSI_MASK_CFS;
	spi_dev->SSI_CTRLR0 |= (phal_ssi_adaptor->control_frame_size << SSI_SHIFT_CFS);

	if ((index == RTK_SLAVE0_INDEX) || (index == RTK_SLAVE1_INDEX)) {
		DBG_SSI_ERR("SPI slave does not support Microwire mode!\r\n");
		return HAL_ERR_PARA;
	}

	if (role == SsiMaster) {
		if ((phal_ssi_adaptor->microwire_transfer_mode) == MwTmodSequential) {
			spi_dev->SSI_CTRLR1 = phal_ssi_adaptor->data_frame_number;
		}
	}

	mwcr |= (phal_ssi_adaptor->microwire_transfer_mode << SSI_SHIFT_MWMOD)
			| (phal_ssi_adaptor->microwire_direction << SSI_SHIFT_MDD)
			| (phal_ssi_adaptor->microwire_handshaking << SSI_SHIFT_MHS);

	DBG_SSI_INFO("[1] Set SSI%d REG_DW_SSI_MWCR Value: %X\n", index, mwcr);
	spi_dev->SSI_MWCR = mwcr;
	DBG_SSI_INFO("[2] SSI%d REG_DW_SSI_MWCR(0x0C) = %X\n", index, spi_dev->SSI_MWCR);

	spi_dev->SSI_SSIENR = ENABLE;

	return HAL_OK;

}

/** \brief Description of hal_rtl_ssi_set_sclk_polarity
 *
 *    hal_rtl_ssi_set_sclk_polarity is used to set clock polarity of SPI mode.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *   \param u8 sclk_polarity:      The clock polarity.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_rtl_ssi_set_sclk_polarity(phal_ssi_adaptor_t phal_ssi_adaptor, u8 sclk_polarity)
{
	DBG_SSI_INFO("hal_rtl_ssi_set_sclk_polarity()\n");

	SSI_TypeDef *spi_dev = (SSI_TypeDef *) phal_ssi_adaptor->spi_dev;

	phal_ssi_adaptor->sclk_polarity = sclk_polarity;

	DBG_SSI_INFO("[1] Set SSI%d SclkPolarity Value: %X\n", phal_ssi_adaptor->index, phal_ssi_adaptor->sclk_polarity);

	spi_dev->SSI_SSIENR = DISABLE;
	spi_dev->SSI_CTRLR0 &= ~SSI_BIT_SCPOL;
	spi_dev->SSI_CTRLR0 |= sclk_polarity << SSI_SHIFT_SCPOL;
	spi_dev->SSI_SSIENR = ENABLE;

	DBG_SSI_INFO("[2] SSI%d REG_DW_SSI_CTRLR0 = %X\n", phal_ssi_adaptor->index, spi_dev->SSI_CTRLR0);

	return HAL_OK;
}

/** \brief Description of hal_rtl_ssi_set_sclk_phase
 *
 *    hal_rtl_ssi_set_sclk_phase is used to set clock phase of SPI mode.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *   \param u8 sclk_phase:      The clock phase.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_rtl_ssi_set_sclk_phase(phal_ssi_adaptor_t phal_ssi_adaptor, u8 sclk_phase)
{
	DBG_SSI_INFO("hal_rtl_ssi_set_sclk_phase()\n");

	SSI_TypeDef *spi_dev = (SSI_TypeDef *) phal_ssi_adaptor->spi_dev;

	phal_ssi_adaptor->sclk_phase = sclk_phase;

	DBG_SSI_INFO("[1] Set SSI%d SclkPhase Value: %X\n", phal_ssi_adaptor->index, phal_ssi_adaptor->sclk_phase);

	spi_dev->SSI_SSIENR = DISABLE;
	spi_dev->SSI_CTRLR0 &= ~SSI_BIT_SCPH;
	spi_dev->SSI_CTRLR0 |= sclk_phase << SSI_SHIFT_SCPH;
	spi_dev->SSI_SSIENR = ENABLE;

	DBG_SSI_INFO("[2] SSI%d REG_DW_SSI_CTRLR0 = %X\n", phal_ssi_adaptor->index, spi_dev->SSI_CTRLR0);

	return HAL_OK;
}

/** \brief Description of hal_rtl_ssi_set_data_frame_number
 *
 *    hal_rtl_ssi_set_data_frame_number is used to set the number of data frame in receive only mode so that the SPI master knows when to deassert CS line.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *   \param u32 length:      Data length expected to receive.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_rtl_ssi_set_data_frame_number(phal_ssi_adaptor_t phal_ssi_adaptor, u32 length)
{
	DBG_SSI_INFO("hal_rtl_ssi_set_data_frame_number()\n");

	u8 role = phal_ssi_adaptor->role;
	spi_ctrlr0_tmod_t transfer_mode = phal_ssi_adaptor->transfer_mode;
	SSI_TypeDef *spi_dev = (SSI_TypeDef *) phal_ssi_adaptor->spi_dev;

	if (role == SsiMaster) {
		///Set Number of Data Frame
		if ((transfer_mode == TmodRo)
			|| (transfer_mode == TmodEEPROMR)
		   ) {
			spi_dev->SSI_SSIENR = DISABLE;
			spi_dev->SSI_CTRLR1 = phal_ssi_adaptor->data_frame_number;
			spi_dev->SSI_SSIENR = ENABLE;
		} else {
			DBG_SSI_ERR("Transfer_mode is not Read only mode nor EEPROM Read mode !\n");
			return HAL_ERR_PARA;
		}
	} else {
		DBG_SSI_ERR("Only Master can set this value!\n");
		return HAL_ERR_PARA;
	}

	return HAL_OK;
}


/** \brief Description of hal_rtl_ssi_set_interrupt_mask
 *
 *    hal_rtl_ssi_set_interrupt_mask is used to set the interrupt mask value to the register.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *   \param u8 imr_value:      The interrupt mask setting.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_rtl_ssi_set_interrupt_mask(phal_ssi_adaptor_t phal_ssi_adaptor, u8 imr_value)
{
	DBG_SSI_INFO("hal_rtl_ssi_set_interrupt_mask()\n");

	SSI_TypeDef *spi_dev = (SSI_TypeDef *) phal_ssi_adaptor->spi_dev;

	phal_ssi_adaptor->interrupt_mask = imr_value;

	DBG_SSI_INFO("[1] Set SSI%d IMR value: %X\n", phal_ssi_adaptor->index, imr_value);

	spi_dev->SSI_SSIENR = DISABLE;
	spi_dev->SSI_IMR = imr_value;
	spi_dev->SSI_SSIENR = ENABLE;

	DBG_SSI_INFO("[2] SSI%d REG_DW_SSI_IMR = %X\n", phal_ssi_adaptor->index, spi_dev->SSI_IMR);

	return HAL_OK;
}

/** \brief Description of hal_rtl_ssi_set_device_role
 *
 *    hal_rtl_ssi_set_device_role is used to set the role of SPI device.
 *    SPI 0 & 1 can be either master or slave device.
 *    SPI 2 can only be a master while SPI 3 can only be a slave.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *   \param u32 role:      The role of the SPI device.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_rtl_ssi_set_device_role(phal_ssi_adaptor_t phal_ssi_adaptor, u32 role)
{
	DBG_SSI_INFO("hal_rtl_ssi_set_device_role()\n");
	SSI_TypeDef *spi_dev = (SSI_TypeDef *) phal_ssi_adaptor->spi_dev;
	u32 ser_value;
	u8  index = phal_ssi_adaptor->index;

	phal_ssi_adaptor->role = (spi_role_select_t)role;

	spi_dev->SSI_SSIENR = DISABLE;

	if (SsiSlave == role) {
		spi_dev->SSI_CTRLR0 &= ~SSI_BIT_SLV_OE;
		spi_dev->SSI_CTRLR0 |= SlvTxdEnable << SSI_SHIFT_SLV_OE;
	} else {
		///Set Slave Select Enable Register
		ser_value = (1 << (phal_ssi_adaptor->slave_select_enable));
		DBG_SSI_INFO("[1] Set SSI%d REG_DW_SSI_SER Value: %X\n", index, ser_value);
		spi_dev->SSI_SER = ser_value;
		DBG_SSI_INFO("[2] SSI%d REG_DW_SSI_SER(0x10) = %X\n", index, spi_dev->SSI_SER);
	}

	spi_dev->SSI_SSIENR = ENABLE;

	return HAL_OK;
}

/** \brief Description of hal_rtl_ssi_set_txfifo_threshold
 *
 *    hal_rtl_ssi_set_txfifo_threshold is used to set the threshold value to trigger an interrupt in transmit mode.
 *    When transmit FIFO entries <= the threshold, the transmit FIFO empty interrupt is triggered.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *   \param u32 txftlr_value:      The threshold value of transmit FIFO.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_rtl_ssi_set_txfifo_threshold(phal_ssi_adaptor_t phal_ssi_adaptor, u32 txftlr_value)
{
	DBG_SSI_INFO("hal_rtl_ssi_tx_fifothreshold()\n");

	SSI_TypeDef *spi_dev = (SSI_TypeDef *) phal_ssi_adaptor->spi_dev;

	phal_ssi_adaptor->tx_threshold_level = txftlr_value;

	spi_dev->SSI_SSIENR = DISABLE;
	spi_dev->SSI_TXFTLR = txftlr_value;
	spi_dev->SSI_SSIENR = ENABLE;

	DBG_SSI_INFO("Set SSI%d Tx FIFO Threshold Level: %d\n", phal_ssi_adaptor->index, txftlr_value);

	return HAL_OK;
}

/** \brief Description of hal_rtl_ssi_set_rxfifo_threshold
 *
 *    hal_rtl_ssi_set_rxfifo_threshold is used to set the threshold value to trigger an interrupt in receive mode.
 *    When receive FIFO entries >= the threshold+1, the receive FIFO full interrupt is triggered.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *   \param u32 rxftlr_value:      The threshold value of receive FIFO.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_rtl_ssi_set_rxfifo_threshold(phal_ssi_adaptor_t phal_ssi_adaptor, u32 rxftlr_value)
{
	DBG_SSI_INFO("hal_rtl_ssi_set_rxfifo_threshold()\n");

	SSI_TypeDef *spi_dev = (SSI_TypeDef *) phal_ssi_adaptor->spi_dev;

	phal_ssi_adaptor->rx_threshold_level = rxftlr_value;

	spi_dev->SSI_SSIENR = DISABLE;
	spi_dev->SSI_RXFTLR = rxftlr_value;
	spi_dev->SSI_SSIENR = ENABLE;

	DBG_SSI_INFO("set ssi%d rx fifo threshold level: %d\n", phal_ssi_adaptor->index, rxftlr_value);

	return HAL_OK;
}

/** \brief Description of hal_rtl_ssi_set_slave_enable
 *
 *    hal_rtl_ssi_set_slave_enable is used to select the target SPI slave device.
 *    Only one slave (value = 0) can be selected for SPI master.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *   \param u32 slave_index:      The target SPI slave index, should be 0.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_rtl_ssi_set_slave_enable(phal_ssi_adaptor_t phal_ssi_adaptor, u32 slave_index)
{
	DBG_SSI_INFO("hal_rtl_ssi_set_slave_enable()\n");

	SSI_TypeDef *spi_dev = (SSI_TypeDef *) phal_ssi_adaptor->spi_dev;

	if (hal_rtl_ssi_get_busy(phal_ssi_adaptor)) {
		DBG_SSI_INFO("SSI%d is busy\n", phal_ssi_adaptor->index);
		return HAL_BUSY;
	}

	spi_dev->SSI_SSIENR = DISABLE;
	spi_dev->SSI_SER = (1 << slave_index);
	spi_dev->SSI_SSIENR = ENABLE;

	phal_ssi_adaptor->slave_select_enable = slave_index;

	DBG_SSI_INFO("Set SSI%d SER: %08X\n", phal_ssi_adaptor->index, (1 << slave_index));

	return HAL_OK;
}

/** \brief Description of hal_rtl_ssi_get_rxfifo_level
 *
 *    hal_rtl_ssi_get_rxfifo_level is used to know the number of data frames in receive FIFO.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *
 *   \return u32: the number of data frames in receive FIFO.
 */
u32 hal_rtl_ssi_get_rxfifo_level(phal_ssi_adaptor_t phal_ssi_adaptor)
{
	DBG_SSI_INFO("hal_rtl_ssi_get_rx_fifo_level()\n");

	SSI_TypeDef *spi_dev = (SSI_TypeDef *) phal_ssi_adaptor->spi_dev;
	u32 rxtfl_value;

	rxtfl_value = spi_dev->SSI_RXFLR;

	DBG_SSI_INFO("Get SSI%d Rx FIFO Level: %d\n", phal_ssi_adaptor->index, rxtfl_value);

	return rxtfl_value;
}

/** \brief Description of hal_rtl_ssi_get_txfifo_level
 *
 *    hal_rtl_ssi_get_txfifo_level is used to know the number of data frames in transmit FIFO.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *
 *   \return u32: the number of data frames in transmit FIFO.
 */
u32 hal_rtl_ssi_get_txfifo_level(phal_ssi_adaptor_t phal_ssi_adaptor)
{
	DBG_SSI_INFO("hal_rtl_ssi_get_tx_fifo_level()\n");

	SSI_TypeDef *spi_dev = (SSI_TypeDef *) phal_ssi_adaptor->spi_dev;
	u32 txtfl_value;

	txtfl_value = spi_dev->SSI_TXFLR;

	DBG_SSI_INFO("Get SSI%d Tx FIFO Level: %d\n", phal_ssi_adaptor->index, txtfl_value);

	return txtfl_value;
}

/** \brief Description of hal_rtl_ssi_get_status
 *
 *    hal_rtl_ssi_get_status is used to know the current status of the SPI devices.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *
 *   \return u32: the value of the status register.
 */
u32 hal_rtl_ssi_get_status(phal_ssi_adaptor_t phal_ssi_adaptor)
{
	DBG_SSI_INFO("hal_rtl_ssi_get_status()\n");

	SSI_TypeDef *spi_dev = (SSI_TypeDef *) phal_ssi_adaptor->spi_dev;
	u32 status_value;

	status_value = spi_dev->SSI_SR;

	DBG_SSI_INFO("SSI%d Status: %x\n", phal_ssi_adaptor->index, status_value);

	return status_value;
}

/** \brief Description of hal_rtl_ssi_get_busy
 *
 *    hal_rtl_ssi_get_busy is used to know if the SPI device is under busy state.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *
 *   \return u32: 1: busy, 0: idle or disable
 */
u32 hal_rtl_ssi_get_busy(phal_ssi_adaptor_t phal_ssi_adaptor)
{
	DBG_SSI_INFO("hal_ssi_get_busy()\n");

	SSI_TypeDef *spi_dev = (SSI_TypeDef *) phal_ssi_adaptor->spi_dev;
	u32 busy;

	busy = spi_dev->SSI_SR & SSI_BIT_BUSY;

	DBG_SSI_INFO("SSI%d Busy: %d\n", phal_ssi_adaptor->index, busy);

	return busy;
}

/** \brief Description of hal_rtl_ssi_get_interrupt_mask
 *
 *    hal_rtl_ssi_get_interrupt_mask is used to get current interrupt mask value from the register.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *
 *   \return u32: interrupt mask value.
 */
u32 hal_rtl_ssi_get_interrupt_mask(phal_ssi_adaptor_t phal_ssi_adaptor)
{
	DBG_SSI_INFO("hal_rtl_ssi_get_interrupt_mask()\n");

	SSI_TypeDef *spi_dev = (SSI_TypeDef *) phal_ssi_adaptor->spi_dev;
	u32 imr_value;

	imr_value = spi_dev->SSI_IMR;

	DBG_SSI_INFO("SSI%d IMR value: %X\n", phal_ssi_adaptor->index, imr_value);

	return imr_value;
}

/** \brief Description of hal_rtl_ssi_get_interrupt_status
 *
 *    hal_rtl_ssi_get_interrupt_status is used to know current interrupt status of the SPI device.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *
 *   \return u32: interrupt status.
 */
u32 hal_rtl_ssi_get_interrupt_status(phal_ssi_adaptor_t phal_ssi_adaptor)
{
	DBG_SSI_INFO("hal_rtl_ssi_get_interrupt_status()\n");

	SSI_TypeDef *spi_dev = (SSI_TypeDef *) phal_ssi_adaptor->spi_dev;
	u32 interrupt_status;

	interrupt_status = spi_dev->SSI_ISR;

	DBG_SSI_INFO("SSI%d interrupt status: %x\n", phal_ssi_adaptor->index, interrupt_status);

	return interrupt_status;
}

/** \brief Description of hal_rtl_ssi_get_raw_interrupt_status
 *
 *    hal_rtl_ssi_get_raw_interrupt_status is used to know current raw interrupt status of the SPI device.
 *    The raw interrupt status indicates whether or not the interrupt is masked, the interrupt will be set once the requirment is met.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *
 *   \return u32: raw interrupt status.
 */
u32 hal_rtl_ssi_get_raw_interrupt_status(phal_ssi_adaptor_t phal_ssi_adaptor)
{
	DBG_SSI_INFO("hal_rtl_ssi_get_raw_interrupt_status()\n");

	SSI_TypeDef *spi_dev = (SSI_TypeDef *) phal_ssi_adaptor->spi_dev;
	u32 raw_interrupt_status;

	raw_interrupt_status = spi_dev->SSI_RISR;

	DBG_SSI_INFO("SSI%d raw interrupt status: %x\n", phal_ssi_adaptor->index, raw_interrupt_status);

	return raw_interrupt_status;
}

/** \brief Description of hal_rtl_ssi_get_slave_enable_register
 *
 *    hal_rtl_ssi_get_slave_enable_register is used to know which slave device is selected. Should always be 0.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *
 *   \return u32: 0.
 */
u32 hal_rtl_ssi_get_slave_enable_register(phal_ssi_adaptor_t phal_ssi_adaptor)
{
	DBG_SSI_INFO("hal_rtl_ssi_get_slave_enable_register()\n");

	SSI_TypeDef *spi_dev = (SSI_TypeDef *) phal_ssi_adaptor->spi_dev;
	u32 ser_value;

	ser_value = spi_dev->SSI_SER;

	DBG_SSI_INFO("SSI%d ser value: %x\n", phal_ssi_adaptor->index, ser_value);

	return ser_value;
}


/** \brief Description of hal_rtl_ssi_writable
 *
 *    hal_rtl_ssi_writable is used to know if SPI transmit FIFO can be written.
 *    SPI transmit FIFO cannot be written if it is full.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *
 *   \return u32: 1: transmit FIFO is available, 0: transmit FIFO is full.
 */
u32 hal_rtl_ssi_writable(phal_ssi_adaptor_t phal_ssi_adaptor)
{
	DBG_SSI_INFO("hal_rtl_ssi_writeable()\n");

	SSI_TypeDef *spi_dev = (SSI_TypeDef *) phal_ssi_adaptor->spi_dev;
	u32 writable = spi_dev->SSI_SR & SSI_BIT_TFNF;

	DBG_SSI_INFO("SSI%d Writeable: %d\n", phal_ssi_adaptor->index, writable);

	return writable;
}

/** \brief Description of hal_rtl_ssi_readable
 *
 *    hal_rtl_ssi_readable is used to know if SPI receive FIFO can be read.
 *    SPI receive FIFO cannot be read if it is empty.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *
 *   \return u32: 1: receive FIFO can be read, 0: receive FIFO is empty.
 */
u32 hal_rtl_ssi_readable(phal_ssi_adaptor_t phal_ssi_adaptor)
{
	DBG_SSI_INFO("hal_rtl_ssi_readable()\n");

	SSI_TypeDef *spi_dev = (SSI_TypeDef *) phal_ssi_adaptor->spi_dev;
	u32 readable = spi_dev->SSI_SR & SSI_BIT_RFNE;

	DBG_SSI_INFO("SSI%d Readable: %d\n", phal_ssi_adaptor->index, readable);

	return readable;
}

/** \brief Description of hal_rtl_ssi_write
 *
 *    hal_rtl_ssi_write is used to push one data into transmit FIFO.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *   \param u32 value:      The data.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_rtl_ssi_write(phal_ssi_adaptor_t phal_ssi_adaptor, u32 value)
{
	DBG_SSI_INFO("hal_rtl_ssi_write()\n");

	SSI_TypeDef *spi_dev = (SSI_TypeDef *) phal_ssi_adaptor->spi_dev;

	DBG_SSI_INFO("SSI%d Write: %04X\n", phal_ssi_adaptor->index, value);

	spi_dev->SSI_DR = value;

	return HAL_OK;
}

/** \brief Description of hal_rtl_ssi_read
 *
 *    hal_rtl_ssi_read is used to read one data from receive FIFO.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *
 *   \return u32: data read from receive FIFO.
 */
u32 hal_rtl_ssi_read(phal_ssi_adaptor_t phal_ssi_adaptor)
{
	DBG_SSI_INFO("hal_rtl_ssi_read()\n");

	SSI_TypeDef *spi_dev = (SSI_TypeDef *) phal_ssi_adaptor->spi_dev;

	u32 data = spi_dev->SSI_DR;

	DBG_SSI_INFO("SSI%d Read: %x\n", phal_ssi_adaptor->index, data);

	return data;
}

/** \brief Description of hal_rtl_ssi_stop_recv
 *
 *    hal_rtl_ssi_stop_recv is used to terminate data receiving for the SPI device.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_rtl_ssi_stop_recv(phal_ssi_adaptor_t phal_ssi_adaptor)
{
	SSI_TypeDef *spi_dev = (SSI_TypeDef *) phal_ssi_adaptor->spi_dev;
	phal_gdma_adaptor_t phal_gdma_adaptor;
	u32 received_cnt = 0;
	u8 dma_mode = 0;

	phal_gdma_adaptor = (phal_gdma_adaptor_t) phal_ssi_adaptor->prx_gdma_adaptor;
	phal_ssi_adaptor->interrupt_mask &= ~(SSI_BIT_RXFIM | SSI_BIT_RXOIM | SSI_BIT_RXUIM);
	spi_dev->SSI_IMR = phal_ssi_adaptor->interrupt_mask;

	if (NULL != phal_gdma_adaptor) {
		if (hal_gdma_query_chnl_en(phal_gdma_adaptor)) {
			dma_mode = 1;
			hal_gdma_clean_chnl_isr(phal_gdma_adaptor);
			hal_gdma_abort(phal_gdma_adaptor);
			received_cnt = hal_gdma_query_abort_recv_bytes(phal_gdma_adaptor);
			phal_ssi_adaptor->rx_length -= received_cnt;
			phal_ssi_adaptor->rx_data = (u8 *)(phal_ssi_adaptor->rx_data) + received_cnt;

			/*Sync Memory & Cache after DMA abortion*/
			if (phal_ssi_adaptor->dcache_invalidate_by_addr != NULL) {
				phal_ssi_adaptor->dcache_invalidate_by_addr((uint32_t *) phal_ssi_adaptor->cache_invalidate_addr, (int32_t) received_cnt);
			}
		}
	}

	while (hal_rtl_ssi_get_rxfifo_level(phal_ssi_adaptor) != 0) {
		if ((phal_ssi_adaptor->data_frame_size) == DfsSixteenBits) {
			// 16~9 bits mode
			*((u16 *)(phal_ssi_adaptor->rx_data)) = HAL_READ16((u32)&spi_dev->SSI_DR, 0x0);
			phal_ssi_adaptor->rx_data = (void *)(((u16 *)phal_ssi_adaptor->rx_data) + 1);

			if (dma_mode) {
				phal_ssi_adaptor->rx_length--;
			}
		} else {
			// 8~4 bits mode
			*((u8 *)(phal_ssi_adaptor->rx_data)) = HAL_READ8((u32)&spi_dev->SSI_DR, 0x0);
			phal_ssi_adaptor->rx_data = (void *)(((u8 *)phal_ssi_adaptor->rx_data) + 1);
		}

		phal_ssi_adaptor->rx_length--;
	}

	return HAL_OK;
}

/** \brief Description of hal_rtl_ssi_enter_critical
 *
 *    hal_rtl_ssi_enter_critical is used to enter critical section for SPI device.
 *    It is accomplished by disabling relevant interrupts.
 *    This function can prevent from inadvert interferences from unexpected interrupts when users initialize the transfer.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_rtl_ssi_enter_critical(phal_ssi_adaptor_t phal_ssi_adaptor)
{
	uint32_t irqn;

	irqn = phal_ssi_adaptor->irq_handle.irq_num;
	hal_irq_disable(irqn);
#ifdef CONFIG_GDMA_EN
	phal_gdma_adaptor_t phal_gdma_adaptor;

	phal_gdma_adaptor = (phal_gdma_adaptor_t) phal_ssi_adaptor->ptx_gdma_adaptor;

	if (NULL != phal_gdma_adaptor) {
		if (phal_gdma_adaptor->ch_en != 0) {
			if (phal_gdma_adaptor->gdma_index == 0) {
				irqn = GDMA0_IRQn;
			} else {
				irqn = GDMA1_IRQn;
			}

			hal_irq_disable(irqn);
		}
	}

	phal_gdma_adaptor = (phal_gdma_adaptor_t) phal_ssi_adaptor->prx_gdma_adaptor;

	if (NULL != phal_gdma_adaptor) {
		if (phal_gdma_adaptor->ch_en != 0) {
			if (phal_gdma_adaptor->gdma_index == 0) {
				irqn = GDMA0_IRQn;
			} else {
				irqn = GDMA1_IRQn;
			}

			hal_irq_disable(irqn);
		}
	}
#endif
	return HAL_OK;
}

/** \brief Description of hal_rtl_ssi_exit_critical
 *
 *    hal_rtl_ssi_exit_critical is used to exit critical section when the transfer finished initializing procedure.
 *    The interrupts being disabled before would be re-enabled again.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_rtl_ssi_exit_critical(phal_ssi_adaptor_t phal_ssi_adaptor)
{
	uint32_t irqn;

	irqn = phal_ssi_adaptor->irq_handle.irq_num;
	hal_irq_enable(irqn);
#ifdef CONFIG_GDMA_EN
	phal_gdma_adaptor_t phal_gdma_adaptor;

	phal_gdma_adaptor = (phal_gdma_adaptor_t) phal_ssi_adaptor->ptx_gdma_adaptor;

	if (NULL != phal_gdma_adaptor) {
		if (phal_gdma_adaptor->ch_en != 0) {
			if (phal_gdma_adaptor->gdma_index == 0) {
				irqn = GDMA0_IRQn;
			} else {
				irqn = GDMA1_IRQn;
			}

			hal_irq_enable(irqn);
		}
	}

	phal_gdma_adaptor = (phal_gdma_adaptor_t) phal_ssi_adaptor->prx_gdma_adaptor;

	if (NULL != phal_gdma_adaptor) {
		if (phal_gdma_adaptor->ch_en != 0) {
			if (phal_gdma_adaptor->gdma_index == 0) {
				irqn = GDMA0_IRQn;
			} else {
				irqn = GDMA1_IRQn;
			}

			hal_irq_enable(irqn);
		}
	}
#endif
	return HAL_OK;
}

/** \brief Description of hal_rtl_ssi_tx_gdma_irq_handle
 *
 *    hal_rtl_ssi_tx_gdma_irq_handle is used to handle an interrupt in transmit mode when the tranfer is accomplished by GDMA.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *
 *   \return void.
 */
void hal_rtl_ssi_tx_gdma_irq_handle(phal_ssi_adaptor_t phal_ssi_adaptor)
{
	SSI_TypeDef *spi_dev = (SSI_TypeDef *) phal_ssi_adaptor->spi_dev;
	/*
	    // call user tx complete callback
	    phal_ssi_adaptor->tx_length = 0;
	    spi_dev->txftlr = 0;
	    phal_ssi_adaptor->interrupt_mask |= BIT_IMR_TXEIM;
	    spi_dev->imr = phal_ssi_adaptor->interrupt_mask;
	*/
	phal_ssi_adaptor->dma_control &= ~SsiTxDmaEnable;
	spi_dev->SSI_DMACR = phal_ssi_adaptor->dma_control;

	if (NULL != phal_ssi_adaptor->tx_done_callback) {
		phal_ssi_adaptor->tx_done_callback(phal_ssi_adaptor->tx_done_cb_para);
	}
}

/** \brief Description of hal_rtl_ssi_rx_gdma_irq_handle
 *
 *    hal_rtl_ssi_rx_gdma_irq_handle is used to handle an interrupt in receive mode when the tranfer is accomplished by GDMA.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *
 *   \return void.
 */
void hal_rtl_ssi_rx_gdma_irq_handle(phal_ssi_adaptor_t phal_ssi_adaptor)
{
	SSI_TypeDef *spi_dev = (SSI_TypeDef *) phal_ssi_adaptor->spi_dev;

	phal_ssi_adaptor->dma_control &= ~SsiRxDmaEnable;
	spi_dev->SSI_DMACR = phal_ssi_adaptor->dma_control;

	if (phal_ssi_adaptor->dcache_invalidate_by_addr != NULL) {
		phal_ssi_adaptor->dcache_invalidate_by_addr((uint32_t *) phal_ssi_adaptor->cache_invalidate_addr, (int32_t) phal_ssi_adaptor->cache_invalidate_len);
	}

	if (NULL != phal_ssi_adaptor->rx_done_callback) {
		phal_ssi_adaptor->rx_done_callback(phal_ssi_adaptor->rx_done_cb_para);
	}
}

/** \brief Description of hal_rtl_ssi_tx_gdma_init_setting
 *
 *    hal_rtl_ssi_tx_gdma_init_setting is used to initialize GDMA when data is moved from memory to SPI FIFO by GDMA.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *   \param phal_gdma_adaptor_t phal_gdma_adaptor:      The pointer of GDMA adaptor.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_rtl_ssi_tx_gdma_init_setting(phal_ssi_adaptor_t phal_ssi_adaptor, phal_gdma_adaptor_t phal_gdma_adaptor)
{
	SSI_TypeDef *spi_dev;
	u8 *pdst = 0;
	u8 dst_per = 0;
	u8 index;

	if (NULL == phal_ssi_adaptor) {
		DBG_SSI_ERR("hal_rtl_ssi_tx_gdma_init : phal_ssi_adaptor is NULL\n");
		return HAL_ERR_MEM;
	}

	index = phal_ssi_adaptor->index;

	if (NULL == phal_gdma_adaptor) {
		DBG_SSI_ERR("hal_rtl_ssi_tx_gdma_init: hal_gdma_adaptor is NULL\r\n");
		return HAL_ERR_MEM;
	}

	spi_dev = (SSI_TypeDef *) phal_ssi_adaptor->spi_dev;
	pdst = (u8 *) & (spi_dev->SSI_DR);

	switch (index) {
	case 0:
		dst_per = GDMA_HANDSHAKE_SPI0_TX;
		break;

	case 1:
		dst_per = GDMA_HANDSHAKE_SPI1_TX;
		break;

	case 2:
		dst_per = GDMA_HANDSHAKE_HS_SPI0_TX;
		break;

	case 3:
		dst_per = GDMA_HANDSHAKE_HS_SPI1_TX;
		break;

	default:
		DBG_SSI_ERR("Invalid SPI Index!\n");
		return HAL_ERR_PARA;
		break;
	}

	phal_gdma_adaptor->gdma_ctl.tt_fc      = TTFCMemToPeri;
	phal_gdma_adaptor->max_block_num = 1;
	phal_gdma_adaptor->gdma_cfg.dest_per   = dst_per;
	phal_gdma_adaptor->ch_dar = (u32)pdst;
	phal_gdma_adaptor->gdma_isr_type = (TransferType | ErrType);
	phal_gdma_adaptor->gdma_ctl.int_en      = 1;
	phal_gdma_adaptor->gdma_ctl.dinc = NoChange;
	phal_gdma_adaptor->gdma_ctl.sinc = IncType;

	hal_gdma_handshake_init(phal_gdma_adaptor, phal_gdma_adaptor->gdma_cfg.dest_per);
	hal_gdma_irq_reg(phal_gdma_adaptor, (irq_handler_t) hal_rtl_ssi_tx_gdma_irq_handle, phal_ssi_adaptor);

	return HAL_OK;
}

/** \brief Description of hal_rtl_ssi_rx_gdma_init_setting
 *
 *    hal_rtl_ssi_rx_gdma_init_setting is used to initialize GDMA when data is moved from SPI FIFO to memory by GDMA.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *   \param phal_gdma_adaptor_t phal_gdma_adaptor:      The pointer of GDMA adaptor.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_rtl_ssi_rx_gdma_init_setting(phal_ssi_adaptor_t phal_ssi_adaptor, phal_gdma_adaptor_t phal_gdma_adaptor)
{
	SSI_TypeDef *spi_dev;
	u8 *psrc = 0;
	u8 src_per = 0;
	u8 index;

	if (NULL == phal_ssi_adaptor) {
		DBG_SSI_ERR("hal_rtl_ssi_rx_gdma_init : phal_ssi_adaptor is NULL\n");
		return HAL_ERR_MEM;
	}

	index = phal_ssi_adaptor->index;

	if (NULL == phal_gdma_adaptor) {
		DBG_SSI_ERR("hal_rtl_ssi_rx_gdma_init: hal_gdma_adaptor is NULL\r\n");
		return HAL_ERR_MEM;
	}

	spi_dev = (SSI_TypeDef *) phal_ssi_adaptor->spi_dev;
	phal_ssi_adaptor->dma_control |= SsiRxDmaEnable;

	psrc = (u8 *) & (spi_dev->SSI_DR);

	switch (index) {
	case 0:
		src_per = GDMA_HANDSHAKE_SPI0_RX;
		break;

	case 1:
		src_per = GDMA_HANDSHAKE_SPI1_RX;
		break;

	case 2:
		src_per = GDMA_HANDSHAKE_HS_SPI0_RX;
		break;

	case 3:
		src_per = GDMA_HANDSHAKE_HS_SPI1_RX;
		break;

	default:
		DBG_SSI_ERR("Invalid SPI Index!\n");
		return HAL_ERR_PARA;
		break;
	}

	phal_gdma_adaptor->gdma_ctl.tt_fc      = TTFCPeriToMem;
	phal_gdma_adaptor->max_block_num = 1;
	phal_gdma_adaptor->gdma_cfg.src_per   = src_per;
	phal_gdma_adaptor->ch_sar = (u32)psrc;
	phal_gdma_adaptor->gdma_isr_type = (TransferType | ErrType);
	phal_gdma_adaptor->gdma_ctl.int_en      = 1;
	phal_gdma_adaptor->gdma_ctl.dinc = IncType;
	phal_gdma_adaptor->gdma_ctl.sinc = NoChange;

	hal_gdma_handshake_init(phal_gdma_adaptor, phal_gdma_adaptor->gdma_cfg.src_per);
	hal_gdma_irq_reg(phal_gdma_adaptor, (irq_handler_t) hal_rtl_ssi_rx_gdma_irq_handle, phal_ssi_adaptor);

	return HAL_OK;
}

/** \brief Description of hal_rtl_ssi_dma_send_init
 *
 *    hal_rtl_ssi_dma_send_init is used to configure a transfer to send data from memory to SPI FIFO by GDMA.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *   \param u8 *ptx_data:      The source address of data(on memory).
 *   \param u32 length:     Total transfer length.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_rtl_ssi_dma_send_init(phal_ssi_adaptor_t phal_ssi_adaptor, u8 *ptx_data, u32 length)
{
	SSI_TypeDef *spi_dev = (SSI_TypeDef *)phal_ssi_adaptor->spi_dev;
	phal_gdma_adaptor_t phal_gdma_adaptor;


	if ((ptx_data == NULL) || (length == 0)) {
		DBG_SSI_ERR("hal_rtl_ssi_dma_send_init: null tx address = 0x%x,  length=%d\n", ptx_data, length);
		return HAL_ERR_PARA;
	}

	/*clean cache prior to dma transfer*/
	if (phal_ssi_adaptor->dcache_clean_by_addr != NULL) {
		phal_ssi_adaptor->dcache_clean_by_addr((uint32_t *) ptx_data, (int32_t) length);
	}

	phal_gdma_adaptor = (phal_gdma_adaptor_t) phal_ssi_adaptor->ptx_gdma_adaptor;
	phal_ssi_adaptor->tx_length = length;
	phal_ssi_adaptor->tx_data = (void *)ptx_data;

	/*Assign Source Address*/
	phal_gdma_adaptor->ch_sar = (u32) ptx_data;

	// cofigure gdma transfer
	if (phal_ssi_adaptor->data_frame_size == DfsSixteenBits) {
		// 16 bits mode
		if ((length & 0x03) == 0) {
			// 4-bytes aligned, move 4 bytes each transfer
			phal_gdma_adaptor->gdma_ctl.src_msize   = MsizeFour;
			phal_gdma_adaptor->gdma_ctl.src_tr_width = TrWidthFourBytes;
			phal_gdma_adaptor->gdma_ctl.dest_msize  = MsizeEight;
			phal_gdma_adaptor->gdma_ctl.dst_tr_width = TrWidthTwoBytes;
			phal_gdma_adaptor->gdma_ctl.block_size = length >> 2;
		} else {
			phal_gdma_adaptor->gdma_ctl.src_msize   = MsizeFour;
			phal_gdma_adaptor->gdma_ctl.src_tr_width = TrWidthTwoBytes;
			phal_gdma_adaptor->gdma_ctl.dest_msize  = MsizeFour;
			phal_gdma_adaptor->gdma_ctl.dst_tr_width = TrWidthTwoBytes;
			phal_gdma_adaptor->gdma_ctl.block_size = length >> 1;
		}
	} else {
		// 8 bits mode
		if ((length & 0x03) == 0) {
			// 4-bytes aligned, move 4 bytes each transfer
			phal_gdma_adaptor->gdma_ctl.src_msize   = MsizeOne;
			phal_gdma_adaptor->gdma_ctl.src_tr_width = TrWidthFourBytes;
			phal_gdma_adaptor->gdma_ctl.block_size = length >> 2;
		} else {
			phal_gdma_adaptor->gdma_ctl.src_msize   = MsizeFour;
			phal_gdma_adaptor->gdma_ctl.src_tr_width = TrWidthOneByte;
			phal_gdma_adaptor->gdma_ctl.block_size = length;
		}
		phal_gdma_adaptor->gdma_ctl.dest_msize  = MsizeFour;
		phal_gdma_adaptor->gdma_ctl.dst_tr_width = TrWidthOneByte;
	}

	DBG_SSI_INFO("TX src_msize=%d src_tr_width=%d dest_msize=%d dst_tr_width=%d block_size=%d\n", \
				 phal_gdma_adaptor->gdma_ctl.src_msize, phal_gdma_adaptor->gdma_ctl.src_tr_width, \
				 phal_gdma_adaptor->gdma_ctl.dest_msize, phal_gdma_adaptor->gdma_ctl.dst_tr_width, \
				 phal_gdma_adaptor->gdma_ctl.block_size);

	phal_ssi_adaptor->dma_control |= SsiTxDmaEnable;
	spi_dev->SSI_DMACR = phal_ssi_adaptor->dma_control;
	spi_dev->SSI_DMATDLR = phal_ssi_adaptor->dma_tx_data_level;

	return HAL_OK;
}


/** \brief Description of hal_rtl_ssi_dma_recv_init
 *
 *    hal_rtl_ssi_dma_recv_init is used to configure a transfer to move data from SPI FIFO to memory by GDMA.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *   \param u8 *prx_data:      The destination address of data(on memory).
 *   \param u32 length:     Total transfer length.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_rtl_ssi_dma_recv_init(phal_ssi_adaptor_t phal_ssi_adaptor, u8 *prx_data, u32 length)
{
	SSI_TypeDef *spi_dev = (SSI_TypeDef *)phal_ssi_adaptor->spi_dev;
	phal_gdma_adaptor_t phal_gdma_adaptor;

	if ((prx_data == NULL) || (length == 0)) {
		DBG_SSI_ERR("hal_ssi_dma_recv_init: null rx address = 0x%x, length=%d\n",  prx_data, length);
		return HAL_ERR_PARA;
	}

	phal_gdma_adaptor = (phal_gdma_adaptor_t) phal_ssi_adaptor->prx_gdma_adaptor;
	phal_ssi_adaptor->rx_length = length;
	phal_ssi_adaptor->rx_data = (void *)prx_data;

	/*Assign Destination Address*/
	phal_gdma_adaptor->ch_dar = (u32) prx_data;
	phal_ssi_adaptor->cache_invalidate_len = (int32_t)length;
	phal_ssi_adaptor->cache_invalidate_addr = (uint32_t *)prx_data;

	// cofigure gdma transfer
	if (phal_ssi_adaptor->data_frame_size == DfsSixteenBits) {
		// 16 bits mode
		phal_gdma_adaptor->gdma_ctl.src_msize   = MsizeEight;
		phal_gdma_adaptor->gdma_ctl.src_tr_width = TrWidthTwoBytes;
		phal_gdma_adaptor->gdma_ctl.block_size = length >> 1;
		phal_gdma_adaptor->gdma_ctl.dest_msize  = MsizeFour;
		phal_gdma_adaptor->gdma_ctl.dst_tr_width = TrWidthFourBytes;
	} else {
		// 8 bits mode
		phal_gdma_adaptor->gdma_ctl.src_msize   = MsizeFour;
		phal_gdma_adaptor->gdma_ctl.src_tr_width = TrWidthOneByte;
		phal_gdma_adaptor->gdma_ctl.block_size = length;
		phal_gdma_adaptor->gdma_ctl.dest_msize  = MsizeOne;
		phal_gdma_adaptor->gdma_ctl.dst_tr_width = TrWidthFourBytes;
	}

	DBG_SSI_INFO("RX src_msize=%d src_tr_width=%d dest_msize=%d dst_tr_width=%d block_size=%d\n", \
				 phal_gdma_adaptor->gdma_ctl.src_msize, phal_gdma_adaptor->gdma_ctl.src_tr_width, \
				 phal_gdma_adaptor->gdma_ctl.dest_msize, phal_gdma_adaptor->gdma_ctl.dst_tr_width, \
				 phal_gdma_adaptor->gdma_ctl.block_size);

	phal_ssi_adaptor->dma_control |= SsiRxDmaEnable;
	spi_dev->SSI_DMACR = phal_ssi_adaptor->dma_control;
	spi_dev->SSI_DMARDLR = phal_ssi_adaptor->dma_rx_data_level;

	return HAL_OK;
}

/** *@} */ /* End of group hal_ssi_rom_func */

/// @endcond /* End of condition DOXYGEN_ROM_HAL_API */

/** *@} */

