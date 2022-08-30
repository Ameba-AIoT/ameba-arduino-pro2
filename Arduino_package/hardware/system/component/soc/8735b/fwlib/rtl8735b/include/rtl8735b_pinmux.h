/**************************************************************************//**
 * @file     rtl8735b_pinmux.h
 * @brief    Define the IC pin name and IO port name
 * @version  V1.00
 * @date     2021-07-16
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2020 Realtek Corporation. All rights reserved.
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

#ifndef RTL8735B_PIN_MUX_H
#define RTL8735B_PIN_MUX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "rtl8735b_pin_name.h"


#define JTAG_PINS_SIZE              (5)

/**
  \brief  Defines the data type for pinmux info. in ROM.
 */
enum  pinmux_rom_info_e {
	PWR_LOG  = 0x0,
	REG_LOG  = 0x1,
	ALL_LOG  = 0x2
};

/**
  \brief  Defines the operation for pinmux info. in ROM.
 */
enum  pinmux_rom_info_op_e {
	OP_RESTORE  = 0x0,
	OP_BACKUP   = 0x1
};

/**
  * @brief The data type of JTAG/SWD pins list.
  */
typedef struct hal_jtag_pin_s {
	union {
		uint32_t pin_tclk;
		uint32_t pin_swclk;
	};
	union {
		uint32_t pin_tms;
		uint32_t pin_swdio;
	};
	uint32_t pin_tdo;
	uint32_t pin_tdi;
	uint32_t pin_trst;
} hal_jtag_pin_t, *phal_jtag_pin_t;

/**
  \brief  Defines the data type for pinmux selection.
 */
typedef struct {
	uint32_t pin_sel_0;
	uint32_t pin_sel_1;
	uint32_t pin_sel_2;
} hal_pinmux_sel_t, *phal_pinmux_sel_t;

/**
  * @brief The data type for IO pin configuration.
  */
typedef struct hal_pin_cfg_s {
	uint16_t pinmux_sel : 4;    /*!< [3..0] 0000: Primary
                                                                         0001: DMIC/I2C
                                                                         0010: PWM
                                                                         0011: RFAFE_CTRL/JTAG
                                                                         0100: TPIU/BT_AOX
                                                                         0101: SPI Master/I2S
                                                                         0110: SDIO Host/UART
                                                                         0111: BT
                                                                         1000: SPI Slave
                                                                         1001: External BT
                                                                         1111: GPIO */
	uint16_t           : 2;     /*!< [5..4] Reserved */
	uint16_t pull_ctrl : 2;     /*!< [7..6] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
	uint16_t           : 1;     /*!< [8..8] Reserved */
	uint16_t smt_en : 1;        /*!< [9..9] Enable Schmitt trigger; 1: enable */
	uint16_t driving : 2;       /*!< [11..10] 00: 4mA; 01: 8mA */
	uint16_t slew_rate : 1;     /*!< [12..12] 0: Disable, 1: Enable */
} hal_pin_cfg_t, *phal_pin_cfg_t;


typedef hal_status_t (*pin_register_t)(uint32_t pin_name, uint32_t periphl_id);
typedef hal_status_t (*pin_unregister_t)(uint32_t pin_name, uint32_t periphl_id);
typedef hal_status_t (*pin_validation_t)(uint32_t pin_name, uint32_t periphl_id);
typedef hal_status_t (*pin_mux_cfg_t)(uint32_t pin_name, uint32_t periphl_id);
typedef hal_status_t (*io_port_pwrup_t)(uint32_t pin_name, uint32_t periphl_id);
typedef hal_status_t (*io_port_pwrdn_t)(uint32_t pin_name, uint32_t periphl_id);


/**
  \brief  Pin management data structure to handle pin mux conflict, validate, power down management functions.
*/
typedef struct hal_pin_mux_mang_s {
	pin_register_t pin_reg_func;                ///< the callback function for pin register: usage record and conflict checking
	pin_unregister_t pin_unreg_func;            ///< the callback function for pin un-register
	pin_validation_t pin_validat_func;          ///< the callback function for pin validation checking
	pin_mux_cfg_t pin_mux_cfg_func;             ///< the callback function for pin mux configuration
	io_port_pwrup_t ioport_pwrup_ctrl_func;     ///< the callback function for GPIO pin power up control
	io_port_pwrdn_t ioport_pwrdn_ctrl_func;     ///< the callback function for GPIO pin power down control
	uint32_t pinmux_pwr_log[PORT_MAX_NUM];      ///< the bit map to record each pin is powered (enabled) or not
	uint32_t pinmux_reg_log[PORT_MAX_NUM];      ///< the bit map to record each pin is in using or not
	uint32_t *ppinmux_reg_rec;  ///< the array to record each pin is allocated to which peripheral
//    uint32_t trap_pin_pwr_log;                  ///< the bit map to record trap pins are powered (enabled) or not
} hal_pin_mux_mang_t, *phal_pin_mux_mang_t;


void hal_rtl_pinmux_manager_init(hal_pin_mux_mang_t *pinmux_manag);
hal_status_t hal_rtl_pin_register(uint32_t pin_name, uint32_t periphl_id);
hal_status_t hal_rtl_pin_unregister(uint32_t pin_name, uint32_t periphl_id);
hal_status_t hal_rtl_pin_mux_cfg(uint32_t pin_name, uint32_t periphl_id);
hal_status_t hal_rtl_pin_get_cfg(uint32_t pin_name, hal_pin_cfg_t *pin_cfg);
hal_status_t hal_rtl_pin_pwrup(uint32_t pin_name, uint32_t periphl_id);
hal_status_t hal_rtl_pin_pwrdwn(uint32_t pin_name, uint32_t periphl_id);
hal_status_t hal_rtl_pinmux_register(uint32_t pin_name, uint32_t periphl_id);
hal_status_t hal_rtl_pinmux_unregister(uint32_t pin_name, uint32_t periphl_id);
void hal_rtl_pinmux_rom_info_copy(uint32_t *p_dst, uint32_t *p_src, const uint32_t size);
void hal_rtl_pinmux_rom_info_manage(hal_pin_mux_mang_t *pinmux_manag, uint8_t op, uint8_t obj_id);

/**
  \brief  The data structure of the stubs function for the pin mux management HAL functions in ROM.
*/
typedef struct hal_pin_manag_func_stubs_s {
	phal_pin_mux_mang_t *pppin_manager;
	void (*hal_pinmux_manager_init)(hal_pin_mux_mang_t *pinmux_manag);
	hal_status_t (*hal_pin_register)(uint32_t pin_name, uint32_t periphl_id);
	hal_status_t (*hal_pin_unregister)(uint32_t pin_name, uint32_t periphl_id);
	hal_status_t (*hal_pin_mux_cfg)(uint32_t pin_name, uint32_t periphl_id);
	hal_status_t (*hal_pin_get_cfg)(uint32_t pin_name, hal_pin_cfg_t *pin_cfg);
	hal_status_t (*hal_pin_pwrup)(uint32_t pin_name, uint32_t periphl_id);
	hal_status_t (*hal_pin_pwrdwn)(uint32_t pin_name, uint32_t periphl_id);
	hal_status_t (*hal_pinmux_register)(uint32_t pin_name, uint32_t periphl_id);
	hal_status_t (*hal_pinmux_unregister)(uint32_t pin_name, uint32_t periphl_id);
#if IS_CUT_TEST(CONFIG_CHIP_VER)
	uint32_t reserved[6];  // reserved space for next ROM code version function table extending.
#else
	void (*hal_pinmux_rom_info_manage)(hal_pin_mux_mang_t *pinmux_manag, uint8_t op, uint8_t obj_id);
	uint32_t reserved[5];  // reserved space for next ROM code version function table extending.
#endif
} hal_pin_manag_func_stubs_t, *phal_pin_manag_func_stubs_t;


#ifdef __cplusplus
}
#endif

#endif /* RTL8735B_PIN_MUX_H */


