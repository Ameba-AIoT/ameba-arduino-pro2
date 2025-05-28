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

#ifndef _VIP_DRV_ALLOCATOR_ARRAY_H
#define _VIP_DRV_ALLOCATOR_ARRAY_H

#include <vip_lite_config.h>
#include <vip_drv_video_memory.h>

#if vpmdENABLE_VIDEO_MEMORY_HEAP
extern vip_status_e allocator_init_freertos_heap(
	vipdrv_allocator_t *allocator,
	vip_char_t *name,
	vipdrv_allocator_type_e type
);
#endif
extern vip_status_e allocator_init_freertos_wrap_physical(
	vipdrv_allocator_t *allocator,
	vip_char_t *name,
	vipdrv_allocator_type_e type
);
extern vip_status_e allocator_init_freertos_wrap_memory(
	vipdrv_allocator_t *allocator,
	vip_char_t *name,
	vipdrv_allocator_type_e type
);
extern vip_status_e allocator_init_freertos_dyna_continue(
	vipdrv_allocator_t *allocator,
	vip_char_t *name,
	vipdrv_allocator_type_e type
);


static vipdrv_allocator_desc_t video_mem_allocator_array[] = {
	VIPDRV_DEFINE_ALLOCATOR_DESC("wrap-user-phy", allocator_init_freertos_wrap_physical,
								 VIPDRV_ALLOCATOR_TYPE_WRAP_USER_PHYSICAL),
	VIPDRV_DEFINE_ALLOCATOR_DESC("wrap-user-mem", allocator_init_freertos_wrap_memory,
								 VIPDRV_ALLOCATOR_TYPE_WRAP_USER_LOGICAL),

#if vpmdENABLE_VIDEO_MEMORY_DYNAMIC
	VIPDRV_DEFINE_ALLOCATOR_DESC("dyn-continue", allocator_init_freertos_dyna_continue,
								 VIPDRV_ALLOCATOR_TYPE_DYN_ALLOC),
#endif

#if vpmdENABLE_VIDEO_MEMORY_HEAP
	VIPDRV_DEFINE_ALLOCATOR_DESC("heap-reserved", allocator_init_freertos_heap,
								 VIPDRV_ALLOCATOR_TYPE_VIDO_HEAP),
#endif
};
#endif
