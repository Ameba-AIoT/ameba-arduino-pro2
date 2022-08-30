/**************************************************************************//**
 * @file     cmsis.h
 * @brief    The generic CMSIS include file.
 * @version  V1.00
 * @date     2021-06-04
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

#ifndef MBED_CMSIS_H
#define MBED_CMSIS_H


#include "cmsis_compiler.h"
#include "platform_conf.h"
#include "basic_types.h"
#ifdef VOE_FW
#include "rtl8735b_voe.h"
#include "rtl8735b_voe_irq.h"             /* The IRQ priority definition */
#include "section_config_voe.h"
#else
#include "rtl8735b.h"
#include "rtl8735b_irq.h"              /* The IRQ priority definition */
#include "rtl8735b_cache.h"
#include "section_config.h"
#endif


#include "hal_api.h"
#include "diag.h"

#include "rtl8735b_pin_name.h"
#include "rtl8735b_pinmux.h"
#include "rtl8735b_vendor.h"
#include "rtl8735b_uart.h"
#include "rtl8735b_gdma.h"
#include "rtl8735b_flash.h"
#include "rtl8735b_timer.h"
#include "rtl8735b_misc.h"
#include "rtl8735b_spic.h"
#include "rtl8735b_ssi.h"
#include "rtl8735b_i2s.h"
#include "rtl8735b_i2c.h"
#include "rtl8735b_sgpio.h"
#include "rtl8735b_sdhost.h"
#include "rtl8735b_sdiohost.h"
#include "rtl8735b_pwm.h"
#include "rtl8735b_gpio.h"
#include "rtl8735b_wdt.h"
#include "rtl8735b_sys_ctrl.h"
#include "rtl8735b_crypto_ctrl.h"
#include "rtl8735b_eddsa_ctrl.h"
#include "rtl8735b_rsa.h"
#include "rtl8735b_adc.h"
#include "rtl8735b_eth.h"
#include "rtl8735b_otp.h"
#include "rtl8735b_snand.h"
#include "rtl8735b_flash_sec.h"
#include "rtl8735b_hkdf.h"
#include "rtl8735b_trng.h"
#include "rtl8735b_trng_sec.h"
#include "rtl8735b_rtc.h"
#include "rtl8735b_ecdsa.h"
#include "rtl8735b_sport.h"

// Todo: Need to find place to include
#include "rtl8735b_aon_type.h"
#include "rtl8735b_pon_type.h"
#include "rtl8735b_syson_type.h"
#include "rtl8735b_syson_s_type.h"
#include "rtl8735b_vndr_type.h"
#include "rtl8735b_vndr_s_type.h"

#if (defined(ROM_REGION) && (ROM_REGION==1)) || (defined(CONFIG_BUILD_LIB) && (CONFIG_BUILD_LIB==1))
// TODO: move ROM & Lib reference header file here

#endif

#include "rtl8735b_peri_id.h"

#include <arm_cmse.h>   /* Use CMSE intrinsics */
#if CONFIG_CMSIS_OS_EN
#include "cmsis_os.h"               // CMSIS RTOS header file
#endif

#endif  // end of "#ifndef MBED_CMSIS_H"
