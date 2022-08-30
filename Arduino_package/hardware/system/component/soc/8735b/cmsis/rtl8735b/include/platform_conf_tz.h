/**************************************************************************//**
 * @file     platform_conf_s_ns.h
 * @brief    The configuration for AmebaPro High Power(TM9) platform.
 * @version  V1.00
 * @date     2022-01-12
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2019 Realtek Corporation. All rights reserved.
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

#ifndef _RTL8735B_CONF_TZ_H_
#define _RTL8735B_CONF_TZ_H_
#include "basic_types.h"


/*  Trustzone world peripheral device enable configuration */
#define CONFIG_GTIMER_EN                    1
#define CONFIG_WDG_EN                       1
#define CONFIG_GDMA_EN                      1
#define CONFIG_GPIO_EN                      1
#define CONFIG_UART_EN                      1
#define CONFIG_I2C_EN                       1
#define CONFIG_OTP_EN                       1
#define CONFIG_SPI_FLASH_EN                 1
#define CONFIG_ADC_EN                       1
#define CONFIG_PWM_EN                       1
#define CONFIG_SPI_EN                       1
#define CONFIG_I2S_EN                       1
#define CONFIG_OTG_EN                       1
#define CONFIG_SDIO_HOST_EN                 1
#define CONFIG_SDHOST_EN                    1
#define CONFIG_MII_EN                       0
#define CONFIG_WLAN_EN                      1
#define CONFIG_CRYPTO_EN                    1
#define CONFIG_ISP_EN                       1
#define CONFIG_ENC_EN                       1
#define CONFIG_VIDEO_EN                     1
#define CONFIG_DDR_EN                       1
#define CONFIG_SGPIO_EN                     1
#define CONFIG_SPORT_EN                     1
#define CONFIG_ECDSA_EN                     1
#define CONFIG_EDDSA_EN                     1
#define CONFIG_RSA_EN                       1
#define CONFIG_FLASH_SEC_EN                 1
#define CONFIG_HKDF_EN                      1
#define CONFIG_TRNG_EN                      1
#define CONFIG_RTC_EN                       1
#define CONFIG_NN_EN                        1
#define CONFIG_AUDIO_EN                     1
#define CONFIG_SNAND_FLASH_EN               1




/*  All peripherals security attribute configuration
    <0=> Secure state <1=> Non-Secure state
*/
// Release to customers setting
#define CONFIG_SEC_SystemOn                   SET_NS_STATE
#define CONFIG_SEC_GTIMER0                    SET_NS_STATE
#define CONFIG_SEC_GTIMER1                    SET_NS_STATE
#define CONFIG_SEC_GTIMER2                    SET_NS_STATE
#define CONFIG_SEC_GTIMER3                    SET_NS_STATE
#define CONFIG_SEC_PWM                        SET_NS_STATE
#define CONFIG_SEC_ADC                        SET_NS_STATE
#define CONFIG_SEC_SGPIO                      SET_NS_STATE
#define CONFIG_SEC_UART0                      SET_NS_STATE
#define CONFIG_SEC_UART1                      SET_NS_STATE
#define CONFIG_SEC_UART2                      SET_NS_STATE
#define CONFIG_SEC_UART3                      SET_NS_STATE
#define CONFIG_SEC_BTUART                     SET_NS_STATE
#define CONFIG_SEC_I2C0                       SET_NS_STATE
#define CONFIG_SEC_I2C1                       SET_NS_STATE
#define CONFIG_SEC_I2C2                       SET_NS_STATE
#define CONFIG_SEC_I2C3                       SET_NS_STATE
#define CONFIG_SEC_SPI0                       SET_NS_STATE
#define CONFIG_SEC_SPI1                       SET_NS_STATE
#define CONFIG_SEC_HS_SPI0                    SET_NS_STATE
#define CONFIG_SEC_HS_SPI1                    SET_NS_STATE
#define CONFIG_SEC_I2S0                       SET_NS_STATE
#define CONFIG_SEC_I2S1                       SET_NS_STATE
#define CONFIG_SEC_SPORT                      SET_NS_STATE
#define CONFIG_SEC_USB_OTG                    SET_NS_STATE
#define CONFIG_SEC_SDIOH                      SET_NS_STATE
#define CONFIG_SEC_SDH                        SET_NS_STATE
#define CONFIG_SEC_MII                        SET_NS_STATE
#define CONFIG_SEC_WLAN                       SET_NS_STATE
#define CONFIG_SEC_ISP                        SET_NS_STATE
#define CONFIG_SEC_ENC                        SET_NS_STATE
#define CONFIG_SEC_VOE                        SET_S_STATE
#define CONFIG_SEC_NN                         SET_NS_STATE
#define CONFIG_SEC_ECDSA                      SET_S_STATE
#define CONFIG_SEC_ED25519                    SET_S_STATE      //Rename EDDSA
#define CONFIG_SEC_RSA                        SET_S_STATE
#define CONFIG_SEC_FlashCtrl                  SET_NS_STATE
#define CONFIG_SEC_PonGPIO                    SET_NS_STATE
#define CONFIG_SEC_GPIO                       SET_NS_STATE
#define CONFIG_SEC_SPIC_NAND                  SET_NS_STATE
#define CONFIG_SEC_CODEC                      SET_NS_STATE
#define CONFIG_SEC_DDR_CTRL                   SET_S_STATE


#endif  // end of "#define _RTL8735B_CONF_TZ_H_"

