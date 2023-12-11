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

#ifndef _VIP_KERNEL_ALLOCATOR_H
#define _VIP_KERNEL_ALLOCATOR_H

#include <gc_vip_common.h>
#include <gc_vip_video_memory.h>
#include <gc_vip_kernel_port.h>
#include <gc_vip_kernel_heap.h>

#if vpmdENABLE_MMU
/*
@brief get user space logical address.
@param, context, the contect of kernel space.
@param, node, dynamic allocate node info.
@param, virtual_addr, the VIP's virtual address.
@param, logical, use space logical address.
@param, video memory type see gckvip_video_memory_type_e
*/
vip_status_e gckvip_allocator_get_userlogical(
	gckvip_context_t *context,
	gckvip_dyn_allocate_node_t *node,
	vip_uint32_t virtual_addr,
	void **logical,
	vip_uint8_t memory_type
);

/*
@brief get kernel space logical address.
@param, context, the contect of kernel space.
@param, node, dynamic allocate node info.
@param, virtual_addr, the VIP's virtual address.
@param, logical, kernel space logical address.
@param, video memory type see gckvip_video_memory_type_e
*/
vip_status_e gckvip_allocator_get_kernellogical(
	gckvip_context_t *context,
	gckvip_dyn_allocate_node_t *node,
	vip_uint32_t virtual_addr,
	void **logical,
	vip_uint8_t memory_type
);

/*
@brief get vip physical address.
@param, context, the contect of kernel space.
@param, node, dynamic allocate node info.
@param IN vip_virtual, the vitual address of VIP.
@param, physical, vip physical address.
@param, video memory type see gckvip_video_memory_type_e
*/
vip_status_e gckvip_allocator_get_vipphysical(
	gckvip_context_t *context,
	gckvip_dyn_allocate_node_t *node,
	vip_uint32_t vip_virtual,
	phy_address_t *physical,
	vip_uint8_t memory_type
);
#endif

/*
@brief convert user's memory to CPU physical. And map to VIP virtual address.
@param, context, the contect of kernel space.
@param, logical, the logical address(handle) should be wraped.
@param, memory_type The type of this VIP buffer memory. see vip_buffer_memory_type_e.
@param, node, dynamic allocate node info.
*/
vip_status_e gckvip_allocator_wrap_usermemory(
	gckvip_context_t *context,
	vip_ptr logical,
	vip_uint32_t memory_type,
	gckvip_dyn_allocate_node_t *node
);

/*
@brief un-wrap user memory(handle).
@param, context, the contect of kernel space.
@param, node, dynamic allocate node info.
*/
vip_status_e gckvip_allocator_unwrap_usermemory(
	gckvip_context_t *context,
	gckvip_dyn_allocate_node_t *node
);

/*
@brief convert cpu's physical to vip physical.
@param IN context, the contect of kernel space.
@param IN physical_table Physical address table. should be wraped for VIP hardware.
@param IN size_table The size of physical memory for each physical_table element.
@param IN physical_num The number of physical table element.
@param, node, dynamic allocate node info.
@param IN alloc_flag the flag of this video memroy. see gckvip_video_mem_alloc_flag_e.
*/
vip_status_e gckvip_allocator_wrap_userphysical(
	gckvip_context_t *context,
	vip_address_t *physical_table,
	vip_uint32_t *size_table,
	vip_uint32_t physical_num,
	gckvip_dyn_allocate_node_t *node,
	vip_uint32_t alloc_flag
);

/*
@brief un-wrap user physical.
@param, context, the contect of kernel space.
@param, node, dynamic allocate node info.
*/
vip_status_e gckvip_allocator_unwrap_userphysical(
	gckvip_context_t *context,
	gckvip_dyn_allocate_node_t *node
);

/*
@brief Flush CPU cache for dynamic alloc video memory and wrap user memory.
@param context, the contect of kernel space.
@param node, dynamic allocate node info.
@param physical, the physical address should be flush CPU cache.
@param logical, the logical address should be flush.
@param size, the size of the memory should be flush.
@param type The type of operate cache.
*/
#if vpmdENABLE_FLUSH_CPU_CACHE
vip_status_e gckvip_alloctor_flush_cache(
	gckvip_context_t *context,
	gckvip_dyn_allocate_node_t *node,
	phy_address_t physical,
	void *logical,
	vip_uint32_t size,
	gckvip_cache_type_e type
);
#endif

/*
@brief allocate memory from system. get the physical address table each page. get size table of eache page
@param context, the contect of kernel space.
@param node, dynamic allocate noe.
@param align, the size of alignment for this video memory.
@param flag the flag of this video memroy. see gckvip_video_mem_alloc_flag_e.
*/
vip_status_e gckvip_allocator_dyn_alloc(
	gckvip_context_t *context,
	gckvip_dyn_allocate_node_t *node,
	vip_uint32_t align,
	vip_uint32_t alloc_flag
);

/*
@brief free a dynamic allocate memory.
@param context, the contect of kernel space.
@param node, dynamic allocate node info.
*/
vip_status_e gckvip_allocator_dyn_free(
	gckvip_context_t *context,
	gckvip_dyn_allocate_node_t *node
);

#endif
