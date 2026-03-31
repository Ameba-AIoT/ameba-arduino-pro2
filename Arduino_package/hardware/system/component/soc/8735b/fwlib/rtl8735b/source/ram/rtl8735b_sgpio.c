/**************************************************************************//**
 * @file     rtl8735b_sgpio.c
 * @brief    This file implements the SGPIO HAL functions in ROM.
 *
 * @version  V1.00
 * @date     2020-08-13
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
#include "hal_irq.h"
#include "hal_gdma.h"
#include "rtl8735b_sgpio_type.h"
#include "hal_cache.h"
#include "hal_sys_ctrl.h"
#include "hal_sys_ctrl_nsc.h"

#if CONFIG_SGPIO_EN

#define SECTION_SGPIO_TEXT           //SECTION(".ram.hal_sgpio.text")
#define SECTION_SGPIO_DATA           //SECTION(".ram.hal_sgpio.data")
#define SECTION_SGPIO_RODATA         //SECTION(".ram.hal_sgpio.rodata")
#define SECTION_SGPIO_BSS            //SECTION(".ram.hal_sgpio.bss")
#define SECTION_SGPIO_STUBS          //SECTION(".ram.hal_sgpio.stubs")

#if !defined(CONFIG_BUILD_NONSECURE)

#undef SGPIO_REG_BASE
#define SGPIO_REG_BASE (SGPIO_S_BASE)

#else

#undef SGPIO_REG_BASE
#define SGPIO_REG_BASE (SGPIO_BASE)

#endif


/**
 * @addtogroup hs_hal_sgpio PCM
 * @{
 */

/**
  * @brief The global common data structure to store common resource
  *        for all SGPIO adapters.
  */
SECTION_SGPIO_BSS hal_sgpio_group_adapter_t sgpio_group_adapter;

/**
  * @brief SGPIO Pin mux table for SGPIO_TX and SGPIO_RX pin
  */
SECTION_SGPIO_RODATA const uint8_t sgpio_pin[] = {
// TBD: the pin names need to be corrected
	PIN_F15, PIN_F14, 0xFF,   /* SGPIO0 S0 */
	PIN_F15, PIN_F14, 0xFF,   /* SGPIO0 S1 */
	PIN_F15, PIN_F14, 0xFF, /* SGPIO0 S2 */
	0xFF, 0xFF, 0xFF,

	PIN_F15, PIN_F14, 0xFF,   /* SGPIO1 S0 */
	PIN_F15, PIN_F14, 0xFF,   /* SGPIO1 S1 */
	PIN_F15, PIN_F14, 0xFF, /* SGPIO1 S2 */
	0xFF, 0xFF, 0xFF,

	PIN_F15, PIN_F14, 0xFF,   /* SGPIO2 S0 */
	PIN_F15, PIN_F14, 0xFF,   /* SGPIO2 S1 */
	PIN_F15, PIN_F14, 0xFF,  /* SGPIO2 S2 */
	0xFF, 0xFF, 0xFF
};

/// @cond DOXYGEN_ROM_HAL_API

/**
 * @addtogroup hs_hal_sgpio_rom_func SGPIO HAL ROM APIs.
 * @ingroup hs_hal_sgpio
 * @{
 * @brief The SGPIO HAL ROM APIs. The user application(in RAM space) should not call these APIs directly.
 *        There is another set of SGPIO HAL APIs in the RAM space is provided for the user application.
 */

/**
  * @brief The stubs functions table to exports SGPIO HAL functions in ROM.
  */
SECTION_SGPIO_STUBS const hal_sgpio_func_stubs_t hal_sgpio_stubs = {
	.psgpio_group_adapter = &sgpio_group_adapter,
	.psgpio_pin = sgpio_pin,
	.hal_sgpio_irq_handler = hal_rom_sgpio_irq_handler,
	.hal_sgpio_irq_reg = hal_rom_sgpio_irq_reg,
	.hal_sgpio_unreg = hal_rom_sgpio_unreg,
	.hal_sgpio_reg_cb = hal_rom_sgpio_reg_cb,
	.hal_sgpio_unreg_cb = hal_rom_sgpio_unreg_cb,
	.hal_sgpio_en_ctrl = hal_rom_sgpio_en_ctrl,
	.hal_sgpio_init = hal_rom_sgpio_init,
	.hal_sgpio_deinit = hal_rom_sgpio_deinit,
	.hal_sgpio_enter_critical = hal_rom_sgpio_enter_critical,
	.hal_sgpio_exit_critical = hal_rom_sgpio_exit_critical,
	.hal_sgpio_set_rxtc_stop_ctrl = hal_rom_sgpio_set_rxtc_stop_ctrl,
	.hal_sgpio_get_rxtc_stop_ctrl = hal_rom_sgpio_get_rxtc_stop_ctrl,
	.hal_sgpio_set_rxtc_reset_ctrl = hal_rom_sgpio_set_rxtc_reset_ctrl,
	.hal_sgpio_get_rxtc_reset_ctrl = hal_rom_sgpio_get_rxtc_reset_ctrl,
	.hal_sgpio_set_rxtc_match_value = hal_rom_sgpio_set_rxtc_match_value,
	.hal_sgpio_set_rxtc_int = hal_rom_sgpio_set_rxtc_int,
	.hal_sgpio_set_capture_ctrl = hal_rom_sgpio_set_capture_ctrl,
	.hal_sgpio_set_capture_compare = hal_rom_sgpio_set_capture_compare,
	.hal_sgpio_set_capture_int = hal_rom_sgpio_set_capture_int,
	.hal_sgpio_set_multc_stop_ctrl = hal_rom_sgpio_set_multc_stop_ctrl,
	.hal_sgpio_get_multc_stop_ctrl = hal_rom_sgpio_get_multc_stop_ctrl,
	.hal_sgpio_set_multc_reset_ctrl = hal_rom_sgpio_set_multc_reset_ctrl,
	.hal_sgpio_get_multc_reset_ctrl = hal_rom_sgpio_get_multc_reset_ctrl,
	.hal_sgpio_set_multc_match_value = hal_rom_sgpio_set_multc_match_value,
	.hal_sgpio_set_multc_match_event0_int = hal_rom_sgpio_set_multc_match_event0_int,
	.hal_sgpio_set_multc_match_group = hal_rom_sgpio_set_multc_match_group,
	.hal_sgpio_set_multc_fifo_value = hal_rom_sgpio_set_multc_fifo_value,
	.hal_sgpio_set_rxtc_external_match = hal_rom_sgpio_set_rxtc_external_match,
	.hal_sgpio_set_multc_external_match = hal_rom_sgpio_set_multc_external_match,
	.hal_sgpio_set_multc_match_event0_cnt_int = hal_rom_sgpio_set_multc_match_event0_cnt_int,
	.hal_sgpio_set_multc_match_event0_cnt = hal_rom_sgpio_set_multc_match_event0_cnt,
	.hal_sgpio_init_rxdata_time_sampling = hal_rom_sgpio_init_rxdata_time_sampling,
	.hal_sgpio_deinit_rxdata_time_sampling = hal_rom_sgpio_deinit_rxdata_time_sampling,
	.hal_sgpio_init_rxdata_capture_compare = hal_rom_sgpio_init_rxdata_capture_compare,
	.hal_sgpio_deinit_rxdata_capture_compare = hal_rom_sgpio_deinit_rxdata_capture_compare,
	.hal_sgpio_set_rxdata_load_int = hal_rom_sgpio_set_rxdata_load_int,
	.hal_sgpio_set_rxdata_prebuf_bit_shift_int = hal_rom_sgpio_set_rxdata_prebuf_bit_shift_int,
	.hal_sgpio_reset_rxdata = hal_rom_sgpio_reset_rxdata,
	.hal_sgpio_set_rxdata_match_int = hal_rom_sgpio_set_rxdata_match_int,
	.hal_sgpio_set_txdata_bit_length_int = hal_rom_sgpio_set_txdata_bit_length_int,
	.hal_sgpio_set_txdata_prebuf_bit_shift_int = hal_rom_sgpio_set_txdata_prebuf_bit_shift_int,
	.hal_sgpio_reset_txdata = hal_rom_sgpio_reset_txdata,
	.hal_sgpio_set_time_to_rxtc = hal_rom_sgpio_set_time_to_rxtc,
	.hal_sgpio_set_time_to_multc = hal_rom_sgpio_set_time_to_multc,
	.hal_sgpio_set_rxtc_to_time = hal_rom_sgpio_set_rxtc_to_time,
	.hal_sgpio_set_multc_to_time = hal_rom_sgpio_set_multc_to_time,
	.hal_sgpio_clean_status = hal_rom_sgpio_clean_status,
	.hal_sgpio_update_rxtcmr = hal_rom_sgpio_update_rxtcmr,
	.hal_sgpio_update_multcmr = hal_rom_sgpio_update_multcmr,
	.hal_sgpio_rxtc_timer_mode = hal_rom_sgpio_rxtc_timer_mode,
	.hal_sgpio_multc_timer_mode = hal_rom_sgpio_multc_timer_mode,
	.hal_sgpio_multc_counter_mode = hal_rom_sgpio_multc_counter_mode,
	.hal_sgpio_rxtc_timer_match_output = hal_rom_sgpio_rxtc_timer_match_output,
	.hal_sgpio_multc_timer_counter_match_output = hal_rom_sgpio_multc_timer_counter_match_output,
	.hal_sgpio_rxtc_capture_mode = hal_rom_sgpio_rxtc_capture_mode,
	.hal_sgpio_rxtc_capture_timeout = hal_rom_sgpio_rxtc_capture_timeout,
	.hal_sgpio_rxtc_capture_monitor = hal_rom_sgpio_rxtc_capture_monitor,
	.hal_sgpio_get_rxtc_capture_time = hal_rom_sgpio_get_rxtc_capture_time,
	.hal_sgpio_init_rxdata_capture_compare_time = hal_rom_sgpio_init_rxdata_capture_compare_time,
	.hal_sgpio_sampling_rxdata = hal_rom_sgpio_sampling_rxdata,
	.hal_sgpio_get_input_rxdata = hal_rom_sgpio_get_input_rxdata,
	.hal_sgpio_get_arrange_rxdata =  hal_rom_sgpio_get_arrange_rxdata,
	.hal_sgpio_capture_compare_rxdata = hal_rom_sgpio_capture_compare_rxdata,
	.hal_sgpio_txdata_bit_symbol =  hal_rom_sgpio_txdata_bit_symbol,
	.hal_sgpio_txdata =  hal_rom_sgpio_txdata,
	.hal_sgpio_txdata_bit_length_irq =  hal_rom_sgpio_txdata_bit_length_irq,
	.hal_sgpio_send_txdata = hal_rom_sgpio_send_txdata,
	.hal_sgpio_reset_receive_rxdata = hal_rom_sgpio_reset_receive_rxdata,
	.hal_sgpio_disable_rxdata_match = hal_rom_sgpio_disable_rxdata_match,
	.hal_sgpio_monitor_rxdata = hal_rom_sgpio_monitor_rxdata,
	.hal_sgpio_multc_fifo_reset = hal_rom_sgpio_multc_fifo_reset,
	.hal_sgpio_dma_match_output_irq_handle = hal_rom_sgpio_dma_match_output_irq_handle,
	.hal_sgpio_dma_match_output_init = hal_rom_sgpio_dma_match_output_init,
	.hal_sgpio_dma_match_output_deinit = hal_rom_sgpio_dma_match_output_deinit,
	.hal_sgpio_dma_handshake_init = hal_rom_sgpio_dma_handshake_init,
	.hal_sgpio_dma_preload_data = hal_rom_sgpio_dma_preload_data,
	.hal_sgpio_dma_send_start = hal_rom_sgpio_dma_send_start,
	.hal_sgpio_dma_time_to_multc = hal_rom_sgpio_dma_time_to_multc
};

/**
 *  @brief This is the common interrupt handler for all SGPIOs.
 *         It read the system register to know the interrupt event
 *         is triggered by which SGPIO device.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void SGPIO_IRQHandler_ram(void)
{
	uint8_t i;

	hal_irq_clear_pending(SGPIO_IRQn);

	for (i = 0; i < Sgpio_Max_Id; i++) {
		if ((sgpio_group_adapter.psgpio_adapter[i] != (hal_sgpio_adapter_t *)NULL) &&
			(sgpio_group_adapter.irq_fun[i] != (irq_handler_t)NULL)) {
			sgpio_group_adapter.irq_fun[i]((void *)(sgpio_group_adapter.psgpio_adapter[i]));
		}
	}
}

/**
 *  @brief The SGPIO interrupt handler. It process all interrupt events.
 *
 *  @param[in]  hid The handler ID, it should be the sgpio adapter.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_irq_handler(void *hid)
{
	hal_sgpio_adapter_t *psgpio_adp;
	SGPIO_TypeDef *psgpio_reg;
	u8 irq_bit_shift;
	u32 bit_shift_temp;
	u32 sgpio_is_reg;

	psgpio_adp = (hal_sgpio_adapter_t *)hid;
	psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;

	sgpio_is_reg =  psgpio_reg->SGPIO_IS;
	psgpio_reg->SGPIO_IS = sgpio_is_reg;
	sgpio_is_reg = sgpio_is_reg & ~(psgpio_reg->SGPIO_IM);

	for (irq_bit_shift = 0 ; irq_bit_shift < Max_Sgpio_Sft; irq_bit_shift++) {
		if (psgpio_adp->irq_user_cb[irq_bit_shift] != NULL) {
			bit_shift_temp = (1 << irq_bit_shift);
			if ((sgpio_is_reg & bit_shift_temp) == bit_shift_temp) {
				psgpio_adp->irq_user_cb[irq_bit_shift](psgpio_adp->user_arg[irq_bit_shift]);
			}
		}
	}

}

/**
 *  @brief To register a IRQ handler for the SGPIO.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_irq_reg(void)
{
	uint8_t i;

	for (i = 0; i < Sgpio_Max_Id; i++) {
		if (sgpio_group_adapter.irq_fun[i] != NULL) {
			break;
		}
	}

	if (i == Sgpio_Max_Id) {
		hal_irq_disable(SGPIO_IRQn);
		__ISB();

		// Register SGPIO common IRQ handler
		hal_irq_set_vector(SGPIO_IRQn, (uint32_t)SGPIO_IRQHandler_ram);
		hal_irq_clear_pending(SGPIO_IRQn);
		hal_irq_enable(SGPIO_IRQn);
	}
}

/**
 *  @brief To un-register the SGPIO IRQ handler.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_unreg(hal_sgpio_adapter_t *psgpio_adp)
{
	uint8_t i;

	sgpio_group_adapter.irq_fun[psgpio_adp->sgpio_index] = (irq_handler_t)NULL;
	for (i = 0; i < Sgpio_Max_Id; i++) {
		if (sgpio_group_adapter.irq_fun[i] != NULL) {
			break;
		}
	}

	if (i == Sgpio_Max_Id) {
		// No any SGPIO port has IRQ handler, so disable the common interrupt
		hal_irq_disable(SGPIO_IRQn);
		__ISB();
	}


}

/**
 *  @brief Register the callback function and argument of the interrupt event.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  callback The callback function.
 *  @param[in]  arg The callback argument.
 *  @param[in]  irq_shift The interrupt event number.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_reg_cb(hal_sgpio_adapter_t *psgpio_adp, sgpio_irq_user_cb_t callback, void *arg, sgpio_irq_shift_t irq_shift)
{
	if (callback != NULL) {
		psgpio_adp->irq_user_cb[irq_shift] = callback;
		psgpio_adp->user_arg[irq_shift] = arg;
	} else {
		psgpio_adp->irq_user_cb[irq_shift] = NULL;
		psgpio_adp->user_arg[irq_shift] = NULL;
	}
}

/**
 *  @brief Cancel the callback function and argument of the interrupt event.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  irq_shift The interrupt event number.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_unreg_cb(hal_sgpio_adapter_t *psgpio_adp, sgpio_irq_shift_t irq_shift)
{
	psgpio_adp->irq_user_cb[irq_shift] = NULL;
	psgpio_adp->user_arg[irq_shift] = NULL;
}

/**
 *  @brief To enable or disable SGPIO for the platform.
 *
 *  @param[in] sgpio_index The SGPIO index. It can be 0 .. 2.
 *  @param[in] en  Enable control: 0: disable, 1: enable.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
SECTION_SGPIO_TEXT
HAL_Status hal_rom_sgpio_en_ctrl(sgpio_index_sel_t sgpio_index, BOOL en)
{
	hal_sys_peripheral_en(SGPIO_SYS, en);
	//*((uint32_t*)(0x40000800 + 0x138)) = 0xF0;
	//*((uint32_t*)(0x50000800 + 0x138)) = 0xF0;

	return HAL_OK;
}

/**
 *  @brief Initialize the sgpio hardware and turn on the SGPIO
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  sgpio_index The SGPIO index. It can be 0 .. 2.
 *  @param[in]  pin_sel sgpio pin mux.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
SECTION_SGPIO_TEXT
HAL_Status hal_rom_sgpio_init(hal_sgpio_adapter_t *psgpio_adp, sgpio_index_sel_t sgpio_index)
{
	uint8_t i;
	SGPIO_TypeDef *psgpio_reg;
	HAL_Status ret = HAL_OK;

	if (psgpio_adp == NULL) {
		//dbg_printf("hal_sgpio_init_rtl8195bhp: psgpio_adp is null \r\n");
		return HAL_ERR_PARA;
	}

	if (sgpio_index >= Sgpio_Max_Id) {
		//dbg_printf("hal_sgpio_init_rtl8195bhp: Invalid sgpio Index(&d)\r\n", sgpio_index);
		return HAL_ERR_PARA;
	}

	psgpio_adp->sgpio_sclk_ns = SGPIO_HP_SCLK_NS;

	hal_rom_sgpio_irq_reg();
	for (i = 0; i < Sgpio_Max_Id; i++) {
		if (sgpio_group_adapter.irq_fun[i] != NULL) {
			break;
		}
	}

	if (i == Sgpio_Max_Id) {
		hal_irq_set_priority(SGPIO_IRQn, SGPIO_IRQPri);
	}

	switch (psgpio_adp->sgpio_index) {
	case Sgpio0_Sel:
		psgpio_adp->base_addr = (SGPIO_Type *)SGPIO_REG_BASE;
		sgpio_group_adapter.irq_fun[0] = hal_rom_sgpio_irq_handler;
		sgpio_group_adapter.psgpio_adapter[0] = psgpio_adp;
		break;

	default:
		return HAL_ERR_PARA;
	}


	hal_rom_sgpio_en_ctrl(sgpio_index, ENABLE);

	//Reg dcache app
	psgpio_adp->dcache_clean_by_addr = hal_cache_stubs.dcache_clean_by_addr;

	// Clear all interrupt status: write clear
	psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	psgpio_reg->SGPIO_IS = 0x0FFF;

	return ret;
}

/**
 *  @brief De-initialize of the sgpio hardware and turn off the SGPIO.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_deinit(hal_sgpio_adapter_t *psgpio_adp)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;

	// Clear all interrupt status: write clear
	psgpio_reg->SGPIO_IS = 0x0FFF;

	hal_rom_sgpio_en_ctrl(psgpio_adp->sgpio_index, DISABLE);
	hal_rom_sgpio_unreg(psgpio_adp);
}

/**
*  @brief To enter a critical code section, mainly it
*         disable the SGPIO interrupt to prevent race condition.
*
*  @returns void
*/
SECTION_SGPIO_TEXT
void hal_rom_sgpio_enter_critical(void)
{
	if (__get_IPSR() == (SGPIO_IRQn + 16)) {
		// In an ISR
		return;
	}

	hal_irq_disable(SGPIO_IRQn);
	__ISB();
	sgpio_group_adapter.critical_lv++;
	__DSB();

}

/**
 *  @brief To exit a critical code section, it will re-enable the SGPIO interrupt
 *         only when the exiting critical section is the top level.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_exit_critical(void)
{
	if (__get_IPSR() == (SGPIO_IRQn + 16)) {
		// In an ISR
		return;
	}

	if (sgpio_group_adapter.critical_lv > 0) {
		sgpio_group_adapter.critical_lv--;
		__DSB();
		if (sgpio_group_adapter.critical_lv == 0) {
			hal_irq_enable(SGPIO_IRQn);
			__ISB();
		}
	}

}

/**
 *  @brief  Set the stop events to make the rxtc timer stop.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  prxtc_event The stop events. 0: disable, 1: enable.
 *                      rxtc_match_event0 - This event is that the rx timer value matches rx match register 0.
 *                      rxtc_match_event1 - This event is that the rx timer value matches rx match register 1.
 *                      rxtc_match_event2 - This event is that the rx timer value matches rx match register 2.
 *                      multc_match_event0 - This event is that the multc timer value matches Multiple Match Register 0.
 *                      rx_postc_zero - This event is that the rxpostc register becomes 0.
 *                      capture_event - This event is that happen the capture.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_set_rxtc_stop_ctrl(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_event_t *prxtc_event)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u32 temp_reg;

	temp_reg = psgpio_reg->SGPIO_RXMC;
	temp_reg &= ~(SGPIO_BIT_RX_MR0STOP_EN | SGPIO_BIT_RX_MR1STOP_EN | SGPIO_BIT_RX_MR2STOP_EN | SGPIO_BIT_RX_POSSTOP_EN);
	temp_reg |= (prxtc_event->rxtc_match_event0 << SGPIO_SHIFT_RX_MR0STOP_EN);
	temp_reg |= (prxtc_event->rxtc_match_event1 << SGPIO_SHIFT_RX_MR1STOP_EN);
	temp_reg |= (prxtc_event->rxtc_match_event2 << SGPIO_SHIFT_RX_MR2STOP_EN);
	temp_reg |= (prxtc_event->rx_postc_zero << SGPIO_SHIFT_RX_POSSTOP_EN);
	psgpio_reg->SGPIO_RXMC = temp_reg;

	temp_reg = psgpio_reg->SGPIO_MULMC;
	temp_reg &= ~(SGPIO_BIT_MUL_MR0RXSTOP_EN);
	temp_reg |= (prxtc_event->multc_match_event0 << SGPIO_SHIFT_MUL_MR0RXSTOP_EN);
	psgpio_reg->SGPIO_MULMC = temp_reg;

	temp_reg = psgpio_reg->SGPIO_CAP_CTRL;
	temp_reg &= ~(SGPIO_BIT_CAP_RXTCSTOP_EN);
	temp_reg |= (prxtc_event->capture_event << SGPIO_SHIFT_CAP_RXTCSTOP_EN);
	psgpio_reg->SGPIO_CAP_CTRL = temp_reg;

}

/**
 *  @brief  Update the rxtc stop events of the SGPIO adapter according to the SGPIO registers.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  prxtc_event The stop events.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_get_rxtc_stop_ctrl(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_event_t *prxtc_event)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u32 temp_reg;

	temp_reg = psgpio_reg->SGPIO_RXMC;
	prxtc_event->rxtc_match_event0 = (temp_reg & SGPIO_BIT_RX_MR0STOP_EN) >> SGPIO_SHIFT_RX_MR0STOP_EN;
	prxtc_event->rxtc_match_event1 = (temp_reg & SGPIO_BIT_RX_MR1STOP_EN) >> SGPIO_SHIFT_RX_MR1STOP_EN;
	prxtc_event->rxtc_match_event2 = (temp_reg & SGPIO_BIT_RX_MR2STOP_EN) >> SGPIO_SHIFT_RX_MR2STOP_EN;
	prxtc_event->rx_postc_zero = (temp_reg & SGPIO_BIT_RX_POSSTOP_EN) >> SGPIO_SHIFT_RX_POSSTOP_EN;

	temp_reg = psgpio_reg->SGPIO_MULMC;
	prxtc_event->multc_match_event0 = (temp_reg & SGPIO_BIT_MUL_MR0RXSTOP_EN) >> SGPIO_SHIFT_MUL_MR0RXSTOP_EN;

	temp_reg = psgpio_reg->SGPIO_CAP_CTRL;
	prxtc_event->capture_event = (temp_reg & SGPIO_BIT_CAP_RXTCSTOP_EN) >> SGPIO_SHIFT_CAP_RXTCSTOP_EN;

}

/**
 *  @brief  Set the reset events to make the rxtc timer reset.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  prxtc_event The reset events. 0: disable, 1: enable.
 *                      rxtc_match_event0 - This event is that the rx timer value matches rx match register 0.
 *                      rxtc_match_event1 - This event is that the rx timer value matches rx match register 1.
 *                      rxtc_match_event2 - This event is that the rx timer value matches rx match register 2.
 *                      multc_match_event0 - This event is that the multc timer value matches Multiple Match Register 0.
 *                      rx_postc_zero - This event is that the rxpostc register becomes 0.
 *                      capture_event - This event is that happen the capture.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_set_rxtc_reset_ctrl(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_event_t *prxtc_event)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u32 temp_reg;

	temp_reg = psgpio_reg->SGPIO_RXMC;
	temp_reg &= ~(SGPIO_BIT_RX_MR0RST_EN | SGPIO_BIT_RX_MR1RST_EN | SGPIO_BIT_RX_MR2RST_EN | SGPIO_BIT_RX_POSRST_EN);
	temp_reg |= (prxtc_event->rxtc_match_event0 << SGPIO_SHIFT_RX_MR0RST_EN);
	temp_reg |= (prxtc_event->rxtc_match_event1 << SGPIO_SHIFT_RX_MR1RST_EN);
	temp_reg |= (prxtc_event->rxtc_match_event2 << SGPIO_SHIFT_RX_MR2RST_EN);
	temp_reg |= (prxtc_event->rx_postc_zero << SGPIO_SHIFT_RX_POSRST_EN);
	psgpio_reg->SGPIO_RXMC = temp_reg;

	temp_reg = psgpio_reg->SGPIO_MULMC;
	temp_reg &= ~(SGPIO_BIT_MUL_MR0RXRST_EN);
	temp_reg |= (prxtc_event->multc_match_event0 << SGPIO_SHIFT_MUL_MR0RXRST_EN);
	psgpio_reg->SGPIO_MULMC = temp_reg;

	temp_reg = psgpio_reg->SGPIO_CAP_CTRL;
	temp_reg &= ~(SGPIO_BIT_CAP_RXTCRST_EN);
	temp_reg |= (prxtc_event->capture_event << SGPIO_SHIFT_CAP_RXTCRST_EN);
	psgpio_reg->SGPIO_CAP_CTRL = temp_reg;

}

/**
 *  @brief  Update the rxtc reset events of the SGPIO adapter according to the SGPIO registers.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  prxtc_event The reset events.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_get_rxtc_reset_ctrl(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_event_t *prxtc_event)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u32 temp_reg;

	temp_reg = psgpio_reg->SGPIO_RXMC;
	prxtc_event->rxtc_match_event0 = (temp_reg & SGPIO_BIT_RX_MR0RST_EN) >> SGPIO_SHIFT_RX_MR0RST_EN;
	prxtc_event->rxtc_match_event1 = (temp_reg & SGPIO_BIT_RX_MR1RST_EN) >> SGPIO_SHIFT_RX_MR1RST_EN;
	prxtc_event->rxtc_match_event2 = (temp_reg & SGPIO_BIT_RX_MR2RST_EN) >> SGPIO_SHIFT_RX_MR2RST_EN;
	prxtc_event->rx_postc_zero = (temp_reg & SGPIO_BIT_RX_POSRST_EN) >> SGPIO_SHIFT_RX_POSRST_EN;

	temp_reg = psgpio_reg->SGPIO_MULMC;
	prxtc_event->multc_match_event0 = (temp_reg & SGPIO_BIT_MUL_MR0RXRST_EN) >> SGPIO_SHIFT_MUL_MR0RXRST_EN;

	temp_reg = psgpio_reg->SGPIO_CAP_CTRL;
	prxtc_event->capture_event = (temp_reg & SGPIO_BIT_CAP_RXTCRST_EN) >> SGPIO_SHIFT_CAP_RXTCRST_EN;
}

/**
 *  @brief  Set the register value of the rxtc match event.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  match_event Select the rxtc match event.
 *  @param[in]  match_value The match value of the register value.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_set_rxtc_match_value(hal_sgpio_adapter_t *psgpio_adp, sgpio_rxtc_match_event_t match_event, u16 match_value)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;

	if (match_event == Rxtc_MatchEvent0) {
		psgpio_reg->SGPIO_RXMR0 = (match_value & SGPIO_MASK_RXMR0);
	} else if (match_event == Rxtc_MatchEvent1) {
		psgpio_reg->SGPIO_RXMR1 = (match_value & SGPIO_MASK_RXMR1);
	} else if (match_event == Rxtc_MatchEvent2) {
		psgpio_reg->SGPIO_RXMR2 = (match_value & SGPIO_MASK_RXMR2);
	}
}

/**
 *  @brief  Set the interrupt control of the rxtc match event.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  match_event Select the rxtc match event.
 *  @param[in]  psgpio_set_irq The parameter structure is for initializing the interrupt event.
 *                      int_en - 0: disbale this event interrupt, 1: enable.
 *                      imr_en - 0: disbale mask event interrupt, 1: enable.
 *                      callback_reg_en - 0: don't register this callback function, 1: register this callback function.
 *                      callback - The callback function.
 *                      arg - The callback argument.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_set_rxtc_int(hal_sgpio_adapter_t *psgpio_adp,  sgpio_rxtc_match_event_t match_event, hal_sgpio_set_irq_t *psgpio_set_irq)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u8 irq_bit_shift = 0;
	u32 rxmc_temp;
	u32 reg_temp;

	rxmc_temp = psgpio_reg->SGPIO_RXMC;

	if (match_event == Rxtc_MatchEvent0) {
		reg_temp = psgpio_reg->SGPIO_IM;
		reg_temp &= ~(SGPIO_BIT_RX_MR0I_IM);
		reg_temp |= (psgpio_set_irq->imr_en << SGPIO_SHIFT_RX_MR0I_IM);
		psgpio_reg->SGPIO_IM = reg_temp;

		rxmc_temp &= ~(SGPIO_BIT_RX_MR0I_EN);
		rxmc_temp |= (psgpio_set_irq->int_en << SGPIO_SHIFT_RX_MR0I_EN);
		irq_bit_shift = Rx_Mr0_Sft;
	} else if (match_event == Rxtc_MatchEvent1) {
		reg_temp = psgpio_reg->SGPIO_IM;
		reg_temp &= ~(SGPIO_BIT_RX_MR1I_IM);
		reg_temp |= (psgpio_set_irq->imr_en << SGPIO_SHIFT_RX_MR1I_IM);
		psgpio_reg->SGPIO_IM = reg_temp;

		rxmc_temp &= ~(SGPIO_BIT_RX_MR1I_EN);
		rxmc_temp |= (psgpio_set_irq->int_en << SGPIO_SHIFT_RX_MR1I_EN);
		irq_bit_shift = Rx_Mr1_Sft;
	} else if (match_event == Rxtc_MatchEvent2) {
		reg_temp = psgpio_reg->SGPIO_IM;
		reg_temp &= ~(SGPIO_BIT_RX_MR2I_IM);
		reg_temp |= (psgpio_set_irq->imr_en << SGPIO_SHIFT_RX_MR2I_IM);
		psgpio_reg->SGPIO_IM = reg_temp;

		rxmc_temp &= ~(SGPIO_BIT_RX_MR2I_EN);
		rxmc_temp |= (psgpio_set_irq->int_en << SGPIO_SHIFT_RX_MR2I_EN);
		irq_bit_shift = Rx_Mr2_Sft;
	}

	psgpio_reg->SGPIO_RXMC = rxmc_temp;

	if (psgpio_set_irq->callback_reg_en == 1) {
		hal_rom_sgpio_reg_cb(psgpio_adp, psgpio_set_irq->callback, psgpio_set_irq->arg, irq_bit_shift);
	} else {
		hal_rom_sgpio_unreg_cb(psgpio_adp, irq_bit_shift);
	}
}

/**
 *  @brief  Set the capture event control.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  capture_type Select the capture event.
 *  @param[in]  cap_en Enable or Disable the capture function
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_set_capture_ctrl(hal_sgpio_adapter_t *psgpio_adp, sgpio_capture_type_t capture_type, BOOL cap_en)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u32 cap_ctrl_temp;

	cap_ctrl_temp = psgpio_reg->SGPIO_CAP_CTRL;
	cap_ctrl_temp &= ~(SGPIO_BIT_CAPFE_EN | SGPIO_BIT_CAPRE_EN | SGPIO_BIT_CAPSRC_SEL | SGPIO_BIT_CAPVALID_EN);

	psgpio_reg->SGPIO_MULMC &= ~(SGPIO_BIT_MUL_MR0CAPSRC_EN);

	if (capture_type == Cap_InputRiseEg) {
		cap_ctrl_temp |= (1 << SGPIO_SHIFT_CAPRE_EN);
	} else if (capture_type == Cap_InputFallEg) {
		cap_ctrl_temp |= (1 << SGPIO_SHIFT_CAPFE_EN);
	} else if (capture_type == Cap_InputBothEg) {
		cap_ctrl_temp |= ((1 << SGPIO_SHIFT_CAPRE_EN) | (1 << SGPIO_SHIFT_CAPFE_EN));
	} else if (capture_type == Cap_MultcMatchEvent0) {
		cap_ctrl_temp |= (1 << SGPIO_SHIFT_CAPSRC_SEL);
		psgpio_reg->SGPIO_MULMC |= (1 << SGPIO_SHIFT_MUL_MR0CAPSRC_EN);
	}

	cap_ctrl_temp &= ~(SGPIO_BIT_CAP_EN);
	cap_ctrl_temp |= (cap_en << SGPIO_SHIFT_CAP_EN);

	psgpio_reg->SGPIO_CAP_CTRL = cap_ctrl_temp;

}

/**
 *  @brief  Translate the capture value into "0" or "1" according to the result of the comparison.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  cap_cmpval_sel Set that the rxdata register receives value 0 or 1 when the capture value is bigger than cap_cmpval.
 *  @param[in]  cap_cmpval The compare value.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_set_capture_compare(hal_sgpio_adapter_t *psgpio_adp, u8 cap_cmpval_sel, u16 cap_cmpval)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u32 reg_temp;

	reg_temp = psgpio_reg->SGPIO_CAP_CTRL;
	reg_temp &= ~(SGPIO_BIT_CAP_CMPVAL_SEL | SGPIO_MASK_CAP_CMPVAL);
	reg_temp |= ((cap_cmpval_sel << SGPIO_SHIFT_CAP_CMPVAL_SEL) | (cap_cmpval << SGPIO_SHIFT_CAP_CMPVAL));
	psgpio_reg->SGPIO_CAP_CTRL = reg_temp;
}

/**
 *  @brief  Set the interrupt control of the capture event.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  psgpio_set_irq The parameter structure is for initializing the interrupt event.
 *                      int_en - 0: disbale this event interrupt, 1: enable.
 *                      imr_en - 0: disbale mask event interrupt, 1: enable.
 *                      callback_reg_en - 0: don't register this callback function, 1: register this callback function.
 *                      callback - The callback function.
 *                      arg - The callback argument.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_set_capture_int(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_set_irq_t *psgpio_set_irq)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u32 reg_temp;

	reg_temp = psgpio_reg->SGPIO_IM;
	reg_temp &= ~(SGPIO_BIT_CAPI_IM);
	reg_temp |= (psgpio_set_irq->imr_en << SGPIO_SHIFT_CAPI_IM);
	psgpio_reg->SGPIO_IM = reg_temp;

	reg_temp = psgpio_reg->SGPIO_CAP_CTRL;
	reg_temp &= ~(SGPIO_BIT_CAPI_EN);
	reg_temp |= (psgpio_set_irq->int_en << SGPIO_SHIFT_CAPI_EN);
	psgpio_reg->SGPIO_CAP_CTRL = reg_temp;

	if (psgpio_set_irq->callback_reg_en == 1) {
		hal_rom_sgpio_reg_cb(psgpio_adp, psgpio_set_irq->callback, psgpio_set_irq->arg, Cap_Sft);
	} else {
		hal_rom_sgpio_unreg_cb(psgpio_adp, Cap_Sft);
	}

}

/**
 *  @brief  Set the stop events to make the multc timer stop.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  pmultc_event The stop events. 0: disable, 1: enable.
 *                      multc_match_event0 - This event is that the multc timer value matches multiple match register 0.
 *                      rxtc_match_event0 - This event is that the rx timer value matches rx match register 0.
 *                      multc_mcnt_zero - This event is that the mul_mcnt register becomes 0.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_set_multc_stop_ctrl(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_multc_event_t *pmultc_event)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u32 reg_temp;

	reg_temp = psgpio_reg->SGPIO_MULMC;
	reg_temp &= ~(SGPIO_BIT_MUL_MR0STOP_EN | SGPIO_BIT_MUL_MCNTSTOP_EN);
	reg_temp |= (pmultc_event->multc_match_event0 << SGPIO_SHIFT_MUL_MR0STOP_EN);
	reg_temp |= (pmultc_event->multc_mcnt_zero << SGPIO_SHIFT_MUL_MCNTSTOP_EN);
	psgpio_reg->SGPIO_MULMC = reg_temp;

	reg_temp = psgpio_reg->SGPIO_RXMC;
	reg_temp &= ~(SGPIO_BIT_RX_MR0MULSTOP_EN);
	reg_temp |= (pmultc_event->rxtc_match_event0 << SGPIO_SHIFT_RX_MR0MULSTOP_EN);
	psgpio_reg->SGPIO_RXMC = reg_temp;

}

/**
 *  @brief  Update the multc stop events of the SGPIO adapter according to the SGPIO registers.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  pmultc_event The stop events.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_get_multc_stop_ctrl(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_multc_event_t *pmultc_event)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u32 reg_temp;

	reg_temp = psgpio_reg->SGPIO_MULMC;
	pmultc_event->multc_match_event0 = (reg_temp & SGPIO_BIT_MUL_MR0STOP_EN) >> SGPIO_SHIFT_MUL_MR0STOP_EN;
	pmultc_event->multc_mcnt_zero = (reg_temp & SGPIO_BIT_MUL_MCNTSTOP_EN) >> SGPIO_SHIFT_MUL_MCNTSTOP_EN;

	reg_temp = psgpio_reg->SGPIO_RXMC;
	pmultc_event->rxtc_match_event0 = (reg_temp & SGPIO_BIT_RX_MR0MULSTOP_EN) >> SGPIO_SHIFT_RX_MR0MULSTOP_EN;
}

/**
 *  @brief  Set the reset events to make the multc timer reset.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  pmultc_event The reset events. 0: disable, 1: enable.
 *                      multc_match_event0 - This event is that the multc timer value matches multiple match register 0.
 *                      rxtc_match_event0 - This event is that the rx timer value matches rx match register 0.
 *                      multc_mcnt_zero - This event is that the mul_mcnt register becomes 0.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_set_multc_reset_ctrl(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_multc_event_t *pmultc_event)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u32 reg_temp;

	reg_temp = psgpio_reg->SGPIO_MULMC;
	reg_temp &= ~(SGPIO_BIT_MUL_MR0RST_EN | SGPIO_BIT_MUL_MCNTRST_EN);
	reg_temp |= (pmultc_event->multc_match_event0 << SGPIO_SHIFT_MUL_MR0RST_EN);
	reg_temp |= (pmultc_event->multc_mcnt_zero << SGPIO_SHIFT_MUL_MCNTRST_EN);
	psgpio_reg->SGPIO_MULMC = reg_temp;

	reg_temp = psgpio_reg->SGPIO_RXMC;
	reg_temp &= ~(SGPIO_BIT_RX_MR0MULRST_EN);
	reg_temp |= (pmultc_event->rxtc_match_event0 << SGPIO_SHIFT_RX_MR0MULRST_EN);
	psgpio_reg->SGPIO_RXMC = reg_temp;

}

/**
 *  @brief  Update the multc reset events of the SGPIO adapter according to the SGPIO registers.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  pmultc_event The reset events.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_get_multc_reset_ctrl(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_multc_event_t *pmultc_event)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u32 reg_temp;

	reg_temp = psgpio_reg->SGPIO_MULMC;
	pmultc_event->multc_match_event0 = (reg_temp & SGPIO_BIT_MUL_MR0RST_EN) >> SGPIO_SHIFT_MUL_MR0RST_EN;
	pmultc_event->multc_mcnt_zero = (reg_temp & SGPIO_BIT_MUL_MCNTRST_EN) >> SGPIO_SHIFT_MUL_MCNTRST_EN;

	reg_temp = psgpio_reg->SGPIO_RXMC;
	pmultc_event->rxtc_match_event0 = (reg_temp & SGPIO_BIT_RX_MR0MULRST_EN) >> SGPIO_SHIFT_RX_MR0MULRST_EN;
}

/**
 *  @brief  Set the register value of the multc match event.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  match_group Select the group of the multc match event.
 *  @param[in]  match_event Select the multc match event.
 *  @param[in]  match_value The match value of the register value.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_set_multc_match_value(hal_sgpio_adapter_t *psgpio_adp, sgpio_multc_match_group_t match_group, sgpio_multc_match_event_t match_event,
		u16 match_value)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u32 reg_temp;

	if (match_group == Multc_MatchGroup0) {
		if (match_event == Multc_MatchEvent0) {
			reg_temp = psgpio_reg->SGPIO_MULMR01GP0;
			reg_temp &= ~(SGPIO_MASK_MULMR0_GP0);
			reg_temp |= (match_value << SGPIO_SHIFT_MULMR0_GP0);
			psgpio_reg->SGPIO_MULMR01GP0 = reg_temp;
		} else if (match_event == Multc_MatchEvent1) {
			reg_temp = psgpio_reg->SGPIO_MULMR01GP0;
			reg_temp &= ~(SGPIO_MASK_MULMR1_GP0);
			reg_temp |= (match_value << SGPIO_SHIFT_MULMR1_GP0);
			psgpio_reg->SGPIO_MULMR01GP0 = reg_temp;
		} else if (match_event == Multc_MatchEvent2) {
			reg_temp = psgpio_reg->SGPIO_MULMR23GP0;
			reg_temp &= ~(SGPIO_MASK_MULMR2_GP0);
			reg_temp |= (match_value << SGPIO_SHIFT_MULMR2_GP0);
			psgpio_reg->SGPIO_MULMR23GP0 = reg_temp;
		} else if (match_event == Multc_MatchEvent3) {
			reg_temp = psgpio_reg->SGPIO_MULMR23GP0;
			reg_temp &= ~(SGPIO_MASK_MULMR3_GP0);
			reg_temp |= (match_value << SGPIO_SHIFT_MULMR3_GP0);
			psgpio_reg->SGPIO_MULMR23GP0 = reg_temp;
		}
	} else if (match_group == Multc_MatchGroup1) {
		if (match_event == Multc_MatchEvent0) {
			reg_temp = psgpio_reg->SGPIO_MULMR01GP1;
			reg_temp &= ~(SGPIO_MASK_MULMR0_GP1);
			reg_temp |= (match_value << SGPIO_SHIFT_MULMR0_GP1);
			psgpio_reg->SGPIO_MULMR01GP1 = reg_temp;
		} else if (match_event == Multc_MatchEvent1) {
			reg_temp = psgpio_reg->SGPIO_MULMR01GP1;
			reg_temp &= ~(SGPIO_MASK_MULMR1_GP1);
			reg_temp |= (match_value << SGPIO_SHIFT_MULMR1_GP1);
			psgpio_reg->SGPIO_MULMR01GP1 = reg_temp;
		} else if (match_event == Multc_MatchEvent2) {
			reg_temp = psgpio_reg->SGPIO_MULMR23GP1;
			reg_temp &= ~(SGPIO_MASK_MULMR2_GP1);
			reg_temp |= (match_value << SGPIO_SHIFT_MULMR2_GP1);
			psgpio_reg->SGPIO_MULMR23GP1 = reg_temp;
		} else if (match_event == Multc_MatchEvent3) {
			reg_temp = psgpio_reg->SGPIO_MULMR23GP1;
			reg_temp &= ~(SGPIO_MASK_MULMR3_GP1);
			reg_temp |= (match_value << SGPIO_SHIFT_MULMR3_GP1);
			psgpio_reg->SGPIO_MULMR23GP1 = reg_temp;
		}
	}

}

/**
 *  @brief  Set the interrupt control of the multc match event 0.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  psgpio_set_irq The parameter structure is for initializing the interrupt event.
 *                      int_en - 0: disbale this event interrupt, 1: enable.
 *                      imr_en - 0: disbale mask event interrupt, 1: enable.
 *                      callback_reg_en - 0: don't register this callback function, 1: register this callback function.
 *                      callback - The callback function.
 *                      arg - The callback argument.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_set_multc_match_event0_int(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_set_irq_t *psgpio_set_irq)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u32 reg_temp;

	reg_temp = psgpio_reg->SGPIO_IM;
	reg_temp &= ~(SGPIO_BIT_MUL_MR0I_IM);
	reg_temp |= (psgpio_set_irq->imr_en << SGPIO_SHIFT_MUL_MR0I_IM);
	psgpio_reg->SGPIO_IM = reg_temp;

	reg_temp = psgpio_reg->SGPIO_MULMC;
	reg_temp &= ~(SGPIO_BIT_MUL_MR0I_EN);
	reg_temp |= (psgpio_set_irq->int_en << SGPIO_SHIFT_MUL_MR0I_EN);
	psgpio_reg->SGPIO_MULMC = reg_temp;

	if (psgpio_set_irq->callback_reg_en == 1) {
		hal_rom_sgpio_reg_cb(psgpio_adp, psgpio_set_irq->callback, psgpio_set_irq->arg, Mul_Mr0_Sft);
	} else {
		hal_rom_sgpio_unreg_cb(psgpio_adp, Mul_Mr0_Sft);
	}

}

/**
 *  @brief  Select the group of the multc match event.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  match_group The group of the multc match event.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_set_multc_match_group(hal_sgpio_adapter_t *psgpio_adp, sgpio_multc_match_group_t match_group)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u32 reg_temp;
	u32 muldata;
	u32 muldata_mask;

	reg_temp = (psgpio_reg->SGPIO_DATA_CTRL & SGPIO_BIT_TXDATA_DIR) >> SGPIO_SHIFT_TXDATA_DIR;

	if (reg_temp == 0x00) {
		muldata_mask = 0x01;
	} else {
		muldata_mask = 0x80000000;
	}

	muldata = psgpio_reg->SGPIO_MULDATA & ~(muldata_mask);

	if (match_group == Multc_MatchGroup1) {
		muldata = muldata | muldata_mask;
	}

	psgpio_reg->SGPIO_MULDATA = muldata;
}

/**
 *  @brief  Set the register value of the multc match event by using the FIFO mode.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  pfifo_value The multc match event when use the FIFO mode.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_set_multc_fifo_value(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_fifo_value_t *pfifo_value)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;

	psgpio_reg->SGPIO_MULFDATA = (u32)pfifo_value->multc_match_event0_val | (u32)((u32)pfifo_value->multc_match_event1_val << 16);
	psgpio_reg->SGPIO_MULFDATA = (u32)pfifo_value->multc_match_event2_val | (u32)((u32)pfifo_value->multc_match_event3_val << 16);
}

/**
 *  @brief  Set the external output for the rxtc match event.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  match_event Select the rxtc match event.
 *  @param[in]  external_output Set the output state when happen the rxtc match event.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_set_rxtc_external_match(hal_sgpio_adapter_t *psgpio_adp, sgpio_rxtc_match_event_t match_event, sgpio_external_output_t external_output)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u32 reg_temp;

	reg_temp = psgpio_reg->SGPIO_MULEMR;

	if (match_event == Rxtc_MatchEvent0) {
		reg_temp &= ~(SGPIO_MASK_RXEMC0);
		reg_temp |= (external_output << SGPIO_SHIFT_RXEMC0);
	} else if (match_event == Rxtc_MatchEvent1) {
		reg_temp &= ~(SGPIO_MASK_RXEMC1);
		reg_temp |= (external_output << SGPIO_SHIFT_RXEMC1);
	} else if (match_event == Rxtc_MatchEvent2) {
		reg_temp &= ~(SGPIO_MASK_RXEMC2);
		reg_temp |= (external_output << SGPIO_SHIFT_RXEMC2);
	}

	psgpio_reg->SGPIO_MULEMR = reg_temp;

}

/**
 *  @brief  Set the external output for the multc match event.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  match_event Select the multc match event.
 *  @param[in]  external_output Set the output state when happen the multc match event.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_set_multc_external_match(hal_sgpio_adapter_t *psgpio_adp, sgpio_multc_match_event_t match_event, sgpio_external_output_t external_output)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u32 reg_temp;

	reg_temp = psgpio_reg->SGPIO_MULEMR;

	if (match_event == Multc_MatchEvent0) {
		//dbg_printf("hal_sgpio_set_multc_external_match_rtl8195bhp: Not support Multc_MatchEvent0 \r\n");
	} else if (match_event == Multc_MatchEvent1) {
		reg_temp &= ~(SGPIO_MASK_MULEMC1);
		reg_temp |= (external_output << SGPIO_SHIFT_MULEMC1);
	} else if (match_event == Multc_MatchEvent2) {
		reg_temp &= ~(SGPIO_MASK_MULEMC2);
		reg_temp |= (external_output << SGPIO_SHIFT_MULEMC2);
	} else if (match_event == Multc_MatchEvent3) {
		reg_temp &= ~(SGPIO_MASK_MULEMC3);
		reg_temp |= (external_output << SGPIO_SHIFT_MULEMC3);
	}

	psgpio_reg->SGPIO_MULEMR = reg_temp;

}

/**
 *  @brief  Set the control and interrupt for counting multc match event 0.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  match_cnt_en Enable or Disable to count the multc match event 0.
 *  @param[in]  match_down_cnt Set the countdown value. When match_down_cnt is zero, make the interrupt.
 *  @param[in]  psgpio_set_irq The parameter structure is for initializing the interrupt event.
 *                      int_en - 0: disbale this event interrupt, 1: enable.
 *                      imr_en - 0: disbale mask event interrupt, 1: enable.
 *                      callback_reg_en - 0: don't register this callback function, 1: register this callback function.
 *                      callback - The callback function.
 *                      arg - The callback argument.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_set_multc_match_event0_cnt_int(hal_sgpio_adapter_t *psgpio_adp, BOOL match_cnt_en, u8 match_down_cnt, hal_sgpio_set_irq_t *psgpio_set_irq)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u32 reg_temp;

	if (match_down_cnt != 0x00) {
		reg_temp = psgpio_reg->SGPIO_MUL_MCNT;
		reg_temp &= ~(SGPIO_MASK_MUL_MCNT);
		reg_temp |= ((match_down_cnt - 1) << SGPIO_SHIFT_MUL_MCNT);
		psgpio_reg->SGPIO_MUL_MCNT = reg_temp;
	} else {
		psgpio_reg->SGPIO_MUL_MCNT = 0;
	}

	reg_temp = psgpio_reg->SGPIO_MULMC;
	reg_temp &= ~(SGPIO_BIT_MUL_MR0MCNT_EN);
	reg_temp |= (match_cnt_en << SGPIO_SHIFT_MUL_MR0MCNT_EN);
	psgpio_reg->SGPIO_MULMC = reg_temp;

	reg_temp = psgpio_reg->SGPIO_IM;
	reg_temp &= ~(SGPIO_BIT_MULMCNT_IM);
	reg_temp |= (psgpio_set_irq->imr_en << SGPIO_SHIFT_MULMCNT_IM);
	psgpio_reg->SGPIO_IM = reg_temp;

	reg_temp = psgpio_reg->SGPIO_MULMC;
	reg_temp &= ~(SGPIO_BIT_MUL_MCNTI_EN);
	reg_temp |= (psgpio_set_irq->int_en << SGPIO_SHIFT_MUL_MCNTI_EN);
	psgpio_reg->SGPIO_MULMC = reg_temp;

	if (psgpio_set_irq->callback_reg_en == 1) {
		hal_rom_sgpio_reg_cb(psgpio_adp, psgpio_set_irq->callback, psgpio_set_irq->arg, Mulmcnt_Sft);
	} else {
		hal_rom_sgpio_unreg_cb(psgpio_adp, Mulmcnt_Sft);
	}
}

/**
 *  @brief  Set the control for counting multc match event 0.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  match_cnt_en Enable or Disable to count the multc match event 0.
 *  @param[in]  match_down_cnt Set the countdown value. When match_down_cnt is zero, make the interrupt.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_set_multc_match_event0_cnt(hal_sgpio_adapter_t *psgpio_adp, BOOL match_cnt_en, u8 match_down_cnt)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u32 reg_temp;

	if (match_down_cnt != 0x00) {
		reg_temp = psgpio_reg->SGPIO_MUL_MCNT;
		reg_temp &= ~(SGPIO_MASK_MUL_MCNT);
		reg_temp |= ((match_down_cnt - 1) << SGPIO_SHIFT_MUL_MCNT);
		psgpio_reg->SGPIO_MUL_MCNT = reg_temp;
	} else {
		psgpio_reg->SGPIO_MUL_MCNT = 0;
	}

	reg_temp = psgpio_reg->SGPIO_MULMC;
	reg_temp &= ~(SGPIO_BIT_MUL_MR0MCNT_EN);
	reg_temp |= (match_cnt_en << SGPIO_SHIFT_MUL_MR0MCNT_EN);
	psgpio_reg->SGPIO_MULMC = reg_temp;

}

/**
 *  @brief  Set the smapling event for rxdata.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  psampling_event The smapling events. 0: disable, 1: enable.
 *                      rxtc_match_event0 - This event is that the rx timer value matches rx match register 0.
 *                      rxtc_match_event1 - This event is that the rx timer value matches rx match register 1.
 *                      rxtc_match_event2 - This event is that the rx timer value matches rx match register 2.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_init_rxdata_time_sampling(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_sampling_event_t *psampling_event)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u32 reg_temp;

	reg_temp = psgpio_reg->SGPIO_RXMC;

	if (psampling_event->rxtc_match_event0 == 1) {
		reg_temp |= SGPIO_BIT_RX_MR0SCLK_EN;
	} else {
		reg_temp &= ~(SGPIO_BIT_RX_MR0SCLK_EN);
	}

	if (psampling_event->rxtc_match_event1 == 1) {
		reg_temp |= SGPIO_BIT_RX_MR1SCLK_EN;
	} else {
		reg_temp &= ~(SGPIO_BIT_RX_MR1SCLK_EN);
	}

	if (psampling_event->rxtc_match_event2 == 1) {
		reg_temp |= SGPIO_BIT_RX_MR2SCLK_EN;
	} else {
		reg_temp &= ~(SGPIO_BIT_RX_MR2SCLK_EN);
	}

	psgpio_reg->SGPIO_RXMC = reg_temp;

	psgpio_reg->SGPIO_DATA_CTRL &= ~(SGPIO_BIT_RXDATASRC_SEL);

}

/**
 *  @brief  Disable the smapling event for rxdata.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_deinit_rxdata_time_sampling(hal_sgpio_adapter_t *psgpio_adp)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u32 reg_temp;

	reg_temp = psgpio_reg->SGPIO_RXMC;
	reg_temp &= ~(SGPIO_BIT_RX_MR0SCLK_EN);
	reg_temp &= ~(SGPIO_BIT_RX_MR1SCLK_EN);
	reg_temp &= ~(SGPIO_BIT_RX_MR2SCLK_EN);
	psgpio_reg->SGPIO_RXMC = reg_temp;

	psgpio_reg->SGPIO_DATA_CTRL &= ~(SGPIO_BIT_RXDATASRC_SEL);

}

/**
 *  @brief  Initialize that the rxdata source is the capture compare result.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  cmp_result_bit Set that the rxdata register receives value 0 or 1 when the capture value is bigger than cap_cmpval.
 *  @param[in]  cap_cmpval The compare value. This unit is count.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_init_rxdata_capture_compare(hal_sgpio_adapter_t *psgpio_adp, sgpio_cmp_result_bit_t cmp_result_bit, u16 cap_cmpval)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;

	hal_rom_sgpio_set_capture_compare(psgpio_adp, cmp_result_bit, cap_cmpval);

	psgpio_reg->SGPIO_DATA_CTRL |= SGPIO_BIT_RXDATASRC_SEL;
}

/**
 *  @brief  De-initialize that the rxdata source is the capture compare result.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_deinit_rxdata_capture_compare(hal_sgpio_adapter_t *psgpio_adp)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;

	hal_rom_sgpio_set_capture_ctrl(psgpio_adp, Cap_None, 0);
	hal_rom_sgpio_set_capture_compare(psgpio_adp, 0, 0);

	psgpio_reg->SGPIO_DATA_CTRL &= ~(SGPIO_BIT_RXDATASRC_SEL);
}

/**
 *  @brief  Set the rxdata sampling length and interrupt. When reach the length to be received, generate the interrupt.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  bit_length The sampling bit length.
 *  @param[in]  psgpio_set_irq The parameter structure is for initializing the interrupt event.
 *                      int_en - 0: disbale this event interrupt, 1: enable.
 *                      imr_en - 0: disbale mask event interrupt, 1: enable.
 *                      callback_reg_en - 0: don't register this callback function, 1: register this callback function.
 *                      callback - The callback function.
 *                      arg - The callback argument.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
SECTION_SGPIO_TEXT
HAL_Status hal_rom_sgpio_set_rxdata_load_int(hal_sgpio_adapter_t *psgpio_adp, u8 bit_length, hal_sgpio_set_irq_t *psgpio_set_irq)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u32 reg_temp;

	if (bit_length > 32) {
		//dbg_printf("hal_sgpio_set_rxdata_load_int_rtl8195bhp: bit_cnt > 32 \r\n");
		return HAL_ERR_PARA;
	} else {
		if (bit_length != 0x00) {
			reg_temp = psgpio_reg->SGPIO_RXPOSR;
			reg_temp &= ~(SGPIO_MASK_RXPOSRST);
			reg_temp |= ((bit_length - 1) << SGPIO_SHIFT_RXPOSRST);
			psgpio_reg->SGPIO_RXPOSR = reg_temp;

			reg_temp = psgpio_reg->SGPIO_RXPOSR;
			reg_temp &= ~(SGPIO_MASK_RXPOSTC);
			reg_temp |= ((bit_length - 1) << SGPIO_SHIFT_RXPOSTC);
			psgpio_reg->SGPIO_RXPOSR = reg_temp;

		} else {
			psgpio_reg->SGPIO_RXPOSR &= ~(SGPIO_MASK_RXPOSTC | SGPIO_MASK_RXPOSRST);
		}
	}

	reg_temp = psgpio_reg->SGPIO_IM;
	reg_temp &= ~(SGPIO_BIT_RXLOAD_IM);
	reg_temp |= (psgpio_set_irq->imr_en << SGPIO_SHIFT_RXLOAD_IM);
	psgpio_reg->SGPIO_IM = reg_temp;

	reg_temp = psgpio_reg->SGPIO_DATA_CTRL;
	reg_temp &= ~(SGPIO_BIT_RXLOAD_IE);
	reg_temp |= (psgpio_set_irq->int_en << SGPIO_SHIFT_RXLOAD_IE);
	psgpio_reg->SGPIO_DATA_CTRL = reg_temp;

	if (psgpio_set_irq->callback_reg_en == 1) {
		hal_rom_sgpio_reg_cb(psgpio_adp, psgpio_set_irq->callback, psgpio_set_irq->arg, Rxload_Sft);
	} else {
		hal_rom_sgpio_unreg_cb(psgpio_adp, Rxload_Sft);
	}

	return HAL_OK;
}

/**
 *  @brief  Control the interrupt when happen the bit shift of rxdata.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  psgpio_set_irq The parameter structure is for initializing the interrupt event.
 *                      int_en - 0: disbale this event interrupt, 1: enable.
 *                      imr_en - 0: disbale mask event interrupt, 1: enable.
 *                      callback_reg_en - 0: don't register this callback function, 1: register this callback function.
 *                      callback - The callback function.
 *                      arg - The callback argument.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_set_rxdata_prebuf_bit_shift_int(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_set_irq_t *psgpio_set_irq)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u32 reg_temp;

	reg_temp = psgpio_reg->SGPIO_IM;
	reg_temp &= ~(SGPIO_BIT_RXSFT_IM);
	reg_temp |= (psgpio_set_irq->imr_en << SGPIO_SHIFT_RXSFT_IM);
	psgpio_reg->SGPIO_IM = reg_temp;

	reg_temp = psgpio_reg->SGPIO_DATA_CTRL;
	reg_temp &= ~(SGPIO_BIT_RXSFT_IE);
	reg_temp |= (psgpio_set_irq->int_en << SGPIO_SHIFT_RXSFT_IE);
	psgpio_reg->SGPIO_DATA_CTRL = reg_temp;

	if (psgpio_set_irq->callback_reg_en == 1) {
		hal_rom_sgpio_reg_cb(psgpio_adp, psgpio_set_irq->callback, psgpio_set_irq->arg, Rxsft_Sft);
	} else {
		hal_rom_sgpio_unreg_cb(psgpio_adp, Rxsft_Sft);
	}
}

/**
 *  @brief  Reset the rxdata.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_reset_rxdata(hal_sgpio_adapter_t *psgpio_adp)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;

	psgpio_reg->SGPIO_RXDATA = 0X00;
	psgpio_reg->SGPIO_RXDATA_DP = 0X00;
}

/**
 *  @brief  Set the control and interrupt for the rxdata match event.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  rxdata_match_en Enable or Disable to the rxdata match function.
 *  @param[in]  match_value Set the match value of rxdata.
 *  @param[in]  psgpio_set_irq The parameter structure is for initializing the interrupt event.
 *                      int_en - 0: disbale this event interrupt, 1: enable.
 *                      imr_en - 0: disbale mask event interrupt, 1: enable.
 *                      callback_reg_en - 0: don't register this callback function, 1: register this callback function.
 *                      callback - The callback function.
 *                      arg - The callback argument.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_set_rxdata_match_int(hal_sgpio_adapter_t *psgpio_adp, BOOL rxdata_match_en, u32 match_value, hal_sgpio_set_irq_t *psgpio_set_irq)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u32 reg_temp;

	reg_temp = psgpio_reg->SGPIO_DATA_CTRL;
	reg_temp &= ~(SGPIO_BIT_PATTERN_MATCH_MODE);
	reg_temp |= (rxdata_match_en << SGPIO_SHIFT_PATTERN_MATCH_MODE);
	psgpio_reg->SGPIO_DATA_CTRL = reg_temp;

	psgpio_reg->SGPIO_RXDATAMASK = 0xFFFFFFFF;
	psgpio_reg->SGPIO_RXDATA_DP = match_value;

	reg_temp = psgpio_reg->SGPIO_IM;
	reg_temp &= ~(SGPIO_BIT_PATTERN_MATCH_IM);
	reg_temp |= (psgpio_set_irq->imr_en << SGPIO_SHIFT_PATTERN_MATCH_IM);
	psgpio_reg->SGPIO_IM = reg_temp;

	reg_temp = psgpio_reg->SGPIO_DATA_CTRL;
	reg_temp &= ~(SGPIO_BIT_PATTERN_MATCH_IE);
	reg_temp |= (psgpio_set_irq->int_en << SGPIO_SHIFT_PATTERN_MATCH_IE);
	psgpio_reg->SGPIO_DATA_CTRL = reg_temp;

	if (psgpio_set_irq->callback_reg_en == 1) {
		hal_rom_sgpio_reg_cb(psgpio_adp, psgpio_set_irq->callback, psgpio_set_irq->arg, Pattern_Match_Sft);
	} else {
		hal_rom_sgpio_unreg_cb(psgpio_adp, Pattern_Match_Sft);
	}
}

/**
 *  @brief  Set the txdata output length and interrupt. When reach the length to be sent, generate the interrupt.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  bit_length The output bit length.
 *  @param[in]  psgpio_set_irq The parameter structure is for initializing the interrupt event.
 *                      int_en - 0: disbale this event interrupt, 1: enable.
 *                      imr_en - 0: disbale mask event interrupt, 1: enable.
 *                      callback_reg_en - 0: don't register this callback function, 1: register this callback function.
 *                      callback - The callback function.
 *                      arg - The callback argument.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
SECTION_SGPIO_TEXT
HAL_Status hal_rom_sgpio_set_txdata_bit_length_int(hal_sgpio_adapter_t *psgpio_adp, u8 bit_length, hal_sgpio_set_irq_t *psgpio_set_irq)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u32 reg_temp;

	if (bit_length > 32) {
		//dbg_printf("hal_sgpio_set_txdata_bit_length_int_rtl8195bhp: bit_cnt > 32 \r\n");
		return HAL_ERR_PARA;
	} else {

		if (bit_length != 0x00) {

			reg_temp = psgpio_reg->SGPIO_MULPOSR;
			reg_temp &= ~(SGPIO_MASK_MULPOSRST);
			reg_temp |= ((bit_length - 1) << SGPIO_SHIFT_MULPOSRST);
			psgpio_reg->SGPIO_MULPOSR = reg_temp;

			reg_temp = psgpio_reg->SGPIO_MULPOSR;
			reg_temp &= ~(SGPIO_MASK_MULPOSTC);
			reg_temp |= ((bit_length - 1) << SGPIO_SHIFT_MULPOSTC);
			psgpio_reg->SGPIO_MULPOSR = reg_temp;

		} else {
			psgpio_reg->SGPIO_MULPOSR &= ~(SGPIO_MASK_MULPOSRST | SGPIO_MASK_MULPOSTC);
		}

	}

	reg_temp = psgpio_reg->SGPIO_IM;
	reg_temp &= ~(SGPIO_BIT_MULLOAD_IM);
	reg_temp |= ((psgpio_set_irq->imr_en) << SGPIO_SHIFT_MULLOAD_IM);
	psgpio_reg->SGPIO_IM = reg_temp;

	reg_temp = psgpio_reg->SGPIO_DATA_CTRL;
	reg_temp &= ~(SGPIO_BIT_MULLOAD_IE);
	reg_temp |= ((psgpio_set_irq->int_en) << SGPIO_SHIFT_MULLOAD_IE);
	psgpio_reg->SGPIO_DATA_CTRL = reg_temp;

	if (psgpio_set_irq->callback_reg_en == 1) {
		hal_rom_sgpio_reg_cb(psgpio_adp, psgpio_set_irq->callback, psgpio_set_irq->arg, Mulload_Sft);
	} else {
		hal_rom_sgpio_unreg_cb(psgpio_adp, Mulload_Sft);
	}

	return HAL_OK;

}

/**
 *  @brief  Control the interrupt when happen the bit shift of txdata.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  psgpio_set_irq The parameter structure is for initializing the interrupt event.
 *                      int_en - 0: disbale this event interrupt, 1: enable.
 *                      imr_en - 0: disbale mask event interrupt, 1: enable.
 *                      callback_reg_en - 0: don't register this callback function, 1: register this callback function.
 *                      callback - The callback function.
 *                      arg - The callback argument.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_set_txdata_prebuf_bit_shift_int(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_set_irq_t *psgpio_set_irq)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u32 reg_temp;

	reg_temp = psgpio_reg->SGPIO_IM;
	reg_temp &= ~(SGPIO_BIT_MULSFT_IM);
	reg_temp |= (psgpio_set_irq->imr_en << SGPIO_SHIFT_MULSFT_IM);
	psgpio_reg->SGPIO_IM = reg_temp;

	reg_temp = psgpio_reg->SGPIO_DATA_CTRL;
	reg_temp &= ~(SGPIO_BIT_MULSFT_IE);
	reg_temp |= (psgpio_set_irq->int_en << SGPIO_SHIFT_MULSFT_IE);
	psgpio_reg->SGPIO_DATA_CTRL = reg_temp;

	if (psgpio_set_irq->callback_reg_en == 1) {
		hal_rom_sgpio_reg_cb(psgpio_adp, psgpio_set_irq->callback, psgpio_set_irq->arg, Mulsft_Sft);
	} else {
		hal_rom_sgpio_unreg_cb(psgpio_adp, Mulsft_Sft);
	}
}

/**
 *  @brief  Reset the txdata.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_reset_txdata(hal_sgpio_adapter_t *psgpio_adp)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;

	psgpio_reg->SGPIO_MULDATA = 0X00;
	psgpio_reg->SGPIO_MULDATA_DP = 0X00;
}

/**
 *  @brief  Get the rxtc match value of the count unit. Change the unit from time to count.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  time_unit Select the time unit us or ns.
 *  @param[in]  time_value The time value.
 *
 *  @returns The rxtc match value.
 */
SECTION_SGPIO_TEXT
u32 hal_rom_sgpio_set_time_to_rxtc(hal_sgpio_adapter_t *psgpio_adp, sgpio_time_unit_t time_unit, u32 time_value)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u32 tc_unit, prescale_num;
	u16 old_prescale, new_prescale;
	float ns_unit, ftc_unit, tc_resolution;
	u32 reg_temp;

	old_prescale = ((psgpio_reg->SGPIO_RXPRVAL & SGPIO_MASK_RXPRVAL) >> SGPIO_SHIFT_RXPRVAL);

	prescale_num = (u32)old_prescale;

	ns_unit = (float)time_value;
	if (time_unit == Time_unit_us) {
		ns_unit = ns_unit * 1000;
	}

	while (1) {

		tc_resolution = (float)(prescale_num + 1) * psgpio_adp->sgpio_sclk_ns;

		ftc_unit = ns_unit / tc_resolution;

		tc_unit = (u32)(ftc_unit + 0.5f);

		if (tc_unit > 0xFFFF) {
			prescale_num++;
			if (prescale_num > 0xFFFF) {
				//dbg_printf("hal_sgpio_set_time_to_rxtc_rtl8195bhp: ns_unit is over range \r\n");
				break;
			}

			reg_temp = psgpio_reg->SGPIO_RXPRVAL;
			reg_temp &= ~(SGPIO_MASK_RXPRVAL);
			reg_temp |= (prescale_num << SGPIO_SHIFT_RXPRVAL);
			psgpio_reg->SGPIO_RXPRVAL = reg_temp;

		} else {
			break;
		}

	}

	new_prescale = (u16)prescale_num;

	if (new_prescale != old_prescale) {
		hal_rom_sgpio_update_rxtcmr(psgpio_adp, Rxtc_MatchEvent0, old_prescale);
		hal_rom_sgpio_update_rxtcmr(psgpio_adp, Rxtc_MatchEvent1, old_prescale);
		hal_rom_sgpio_update_rxtcmr(psgpio_adp, Rxtc_MatchEvent2, old_prescale);
	}

	if (tc_unit != 0x00) {
		tc_unit = tc_unit - 1;
	}

	return tc_unit;
}

/**
 *  @brief  Get the multc match value of the count unit. Change the unit from time to count.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  time_unit Select the time unit us or ns.
 *  @param[in]  time_value The time value.
 *
 *  @returns The multc match value.
 */
SECTION_SGPIO_TEXT
u32 hal_rom_sgpio_set_time_to_multc(hal_sgpio_adapter_t *psgpio_adp, sgpio_time_unit_t time_unit, u32 time_value)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u32 tc_unit, prescale_num;
	u16 old_prescale, new_prescale;
	float ns_unit, ftc_unit, tc_resolution;
	u32 reg_temp;

	old_prescale = ((psgpio_reg->SGPIO_MULPRVAL & SGPIO_MASK_MULPRVAL) >> SGPIO_SHIFT_MULPRVAL);

	prescale_num = (u32)old_prescale;

	ns_unit = (float)time_value;
	if (time_unit == Time_unit_us) {
		ns_unit = ns_unit * 1000;
	}

	while (1) {

		tc_resolution = (float)(prescale_num + 1) * psgpio_adp->sgpio_sclk_ns;

		ftc_unit = ns_unit / tc_resolution;

		tc_unit = (u32)(ftc_unit + 0.5f);

		if (tc_unit > 0xFFFF) {
			prescale_num++;
			if (prescale_num > 0xFFFF) {
				//dbg_printf("hal_sgpio_set_time_to_multc_rtl8195bhp: ns_unit is over range \r\n");
				break;
			}

			reg_temp = psgpio_reg->SGPIO_MULPRVAL;
			reg_temp &= ~(SGPIO_MASK_MULPRVAL);
			reg_temp |= (prescale_num << SGPIO_SHIFT_MULPRVAL);
			psgpio_reg->SGPIO_MULPRVAL = reg_temp;

		} else {
			break;
		}

	}

	new_prescale = (u16)prescale_num;

	if (tc_unit != 0x00) {
		tc_unit = tc_unit - 1;
	}

	if (new_prescale != old_prescale) {

		hal_rom_sgpio_update_multcmr(psgpio_adp, Multc_MatchGroup0, Multc_MatchEvent0, old_prescale);
		hal_rom_sgpio_update_multcmr(psgpio_adp, Multc_MatchGroup0, Multc_MatchEvent1, old_prescale);
		hal_rom_sgpio_update_multcmr(psgpio_adp, Multc_MatchGroup0, Multc_MatchEvent2, old_prescale);
		hal_rom_sgpio_update_multcmr(psgpio_adp, Multc_MatchGroup0, Multc_MatchEvent3, old_prescale);
		hal_rom_sgpio_update_multcmr(psgpio_adp, Multc_MatchGroup1, Multc_MatchEvent0, old_prescale);
		hal_rom_sgpio_update_multcmr(psgpio_adp, Multc_MatchGroup1, Multc_MatchEvent1, old_prescale);
		hal_rom_sgpio_update_multcmr(psgpio_adp, Multc_MatchGroup1, Multc_MatchEvent2, old_prescale);
		hal_rom_sgpio_update_multcmr(psgpio_adp, Multc_MatchGroup1, Multc_MatchEvent3, old_prescale);
	}

	return tc_unit;
}

/**
 *  @brief  Get the rxtc match value of the time unit. Change the unit from count to time.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  rxtc_unit The count value.
 *  @param[in]  time_unit Select the time unit us or ns.
 *
 *  @returns The rxtc match value.
 */
SECTION_SGPIO_TEXT
u32 hal_rom_sgpio_set_rxtc_to_time(hal_sgpio_adapter_t *psgpio_adp, u16 rxtc_unit, sgpio_time_unit_t time_unit)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u32 ns_unit, tc_resolution;
	u32 reg_temp;

	reg_temp = (psgpio_reg->SGPIO_RXPRVAL & SGPIO_MASK_RXPRVAL) >> SGPIO_SHIFT_RXPRVAL;
	tc_resolution = (reg_temp + 1) * (u32)psgpio_adp->sgpio_sclk_ns;

	ns_unit = (u32)rxtc_unit;

	if (ns_unit != 0x00) {
		ns_unit = (ns_unit + 1) * tc_resolution;
	}

	if (time_unit == Time_unit_us) {
		ns_unit = ns_unit / 1000;
	}

	return ns_unit;
}

/**
 *  @brief  Get the multc match value of the time unit. Change the unit from count to time.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  multc_unit The count value.
 *  @param[in]  time_unit Select the time unit us or ns.
 *
 *  @returns The multc match value.
 */
SECTION_SGPIO_TEXT
u32 hal_rom_sgpio_set_multc_to_time(hal_sgpio_adapter_t *psgpio_adp, u16 multc_unit, sgpio_time_unit_t time_unit)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u32 ns_unit, tc_resolution;
	u32 reg_temp;

	reg_temp = (psgpio_reg->SGPIO_MULPRVAL & SGPIO_MASK_MULPRVAL) >> SGPIO_SHIFT_MULPRVAL;
	tc_resolution = (reg_temp + 1) * (u32)psgpio_adp->sgpio_sclk_ns;

	ns_unit = (u32)multc_unit;

	if (ns_unit != 0x00) {
		ns_unit = (ns_unit + 1) * tc_resolution;
	}

	if (time_unit == Time_unit_us) {
		ns_unit = ns_unit / 1000;
	}

	return ns_unit;
}

/**
 *  @brief  Clean the SGPIO interrupt status.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  sgpio_is The interrupt event.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_clean_status(hal_sgpio_adapter_t *psgpio_adp, u32 sgpio_is)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;

	psgpio_reg->SGPIO_IS = sgpio_is;
}

/**
 *  @brief  Upate the rxtc match value because the prescaler value is changed.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  match_event Select the rxtc match event.
 *  @param[in]  old_prescale The old prescaler value.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_update_rxtcmr(hal_sgpio_adapter_t *psgpio_adp, sgpio_rxtc_match_event_t match_event, u16 old_prescale)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u32 rxprval, rxmr_new;
	float frxmr_new;
	u32 rxmr = 0;
	u32 reg_temp;

	reg_temp = (psgpio_reg->SGPIO_RXPRVAL & SGPIO_MASK_RXPRVAL) >> SGPIO_SHIFT_RXPRVAL;
	rxprval = reg_temp + 1;

	if (match_event == Rxtc_MatchEvent0) {
		rxmr = ((psgpio_reg->SGPIO_RXMR0 & SGPIO_MASK_RXMR0) >> SGPIO_SHIFT_RXMR0) + 1;
	} else if (match_event == Rxtc_MatchEvent1) {
		rxmr = ((psgpio_reg->SGPIO_RXMR1 & SGPIO_MASK_RXMR1) >> SGPIO_SHIFT_RXMR1) + 1;
	} else if (match_event == Rxtc_MatchEvent2) {
		rxmr = ((psgpio_reg->SGPIO_RXMR2 & SGPIO_MASK_RXMR2) >> SGPIO_SHIFT_RXMR2) + 1;
	}

	frxmr_new = (float)(rxmr * (u32)(old_prescale + 1)) / (float)(rxprval);
	rxmr_new = (u32)(frxmr_new + 0.5f);

	if (rxmr_new == 0x00) {
		rxmr_new = 1;
	}

	if (match_event == Rxtc_MatchEvent0) {
		reg_temp = psgpio_reg->SGPIO_RXMR0;
		reg_temp &= ~(SGPIO_MASK_RXMR0);
		reg_temp |= (((u16)rxmr_new - 1) << SGPIO_SHIFT_RXMR0);
		psgpio_reg->SGPIO_RXMR0 = reg_temp;
	} else if (match_event == Rxtc_MatchEvent1) {
		reg_temp = psgpio_reg->SGPIO_RXMR1;
		reg_temp &= ~(SGPIO_MASK_RXMR1);
		reg_temp |= (((u16)rxmr_new - 1) << SGPIO_SHIFT_RXMR1);
		psgpio_reg->SGPIO_RXMR1 = reg_temp;
	} else if (match_event == Rxtc_MatchEvent2) {
		reg_temp = psgpio_reg->SGPIO_RXMR2;
		reg_temp &= ~(SGPIO_MASK_RXMR2);
		reg_temp |= (((u16)rxmr_new - 1) << SGPIO_SHIFT_RXMR2);
		psgpio_reg->SGPIO_RXMR2 = reg_temp;
	}

}

/**
 *  @brief  Upate the multc match value because the prescaler value is changed.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  match_group Select the multc match group.
 *  @param[in]  match_event Select the multc match event.
 *  @param[in]  old_prescale The old prescaler value.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_update_multcmr(hal_sgpio_adapter_t *psgpio_adp, sgpio_multc_match_group_t match_group, sgpio_multc_match_event_t match_event,
								  u16 old_prescale)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u32 mulprval, mulmr_new;
	float fmulmr_new;
	u32 mulmr = 0;
	u32 reg_temp;

	reg_temp = (psgpio_reg->SGPIO_MULPRVAL & SGPIO_MASK_MULPRVAL) >> SGPIO_SHIFT_MULPRVAL;
	mulprval = reg_temp + 1;

	if (match_group == Multc_MatchGroup0) {
		if (match_event == Multc_MatchEvent0) {
			mulmr = ((psgpio_reg->SGPIO_MULMR01GP0 & SGPIO_MASK_MULMR0_GP0) >> SGPIO_SHIFT_MULMR0_GP0) + 1;
		} else if (match_event == Multc_MatchEvent1) {
			mulmr = ((psgpio_reg->SGPIO_MULMR01GP0 & SGPIO_MASK_MULMR1_GP0) >> SGPIO_SHIFT_MULMR1_GP0) + 1;
		} else if (match_event == Multc_MatchEvent2) {
			mulmr = ((psgpio_reg->SGPIO_MULMR23GP0 & SGPIO_MASK_MULMR2_GP0) >> SGPIO_SHIFT_MULMR2_GP0) + 1;
		} else if (match_event == Multc_MatchEvent3) {
			mulmr = ((psgpio_reg->SGPIO_MULMR23GP0 & SGPIO_MASK_MULMR3_GP0) >> SGPIO_SHIFT_MULMR3_GP0) + 1;
		}
	} else {
		if (match_event == Multc_MatchEvent0) {
			mulmr = ((psgpio_reg->SGPIO_MULMR01GP1 & SGPIO_MASK_MULMR0_GP1) >> SGPIO_SHIFT_MULMR0_GP1) + 1;
		} else if (match_event == Multc_MatchEvent1) {
			mulmr = ((psgpio_reg->SGPIO_MULMR01GP1 & SGPIO_MASK_MULMR1_GP1) >> SGPIO_SHIFT_MULMR1_GP1) + 1;
		} else if (match_event == Multc_MatchEvent2) {
			mulmr = ((psgpio_reg->SGPIO_MULMR23GP1 & SGPIO_MASK_MULMR2_GP1) >> SGPIO_SHIFT_MULMR2_GP1) + 1;
		} else if (match_event == Multc_MatchEvent3) {
			mulmr = ((psgpio_reg->SGPIO_MULMR23GP1 & SGPIO_MASK_MULMR3_GP1) >> SGPIO_SHIFT_MULMR3_GP1) + 1;
		}
	}

	fmulmr_new = (float)(mulmr * (u32)(old_prescale + 1)) / (float)(mulprval);
	mulmr_new = (u32)(fmulmr_new + 0.5f);

	if (mulmr_new == 0x00) {
		mulmr_new = 1;
	}

	if (match_group == Multc_MatchGroup0) {
		if (match_event == Multc_MatchEvent0) {
			reg_temp = psgpio_reg->SGPIO_MULMR01GP0;
			reg_temp &= ~(SGPIO_MASK_MULMR0_GP0);
			reg_temp |= (((u16)mulmr_new - 1) << SGPIO_SHIFT_MULMR0_GP0);
			psgpio_reg->SGPIO_MULMR01GP0 = reg_temp;
		} else if (match_event == Multc_MatchEvent1) {
			reg_temp = psgpio_reg->SGPIO_MULMR01GP0;
			reg_temp &= ~(SGPIO_MASK_MULMR1_GP0);
			reg_temp |= (((u16)mulmr_new - 1) << SGPIO_SHIFT_MULMR1_GP0);
			psgpio_reg->SGPIO_MULMR01GP0 = reg_temp;
		} else if (match_event == Multc_MatchEvent2) {
			reg_temp = psgpio_reg->SGPIO_MULMR23GP0;
			reg_temp &= ~(SGPIO_MASK_MULMR2_GP0);
			reg_temp |= (((u16)mulmr_new - 1) << SGPIO_SHIFT_MULMR2_GP0);
			psgpio_reg->SGPIO_MULMR23GP0 = reg_temp;
		} else if (match_event == Multc_MatchEvent3) {
			reg_temp = psgpio_reg->SGPIO_MULMR23GP0;
			reg_temp &= ~(SGPIO_MASK_MULMR3_GP0);
			reg_temp |= (((u16)mulmr_new - 1) << SGPIO_SHIFT_MULMR3_GP0);
			psgpio_reg->SGPIO_MULMR23GP0 = reg_temp;
		}
	} else {
		if (match_event == Multc_MatchEvent0) {
			reg_temp = psgpio_reg->SGPIO_MULMR01GP1;
			reg_temp &= ~(SGPIO_MASK_MULMR0_GP1);
			reg_temp |= (((u16)mulmr_new - 1) << SGPIO_SHIFT_MULMR0_GP1);
			psgpio_reg->SGPIO_MULMR01GP1 = reg_temp;
		} else if (match_event == Multc_MatchEvent1) {
			reg_temp = psgpio_reg->SGPIO_MULMR01GP1;
			reg_temp &= ~(SGPIO_MASK_MULMR1_GP1);
			reg_temp |= (((u16)mulmr_new - 1) << SGPIO_SHIFT_MULMR1_GP1);
			psgpio_reg->SGPIO_MULMR01GP1 = reg_temp;
		} else if (match_event == Multc_MatchEvent2) {
			reg_temp = psgpio_reg->SGPIO_MULMR23GP1;
			reg_temp &= ~(SGPIO_MASK_MULMR2_GP1);
			reg_temp |= (((u16)mulmr_new - 1) << SGPIO_SHIFT_MULMR2_GP1);
			psgpio_reg->SGPIO_MULMR23GP1 = reg_temp;
		} else if (match_event == Multc_MatchEvent3) {
			reg_temp = psgpio_reg->SGPIO_MULMR23GP1;
			reg_temp &= ~(SGPIO_MASK_MULMR3_GP1);
			reg_temp |= (((u16)mulmr_new - 1) << SGPIO_SHIFT_MULMR3_GP1);
			psgpio_reg->SGPIO_MULMR23GP1 = reg_temp;
		}
	}

}


//====== Normal Function======

/**
 *  @brief Configure SGPIO to become the rxtc timer.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  psgpio_rxtc_timer_mode The parameter structure is for initializing the rxtc timer mode.
 *                      timer_once_en - Enable that matching event is executed once.
 *                      time_unit - Select the time unit.
 *                      match_time1 - Matching this time 1 generates the interrupt.
 *                      match_time1_cb - User defined IRQ callback function. Using "NULL" will not generate this interrupt.
 *                      pmatch_time1_arg - User defined IRQ callback parameter.
 *                      match_time2 - Matching this time 2 generates the interrupt.
 *                      match_time2_cb - User defined IRQ callback function. Using "NULL" will not generate this interrupt.
 *                      pmatch_time2_arg - User defined IRQ callback parameter.
 *                      match_time_reset - This match time is able to make the timer reset and stop.
 *                      time_reset_cb - User defined IRQ callback function. Using "NULL" will not generate this interrupt.
 *                      ptime_reset_arg - User defined IRQ callback parameter.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_rxtc_timer_mode(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_timer_mode_t *psgpio_rxtc_timer_mode)
{
	hal_sgpio_rxtc_event_t sgpio_rxtc_event, sgpio_rxtc_event_stop;
	hal_sgpio_set_irq_t sgpio_set_irq;
	u16 cnt_tp;
	sgpio_time_unit_t time_unit;

	time_unit = psgpio_rxtc_timer_mode->time_unit;

	cnt_tp = (u16)hal_rom_sgpio_set_time_to_rxtc(psgpio_adp, time_unit, psgpio_rxtc_timer_mode->match_value1_time);
	hal_rom_sgpio_set_rxtc_match_value(psgpio_adp, Rxtc_MatchEvent1, cnt_tp);

	cnt_tp = (u16)hal_rom_sgpio_set_time_to_rxtc(psgpio_adp, time_unit, psgpio_rxtc_timer_mode->match_value2_time);
	hal_rom_sgpio_set_rxtc_match_value(psgpio_adp, Rxtc_MatchEvent2, cnt_tp);

	cnt_tp = (u16)hal_rom_sgpio_set_time_to_rxtc(psgpio_adp, time_unit, psgpio_rxtc_timer_mode->match_reset_value_time);
	hal_rom_sgpio_set_rxtc_match_value(psgpio_adp, Rxtc_MatchEvent0, cnt_tp);

	hal_rom_sgpio_get_rxtc_reset_ctrl(psgpio_adp, &sgpio_rxtc_event);
	sgpio_rxtc_event.rxtc_match_event0 = 1;
	hal_rom_sgpio_set_rxtc_reset_ctrl(psgpio_adp, &sgpio_rxtc_event);

	hal_rom_sgpio_get_rxtc_stop_ctrl(psgpio_adp, &sgpio_rxtc_event_stop);
	sgpio_rxtc_event_stop.rxtc_match_event0 = psgpio_rxtc_timer_mode->timer_once_en;
	hal_rom_sgpio_set_rxtc_stop_ctrl(psgpio_adp, &sgpio_rxtc_event_stop);

	sgpio_set_irq.imr_en = 0;
	if (psgpio_rxtc_timer_mode->match_value1_cb != NULL) {
		sgpio_set_irq.int_en = 1;
		sgpio_set_irq.callback_reg_en = 1;
		sgpio_set_irq.callback = psgpio_rxtc_timer_mode->match_value1_cb;
		sgpio_set_irq.arg = psgpio_rxtc_timer_mode->pmatch_value1_arg;
	} else {
		sgpio_set_irq.int_en = 0;
		sgpio_set_irq.callback_reg_en = 0;
	}
	hal_rom_sgpio_set_rxtc_int(psgpio_adp, Rxtc_MatchEvent1, &sgpio_set_irq);

	if (psgpio_rxtc_timer_mode->match_value2_cb != NULL) {
		sgpio_set_irq.int_en = 1;
		sgpio_set_irq.callback_reg_en = 1;
		sgpio_set_irq.callback = psgpio_rxtc_timer_mode->match_value2_cb;
		sgpio_set_irq.arg = psgpio_rxtc_timer_mode->pmatch_value2_arg;
	} else {
		sgpio_set_irq.int_en = 0;
		sgpio_set_irq.callback_reg_en = 0;
	}
	hal_rom_sgpio_set_rxtc_int(psgpio_adp, Rxtc_MatchEvent2, &sgpio_set_irq);

	if (psgpio_rxtc_timer_mode->reset_value_cb != NULL) {
		sgpio_set_irq.int_en = 1;
		sgpio_set_irq.callback_reg_en = 1;
		sgpio_set_irq.callback = psgpio_rxtc_timer_mode->reset_value_cb;
		sgpio_set_irq.arg = psgpio_rxtc_timer_mode->preset_value_arg;
	} else {
		sgpio_set_irq.int_en = 0;
		sgpio_set_irq.callback_reg_en = 0;
	}
	hal_rom_sgpio_set_rxtc_int(psgpio_adp, Rxtc_MatchEvent0, &sgpio_set_irq);

}

/**
 *  @brief Configure SGPIO to become the multc timer.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  psgpio_multc_timer_mode The parameter structure is for initializing the multc timer mode.
 *                      timer_once_en - Enable that matching event is executed once.
 *                      time_unit - Select the time unit.
 *                      match_time_reset - This match time is able to make the timer reset and stop.
 *                      time_reset_cb - User defined IRQ callback function. Using "NULL" will not generate this interrupt.
 *                      ptime_reset_arg - User defined IRQ callback parameter.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_multc_timer_mode(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_multc_timer_mode_t *psgpio_multc_timer_mode)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	hal_sgpio_multc_event_t sgpio_multc_event, sgpio_multc_event_stop;
	hal_sgpio_set_irq_t sgpio_set_irq;
	u16 cnt_tp;
	sgpio_time_unit_t time_unit;

	time_unit = psgpio_multc_timer_mode->time_unit;

	psgpio_reg->SGPIO_MULDATA = psgpio_reg->SGPIO_MULDATA & 0xFFFFFFFE;
	cnt_tp = (u16)hal_rom_sgpio_set_time_to_multc(psgpio_adp, time_unit, psgpio_multc_timer_mode->match_reset_value_time);
	hal_rom_sgpio_set_multc_match_value(psgpio_adp, Multc_MatchGroup0, Multc_MatchEvent0, cnt_tp);

	hal_rom_sgpio_get_multc_reset_ctrl(psgpio_adp, &sgpio_multc_event);
	sgpio_multc_event.multc_match_event0 = 1;
	hal_rom_sgpio_set_multc_reset_ctrl(psgpio_adp, &sgpio_multc_event);

	hal_rom_sgpio_get_multc_stop_ctrl(psgpio_adp, &sgpio_multc_event_stop);
	sgpio_multc_event_stop.multc_match_event0 = psgpio_multc_timer_mode->timer_once_en;
	hal_rom_sgpio_set_multc_stop_ctrl(psgpio_adp, &sgpio_multc_event_stop);

	sgpio_set_irq.imr_en = 0;
	if (psgpio_multc_timer_mode->reset_value_cb != NULL) {
		sgpio_set_irq.int_en = 1;
		sgpio_set_irq.callback_reg_en = 1;
		sgpio_set_irq.callback = psgpio_multc_timer_mode->reset_value_cb;
		sgpio_set_irq.arg = psgpio_multc_timer_mode->preset_value_arg;
	} else {
		sgpio_set_irq.int_en = 0;
		sgpio_set_irq.callback_reg_en = 0;
	}
	hal_rom_sgpio_set_multc_match_event0_int(psgpio_adp, &sgpio_set_irq);

}

/**
 *  @brief Configure SGPIO to count input triggers.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  psgpio_multc_counter_mode The parameter structure is for initializing the multc counter mode.
 *                      counter_en - To enable or disable.
 *                      input_edge - Select the edge of the trigger event.
 *                      match_value - When the counter value is equal to match_value, generate an interrupt.
 *                      match_cb - User defined IRQ callback function. Using "NULL" will not generate this interrupt.
 *                      pmatch_arg - User defined IRQ callback parameter.
 *                      match_reset_en - When the counter value is equal to match_value, reset the counter.
 *                      match_disable_en - When the counter value is equal to match_value, make counter_en become disable(0).
 *                      timeout_unit -Select the time unit.
 *                      counter_reset_timeout -Set the monitor period.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_multc_counter_mode(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_multc_counter_mode_t *psgpio_multc_counter_mode)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	hal_sgpio_multc_event_t sgpio_multc_event, sgpio_multc_event_stop;
	hal_sgpio_rxtc_event_t sgpio_rxtc_event, sgpio_rxtc_event_stop;
	hal_sgpio_set_irq_t sgpio_set_irq;
	u16 cnt_tp;
	sgpio_time_unit_t time_unit;
	u32 reg_temp;

	time_unit = psgpio_multc_counter_mode->time_unit;

	reg_temp = psgpio_reg->SGPIO_MULTMR_CTRL;
	reg_temp &= ~(SGPIO_MASK_MULMODE_EN);
	reg_temp |= (psgpio_multc_counter_mode->input_edge << SGPIO_SHIFT_MULMODE_EN);
	psgpio_reg->SGPIO_MULTMR_CTRL = reg_temp;

	psgpio_reg->SGPIO_MULDATA = psgpio_reg->SGPIO_MULDATA & 0xFFFFFFFE;

	hal_rom_sgpio_set_multc_match_value(psgpio_adp, Multc_MatchGroup0, Multc_MatchEvent0, psgpio_multc_counter_mode->match_counter_value);

	hal_rom_sgpio_get_multc_reset_ctrl(psgpio_adp, &sgpio_multc_event);
	sgpio_multc_event.multc_match_event0 = psgpio_multc_counter_mode->match_counter_reset_en;
	sgpio_multc_event.rxtc_match_event0 = 1;
	hal_rom_sgpio_set_multc_reset_ctrl(psgpio_adp, &sgpio_multc_event);

	hal_rom_sgpio_get_multc_stop_ctrl(psgpio_adp, &sgpio_multc_event_stop);
	sgpio_multc_event_stop.multc_match_event0 = psgpio_multc_counter_mode->match_counter_disable_en;
	hal_rom_sgpio_set_multc_stop_ctrl(psgpio_adp, &sgpio_multc_event_stop);

	if (psgpio_multc_counter_mode->counter_reset_timeout_value != 0x00) {
		reg_temp = psgpio_reg->SGPIO_RXTMR_CTRL;
		reg_temp &= ~(SGPIO_MASK_RXTMREDGE_SEL);
		reg_temp |= (psgpio_multc_counter_mode->input_edge << SGPIO_SHIFT_RXTMREDGE_SEL);
		psgpio_reg->SGPIO_RXTMR_CTRL = reg_temp;

		cnt_tp = (u16)hal_rom_sgpio_set_time_to_rxtc(psgpio_adp, time_unit, psgpio_multc_counter_mode->counter_reset_timeout_value);
		hal_rom_sgpio_set_rxtc_match_value(psgpio_adp, Rxtc_MatchEvent0, cnt_tp);

		hal_rom_sgpio_get_rxtc_reset_ctrl(psgpio_adp, &sgpio_rxtc_event);
		sgpio_rxtc_event.rxtc_match_event0 = 1;
		sgpio_rxtc_event.multc_match_event0 = 1;
		hal_rom_sgpio_set_rxtc_reset_ctrl(psgpio_adp, &sgpio_rxtc_event);

		hal_rom_sgpio_get_rxtc_stop_ctrl(psgpio_adp, &sgpio_rxtc_event_stop);
		sgpio_rxtc_event_stop.rxtc_match_event0 = 1;
		sgpio_rxtc_event_stop.multc_match_event0 = 1;
		hal_rom_sgpio_set_rxtc_stop_ctrl(psgpio_adp, &sgpio_rxtc_event_stop);
	} else {
		reg_temp = psgpio_reg->SGPIO_RXTMR_CTRL;
		reg_temp &= ~(SGPIO_MASK_RXTMREDGE_SEL);
		psgpio_reg->SGPIO_RXTMR_CTRL = reg_temp;
	}

	sgpio_set_irq.imr_en = 0;
	if (psgpio_multc_counter_mode->match_counter_cb != NULL) {
		sgpio_set_irq.int_en = 1;
		sgpio_set_irq.callback_reg_en = 1;
		sgpio_set_irq.callback = psgpio_multc_counter_mode->match_counter_cb;
		sgpio_set_irq.arg = psgpio_multc_counter_mode->pmatch_counter_arg;
	} else {
		sgpio_set_irq.int_en = 0;
		sgpio_set_irq.callback_reg_en = 0;
	}
	hal_rom_sgpio_set_multc_match_event0_int(psgpio_adp, &sgpio_set_irq);

	reg_temp = (psgpio_reg->SGPIO_MULTMR_CTRL & SGPIO_MASK_MULMODE_EN) >> SGPIO_SHIFT_MULMODE_EN;

	if (reg_temp != 0x00) {
		reg_temp = psgpio_reg->SGPIO_MULTMR_CTRL;
		reg_temp &= ~(SGPIO_BIT_MULTMR_CEN);
		reg_temp |= (psgpio_multc_counter_mode->counter_en << SGPIO_SHIFT_MULTMR_CEN);
		psgpio_reg->SGPIO_MULTMR_CTRL = reg_temp;
	} else {
		reg_temp = psgpio_reg->SGPIO_MULTMR_CTRL;
		reg_temp &= ~(SGPIO_BIT_MULTMR_CEN);
		psgpio_reg->SGPIO_MULTMR_CTRL = reg_temp;
	}

}

/**
 *  @brief Generate the external output when happen the match events of the rxtc timer.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  psgpio_rxtc_timer_match_output The parameter structure is for initializing the rxtc timer match output.
 *                      match_time1_output - Set the output value when match the time 1.
 *                      match_time2_output - Set the output value when match the time 2.
 *                      match_reset_time_output - Set the output value when match the reset time.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_rxtc_timer_match_output(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_timer_match_output_t *psgpio_rxtc_timer_match_output)
{
	hal_rom_sgpio_set_rxtc_external_match(psgpio_adp, Rxtc_MatchEvent1, psgpio_rxtc_timer_match_output->match_value1_output);
	hal_rom_sgpio_set_rxtc_external_match(psgpio_adp, Rxtc_MatchEvent2, psgpio_rxtc_timer_match_output->match_value2_output);
	hal_rom_sgpio_set_rxtc_external_match(psgpio_adp, Rxtc_MatchEvent0, psgpio_rxtc_timer_match_output->match_reset_value_output);
}

/**
 *  @brief Generate the external output when happen the match events of the multc timer counter.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  psgpio_multc_timer_counter_match_output The parameter structure is for initializing the multc timer match output.
 *                      source_unit - Select the time unit.
 *                      match_value1_output - Set the output value when happen the multc match event 1.
 *                      match_value1 - The match value 1 of the multc timer counter.
 *                      match_value2_output - Set the output value when happen the multc match event 2.
 *                      match_value2 - The match value 2 of the multc timer counter.
 *                      match_value3_output - Set the output value when happen the multc match event 3.
 *                      match_value3 - The match value 3 of the multc timer counter.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_multc_timer_counter_match_output(hal_sgpio_adapter_t *psgpio_adp,
		hal_sgpio_multc_timer_counter_match_output_t *psgpio_multc_timer_counter_match_output)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u16 cnt_tp;
	sgpio_time_unit_t time_unit;

	psgpio_reg->SGPIO_MULDATA = psgpio_reg->SGPIO_MULDATA & 0xFFFFFFFE;

	if (psgpio_multc_timer_counter_match_output->source_unit != Countr_mode_unit_cnt) {

		time_unit = psgpio_multc_timer_counter_match_output->source_unit;

		cnt_tp = (u16)hal_rom_sgpio_set_time_to_multc(psgpio_adp, time_unit, psgpio_multc_timer_counter_match_output->match_value1);
		hal_rom_sgpio_set_multc_match_value(psgpio_adp, Multc_MatchGroup0, Multc_MatchEvent1, cnt_tp);

		cnt_tp = (u16)hal_rom_sgpio_set_time_to_multc(psgpio_adp, time_unit, psgpio_multc_timer_counter_match_output->match_value2);
		hal_rom_sgpio_set_multc_match_value(psgpio_adp, Multc_MatchGroup0, Multc_MatchEvent2, cnt_tp);

		cnt_tp = (u16)hal_rom_sgpio_set_time_to_multc(psgpio_adp, time_unit, psgpio_multc_timer_counter_match_output->match_value3);
		hal_rom_sgpio_set_multc_match_value(psgpio_adp, Multc_MatchGroup0, Multc_MatchEvent3, cnt_tp);

	} else {
		hal_rom_sgpio_set_multc_match_value(psgpio_adp, Multc_MatchGroup0, Multc_MatchEvent1, psgpio_multc_timer_counter_match_output->match_value1);
		hal_rom_sgpio_set_multc_match_value(psgpio_adp, Multc_MatchGroup0, Multc_MatchEvent2, psgpio_multc_timer_counter_match_output->match_value2);
		hal_rom_sgpio_set_multc_match_value(psgpio_adp, Multc_MatchGroup0, Multc_MatchEvent3, psgpio_multc_timer_counter_match_output->match_value3);
	}

	hal_rom_sgpio_set_multc_external_match(psgpio_adp, Multc_MatchEvent1, psgpio_multc_timer_counter_match_output->match_value1_output);
	hal_rom_sgpio_set_multc_external_match(psgpio_adp, Multc_MatchEvent2, psgpio_multc_timer_counter_match_output->match_value2_output);
	hal_rom_sgpio_set_multc_external_match(psgpio_adp, Multc_MatchEvent3, psgpio_multc_timer_counter_match_output->match_value3_output);
}

/**
 *  @brief Configure SGPIO to become the capture mode for measuring the pulse width.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  psgpio_rxtc_capture_mode The parameter structure is for initializing the rxtc capture mode.
 *                      capture_en - To enable or disable.
 *                      start_timer_edge - Select the trigger edge for starting the rxtc timer.
 *                      input_capture_edge - Select the capture edge for capturing the time.
 *                      capture_timer_reset_en - When happen the capture event, reset the rxtc timer.
 *                      capture_timer_disable_en - When happen the capture event, stop the rxtc timer.
 *                      max_capture_range_us - Set the maximum possible measurement value for making the prescale of the timer automatically.
 *                      capture_cb - User defined IRQ callback function. Using "NULL" will not generate this interrupt.
 *                      pcapture_arg - User defined IRQ callback parameter.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_rxtc_capture_mode(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_capture_mode_t *psgpio_rxtc_capture_mode)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	hal_sgpio_rxtc_event_t sgpio_rxtc_event, sgpio_rxtc_event_stop;
	hal_sgpio_set_irq_t sgpio_set_irq;
	float max_capture_range_us, timer_max_us;
	u32 prescale32_tp;
	u32 reg_temp;

	if (psgpio_rxtc_capture_mode->max_capture_range_us != 0x00) {
		timer_max_us = 0xFFFF * psgpio_adp->sgpio_sclk_ns / 1000;
		max_capture_range_us = (float)psgpio_rxtc_capture_mode->max_capture_range_us;
		prescale32_tp = (u32)(max_capture_range_us / timer_max_us);

		if ((prescale32_tp & 0xffff0000) == 0x00) {
			reg_temp = psgpio_reg->SGPIO_RXPRVAL;
			reg_temp &= ~(SGPIO_MASK_RXPRVAL);
			reg_temp |= (((u16)prescale32_tp) << SGPIO_SHIFT_RXPRVAL);
			psgpio_reg->SGPIO_RXPRVAL = reg_temp;
		} else {
			reg_temp = psgpio_reg->SGPIO_RXPRVAL;
			reg_temp &= ~(SGPIO_MASK_RXPRVAL);
			psgpio_reg->SGPIO_RXPRVAL = reg_temp;
			//dbg_printf("hal_sgpio_rxtc_capture_mode_rtl8195bhp: max_capture_range_us is over range \r\n");
		}

	} else {
		reg_temp = psgpio_reg->SGPIO_RXPRVAL;
		reg_temp &= ~(SGPIO_MASK_RXPRVAL);
		psgpio_reg->SGPIO_RXPRVAL = reg_temp;
	}

	reg_temp = psgpio_reg->SGPIO_RXTMR_CTRL;
	reg_temp &= ~(SGPIO_MASK_RXTMREDGE_SEL);
	reg_temp |= (psgpio_rxtc_capture_mode->start_timer_edge << SGPIO_SHIFT_RXTMREDGE_SEL);
	psgpio_reg->SGPIO_RXTMR_CTRL = reg_temp;

	hal_rom_sgpio_set_capture_ctrl(psgpio_adp, psgpio_rxtc_capture_mode->input_capture_edge, psgpio_rxtc_capture_mode->capture_en);

	hal_rom_sgpio_get_rxtc_reset_ctrl(psgpio_adp, &sgpio_rxtc_event);
	sgpio_rxtc_event.capture_event = psgpio_rxtc_capture_mode->capture_timer_reset_en;
	hal_rom_sgpio_set_rxtc_reset_ctrl(psgpio_adp, &sgpio_rxtc_event);

	hal_rom_sgpio_get_rxtc_stop_ctrl(psgpio_adp, &sgpio_rxtc_event_stop);
	sgpio_rxtc_event_stop.capture_event = psgpio_rxtc_capture_mode->capture_timer_disable_en;
	hal_rom_sgpio_set_rxtc_stop_ctrl(psgpio_adp, &sgpio_rxtc_event_stop);

	sgpio_set_irq.imr_en = 0;
	if (psgpio_rxtc_capture_mode->capture_cb != NULL) {
		sgpio_set_irq.int_en = 1;
		sgpio_set_irq.callback_reg_en = 1;
		sgpio_set_irq.callback = psgpio_rxtc_capture_mode->capture_cb;
		sgpio_set_irq.arg = psgpio_rxtc_capture_mode->pcapture_arg;
	} else {
		sgpio_set_irq.int_en = 0;
		sgpio_set_irq.callback_reg_en = 0;
	}
	hal_rom_sgpio_set_capture_int(psgpio_adp, &sgpio_set_irq);

}

/**
 *  @brief Make the capture timer reset and stop in the capture mode when the timer value is equal to timeout_value.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  psgpio_rxtc_capture_mode The parameter structure is for initializing the rxtc capture timeout.
 *                      capture_timeout_en - To enable or disable.
 *                      capture_timer_reset_en - Reset the capture timer when the timer value is equal to timeout_value.
 *                      capture_timer_disable_en - Stop the capture timer when the timer value is equal to timeout_value.
 *                      time_unit - Select the time unit.
 *                      timeout_value - Matching this timeout value generates the interrupt.
 *                      capture_timeout_cb - User defined IRQ callback function. Using "NULL" will not generate this interrupt.
 *                      pcapture_timeout_arg - User defined IRQ callback parameter.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_rxtc_capture_timeout(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_capture_timeout_t *psgpio_rxtc_capture_timeout)
{
	hal_sgpio_rxtc_event_t sgpio_rxtc_event, sgpio_rxtc_event_stop;
	hal_sgpio_set_irq_t sgpio_set_irq;
	u16 cnt_tp;
	sgpio_time_unit_t time_unit;

	time_unit = psgpio_rxtc_capture_timeout->time_unit;

	cnt_tp = (u16)hal_rom_sgpio_set_time_to_rxtc(psgpio_adp, time_unit, psgpio_rxtc_capture_timeout->timeout_value);
	hal_rom_sgpio_set_rxtc_match_value(psgpio_adp, Rxtc_MatchEvent2, cnt_tp);

	hal_rom_sgpio_get_rxtc_reset_ctrl(psgpio_adp, &sgpio_rxtc_event);
	hal_rom_sgpio_get_rxtc_stop_ctrl(psgpio_adp, &sgpio_rxtc_event_stop);

	if (psgpio_rxtc_capture_timeout->capture_timeout_en != 0x00) {
		sgpio_rxtc_event.rxtc_match_event2 = psgpio_rxtc_capture_timeout->capture_timer_reset_en;
		sgpio_rxtc_event_stop.rxtc_match_event2 = psgpio_rxtc_capture_timeout->capture_timer_disable_en;
	} else {
		sgpio_rxtc_event.rxtc_match_event2 = 0;
		sgpio_rxtc_event_stop.rxtc_match_event2 = 0;
	}

	hal_rom_sgpio_set_rxtc_reset_ctrl(psgpio_adp, &sgpio_rxtc_event);
	hal_rom_sgpio_set_rxtc_stop_ctrl(psgpio_adp, &sgpio_rxtc_event_stop);

	sgpio_set_irq.imr_en = 0;
	if ((psgpio_rxtc_capture_timeout->capture_timeout_en != 0x00) && (psgpio_rxtc_capture_timeout->capture_timeout_cb != NULL)) {
		sgpio_set_irq.int_en = 1;
		sgpio_set_irq.callback_reg_en = 1;
		sgpio_set_irq.callback = psgpio_rxtc_capture_timeout->capture_timeout_cb;
		sgpio_set_irq.arg = psgpio_rxtc_capture_timeout->pcapture_timeout_arg;
	} else {
		sgpio_set_irq.int_en = 0;
		sgpio_set_irq.callback_reg_en = 0;
	}
	hal_rom_sgpio_set_rxtc_int(psgpio_adp, Rxtc_MatchEvent2, &sgpio_set_irq);

}

/**
 *  @brief Monitor the capture value. When the capture value is bigger than monitor time, generate the interrupt.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  psgpio_rxtc_capture_monitor The parameter structure is for initializing the rxtc capture monitor.
 *                      capture_monitor_en - To enable or disable.
 *                      time_unit - Select the time unit.
 *                      monitor_time - The monitor value.
 *                      monitor_count - Set the continuous numbers of the successful condition. Value: 1 ~ 32, 0: do nothing.
 *                      capture_monitor_cb - User defined IRQ callback function. Using "NULL" will not generate this interrupt.
 *                      pcapture_monitor_arg - User defined IRQ callback parameter.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_rxtc_capture_monitor(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_rxtc_capture_monitor_t *psgpio_rxtc_capture_monitor)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	hal_sgpio_set_irq_t sgpio_set_irq;
	u32 data_mask;

	data_mask = 0xffffffff;
	if ((psgpio_rxtc_capture_monitor->monitor_count != 0x00) && (psgpio_rxtc_capture_monitor->monitor_count < 33)) {

		if (psgpio_rxtc_capture_monitor->monitor_count != 32) {
			data_mask = ~(data_mask >> (psgpio_rxtc_capture_monitor->monitor_count));
		} else {
			data_mask = 0xffffffff;
		}
	}

	if (psgpio_rxtc_capture_monitor->monitor_count > 32) {
		//dbg_printf("hal_sgpio_rxtc_capture_monitor_rtl8195bhp: monitor_count is bigger than 32 \r\n");
	}

	sgpio_set_irq.imr_en = 0;
	if ((psgpio_rxtc_capture_monitor->capture_monitor_en != 0x00) && (psgpio_rxtc_capture_monitor->capture_monitor_cb != NULL)) {
		hal_rom_sgpio_init_rxdata_capture_compare_time(psgpio_adp, 1, psgpio_rxtc_capture_monitor->time_unit, psgpio_rxtc_capture_monitor->monitor_time);
		hal_rom_sgpio_set_rxdata_direction(psgpio_adp, 0);

		sgpio_set_irq.int_en = 1;
		sgpio_set_irq.callback_reg_en = 1;
		sgpio_set_irq.callback = psgpio_rxtc_capture_monitor->capture_monitor_cb;
		sgpio_set_irq.arg = psgpio_rxtc_capture_monitor->pcapture_monitor_arg;
		hal_rom_sgpio_set_rxdata_match_int(psgpio_adp, 1, data_mask, &sgpio_set_irq);

		psgpio_reg->SGPIO_RXDATAMASK = data_mask;
	} else {
		hal_rom_sgpio_deinit_rxdata_capture_compare(psgpio_adp);

		sgpio_set_irq.int_en = 0;
		sgpio_set_irq.callback_reg_en = 0;
		hal_rom_sgpio_set_rxdata_match_int(psgpio_adp, 0, 0, &sgpio_set_irq);
		hal_rom_sgpio_reset_rxdata(psgpio_adp);
	}

}

/**
 *  @brief Get the capture value.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  time_unit Select the time unit.
 *
 *  @returns The capture value.
 */
SECTION_SGPIO_TEXT
u32 hal_rom_sgpio_get_rxtc_capture_time(hal_sgpio_adapter_t *psgpio_adp, sgpio_time_unit_t time_unit)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u16 capr;
	u32 cap_us;

	capr = (psgpio_reg->SGPIO_CAPR & SGPIO_MASK_CAPR) >> SGPIO_SHIFT_CAPR;
	cap_us = hal_rom_sgpio_set_rxtc_to_time(psgpio_adp, capr, time_unit);

	return cap_us;
}

/**
 *  @brief  Initialize that the rxdata source is the capture compare result.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  cmp_result_bit Set that the rxdata register receives value 0 or 1 when the capture value is bigger than cap_cmpval.
 *  @param[in]  time_unit Select the time unit.
 *  @param[in]  cap_cmpval_time The compare value. This unit is time.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_init_rxdata_capture_compare_time(hal_sgpio_adapter_t *psgpio_adp, sgpio_cmp_result_bit_t cmp_result_bit, sgpio_time_unit_t time_unit,
		u32 cap_cmpval_time)
{
	u16 cnt_tp;

	cnt_tp = (u16)hal_rom_sgpio_set_time_to_rxtc(psgpio_adp, time_unit, cap_cmpval_time);
	hal_rom_sgpio_init_rxdata_capture_compare(psgpio_adp, cmp_result_bit, cnt_tp);
}

/**
 *  @brief Set the trigger edge to start the timer, and sample the input value according to the sampling time.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  psgpio_sampling_data The parameter structure is for initializing the sampling rxdata.
 *                      sampling_en - To enable or disable.
 *                      start_timer_edge - Select the trigger edge for starting the rxtc timer.
 *                      time_unit - Select the time unit.
 *                      sampling_time1 - The sampling time 1 needs less than the sampling end time. Set to 0 when not in use.
 *                      sampling_time2 - The sampling time 2 needs less than the sampling end time. Set to 0 when not in use.
 *                      sampling_end_time - The sampling end time. Matching this time is to make the timer reset and stop.
 *                      sampling_bit_length - Set the bit length generated the interrupt. Value: 1 ~ 32, 0: do nothing.
 *                      first_msb_or_lsb - Putting in the register is LSB or MSB.
 *                      sampling_finish_cb - User defined IRQ callback function. Using "NULL" will not generate this interrupt.
 *                      psampling_finish_arg - User defined IRQ callback parameter.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_sampling_rxdata(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_sampling_rxdata_t *psgpio_sampling_data)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	hal_sgpio_rxtc_event_t sgpio_rxtc_event, sgpio_rxtc_event_stop;
	hal_sgpio_set_irq_t sgpio_set_irq;
	hal_sgpio_sampling_event_t sgpio_sampling_event;

	u16 cnt_tp;
	sgpio_time_unit_t time_unit;
	u32 reg_temp;

	time_unit = psgpio_sampling_data->time_unit;

	cnt_tp = (u16)hal_rom_sgpio_set_time_to_rxtc(psgpio_adp, time_unit, psgpio_sampling_data->sampling_time1_time);
	hal_rom_sgpio_set_rxtc_match_value(psgpio_adp, Rxtc_MatchEvent1, cnt_tp);

	cnt_tp = (u16)hal_rom_sgpio_set_time_to_rxtc(psgpio_adp, time_unit, psgpio_sampling_data->sampling_time2_time);
	hal_rom_sgpio_set_rxtc_match_value(psgpio_adp, Rxtc_MatchEvent2, cnt_tp);

	cnt_tp = (u16)hal_rom_sgpio_set_time_to_rxtc(psgpio_adp, time_unit, psgpio_sampling_data->sampling_time_end_time);
	hal_rom_sgpio_set_rxtc_match_value(psgpio_adp, Rxtc_MatchEvent0, cnt_tp);

	hal_rom_sgpio_get_rxtc_reset_ctrl(psgpio_adp, &sgpio_rxtc_event);
	sgpio_rxtc_event.rxtc_match_event0 = 1;
	hal_rom_sgpio_set_rxtc_reset_ctrl(psgpio_adp, &sgpio_rxtc_event);

	hal_rom_sgpio_get_rxtc_stop_ctrl(psgpio_adp, &sgpio_rxtc_event_stop);
	sgpio_rxtc_event_stop.rxtc_match_event0 = 1;
	hal_rom_sgpio_set_rxtc_stop_ctrl(psgpio_adp, &sgpio_rxtc_event_stop);

	hal_rom_sgpio_set_rxdata_direction(psgpio_adp, psgpio_sampling_data->first_msb_or_lsb);
	psgpio_adp->sgpio_rx_info.first_data_flag = psgpio_sampling_data->first_msb_or_lsb;

	if (psgpio_sampling_data->sampling_en != 0x00) {

		if (psgpio_sampling_data->sampling_time1_time != 0x00) {
			sgpio_sampling_event.rxtc_match_event1 = 1;
		} else {
			sgpio_sampling_event.rxtc_match_event1 = 0;
		}
		if (psgpio_sampling_data->sampling_time2_time != 0x00) {
			sgpio_sampling_event.rxtc_match_event2 = 1;
		} else {
			sgpio_sampling_event.rxtc_match_event2 = 0;
		}
		if (psgpio_sampling_data->sampling_time_end_time != 0x00) {
			sgpio_sampling_event.rxtc_match_event0 = 1;
		} else {
			sgpio_sampling_event.rxtc_match_event0 = 0;
		}
		hal_rom_sgpio_init_rxdata_time_sampling(psgpio_adp, &sgpio_sampling_event);

	} else {
		hal_rom_sgpio_deinit_rxdata_time_sampling(psgpio_adp);
	}

	sgpio_set_irq.imr_en = 0;
	if (psgpio_sampling_data->sampling_finish_cb != NULL) {
		sgpio_set_irq.int_en = 1;
		sgpio_set_irq.callback_reg_en = 1;
		sgpio_set_irq.callback = psgpio_sampling_data->sampling_finish_cb;
		sgpio_set_irq.arg = psgpio_sampling_data->psampling_finish_arg;
	} else {
		sgpio_set_irq.int_en = 0;
		sgpio_set_irq.callback_reg_en = 0;
	}
	hal_rom_sgpio_set_rxdata_load_int(psgpio_adp, psgpio_sampling_data->sampling_bit_length, &sgpio_set_irq);

	reg_temp = psgpio_reg->SGPIO_RXTMR_CTRL;
	reg_temp &= ~(SGPIO_MASK_RXTMREDGE_SEL);
	reg_temp |= (psgpio_sampling_data->start_timer_edge << SGPIO_SHIFT_RXTMREDGE_SEL);
	psgpio_reg->SGPIO_RXTMR_CTRL = reg_temp;

	psgpio_adp->sgpio_rx_info.rx_bit_length_copy = psgpio_sampling_data->sampling_bit_length;

}

/**
 *  @brief Get the register of the rxdata by sample or capture.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *
 *  @returns The result register.
 */
SECTION_SGPIO_TEXT
u32 hal_rom_sgpio_get_input_rxdata(hal_sgpio_adapter_t *psgpio_adp)
{
	u32 rxdata_tp;

	rxdata_tp = hal_rom_sgpio_get_rxdata(psgpio_adp);
	rxdata_tp = hal_rom_sgpio_get_arrange_rxdata(psgpio_adp, rxdata_tp);

	return rxdata_tp;
}

/**
 *  @brief Get the mask and arrange rxdata.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  rxdata_tp The rxdata value.
 *
 *  @returns The rxdata result.
 */
SECTION_SGPIO_TEXT
u32 hal_rom_sgpio_get_arrange_rxdata(hal_sgpio_adapter_t *psgpio_adp, u32 rxdata_tp)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u8 bit_length;
	u32 bit_length_mask;
	u8 bit_length_shift;

	bit_length = ((psgpio_reg->SGPIO_RXPOSR & SGPIO_MASK_RXPOSRST) >> SGPIO_SHIFT_RXPOSRST) + 1;

	bit_length_mask = 0xFFFFFFFF;
	bit_length_shift = 32 - bit_length;
	bit_length_mask = bit_length_mask >> bit_length_shift;

	if (psgpio_adp->sgpio_rx_info.first_data_flag == First_Data_LSB) {
		rxdata_tp = rxdata_tp >> bit_length_shift;
	}

	rxdata_tp = rxdata_tp & bit_length_mask;

	return rxdata_tp;
}

/**
 *  @brief Set the trigger edge to start the timer, and translate the capture time into "0" or "1" according to the result of the comparison.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  psgpio_compare_data The parameter structure is for initializing the capture compare rxdata.
 *                      sampling_en - To enable or disable.
 *                      capture_en - Select the trigger edge for starting the rxtc timer.
 *                      input_capture_edge - Select the capture edge for capturing the time.
 *                      max_capture_range_us - Set the maximum possible measurement value for making the prescale of the timer automatically.
 *                      time_unit - Select the time unit.
 *                      capture_compare_value_time - Set the compare time.
 *                      compare_result_bit - Deciding the value of the result bit is "0" or "1".
 *                      compare_bit_length - Set the bit length generated the interrupt. Value: 1 ~ 32, 0: do nothing.
 *                      first_msb_or_lsb - Putting in the register is LSB or MSB.
 *                      sampling_finish_cb - User defined IRQ callback function. Using "NULL" will not generate this interrupt.
 *                      psampling_finish_arg - User defined IRQ callback parameter.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_capture_compare_rxdata(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_capture_compare_rxdata_t *psgpio_compare_data)
{
	hal_sgpio_rxtc_capture_mode_t rxtc_capture_mode;
	hal_sgpio_set_irq_t sgpio_set_irq;

	rxtc_capture_mode.capture_en = psgpio_compare_data->capture_en;
	rxtc_capture_mode.start_timer_edge = psgpio_compare_data->start_timer_edge;
	rxtc_capture_mode.input_capture_edge = psgpio_compare_data->input_capture_edge;
	rxtc_capture_mode.capture_timer_reset_en = 1;
	rxtc_capture_mode.capture_timer_disable_en = 1;
	rxtc_capture_mode.max_capture_range_us = psgpio_compare_data->max_capture_range_us;
	rxtc_capture_mode.capture_cb = NULL;
	rxtc_capture_mode.pcapture_arg = NULL;
	hal_rom_sgpio_rxtc_capture_mode(psgpio_adp, &rxtc_capture_mode);

	hal_rom_sgpio_set_rxdata_direction(psgpio_adp, psgpio_compare_data->first_msb_or_lsb);
	psgpio_adp->sgpio_rx_info.first_data_flag = psgpio_compare_data->first_msb_or_lsb;

	if (psgpio_compare_data->capture_en != 0x00) {
		hal_rom_sgpio_init_rxdata_capture_compare_time(psgpio_adp, psgpio_compare_data->compare_result_bit, psgpio_compare_data->time_unit,
				psgpio_compare_data->capture_compare_value_time);
	} else {
		hal_rom_sgpio_deinit_rxdata_capture_compare(psgpio_adp);
	}

	sgpio_set_irq.imr_en = 0;
	if (psgpio_compare_data->compare_finish_cb != NULL) {
		sgpio_set_irq.int_en = 1;
		sgpio_set_irq.callback_reg_en = 1;
		sgpio_set_irq.callback = psgpio_compare_data->compare_finish_cb;
		sgpio_set_irq.arg = psgpio_compare_data->pcompare_finish_arg;
	} else {
		sgpio_set_irq.int_en = 0;
		sgpio_set_irq.callback_reg_en = 0;
	}
	hal_rom_sgpio_set_rxdata_load_int(psgpio_adp, psgpio_compare_data->compare_bit_length, &sgpio_set_irq);

}

/**
 *  @brief Configure the waveforms of the bit 0 and bit 1 for the output.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  psgpio_txdata_bit_symbol The parameter structure is for initializing the txdata bit symbol.
 *                      initial_output_value - Set the initial output value.
 *                      time_unit - Select the time unit.
 *                      bit0_middle_change_time - The time is to change the output value for the bit 0.
 *                      bit0_duration_time - The duration of the bit 0.
 *                      bit1_middle_change_time - The time is to change the output value for the bit 1.
 *                      bit1_duration_time - The duration of the bit 1.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_txdata_bit_symbol(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_txdata_bit_symbol_t *psgpio_txdata_bit_symbol)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u16 cnt_tp;
	sgpio_time_unit_t time_unit;
	u32 reg_temp;

	time_unit = psgpio_txdata_bit_symbol->time_unit;

	if (psgpio_txdata_bit_symbol->initial_output_value == Output_Is_Low) {
		reg_temp = psgpio_reg->SGPIO_OUTPUT;
		reg_temp &= ~(SGPIO_BIT_OUTPUT);
		psgpio_reg->SGPIO_OUTPUT = reg_temp;
	} else {
		reg_temp = psgpio_reg->SGPIO_OUTPUT;
		reg_temp |= SGPIO_BIT_OUTPUT;
		psgpio_reg->SGPIO_OUTPUT = reg_temp;
	}

	hal_rom_sgpio_set_multc_match_value(psgpio_adp, Multc_MatchGroup0, Multc_MatchEvent1, 0x00);
	hal_rom_sgpio_set_multc_match_value(psgpio_adp, Multc_MatchGroup1, Multc_MatchEvent1, 0x00);

	cnt_tp = (u16)hal_rom_sgpio_set_time_to_multc(psgpio_adp, time_unit, psgpio_txdata_bit_symbol->bit0_middle_change_time);
	hal_rom_sgpio_set_multc_match_value(psgpio_adp, Multc_MatchGroup0, Multc_MatchEvent2, cnt_tp);

	cnt_tp = (u16)hal_rom_sgpio_set_time_to_multc(psgpio_adp, time_unit, psgpio_txdata_bit_symbol->bit0_duration_time);
	hal_rom_sgpio_set_multc_match_value(psgpio_adp, Multc_MatchGroup0, Multc_MatchEvent0, cnt_tp);

	cnt_tp = (u16)hal_rom_sgpio_set_time_to_multc(psgpio_adp, time_unit, psgpio_txdata_bit_symbol->bit1_middle_change_time);
	hal_rom_sgpio_set_multc_match_value(psgpio_adp, Multc_MatchGroup1, Multc_MatchEvent2, cnt_tp);

	cnt_tp = (u16)hal_rom_sgpio_set_time_to_multc(psgpio_adp, time_unit, psgpio_txdata_bit_symbol->bit1_duration_time);
	hal_rom_sgpio_set_multc_match_value(psgpio_adp, Multc_MatchGroup1, Multc_MatchEvent0, cnt_tp);

	hal_rom_sgpio_set_multc_external_match(psgpio_adp, Multc_MatchEvent1, External_Toggle);
	hal_rom_sgpio_set_multc_external_match(psgpio_adp, Multc_MatchEvent2, External_Toggle);


}

/**
 *  @brief Set the output data according to the waveforms of the bit 0 and bit 1.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  psgpio_txdata The parameter structure is for initializing the txdata.
 *                      txdata_en - To enable or disable.
 *                      rx_output_en - Control the output behavior of the bidirectional Rx.
 *                      output_bit_counts - Set the output bit number.
 *                      ptxdata_pointer - Set the output data pointer.
 *                      txdata_finish_cb - When finish the TX output, generate the interrupt.
 *                      ptxdata_finish_arg - User defined IRQ callback parameter.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_txdata(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_txdata_t *psgpio_txdata)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	hal_sgpio_set_irq_t sgpio_set_irq;
	u32 bit_counts_tp, bit_counts_quot, bit_counts_rem;
	u16 bit_length;
	u32 *ptxdata_pointer;
	u32 reg_temp;

	if (psgpio_txdata->txdata_en != 0x00) {

		reg_temp = psgpio_reg->SGPIO_MULMC;
		reg_temp |= SGPIO_BIT_MUL_MCNTSTOP_EN;
		reg_temp |= SGPIO_BIT_MUL_MR0RST_EN;
		reg_temp |= SGPIO_BIT_MUL_MCNTRST_EN;
		reg_temp |= SGPIO_BIT_MUL_MR0SCLK_EN;
		psgpio_reg->SGPIO_MULMC = reg_temp;

		reg_temp = psgpio_reg->SGPIO_MULEMR;
		reg_temp &= ~(SGPIO_BIT_BIOUT_EN);
		reg_temp |= (psgpio_txdata->rx_direction_output_en << SGPIO_SHIFT_BIOUT_EN);
		psgpio_reg->SGPIO_MULEMR = reg_temp;

		bit_length = psgpio_txdata->output_bit_counts;
		if (bit_length > 32) {
			bit_length = 32;
		}
		psgpio_adp->sgpio_tx_info.bit_length_copy = bit_length;
		sgpio_set_irq.imr_en = 0;
		sgpio_set_irq.int_en = 1;
		sgpio_set_irq.callback_reg_en = 1;
		sgpio_set_irq.callback = hal_rom_sgpio_txdata_bit_length_irq;
		sgpio_set_irq.arg = psgpio_adp;
		hal_rom_sgpio_set_txdata_bit_length_int(psgpio_adp, bit_length, &sgpio_set_irq);

		psgpio_adp->sgpio_tx_info.output_bit_counts_copy = psgpio_txdata->output_bit_counts;
		bit_counts_tp = psgpio_txdata->output_bit_counts;

		bit_counts_quot = 0;
		if (bit_counts_tp > 64) {
			bit_counts_quot = bit_counts_tp >> 5;
			bit_counts_rem = bit_counts_tp & 0x1F;
			if (bit_counts_rem != 0x00) {
				bit_counts_quot = bit_counts_quot + 1;
			}
			bit_counts_quot = bit_counts_quot - 2;
		}
		psgpio_adp->sgpio_tx_info.bit_counts_quot_irq = bit_counts_quot;
		psgpio_adp->sgpio_tx_info.bit_counts_quot_irq_source = psgpio_adp->sgpio_tx_info.bit_counts_quot_irq;

		psgpio_adp->sgpio_tx_info.ptxdata_pointer_copy = psgpio_txdata->ptxdata_pointer;
		ptxdata_pointer = psgpio_txdata->ptxdata_pointer;
		psgpio_adp->sgpio_tx_info.ptxdata_pointer_irq = ptxdata_pointer;

		psgpio_reg->SGPIO_MULDATA = *ptxdata_pointer;

		if (bit_counts_tp > 32) {
			psgpio_adp->sgpio_tx_info.ptxdata_pointer_irq = (ptxdata_pointer + 1);
			psgpio_reg->SGPIO_MULDATA_DP = *(ptxdata_pointer + 1);
		}

		sgpio_set_irq.imr_en = 0;
		sgpio_set_irq.int_en = 1;
		sgpio_set_irq.callback_reg_en = 1;
		sgpio_set_irq.callback = psgpio_txdata->txdata_finish_cb;
		sgpio_set_irq.arg = psgpio_txdata->ptxdata_finish_arg;
		hal_rom_sgpio_set_multc_match_event0_cnt_int(psgpio_adp, 1, psgpio_txdata->output_bit_counts, &sgpio_set_irq);


	} else {
		sgpio_set_irq.imr_en = 0;
		sgpio_set_irq.int_en = 0;
		sgpio_set_irq.callback_reg_en = 0;
		hal_rom_sgpio_set_txdata_bit_length_int(psgpio_adp, 0, &sgpio_set_irq);
		hal_rom_sgpio_set_multc_match_event0_cnt_int(psgpio_adp, 0, 0, &sgpio_set_irq);

		psgpio_adp->sgpio_tx_info.bit_counts_quot_irq = 0;
		psgpio_adp->sgpio_tx_info.bit_counts_quot_irq_source = 0;
		psgpio_adp->sgpio_tx_info.ptxdata_pointer_irq = NULL;
	}
}

/**
 *  @brief Process txdata in the interrupt handler
 *
 *  @param[in]  data Set the SGPIO adapter.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_txdata_bit_length_irq(void *data)
{
	hal_sgpio_adapter_t *psgpio_adp = (hal_sgpio_adapter_t *) data;
	SGPIO_TypeDef *psgpio_reg;

	psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;

	if (psgpio_adp->sgpio_tx_info.bit_counts_quot_irq != 0x00) {
		psgpio_reg->SGPIO_MULDATA_DP = *(psgpio_adp->sgpio_tx_info.ptxdata_pointer_irq  + 1);
		psgpio_adp->sgpio_tx_info.ptxdata_pointer_irq = (psgpio_adp->sgpio_tx_info.ptxdata_pointer_irq  + 1);
		psgpio_adp->sgpio_tx_info.bit_counts_quot_irq = psgpio_adp->sgpio_tx_info.bit_counts_quot_irq - 1;
	}

}

/**
 *  @brief Start to output the TX data.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_send_txdata(hal_sgpio_adapter_t *psgpio_adp)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u32 *ptxdata_pointer;
	u32 bit_counts_tp;
	u32 reg_temp;

	ptxdata_pointer = psgpio_adp->sgpio_tx_info.ptxdata_pointer_copy;

	if (ptxdata_pointer != NULL) {
		hal_rom_sgpio_set_multc_rst(psgpio_adp);
		if (psgpio_adp->sgpio_tx_info.bit_length_copy != 0x00) {
			reg_temp = psgpio_reg->SGPIO_MULPOSR;
			reg_temp &= ~(SGPIO_MASK_MULPOSTC);
			reg_temp |= ((psgpio_adp->sgpio_tx_info.bit_length_copy - 1) << SGPIO_SHIFT_MULPOSTC);
			psgpio_reg->SGPIO_MULPOSR = reg_temp;
		} else {
			reg_temp = psgpio_reg->SGPIO_MULPOSR;
			reg_temp &= ~(SGPIO_MASK_MULPOSTC);
			psgpio_reg->SGPIO_MULPOSR = reg_temp;
		}
		if (psgpio_adp->sgpio_tx_info.output_bit_counts_copy != 0x00) {
			reg_temp = psgpio_reg->SGPIO_MUL_MCNT;
			reg_temp &= ~(SGPIO_MASK_MUL_MCNT);
			reg_temp |= ((psgpio_adp->sgpio_tx_info.output_bit_counts_copy - 1) << SGPIO_SHIFT_MUL_MCNT);
			psgpio_reg->SGPIO_MUL_MCNT = reg_temp;
		} else {
			reg_temp = psgpio_reg->SGPIO_MUL_MCNT;
			reg_temp &= ~(SGPIO_MASK_MUL_MCNT);
			psgpio_reg->SGPIO_MUL_MCNT = reg_temp;
		}

		bit_counts_tp = psgpio_adp->sgpio_tx_info.output_bit_counts_copy;

		psgpio_reg->SGPIO_MULDATA = *ptxdata_pointer;

		if (bit_counts_tp > 32) {
			ptxdata_pointer = ptxdata_pointer + 1;
			psgpio_reg->SGPIO_MULDATA_DP = *ptxdata_pointer;
		}

		psgpio_adp->sgpio_tx_info.bit_counts_quot_irq = psgpio_adp->sgpio_tx_info.bit_counts_quot_irq_source;
		psgpio_adp->sgpio_tx_info.ptxdata_pointer_irq = ptxdata_pointer;
		hal_rom_sgpio_set_multc_start_en(psgpio_adp, 1);
	} else {
		//dbg_printf("hal_sgpio_send_txdata_rtl8195bhp: ptxdata_pointer is null \r\n");
	}
}

/**
 *  @brief Reset the register of the RX data.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_reset_receive_rxdata(hal_sgpio_adapter_t *psgpio_adp)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u32 reg_temp;

	if (psgpio_adp->sgpio_rx_info.rx_bit_length_copy != 0x00) {
		reg_temp = psgpio_reg->SGPIO_RXPOSR;
		reg_temp &= ~(SGPIO_MASK_RXPOSRST);
		reg_temp |= ((psgpio_adp->sgpio_rx_info.rx_bit_length_copy - 1) << SGPIO_SHIFT_RXPOSRST);
		psgpio_reg->SGPIO_RXPOSR = reg_temp;

		reg_temp = psgpio_reg->SGPIO_RXPOSR;
		reg_temp &= ~(SGPIO_MASK_RXPOSTC);
		reg_temp |= ((psgpio_adp->sgpio_rx_info.rx_bit_length_copy - 1) << SGPIO_SHIFT_RXPOSTC);
		psgpio_reg->SGPIO_RXPOSR = reg_temp;

	} else {
		reg_temp = psgpio_reg->SGPIO_RXPOSR;
		reg_temp &= ~(SGPIO_MASK_RXPOSRST);
		psgpio_reg->SGPIO_RXPOSR = reg_temp;
	}
	hal_rom_sgpio_reset_rxdata(psgpio_adp);
}

/**
 *  @brief Disable the monitor mode.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_disable_rxdata_match(hal_sgpio_adapter_t *psgpio_adp)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u32 reg_temp;

	reg_temp = psgpio_reg->SGPIO_DATA_CTRL;
	reg_temp &= ~(SGPIO_BIT_PATTERN_MATCH_MODE);
	psgpio_reg->SGPIO_DATA_CTRL = reg_temp;
}

/**
 *  @brief Monitor the register of the sample or capture data. When the register value is equal to the monitor data, generate the interrupt.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  pmonitor_rxdata The parameter structure is for initializing the monitor rxdata.
 *                      monitor_en - To enable or disable.
 *                      monitor_data - Set the monitor data.
 *                      monitor_input_data_mask - Set the bit mask of the monitor data.
 *                      monitor_rxdata_cb -User defined IRQ callback function. Using "NULL" will not generate this interrupt.
 *                      pmonitor_rxdata_arg - User defined IRQ callback parameter.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_monitor_rxdata(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_monitor_rxdata_t *pmonitor_rxdata)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	hal_sgpio_set_irq_t sgpio_set_irq;
	u8 bit_length;
	u32 bit_length_mask;
	u8 bit_length_shift;
	u32 monitor_data;
	u32 mask_value;

	bit_length = ((psgpio_reg->SGPIO_RXPOSR & SGPIO_MASK_RXPOSRST) >> SGPIO_SHIFT_RXPOSRST) + 1;

	bit_length_mask = 0xFFFFFFFF;
	bit_length_shift = 32 - bit_length;
	bit_length_mask = bit_length_mask >> bit_length_shift;
	monitor_data = pmonitor_rxdata->monitor_data & bit_length_mask;
	mask_value = pmonitor_rxdata->monitor_input_data_mask & bit_length_mask;

	if (psgpio_adp->sgpio_rx_info.first_data_flag == First_Data_LSB) {
		monitor_data = monitor_data << bit_length_shift;
		mask_value = mask_value << bit_length_shift;
	}

	sgpio_set_irq.imr_en = 0;
	if ((pmonitor_rxdata->monitor_en != 0x00) && (pmonitor_rxdata->monitor_rxdata_cb != NULL)) {
		sgpio_set_irq.int_en = 1;
		sgpio_set_irq.callback_reg_en = 1;
		sgpio_set_irq.callback = pmonitor_rxdata->monitor_rxdata_cb;
		sgpio_set_irq.arg = pmonitor_rxdata->pmonitor_rxdata_arg;
		hal_rom_sgpio_set_rxdata_match_int(psgpio_adp, 1, monitor_data, &sgpio_set_irq);
	} else {
		sgpio_set_irq.int_en = 0;
		sgpio_set_irq.callback_reg_en = 0;
		hal_rom_sgpio_set_rxdata_match_int(psgpio_adp, 0, monitor_data, &sgpio_set_irq);
		hal_rom_sgpio_reset_rxdata(psgpio_adp);
	}

	psgpio_reg->SGPIO_RXDATAMASK = mask_value;

}

/**
 *  @brief Reset the multc FIFO.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_multc_fifo_reset(hal_sgpio_adapter_t *psgpio_adp)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u8 mul_fmode_en_tp;
	u32 reg_temp;

	mul_fmode_en_tp = (psgpio_reg->SGPIO_MULMC & SGPIO_BIT_MUL_FMODE_EN) >> SGPIO_SHIFT_MUL_FMODE_EN;

	reg_temp = psgpio_reg->SGPIO_MULMC;
	reg_temp &= ~(SGPIO_BIT_MUL_FMODE_EN);
	psgpio_reg->SGPIO_MULMC = reg_temp;

	reg_temp = psgpio_reg->SGPIO_MULMC;
	reg_temp &= ~(SGPIO_BIT_MUL_FMODE_EN);
	reg_temp |= (mul_fmode_en_tp << SGPIO_SHIFT_MUL_FMODE_EN);
	psgpio_reg->SGPIO_MULMC = reg_temp;

}

/**
 *  @brief Set the interrupt handler for the dma match output
 *
 *  @param[in]  data Set the SGPIO adapter.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_dma_match_output_irq_handle(void *data)
{
	hal_sgpio_adapter_t *psgpio_adp = (hal_sgpio_adapter_t *) data;

	// Call user TX complete callback
	if (NULL != psgpio_adp->sgpio_dma_info.irq_user_dma_cb) {
		psgpio_adp->sgpio_dma_info.irq_user_dma_cb(psgpio_adp->sgpio_dma_info.user_dma_arg);
	}

	//dbg_printf("=== Enter hal_sgpio_dma_match_output_irq_handle_rtl8195bhp === \r\n");
}

/**
 *  @brief Init GDMA for the dma match output
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  pgdma_adaptor The GDMA adapter.
 *  @param[in]  pdma_match_output The parameter structure is for initializing the SGPIO dma output.
 *                      match_value1_output - Set the output value when match value 1.
 *                      match_value2_output - Set the output value when match value 2.
 *                      match_value3_output - Set the output value when match value 3.
 *                      pmatch_value_ptr -The pointer is the memory address of setting the match time.
 *                      match_reset_counter - Set the number of reset times. An interrupt will be generated when the number of times is reached.
 *                      counter_finish_cb -User defined IRQ callback function. Using "NULL" will not generate this interrupt.
 *                      pcounter_finish_arg - User defined IRQ callback parameter.
 *
 *  @returns Always return HAL_OK
 */
SECTION_SGPIO_TEXT
HAL_Status hal_rom_sgpio_dma_match_output_init(hal_sgpio_adapter_t *psgpio_adp, hal_gdma_adaptor_t *pgdma_adaptor,
		hal_sgpio_dma_match_output_t *pdma_match_output)
{
	u8 sgpio_gdma_tp;

	psgpio_adp->phal_gdma_adaptor = pgdma_adaptor;


	if (psgpio_adp->sgpio_index == Sgpio0_Sel) {
		sgpio_gdma_tp = GDMA_HANDSHAKE_SGPIO0_TX;
	} else if (psgpio_adp->sgpio_index == Sgpio1_Sel) {
		sgpio_gdma_tp = 0; // Unknow
	} else if (psgpio_adp->sgpio_index == Sgpio2_Sel) {
		sgpio_gdma_tp = 0; // Unknow
	} else {
		return HAL_ERR_PARA;
	}

	pgdma_adaptor->gdma_ctl.tt_fc = TTFCMemToPeri;
	pgdma_adaptor->gdma_cfg.reload_dst = 1;
	pgdma_adaptor->gdma_cfg.dest_per = sgpio_gdma_tp;
	pgdma_adaptor->ch_dar = ((u32)psgpio_adp->base_addr + REG_PERI_MULFDATA);
	pgdma_adaptor->gdma_isr_type = (TransferType | ErrType);
	pgdma_adaptor->gdma_ctl.int_en = 1;
	pgdma_adaptor->gdma_ctl.dinc = NoChange;
	pgdma_adaptor->gdma_ctl.sinc = IncType;
	// cofigure gdma transfer
	pgdma_adaptor->gdma_ctl.src_msize   = MsizeFour;
	pgdma_adaptor->gdma_ctl.src_tr_width = TrWidthTwoBytes;
	pgdma_adaptor->gdma_ctl.dest_msize  = MsizeFour;
	pgdma_adaptor->gdma_ctl.dst_tr_width = TrWidthTwoBytes;
	pgdma_adaptor->gdma_ctl.block_size = 4 * pdma_match_output->match_reset_counter; //---4*length
	pgdma_adaptor->ch_sar = (u32)pdma_match_output->pmatch_value_ptr;

	hal_gdma_irq_reg(pgdma_adaptor, hal_rom_sgpio_dma_match_output_irq_handle, psgpio_adp);

	psgpio_adp->sgpio_dma_info.irq_user_dma_cb = pdma_match_output->counter_finish_cb;
	psgpio_adp->sgpio_dma_info.user_dma_arg = pdma_match_output->pcounter_finish_arg;

	hal_rom_sgpio_dma_handshake_init(psgpio_adp, pdma_match_output);

	return HAL_OK;
}

/**
 *  @brief De-initialize GDMA for the dma match output
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *
 *  @returns Always return HAL_OK
 */
SECTION_SGPIO_TEXT
HAL_Status hal_rom_sgpio_dma_match_output_deinit(hal_sgpio_adapter_t *psgpio_adp)
{
	if (psgpio_adp->phal_gdma_adaptor != NULL) {

		psgpio_adp->phal_gdma_adaptor = NULL;
	}

	return HAL_OK;
}

/**
 *  @brief Init the handshake for SGPIO and GDMA.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  pdma_match_output The parameter structure is for initializing the SGPIO dma output.
 *                      match_value1_output - Set the output value when match value 1.
 *                      match_value2_output - Set the output value when match value 2.
 *                      match_value3_output - Set the output value when match value 3.
 *                      pmatch_value_ptr -The pointer is the memory address of setting the match time.
 *                      match_reset_counter - Set the number of reset times. An interrupt will be generated when the number of times is reached.
 *                      counter_finish_cb -User defined IRQ callback function. Using "NULL" will not generate this interrupt.
 *                      pcounter_finish_arg - User defined IRQ callback parameter.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_dma_handshake_init(hal_sgpio_adapter_t *psgpio_adp, hal_sgpio_dma_match_output_t *pdma_match_output)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u32 reg_temp;

	reg_temp = psgpio_reg->SGPIO_MULMC;
	reg_temp |= SGPIO_BIT_MUL_FMODE_EN;
	reg_temp |= SGPIO_BIT_MUL_MR0RST_EN;
	reg_temp |= SGPIO_BIT_MUL_MCNTRST_EN;
	reg_temp |= SGPIO_BIT_MUL_MCNTSTOP_EN;
	reg_temp |= SGPIO_BIT_MUL_MR0MCNT_EN;
	reg_temp |= SGPIO_BIT_MUL_DMA_EN;
	psgpio_reg->SGPIO_MULMC = reg_temp;

	hal_rom_sgpio_set_multc_external_match(psgpio_adp, Multc_MatchEvent1, pdma_match_output->match_value1_output);
	hal_rom_sgpio_set_multc_external_match(psgpio_adp, Multc_MatchEvent2, pdma_match_output->match_value2_output);
	hal_rom_sgpio_set_multc_external_match(psgpio_adp, Multc_MatchEvent3, pdma_match_output->match_value3_output);

	if (pdma_match_output->match_reset_counter != 0x00) {
		reg_temp = psgpio_reg->SGPIO_MUL_MCNT;
		reg_temp &= ~(SGPIO_MASK_MUL_MCNT);
		reg_temp |= ((pdma_match_output->match_reset_counter - 1) << SGPIO_SHIFT_MUL_MCNT);
		psgpio_reg->SGPIO_MUL_MCNT = reg_temp;
	} else {
		reg_temp = psgpio_reg->SGPIO_MUL_MCNT;
		reg_temp &= ~(SGPIO_MASK_MUL_MCNT);
		psgpio_reg->SGPIO_MUL_MCNT = reg_temp;
	}

	reg_temp = (psgpio_reg->SGPIO_MUL_MCNT & SGPIO_MASK_MUL_MCNT) >> SGPIO_SHIFT_MUL_MCNT;
	psgpio_adp->sgpio_dma_info.match_reset_counter_copy = reg_temp;

}

/**
 *  @brief Preload the data to the buffer for starting GDMA.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_dma_preload_data(hal_sgpio_adapter_t *psgpio_adp)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u32 reg_temp;

	reg_temp = psgpio_reg->SGPIO_MULMC;
	reg_temp &= ~(SGPIO_BIT_MUL_DMA_START);
	reg_temp |= (1 << SGPIO_SHIFT_MUL_DMA_START);
	psgpio_reg->SGPIO_MULMC = reg_temp;

	while (((psgpio_reg->SGPIO_MULMC & SGPIO_BIT_MUL_DMA_START) >> SGPIO_SHIFT_MUL_DMA_START) == 1);
}

/**
 *  @brief Start the GDMA to send the TX waveform.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_dma_send_start(hal_sgpio_adapter_t *psgpio_adp)
{
	SGPIO_TypeDef *psgpio_reg = (SGPIO_TypeDef *)psgpio_adp->base_addr;
	u32 clean_cnt;
	phal_gdma_adaptor_t phal_gdma_adaptor;
	u32 reg_temp;

	clean_cnt = (u32)((u32)(psgpio_adp->sgpio_dma_info.match_reset_counter_copy + 1) << 3);

	if (psgpio_adp->dcache_memory_en == 1) {
		if (psgpio_adp->dcache_clean_by_addr != NULL) {
			psgpio_adp->dcache_clean_by_addr((uint32_t *)psgpio_adp->pmemory_addr, (int32_t)clean_cnt);
		} else {
			dbg_printf(" psgpio_adp->dcache_clean_by_addr is null \r\n");
		}
	}

	phal_gdma_adaptor = psgpio_adp->phal_gdma_adaptor;

	hal_rom_sgpio_multc_fifo_reset(psgpio_adp);
	hal_gdma_transfer_start(phal_gdma_adaptor, MultiBlkDis);
	hal_rom_sgpio_dma_preload_data(psgpio_adp);

	reg_temp = psgpio_reg->SGPIO_MUL_MCNT;
	reg_temp &= ~(SGPIO_MASK_MUL_MCNT);
	reg_temp |= (psgpio_adp->sgpio_dma_info.match_reset_counter_copy << SGPIO_SHIFT_MUL_MCNT);
	psgpio_reg->SGPIO_MUL_MCNT = reg_temp;

	hal_rom_sgpio_set_multc_start_en(psgpio_adp, 1);
}

/**
 *  @brief Change the memory data from the time unit to the count unit.
 *
 *  @param[in]  psgpio_adp The SGPIO adapter.
 *  @param[in]  pmemory_addr The pointer is the memory address of setting the match time.
 *  @param[in]  reset_cnt Set the number of reset times. An interrupt will be generated when the number of times is reached.
 *  @param[in]  time_unit Select the time unit.
 *
 *  @returns void
 */
SECTION_SGPIO_TEXT
void hal_rom_sgpio_dma_time_to_multc(hal_sgpio_adapter_t *psgpio_adp, u16 *pmemory_addr, u8 reset_cnt, sgpio_time_unit_t time_unit)
{
	u32 i, reset_cnt_tp;
	u16 value_max, value_tp;

	reset_cnt_tp = (u32)((u32)reset_cnt << 2);

	psgpio_adp->pmemory_addr = pmemory_addr;
	value_max = *pmemory_addr;

	for (i = 0; i < reset_cnt_tp; i++) {

		value_tp = *(pmemory_addr + i);
		if (value_max < value_tp) {
			value_max = value_tp;
		}
	}

	hal_rom_sgpio_set_time_to_multc(psgpio_adp, time_unit, value_max);

	for (i = 0; i < reset_cnt_tp; i++) {

		value_tp = *(pmemory_addr + i);
		*(pmemory_addr + i) = hal_rom_sgpio_set_time_to_multc(psgpio_adp, time_unit, value_tp);
	}

}

/** @} */ /* End of group hs_hal_sgpio_rom_func */
/// @endcond /* End of condition DOXYGEN_ROM_HAL_API */

/** @} */ /* End of group hs_hal_sgpio */

#endif /* CONFIG_SGPIO_EN */
