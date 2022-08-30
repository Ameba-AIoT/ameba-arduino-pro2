/******************************************************************************
 *
 * Copyright(c) 2019 - 2021 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#ifndef __MESH_DFU_8710C_H_
#define __MESH_DFU_8710C_H_

#include <sys.h>
#include <device_lock.h>
#include "sys_api.h"
#include <flash_api.h>
#include "hal_wdt.h"

uint32_t mesh_dfu_prepare_addr(void);

uint32_t mesh_dfu_get_curr_fw_idx(void);

void mesh_dfu_platform_reset(void);

int mesh_dfu_erase_upg_region(uint32_t img_len, uint32_t new_fw_len, uint32_t new_fw_addr);

uint8_t mesh_dfu_flash_write(uint32_t address, uint32_t length, uint8_t *data);

int mesh_dfu_erase_upg_region(uint32_t img_len, uint32_t new_fw_len, uint32_t new_fw_addr);

#endif