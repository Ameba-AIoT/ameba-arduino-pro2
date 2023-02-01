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

#ifndef __GC_VIP_KERNEL_DRV_H__
#define __GC_VIP_KERNEL_DRV_H__

#include <gc_vip_common.h>
#include "FreeRTOS.h"
#include "semphr.h"
#include <gc_vip_kernel_port.h>
#include <stdint.h>
#include <stdarg.h>

typedef uintptr_t  gckvip_uintptr_t;

/*
@brief Set power on/off and clock on/off
@param state, power status. refer to gckvip_power_status_e.
*/
vip_status_e gckvip_drv_set_power_clk(
	vip_uint32_t core,
	vip_uint32_t state
);

/*
@brief Get hardware information.
*/
vip_status_e gckvip_drv_get_hardware_info(
	gckvip_hardware_info_t *info
);

/*
@brief do some initialize in this function.
@param, vip_memsizem, the size of video memory heap.
*/
vip_status_e gckvip_drv_init(
	vip_uint32_t vip_memsize
);

/*
@brief do some un-initialize in this function.
*/
vip_status_e gckvip_drv_exit(void);

#endif /* __GC_VIP_KERNEL_DRV_H__ */
