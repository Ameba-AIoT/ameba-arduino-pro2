/**************************************************************************//**
* @file        hal_gpio_nsc.h
* @brief       The HAL Non-secure callable API implementation for GPIO
*
* @version     V1.00
* @date        2020-11-12
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



#ifndef _HAL_GPIO_NSC_H_
#define _HAL_GPIO_NSC_H_
#include "cmsis.h"

#ifdef  __cplusplus
extern "C"
{
#endif


#if defined(CONFIG_BUILD_SECURE)

void NS_ENTRY hal_aon_gpio_comm_init_nsc(phal_aon_gpio_comm_adapter_t paon_gpio_comm_adp);
void NS_ENTRY hal_aon_gpio_comm_deinit_nsc(void);
hal_status_t NS_ENTRY hal_gpio_init_nsc(phal_gpio_adapter_t pgpio_adapter, uint32_t pin_name);
void NS_ENTRY hal_gpio_deinit_nsc(phal_gpio_adapter_t pgpio_adapter);
hal_status_t NS_ENTRY hal_gpio_irq_init_nsc(phal_gpio_irq_adapter_t pgpio_irq_adapter, uint32_t pin_name,
		gpio_irq_callback_t callback, uint32_t arg);
void NS_ENTRY hal_gpio_irq_deinit_nsc(phal_gpio_irq_adapter_t pgpio_irq_adapter);
hal_status_t NS_ENTRY hal_gpio_port_init_nsc(phal_gpio_port_adapter_t pgpio_port_adapter, uint32_t port_idx,
		uint32_t mask, gpio_dir_t dir);
void NS_ENTRY hal_gpio_port_deinit_nsc(phal_gpio_port_adapter_t pgpio_port_adapter);

#if !IS_CUT_TEST(CONFIG_CHIP_VER) // MP chip
void NS_ENTRY hal_gpio_port_dir_nsc(phal_gpio_port_adapter_t pgpio_port_adapter, gpio_dir_t dir);
#else // Test chip
void NS_ENTRY hal_gpio_port_dir_nsc(phal_gpio_port_adapter_t pgpio_port_adapter, uint32_t mask, gpio_dir_t dir);
#endif

#if IS_AFTER_CUT_A(CONFIG_CHIP_VER)
hal_status_t NS_ENTRY hal_gpio_interrupt_clk_sel_nsc(gpio_type_t gpio_type, uint8_t clk_sel);
#endif

void NS_ENTRY hal_aon_gpio_enter_critical_nsc(void);
void NS_ENTRY hal_aon_gpio_exit_critical_nsc(void);
void NS_ENTRY hal_gpio_set_dir_nsc(phal_gpio_adapter_t pgpio_adapter, gpio_dir_t dir);
gpio_dir_t NS_ENTRY hal_gpio_get_dir_nsc(phal_gpio_adapter_t pgpio_adapter);
void NS_ENTRY hal_gpio_write_nsc(phal_gpio_adapter_t pgpio_adapter, uint32_t io_data);
void NS_ENTRY hal_gpio_toggle_nsc(phal_gpio_adapter_t pgpio_adapter);
uint32_t NS_ENTRY hal_gpio_read_nsc(phal_gpio_adapter_t pgpio_adapter);
hal_status_t NS_ENTRY hal_gpio_debounce_enable_nsc(phal_gpio_adapter_t pgpio_adapter, uint32_t debounce_us);
uint32_t NS_ENTRY hal_gpio_read_debounce_nsc(phal_gpio_adapter_t pgpio_adapter);
void NS_ENTRY hal_gpio_debounce_disable_nsc(phal_gpio_adapter_t pgpio_adapter);
void NS_ENTRY hal_gpio_irq_set_trig_type_nsc(phal_gpio_irq_adapter_t pgpio_adapter, gpio_int_trig_type_t int_type);
gpio_int_trig_type_t NS_ENTRY hal_gpio_irq_get_trig_type_nsc(phal_gpio_irq_adapter_t pgpio_adapter);
void NS_ENTRY hal_gpio_irq_enable_nsc(phal_gpio_irq_adapter_t pgpio_irq_adapter);
void NS_ENTRY hal_gpio_irq_disable_nsc(phal_gpio_irq_adapter_t pgpio_irq_adapter);
hal_status_t NS_ENTRY hal_gpio_irq_debounce_enable_nsc(phal_gpio_irq_adapter_t pgpio_irq_adapter,
		uint32_t debounce_us);
void NS_ENTRY hal_gpio_irq_debounce_disable_nsc(phal_gpio_irq_adapter_t pgpio_irq_adapter);
uint32_t NS_ENTRY hal_gpio_irq_read_nsc(phal_gpio_irq_adapter_t pgpio_irq_adapter);

#if !IS_CUT_TEST(CONFIG_CHIP_VER) // MP chip
void NS_ENTRY hal_gpio_port_write_nsc(phal_gpio_port_adapter_t pgpio_port_adapter, uint32_t io_data);
uint32_t NS_ENTRY hal_gpio_port_read_nsc(phal_gpio_port_adapter_t pgpio_port_adapter);
#else // Test chip
void NS_ENTRY hal_gpio_port_write_nsc(phal_gpio_port_adapter_t pgpio_port_adapter, uint32_t mask, uint32_t io_data);
uint32_t NS_ENTRY hal_gpio_port_read_nsc(phal_gpio_port_adapter_t pgpio_port_adapter, uint32_t mask);
#endif

hal_status_t NS_ENTRY hal_gpio_pull_ctrl_nsc(uint32_t pin_name, pin_pull_type_t pull_type);
hal_status_t NS_ENTRY hal_gpio_schmitt_ctrl_nsc(uint32_t pin_name, BOOLEAN ctrl);
hal_status_t NS_ENTRY hal_gpio_drive_ctrl_nsc(uint32_t pin_name, uint8_t drv);
hal_status_t NS_ENTRY hal_gpio_slew_rate_ctrl_nsc(uint32_t pin_name, uint8_t slew_rate_func);

// Newly added functions will come here for greater clarity when debugging - added from 30JUL2021 onwards， only for MP A-cut chip and beyond
void NS_ENTRY aon_gpio_sclk_source_select_nsc(uint32_t sclk_src_sel);
#endif // end of #if defined(CONFIG_BUILD_SECURE)



#if defined(CONFIG_BUILD_NONSECURE)

void hal_aon_gpio_comm_init_nsc(phal_aon_gpio_comm_adapter_t paon_gpio_comm_adp);
void hal_aon_gpio_comm_deinit_nsc(void);
hal_status_t hal_gpio_init_nsc(phal_gpio_adapter_t pgpio_adapter, uint32_t pin_name);
void hal_gpio_deinit_nsc(phal_gpio_adapter_t pgpio_adapter);
hal_status_t hal_gpio_irq_init_nsc(phal_gpio_irq_adapter_t pgpio_irq_adapter, uint32_t pin_name,
								   gpio_irq_callback_t callback, uint32_t arg);
void hal_gpio_irq_deinit_nsc(phal_gpio_irq_adapter_t pgpio_irq_adapter);
hal_status_t hal_gpio_port_init_nsc(phal_gpio_port_adapter_t pgpio_port_adapter, uint32_t port_idx,
									uint32_t mask, gpio_dir_t dir);
void hal_gpio_port_deinit_nsc(phal_gpio_port_adapter_t pgpio_port_adapter);

#if !IS_CUT_TEST(CONFIG_CHIP_VER) // MP chip
void hal_gpio_port_dir_nsc(phal_gpio_port_adapter_t pgpio_port_adapter, gpio_dir_t dir);
#else // Test chip
void hal_gpio_port_dir_nsc(phal_gpio_port_adapter_t pgpio_port_adapter, uint32_t mask, gpio_dir_t dir);
#endif

void hal_gpio_reg_irq_nsc(gpio_type_t gpio_type, irq_handler_t irq_handler);

#if IS_AFTER_CUT_A(CONFIG_CHIP_VER)
hal_status_t hal_gpio_interrupt_clk_sel_nsc(gpio_type_t gpio_type, uint8_t clk_sel);
#endif

void hal_aon_gpio_enter_critical_nsc(void);
void hal_aon_gpio_exit_critical_nsc(void);
void hal_gpio_set_dir_nsc(phal_gpio_adapter_t pgpio_adapter, gpio_dir_t dir);
gpio_dir_t hal_gpio_get_dir_nsc(phal_gpio_adapter_t pgpio_adapter);
void hal_gpio_write_nsc(phal_gpio_adapter_t pgpio_adapter, uint32_t io_data);
void hal_gpio_toggle_nsc(phal_gpio_adapter_t pgpio_adapter);
uint32_t hal_gpio_read_nsc(phal_gpio_adapter_t pgpio_adapter);
hal_status_t hal_gpio_debounce_enable_nsc(phal_gpio_adapter_t pgpio_adapter, uint32_t debounce_us);
uint32_t hal_gpio_read_debounce_nsc(phal_gpio_adapter_t pgpio_adapter);
void hal_gpio_debounce_disable_nsc(phal_gpio_adapter_t pgpio_adapter);
void hal_gpio_irq_set_trig_type_nsc(phal_gpio_irq_adapter_t pgpio_adapter, gpio_int_trig_type_t int_type);
gpio_int_trig_type_t hal_gpio_irq_get_trig_type_nsc(phal_gpio_irq_adapter_t pgpio_adapter);
void hal_gpio_irq_enable_nsc(phal_gpio_irq_adapter_t pgpio_irq_adapter);
void hal_gpio_irq_disable_nsc(phal_gpio_irq_adapter_t pgpio_irq_adapter);
hal_status_t hal_gpio_irq_debounce_enable_nsc(phal_gpio_irq_adapter_t pgpio_irq_adapter,
		uint32_t debounce_us);
void hal_gpio_irq_debounce_disable_nsc(phal_gpio_irq_adapter_t pgpio_irq_adapter);
uint32_t hal_gpio_irq_read_nsc(phal_gpio_irq_adapter_t pgpio_irq_adapter);

#if !IS_CUT_TEST(CONFIG_CHIP_VER) // MP chip
void hal_gpio_port_write_nsc(phal_gpio_port_adapter_t pgpio_port_adapter, uint32_t io_data);
uint32_t hal_gpio_port_read_nsc(phal_gpio_port_adapter_t pgpio_port_adapter);
#else // Test chip
void hal_gpio_port_write_nsc(phal_gpio_port_adapter_t pgpio_port_adapter, uint32_t mask, uint32_t io_data);
uint32_t hal_gpio_port_read_nsc(phal_gpio_port_adapter_t pgpio_port_adapter, uint32_t mask);
#endif

hal_status_t hal_gpio_pull_ctrl_nsc(uint32_t pin_name, pin_pull_type_t pull_type);
hal_status_t hal_gpio_schmitt_ctrl_nsc(uint32_t pin_name, BOOLEAN ctrl);
hal_status_t hal_gpio_drive_ctrl_nsc(uint32_t pin_name, uint8_t drv);
hal_status_t hal_gpio_slew_rate_ctrl_nsc(uint32_t pin_name, uint8_t slew_rate_func);

// Newly added functions will come here for greater clarity when debugging - added from 30JUL2021 onwards， only for MP A-cut chip and beyond
void aon_gpio_sclk_source_select_nsc(uint32_t sclk_src_sel);

#endif  // end of "#if defined(CONFIG_BUILD_NONSECURE)"


#ifdef  __cplusplus
}
#endif

#endif  // end of "#define _HAL_GPIO_NSC_H_"
