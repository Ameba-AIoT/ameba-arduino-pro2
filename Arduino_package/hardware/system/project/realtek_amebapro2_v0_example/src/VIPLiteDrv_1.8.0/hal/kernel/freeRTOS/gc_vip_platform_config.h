/******************************************************************************\
|* Copyright (c) 2017-2022 by Vivante Corporation.  All Rights Reserved.      *|
|*                                                                            *|
|* The material in this file is confidential and contains trade secrets of    *|
|* of Vivante Corporation.  This is proprietary information owned by Vivante  *|
|* Corporation.  No part of this work may be disclosed, reproduced, copied,   *|
|* transmitted, or used in any way for any purpose, without the express       *|
|* written permission of Vivante Corporation.                                 *|
|*                                                                            *|
\******************************************************************************/


#ifndef _GC_VIP_PLATFORM_CONFIG_H
#define _GC_VIP_PLATFORM_CONFIG_H

// rtk, for NN_BASE
#include "rtl8735b.h"
/* the core number of VIP.
   It's for multiple VIP hardware. Please set vpmdCORE_COUNT to 1 if is single core VIP
*/
#define  vpmdCORE_COUNT                  1

/* the logic devices number and core number for each logical device.
 * we need configure this after create nbg files.
 * The core count of logical device should be matched with core count in NBG file.
 * for example: LOGIC_DEVICES_WITH_CORE[8] = {2,2,4,0,0,0,0,0}.
 * indicate that the current driver supports 3 logical device.
 * device[0] and device[1] have 2 cores, device[2] have 4 cores.
 * the others devices not available, each device have different core index.
 * NOTE:
 * LOGIC_DEVICES_WITH_CORE[8] = {2,1,0,4,0,0,0,0}. indicate that driver supports 2 logical device.
 * device[0] is 2 cores, device[1] is 1 core.  the 4 is invalid config.
*/
static const vip_uint32_t LOGIC_DEVICES_WITH_CORE[vpmdCORE_COUNT] = {1};


/* default size 2M for system memory heap, access by CPU only */
#define SYSTEM_MEMORY_HEAP_SIZE         34000 //(2 << 20)

extern uint32_t __nn_eram_start__[];
extern uint32_t __nn_eram_end__[];

/* default size xx bytes for video memory heap, access by VIP */
#define VIDEO_MEMORY_HEAP_SIZE          ( (uint32_t)__nn_eram_end__ - (uint32_t)__nn_eram_start__ ) //(0x900000


/* defalut base pyhsical address of video memory heap */
#define VIDEO_MEMORY_HEAP_BASE_ADDRESS  ( (uint32_t*)__nn_eram_start__ ) //0x32000000


/* AHB register base physical address */
static const vip_uint32_t AHB_REGISTER_BASE_ADDRESS[vpmdCORE_COUNT] = {NN_BASE};

/* The size of AHB register */
static const vip_uint32_t AHB_REGISTER_SIZE[vpmdCORE_COUNT] = {0x800};

/* irq line number */
static const vip_uint32_t IRQ_LINE_NUMBER[vpmdCORE_COUNT] = {NN_IRQn};


/* the size of VIP SRAM */
#define VIP_SRAM_SIZE                   0x20000 //0x100000

/*
The base address of VIP SRAM.
VIP SRAM is a SRAM inside VIP core. It needs to be mapped to a 32 bits address space.
The VIP_SRAM_BASE_ADDRESS is a base address for mapping VIP SRAM, so the VIP SRAM has been mapped to
[VIP_SRAM_BASE_ADDRESS ~~ VIP_SRAM_BASE_ADDRESS + VIP_SRAM_SIZE] range.
After this mapping, VIP core access VIP SRAM through
VIP_SRAM_BASE_ADDRESS ~~ VIP_SRAM_BASE_ADDRESS+VIP_SRAM_SIZE address range.
Actually, The value of VIP_SRAM_BASE_ADDRESS may not be on DRAM.

How to config the VIP_SRAM_BASE_ADDRESS?
1. It can only be a 32bits value.
2. can't be config to zero.
3. It can't be configured to be close to 4Gbytes value.
   (VIP_SRAM_BASE_ADDRESS+vip_sram_size) can't be close to 4Gbytes.
4. It should be align to 64bytes.
5. can't be overlap with video memory range.

example:

The size of DRAM is 1G bytes. So DRAM memory address range is [0 ~~ 0x40000000].
In this case, you can set the value of vip_sram_address to 0x50000000. 0x50000000 is outside of DRAM.
0x50000000 is not a real physical address on SRAM.

If you need to specify address for VIP-SRAM, this value can be outside the range of video memory.
The address shoule be aligned to 64byte.

don't need configure VIP_SRAM_BASE_ADDRESS if set vpmdENABLE_MMU to 1.
Because driver will reserved memory space for VIP-SRAM in MMU page table.
We recomment that remap VIP-SRAM base address to 0x400000 when MMU is disabled.
*/
#define VIP_SRAM_BASE_ADDRESS           0x00

/* the size of AXI SRAM, please set the value to zero if chip without AXI-SRAM.
    otherwise, follow chip real AXI-SRAM size setting. */
#define AXI_SRAM_SIZE                   0 //00x43f000

/* the physical base address of AXI SRAM. The value of AXI_SRAM_BASE_ADDRESS
    is should be real address of AXI-SRAM on chip if the chip have AXI-SRAM. */
#define AXI_SRAM_BASE_ADDRESS           0xffffffff //0xFFD80000

#endif
