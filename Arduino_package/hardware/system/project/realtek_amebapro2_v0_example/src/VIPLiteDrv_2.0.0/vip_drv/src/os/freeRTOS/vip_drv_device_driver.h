/******************************************************************************\
|* Copyright (c) 2017-2024 by Vivante Corporation.  All Rights Reserved.      *|
|*                                                                            *|
|* The material in this file is confidential and contains trade secrets of    *|
|* of Vivante Corporation.  This is proprietary information owned by Vivante  *|
|* Corporation.  No part of this work may be disclosed, reproduced, copied,   *|
|* transmitted, or used in any way for any purpose, without the express       *|
|* written permission of Vivante Corporation.                                 *|
|*                                                                            *|
\******************************************************************************/

#ifndef __VIP_DRV_DEVICE_DRIVER_H__
#define __VIP_DRV_DEVICE_DRIVER_H__

#include <vip_lite_config.h>
#include "FreeRTOS.h"
#include "semphr.h"
#include <vip_drv_os_port.h>
#include <stdint.h>
#include <stdarg.h>

typedef uintptr_t  vipdrv_uintptr_t;

/*
@brief Set power on/off and clock on/off
@param state, power status. refer to vipdrv_power_status_e.
*/
vip_status_e vipdrv_drv_set_power_clk(
	vip_uint32_t core,
	vip_uint32_t state
);

/*
@brief convert CPU physical to VIP physical.
@param cpu_physical. the physical address of CPU domain.
*/
vip_physical_t vipdrv_drv_get_vipphysical(
	vip_physical_t cpu_physical
);

/*
@brief convert VIP physical to CPU physical.
@param vip_physical. the physical address of VIP domain.
*/
vip_physical_t vipdrv_drv_get_cpuphysical(
	vip_physical_t vip_physical
);

/*
 Get the video memory config information
*/
vip_status_e vipdrv_drv_get_memory_config(
	vipdrv_platform_memory_config_t *memory_info
);

/*
 Get the video memory config information
 1. the size of system memory used by vip_hal.
 2. reserve_physical is a video memory, used by vip_create_network_from_physical() api in nbg_linker.
 3. heap info is used for video memory heap basic information.
*/
vip_status_e vipdrv_drv_get_hardware_info(
	vipdrv_hardware_info_t *info
);

/*
@brief do some initialize in this function.
@param, vip_memsizem, the size of video memory heap.
*/
vip_status_e vipdrv_drv_init(
	vip_uint32_t vip_memsize
);

/*
@brief do some un-initialize in this function.
*/
vip_status_e vipdrv_drv_exit(void);

#endif /* __VIP_DRV_DEVICE_DRIVER_H__ */
