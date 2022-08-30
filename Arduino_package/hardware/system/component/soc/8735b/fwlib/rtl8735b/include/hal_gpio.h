/**************************************************************************//**
 * @file     hal_gpio.h
 * @brief    The HAL API implementation for the GPIO.
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

#ifndef _HAL_GPIO_H_
#define _HAL_GPIO_H_

#include "cmsis.h"

#if defined(CONFIG_BUILD_NONSECURE)
#include "hal_gpio_nsc.h" //wd try, can call nsc w/o going thru _nsc()
#endif

#ifdef  rtl8735b
extern "C"
{
#endif

	/**
	 * @addtogroup hs_hal_gpio GPIO
	 * @{
	 * brief The GPIO HAL RAM APIs. These APIs is provided for user application to control the GPIO hardware.
	 */

	extern const hal_gpio_func_stubs_t hal_gpio_stubs;


	/* Functions parking, to be called from AON GPIO NSC function */
	/* These functions will not be exposed. */ /* START */

	__STATIC_INLINE uint32_t hal_aon_gpio_read(phal_gpio_adapter_t pgpio_adapter)
	{

		return hal_gpio_stubs.hal_gpio_read(pgpio_adapter);
	}

	__STATIC_INLINE void hal_aon_gpio_write(phal_gpio_adapter_t pgpio_adapter, uint32_t io_data)
	{

		hal_gpio_stubs.hal_gpio_write(pgpio_adapter, io_data);
	}

	__STATIC_INLINE void hal_aon_gpio_toggle(phal_gpio_adapter_t pgpio_adapter)
	{

		hal_gpio_stubs.hal_gpio_toggle(pgpio_adapter);
	}

	__STATIC_INLINE void hal_aon_gpio_set_dir(phal_gpio_adapter_t pgpio_adapter, gpio_dir_t dir)
	{
		hal_gpio_stubs.hal_gpio_set_dir(pgpio_adapter, dir);
	}

	__STATIC_INLINE gpio_dir_t hal_aon_gpio_get_dir(phal_gpio_adapter_t pgpio_adapter)
	{
		return hal_gpio_stubs.hal_gpio_get_dir(pgpio_adapter);
	}

#if !IS_CUT_TEST(CONFIG_CHIP_VER) // MP Chip only
	__STATIC_INLINE void hal_aon_gpio_port_write(phal_gpio_port_adapter_t pgpio_port_adapter, uint32_t io_data)
	{
		hal_gpio_stubs.hal_gpio_port_write(pgpio_port_adapter, io_data);
	}

	__STATIC_INLINE uint32_t hal_aon_gpio_port_read(phal_gpio_port_adapter_t pgpio_port_adapter)
	{
		return hal_gpio_stubs.hal_gpio_port_read(pgpio_port_adapter);
	}
#endif

	__STATIC_INLINE void hal_aon_gpio_irq_set_trig_type(phal_gpio_irq_adapter_t pgpio_adapter, gpio_int_trig_type_t int_type)
	{
		hal_gpio_stubs.hal_gpio_irq_set_trig_type(pgpio_adapter, int_type);
	}

	__STATIC_INLINE gpio_int_trig_type_t hal_aon_gpio_irq_get_trig_type(phal_gpio_irq_adapter_t pgpio_adapter)
	{
		return hal_gpio_stubs.hal_gpio_irq_get_trig_type(pgpio_adapter);
	}

	__STATIC_INLINE uint32_t hal_aon_gpio_irq_read(phal_gpio_irq_adapter_t pgpio_irq_adapter)
	{
		return hal_gpio_stubs.hal_gpio_irq_read(pgpio_irq_adapter);
	}

	__STATIC_INLINE void hal_aon_gpio_irq_enable(phal_gpio_irq_adapter_t pgpio_irq_adapter)
	{
		hal_gpio_stubs.hal_gpio_irq_enable(pgpio_irq_adapter);
	}

	__STATIC_INLINE void hal_aon_gpio_irq_disable(phal_gpio_irq_adapter_t pgpio_irq_adapter)
	{
		hal_gpio_stubs.hal_gpio_irq_disable(pgpio_irq_adapter);
	}

	// This static inline function has been moved to hal_gpio.c due to need for patching,to remove
	// static inline attributes.

	/*__STATIC_INLINE hal_status_t hal_aon_gpio_debounce_enable(phal_gpio_adapter_t pgpio_adapter, uint32_t debounce_us)
	{
		return hal_gpio_stubs.hal_gpio_debounce_enable(pgpio_adapter, debounce_us);
	}*/

	__STATIC_INLINE uint32_t hal_aon_gpio_read_debounce(phal_gpio_adapter_t pgpio_adapter)
	{
		return hal_gpio_stubs.hal_gpio_read_debounce(pgpio_adapter);
	}

	__STATIC_INLINE void hal_aon_gpio_debounce_disable(phal_gpio_adapter_t pgpio_adapter)
	{
		hal_gpio_stubs.hal_gpio_debounce_disable(pgpio_adapter);
	}

	// This static inline function has been moved to hal_gpio.c due to need for patching,to remove
	// static inline attributes.

	/*__STATIC_INLINE hal_status_t hal_aon_gpio_irq_debounce_enable(phal_gpio_irq_adapter_t pgpio_irq_adapter,
			uint32_t debounce_us)
	{
		return hal_gpio_stubs.hal_gpio_irq_debounce_enable(pgpio_irq_adapter, debounce_us);
	}*/

	__STATIC_INLINE void hal_aon_gpio_irq_debounce_disable(phal_gpio_irq_adapter_t pgpio_irq_adapter)
	{
		hal_gpio_stubs.hal_gpio_irq_debounce_disable(pgpio_irq_adapter);
	}

	__STATIC_INLINE hal_status_t hal_aon_gpio_slew_rate_ctrl(uint32_t pin_name, uint8_t slew_rate_func)
	{
		return hal_gpio_stubs.hal_gpio_slew_rate_ctrl(pin_name, slew_rate_func);
	}

	__STATIC_INLINE hal_status_t hal_aon_gpio_drive_ctrl(uint32_t pin_name, uint8_t drv)
	{
		return hal_gpio_stubs.hal_gpio_drive_ctrl(pin_name, drv);
	}

	__STATIC_INLINE hal_status_t hal_aon_gpio_schmitt_ctrl(uint32_t pin_name, BOOLEAN ctrl)
	{
		return hal_gpio_stubs.hal_gpio_schmitt_ctrl(pin_name, ctrl);
	}

	__STATIC_INLINE hal_status_t hal_aon_gpio_pull_ctrl(uint32_t pin_name, pin_pull_type_t pull_type)
	{
		return hal_gpio_stubs.hal_gpio_pull_ctrl(pin_name, pull_type);
	}

	/* Functions parking, to be called from AON GPIO NSC function */
	/* These functions will not be exposed. */ /* END */


#if IS_CUT_TEST(CONFIG_CHIP_VER) // Only for Test Chip
	/**
	 *  @brief Function declaration for GPIO port write patch function
	 *
	 *  @param[in]  irq_handler  The GPIO interrupt handler.
	 *
	 *  @returns    void
	 */
	void hal_rtl_gpio_port_write_patch(phal_gpio_port_adapter_t pgpio_port_adapter, uint32_t mask, uint32_t io_data);
#endif

	/**
	 *  @brief To register an interrupt handler for all GPIO interrupt pins and enable
	 *         the GPIO interrupt.
	 *
	 *  @param[in]  irq_handler  The GPIO interrupt handler.
	 *
	 *  @returns    void
	 */
	__STATIC_INLINE void hal_gpio_reg_irq(gpio_type_t gpio_type, irq_handler_t irq_handler)
	{
		hal_gpio_stubs.hal_gpio_reg_irq(gpio_type, irq_handler);
	}

#if IS_AFTER_CUT_A(CONFIG_CHIP_VER)

	__STATIC_INLINE hal_status_t hal_aon_gpio_interrupt_clk_sel(gpio_type_t gpio_type, uint8_t clk_sel)
	{
		return hal_gpio_stubs.hal_gpio_interrupt_clk_sel(gpio_type, clk_sel);
	}


	/**
	 *  @brief Changes the interrupt clock selection for the various GPIO types -
	 *         AON GPIO/PON GPIO/SYSON GPIO.
	 *
	 *  @param[in]  gpio_type   The type of GPIO - AON/PON/SYSON GPIO
	 *  @param[in]  clk_sel     The clock selection according to the
	 *                          various types of GPIO
	 *
	 *  @return     HAL_ERR:  Input arguments are invalid.
	 *  @return     HAL_OK:  Debounce function is enabled on this GPIO.
	 */
	__STATIC_INLINE hal_status_t hal_gpio_interrupt_clk_sel(gpio_type_t gpio_type, uint8_t clk_sel)
	{
#if defined(CONFIG_BUILD_NONSECURE)

		if (gpio_type == AonGPIO || gpio_type == SysonGPIO) { // SYSON GPIO's interrupt clk sel is in SYSON_S (secure region)
			return hal_gpio_interrupt_clk_sel_nsc(gpio_type, clk_sel);

		} else {
			return hal_gpio_stubs.hal_gpio_interrupt_clk_sel(gpio_type, clk_sel);
		}
#else

		return hal_gpio_stubs.hal_gpio_interrupt_clk_sel(gpio_type, clk_sel);
#endif
	}
#endif

	/**
	 *  @brief To enter a critical section of code, mainly it
	 *         disable the SYSON GPIO interrupt to prevent any race condition.
	 *
	 *  @returns void
	 */
	__STATIC_INLINE void hal_gpio_enter_critical(void)
	{
		hal_gpio_stubs.hal_gpio_enter_critical();
	}

	__STATIC_INLINE void hal_aon_gpio_enter_critical_via_NSC(void)
	{
		hal_gpio_stubs.hal_aon_gpio_enter_critical();
	}

	/**
	 *  @brief To enter a critical section of code, mainly it
	 *         disable the AON GPIO interrupt to prevent any race condition.
	 *
	 *  @returns void
	 */
	__STATIC_INLINE void hal_aon_gpio_enter_critical(void)
	{
#if defined(CONFIG_BUILD_NONSECURE)
		hal_aon_gpio_enter_critical_nsc();
#else
		hal_gpio_stubs.hal_aon_gpio_enter_critical();
#endif
	}

	/**
	 *  @brief To enter a critical section of code, mainly it
	 *         disable the PON GPIO interrupt to prevent any race condition.
	 *
	 *  @returns void
	 */
	__STATIC_INLINE void hal_pon_gpio_enter_critical(void)
	{
		hal_gpio_stubs.hal_pon_gpio_enter_critical();
	}

	/**
	 *  @brief To exit a critical code section, it will re-enable the SYSON GPIO interrupt
	 *         only when the exiting critical section is the top level.
	 *
	 *  @returns void
	 */
	__STATIC_INLINE void hal_gpio_exit_critical(void)
	{
		hal_gpio_stubs.hal_gpio_exit_critical();
	}

	__STATIC_INLINE void hal_aon_gpio_exit_critical_via_NSC(void)
	{
		hal_gpio_stubs.hal_aon_gpio_exit_critical();
	}

	/**
	 *  @brief To exit a critical code section, it will re-enable the AON GPIO interrupt
	 *         only when the exiting critical section is the top level.
	 *
	 *  @returns void
	 */
	__STATIC_INLINE void hal_aon_gpio_exit_critical(void)
	{
#if defined(CONFIG_BUILD_NONSECURE)
		hal_aon_gpio_exit_critical_nsc();
#else
		hal_gpio_stubs.hal_aon_gpio_exit_critical();
#endif
	}

	/**
	 *  @brief To exit a critical code section, it will re-enable the PON GPIO interrupt
	 *         only when the exiting critical section is the top level.
	 *
	 *  @returns void
	 */
	__STATIC_INLINE void hal_pon_gpio_exit_critical(void)
	{
		hal_gpio_stubs.hal_pon_gpio_exit_critical();
	}

	/**
	 *  @brief To set the direction of the specified GPIO pin.
	 *
	 *  @param pgpio_adapter The GPIO pin adapter.
	 *  @param dir The direction (IN or OUT)
	 *
	 *  @returns void
	 */
	__STATIC_INLINE void hal_gpio_set_dir(phal_gpio_adapter_t pgpio_adapter, gpio_dir_t dir)
	{
#if defined(CONFIG_BUILD_NONSECURE)
		if (pgpio_adapter->port_idx == PORT_A) {
			hal_gpio_set_dir_nsc(pgpio_adapter, dir);
		} else {
			hal_gpio_stubs.hal_gpio_set_dir(pgpio_adapter, dir);
		}
#else
		hal_gpio_stubs.hal_gpio_set_dir(pgpio_adapter, dir);
#endif
	}

	/**
	 *  @brief Gets current direction of the specified GPIO pin.
	 *
	 *  @param[in]  pgpio_adapter  The GPIO pin adapter.
	 *
	 *  @returns    The GPIO pin direction.
	 *                - 0: input.
	 *                - 1: output.
	 */
	__STATIC_INLINE gpio_dir_t hal_gpio_get_dir(phal_gpio_adapter_t pgpio_adapter)
	{
#if defined(CONFIG_BUILD_NONSECURE)
		if (pgpio_adapter->port_idx == PORT_A) {
			return hal_gpio_get_dir_nsc(pgpio_adapter);
		} else {
			return hal_gpio_stubs.hal_gpio_get_dir(pgpio_adapter);
		}
#else
		return hal_gpio_stubs.hal_gpio_get_dir(pgpio_adapter);
#endif
	}

	/**
	 *  @brief Sets the output level of the specified GPIO pin.
	 *
	 *  @param[in]  pgpio_adapter  The GPIO pin adapter.
	 *  @param[in]  io_data  The value to be set to the GPIO pin, 0 or 1.
	 *                - 0: the GPIO pin output low level.
	 *                - 1: the GPIO pin output high level.
	 *
	 *  @returns    void
	 */
	__STATIC_INLINE void hal_gpio_write(phal_gpio_adapter_t pgpio_adapter, uint32_t io_data)
	{
#if defined(CONFIG_BUILD_NONSECURE)
		if (pgpio_adapter->port_idx == PORT_A) {
			hal_gpio_write_nsc(pgpio_adapter, io_data);
		} else {
			hal_gpio_stubs.hal_gpio_write(pgpio_adapter, io_data);
		}
#else
		hal_gpio_stubs.hal_gpio_write(pgpio_adapter, io_data);
#endif
	}

	/**
	 *  @brief To toggle (0 -> 1 or 1 -> 0) the output level of the specified GPIO pin.
	 *
	 *  @param[in]  pgpio_adapter  The GPIO pin adapter.
	 *
	 *  @returns    void
	 */
	__STATIC_INLINE void hal_gpio_toggle(phal_gpio_adapter_t pgpio_adapter)
	{
#if defined(CONFIG_BUILD_NONSECURE)
		if (pgpio_adapter->port_idx == PORT_A) {
			hal_gpio_toggle_nsc(pgpio_adapter);
		} else {
			hal_gpio_stubs.hal_gpio_toggle(pgpio_adapter);
		}
#else
		hal_gpio_stubs.hal_gpio_toggle(pgpio_adapter);
#endif
	}

	/**
	 *  @brief To read the input level of the specified GPIO pin.
	 *
	 *  @param pgpio_adapter The GPIO pin adapter.
	 *
	 *  @returns The GPIO IN level (0 or 1).
	 */
	__STATIC_INLINE uint32_t hal_gpio_read(phal_gpio_adapter_t pgpio_adapter)
	{
#if defined(CONFIG_BUILD_NONSECURE)
		if (pgpio_adapter->port_idx == PORT_A) {
			return hal_gpio_read_nsc(pgpio_adapter);
		} else {
			return hal_gpio_stubs.hal_gpio_read(pgpio_adapter);
		}
#else
		return hal_gpio_stubs.hal_gpio_read(pgpio_adapter);
#endif
	}

	/*#if !IS_CUT_TEST(CONFIG_CHIP_VER)
		__STATIC_INLINE hal_status_t hal_gpio_debounce_enable(phal_gpio_adapter_t pgpio_adapter, uint32_t debounce_us)
		{
	#if defined(CONFIG_BUILD_NONSECURE)
			if (pgpio_adapter->port_idx == PORT_A) {
				return hal_gpio_debounce_enable_nsc(pgpio_adapter, debounce_us);
			} else {
				return hal_gpio_stubs.hal_gpio_debounce_enable(pgpio_adapter, debounce_us);
			}
	#else
			return hal_gpio_stubs.hal_gpio_debounce_enable(pgpio_adapter, debounce_us);
	#endif
		}
	#endif*/

	/**
	 *  @brief Reads the given GPIO pin input level with de-bounced.
	 *
	 *  @param[in]  pgpio_adapter  The GPIO pin adapter.
	 *
	 *  @returns The GPIO pin input level after debouncing.
	 *             - 0: the GPIO pin input level is low.
	 *             - 1: the GPIO pin input level is high.
	 */
	__STATIC_INLINE uint32_t hal_gpio_read_debounce(phal_gpio_adapter_t pgpio_adapter)
	{
#if defined(CONFIG_BUILD_NONSECURE)
		if (pgpio_adapter->port_idx == PORT_A) {
			return hal_gpio_read_debounce_nsc(pgpio_adapter);
		} else {

			return hal_gpio_stubs.hal_gpio_read_debounce(pgpio_adapter);
		}
#else
		return hal_gpio_stubs.hal_gpio_read_debounce(pgpio_adapter);
#endif
	}

	/**
	 *  @brief Disables the debounce function of the given GPIO pin.
	 *         The released debounce circuit can be assign to other GPIO pin.
	 *
	 *  @param[in]  pgpio_adapter  The GPIO pin adapter.
	 *
	 *  @returns    void
	 */
#if !IS_CUT_TEST(CONFIG_CHIP_VER)
	__STATIC_INLINE void hal_gpio_debounce_disable(phal_gpio_adapter_t pgpio_adapter)
	{
#if defined(CONFIG_BUILD_NONSECURE)
		if (pgpio_adapter->port_idx == PORT_A) {
			hal_gpio_debounce_disable_nsc(pgpio_adapter);
		} else {
			hal_gpio_stubs.hal_gpio_debounce_disable(pgpio_adapter);
		}
#else
		hal_gpio_stubs.hal_gpio_debounce_disable(pgpio_adapter);
#endif
	}
#endif

	/**
	 *  @brief Configures the interrupt trigger type of a given GPIO IRQ pin.
	 *
	 *  @param[in]  pgpio_adapter  The GPIO pin adapter.
	 *  @param[in]  int_type  The interrupt trigger type.
	 *                     - 1: Rising edge trigger.
	 *                     - 2: Falling edge trigger.
	 *                     - 3: Low level trigger.
	 *                     - 4: High level trigger.
	 *                     - 5: Dual(rising and falling) edge trigger.
	 *
	 *  @returns    void
	 */
	__STATIC_INLINE void hal_gpio_irq_set_trig_type(phal_gpio_irq_adapter_t pgpio_adapter, gpio_int_trig_type_t int_type)
	{
#if defined(CONFIG_BUILD_NONSECURE)

		uint8_t port_idx = PIN_NAME_2_PORT(pgpio_adapter->pin_name);

		if (port_idx == PORT_A) {
			hal_gpio_irq_set_trig_type_nsc(pgpio_adapter, int_type);
		} else {
			hal_gpio_stubs.hal_gpio_irq_set_trig_type(pgpio_adapter, int_type);
		}

#else
		hal_gpio_stubs.hal_gpio_irq_set_trig_type(pgpio_adapter, int_type);
#endif
	}

	/**
	 *  @brief Gets current GPIO interrupt trigger type configuration.
	 *
	 *  @param[in]  pgpio_adapter  The GPIO pin adapter.
	 *
	 *  @returns    The interrupt trigger type.
	 *                - 1: Rising edge trigger.
	 *                - 2: Falling edge trigger.
	 *                - 3: Low level trigger.
	 *                - 4: High level trigger.
	 *                - 5: Dual(rising and falling) edge trigger.
	 */
	__STATIC_INLINE gpio_int_trig_type_t hal_gpio_irq_get_trig_type(phal_gpio_irq_adapter_t pgpio_adapter)
	{
#if defined(CONFIG_BUILD_NONSECURE)
		uint8_t port_idx = PIN_NAME_2_PORT(pgpio_adapter->pin_name);

		if (port_idx == PORT_A) {
			return hal_gpio_irq_get_trig_type_nsc(pgpio_adapter);
		} else {
			return hal_gpio_stubs.hal_gpio_irq_get_trig_type(pgpio_adapter);
		}

#else
		return hal_gpio_stubs.hal_gpio_irq_get_trig_type(pgpio_adapter);
#endif
	}

	/**
	 *  @brief Enables the interrupt of the given GPIO IRQ pin.
	 *
	 *  @param[in]  pgpio_irq_adapter  The GPIO IRQ pin adapter.
	 *
	 *  @returns void
	 */
	__STATIC_INLINE void hal_gpio_irq_enable(phal_gpio_irq_adapter_t pgpio_irq_adapter)
	{
#if defined(CONFIG_BUILD_NONSECURE)
		uint8_t port_idx = PIN_NAME_2_PORT(pgpio_irq_adapter->pin_name);

		if (port_idx == PORT_A) {
			hal_gpio_irq_enable_nsc(pgpio_irq_adapter);
		} else {
			hal_gpio_stubs.hal_gpio_irq_enable(pgpio_irq_adapter);
		}
#else

		hal_gpio_stubs.hal_gpio_irq_enable(pgpio_irq_adapter);
#endif
	}

	/**
	 *  @brief Disables the interrupt of the given GPIO IRQ pin.
	 *
	 *  @param[in]  pgpio_irq_adapter  The GPIO IRQ pin adapter.
	 *
	 *  @returns    void
	 */
#if !IS_CUT_TEST(CONFIG_CHIP_VER)
	__STATIC_INLINE void hal_gpio_irq_disable(phal_gpio_irq_adapter_t pgpio_irq_adapter)
	{
#if defined(CONFIG_BUILD_NONSECURE)
		uint8_t port_idx = PIN_NAME_2_PORT(pgpio_irq_adapter->pin_name);

		if (port_idx == PORT_A) {
			hal_gpio_irq_disable_nsc(pgpio_irq_adapter);
		} else {
			hal_gpio_stubs.hal_gpio_irq_disable(pgpio_irq_adapter);
		}

#else
		hal_gpio_stubs.hal_gpio_irq_disable(pgpio_irq_adapter);
#endif
	}
#endif

	// This function has been moved to hal_gpio.c, due to patching, and removal of static inline attribute.
#if !IS_CUT_TEST(CONFIG_CHIP_VER)
	/*__STATIC_INLINE hal_status_t hal_gpio_irq_debounce_enable(phal_gpio_irq_adapter_t pgpio_irq_adapter,
			uint32_t debounce_us)
	{
	#if defined(CONFIG_BUILD_NONSECURE)

		uint8_t port_idx = PIN_NAME_2_PORT(pgpio_irq_adapter->pin_name);

		if (port_idx == PORT_A) {
			return hal_gpio_irq_debounce_enable_nsc(pgpio_irq_adapter, debounce_us);
		} else {

			return hal_gpio_stubs.hal_gpio_irq_debounce_enable(pgpio_irq_adapter, debounce_us);
		}
	#else

		return hal_gpio_stubs.hal_gpio_irq_debounce_enable(pgpio_irq_adapter, debounce_us);
	#endif
	}*/

	/**
	 *  @brief To disable the debounce function of the given GPIO IRQ pin.
	 *
	 *  @param[in]  pgpio_irq_adapter  The GPIO IRQ pin adapter.
	 *
	 *  @returns    void
	 */
	__STATIC_INLINE void hal_gpio_irq_debounce_disable(phal_gpio_irq_adapter_t pgpio_irq_adapter)
	{
#if defined(CONFIG_BUILD_NONSECURE)

		uint8_t port_idx = PIN_NAME_2_PORT(pgpio_irq_adapter->pin_name);

		if (port_idx == PORT_A) {
			hal_gpio_irq_debounce_disable_nsc(pgpio_irq_adapter);

		} else {
			hal_gpio_stubs.hal_gpio_irq_debounce_disable(pgpio_irq_adapter);
		}
#else

		hal_gpio_stubs.hal_gpio_irq_debounce_disable(pgpio_irq_adapter);
#endif
	}
#endif

	/**
	 *  @brief Reads the input level of the given GPIO IRQ pin.
	 *         If a debounce function is enabled on this GPIO IRQ pin,
	 *         then reads the de-bounced input level.
	 *
	 *  @param[in]  pgpio_irq_adapter  The GPIO IRQ pin adapter.
	 *
	 *  @returns    The input level(0 or 1) of the GPIO IRQ pin.
	 *                - 0: the GPIO IRQ pin input level is low.
	 *                - 1: the GPIO IRQ pin input level is high.
	 */
	__STATIC_INLINE uint32_t hal_gpio_irq_read(phal_gpio_irq_adapter_t pgpio_irq_adapter)
	{
#if defined(CONFIG_BUILD_NONSECURE)
		uint8_t port_idx = PIN_NAME_2_PORT(pgpio_irq_adapter->pin_name);

		if (port_idx == PORT_A) {
			return hal_gpio_irq_read_nsc(pgpio_irq_adapter);
		} else {
			return hal_gpio_stubs.hal_gpio_irq_read(pgpio_irq_adapter);
		}
#else

		return hal_gpio_stubs.hal_gpio_irq_read(pgpio_irq_adapter);
#endif
	}

	/**
	 *  @brief Writes a value to the given GPIO output port.
	 *
	 *  @param[in]  pgpio_port_adapter  The GPIO port adapter.
	 *  @param[in]  io_data  The value to be write to the GPIO port.
	 *
	 *  @returns    void
	 */
#if !IS_CUT_TEST(CONFIG_CHIP_VER) // MP chip
	__STATIC_INLINE void hal_gpio_port_write(phal_gpio_port_adapter_t pgpio_port_adapter, uint32_t io_data)
	{
#if defined(CONFIG_BUILD_NONSECURE)
		if (pgpio_port_adapter->port_idx == PORT_A) {
			hal_gpio_port_write_nsc(pgpio_port_adapter, io_data);
		} else {
			hal_gpio_stubs.hal_gpio_port_write(pgpio_port_adapter, io_data);
		}
#else
		hal_gpio_stubs.hal_gpio_port_write(pgpio_port_adapter, io_data);
#endif

	}
#else // Test chip
	__STATIC_INLINE void hal_gpio_port_write(phal_gpio_port_adapter_t pgpio_port_adapter, uint32_t mask, uint32_t io_data)
	{
		hal_rtl_gpio_port_write_patch(pgpio_port_adapter, mask, io_data);
	}
#endif

	/**
	 *  @brief Read the GPIO port.
	 *
	 *  @param[in]  pgpio_port_adapter  The GPIO port adapter.
	 *
	 *  @returns    The level status of the GPIO port.
	 */
#if !IS_CUT_TEST(CONFIG_CHIP_VER) // MP chip will use static inline here; Test chip will have hal_gpio_port_read() defined in hal_gpio.c.
	__STATIC_INLINE uint32_t hal_gpio_port_read(phal_gpio_port_adapter_t pgpio_port_adapter)
	{
#if defined(CONFIG_BUILD_NONSECURE)
		if (pgpio_port_adapter->port_idx == PORT_A) {
			return hal_gpio_port_read_nsc(pgpio_port_adapter);
		} else {
			return hal_gpio_stubs.hal_gpio_port_read(pgpio_port_adapter);
		}
#else

		return hal_gpio_stubs.hal_gpio_port_read(pgpio_port_adapter);
#endif
	}
#endif

	/**
	 *  @brief Configures the pull type of the given GPIO pin.
	 *
	 *  @param[in]  pin_name  The GPIO pin.
	 *                - bit[7:5]: the GPIO port number. Each port has 32 GPIO pins.
	 *                - bit[4:0]: the pin number of the GPIO port.
	 *  @param[in]  pull_type  The pull type:
	 *                - 0: No pull.
	 *                - 1: Pull high.
	 *                - 2: Pull low.
	 *                - other value: No pull.
	 *
	 *  @return     HAL_ERR_PARA:  Input arguments are invalid.
	 *  @return     HAL_OK:  Configures IO pad pull type OK.
	 */
	__STATIC_INLINE hal_status_t hal_gpio_pull_ctrl(uint32_t pin_name, pin_pull_type_t pull_type)
	{
#if defined(CONFIG_BUILD_NONSECURE)

		uint8_t port_idx = PIN_NAME_2_PORT(pin_name);

		if (port_idx == PORT_A) {
			return hal_gpio_pull_ctrl_nsc(pin_name, pull_type);
		} else {
			return hal_gpio_stubs.hal_gpio_pull_ctrl(pin_name, pull_type);
		}
#else

		return hal_gpio_stubs.hal_gpio_pull_ctrl(pin_name, pull_type);
#endif
	}

	/**
	 *  @brief The schmitt trigger on/off control on the given GPIO pin .
	 *
	 *  @param[in]  pin_name  The GPIO pin.
	 *                - bit[7:5]: the GPIO port number. Each port has 32 GPIO pins.
	 *                - bit[4:0]: the pin number of the GPIO port.
	 *  @param[in]  ctrl  The on/off control:
	 *                      - 0: disable the schmitt trigger.
	 *                      - 1: enable the schmitt trigger.
	 *
	 *  @return     HAL_ERR_PARA:  Input arguments are invalid.
	 *  @return     HAL_OK:  Schmitt trigger enable control setup OK.
	 */
	__STATIC_INLINE hal_status_t hal_gpio_schmitt_ctrl(uint32_t pin_name, BOOLEAN ctrl)
	{
#if defined(CONFIG_BUILD_NONSECURE)

		uint8_t port_idx = PIN_NAME_2_PORT(pin_name);

		if (port_idx == PORT_A) {
			return hal_gpio_schmitt_ctrl_nsc(pin_name, ctrl);
		} else {
			return hal_gpio_stubs.hal_gpio_schmitt_ctrl(pin_name, ctrl);
		}
#else

		return hal_gpio_stubs.hal_gpio_schmitt_ctrl(pin_name, ctrl);
#endif
	}

	/**
	 *  @brief Controls the IO pad drive power current on the given GPIO pin .
	 *
	 *  @param[in]  pin_name  The GPIO pin.
	 *                - bit[7:5]: the GPIO port number. Each port has 32 GPIO pins.
	 *                - bit[4:0]: the pin number of the GPIO port.
	 *  @param[in]  drv  The I/O pad driving power selection:
	                    0: 4mA
	                    1: 8mA
	 *
	 *  @return     HAL_ERR_PARA:  Input arguments are invalid.
	 *  @return     HAL_OK:  IO pad driving current setup OK.
	 */
	__STATIC_INLINE hal_status_t hal_gpio_drive_ctrl(uint32_t pin_name, uint8_t drv)
	{
#if defined(CONFIG_BUILD_NONSECURE)
		uint8_t port_idx = PIN_NAME_2_PORT(pin_name);

		if (port_idx == PORT_A) {
			return hal_gpio_drive_ctrl_nsc(pin_name, drv);
		} else {
			return hal_gpio_stubs.hal_gpio_drive_ctrl(pin_name, drv);
		}
#else

		return hal_gpio_stubs.hal_gpio_drive_ctrl(pin_name, drv);
#endif
	}

	/**
	 *  @brief Controls the slew rate function enable/disable on the given GPIO pin .
	 *
	 *  @param[in]  pin_name  The GPIO pin.
	 *                - bit[7:5]: the GPIO port number. Each port has 32 GPIO pins.
	 *                - bit[4:0]: the pin number of the GPIO port.
	 *  @param[in]  slew_rate_func  The slew rate function enable selection:
	                    0: Disable
	                    1: Enable
	 *
	 *  @return     HAL_ERR_PARA:  Input arguments are invalid.
	 *  @return     HAL_OK:  Slew rate function setup OK.
	 */

	__STATIC_INLINE hal_status_t hal_gpio_slew_rate_ctrl(uint32_t pin_name, uint8_t slew_rate_func)
	{

#if defined(CONFIG_BUILD_NONSECURE)

		uint8_t port_idx = PIN_NAME_2_PORT(pin_name);

		if (port_idx == PORT_A) {
			return hal_gpio_slew_rate_ctrl_nsc(pin_name, slew_rate_func);
		} else {
			return hal_gpio_stubs.hal_gpio_slew_rate_ctrl(pin_name, slew_rate_func);
		}
#else

		return hal_gpio_stubs.hal_gpio_slew_rate_ctrl(pin_name, slew_rate_func);
#endif
	}

	void hal_gpio_comm_init(phal_gpio_comm_adapter_t pgpio_comm_adp);
	void hal_aon_gpio_comm_init(phal_aon_gpio_comm_adapter_t paon_gpio_comm_adp);
	void hal_pon_gpio_comm_init(phal_pon_gpio_comm_adapter_t ppon_gpio_comm_adp);
	void hal_gpio_comm_deinit(void);
	void hal_aon_gpio_comm_deinit(void);
	void hal_pon_gpio_comm_deinit(void);
	hal_status_t hal_gpio_init(phal_gpio_adapter_t pgpio_adapter, uint32_t pin_name);
	void hal_gpio_deinit(phal_gpio_adapter_t pgpio_adapter);
	void aon_gpio_sclk_source_select(uint32_t sclk_src_sel);
	hal_status_t hal_gpio_irq_init(phal_gpio_irq_adapter_t pgpio_irq_adapter, uint32_t pin_name,
								   gpio_irq_callback_t callback, uint32_t arg);
	void hal_gpio_irq_deinit(phal_gpio_irq_adapter_t pgpio_irq_adapter);
	hal_status_t hal_gpio_port_init(phal_gpio_port_adapter_t pgpio_port_adapter, uint32_t port_idx,
									uint32_t mask, gpio_dir_t dir);
	void hal_gpio_port_deinit(phal_gpio_port_adapter_t pgpio_port_adapter);
#if !IS_CUT_TEST(CONFIG_CHIP_VER) // MP chip
	void hal_gpio_port_dir(phal_gpio_port_adapter_t pgpio_port_adapter, gpio_dir_t dir);
#else // Test chip
	void hal_gpio_port_dir(phal_gpio_port_adapter_t pgpio_port_adapter, uint32_t mask, gpio_dir_t dir);
#endif
#if IS_CUT_TEST(CONFIG_CHIP_VER) // Test chip will have hal_gpio_port_read() defined in hal_gpio.c, but MP chip will use static inline here
	uint32_t hal_gpio_port_read(phal_gpio_port_adapter_t pgpio_port_adapter, uint32_t mask);
#endif
	uint8_t hal_gpio_ip_pin_to_chip_pin(uint32_t port_idx, uint32_t pin_idx);

	hal_status_t hal_gpio_pull_ctrl(uint32_t pin_name, pin_pull_type_t pull_type);
	hal_status_t hal_gpio_schmitt_ctrl(uint32_t pin_name, BOOLEAN ctrl);
	hal_status_t hal_gpio_drive_ctrl(uint32_t pin_name, uint8_t drv);
	hal_status_t hal_gpio_slew_rate_ctrl(uint32_t pin_name, uint8_t slew_rate_func);

	void hal_gpio_reinit(phal_gpio_adapter_t pgpio_adapter, uint32_t pin_name);
	hal_status_t hal_gpio_irq_debounce_enable(phal_gpio_irq_adapter_t pgpio_irq_adapter,
			uint32_t debounce_us);
	hal_status_t hal_gpio_debounce_enable(phal_gpio_adapter_t pgpio_adapter, uint32_t debounce_us);

	// Function prototypes for AON GPIO [Start]
	void hal_aon_gpio_comm_init_via_NSC(phal_aon_gpio_comm_adapter_t paon_gpio_comm_adp);
	void hal_aon_gpio_comm_deinit_via_NSC(void);
	hal_status_t hal_aon_gpio_init(phal_gpio_adapter_t pgpio_adapter, uint32_t pin_name);
	void hal_aon_gpio_deinit(phal_gpio_adapter_t pgpio_adapter);
	hal_status_t hal_aon_gpio_irq_init(phal_gpio_irq_adapter_t pgpio_irq_adapter, uint32_t pin_name,
									   gpio_irq_callback_t callback, uint32_t arg);
	void hal_aon_gpio_irq_deinit(phal_gpio_irq_adapter_t pgpio_irq_adapter);
	hal_status_t hal_aon_gpio_port_init(phal_gpio_port_adapter_t pgpio_port_adapter, uint32_t port_idx,
										uint32_t mask, gpio_dir_t dir);
	void hal_aon_gpio_port_deinit(phal_gpio_port_adapter_t pgpio_port_adapter);
	void hal_aon_gpio_port_dir(phal_gpio_port_adapter_t pgpio_port_adapter, gpio_dir_t dir);
	void aon_gpio_sclk_source_select_via_NSC(uint32_t sclk_src_sel);
	hal_status_t hal_aon_gpio_irq_debounce_enable(phal_gpio_irq_adapter_t pgpio_irq_adapter,
			uint32_t debounce_us);
	hal_status_t hal_aon_gpio_debounce_enable(phal_gpio_adapter_t pgpio_adapter, uint32_t debounce_us);

	// Function prototypes for AON GPIO [End]

	/** @} */ /* End of group hs_hal_gpio */

#ifdef  rtl8735b
}
#endif

#endif  // end of "#define _HAL_GPIO_H_"

