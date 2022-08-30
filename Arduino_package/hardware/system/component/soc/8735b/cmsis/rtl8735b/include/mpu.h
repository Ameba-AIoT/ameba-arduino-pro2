/**************************************************************************//**
 * @file     mpu.h
 * @brief    Defines macros for the MPU registers seting.
 *
 * @version  V1.00
 * @date     2017-03-21
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

#ifndef _MPU_H_
#define _MPU_H_

#define MPU_MAX_REGION              8
/*
Outer, bits [7:4]:
0b0000 Device memory.
0b00RW Normal memory, Outer write-through transient (RW!='00').
0b0100 Normal memory, Outer non-cacheable.
0b01RW Normal memory, Outer write-back transient (RW!='00').
0b10RW Normal memory, Outer write-through non-transient.
0b11RW Normal memory, Outer write-back non-transient.
*/

/* The transient attribute indicates that the benefit of caching is for a relatively short period,
   and that therefore it might be better to restrict allocation, to avoid possibly casting-out other,
   less transient, entries. */

// define memory attribute of Normal memory with Outer write-through transient, outer write allocation
#define NORMAL_O_WT_T_WA            ((0x01) << 4)

// define memory attribute of Normal memory with Outer write-through transient, outer read allocation
#define NORMAL_O_WT_T_RA            ((0x02) << 4)

// define memory attribute of Normal memory with Outer write-through transient, outer read and write allocation
#define NORMAL_O_WT_T_RWA           ((0x03) << 4)

// define memory attribute of Normal memory with Outer non-cacheable.
#define NORMAL_O_NC                 ((0x04) << 4)

// define memory attribute of Normal memory with Outer write-back transient, outer write allocation
#define NORMAL_O_WB_T_WA            ((0x05) << 4)

// define memory attribute of Normal memory with Outer write-back transient, outer read allocation
#define NORMAL_O_WB_T_RA            ((0x06) << 4)

// define memory attribute of Normal memory with Outer write-back transient, outer read and write allocation
#define NORMAL_O_WB_T_RWA           ((0x07) << 4)

// define memory attribute of Normal memory with Outer write-through non-transient, no outer allocation
#define NORMAL_O_WT_NT              ((0x08) << 4)

// define memory attribute of Normal memory with Outer write-through non-transient, outer write allocation
#define NORMAL_O_WT_NT_WA           ((0x09) << 4)

// define memory attribute of Normal memory with Outer write-through non-transient, outer read allocation
#define NORMAL_O_WT_NT_RA           ((0x0A) << 4)

// define memory attribute of Normal memory with Outer write-through non-transient, outer read and write allocation
#define NORMAL_O_WT_NT_RWA          ((0x0B) << 4)

// define memory attribute of Normal memory with Outer write-back non-transient, no outer allocation
#define NORMAL_O_WB_NT              ((0x0C) << 4)

// define memory attribute of Normal memory with Outer write-back non-transient, outer write allocation
#define NORMAL_O_WB_NT_WA           ((0x0D) << 4)

// define memory attribute of Normal memory with Outer write-back non-transient, outer read allocation
#define NORMAL_O_WB_NT_RA           ((0x0E) << 4)

// define memory attribute of Normal memory with Outer write-back non-transient, outer read & write allocation
#define NORMAL_O_WB_NT_RWA          ((0x0F) << 4)

/*
Inner, bits [3:0], when Outer != '0000'
0b00RW Normal memory, Inner write-through transient (RW!='00').
0b0100 Normal memory, Inner non-cacheable.
0b01RW Normal memory, Inner write-back transient (RW!='00').
0b10RW Normal memory, Inner write-through non-transient.
0b11RW Normal memory, Inner write-back non-transient
*/

// define memory attribute of Normal memory with Inner write-through transient, Inner write allocation
#define NORMAL_I_WT_T_WA            (0x01)

// define memory attribute of Normal memory with Inner write-through transient, Inner read allocation
#define NORMAL_I_WT_T_RA            (0x02)

// define memory attribute of Normal memory with Inner write-through transient, Inner read & write allocation
#define NORMAL_I_WT_T_RWA           (0x03)

// define memory attribute of Normal memory with Inner non-cacheable
#define NORMAL_I_NC                 (0x04)

// define memory attribute of Normal memory with Inner write-back transient, Inner write allocation
#define NORMAL_I_WB_T_WA            (0x05)

// define memory attribute of Normal memory with Inner write-back transient, Inner read allocation
#define NORMAL_I_WB_T_RA            (0x06)

// define memory attribute of Normal memory with Inner write-back transient, Inner read and write allocation
#define NORMAL_I_WB_T_RWA           (0x07)

// define memory attribute of Normal memory with Inner write-through non-transient, no Inner allocation
#define NORMAL_I_WT_NT              (0x08)

// define memory attribute of Normal memory with Inner write-through non-transient, Inner write allocation
#define NORMAL_I_WT_NT_WA           (0x09)

// define memory attribute of Normal memory with Inner write-through non-transient, Inner read allocation
#define NORMAL_I_WT_NT_RA           (0x0A)

// define memory attribute of Normal memory with Inner write-through non-transient, Inner read and write allocation
#define NORMAL_I_WT_NT_RWA          (0x0B)

// define memory attribute of Normal memory with Inner write-back non-transient, no Inner allocation
#define NORMAL_I_WB_NT              (0x0C)

// define memory attribute of Normal memory with Inner write-back non-transient, Inner write allocation
#define NORMAL_I_WB_NT_WA           (0x0D)

// define memory attribute of Normal memory with Inner write-back non-transient, Inner read allocation
#define NORMAL_I_WB_NT_RA           (0x0E)

// define memory attribute of Normal memory with Inner write-back non-transient, Inner read and write allocation
#define NORMAL_I_WB_NT_RWA          (0x0F)

/*
Device, bits [3:2], when Outer == '0000':
0b00 Device-nGnRnE.
0b01 Device-nGnRE.
0b10 Device-nGRE.
0b11 Device-GRE.
*/
// define memory attribute of Device memory with non-gathering, non-reording, non-Early Write Acknowledge
#define DEVICE_NG_NR_NE             ((0<<4)|(0<<2))

// define memory attribute of Device memory with non-gathering, non-reording, Early Write Acknowledge
#define DEVICE_NG_NR_E              ((0<<4)|(1<<2))

// define memory attribute of Device memory with non-gathering, reording, Early Write Acknowledge
#define DEVICE_NG_R_E               ((0<<4)|(2<<2))

// define memory attribute of Device memory with gathering, reording, Early Write Acknowledge
#define DEVICE_G_R_E                ((0<<4)|(3<<2))

/*
eXecute Never attribute(MPU_RBAR[0]):
0: Allow program execution in this region.
1: Does not allow program execution in this region.
*/
//#define MPU_EXEC_ALLOW              (0)
//#define MPU_EXEC_NEVER              (1)

enum mpu_region_xn_e {
	MPU_EXEC_ALLOW = 0,
	MPU_EXEC_NEVER = 1
};
typedef uint8_t   mpu_region_xn_t;

/*
Access permissions (MPU_RBAR[2:1]):
00: Read/write by privileged code only.
01: Read/write by any privilege level.
10: Read only by privileged code only.
11: Read only by any privilege level.
*/

enum mpu_region_ap_e {
	MPU_PRIV_RW = (0 << 1),
	MPU_UN_PRIV_RW = (1 << 1),
	MPU_PRIV_R = (2 << 1),
	MPU_PRIV_W = (3 << 1)
};
typedef uint8_t   mpu_region_ap_t;

// MPU Region enable(MPU_RLAR[0])
enum mpu_region_en_e {
	MPU_REGION_DISABLE =     0,
	MPU_REGION_ENABLE =      1
};
typedef uint8_t   mpu_region_en_t;

/*
Shareability for Normal memory(MPU_RBAR[4:3]):
00: Non-shareable.
01: Reserved.
10: Outer shareable.
11: Inner shareable.
*/
enum mpu_region_sh_e {
	MPU_NON_SHAREABLE = (0 << 3),
	MPU_OUT_SHAREABLE = (2 << 3),
	MPU_INR_SHAREABLE = (3 << 3)
};
typedef uint8_t   mpu_region_sh_t;

/**
  \brief  The data structure for a MPU region configuration
*/
typedef struct mpu_region_config_s {
	uint32_t region_base;       // MPU region base, 32 bytes aligned
	uint32_t region_limit;      // MPU region limit, 32 bytes aligned
	mpu_region_xn_t  xn;        // eXecute Never attribute
	mpu_region_ap_t  ap;        // Access permissions
	mpu_region_sh_t  sh;        // Shareability for Normal memory
	uint8_t  attr_idx;          // memory attribute indirect index
} mpu_region_config_t, *pmpu_region_config_t;

void mpu_init(void);
void mpu_set_mem_attr(uint8_t attr_idx, uint8_t mem_attr);
void mpu_region_cfg(uint8_t region_num, mpu_region_config_t *pmpu_cfg);

#endif //_MPU_H_

