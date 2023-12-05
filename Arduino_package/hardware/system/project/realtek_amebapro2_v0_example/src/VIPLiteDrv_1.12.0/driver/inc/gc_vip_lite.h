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


#ifndef _GC_VIP_LITE_H
#define _GC_VIP_LITE_H

#include <gc_vip_common.h>
#include <vip_lite.h>
#include <gc_vip_user.h>
#include <gc_vip_kernel_share.h>
#include <gc_vip_lite_util.h>

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

#define BITS_PER_BYTE       8

typedef struct _gcvip_context {
	/* cid */
	vip_uint32_t        hw_target;
	vip_uint32_t        *axi_sram_base;
	vip_uint32_t        *axi_sram_size;
	vip_uint32_t        vip_sram_base;
	vip_uint32_t        vip_sram_size;

#if vpmdENABLE_VIDEO_MEMORY_HEAP
	vip_uint32_t        heap_size;
	/* the base address of video memory heap, access by VIP core */
	vip_address_t       vip_heap_base;
#endif
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
	gcvip_recursive_mutex_t capture_mutex;
#endif
#endif

	/* device number of vip device */
	vip_uint32_t        device_count;
	/* the core numbers for each logical device */
	vip_uint32_t        device_core_number[gcdMAX_CORE];
	/* the core index for each logical device */
	vip_uint32_t        device_core_index[gcdMAX_CORE][gcdMAX_CORE];
	/* function config by kernel space fs node */
	gckvip_feature_config_t func_config;
} gcvip_lite_context_t;

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
