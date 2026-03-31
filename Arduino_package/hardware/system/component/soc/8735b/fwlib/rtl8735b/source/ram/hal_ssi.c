/**************************************************************************//**
 * @file     hal_ssi.c
 * @brief    Implement SSI HAL RAM code function.
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
#include "hal_ssi.h"
#include "hal_gdma.h"
#include "hal_pinmux.h"
#include "hal_cache.h"
#include "hal_irq.h"
#include "hal_gpio.h"
#include "rtl8735b_ssi_type.h"

/**

        \addtogroup hs_hal_ssi SPI
        \brief The Serial Peripheral Interface bus(SPI) HAL APIs.
        @{
*/


/**

        \addtogroup hs_hal_ssi_ram_func SPI HAL RAM APIs
        \ingroup hs_hal_ssi
        \brief The SPI HAL APIs
        @{
*/

/** \brief Description of hal_ssi_pin_ctl
 *
 *    hal_ssi_pin_ctl is used to enable and select pins for the target SPI device.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *   \param u8 ctl:      A control bit to decide to enable or disable the pinmux of the device.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_ssi_pin_ctl(phal_ssi_adaptor_t phal_ssi_adaptor, u8 ctl)
{
	u8 index;
	u8 spi_index = phal_ssi_adaptor->index;
	u32 pid;
	hal_status_t ret;
	pspi_pin_sel_t pspi_pin = &(phal_ssi_adaptor->spi_pin);

	switch (spi_index) {
	case 0:
		pid = PID_SPI0;
		break;

	case 1:
		pid = PID_SPI1;
		break;

	case 2:
		pid = PID_SPI2;
		break;

	case 3:
		pid = PID_SPI3;
		break;

	default:
		pid = PID_SPI0;
		break;
	}

	if (ctl == ENABLE) {
		for (index = 0; index < 4; index++) {
			ret = hal_pinmux_register(*(((u32 *)pspi_pin) + index), pid);
			if (ret != HAL_OK) {
				DBG_SSI_ERR("PIN %x cannot be registered.\r\n", *(((u32 *)pspi_pin) + index));
				return ret;
			}
			hal_gpio_schmitt_ctrl(*(((u32 *)pspi_pin) + index), ctl);
		}
	} else {
		for (index = 0; index < 4; index++) {
			ret = hal_pinmux_unregister(*(((u32 *)pspi_pin) + index), pid);
			if (ret != HAL_OK) {
				DBG_SSI_ERR("PIN %x cannot be unregistered.\r\n", *(((u32 *)pspi_pin) + index));
				return ret;
			}
			hal_gpio_schmitt_ctrl(*(((u32 *)pspi_pin) + index), ctl);
		}
	}


	return HAL_OK;
}

/** \brief Description of hal_ssi_init
 *
 *    hal_ssi_init is used to initialize the SPI device through ROM code. The pinmux selection is also registered here.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_ssi_init(phal_ssi_adaptor_t phal_ssi_adaptor)
{
	hal_status_t ret;

	ret = hal_ssi_pin_ctl(phal_ssi_adaptor, ENABLE);

	if (ret == HAL_OK) {
		return hal_ssi_init_setting(phal_ssi_adaptor);
	} else {
		return ret;
	}
}

/** \brief Description of hal_spi_format
 *
 *    hal_spi_format is used to setup SPI frame format, size and SPI mode.
 *    The transfer mode is always transmit and receive mode.
 *    The SPI mode number is transformed  into clock phase and clock polarity before setting these values to registers through ROM code functions.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *   \param u8 bits:      The size of frame, only 8 bits and 16 bits are supported.
 *   \param u8 mode:      The SPI mode, mode 0~3 are supported.
 *
 *   \return void.
 */
void hal_spi_format(phal_ssi_adaptor_t phal_ssi_adaptor, u8 bits, u8 mode)
{
	phal_ssi_adaptor->data_frame_size = bits;
	phal_ssi_adaptor->data_frame_format = FrfMotorolaSpi;
	phal_ssi_adaptor->transfer_mode = TmodTr;

	switch (mode) {
	case 0:
		phal_ssi_adaptor->sclk_polarity = ScpolInactiveIsLow;
		phal_ssi_adaptor->sclk_phase    = ScphToggleInMiddle;
		break;

	case 1:
		phal_ssi_adaptor->sclk_polarity = ScpolInactiveIsLow;
		phal_ssi_adaptor->sclk_phase    = ScphToggleAtStart;
		break;

	case 2:
		phal_ssi_adaptor->sclk_polarity = ScpolInactiveIsHigh;
		phal_ssi_adaptor->sclk_phase    = ScphToggleInMiddle;
		break;

	case 3:
		phal_ssi_adaptor->sclk_polarity = ScpolInactiveIsHigh;
		phal_ssi_adaptor->sclk_phase    = ScphToggleAtStart;
		break;

	default:  // same as 0
		phal_ssi_adaptor->sclk_polarity = ScpolInactiveIsLow;
		phal_ssi_adaptor->sclk_phase    = ScphToggleInMiddle;
		break;
	}

	hal_ssi_set_format(phal_ssi_adaptor);
}

void hal_ssi_toggle_between_frame(phal_ssi_adaptor_t phal_ssi_adaptor, u8 ctl)
{
	u8 sclk_phase = phal_ssi_adaptor->sclk_phase;
	u8 index = phal_ssi_adaptor->index;
	SSI_TypeDef *spi_dev = (SSI_TypeDef *) phal_ssi_adaptor->spi_dev;

	if (sclk_phase == ScphToggleInMiddle) {
		/*High Speed Slave does not have to control the toggle bit*/
		if ((index == 0)
			|| (index == 1)) {
			spi_dev->SSI_SSIENR = DISABLE;
			spi_dev->SSI_CTRLR0 &= ~SSI_BIT_SS_T;
			spi_dev->SSI_CTRLR0 |= (ctl << SSI_SHIFT_SS_T);
			spi_dev->SSI_SSIENR = ENABLE;
		}
	}
}

/** \brief Description of hal_ssi_callback_hook
 *
 *    hal_ssi_callback_hook is used to set callback functions when the transfer is complete.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *   \param void *tx_handler:      The callback function when data is transmitted.
 *   \param void *rx_handler:      The callback function when data is received.
 *
 *   \return void.
 */
void hal_ssi_callback_hook(phal_ssi_adaptor_t phal_ssi_adaptor, void *tx_handler, void *rx_handler)
{
	if (tx_handler != NULL) {
		phal_ssi_adaptor->tx_done_callback = (void(*)(void *))tx_handler;
		phal_ssi_adaptor->tx_done_cb_para = phal_ssi_adaptor;
	}

	if (rx_handler != NULL) {
		phal_ssi_adaptor->rx_done_callback = (void(*)(void *))rx_handler;
		phal_ssi_adaptor->rx_done_cb_para = phal_ssi_adaptor;
	}
}

/** \brief Description of hal_ssi_deinit
 *
 *    hal_ssi_deinit is used to deinit the SPI device when it is no longer to be used.
 *    If the transfer involves with GDMA engine, the channel is released by gdma_deinit functions.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_ssi_deinit(phal_ssi_adaptor_t phal_ssi_adaptor)
{
	hal_status_t ret;

	ret = hal_ssi_pin_ctl(phal_ssi_adaptor, DISABLE);
	if (ret != HAL_OK) {
		DBG_SSI_ERR("Deinit pins fails.\r\n");
	}

	ret = hal_ssi_deinit_setting(phal_ssi_adaptor);
	if (ret != HAL_OK) {
		DBG_SSI_ERR("Deinit fails.\r\n");
	}

	hal_ssi_tx_gdma_deinit(phal_ssi_adaptor);
	hal_ssi_rx_gdma_deinit(phal_ssi_adaptor);

	return ret;
}

/** \brief Description of hal_ssi_tx_gdma_init
 *
 *    hal_ssi_tx_gdma_init is used to initialize GDMA settings if the SPI device will handshake with GDMA to transmit data.
 *    GDMA channel management functions are called in GDMA RAM code.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *   \param phal_gdma_adaptor_t phal_gdma_adaptor:      The pointer of GDMA adaptor.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_ssi_tx_gdma_init(phal_ssi_adaptor_t phal_ssi_adaptor, phal_gdma_adaptor_t phal_gdma_adaptor)
{
	hal_status_t ret;

	phal_gdma_adaptor->have_chnl = 0;
	ret = hal_gdma_chnl_alloc(phal_gdma_adaptor, MultiBlkDis);     // default no-multiple block support

	if (ret == HAL_OK) {
		ret = hal_ssi_tx_gdma_init_setting(phal_ssi_adaptor, phal_gdma_adaptor);

#if !defined (CONFIG_BUILD_NONSECURE)
		hal_irq_disable(phal_gdma_adaptor->gdma_irq_num);
		__ISB();

		if (phal_gdma_adaptor->gdma_index == 0) {
			phal_gdma_adaptor->gdma_irq_num = SGDMA0_IRQn;
		} else {
			phal_gdma_adaptor->gdma_irq_num = SGDMA1_IRQn;
		}

		hal_irq_enable(phal_gdma_adaptor->gdma_irq_num);
#endif

		if (ret == HAL_OK) {
			hal_gdma_chnl_init(phal_gdma_adaptor);
		} else {
			DBG_SSI_ERR("hal_ssi_tx_gdma_init: GDMA init failed(%d)\r\n", ret);
			hal_gdma_chnl_free(phal_gdma_adaptor);
		}
	} else {
		DBG_SSI_ERR("hal_ssi_tx_gdma_init: GDMA channel allocate failed(%d)\r\n", ret);
	}

	phal_ssi_adaptor->dcache_clean_by_addr = hal_cache_stubs.dcache_clean_by_addr;

	if (phal_ssi_adaptor->data_frame_size == DfsSixteenBits) {
		// 16 bits mode
		phal_ssi_adaptor->dma_tx_data_level = 8;  // when tx fifo entity number <=48 then dma request asserted
	} else {
		// 8 bits mode
		phal_ssi_adaptor->dma_tx_data_level = 16;  // when tx fifo entity number <=56 then dma request asserted
	}
	return ret;
}

/** \brief Description of hal_ssi_rx_gdma_init
 *
 *    hal_ssi_rx_gdma_init is used to initialize GDMA settings if the SPI device will handshake with GDMA to receive data.
 *    GDMA channel management functions are called in GDMA RAM code.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *   \param phal_gdma_adaptor_t phal_gdma_adaptor:      The pointer of GDMA adaptor.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_ssi_rx_gdma_init(phal_ssi_adaptor_t phal_ssi_adaptor, phal_gdma_adaptor_t phal_gdma_adaptor)
{
	hal_status_t ret;

	phal_gdma_adaptor->have_chnl = 0;

	ret = hal_gdma_chnl_alloc(phal_gdma_adaptor, MultiBlkDis);     // default no-multiple block support
	if (ret == HAL_OK) {
		ret = hal_ssi_rx_gdma_init_setting(phal_ssi_adaptor, phal_gdma_adaptor);

#if !defined (CONFIG_BUILD_NONSECURE)
		hal_irq_disable(phal_gdma_adaptor->gdma_irq_num);
		__ISB();

		if (phal_gdma_adaptor->gdma_index == 0) {
			phal_gdma_adaptor->gdma_irq_num = SGDMA0_IRQn;
		} else {
			phal_gdma_adaptor->gdma_irq_num = SGDMA1_IRQn;
		}

		hal_irq_enable(phal_gdma_adaptor->gdma_irq_num);
#endif

		if (ret == HAL_OK) {
			hal_gdma_chnl_init(phal_gdma_adaptor);
		} else {
			DBG_SSI_ERR("hal_ssi_rx_gdma_init: GDMA init failed(%d)\r\n", ret);
			hal_gdma_chnl_free(phal_gdma_adaptor);
		}
	} else {
		DBG_SSI_ERR("hal_ssi_rx_gdma_init: GDMA channel allocate failed(%d)\r\n", ret);
	}

	phal_ssi_adaptor->dcache_invalidate_by_addr = hal_cache_stubs.dcache_invalidate_by_addr;

	if (phal_ssi_adaptor->data_frame_size == DfsSixteenBits) {
		// 16~9 bits mode
		phal_ssi_adaptor->dma_rx_data_level = 7;  // when rx fifo entity number >=8 then dma request asserted
	} else {
		// 8~4 bits mode
		phal_ssi_adaptor->dma_rx_data_level = 3;  // when rx fifo entity number >=4 then dma request asserted
	}

	return ret;
}


/** \brief Description of hal_ssi_tx_gdma_deinit
 *
 *    hal_ssi_tx_gdma_deinit is used to de-initialize GDMA settings if the SPI device will not handshake with GDMA to transmit data anymore.
 *    hal_gdma_chnl_free function is called in GDMA RAM code.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_ssi_tx_gdma_deinit(phal_ssi_adaptor_t phal_ssi_adaptor)
{
	phal_gdma_adaptor_t phal_gdma_adaptor;

	if (phal_ssi_adaptor == NULL) {
		DBG_SSI_ERR("hal_ssi_tx_gdma_deinit : Null Adaptor!\n");
		return HAL_ERR_PARA;
	}

	phal_gdma_adaptor = (phal_gdma_adaptor_t) phal_ssi_adaptor->ptx_gdma_adaptor;

	if (phal_gdma_adaptor->gdma_dev != NULL) {
		hal_gdma_chnl_free(phal_gdma_adaptor);
	}

	return HAL_OK;
}

/** \brief Description of hal_ssi_rx_gdma_deinit
 *
 *    hal_ssi_rx_gdma_deinit is used to de-initialize GDMA settings if the SPI device will not handshake with GDMA to receive data anymore.
 *    hal_gdma_chnl_free function is called in GDMA RAM code.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_ssi_rx_gdma_deinit(phal_ssi_adaptor_t phal_ssi_adaptor)
{
	phal_gdma_adaptor_t phal_gdma_adaptor;

	if (phal_ssi_adaptor == NULL) {
		DBG_SSI_ERR("hal_ssi_rx_gdma_deinit : Null Adaptor!\n");
		return HAL_ERR_PARA;
	}

	phal_gdma_adaptor = (phal_gdma_adaptor_t) phal_ssi_adaptor->prx_gdma_adaptor;

	if (phal_gdma_adaptor->gdma_dev != NULL) {
		hal_gdma_chnl_free(phal_gdma_adaptor);
	}

	return HAL_OK;
}

/** \brief Description of hal_ssi_dma_send
 *
 *    hal_ssi_dma_send is used to setup the transfer when the SPI device will transmit data with GDMA.
 *    GDMA moves data from memory (ptx_data) to the SPI FIFO, then the SPI device pops data out of its FIFO.
 *    If data length exceeds MAX_DMA_BLOCK_SIZE, this function will re-allocate a channel supporting multiblock mode.
 *    At the end of this function, the transfer begins.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *   \param u8 *ptx_data:      The source address.
 *   \param u32 length:      The total data length.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_ssi_dma_send(phal_ssi_adaptor_t phal_ssi_adaptor, u8  *ptx_data, u32 length)
{
	phal_gdma_adaptor_t phal_gdma_adaptor;
	u8 multi_block_en = MultiBlkDis;
	u8 gdma_index;

	phal_gdma_adaptor = (phal_gdma_adaptor_t) phal_ssi_adaptor->ptx_gdma_adaptor;

	hal_ssi_dma_send_init(phal_ssi_adaptor, ptx_data, length);
	if (phal_gdma_adaptor->gdma_ctl.block_size > MAX_DMA_BLOCK_SIZE) {
		multi_block_en = MultiBlkEn;

		if (phal_gdma_adaptor->ch_num < MIN_MULTI_CHNL_NUM) {
			gdma_index = phal_gdma_adaptor->gdma_index;
			if (hal_gdma_chnl_alloc(phal_gdma_adaptor, multi_block_en) != HAL_OK) {
				phal_ssi_adaptor->ptx_gdma_adaptor = NULL;
				DBG_SSI_ERR("hal_ssi_dma_send: Err: re-allocate multiple block DMA channel failed\r\n");
				return HAL_ERR_HW;
			} else {
				hal_gdma_chnl_init(phal_gdma_adaptor);
			}

			if (gdma_index != phal_gdma_adaptor->gdma_index) {
				hal_gdma_handshake_init(phal_gdma_adaptor, phal_gdma_adaptor->gdma_cfg.dest_per);
			}

			hal_gdma_irq_reg(phal_gdma_adaptor, (irq_handler_t) hal_ssi_stubs.hal_ssi_tx_gdma_irq_handle, phal_ssi_adaptor);
		}
	}

	hal_gdma_transfer_start(phal_gdma_adaptor, multi_block_en);
	return HAL_OK;
}

/** \brief Description of hal_ssi_dma_recv
 *
 *    hal_ssi_dma_recv is used to setup the transfer when the SPI device will receive data with GDMA.
 *    Data is received to the SPI device's FIFO, then GDMA moves data from SPI device's FIFO to memory (prx_data).
 *    If data length exceeds MAX_DMA_BLOCK_SIZE, this function will re-allocate a channel supporting multiblock mode.
 *    At the end of this function, the transfer begins.
 *
 *   \param phal_ssi_adaptor_t phal_ssi_adaptor:      The pointer of SPI adaptor.
 *   \param u8 *ptx_data:      The source address.
 *   \param u32 length:      The total data length.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_ssi_dma_recv(phal_ssi_adaptor_t phal_ssi_adaptor, u8  *prx_data, u32 length)
{
	phal_gdma_adaptor_t phal_gdma_adaptor;
	u8 multi_block_en = MultiBlkDis;
	u8 gdma_index;

	phal_gdma_adaptor = (phal_gdma_adaptor_t) phal_ssi_adaptor->prx_gdma_adaptor;

	hal_ssi_dma_recv_init(phal_ssi_adaptor, prx_data, length);
	if (phal_gdma_adaptor->gdma_ctl.block_size > MAX_DMA_BLOCK_SIZE) {
		multi_block_en = MultiBlkEn;

		if (phal_gdma_adaptor->ch_num < MIN_MULTI_CHNL_NUM) {
			gdma_index = phal_gdma_adaptor->gdma_index;
			if (hal_gdma_chnl_alloc(phal_gdma_adaptor, multi_block_en) != HAL_OK) {
				phal_ssi_adaptor->prx_gdma_adaptor = NULL;
				DBG_SSI_ERR("hal_ssi_dma_recv: Err: re-allocate multiple block DMA channel failed\r\n");
				return HAL_ERR_HW;
			} else {
				hal_gdma_chnl_init(phal_gdma_adaptor);
			}

			if (gdma_index != phal_gdma_adaptor->gdma_index) {
				hal_gdma_handshake_init(phal_gdma_adaptor, phal_gdma_adaptor->gdma_cfg.src_per);
			}

			hal_gdma_irq_reg(phal_gdma_adaptor, (irq_handler_t) hal_ssi_stubs.hal_ssi_rx_gdma_irq_handle, phal_ssi_adaptor);
		}
	}

	hal_gdma_transfer_start(phal_gdma_adaptor, multi_block_en);
	return HAL_OK;
}

/** *@} */ /* End of group hs_hal_ssi_ram_func */

/** *@} */ /* End of group hs_hal_ssi */

