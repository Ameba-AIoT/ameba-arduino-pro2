/******************************************************************************\
|* Copyright (c) 2017-2023 by Vivante Corporation.  All Rights Reserved.      *|
|*                                                                            *|
|* The material in this file is confidential and contains trade secrets of    *|
|* of Vivante Corporation.  This is proprietary information owned by Vivante  *|
|* Corporation.  No part of this work may be disclosed, reproduced, copied,   *|
|* transmitted, or used in any way for any purpose, without the express       *|
|* written permission of Vivante Corporation.                                 *|
|*                                                                            *|
\******************************************************************************/

#ifndef _GC_VIP_BUFFER_H
#define _GC_VIP_BUFFER_H

#include <gc_vip_common.h>
#include <vip_lite.h>

typedef enum _gcvip_obj_type {
	GCVIP_OBJ_NONE          = 0x00,
	GCVIP_OBJ_NETWORK       = 0x01,
	GCVIP_OBJ_BUFFER        = 0x02,
	GCVIP_OBJ_IMAGE         = 0x03,
	GCVIP_OBJ_NODE          = 0x04,
	GCVIP_OBJ_MAX,
} gcvip_obj_type_e;

typedef enum _gcvip_buffer_type {
	GCVIP_BUFFER_TYPE_TENSOR      = 0,
	GCVIP_BUFFER_TYPE_IMAGE       = 1,
	GCVIP_BUFFER_TYPE_ARRAY       = 2,
	GCVIP_BUFFER_TYPE_SCALAR      = 3,
} gcvip_buffer_type_e;

typedef enum _gcvip_buffer_allocate {
	GCVIP_BUFFER_ALLOCATE_NONE                = 0,
	GCVIP_BUFFER_ALLOCATE_FROM_INTERNAL       = 1,
	GCVIP_BUFFER_ALLOCATE_FROM_USER_MEMORY    = 2,
	GCVIP_BUFFER_ALLOCATE_FROM_USER_PHYSICAL  = 3,
	GCVIP_BUFFER_ALLOCATE_FROM_USER_DMA_BUF   = 4,
	GCVIP_BUFFER_ALLOCATE_MAX,
} gcvip_buffer_allocate_e;

typedef struct _gcvip_object {
	gcvip_obj_type_e  type;
} gcvip_object_t;

/* video memory object that VIP hardware could access */
typedef struct _gcvip_videomemory {
	/*
	an anonymous handle to this video memory object.
	it can be parsed video memory maintiner.
	*/
	void                *handle;
	/* the logical address of CPU. maybe it is equal to CPU's physical address on flat system(RTOS, bare metal) */
	vip_uint8_t         *logical;
	/* when MMU enabled, physical is NPU's virtual address.
	   when MMU disable, physical is NPU's physical address.
	*/
	vip_uint32_t        physical;
	/* the size of the video memory */
	vip_uint32_t        size;
} gcvip_videomemory_t;

typedef struct _vip_buffer {
	gcvip_object_t      object;
	gcvip_videomemory_t memory;
	vip_uint32_t        allocated;
	vip_buffer_create_params_t param;
} vip_buffer_t;

#endif
