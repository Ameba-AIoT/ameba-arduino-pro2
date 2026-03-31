/**************************************************************************//**
 * @file     rtl8735b_comp.c
 * @brief    Implement flash controller ROM code functions.
 * @version  1.00
 * @date     2020-08-26
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
#include "hal_comp.h"
#include "hal_irq.h"
#include "hal_timer.h"
#include "hal_pinmux.h"
#include "hal_otp.h"

hal_comp_adapter_t comp_adapter;
void COMP_IRQHandler(void);

/// @cond DOXYGEN_ROM_HAL_API

/**

        \addtogroup hal_comp_rom_func Comparator HAL APIs
        \ingroup hal_comp
        \brief Configure COMP functions to check CPU status.
               The user application(in RAM space) should not call these APIs directly.
        @{
*/

void COMP_IRQHandler(void)
{
	uint32_t int_sts;
	//dbg_printf("\r\n comp int sts:%x.\r\n",&comp_adapter);
	hal_irq_clear_pending(Comparator_IRQn);

	int_sts = hal_comp_read_intr();
	//dbg_printf("\r\n comp int sts:%x.\r\n",&comp_adapter);
#if 0
	if (&comp_adapter == NULL) {
		// Not initialed yet, ignore interrupt
		__DSB();
		__ISB();
		return;
	}
#endif
	if (comp_adapter.comp_handler != NULL) {
		// call the user registed call-back
		(comp_adapter.comp_handler)(comp_adapter.comp_arg);
	}
	hal_comp_write(0x14, int_sts);
	__DSB();
	__ISB();
}

#if 0
/**
  \brief The stubs functions table to exports flash controller HAL functions in ROM.
*/
SECTION_WDT_STUBS const hal_wdt_func_stubs_t hal_wdt_stubs = {
	.wdt_set_timeout = hal_wdt_set_timeout,
	.wdt_init = hal_wdt_init,
	.wdt_enable = hal_wdt_enable,
	.wdt_disable = hal_wdt_disable,
	.wdt_refresh = hal_wdt_refresh,
	.wdt_reg_irq = hal_wdt_reg_irq,
	.wdt_reset = hal_wdt_reset
};
#endif
/**
 *  @brief comparator initial.
 *
 *
 *  @returns    void
 */
void hal_comp_init(void)
{
	memset((void *)&comp_adapter, 0, sizeof(hal_comp_adapter_t));
	AON_TypeDef *aon = AON;
	u8 data = 0;
	aon->AON_REG_AON_CLK_CTRL &= ~(AON_BIT_INT_CLK_SEL);
	aon->AON_REG_AON_PLL_CTRL0 &= ~(AON_MASK_PLL_R1_TUNE_2_0);
	aon->AON_REG_AON_PLL_CTRL0 |= (7 << AON_SHIFT_PLL_R1_TUNE_2_0);
	aon->AON_REG_AON_PLL_CTRL0 &= ~(AON_MASK_PLL_R2_TUNE_2_0);
	aon->AON_REG_AON_PLL_CTRL0 |= (3 << AON_SHIFT_PLL_R2_TUNE_2_0);
	aon->AON_REG_AON_FUNC_CTRL |= AON_BIT_COMP_FEN;
	hal_otp_init();
	data = hal_otp_byte_rd_syss(0x4A0);
	if (data != 0xFF) {
		aon->AON_REG_AON_SD_CTRL0 &= 0xFFFC0FFF;
		aon->AON_REG_AON_SD_CTRL0 |= ((data & 0x7) << 15);
		aon->AON_REG_AON_SD_CTRL0 |= ((data & 0x70) << 8);
	}
	aon->AON_REG_AON_SD_CTRL0 |= AON_BIT_POW_SD;
	hal_comp_write(0x44, 0x4020404);
	comp_adapter.comp_init = 1;
}

/**
 *  @brief comparator De-initial.
 *
 *
 *  @returns    void
 */
void hal_comp_deinit(void)
{
	AON_TypeDef *aon = AON;
	aon->AON_REG_AON_FUNC_CTRL &= ~AON_BIT_COMP_FEN;
	aon->AON_REG_AON_SD_CTRL0 &= ~AON_BIT_POW_SD;
	hal_comp_write(0x40, 0x0);
	memset((void *)&comp_adapter, 0, sizeof(hal_comp_adapter_t));
}

/**
 *  @brief Enable Auto Switch Mode.
 *
 *
 *  @returns    void
 */
void hal_comp_auto_switch(void)
{
	AON_TypeDef *aon = AON;
	aon->AON_REG_AON_FUNC_CTRL |= AON_BIT_COMP_FEN;
	hal_comp_write(0x40, 0x3);
	hal_comp_write(0x3C, 0x1);
	comp_adapter.comp_mode = 1;
}

/**
 *  @brief Enable SW Trigger.
 *
 *
 *  @returns    void
 */
void hal_comp_sw_trigger(void)
{
	AON_TypeDef *aon = AON;
	aon->AON_REG_AON_FUNC_CTRL |= AON_BIT_COMP_FEN;
	hal_comp_write(0x40, 0x1);
	hal_delay_ms(100);
	hal_comp_write(0x40, 0x3);
	comp_adapter.comp_mode = 2;
}

/**
 *  @brief Enable Extenal Timer.
 *
 *  @param[in]  timer_sel  Select timer number.
 *
 *  @returns    void
 */
void hal_comp_ext_timer(u8 timer_sel)
{
	AON_TypeDef *aon = AON;
	aon->AON_REG_AON_FUNC_CTRL |= AON_BIT_COMP_FEN;
	hal_comp_write(0x30, 0x1);
	hal_comp_write(0x34, timer_sel);
	hal_comp_write(0x40, 0x1);
	comp_adapter.comp_mode = 3;
}

/**
 *  @brief To Write Comprartor register.
 *
 *  @param[in]  addr  The comparator address.
 *  @param[in]  value  The comparator data.
 *
 *  @returns    void
 */
void hal_comp_write(u8 addr, u32 value)
{
	AON_TypeDef *aon = AON;
	aon->AON_REG_AON_LSFIF_RWD = value;
	aon->AON_REG_AON_LSFIF_CMD = 0;
	aon->AON_REG_AON_LSFIF_CMD |= addr;
	aon->AON_REG_AON_LSFIF_CMD |= (AON_MASK_AON_LSFIF_WE | AON_BIT_AON_LSFIF_WR);
	aon->AON_REG_AON_LSFIF_CMD |= (0x3 << AON_SHIFT_LSF_SEL);
	aon->AON_REG_AON_LSFIF_CMD |= AON_BIT_AON_LSFIF_POLL;
	u32 i = 0;

	for (i = 0; i < 1000000; i++) {
		if ((aon->AON_REG_AON_LSFIF_CMD & AON_BIT_AON_LSFIF_POLL) != AON_BIT_AON_LSFIF_POLL) {
			break;  // break the for loop
		} else {
			hal_delay_us(100);
		}
	}
}

/**
 *  @brief To Read Comprartor register.
 *
 *  @param[in]  addr  The comparator address.
 *
 *  @returns    vaule
 */
u32 hal_comp_read(u8 addr)
{
	AON_TypeDef *aon = AON;
	aon->AON_REG_AON_LSFIF_CMD = 0;
	aon->AON_REG_AON_LSFIF_CMD |= addr;
	aon->AON_REG_AON_LSFIF_CMD |= (AON_MASK_AON_LSFIF_WE);
	aon->AON_REG_AON_FUNC_CTRL &= ~AON_BIT_AON_LSFIF_WR;
	aon->AON_REG_AON_LSFIF_CMD |= (0x3 << AON_SHIFT_LSF_SEL);
	aon->AON_REG_AON_LSFIF_CMD |= AON_BIT_AON_LSFIF_POLL;
	u32 i = 0;

	for (i = 0; i < 1000000; i++) {
		if ((aon->AON_REG_AON_LSFIF_CMD & AON_BIT_AON_LSFIF_POLL) != AON_BIT_AON_LSFIF_POLL) {
			break;  // break the for loop
		} else {
			hal_delay_us(100);
		}
	}
	return aon->AON_REG_AON_LSFIF_RWD;
}

/**
 *  @brief To Set Comprartor Vref0 and Vref1.
 *
 *  @param[in]  ch_num   Select Channel Number0~3
 *  @param[in]  ref0        Set Vref0
 *  @param[in]  ref1        Set Vref1
 *
 *  @returns    void
 */
void hal_comp_set_vref(u8 ch_num, u8 ref0, u8 ref1)
{
	//AON_TypeDef *aon = AON;
	u32 buff = 0;
	buff = (ref1 << COMP_SHIFT_REF1);
	buff = buff | ref0;
	switch (ch_num) {
	case 0:
		comp_adapter.vref0_0 = ref0;
		comp_adapter.vref1_0 = ref1;
		hal_comp_write(0x0, buff);
		break;
	case 1:
		comp_adapter.vref0_1 = ref0;
		comp_adapter.vref1_1 = ref1;
		hal_comp_write(0x4, buff);
		break;
	case 2:
		comp_adapter.vref0_2 = ref0;
		comp_adapter.vref1_2 = ref1;
		hal_comp_write(0x8, buff);
		break;
	case 3:
		comp_adapter.vref0_3 = ref0;
		comp_adapter.vref1_3 = ref1;
		hal_comp_write(0xC, buff);
		break;
	}
}

/**
 *  @brief To Read Comprartor Interrupt Status.
 *
 *  @param[in]  void
 *
 *  @returns    vaule
 */
u32 hal_comp_read_intr(void)
{
	return hal_comp_read(0x14);
}
/**
 *  @brief To Set Comprartor Itemlist.
 *
 *  @param[in]  array   Itemlist
 *  @param[in]  length   Itemlist list length
 *
 *  @returns    void
 */
void hal_comp_set_itemlist(u8 *array, u8 length)
{
	u32 buff = 0, temp = 0;
	if (length > 4) {
		dbg_printf("comp list length is larger than 4.\n");
	}
	temp = *(array + 3);
	buff = (temp << COMP_SHIFT_ITEMSW_3);
	temp = *(array + 2);
	buff |= (temp << COMP_SHIFT_ITEMSW_2);
	temp = *(array + 1);
	buff |= (temp << COMP_SHIFT_ITEMSW_1);
	buff |= *array;
	hal_comp_write(0x1C, buff);
}

/**
 *  @brief To Set Comparartor Interrupt condition.
 *
 *  @param[in]  ch_num   Select Channel Number0~3
 *  @param[in]  en          Enable/disable interrrupt to system
 *  @param[in]  ctrl         Set interrupt trigger condition
 *
 *  @returns    void
 */
void hal_comp_set_intr_ctrl(u8 ch_num, u8 en, u8 ctrl)
{
	//AON_TypeDef *aon = AON;
	/*
	    ctrl:   sts
	    0:      00
	    1:      11
	    2:      10
	    3:      00 or 11
	*/
	u32 buff = 0;
	if (en == 1) {
		switch (ch_num) {
		case 0:
			buff = hal_comp_read(0x10);
			buff |= COMP_BIT_WK_SYS_EN_0;
			buff |= ((u32)ctrl << COMP_SHIFT_WK_SYS_CTRL_0);
			hal_comp_write(0x10, buff);
			break;
		case 1:
			buff = hal_comp_read(0x10);
			buff |= COMP_BIT_WK_SYS_EN_1;
			buff |= ((u32)ctrl << COMP_SHIFT_WK_SYS_CTRL_1);
			hal_comp_write(0x10, buff);
			break;
		case 2:
			buff = hal_comp_read(0x10);
			buff |= COMP_BIT_WK_SYS_EN_2;
			buff |= ((u32)ctrl << COMP_SHIFT_WK_SYS_CTRL_2);
			hal_comp_write(0x10, buff);
			break;
		case 3:
			buff = hal_comp_read(0x10);
			buff |= COMP_BIT_WK_SYS_EN_3;
			buff |= ((u32)ctrl << COMP_SHIFT_WK_SYS_CTRL_3);
			hal_comp_write(0x10, buff);
			break;
		}
	} else {
		switch (ch_num) {
		case 0:
			buff = hal_comp_read(0x10);
			buff &= ~(COMP_BIT_WK_SYS_EN_0);
			buff &= ~(COMP_MASK_WK_SYS_CTRL_0);
			hal_comp_write(0x10, buff);
			break;
		case 1:
			buff = hal_comp_read(0x10);
			buff &= ~(COMP_BIT_WK_SYS_EN_1);
			buff &= ~(COMP_MASK_WK_SYS_CTRL_1);
			hal_comp_write(0x10, buff);
			break;
		case 2:
			buff = hal_comp_read(0x10);
			buff &= ~(COMP_BIT_WK_SYS_EN_2);
			buff &= ~(COMP_MASK_WK_SYS_CTRL_2);
			hal_comp_write(0x10, buff);
			break;
		case 3:
			buff = hal_comp_read(0x10);
			buff &= ~(COMP_BIT_WK_SYS_EN_3);
			buff &= ~(COMP_MASK_WK_SYS_CTRL_3);
			hal_comp_write(0x10, buff);
			break;
		}
	}
}
/**
 *  @brief Registers a handler for the comparator interrupt.
 *
 *
 *  @param[in]  handler  The interrupt handler.
 *  @param[in]  arg  The application data will be passed back to the application
 *                   with the callback function.
 *
 *  @returns    void
 */
void hal_comp_reg_irq(irq_handler_t handler, void *arg)
{
#if 0
	if (pwdt_adapter == NULL) {
		DBG_MISC_ERR("Misc. Adp is NULL\r\n");
		return;
	}
#endif
	hal_irq_disable(Comparator_IRQn);
	__ISB();

	// Register UART    IRQ  to Vector table
	hal_irq_set_vector(Comparator_IRQn, (uint32_t)&COMP_IRQHandler);
	hal_irq_clear_pending(Comparator_IRQn);
	hal_irq_set_priority(Comparator_IRQn, 9);

	hal_irq_enable(Comparator_IRQn);
	comp_adapter.comp_arg = arg;
	comp_adapter.comp_handler = handler;
}

/**
 *  @brief To un-register the interrupt handler of the Comparator.
 *
 *
 *  @returns    void
 */
void hal_comp_unreg_irq(void)
{
	hal_irq_disable(Comparator_IRQn);    //tmp workaroud
	__ISB();
	comp_adapter.comp_arg = NULL;
	comp_adapter.comp_handler = NULL;
}

/** *@} */ /* End of group hal_comp_func */

/// @endcond /* End of condition DOXYGEN_ROM_HAL_API */

/** *@} */
