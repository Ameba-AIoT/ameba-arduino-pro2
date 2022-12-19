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

#ifndef _GC_VIP_KERNEL_UTIL_H
#define _GC_VIP_KERNEL_UTIL_H

#include <gc_vip_common.h>
#include <vip_lite.h>
#include <gc_vip_kernel_port.h>

typedef struct _gckvip_recursive_mutex {
	/* current thread id*/
	vip_uint32_t        current_tid;
	/* reference count*/
	vip_int32_t         ref_count;
	gckvip_mutex        mutex;
} gckvip_recursive_mutex;

vip_status_e gckvip_lock_recursive_mutex(
	gckvip_recursive_mutex *recursive_mutex
);

vip_status_e gckvip_unlock_recursive_mutex(
	gckvip_recursive_mutex *recursive_mutex
);

typedef enum _gckvip_queue_status {
	GCKVIP_QUEUE_NONE       = 0,
	GCKVIP_QUEUE_EMPTY      = 1,
	GCKVIP_QUEUE_WITH_DATA  = 2,
	GCKVIP_QUEUE_FULL       = 3,
	GCKVIP_QUEUE_MAX,
} gckvip_queue_status_e;

typedef struct _gckvip_database_table {
	vip_ptr            *handle;
	vip_uint32_t       process_id;
} gckvip_database_table_t;

typedef struct _gckvip_database {
	gckvip_database_table_t *table;
	vip_uint32_t       capacity;
	vip_uint32_t       free_count;     /* the number of free in database */
	vip_uint32_t       first_free_pos; /* the first free position in database */
#if vpmdENABLE_MULTIPLE_TASK
	gckvip_mutex       mutex;
#endif
} gckvip_database_t;

#if vpmdENABLE_MULTIPLE_TASK
#define QUEUE_CAPABILITY 32
typedef struct _gckvip_queue_data {
	vip_uint64_t        v1;
	vip_uint64_t        v2;
#if vpmdENABLE_PREEMPTION
	vip_uint8_t         priority;
#endif
} gckvip_queue_data_t;

#if vpmdENABLE_PREEMPTION
typedef struct _gckvip_queue_node {
	vip_uint32_t         index;
	gckvip_queue_data_t *data;
} gckvip_queue_node;

typedef struct _gckvip_priority_queue {
	gckvip_queue_node  *head;
	vip_uint32_t        max_size;
	vip_uint32_t        cur_size;
	vip_uint32_t        count;
} gckvip_priority_queue;
#else
typedef struct _gckvip_fifo_queue {
	gckvip_queue_data_t  *data[QUEUE_CAPABILITY];
	vip_int32_t           begin_index;
	vip_int32_t           end_index;
} gckvip_fifo_queue;
#endif

typedef struct _gckvip_queue {
	gckvip_mutex            mutex;
	gckvip_mutex            read_mutex;
	gckvip_mutex            write_mutex;
	void                    *read_signal;
	void                    *write_signal;
	vip_bool_e              queue_stop;
	vip_uint32_t            device_id;
#if vpmdENABLE_PREEMPTION
	gckvip_priority_queue   queue;
#else
	gckvip_fifo_queue       queue;
#endif
} gckvip_queue_t;

vip_status_e gckvip_queue_initialize(
	gckvip_queue_t *queue,
	vip_uint32_t   device_id
);

vip_status_e gckvip_queue_destroy(
	gckvip_queue_t *queue
);

vip_bool_e gckvip_queue_read(
	gckvip_queue_t *queue,
	gckvip_queue_data_t **data_ptr
);

vip_bool_e gckvip_queue_write(
	gckvip_queue_t *queue,
	gckvip_queue_data_t *data
);

vip_status_e gckvip_queue_clean(
	gckvip_queue_t *queue
);
gckvip_queue_status_e gckvip_queue_status(
	gckvip_queue_t *queue
);
#endif

#define DATABASE_MAGIC_DATA          0x15000000

vip_status_e gckvip_database_init(
	gckvip_database_t *database
);

vip_status_e gckvip_database_get_id(
	gckvip_database_t *database,
	vip_ptr handle,
	vip_uint32_t process_id,
	vip_uint32_t *database_id
);

vip_status_e gckvip_database_put_id(
	gckvip_database_t *database,
	vip_uint32_t database_id
);

vip_status_e gckvip_database_get_handle(
	gckvip_database_t *database,
	vip_uint32_t database_id,
	vip_ptr *handle
);

vip_uint32_t gckvip_database_get_freepos(
	gckvip_database_t *database
);

vip_status_e gckvip_database_get_table(
	gckvip_database_t *database,
	vip_uint32_t database_id,
	gckvip_database_table_t **table
);

vip_status_e gckvip_database_uninit(
	gckvip_database_t *database
);

#define HASH_MAP_CAPABILITY 128

typedef struct _gckvip_hashmap_node {
	void                 *handle;
	/* for red black tree */
	vip_uint32_t          parent_index;
	vip_uint32_t          left_index;
	vip_uint32_t          right_index;
	vip_bool_e            is_black;
} gckvip_hashmap_node_t;

typedef struct _gckvip_hashmap {
	gckvip_hashmap_node_t  hashmap[HASH_MAP_CAPABILITY];
	gckvip_hashmap_node_t *idle_list;
	gckvip_hashmap_node_t *node_array;
	vip_uint32_t           size;
} gckvip_hashmap_t;

vip_status_e gckvip_hashmap_init(
	gckvip_hashmap_t *hashmap,
	vip_uint32_t init_size
);

vip_status_e gckvip_hashmap_expand(
	gckvip_hashmap_t *hashmap
);

vip_status_e gckvip_hashmap_destroy(
	gckvip_hashmap_t *hashmap
);

vip_uint32_t gckvip_hashmap_put(
	gckvip_hashmap_t *hashmap,
	void *handle,
	vip_bool_e *exist
);

vip_uint32_t gckvip_hashmap_get(
	gckvip_hashmap_t *hashmap,
	void *handle,
	vip_bool_e remove
);
#endif
