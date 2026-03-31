/**************************************************************************//**
 * @file     rtl8735bhp_i2s.c
 * @brief    This file implements the I2S HAL functions in ROM.
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
#include "hal.h"
#include "hal_sys_ctrl.h"
#include "hal_sys_ctrl_nsc.h"


#define SECTION_I2S_TEXT           //SECTION(".ram.hal_i2s.text")
#define SECTION_I2S_DATA           //SECTION(".ram.hal_i2s.data")
#define SECTION_I2S_RODATA         //SECTION(".ram.hal_i2s.rodata")
#define SECTION_I2S_BSS            //SECTION(".ram.hal_i2s.bss")
#define SECTION_I2S_STUBS          //SECTION(".ram.hal_i2s.stubs")


#if !defined(CONFIG_BUILD_NONSECURE)

#undef I2S0_REG_BASE
#define I2S0_REG_BASE (I2S0_S_BASE)

#undef I2S1_REG_BASE
#define I2S1_REG_BASE (I2S1_S_BASE)

#else

#undef I2S0_REG_BASE
#define I2S0_REG_BASE (I2S0_BASE)

#undef I2S1_REG_BASE
#define I2S1_REG_BASE (I2S1_BASE)

#endif


/**
 * @addtogroup hs_hal_i2s I2S
 * @{
 */


/**
  * @brief The global common data structure to store common resource
  *        for all I2S adapters.
  */
SECTION_I2S_BSS hal_i2s_group_adapter_t i2s_group_adapter;

/**
  * @brief I2S Pin mux table for WS, CLK, TX0, RX, MCK, TX1 and TX2 pin.
  */
SECTION_I2S_RODATA const uint8_t i2s_pin_group[] = {

#if 0                                                                    /* === I2S0, S0 === */
	PIN_E0, PIN_E1, PIN_E2, PIN_LIST_END,                           /* WS, CLK, TX0 */
	PIN_E0, PIN_E1, PIN_E2, PIN_E5, PIN_LIST_END,                   /* WS, CLK, TX0, RX */
	PIN_E0, PIN_E1, PIN_E2, PIN_E4, PIN_E6, PIN_LIST_END,           /* WS, CLK, TX0, TX1, TX2 */
	PIN_E0, PIN_E1, PIN_E2, PIN_E3, PIN_LIST_END,                   /* WS, CLK, TX0, MCK */
	PIN_E0, PIN_E1, PIN_E2, PIN_E5, PIN_E3, PIN_LIST_END,           /* WS, CLK, TX0, RX, MCK */
	PIN_E0, PIN_E1, PIN_E2, PIN_E4, PIN_E6, PIN_E3, PIN_LIST_END,   /* WS, CLK, TX0, TX1, TX2, MCK */

	/* === I2S0, S1 === */
	PIN_G0, PIN_G1, PIN_G2, PIN_LIST_END,                           /* WS, CLK, TX0 */
	PIN_G0, PIN_G1, PIN_G2, PIN_G6, PIN_LIST_END,                   /* WS, CLK, TX0, RX */
	PIN_G0, PIN_G1, PIN_G2, PIN_G4, PIN_G5, PIN_LIST_END,           /* WS, CLK, TX0, TX1, TX2 */
	PIN_G0, PIN_G1, PIN_G2, PIN_G3, PIN_LIST_END,                   /* WS, CLK, TX0, MCK */
	PIN_G0, PIN_G1, PIN_G2, PIN_G6, PIN_G3, PIN_LIST_END,           /* WS, CLK, TX0, RX, MCK */
	PIN_G0, PIN_G1, PIN_G2, PIN_G4, PIN_G5, PIN_G3, PIN_LIST_END,   /* WS, CLK, TX0, TX1, TX2, MCK */

	/* === I2S1, S0 === */
	PIN_B0, PIN_B1, PIN_B2, PIN_LIST_END,                           /* WS, CLK, TX0 */
	PIN_B0, PIN_B1, PIN_B2, PIN_B6, PIN_LIST_END,                   /* WS, CLK, TX0, RX */
	PIN_B0, PIN_B1, PIN_B2, PIN_B4, PIN_B5, PIN_LIST_END,           /* WS, CLK, TX0, TX1, TX2 */
	PIN_B0, PIN_B1, PIN_B2, PIN_B3, PIN_LIST_END,                   /* WS, CLK, TX0, MCK */
	PIN_B0, PIN_B1, PIN_B2, PIN_B6, PIN_B3, PIN_LIST_END,           /* WS, CLK, TX0, RX, MCK */
	PIN_B0, PIN_B1, PIN_B2, PIN_B4, PIN_B5, PIN_B3, PIN_LIST_END,   /* WS, CLK, TX0, TX1, TX2, MCK */

	/* === I2S1, S1 === */
	PIN_G6, PIN_G7, PIN_G8, PIN_LIST_END,                                               /* WS, CLK, TX0 */
	PIN_G6, PIN_G7, PIN_G8, PIN_G5, PIN_LIST_END,                                       /* WS, CLK, TX0, RX */
	PIN_LIST_END, PIN_LIST_END, PIN_LIST_END, PIN_LIST_END, PIN_LIST_END, PIN_LIST_END, /* X, X, X, X, X */
	PIN_G6, PIN_G7, PIN_G8, PIN_G9, PIN_LIST_END,                                       /* WS, CLK, TX0, MCK */
	PIN_G6, PIN_G7, PIN_G8, PIN_G5, PIN_G9, PIN_LIST_END,                               /* WS, CLK, TX0, RX, MCK */
	PIN_LIST_END                                                                        /* X, X, X, X, X, X */
#endif
};

/// @cond DOXYGEN_ROM_HAL_API

/**
 * @addtogroup hs_hal_i2s_rom_func I2S HAL ROM APIs.
 * @ingroup hs_hal_i2s
 * @{
 * @brief The I2S HAL ROM APIs. The user application(in RAM space) should not call these APIs directly.
 *        There is another set of I2S HAL APIs in the RAM space is provided for the user application.
 */

/**
  * @brief The stubs functions table to exports I2S HAL functions in ROM.
  */
SECTION_I2S_STUBS const hal_i2s_func_stubs_t hal_i2s_stubs = {
	.pi2s_group_adapter = &i2s_group_adapter,
	.pi2s_pin_group = i2s_pin_group,
	.hal_i2s_irq_handler = hal_rtl_i2s_irq_handler,
	.hal_i2s_irq_reg = hal_rtl_i2s_irq_reg,
	.hal_i2s_irq_unreg = hal_rtl_i2s_irq_unreg,
	.hal_i2s_clk_ctrl = hal_rtl_i2s_en_clk_ctrl,
	.hal_i2s_func_ctrl = hal_rtl_i2s_func_ctrl,
	.hal_i2s_init = hal_rtl_i2s_init,
	.hal_i2s_deinit = hal_rtl_i2s_deinit,
	.hal_i2s_enter_critical = hal_rtl_i2s_enter_critical,
	.hal_i2s_exit_critical = hal_rtl_i2s_exit_critical,
	.hal_i2s_set_parameter = hal_rtl_i2s_set_parameter,
	.hal_i2s_set_rate = hal_rtl_i2s_set_rate,
	.hal_i2s_set_dma_buf = hal_rtl_i2s_set_dma_buf,
	.hal_i2s_get_tx_page = hal_rtl_i2s_get_tx_page,
	.hal_i2s_get_rx_page = hal_rtl_i2s_get_rx_page,
	.hal_i2s_page_send = hal_rtl_i2s_page_send,
	.hal_i2s_page_recv = hal_rtl_i2s_page_recv,
	.hal_i2s_clear_all_own_bit = hal_rtl_i2s_clear_all_own_bit,
	.hal_i2s_reset = hal_rtl_i2s_reset,
	.hal_i2s_en_ctrl = hal_rtl_i2s_en_ctrl,
	.hal_i2s_clr_intr = hal_rtl_i2s_clr_intr,
	.hal_i2s_clr_all_intr = hal_rtl_i2s_clr_all_intr,
	.hal_i2s_intr_ctrl = hal_rtl_i2s_intr_ctrl,
	.hal_i2s_read_memory_cache_invalidate = hal_rtl_i2s_read_memory_cache_invalidate
};

/**
 *  @brief This is the common interrupt handler for all I2S0.
 *         It read the system register to know the interrupt event
 *         is triggered by which I2S0 device.
 *
 *  @returns void
 */
SECTION_I2S_TEXT
void I2S0_IRQHandler_ram(void)
{
	hal_irq_clear_pending(I2S0_IRQn);

	if ((i2s_group_adapter.pi2s_adapter[0] != (hal_i2s_adapter_t *)NULL) &&
		(i2s_group_adapter.irq_fun[0] != (irq_handler_t)NULL)) {
		i2s_group_adapter.irq_fun[0]((void *)(i2s_group_adapter.pi2s_adapter[0]));
	}

}

/**
 *  @brief This is the common interrupt handler for all I2S1.
 *         It read the system register to know the interrupt event
 *         is triggered by which I2S1 device.
 *
 *  @returns void
 */
SECTION_I2S_TEXT
void I2S1_IRQHandler_ram(void)
{
	hal_irq_clear_pending(I2S1_IRQn);

	if ((i2s_group_adapter.pi2s_adapter[1] != (hal_i2s_adapter_t *)NULL) &&
		(i2s_group_adapter.irq_fun[1] != (irq_handler_t)NULL)) {
		i2s_group_adapter.irq_fun[1]((void *)(i2s_group_adapter.pi2s_adapter[1]));
	}

}

/**
 *  @brief The I2S interrupt handler. It process all interrupt events.
 *
 *  @param[in]  hid The handler ID, it should be the I2S adapter.
 *
 *  @returns void
 */
SECTION_I2S_TEXT
void hal_rtl_i2s_irq_handler(void *hid)
{
	I2S_TypeDef *pi2s_reg;
	hal_i2s_adapter_t *pi2s_adapter;
	hal_i2s_init_dat_t *pi2s_init_dat;
	u32 i;
	u32 i2s_tx_intr, i2s_rx_intr, i2s_tx_intr_event, i2s_rx_intr_event;
	u32 i2s_tx_intr_error, i2s_rx_intr_error;
	u8 i2s_page_num;
	u32 pbuf;

	pi2s_adapter = (hal_i2s_adapter_t *)hid;
	pi2s_init_dat = &pi2s_adapter->init_dat;
	pi2s_reg = (I2S_TypeDef *)pi2s_adapter->base_addr;

	//=== Old IRQ ===
	i2s_page_num = ((pi2s_reg->I2S_PAGE_SIZE_RATE & I2S_MASK_PAGE_NUM) >> I2S_SHIFT_PAGE_NUM) + 1;
	i2s_tx_intr = pi2s_reg->I2S_TX_ISR_STATUS;
	i2s_rx_intr = pi2s_reg->I2S_RX_ISR_STATUS;


	for (i = 0; i < i2s_page_num; i++) { // page 0, 1, 2, 3

		if ((i2s_tx_intr & 0xf0) != 0x00) {
			DBG_I2S_ERR("I2S tx page own control error: 0x%8x \r\n", i2s_tx_intr);
			DBG_I2S_ERR(" Check tx interrupt proccess time(1) \r\n");
		}
		if ((i2s_rx_intr & 0xf0) != 0x00) {
			DBG_I2S_ERR("I2S rx page own control error: 0x%8x \r\n", i2s_rx_intr);
			DBG_I2S_ERR(" Check rx interrupt proccess time(1) \r\n");
		}

		i2s_tx_intr_event = i2s_tx_intr & (1 << pi2s_init_dat->i2s_hw_tx_idx);
		if (i2s_tx_intr_event != 0x00) {
			pbuf = (u32)pi2s_adapter->ptx_page_list[pi2s_init_dat->i2s_hw_tx_idx];
			pi2s_adapter->user_cb.tx_ccb(pi2s_adapter->user_cb.tx_cbid, (char *)pbuf);

			i2s_tx_intr_error = pi2s_reg->I2S_TX_ISR_STATUS;
			if ((i2s_tx_intr_error & 0xf0) != 0x00) {
				DBG_I2S_ERR("I2S tx page own control error: 0x%8x \r\n", i2s_tx_intr_error);
				DBG_I2S_ERR(" Check tx interrupt proccess time(2) \r\n");
			}

			pi2s_reg->I2S_TX_ISR_STATUS = i2s_tx_intr_event;
			i2s_tx_intr &= ~(1 << pi2s_init_dat->i2s_hw_tx_idx);
			pi2s_init_dat->i2s_hw_tx_idx += 1;
			if (pi2s_init_dat->i2s_hw_tx_idx == i2s_page_num) {
				pi2s_init_dat->i2s_hw_tx_idx = 0;
			}
		}

		i2s_rx_intr_event = i2s_rx_intr & (1 << pi2s_init_dat->i2s_hw_rx_idx);
		if (i2s_rx_intr_event != 0x00) {

			pbuf = (u32)pi2s_adapter->prx_page_list[pi2s_init_dat->i2s_hw_rx_idx];

			if (pi2s_adapter->dcache_memory_en == 1) {
				if (pi2s_adapter->dcache_invalidate_by_addr != NULL) {
					// D-Cache sync (Invalidate)
					pi2s_adapter->dcache_invalidate_by_addr((uint32_t *)pbuf, (int32_t)((((pi2s_reg->I2S_PAGE_SIZE_RATE & I2S_MASK_PAGE_SIZE) >> I2S_SHIFT_PAGE_SIZE) + 1) << 2));
				} else {
					DBG_I2S_ERR(" pi2s_adapter->dcache_invalidate_by_addr is null \r\n");
				}
			}
			pi2s_adapter->user_cb.rx_ccb(pi2s_adapter->user_cb.rx_cbid, (char *)pbuf);

			i2s_rx_intr_error = pi2s_reg->I2S_RX_ISR_STATUS;
			if ((i2s_rx_intr_error & 0xf0) != 0x00) {
				DBG_I2S_ERR("I2S rx page own control error: 0x%8x \r\n", i2s_rx_intr_error);
				DBG_I2S_ERR(" Check rx interrupt proccess time(2) \r\n");
			}

			pi2s_reg->I2S_RX_ISR_STATUS = i2s_rx_intr_event;
			i2s_rx_intr &= ~(1 << pi2s_init_dat->i2s_hw_rx_idx);
			pi2s_init_dat->i2s_hw_rx_idx += 1;
			if (pi2s_init_dat->i2s_hw_rx_idx == i2s_page_num) {
				pi2s_init_dat->i2s_hw_rx_idx = 0;
			}
		}
	}

}

/**
 *  @brief To register a IRQ handler for I2S0.
 *
 *  @returns void
 */
SECTION_I2S_TEXT
void hal_rtl_i2s_irq_reg(hal_i2s_adapter_t *pi2s_adapter)
{
	if (pi2s_adapter->dev_num == I2s0_Sel) {
		hal_irq_disable(I2S0_IRQn);
		__ISB();
		hal_irq_set_vector(I2S0_IRQn, (uint32_t)I2S0_IRQHandler_ram);
		hal_irq_clear_pending(I2S0_IRQn);
		hal_irq_enable(I2S0_IRQn);
	} else if (pi2s_adapter->dev_num == I2s1_Sel) {
		hal_irq_disable(I2S1_IRQn);
		__ISB();
		hal_irq_set_vector(I2S1_IRQn, (uint32_t)I2S1_IRQHandler_ram);
		hal_irq_clear_pending(I2S1_IRQn);
		hal_irq_enable(I2S1_IRQn);
	}
}

/**
 *  @brief To un-register the I2S IRQ handler.
 *
 *  @param[in]  pi2s_adapter The I2S adapter.
 *
 *  @returns void
 */
SECTION_I2S_TEXT
void hal_rtl_i2s_irq_unreg(hal_i2s_adapter_t *pi2s_adapter)
{

	if (pi2s_adapter->dev_num == I2s0_Sel) {
		// No any I2S port has IRQ handler, so disable the common interrupt
		hal_irq_disable(I2S0_IRQn);
		__ISB();
	} else if (pi2s_adapter->dev_num == I2s1_Sel) {
		// No any I2S port has IRQ handler, so disable the common interrupt
		hal_irq_disable(I2S1_IRQn);
		__ISB();
	}

}

/**
 *  @brief To enable/disable the bus clock for I2S.
 *
 *  @param[in] index_sel The I2S index. It can be 0 or 1.
 *  @param[in] en  Enable control: 0 is disable, 1 is enable.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
SECTION_I2S_TEXT
HAL_Status hal_rtl_i2s_en_clk_ctrl(i2s_index_sel_t index_sel, BOOL en)
{

	if (index_sel == I2s0_Sel) {
		hal_sys_peripheral_en(I2S0_SYS, en); //I2S0 En and Clock 0x03
	} else if (index_sel == I2s1_Sel) {
		hal_sys_peripheral_en(I2S1_SYS, en); //I2S1 En and Clock 0x0C
	}

	//hal_sys_peripheral_en(LXBUS_SYS, ENABLE); //LXBUS En and Clock
	hal_sys_lxbus_shared_en(LXBUS_CTRL_I2S, en);

	return HAL_OK;

}


/**
 *  @brief Control the I2S bus and hardware clock.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] i2s_func_en  Enable control: 0 is disable, 1 is enable.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
SECTION_I2S_TEXT
HAL_Status hal_rtl_i2s_func_ctrl(hal_i2s_adapter_t *pi2s_adapter, BOOL i2s_func_en)
{
	I2S_TypeDef *pi2s_reg;
	uint8_t reg = 0;

	if (pi2s_adapter->dev_num >= I2s_Max_Id) {
		DBG_I2S_ERR("hal_rtl_i2s_func_ctrl: Invalid I2S Index(&d)\r\n", pi2s_adapter->dev_num);
		return HAL_ERR_PARA;
	}

	if (pi2s_adapter->dev_num == I2s0_Sel) {
		pi2s_adapter->base_addr = (I2S_Type *) I2S0_REG_BASE;
		i2s_group_adapter.irq_fun[0] = hal_rtl_i2s_irq_handler;
		i2s_group_adapter.pi2s_adapter[0] = pi2s_adapter;
		reg = 1;
	} else if (pi2s_adapter->dev_num == I2s1_Sel) {
		pi2s_adapter->base_addr = (I2S_Type *) I2S1_REG_BASE;
		i2s_group_adapter.irq_fun[1] = hal_rtl_i2s_irq_handler;
		i2s_group_adapter.pi2s_adapter[1] = pi2s_adapter;
		reg = 1;
	}

	if (i2s_func_en == ENABLE) {
		hal_rtl_i2s_en_clk_ctrl(pi2s_adapter->dev_num, ENABLE);

		if (reg != 0x00) {
			/* Set I2S Burst Size*/
			pi2s_reg = (I2S_TypeDef *)pi2s_adapter->base_addr;
			pi2s_reg->I2S_CTRL = (pi2s_reg->I2S_CTRL & ~(I2S_MASK_BURST_SIZE)) | ((I2S_BURST12 << I2S_SHIFT_BURST_SIZE) & I2S_MASK_BURST_SIZE);
		}
	} else {
		hal_rtl_i2s_en_clk_ctrl(pi2s_adapter->dev_num, DISABLE);
	}

	if (i2s_func_en == ENABLE) {
		hal_pll_98p304_ctrl(ENABLE, 0);
		hal_pll_45p158_ctrl(ENABLE, 0);
	} else {
		hal_pll_98p304_ctrl(DISABLE, 0);
		hal_pll_45p158_ctrl(DISABLE, 0);
	}

	return HAL_OK;
}

/**
 *  @brief Initialize the I2S hardware and turn on the I2S
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
SECTION_I2S_TEXT
HAL_Status hal_rtl_i2s_init(hal_i2s_adapter_t *pi2s_adapter)
{
	uint8_t i;

	if (pi2s_adapter == NULL) {
		DBG_I2S_ERR("hal_rtl_i2s_init: Null Pointer\r\n");
		return HAL_ERR_PARA;
	}

	if (pi2s_adapter->dev_num >= I2s_Max_Id) {
		DBG_I2S_ERR("hal_rtl_i2s_init: Invalid I2S Index(&d)\r\n", pi2s_adapter->dev_num);
		return HAL_ERR_PARA;
	}

	/*I2S Interrupt Initialization*/
	hal_rtl_i2s_irq_reg(pi2s_adapter);
	for (i = 0; i < I2s_Max_Id; i++) {
		if (i2s_group_adapter.irq_fun[i] != NULL) {
			break;
		}
	}

	hal_irq_set_priority(I2S0_IRQn, I2S0_IRQPri);
	hal_irq_set_priority(I2S1_IRQn, I2S1_IRQPri);

	/*I2S IP function*/
	hal_rtl_i2s_func_ctrl(pi2s_adapter, ENABLE);

	/*I2S Pin Mux Initialization*/

	return HAL_OK;
}

/**
 *  @brief De-initialize of the I2S hardware and turn off the I2S.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
SECTION_I2S_TEXT
HAL_Status hal_rtl_i2s_deinit(hal_i2s_adapter_t *pi2s_adapter)
{
	if (pi2s_adapter == 0) {
		DBG_I2S_ERR("hal_rtl_i2s_deinit: Null Pointer\r\n");
		return HAL_ERR_PARA;
	}

	/*I2S Disable Module*/
	hal_rtl_i2s_en_ctrl(pi2s_adapter, DISABLE);
	hal_rtl_i2s_clear_all_own_bit(pi2s_adapter);

	/*I2S Interrupt DeInitialization*/
	hal_rtl_i2s_irq_unreg(pi2s_adapter);

	/*I2S Pin Mux DeInitialization*/

	/*I2S HAL DeInitialization*/
	hal_rtl_i2s_reset(pi2s_adapter);

	/*I2S IP function*/
	hal_rtl_i2s_func_ctrl(pi2s_adapter, DISABLE);

	return HAL_OK;
}

/**
 *  @brief To enter a critical section of code, mainly it
 *         disable I2S interrupt to prevent race condition.
 *
 *  @returns void
 */
SECTION_I2S_TEXT
void hal_rtl_i2s_enter_critical(void)
{
	if (__get_IPSR() == (I2S0_IRQn + 16)) {
		// In an ISR
		return;
	}

	hal_irq_disable(I2S0_IRQn);
	__ISB();
	i2s_group_adapter.critical_lv++;
	__DSB();

}

/**
 *  @brief To exit a critical code section, it will re-enable the I2S interrupt
 *         only when the exiting critical section is the top level.
 *
 *  @returns void
 */
SECTION_I2S_TEXT
void hal_rtl_i2s_exit_critical(void)
{
	if (__get_IPSR() == (I2S0_IRQn + 16)) {
		// In an ISR
		return;
	}

	if (i2s_group_adapter.critical_lv > 0) {
		i2s_group_adapter.critical_lv--;
		__DSB();
		if (i2s_group_adapter.critical_lv == 0) {
			hal_irq_enable(I2S0_IRQn);
			__ISB();
		}
	}
}

/**
 *  @brief Set the I2S parameter.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] psetting The I2S parameter.
 *                      i2s_burst_size - Burst size for DMA.
 *                      i2s_master - Master or Slave mode.
 *                      i2s_word_len - Word length 16 or 24bits.
 *                      i2s_ch_num - Channel number mono or stereo.
 *                      i2s_page_num - Page number 2~4.
 *                      i2s_page_size - Page Size 1~4096 word.
 *                      i2s_rate - Sample rate.
 *                      i2s_trx_act - Conrtol the tx and rx.
 *                      i2s_byte_swap - Make the data do the byte switch.
 *                      i2s_sck_inv - Invert SCK.
 *                      i2s_ws_swap - Control whether the data appear in "right" or "left" phase of WS clock.
 *                      i2s_format - Interface format.
 *                      i2s_loop_back - Control the loopback mode.
 *                      i2s_edge_sw - Chose to send data at the negative edge or positive edge of SCK.
 *                      i2s_tx_intr_msk - Tx interrupt mask.
 *                      i2s_rx_intr_msk - Rx interrupt mask.
 *
 *  @returns void
 */
SECTION_I2S_TEXT
void hal_rtl_i2s_set_parameter(hal_i2s_adapter_t *pi2s_adapter, hal_i2s_def_setting_t *psetting)
{
	I2S_TypeDef *pi2s_reg = (I2S_TypeDef *)pi2s_adapter->base_addr;
	hal_i2s_init_dat_t *pi2s_init_dat;
	uint32_t temp_reg;
	u32 mask_and;
	u32 set_or;

	if ((psetting->i2s_page_num < 2) || (psetting->i2s_page_num > 4) || (psetting->i2s_page_size < 8)) {
		DBG_I2S_ERR("hal_rtl_i2s_set_parameter: PageNum(%d) valid value is 2~4; PageSize(%d must > 8)\r\n", psetting->i2s_page_num, psetting->i2s_page_size);
	}

	pi2s_init_dat = &pi2s_adapter->init_dat;

	/* Set I2S Burst Size*/
	pi2s_reg->I2S_CTRL &= ~(I2S_MASK_BURST_SIZE);
	pi2s_reg->I2S_CTRL |= (psetting->i2s_burst_size << I2S_SHIFT_BURST_SIZE);

	/* Set I2S Edge Sw*/
	pi2s_reg->I2S_CTRL &= ~(I2S_BIT_EDGE_SW);
	pi2s_reg->I2S_CTRL |= (psetting->i2s_edge_sw << I2S_SHIFT_EDGE_SW);

	/* Disable the I2S first, and reset to default */
	pi2s_reg->I2S_CTRL &= ~(I2S_BIT_IIS_EN);
	pi2s_reg->I2S_CTRL |= I2S_BIT_SW_RSTN;
	pi2s_reg->I2S_CTRL &= ~(I2S_BIT_SW_RSTN);
	pi2s_reg->I2S_CTRL |= I2S_BIT_SW_RSTN;

	/* set 44.1khz clock source, word length, channel number, master or slave, trx act */
	temp_reg = pi2s_reg->I2S_CTRL;
	mask_and = I2S_BIT_BYTE_SWAP | I2S_BIT_LR_SWAP | I2S_BIT_SCK_SWAP | I2S_MASK_FORMAT | I2S_BIT_LOOP_BACK;
	mask_and |= I2S_MASK_WL | I2S_MASK_AUDIO_MONO | I2S_BIT_SLAVE_MODE | I2S_MASK_TX_ACT;
	temp_reg &= ~(mask_and);
	set_or = ((psetting->i2s_byte_swap << I2S_SHIFT_BYTE_SWAP) & I2S_BIT_BYTE_SWAP);
	set_or |= ((psetting->i2s_ws_swap << I2S_SHIFT_LR_SWAP) & I2S_BIT_LR_SWAP);
	set_or |= ((psetting->i2s_sck_inv << I2S_SHIFT_SCK_SWAP) & I2S_BIT_SCK_SWAP);
	set_or |= ((psetting->i2s_format << I2S_SHIFT_FORMAT) & I2S_MASK_FORMAT);
	set_or |= ((psetting->i2s_loop_back << I2S_SHIFT_LOOP_BACK) & I2S_BIT_LOOP_BACK);
	set_or |= ((psetting->i2s_word_len << I2S_SHIFT_WL) & I2S_MASK_WL);
	set_or |= ((psetting->i2s_ch_num << I2S_SHIFT_AUDIO_MONO) & I2S_MASK_AUDIO_MONO);
	set_or |= ((psetting->i2s_master << I2S_SHIFT_SLAVE_MODE) & I2S_BIT_SLAVE_MODE);

	if ((psetting->i2s_loop_back == I2S_LOOPBACK_ENABLE) || (psetting->i2s_ch_num == I2S_CH_5p1)) {
		set_or |= ((I2S_ONLY_TX << I2S_SHIFT_TX_ACT) & I2S_MASK_TX_ACT);
		DBG_I2S_INFO("i2s_def_setting is the loopback mode or 5.1 channel, force the direction is only TX \r\n");
	} else {
		set_or |= ((psetting->i2s_trx_act << I2S_SHIFT_TX_ACT) & I2S_MASK_TX_ACT);
	}
	temp_reg |= set_or;
	pi2s_reg->I2S_CTRL = temp_reg;
	DBG_I2S_INFO("hal_rtl_i2s_set_parameter, ctrl: 0x%8x \r\n", pi2s_reg->I2S_CTRL);

	/* set sample rate */
	hal_rtl_i2s_set_rate(pi2s_adapter, psetting->i2s_rate);
	DBG_I2S_INFO("hal_rtl_i2s_set_parameter, page_size_rate: 0x%8x \r\n", pi2s_reg->I2S_PAGE_SIZE_RATE);

	/* set page size, page number */
	hal_rtl_i2s_set_page_size(pi2s_adapter, (psetting->i2s_page_size / 4 - 1));
	hal_rtl_i2s_set_page_num(pi2s_adapter, psetting->i2s_page_num);

	/* I2S Clear all interrupts first */
	pi2s_init_dat->i2s_tx_idx = 0;
	pi2s_init_dat->i2s_rx_idx = 0;
	pi2s_init_dat->i2s_hw_tx_idx = 0;
	pi2s_init_dat->i2s_hw_rx_idx = 0;
	hal_rtl_i2s_clr_all_intr(pi2s_adapter);

	/* Update interrupts first */
	pi2s_init_dat->i2s_tx_intr_msk = psetting->i2s_tx_intr_msk;
	pi2s_init_dat->i2s_rx_intr_msk = psetting->i2s_rx_intr_msk;
	hal_rtl_i2s_intr_ctrl(pi2s_adapter, psetting->i2s_tx_intr_msk, psetting->i2s_rx_intr_msk);


}

/**
 *  @brief Set the I2S sample rate.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] i2s_sample_rate Sample rate.
 *
 *  @returns void
 */
SECTION_I2S_TEXT
void hal_rtl_i2s_set_rate(hal_i2s_adapter_t *pi2s_adapter, i2s_sample_rate_t i2s_sample_rate)
{
	I2S_TypeDef *pi2s_reg = (I2S_TypeDef *)pi2s_adapter->base_addr;
	uint32_t temp_reg;

	if (i2s_sample_rate & 0x10) {
		pi2s_reg->I2S_PAGE_SIZE_RATE |= I2S_BIT_CLK_SWITCH;
	} else {
		pi2s_reg->I2S_PAGE_SIZE_RATE &= ~(I2S_BIT_CLK_SWITCH);
	}

	temp_reg = pi2s_reg->I2S_PAGE_SIZE_RATE;
	temp_reg &= ~(I2S_MASK_SR);
	temp_reg |= ((i2s_sample_rate << I2S_SHIFT_SR) & I2S_MASK_SR);
	pi2s_reg->I2S_PAGE_SIZE_RATE = temp_reg;
}

/**
 *  @brief Set the I2S buffer.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] i2s_page_size This parameter must be set to a value in the 4~16384 bytes range.
 *  @param[in] i2s_page_num This parameter must be set to a value in the 2~4 range.
 *
 *  @returns void
 */
SECTION_I2S_TEXT
void hal_rtl_i2s_set_dma_buf(hal_i2s_adapter_t *pi2s_adapter, u16 i2s_page_size, i2s_page_num_t i2s_page_num)
{
	I2S_TypeDef *pi2s_reg = (I2S_TypeDef *)pi2s_adapter->base_addr;
	uint32_t temp_reg;

	temp_reg = pi2s_reg->I2S_PAGE_SIZE_RATE;
	temp_reg &= ~(I2S_MASK_PAGE_SIZE | I2S_MASK_PAGE_NUM);
	temp_reg |= ((i2s_page_size << I2S_SHIFT_PAGE_SIZE) & I2S_MASK_PAGE_SIZE);
	temp_reg |= (((i2s_page_num - 1) << I2S_SHIFT_PAGE_NUM) & I2S_MASK_PAGE_NUM);
	pi2s_reg->I2S_PAGE_SIZE_RATE = temp_reg;

	pi2s_adapter->init_dat.i2s_data_byte_cnt = (u32)((i2s_page_size + 1) << 2) * i2s_page_num;

	if (pi2s_adapter->init_dat.i2s_tx_data) {
		pi2s_reg->I2S_PAGE_PTR_TX = (u32)pi2s_adapter->init_dat.i2s_tx_data;
	} else {
		DBG_I2S_ERR(" hal_rtl_i2s_set_dma_buf: pi2s_adapter->init_dat.i2s_tx_data is null \r\n");
	}


	if (pi2s_adapter->init_dat.i2s_rx_data) {
		pi2s_reg->I2S_PAGE_PTR_RX = (u32)pi2s_adapter->init_dat.i2s_rx_data;

		if (pi2s_adapter->dcache_memory_en == 1) {
			if (pi2s_adapter->dcache_clean_by_addr != NULL) {
				pi2s_adapter->dcache_clean_by_addr((uint32_t *)pi2s_reg->I2S_PAGE_PTR_RX, (int32_t)pi2s_adapter->init_dat.i2s_data_byte_cnt);
			} else {
				DBG_I2S_ERR(" pi2s_adapter->dcache_clean_by_addr is null \r\n");
			}
		}
	} else {
		DBG_I2S_ERR(" hal_rtl_i2s_set_dma_buf: pi2s_adapter->init_dat.i2s_rx_data is null \r\n");
	}

}

/**
 *  @brief Get the current tx page address.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *
 *  @returns The address of current tx page or NULL.
 */
SECTION_I2S_TEXT
u8 hal_rtl_i2s_get_tx_page(hal_i2s_adapter_t *pi2s_adapter)
{
	I2S_TypeDef *pi2s_reg = (I2S_TypeDef *)pi2s_adapter->base_addr;
	u32 reg = 0;
	u8 i2s_tx_idx = pi2s_adapter->init_dat.i2s_tx_idx;

	switch (i2s_tx_idx) {

	case 0:
		reg = (pi2s_reg->I2S_TX_PAGE0_OWN & I2S_BIT_P0OWN_TX) >> I2S_SHIFT_P0OWN_TX;
		break;

	case 1:
		reg = (pi2s_reg->I2S_TX_PAGE1_OWN & I2S_BIT_P1OWN_TX) >> I2S_SHIFT_P1OWN_TX;
		break;

	case 2:
		reg = (pi2s_reg->I2S_TX_PAGE2_OWN & I2S_BIT_P2OWN_TX) >> I2S_SHIFT_P2OWN_TX;
		break;

	case 3:
		reg = (pi2s_reg->I2S_TX_PAGE3_OWN & I2S_BIT_P3OWN_TX) >> I2S_SHIFT_P3OWN_TX;
		break;

	default:
		DBG_I2S_INFO("hal_rtl_i2s_get_tx_page, i2s_tx_idx: %d is illegal \r\n", i2s_tx_idx);
		break;

	}

	if (reg == 0) {
		// Cpu control
		return i2s_tx_idx;
	} else {
		// I2S controller control
		return 0xFF;
	}

}

/**
 *  @brief Get the current rx page address.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *
 *  @returns The address of current rx page or NULL.
 */
SECTION_I2S_TEXT
u8 hal_rtl_i2s_get_rx_page(hal_i2s_adapter_t *pi2s_adapter)
{
	I2S_TypeDef *pi2s_reg = (I2S_TypeDef *)pi2s_adapter->base_addr;
	u32 reg = 0;
	u8 i2s_rx_idx = pi2s_adapter->init_dat.i2s_rx_idx;

	switch (i2s_rx_idx) {

	case 0:
		reg = (pi2s_reg->I2S_RX_PAGE0_OWN & I2S_BIT_P0OWN_RX) >> I2S_SHIFT_P0OWN_RX;
		break;

	case 1:
		reg = (pi2s_reg->I2S_RX_PAGE1_OWN & I2S_BIT_P1OWN_RX) >> I2S_SHIFT_P1OWN_RX;
		break;

	case 2:
		reg = (pi2s_reg->I2S_RX_PAGE2_OWN & I2S_BIT_P2OWN_RX) >> I2S_SHIFT_P2OWN_RX;
		break;

	case 3:
		reg = (pi2s_reg->I2S_RX_PAGE3_OWN & I2S_BIT_P3OWN_RX) >> I2S_SHIFT_P3OWN_RX;
		break;

	default:
		DBG_I2S_INFO("hal_rtl_i2s_get_rx_page, i2s_rx_idx: %d is illegal \r\n", i2s_rx_idx);
		break;

	}

	if (reg == 0) {
		// Cpu control
		return i2s_rx_idx;
	} else {
		// I2S controller control
		return 0xFF;
	}

}

/**
 *  @brief Set the current tx page own.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] page_idx The page index.
 *
 *  @returns void
 */
SECTION_I2S_TEXT
void hal_rtl_i2s_page_send(hal_i2s_adapter_t *pi2s_adapter, u8 page_idx)
{
	I2S_TypeDef *pi2s_reg = (I2S_TypeDef *)pi2s_adapter->base_addr;
	u8 i2s_tx_idx = pi2s_adapter->init_dat.i2s_tx_idx;
	u8 i2s_page_num;

	i2s_page_num = (pi2s_reg->I2S_PAGE_SIZE_RATE & I2S_MASK_PAGE_NUM) >> I2S_SHIFT_PAGE_NUM;

	if (i2s_tx_idx != page_idx) {
		DBG_I2S_ERR("hal_rtl_i2s_page_send: UnExpected Page Index. TxPage=%d, Expected:%d\r\n",
					page_idx, i2s_tx_idx);
	}

	if (pi2s_adapter->dcache_memory_en == 1) {
		if (pi2s_adapter->dcache_clean_by_addr != NULL) {
			pi2s_adapter->dcache_clean_by_addr((uint32_t *)pi2s_adapter->ptx_page_list[page_idx],
											   (int32_t)((pi2s_adapter->base_addr->page_size_rate_b.page_size + 1) << 2));
		} else {
			DBG_I2S_ERR(" pi2s_adapter->dcache_clean_by_addr is null \r\n");
		}
	}

	switch (page_idx) {

	case 0:
		pi2s_reg->I2S_TX_PAGE0_OWN |= I2S_BIT_P0OWN_TX;
		break;

	case 1:
		pi2s_reg->I2S_TX_PAGE1_OWN |= I2S_BIT_P1OWN_TX;
		break;

	case 2:
		pi2s_reg->I2S_TX_PAGE2_OWN |= I2S_BIT_P2OWN_TX;
		break;

	case 3:
		pi2s_reg->I2S_TX_PAGE3_OWN |= I2S_BIT_P3OWN_TX;
		break;

	default:
		DBG_I2S_INFO("hal_rtl_i2s_page_send, page_idx: %d is illegal \r\n", page_idx);
		break;

	}

	i2s_tx_idx = page_idx + 1;
	if (i2s_tx_idx > i2s_page_num) {
		i2s_tx_idx = 0;
	}
	pi2s_adapter->init_dat.i2s_tx_idx = i2s_tx_idx;

}

/**
 *  @brief Set the current rx page own.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *
 *  @return     HAL_NOT_READY
 *  @return     HAL_OK
 */
SECTION_I2S_TEXT
HAL_Status hal_rtl_i2s_page_recv(hal_i2s_adapter_t *pi2s_adapter)
{
	I2S_TypeDef *pi2s_reg = (I2S_TypeDef *)pi2s_adapter->base_addr;
	u32 reg = 0;
	u8 i2s_rx_idx = pi2s_adapter->init_dat.i2s_rx_idx;
	u8 i2s_page_num;

	i2s_page_num = (pi2s_reg->I2S_PAGE_SIZE_RATE & I2S_MASK_PAGE_NUM) >> I2S_SHIFT_PAGE_NUM;

	switch (i2s_rx_idx) {

	case 0:
		reg = (pi2s_reg->I2S_RX_PAGE0_OWN & I2S_BIT_P0OWN_RX) >> I2S_SHIFT_P0OWN_RX;
		break;

	case 1:
		reg = (pi2s_reg->I2S_RX_PAGE1_OWN & I2S_BIT_P1OWN_RX) >> I2S_SHIFT_P1OWN_RX;
		break;

	case 2:
		reg = (pi2s_reg->I2S_RX_PAGE2_OWN & I2S_BIT_P2OWN_RX) >> I2S_SHIFT_P2OWN_RX;
		break;

	case 3:
		reg = (pi2s_reg->I2S_RX_PAGE3_OWN & I2S_BIT_P3OWN_RX) >> I2S_SHIFT_P3OWN_RX;
		break;

	default:
		DBG_I2S_INFO("hal_rtl_i2s_page_recv, i2s_rx_idx: %d is illegal \r\n", i2s_rx_idx);
		break;

	}

	if (reg != 0) {
		DBG_I2S_ERR("hal_rtl_i2s_page_recv: No Idle Rx Page\r\n");
		return HAL_NOT_READY;
	}

	switch (i2s_rx_idx) {

	case 0:
		pi2s_reg->I2S_RX_PAGE0_OWN |= I2S_BIT_P0OWN_RX;
		break;

	case 1:
		pi2s_reg->I2S_RX_PAGE1_OWN |= I2S_BIT_P1OWN_RX;
		break;

	case 2:
		pi2s_reg->I2S_RX_PAGE2_OWN |= I2S_BIT_P2OWN_RX;
		break;

	case 3:
		pi2s_reg->I2S_RX_PAGE3_OWN |= I2S_BIT_P3OWN_RX;
		break;

	default:
		DBG_I2S_INFO("hal_rtl_i2s_page_recv, i2s_rx_idx: %d is illegal \r\n", i2s_rx_idx);
		break;

	}

	i2s_rx_idx = i2s_rx_idx + 1;
	if (i2s_rx_idx > i2s_page_num) {
		i2s_rx_idx = 0;
	}
	pi2s_adapter->init_dat.i2s_rx_idx = i2s_rx_idx;

	return HAL_OK;

}

/**
 *  @brief Clean all page own of tx and rx.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *
 *  @returns void
 */
SECTION_I2S_TEXT
void hal_rtl_i2s_clear_all_own_bit(hal_i2s_adapter_t *pi2s_adapter)
{
	I2S_TypeDef *pi2s_reg = (I2S_TypeDef *)pi2s_adapter->base_addr;

	pi2s_reg->I2S_RX_PAGE0_OWN = 0x00;
	pi2s_reg->I2S_TX_PAGE0_OWN = 0x00;

	pi2s_reg->I2S_RX_PAGE1_OWN = 0x00;
	pi2s_reg->I2S_TX_PAGE1_OWN = 0x00;

	pi2s_reg->I2S_RX_PAGE2_OWN = 0x00;
	pi2s_reg->I2S_TX_PAGE2_OWN = 0x00;

	pi2s_reg->I2S_RX_PAGE3_OWN = 0x00;
	pi2s_reg->I2S_TX_PAGE3_OWN = 0x00;
}

/**
 *  @brief Reset the I2S.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *
 *  @returns void
 */
SECTION_I2S_TEXT
void hal_rtl_i2s_reset(hal_i2s_adapter_t *pi2s_adapter)
{
	I2S_TypeDef *pi2s_reg = (I2S_TypeDef *)pi2s_adapter->base_addr;
	hal_i2s_init_dat_t *pi2s_init_dat = &pi2s_adapter->init_dat;

	hal_rtl_i2s_clear_all_own_bit(pi2s_adapter);

	/* Disable the I2S first, and reset to default */
	pi2s_reg->I2S_CTRL &= ~(I2S_BIT_IIS_EN);
	pi2s_reg->I2S_CTRL |= I2S_BIT_SW_RSTN;
	pi2s_reg->I2S_CTRL &= ~(I2S_BIT_SW_RSTN);
	pi2s_reg->I2S_CTRL |= I2S_BIT_SW_RSTN;
	pi2s_init_dat->i2s_tx_idx = 0;
	pi2s_init_dat->i2s_rx_idx = 0;
	pi2s_init_dat->i2s_hw_tx_idx = 0;
	pi2s_init_dat->i2s_hw_rx_idx = 0;
	/* I2S Clear all interrupts first */
	hal_rtl_i2s_clr_all_intr(pi2s_adapter);

}

/**
 *  @brief Enable or disable the I2S.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
SECTION_I2S_TEXT
void hal_rtl_i2s_en_ctrl(hal_i2s_adapter_t *pi2s_adapter, BOOL en)
{
	I2S_TypeDef *pi2s_reg = (I2S_TypeDef *)pi2s_adapter->base_addr;
	hal_i2s_init_dat_t *pi2s_init_dat = &pi2s_adapter->init_dat;

	if (en == 1) {
		pi2s_reg->I2S_TX_ISR_EN = pi2s_init_dat->i2s_tx_intr_msk;
		pi2s_reg->I2S_RX_ISR_EN = pi2s_init_dat->i2s_rx_intr_msk;
		pi2s_reg->I2S_CTRL |= I2S_BIT_IIS_EN;
	} else {
		pi2s_reg->I2S_TX_ISR_EN = 0;
		pi2s_reg->I2S_RX_ISR_EN = 0;
		pi2s_reg->I2S_CTRL &= ~(I2S_BIT_IIS_EN);
	}
}

/**
 *  @brief Clean the I2S interrupt status of enabling the interrupt.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *
 *  @returns void
 */
SECTION_I2S_TEXT
void hal_rtl_i2s_clr_intr(hal_i2s_adapter_t *pi2s_adapter)
{
	I2S_TypeDef *pi2s_reg = (I2S_TypeDef *)pi2s_adapter->base_addr;

	pi2s_reg->I2S_TX_ISR_STATUS = pi2s_adapter->init_dat.i2s_tx_intr_clr;
	pi2s_reg->I2S_RX_ISR_STATUS = pi2s_adapter->init_dat.i2s_rx_intr_clr;
}

/**
 *  @brief Clean all I2S interrupt status.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *
 *  @returns void
 */
SECTION_I2S_TEXT
void hal_rtl_i2s_clr_all_intr(hal_i2s_adapter_t *pi2s_adapter)
{
	I2S_TypeDef *pi2s_reg = (I2S_TypeDef *)pi2s_adapter->base_addr;
	pi2s_reg->I2S_TX_ISR_STATUS = 0x1ff;
	pi2s_reg->I2S_RX_ISR_STATUS = 0x1ff;
}

/**
 *  @brief Control the I2S interupt event by tx and rx mask.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *  @param[in] i2s_tx_intr_msk Tx interrupt mask.
 *  @param[in] i2s_rx_intr_msk Rx interrupt mask.
 *
 *  @returns void
 */
SECTION_I2S_TEXT
void hal_rtl_i2s_intr_ctrl(hal_i2s_adapter_t *pi2s_adapter, i2s_tx_imr_t i2s_tx_intr_msk, i2s_rx_imr_t i2s_rx_intr_msk)
{
	I2S_TypeDef *pi2s_reg = (I2S_TypeDef *)pi2s_adapter->base_addr;
	pi2s_reg->I2S_TX_ISR_EN = i2s_tx_intr_msk;
	pi2s_reg->I2S_RX_ISR_EN = i2s_rx_intr_msk;
}

/**
 *  @brief Make the rx memory invalidate D-Cache.
 *
 *  @param[in] pi2s_adapter The I2S adapter.
 *
 *  @returns void
 */
SECTION_I2S_TEXT
void hal_rtl_i2s_read_memory_cache_invalidate(hal_i2s_adapter_t *pi2s_adapter)
{
	I2S_TypeDef *pi2s_reg = (I2S_TypeDef *)pi2s_adapter->base_addr;

	if (pi2s_adapter->dcache_memory_en == 1) {
		if (pi2s_adapter->dcache_invalidate_by_addr != NULL) {
			pi2s_adapter->dcache_invalidate_by_addr((uint32_t *)pi2s_reg->I2S_PAGE_PTR_RX, (int32_t)pi2s_adapter->init_dat.i2s_data_byte_cnt);
		} else {
			DBG_I2S_ERR(" pi2s_adapter->dcache_invalidate_by_addr is null \r\n");
		}
	}
}

/** @} */ /* End of group hs_hal_i2s_rom_func */
/// @endcond /* End of condition DOXYGEN_ROM_HAL_API */

/** @} */ /* End of group hs_hal_i2s */



