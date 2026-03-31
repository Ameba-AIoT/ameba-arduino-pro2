/**************************************************************************//**
 * @file     sys_api.c
 * @brief    This file implements system related API functions.
 *
 * @version  V1.00
 * @date     2022-02-18
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2022 Realtek Corporation. All rights reserved.
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
#include <stdio.h>
#include <string.h>
#include "cmsis.h"
#include "sys_api.h"
#include "hal_sys_ctrl.h"


/**
  * @brief  system software reset.
  * @retval none
  */
void sys_reset(void)
{
	hal_sys_set_system_reset();
}

/**
  * @brief  Turn off the JTAG/SWD function.
  * @retval none
  */
void sys_jtag_off(void)
{
	hal_sys_dbg_port_cfg(DBG_PORT_OFF, TMS_IO_S0_CLK_S0);
	hal_sys_dbg_port_cfg(DBG_PORT_OFF, TMS_IO_S1_CLK_S1);
}

/**
  * @brief  Get currently selected boot device.
  * @retval boot device
  * @note
  *  BootFromNORFlash            = 0,
  *  BootFromNANDFlash           = 1,
  *  BootFromUART                = 2
  */
uint8_t sys_get_boot_sel(void)
{
	uint8_t boot_sel;
	boot_sel = hal_sys_get_boot_select();
	return boot_sel;
}

/**
  * @brief  Get currently DRAM type.
  * @retval dram byte
  * @note
  *  DRAM_TYP_DDR2 = 0,
  *  DRAM_TYP_DDR3 = 1,
  *  DRAM_TYP_UNDEFINE = 0xFF
  */
uint8_t sys_get_dram_type(void)
{
	u32 chip_id = 0;
	u8 dram_type = 0;
	hal_sys_get_chip_id(&chip_id);

	if (((chip_id >> 16) & 0x3) == 0x3) {
		dram_type = DRAM_TYP_DDR2;
	} else if (((chip_id >> 16) & 0x3) == 0x2) {
		dram_type = DRAM_TYP_DDR3;
	} else {
		dram_type = DRAM_TYP_UNDEFINE;
	}

	return dram_type;
}

/**
  * @brief  Get currently DRAM density.
  * @retval dram size
  * @note
  *  32MB = 0,
  *  64MB = 1,
  *  128MB = 2,
  *  256MB = 3,
  *  512MB = 4,
  *  1024MB = 5,
  *  2048MB = 6,
  *  UNDEFINE = 0xFF
  */
uint8_t sys_get_dram_size(void)
{
	u32 chip_id = 0;
	u8 dram_size = 0;
	hal_sys_get_chip_id(&chip_id);

	if ((((chip_id >> 2) & 0x3) == 0x3)
		|| (((chip_id >> 2) & 0x3) == 0x0)) {
		if (((chip_id >> 4) & 0x3) == 0x0) {
			dram_size = DDR_64MB;
		} else if (((chip_id >> 4) & 0x3) == 0x2) {
			dram_size = DDR_128MB;
		} else if (((chip_id >> 4) & 0x3) == 0x3) {
			dram_size = DDR_256MB;
		} else {
			dram_size = DDR_UNDEFINE;
		}
	} else if (((chip_id >> 2) & 0x3) == 0x1) {
		dram_size = DDR_64MB;
	} else {
		dram_size = DDR_128MB;
	}

	return dram_size;
}


