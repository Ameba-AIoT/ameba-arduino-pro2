/******************************************************************************
 * @file     hal_gpio.c
 * @brief    This GPIO HAL API functions.
 *
 * @version  V1.00
 * @date     2021-05-12
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

/**
 * @addtogroup hs_hal_gpio GPIO
 * @{
 */
#include "hal_gpio.h"
#include "hal_pinmux.h"
#include "platform_stdlib.h"

#include "hal_sys_ctrl.h"

#if defined(CONFIG_BUILD_NONSECURE) && (CONFIG_BUILD_NONSECURE != 0)
#include "hal_sys_ctrl_nsc.h"
#endif


#if CONFIG_GPIO_EN

#if defined(CONFIG_BUILD_SECURE) && (CONFIG_BUILD_SECURE != 0)
typedef void __attribute__((cmse_nonsecure_call)) ns_func(uint32_t, gpio_int_trig_type_t);
#endif

#if defined (CONFIG_BUILD_SECURE) && (CONFIG_BUILD_SECURE != 0)
void AON_IRQHandler_S_to_NS(void)
{
	uint32_t int_sts;
	uint32_t int_idx;
	uint32_t bit_mask;
	phal_gpio_irq_adapter_t pgpio_irq;
	gpio_int_trig_type_t int_type;

	hal_irq_clear_pending(AON_IRQn);
	DBG_GPIO_INFO("TZ RAM AON GPIO S->NS IRQHandler\r\n");

	int_sts = AON_GPIO->GPIO_INT_STS;

	if (*(hal_gpio_stubs.ppaon_gpio_comm_adp) == NULL) {
		// Not initialed yet, ignore interrupt
		AON_GPIO->GPIO_INT_CLR = int_sts;
		__DSB();
		__ISB();
		return;
	}

	pgpio_irq = (*(hal_gpio_stubs.ppaon_gpio_comm_adp))->gpio_irq_list_head;

	while ((pgpio_irq != NULL) && (int_sts != 0)) {

		int_idx = pgpio_irq->int_idx;
		bit_mask = 1 << int_idx;
		if (int_sts & bit_mask) {
			// this AON GPIO pin IRQ is pending
			// clear interrupt status
			AON_GPIO->GPIO_INT_CLR = bit_mask;
			int_sts &= ~bit_mask;
			if (pgpio_irq->irq_callback != NULL) {
				int_type = pgpio_irq->int_type;
				if (pgpio_irq->int_type == GPIO_IntType_EdgeDual) {
					if (*((volatile uint32_t *)(pgpio_irq->in_port)) & pgpio_irq->bit_mask) {
						int_type = GPIO_IntType_EdgeRising;
					} else {
						int_type = GPIO_IntType_EdgeFalling;
					}
				}

#if defined(CONFIG_BUILD_SECURE) && (CONFIG_BUILD_SECURE != 0) // Use this interrupt handler when AON GPIO calls cb func in non-secure domain
				// call the user registed call-back(S call NS)
				ns_func *fptr = cmse_nsfptr_create((ns_func *)(pgpio_irq->irq_callback));
				fptr(pgpio_irq->irq_callback_arg, int_type);
#else
				// call the user registed call-back (for Ignore Secure Build ONLY, because AON GPIO is Secure-only by default)
				(pgpio_irq->irq_callback)(pgpio_irq->irq_callback_arg, int_type);
#endif

			}
		}
		// check next AON GPIO IRQ pin
		pgpio_irq = pgpio_irq->pnext;
	}

	if (int_sts != 0) {
		// error: somehow, at least one AON GPIO pin IRQ didn't be handled
		// But we still need to clear all interrupt status
		AON_GPIO->GPIO_INT_CLR = int_sts;
		(*(hal_gpio_stubs.ppaon_gpio_comm_adp))->err_flag.irq_err = 1;
	}
	__DSB();
	__ISB();
}
#endif

/* Functions parking, to be called from AON GPIO NSC function */
/* These functions will not be exposed, meaning they will not be in hal_gpio.h. */

hal_status_t hal_aon_gpio_init(phal_gpio_adapter_t pgpio_adapter, uint32_t pin_name)
{

	hal_status_t ret;

	// AON GPIO
	hal_sys_peripheral_en(GPIO_AON, ENABLE);
#if (!defined (CONFIG_BUILD_NONSECURE)) || (CONFIG_BUILD_NONSECURE == 0)
	pgpio_adapter->s_ram_aon_gpio_on = 1;
#endif

	ret = hal_pinmux_register(pin_name, PID_GPIO);
	if (ret != HAL_OK) {
		return ret;
	}

	return hal_gpio_stubs.hal_gpio_init(pgpio_adapter, pin_name);
}

void hal_aon_gpio_deinit(phal_gpio_adapter_t pgpio_adapter)
{

	// AON GPIO
	hal_pinmux_unregister(pgpio_adapter->pin_name, PID_GPIO);
	hal_gpio_stubs.hal_gpio_deinit(pgpio_adapter);

}

hal_status_t hal_aon_gpio_port_init(phal_gpio_port_adapter_t pgpio_port_adapter, uint32_t port_idx,
									uint32_t mask, gpio_dir_t dir)
{
	// Note: No need to check parameters - has been checked in hal_gpio_port_init()
	io_pin_t pin_list[MAX_PIN_IN_PORT + 1];
	hal_status_t ret;
	gpio_pin_t pin;
	uint32_t i;
	uint32_t j;

	j = 0;

	hal_sys_peripheral_en(GPIO_AON, ENABLE);
	pin.pin_name_b.port = port_idx;

	DBG_GPIO_INFO("port_idx in **RAM**:%d\r\n", pin.pin_name_b.port);

	for (i = 0; i < MAX_PIN_IN_PORT; i++) {
		if (mask & (1 << i)) {
			pin.pin_name_b.pin = i;
			pin_list[j].pin_name = pin.pin_name;
			ret = hal_pinmux_register(pin_list[j].pin_name, PID_GPIO);
			if (ret != HAL_OK) {
				return ret;
			}
			j++;
		}
	}

#if IS_CUT_TEST(CONFIG_CHIP_VER) // Test Chip - Use patch
	return hal_rtl_gpio_port_init_patch(pgpio_port_adapter, port_idx, mask, dir);
#else // MP Chip
	return hal_gpio_stubs.hal_gpio_port_init(pgpio_port_adapter, port_idx, mask, dir);
#endif
}

#if !IS_CUT_TEST(CONFIG_CHIP_VER) // MP Chip only
void hal_aon_gpio_port_dir(phal_gpio_port_adapter_t pgpio_port_adapter, gpio_dir_t dir)
{
	hal_gpio_stubs.hal_gpio_port_dir(pgpio_port_adapter, dir);
}
#endif

void hal_aon_gpio_port_deinit(phal_gpio_port_adapter_t pgpio_port_adapter)
{

#if IS_CUT_TEST(CONFIG_CHIP_VER) // Test chip
	hal_rtl_gpio_port_deinit_patch(pgpio_port_adapter);

#else // MP Chip
	hal_gpio_stubs.hal_gpio_port_deinit(pgpio_port_adapter);

#endif
}

hal_status_t hal_aon_gpio_irq_init(phal_gpio_irq_adapter_t pgpio_irq_adapter, uint32_t pin_name,
								   gpio_irq_callback_t callback, uint32_t arg)
{
	hal_status_t ret;

	hal_sys_peripheral_en(GPIO_AON, ENABLE);

	ret = hal_pinmux_register(pin_name, PID_GPIO);
	if (ret != HAL_OK) {
		DBG_GPIO_ERR("If pin has been registered under GPIO pin init, deinit GPIO pin before reinitializing as GPIO pin.\r\n");
		return ret;
	}

#if IS_CUT_TEST(CONFIG_CHIP_VER)
	return hal_rtl_gpio_irq_init_patch(pgpio_irq_adapter, pin_name, callback, arg);
#else

	return hal_gpio_stubs.hal_gpio_irq_init(pgpio_irq_adapter, pin_name, callback, arg);
#endif
}

void hal_aon_gpio_irq_deinit(phal_gpio_irq_adapter_t pgpio_irq_adapter)
{
	hal_pinmux_unregister(pgpio_irq_adapter->pin_name, PID_GPIO);

#if IS_CUT_TEST(CONFIG_CHIP_VER)
	return hal_rtl_gpio_irq_deinit_patch(pgpio_irq_adapter);
#else
	hal_gpio_stubs.hal_gpio_irq_deinit(pgpio_irq_adapter);
#endif
}

void aon_gpio_sclk_source_select_via_NSC(uint32_t sclk_src_sel)
{

	AON_TypeDef *aon = AON;
	uint32_t val;

	if (sclk_src_sel) {
		if (sclk_src_sel > 1) {
			DBG_GPIO_WARN("sclk_src_sel is greater than 1! Using the case where sclk_src_sel == 1\r\n");
		}
		DBG_GPIO_INFO("AON LP 32K clock source\r\n");
		val = aon->AON_REG_AON_SRC_CLK_CTRL;
		val |= AON_BIT_GPIO_SCLK_SEL;
		aon->AON_REG_AON_SRC_CLK_CTRL = val;
	} else {
		DBG_GPIO_INFO("OSC 128K/4 (without SDM?)\r\n");
		val = aon->AON_REG_AON_SRC_CLK_CTRL;
		val &= ~AON_BIT_GPIO_SCLK_SEL;
		aon->AON_REG_AON_SRC_CLK_CTRL = val;
	}

}


void hal_aon_gpio_comm_init_via_NSC(phal_aon_gpio_comm_adapter_t paon_gpio_comm_adp)
{
#if defined (CONFIG_BUILD_SECURE) && (CONFIG_BUILD_SECURE != 0)

	AON_TypeDef *aon = AON;
	volatile uint32_t val;

	paon_gpio_comm_adp->gpio_irq_using = 0;
	paon_gpio_comm_adp->gpio_irq_list_head = NULL;
	paon_gpio_comm_adp->gpio_irq_list_tail = NULL;

	*(hal_gpio_stubs.ppaon_gpio_comm_adp) = paon_gpio_comm_adp;


	// This part below is added to address issues related to low-power operations - Standby/Sleep
	// This is because when exiting Standby mode, AON+0xC[7] is not reset to 0,
	// causing multiple interrupts to be triggered when GPIO IRQ is re-initialized and enabled.
	// FIX: Manually reset AON+0xC[7] (i.e., set to 0) in this function.

	val = AON->AON_REG_AON_CLK_CTRL;
	val &= ~(AON_BIT_GPIO_INTR_CLK);
	AON->AON_REG_AON_CLK_CTRL = val;

	DBG_GPIO_INFO("TZ RAM AON GPIO comm init (calling from NSC)\r\n");

	hal_irq_set_priority(AON_IRQn, AON_IRQPri);
	hal_irq_disable(AON_IRQn);
	__ISB();
	hal_irq_set_vector(AON_IRQn, (uint32_t)&AON_IRQHandler_S_to_NS);
	if (((AON->AON_REG_AON_FUNC_CTRL) & AON_BIT_GPIO_FEN) >> AON_SHIFT_GPIO_FEN == 1) {
		AON_GPIO->GPIO_INT_DIS = 0x3F;
		AON_GPIO->GPIO_INT_FUNC_DIS = 0x3F;
		AON_GPIO->GPIO_EI_EN = 0x3F;
	}
	hal_irq_enable(AON_IRQn);
	DBG_GPIO_INFO("ppaon_gpio_comm_adp in GPIO RAM (equivalent of __paon_gpio_comm_adp): %x\r\n", *(hal_gpio_stubs.ppaon_gpio_comm_adp));
#endif

}

/* Functions parking, to be called from AON GPIO NSC function */
/* These functions will not be exposed, meaning they will not be in hal_gpio.h. */

void hal_gpio_comm_init(phal_gpio_comm_adapter_t pgpio_comm_adp)
{
#if IS_CUT_TEST(CONFIG_CHIP_VER)
	hal_rtl_gpio_comm_init_patch(pgpio_comm_adp);
#else
	hal_gpio_stubs.hal_gpio_comm_init(pgpio_comm_adp);
#endif
}


// Note to self: For commm_init, actually can just, if NS, call to NSC then call down to ROM to do everything; if the config below doesn't work
void hal_aon_gpio_comm_init(phal_aon_gpio_comm_adapter_t paon_gpio_comm_adp)
{

#if defined(CONFIG_BUILD_NONSECURE) && (CONFIG_BUILD_NONSECURE != 0)
	DBG_GPIO_INFO("TZ RAM AON GPIO comm init (Calling NSC)\r\n");

	hal_aon_gpio_comm_init_nsc(paon_gpio_comm_adp);

#else
	DBG_GPIO_INFO("NTZ RAM AON GPIO comm init (Calling ROM patch)\r\n");

	// All cuts of chip to route via ROM patch
	hal_rtl_aon_gpio_comm_init_patch(paon_gpio_comm_adp);

	//hal_gpio_stubs.hal_aon_gpio_comm_init(paon_gpio_comm_adp); // unused - taking ROM patch route

#endif


}

void hal_pon_gpio_comm_init(phal_pon_gpio_comm_adapter_t ppon_gpio_comm_adp)
{
	hal_rtl_pon_gpio_comm_init_patch(ppon_gpio_comm_adp);

	//hal_gpio_stubs.hal_pon_gpio_comm_init(ppon_gpio_comm_adp); // unused - going by patch route
}

/**
 *  @brief To de-initial the SYSON GPIO common resource.
 *           - Disable the SYSON GPIO hardware function.
 *
 *  @returns    void
 */
void hal_gpio_comm_deinit(void)
{

#if IS_CUT_TEST(CONFIG_CHIP_VER)
	hal_rtl_gpio_comm_deinit_patch();
#else

	hal_sys_peripheral_en(GPIO_SYS, DISABLE);
	hal_gpio_stubs.hal_gpio_comm_deinit();
#endif // #if IS_CUT_TEST(CONFIG_CHIP_VER)
}

void hal_aon_gpio_comm_deinit_via_NSC(void)
{
	hal_sys_peripheral_en(GPIO_AON, DISABLE);
	hal_gpio_stubs.hal_aon_gpio_comm_deinit();
}

/**
 *  @brief To de-initial the AON GPIO common resource.
 *           - Disable the AON GPIO hardware function.
 *
 *  @returns    void
 */
void hal_aon_gpio_comm_deinit(void)
{

#if IS_CUT_TEST(CONFIG_CHIP_VER)
	hal_rtl_aon_gpio_comm_deinit_patch();
#else

#if defined(CONFIG_BUILD_NONSECURE) && (CONFIG_BUILD_NONSECURE != 0)
	hal_aon_gpio_comm_deinit_nsc();
#else

	hal_sys_peripheral_en(GPIO_AON, DISABLE);
	hal_gpio_stubs.hal_aon_gpio_comm_deinit();
#endif

#endif // #if IS_CUT_TEST(CONFIG_CHIP_VER)
}

/**
 *  @brief To de-initial the PON GPIO common resource.
 *           - Disable the PON GPIO hardware function.
 *
 *  @returns    void
 */
void hal_pon_gpio_comm_deinit(void)
{

#if IS_CUT_TEST(CONFIG_CHIP_VER)
	hal_rtl_pon_gpio_comm_deinit_patch();
#else

	hal_sys_peripheral_en(GPIO_PON, DISABLE);
	hal_gpio_stubs.hal_pon_gpio_comm_deinit();
#endif // #if IS_CUT_TEST(CONFIG_CHIP_VER)
}

#if !IS_AFTER_CUT_A(CONFIG_CHIP_VER) // i.e. if test chip, this function will be used

hal_status_t hal_gpio_interrupt_clk_sel(gpio_type_t gpio_type, uint8_t clk_sel)
{
	return hal_rtl_gpio_interrupt_clk_sel_patch(gpio_type, clk_sel);
}
#endif

/**
 *  @brief Re-initials a GPIO pin. Excludes: Turning on respective GPIO group's clock/power; No pinmux registration.
 *           - Maintains H/W state of GPIO pins from previous init.
 *           - For Fast Camera Boot use only!
 *
 *  @param[in]  pgpio_adapter  The GPIO pin adapter.
 *  @param[in]  pin_name  The GPIO pin.
 *                - bit[7:5]: the GPIO port number. Each port has 32 GPIO pins.
 *                - bit[4:0]: the pin number of the GPIO port.
 *
 *  @return     None
 */

void hal_gpio_reinit(phal_gpio_adapter_t pgpio_adapter, uint32_t pin_name)
{

	DBG_GPIO_INFO("Executing hal_gpio_reinit\r\n");

	uint8_t port_idx = PIN_NAME_2_PORT(pin_name);
	uint8_t pin_idx = PIN_NAME_2_PIN(pin_name);
	uint32_t bit_mask;

	// Default to 0, which safe because if GPIO pin init fails, an early return via HAL_ERR_PARA would ensue.
	uint8_t port_array_idx = 0; // number indicator for array indices, e.g. pport_dp_sts[] based on port_idx

	// Default to 0; to store value of gpio_deb_using (struct member of respective GPIO comm adapters)
	uint32_t deb_idx_tally = 0;

	/* *** Test Chip ***
	 * Port A: GPIO IP Port0[5:0] // ***AON*** GPIO 6 pins - GPIOA0 - A5
	 * Port B: GPIO IP Port2[2:0] // SYSON GPIO 3 pins - GPIOB0 - B2
	 * Port C: GPIO IP Port2[8:3] // SYSON GPIO 6 pins - GPIOC0 - C5
	 * Port D: GPIO IP Port2[25:9] // SYSON GPIO 17 pins - GPIOD0 - D16
	 * Port E1: GPIO IP Port2[31:26] // SYSON GPIO 6 pins - GPIOE0 - E5
	 * Port E2: GPIO IP Port3[4:0] // SYSON GPIO 5 pins (overflow to Port 3 from Port 2) - GPIOE6 - E10
	 * Port F: GPIO IP Port1[17:0] // ***PON*** GPIO 18 pins - GPIOF0 - F17
	 * Port S: GPIO IP Port3[11:5] // SYSON GPIO 7 pins (overflow to Port 3 from Port 2) - GPIO

	 *** MP Chip ***
	 * Port A: GPIO IP Port0[5:0] // ***AON*** GPIO 6 pins - GPIOA0 - A5
	 * Port B: GPIO IP Port2[2:0] // SYSON GPIO 3 pins - GPIOB0 - B2
	 * Port C: GPIO IP Port2[8:3] // SYSON GPIO 6 pins - GPIOC0 - C5
	 * Port D: GPIO IP Port2[29:9] // SYSON GPIO 21 pins - GPIOD0 - D20
	 * Port E1: GPIO IP Port2[31:30] // SYSON GPIO 2 pins - GPIOE0 - E1
	 * Port E2: GPIO IP Port3[4:0] // SYSON GPIO 5 pins (overflow to Port 3 from Port 2) - GPIOE2 - E6
	 * Port F: GPIO IP Port1[17:0] // ***PON*** GPIO 18 pins - GPIOF0 - F17
	 * Port S: GPIO IP Port3[11:5] // SYSON GPIO 7 pins (overflow to Port 3 from Port 2) - GPIO
	 */

	switch (port_idx) {
	case PORT_A: // AON GPIO
		port_array_idx = 0;
		pin_idx += 0;
		break;
	case PORT_B:
		port_array_idx = 2; // for the sake of pport_odl/odh/odt/dmd arrays; Still at Port A (SYSON GPIO)
		pin_idx += 0;
		break;
	case PORT_C:
		port_array_idx = 2; // for the sake of pport_odl/odh/odt/dmd arrays; Still at Port A (SYSON GPIO)
		pin_idx += 3; // pin starts at 4th position, Pin 3 (Pin 0 is the 1st pin)
		break;
	case PORT_D:
		port_array_idx = 2; // for the sake of pport_odl/odh/odt/dmd arrays; Still at Port A (SYSON GPIO)
		pin_idx += 9; // pin starts at 10th position, Pin 9 (Pin 0 is the 1st pin)
		break;
	case PORT_E:
#if IS_CUT_TEST(CONFIG_CHIP_VER) // Test Chip
		if (pin_idx > 5) {
			port_array_idx = 3;
			pin_idx -= 6; // because pin_idx = 6 will be mapped to Group B[0], pin_idx = 7 mapped to Group B[1], etc
		} else { // means still at Port A [31:26]
			port_array_idx = 2;
			pin_idx += 26;
		}
#else // MP Chip
		if (pin_idx > 1) {
			port_array_idx = 3;
			pin_idx -= 2; // because pin_idx = 2 will be mapped to Group B[0], pin_idx = 3 mapped to Group B[1], etc
		} else { // means still at Port A [31:30]
			port_array_idx = 2;
			pin_idx += 30;
		}
#endif
		break;
	case PORT_F: // PON GPIO
		port_array_idx = 1;
		pin_idx += 0;
		break;
	case PORT_S: // SYSON GPIO Group B
		port_array_idx = 3;
		pin_idx += 5; // pin starts at 6th position, Pin 5 (Pin 0 is the 1st pin)
		break;
	}

	memset((void *) pgpio_adapter, 0, sizeof(hal_gpio_adapter_t));

	bit_mask = 1 << pin_idx;
	DBG_GPIO_INFO("bit_mask:%x\r\n", bit_mask);

	pgpio_adapter->pin_name = pin_name;
	pgpio_adapter->port_idx = port_array_idx;
	pgpio_adapter->pin_idx = pin_idx;
	pgpio_adapter->bit_mask = 1 << pin_idx;

	if (port_array_idx == 0) {

		pgpio_adapter->in_port = (uint32_t *)(&(AON_GPIO->GPIO_PORT_A_DP_STS));
		DBG_GPIO_INFO("in_port: %x\r\n", pgpio_adapter->in_port);

		pgpio_adapter->out0_port = (uint32_t *)(&(AON_GPIO->GPIO_PORT_A_ODL_EN));
		DBG_GPIO_INFO("out0_port: %x\r\n", pgpio_adapter->out0_port);

		pgpio_adapter->out1_port = (uint32_t *)(&(AON_GPIO->GPIO_PORT_A_ODH_EN));
		DBG_GPIO_INFO("out1_port: %x\r\n", pgpio_adapter->out1_port);

		pgpio_adapter->outt_port = (uint32_t *)(&(AON_GPIO->GPIO_PORT_A_ODT_EN));
		DBG_GPIO_INFO("outt_port: %x\r\n", pgpio_adapter->outt_port);

		deb_idx_tally = (*(hal_gpio_stubs.ppaon_gpio_comm_adp))->gpio_deb_using;
		DBG_GPIO_INFO("AON GPIO reinit deb_using: %x\r\n", (*(hal_gpio_stubs.ppaon_gpio_comm_adp))->gpio_deb_using);
		for (int i = 0; i < 6; i++) {
			if ((deb_idx_tally & (1 << i)) == 1) {
				pgpio_adapter->debounce_idx++;
			}
		}

	} else if (port_array_idx == 1) {

		pgpio_adapter->in_port = (uint32_t *)(&(PON_GPIO->GPIO_PORT_A_DP_STS));
		DBG_GPIO_INFO("in_port: %x\r\n", pgpio_adapter->in_port);

		pgpio_adapter->out0_port = (uint32_t *)(&(PON_GPIO->GPIO_PORT_A_ODL_EN));
		DBG_GPIO_INFO("out0_port: %x\r\n", pgpio_adapter->out0_port);

		pgpio_adapter->out1_port = (uint32_t *)(&(PON_GPIO->GPIO_PORT_A_ODH_EN));
		DBG_GPIO_INFO("out1_port: %x\r\n", pgpio_adapter->out1_port);

		pgpio_adapter->outt_port = (uint32_t *)(&(PON_GPIO->GPIO_PORT_A_ODT_EN));
		DBG_GPIO_INFO("outt_port: %x\r\n", pgpio_adapter->outt_port);

		deb_idx_tally = (*(hal_gpio_stubs.pppon_gpio_comm_adp))->gpio_deb_using;
		DBG_GPIO_INFO("PON GPIO reinit deb_using: %x\r\n", (*(hal_gpio_stubs.pppon_gpio_comm_adp))->gpio_deb_using);
		for (int i = 0; i < 16; i++) {
			if ((deb_idx_tally & (1 << i)) == 1) {
				pgpio_adapter->debounce_idx++;
			}
		}

	} else if (port_array_idx == 2) {

		pgpio_adapter->in_port = (uint32_t *)(&(SYSON_GPIO->GPIO_PORT_A_DP_STS));
		DBG_GPIO_INFO("in_port: %x\r\n", pgpio_adapter->in_port);

		pgpio_adapter->out0_port = (uint32_t *)(&(SYSON_GPIO->GPIO_PORT_A_ODL_EN));
		DBG_GPIO_INFO("out0_port: %x\r\n", pgpio_adapter->out0_port);

		pgpio_adapter->out1_port = (uint32_t *)(&(SYSON_GPIO->GPIO_PORT_A_ODH_EN));
		DBG_GPIO_INFO("out1_port: %x\r\n", pgpio_adapter->out1_port);

		pgpio_adapter->outt_port = (uint32_t *)(&(SYSON_GPIO->GPIO_PORT_A_ODT_EN));
		DBG_GPIO_INFO("outt_port: %x\r\n", pgpio_adapter->outt_port);

	} else { // port_array_idx == 3

		pgpio_adapter->in_port = (uint32_t *)(&(SYSON_GPIO->GPIO_PORT_B_DP_STS));
		DBG_GPIO_INFO("in_port: %x\r\n", pgpio_adapter->in_port);

		pgpio_adapter->out0_port = (uint32_t *)(&(SYSON_GPIO->GPIO_PORT_B_ODL_EN));
		DBG_GPIO_INFO("out0_port: %x\r\n", pgpio_adapter->out0_port);

		pgpio_adapter->out1_port = (uint32_t *)(&(SYSON_GPIO->GPIO_PORT_B_ODH_EN));
		DBG_GPIO_INFO("out1_port: %x\r\n", pgpio_adapter->out1_port);

		pgpio_adapter->outt_port = (uint32_t *)(&(SYSON_GPIO->GPIO_PORT_B_ODT_EN));
		DBG_GPIO_INFO("outt_port: %x\r\n", pgpio_adapter->outt_port);
	}

	if (port_array_idx == 2 || port_array_idx == 3) {
		deb_idx_tally = (*(hal_gpio_stubs.ppgpio_comm_adp))->gpio_deb_using;
		DBG_GPIO_INFO("SYSON GPIO reinit deb_using: %x\r\n", (*(hal_gpio_stubs.ppgpio_comm_adp))->gpio_deb_using);
		for (int i = 0; i < 16; i++) {
			if ((deb_idx_tally & (1 << i)) == 1) {
				pgpio_adapter->debounce_idx++;
			}
		}
	}

}

/**
 *  @brief Initials a GPIO pin.
 *           - Defult configure the GPIO pin as a normal input pin (not an interrupt pin).
 *
 *  @param[in]  pgpio_adapter  The GPIO pin adapter.
 *  @param[in]  pin_name  The GPIO pin.
 *                - bit[7:5]: the GPIO port number. Each port has 32 GPIO pins.
 *                - bit[4:0]: the pin number of the GPIO port.
 *
 *  @return     HAL_ERR_PARA:  Input arguments are invalid.
 *  @return     HAL_OK:  GPIO pin initialization OK.
 */
hal_status_t hal_gpio_init(phal_gpio_adapter_t pgpio_adapter, uint32_t pin_name)
{

	hal_status_t ret;
	uint8_t port_idx = PIN_NAME_2_PORT(pin_name);

#if defined (CONFIG_BUILD_NONSECURE) && (CONFIG_BUILD_NONSECURE != 0)

#if IS_CUT_TEST(CONFIG_CHIP_VER) // Test Chip
	ret = hal_pinmux_register(pin_name, PID_GPIO);
	if (ret != HAL_OK) {
		return ret;
	} else {
		// pinmux_register is successful; proceed to turn on LDO SDIO to give GPIO S pad power - for test chip
		if (port_idx == PORT_S) {
			hal_sys_peripheral_en(LDO_SDIO_3V3_EN, ENABLE);
		}

		return hal_rtl_gpio_init_patch(pgpio_adapter, pin_name);
	}
#else // MP Chip A-cut

	if (port_idx == PORT_A) {
		// AON GPIO
		return hal_gpio_init_nsc(pgpio_adapter, pin_name);

	} else {

		if (port_idx == PORT_B || port_idx == PORT_C || port_idx == PORT_D || port_idx == PORT_E || port_idx == PORT_S) {
			// SYSON GPIO
			hal_sys_peripheral_en(GPIO_SYS, ENABLE);
#if (!defined (CONFIG_BUILD_NONSECURE)) || (CONFIG_BUILD_NONSECURE == 0)
			pgpio_adapter->s_ram_gpio_on = 1;
#endif

		} else if (port_idx == PORT_F) {
			// PON GPIO
			hal_sys_peripheral_en(GPIO_PON, ENABLE);
#if (!defined (CONFIG_BUILD_NONSECURE)) || (CONFIG_BUILD_NONSECURE == 0)
			pgpio_adapter->s_ram_pon_gpio_on = 1;
#endif
		}

		ret = hal_pinmux_register(pin_name, PID_GPIO);
		if (ret != HAL_OK) {
			return ret;
		}

		// pinmux_register is successful; proceed to turn on LDO SDIO to give GPIO S pad power - for test chip // I think applies to all, not only test chip
		if (port_idx == PORT_S) {
			hal_sys_peripheral_en(LDO_SDIO_3V3_EN, ENABLE);
		}

		return hal_gpio_stubs.hal_gpio_init(pgpio_adapter, pin_name);
	}

#endif

#else // #if defined (CONFIG_BUILD_NONSECURE) && (CONFIG_BUILD_NONSECURE != 0)

#if IS_CUT_TEST(CONFIG_CHIP_VER) // Test Chip
	ret = hal_pinmux_register(pin_name, PID_GPIO);
	if (ret != HAL_OK) {
		return ret;
	} else {
		// pinmux_register is successful; proceed to turn on LDO SDIO to give GPIO S pad power - for test chip
		if (port_idx == PORT_S) {
			hal_sys_peripheral_en(LDO_SDIO_3V3_EN, ENABLE);
		}

		return hal_rtl_gpio_init_patch(pgpio_adapter, pin_name);
	}
#else // MP Chip A-cut

	if (port_idx == PORT_A) {
		// AON GPIO
		hal_sys_peripheral_en(GPIO_AON, ENABLE);
#if (!defined (CONFIG_BUILD_NONSECURE)) || (CONFIG_BUILD_NONSECURE == 0)
		pgpio_adapter->s_ram_aon_gpio_on = 1;
#endif

	} else if (port_idx == PORT_B || port_idx == PORT_C || port_idx == PORT_D || port_idx == PORT_E || port_idx == PORT_S) {
		// SYSON GPIO
		hal_sys_peripheral_en(GPIO_SYS, ENABLE);
#if (!defined (CONFIG_BUILD_NONSECURE)) || (CONFIG_BUILD_NONSECURE == 0)
		pgpio_adapter->s_ram_gpio_on = 1;
#endif

	} else if (port_idx == PORT_F) {
		// PON GPIO
		hal_sys_peripheral_en(GPIO_PON, ENABLE);
#if (!defined (CONFIG_BUILD_NONSECURE)) || (CONFIG_BUILD_NONSECURE == 0)
		pgpio_adapter->s_ram_pon_gpio_on = 1;
#endif
	}

	ret = hal_pinmux_register(pin_name, PID_GPIO);
	if (ret != HAL_OK) {
		return ret;
	}

	// pinmux_register is successful; proceed to turn on LDO SDIO to give GPIO S pad power - for test chip
	if (port_idx == PORT_S) {
		hal_sys_peripheral_en(LDO_SDIO_3V3_EN, ENABLE);
	}

	return hal_gpio_stubs.hal_gpio_init(pgpio_adapter, pin_name);

#endif

#endif
}

/**
 *  @brief To de-initial a GPIO pin.
 *
 *  @param[in]  pgpio_adapter  The GPIO pin adapter.
 *
 *  @returns    void
 */
void hal_gpio_deinit(phal_gpio_adapter_t pgpio_adapter)
{
	uint8_t port_idx = PIN_NAME_2_PORT(pgpio_adapter->pin_name);

#if defined(CONFIG_BUILD_NONSECURE) && (CONFIG_BUILD_NONSECURE != 0)
	if (port_idx == PORT_A) {
		// AON GPIO
		hal_gpio_deinit_nsc(pgpio_adapter);

	} else {
		// For GPIO S, when it is deinit-ed, turn off LDO SDIO too
		if (port_idx == PORT_S) {
			hal_sys_peripheral_en(LDO_SDIO_3V3_EN, DISABLE);
		}

		hal_pinmux_unregister(pgpio_adapter->pin_name, PID_GPIO);
		hal_gpio_stubs.hal_gpio_deinit(pgpio_adapter);
	}
#else
	// For GPIO S, when it is deinit-ed, turn off LDO SDIO too
	if (port_idx == PORT_S) {
		hal_sys_peripheral_en(LDO_SDIO_3V3_EN, DISABLE);
	}

	hal_pinmux_unregister(pgpio_adapter->pin_name, PID_GPIO);
	hal_gpio_stubs.hal_gpio_deinit(pgpio_adapter);
#endif

}


/**
 *  @brief To select the clock source for AON GPIO SCLK.
 *
 *  @param[in]  sclk_src_sel  The selector to choose the clock source for AON GPIO SCLK.
 *
 *  @returns    void
 */
void aon_gpio_sclk_source_select(uint32_t sclk_src_sel)
{

#if defined(CONFIG_BUILD_NONSECURE) && (CONFIG_BUILD_NONSECURE != 0)

	aon_gpio_sclk_source_select_nsc(sclk_src_sel);
#else

	AON_TypeDef *aon = AON;
	uint32_t val;

	if (sclk_src_sel) {
		if (sclk_src_sel > 1) {
			DBG_GPIO_WARN("sclk_src_sel is greater than 1! Using the case where sclk_src_sel == 1\r\n");
		}
		DBG_GPIO_INFO("AON LP 32K clock source\r\n");
		val = aon->AON_REG_AON_SRC_CLK_CTRL;
		val |= AON_BIT_GPIO_SCLK_SEL;
		aon->AON_REG_AON_SRC_CLK_CTRL = val;
	} else {
		DBG_GPIO_INFO("OSC 128K/4 (without SDM?)\r\n");
		val = aon->AON_REG_AON_SRC_CLK_CTRL;
		val &= ~AON_BIT_GPIO_SCLK_SEL;
		aon->AON_REG_AON_SRC_CLK_CTRL = val;
	}
#endif
}

/**
 *  @brief Initials a GPIO IRQ pin.
 *
 *  @param[in]  pgpio_irq_adapter  The GPIO IRQ pin adapter.
 *  @param[in]  pin_name  The GPIO IRQ pin.
 *                - bit[7:5]: the GPIO port number. Each port has 32 GPIO pins.
 *                - bit[4:0]: the pin number of the GPIO port.
 *  @param[in]  callback  The GPIO IRQ call back function.
 *  @param[in]  arg  The argument of the GPIO IRQ call back function. It is an application
 *                   priviate data to be passed by the call back function.
 *
 *  @return     HAL_NOT_READY:  The GPIO group adapter does not been initialed yet.
 *  @return     HAL_ERR_PARA:  Input arguments are invalid.
 *  @return     HAL_NO_RESOURCE: No GPIO IRQ resource (circuit). The GPIO IRQ resource is limited,
 *                               not all GPIO pin can has GPIO IRQ function.
 *  @return     HAL_OK: GPIO IRQ pin initialization OK.
 */
hal_status_t hal_gpio_irq_init(phal_gpio_irq_adapter_t pgpio_irq_adapter, uint32_t pin_name,
							   gpio_irq_callback_t callback, uint32_t arg)
{
	hal_status_t ret;
	uint8_t port_idx = PIN_NAME_2_PORT(pin_name);

#if defined(CONFIG_BUILD_NONSECURE) && (CONFIG_BUILD_NONSECURE != 0)
	if (port_idx == PORT_A) {
		// AON GPIO
		return hal_gpio_irq_init_nsc(pgpio_irq_adapter, pin_name, callback, arg);

	} else {
		if (port_idx == PORT_B || port_idx == PORT_C || port_idx == PORT_D || port_idx == PORT_E || port_idx == PORT_S) {
			// SYSON GPIO
			hal_sys_peripheral_en(GPIO_SYS, ENABLE);

		} else if (port_idx == PORT_F) { // if compiler complain, switch to else
			// PON GPIO
			hal_sys_peripheral_en(GPIO_PON, ENABLE);
		}

		ret = hal_pinmux_register(pin_name, PID_GPIO);
		if (ret != HAL_OK) {
			DBG_GPIO_ERR("If pin has been registered under GPIO pin init, deinit GPIO pin before reinitializing as GPIO pin.\r\n");
			return ret;
		}

		// pinmux_register is successful; proceed to turn on LDO SDIO to give GPIO S pad power - for test chip // I think applies to all, not only test chip
		if (port_idx == PORT_S) {
			hal_sys_peripheral_en(LDO_SDIO_3V3_EN, ENABLE);
		}

#if IS_CUT_TEST(CONFIG_CHIP_VER)
		return hal_rtl_gpio_irq_init_patch(pgpio_irq_adapter, pin_name, callback, arg);
#else
		return hal_gpio_stubs.hal_gpio_irq_init(pgpio_irq_adapter, pin_name, callback, arg);
#endif
	}

#else // $if defined(CONFIG_BUILD_NONSECURE) && (CONFIG_BUILD_NONSECURE != 0)
	if (port_idx == PORT_A) {
		// AON GPIO
		hal_sys_peripheral_en(GPIO_AON, ENABLE);

	} else  if (port_idx == PORT_B || port_idx == PORT_C || port_idx == PORT_D || port_idx == PORT_E || port_idx == PORT_S) {
		// SYSON GPIO
		hal_sys_peripheral_en(GPIO_SYS, ENABLE);

	} else if (port_idx == PORT_F) { // if compiler complain, switch to else
		// PON GPIO
		hal_sys_peripheral_en(GPIO_PON, ENABLE);
	}

	ret = hal_pinmux_register(pin_name, PID_GPIO);
	if (ret != HAL_OK) {
		DBG_GPIO_ERR("If pin has been registered under GPIO pin init, deinit GPIO pin before reinitializing as GPIO pin.\r\n");
		return ret;
	}

	// pinmux_register is successful; proceed to turn on LDO SDIO to give GPIO S pad power - for test chip // I think applies to all, not only test chip
	if (port_idx == PORT_S) {
		hal_sys_peripheral_en(LDO_SDIO_3V3_EN, ENABLE);
	}

#if IS_CUT_TEST(CONFIG_CHIP_VER)
	return hal_rtl_gpio_irq_init_patch(pgpio_irq_adapter, pin_name, callback, arg);
#else
	return hal_gpio_stubs.hal_gpio_irq_init(pgpio_irq_adapter, pin_name, callback, arg);
#endif

#endif  // $if defined(CONFIG_BUILD_NONSECURE) && (CONFIG_BUILD_NONSECURE != 0)
}

/**
 *  @brief To de-initial and disable a GPIO IRQ pin.
 *
 *  @param[in]  pgpio_irq_adapter  The GPIO IRQ pin adapter.
 *
 *  @returns    void
 */
void hal_gpio_irq_deinit(phal_gpio_irq_adapter_t pgpio_irq_adapter)
{
	uint8_t port_idx = PIN_NAME_2_PORT(pgpio_irq_adapter->pin_name);

#if defined(CONFIG_BUILD_NONSECURE) && (CONFIG_BUILD_NONSECURE != 0)
	if (port_idx == PORT_A) {
		hal_gpio_irq_deinit_nsc(pgpio_irq_adapter);

	} else {

		// For GPIO S, when it is deinit-ed, turn off LDO SDIO too
		if (port_idx == PORT_S) {
			hal_sys_peripheral_en(LDO_SDIO_3V3_EN, DISABLE);
		}

		hal_pinmux_unregister(pgpio_irq_adapter->pin_name, PID_GPIO);
	}

#if IS_CUT_TEST(CONFIG_CHIP_VER)
	return hal_rtl_gpio_irq_deinit_patch(pgpio_irq_adapter);
#else
	hal_gpio_stubs.hal_gpio_irq_deinit(pgpio_irq_adapter);
#endif

#else // #if defined(CONFIG_BUILD_NONSECURE)

	// For GPIO S, when it is deinit-ed, turn off LDO SDIO too
	if (port_idx == PORT_S) {
		hal_sys_peripheral_en(LDO_SDIO_3V3_EN, DISABLE);
	}

	hal_pinmux_unregister(pgpio_irq_adapter->pin_name, PID_GPIO);

#if IS_CUT_TEST(CONFIG_CHIP_VER)
	return hal_rtl_gpio_irq_deinit_patch(pgpio_irq_adapter);
#else
	hal_gpio_stubs.hal_gpio_irq_deinit(pgpio_irq_adapter);
#endif

#endif // #if defined(CONFIG_BUILD_NONSECURE) && (CONFIG_BUILD_NONSECURE != 0)
}

/**
 *  @brief Initials a GPIO port. A GPIO port has 32 GPIO pins. However, may not all
 *         GPIO pin will be bound out. Checks the IC package to know what pins are
 *         available on this GPIO port.
 *
 *  @param[in]  pgpio_port_adapter  The GPIO port adapter.
 *  @param[in]  port_idx The GPIO port index.
 *                - 0: Port A
 *                - 1: Port B
 *                - 2: Port C
 *                - 3: Port D
 *                - 4: Port E1
 *                - 5: Port E2
 *                - 6: Port F
 *                - 7: Port S
 *  @param[in]  mask  The GPIO pin mask to indicate what pin are included in this port.
 *                    Bit 0 maps to pin 0; bit 1 maps to pin 1; ... etc. The bit value 1
 *                    means the maped pin is included in this GPIO port.
 *  @param[in]  dir  The GPIO port direction, IN or OUT.
 *
 *  @return     HAL_ERR_PARA:  Input arguments are invalid.
 *  @return     HAL_OK:  GPIO port initialization OK.
 */
hal_status_t hal_gpio_port_init(phal_gpio_port_adapter_t pgpio_port_adapter, uint32_t port_idx,
								uint32_t mask, gpio_dir_t dir)
{
	io_pin_t pin_list[MAX_PIN_IN_PORT + 1];
	hal_status_t ret;
	gpio_pin_t pin;
	uint32_t i;
	uint32_t j;

	j = 0;

	// First check the port_idx
	if (port_idx > (PORT_MAX_NUM - 1)) {
		DBG_GPIO_ERR("port_idx: %d is invalid\r\n", port_idx);
		return HAL_ERR_PARA;
	}

	// Then check the mask; its value cannot exceed the number of pins of the respective GPIO ports

	if (port_idx == PORT_A) {
		if (mask > 0x3F) {
			DBG_GPIO_ERR("GPIO Port A mask: 0x%x is invalid\r\n", mask);
			return HAL_ERR_PARA;
		}
	} else if (port_idx == PORT_B) {
		if (mask > 0x7) {
			DBG_GPIO_ERR("GPIO Port B mask: 0x%x is invalid\r\n", mask);
			return HAL_ERR_PARA;
		}
	} else if (port_idx == PORT_C) {
		if (mask > 0x3F) {
			DBG_GPIO_ERR("GPIO Port C mask: 0x%x is invalid\r\n", mask);
			return HAL_ERR_PARA;
		}
	} else if (port_idx == PORT_D) {
#if !IS_CUT_TEST(CONFIG_CHIP_VER) // MP Chip
		if (mask > 0x1FFFFF) {
#else // Test Chip
		if (mask > 0x1FFFF) {
#endif
			DBG_GPIO_ERR("GPIO Port D mask: 0x%x is invalid\r\n", mask);
			return HAL_ERR_PARA;
		}
	} else if (port_idx == PORT_E) {
#if !IS_CUT_TEST(CONFIG_CHIP_VER) // MP Chip
		if (mask > 0x7F) {
#else // Test Chip
		if (mask > 0x7FF) {
#endif
			DBG_GPIO_ERR("GPIO Port E mask: 0x%x is invalid\r\n", mask);
			return HAL_ERR_PARA;
		}
	} else if (port_idx == PORT_F) {
#if !IS_CUT_TEST(CONFIG_CHIP_VER) // MP Chip
		if (mask > 0x3FFE7) {
#else // Test Chip
		if (mask > 0x3FFCF) {
#endif
			DBG_GPIO_ERR("GPIO Port F mask: 0x%x is invalid\r\n", mask);
			return HAL_ERR_PARA;
		}
	} else if (port_idx == PORT_S) {
		if (mask > 0x7F) {
			DBG_GPIO_ERR("GPIO Port S mask: 0x%x is invalid\r\n", mask);
			return HAL_ERR_PARA;
		}
	}

#if defined(CONFIG_BUILD_NONSECURE) && (CONFIG_BUILD_NONSECURE != 0)
	if (port_idx == PORT_A) { // AON GPIO (Port A)
		return hal_gpio_port_init_nsc(pgpio_port_adapter, port_idx, mask, dir);

	} else {

		if (port_idx == PORT_F) { // PON GPIO (Port F)
			hal_sys_peripheral_en(GPIO_PON, ENABLE);

		} else { // SYSON GPIO
			hal_sys_peripheral_en(GPIO_SYS, ENABLE);
		}

		pin.pin_name_b.port = port_idx;

		DBG_GPIO_INFO("port_idx in **RAM**:%d\r\n", pin.pin_name_b.port);

		for (i = 0; i < MAX_PIN_IN_PORT; i++) {
			if (mask & (1 << i)) {
				pin.pin_name_b.pin = i;
				pin_list[j].pin_name = pin.pin_name;
				ret = hal_pinmux_register(pin_list[j].pin_name, PID_GPIO);
				if (ret != HAL_OK) {
					return ret;
				}
				j++;
			}
		}

		if (port_idx == PORT_F || port_idx == PORT_S) {
#if IS_CUT_TEST(CONFIG_CHIP_VER) // Test Chip - Use patch
			return hal_rtl_gpio_port_init_patch(pgpio_port_adapter, port_idx + 1, mask, dir);
#else // MP Chip

			// pinmux_register is successful; proceed to turn on LDO SDIO to give GPIO S pad power - for test chip
			if (port_idx == PORT_S) {
				hal_sys_peripheral_en(LDO_SDIO_3V3_EN, ENABLE);
			}
			return hal_gpio_stubs.hal_gpio_port_init(pgpio_port_adapter, port_idx + 1, mask, dir);
#endif
		} else {
#if IS_CUT_TEST(CONFIG_CHIP_VER) // Test Chip - Use patch
			return hal_rtl_gpio_port_init_patch(pgpio_port_adapter, port_idx, mask, dir);
#else // MP Chip
			return hal_gpio_stubs.hal_gpio_port_init(pgpio_port_adapter, port_idx, mask, dir);
#endif
		}
	}

#else // #if defined(CONFIG_BUILD_NONSECURE) && (CONFIG_BUILD_NONSECURE != 0)
	if (port_idx == PORT_A) { // AON GPIO (Port A)
		hal_sys_peripheral_en(GPIO_AON, ENABLE);

	} else if (port_idx == PORT_F) { // PON GPIO (Port F)
		hal_sys_peripheral_en(GPIO_PON, ENABLE);

	} else { // SYSON GPIO
		hal_sys_peripheral_en(GPIO_SYS, ENABLE);
	}

	pin.pin_name_b.port = port_idx;

	DBG_GPIO_INFO("port_idx in **RAM**:%d\r\n", pin.pin_name_b.port);

	for (i = 0; i < MAX_PIN_IN_PORT; i++) {
		if (mask & (1 << i)) {
			pin.pin_name_b.pin = i;
			pin_list[j].pin_name = pin.pin_name;
			ret = hal_pinmux_register(pin_list[j].pin_name, PID_GPIO);
			if (ret != HAL_OK) {
				return ret;
			}
			j++;
		}
	}

	if (port_idx == PORT_F || port_idx == PORT_S) {
#if IS_CUT_TEST(CONFIG_CHIP_VER) // Test Chip - Use patch
		return hal_rtl_gpio_port_init_patch(pgpio_port_adapter, port_idx + 1, mask, dir);
#else // MP Chip

		// pinmux_register is successful; proceed to turn on LDO SDIO to give GPIO S pad power - for test chip
		if (port_idx == PORT_S) {
			hal_sys_peripheral_en(LDO_SDIO_3V3_EN, ENABLE);
		}
		return hal_gpio_stubs.hal_gpio_port_init(pgpio_port_adapter, port_idx + 1, mask, dir);
#endif
	} else {
#if IS_CUT_TEST(CONFIG_CHIP_VER) // Test Chip - Use patch
		return hal_rtl_gpio_port_init_patch(pgpio_port_adapter, port_idx, mask, dir);
#else // MP Chip
		return hal_gpio_stubs.hal_gpio_port_init(pgpio_port_adapter, port_idx, mask, dir);
#endif
	}
#endif // #if defined(CONFIG_BUILD_NONSECURE) && (CONFIG_BUILD_NONSECURE != 0)
}

/**
 *  @brief To de-initial a GPIO port. All pins in this GPIO port will be switched
 *         as input pin.
 *
 *  @param[in]  pgpio_port_adapter The GPIO port adapter.
 *
 *  @returns    void
 */

void hal_gpio_port_deinit(phal_gpio_port_adapter_t pgpio_port_adapter)
{
	io_pin_t pin_list[MAX_PIN_IN_PORT + 1];
	gpio_pin_t pin;
	uint32_t i;
	uint32_t j;
	uint32_t mask = 0;
	j = 0;

	pin.pin_name = hal_gpio_ip_pin_to_chip_pin(pgpio_port_adapter->port_idx, pgpio_port_adapter->pin_offset);
	DBG_GPIO_INFO("pin.pin_name deinit: %x\r\n", pin.pin_name);
	DBG_GPIO_INFO("port_idx deinit: %x\r\n", pgpio_port_adapter->port_idx);
	DBG_GPIO_INFO("pin_offset deinit: %x\r\n", pgpio_port_adapter->pin_offset);

	mask = pgpio_port_adapter->pin_mask;
	DBG_GPIO_INFO("mask: %x\r\n", mask);

	for (i = 0; i < MAX_PIN_IN_PORT; i++) {
		if (mask & (1 << i)) {
			pin.pin_name_b.pin = i;
			pin_list[j].pin_name = pin.pin_name;
			hal_pinmux_unregister(pin_list[j].pin_name, PID_GPIO);
			j++;
		}
	}

#if defined(CONFIG_BUILD_NONSECURE) && (CONFIG_BUILD_NONSECURE != 0)
	if (pgpio_port_adapter->port_idx == PORT_A) {
		hal_gpio_port_deinit_nsc(pgpio_port_adapter);

	} else {
#if IS_CUT_TEST(CONFIG_CHIP_VER) // Test chip
		hal_rtl_gpio_port_deinit_patch(pgpio_port_adapter);
#else // MP Chip

		// For GPIO S, when it is deinit-ed, turn off LDO SDIO too
		if (pin.pin_name_b.port == PORT_S) {
			hal_sys_peripheral_en(LDO_SDIO_3V3_EN, DISABLE);
		}

		hal_gpio_stubs.hal_gpio_port_deinit(pgpio_port_adapter);
#endif
	}

#else // #if defined(CONFIG_BUILD_NONSECURE) && (CONFIG_BUILD_NONSECURE != 0)

#if IS_CUT_TEST(CONFIG_CHIP_VER) // Test chip
	hal_rtl_gpio_port_deinit_patch(pgpio_port_adapter);
#else // MP Chip

	// For GPIO S, when it is deinit-ed, turn off LDO SDIO too
	if (pin.pin_name_b.port == PORT_S) {
		hal_sys_peripheral_en(LDO_SDIO_3V3_EN, DISABLE);
	}

	hal_gpio_stubs.hal_gpio_port_deinit(pgpio_port_adapter);
#endif
#endif // #if defined(CONFIG_BUILD_NONSECURE) && (CONFIG_BUILD_NONSECURE != 0)

}

/**
 *  @brief To set the direction of the given GPIO port.
 *
 *  @param[in]  pgpio_port_adapter The GPIO port adapter.
 *  @param[in]  dir  The GPIO port direction, IN or OUT.
 *                     -0: input.
 *                     -1: output.
 *
 *  @returns    void
 */
#if !IS_CUT_TEST(CONFIG_CHIP_VER) // MP chip
void hal_gpio_port_dir(phal_gpio_port_adapter_t pgpio_port_adapter, gpio_dir_t dir)
{
#if defined(CONFIG_BUILD_NONSECURE) && (CONFIG_BUILD_NONSECURE != 0)

	if (pgpio_port_adapter->port_idx == PORT_A) {
		hal_gpio_port_dir_nsc(pgpio_port_adapter, dir);
	} else {
		hal_gpio_stubs.hal_gpio_port_dir(pgpio_port_adapter, dir);
	}
#else

	hal_gpio_stubs.hal_gpio_port_dir(pgpio_port_adapter, dir);
#endif

}
#else // Test chip
void hal_gpio_port_dir(phal_gpio_port_adapter_t pgpio_port_adapter, uint32_t mask, gpio_dir_t dir)
{
	hal_rtl_gpio_port_dir_patch(pgpio_port_adapter, mask, dir);
}
#endif


hal_status_t hal_aon_gpio_irq_debounce_enable(phal_gpio_irq_adapter_t pgpio_irq_adapter,
		uint32_t debounce_us)
{
	return hal_rtl_gpio_irq_debounce_enable_patch(pgpio_irq_adapter, debounce_us);
}

hal_status_t hal_aon_gpio_debounce_enable(phal_gpio_adapter_t pgpio_adapter, uint32_t debounce_us)
{
	return hal_rtl_gpio_debounce_enable_patch(pgpio_adapter, debounce_us);
}

/**
 *  @brief Enables the debounce function of the given GPIO IRQ pin.
 *         The debounce resource(circuit) is limited, not all GPIO pin
 *         can has debounce function.
 *
 *  @param[in]  pgpio_irq_adapter  The GPIO IRQ pin adapter.
 *  @param[in]  debounce_us  The time filter for the debounce, in micro-second.
 *                           But the time resolution is 31.25us (1/32K) and the
 *                           maximum time is 512 ms.
 *
 *  @return     HAL_NO_RESOURCE:  No debounce resource. (All debounce circuit are allocated).
 *  @return     HAL_OK:  Debounce function is enabled on this GPIO.
 */

// Special note: All cuts of chip, Test/A/B/C/D and beyond will always use this HAL RAM function.
// This also means that for GPIO IRQ Debounce Enable, we will call the RAM patch forever.
// The affected ROM function is hal_rtl_gpio_irq_debounce().
// For AON GPIO, the function that the NSC will call is stated right above.

hal_status_t hal_gpio_irq_debounce_enable(phal_gpio_irq_adapter_t pgpio_irq_adapter,
		uint32_t debounce_us)
{

#if defined(CONFIG_BUILD_NONSECURE)

	uint8_t port_idx = PIN_NAME_2_PORT(pgpio_irq_adapter->pin_name);

	if (port_idx == PORT_A) {
		return hal_gpio_irq_debounce_enable_nsc(pgpio_irq_adapter, debounce_us);
	} else {

		return hal_rtl_gpio_irq_debounce_enable_patch(pgpio_irq_adapter, debounce_us);
	}

#else
	return hal_rtl_gpio_irq_debounce_enable_patch(pgpio_irq_adapter, debounce_us);

#endif

}

/**
 *  @brief Enable the debounce function for the given GPIO pin.
 *         The debounce resource(circuit) is limited, not all GPIO pin
 *         can has debounce function.
 *
 *  @param[in]  pgpio_adapter  The GPIO pin adapter.
 *  @param[in]  debounce_us  The time filter for the debounce, in micro-second.
 *                           But the time resolution is 31.25us (1/32K) and the
 *                           maximum time is 512 ms.
 *
 *  @return     HAL_NO_RESOURCE:  No debounce resource. (All debounce circuit are allocated).
 *  @return     HAL_ERR_PARA:  Input arguments are invlaid.
 *  @return     HAL_OK:  Debounce function is enabled on this GPIO.
 */

hal_status_t hal_gpio_debounce_enable(phal_gpio_adapter_t pgpio_adapter, uint32_t debounce_us)
{
#if defined(CONFIG_BUILD_NONSECURE)
	if (pgpio_adapter->port_idx == PORT_A) {
		return hal_gpio_debounce_enable_nsc(pgpio_adapter, debounce_us);
	} else {
		return hal_rtl_gpio_debounce_enable_patch(pgpio_adapter, debounce_us);
	}
#else
	return hal_rtl_gpio_debounce_enable_patch(pgpio_adapter, debounce_us);
#endif
}

// For Test chip patching only

#if IS_CUT_TEST(CONFIG_CHIP_VER)
void hal_gpio_irq_disable(phal_gpio_irq_adapter_t pgpio_irq_adapter)
{
	hal_rtl_gpio_irq_disable_patch(pgpio_irq_adapter);
}

// This function has been moved above (out of section within #IS_CUT_TEST(CONFIG_CHIP_VER))
/*hal_status_t hal_gpio_debounce_enable(phal_gpio_adapter_t pgpio_adapter, uint32_t debounce_us)
{
    return hal_rtl_gpio_debounce_enable_patch(pgpio_adapter, debounce_us);
}*/

void hal_gpio_debounce_disable(phal_gpio_adapter_t pgpio_adapter)
{
	hal_rtl_gpio_debounce_disable_patch(pgpio_adapter);
}

// This function has been moved above (out of section within #IS_CUT_TEST(CONFIG_CHIP_VER))
/*hal_status_t hal_gpio_irq_debounce_enable(phal_gpio_irq_adapter_t pgpio_irq_adapter,
        uint32_t debounce_us)
{
    return hal_rtl_gpio_irq_debounce_enable_patch(pgpio_irq_adapter, debounce_us);
}*/

void hal_gpio_irq_debounce_disable(phal_gpio_irq_adapter_t pgpio_irq_adapter)
{
	hal_rtl_gpio_irq_debounce_disable_patch(pgpio_irq_adapter);
}

uint32_t hal_gpio_port_read(phal_gpio_port_adapter_t pgpio_port_adapter, uint32_t mask)
{
	return hal_rtl_gpio_port_read_patch(pgpio_port_adapter, mask);
}

#endif

/**
 *  @brief Coverts an IP pin to a chip pin name.
 *
 *  @param[in]  port_idx The port index of the IP pin.
 *  @param[in]  pin_idx The pin index of the IP pin.
 *
 *  @returns    The converted chip pin name.
 */
uint8_t hal_gpio_ip_pin_to_chip_pin(uint32_t port_idx, uint32_t pin_idx)
{
	uint8_t chip_port = 0;
	uint8_t chip_pin = 0;

	DBG_GPIO_INFO("ip2chip: port_idx: %x\r\n", port_idx);
	DBG_GPIO_INFO("ip2chip: pin_idx: %x\r\n", pin_idx);

	// convert chip pin definition to IP pin definition - Test Chip
	// Port A: GPIO IP Port0[5:0] // ***AON*** GPIO 6 pins
	// Port B: GPIO IP Port2[2:0] // SYSON GPIO 3 pins
	// Port C: GPIO IP Port2[8:3] // SYSON GPIO 6 pins
	// Port D: GPIO IP Port2[25:9] // SYSON GPIO 17 pins
	// Port E1: GPIO IP Port2[31:26] // SYSON GPIO 6 pins
	// Port E2: GPIO IP Port3[4:0] // SYSON GPIO 5 pins (overflow to Group B GPIO)
	// Port F: GPIO IP Port1[17:0] // ***PON*** GPIO 18 pins
	// Port S: GPIO IP Port3[11:5] // SYSON GPIO 7 pins (overflow to Group B GPIO)

	// convert chip pin definition to IP pin definition - MP Chip
	// Port A: GPIO IP Port0[5:0] // ***AON*** GPIO 6 pins
	// Port B: GPIO IP Port2[2:0] // SYSON GPIO 3 pins
	// Port C: GPIO IP Port2[8:3] // SYSON GPIO 6 pins
	// Port D: GPIO IP Port2[29:9] // SYSON GPIO 21 pins
	// Port E1: GPIO IP Port2[31:30] // SYSON GPIO 2 pins
	// Port E2: GPIO IP Port3[4:0] // SYSON GPIO 5 pins (overflow to Group B GPIO)
	// Port F: GPIO IP Port1[17:0] // ***PON*** GPIO 18 pins
	// Port S: GPIO IP Port3[11:5] // SYSON GPIO 7 pins (overflow to Group B GPIO)

	if (port_idx == 0) { // Port A (GPIO IP, AON GPIO)
		DBG_GPIO_INFO("chip2pin A\r\n");
		chip_port = 0;
		chip_pin = pin_idx;

	} else if (port_idx == 1) { // Port F (GPIO IP; PON GPIO)
		DBG_GPIO_INFO("chip2pin F\r\n");
		chip_port = 5;
		chip_pin = pin_idx;
	} else if (port_idx == 2) { // Port B, C, D, E, S
		if (pin_idx < 3) { // PORT_B will be from [0,2] in terms of pin_idx
			DBG_GPIO_INFO("chip2pin B\r\n");
			chip_port = 1; // "PORT_B" in pin_name.h
			chip_pin = pin_idx; // because IP pin number range will be [2:0], '0' corresponds to PIN_NAME(PORT_B, 0)
		} else if (pin_idx == 3) {  // "PORT_C" in pin_name.h
			DBG_GPIO_INFO("chip2pin C\r\n");
			chip_port = 2;
			chip_pin = (pin_idx - 3); // because IP pin number range will be [8:3], '3' corresponds to PIN_NAME(PORT_C, 0)
		} else if (pin_idx == 9) { // "PORT_D" in pin_name.h
			DBG_GPIO_INFO("chip2pin D\r\n");
			chip_port = 3;
			chip_pin = (pin_idx - 9); // because IP pin number range will be [25:9] (for Test Chip) or [29:9] (for MP A-cut), '9' corresponds to PIN_NAME(PORT_D, 0)
		}
	} else if (port_idx == 3) {
		if (pin_idx == 5) { // "PORT_S" in pin_name.h
			DBG_GPIO_INFO("chip2pin S\r\n");
			chip_port = 6;
			chip_pin = (pin_idx - 5); // because IP pin number range will be [11:5], '5' corresponds to PIN_NAME(PORT_S, 0)
		}
	}

	// Special handling for Port E

#if IS_CUT_TEST(CONFIG_CHIP_VER) // Test Chip
	if ((port_idx == 2 && pin_idx == 26) || (port_idx == 3 && pin_idx == 26)) { // E1 (former) or E2 (latter)
		DBG_GPIO_INFO("chip2pin E\r\n");
		chip_port = 4;
		chip_pin = (pin_idx - 26);
	}

#else // MP Chip
	if ((port_idx == 2 && pin_idx == 30) || (port_idx == 3 && pin_idx == 30)) { // E1 (former) or E2 (latter)
		DBG_GPIO_INFO("chip2pin E\r\n");
		chip_port = 4;
		chip_pin = (pin_idx - 30);
	}

#endif

	return PIN_NAME(chip_port, chip_pin);
}

#endif  // end of "#if CONFIG_GPIO_EN"

/** @} */ /* End of group hs_hal_gpio */

