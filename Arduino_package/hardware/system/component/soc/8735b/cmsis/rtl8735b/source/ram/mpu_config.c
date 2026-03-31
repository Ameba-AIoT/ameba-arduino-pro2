/**************************************************************************//**
 * @file     mpu_config.c
 * @brief    The functions to configure the MPU.
 * @version  V1.00
 * @date     2021-03-26
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2023 Realtek Corporation. All rights reserved.
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

#include "cmsis.h"
#if defined(CONFIG_BUILD_NONSECURE) && (CONFIG_BUILD_NONSECURE == 1)
#include "mpu_config_ns.h"
#elif defined(CONFIG_BUILD_SECURE) && (CONFIG_BUILD_SECURE == 1)
#include "mpu_config_s.h"
#else
#include "mpu_config.h"
#endif

void mpu_init(void)
{
	if (MPU_REGION_CFG_EN == 0) {
		// no MPU region configuration enabled
		return;
	}
	__DMB(); /* Force any outstanding transfers to complete before disabling MPU */
	/* Disable MPU */
	MPU->CTRL = 0;
	/* Configure memory types */
	MPU->MAIR0 = ((MPU_MEM_ATTR0) << MPU_MAIR0_Attr0_Pos) | \
				 ((MPU_MEM_ATTR1) << MPU_MAIR0_Attr1_Pos) | \
				 ((MPU_MEM_ATTR2) << MPU_MAIR0_Attr2_Pos) | \
				 ((MPU_MEM_ATTR3) << MPU_MAIR0_Attr3_Pos);

	MPU->MAIR1 = ((MPU_MEM_ATTR4) << MPU_MAIR1_Attr4_Pos) | \
				 ((MPU_MEM_ATTR5) << MPU_MAIR1_Attr5_Pos) | \
				 ((MPU_MEM_ATTR6) << MPU_MAIR1_Attr6_Pos) | \
				 ((MPU_MEM_ATTR7) << MPU_MAIR1_Attr7_Pos);

	/* Configure region 0 */
	MPU->RNR = 0;
#if MPU_REGION0_EN
	DBG_MISC_INFO("Set MPU 0: 0x%x ~ 0x%x: \r\n", MPU_REGION0_BASE, MPU_REGION0_LIMIT);
	DBG_MISC_INFO("Shareable=0x%x  AccessPermision=0x%x XNever=0x%x AttrIdx=%lu\r\n", MPU_REGION0_SH, MPU_REGION0_AP, MPU_REGION0_XN, MPU_REGION0_ATTR_IDX);
	MPU->RBAR = (MPU_REGION0_BASE & MPU_RBAR_BASE_Msk) | MPU_REGION0_SH | MPU_REGION0_AP | MPU_REGION0_XN;
	MPU->RLAR = (MPU_REGION0_LIMIT & MPU_RLAR_LIMIT_Msk) | \
				((MPU_REGION0_ATTR_IDX << MPU_RLAR_AttrIndx_Pos) & MPU_RLAR_AttrIndx_Msk) | MPU_REGION_ENABLE;
#endif

	/* Configure region 1 */
#if MPU_REGION1_EN
	DBG_MISC_INFO("Set MPU 1: 0x%x ~ 0x%x: \r\n", MPU_REGION1_BASE, MPU_REGION1_LIMIT);
	DBG_MISC_INFO("Shareable=0x%x  AccessPermision=0x%x XNever=0x%x AttrIdx=%lu\r\n", MPU_REGION1_SH, MPU_REGION1_AP, MPU_REGION1_XN, MPU_REGION1_ATTR_IDX);
	MPU->RBAR_A1 = (MPU_REGION1_BASE & MPU_RBAR_BASE_Msk) | MPU_REGION1_SH | MPU_REGION1_AP | MPU_REGION1_XN;
	MPU->RLAR_A1 = (MPU_REGION1_LIMIT & MPU_RLAR_LIMIT_Msk) | \
				   ((MPU_REGION1_ATTR_IDX << MPU_RLAR_AttrIndx_Pos) & MPU_RLAR_AttrIndx_Msk) | MPU_REGION_ENABLE;
#endif

	/* Configure region 2 */
#if MPU_REGION2_EN
	DBG_MISC_INFO("Set MPU 2: 0x%x ~ 0x%x: \r\n", MPU_REGION2_BASE, MPU_REGION2_LIMIT);
	DBG_MISC_INFO("Shareable=0x%x  AccessPermision=0x%x XNever=0x%x AttrIdx=%lu\r\n", MPU_REGION2_SH, MPU_REGION2_AP, MPU_REGION2_XN, MPU_REGION2_ATTR_IDX);

	MPU->RBAR_A2 = (MPU_REGION2_BASE & MPU_RBAR_BASE_Msk) | MPU_REGION2_SH | MPU_REGION2_AP | MPU_REGION2_XN;
	MPU->RLAR_A2 = (MPU_REGION2_LIMIT & MPU_RLAR_LIMIT_Msk) | \
				   ((MPU_REGION2_ATTR_IDX << MPU_RLAR_AttrIndx_Pos) & MPU_RLAR_AttrIndx_Msk) | MPU_REGION_ENABLE;
#endif

	/* Configure region 3 */
#if MPU_REGION3_EN
	MPU->RBAR_A3 = (MPU_REGION3_BASE & MPU_RBAR_BASE_Msk) | MPU_REGION3_SH | MPU_REGION3_AP | MPU_REGION3_XN;
	MPU->RLAR_A3 = (MPU_REGION3_LIMIT & MPU_RLAR_LIMIT_Msk) | \
				   ((MPU_REGION3_ATTR_IDX << MPU_RLAR_AttrIndx_Pos) & MPU_RLAR_AttrIndx_Msk) | MPU_REGION_ENABLE;
#endif

	/* Configure region 4 */
	MPU->RNR = 4;
#if MPU_REGION4_EN
	MPU->RBAR = (MPU_REGION4_BASE & MPU_RBAR_BASE_Msk) | MPU_REGION4_SH | MPU_REGION4_AP | MPU_REGION4_XN;
	MPU->RLAR = (MPU_REGION4_LIMIT & MPU_RLAR_LIMIT_Msk) | \
				((MPU_REGION4_ATTR_IDX << MPU_RLAR_AttrIndx_Pos) & MPU_RLAR_AttrIndx_Msk) | MPU_REGION_ENABLE;
#endif

	/* Configure region 5 */
#if MPU_REGION5_EN
	MPU->RBAR_A1 = (MPU_REGION5_BASE & MPU_RBAR_BASE_Msk) | MPU_REGION5_SH | MPU_REGION5_AP | MPU_REGION5_XN;
	MPU->RLAR_A1 = (MPU_REGION5_LIMIT & MPU_RLAR_LIMIT_Msk) | \
				   ((MPU_REGION5_ATTR_IDX << MPU_RLAR_AttrIndx_Pos) & MPU_RLAR_AttrIndx_Msk) | MPU_REGION_ENABLE;
#endif

	/* Configure region 6 */
#if MPU_REGION6_EN
	MPU->RBAR_A2 = (MPU_REGION6_BASE & MPU_RBAR_BASE_Msk) | MPU_REGION6_SH | MPU_REGION6_AP | MPU_REGION6_XN;
	MPU->RLAR_A2 = (MPU_REGION6_LIMIT & MPU_RLAR_LIMIT_Msk) | \
				   ((MPU_REGION6_ATTR_IDX << MPU_RLAR_AttrIndx_Pos) & MPU_RLAR_AttrIndx_Msk) | MPU_REGION_ENABLE;
#endif

	/* Configure region 7 */
#if MPU_REGION7_EN
	MPU->RBAR_A3 = (MPU_REGION7_BASE & MPU_RBAR_BASE_Msk) | MPU_REGION7_SH | MPU_REGION7_AP | MPU_REGION7_XN;
	MPU->RLAR_A3 = (MPU_REGION7_LIMIT & MPU_RLAR_LIMIT_Msk) | \
				   ((MPU_REGION7_ATTR_IDX << MPU_RLAR_AttrIndx_Pos) & MPU_RLAR_AttrIndx_Msk) | MPU_REGION_ENABLE;
#endif

	MPU->CTRL |= (MPU_INIT_CTRL_PRIVDEFENA << MPU_CTRL_PRIVDEFENA_Pos) | (MPU_INIT_CTRL_HFNMIENA << MPU_CTRL_HFNMIENA_Pos);

	MPU->CTRL |= (MPU_INIT_CTRL_ENABLE << MPU_CTRL_ENABLE_Pos); /* Enable the MPU */

	__DSB(); /* Force memory writes before continuing */
	__ISB(); /* Flush and refill pipeline with updated permissions */
}

void mpu_set_mem_attr(uint8_t attr_idx, uint8_t mem_attr)
{
	uint32_t mair_mask;
	uint32_t bit_offset;

	if (attr_idx >= 8) {
		return;
	}

	bit_offset = (8 * (attr_idx & 0x03));
	mair_mask = 0xFF << bit_offset;

	if (attr_idx < 4) {
		MPU->MAIR0 &= ~mair_mask;
		MPU->MAIR0 |= mem_attr << bit_offset;
	} else {
		MPU->MAIR1 &= ~mair_mask;
		MPU->MAIR1 |= mem_attr << bit_offset;
	}
}

void mpu_region_cfg(uint8_t region_num, mpu_region_config_t *pmpu_cfg)
{
	if (region_num >= MPU_MAX_REGION) {
		return;
	}

	__DMB(); /* Force any outstanding transfers to complete before disabling MPU */
	/* Disable MPU */
	MPU->CTRL &= ~(1 << MPU_CTRL_ENABLE_Pos);

	MPU->RNR = region_num;
	MPU->RBAR = (pmpu_cfg->region_base & MPU_RBAR_BASE_Msk) | pmpu_cfg->sh | pmpu_cfg->ap | pmpu_cfg->xn;
	MPU->RLAR = (pmpu_cfg->region_limit & MPU_RLAR_LIMIT_Msk) | \
				((pmpu_cfg->attr_idx << MPU_RLAR_AttrIndx_Pos) & MPU_RLAR_AttrIndx_Msk) | MPU_REGION_ENABLE;

	MPU->CTRL |= (1 << MPU_CTRL_ENABLE_Pos); /* Enable the MPU */

	__DSB(); /* Force memory writes before continuing */
	__ISB(); /* Flush and refill pipeline with updated permissions */
}

