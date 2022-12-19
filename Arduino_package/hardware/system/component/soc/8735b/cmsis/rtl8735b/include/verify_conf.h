/**************************************************************************//**
 * @file     verify_conf.h
 * @brief    The configuration for AmebaPro2 verify code.
 * @version  V1.00
 * @date     2022-05-05
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

#ifndef _VERIFY_CONF_H_
#define _VERIFY_CONF_H_

#define CONFIG_VERIFY                           1


#define CONFIG_VERIFY_WDG                       0
#define CONFIG_VERIFY_GTIMER                    0
#define CONFIG_VERIFY_GPIO                      0
#define CONFIG_VERIFY_UART                      0
#define CONFIG_VERIFY_ADC                       0
#define CONFIG_VERIFY_GDMA                      0
#define CONFIG_VERIFY_I2C                       0
#define CONFIG_VERIFY_SPI_FLASH                 0
#define CONFIG_VERIFY_SNAND_FLASH               0
#define CONFIG_VERIFY_PWM                       0
#define CONFIG_VERIFY_WDT                       0

#define CONFIG_VERIFY_ECDSA                     0
#define CONFIG_VERIFY_EDDSA                     0
#define CONFIG_VERIFY_CRYPTO                    0
#define CONFIG_VERIFY_RSA                       0
#define CONFIG_VERIFY_ECC                       0
#define CONFIG_VERIFY_COMP                      0


#define CONFIG_VERIFY_I2S                       0
#define CONFIG_VERIFY_SGPIO                     0
#define CONFIG_VERIFY_SPORT                     0
#define CONFIG_VERIFY_SSI                       0
#define CONFIG_VERIFY_AUDIO                     0

#define CONFIG_VERIFY_SEMIHOST                  0
#define CONFIG_VERIFY_DHRYSTONE                 0
#define CONFIG_VERIFY_RTOS                      0


#define CONFIG_VERIFY_ENC                       0
#define CONFIG_VERIFY_NN                        0
#define CONFIG_VERIFY_VIDEO                     0
#define CONFIG_VERIFY_VIDEO_OLT                 0

#define CONFIG_VERIFY_DDR                       0

#define CONFIG_VERIFY_WLAN                      0
#define CONFIG_VERIFY_OTG                       0
#define CONFIG_VERIFY_SYSVIEW                   0
#define CONFIG_VERIFY_RXI316                    0
#define CONFIG_VERIFY_SDHOST                    0
#define CONFIG_VERIFY_SDIOHOST                  0
#define CONFIG_VERIFY_GMAC                      0
#define CONFIG_VERIFY_OTP                       0
#define CONFIG_VERIFY_FLASH_SEC                 0
#define CONFIG_VERIFY_HKDF                      0
#define CONFIG_VERIFY_TRNG                      0
#define CONFIG_VERIFY_RTC                       0
#define CONFIG_VERIFY_FS                        0
#define CONFIG_VERIFY_BSP                       0

// Verify dependency

// OLT verification needs many IPs.
//And remember to open CONFIG_CMSIS_DSP_EN.
#define VERIFY_OLT                              0
#if VERIFY_OLT
#undef CONFIG_VERIFY_I2C
#define CONFIG_VERIFY_I2C                       1
#undef CONFIG_VERIFY_OTG
#define CONFIG_VERIFY_OTG                       1
#undef CONFIG_VERIFY_WLAN
#define CONFIG_VERIFY_WLAN                      1
#undef CONFIG_VERIFY_VIDEO_OLT
#define CONFIG_VERIFY_VIDEO_OLT                 1
#endif

#endif  // end of "#define _VERIFY_CONF_H_"
