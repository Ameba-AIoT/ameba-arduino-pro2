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

#ifndef __GC_VIP_USER_HEAP_H__
#define __GC_VIP_USER_HEAP_H__

#include <gc_vip_common.h>
#if vpmdENABLE_SYS_MEMORY_HEAP

typedef struct _list_head {
	struct _list_head *next;
	struct _list_head *prev;
} list_head_t;

#define INIT_LIST_HEAD(entry) \
        (entry)->next = (entry);\
        (entry)->prev = (entry);

typedef struct _heap_node {
	list_head_t     list;
	vip_uint32_t    offset;
	vip_uint32_t    size;
	vip_uint32_t    status;
} heap_node_t;

typedef struct _memory_heap {
	vip_uint32_t    free_bytes;
	list_head_t     list;

	void           *memory;

	vip_uint32_t    node_count;
	vip_uint32_t    node_max_count;
	vip_uint32_t    node_capacity;
	heap_node_t    *nodes;
} heap_t;

vip_status_e gcvip_heap_construct(
	heap_t *heap,
	vip_uint32_t size,
	void *logical
);

vip_status_e gcvip_heap_destroy(
	heap_t *heap
);

void *gcvip_heap_alloc(
	heap_t *heap,
	vip_uint32_t size,
	void **logical
);

vip_status_e gcvip_heap_free(
	heap_t *heap,
	void *handle
);

vip_status_e gcvip_heap_free_mem(
	heap_t *heap,
	void *memory
);

vip_status_e gcvip_heap_get_memsize(
	heap_t *heap,
	void *memory,
	vip_uint32_t *size
);

vip_uint32_t gcvip_heap_max_size(
	heap_t *heap
);

#endif
#endif
