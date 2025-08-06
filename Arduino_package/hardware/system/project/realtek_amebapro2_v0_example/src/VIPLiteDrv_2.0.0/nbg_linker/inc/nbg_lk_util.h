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

#ifndef _NBG_LK_UTIL_H
#define _NBG_LK_UTIL_H

#include <vip_lite_config.h>

#if vpmdENABLE_CAPTURE && vpmdENABLE_MULTIPLE_TASK
typedef struct _nbglk_recursive_mutex {
	/* current thread id*/
	vip_uint32_t        current_tid;
	/* reference count*/
	vip_int32_t         ref_count;
	void                *mutex;
} nbglk_recursive_mutex_t;


vip_status_e nbglk_lock_recursive_mutex(
	nbglk_recursive_mutex_t *recursive_mutex
);

vip_status_e nbglk_unlock_recursive_mutex(
	nbglk_recursive_mutex_t *recursive_mutex
);
#endif

#if vpmdENABLE_RECORD_INFO
#define HASH_MAP_CAPABILITY 128

typedef struct _nbglk_hashmap_node {
	vip_uint64_t          handle;
	/* for red black tree */
	vip_uint32_t          parent_index;
	vip_uint32_t          left_index;
	vip_uint32_t          right_index;
	vip_bool_e            is_black;
} nbglk_hashmap_node_t;

typedef struct _nbglk_hashmap {
	nbglk_hashmap_node_t  hashmap[HASH_MAP_CAPABILITY];
	nbglk_hashmap_node_t *idle_list_head;
	nbglk_hashmap_node_t *node_array;
	vip_uint32_t          capacity;
	vip_uint32_t          free_pos;
	vip_uint32_t          size_per_element;
	vip_char_t           *name;
	void                 *container; /* capacity elements in container */
#if vpmdENABLE_MULTIPLE_TASK
	void                 *mutex;
#endif
} nbglk_hashmap_t;

/*
@brief  init hashmap.
@param  hashmap, the hashmap.
@param  init_capacity, the initial capacity of hashmap.
@param  size_per_element, the size of each element in container.
@param  name, name of this hashmap.
*/
vip_status_e nbglk_hashmap_init(
	IN nbglk_hashmap_t *hashmap,
	IN vip_uint32_t init_capacity,
	IN vip_uint32_t size_per_element,
	IN vip_char_t_ptr name
);

/*
@brief  expand hashmap.
@param  hashmap, the hashmap.
*/
vip_status_e nbglk_hashmap_expand(
	IN nbglk_hashmap_t *hashmap
);

/*
@brief  destroy hashmap.
@param  hashmap, the hashmap.
*/
vip_status_e nbglk_hashmap_destroy(
	IN nbglk_hashmap_t *hashmap
);

/*
@brief  insert handle into hashmap.
@param  hashmap, the hashmap.
@param  handle, the unique handle.
@param  index, the index of element in container.
*/
vip_status_e nbglk_hashmap_insert(
	IN nbglk_hashmap_t *hashmap,
	IN vip_uint64_t handle,
	OUT vip_uint32_t *index
);

/*
@brief  get from hashmap by index.
@param  hashmap, the hashmap.
@param  index, the index of element in container.
@param  element, the handle of element.
*/
vip_status_e nbglk_hashmap_get_by_index(
	IN nbglk_hashmap_t *hashmap,
	IN vip_uint32_t index,
	OUT void **element
);

vip_uint32_t nbglk_hashmap_free_pos(
	nbglk_hashmap_t *hashmap
);

vip_bool_e nbglk_hashmap_full(
	nbglk_hashmap_t *hashmap
);

#endif
#endif
