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

#ifndef _NBG_LK_BUFFER_H
#define _NBG_LK_BUFFER_H

#include <vip_lite_config.h>
#include <vip_lite.h>

typedef enum _nbglk_obj_type {
	NBGLK_OBJ_NONE          = 0x00,
	NBGLK_OBJ_NETWORK       = 0x01,
	NBGLK_OBJ_BUFFER        = 0x02,
	NBGLK_OBJ_IMAGE         = 0x03,
	NBGLK_OBJ_NODE          = 0x04,
	NBGLK_OBJ_MAX,
} nbglk_obj_type_e;

typedef enum _nbglk_buffer_type {
	VIP_BUFFER_TYPE_TENSOR      = 0,
	VIP_BUFFER_TYPE_IMAGE       = 1,
	VIP_BUFFER_TYPE_ARRAY       = 2,
	VIP_BUFFER_TYPE_SCALAR      = 3,
} nbglk_buffer_type_e;

typedef enum _nbglk_buffer_allocate {
	NBGLK_BUFFER_ALLOCATE_NONE                = 0,
	NBGLK_BUFFER_ALLOCATE_FROM_INTERNAL       = 1,
	NBGLK_BUFFER_ALLOCATE_FROM_USER_MEMORY    = 2,
	NBGLK_BUFFER_ALLOCATE_FROM_USER_PHYSICAL  = 3,
	NBGLK_BUFFER_ALLOCATE_FROM_USER_DMA_BUF   = 4,
	NBGLK_BUFFER_ALLOCATE_MAX,
} nbglk_buffer_allocate_e;

typedef struct _nbglk_object {
	nbglk_obj_type_e  type;
} nbglk_object_t;

/* video memory object that VIP hardware could access */
typedef struct _nbglk_videomemory {
	/*
	The indentity of video memory, it can be parsed video memory maintiner.
	*/
	vip_uint32_t        mem_id;
	/* the logical address of CPU. maybe it is equal to CPU's physical address on flat system(RTOS, bare metal) */
	vip_uint8_t         *logical;
	/* when MMU enabled, physical is NPU's virtual address.
	   when MMU disable, physical is NPU's physical address.
	*/
	vip_address_t       physical;
	/* the size of the video memory */
	vip_size_t          size;
} nbglk_videomemory_t;

typedef struct _vip_buffer {
	nbglk_object_t      object;
	nbglk_videomemory_t memory;
	vip_uint32_t        allocated;
	vip_buffer_create_params_t param;
} vip_buffer_t;

#endif
