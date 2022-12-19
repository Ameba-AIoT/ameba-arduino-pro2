/****************************************************************************
*
*    The MIT License (MIT)
*
*    Copyright (c) 2017 - 2022 Vivante Corporation
*
*    Permission is hereby granted, free of charge, to any person obtaining a
*    copy of this software and associated documentation files (the "Software"),
*    to deal in the Software without restriction, including without limitation
*    the rights to use, copy, modify, merge, publish, distribute, sublicense,
*    and/or sell copies of the Software, and to permit persons to whom the
*    Software is furnished to do so, subject to the following conditions:
*
*    The above copyright notice and this permission notice shall be included in
*    all copies or substantial portions of the Software.
*
*    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
*    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
*    DEALINGS IN THE SOFTWARE.
*
*****************************************************************************/

#ifndef __GC_VIP_KERNEL_HEAP_H__
#define __GC_VIP_KERNEL_HEAP_H__

#include <gc_vip_common.h>

#if vpmdENABLE_VIDEO_MEMORY_HEAP
#include <gc_vip_kernel_port.h>

typedef struct _gckvip_list_head {
	struct _gckvip_list_head *next;
	struct _gckvip_list_head *prev;
} gckvip_list_head_t;

#define GCKVIP_INIT_LIST_HEAD(entry) \
        (entry)->next = (entry);\
        (entry)->prev = (entry);

typedef struct _gckvip_heap_node {
	gckvip_list_head_t list;
	vip_uint32_t    offset;
	vip_uint32_t    size;
	vip_uint32_t    status;
} gckvip_heap_node_t;

typedef struct _gckvip_heap {
	vip_uint32_t    free_bytes;
	gckvip_list_head_t list;

	phy_address_t   physical;
	vip_uint32_t    total_size;
	void            *memory;

	vip_uint32_t    node_count;
	vip_uint32_t    node_capacity;
	gckvip_heap_node_t *nodes;
#if vpmdENABLE_MULTIPLE_TASK
	gckvip_mutex       mutex;
#endif
} gckvip_heap_t;

vip_status_e gckvip_heap_construct(
	gckvip_heap_t *heap,
	vip_uint32_t size,
	void *logical,
	phy_address_t physical,
	vip_uint32_t node_cap
);

vip_status_e gckvip_heap_destroy(
	gckvip_heap_t *heap
);

void *gckvip_heap_alloc(
	gckvip_heap_t *heap,
	vip_uint32_t size,
	void **logical,
	phy_address_t *physical,
	vip_uint32_t align
);

vip_status_e gckvip_heap_free(
	gckvip_heap_t *heap,
	void *handle
);

vip_uint32_t gckvip_heap_capability(
	gckvip_heap_t *heap
);

#endif

#endif
