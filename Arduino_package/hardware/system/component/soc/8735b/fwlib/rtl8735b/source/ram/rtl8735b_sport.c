/**************************************************************************//**
 * @file     rtl8735b_sport.c
 * @brief    This file implements the SPORT HAL functions in ROM.
 *
 * @version  V1.00
 * @date     2016-07-20
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
#include "rtl8735b_sport.h"
#include "hal_cache.h"
#include "hal_sys_ctrl.h"
#include "hal_sys_ctrl_nsc.h"

#if !defined(CONFIG_BUILD_NONSECURE)

#undef SPORT_REG_BASE
#define SPORT_REG_BASE (SPORT_S_BASE)

#else

#undef SPORT_REG_BASE
#define SPORT_REG_BASE (SPORT_BASE)

#endif


/**
  * @brief The global common data structure to store common resource
  *        for SPORT adapters.
  */
hal_sport_group_adapter_t sport_group_adapter;

/// @cond DOXYGEN_ROM_HAL_API

/**
 * @addtogroup hs_hal_sport_rom_func SPORT HAL ROM APIs.
 * @ingroup hs_hal_sport
 * @{
 * @brief The SPORT HAL ROM APIs. The user application(in RAM space) should not call these APIs directly.
 *        There is another set of SPORT HAL APIs in the RAM space is provided for the user application.
 */

/**
  * @brief The stubs functions table to exports SPORT HAL functions in ROM.
  */
const hal_sport_func_stubs_t hal_sport_stubs = {
	.hal_sport_irqhandler_ram = hal_rtl_sport_irqhandler_ram,
	.hal_sport_irq_reg = hal_rtl_sport_irq_reg,
	.hal_sport_irq_unreg = hal_rtl_sport_irq_unreg,
	.hal_sport_init = hal_rtl_sport_init,
	.hal_sport_deinit = hal_rtl_sport_deinit,
	.hal_sport_reset = hal_rtl_sport_reset,
	.hal_sport_reset_tx_fifo = hal_rtl_sport_reset_tx_fifo,
	.hal_sport_reset_rx_fifo = hal_rtl_sport_reset_rx_fifo,
	.hal_sport_bclk_reset = hal_rtl_sport_bclk_reset,
	.hal_sport_dma_reset = hal_rtl_sport_dma_reset,
	.hal_sport_clean_tx_page_own = hal_rtl_sport_clean_tx_page_own,
	.hal_sport_clean_rx_page_own = hal_rtl_sport_clean_rx_page_own,
	.hal_sport_set_master = hal_rtl_sport_set_master,
	.hal_sport_set_loopback = hal_rtl_sport_set_loopback,
	.hal_sport_mode = hal_rtl_sport_mode,
	.hal_sport_tx_ch = hal_rtl_sport_tx_ch,
	.hal_sport_rx_ch = hal_rtl_sport_rx_ch,
	.hal_sport_format = hal_rtl_sport_format,
	.hal_sport_rx_same_format = hal_rtl_sport_rx_same_format,
	.hal_sport_rx_format = hal_rtl_sport_rx_format,
	.hal_sport_tx0_mono = hal_rtl_sport_tx0_mono,
	.hal_sport_tx1_mono =  hal_rtl_sport_tx1_mono,
	.hal_sport_rx_same_mono_stereo = hal_rtl_sport_rx_same_mono_stereo,
	.hal_sport_rx0_mono = hal_rtl_sport_rx0_mono,
	.hal_sport_rx1_mono = hal_rtl_sport_rx1_mono,
	.hal_sport_tx0_data_length = hal_rtl_sport_tx0_data_length,
	.hal_sport_tx1_data_length = hal_rtl_sport_tx1_data_length,
	.hal_sport_rx_same_data_length = hal_rtl_sport_rx_same_data_length,
	.hal_sport_rx0_data_length = hal_rtl_sport_rx0_data_length,
	.hal_sport_rx1_data_length = hal_rtl_sport_rx1_data_length,
	.hal_sport_tx_channel_length = hal_rtl_sport_tx_channel_length,
	.hal_sport_rx_same_channel_length = hal_rtl_sport_rx_same_channel_length,
	.hal_sport_rx_channel_length = hal_rtl_sport_rx_channel_length,
	.hal_sport_tx_rate = hal_rtl_sport_tx_rate,
	.hal_sport_rx_rate = hal_rtl_sport_rx_rate,
	.hal_sport_tx_data_dir = hal_rtl_sport_tx_data_dir,
	.hal_sport_rx_data_dir = hal_rtl_sport_rx_data_dir,
	.hal_sport_tx_lr_swap = hal_rtl_sport_tx_lr_swap,
	.hal_sport_rx_lr_swap = hal_rtl_sport_rx_lr_swap,
	.hal_sport_tx_byte_swap = hal_rtl_sport_tx_byte_swap,
	.hal_sport_rx_byte_swap = hal_rtl_sport_rx_byte_swap,
	.hal_sport_bclk_inverse = hal_rtl_sport_bclk_inverse,
	.hal_sport_set_mclk = hal_rtl_sport_set_mclk,
	.hal_sport_sel_tx_tdm = hal_rtl_sport_sel_tx_tdm,
	.hal_sport_sel_rx_tdm = hal_rtl_sport_sel_rx_tdm,
	.hal_sport_set_tx0_consum = hal_rtl_sport_set_tx0_consum,
	.hal_sport_set_tx1_consum = hal_rtl_sport_set_tx1_consum,
	.hal_sport_set_rx0_consum = hal_rtl_sport_set_rx0_consum,
	.hal_sport_set_rx1_consum = hal_rtl_sport_set_rx1_consum,
	.hal_sport_tx_fifo_0 = hal_rtl_sport_tx_fifo_0,
	.hal_sport_tx_fifo_1 = hal_rtl_sport_tx_fifo_1,
	.hal_sport_rx_fifo_0 = hal_rtl_sport_rx_fifo_0,
	.hal_sport_rx_fifo_1 = hal_rtl_sport_rx_fifo_1,
	.hal_sport_set_tx_lrck = hal_rtl_sport_set_tx_lrck,
	.hal_sport_set_rx_lrck = hal_rtl_sport_set_rx_lrck,
	.hal_sport_tx_params = hal_rtl_sport_tx_params,
	.hal_sport_rx_params = hal_rtl_sport_rx_params,
	.hal_sport_tx_fifo_th = hal_rtl_sport_tx_fifo_th,
	.hal_sport_rx_fifo_th = hal_rtl_sport_rx_fifo_th,
	.hal_sport_set_dma_burst = hal_rtl_sport_set_dma_burst,
	.hal_sport_autoload_dma_burst = hal_rtl_sport_autoload_dma_burst,
	.hal_sport_set_dma_intr = hal_rtl_sport_set_dma_intr,
	.hal_sport_set_tx_fifo_intr = hal_rtl_sport_set_tx_fifo_intr,
	.hal_sport_set_rx_fifo_intr = hal_rtl_sport_set_rx_fifo_intr,
	.hal_sport_dma_params = hal_rtl_sport_dma_params,
	.hal_sport_tx_start = hal_rtl_sport_tx_start,
	.hal_sport_rx_start = hal_rtl_sport_rx_start,
	.hal_sport_tx_dma_start = hal_rtl_sport_tx_dma_start,
	.hal_sport_get_tx_dma_start_sta = hal_rtl_sport_get_tx_dma_start_sta,
	.hal_sport_rx_dma_start = hal_rtl_sport_rx_dma_start,
	.hal_sport_get_rx_dma_start_sta = hal_rtl_sport_get_rx_dma_start_sta,
	.hal_sport_dma_buffer = hal_rtl_sport_dma_buffer,
	.hal_sport_get_tx0_page = hal_rtl_sport_get_tx0_page,
	.hal_sport_get_tx1_page = hal_rtl_sport_get_tx1_page,
	.hal_sport_tx0_page_send = hal_rtl_sport_tx0_page_send,
	.hal_sport_tx1_page_send = hal_rtl_sport_tx1_page_send,
	.hal_sport_rx0_page_recv = hal_rtl_sport_rx0_page_recv,
	.hal_sport_rx1_page_recv = hal_rtl_sport_rx1_page_recv,
	.hal_sport_get_tx_fifo_err = hal_rtl_sport_get_tx_fifo_err,
	.hal_sport_get_rx_fifo_err = hal_rtl_sport_get_rx_fifo_err,
	.hal_sport_clr_tx_fifo_err = hal_rtl_sport_clr_tx_fifo_err,
	.hal_sport_clr_rx_fifo_err = hal_rtl_sport_clr_rx_fifo_err,
	.hal_sport_fifo_cb_handler = hal_rtl_sport_fifo_cb_handler,
	.hal_sport_tx0_dma_cb_handler = hal_rtl_sport_tx0_dma_cb_handler,
	.hal_sport_tx1_dma_cb_handler = hal_rtl_sport_tx1_dma_cb_handler,
	.hal_sport_rx0_dma_cb_handler = hal_rtl_sport_rx0_dma_cb_handler,
	.hal_sport_rx1_dma_cb_handler = hal_rtl_sport_rx1_dma_cb_handler,
	.hal_sport_dma_err_cb_handler = hal_rtl_sport_dma_err_cb_handler,
	.hal_sport_fixed_bclk = hal_rtl_sport_fixed_bclk,
	.hal_sport_rx_same_fs = hal_rtl_sport_rx_same_fs
};

/**
 *  @brief This is the common interrupt handler for SPORT.
 *         It read the system register to know the interrupt event
 *         is triggered by which SPORT device.
 *
 *  @returns void
 */
void hal_rtl_sport_irqhandler_ram(void)
{
	hal_sport_adapter_t *psport_adapter;
	SPORT_TypeDef *psport_reg;

	uint32_t i;
	uint32_t sp_tx_err_sta, sp_rx_err_sta;
	uint32_t sp_tx0_dma_int_sta, sp_tx1_dma_int_sta;
	uint32_t sp_rx0_dma_int_sta, sp_rx1_dma_int_sta;
	uint32_t sp_tx0_dma_int_sta_err, sp_tx1_dma_int_sta_err;
	uint32_t sp_rx0_dma_int_sta_err, sp_rx1_dma_int_sta_err;
	uint32_t sp_page_num;
	uint32_t sport_tx0_intr_event, sport_tx1_intr_event;
	uint32_t sport_rx0_intr_event, sport_rx1_intr_event;
	hal_sport_init_dat_t *psport_init_dat;
	uint32_t pbuf;

	hal_irq_clear_pending(SPORT_IRQn);

	psport_adapter = sport_group_adapter.psport_adapter[SPORT_id];

	psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	//dbg_printf("SPORT_IRQHandler \r\n");

	if (psport_adapter->sport_mode_record == SPORT_FIFO_MODE) {

		//FIFO mode : Input callback function
		if (psport_adapter->sport_irq_user_cb != NULL) {
			psport_adapter->sport_irq_user_cb(psport_adapter->sport_user_arg, NULL);
		}

	} else {

		psport_init_dat = &psport_adapter->init_dat;

		sp_tx_err_sta = hal_rtl_sport_get_tx_fifo_err(psport_adapter);
		sp_rx_err_sta = hal_rtl_sport_get_rx_fifo_err(psport_adapter);

		if ((sp_tx_err_sta != 0x00) || (sp_rx_err_sta != 0x00)) {
			//dbg_printf("sp_tx_err_sta: %d \r\n", sp_tx_err_sta);
			//dbg_printf("sp_rx_err_sta: %d \r\n", sp_rx_err_sta);
		}

		sp_tx0_dma_int_sta = hal_rtl_sport_get_tx0_dma_intr(psport_adapter);
		sp_tx1_dma_int_sta = hal_rtl_sport_get_tx1_dma_intr(psport_adapter);
		sp_rx0_dma_int_sta = hal_rtl_sport_get_rx0_dma_intr(psport_adapter);
		sp_rx1_dma_int_sta = hal_rtl_sport_get_rx1_dma_intr(psport_adapter);

		sp_tx0_dma_int_sta_err = hal_rtl_sport_get_tx0_dma_err_intr(psport_adapter);
		sp_tx1_dma_int_sta_err = hal_rtl_sport_get_tx1_dma_err_intr(psport_adapter);
		sp_rx0_dma_int_sta_err = hal_rtl_sport_get_rx0_dma_err_intr(psport_adapter);
		sp_rx1_dma_int_sta_err = hal_rtl_sport_get_rx1_dma_err_intr(psport_adapter);

		psport_adapter->tx_fifo_err = sp_tx_err_sta;
		psport_adapter->rx_fifo_err = sp_rx_err_sta;
		psport_adapter->tx0_dma_err = sp_tx0_dma_int_sta_err;
		psport_adapter->tx1_dma_err = sp_tx1_dma_int_sta_err;
		psport_adapter->rx0_dma_err = sp_rx0_dma_int_sta_err;
		psport_adapter->rx1_dma_err = sp_rx1_dma_int_sta_err;

		if (sp_tx0_dma_int_sta_err != 0x00) {
			DBG_SPORT_ERR("sp_tx0_dma_int_sta_err: 0x%8x \r\n", sp_tx0_dma_int_sta_err);
			hal_rtl_sport_tx_dma_start(psport_adapter, DISABLE);
			hal_rtl_sport_rx_dma_start(psport_adapter, DISABLE);
			hal_rtl_sport_clr_tx0_dma_intr(psport_adapter);
			psport_adapter->dma_err_sta |= 0x01;
		}

		if (sp_tx1_dma_int_sta_err != 0x00) {
			DBG_SPORT_ERR("sp_tx1_dma_int_sta_err: 0x%8x \r\n", sp_tx1_dma_int_sta_err);
			hal_rtl_sport_tx_dma_start(psport_adapter, DISABLE);
			hal_rtl_sport_rx_dma_start(psport_adapter, DISABLE);
			hal_rtl_sport_clr_tx1_dma_intr(psport_adapter);
			psport_adapter->dma_err_sta |= 0x02;
		}

		if (sp_rx0_dma_int_sta_err != 0x00) {
			DBG_SPORT_ERR("sp_rx0_dma_int_sta_err: 0x%8x \r\n", sp_rx0_dma_int_sta_err);
			hal_rtl_sport_tx_dma_start(psport_adapter, DISABLE);
			hal_rtl_sport_rx_dma_start(psport_adapter, DISABLE);
			hal_rtl_sport_clr_rx0_dma_intr(psport_adapter);
			psport_adapter->dma_err_sta |= 0x04;
		}

		if (sp_rx1_dma_int_sta_err != 0x00) {
			DBG_SPORT_ERR("sp_rx1_dma_int_sta_err: 0x%8x \r\n", sp_rx1_dma_int_sta_err);
			hal_rtl_sport_tx_dma_start(psport_adapter, DISABLE);
			hal_rtl_sport_rx_dma_start(psport_adapter, DISABLE);
			hal_rtl_sport_clr_rx1_dma_intr(psport_adapter);
			psport_adapter->dma_err_sta |= 0x08;
		}

		if (psport_adapter->dma_err_sta != 0x00) {
			if (psport_adapter->sport_dma_err_irq_user_cb != NULL) {
				psport_adapter->sport_dma_err_irq_user_cb(psport_adapter->sport_dma_err_user_arg, &psport_adapter->dma_err_sta);
			}
		}

		sp_page_num = hal_rtl_sport_get_page_number(psport_adapter) + 1;

		for (i = 0; i < sp_page_num; i++) { // page 0, 1, 2, 3

			sport_tx0_intr_event = sp_tx0_dma_int_sta & (1 << psport_init_dat->sport_hw_tx0_idx);

			if (sport_tx0_intr_event != 0x00) {
				pbuf = (u32)psport_adapter->ptx0_page_list[psport_init_dat->sport_hw_tx0_idx];

				//--------TX0 Data Process-----------

				if (psport_adapter->sport_tx0_irq_user_cb != NULL) {
					psport_adapter->sport_tx0_irq_user_cb(psport_adapter->sport_tx0_user_arg, (u8 *)pbuf);
				}

				//--------TX0 Data Process End--------

				hal_rtl_sport_clr_tx0_page_intr(psport_adapter, sport_tx0_intr_event);
				sp_tx0_dma_int_sta &= ~(sport_tx0_intr_event);
				psport_init_dat->sport_hw_tx0_idx += 1;
				if (psport_init_dat->sport_hw_tx0_idx == sp_page_num) {
					psport_init_dat->sport_hw_tx0_idx = 0;
				}
			}

			sport_tx1_intr_event = sp_tx1_dma_int_sta & (1 << psport_init_dat->sport_hw_tx1_idx);

			if (sport_tx1_intr_event != 0x00) {
				pbuf = (u32)psport_adapter->ptx1_page_list[psport_init_dat->sport_hw_tx1_idx];

				//--------TX1 Data Process-----------

				if (psport_adapter->sport_tx1_irq_user_cb != NULL) {
					psport_adapter->sport_tx1_irq_user_cb(psport_adapter->sport_tx1_user_arg, (u8 *)pbuf);
				}

				//--------TX1 Data Process End--------

				hal_rtl_sport_clr_tx1_page_intr(psport_adapter, sport_tx1_intr_event);
				sp_tx1_dma_int_sta &= ~(sport_tx1_intr_event);
				psport_init_dat->sport_hw_tx1_idx += 1;
				if (psport_init_dat->sport_hw_tx1_idx == sp_page_num) {
					psport_init_dat->sport_hw_tx1_idx = 0;
				}
			}

			sport_rx0_intr_event = sp_rx0_dma_int_sta & (1 << psport_init_dat->sport_hw_rx0_idx);

			if (sport_rx0_intr_event != 0x00) {
				pbuf = (u32)psport_adapter->prx0_page_list[psport_init_dat->sport_hw_rx0_idx];

				//--------RX0 Data Process-----------

				if (psport_adapter->dcache_memory_en == 1) {
					if (psport_adapter->dcache_invalidate_by_addr != NULL) {
						// D-Cache sync (Invalidate)
						psport_adapter->dcache_invalidate_by_addr((uint32_t *)pbuf,
								(int32_t)((((psport_reg->SPORT_SP_DMA_CON & SPORT_MASK_SP_PAGE_SIZE) >> SPORT_SHIFT_SP_PAGE_SIZE) + 1) << 2));
					} else {
						DBG_SPORT_ERR(" psport_adapter->dcache_invalidate_by_addr is null \r\n");
					}
				}

				if (psport_adapter->sport_rx0_irq_user_cb != NULL) {
					psport_adapter->sport_rx0_irq_user_cb(psport_adapter->sport_rx0_user_arg, (u8 *)pbuf);
				}

				//--------RX0 Data Process End--------

				hal_rtl_sport_clr_rx0_page_intr(psport_adapter, sport_rx0_intr_event);
				sp_rx0_dma_int_sta &= ~(sport_rx0_intr_event);
				psport_init_dat->sport_hw_rx0_idx += 1;
				if (psport_init_dat->sport_hw_rx0_idx == sp_page_num) {
					psport_init_dat->sport_hw_rx0_idx = 0;
				}
			}

			sport_rx1_intr_event = sp_rx1_dma_int_sta & (1 << psport_init_dat->sport_hw_rx1_idx);

			if (sport_rx1_intr_event != 0x00) {
				pbuf = (u32)psport_adapter->prx1_page_list[psport_init_dat->sport_hw_rx1_idx];

				//--------RX1 Data Process-----------

				if (psport_adapter->dcache_memory_en == 1) {
					if (psport_adapter->dcache_invalidate_by_addr != NULL) {
						// D-Cache sync (Invalidate)
						psport_adapter->dcache_invalidate_by_addr((uint32_t *)pbuf,
								(int32_t)((((psport_reg->SPORT_SP_DMA_CON & SPORT_MASK_SP_PAGE_SIZE) >> SPORT_SHIFT_SP_PAGE_SIZE) + 1) << 2));
					} else {
						DBG_SPORT_ERR(" psport_adapter->dcache_invalidate_by_addr is null \r\n");
					}
				}

				if (psport_adapter->sport_rx1_irq_user_cb != NULL) {
					psport_adapter->sport_rx1_irq_user_cb(psport_adapter->sport_rx1_user_arg, (u8 *)pbuf);
				}

				//--------RX1 Data Process End--------

				hal_rtl_sport_clr_rx1_page_intr(psport_adapter, sport_rx1_intr_event);
				sp_rx1_dma_int_sta &= ~(sport_rx1_intr_event);
				psport_init_dat->sport_hw_rx1_idx += 1;
				if (psport_init_dat->sport_hw_rx1_idx == sp_page_num) {
					psport_init_dat->sport_hw_rx1_idx = 0;
				}
			}

		}

	}

}

/**
 *  @brief To register a IRQ handler for SPORT.
 *
 *  @returns void
 */
void hal_rtl_sport_irq_reg(void)
{
	hal_irq_disable(SPORT_IRQn);
	__ISB();

	// Register SPORT common IRQ handler
	hal_irq_set_vector(SPORT_IRQn, (uint32_t)hal_rtl_sport_irqhandler_ram);
	hal_irq_clear_pending(SPORT_IRQn);
	hal_irq_enable(SPORT_IRQn);
}

/**
 *  @brief To un-register the SPORT IRQ handler.
 *
 *  @returns void
 */
void hal_rtl_sport_irq_unreg(void)
{
	// No any SPORT port has IRQ handler, so disable the common interrupt
	hal_irq_disable(SPORT_IRQn);
	__ISB();
}


/**
 *  @brief Initialize the SPORT hardware and turn on the SPORT
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_rtl_sport_init(hal_sport_adapter_t *psport_adapter)
{
	uint8_t i;

	//Check if SPORT has been registered.
	for (i = 0; i < SPORT_Max_Id; i++) {
		if (sport_group_adapter.psport_adapter[i] != NULL) {
			DBG_SPORT_WARN("The sport had been registered. \r\n");
			break;
		}
	}

	hal_rtl_sport_irq_reg();

	//Set IRQ priority
	hal_irq_set_priority(SPORT_IRQn, SPORT_IRQPri);

	psport_adapter->base_addr = (SPORT_Type *)SPORT_REG_BASE;

	sport_group_adapter.psport_adapter[SPORT_id] = psport_adapter;

	//hal_rtl_sys_sport_src_sel(SPORT_40MHZ);
	hal_sys_set_clk(SPORT_SYS, SPORT_40MHZ);

	hal_sys_peripheral_en(SPORT_SYS, ENABLE);

	//Reg dcache app
	psport_adapter->dcache_clean_by_addr = hal_cache_stubs.dcache_clean_by_addr;
	psport_adapter->dcache_invalidate_by_addr = hal_cache_stubs.dcache_invalidate_by_addr;

	//Initial
	psport_adapter->tx_channel_factor = 1;
	psport_adapter->rx_channel_factor = 1;
	psport_adapter->dma_err_sta = 0x00;
	psport_adapter->dcache_memory_en = 1;

	hal_rtl_sport_reset(psport_adapter);

	return 0;

}

/**
 *  @brief De-initialize of the SPORT hardware and turn off the SPORT.
 *
 *  @param[in] pecdsa_adapter The SPORT adapter.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_rtl_sport_deinit(hal_sport_adapter_t *psport_adapter)
{
	if (psport_adapter == 0) {
		DBG_SPORT_WARN("hal_rtl_sport_deinit: Null Pointer\r\n");
		return HAL_ERR_PARA;
	}

	hal_rtl_sport_reset(psport_adapter);

	/*SPORT Interrupt DeInitialization*/
	hal_rtl_sport_irq_unreg();

	hal_sys_peripheral_en(SPORT_SYS, DISABLE);

	sport_group_adapter.psport_adapter[SPORT_id] = NULL;

	return 0;
}

/**
 *  @brief Reset the SPORT module.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns void
 */
void hal_rtl_sport_reset(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	psport_adapter->init_dat.sport_tx0_idx = 0x00;
	psport_adapter->init_dat.sport_rx0_idx = 0x00;
	psport_adapter->init_dat.sport_tx1_idx = 0x00;
	psport_adapter->init_dat.sport_rx1_idx = 0x00;
	psport_adapter->init_dat.sport_hw_tx0_idx = 0x00;
	psport_adapter->init_dat.sport_hw_rx0_idx = 0x00;
	psport_adapter->init_dat.sport_hw_tx1_idx = 0x00;
	psport_adapter->init_dat.sport_hw_rx1_idx = 0x00;
	psport_adapter->dma_err_sta = 0x00;

	psport_reg->SPORT_SP_CON |= SPORT_BIT_SP_RESET;
	psport_reg->SPORT_SP_CON &= ~(SPORT_BIT_SP_RESET);
}

/**
 *  @brief Reset the SPORT TX FIFO.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns void
 */
void hal_rtl_sport_reset_tx_fifo(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	psport_reg->SPORT_SP_FIFO_EN_CLK_CON |= SPORT_BIT_SP_TX_FIFO_RESET;
	psport_reg->SPORT_SP_FIFO_EN_CLK_CON &= ~(SPORT_BIT_SP_TX_FIFO_RESET);
}

/**
 *  @brief Reset the SPORT RX FIFO.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns void
 */
void hal_rtl_sport_reset_rx_fifo(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	psport_reg->SPORT_SP_FIFO_EN_CLK_CON |= SPORT_BIT_SP_RX_FIFO_RESET;
	psport_reg->SPORT_SP_FIFO_EN_CLK_CON &= ~(SPORT_BIT_SP_RX_FIFO_RESET);
}

/**
 *  @brief Reset the SPORT bclk.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns void
 */
void hal_rtl_sport_bclk_reset(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	psport_reg->SPORT_SP_FIFO_EN_CLK_CON |= SPORT_BIT_SP_BCLK_RESET;
	psport_reg->SPORT_SP_FIFO_EN_CLK_CON &= ~(SPORT_BIT_SP_BCLK_RESET);
}

/**
 *  @brief Reset the SPORT DMA.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns void
 */
void hal_rtl_sport_dma_reset(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	psport_reg->SPORT_SP_DMA_CON &= ~(SPORT_BIT_SP_DMA_RSTN);
	psport_reg->SPORT_SP_DMA_CON |= SPORT_BIT_SP_DMA_RSTN;
}

/**
 *  @brief Clean the SPORT TX page own.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns void
 */
void hal_rtl_sport_clean_tx_page_own(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	psport_reg->SPORT_SP_TX_PAGE_OWN = 0x00;
}

/**
 *  @brief Clean the SPORT RX page own.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns void
 */
void hal_rtl_sport_clean_rx_page_own(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	psport_reg->SPORT_SP_RX_PAGE_OWN = 0x00;
}

/**
 *  @brief  Set the master or slave mode.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] dev_mode Select the master or slave mode.
 *
 *  @returns void
 */
void hal_rtl_sport_set_master(hal_sport_adapter_t *psport_adapter, sport_dev_mode_t dev_mode)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_CON;
	temp_reg &= ~(SPORT_BIT_SP_SLAVE_DATA_SEL);
	temp_reg |= (dev_mode << SPORT_SHIFT_SP_SLAVE_DATA_SEL);
	psport_reg->SPORT_SP_CON = temp_reg;
}

/**
 *  @brief Control the SPORT loopback mode.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] loopback_en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_rtl_sport_set_loopback(hal_sport_adapter_t *psport_adapter, BOOL loopback_en)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_CON;
	temp_reg &= ~(SPORT_BIT_SP_LOOPBACK);
	temp_reg |= (loopback_en << SPORT_SHIFT_SP_LOOPBACK);
	psport_reg->SPORT_SP_CON = temp_reg;
}

/**
 *  @brief  Set the DMA or FIFO mode.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] wk_mode Select the DMA or FIFO mode.
 *
 *  @returns void
 */
void hal_rtl_sport_mode(hal_sport_adapter_t *psport_adapter, sport_wk_mode_t wk_mode)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	psport_adapter->sport_mode_record = wk_mode;

	temp_reg = psport_reg->SPORT_SP_CON;
	temp_reg &= ~(SPORT_BIT_SP_MCU_CTL_MODE);
	temp_reg |= (wk_mode << SPORT_SHIFT_SP_MCU_CTL_MODE);
	psport_reg->SPORT_SP_CON = temp_reg;
}

/**
 *  @brief Control the tx data format of the sport. Don't support the TDM mode.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] sport_sel_ch  Set the relation between the data and channel.
 *                      -00: L/R.
 *                      -01: R/L.
 *                      -10: L/L.
 *                      -11: R/R.
 *
 *  @returns void
 */
void hal_rtl_sport_tx_ch(hal_sport_adapter_t *psport_adapter, sport_sel_ch_t sport_sel_ch)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_CON;
	temp_reg &= ~(SPORT_MASK_SP_SEL_I2S_TX_CH);
	temp_reg |= (sport_sel_ch << SPORT_SHIFT_SP_SEL_I2S_TX_CH);
	psport_reg->SPORT_SP_CON = temp_reg;
}

/**
 *  @brief Control the rx data format of the sport. Don't support the TDM mode.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] sport_sel_ch  Set the relation between the data and channel.
 *                      -00: L/R.
 *                      -01: R/L.
 *                      -10: L/L.
 *                      -11: R/R.
 *
 *  @returns void
 */
void hal_rtl_sport_rx_ch(hal_sport_adapter_t *psport_adapter, sport_sel_ch_t sport_sel_ch)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_CON;
	temp_reg &= ~(SPORT_MASK_SP_SEL_I2S_RX_CH);
	temp_reg |= (sport_sel_ch << SPORT_SHIFT_SP_SEL_I2S_RX_CH);
	psport_reg->SPORT_SP_CON = temp_reg;
}

/**
 *  @brief Set the format of the SPORT.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] sport_format  Select the interface format.
 *
 *  @returns void
 */
void hal_rtl_sport_format(hal_sport_adapter_t *psport_adapter, sport_format_t sport_format)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_CON;
	temp_reg &= ~(SPORT_MASK_SP_DATA_FORMAT_SEL_TX);
	temp_reg |= (sport_format << SPORT_SHIFT_SP_DATA_FORMAT_SEL_TX);
	psport_reg->SPORT_SP_CON = temp_reg;
}

/**
 *  @brief Set tx and rx are the same format. Only support I2S and PCM_A format.
 *         The sample rate clock of SD_I is according to LRCK_RX. Need to set rx rate.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] rx_en 1: Tx and rx are the same, 0: Need to set rx format and rate.
 *
 *  @returns void
 */
void hal_rtl_sport_rx_same_format(hal_sport_adapter_t *psport_adapter, BOOL rx_en)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_FORM_CON;
	temp_reg &= ~(SPORT_BIT_SP_TRX_SAME_FS);
	temp_reg |= (rx_en << SPORT_SHIFT_SP_TRX_SAME_FS);
	psport_reg->SPORT_SP_FORM_CON = temp_reg;
}

/**
 *  @brief Set the rx format of the SPORT.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] sport_format  Select the interface format.
 *
 *  @returns void
 */
void hal_rtl_sport_rx_format(hal_sport_adapter_t *psport_adapter, sport_format_t sport_format)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_FORM_CON;
	temp_reg &= ~(SPORT_MASK_SP_DATA_FORMAT_SEL_RX);
	temp_reg |= (sport_format << SPORT_SHIFT_SP_DATA_FORMAT_SEL_RX);
	psport_reg->SPORT_SP_FORM_CON = temp_reg;
}


/**
 *  @brief Select tx0 mono or stereo of the SPORT.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] type_sel  Select the mono and stereo. 0:stereo, 1:mono
 *
 *  @returns void
 */
void hal_rtl_sport_tx0_mono(hal_sport_adapter_t *psport_adapter, BOOL type_sel)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_CON;
	temp_reg &= ~(SPORT_BIT_SP_EN_I2S_MONO_TX_0);
	temp_reg |= (type_sel << SPORT_SHIFT_SP_EN_I2S_MONO_TX_0);
	psport_reg->SPORT_SP_CON = temp_reg;
}

/**
 *  @brief Select tx1 mono or stereo of the SPORT.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] type_sel  Select the mono and stereo. 0:stereo, 1:mono
 *
 *  @returns void
 */
void hal_rtl_sport_tx1_mono(hal_sport_adapter_t *psport_adapter, BOOL type_sel)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_TX1_RX1_FORM_CON;
	temp_reg &= ~(SPORT_BIT_SP_EN_I2S_MONO_TX_1);
	temp_reg |= (type_sel << SPORT_SHIFT_SP_EN_I2S_MONO_TX_1);
	psport_reg->SPORT_SP_TX1_RX1_FORM_CON = temp_reg;
}

/**
 *  @brief Set tx and rx are the same mono or stereo type .
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] rx_en 1: Tx and rx are the same, 0: Need to set rx.
 *
 *  @returns void
 */
void hal_rtl_sport_rx_same_mono_stereo(hal_sport_adapter_t *psport_adapter, BOOL rx_en)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_FORM_CON;
	temp_reg &= ~(SPORT_BIT_SP_TRX_SAME_CH);
	temp_reg |= (rx_en << SPORT_SHIFT_SP_TRX_SAME_CH);
	psport_reg->SPORT_SP_FORM_CON = temp_reg;
}

/**
 *  @brief Select rx0 mono or stereo of the SPORT.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] type_sel  Select the mono and stereo. 0:stereo, 1:mono
 *
 *  @returns void
 */
void hal_rtl_sport_rx0_mono(hal_sport_adapter_t *psport_adapter, BOOL type_sel)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_FORM_CON;
	temp_reg &= ~(SPORT_BIT_SP_EN_I2S_MONO_RX_0);
	temp_reg |= (type_sel << SPORT_SHIFT_SP_EN_I2S_MONO_RX_0);
	psport_reg->SPORT_SP_FORM_CON = temp_reg;
}

/**
 *  @brief Select rx1 mono or stereo of the SPORT.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] type_sel  Select the mono and stereo. 0:stereo, 1:mono
 *
 *  @returns void
 */
void hal_rtl_sport_rx1_mono(hal_sport_adapter_t *psport_adapter, BOOL type_sel)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_TX1_RX1_FORM_CON;
	temp_reg &= ~(SPORT_BIT_SP_EN_I2S_MONO_RX_1);
	temp_reg |= (type_sel << SPORT_SHIFT_SP_EN_I2S_MONO_RX_1);
	psport_reg->SPORT_SP_TX1_RX1_FORM_CON = temp_reg;
}

/**
 *  @brief Select tx0 data length of the SPORT.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] dl  Select the data length.
 *
 *  @returns void
 */
void hal_rtl_sport_tx0_data_length(hal_sport_adapter_t *psport_adapter, sport_dl_t dl)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_CON;
	temp_reg &= ~(SPORT_MASK_SP_DATA_LEN_SEL_TX_0);
	temp_reg |= (dl << SPORT_SHIFT_SP_DATA_LEN_SEL_TX_0);
	psport_reg->SPORT_SP_CON = temp_reg;
}

/**
 *  @brief Select tx1 data length of the SPORT.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] dl  Select the data length.
 *
 *  @returns void
 */
void hal_rtl_sport_tx1_data_length(hal_sport_adapter_t *psport_adapter, sport_dl_t dl)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_TX1_RX1_FORM_CON;
	temp_reg &= ~(SPORT_MASK_SP_DATA_LEN_SEL_TX_1);
	temp_reg |= (dl << SPORT_SHIFT_SP_DATA_LEN_SEL_TX_1);
	psport_reg->SPORT_SP_TX1_RX1_FORM_CON = temp_reg;
}

/**
 *  @brief Set tx and rx are the same data length .
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] rx_en 1: Tx and rx are the same, 0: Need to set rx.
 *
 *  @returns void
 */
void hal_rtl_sport_rx_same_data_length(hal_sport_adapter_t *psport_adapter, BOOL rx_en)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_FORM_CON;
	temp_reg &= ~(SPORT_BIT_SP_TRX_SAME_LENGTH);
	temp_reg |= (rx_en << SPORT_SHIFT_SP_TRX_SAME_LENGTH);
	psport_reg->SPORT_SP_FORM_CON = temp_reg;
}

/**
 *  @brief Select rx0 data length of the SPORT.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] dl  Select the data length.
 *
 *  @returns void
 */
void hal_rtl_sport_rx0_data_length(hal_sport_adapter_t *psport_adapter, sport_dl_t dl)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_FORM_CON;
	temp_reg &= ~(SPORT_MASK_SP_DATA_LEN_SEL_RX_0);
	temp_reg |= (dl << SPORT_SHIFT_SP_DATA_LEN_SEL_RX_0);
	psport_reg->SPORT_SP_FORM_CON = temp_reg;
}

/**
 *  @brief Select rx1 data length of the SPORT.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] dl  Select the data length.
 *
 *  @returns void
 */
void hal_rtl_sport_rx1_data_length(hal_sport_adapter_t *psport_adapter, sport_dl_t dl)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_TX1_RX1_FORM_CON;
	temp_reg &= ~(SPORT_MASK_SP_DATA_LEN_SEL_RX_1);
	temp_reg |= (dl << SPORT_SHIFT_SP_DATA_LEN_SEL_RX_1);
	psport_reg->SPORT_SP_TX1_RX1_FORM_CON = temp_reg;
}

/**
 *  @brief Select tx channel length of the SPORT.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] dl  Select the channel length.
 *
 *  @returns void
 */
void hal_rtl_sport_tx_channel_length(hal_sport_adapter_t *psport_adapter, sport_cl_t cl)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_FORM_CON;
	temp_reg &= ~(SPORT_MASK_SP_CH_LEN_SEL_TX);
	temp_reg |= (cl << SPORT_SHIFT_SP_CH_LEN_SEL_TX);
	psport_reg->SPORT_SP_FORM_CON = temp_reg;
}

/**
 *  @brief Set tx and rx are the same channel length .
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] rx_en 1 Tx and rx are the same, 0: Need to set rx.
 *
 *  @returns void
 */
void hal_rtl_sport_rx_same_channel_length(hal_sport_adapter_t *psport_adapter, BOOL rx_en)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_FORM_CON;
	temp_reg &= ~(SPORT_BIT_SP_TRX_SAME_CH_LEN);
	temp_reg |= (rx_en << SPORT_SHIFT_SP_TRX_SAME_CH_LEN);
	psport_reg->SPORT_SP_FORM_CON = temp_reg;
}

/**
 *  @brief Select rx channel length of the SPORT.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] dl  Select the channel length.
 *
 *  @returns void
 */
void hal_rtl_sport_rx_channel_length(hal_sport_adapter_t *psport_adapter, sport_cl_t cl)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_FORM_CON;
	temp_reg &= ~(SPORT_MASK_SP_CH_LEN_SEL_RX);
	temp_reg |= (cl << SPORT_SHIFT_SP_CH_LEN_SEL_RX);
	psport_reg->SPORT_SP_FORM_CON = temp_reg;
}

/**
 *  @brief Set the sport tx rate.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] sport_sample_rate  Sample rate.
 *
 *  @returns void
 */
void hal_rtl_sport_tx_rate(hal_sport_adapter_t *psport_adapter, sport_rate_t sport_sample_rate)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;
	u32 mi = 625;
	u32 ni = 8;

	switch (sport_sample_rate) {

	case R_1KHZ:
		mi = 625;
		ni = 1;
		break;

	case R_4KHZ:
		mi = 625;
		ni = 4;
		break;

	case R_8KHZ:
		mi = 625;
		ni = 8;
		break;

	case R_16KHZ:
		mi = 625;
		ni = 16;
		break;

	case R_32KHZ:
		mi = 625;
		ni = 32;
		break;

	case R_44p1KHZ:
		mi = 411;
		ni = 29;
		break;

	case R_48KHZ:
		mi = 625;
		ni = 48;
		break;

	case R_88p2KHZ:
		mi = 411;
		ni = 58;
		break;

	case R_96KHZ:
		mi = 625;
		ni = 96;
		break;

	case R_12KHZ:
		mi = 625;
		ni = 12;
		break;

	case R_24KHZ:
		mi = 625;
		ni = 24;
		break;

	case R_192KHZ:
		mi = 625;
		ni = 192;
		break;

	case R_384KHZ:
		mi = 625;
		ni = 384;
		break;

	case R_7p35KHZ:
		mi = 85;
		ni = 1;
		break;

	case R_11p025KHZ:
		mi = 907;
		ni = 16;
		break;

	case R_14p7KHZ:
		mi = 85;
		ni = 2;
		break;

	case R_22p05KHZ:
		mi = 822;
		ni = 29;
		break;

	case R_29p4KHZ:
		mi = 659;
		ni = 31;
		break;

	case R_58p8KHZ:
		mi = 946;
		ni = 89;
		break;

	case R_176p4KHZ:
		mi = 411;
		ni = 116;
		break;

	default :

		break;

	}

	ni = ni * psport_adapter->tx_ch_len_factor;
	mi = mi * 8;

	//temp_reg = psport_reg->SPORT_SP_TX_FRA_DIV;
	//temp_reg &= ~(SPORT_MASK_SP_TX_MI | SPORT_MASK_SP_TX_NI | SPORT_BIT_SP_TX_MI_NI_UPDATE);
	temp_reg = 0x00;
	temp_reg |= (mi << SPORT_SHIFT_SP_TX_MI) | ((ni * psport_adapter->tx_channel_factor) << SPORT_SHIFT_SP_TX_NI);

	psport_reg->SPORT_SP_FIFO_EN_CLK_CON |= SPORT_BIT_SP_BCLK_RESET;
	psport_reg->SPORT_SP_TX_FRA_DIV = temp_reg;
	psport_reg->SPORT_SP_TX_FRA_DIV = (temp_reg | SPORT_BIT_SP_TX_MI_NI_UPDATE);
	psport_reg->SPORT_SP_FIFO_EN_CLK_CON &= ~(SPORT_BIT_SP_BCLK_RESET);

}

/**
 *  @brief Set the sport rx rate.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] sport_sample_rate  Sample rate.
 *
 *  @returns void
 */
void hal_rtl_sport_rx_rate(hal_sport_adapter_t *psport_adapter, sport_rate_t sport_sample_rate)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;
	u32 mi = 625;
	u32 ni = 8;

	switch (sport_sample_rate) {

	case R_1KHZ:
		mi = 625;
		ni = 1;
		break;

	case R_4KHZ:
		mi = 625;
		ni = 4;
		break;

	case R_8KHZ:
		mi = 625;
		ni = 8;
		break;

	case R_16KHZ:
		mi = 625;
		ni = 16;
		break;

	case R_32KHZ:
		mi = 625;
		ni = 32;
		break;

	case R_44p1KHZ:
		mi = 411;
		ni = 29;
		break;

	case R_48KHZ:
		mi = 625;
		ni = 48;
		break;

	case R_88p2KHZ:
		mi = 411;
		ni = 58;
		break;

	case R_96KHZ:
		mi = 625;
		ni = 96;
		break;

	case R_12KHZ:
		mi = 625;
		ni = 12;
		break;

	case R_24KHZ:
		mi = 625;
		ni = 24;
		break;

	case R_192KHZ:
		mi = 625;
		ni = 192;
		break;

	case R_384KHZ:
		mi = 625;
		ni = 384;
		break;

	case R_7p35KHZ:
		mi = 85;
		ni = 1;
		break;

	case R_11p025KHZ:
		mi = 907;
		ni = 16;
		break;

	case R_14p7KHZ:
		mi = 85;
		ni = 2;
		break;

	case R_22p05KHZ:
		mi = 822;
		ni = 29;
		break;

	case R_29p4KHZ:
		mi = 659;
		ni = 31;
		break;

	case R_58p8KHZ:
		mi = 946;
		ni = 89;
		break;

	case R_176p4KHZ:
		mi = 411;
		ni = 116;
		break;

	default :

		break;

	}

	ni = ni * psport_adapter->rx_ch_len_factor;
	mi = mi * 8;

	//temp_reg = psport_reg->SPORT_SP_RX_FRA_DIV;
	//temp_reg &= ~(SPORT_MASK_SP_RX_MI | SPORT_MASK_SP_RX_NI | SPORT_BIT_SP_RX_MI_NI_UPDATE);
	temp_reg = 0x00;
	temp_reg |= (mi << SPORT_SHIFT_SP_RX_MI) | ((ni * psport_adapter->rx_channel_factor) << SPORT_SHIFT_SP_RX_NI);
	psport_reg->SPORT_SP_FIFO_EN_CLK_CON |= SPORT_BIT_SP_BCLK_RESET;
	psport_reg->SPORT_SP_RX_FRA_DIV = temp_reg;
	psport_reg->SPORT_SP_RX_FRA_DIV = (temp_reg | SPORT_BIT_SP_RX_MI_NI_UPDATE);
	psport_reg->SPORT_SP_FIFO_EN_CLK_CON &= ~(SPORT_BIT_SP_BCLK_RESET);

}

/**
 *  @brief Set the MSB or LBS first of tx data.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] tx0_ml  Set the MSB or LBS first for FIFO_0.
 *  @param[in] tx1_ml  Set the MSB or LBS first for FIFO_1.
 *
 *  @returns void
 */
void hal_rtl_sport_tx_data_dir(hal_sport_adapter_t *psport_adapter, sport_ml_t tx0_ml, sport_ml_t tx1_ml)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_CON;
	temp_reg &= ~(SPORT_BIT_SP_TX_LSB_FIRST_0);
	temp_reg |= (tx0_ml << SPORT_SHIFT_SP_TX_LSB_FIRST_0);
	psport_reg->SPORT_SP_CON = temp_reg;

	temp_reg = psport_reg->SPORT_SP_TX1_RX1_DAT_CON;
	temp_reg &= ~(SPORT_BIT_SP_TX_LSB_FIRST_1);
	temp_reg |= (tx1_ml << SPORT_SHIFT_SP_TX_LSB_FIRST_1);
	psport_reg->SPORT_SP_TX1_RX1_DAT_CON = temp_reg;
}

/**
 *  @brief Set the MSB or LBS first of rx data.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] rx0_ml  Set the MSB or LBS first for FIFO_0.
 *  @param[in] rx1_ml  Set the MSB or LBS first for FIFO_1.
 *
 *  @returns void
 */
void hal_rtl_sport_rx_data_dir(hal_sport_adapter_t *psport_adapter, sport_ml_t rx0_ml, sport_ml_t rx1_ml)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_CON;
	temp_reg &= ~(SPORT_BIT_SP_RX_LSB_FIRST_0);
	temp_reg |= (rx0_ml << SPORT_SHIFT_SP_RX_LSB_FIRST_0);
	psport_reg->SPORT_SP_CON = temp_reg;

	temp_reg = psport_reg->SPORT_SP_TX1_RX1_DAT_CON;
	temp_reg &= ~(SPORT_BIT_SP_RX_LSB_FIRST_1);
	temp_reg |= (rx1_ml << SPORT_SHIFT_SP_RX_LSB_FIRST_1);
	psport_reg->SPORT_SP_TX1_RX1_DAT_CON = temp_reg;
}

/**
 *  @brief Swap the L/R of tx data.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] tx0_en  Enable the swap for FIFO_0.
 *  @param[in] tx1_en  Enable the swap for FIFO_1.
 *
 *  @returns void
 */
void hal_rtl_sport_tx_lr_swap(hal_sport_adapter_t *psport_adapter, BOOL tx0_en, BOOL tx1_en)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_FIFO_EN_CLK_CON;
	temp_reg &= ~(SPORT_BIT_SP_TX_SRC_LR_SWAP_0);
	temp_reg |= (tx0_en << SPORT_SHIFT_SP_TX_SRC_LR_SWAP_0);
	psport_reg->SPORT_SP_FIFO_EN_CLK_CON = temp_reg;

	temp_reg = psport_reg->SPORT_SP_TX1_RX1_DAT_CON;
	temp_reg &= ~(SPORT_BIT_SP_TX_SRC_LR_SWAP_1);
	temp_reg |= (tx1_en << SPORT_SHIFT_SP_TX_SRC_LR_SWAP_1);
	psport_reg->SPORT_SP_TX1_RX1_DAT_CON = temp_reg;
}

/**
 *  @brief Swap the L/R of rx data.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] rx0_en  Enable the swap for FIFO_0.
 *  @param[in] rx1_en  Enable the swap for FIFO_1.
 *
 *  @returns void
 */
void hal_rtl_sport_rx_lr_swap(hal_sport_adapter_t *psport_adapter, BOOL rx0_en, BOOL rx1_en)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_FIFO_EN_CLK_CON;
	temp_reg &= ~(SPORT_BIT_SP_RX_SNK_LR_SWAP_0);
	temp_reg |= (rx0_en << SPORT_SHIFT_SP_RX_SNK_LR_SWAP_0);
	psport_reg->SPORT_SP_FIFO_EN_CLK_CON = temp_reg;

	temp_reg = psport_reg->SPORT_SP_TX1_RX1_DAT_CON;
	temp_reg &= ~(SPORT_BIT_SP_RX_SNK_LR_SWAP_1);
	temp_reg |= (rx1_en << SPORT_SHIFT_SP_RX_SNK_LR_SWAP_1);
	psport_reg->SPORT_SP_TX1_RX1_DAT_CON = temp_reg;
}

/**
 *  @brief Swap the byte of tx data.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] tx0_en  Enable the swap for FIFO_0.
 *  @param[in] tx1_en  Enable the swap for FIFO_1.
 *
 *  @returns void
 */
void hal_rtl_sport_tx_byte_swap(hal_sport_adapter_t *psport_adapter, BOOL tx0_en, BOOL tx1_en)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_FIFO_EN_CLK_CON;
	temp_reg &= ~(SPORT_BIT_SP_TX_SRC_BYTE_SWAP_0);
	temp_reg |= (tx0_en << SPORT_SHIFT_SP_TX_SRC_BYTE_SWAP_0);
	psport_reg->SPORT_SP_FIFO_EN_CLK_CON = temp_reg;

	temp_reg = psport_reg->SPORT_SP_TX1_RX1_DAT_CON;
	temp_reg &= ~(SPORT_BIT_SP_TX_SRC_BYTE_SWAP_1);
	temp_reg |= (tx1_en << SPORT_SHIFT_SP_TX_SRC_BYTE_SWAP_1);
	psport_reg->SPORT_SP_TX1_RX1_DAT_CON = temp_reg;
}

/**
 *  @brief Swap the byte of rx data.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] rx0_en  Enable the swap for FIFO_0.
 *  @param[in] rx1_en  Enable the swap for FIFO_1.
 *
 *  @returns void
 */
void hal_rtl_sport_rx_byte_swap(hal_sport_adapter_t *psport_adapter, BOOL rx0_en, BOOL rx1_en)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_FIFO_EN_CLK_CON;
	temp_reg &= ~(SPORT_BIT_SP_RX_SNK_BYTE_SWAP_0);
	temp_reg |= (rx0_en << SPORT_SHIFT_SP_RX_SNK_BYTE_SWAP_0);
	psport_reg->SPORT_SP_FIFO_EN_CLK_CON = temp_reg;

	temp_reg = psport_reg->SPORT_SP_TX1_RX1_DAT_CON;
	temp_reg &= ~(SPORT_BIT_SP_RX_SNK_BYTE_SWAP_1);
	temp_reg |= (rx1_en << SPORT_SHIFT_SP_RX_SNK_BYTE_SWAP_1);
	psport_reg->SPORT_SP_TX1_RX1_DAT_CON = temp_reg;
}

/**
 *  @brief Set the sport bclk inverse.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] inverse_en  Make bclk inverse.
 *
 *  @returns void
 */
void hal_rtl_sport_bclk_inverse(hal_sport_adapter_t *psport_adapter, BOOL inverse_en)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_FORM_CON;
	temp_reg &= ~(SPORT_BIT_SP_BCLK_OUT_INVERSE);
	temp_reg |= (inverse_en << SPORT_SHIFT_SP_BCLK_OUT_INVERSE);
	psport_reg->SPORT_SP_FORM_CON = temp_reg;

#if 1
	temp_reg = psport_reg->SPORT_SP_CON;
	temp_reg &= ~(SPORT_BIT_SP_INV_I2S_SCLK);
	temp_reg |= (inverse_en << SPORT_SHIFT_SP_INV_I2S_SCLK);
	psport_reg->SPORT_SP_CON = temp_reg;
#else
	temp_reg = psport_reg->SPORT_SP_CON;
	temp_reg &= ~(SPORT_BIT_SP_TX_INV_I2S_SCLK);
	temp_reg |= (inverse_en << SPORT_SHIFT_SP_TX_INV_I2S_SCLK);
	psport_reg->SPORT_SP_CON = temp_reg;

	temp_reg = psport_reg->SPORT_SP_CON;
	temp_reg &= ~(SPORT_BIT_SP_RX_INV_I2S_SCLK);
	temp_reg |= (inverse_en << SPORT_SHIFT_SP_RX_INV_I2S_SCLK);
	psport_reg->SPORT_SP_CON = temp_reg;
#endif

}

/**
 *  @brief Set the sport mclk.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] sport_mclk  Select the mclk rate.
 *  @param[in] mclk_en  Enable mclk.
 *
 *  @returns void
 */
void hal_rtl_sport_set_mclk(hal_sport_adapter_t *psport_adapter, sport_mclk_t sport_mclk, BOOL mclk_en)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_CON;
	temp_reg &= ~(SPORT_MASK_SP_MCLK_SEL);
	temp_reg |= (sport_mclk << SPORT_SHIFT_SP_MCLK_SEL);
	psport_reg->SPORT_SP_CON = temp_reg;

	temp_reg = psport_reg->SPORT_SP_FIFO_EN_CLK_CON;
	temp_reg &= ~(SPORT_BIT_SP_ENABLE_MCLK);
	temp_reg |= (mclk_en << SPORT_SHIFT_SP_ENABLE_MCLK);
	psport_reg->SPORT_SP_FIFO_EN_CLK_CON = temp_reg;

}

/**
 *  @brief Select the sport tx tdm mode
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] sport_tdm  Select the tdm mode.
 *
 *  @returns void
 */
void hal_rtl_sport_sel_tx_tdm(hal_sport_adapter_t *psport_adapter, sport_tdm_t sport_tdm)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_CON;
	temp_reg &= ~(SPORT_MASK_SP_TDM_MODE_SEL_TX);
	temp_reg |= (sport_tdm << SPORT_SHIFT_SP_TDM_MODE_SEL_TX);
	psport_reg->SPORT_SP_CON = temp_reg;

}

/**
 *  @brief Select the sport rx tdm mode
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] sport_tdm  Select the tdm mode.
 *
 *  @returns void
 */
void hal_rtl_sport_sel_rx_tdm(hal_sport_adapter_t *psport_adapter, sport_tdm_t sport_tdm)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_CON;
	temp_reg &= ~(SPORT_MASK_SP_TDM_MODE_SEL_RX);
	temp_reg |= (sport_tdm << SPORT_SHIFT_SP_TDM_MODE_SEL_RX);
	psport_reg->SPORT_SP_CON = temp_reg;

}

/**
 *  @brief Set the sport data consumption of TX_FIFO_0
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] sport_layer  Set the number of consumption layers. One layer is 32 bits.
 *
 *  @returns void
 */
void hal_rtl_sport_set_tx0_consum(hal_sport_adapter_t *psport_adapter, u8 sport_layer)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_ERR_CNT_CON;
	temp_reg &= ~(SPORT_MASK_SP_TX_DEPTH_THR_0);
	temp_reg |= (sport_layer << SPORT_SHIFT_SP_TX_DEPTH_THR_0);
	psport_reg->SPORT_SP_ERR_CNT_CON = temp_reg;

}

/**
 *  @brief Set the sport data consumption of TX_FIFO_1
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] sport_layer  Set the number of consumption layers. One layer is 32 bits.
 *
 *  @returns void
 */
void hal_rtl_sport_set_tx1_consum(hal_sport_adapter_t *psport_adapter, u8 sport_layer)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_ERR_CNT_CON;
	temp_reg &= ~(SPORT_MASK_SP_TX_DEPTH_THR_1);
	temp_reg |= (sport_layer << SPORT_SHIFT_SP_TX_DEPTH_THR_1);
	psport_reg->SPORT_SP_ERR_CNT_CON = temp_reg;

}

/**
 *  @brief Set the sport data consumption of RX_FIFO_0
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] sport_layer  Set the number of consumption layers. One layer is 32 bits.
 *
 *  @returns void
 */
void hal_rtl_sport_set_rx0_consum(hal_sport_adapter_t *psport_adapter, u8 sport_layer)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_ERR_CNT_CON;
	temp_reg &= ~(SPORT_MASK_SP_RX_DEPTH_THR_0);
	temp_reg |= (sport_layer << SPORT_SHIFT_SP_RX_DEPTH_THR_0);
	psport_reg->SPORT_SP_ERR_CNT_CON = temp_reg;

}

/**
 *  @brief Set the sport data consumption of RX_FIFO_1
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] sport_layer  Set the number of consumption layers. One layer is 32 bits.
 *
 *  @returns void
 */
void hal_rtl_sport_set_rx1_consum(hal_sport_adapter_t *psport_adapter, u8 sport_layer)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_ERR_CNT_CON;
	temp_reg &= ~(SPORT_MASK_SP_RX_DEPTH_THR_1);
	temp_reg |= (sport_layer << SPORT_SHIFT_SP_RX_DEPTH_THR_1);
	psport_reg->SPORT_SP_ERR_CNT_CON = temp_reg;

}

/**
 *  @brief Control the sport tx FIFO_0.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] ch1ch0_en  Enable channel 0 and 1 data path for FIFO_0.
 *  @param[in] ch2ch3_en  Enable channel 2 and 3 data path for FIFO_0.
 *
 *  @returns void
 */
void hal_rtl_sport_tx_fifo_0(hal_sport_adapter_t *psport_adapter, BOOL ch1ch0_en, BOOL ch2ch3_en)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_FIFO_EN_CLK_CON;
	temp_reg &= ~(SPORT_BIT_SP_TX_FIFO_0_CH0_1_EN | SPORT_BIT_SP_TX_FIFO_0_CH2_3_EN);
	temp_reg |= (ch1ch0_en << SPORT_SHIFT_SP_TX_FIFO_0_CH0_1_EN) | (ch2ch3_en << SPORT_SHIFT_SP_TX_FIFO_0_CH2_3_EN);
	psport_reg->SPORT_SP_FIFO_EN_CLK_CON = temp_reg;

}

/**
 *  @brief Control the sport tx FIFO_1.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] ch4ch5_en  Enable channel 4 and 5 data path for FIFO_1.
 *  @param[in] ch6ch7_en  Enable channel 6 and 7 data path for FIFO_1.
 *
 *  @returns void
 */
void hal_rtl_sport_tx_fifo_1(hal_sport_adapter_t *psport_adapter, BOOL ch4ch5_en, BOOL ch6ch7_en)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_FIFO_EN_CLK_CON;
	temp_reg &= ~(SPORT_BIT_SP_TX_FIFO_1_CH4_5_EN | SPORT_BIT_SP_TX_FIFO_1_CH6_7_EN);
	temp_reg |= (ch4ch5_en << SPORT_SHIFT_SP_TX_FIFO_1_CH4_5_EN) | (ch6ch7_en << SPORT_SHIFT_SP_TX_FIFO_1_CH6_7_EN);
	psport_reg->SPORT_SP_FIFO_EN_CLK_CON = temp_reg;

}

/**
 *  @brief Control the sport rx FIFO_0.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] ch1ch0_en  Enable channel 0 and 1 data path for FIFO_0.
 *  @param[in] ch2ch3_en  Enable channel 2 and 3 data path for FIFO_0.
 *
 *  @returns void
 */
void hal_rtl_sport_rx_fifo_0(hal_sport_adapter_t *psport_adapter, BOOL ch1ch0_en, BOOL ch2ch3_en)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_FIFO_EN_CLK_CON;
	temp_reg &= ~(SPORT_BIT_SP_RX_FIFO_0_CH0_1_EN | SPORT_BIT_SP_RX_FIFO_0_CH2_3_EN);
	temp_reg |= (ch1ch0_en << SPORT_SHIFT_SP_RX_FIFO_0_CH0_1_EN) | (ch2ch3_en << SPORT_SHIFT_SP_RX_FIFO_0_CH2_3_EN);
	psport_reg->SPORT_SP_FIFO_EN_CLK_CON = temp_reg;

}

/**
 *  @brief Control the sport rx FIFO_1.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] ch4ch5_en  Enable channel 4 and 5 data path for FIFO_1.
 *  @param[in] ch6ch7_en  Enable channel 6 and 7 data path for FIFO_1.
 *
 *  @returns void
 */
void hal_rtl_sport_rx_fifo_1(hal_sport_adapter_t *psport_adapter, BOOL ch4ch5_en, BOOL ch6ch7_en)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_FIFO_EN_CLK_CON;
	temp_reg &= ~(SPORT_BIT_SP_RX_FIFO_1_CH4_5_EN | SPORT_BIT_SP_RX_FIFO_1_CH6_7_EN);
	temp_reg |= (ch4ch5_en << SPORT_SHIFT_SP_RX_FIFO_1_CH4_5_EN) | (ch6ch7_en << SPORT_SHIFT_SP_RX_FIFO_1_CH6_7_EN);
	psport_reg->SPORT_SP_FIFO_EN_CLK_CON = temp_reg;

}

/**
 *  @brief Set BCLK numbers of one period LRCK for TX.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] bclk_cnt  Set the number of bclks for LRCK.
 *
 *  @returns void
 */
void hal_rtl_sport_set_tx_lrck(hal_sport_adapter_t *psport_adapter, u8 bclk_cnt)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_LRCK_FIFO_TH_CON;
	temp_reg &= ~(SPORT_MASK_SP_BCLK_DIV_RATIO);
	temp_reg |= ((bclk_cnt - 1) << SPORT_SHIFT_SP_BCLK_DIV_RATIO);
	psport_reg->SPORT_SP_LRCK_FIFO_TH_CON = temp_reg;

}

/**
 *  @brief Set BCLK numbers of one period LRCK for RX.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] bclk_cnt  Set the number of bclks for LRCK.
 *
 *  @returns void
 */
void hal_rtl_sport_set_rx_lrck(hal_sport_adapter_t *psport_adapter, u8 bclk_cnt)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_LRCK_FIFO_TH_CON;
	temp_reg &= ~(SPORT_MASK_SP_RX_BCLK_DIV_RATIO);
	temp_reg |= ((bclk_cnt - 1) << SPORT_SHIFT_SP_RX_BCLK_DIV_RATIO);
	psport_reg->SPORT_SP_LRCK_FIFO_TH_CON = temp_reg;

}

/**
 *  @brief Set sport tx parameters.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] psport_tx_params  Set tx parameter inputs.
 *
 *  @returns void
 */
void hal_rtl_sport_tx_params(hal_sport_adapter_t *psport_adapter, hal_sport_tx_params_t *psport_tx_params)
{
	u32 channel_len = 16;
	u32 channel_factor = 1;

	// 0: 16bits, 1: 20bits, 2: 24bits, 4: 32bits
	hal_rtl_sport_tx_channel_length(psport_adapter, psport_tx_params->sport_tx_cl);

	switch (psport_tx_params->sport_tx_cl) {

	case SPORT_CL_16BIT:
		channel_len = 16;
		psport_adapter->tx_ch_len_factor = 4;
		break;

	case SPORT_CL_20BIT:
		channel_len = 20;
		psport_adapter->tx_ch_len_factor = 5;
		break;

	case SPORT_CL_24BIT:
		channel_len = 24;
		psport_adapter->tx_ch_len_factor = 6;
		break;

	case SPORT_CL_32BIT:
		channel_len = 32;
		psport_adapter->tx_ch_len_factor = 8;
		break;

	default :
		DBG_SPORT_ERR("hal_rtl_sport_tx_params, sport_tx_cl is invalid \r\n");
		break;

	}

	hal_rtl_sport_tx0_data_length(psport_adapter, psport_tx_params->sport_tx0_dl);
	hal_rtl_sport_tx1_data_length(psport_adapter, psport_tx_params->sport_tx1_dl);

	switch (psport_tx_params->sport_tx_ch) {

	case CH_1_MONO:
		hal_rtl_sport_sel_tx_tdm(psport_adapter, SPORT_NO_TDM);
		hal_rtl_sport_tx0_mono(psport_adapter, 1);
		hal_rtl_sport_tx1_mono(psport_adapter, 1);
		hal_rtl_sport_set_tx0_consum(psport_adapter, 1);
		hal_rtl_sport_set_tx1_consum(psport_adapter, 1);
		hal_rtl_sport_tx_fifo_0(psport_adapter, 1, 0);
		hal_rtl_sport_tx_fifo_1(psport_adapter, 0, 0);
		channel_factor = 1;
		break;

	case CH_2_STEREO:
		hal_rtl_sport_sel_tx_tdm(psport_adapter, SPORT_NO_TDM);
		//FIFO 0
		hal_rtl_sport_tx0_mono(psport_adapter, 0);
		if (psport_tx_params->sport_tx0_dl ==  SPORT_DL_16BIT) {
			// data length = 16bits
			hal_rtl_sport_set_tx0_consum(psport_adapter, 1);
		} else {
			// data length > 16bits
			hal_rtl_sport_set_tx0_consum(psport_adapter, 2);
		}
		hal_rtl_sport_tx_fifo_0(psport_adapter, 1, 0);
		//FIFO 1
		hal_rtl_sport_tx1_mono(psport_adapter, 0);
		if (psport_tx_params->sport_tx1_dl ==  SPORT_DL_16BIT) {
			// data length = 16bits
			hal_rtl_sport_set_tx1_consum(psport_adapter, 1);
		} else {
			// data length > 16bits
			hal_rtl_sport_set_tx1_consum(psport_adapter, 2);
		}
		hal_rtl_sport_tx_fifo_1(psport_adapter, 0, 0);
		channel_factor = 1;
		break;

	case CH_4:
		hal_rtl_sport_sel_tx_tdm(psport_adapter, SPORT_4_TDM);
		//FIFO 0
		hal_rtl_sport_tx0_mono(psport_adapter, 0);
		if (psport_tx_params->sport_tx0_dl ==  SPORT_DL_16BIT) {
			// data length = 16bits
			hal_rtl_sport_set_tx0_consum(psport_adapter, 2);
		} else {
			// data length > 16bits
			hal_rtl_sport_set_tx0_consum(psport_adapter, 4);
		}
		hal_rtl_sport_tx_fifo_0(psport_adapter, 1, 1);
		//FIFO 1
		hal_rtl_sport_tx1_mono(psport_adapter, 1);
		if (psport_tx_params->sport_tx1_dl ==  SPORT_DL_16BIT) {
			// data length = 16bits
			hal_rtl_sport_set_tx1_consum(psport_adapter, 1);
		} else {
			// data length > 16bits
			hal_rtl_sport_set_tx1_consum(psport_adapter, 2);
		}
		hal_rtl_sport_tx_fifo_1(psport_adapter, 0, 0);
		channel_factor = 2;
		break;

	case CH_6:
		hal_rtl_sport_sel_tx_tdm(psport_adapter, SPORT_6_TDM);
		//FIFO 0
		hal_rtl_sport_tx0_mono(psport_adapter, 0);
		if (psport_tx_params->sport_tx0_dl ==  SPORT_DL_16BIT) {
			// data length = 16bits
			hal_rtl_sport_set_tx0_consum(psport_adapter, 2);
		} else {
			// data length > 16bits
			hal_rtl_sport_set_tx0_consum(psport_adapter, 4);
		}
		hal_rtl_sport_tx_fifo_0(psport_adapter, 1, 1);
		//FIFO 1
		hal_rtl_sport_tx1_mono(psport_adapter, 0);
		if (psport_tx_params->sport_tx1_dl ==  SPORT_DL_16BIT) {
			// data length = 16bits
			hal_rtl_sport_set_tx1_consum(psport_adapter, 1);
		} else {
			// data length > 16bits
			hal_rtl_sport_set_tx1_consum(psport_adapter, 2);
		}
		hal_rtl_sport_tx_fifo_1(psport_adapter, 1, 0);
		channel_factor = 3;
		break;

	case CH_8:
		hal_rtl_sport_sel_tx_tdm(psport_adapter, SPORT_8_TDM);
		//FIFO 0
		hal_rtl_sport_tx0_mono(psport_adapter, 0);
		if (psport_tx_params->sport_tx0_dl ==  SPORT_DL_16BIT) {
			// data length = 16bits
			hal_rtl_sport_set_tx0_consum(psport_adapter, 2);
		} else {
			// data length > 16bits
			hal_rtl_sport_set_tx0_consum(psport_adapter, 4);
		}
		hal_rtl_sport_tx_fifo_0(psport_adapter, 1, 1);
		//FIFO 1
		hal_rtl_sport_tx1_mono(psport_adapter, 0);
		if (psport_tx_params->sport_tx1_dl ==  SPORT_DL_16BIT) {
			// data length = 16bits
			hal_rtl_sport_set_tx1_consum(psport_adapter, 2);
		} else {
			// data length > 16bits
			hal_rtl_sport_set_tx1_consum(psport_adapter, 4);
		}
		hal_rtl_sport_tx_fifo_1(psport_adapter, 1, 1);
		channel_factor = 4;
		break;

	default :
		DBG_SPORT_ERR("hal_rtl_sport_tx_params, sport_tx_ch is invalid \r\n");
		break;

	}

	hal_rtl_sport_set_tx_lrck(psport_adapter, (channel_len * channel_factor * 2));

	psport_adapter->tx_channel_factor = channel_factor;
	hal_rtl_sport_tx_rate(psport_adapter, psport_tx_params->sport_tx_rate);

}

/**
 *  @brief Set sport rx parameters.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] psport_rx_params  Set rx parameter inputs.
 *
 *  @returns void
 */
void hal_rtl_sport_rx_params(hal_sport_adapter_t *psport_adapter, hal_sport_rx_params_t *psport_rx_params)
{
	u32 channel_len = 16;
	u32 channel_factor = 1;

	// 0: 16bits, 1: 20bits, 2: 24bits, 4: 32bits
	hal_rtl_sport_rx_channel_length(psport_adapter, psport_rx_params->sport_rx_cl);

	switch (psport_rx_params->sport_rx_cl) {

	case SPORT_CL_16BIT:
		channel_len = 16;
		psport_adapter->rx_ch_len_factor = 4;
		break;

	case SPORT_CL_20BIT:
		channel_len = 20;
		psport_adapter->rx_ch_len_factor = 5;
		break;

	case SPORT_CL_24BIT:
		channel_len = 24;
		psport_adapter->rx_ch_len_factor = 6;
		break;

	case SPORT_CL_32BIT:
		channel_len = 32;
		psport_adapter->rx_ch_len_factor = 8;
		break;

	default :
		DBG_SPORT_ERR("hal_rtl_sport_rx_params, sport_rx_cl is invalid \r\n");
		break;

	}

	hal_rtl_sport_rx0_data_length(psport_adapter, psport_rx_params->sport_rx0_dl);
	hal_rtl_sport_rx1_data_length(psport_adapter, psport_rx_params->sport_rx1_dl);

	switch (psport_rx_params->sport_rx_ch) {

	case CH_1_MONO:
		hal_rtl_sport_sel_rx_tdm(psport_adapter, SPORT_NO_TDM);
		hal_rtl_sport_rx0_mono(psport_adapter, 1);
		hal_rtl_sport_rx1_mono(psport_adapter, 1);
		hal_rtl_sport_set_rx0_consum(psport_adapter, 1);
		hal_rtl_sport_set_rx1_consum(psport_adapter, 1);
		hal_rtl_sport_rx_fifo_0(psport_adapter, 1, 0);
		hal_rtl_sport_rx_fifo_1(psport_adapter, 0, 0);
		channel_factor = 1;
		break;

	case CH_2_STEREO:
		hal_rtl_sport_sel_rx_tdm(psport_adapter, SPORT_NO_TDM);
		//FIFO 0
		hal_rtl_sport_rx0_mono(psport_adapter, 0);
		if (psport_rx_params->sport_rx0_dl ==  SPORT_DL_16BIT) {
			// data length = 16bits
			hal_rtl_sport_set_rx0_consum(psport_adapter, 1);
		} else {
			// data length > 16bits
			hal_rtl_sport_set_rx0_consum(psport_adapter, 2);
		}
		hal_rtl_sport_rx_fifo_0(psport_adapter, 1, 0);
		//FIFO 1
		hal_rtl_sport_rx1_mono(psport_adapter, 0);
		if (psport_rx_params->sport_rx1_dl ==  SPORT_DL_16BIT) {
			// data length = 16bits
			hal_rtl_sport_set_rx1_consum(psport_adapter, 1);
		} else {
			// data length > 16bits
			hal_rtl_sport_set_rx1_consum(psport_adapter, 2);
		}
		hal_rtl_sport_rx_fifo_1(psport_adapter, 0, 0);
		channel_factor = 1;
		break;

	case CH_4:
		hal_rtl_sport_sel_rx_tdm(psport_adapter, SPORT_4_TDM);
		//FIFO 0
		hal_rtl_sport_rx0_mono(psport_adapter, 0);
		if (psport_rx_params->sport_rx0_dl ==  SPORT_DL_16BIT) {
			// data length = 16bits
			hal_rtl_sport_set_rx0_consum(psport_adapter, 2);
		} else {
			// data length > 16bits
			hal_rtl_sport_set_rx0_consum(psport_adapter, 4);
		}
		hal_rtl_sport_rx_fifo_0(psport_adapter, 1, 1);
		//FIFO 1
		hal_rtl_sport_rx1_mono(psport_adapter, 1);
		if (psport_rx_params->sport_rx1_dl ==  SPORT_DL_16BIT) {
			// data length = 16bits
			hal_rtl_sport_set_rx1_consum(psport_adapter, 1);
		} else {
			// data length > 16bits
			hal_rtl_sport_set_rx1_consum(psport_adapter, 2);
		}
		hal_rtl_sport_rx_fifo_1(psport_adapter, 0, 0);
		channel_factor = 2;
		break;

	case CH_6:
		hal_rtl_sport_sel_rx_tdm(psport_adapter, SPORT_6_TDM);
		//FIFO 0
		hal_rtl_sport_rx0_mono(psport_adapter, 0);
		if (psport_rx_params->sport_rx0_dl ==  SPORT_DL_16BIT) {
			// data length = 16bits
			hal_rtl_sport_set_rx0_consum(psport_adapter, 2);
		} else {
			// data length > 16bits
			hal_rtl_sport_set_rx0_consum(psport_adapter, 4);
		}
		hal_rtl_sport_rx_fifo_0(psport_adapter, 1, 1);
		//FIFO 1
		hal_rtl_sport_rx1_mono(psport_adapter, 0);
		if (psport_rx_params->sport_rx1_dl ==  SPORT_DL_16BIT) {
			// data length = 16bits
			hal_rtl_sport_set_rx1_consum(psport_adapter, 1);
		} else {
			// data length > 16bits
			hal_rtl_sport_set_rx1_consum(psport_adapter, 2);
		}
		hal_rtl_sport_rx_fifo_1(psport_adapter, 1, 0);
		channel_factor = 3;
		break;

	case CH_8:
		hal_rtl_sport_sel_rx_tdm(psport_adapter, SPORT_8_TDM);
		//FIFO 0
		hal_rtl_sport_rx0_mono(psport_adapter, 0);
		if (psport_rx_params->sport_rx0_dl ==  SPORT_DL_16BIT) {
			// data length = 16bits
			hal_rtl_sport_set_rx0_consum(psport_adapter, 2);
		} else {
			// data length > 16bits
			hal_rtl_sport_set_rx0_consum(psport_adapter, 4);
		}
		hal_rtl_sport_rx_fifo_0(psport_adapter, 1, 1);
		//FIFO 1
		hal_rtl_sport_rx1_mono(psport_adapter, 0);
		if (psport_rx_params->sport_rx1_dl ==  SPORT_DL_16BIT) {
			// data length = 16bits
			hal_rtl_sport_set_rx1_consum(psport_adapter, 2);
		} else {
			// data length > 16bits
			hal_rtl_sport_set_rx1_consum(psport_adapter, 4);
		}
		hal_rtl_sport_rx_fifo_1(psport_adapter, 1, 1);
		channel_factor = 4;
		break;

	default :
		DBG_SPORT_ERR("hal_rtl_sport_rx_params, sport_rx_ch is invalid \r\n");
		break;

	}

	hal_rtl_sport_set_rx_lrck(psport_adapter, (channel_len * channel_factor * 2));

	psport_adapter->rx_channel_factor = channel_factor;
	hal_rtl_sport_rx_rate(psport_adapter, psport_rx_params->sport_rx_rate);

}


/**
 *  @brief Set TX FIFO interrupt and DMA request threshold.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] tx_th  Set number of tx FIFO threshold.
 *
 *  @returns void
 */
void hal_rtl_sport_tx_fifo_th(hal_sport_adapter_t *psport_adapter, u8 tx_th)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_LRCK_FIFO_TH_CON;
	temp_reg &= ~(SPORT_MASK_SP_TX_FIFO_TH);
	temp_reg |= ((tx_th - 1) << SPORT_SHIFT_SP_TX_FIFO_TH);
	psport_reg->SPORT_SP_LRCK_FIFO_TH_CON = temp_reg;

}

/**
 *  @brief Set RX FIFO interrupt and DMA request threshold.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] rx_th  Set number of rx FIFO threshold.
 *
 *  @returns void
 */
void hal_rtl_sport_rx_fifo_th(hal_sport_adapter_t *psport_adapter, u8 rx_th)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_LRCK_FIFO_TH_CON;
	temp_reg &= ~(SPORT_MASK_SP_RX_FIFO_TH);
	temp_reg |= ((rx_th - 1) << SPORT_SHIFT_SP_RX_FIFO_TH);
	psport_reg->SPORT_SP_LRCK_FIFO_TH_CON = temp_reg;

}

/**
 *  @brief Set dma burst size.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] burst_size Select the DMA burst size.
 *
 *  @returns void
 */
void hal_rtl_sport_set_dma_burst(hal_sport_adapter_t *psport_adapter, sport_burst_size_t burst_size)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_DMA_CON;
	temp_reg &= ~(SPORT_MASK_SP_BURST_SIZE);
	temp_reg |= (burst_size << SPORT_SHIFT_SP_BURST_SIZE);
	psport_reg->SPORT_SP_DMA_CON = temp_reg;

}

/**
 *  @brief Automatically set dma burst size.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns void
 */
void hal_rtl_sport_autoload_dma_burst(hal_sport_adapter_t *psport_adapter)
{
	u8 sp_tx_fifo_th, sp_rx_fifo_th;

	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_LRCK_FIFO_TH_CON;

	sp_tx_fifo_th = (temp_reg & SPORT_MASK_SP_TX_FIFO_TH) >> SPORT_SHIFT_SP_TX_FIFO_TH;
	sp_rx_fifo_th = (temp_reg & SPORT_MASK_SP_RX_FIFO_TH) >> SPORT_SHIFT_SP_RX_FIFO_TH;

	if ((sp_tx_fifo_th == 15) && (sp_rx_fifo_th == 15)) {
		hal_rtl_sport_set_dma_burst(psport_adapter, SPORT_BURST_16);
	} else if ((sp_tx_fifo_th == 7) && (sp_rx_fifo_th == 7)) {
		hal_rtl_sport_set_dma_burst(psport_adapter, SPORT_BURST_8);
	} else if ((sp_tx_fifo_th == 3) && (sp_rx_fifo_th == 3)) {
		hal_rtl_sport_set_dma_burst(psport_adapter, SPORT_BURST_4);
	} else {
		DBG_SPORT_WARN(" hal_sport_autoload_dma_burst: fifo_th doesn't meet burst_size\r\n");
	}

	temp_reg = psport_reg->SPORT_SP_DMA_CON;
	temp_reg &= ~(SPORT_BIT_SP_DMA_CTRL);
	psport_reg->SPORT_SP_DMA_CON = temp_reg;

}

/**
 *  @brief Set DMA interrupts
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] trx Select TX/RX.
 *  @param[in] ppage_intr Set DMA interrupts..
 *
 *  @returns void
 */
void hal_rtl_sport_set_dma_intr(hal_sport_adapter_t *psport_adapter, sport_trx_t trx, hal_sport_page_intr_t *ppage_intr)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg = 0x00;

	temp_reg = (ppage_intr->sport_p0ok << SPORT_SHIFT_SP_TX0_P0OKIE) | (ppage_intr->sport_p1ok << SPORT_SHIFT_SP_TX0_P1OKIE);
	temp_reg |= (ppage_intr->sport_p2ok << SPORT_SHIFT_SP_TX0_P2OKIE) | (ppage_intr->sport_p3ok << SPORT_SHIFT_SP_TX0_P3OKIE);
	temp_reg |= (ppage_intr->sport_p0unava << SPORT_SHIFT_SP_TX0_PAGE0UNAVA_IE) | (ppage_intr->sport_p1unava << SPORT_SHIFT_SP_TX0_PAGE1UNAVA_IE);
	temp_reg |= (ppage_intr->sport_p2unava << SPORT_SHIFT_SP_TX0_PAGE2UNAVA_IE) | (ppage_intr->sport_p3unava << SPORT_SHIFT_SP_TX0_PAGE3UNAVA_IE);
	temp_reg |= (ppage_intr->sport_p0err << SPORT_SHIFT_SP_TX0_PAGE0ERRIE) | (ppage_intr->sport_p1err << SPORT_SHIFT_SP_TX0_PAGE1ERRIE);
	temp_reg |= (ppage_intr->sport_p2err << SPORT_SHIFT_SP_TX0_PAGE2ERRIE) | (ppage_intr->sport_p3err << SPORT_SHIFT_SP_TX0_PAGE3ERRIE);
	temp_reg |= (ppage_intr->sport_fifo_err << SPORT_SHIFT_SP_TX0_UNDERFLOW_IE);

	if (trx == SPORT_TX0) {
		psport_reg->SPORT_SP_TX0_DMA_INT_EN = temp_reg;
	} else if (trx == SPORT_TX1) {
		psport_reg->SPORT_SP_TX1_DMA_INT_EN = temp_reg;
	} else if (trx == SPORT_RX0) {
		psport_reg->SPORT_SP_RX0_DMA_INT_EN = temp_reg;
	} else if (trx == SPORT_RX1) {
		psport_reg->SPORT_SP_RX1_DMA_INT_EN = temp_reg;
	}

}

/**
 *  @brief Set TX FIFO interrupts
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] ptx_fifo_intr Set TX FIFO interrupts..
 *
 *  @returns void
 */
void hal_rtl_sport_set_tx_fifo_intr(hal_sport_adapter_t *psport_adapter, hal_sport_tx_fifo_intr_t *ptx_fifo_intr)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_FIFO_INTR_CON;

	temp_reg &= ~(SPORT_BIT_SP_TX_IDLE_INTR_1_EN | SPORT_BIT_SP_TX_FIFO_EMPTY_1_EN | SPORT_BIT_SP_TX_FIFO_FULL_INTR_1_EN | SPORT_BIT_SP_TX_FIFO_TH_INTR_1_EN);
	temp_reg &= ~(SPORT_BIT_SP_TX_IDLE_INTR_0_EN | SPORT_BIT_SP_TX_FIFO_EMPTY_0_EN | SPORT_BIT_SP_TX_FIFO_FULL_INTR_0_EN | SPORT_BIT_SP_TX_FIFO_TH_INTR_0_EN);

	temp_reg |= (ptx_fifo_intr->sport_idle_tx1 << SPORT_SHIFT_SP_TX_IDLE_INTR_1_EN);
	temp_reg |= (ptx_fifo_intr->sport_empty_tx1 << SPORT_SHIFT_SP_TX_FIFO_EMPTY_1_EN);
	temp_reg |= (ptx_fifo_intr->sport_full_tx1 << SPORT_SHIFT_SP_TX_FIFO_FULL_INTR_1_EN);
	temp_reg |= (ptx_fifo_intr->sport_th_tx1 << SPORT_SHIFT_SP_TX_FIFO_TH_INTR_1_EN);

	temp_reg |= (ptx_fifo_intr->sport_idle_tx0 << SPORT_SHIFT_SP_TX_IDLE_INTR_0_EN);
	temp_reg |= (ptx_fifo_intr->sport_empty_tx0 << SPORT_SHIFT_SP_TX_FIFO_EMPTY_0_EN);
	temp_reg |= (ptx_fifo_intr->sport_full_tx0 << SPORT_SHIFT_SP_TX_FIFO_FULL_INTR_0_EN);
	temp_reg |= (ptx_fifo_intr->sport_th_tx0 << SPORT_SHIFT_SP_TX_FIFO_TH_INTR_0_EN);

	psport_reg->SPORT_SP_FIFO_INTR_CON = temp_reg;

}

/**
 *  @brief Set RX FIFO interrupts
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] prx_fifo_intr Set RX FIFO interrupts..
 *
 *  @returns void
 */
void hal_rtl_sport_set_rx_fifo_intr(hal_sport_adapter_t *psport_adapter, hal_sport_rx_fifo_intr_t *prx_fifo_intr)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_FIFO_INTR_CON;

	temp_reg &= ~(SPORT_BIT_SP_RX_FIFO_EMPTY_1_EN | SPORT_BIT_SP_RX_FIFO_FULL_INTR_1_EN | SPORT_BIT_SP_RX_FIFO_TH_INTR_1_EN);
	temp_reg &= ~(SPORT_BIT_SP_RX_FIFO_EMPTY_0_EN | SPORT_BIT_SP_RX_FIFO_FULL_INTR_0_EN | SPORT_BIT_SP_RX_FIFO_TH_INTR_0_EN);

	temp_reg |= (prx_fifo_intr->sport_empty_rx1 << SPORT_SHIFT_SP_RX_FIFO_EMPTY_1_EN);
	temp_reg |= (prx_fifo_intr->sport_full_rx1 << SPORT_SHIFT_SP_RX_FIFO_FULL_INTR_1_EN);
	temp_reg |= (prx_fifo_intr->sport_th_rx1 << SPORT_SHIFT_SP_RX_FIFO_TH_INTR_1_EN);

	temp_reg |= (prx_fifo_intr->sport_empty_rx0 << SPORT_SHIFT_SP_RX_FIFO_EMPTY_0_EN);
	temp_reg |= (prx_fifo_intr->sport_full_rx0 << SPORT_SHIFT_SP_RX_FIFO_FULL_INTR_0_EN);
	temp_reg |= (prx_fifo_intr->sport_th_rx0 << SPORT_SHIFT_SP_RX_FIFO_TH_INTR_0_EN);

	psport_reg->SPORT_SP_FIFO_INTR_CON = temp_reg;

}


/**
 *  @brief Set DMA parameters
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] page_size Set the page size.
 *  @param[in] page_num Set page numbers.
 *
 *  @returns void
 */
void hal_rtl_sport_dma_params(hal_sport_adapter_t *psport_adapter, u16 page_size, sport_page_num page_num)
{

	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_DMA_CON;
	temp_reg &= ~(SPORT_MASK_SP_PAGE_SIZE | SPORT_MASK_SP_PAGE_NUM);
	temp_reg |= (page_size << SPORT_SHIFT_SP_PAGE_SIZE) | (page_num << SPORT_SHIFT_SP_PAGE_NUM);
	psport_reg->SPORT_SP_DMA_CON = temp_reg;

	psport_adapter->init_dat.sport_data_byte_cnt = (u32)((page_num + 1) * ((page_size + 1) << 2));

	if (psport_adapter->init_dat.sport_tx0_data) {
		psport_reg->SPORT_SP_TX0_DMA_PP = (u32)psport_adapter->init_dat.sport_tx0_data;
	}

	if (psport_adapter->init_dat.sport_rx0_data) {
		psport_reg->SPORT_SP_RX0_DMA_PP = (u32)psport_adapter->init_dat.sport_rx0_data;

		if (psport_adapter->dcache_memory_en == 1) {
			if (psport_adapter->dcache_clean_by_addr != NULL) {
				psport_adapter->dcache_clean_by_addr((uint32_t *)psport_reg->SPORT_SP_RX0_DMA_PP, (int32_t) psport_adapter->init_dat.sport_data_byte_cnt);
			} else {
				DBG_SPORT_WARN(" psport_adapter->dcache_clean_by_addr is null \r\n");
			}
		}

	}

	if (psport_adapter->init_dat.sport_tx1_data) {
		psport_reg->SPORT_SP_TX1_DMA_PP = (u32)psport_adapter->init_dat.sport_tx1_data;
	}

	if (psport_adapter->init_dat.sport_rx1_data) {
		psport_reg->SPORT_SP_RX1_DMA_PP = (u32)psport_adapter->init_dat.sport_rx1_data;

		if (psport_adapter->dcache_memory_en == 1) {
			if (psport_adapter->dcache_clean_by_addr != NULL) {
				psport_adapter->dcache_clean_by_addr((uint32_t *)psport_reg->SPORT_SP_RX1_DMA_PP, (int32_t) psport_adapter->init_dat.sport_data_byte_cnt);
			} else {
				DBG_SPORT_WARN(" psport_adapter->dcache_clean_by_addr is null \r\n");
			}
		}

	}

}

/**
 *  @brief Control TX Start.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] en Control the enable.
 *
 *  @returns void
 */
void hal_rtl_sport_tx_start(hal_sport_adapter_t *psport_adapter, BOOL en)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;
	uint8_t ctrl_1, ctrl_2;

	if (en == 0) {
		ctrl_1 = 1;
		ctrl_2 = 0;
	} else {
		ctrl_1 = 0;
		ctrl_2 = 1;
	}

	temp_reg = psport_reg->SPORT_SP_CON;
	temp_reg &= ~(SPORT_BIT_SP_TX_DISABLE | SPORT_BIT_SP_START_TX);
	temp_reg |= (ctrl_1 << SPORT_SHIFT_SP_TX_DISABLE) | (ctrl_2 << SPORT_SHIFT_SP_START_TX);
	psport_reg->SPORT_SP_CON = temp_reg;

}

/**
 *  @brief Control RX Start.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] en Control the enable.
 *
 *  @returns void
 */
void hal_rtl_sport_rx_start(hal_sport_adapter_t *psport_adapter, BOOL en)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;
	uint8_t ctrl_1, ctrl_2;

	if (en == 0) {
		ctrl_1 = 1;
		ctrl_2 = 0;
	} else {
		ctrl_1 = 0;
		ctrl_2 = 1;
	}

	temp_reg = psport_reg->SPORT_SP_CON;
	temp_reg &= ~(SPORT_BIT_SP_RX_DISABLE | SPORT_BIT_SP_START_RX);
	temp_reg |= (ctrl_1 << SPORT_SHIFT_SP_RX_DISABLE) | (ctrl_2 << SPORT_SHIFT_SP_START_RX);
	psport_reg->SPORT_SP_CON = temp_reg;

}

/**
 *  @brief Control TX DMA Start.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] en Control the enable.
 *
 *  @returns void
 */
void hal_rtl_sport_tx_dma_start(hal_sport_adapter_t *psport_adapter, BOOL en)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_DMA_CON;
	temp_reg &= ~(SPORT_BIT_SP_TX_DMA_EN);
	temp_reg |= (en << SPORT_SHIFT_SP_TX_DMA_EN);
	psport_reg->SPORT_SP_DMA_CON = temp_reg;
}

/**
 *  @brief Get TX DMA Start Status.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns void
 */
u32 hal_rtl_sport_get_tx_dma_start_sta(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	return ((psport_reg->SPORT_SP_DMA_CON & SPORT_BIT_SP_TX_DMA_EN) >> SPORT_SHIFT_SP_TX_DMA_EN);
}

/**
 *  @brief Control RX DMA Start.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] en Control the enable.
 *
 *  @returns void
 */
void hal_rtl_sport_rx_dma_start(hal_sport_adapter_t *psport_adapter, BOOL en)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_DMA_CON;
	temp_reg &= ~(SPORT_BIT_SP_RX_DMA_EN);
	temp_reg |= (en << SPORT_SHIFT_SP_RX_DMA_EN);
	psport_reg->SPORT_SP_DMA_CON = temp_reg;
}

/**
 *  @brief Get RX DMA Start Status.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns void
 */
u32 hal_rtl_sport_get_rx_dma_start_sta(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	return ((psport_reg->SPORT_SP_DMA_CON & SPORT_BIT_SP_RX_DMA_EN) >> SPORT_SHIFT_SP_RX_DMA_EN);
}

/**
 *  @brief Set sport DMA buffer.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] pbuf_params  Set DMA buffer inputs.
 *
 *  @returns void
 */
void hal_rtl_sport_dma_buffer(hal_sport_adapter_t *psport_adapter, hal_sport_buf_params_t *pbuf_params)
{
	u32 i;

	if ((pbuf_params->page_num < 2) || (pbuf_params->page_num > 4) || (pbuf_params->page_size < 8)) {
		DBG_SPORT_WARN("PageNum(%d) valid value is 2~4; PageSize(%d must > 8)\r\n", pbuf_params->page_num, pbuf_params->page_size);
		return;
	}

	psport_adapter->init_dat.sport_tx0_data = (u8 *)pbuf_params->tx0_buf;
	psport_adapter->init_dat.sport_rx0_data = (u8 *)pbuf_params->rx0_buf;

	psport_adapter->init_dat.sport_tx1_data = (u8 *)pbuf_params->tx1_buf;
	psport_adapter->init_dat.sport_rx1_data = (u8 *)pbuf_params->rx1_buf;

	hal_rtl_sport_dma_params(psport_adapter, (pbuf_params->page_size / 4 - 1), (pbuf_params->page_num - 1));

	for (i = 0; i < pbuf_params->page_num; i++) {
		psport_adapter->ptx0_page_list[i] = (u32 *)(pbuf_params->tx0_buf + ((pbuf_params->page_size) * i));
		psport_adapter->prx0_page_list[i] = (u32 *)(pbuf_params->rx0_buf + ((pbuf_params->page_size) * i));
		psport_adapter->ptx1_page_list[i] = (u32 *)(pbuf_params->tx1_buf + ((pbuf_params->page_size) * i));
		psport_adapter->prx1_page_list[i] = (u32 *)(pbuf_params->rx1_buf + ((pbuf_params->page_size) * i));
	}

}

/**
 *  @brief Get the current tx0 page address.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns The address of current tx0 page or NULL.
 */
int *hal_rtl_sport_get_tx0_page(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	u32 reg = 0;
	u8 sport_tx0_idx = psport_adapter->init_dat.sport_tx0_idx;

	switch (sport_tx0_idx) {

	case 0:
		reg = (psport_reg->SPORT_SP_TX_PAGE_OWN & SPORT_BIT_SP_TX0_P0OWN) >> SPORT_SHIFT_SP_TX0_P0OWN;
		break;

	case 1:
		reg = (psport_reg->SPORT_SP_TX_PAGE_OWN & SPORT_BIT_SP_TX0_P1OWN) >> SPORT_SHIFT_SP_TX0_P1OWN;
		break;

	case 2:
		reg = (psport_reg->SPORT_SP_TX_PAGE_OWN & SPORT_BIT_SP_TX0_P2OWN) >> SPORT_SHIFT_SP_TX0_P2OWN;
		break;

	case 3:
		reg = (psport_reg->SPORT_SP_TX_PAGE_OWN & SPORT_BIT_SP_TX0_P3OWN) >> SPORT_SHIFT_SP_TX0_P3OWN;
		break;

	default:
		DBG_SPORT_WARN("hal_sport_get_tx0_page, sport_tx0_idx: %d is illegal \r\n", sport_tx0_idx);
		break;

	}

	if (reg == 0) {
		// Cpu control
		return ((int *)psport_adapter->ptx0_page_list[sport_tx0_idx]);
	} else {
		// SPORT controller control
		DBG_SPORT_WARN("Tx_0_page is busy: \r\n");
		DBG_SPORT_WARN("page_idx: %d \r\n", sport_tx0_idx);
		return NULL;
	}

}

/**
 *  @brief Get the current tx1 page address.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns The address of current tx1 page or NULL.
 */
int *hal_rtl_sport_get_tx1_page(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	u32 reg = 0;
	u8 sport_tx1_idx = psport_adapter->init_dat.sport_tx1_idx;

	switch (sport_tx1_idx) {

	case 0:
		reg = (psport_reg->SPORT_SP_TX_PAGE_OWN & SPORT_BIT_SP_TX1_P0OWN) >> SPORT_SHIFT_SP_TX1_P0OWN;
		break;

	case 1:
		reg = (psport_reg->SPORT_SP_TX_PAGE_OWN & SPORT_BIT_SP_TX1_P1OWN) >> SPORT_SHIFT_SP_TX1_P1OWN;
		break;

	case 2:
		reg = (psport_reg->SPORT_SP_TX_PAGE_OWN & SPORT_BIT_SP_TX1_P2OWN) >> SPORT_SHIFT_SP_TX1_P2OWN;
		break;

	case 3:
		reg = (psport_reg->SPORT_SP_TX_PAGE_OWN & SPORT_BIT_SP_TX1_P3OWN) >> SPORT_SHIFT_SP_TX1_P3OWN;
		break;

	default:
		DBG_SPORT_WARN("hal_sport_get_tx1_page, sport_tx1_idx: %d is illegal \r\n", sport_tx1_idx);
		break;

	}

	if (reg == 0) {
		// Cpu control
		return ((int *)psport_adapter->ptx1_page_list[sport_tx1_idx]);
	} else {
		// SPORT controller control
		DBG_SPORT_WARN("Tx_1_page is busy: \r\n");
		DBG_SPORT_WARN("page_idx: %d \r\n", sport_tx1_idx);
		return NULL;
	}

}

/**
 *  @brief Sets current tx0 page own by SPORT.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] pbuf  Set tx buffer adderss.
 *
 *  @returns void
 */
void hal_rtl_sport_tx0_page_send(hal_sport_adapter_t *psport_adapter, u32 *pbuf)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	u32 page_num, i;
	u8 sport_tx0_idx = psport_adapter->init_dat.sport_tx0_idx;
	u8 sport_page_num = (psport_reg->SPORT_SP_DMA_CON & SPORT_MASK_SP_PAGE_NUM) >> SPORT_SHIFT_SP_PAGE_NUM;

	page_num = sport_page_num + 1;
	for (i = 0; i < page_num; i++) {

		if (psport_adapter->ptx0_page_list[i] == pbuf) {

			if (sport_tx0_idx != i) {
				DBG_SPORT_WARN("hal_sport_tx0_page_send: UnExpected Page Index. TxPage=%d, Expected:%d\r\n",
							   i, sport_tx0_idx);
			}

			if (psport_adapter->dcache_memory_en == 1) {
				if (psport_adapter->dcache_clean_by_addr != NULL) {
					psport_adapter->dcache_clean_by_addr((uint32_t *)psport_adapter->ptx0_page_list[i],
														 (int32_t)((((psport_reg->SPORT_SP_DMA_CON & SPORT_MASK_SP_PAGE_SIZE) >> SPORT_SHIFT_SP_PAGE_SIZE) + 1) << 2));
				} else {
					DBG_SPORT_WARN(" psport_adapter->dcache_clean_by_addr is null \r\n");
				}
			}

			switch (i) {

			case 0:
				psport_reg->SPORT_SP_TX_PAGE_OWN |= SPORT_BIT_SP_TX0_P0OWN;
				break;

			case 1:
				psport_reg->SPORT_SP_TX_PAGE_OWN |= SPORT_BIT_SP_TX0_P1OWN;
				break;

			case 2:
				psport_reg->SPORT_SP_TX_PAGE_OWN |= SPORT_BIT_SP_TX0_P2OWN;
				break;

			case 3:
				psport_reg->SPORT_SP_TX_PAGE_OWN |= SPORT_BIT_SP_TX0_P3OWN;
				break;

			default:
				DBG_SPORT_WARN("hal_sport_tx0_page_send, page_idx: %d is illegal \r\n", i);
				break;

			}

			sport_tx0_idx = i + 1;
			if (sport_tx0_idx > sport_page_num) {
				sport_tx0_idx = 0;
			}
			psport_adapter->init_dat.sport_tx0_idx = sport_tx0_idx;

			break;  // break the for loop
		}
	}

	if (i == page_num) {
		DBG_SPORT_WARN("sport_tx0_page_send: the pbuf(0x%x) is not a DMA buffer\r\n", pbuf);
	}

}

/**
 *  @brief Sets current tx1 page own by SPORT.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] pbuf  Set tx buffer adderss.
 *
 *  @returns void
 */
void hal_rtl_sport_tx1_page_send(hal_sport_adapter_t *psport_adapter, u32 *pbuf)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	u8 page_num, i;
	u8 sport_tx1_idx = psport_adapter->init_dat.sport_tx1_idx;
	u8 sport_page_num = (psport_reg->SPORT_SP_DMA_CON & SPORT_MASK_SP_PAGE_NUM) >> SPORT_SHIFT_SP_PAGE_NUM;

	page_num = sport_page_num + 1;
	for (i = 0; i < page_num; i++) {

		if (psport_adapter->ptx1_page_list[i] == pbuf) {

			if (sport_tx1_idx != i) {
				DBG_SPORT_WARN("hal_sport_tx1_page_send: UnExpected Page Index. TxPage=%d, Expected:%d\r\n",
							   i, sport_tx1_idx);
			}

			if (psport_adapter->dcache_memory_en == 1) {
				if (psport_adapter->dcache_clean_by_addr != NULL) {
					psport_adapter->dcache_clean_by_addr((uint32_t *)psport_adapter->ptx1_page_list[i],
														 (int32_t)((((psport_reg->SPORT_SP_DMA_CON & SPORT_MASK_SP_PAGE_SIZE) >> SPORT_SHIFT_SP_PAGE_SIZE) + 1) << 2));
				} else {
					DBG_SPORT_WARN(" psport_adapter->dcache_clean_by_addr is null \r\n");
				}
			}

			switch (i) {

			case 0:
				psport_reg->SPORT_SP_TX_PAGE_OWN |= SPORT_BIT_SP_TX1_P0OWN;
				break;

			case 1:
				psport_reg->SPORT_SP_TX_PAGE_OWN |= SPORT_BIT_SP_TX1_P1OWN;
				break;

			case 2:
				psport_reg->SPORT_SP_TX_PAGE_OWN |= SPORT_BIT_SP_TX1_P2OWN;
				break;

			case 3:
				psport_reg->SPORT_SP_TX_PAGE_OWN |= SPORT_BIT_SP_TX1_P3OWN;
				break;

			default:
				DBG_SPORT_WARN("hal_sport_tx1_page_send, page_idx: %d is illegal \r\n", i);
				break;

			}

			sport_tx1_idx = i + 1;
			if (sport_tx1_idx > sport_page_num) {
				sport_tx1_idx = 0;
			}
			psport_adapter->init_dat.sport_tx1_idx = sport_tx1_idx;

			break;  // break the for loop
		}
	}

	if (i == page_num) {
		DBG_SPORT_WARN("sport_tx1_page_send: the pbuf(0x%x) is not a DMA buffer\r\n", pbuf);
	}

}

/**
 *  @brief Sets current rx0 page own by SPORT.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns void
 */
u32 hal_rtl_sport_rx0_page_recv(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	u32 reg = 0;
	u8 sport_rx0_idx = psport_adapter->init_dat.sport_rx0_idx;
	u8 sport_page_num = (psport_reg->SPORT_SP_DMA_CON & SPORT_MASK_SP_PAGE_NUM) >> SPORT_SHIFT_SP_PAGE_NUM;

	switch (sport_rx0_idx) {

	case 0:
		reg = (psport_reg->SPORT_SP_RX_PAGE_OWN & SPORT_BIT_SP_RX0_P0OWN) >> SPORT_SHIFT_SP_RX0_P0OWN;
		break;

	case 1:
		reg = (psport_reg->SPORT_SP_RX_PAGE_OWN & SPORT_BIT_SP_RX0_P1OWN) >> SPORT_SHIFT_SP_RX0_P1OWN;
		break;

	case 2:
		reg = (psport_reg->SPORT_SP_RX_PAGE_OWN & SPORT_BIT_SP_RX0_P2OWN) >> SPORT_SHIFT_SP_RX0_P2OWN;
		break;

	case 3:
		reg = (psport_reg->SPORT_SP_RX_PAGE_OWN & SPORT_BIT_SP_RX0_P3OWN) >> SPORT_SHIFT_SP_RX0_P3OWN;
		break;

	default:
		DBG_SPORT_WARN("hal_sport_rx0_page_recv, sport_rx0_idx: %d is illegal \r\n", sport_rx0_idx);
		break;

	}

	if (reg != 0) {
		DBG_SPORT_WARN("hal_sport_rx0_page_recv: No Idle Rx Page\r\n");
		return HAL_NOT_READY;
	}

	switch (sport_rx0_idx) {

	case 0:
		psport_reg->SPORT_SP_RX_PAGE_OWN |= SPORT_BIT_SP_RX0_P0OWN;
		break;

	case 1:
		psport_reg->SPORT_SP_RX_PAGE_OWN |= SPORT_BIT_SP_RX0_P1OWN;
		break;

	case 2:
		psport_reg->SPORT_SP_RX_PAGE_OWN |= SPORT_BIT_SP_RX0_P2OWN;
		break;

	case 3:
		psport_reg->SPORT_SP_RX_PAGE_OWN |= SPORT_BIT_SP_RX0_P3OWN;
		break;

	default:
		DBG_SPORT_WARN("hal_sport_rx0_page_recv, sport_rx0_idx: %d is illegal \r\n", sport_rx0_idx);
		break;

	}

	sport_rx0_idx = sport_rx0_idx + 1;
	if (sport_rx0_idx > sport_page_num) {
		sport_rx0_idx = 0;
	}
	psport_adapter->init_dat.sport_rx0_idx = sport_rx0_idx;

	return HAL_OK;

}

/**
 *  @brief Sets current rx1 page own by SPORT.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns void
 */
u32 hal_rtl_sport_rx1_page_recv(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	u32 reg = 0;
	u8 sport_rx1_idx = psport_adapter->init_dat.sport_rx1_idx;
	u8 sport_page_num = (psport_reg->SPORT_SP_DMA_CON & SPORT_MASK_SP_PAGE_NUM) >> SPORT_SHIFT_SP_PAGE_NUM;

	switch (sport_rx1_idx) {

	case 0:
		reg = (psport_reg->SPORT_SP_RX_PAGE_OWN & SPORT_BIT_SP_RX1_P0OWN) >> SPORT_SHIFT_SP_RX1_P0OWN;
		break;

	case 1:
		reg = (psport_reg->SPORT_SP_RX_PAGE_OWN & SPORT_BIT_SP_RX1_P1OWN) >> SPORT_SHIFT_SP_RX1_P1OWN;
		break;

	case 2:
		reg = (psport_reg->SPORT_SP_RX_PAGE_OWN & SPORT_BIT_SP_RX1_P2OWN) >> SPORT_SHIFT_SP_RX1_P2OWN;
		break;

	case 3:
		reg = (psport_reg->SPORT_SP_RX_PAGE_OWN & SPORT_BIT_SP_RX1_P3OWN) >> SPORT_SHIFT_SP_RX1_P3OWN;
		break;

	default:
		DBG_SPORT_WARN("hal_sport_rx1_page_recv, sport_rx1_idx: %d is illegal \r\n", sport_rx1_idx);
		break;

	}

	if (reg != 0) {
		DBG_SPORT_WARN("hal_sport_rx1_page_recv: No Idle Rx Page\r\n");
		return HAL_NOT_READY;
	}

	switch (sport_rx1_idx) {

	case 0:
		psport_reg->SPORT_SP_RX_PAGE_OWN |= SPORT_BIT_SP_RX1_P0OWN;
		break;

	case 1:
		psport_reg->SPORT_SP_RX_PAGE_OWN |= SPORT_BIT_SP_RX1_P1OWN;
		break;

	case 2:
		psport_reg->SPORT_SP_RX_PAGE_OWN |= SPORT_BIT_SP_RX1_P2OWN;
		break;

	case 3:
		psport_reg->SPORT_SP_RX_PAGE_OWN |= SPORT_BIT_SP_RX1_P3OWN;
		break;

	default:
		DBG_SPORT_WARN("hal_sport_rx1_page_recv, sport_rx1_idx: %d is illegal \r\n", sport_rx1_idx);
		break;

	}

	sport_rx1_idx = sport_rx1_idx + 1;
	if (sport_rx1_idx > sport_page_num) {
		sport_rx1_idx = 0;
	}
	psport_adapter->init_dat.sport_rx1_idx = sport_rx1_idx;

	return HAL_OK;

}

/**
 *  @brief Get the error status of TX FIFO.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  TX FIFO error counts
 */
u32 hal_rtl_sport_get_tx_fifo_err(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = (psport_reg->SPORT_SP_TX_RX_ERR_STA & SPORT_MASK_SP_TX_ERR_CNT) >> SPORT_SHIFT_SP_TX_ERR_CNT;

	return temp_reg;

}

/**
 *  @brief Get the error status of RX FIFO.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns RX FIFO error counts
 */
u32 hal_rtl_sport_get_rx_fifo_err(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = (psport_reg->SPORT_SP_TX_RX_ERR_STA & SPORT_MASK_SP_RX_ERR_CNT) >> SPORT_SHIFT_SP_RX_ERR_CNT;

	return temp_reg;

}

/**
 *  @brief Clean the error status of TX FIFO.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns void
 */
void hal_rtl_sport_clr_tx_fifo_err(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	psport_reg->SPORT_SP_FIFO_EN_CLK_CON |= SPORT_BIT_SP_CLEAR_TX_ERR_CNT;
	psport_reg->SPORT_SP_FIFO_EN_CLK_CON &= ~(SPORT_BIT_SP_CLEAR_TX_ERR_CNT);

}

/**
 *  @brief Clean the error status of RX FIFO.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns void
 */
void hal_rtl_sport_clr_rx_fifo_err(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	psport_reg->SPORT_SP_FIFO_EN_CLK_CON |= SPORT_BIT_SP_CLEAR_RX_ERR_CNT;
	psport_reg->SPORT_SP_FIFO_EN_CLK_CON &= ~(SPORT_BIT_SP_CLEAR_RX_ERR_CNT);

}

/**
 *  @brief Register the SPORT FIFO IRQ callback function and argument.
 *
 *  @param[in] pecdsa_adapter The SPORT adapter.
 *  @param[in]  callback The callback function.
 *  @param[in]  arg The callback argument.
 *  @returns void
 */
void hal_rtl_sport_fifo_cb_handler(hal_sport_adapter_t *psport_adapter, sport_irq_user_cb_t callback, u32 *arg)
{
	if (callback != NULL) {
		psport_adapter->sport_irq_user_cb = callback;
		psport_adapter->sport_user_arg = arg;
	}
}

/**
 *  @brief Register the SPORT TX0 DMA IRQ callback function and argument.
 *
 *  @param[in] pecdsa_adapter The SPORT adapter.
 *  @param[in]  callback The callback function.
 *  @param[in]  arg The callback argument.
 *  @returns void
 */
void hal_rtl_sport_tx0_dma_cb_handler(hal_sport_adapter_t *psport_adapter, sport_irq_user_cb_t callback, u32 *arg)
{
	if (callback != NULL) {
		psport_adapter->sport_tx0_irq_user_cb = callback;
		psport_adapter->sport_tx0_user_arg = arg;
	} else {
		psport_adapter->sport_tx0_irq_user_cb = NULL;
		psport_adapter->sport_tx0_user_arg = NULL;
	}
}

/**
 *  @brief Register the SPORT TX1 DMA IRQ callback function and argument.
 *
 *  @param[in] pecdsa_adapter The SPORT adapter.
 *  @param[in]  callback The callback function.
 *  @param[in]  arg The callback argument.
 *  @returns void
 */
void hal_rtl_sport_tx1_dma_cb_handler(hal_sport_adapter_t *psport_adapter, sport_irq_user_cb_t callback, u32 *arg)
{
	if (callback != NULL) {
		psport_adapter->sport_tx1_irq_user_cb = callback;
		psport_adapter->sport_tx1_user_arg = arg;
	} else {
		psport_adapter->sport_tx1_irq_user_cb = NULL;
		psport_adapter->sport_tx1_user_arg = NULL;
	}
}

/**
 *  @brief Register the SPORT RX0 DMA IRQ callback function and argument.
 *
 *  @param[in] pecdsa_adapter The SPORT adapter.
 *  @param[in]  callback The callback function.
 *  @param[in]  arg The callback argument.
 *  @returns void
 */
void hal_rtl_sport_rx0_dma_cb_handler(hal_sport_adapter_t *psport_adapter, sport_irq_user_cb_t callback, u32 *arg)
{
	if (callback != NULL) {
		psport_adapter->sport_rx0_irq_user_cb = callback;
		psport_adapter->sport_rx0_user_arg = arg;
	} else {
		psport_adapter->sport_rx0_irq_user_cb = NULL;
		psport_adapter->sport_rx0_user_arg = NULL;
	}
}

/**
 *  @brief Register the SPORT RX1 DMA IRQ callback function and argument.
 *
 *  @param[in] pecdsa_adapter The SPORT adapter.
 *  @param[in]  callback The callback function.
 *  @param[in]  arg The callback argument.
 *  @returns void
 */
void hal_rtl_sport_rx1_dma_cb_handler(hal_sport_adapter_t *psport_adapter, sport_irq_user_cb_t callback, u32 *arg)
{
	if (callback != NULL) {
		psport_adapter->sport_rx1_irq_user_cb = callback;
		psport_adapter->sport_rx1_user_arg = arg;
	} else {
		psport_adapter->sport_rx1_irq_user_cb = NULL;
		psport_adapter->sport_rx1_user_arg = NULL;
	}
}

/**
 *  @brief Register the SPORT DMA error IRQ callback function and argument.
 *
 *  @param[in] pecdsa_adapter The SPORT adapter.
 *  @param[in]  callback The callback function.
 *  @param[in]  arg The callback argument.
 *  @returns void
 */
void hal_rtl_sport_dma_err_cb_handler(hal_sport_adapter_t *psport_adapter, sport_irq_user_cb_t callback, u32 *arg)
{
	if (callback != NULL) {
		psport_adapter->sport_dma_err_irq_user_cb = callback;
		psport_adapter->sport_dma_err_user_arg = arg;
	} else {
		psport_adapter->sport_dma_err_irq_user_cb = NULL;
		psport_adapter->sport_dma_err_user_arg = NULL;
	}
}

/**
 *  @brief Set sport uses the fixed bclk.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] fixed_en: Control fixed bclk
 *  @param[in] fixed_bclk_sel: Select the fixed bclk frequence.
 *
 *  @returns void
 */
void hal_rtl_sport_fixed_bclk(hal_sport_adapter_t *psport_adapter, BOOL fixed_en, sport_fixed_bclk_t fixed_bclk_sel)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_FORM_CON;
	temp_reg &= ~(SPORT_BIT_SP_FIXED_BCLK_SEL | SPORT_BIT_SP_FIXED_BCLK);
	temp_reg |= (fixed_en << SPORT_SHIFT_SP_FIXED_BCLK);
	temp_reg |= (fixed_bclk_sel << SPORT_SHIFT_SP_FIXED_BCLK_SEL);
	psport_reg->SPORT_SP_FORM_CON = temp_reg;
}

/**
 *  @brief Set tx and rx are the same FS.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] en 1: Tx and rx are the same, 0: FS is not the same.
 *
 *  @returns void
 */
void hal_rtl_sport_rx_same_fs(hal_sport_adapter_t *psport_adapter, BOOL en)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = psport_reg->SPORT_SP_FORM_CON;
	temp_reg &= ~(SPORT_BIT_SP_TRX_SAME_LRCK);
	temp_reg |= (en << SPORT_SHIFT_SP_TRX_SAME_LRCK);
	psport_reg->SPORT_SP_FORM_CON = temp_reg;
}


