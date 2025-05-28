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
#ifndef _NBG_LK_NODE_H
#define _NBG_LK_NODE_H

#include <vip_lite_node.h>
#include <vip_lite_config.h>
#include <nbg_lk.h>
#include <nbg_lk_buffer.h>


#define MAX_IMAGE_DEPTH         4

typedef enum _nbglk_node_type {
	NBGLK_NODE_TYPE_NONE    = 0x00,
	NBGLK_NODE_TYPE_SCALER  = 0x01,
	NBGLK_NODE_TYPE_MAX,
} nbglk_node_type_t;

typedef struct _nbglk_image_params_t {
	vip_uint32_t         height;
	vip_uint32_t         width;
	vip_uint32_t         depth;
	vip_enum             color;
	vip_enum             data_format;
	vip_uint32_t         memory_type;
} nbglk_image_params_t;

typedef struct _vip_image {
	nbglk_object_t       object;
	nbglk_videomemory_t  memories[MAX_IMAGE_DEPTH];
	vip_uint32_t         allocated;
	nbglk_image_params_t param;
} vip_image_t;

typedef struct _vip_node_t {
	nbglk_object_t       object;
	nbglk_node_type_t    type;

	nbglk_videomemory_t  states_buffer;
	/* the size of command buffer after append cmds. real command buffer size */
	vip_uint32_t         command_size;
	/* mark to capture complete, don't need capture again*/
	vip_uint8_t          capture_done;
	vip_ptr             *inputs;
	vip_ptr             *outputs;
	vip_uint32_t         input_num;
	vip_uint32_t         output_num;

#if vpmdENABLE_CNN_PROFILING
	vip_uint64_t        start_time;
	vip_uint64_t        end_time;
#endif
	vip_uint32_t        device_index;
	viphal_file_t        capture_file;
	vip_uint32_t        task_id;
} vip_node_t;

vip_status_e nbglk_create_node(
	vip_node_t **node_ptr
);

vip_status_e nbglk_create_preprocess(
	const vip_preprocess_type_e type,
	const vip_preprocess_yuv2rgb_t *param,
	const vip_uint32_t param_size,
	const vip_image input_buffer,
	const vip_buffer output_buffer,
	vip_node *out_node
);

vip_status_e nbglk_update_preprocess(
	vip_node node,
	const vip_preprocess_type_e type,
	const vip_preprocess_yuv2rgb_t *param,
	const vip_uint32_t param_size,
	const vip_image input_buffer,
	const vip_buffer output_buffer
);

#if (vpmdENABLE_HANG_DUMP > 1) || (vpmdENABLE_CAPTURE > 1)
vip_status_e nbglk_capture_node_inputs(
	vip_node node,
	viphal_file_t capture_file
);

vip_status_e nbglk_capture_node_outputs(
	vip_node node,
	viphal_file_t capture_file
);
#endif

#endif
