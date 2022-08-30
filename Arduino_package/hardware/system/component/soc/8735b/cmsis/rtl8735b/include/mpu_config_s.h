/**************************************************************************//**
 * @file     mpu_config_s.h
 * @brief    Defines macros for the MPU configuration for the Secure region.
 *
 * @version  V1.00
 * @date     2021-03-26
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

#ifndef _MPU_CONFIG_S_H_
#define _MPU_CONFIG_S_H_

#include "mpu.h"
/*
//   <q> Enable MPU
//   <i> Value for MPU->CTRL register bit ENABLE
//     <0=> MPU is disabled.
//     <1=> MPU is enabled.
*/
#define MPU_INIT_CTRL_ENABLE            1

/*
//   <i> Value for MPU->CTRL register bit PRIVDEFENA
//       Privileged background region enable:
//     <0=> All accesses to unmapped addresses result in faults.
//     <1=> Enables the default memory map for privilege code when the address accessed
//          does not map into any MPU region. Unprivileged accesses to unmapped addresses
//          result in faults.
*/
#define MPU_INIT_CTRL_PRIVDEFENA        1

/*
//   <i> Value for MPU->CTRL register bit HFNMIENA
//       MPU Enable for HardFault and NMI (Non-Maskable Interrupt):
//     <0=> HardFault and NMI handlers bypass MPU configuration as if MPU is disabled.
//     <1=> MPU access rules apply to HardFault and NMI handlers.
*/
#define MPU_INIT_CTRL_HFNMIENA          0

// The memory attribute configuration of the MAIR[Attr0]
#define MPU_MEM_ATTR0                   (NORMAL_O_NC | NORMAL_I_NC)

// The memory attribute configuration of the MAIR[Attr1]
#define MPU_MEM_ATTR1                   (NORMAL_O_WT_T_RA | NORMAL_I_WT_T_RA)

// The memory attribute configuration of the MAIR[Attr2]
#define MPU_MEM_ATTR2                   (NORMAL_O_WB_T_RA | NORMAL_I_WB_T_RA)

// The memory attribute configuration of the MAIR[Attr3]
#define MPU_MEM_ATTR3                   (NORMAL_O_WT_NT_RA | NORMAL_I_WT_NT_RA)

// The memory attribute configuration of the MAIR[Attr4]
#define MPU_MEM_ATTR4                   (NORMAL_O_WB_NT_RA | NORMAL_I_WB_NT_RA)

// The memory attribute configuration of the MAIR[Attr5]
#define MPU_MEM_ATTR5                   (NORMAL_O_WB_T_RWA | NORMAL_I_WB_T_RWA)

// The memory attribute configuration of the MAIR[Attr6]
#define MPU_MEM_ATTR6                   (NORMAL_O_WB_NT_RWA | NORMAL_I_WB_NT_RWA)

// The memory attribute configuration of the MAIR[Attr7]
#define MPU_MEM_ATTR7                   (DEVICE_NG_NR_NE)

// MPU region 0 configuration
#define MPU_REGION0_EN                  0   // If MPU region 0 configuration enabled
// define MPU region 0 configuration
#define MPU_REGION0_BASE                (0x2013D000)        /* region base, the address must be aligned to multiple of 32 bytes,
                                                               it should sync. with the linker script */
#define MPU_REGION0_LIMIT               (0x2013FA00)        // region limit, it should sync. with linker script
#define MPU_REGION0_XN                  MPU_EXEC_ALLOW      // eXecute Never attribute
#define MPU_REGION0_AP                  MPU_UN_PRIV_RW      // Access permissions
#define MPU_REGION0_SH                  MPU_OUT_SHAREABLE   // Shareability for Normal memory
#define MPU_REGION0_ATTR_IDX            0                   // the memory attribute indirect index of the MAIR0/1

// MPU region 1 configuration
#define MPU_REGION1_EN                  1   // If MPU region 1 configuration enabled
// define MPU region 1 configuration
#define MPU_REGION1_BASE                (0x08000000)        /* region base, the address must be aligned to multiple of 32 bytes,
                                                               it should sync. with the linker script */
#define MPU_REGION1_LIMIT               (0x08001FFF)        // region limit, it should sync. with linker script
#define MPU_REGION1_XN                  MPU_EXEC_NEVER      // eXecute Never attribute
#define MPU_REGION1_AP                  MPU_UN_PRIV_RW      // Access permissions
#define MPU_REGION1_SH                  MPU_OUT_SHAREABLE   // Shareability for Normal memory
#define MPU_REGION1_ATTR_IDX            0                   // the memory attribute indirect index of the MAIR0/1

// MPU region 2 configuration
#define MPU_REGION2_EN                  0   // If MPU region 2 configuration enabled
// define MPU region 2 configuration
#define MPU_REGION2_BASE                (0x20179E00)        /* region base, the address must be aligned to multiple of 32 bytes,
                                                               it should sync. with the linker script */
#define MPU_REGION2_LIMIT               (0x20179FFF)        // region limit, it should sync. with linker script
#define MPU_REGION2_XN                  MPU_EXEC_ALLOW      // eXecute Never attribute
#define MPU_REGION2_AP                  MPU_UN_PRIV_RW      // Access permissions
#define MPU_REGION2_SH                  MPU_OUT_SHAREABLE   // Shareability for Normal memory
#define MPU_REGION2_ATTR_IDX            2                   // the memory attribute indirect index of the MAIR0/1

// MPU region 3 configuration
#define MPU_REGION3_EN                  0   // If MPU region 3 configuration enabled
// define MPU region 3 configuration
#define MPU_REGION3_BASE                (0x20179E00)        /* region base, the address must be aligned to multiple of 32 bytes,
                                                               it should sync. with the linker script */
#define MPU_REGION3_LIMIT               (0x20179FFF)        // region limit, it should sync. with linker script
#define MPU_REGION3_XN                  MPU_EXEC_ALLOW      // eXecute Never attribute
#define MPU_REGION3_AP                  MPU_UN_PRIV_RW      // Access permissions
#define MPU_REGION3_SH                  MPU_OUT_SHAREABLE   // Shareability for Normal memory
#define MPU_REGION3_ATTR_IDX            2                   // the memory attribute indirect index of the MAIR0/1

// MPU region 4 configuration
#define MPU_REGION4_EN                  0   // If MPU region 4 configuration enabled
// define MPU region 4 configuration
#define MPU_REGION4_BASE                (0x20179E00)        /* region base, the address must be aligned to multiple of 32 bytes,
                                                               it should sync. with the linker script */
#define MPU_REGION4_LIMIT               (0x20179FFF)        // region limit, it should sync. with linker script
#define MPU_REGION4_XN                  MPU_EXEC_ALLOW      // eXecute Never attribute
#define MPU_REGION4_AP                  MPU_UN_PRIV_RW      // Access permissions
#define MPU_REGION4_SH                  MPU_OUT_SHAREABLE   // Shareability for Normal memory
#define MPU_REGION4_ATTR_IDX            2                   // the memory attribute indirect index of the MAIR0/1

// MPU region 5 configuration
#define MPU_REGION5_EN                  0   // If MPU region 5 configuration enabled
// define MPU region 5 configuration
#define MPU_REGION5_BASE                (0x20179E00)        /* region base, the address must be aligned to multiple of 32 bytes,
                                                               it should sync. with the linker script */
#define MPU_REGION5_LIMIT               (0x20179FFF)        // region limit, it should sync. with linker script
#define MPU_REGION5_XN                  MPU_EXEC_ALLOW      // eXecute Never attribute
#define MPU_REGION5_AP                  MPU_UN_PRIV_RW      // Access permissions
#define MPU_REGION5_SH                  MPU_OUT_SHAREABLE   // Shareability for Normal memory
#define MPU_REGION5_ATTR_IDX            2                   // the memory attribute indirect index of the MAIR0/1

// MPU region 6 configuration
#define MPU_REGION6_EN                  0   // If MPU region 6 configuration enabled
// define MPU region 6 configuration
#define MPU_REGION6_BASE                (0x20179E00)        /* region base, the address must be aligned to multiple of 32 bytes,
                                                               it should sync. with the linker script */
#define MPU_REGION6_LIMIT               (0x20179FFF)        // region limit, it should sync. with linker script
#define MPU_REGION6_XN                  MPU_EXEC_ALLOW      // eXecute Never attribute
#define MPU_REGION6_AP                  MPU_UN_PRIV_RW      // Access permissions
#define MPU_REGION6_SH                  MPU_OUT_SHAREABLE   // Shareability for Normal memory
#define MPU_REGION6_ATTR_IDX            2                   // the memory attribute indirect index of the MAIR0/1

// MPU region 7 configuration
#define MPU_REGION7_EN                  0   // If MPU region 7 configuration enabled
// define MPU region 7 configuration
#define MPU_REGION7_BASE                (0x20179E00)        /* region base, the address must be aligned to multiple of 32 bytes,
                                                               it should sync. with the linker script */
#define MPU_REGION7_LIMIT               (0x20179FFF)        // region limit, it should sync. with linker script
#define MPU_REGION7_XN                  MPU_EXEC_ALLOW      // eXecute Never attribute
#define MPU_REGION7_AP                  MPU_UN_PRIV_RW      // Access permissions
#define MPU_REGION7_SH                  MPU_OUT_SHAREABLE   // Shareability for Normal memory
#define MPU_REGION7_ATTR_IDX            2                   // the memory attribute indirect index of the MAIR0/1

#define MPU_REGION_CFG_EN               ((MPU_REGION7_EN << 7) | (MPU_REGION6_EN << 6) | \
                                         (MPU_REGION5_EN << 5) | (MPU_REGION4_EN << 4) | \
                                         (MPU_REGION3_EN << 3) | (MPU_REGION2_EN << 2) | \
                                         (MPU_REGION1_EN << 1) | (MPU_REGION0_EN))
#endif //_MPU_CONFIG_S_H_

