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


#ifndef _GC_VIP_LITE_H
#define _GC_VIP_LITE_H

#include <gc_vip_common.h>
#include <vip_lite.h>
#include <gc_vip_user.h>
#include <gc_vip_kernel_share.h>

#define GCVIP_SET_VALUE(x, y) \
{   \
    if ((x) != VIP_NULL) {  \
        *((vip_uint32_t*)(x)) = (vip_uint32_t)(y);  \
    }   \
    else {   \
        gcvip_error("failed to set value=%d, x=%p\n", x);   \
        gcGoOnError(VIP_ERROR_NOT_SUPPORTED);   \
    }   \
}




typedef enum _gcvip_obj_type {
	GCVIP_OBJ_NONE          = 0x00,
	GCVIP_OBJ_NETWORK       = 0x01,
	GCVIP_OBJ_BUFFER        = 0x02,
	GCVIP_OBJ_IMAGE         = 0x03,
	GCVIP_OBJ_NODE          = 0x04,
	GCVIP_OBJ_MAX,
} gcvip_obj_type_e;

typedef enum _gcvip_buffer_allocate {
	GCVIP_BUFFER_ALLOCATE_NONE                = 0,
	GCVIP_BUFFER_ALLOCATE_FROM_INTERNAL       = 1,
	GCVIP_BUFFER_ALLOCATE_FROM_USER_MEMORY    = 2,
	GCVIP_BUFFER_ALLOCATE_FROM_USER_PHYSICAL  = 3,
	GCVIP_BUFFER_ALLOCATE_FROM_USER_DMA_BUF   = 4,
	GCVIP_BUFFER_ALLOCATE_MAX,
} gcvip_buffer_allocate_e;

typedef enum _gcvip_init_cmd_status {
	GCVIP_INIT_CMD_STATUS_NO         = 0,
	GCVIP_INIT_CMD_STATUS_DONE       = 1,
	GCVIP_INIT_CMD_STATUS_POWER_OFF  = 2,
} gcvip_init_cmd_status_e;

typedef struct _gcvip_object {
	gcvip_obj_type_e  type;
} gcvip_object_t;

/* video memory object that VIP hardware could access */
typedef struct _gcvip_videomemory_t {
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

#if vpmdENABLE_CAPTURE && vpmdENABLE_MULTIPLE_TASK
typedef struct _gcvip_recursive_mutex {
	/* current thread id*/
	vip_uint32_t        current_tid;
	/* reference count*/
	vip_int32_t         ref_count;
	void                *mutex;
} gcvip_recursive_mutex;
#endif

typedef struct _gcvip_context {
	/* cid */
	vip_uint32_t        hw_target;
	vip_uint32_t        *axi_sram_base;
	vip_uint32_t        *axi_sram_size;
	vip_uint32_t        vip_sram_base;
	vip_uint32_t        vip_sram_size;

	volatile vip_int8_t  initialize;
	volatile vip_uint32_t *init_status;

#if vpmdENABLE_CAPTURE
	gcvip_file_t        capture_file;
#endif

#if vpmdENABLE_MULTIPLE_TASK
	/* mutex for vip_init/vip_destroy */
	void                *initialize_mutex;
#if vpmdENABLE_CAPTURE
	/* mutex for capture */
	gcvip_recursive_mutex capture_mutex;
#endif
#endif

	/* device number of vip device */
	vip_uint32_t        device_count;
	/* the core numbers for each logical device */
	vip_uint32_t        device_core_number[gcdMAX_CORE];
	/* the core index for each logical device */
	vip_uint32_t        device_core_index[gcdMAX_CORE][gcdMAX_CORE];
	/* function config by kernel space fs node */
	gckvip_feature_config func_config;
} gcvip_lite_context_t;

typedef struct _vip_buffer {
	gcvip_object_t      object;
	gcvip_videomemory_t memory;
	vip_uint32_t        allocated;
	vip_buffer_create_params_t param;
} vip_buffer_t;

typedef struct _gcvip_group_item {
	gcvip_object_t      object;
	vip_ptr             task;
} gcvip_group_item_t;

typedef struct _vip_group {
	gcvip_group_item_t    *tasks;
	vip_uint32_t           max_task_num;
	vip_uint32_t           add_task_num;
	vip_uint32_t           run_task_num;
#if vpmdENABLE_MULTIPLE_TASK
	void                  *mutex;
#endif
	/* the index of device run this group */
	vip_uint32_t           device_id;
	gcvip_file_t           capture_file;
} vip_group_t;

#if vpmdENABLE_CAPTURE || (vpmdENABLE_HANG_DUMP > 1)
typedef struct _gcvip_command_dump {
	vip_uint32_t cmd_type;
	vip_uint32_t size;
	vip_uint32_t offset;
	vip_uint32_t layer_id;
	vip_uint32_t uid;
	struct _gcvip_command_dump *next;
} gcvip_command_dump_t;
#endif

#if vpmdENABLE_USE_AGENT_TRIGGER
/* vip_input_output_info_t and vip_address_info_t should be defined into agent driver
*/

/*! \brief network's inputs/outputs address in command buffer. it only used by Agent driver.
 */
typedef struct _vip_input_output_info {
	/*!< the logical address of input/output in command buffer */
	void                *logical_in_cmd;
	/*!< the physical address of input/output in command buffer */
	vip_uint32_t        *physical_in_cmd;
	/*!< the offset for every slice */
	vip_uint32_t        *offset;
	/*!< the number of input/output slice */
	vip_uint32_t        slice_num;
	/*!< the physical address of input/output buffer */
	vip_uint32_t        physical;
} vip_input_output_info_t;

/*! \brief address infromation of network's buffers, it only used by Agent driver.
 */
typedef struct _vip_address_info {
	/*!< the logical address of wait-link buffer */
	void                *waitlink_logical;
	/*!< the physical address of wait-link buffer */
	vip_uint32_t        waitlink_physical;
	/*!< the size of wait-link buffer */
	vip_uint32_t        waitlink_size;

	/*!< the logical address of command buffer */
	void                *commandbuffer_logical;
	/*!< the physical address of command buffer */
	vip_uint32_t        commandbuffer_physical;
	/*!< the size of commands */
	vip_uint32_t        commandbuffer_size;

	/*!< network's input information */
	vip_input_output_info_t *input_info;
	/*!< the number of inputs */
	vip_uint32_t            input_num;

	/*!< network's output information */
	vip_input_output_info_t *output_info;
	/*!< the number of outputs */
	vip_uint32_t            output_num;
} vip_address_info_t;
#endif

#endif
