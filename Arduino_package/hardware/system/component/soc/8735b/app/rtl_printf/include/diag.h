/**************************************************************************//**
 * @file     diag.h
 * @brief    This file defines macros for debug message printing.
 * @version  V1.00
 * @date     2022-03-31
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

#ifndef _DIAG_H_
#define _DIAG_H_
#include "platform_conf.h"
#include "basic_types.h"
#include <stdarg.h>
#include <stddef.h> /* for size_t */
#include "log_buf.h"
#include "rt_printf.h"
#include "utility.h"

#if defined(CONFIG_VRF_MODE) && (CONFIG_VRF_MODE==1)
extern osMutexId PrintLock_id;
extern log_buf_type_t debug_log;
#endif

#if defined(ROM_REGION)
extern u32 ConfigDebugErr;
extern u32 ConfigDebugInfo;
extern u32 ConfigDebugWarn;
#else
#define ConfigDebugErr          (*(utility_stubs.config_debug_err))
#define ConfigDebugWarn         (*(utility_stubs.config_debug_warn))
#define ConfigDebugInfo         (*(utility_stubs.config_debug_info))
#if defined(CONFIG_BUILD_BOOT) && (CONFIG_BUILD_BOOT==1)
extern uint8_t ConfigBootLOG_EN;
#endif
#if !defined(CONFIG_BUILD_SECURE) && !defined(CONFIG_BUILD_NONSECURE)
#define ConfigDebugErr_NS       (*(__rom_stubs_utility_ns.config_debug_err))
#define ConfigDebugWarn_NS      (*(__rom_stubs_utility_ns.config_debug_warn))
#define ConfigDebugInfo_NS      (*(__rom_stubs_utility_ns.config_debug_info))
#endif
#endif

#if !defined(CONFIG_BUILD_SECURE) && !defined(CONFIG_BUILD_NONSECURE) && !defined(ROM_REGION)
#define DBG_ERR_MSG_ON(x)       do {(ConfigDebugErr |= (x)); (ConfigDebugErr_NS |= (x));} while(0)
#define DBG_WARN_MSG_ON(x)      do {(ConfigDebugWarn |= (x)); (ConfigDebugWarn_NS |= (x));} while(0)
#define DBG_INFO_MSG_ON(x)      do {(ConfigDebugInfo |= (x)); (ConfigDebugInfo_NS |= (x));} while(0)

#define DBG_ERR_MSG_OFF(x)      do {(ConfigDebugErr &= ~(x)); (ConfigDebugErr_NS &= ~(x));} while(0)
#define DBG_WARN_MSG_OFF(x)     do {(ConfigDebugWarn &= ~(x)); (ConfigDebugWarn_NS &= ~(x));} while(0)
#define DBG_INFO_MSG_OFF(x)     do {(ConfigDebugInfo &= ~(x)); (ConfigDebugInfo_NS &= ~(x));} while(0)

#else
#define DBG_ERR_MSG_ON(x)       (ConfigDebugErr |= (x))
#define DBG_WARN_MSG_ON(x)      (ConfigDebugWarn |= (x))
#define DBG_INFO_MSG_ON(x)      (ConfigDebugInfo |= (x))

#define DBG_ERR_MSG_OFF(x)      (ConfigDebugErr &= ~(x))
#define DBG_WARN_MSG_OFF(x)     (ConfigDebugWarn &= ~(x))
#define DBG_INFO_MSG_OFF(x)     (ConfigDebugInfo &= ~(x))
#endif

// Define debug group
#define _DBG_BOOT_              0x00000001
#define _DBG_GDMA_              0x00000002
#define _DBG_GPIO_              0x00000004
#define _DBG_TIMER_             0x00000008
#define _DBG_UART_              0x00000010
#define _DBG_I2C_               0x00000020
#define _DBG_SSI_               0x00000040
#define _DBG_SPI_FLASH_         0x00000080
#define _DBG_CRYPTO_            0x00000100
#define _DBG_EDDSA_             0x00000200
#define _DBG_ECDSA_             0x00000400
#define _DBG_ADC_               0x00000800
#define _DBG_PWM_               0x00001000
#define _DBG_I2S_               0x00002000
#define _DBG_SDIO_HOST_         0x00004000
#define _DBG_SDHOST_            0x00008000
#define _DBG_OTG_               0x00010000
#define _DBG_MII_               0x00020000
#define _DBG_WLAN_              0x00040000
#define _DBG_SGPIO_             0x00080000
#define _DBG_SPORT_             0x00100000
#define _DBG_AUDIO_             0x00200000
#define _DBG_PCM_               0x00400000
#define _DBG_ISP_               0x00800000
#define _DBG_ENC_               0x01000000
#define _DBG_OTP_               0x02000000
#define _DBG_FLASH_SEC_         0x04000000
#define _DBG_MISC_              0x08000000
#define _DBG_RSA_               0x10000000
#define _DBG_SNAND_             0x20000000
#define _DBG_DRAM_              0x40000000



#if CONFIG_LIGHT_PRINTF
// Light weight printf
#if defined(ROM_REGION)
#define dbg_printf(...)                     do { if(ConfigDebugErr & _DBG_BOOT_){_rtl_printf(__VA_ARGS__);} }while(0)
#define dbg_sprintf(buf, ...)               do { _rtl_sprintf(buf, __VA_ARGS__); }while(0)
#define dbg_snprintf(buf, size, ...)        do { _rtl_snprintf(buf, size, __VA_ARGS__); }while(0)
// Verifi mode, _DbgDump() for ROM Code
#if defined(CONFIG_VRF_MODE) && (CONFIG_VRF_MODE==1)
#define _DbgDump(...) do{\
    if(PrintLock_id != NULL) \
        _mutex_rtl_printf(PrintLock_id,__VA_ARGS__);\
    else \
        _rtl_printf(__VA_ARGS__); \
}while(0)
#else
#define _DbgDump                            _rtl_printf
#endif

#else
#if defined(CONFIG_BUILD_BOOT) && (CONFIG_BUILD_BOOT==1)
#define dbg_printf(...)                     do { if(ConfigBootLOG_EN){rt_printfl(__VA_ARGS__);} }while(0)
#else
#define dbg_printf                          rt_printfl
#endif
#define dbg_sprintf                         rt_sprintfl
#define dbg_snprintf                        rt_snprintfl
// Verifi mode, _DbgDump() for RAM Code
#if defined(CONFIG_VRF_MODE) && (CONFIG_VRF_MODE==1)
#define _DbgDump(...) do{\
    if(PrintLock_id != NULL) \
        _mutex_rtl_printf(PrintLock_id,__VA_ARGS__);\
    else \
        rt_printfl(__VA_ARGS__); \
}while(0)
#else
#define _DbgDump                            rt_printfl
#endif
#endif

#else
// all-format printf
#if defined(ROM_REGION)
#define dbg_printf(...)                     do { if(ConfigDebugErr & _DBG_BOOT_){_xprintf(__VA_ARGS__);} }while(0)
#define dbg_sprintf(buf, ...)               do { _xsprintf(buf, __VA_ARGS__); }while(0)
#define dbg_snprintf(buf, size, ...)        do { _xsnprintf(buf, size, __VA_ARGS__); }while(0)
#define _DbgDump                            _xprintf
#else
#define dbg_printf                          rt_printf
#define dbg_sprintf                         rt_sprintf
#define dbg_snprintf                        rt_snprintf
#define _DbgDump                            rt_printf
#endif
#endif

#if defined(ROM_REGION)
#define log_printf(plog, ...)       do { _log_buf_printf(plog, __VA_ARGS__); }while(0)
#else
// Verifi mode, log_printf() for RAM Code
#if defined(CONFIG_VRF_MODE) && (CONFIG_VRF_MODE==1)
#define log_printf(...) do {\
    rt_log_printf(&debug_log,__VA_ARGS__); \
}while(0)
#else
#define log_printf                  rt_log_printf
#endif
#endif

#define DRIVER_PREFIX           "[Driver]: "
#define HAL_PREFIX              "[HAL]: "

#define BOOT_ERR_PREFIX         "[BOOT Err]"
#define BOOT_WARN_PREFIX        "[BOOT Wrn]"
#define BOOT_INFO_PREFIX        "[BOOT Inf]"

#define GDMA_ERR_PREFIX         "[GDMA Err]"
#define GDMA_WARN_PREFIX        "[GDMA Wrn]"
#define GDMA_INFO_PREFIX        "[GDMA Inf]"

#define GPIO_ERR_PREFIX         "[GPIO Err]"
#define GPIO_WARN_PREFIX        "[GPIO Wrn]"
#define GPIO_INFO_PREFIX        "[GPIO Inf]"

#define TIMER_ERR_PREFIX        "[TIMR Err]"
#define TIMER_WARN_PREFIX       "[TIMR Wrn]"
#define TIMER_INFO_PREFIX       "[TIMR Inf]"

#define UART_ERR_PREFIX         "[UART Err]"
#define UART_WARN_PREFIX        "[UART Wrn]"
#define UART_INFO_PREFIX        "[UART Inf]"

#define I2C_ERR_PREFIX          "[I2C  Err]"
#define I2C_WARN_PREFIX         "[I2C  Wrn]"
#define I2C_INFO_PREFIX         "[I2C  Inf]"

#define SSI_ERR_PREFIX          "[SSI  Err]"
#define SSI_WARN_PREFIX         "[SSI  Wrn]"
#define SSI_INFO_PREFIX         "[SSI  Inf]"

#define SPIF_ERR_PREFIX         "[SPIF Err]"
#define SPIF_WARN_PREFIX        "[SPIF Wrn]"
#define SPIF_INFO_PREFIX        "[SPIF Inf]"

#define CRYPTO_ERR_PREFIX       "[CRYP Err]"
#define CRYPTO_WARN_PREFIX      "[CRYP Wrn]"
#define CRYPTO_INFO_PREFIX      "[CRYP Inf]"

#define EDDSA_ERR_PREFIX        "[EDDSA Err]"
#define EDDSA_WARN_PREFIX       "[EDDSA Wrn]"
#define EDDSA_INFO_PREFIX       "[EDDSA Inf]"

#define ECDSA_ERR_PREFIX        "[ECDSA Err]"
#define ECDSA_WARN_PREFIX       "[ECDSA Wrn]"
#define ECDSA_INFO_PREFIX       "[ECDSA Inf]"

#define ADC_ERR_PREFIX          "[ADC  Err]"
#define ADC_WARN_PREFIX         "[ADC  Wrn]"
#define ADC_INFO_PREFIX         "[ADC  Inf]"

#define PWM_ERR_PREFIX          "[PWM  Err]"
#define PWM_WARN_PREFIX         "[PWM  Wrn]"
#define PWM_INFO_PREFIX         "[PWM  Inf]"

#define I2S_ERR_PREFIX          "[I2S  Err]"
#define I2S_WARN_PREFIX         "[I2S  Wrn]"
#define I2S_INFO_PREFIX         "[I2S  Inf]"

#define SDIOH_ERR_PREFIX        "[SDIOH Err]"
#define SDIOH_WARN_PREFIX       "[SDIOH Wrn]"
#define SDIOH_INFO_PREFIX       "[SDIOH Inf]"

#define SDHOST_ERR_PREFIX       "[SDHOST Err]"
#define SDHOST_WARN_PREFIX      "[SDHOST Wrn]"
#define SDHOST_INFO_PREFIX      "[SDHOST Inf]"

#define OTG_ERR_PREFIX          "[OTG Err]"
#define OTG_WARN_PREFIX         "[OTG Wrn]"
#define OTG_INFO_PREFIX         "[OTG Inf]"

#define MII_ERR_PREFIX          "[MII  Err]"
#define MII_WARN_PREFIX         "[MII  Wrn]"
#define MII_INFO_PREFIX         "[MII  Inf]"

#define WLAN_ERR_PREFIX         "[WLAN Err]"
#define WLAN_WARN_PREFIX        "[WLAN Wrn]"
#define WLAN_INFO_PREFIX        "[WLAN Inf]"

#define SGPIO_ERR_PREFIX        "[SGPIO  Err]"
#define SGPIO_WARN_PREFIX       "[SGPIO  Wrn]"
#define SGPIO_INFO_PREFIX       "[SGPIO  Inf]"

#define SPORT_ERR_PREFIX        "[SPORT Err]"
#define SPORT_WARN_PREFIX       "[SPORT Wrn]"
#define SPORT_INFO_PREFIX       "[SPORT Inf]"

#define AUDIO_ERR_PREFIX        "[AUDIO  Err]"
#define AUDIO_WARN_PREFIX       "[AUDIO  Wrn]"
#define AUDIO_INFO_PREFIX       "[AUDIO  Inf]"

#define PCM_ERR_PREFIX          "[PCM  Err]"
#define PCM_WARN_PREFIX         "[PCM  Wrn]"
#define PCM_INFO_PREFIX         "[PCM  Inf]"

#define ISP_ERR_PREFIX          "[ISP  Err]"
#define ISP_WARN_PREFIX         "[ISP  Wrn]"
#define ISP_INFO_PREFIX         "[ISP  Inf]"

#define ENC_ERR_PREFIX          "[ENC  Err]"
#define ENC_WARN_PREFIX         "[ENC  Wrn]"
#define ENC_INFO_PREFIX         "[ENC  Inf]"

#define OTP_ERR_PREFIX          "[OTP  Err]"
#define OTP_WARN_PREFIX         "[OTP  Wrn]"
#define OTP_INFO_PREFIX         "[OTP  Inf]"

#define FSEC_ERR_PREFIX         "[FSEC Err]"
#define FSEC_WARN_PREFIX        "[FSEC Wrn]"
#define FSEC_INFO_PREFIX        "[FSEC Inf]"

#define MISC_ERR_PREFIX         "[MISC Err]"
#define MISC_WARN_PREFIX        "[MISC Wrn]"
#define MISC_INFO_PREFIX        "[MISC Inf]"

#define RSA_ERR_PREFIX         "[RSA Err]"
#define RSA_WARN_PREFIX        "[RSA Wrn]"
#define RSA_INFO_PREFIX        "[RSA Inf]"

#define SNAND_ERR_PREFIX       "[SNAND Err]"
#define SNAND_WARN_PREFIX      "[SNAND Wrn]"
#define SNAND_INFO_PREFIX      "[SNAND Inf]"

#define DRAM_ERR_PREFIX        "[DRAM Err]"
#define DRAM_WARN_PREFIX       "[DRAM Wrn]"
#define DRAM_INFO_PREFIX       "[DRAM Inf]"

#ifndef likely
#define likely(x)               (x)
#define unlikely(x)             (x)
#endif

#if CONFIG_DEBUG_LOG

#if CONFIG_DEBUG_ERROR      // if Build-In Debug Error Message

#define DBG_BOOT_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_BOOT_)) \
        _DbgDump("\r" BOOT_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_GDMA_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_GDMA_)) \
        _DbgDump("\r" GDMA_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_GPIO_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_GPIO_)) \
        _DbgDump("\r" GPIO_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_TIMER_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_TIMER_)) \
        _DbgDump("\r" TIMER_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_UART_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_UART_)) \
        _DbgDump("\r" UART_ERR_PREFIX __VA_ARGS__);\
}while(0)

#ifdef ARDUINO_SDK
#define DBG_I2C_ERR(...)
#else
#define DBG_I2C_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_I2C_)) \
        _DbgDump("\r" I2C_ERR_PREFIX __VA_ARGS__);\
}while(0)
#endif

#define DBG_SSI_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_SSI_)) \
        _DbgDump("\r" SSI_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_SPIF_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_SPI_FLASH_)) \
        _DbgDump("\r" SPIF_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_CRYPTO_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_CRYPTO_)) \
        _DbgDump("\r" CRYPTO_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_EDDSA_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_EDDSA_)) \
        _DbgDump("\r" EDDSA_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_ECDSA_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_ECDSA_)) \
        _DbgDump("\r" ECDSA_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_ADC_ERR(...)     do {\
        if (likely(ConfigDebugErr & _DBG_ADC_)) \
        _DbgDump("\r" ADC_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_PWM_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_PWM_)) \
        _DbgDump("\r" PWM_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_I2S_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_I2S_)) \
        _DbgDump("\r" I2S_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_SDIO_HOST_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_SDIO_HOST_)) \
        _DbgDump("\r" SDIOH_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_SDHOST_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_SDHOST_)) \
        _DbgDump("\r" SDHOST_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_OTG_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_OTG_)) \
        _DbgDump("\r" OTG_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_MII_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_MII_)) \
        _DbgDump("\r" MII_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_WLAN_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_WLAN_)) \
        _DbgDump("\r" WLAN_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_SGPIO_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_SGPIO_)) \
        _DbgDump("\r" SGPIO_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_SPORT_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_SPORT_)) \
        _DbgDump("\r" SPORT_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_AUDIO_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_AUDIO_)) \
        _DbgDump("\r" AUDIO_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_PCM_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_PCM_)) \
        _DbgDump("\r" PCM_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_ISP_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_ISP_)) \
        _DbgDump("\r" ISP_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_ENC_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_ENC_)) \
        _DbgDump("\r" ENC_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_OTP_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_OTP_)) \
        _DbgDump("\r" OTP_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_FLASH_SEC_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_FLASH_SEC_)) \
        _DbgDump("\r" FSEC_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_MISC_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_MISC_)) \
        _DbgDump("\r" MISC_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_RSA_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_RSA_)) \
        _DbgDump("\r" RSA_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_SNAND_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_SNAND_)) \
        _DbgDump("\r" SNAND_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_DRAM_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_DRAM_)) \
        _DbgDump("\r" DRAM_ERR_PREFIX __VA_ARGS__);\
}while(0)

#else   // else of "#if CONFIG_DEBUG_ERROR"

#define DBG_BOOT_ERR(...)
#define DBG_GDMA_ERR(...)
#define DBG_GPIO_ERR(...)
#define DBG_TIMER_ERR(...)
#define DBG_UART_ERR(...)
#define DBG_I2C_ERR(...)
#define DBG_SSI_ERR(...)
#define DBG_SPIF_ERR(...)
#define DBG_CRYPTO_ERR(...)
#define DBG_EDDSA_ERR(...)
#define DBG_ECDSA_ERR(...)
#define DBG_ADC_ERR(...)
#define DBG_PWM_ERR(...)
#define DBG_I2S_ERR(...)
#define DBG_SDIO_HOST_ERR(...)
#define DBG_SDHOST_ERR(...)
#define DBG_OTG_ERR(...)
#define DBG_MII_ERR(...)
#define DBG_WLAN_ERR(...)
#define DBG_SGPIO_ERR(...)
#define DBG_SPORT_ERR(...)
#define DBG_AUDIO_ERR(...)
#define DBG_PCM_ERR(...)
#define DBG_ISP_ERR(...)
#define DBG_ENC_ERR(...)
#define DBG_OTP_ERR(...)
#define DBG_FLASH_SEC_ERR(...)
#define DBG_MISC_ERR(...)
#define DBG_RSA_ERR(...)
#define DBG_SNAND_ERR(...)
#define DBG_DRAM_ERR(...)


#endif  // end of else of "#if CONFIG_DEBUG_ERROR"

// =============================================================

#if CONFIG_DEBUG_WARN     // if Build-In Debug Warring Message

#define DBG_BOOT_WARN(...)     do {\
    if (likely(ConfigDebugWarn & _DBG_BOOT_)) \
        _DbgDump("\r" BOOT_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_GDMA_WARN(...)     do {\
    if (likely(ConfigDebugWarn & _DBG_GDMA_)) \
        _DbgDump("\r" GDMA_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_GPIO_WARN(...)     do {\
    if (likely(ConfigDebugWarn & _DBG_GPIO_)) \
        _DbgDump("\r" GPIO_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_TIMER_WARN(...)     do {\
    if (likely(ConfigDebugWarn & _DBG_TIMER_)) \
        _DbgDump("\r" TIMER_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_UART_WARN(...)     do {\
    if (likely(ConfigDebugWarn & _DBG_UART_)) \
        _DbgDump("\r" UART_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_I2C_WARN(...)     do {\
    if (likely(ConfigDebugWarn & _DBG_I2C_)) \
        _DbgDump("\r" I2C_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_SSI_WARN(...)     do {\
    if (likely(ConfigDebugWarn & _DBG_SSI_)) \
        _DbgDump("\r" SSI_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_SPIF_WARN(...)     do {\
    if (likely(ConfigDebugWarn & _DBG_SPI_FLASH_)) \
        _DbgDump("\r" SPIF_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_CRYPTO_WARN(...)     do {\
    if (likely(ConfigDebugWarn & _DBG_CRYPTO_)) \
        _DbgDump("\r" CRYPTO_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_EDDSA_WARN(...)     do {\
    if (likely(ConfigDebugWarn & _DBG_EDDSA_)) \
        _DbgDump("\r" EDDSA_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_ECDSA_WARN(...)     do {\
    if (likely(ConfigDebugWarn & _DBG_ECDSA_)) \
        _DbgDump("\r" ECDSA_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_ADC_WARN(...)     do {\
        if (likely(ConfigDebugWarn & _DBG_ADC_)) \
        _DbgDump("\r" ADC_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_PWM_WARN(...)     do {\
    if (likely(ConfigDebugWarn & _DBG_PWM_)) \
        _DbgDump("\r" PWM_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_I2S_WARN(...)     do {\
    if (likely(ConfigDebugWarn & _DBG_I2S_)) \
        _DbgDump("\r" I2S_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_SDIO_HOST_WARN(...)     do {\
    if (likely(ConfigDebugWarn & _DBG_SDIO_HOST_)) \
        _DbgDump("\r" SDIOH_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_SDHOST_WARN(...)     do {\
    if (likely(ConfigDebugWarn & _DBG_SDHOST_)) \
        _DbgDump("\r" SDHOST_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_OTG_WARN(...)     do {\
    if (likely(ConfigDebugWarn & _DBG_OTG_)) \
        _DbgDump("\r" OTG_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_MII_WARN(...)     do {\
    if (likely(ConfigDebugWarn & _DBG_MII_)) \
        _DbgDump("\r" MII_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_WLAN_WARN(...)     do {\
    if (likely(ConfigDebugWarn & _DBG_WLAN_)) \
        _DbgDump("\r" WLAN_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_SGPIO_WARN(...)     do {\
    if (likely(ConfigDebugWarn & _DBG_SGPIO_)) \
        _DbgDump("\r" SGPIO_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_SPORT_WARN(...)     do {\
    if (likely(ConfigDebugWarn & _DBG_SPORT_)) \
        _DbgDump("\r" SPORT_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_AUDIO_WARN(...)     do {\
    if (likely(ConfigDebugWarn & _DBG_AUDIO_)) \
        _DbgDump("\r" AUDIO_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_PCM_WARN(...)     do {\
    if (likely(ConfigDebugWarn & _DBG_PCM_)) \
        _DbgDump("\r" PCM_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_ISP_WARN(...)     do {\
    if (likely(ConfigDebugWarn & _DBG_ISP_)) \
        _DbgDump("\r" ISP_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_ENC_WARN(...)     do {\
    if (likely(ConfigDebugWarn & _DBG_ENC_)) \
        _DbgDump("\r" ENC_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_OTP_WARN(...)     do {\
    if (likely(ConfigDebugWarn & _DBG_OTP_)) \
        _DbgDump("\r" OTP_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_FLASH_SEC_WARN(...)     do {\
    if (likely(ConfigDebugWarn & _DBG_FLASH_SEC_)) \
        _DbgDump("\r" FSEC_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_MISC_WARN(...)     do {\
    if (likely(ConfigDebugWarn & _DBG_MISC_)) \
        _DbgDump("\r" MISC_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_RSA_WARN(...)     do {\
        if (likely(ConfigDebugWarn & _DBG_RSA_)) \
            _DbgDump("\r" RSA_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_SNAND_WARN(...)     do {\
        if (likely(ConfigDebugWarn & _DBG_SNAND_)) \
            _DbgDump("\r" SNAND_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_DRAM_WARN(...)     do {\
        if (likely(ConfigDebugWarn & _DBG_DRAM_)) \
            _DbgDump("\r" DRAM_WARN_PREFIX __VA_ARGS__);\
}while(0)

#else   // else of "#if CONFIG_DEBUG_WARNOR"

#define DBG_BOOT_WARN(...)
#define DBG_GDMA_WARN(...)
#define DBG_GPIO_WARN(...)
#define DBG_TIMER_WARN(...)
#define DBG_UART_WARN(...)
#define DBG_I2C_WARN(...)
#define DBG_SSI_WARN(...)
#define DBG_SPIF_WARN(...)
#define DBG_CRYPTO_WARN(...)
#define DBG_EDDSA_WARN(...)
#define DBG_ECDSA_WARN(...)
#define DBG_ADC_WARN(...)
#define DBG_PWM_WARN(...)
#define DBG_I2S_WARN(...)
#define DBG_SDIO_HOST_WARN(...)
#define DBG_SDHOST_WARN(...)
#define DBG_OTG_WARN(...)
#define DBG_MII_WARN(...)
#define DBG_WLAN_WARN(...)
#define DBG_SGPIO_WARN(...)
#define DBG_SPORT_WARN(...)
#define DBG_AUDIO_WARN(...)
#define DBG_PCM_WARN(...)
#define DBG_ISP_WARN(...)
#define DBG_ENC_WARN(...)
#define DBG_OTP_WARN(...)
#define DBG_FLASH_SEC_WARN(...)
#define DBG_MISC_WARN(...)
#define DBG_RSA_WARN(...)
#define DBG_SNAND_WARN(...)
#define DBG_DRAM_WARN(...)


#endif  // end of else of "#if CONFIG_DEBUG_WARN"

// =============================================================

#if CONFIG_DEBUG_INFO     // if Build-In Debug Information Message

#define DBG_BOOT_INFO(...)     do {\
    if (likely(ConfigDebugInfo & _DBG_BOOT_)) \
        _DbgDump("\r" BOOT_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_GDMA_INFO(...)     do {\
    if (likely(ConfigDebugInfo & _DBG_GDMA_)) \
        _DbgDump("\r" GDMA_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_GPIO_INFO(...)     do {\
    if (likely(ConfigDebugInfo & _DBG_GPIO_)) \
        _DbgDump("\r" GPIO_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_TIMER_INFO(...)     do {\
    if (likely(ConfigDebugInfo & _DBG_TIMER_)) \
        _DbgDump("\r" TIMER_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_UART_INFO(...)     do {\
    if (likely(ConfigDebugInfo & _DBG_UART_)) \
        _DbgDump("\r" UART_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_I2C_INFO(...)     do {\
    if (likely(ConfigDebugInfo & _DBG_I2C_)) \
        _DbgDump("\r" I2C_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_SSI_INFO(...)     do {\
    if (likely(ConfigDebugInfo & _DBG_SSI_)) \
        _DbgDump("\r" SSI_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_SPIF_INFO(...)     do {\
    if (likely(ConfigDebugInfo & _DBG_SPI_FLASH_)) \
        _DbgDump("\r" SPIF_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_CRYPTO_INFO(...)     do {\
    if (likely(ConfigDebugInfo & _DBG_CRYPTO_)) \
        _DbgDump("\r" CRYPTO_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_EDDSA_INFO(...)     do {\
    if (likely(ConfigDebugInfo & _DBG_EDDSA_)) \
        _DbgDump("\r" EDDSA_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_ECDSA_INFO(...)     do {\
    if (likely(ConfigDebugInfo & _DBG_ECDSA_)) \
        _DbgDump("\r" ECDSA_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_ADC_INFO(...)     do {\
        if (likely(ConfigDebugInfo & _DBG_ADC_)) \
        _DbgDump("\r" ADC_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_PWM_INFO(...)     do {\
    if (likely(ConfigDebugInfo & _DBG_PWM_)) \
        _DbgDump("\r" PWM_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_I2S_INFO(...)     do {\
    if (likely(ConfigDebugInfo & _DBG_I2S_)) \
        _DbgDump("\r" I2S_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_SDIO_HOST_INFO(...)     do {\
    if (likely(ConfigDebugInfo & _DBG_SDIO_HOST_)) \
        _DbgDump("\r" SDIOH_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_SDHOST_INFO(...)     do {\
    if (likely(ConfigDebugInfo & _DBG_SDHOST_)) \
        _DbgDump("\r" SDHOST_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_OTG_INFO(...)     do {\
    if (likely(ConfigDebugInfo & _DBG_OTG_)) \
        _DbgDump("\r" OTG_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_MII_INFO(...)     do {\
    if (likely(ConfigDebugInfo & _DBG_MII_)) \
        _DbgDump("\r" MII_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_WLAN_INFO(...)     do {\
    if (likely(ConfigDebugInfo & _DBG_WLAN_)) \
        _DbgDump("\r" WLAN_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_SGPIO_INFO(...)     do {\
    if (likely(ConfigDebugInfo & _DBG_SGPIO_)) \
        _DbgDump("\r" SGPIO_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_SPORT_INFO(...)     do {\
    if (likely(ConfigDebugInfo & _DBG_SPORT_)) \
        _DbgDump("\r" SPORT_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_AUDIO_INFO(...)     do {\
    if (likely(ConfigDebugInfo & _DBG_AUDIO_)) \
        _DbgDump("\r" AUDIO_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_PCM_INFO(...)     do {\
    if (likely(ConfigDebugInfo & _DBG_PCM_)) \
        _DbgDump("\r" PCM_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_ISP_INFO(...)     do {\
    if (likely(ConfigDebugInfo & _DBG_ISP_)) \
        _DbgDump("\r" ISP_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_ENC_INFO(...)     do {\
    if (likely(ConfigDebugInfo & _DBG_ENC_)) \
        _DbgDump("\r" ENC_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_OTP_INFO(...)     do {\
    if (likely(ConfigDebugInfo & _DBG_OTP_)) \
        _DbgDump("\r" OTP_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_FLASH_SEC_INFO(...)     do {\
    if (likely(ConfigDebugInfo & _DBG_FLASH_SEC_)) \
        _DbgDump("\r" FSEC_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_MISC_INFO(...)     do {\
    if (likely(ConfigDebugInfo & _DBG_MISC_)) \
        _DbgDump("\r" MISC_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_RSA_INFO(...)     do {\
    if (likely(ConfigDebugInfo & _DBG_RSA_)) \
        _DbgDump("\r" RSA_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_SNAND_INFO(...)     do {\
    if (likely(ConfigDebugInfo & _DBG_SNAND_)) \
        _DbgDump("\r" SNAND_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_DRAM_INFO(...)     do {\
    if (likely(ConfigDebugInfo & _DBG_DRAM_)) \
        _DbgDump("\r" DRAM_INFO_PREFIX __VA_ARGS__);\
}while(0)

#else   // else of "#if CONFIG_DEBUG_INFOOR"

#define DBG_BOOT_INFO(...)
#define DBG_GDMA_INFO(...)
#define DBG_GPIO_INFO(...)
#define DBG_TIMER_INFO(...)
#define DBG_UART_INFO(...)
#define DBG_I2C_INFO(...)
#define DBG_SSI_INFO(...)
#define DBG_SPIF_INFO(...)
#define DBG_CRYPTO_INFO(...)
#define DBG_EDDSA_INFO(...)
#define DBG_ECDSA_INFO(...)
#define DBG_ADC_INFO(...)
#define DBG_PWM_INFO(...)
#define DBG_I2S_INFO(...)
#define DBG_SDIO_HOST_INFO(...)
#define DBG_SDHOST_INFO(...)
#define DBG_OTG_INFO(...)
#define DBG_MII_INFO(...)
#define DBG_WLAN_INFO(...)
#define DBG_SGPIO_INFO(...)
#define DBG_SPORT_INFO(...)
#define DBG_AUDIO_INFO(...)
#define DBG_PCM_INFO(...)
#define DBG_ISP_INFO(...)
#define DBG_ENC_INFO(...)
#define DBG_OTP_INFO(...)
#define DBG_FLASH_SEC_INFO(...)
#define DBG_MISC_INFO(...)
#define DBG_RSA_INFO(...)
#define DBG_SNAND_INFO(...)
#define DBG_DRAM_INFO(...)


#endif  // end of else of "#if CONFIG_DEBUG_INFO"

#define DBG_8735B(...)     do {\
    if (unlikely(ConfigDebugErr & _DBG_MISC_)) \
        _DbgDump("\r" __VA_ARGS__);\
}while(0)

#define MONITOR_LOG(...)     do {\
    if (unlikely(ConfigDebugErr & _DBG_MISC_)) \
        _DbgDump( __VA_ARGS__);\
}while(0)

#undef DBG_ASSERT
#ifdef __GNUC__
#define DBG_ASSERT(x)     do {\
        if (unlikely(!(x))) \
            _DbgDump("Assertion: %s:%s, %d\n", __FILE__, __func__, __LINE__);\
    }while(0)
#endif

#ifdef __ICCARM__
#define DBG_ASSERT(x)     do {\
        if (unlikely(!(x))) \
            _DbgDump("Assertion: %s:%s, %d\n", __FILE__, __func__, __LINE__);\
    }while(0)
#endif

#else   // else of "#if CONFIG_DEBUG_LOG"
#define DBG_8735B(...)
#define MONITOR_LOG(...)
#undef DBG_ASSERT
#define DBG_ASSERT(x)

#define DBG_BOOT_ERR(...)
#define DBG_GDMA_ERR(...)
#define DBG_GPIO_ERR(...)
#define DBG_TIMER_ERR(...)
#define DBG_UART_ERR(...)
#define DBG_I2C_ERR(...)
#define DBG_SSI_ERR(...)
#define DBG_SPIF_ERR(...)
#define DBG_CRYPTO_ERR(...)
#define DBG_EDDSA_ERR(...)
#define DBG_ECDSA_ERR(...)
#define DBG_ADC_ERR(...)
#define DBG_PWM_ERR(...)
#define DBG_I2S_ERR(...)
#define DBG_SDIO_HOST_ERR(...)
#define DBG_SDHOST_ERR(...)
#define DBG_OTG_ERR(...)
#define DBG_MII_ERR(...)
#define DBG_WLAN_ERR(...)
#define DBG_SGPIO_ERR(...)
#define DBG_SPORT_ERR(...)
#define DBG_AUDIO_ERR(...)
#define DBG_PCM_ERR(...)
#define DBG_ISP_ERR(...)
#define DBG_ENC_ERR(...)
#define DBG_OTP_ERR(...)
#define DBG_FLASH_SEC_ERR(...)
#define DBG_MISC_ERR(...)
#define DBG_RSA_ERR(...)
#define DBG_SNAND_ERR(...)
#define DBG_DRAM_ERR(...)


#define DBG_BOOT_WARN(...)
#define DBG_GDMA_WARN(...)
#define DBG_GPIO_WARN(...)
#define DBG_TIMER_WARN(...)
#define DBG_UART_WARN(...)
#define DBG_I2C_WARN(...)
#define DBG_SSI_WARN(...)
#define DBG_SPIF_WARN(...)
#define DBG_CRYPTO_WARN(...)
#define DBG_EDDSA_WARN(...)
#define DBG_ECDSA_WARN(...)
#define DBG_ADC_WARN(...)
#define DBG_PWM_WARN(...)
#define DBG_I2S_WARN(...)
#define DBG_SDIO_HOST_WARN(...)
#define DBG_SDHOST_WARN(...)
#define DBG_OTG_WARN(...)
#define DBG_MII_WARN(...)
#define DBG_WLAN_WARN(...)
#define DBG_SGPIO_WARN(...)
#define DBG_SPORT_WARN(...)
#define DBG_AUDIO_WARN(...)
#define DBG_PCM_WARN(...)
#define DBG_ISP_WARN(...)
#define DBG_ENC_WARN(...)
#define DBG_OTP_WARN(...)
#define DBG_FLASH_SEC_WARN(...)
#define DBG_MISC_WARN(...)
#define DBG_RSA_WARN(...)
#define DBG_SNAND_WARN(...)
#define DBG_DRAM_WARN(...)


#define DBG_BOOT_INFO(...)
#define DBG_GDMA_INFO(...)
#define DBG_GPIO_INFO(...)
#define DBG_TIMER_INFO(...)
#define DBG_UART_INFO(...)
#define DBG_I2C_INFO(...)
#define DBG_SSI_INFO(...)
#define DBG_SPIF_INFO(...)
#define DBG_CRYPTO_INFO(...)
#define DBG_EDDSA_INFO(...)
#define DBG_ECDSA_INFO(...)
#define DBG_ADC_INFO(...)
#define DBG_PWM_INFO(...)
#define DBG_I2S_INFO(...)
#define DBG_SDIO_HOST_INFO(...)
#define DBG_SDHOST_INFO(...)
#define DBG_OTG_INFO(...)
#define DBG_MII_INFO(...)
#define DBG_WLAN_INFO(...)
#define DBG_SGPIO_INFO(...)
#define DBG_SPORT_INFO(...)
#define DBG_AUDIO_INFO(...)
#define DBG_PCM_INFO(...)
#define DBG_ISP_INFO(...)
#define DBG_ENC_INFO(...)
#define DBG_OTP_INFO(...)
#define DBG_FLASH_SEC_INFO(...)
#define DBG_MISC_INFO(...)
#define DBG_RSA_INFO(...)
#define DBG_SNAND_INFO(...)
#define DBG_DRAM_INFO(...)


#endif

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define IDENT_ONE_SPACE    " "
#define IDENT_TWO_SPACE    "  "
#define IDENT_FOUR_SPACE   "    "
#define IDENT_SIX_SPACE    "      "
#define IDENT_EIGHT_SPACE  "        "

#if CONFIG_DEBUG_LOG
typedef enum _DBG_CFG_TYPE_ {
	DBG_CFG_ERR = 0,
	DBG_CFG_WARN = 1,
	DBG_CFG_INFO = 2
} DBG_CFG_TYPE;

typedef struct _DBG_CFG_CMD_ {
	u8 cmd_name[16];
	u32 cmd_type;
} DBG_CFG_CMD, *PDBG_CFG_CMD;

#endif

typedef enum _CONSOLE_OP_STAGE_ {
	ROM_STAGE = 0,
	RAM_STAGE = 1
} CONSOLE_OP_STAGE;

#endif //_DIAG_H_
