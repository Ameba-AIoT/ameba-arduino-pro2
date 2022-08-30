/**************************************************************************//**
 * @file     rtl8735b_pin_name.h
 * @brief    Define the IC pin name and IO port name
 * @version  V1.00
 * @date     2020-10-19
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2016 Realtek Corporation. All rights reserved.
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

#ifndef RTL8735B_PIN_NAME_H
#define RTL8735B_PIN_NAME_H

#ifdef __cplusplus
extern "C" {
#endif

/// Defines the macro to convert port index and pin index to a pin name
#define PIN_NAME(port_id, pin_id)           (((port_id) << 5) | (pin_id))
/// Defines the macro to get the port index by the given pin name
#define PIN_NAME_2_PORT(pin_name)           (((pin_name) >> 5) & 0xF)
/// Defines the macro to get the pin index by the given pin name
#define PIN_NAME_2_PIN(pin_name)            ((pin_name) & 0x1F)

/// Defines maximum number of pin in a GPIO port
#if IS_CUT_TEST(CONFIG_CHIP_VER)

#define MAX_PIN_IN_PORT     18  // not including DDR pins
#else
#define MAX_PIN_IN_PORT     21  // not including DDR pins
#endif

/**
  \brief  Defines Chip's IO port name.
 */
enum {
	PORT_A          = 0,
	PORT_B          = 1,
	PORT_C          = 2,
	PORT_D          = 3,
	PORT_E          = 4,
	PORT_F          = 5,
	PORT_S          = 6,
	PORT_DDR        = 7,

	PORT_MAX_NUM    = 8
};

/// Defines the virtual internal port, no pin out (BT UART HCI port)
#define PORT_INTERNAL       (9)

/**
  \brief  Defines Chip's IO pin name.
 */
enum {
	PIN_A0          = PIN_NAME(PORT_A, 0),
	PIN_A1          = PIN_NAME(PORT_A, 1),
	PIN_A2          = PIN_NAME(PORT_A, 2),
	PIN_A3          = PIN_NAME(PORT_A, 3),
	PIN_A4          = PIN_NAME(PORT_A, 4),
	PIN_A5          = PIN_NAME(PORT_A, 5),

	PIN_B0          = PIN_NAME(PORT_B, 0),
	PIN_B1          = PIN_NAME(PORT_B, 1),
	PIN_B2          = PIN_NAME(PORT_B, 2),

	PIN_C0          = PIN_NAME(PORT_C, 0),
	PIN_C1          = PIN_NAME(PORT_C, 1),
	PIN_C2          = PIN_NAME(PORT_C, 2),
	PIN_C3          = PIN_NAME(PORT_C, 3),
	PIN_C4          = PIN_NAME(PORT_C, 4),
	PIN_C5          = PIN_NAME(PORT_C, 5),

	PIN_D0          = PIN_NAME(PORT_D, 0),
	PIN_D1          = PIN_NAME(PORT_D, 1),
	PIN_D2          = PIN_NAME(PORT_D, 2),
	PIN_D3          = PIN_NAME(PORT_D, 3),
	PIN_D4          = PIN_NAME(PORT_D, 4),
	PIN_D5          = PIN_NAME(PORT_D, 5),
	PIN_D6          = PIN_NAME(PORT_D, 6),
	PIN_D7          = PIN_NAME(PORT_D, 7),
	PIN_D8          = PIN_NAME(PORT_D, 8),
	PIN_D9          = PIN_NAME(PORT_D, 9),
	PIN_D10         = PIN_NAME(PORT_D, 10),
	PIN_D11         = PIN_NAME(PORT_D, 11),
	PIN_D12         = PIN_NAME(PORT_D, 12),
	PIN_D13         = PIN_NAME(PORT_D, 13),
	PIN_D14         = PIN_NAME(PORT_D, 14),
	PIN_D15         = PIN_NAME(PORT_D, 15),
	PIN_D16         = PIN_NAME(PORT_D, 16),
#if !IS_CUT_TEST(CONFIG_CHIP_VER)
	PIN_D17         = PIN_NAME(PORT_D, 17),
	PIN_D18         = PIN_NAME(PORT_D, 18),
	PIN_D19         = PIN_NAME(PORT_D, 19),
	PIN_D20         = PIN_NAME(PORT_D, 20),
#endif

	PIN_E0          = PIN_NAME(PORT_E, 0),
	PIN_E1          = PIN_NAME(PORT_E, 1),
	PIN_E2          = PIN_NAME(PORT_E, 2),
	PIN_E3          = PIN_NAME(PORT_E, 3),
	PIN_E4          = PIN_NAME(PORT_E, 4),
	PIN_E5          = PIN_NAME(PORT_E, 5),
	PIN_E6          = PIN_NAME(PORT_E, 6),
#if IS_CUT_TEST(CONFIG_CHIP_VER)
	PIN_E7          = PIN_NAME(PORT_E, 7),
	PIN_E8          = PIN_NAME(PORT_E, 8),
	PIN_E9          = PIN_NAME(PORT_E, 9),
	PIN_E10         = PIN_NAME(PORT_E, 10),
#endif

	PIN_F0          = PIN_NAME(PORT_F, 0),
	PIN_F1          = PIN_NAME(PORT_F, 1),
	PIN_F2          = PIN_NAME(PORT_F, 2),
	PIN_F3          = PIN_NAME(PORT_F, 3),
	PIN_F4          = PIN_NAME(PORT_F, 4),
	PIN_F5          = PIN_NAME(PORT_F, 5),
	PIN_F6          = PIN_NAME(PORT_F, 6),
	PIN_F7          = PIN_NAME(PORT_F, 7),
	PIN_F8          = PIN_NAME(PORT_F, 8),
	PIN_F9          = PIN_NAME(PORT_F, 9),
	PIN_F10         = PIN_NAME(PORT_F, 10),
	PIN_F11         = PIN_NAME(PORT_F, 11),
	PIN_F12         = PIN_NAME(PORT_F, 12),
	PIN_F13         = PIN_NAME(PORT_F, 13),
	PIN_F14         = PIN_NAME(PORT_F, 14),
	PIN_F15         = PIN_NAME(PORT_F, 15),
	PIN_F16         = PIN_NAME(PORT_F, 16),
	PIN_F17         = PIN_NAME(PORT_F, 17),

	PIN_S0          = PIN_NAME(PORT_S, 0),
	PIN_S1          = PIN_NAME(PORT_S, 1),
	PIN_S2          = PIN_NAME(PORT_S, 2),
	PIN_S3          = PIN_NAME(PORT_S, 3),
	PIN_S4          = PIN_NAME(PORT_S, 4),
	PIN_S5          = PIN_NAME(PORT_S, 5),
	PIN_S6          = PIN_NAME(PORT_S, 6),

	PIN_DDR         = PIN_NAME(PORT_DDR, 0),

// Virtual pin (internal pin, no pin out)
	PIN_UART4_TX    = PIN_NAME(PORT_INTERNAL, 0),
	PIN_UART4_RX    = PIN_NAME(PORT_INTERNAL, 1),
	PIN_UART4_RTS   = PIN_NAME(PORT_INTERNAL, 2),
	PIN_UART4_CTS   = PIN_NAME(PORT_INTERNAL, 3),

	PIN_NC          = 0x1FF,
	PIN_LIST_END    = 0x1FF
};
typedef uint32_t pin_name_t;

/**
  \brief  Defines the data type for IO pin.
 */
typedef struct io_pin_s {
	union {
		uint32_t pin_name;
		struct {
			uint32_t pin         : 5;            /*!< [4:0] the pin index in a port */
			uint32_t port        : 4;            /*!< [8:5] the IO port index */
			uint32_t reserved    : 23;           /*!< [31:9] Reserved */
		} pin_name_b;
	};
} io_pin_t, *pio_pin_t;


#ifdef __cplusplus
}
#endif

#endif /* RTL8735B_PIN_NAME_H */


