/**************************************************************************//**
 * @file     section_config.h
 * @brief    Defines section name for code text or data, then we can locate
 *           them to a specific address.
 *
 * @version  V1.00
 * @date     2022-02-16
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

#ifndef _SECTION_CONFIG_H_
#define _SECTION_CONFIG_H_

#include "platform_conf.h"
#include "basic_types.h"

#define INFRA_ROM_TEXT_SECTION                  SECTION(".infra.rom.text")
#define INFRA_ROM_DATA_SECTION                  SECTION(".infra.rom.data")
#define INFRA_ROM_BSS_SECTION                   SECTION(".infra.rom.bss")

#define START_RAM_FUN_A_SECTION                 SECTION(".start.ram.data.a")

#define START_RAM_SIGNATURE_SECTION             SECTION(".start.ram.sign")

#define BL4FW_RAM_DATA_SECTION                  SECTION(".bl4fw.ram.data")

#define BL4VOE_RAM_DATA_SECTION                 SECTION(".bl4voe.ram.data")

#define BL4VOE_LDINFO_RAM_DATA_SECTION          SECTION(".bl4voe.ldinfo.ram.data")

#define BL4VOE_PERI_RAM_DATA_SECTION            SECTION(".bl4voe.peri.ram.data")

#define SECTION_RAM_VECTOR_TABLE                SECTION(".ram_vector_table")

//WLAN Section
#define WLAN_ROM_STUB_SECTION                           \
        SECTION(".rom.wlan.stubs")

#define WLAN_ROM_TEXT_SECTION                           \
        SECTION(".rom.wlan.text")

#define WLAN_ROM_DATA_SECTION                           \
        SECTION(".rom.wlan.rodata")

#define WLAN_RAM_MAP_SECTION                            \
        SECTION(".rom.wlan.bss")

//Apple Section
#define APPLE_ROM_STUB_SECTION                          \
        SECTION(".rom.apple.stubs")

#define APPLE_ROM_TEXT_SECTION                          \
        SECTION(".rom.apple.text")

#define APPLE_ROM_DATA_SECTION                          \
        SECTION(".rom.apple.rodata")

//SSL Section
#define SSL_ROM_STUB_SECTION                           \
        SECTION(".rom.ssl.stubs")

#define SSL_ROM_TEXT_SECTION                           \
        SECTION(".rom.ssl.text")

#define SSL_ROM_DATA_SECTION                           \
        SECTION(".rom.ssl.rodata")

#define SSL_RAM_MAP_SECTION                            \
        SECTION(".rom.ssl.bss")

//For external ram section(PSRAM and LPDDR)
#define SDRAM_DATA_SECTION                              \
        SECTION(".sdram.data")

#define SDRAM_BSS_SECTION                               \
        SECTION(".sdram.bss")

#define SDRAM_TEXT_SECTION                              \
        SECTION(".sdram.text")

#define SDRAM_RODATA_SECTION                            \
        SECTION(".sdram.rodata")

// Temp buffer for ROM code
#define SECTION_ROM_TEMP_BSS                    SECTION(".rom_temp.bss")
#define SECTION_ROM_ICC_TEMP_BSS                SECTION(".rom_icc_temp.bss")

// Section for Non-Secure Callable function
#define SECTION_NS_ENTRY_FUNC                   SECTION(".ns_entry_func.text")

// non-cacheable data memory
#define NC_DATA_SECTION                         SECTION(".non_cache.data")
#define NC_BSS_SECTION                          SECTION(".non_cache.bss")

#define SECTION_SYS_RESTORE                     SECTION(".sys_restore.bss")
#define SECTION_RAM_ENTRY_FUNC                  SECTION(".ram_entry_func.text")
#define SECTION_CINIT_ENTRY_FUNC                SECTION(".cinit_entry_func.data")

// sections for ITCM RAM
#define ITCM_RAM_TEXT_SECTION                   SECTION(".itcm_ram.text")
#define ITCM_RAM_RODATA_SECTION                 SECTION(".itcm_ram.rodata")

// sections for internal SRAM
#define RAM_BSS_NOINIT_SECTION                  SECTION(".ram.bss.noinit")

// sections for DTCM RAM
#define DTCM_RAM_BSS_SECTION                    SECTION(".dtcm_ram.bss")
#define DTCM_RAM_BSS_NOINIT_SECTION             SECTION(".dtcm_ram.bss.noinit")

// sections for external LPDDR
#define LPDDR_TEXT_SECTION                      SECTION(".lpddr.text")
#define LPDDR_RODATA_SECTION                    SECTION(".lpddr.rodata")
#define LPDDR_DATA_SECTION                      SECTION(".lpddr.data")
#define LPDDR_BSS_SECTION                       SECTION(".lpddr.bss")
#define LPDDR_BSS_NOINIT_SECTION                SECTION(".lpddr.bss.noinit")


#if defined (CONFIG_EXRAM_LPDDR_EN) && (CONFIG_EXRAM_LPDDR_EN == 1)
#define EXTRAM_TEXT_SECTION                     LPDDR_TEXT_SECTION
#define EXTRAM_RODATA_SECTION                   LPDDR_RODATA_SECTION
#define EXTRAM_DATA_SECTION                     LPDDR_DATA_SECTION
#define EXTRAM_BSS_SECTION                      LPDDR_BSS_SECTION
#else
#define EXTRAM_TEXT_SECTION
#define EXTRAM_RODATA_SECTION
#define EXTRAM_DATA_SECTION
#define EXTRAM_BSS_SECTION
#endif

// sections for Flash-XIP
#define XIP_TEXT_SECTION                        SECTION(".xip.text")
#define XIP_RODATA_SECTION                      SECTION(".xip.rodata")

#if !defined (CONFIG_BUILD_NONSECURE)
// Section for Non-Secure BSS RAM
#define SECTION_NS_BSS                          SECTION(".nonsecure.bss")
#else
// Section for Non-Secure BSS RAM
#define SECTION_NS_BSS
#endif

#endif //_SECTION_CONFIG_H_

