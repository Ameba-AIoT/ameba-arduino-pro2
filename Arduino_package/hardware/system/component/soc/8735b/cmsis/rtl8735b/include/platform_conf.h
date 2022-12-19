/**************************************************************************//**
 * @file     platform_conf.h
 * @brief    The configuration for AmebaPro2 (TM9) platform.
 * @version  V1.00
 * @date     2022-07-27
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

#ifndef _RTL8735B_CONF_H_
#define _RTL8735B_CONF_H_

/* System configuration */
#define RTL8735B                            1

// NOTE Do not directly use these macro, use IS_CUT_ macro instead
#define CHIP_TEST_CUT                       0
#define CHIP_A_CUT                          1
#define CHIP_B_CUT                          2
#define CHIP_C_CUT                          3
#define CHIP_D_CUT                          4


#define IS_CUT_TEST(chip)                   (CHIP_TEST_CUT == chip)
#define IS_CUT_A(chip)                      (CHIP_A_CUT == chip)
#define IS_CUT_B(chip)                      (CHIP_B_CUT == chip)
#define IS_CUT_C(chip)                      (CHIP_C_CUT == chip)
#define IS_CUT_D(chip)                      (CHIP_D_CUT == chip)
#define IS_AFTER_CUT_A(chip)                (CHIP_A_CUT <= chip)
#define IS_AFTER_CUT_B(chip)                (CHIP_B_CUT <= chip)
#define IS_AFTER_CUT_C(chip)                (CHIP_C_CUT <= chip)
#define IS_AFTER_CUT_D(chip)                (CHIP_D_CUT <= chip)


#define CONFIG_CHIP_VER							CHIP_B_CUT

#define CONFIG_FPGA                         0
#define CONFIG_PXP                          0
#define CONFIG_ASIC                         1

#if CONFIG_FPGA // FPGA
#define XTAL                                (20000000U)     /* 20Mhz */
#define CONFIG_VOE_CLK                      (20000000U)     /* 20Mhz */
#define CONFIG_CPU_CLK                      (XTAL)
#define PLATFORM_SCLK                       (40000000)       /* FPGA PCLK 40MHz for UART*/

#elif CONFIG_PXP // PXP
#define CONFIG_CPU_CLK                      (500000000U)    /* 500Mhz */
#define PLATFORM_SCLK                       (40000000U)     /* 40Mhz */

#else  // ASIC
#define CONFIG_VOE_CLK                      (250000000U)    /* 250Mhz */
#define CONFIG_CPU_CLK                      (500000000U)    /* 500Mhz */
#define PLATFORM_SCLK                       (40000000U)     /* 40Mhz */
#endif

#if !defined (CONFIG_BUILD_SECURE) && !defined (CONFIG_BUILD_NONSECURE)
/* Ignore Secure(All secure) peripheral device configuration */
#include "platform_conf_ntz.h"
#else
/*  Trustzone world peripheral device configuration */
#include "platform_conf_tz.h"
#endif


/* ROM code version */
#define ROM_VER_MAIN                        (CONFIG_CHIP_VER+1)
#define ROM_VER_SUB                         (0)


#define CONFIG_DEBUG_LOG                    1
#define CONFIG_DEBUG_ERROR                  1
#define CONFIG_DEBUG_WARN                   1
#define CONFIG_DEBUG_INFO                   1


#define CONFIG_CMSIS_FREERTOS_EN            1
#define CONFIG_CMSIS_TZ_FREERTOS            1

#if CONFIG_ASIC // ASIC (Default enable boot trap pin feature)
#define CONFIG_BOOT_TRAP_CTRL               1
#define CONFIG_BOOT_LD_VOE_CTRL             1   // (Default enable load VOE feature)

#else // FPGA, PXP (Default not enable boot trap pin feature)
#define CONFIG_BOOT_TRAP_CTRL               0
#define CONFIG_BOOT_LD_VOE_CTRL             0   // (Default disable load VOE feature)

#endif

#define CONFIG_BOOT_SETMOD_EN               0

#if CONFIG_FPGA
// Default disable OTP simulation Setting value for autoload; only for FPGA
#define CONFIG_BOOT_OTP_SIMU_AUTO_EN            (0)

// Default disable Debug port select(interface/pinmux) from otp autoload; only for FPGA
#define CONFIG_BOOT_DBG_PORT_AUTO_SEL_EN        (0)
#define CONFIG_SJTAG_SIMU_EN                    (0)   // SIMU SJTAG USING, Default Disable
#define CONFIG_HIGH_VAL_RANDOM_LOAD_EN          (0)   // SIMU HIGH_VAL_RNG_LOAD, Default Disable
#define CONFIG_SIMU_ASIC_FLOW_EN                (0)   // SIMU ASIC_FLOW_EN, Default Disable
#endif

#if CONFIG_ASIC // ASIC (Default enable cache)
#define CONFIG_ROM_ICACHE_EN                    1
#define CONFIG_ROM_DCACHE_EN                    1
#define CONFIG_BOOTLOAD_DCACHE_EN               1
#define CONFIG_RAM_START_CACHE_EN               1

#else // FPGA, PXP (Default enable cache)
#define CONFIG_ROM_ICACHE_EN                    1
#define CONFIG_ROM_DCACHE_EN                    1
#define CONFIG_BOOTLOAD_DCACHE_EN               1
#define CONFIG_RAM_START_CACHE_EN               1

#endif

// Enable top registers use test-chip version
#define CONFIG_TOPREG_TESTCHIP_EN               (0)

// default enable IRQ
#define CONFIG_SW_XMODEM_EN                 1
#define CONFIG_MISC_EN                      0
#define CONFIG_SYSON_EN                     0
#define CONFIG_CACHE_EN                     1
#define CONFIG_PINMUX_EN                    0
#define CONFIG_VENDOR_EN                    0

#define CONFIG_BOOTLOAD_LOG_EN              (1)   // default enable boot loader log
#define CONFIG_CMSIS_OS_EN                  CONFIG_CMSIS_FREERTOS_EN


#define CONFIG_LIGHT_PRINTF                 1   // use lighter printf (use smaller stack size)
#define CONFIG_SYS_TIMER_ID                 0   // the G-Timer ID be used as free run system ticker
#define CONFIG_TIMER_SCLK_FREQ              (2000000)   // GTimer SCLK: 32K/ 2M / 20M
#if (CONFIG_TIMER_SCLK_FREQ == 32000)
#define CONFIG_SYS_TICK_TIME                (1000000/CONFIG_TIMER_SCLK_FREQ)   // in us
#else
#define CONFIG_SYS_TICK_TIME                (1)   // in us
#endif

#if CONFIG_FPGA  // FPGA
#if IS_CUT_TEST(CONFIG_CHIP_VER)    // Test-chip
#define STDIO_UART_TX_PIN                   (PIN_F5)    // GPIO F_5
#define STDIO_UART_RX_PIN                   (PIN_F4)    // GPIO F_4
#else   // A-cut
#define STDIO_UART_TX_PIN                   (PIN_F4)    // GPIO F_4
#define STDIO_UART_RX_PIN                   (PIN_F3)    // GPIO F_3
#endif
#elif CONFIG_PXP  // PXP
#define STDIO_UART_TX_PIN                   (PIN_A2)    // GPIO A_2
#define STDIO_UART_RX_PIN                   (PIN_A3)    // GPIO A_3

#else  // ASIC
#if IS_CUT_TEST(CONFIG_CHIP_VER)    // Test-chip
#define STDIO_UART_TX_PIN                   (PIN_F5)    // GPIO F_5
#define STDIO_UART_RX_PIN                   (PIN_F4)    // GPIO F_4
#else  // A-cut
#define STDIO_UART_TX_PIN                   (PIN_F4)    // GPIO F_4
#define STDIO_UART_RX_PIN                   (PIN_F3)    // GPIO F_3
#endif
#endif

/* Verifi each IP configuration */
#define CONFIG_VRF_MODE                      0

#define CONFIG_VERIFY_EN                    1     // verify code enable

#if CONFIG_PXP  // PXP(Default not load flash img)
#define LOAD_FLAH_IMG_EN                    (0)   // is enable to load the image from the flash

#else // FPGA, ASIC
#define LOAD_FLAH_IMG_EN                    (1)   // is enable to load the image from the flash
#endif

#if CONFIG_FPGA
#define LOAD_NAND_FLASH_IMG_EN              (0)   // is enable to load the image from the NAND flash for FPGA OTP simu flow
#endif

#if CONFIG_ASIC  // ASIC(Default not run PXP DDR Init flow)
#define SIMU_DDR_PXP_INIT_FLOW_EN           (0)   // is enable to run PXP DDR init flow
#define POST_SIMU_ADJUST_FLOW_EN            (0)   // is enable to run post-simu related flow

#endif

#define FCS_SIMU_DISABLE_KM_BLDR_INIT_EN    (0)   // is enable to skip boot loader voe ram init process

#if IS_CUT_TEST(CONFIG_CHIP_VER)    // Test-chip
#define LOAD_FLAH_IMG_NEW_FORMAT            (0)   // IMG new format(TLV), Default Disable for test-chip
#else   // other cuts
#define LOAD_FLAH_IMG_NEW_FORMAT            (1)   // IMG new format(TLV), Default Enable for other cuts
#endif
#define LOAD_FLAH_IMG_NEW_FORMAT_SECTLD_VRF_EN  (0)   // IMG new format(TLV) IMG sections load hash check, Default Disable
#define LOAD_FLAH_IMG_NEW_FORMAT_IMGHSH_EN      (0)   // IMG new format(TLV) IMG hash check boot, Default Disable
#define LOAD_FLAH_IMG_NEW_FORMAT_TB_EN          (0)   // IMG new format(TLV) Trust boot, Default Disable
#define LOAD_FLAH_IMG_NEW_FORMAT_SB_EN          (0)   // IMG new format(TLV) Secure boot, Default Disable

#if CONFIG_FPGA
#define LOAD_RMA0_PTN_EN                        (0)   // Load RMA0 PTN, Default Disable
#define LOAD_RMA_SIMU_EN                        (0)   // Load RMA SIMU, Default Disable
#define LOAD_CUST_UID_PTN_DIS                   (0)   // Load Customer uid derived huk PTN, Default Not Disable
#endif


#define CONFIG_FLASH_XIP_EN                 (0)   // is enable the Flash XIP (eXecute In Place)
#define CONFIG_EXRAM_LPDDR_EN               (1)   // is DDR memory present on this platform

#define CONFIG_EXRAM_EN                     (CONFIG_EXRAM_LPDDR_EN)   // is enable EXternal RAM (PSRAM/LPDDR)

#define CONFIG_HEAP0_EN                      1    // Memory management HEAP0 (DDR CB) Enable
#define CONFIG_HEAP1_EN                      1    // Memory management HEAP1 (SRAM CB) Enable
#define CONFIG_HEAP2_EN                      0    // Memory management HEAP2 (DDR NCB) Enable


#define CONFIG_FBOOT_AUTH                   (0)   /* is do IMG2 authentication on fast reboot.
                                                  // if the FW image is encrypted then should rise this flag */

#if (CONFIG_CHIP_VER > CHIP_TEST_CUT)
#define HARD_FAULT_BACK_TRACE               (0)     // is enable the stack back trace for hard fault exception
#else
#define HARD_FAULT_BACK_TRACE               (0)
#endif

#if defined(CONFIG_BUILD_RAM) && (CONFIG_BUILD_RAM == 1)
#if defined(CONFIG_BUILD_SECURE)
#define __STACK_SIZE                        (0x1000)    // main stack memory size of secure region
#elif defined(CONFIG_BUILD_NONSECURE)
#define __STACK_SIZE                        (0x1000)    // main stack memory size of non-secure region
#else
#define __STACK_SIZE                        (0x1000)    // main stack memory size of ignore-secure
#endif
#endif  // end of "#if defined(CONFIG_BUILD_RAM) && (CONFIG_BUILD_RAM == 1)"

// Application layer related configuration
#define CONFIG_CMSIS_DSP_EN                  0       // cmsis-dsp enable

#define CONFIG_SEMIHOST_EN                   1       // SEGGER semihosting enable
#define CONFIG_DHRYSTONE_EN                  1       // SEGGER Dhryston enable

#define CONFIG_PMC_LIB_EN                    1       // Use power management libray

#include "verify_conf.h"
#include "sw_feature_conf.h"

#endif  // end of "#define _RTL8735B_CONF_H_"

