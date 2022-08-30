#ifndef _RTL8735B_SYSON_TYPE_H_
#define _RTL8735B_SYSON_TYPE_H_
#include "platform_conf.h"

/**************************************************************************//**
 * @defgroup SYSON_REG_SYSON_GPIOB_0_1_CTRL
 * @brief                                            (@ 0X008)
 * @{
 *****************************************************************************/
#define SYSON_SHIFT_SYSON_GPIO1_SLEW_RATE            28
#define SYSON_BIT_SYSON_GPIO1_SLEW_RATE              ((u32)0x00000001 << 28)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO1_DRIVING              26
#define SYSON_MASK_SYSON_GPIO1_DRIVING               ((u32)0x00000003 << 26)                             /*!<R/W 0  0:4mA, 1:8mA */
#define SYSON_SHIFT_SYSON_GPIO1_SMT_EN               25
#define SYSON_BIT_SYSON_GPIO1_SMT_EN                 ((u32)0x00000001 << 25)                             /*!<R/W 0  Enable SYSON GPIO1 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO1_PULL_CTRL            22
#define SYSON_MASK_SYSON_GPIO1_PULL_CTRL             ((u32)0x00000003 << 22)                             /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO1_PINMUX_SEL           16
#define SYSON_MASK_SYSON_GPIO1_PINMUX_SEL            ((u32)0x0000000F << 16)                             /*!<R/W 1111  0000: USB_HSDM 0001: I2C0_SDA 0010: 0011: 0100: 0101: 0110: 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
#define SYSON_SHIFT_SYSON_GPIO0_SLEW_RATE            12
#define SYSON_BIT_SYSON_GPIO0_SLEW_RATE              ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO0_DRIVING              10
#define SYSON_MASK_SYSON_GPIO0_DRIVING               ((u32)0x00000003 << 10)                             /*!<R/W 0  0:4mA, 1:8mA */
#define SYSON_SHIFT_SYSON_GPIO0_SMT_EN               9
#define SYSON_BIT_SYSON_GPIO0_SMT_EN                 ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable SYSON GPIO0 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO0_PULL_CTRL            6
#define SYSON_MASK_SYSON_GPIO0_PULL_CTRL             ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO0_PINMUX_SEL           0
#define SYSON_MASK_SYSON_GPIO0_PINMUX_SEL            ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000: USB_HSDP 0001: I2C0_SCL 0010: 0011: 0100: 0101: 0110: 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_REG_SYSON_GPIOB_2_CTRL
 * @brief                                            (@ 0X00C)
 * @{
 *****************************************************************************/
#define SYSON_SHIFT_SYSON_GPIO2_SLEW_RATE            12
#define SYSON_BIT_SYSON_GPIO2_SLEW_RATE              ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO2_DRIVING              10
#define SYSON_MASK_SYSON_GPIO2_DRIVING               ((u32)0x00000003 << 10)                             /*!<R/W 0  0:4mA, 1:8mA */
#define SYSON_SHIFT_SYSON_GPIO2_SMT_EN               9
#define SYSON_BIT_SYSON_GPIO2_SMT_EN                 ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable SYSON GPIO2 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO2_PULL_CTRL            6
#define SYSON_MASK_SYSON_GPIO2_PULL_CTRL             ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO2_PINMUX_SEL           0
#define SYSON_MASK_SYSON_GPIO2_PINMUX_SEL            ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000: 0001: 0010: 0011: 0100: 0101: 0110: 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_REG_SYSON_GPIOC_0_1_CTRL
 * @brief                                            (@ 0X010)
 * @{
 *****************************************************************************/
#define SYSON_SHIFT_SYSON_GPIO1_SLEW_RATE            28
#define SYSON_BIT_SYSON_GPIO1_SLEW_RATE              ((u32)0x00000001 << 28)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO1_DRIVING              26
#define SYSON_MASK_SYSON_GPIO1_DRIVING               ((u32)0x00000003 << 26)                             /*!<R/W 0  0:4mA, 1:8mA */
#define SYSON_SHIFT_SYSON_GPIO1_SMT_EN               25
#define SYSON_BIT_SYSON_GPIO1_SMT_EN                 ((u32)0x00000001 << 25)                             /*!<R/W 0  Enable SYSON GPIO1 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO1_PULL_CTRL            22
#define SYSON_MASK_SYSON_GPIO1_PULL_CTRL             ((u32)0x00000003 << 22)                             /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO1_PINMUX_SEL           16
#define SYSON_MASK_SYSON_GPIO1_PINMUX_SEL            ((u32)0x0000000F << 16)                             /*!<R/W 1111  0000: SPI_M_DATA3 0001: 0010: 0011: 0100: 0101: 0110: 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
#define SYSON_SHIFT_SYSON_GPIO0_SLEW_RATE            12
#define SYSON_BIT_SYSON_GPIO0_SLEW_RATE              ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO0_DRIVING              10
#define SYSON_MASK_SYSON_GPIO0_DRIVING               ((u32)0x00000003 << 10)                             /*!<R/W 0  0:8mA, 1:16mA */
#define SYSON_SHIFT_SYSON_GPIO0_SMT_EN               9
#define SYSON_BIT_SYSON_GPIO0_SMT_EN                 ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable SYSON GPIO0 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO0_PULL_CTRL            6
#define SYSON_MASK_SYSON_GPIO0_PULL_CTRL             ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO0_PINMUX_SEL           0
#define SYSON_MASK_SYSON_GPIO0_PINMUX_SEL            ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000: SPI_M_CLK 0001: 0010: 0011: 0100: 0101: 0110: 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_REG_SYSON_GPIOC_2_3_CTRL
 * @brief                                            (@ 0X014)
 * @{
 *****************************************************************************/
#define SYSON_SHIFT_SYSON_GPIO3_SLEW_RATE            28
#define SYSON_BIT_SYSON_GPIO3_SLEW_RATE              ((u32)0x00000001 << 28)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO3_DRIVING              26
#define SYSON_MASK_SYSON_GPIO3_DRIVING               ((u32)0x00000003 << 26)                             /*!<R/W 0  0:4mA, 1:8mA */
#define SYSON_SHIFT_SYSON_GPIO3_SMT_EN               25
#define SYSON_BIT_SYSON_GPIO3_SMT_EN                 ((u32)0x00000001 << 25)                             /*!<R/W 0  Enable SYSON GPIO3 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO3_PULL_CTRL            22
#define SYSON_MASK_SYSON_GPIO3_PULL_CTRL             ((u32)0x00000003 << 22)                             /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO3_PINMUX_SEL           16
#define SYSON_MASK_SYSON_GPIO3_PINMUX_SEL            ((u32)0x0000000F << 16)                             /*!<R/W 1111  0000: SPI_M_DATA2 0001: 0010: 0011: 0100: 0101: 0110: 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
#define SYSON_SHIFT_SYSON_GPIO2_SLEW_RATE            12
#define SYSON_BIT_SYSON_GPIO2_SLEW_RATE              ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO2_DRIVING              10
#define SYSON_MASK_SYSON_GPIO2_DRIVING               ((u32)0x00000003 << 10)                             /*!<R/W 0  0:4mA, 1:8mA */
#define SYSON_SHIFT_SYSON_GPIO2_SMT_EN               9
#define SYSON_BIT_SYSON_GPIO2_SMT_EN                 ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable SYSON GPIO2 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO2_PULL_CTRL            6
#define SYSON_MASK_SYSON_GPIO2_PULL_CTRL             ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO2_PINMUX_SEL           0
#define SYSON_MASK_SYSON_GPIO2_PINMUX_SEL            ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000: SPI_M_DATA0 0001: 0010: 0011: 0100: 0101: 0110: 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_REG_SYSON_GPIOC_4_5_CTRL
 * @brief                                            (@ 0X018)
 * @{
 *****************************************************************************/
#define SYSON_SHIFT_SYSON_GPIO5_SLEW_RATE            28
#define SYSON_BIT_SYSON_GPIO5_SLEW_RATE              ((u32)0x00000001 << 28)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO5_DRIVING              26
#define SYSON_MASK_SYSON_GPIO5_DRIVING               ((u32)0x00000003 << 26)                             /*!<R/W 0  0:4mA, 1:8mA */
#define SYSON_SHIFT_SYSON_GPIO5_SMT_EN               25
#define SYSON_BIT_SYSON_GPIO5_SMT_EN                 ((u32)0x00000001 << 25)                             /*!<R/W 0  Enable SYSON GPIO5 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO5_PULL_CTRL            22
#define SYSON_MASK_SYSON_GPIO5_PULL_CTRL             ((u32)0x00000003 << 22)                             /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO5_PINMUX_SEL           16
#define SYSON_MASK_SYSON_GPIO5_PINMUX_SEL            ((u32)0x0000000F << 16)                             /*!<R/W 1111  0000: SPI_M_CS 0001: 0010: 0011: 0100: 0101: 0110: 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
#define SYSON_SHIFT_SYSON_GPIO4_SLEW_RATE            12
#define SYSON_BIT_SYSON_GPIO4_SLEW_RATE              ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO4_DRIVING              10
#define SYSON_MASK_SYSON_GPIO4_DRIVING               ((u32)0x00000003 << 10)                             /*!<R/W 0  0:4mA, 1:8mA */
#define SYSON_SHIFT_SYSON_GPIO4_SMT_EN               9
#define SYSON_BIT_SYSON_GPIO4_SMT_EN                 ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable SYSON GPIO4 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO4_PULL_CTRL            6
#define SYSON_MASK_SYSON_GPIO4_PULL_CTRL             ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO4_PINMUX_SEL           0
#define SYSON_MASK_SYSON_GPIO4_PINMUX_SEL            ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000: SPI_M_DATA1 0001: 0010: 0011: 0100: 0101: 0110: 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_REG_SYSON_GPIOD_0_1_CTRL
 * @brief                                            (@ 0X01C)
 * @{
 *****************************************************************************/
#define SYSON_SHIFT_SYSON_GPIO1_SLEW_RATE            28
#define SYSON_BIT_SYSON_GPIO1_SLEW_RATE              ((u32)0x00000001 << 28)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO1_DRIVING              26
#define SYSON_MASK_SYSON_GPIO1_DRIVING               ((u32)0x00000003 << 26)                             /*!<R/W 0  Wait for pad type */
#define SYSON_SHIFT_SYSON_GPIO1_SMT_EN               25
#define SYSON_BIT_SYSON_GPIO1_SMT_EN                 ((u32)0x00000001 << 25)                             /*!<R/W 0  Enable SYSON GPIO1 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO1_PULL_CTRL            22
#define SYSON_MASK_SYSON_GPIO1_PULL_CTRL             ((u32)0x00000003 << 22)                             /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO1_PINMUX_SEL           16
#define SYSON_MASK_SYSON_GPIO1_PINMUX_SEL            ((u32)0x0000000F << 16)                             /*!<R/W 1111  0000: MIPI_DATA0_N 0001: 0010: 0011: 0100: 0101: 0110: 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
#define SYSON_SHIFT_SYSON_GPIO0_SLEW_RATE            12
#define SYSON_BIT_SYSON_GPIO0_SLEW_RATE              ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO0_DRIVING              10
#define SYSON_MASK_SYSON_GPIO0_DRIVING               ((u32)0x00000003 << 10)                             /*!<R/W 0  Wait for pad type */
#define SYSON_SHIFT_SYSON_GPIO0_SMT_EN               9
#define SYSON_BIT_SYSON_GPIO0_SMT_EN                 ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable SYSON GPIO0 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO0_PULL_CTRL            6
#define SYSON_MASK_SYSON_GPIO0_PULL_CTRL             ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO0_PINMUX_SEL           0
#define SYSON_MASK_SYSON_GPIO0_PINMUX_SEL            ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000: MIPI_DATA0_P 0001: 0010: 0011: 0100: 0101: 0110: 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_REG_SYSON_GPIOD_2_3_CTRL
 * @brief                                            (@ 0X020)
 * @{
 *****************************************************************************/
#define SYSON_SHIFT_SYSON_GPIO3_SLEW_RATE            28
#define SYSON_BIT_SYSON_GPIO3_SLEW_RATE              ((u32)0x00000001 << 28)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO3_DRIVING              26
#define SYSON_MASK_SYSON_GPIO3_DRIVING               ((u32)0x00000003 << 26)                             /*!<R/W 0  Wait for pad type */
#define SYSON_SHIFT_SYSON_GPIO3_SMT_EN               25
#define SYSON_BIT_SYSON_GPIO3_SMT_EN                 ((u32)0x00000001 << 25)                             /*!<R/W 0  Enable SYSON GPIO3 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO3_PULL_CTRL            22
#define SYSON_MASK_SYSON_GPIO3_PULL_CTRL             ((u32)0x00000003 << 22)                             /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO3_PINMUX_SEL           16
#define SYSON_MASK_SYSON_GPIO3_PINMUX_SEL            ((u32)0x0000000F << 16)                             /*!<R/W 1111  0000: MIPI_DATA1_N 0001: 0010: 0011: 0100: 0101: 0110: 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
#define SYSON_SHIFT_SYSON_GPIO2_SLEW_RATE            12
#define SYSON_BIT_SYSON_GPIO2_SLEW_RATE              ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO2_DRIVING              10
#define SYSON_MASK_SYSON_GPIO2_DRIVING               ((u32)0x00000003 << 10)                             /*!<R/W 0  Wait for pad type */
#define SYSON_SHIFT_SYSON_GPIO2_SMT_EN               9
#define SYSON_BIT_SYSON_GPIO2_SMT_EN                 ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable SYSON GPIO2 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO2_PULL_CTRL            6
#define SYSON_MASK_SYSON_GPIO2_PULL_CTRL             ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO2_PINMUX_SEL           0
#define SYSON_MASK_SYSON_GPIO2_PINMUX_SEL            ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000: MIPI_DATA1_P 0001: 0010: 0011: 0100: 0101: 0110: 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_REG_SYSON_GPIOD_4_5_CTRL
 * @brief                                            (@ 0X024)
 * @{
 *****************************************************************************/
#define SYSON_SHIFT_SYSON_GPIO5_SLEW_RATE            28
#define SYSON_BIT_SYSON_GPIO5_SLEW_RATE              ((u32)0x00000001 << 28)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO5_DRIVING              26
#define SYSON_MASK_SYSON_GPIO5_DRIVING               ((u32)0x00000003 << 26)                             /*!<R/W 0  Wait for pad type */
#define SYSON_SHIFT_SYSON_GPIO5_SMT_EN               25
#define SYSON_BIT_SYSON_GPIO5_SMT_EN                 ((u32)0x00000001 << 25)                             /*!<R/W 0  Enable SYSON GPIO5 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO5_PULL_CTRL            22
#define SYSON_MASK_SYSON_GPIO5_PULL_CTRL             ((u32)0x00000003 << 22)                             /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO5_PINMUX_SEL           16
#define SYSON_MASK_SYSON_GPIO5_PINMUX_SEL            ((u32)0x0000000F << 16)                             /*!<R/W 1111  0000: MIPI_CKI_N 0001: 0010: 0011: 0100: 0101: 0110: 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
#define SYSON_SHIFT_SYSON_GPIO4_SLEW_RATE            12
#define SYSON_BIT_SYSON_GPIO4_SLEW_RATE              ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO4_DRIVING              10
#define SYSON_MASK_SYSON_GPIO4_DRIVING               ((u32)0x00000003 << 10)                             /*!<R/W 0  Wait for pad type */
#define SYSON_SHIFT_SYSON_GPIO4_SMT_EN               9
#define SYSON_BIT_SYSON_GPIO4_SMT_EN                 ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable SYSON GPIO4 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO4_PULL_CTRL            6
#define SYSON_MASK_SYSON_GPIO4_PULL_CTRL             ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO4_PINMUX_SEL           0
#define SYSON_MASK_SYSON_GPIO4_PINMUX_SEL            ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000: MIPI_CKI_P 0001: 0010: 0011: 0100: 0101: 0110: 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_REG_SYSON_GPIOD_6_7_CTRL
 * @brief                                            (@ 0X028)
 * @{
 *****************************************************************************/
#define SYSON_SHIFT_SYSON_GPIO7_SLEW_RATE            28
#define SYSON_BIT_SYSON_GPIO7_SLEW_RATE              ((u32)0x00000001 << 28)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO7_DRIVING              26
#define SYSON_MASK_SYSON_GPIO7_DRIVING               ((u32)0x00000003 << 26)                             /*!<R/W 0  Wait for pad type */
#define SYSON_SHIFT_SYSON_GPIO7_SMT_EN               25
#define SYSON_BIT_SYSON_GPIO7_SMT_EN                 ((u32)0x00000001 << 25)                             /*!<R/W 0  Enable SYSON GPIO7 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO7_PULL_CTRL            22
#define SYSON_MASK_SYSON_GPIO7_PULL_CTRL             ((u32)0x00000003 << 22)                             /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO7_PINMUX_SEL           16
#define SYSON_MASK_SYSON_GPIO7_PINMUX_SEL            ((u32)0x0000000F << 16)                             /*!<R/W 1111  0000: MIPI_DATA2_N 0001: 0010: 0011: 0100: 0101: 0110: 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
#define SYSON_SHIFT_SYSON_GPIO6_SLEW_RATE            12
#define SYSON_BIT_SYSON_GPIO6_SLEW_RATE              ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO6_DRIVING              10
#define SYSON_MASK_SYSON_GPIO6_DRIVING               ((u32)0x00000003 << 10)                             /*!<R/W 0  Wait for pad type */
#define SYSON_SHIFT_SYSON_GPIO6_SMT_EN               9
#define SYSON_BIT_SYSON_GPIO6_SMT_EN                 ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable SYSON GPIO6 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO6_PULL_CTRL            6
#define SYSON_MASK_SYSON_GPIO6_PULL_CTRL             ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO6_PINMUX_SEL           0
#define SYSON_MASK_SYSON_GPIO6_PINMUX_SEL            ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000: MIPI_DATA2_P 0001: 0010: 0011: 0100: 0101: 0110: 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_REG_SYSON_GPIOD_8_9_CTRL
 * @brief                                            (@ 0X02C)
 * @{
 *****************************************************************************/
#define SYSON_SHIFT_SYSON_GPIO9_SLEW_RATE            28
#define SYSON_BIT_SYSON_GPIO9_SLEW_RATE              ((u32)0x00000001 << 28)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO9_DRIVING              26
#define SYSON_MASK_SYSON_GPIO9_DRIVING               ((u32)0x00000003 << 26)                             /*!<R/W 0  Wait for pad type */
#define SYSON_SHIFT_SYSON_GPIO9_SMT_EN               25
#define SYSON_BIT_SYSON_GPIO9_SMT_EN                 ((u32)0x00000001 << 25)                             /*!<R/W 0  Enable SYSON GPIO9 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO9_PULL_CTRL            22
#define SYSON_MASK_SYSON_GPIO9_PULL_CTRL             ((u32)0x00000003 << 22)                             /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO9_PINMUX_SEL           16
#define SYSON_MASK_SYSON_GPIO9_PINMUX_SEL            ((u32)0x0000000F << 16)                             /*!<R/W 1111  0000: MIPI_DATA3_N 0001: 0010: 0011: 0100: 0101: 0110: 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
#define SYSON_SHIFT_SYSON_GPIO8_SLEW_RATE            12
#define SYSON_BIT_SYSON_GPIO8_SLEW_RATE              ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO8_DRIVING              10
#define SYSON_MASK_SYSON_GPIO8_DRIVING               ((u32)0x00000003 << 10)                             /*!<R/W 0  Wait for pad type */
#define SYSON_SHIFT_SYSON_GPIO8_SMT_EN               9
#define SYSON_BIT_SYSON_GPIO8_SMT_EN                 ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable SYSON GPIO8 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO8_PULL_CTRL            6
#define SYSON_MASK_SYSON_GPIO8_PULL_CTRL             ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO8_PINMUX_SEL           0
#define SYSON_MASK_SYSON_GPIO8_PINMUX_SEL            ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000: MIPI_DATA3_P 0001: 0010: 0011: 0100: 0101: 0110: 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_REG_SYSON_GPIOD_10_11_CTRL
 * @brief                                            (@ 0X030)
 * @{
 *****************************************************************************/
#define SYSON_SHIFT_SYSON_GPIO11_SLEW_RATE           28
#define SYSON_BIT_SYSON_GPIO11_SLEW_RATE             ((u32)0x00000001 << 28)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO11_DRIVING             26
#define SYSON_MASK_SYSON_GPIO11_DRIVING              ((u32)0x00000003 << 26)                             /*!<R/W 0  0:4mA, 1:8mA */
#define SYSON_SHIFT_SYSON_GPIO11_SMT_EN              25
#define SYSON_BIT_SYSON_GPIO11_SMT_EN                ((u32)0x00000001 << 25)                             /*!<R/W 0  Enable SYSON GPIO11 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO11_PULL_CTRL           22
#define SYSON_MASK_SYSON_GPIO11_PULL_CTRL            ((u32)0x00000003 << 22)                             /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO11_PINMUX_SEL          16
#define SYSON_MASK_SYSON_GPIO11_PINMUX_SEL           ((u32)0x0000000F << 16)                             /*!<R/W 1111  0000: 0001: 0010: 0011: 0100: 0101: 0110: 0111: BT_GPIO3 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
#define SYSON_SHIFT_SYSON_GPIO10_SLEW_RATE           12
#define SYSON_BIT_SYSON_GPIO10_SLEW_RATE             ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO10_DRIVING             10
#define SYSON_MASK_SYSON_GPIO10_DRIVING              ((u32)0x00000003 << 10)                             /*!<R/W 0  0:8mA, 1:16mA */
#define SYSON_SHIFT_SYSON_GPIO10_SMT_EN              9
#define SYSON_BIT_SYSON_GPIO10_SMT_EN                ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable SYSON GPIO10 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO10_PULL_CTRL           6
#define SYSON_MASK_SYSON_GPIO10_PULL_CTRL            ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO10_PINMUX_SEL          0
#define SYSON_MASK_SYSON_GPIO10_PINMUX_SEL           ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000: I2C3_SDA 0001: 0010: 0011: 0100: 0101: 0110: 0111: BT_UART_OUT 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_REG_SYSON_GPIOD_12_13_CTRL
 * @brief                                            (@ 0X034)
 * @{
 *****************************************************************************/
#define SYSON_SHIFT_SYSON_GPIO13_SLEW_RATE           28
#define SYSON_BIT_SYSON_GPIO13_SLEW_RATE             ((u32)0x00000001 << 28)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO13_DRIVING             26
#define SYSON_MASK_SYSON_GPIO13_DRIVING              ((u32)0x00000003 << 26)                             /*!<R/W 0  0:4mA, 1:8mA */
#define SYSON_SHIFT_SYSON_GPIO13_SMT_EN              25
#define SYSON_BIT_SYSON_GPIO13_SMT_EN                ((u32)0x00000001 << 25)                             /*!<R/W 0  Enable SYSON GPIO13 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO13_PULL_CTRL           22
#define SYSON_MASK_SYSON_GPIO13_PULL_CTRL            ((u32)0x00000003 << 22)                             /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO13_PINMUX_SEL          16
#define SYSON_MASK_SYSON_GPIO13_PINMUX_SEL           ((u32)0x0000000F << 16)                             /*!<R/W 1111  0000: SSOR_SYSCLK 0001: 0010: 0011: 0100: 0101: 0110: 0111: BT_LOG 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
#define SYSON_SHIFT_SYSON_GPIO12_SLEW_RATE           12
#define SYSON_BIT_SYSON_GPIO12_SLEW_RATE             ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO12_DRIVING             10
#define SYSON_MASK_SYSON_GPIO12_DRIVING              ((u32)0x00000003 << 10)                             /*!<R/W 0  0:4mA, 1:8mA */
#define SYSON_SHIFT_SYSON_GPIO12_SMT_EN              9
#define SYSON_BIT_SYSON_GPIO12_SMT_EN                ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable SYSON GPIO12 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO12_PULL_CTRL           6
#define SYSON_MASK_SYSON_GPIO12_PULL_CTRL            ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO12_PINMUX_SEL          0
#define SYSON_MASK_SYSON_GPIO12_PINMUX_SEL           ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000: I2C3_SCL 0001: 0010: 0011: 0100: 0101: 0110: 0111: BT_UART_IN 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_REG_SYSON_GPIOD_14_15_CTRL
 * @brief                                            (@ 0X038)
 * @{
 *****************************************************************************/
#define SYSON_SHIFT_SYSON_GPIO15_SLEW_RATE           28
#define SYSON_BIT_SYSON_GPIO15_SLEW_RATE             ((u32)0x00000001 << 28)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO15_DRIVING             26
#define SYSON_MASK_SYSON_GPIO15_DRIVING              ((u32)0x00000003 << 26)                             /*!<R/W 0  0:4mA, 1:8mA */
#define SYSON_SHIFT_SYSON_GPIO15_SMT_EN              25
#define SYSON_BIT_SYSON_GPIO15_SMT_EN                ((u32)0x00000001 << 25)                             /*!<R/W 0  Enable SYSON GPIO15 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO15_PULL_CTRL           22
#define SYSON_MASK_SYSON_GPIO15_PULL_CTRL            ((u32)0x00000003 << 22)                             /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO15_PINMUX_SEL          16
#define SYSON_MASK_SYSON_GPIO15_PINMUX_SEL           ((u32)0x0000000F << 16)                             /*!<R/W 1111  0000: 0001: 0010: 0011: 0100:BT_AOX_0 0101:I2S1_SD_TX0 0110:UART2_OUT 0111: BT_UART_OUT 1000: 1001: BT_STA 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
#define SYSON_SHIFT_SYSON_GPIO14_SLEW_RATE           12
#define SYSON_BIT_SYSON_GPIO14_SLEW_RATE             ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO14_DRIVING             10
#define SYSON_MASK_SYSON_GPIO14_DRIVING              ((u32)0x00000003 << 10)                             /*!<R/W 0  0:4mA, 1:8mA */
#define SYSON_SHIFT_SYSON_GPIO14_SMT_EN              9
#define SYSON_BIT_SYSON_GPIO14_SMT_EN                ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable SYSON GPIO14 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO14_PULL_CTRL           6
#define SYSON_MASK_SYSON_GPIO14_PULL_CTRL            ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO14_PINMUX_SEL          0
#define SYSON_MASK_SYSON_GPIO14_PINMUX_SEL           ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000: 0001: DMIC_CLK 0010: WIFI_LED 0011: 0100: 0101: I2S1_CLK 0110: 0111: BT_UART_IN 1000: 1001: BT_PRI 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_REG_SYSON_GPIOD_16_17_CTRL
 * @brief                                            (@ 0X03C)
 * @{
 *****************************************************************************/
#define SYSON_SHIFT_SYSON_GPIO17_SLEW_RATE           28
#define SYSON_BIT_SYSON_GPIO17_SLEW_RATE             ((u32)0x00000001 << 28)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO17_DRIVING             26
#define SYSON_MASK_SYSON_GPIO17_DRIVING              ((u32)0x00000003 << 26)                             /*!<R/W 0  0:4mA, 1:8mA */
#define SYSON_SHIFT_SYSON_GPIO17_SMT_EN              25
#define SYSON_BIT_SYSON_GPIO17_SMT_EN                ((u32)0x00000001 << 25)                             /*!<R/W 0  Enable SYSON GPIO17 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO17_PULL_CTRL           22
#define SYSON_MASK_SYSON_GPIO17_PULL_CTRL            ((u32)0x00000003 << 22)                             /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO17_PINMUX_SEL          16
#define SYSON_MASK_SYSON_GPIO17_PINMUX_SEL           ((u32)0x0000000F << 16)                             /*!<R/W 1111  0000: 0001: 0010: 0011:RFE_CTRL_4 0100:BT_AOX_2 0101:I2S1_WS 0110:UART2_CTS 0111: BT_MP_I2C_SCL 1000: 1001: WL_ACT 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
#define SYSON_SHIFT_SYSON_GPIO16_SLEW_RATE           12
#define SYSON_BIT_SYSON_GPIO16_SLEW_RATE             ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO16_DRIVING             10
#define SYSON_MASK_SYSON_GPIO16_DRIVING              ((u32)0x00000003 << 10)                             /*!<R/W 0  0:4mA, 1:8mA */
#define SYSON_SHIFT_SYSON_GPIO16_SMT_EN              9
#define SYSON_BIT_SYSON_GPIO16_SMT_EN                ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable SYSON GPIO16 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO16_PULL_CTRL           6
#define SYSON_MASK_SYSON_GPIO16_PULL_CTRL            ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO16_PINMUX_SEL          0
#define SYSON_MASK_SYSON_GPIO16_PINMUX_SEL           ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000: 0001:DMIC_CLK 0010: 0011: 0100:BT_AOX_1 0101:I2S1_MCK 0110:UART2_IN 0111: BT_GPIO4 1000: 1001: BT_CK 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */

#if IS_CUT_TEST(CONFIG_CHIP_VER)
/**************************************************************************//**
 * @defgroup SYSON_REG_SYSON_GPIOE_0_1_CTRL
 * @brief                                            (@ 0X040)
 * @{
 *****************************************************************************/
#define SYSON_SHIFT_SYSON_GPIO1_SLEW_RATE            28
#define SYSON_BIT_SYSON_GPIO1_SLEW_RATE              ((u32)0x00000001 << 28)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO1_DRIVING              26
#define SYSON_MASK_SYSON_GPIO1_DRIVING               ((u32)0x00000003 << 26)                             /*!<R/W 0  0:4mA, 1:8mA */
#define SYSON_SHIFT_SYSON_GPIO1_SMT_EN               25
#define SYSON_BIT_SYSON_GPIO1_SMT_EN                 ((u32)0x00000001 << 25)                             /*!<R/W 0  Enable SYSON GPIO1 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO1_PULL_CTRL            22
#define SYSON_MASK_SYSON_GPIO1_PULL_CTRL             ((u32)0x00000003 << 22)                             /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO1_PINMUX_SEL           16
#define SYSON_MASK_SYSON_GPIO1_PINMUX_SEL            ((u32)0x0000000F << 16)                             /*!<R/W 1111  0000: 0001: 0010: 0011: 0100:BT_AOX_0 0101:I2S1_SD_TX0 0110:UART2_OUT 0111: BT_UART_OUT 1000: 1001: BT_STA 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
#define SYSON_SHIFT_SYSON_GPIO0_SLEW_RATE            12
#define SYSON_BIT_SYSON_GPIO0_SLEW_RATE              ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO0_DRIVING              10
#define SYSON_MASK_SYSON_GPIO0_DRIVING               ((u32)0x00000003 << 10)                             /*!<R/W 0  0:4mA, 1:8mA */
#define SYSON_SHIFT_SYSON_GPIO0_SMT_EN               9
#define SYSON_BIT_SYSON_GPIO0_SMT_EN                 ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable SYSON GPIO0 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO0_PULL_CTRL            6
#define SYSON_MASK_SYSON_GPIO0_PULL_CTRL             ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO0_PINMUX_SEL           0
#define SYSON_MASK_SYSON_GPIO0_PINMUX_SEL            ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000: 0001: DMIC_CLK 0010: 0011: 0100: 0101:I2S1_CLK 0110: 0111: BT_UART_IN 1000: 1001: BT_PRI 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_REG_SYSON_GPIOE_2_3_CTRL
 * @brief                                            (@ 0X044)
 * @{
 *****************************************************************************/
#define SYSON_SHIFT_SYSON_GPIO3_SLEW_RATE            28
#define SYSON_BIT_SYSON_GPIO3_SLEW_RATE              ((u32)0x00000001 << 28)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO3_DRIVING              26
#define SYSON_MASK_SYSON_GPIO3_DRIVING               ((u32)0x00000003 << 26)                             /*!<R/W 0  0:4mA, 1:8mA */
#define SYSON_SHIFT_SYSON_GPIO3_SMT_EN               25
#define SYSON_BIT_SYSON_GPIO3_SMT_EN                 ((u32)0x00000001 << 25)                             /*!<R/W 0  Enable SYSON GPIO3 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO3_PULL_CTRL            22
#define SYSON_MASK_SYSON_GPIO3_PULL_CTRL             ((u32)0x00000003 << 22)                             /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO3_PINMUX_SEL           16
#define SYSON_MASK_SYSON_GPIO3_PINMUX_SEL            ((u32)0x0000000F << 16)                             /*!<R/W 1111  0000: 0001: 0010: WIFI_LED 0011:RFE_CTRL_5 0100:BT_AOX_2 0101:I2S1_WS 0110: UART2_CTS 0111: BT_MP_I2C_SCL 1000: 1001: WL_ACT 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
#define SYSON_SHIFT_SYSON_GPIO2_SLEW_RATE            12
#define SYSON_BIT_SYSON_GPIO2_SLEW_RATE              ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO2_DRIVING              10
#define SYSON_MASK_SYSON_GPIO2_DRIVING               ((u32)0x00000003 << 10)                             /*!<R/W 0  0:4mA, 1:8mA */
#define SYSON_SHIFT_SYSON_GPIO2_SMT_EN               9
#define SYSON_BIT_SYSON_GPIO2_SMT_EN                 ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable SYSON GPIO2 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO2_PULL_CTRL            6
#define SYSON_MASK_SYSON_GPIO2_PULL_CTRL             ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO2_PINMUX_SEL           0
#define SYSON_MASK_SYSON_GPIO2_PINMUX_SEL            ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000: 0001: DMIC_CLK 0010: 0011: 0100: BT_AOX_1 0101: I2S1_MCK 0110: UART2_IN 0111: BT_GPIO4 1000: 1001: BT_CK 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_REG_SYSON_GPIOE_4_5_CTRL
 * @brief                                            (@ 0X048)
 * @{
 *****************************************************************************/
#define SYSON_SHIFT_SYSON_GPIO5_SLEW_RATE            28
#define SYSON_BIT_SYSON_GPIO5_SLEW_RATE              ((u32)0x00000001 << 28)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO5_DRIVING              26
#define SYSON_MASK_SYSON_GPIO5_DRIVING               ((u32)0x00000003 << 26)                             /*!<R/W 0  0:4mA, 1:8mA */
#define SYSON_SHIFT_SYSON_GPIO5_SMT_EN               25
#define SYSON_BIT_SYSON_GPIO5_SMT_EN                 ((u32)0x00000001 << 25)                             /*!<R/W 0  Enable SYSON GPIO5 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO5_PULL_CTRL            22
#define SYSON_MASK_SYSON_GPIO5_PULL_CTRL             ((u32)0x00000003 << 22)                             /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO5_PINMUX_SEL           16
#define SYSON_MASK_SYSON_GPIO5_PINMUX_SEL            ((u32)0x0000000F << 16)                             /*!<R/W 1111  0000: 0001: 0010: WIFI_UART_OUT 0011: 0100:BT_AOX_0 0101:SPI_0_SCL 0110: UART3_OUT 0111: BT_UART_OUT 1000: SPI_2_SCL 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
#define SYSON_SHIFT_SYSON_GPIO4_SLEW_RATE            12
#define SYSON_BIT_SYSON_GPIO4_SLEW_RATE              ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO4_DRIVING              10
#define SYSON_MASK_SYSON_GPIO4_DRIVING               ((u32)0x00000003 << 10)                             /*!<R/W 0  0:4mA, 1:8mA */
#define SYSON_SHIFT_SYSON_GPIO4_SMT_EN               9
#define SYSON_BIT_SYSON_GPIO4_SMT_EN                 ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable SYSON GPIO4 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO4_PULL_CTRL            6
#define SYSON_MASK_SYSON_GPIO4_PULL_CTRL             ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO4_PINMUX_SEL           0
#define SYSON_MASK_SYSON_GPIO4_PINMUX_SEL            ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000: 0001: DMIC_DATA 0010: 0011:RFE_CTRL_3 0100:BT_AOX_3 0101:I2S1_SD_RX 0110: UART2_RTS 0111:BT_MP_I2C_SDA 1000: 1001: BTCMD_IRQ 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_REG_SYSON_GPIOE_6_7_CTRL
 * @brief                                            (@ 0X04C)
 * @{
 *****************************************************************************/
#define SYSON_SHIFT_SYSON_GPIO7_SLEW_RATE            28
#define SYSON_BIT_SYSON_GPIO7_SLEW_RATE              ((u32)0x00000001 << 28)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO7_DRIVING              26
#define SYSON_MASK_SYSON_GPIO7_DRIVING               ((u32)0x00000003 << 26)                             /*!<R/W 0  0:4mA, 1:8mA */
#define SYSON_SHIFT_SYSON_GPIO7_SMT_EN               25
#define SYSON_BIT_SYSON_GPIO7_SMT_EN                 ((u32)0x00000001 << 25)                             /*!<R/W 0  Enable SYSON GPIO7 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO7_PULL_CTRL            22
#define SYSON_MASK_SYSON_GPIO7_PULL_CTRL             ((u32)0x00000003 << 22)                             /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO7_PINMUX_SEL           16
#define SYSON_MASK_SYSON_GPIO7_PINMUX_SEL            ((u32)0x0000000F << 16)                             /*!<R/W 1111  0000: TRXIP 0001: I2C2_SCL 0010: 0011:RFE_CTRL_4 0100:BT_AOX_2 0101:SPI_0_MISO 0110: UART3_RTS 0111: BT_UART_RTS 1000: SPI_2_MOSI 1001: BTCMD_I2C_CK 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
#define SYSON_SHIFT_SYSON_GPIO6_SLEW_RATE            12
#define SYSON_BIT_SYSON_GPIO6_SLEW_RATE              ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO6_DRIVING              10
#define SYSON_MASK_SYSON_GPIO6_DRIVING               ((u32)0x00000003 << 10)                             /*!<R/W 0  0:4mA, 1:8mA */
#define SYSON_SHIFT_SYSON_GPIO6_SMT_EN               9
#define SYSON_BIT_SYSON_GPIO6_SMT_EN                 ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable SYSON GPIO6 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO6_PULL_CTRL            6
#define SYSON_MASK_SYSON_GPIO6_PULL_CTRL             ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO6_PINMUX_SEL           0
#define SYSON_MASK_SYSON_GPIO6_PINMUX_SEL            ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000: 0001: 0010: WIFI_UART_IN 0011: 0100:BT_AOX_1 0101:SPI_0_MOSI 0110: UART3_IN 0111: BT_UART_IN 1000:SPI_2_MISO 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_REG_SYSON_GPIOE_8_9_CTRL
 * @brief                                            (@ 0X050)
 * @{
 *****************************************************************************/
#define SYSON_SHIFT_SYSON_GPIO9_SLEW_RATE            28
#define SYSON_BIT_SYSON_GPIO9_SLEW_RATE              ((u32)0x00000001 << 28)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO9_DRIVING              26
#define SYSON_MASK_SYSON_GPIO9_DRIVING               ((u32)0x00000003 << 26)                             /*!<R/W 0  0:4mA, 1:8mA */
#define SYSON_SHIFT_SYSON_GPIO9_SMT_EN               25
#define SYSON_BIT_SYSON_GPIO9_SMT_EN                 ((u32)0x00000001 << 25)                             /*!<R/W 0  Enable SYSON GPIO9 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO9_PULL_CTRL            22
#define SYSON_MASK_SYSON_GPIO9_PULL_CTRL             ((u32)0x00000003 << 22)                             /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO9_PINMUX_SEL           16
#define SYSON_MASK_SYSON_GPIO9_PINMUX_SEL            ((u32)0x0000000F << 16)                             /*!<R/W 1111  0000: TRXQP 0001: I2C2_SCL 0010: 0011: 0100: 0101:SPI_0_CS1 0110: 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
#define SYSON_SHIFT_SYSON_GPIO8_SLEW_RATE            12
#define SYSON_BIT_SYSON_GPIO8_SLEW_RATE              ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO8_DRIVING              10
#define SYSON_MASK_SYSON_GPIO8_DRIVING               ((u32)0x00000003 << 10)                             /*!<R/W 0  0:4mA, 1:8mA */
#define SYSON_SHIFT_SYSON_GPIO8_SMT_EN               9
#define SYSON_BIT_SYSON_GPIO8_SMT_EN                 ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable SYSON GPIO8 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO8_PULL_CTRL            6
#define SYSON_MASK_SYSON_GPIO8_PULL_CTRL             ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO8_PINMUX_SEL           0
#define SYSON_MASK_SYSON_GPIO8_PINMUX_SEL            ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000: TRXIN 0001: I2C2_SDA 0010: 0011:RFE_CTRL_5 0100:BT_AOX_3 0101:SPI_0_CS0 0110: UART3_CTS 0111: BT_UART_CTS 1000: SPI_2_CS 1001: BTCMC_I2C_DD 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_REG_SYSON_GPIOE_10_CTRL
 * @brief                                            (@ 0X054)
 * @{
 *****************************************************************************/
#define SYSON_SHIFT_SYSON_GPIO10_SLEW_RATE           12
#define SYSON_BIT_SYSON_GPIO10_SLEW_RATE             ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO10_DRIVING             10
#define SYSON_MASK_SYSON_GPIO10_DRIVING              ((u32)0x00000003 << 10)                             /*!<R/W 0  0:4mA, 1:8mA */
#define SYSON_SHIFT_SYSON_GPIO10_SMT_EN              9
#define SYSON_BIT_SYSON_GPIO10_SMT_EN                ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable SYSON GPIO10 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO10_PULL_CTRL           6
#define SYSON_MASK_SYSON_GPIO10_PULL_CTRL            ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO10_PINMUX_SEL          0
#define SYSON_MASK_SYSON_GPIO10_PINMUX_SEL           ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000: TRXQN 0001: I2C2_SDA 0010: 0011: 0100: 0101:SPI_0_CS2 0110: 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */
#else
/**************************************************************************//**
 * @defgroup SYSON_REG_SYSON_GPIOD_18_19_CTRL
 * @brief                                            (@ 0X040)
 * @{
 *****************************************************************************/
#define SYSON_SHIFT_SYSON_GPIO19_SLEW_RATE           28
#define SYSON_BIT_SYSON_GPIO19_SLEW_RATE             ((u32)0x00000001 << 28)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO19_DRIVING             26
#define SYSON_MASK_SYSON_GPIO19_DRIVING              ((u32)0x00000003 << 26)                             /*!<R/W 0  0:4mA, 1:8mA */
#define SYSON_SHIFT_SYSON_GPIO19_SMT_EN              25
#define SYSON_BIT_SYSON_GPIO19_SMT_EN                ((u32)0x00000001 << 25)                             /*!<R/W 0  Enable SYSON GPIO19 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO19_PULL_CTRL           22
#define SYSON_MASK_SYSON_GPIO19_PULL_CTRL            ((u32)0x00000003 << 22)                             /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO19_PINMUX_SEL          16
#define SYSON_MASK_SYSON_GPIO19_PINMUX_SEL           ((u32)0x0000000F << 16)                             /*!<R/W 1111  0000: 0001: I2C1_SCL 0010: 0011: RFE_CTRL_3 0100: 0101: 0110:UART2_OUT 0111: BT_LOG 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
#define SYSON_SHIFT_SYSON_GPIO18_SLEW_RATE           12
#define SYSON_BIT_SYSON_GPIO18_SLEW_RATE             ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO18_DRIVING             10
#define SYSON_MASK_SYSON_GPIO18_DRIVING              ((u32)0x00000003 << 10)                             /*!<R/W 0  0:4mA, 1:8mA */
#define SYSON_SHIFT_SYSON_GPIO18_SMT_EN              9
#define SYSON_BIT_SYSON_GPIO18_SMT_EN                ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable SYSON GPIO18 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO18_PULL_CTRL           6
#define SYSON_MASK_SYSON_GPIO18_PULL_CTRL            ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO18_PINMUX_SEL          0
#define SYSON_MASK_SYSON_GPIO18_PINMUX_SEL           ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000: 0001: DMIC_DATA 0010: 0011: RFE_CTRL_5 0100: BT_AOX_3 0101:I2S1_SD_RX 0110:UART2_RTS 0111: BT_MP_I2C_SDA 1000: 1001: BTCMD_IRQ 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_REG_SYSON_GPIOD_20_CTRL
 * @brief                                            (@ 0X044)
 * @{
 *****************************************************************************/
#define SYSON_SHIFT_SYSON_GPIO20_SLEW_RATE           12
#define SYSON_BIT_SYSON_GPIO20_SLEW_RATE             ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO20_DRIVING             10
#define SYSON_MASK_SYSON_GPIO20_DRIVING              ((u32)0x00000003 << 10)                             /*!<R/W 0  0:4mA, 1:8mA */
#define SYSON_SHIFT_SYSON_GPIO20_SMT_EN              9
#define SYSON_BIT_SYSON_GPIO20_SMT_EN                ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable SYSON GPIO20 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO20_PULL_CTRL           6
#define SYSON_MASK_SYSON_GPIO20_PULL_CTRL            ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO20_PINMUX_SEL          0
#define SYSON_MASK_SYSON_GPIO20_PINMUX_SEL           ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000: 0001: I2C1_SDA 0010: 0011: 0100: 0101: 0110: UART2_IN 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_REG_SYSON_GPIOE_0_1_CTRL
 * @brief                                            (@ 0X048)
 * @{
 *****************************************************************************/
#define SYSON_SHIFT_SYSON_GPIO1_SLEW_RATE            28
#define SYSON_BIT_SYSON_GPIO1_SLEW_RATE              ((u32)0x00000001 << 28)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO1_DRIVING              26
#define SYSON_MASK_SYSON_GPIO1_DRIVING               ((u32)0x00000003 << 26)                             /*!<R/W 0  Wait for pad type */
#define SYSON_SHIFT_SYSON_GPIO1_SMT_EN               25
#define SYSON_BIT_SYSON_GPIO1_SMT_EN                 ((u32)0x00000001 << 25)                             /*!<R/W 0  Enable SYSON GPIO1 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO1_PULL_CTRL            22
#define SYSON_MASK_SYSON_GPIO1_PULL_CTRL             ((u32)0x00000003 << 22)                             /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO1_PINMUX_SEL           16
#define SYSON_MASK_SYSON_GPIO1_PINMUX_SEL            ((u32)0x0000000F << 16)                             /*!<R/W 1111  0000: SPI_2_SCL 0001: SPI_2_SCL 0010: WIFI_UART_OUT 0011: 0100: BT_AOX_0 0101: SPI_0_SCL 0110:UART3_OUT 0111: BT_UART_OUT 1000:SPI_2_SCL 1001: SPI_2_SCL 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
#define SYSON_SHIFT_SYSON_GPIO0_SLEW_RATE            12
#define SYSON_BIT_SYSON_GPIO0_SLEW_RATE              ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO0_DRIVING              10
#define SYSON_MASK_SYSON_GPIO0_DRIVING               ((u32)0x00000003 << 10)                             /*!<R/W 0  Wait for pad type */
#define SYSON_SHIFT_SYSON_GPIO0_SMT_EN               9
#define SYSON_BIT_SYSON_GPIO0_SMT_EN                 ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable SYSON GPIO0 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO0_PULL_CTRL            6
#define SYSON_MASK_SYSON_GPIO0_PULL_CTRL             ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO0_PINMUX_SEL           0
#define SYSON_MASK_SYSON_GPIO0_PINMUX_SEL            ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000: 0001: 0010: WIFI_LED 0011: RFE_CTRL_3 0100: 0101: 0110: UART2_OUT 0111: BT_LOG 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_REG_SYSON_GPIOE_2_3_CTRL
 * @brief                                            (@ 0X04C)
 * @{
 *****************************************************************************/
#define SYSON_SHIFT_SYSON_GPIO3_SLEW_RATE            28
#define SYSON_BIT_SYSON_GPIO3_SLEW_RATE              ((u32)0x00000001 << 28)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO3_DRIVING              26
#define SYSON_MASK_SYSON_GPIO3_DRIVING               ((u32)0x00000003 << 26)                             /*!<R/W 0  Wait for pad type */
#define SYSON_SHIFT_SYSON_GPIO3_SMT_EN               25
#define SYSON_BIT_SYSON_GPIO3_SMT_EN                 ((u32)0x00000001 << 25)                             /*!<R/W 0  Enable SYSON GPIO3 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO3_PULL_CTRL            22
#define SYSON_MASK_SYSON_GPIO3_PULL_CTRL             ((u32)0x00000003 << 22)                             /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO3_PINMUX_SEL           16
#define SYSON_MASK_SYSON_GPIO3_PINMUX_SEL            ((u32)0x0000000F << 16)                             /*!<R/W 1111  0000: TRXIP 0001: I2C2_SCL 0010: 0011: RFE_CTRL_4 0100:BT_AOX_2 0101: SPI_0_MOSI 0110: UART3_RTS 0111: BT_UART_RTS 1000: SPI_2_MOSI 1001: BTCMD_I2C_CK 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
#define SYSON_SHIFT_SYSON_GPIO2_SLEW_RATE            12
#define SYSON_BIT_SYSON_GPIO2_SLEW_RATE              ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO2_DRIVING              10
#define SYSON_MASK_SYSON_GPIO2_DRIVING               ((u32)0x00000003 << 10)                             /*!<R/W 0  Wait for pad type */
#define SYSON_SHIFT_SYSON_GPIO2_SMT_EN               9
#define SYSON_BIT_SYSON_GPIO2_SMT_EN                 ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable SYSON GPIO2 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO2_PULL_CTRL            6
#define SYSON_MASK_SYSON_GPIO2_PULL_CTRL             ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO2_PINMUX_SEL           0
#define SYSON_MASK_SYSON_GPIO2_PINMUX_SEL            ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000: SPI_2_MISO 0001: SPI_2_MISO 0010: WIFI_UART_IN 0011: 0100:BT_AOX_1 0101: SPI_0_MISO 0110: UART3_IN 0111: BT_UART_IN 1000: SPI_2_MISO 1001: SPI_2_MISO 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_REG_SYSON_GPIOE_4_5_CTRL
 * @brief                                            (@ 0X050)
 * @{
 *****************************************************************************/
#define SYSON_SHIFT_SYSON_GPIO5_SLEW_RATE            28
#define SYSON_BIT_SYSON_GPIO5_SLEW_RATE              ((u32)0x00000001 << 28)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO5_DRIVING              26
#define SYSON_MASK_SYSON_GPIO5_DRIVING               ((u32)0x00000003 << 26)                             /*!<R/W 0  0:4mA, 1:8mA */
#define SYSON_SHIFT_SYSON_GPIO5_SMT_EN               25
#define SYSON_BIT_SYSON_GPIO5_SMT_EN                 ((u32)0x00000001 << 25)                             /*!<R/W 0  Enable SYSON GPIO5 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO5_PULL_CTRL            22
#define SYSON_MASK_SYSON_GPIO5_PULL_CTRL             ((u32)0x00000003 << 22)                             /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO5_PINMUX_SEL           16
#define SYSON_MASK_SYSON_GPIO5_PINMUX_SEL            ((u32)0x0000000F << 16)                             /*!<R/W 1111  0000:TRXQP 0001: I2C2_SCL 0010: 0011: 0100: 0101:SPI_0_CS1 0110: 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
#define SYSON_SHIFT_SYSON_GPIO4_SLEW_RATE            12
#define SYSON_BIT_SYSON_GPIO4_SLEW_RATE              ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO4_DRIVING              10
#define SYSON_MASK_SYSON_GPIO4_DRIVING               ((u32)0x00000003 << 10)                             /*!<R/W 0  0:4mA, 1:8mA */
#define SYSON_SHIFT_SYSON_GPIO4_SMT_EN               9
#define SYSON_BIT_SYSON_GPIO4_SMT_EN                 ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable SYSON GPIO4 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO4_PULL_CTRL            6
#define SYSON_MASK_SYSON_GPIO4_PULL_CTRL             ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO4_PINMUX_SEL           0
#define SYSON_MASK_SYSON_GPIO4_PINMUX_SEL            ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000: TRXIN 0001: I2C2_SDA 0010: 0011:RFE_CTRL_5 0100:BT_AOX_3 0101:SPI_0_CS0 0110: UART3_CTS 0111:BT_UART_CTS 1000:SPI_2_CS 1001: BTCMC_I2C_DD 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_REG_SYSON_GPIOE_6_CTRL
 * @brief                                            (@ 0X054)
 * @{
 *****************************************************************************/
#define SYSON_SHIFT_SYSON_GPIO6_SLEW_RATE            12
#define SYSON_BIT_SYSON_GPIO6_SLEW_RATE              ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO6_DRIVING              10
#define SYSON_MASK_SYSON_GPIO6_DRIVING               ((u32)0x00000003 << 10)                             /*!<R/W 0  0:4mA, 1:8mA */
#define SYSON_SHIFT_SYSON_GPIO6_SMT_EN               9
#define SYSON_BIT_SYSON_GPIO6_SMT_EN                 ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable SYSON GPIO6 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO6_PULL_CTRL            6
#define SYSON_MASK_SYSON_GPIO6_PULL_CTRL             ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO6_PINMUX_SEL           0
#define SYSON_MASK_SYSON_GPIO6_PINMUX_SEL            ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000:TRXQN 0001: I2C2_SDA 0010: 0011: 0100: 0101:SPI_0_CS2 0110: 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */
#endif

/**************************************************************************//**
 * @defgroup SYSON_REG_SYSON_GPIOS_0_1_CTRL
 * @brief                                            (@ 0X058)
 * @{
 *****************************************************************************/
#define SYSON_SHIFT_SYSON_GPIO1_SLEW_RATE            28
#define SYSON_BIT_SYSON_GPIO1_SLEW_RATE              ((u32)0x00000001 << 28)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO1_DRIVING              26
#define SYSON_MASK_SYSON_GPIO1_DRIVING               ((u32)0x00000003 << 26)                             /*!<R/W 0  0:4mA, 1:8mA */
#define SYSON_SHIFT_SYSON_GPIO1_SMT_EN               25
#define SYSON_BIT_SYSON_GPIO1_SMT_EN                 ((u32)0x00000001 << 25)                             /*!<R/W 0  Enable SYSON GPIO1 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO1_PULL_CTRL            22
#define SYSON_MASK_SYSON_GPIO1_PULL_CTRL             ((u32)0x00000003 << 22)                             /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO1_PINMUX_SEL           16
#define SYSON_MASK_SYSON_GPIO1_PINMUX_SEL            ((u32)0x0000000F << 16)                             /*!<R/W 1111  0000: SD_D1 0001: 0010: PWM8 0011: 0100: 0101: 0110: 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
#define SYSON_SHIFT_SYSON_GPIO0_SLEW_RATE            12
#define SYSON_BIT_SYSON_GPIO0_SLEW_RATE              ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO0_DRIVING              10
#define SYSON_MASK_SYSON_GPIO0_DRIVING               ((u32)0x00000003 << 10)                             /*!<R/W 0  0:8mA, 1:16mA */
#define SYSON_SHIFT_SYSON_GPIO0_SMT_EN               9
#define SYSON_BIT_SYSON_GPIO0_SMT_EN                 ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable SYSON GPIO0 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO0_PULL_CTRL            6
#define SYSON_MASK_SYSON_GPIO0_PULL_CTRL             ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO0_PINMUX_SEL           0
#define SYSON_MASK_SYSON_GPIO0_PINMUX_SEL            ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000: SD_CLK 0001: 0010: 0011: 0100: 0101: 0110: 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_REG_SYSON_GPIOS_2_3_CTRL
 * @brief                                            (@ 0X05C)
 * @{
 *****************************************************************************/
#define SYSON_SHIFT_SYSON_GPIO3_SLEW_RATE            28
#define SYSON_BIT_SYSON_GPIO3_SLEW_RATE              ((u32)0x00000001 << 28)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO3_DRIVING              26
#define SYSON_MASK_SYSON_GPIO3_DRIVING               ((u32)0x00000003 << 26)                             /*!<R/W 0  0:4mA, 1:8mA */
#define SYSON_SHIFT_SYSON_GPIO3_SMT_EN               25
#define SYSON_BIT_SYSON_GPIO3_SMT_EN                 ((u32)0x00000001 << 25)                             /*!<R/W 0  Enable SYSON GPIO3 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO3_PULL_CTRL            22
#define SYSON_MASK_SYSON_GPIO3_PULL_CTRL             ((u32)0x00000003 << 22)                             /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO3_PINMUX_SEL           16
#define SYSON_MASK_SYSON_GPIO3_PINMUX_SEL            ((u32)0x0000000F << 16)                             /*!<R/W 1111  0000: SD_CMD 0001: 0010: 0011: 0100: 0101: 0110: 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
#define SYSON_SHIFT_SYSON_GPIO2_SLEW_RATE            12
#define SYSON_BIT_SYSON_GPIO2_SLEW_RATE              ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO2_DRIVING              10
#define SYSON_MASK_SYSON_GPIO2_DRIVING               ((u32)0x00000003 << 10)                             /*!<R/W 0  0:4mA, 1:8mA */
#define SYSON_SHIFT_SYSON_GPIO2_SMT_EN               9
#define SYSON_BIT_SYSON_GPIO2_SMT_EN                 ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable SYSON GPIO2 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO2_PULL_CTRL            6
#define SYSON_MASK_SYSON_GPIO2_PULL_CTRL             ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO2_PINMUX_SEL           0
#define SYSON_MASK_SYSON_GPIO2_PINMUX_SEL            ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000: SD_D0 0001: 0010: 0011: 0100: 0101: 0110: 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_REG_SYSON_GPIOS_4_5_CTRL
 * @brief                                            (@ 0X060)
 * @{
 *****************************************************************************/
#define SYSON_SHIFT_SYSON_GPIO5_SLEW_RATE            28
#define SYSON_BIT_SYSON_GPIO5_SLEW_RATE              ((u32)0x00000001 << 28)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO5_DRIVING              26
#define SYSON_MASK_SYSON_GPIO5_DRIVING               ((u32)0x00000003 << 26)                             /*!<R/W 0  0:4mA, 1:8mA */
#define SYSON_SHIFT_SYSON_GPIO5_SMT_EN               25
#define SYSON_BIT_SYSON_GPIO5_SMT_EN                 ((u32)0x00000001 << 25)                             /*!<R/W 0  Enable SYSON GPIO5 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO5_PULL_CTRL            22
#define SYSON_MASK_SYSON_GPIO5_PULL_CTRL             ((u32)0x00000003 << 22)                             /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO5_PINMUX_SEL           16
#define SYSON_MASK_SYSON_GPIO5_PINMUX_SEL            ((u32)0x0000000F << 16)                             /*!<R/W 1111  0000: SD_D3 0001: 0010: PWM10 0011: 0100: 0101: 0110: 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
#define SYSON_SHIFT_SYSON_GPIO4_SLEW_RATE            12
#define SYSON_BIT_SYSON_GPIO4_SLEW_RATE              ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO4_DRIVING              10
#define SYSON_MASK_SYSON_GPIO4_DRIVING               ((u32)0x00000003 << 10)                             /*!<R/W 0  0:4mA, 1:8mA */
#define SYSON_SHIFT_SYSON_GPIO4_SMT_EN               9
#define SYSON_BIT_SYSON_GPIO4_SMT_EN                 ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable SYSON GPIO4 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO4_PULL_CTRL            6
#define SYSON_MASK_SYSON_GPIO4_PULL_CTRL             ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO4_PINMUX_SEL           0
#define SYSON_MASK_SYSON_GPIO4_PINMUX_SEL            ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000: SD_CD 0001: 0010:PWM9 0011: 0100: 0101: 0110: 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_REG_SYSON_GPIOS_6_CTRL
 * @brief                                            (@ 0X064)
 * @{
 *****************************************************************************/
#define SYSON_SHIFT_SYSON_GPIO6_SLEW_RATE            12
#define SYSON_BIT_SYSON_GPIO6_SLEW_RATE              ((u32)0x00000001 << 12)                             /*!<R/W 0  0:Disable,1:Enable */
#define SYSON_SHIFT_SYSON_GPIO6_DRIVING              10
#define SYSON_MASK_SYSON_GPIO6_DRIVING               ((u32)0x00000003 << 10)                             /*!<R/W 0  0:4mA, 1:8mA */
#define SYSON_SHIFT_SYSON_GPIO6_SMT_EN               9
#define SYSON_BIT_SYSON_GPIO6_SMT_EN                 ((u32)0x00000001 << 9)                              /*!<R/W 0  Enable SYSON GPIO6 Schmitt trigger; 1: enable */
#define SYSON_SHIFT_SYSON_GPIO6_PULL_CTRL            6
#define SYSON_MASK_SYSON_GPIO6_PULL_CTRL             ((u32)0x00000003 << 6)                              /*!<R/W 0  2b'00: high impedence; 2b'01: pull low; 2b'10: pull high; 2b'11: reserved */
#define SYSON_SHIFT_SYSON_GPIO6_PINMUX_SEL           0
#define SYSON_MASK_SYSON_GPIO6_PINMUX_SEL            ((u32)0x0000000F << 0)                              /*!<R/W 1111  0000: SD_D2 0001: 0010: PWM11 0011: 0100: 0101: 0110: 0111: 1000: 1001: 1010: 1011: 1100: 1101: 1110: 1111: GPIO */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_REG_OTP_AS_CTRL_NS
 * @brief                                            (@ 0X068)
 * @{
 *****************************************************************************/
#define SYSON_SHIFT_OTP_MODE_SEL                     30
#define SYSON_MASK_OTP_MODE_SEL                      ((u32)0x00000003 << 30)                             /*!<R/W 0  OTP controller Mode (command) selection Program to this field could trigger OTP controller to do related command operation. 2'b00 :Read 2'b10 :Write 2'b01 :Autoload Enable 2'b11 :Compare Secure Data Enable */
#define SYSON_SHIFT_OTP_RDY                          29
#define SYSON_BIT_OTP_RDY                            ((u32)0x00000001 << 29)                             /*!<R/W1C 0  OTP Operation Ready bit 0: OTP controller has NOT done a requested command. 1: OTP controller has done a requested command. Note : HW set , SW clear Note before any operations, HW/SW should clear ready bit first Note: For autoload operation, this bit is not used for autoload done status. Autoload done status of each zone is shown in 0x40009128[6:4] */
#define SYSON_SHIFT_OTP_COMP_RESULT                  28
#define SYSON_BIT_OTP_COMP_RESULT                    ((u32)0x00000001 << 28)                             /*!<R/W1C 0  compare result 0 : PASS 1 : FAIL Note : HW set , SW clear */
#define SYSON_SHIFT_OTP_OP_EN                        27
#define SYSON_BIT_OTP_OP_EN                          ((u32)0x00000001 << 27)                             /*!<W1Once 0  OTP controller operation enable control This bit could be set to 1 by software and automatically cleared to 0 by hardware 0: OTP controller does NOT perforam any operations even B_OTP_MODE_SEL is given by a valid value. 1: OTP controller performs corresponding operation according to B_OTP_MODE_SEL, B_OTP_ADDR and B_OTP_DATA */
#define SYSON_SHIFT_OTP_ADDR                         16
#define SYSON_MASK_OTP_ADDR                          ((u32)0x000007FF << 16)                             /*!<R/W 0  Access Address */
#define SYSON_SHIFT_RSVD1                            9
#define SYSON_MASK_RSVD1                             ((u32)0x0000007F << 9)                              /*!<R/W 0x00  Reserved */
#define SYSON_SHIFT_OTP_AUTO_RDCHK_CTRL              8
#define SYSON_BIT_OTP_AUTO_RDCHK_CTRL                ((u32)0x00000001 << 8)                              /*!<R/W 0  Automatic Read Check Control When this bit is set to 1 in OTP write mode, OTP controller would perform a write-read-check process automatically. Read back data would be compared with original write data and the result would be updated in bit28 of this register 0: Disable auto read check mechanism 1: Enable auto read check mechanism */
#define SYSON_SHIFT_OTP_DATA                         0
#define SYSON_MASK_OTP_DATA                          ((u32)0x000000FF << 0)                              /*!<R/W 0  Access Data [7:0] : Read / Write/Data to be compared */
/** @} */

/**************************************************************************//**
 * @defgroup SYSON_REG_SYS_JTAG_SWD_CTRL
 * @brief                                            (@ 0X070)
 * @{
 *****************************************************************************/
#define SYSON_SHIFT_RM3_DBG_MD_SEL                   4
#define SYSON_BIT_RM3_DBG_MD_SEL                     ((u32)0x00000001 << 4)                              /*!<R/W 0  Real-M300 SWJ-DP Mode Selection 0:SWD-DP Mode 1:JTAG-DP Mode */
#define SYSON_SHIFT_RM3_DBG_PIN_EN                   3
#define SYSON_BIT_RM3_DBG_PIN_EN                     ((u32)0x00000001 << 3)                              /*!<R/W 0  Real-M300 SWJ-DP Pinmux Function Enable 0:SWD/JTAG Pin Disable 1:SWD/JTAG Pin Enable */
#define SYSON_SHIFT_DBG_CHAIN_EN                     2
#define SYSON_BIT_DBG_CHAIN_EN                       ((u32)0x00000001 << 2)                              /*!<R/W 0  Real-M500 and Real-M300 JTAG Chain Mode Enable 0:JTAG Chain Mode Disable 1:JTAG Chain Mode Enable */
#define SYSON_SHIFT_RM5_DBG_MD_SEL                   1
#define SYSON_BIT_RM5_DBG_MD_SEL                     ((u32)0x00000001 << 1)                              /*!<R/W 0  Real-M500 SWJ-DP Mode Selection 0:SWD-DP Mode 1:JTAG-DP Mode */
#define SYSON_SHIFT_RM5_DBG_PIN_EN                   0
#define SYSON_BIT_RM5_DBG_PIN_EN                     ((u32)0x00000001 << 0)                              /*!<R/W 0  Real-M500 SWJ-DP Pinmux Function Enable 0:SWD/JTAG Pin Disable 1:SWD/JTAG Pin Enable */
/** @} */

/**************************************************************************//**
 * @defgroup rtl8735b_SYSON
 * @{
 * @brief rtl8735b_SYSON Register Declaration
 *****************************************************************************/
typedef struct {
	__O  uint32_t SYSON_REG_SYSON_GPIO_CTRL0 ;             /*!<   register,  Address offset: 0x000 */
	__O  uint32_t SYSON_REG_SYSON_GPIO_CTRL1 ;             /*!<   register,  Address offset: 0x004 */
	__IO uint32_t SYSON_REG_SYSON_GPIOB_0_1_CTRL ;         /*!<   register,  Address offset: 0x008 */
	__IO uint32_t SYSON_REG_SYSON_GPIOB_2_CTRL ;           /*!<   register,  Address offset: 0x00C */
	__IO uint32_t SYSON_REG_SYSON_GPIOC_0_1_CTRL ;         /*!<   register,  Address offset: 0x010 */
	__IO uint32_t SYSON_REG_SYSON_GPIOC_2_3_CTRL ;         /*!<   register,  Address offset: 0x014 */
	__IO uint32_t SYSON_REG_SYSON_GPIOC_4_5_CTRL ;         /*!<   register,  Address offset: 0x018 */
	__IO uint32_t SYSON_REG_SYSON_GPIOD_0_1_CTRL ;         /*!<   register,  Address offset: 0x01C */
	__IO uint32_t SYSON_REG_SYSON_GPIOD_2_3_CTRL ;         /*!<   register,  Address offset: 0x020 */
	__IO uint32_t SYSON_REG_SYSON_GPIOD_4_5_CTRL ;         /*!<   register,  Address offset: 0x024 */
	__IO uint32_t SYSON_REG_SYSON_GPIOD_6_7_CTRL ;         /*!<   register,  Address offset: 0x028 */
	__IO uint32_t SYSON_REG_SYSON_GPIOD_8_9_CTRL ;         /*!<   register,  Address offset: 0x02C */
	__IO uint32_t SYSON_REG_SYSON_GPIOD_10_11_CTRL ;       /*!<   register,  Address offset: 0x030 */
	__IO uint32_t SYSON_REG_SYSON_GPIOD_12_13_CTRL ;       /*!<   register,  Address offset: 0x034 */
	__IO uint32_t SYSON_REG_SYSON_GPIOD_14_15_CTRL ;       /*!<   register,  Address offset: 0x038 */
#if IS_CUT_TEST(CONFIG_CHIP_VER)
	__IO uint32_t SYSON_REG_SYSON_GPIOD_16_CTRL ;          /*!<   register,  Address offset: 0x03C */
	__IO uint32_t SYSON_REG_SYSON_GPIOE_0_1_CTRL ;         /*!<   register,  Address offset: 0x040 */
	__IO uint32_t SYSON_REG_SYSON_GPIOE_2_3_CTRL ;         /*!<   register,  Address offset: 0x044 */
	__IO uint32_t SYSON_REG_SYSON_GPIOE_4_5_CTRL ;         /*!<   register,  Address offset: 0x048 */
	__IO uint32_t SYSON_REG_SYSON_GPIOE_6_7_CTRL ;         /*!<   register,  Address offset: 0x04C */
	__IO uint32_t SYSON_REG_SYSON_GPIOE_8_9_CTRL ;         /*!<   register,  Address offset: 0x050 */
	__IO uint32_t SYSON_REG_SYSON_GPIOE_10_CTRL ;          /*!<   register,  Address offset: 0x054 */
#else
	__IO uint32_t SYSON_REG_SYSON_GPIOD_16_17_CTRL ;       /*!<   register,  Address offset: 0x03C */
	__IO uint32_t SYSON_REG_SYSON_GPIOD_18_19_CTRL ;       /*!<   register,  Address offset: 0x040 */
	__IO uint32_t SYSON_REG_SYSON_GPIOD_20_CTRL ;          /*!<   register,  Address offset: 0x044 */
	__IO uint32_t SYSON_REG_SYSON_GPIOE_0_1_CTRL ;         /*!<   register,  Address offset: 0x048 */
	__IO uint32_t SYSON_REG_SYSON_GPIOE_2_3_CTRL ;         /*!<   register,  Address offset: 0x04C */
	__IO uint32_t SYSON_REG_SYSON_GPIOE_4_5_CTRL ;         /*!<   register,  Address offset: 0x050 */
	__IO uint32_t SYSON_REG_SYSON_GPIOE_6_CTRL ;           /*!<   register,  Address offset: 0x054 */
#endif
	__IO uint32_t SYSON_REG_SYSON_GPIOS_0_1_CTRL ;         /*!<   register,  Address offset: 0x058 */
	__IO uint32_t SYSON_REG_SYSON_GPIOS_2_3_CTRL ;         /*!<   register,  Address offset: 0x05C */
	__IO uint32_t SYSON_REG_SYSON_GPIOS_4_5_CTRL ;         /*!<   register,  Address offset: 0x060 */
	__IO uint32_t SYSON_REG_SYSON_GPIOS_6_CTRL ;           /*!<   register,  Address offset: 0x064 */
	__IO uint32_t SYSON_REG_OTP_AS_CTRL_NS ;               /*!<   register,  Address offset: 0x068 */
	__IO uint32_t SYSON_REG_OTP_SCAN_TEST_NS ;             /*!<   register,  Address offset: 0x06C */
	__IO uint32_t SYSON_REG_SYS_JTAG_SWD_CTRL ;            /*!<   register,          Address offset: 0x070 */
} SYSON_TypeDef;
/** @} */

#endif
