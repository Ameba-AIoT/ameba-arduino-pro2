/**************************************************************************//**
 * @file     rtl8735b_peripheral_id.h
 * @brief    Define a identification ID for each peripheral device.
 * @version  V1.00
 * @date     2020-10-19
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2016 Realtek Corporation. All rights reserved.
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


#ifndef _RTL8735B_PHERI_ID_H_
#define _RTL8735B_PHERI_ID_H_

#include "basic_types.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
  \brief  Defines IO Pin peripheral function category.
             0: Primary
             1: DMIC/I2C
             2: PWM
             3: RFAFE_CTRL/JTAG
             4: TPIU/BT_AOX
             5: SPI Master/I2S
             6: SDIO Host/UART
             7: BT
             8: SPI Slave
             9: External BT
             F: GPIO/DDR
 */
enum  peripheral_func_cat_e {
	FUNC_COMP_ADC   = 0x00,
	FUNC_VP         = 0x00,
	FUNC_USB        = 0x00,
	FUNC_FLASH      = 0x00,
	FUNC_MIPI       = 0x00,
	FUNC_SENSOR     = 0x00,
	FUNC_I2C3       = 0x00,
	FUNC_RF_DBG     = 0x00,
	FUNC_ADC        = 0x00,
	FUNC_SD_HOST    = 0x00,

	FUNC_I2C        = 0x01,
	FUNC_SIC        = 0x01,
	FUNC_DMIC       = 0x01,
	FUNC_SGPIO      = 0x01,

	FUNC_WLAN_LED   = 0x02,
	FUNC_WLAN_UART  = 0x02,
	FUNC_PWM        = 0x02,

	FUNC_JTAG       = 0x03,
	FUNC_RFE_CTRL   = 0x03,

	FUNC_BT_AOX     = 0x04,
#if IS_CUT_TEST(CONFIG_CHIP_VER)
	FUNC_TPIU       = 0x04,
#else
	FUNC_SDIO_HOST  = 0x04,
#endif

	FUNC_I2S        = 0x05,
	FUNC_SPI_M      = 0x05,

	FUNC_UART       = 0x06,
#if IS_CUT_TEST(CONFIG_CHIP_VER)
	FUNC_SDIO_HOST  = 0x06,
#else
	FUNC_TPIU       = 0x06,
#endif

	FUNC_BT_UART    = 0x07,
	FUNC_BT_GPIO    = 0x07,
	FUNC_BT_LOG     = 0x07,
	FUNC_BT_MP      = 0x07,
	FUNC_BT_JTAG    = 0x07,

	FUNC_SPI_S      = 0x08,
	FUNC_VOE_JTAG   = 0x08,

	FUNC_EXT_BT     = 0x09,

	FUNC_GPIO       = 0x0F,
	FUNC_DDR        = 0x0F
};

enum  peripheral_id_e {
	/* Peripheral function category = 0x00 */
	PID_COMP_ADC        = (FUNC_COMP_ADC << 28) + 2,
	PID_VP              = (FUNC_VP << 28) + 4,
	PID_USB             = (FUNC_USB << 28) + 6,
	PID_FLASH           = (FUNC_FLASH << 28) + 8,
	PID_MIPI            = (FUNC_MIPI << 28) + 10,
	PID_SENSOR          = (FUNC_SENSOR << 28) + 12,
	PID_I2C3            = (FUNC_I2C3 << 28) + 14,
	PID_RF_DBG          = (FUNC_RF_DBG << 28) + 16,
	PID_ADC0            = (FUNC_ADC << 28) + 18,
	PID_ADC1            = (PID_ADC0 + 1),
	PID_ADC2            = (PID_ADC0 + 2),
	PID_ADC3            = (PID_ADC0 + 3),
	PID_SD_HOST         = (FUNC_SD_HOST << 28) | (1 << 5),
#if !IS_CUT_TEST(CONFIG_CHIP_VER)
	PID_SPI2_1          = (FUNC_COMP_ADC << 28) | (1 << 6),
#endif
	/* Peripheral function category = 0x01 */
	PID_I2C0            = (FUNC_I2C << 28),
	PID_I2C1            = (PID_I2C0 + 1),
	PID_I2C2            = (PID_I2C0 + 2),
	PID_SIC             = (FUNC_SIC << 28) | (1 << 2),
	PID_DMIC            = (FUNC_DMIC << 28) | (1 << 4),
	PID_SGPIO           = (FUNC_SGPIO << 28) | (1 << 6),
#if !IS_CUT_TEST(CONFIG_CHIP_VER)
	PID_SPI2_2          = (FUNC_I2C << 28) | (1 << 8),
#endif
	/* Peripheral function category = 0x02 */
	PID_WLAN_LED        = (FUNC_WLAN_LED << 28),
	PID_WLAN_UART       = (FUNC_WLAN_UART << 28) | (1 << 2),
	PID_PWM0            = (FUNC_PWM << 28) | (1 << 4),
	PID_PWM1            = (PID_PWM0 + 1),
	PID_PWM2            = (PID_PWM0 + 2),
	PID_PWM3            = (PID_PWM0 + 3),
	PID_PWM4            = (PID_PWM0 + 4),
	PID_PWM5            = (PID_PWM0 + 5),
	PID_PWM6            = (PID_PWM0 + 6),
	PID_PWM7            = (PID_PWM0 + 7),
	PID_PWM8            = (PID_PWM0 + 8),
	PID_PWM9            = (PID_PWM0 + 9),
	PID_PWM10           = (PID_PWM0 + 10),
	PID_PWM11           = (PID_PWM0 + 11),
	/* Peripheral function category = 0x03 */
	PID_JTAG            = (FUNC_JTAG << 28),
	PID_RFE_CTRL        = (FUNC_RFE_CTRL << 28) | (1 << 2),
	/* Peripheral function category = 0x04 */
	PID_BT_AOX          = (FUNC_BT_AOX << 28),
#if IS_CUT_TEST(CONFIG_CHIP_VER)
	PID_TPIU            = (FUNC_TPIU << 28) | (1 << 2),
#else
	PID_SDIO_HOST       = (FUNC_SDIO_HOST << 28) | (1 << 2),
#endif
	/* Peripheral function category = 0x05 */
	PID_I2S0            = (FUNC_I2S << 28),
	PID_I2S1            = (PID_I2S0 + 1),
	PID_SPI0            = (FUNC_SPI_M << 28) | (1 << 2),
	PID_SPI1            = (PID_SPI0 + 1),
	/* Peripheral function category = 0x06 */
	PID_UART0           = (FUNC_UART << 28),
	PID_UART1           = (PID_UART0 + 1),
	PID_UART2           = (PID_UART0 + 2),
	PID_UART3           = (PID_UART0 + 3),
	PID_UART4           = (PID_UART0 + 4),  // BT UART
#if IS_CUT_TEST(CONFIG_CHIP_VER)
	PID_SDIO_HOST       = (FUNC_SDIO_HOST << 28) | (1 << 3),
#else
	PID_TPIU            = (FUNC_TPIU << 28) | (1 << 3),
#endif
	/* Peripheral function category = 0x07 */
	PID_BT_UART         = (FUNC_BT_UART << 28),
	PID_BT_GPIO         = (FUNC_BT_GPIO << 28) + 2,
	PID_BT_LOG          = (FUNC_BT_LOG << 28) + 4,
	PID_BT_MP_I2C       = (FUNC_BT_MP << 28) + 6,
	PID_BT_JTAG         = (FUNC_BT_JTAG << 28) + 8,
	/* Peripheral function category = 0x08 */
	PID_SPI2            = (FUNC_SPI_S << 28),
	PID_SPI3            = (PID_SPI2 + 1),
	PID_VOE_JTAG        = (FUNC_VOE_JTAG << 28) | (1 << 2),
	/* Peripheral function category = 0x09 */
	PID_EXT_BT          = (FUNC_EXT_BT << 28),
#if !IS_CUT_TEST(CONFIG_CHIP_VER)
	PID_SPI2_3          = (FUNC_EXT_BT << 28) | (1 << 2),
#endif
	/* Peripheral function category = 0x0F */
	PID_GPIO            = (FUNC_GPIO << 28),
	PID_DDR             = (FUNC_DDR << 28) | (1 << 2),


	PID_ERR           = 0xFFFFFFFF
};


typedef struct {
	uint32_t pin_name;
	uint32_t peripheral_id;
} hal_pin_map, *phal_pin_map;

#ifdef __cplusplus
}
#endif


#endif //_RTL8735B_PHERI_ID_H_

