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

#ifndef _NBG_LK_DEBUG_H
#define _NBG_LK_DEBUG_H

#include <vip_lite.h>
#include <vip_hal_os_port.h>
#include <vip_hal_hardware.h>
#include <nbg_lk_network.h>


#define NBGLK_GET_STRING    viphal_os_snprint
#define NBGLK_DUMP_STRING   viphal_print_string


#define CHECK_DUMP_NBG(context)                                  \
{                                                                \
    if (vip_false_e == context->func_config.enable_dump_nbg) {   \
        return VIP_SUCCESS;                                      \
    }                                                            \
}

#if vpmdDUMP_NBG_RESOURCE
vip_status_e nbglk_dump_network_outputs(
	vip_network_t *network
);

vip_status_e nbglk_dump_network_inputs(
	vip_network_t *network
);

vip_status_e nbglk_dump_nbg(
	viphal_file_t file,
	void *data,
	vip_size_t size
);
#endif

typedef enum _nbglk_record_info_type {
	RECORD_TYPE_NONE                = 0,
	RECORD_TYPE_NN_COMMAND          = 1,
	RECORD_TYPE_TP_COMMAND          = 2,
	RECORD_TYPE_SH_COMMAND          = 3,
	/* NN or NN_LUT weight */
	RECORD_TYPE_NN_WEIGHT           = 4,
	RECORD_TYPE_TP_WEIGHT           = 5,
	RECORD_TYPE_SH_WEIGHT           = 6,
	RECORD_TYPE_DYNA_DATA           = 7,
	/* NN or NN_LUT weight */
	RECORD_TYPE_NN_WEIGHT_BITSTREAM = 8,
	RECORD_TYPE_SP_WEIGHT           = 9,
	RECORD_TYPE_SP_WEIGHT_BITSTREAM = 10,
	RECORD_TYPE_SP_COMMAND          = 11,
	RECORD_TYPE_NN_LUT_COMMAND      = 12,
	RECORD_TYPE_NT_COMMAND          = 13,
	RECORD_TYPE_MAX
} nbglk_record_info_type_e;

typedef struct _nbglk_record_info {
	nbglk_record_info_type_e record_type;
	vip_size_t size;
	vip_size_t offset; /* when record type is coeff, indicate patch index */
	vip_uint32_t layer_id;
	vip_uint32_t op_index;
	/* absolute operation id */
	vip_uint32_t abs_op_id;
} nbglk_record_info_t;

#if vpmdTASK_CMD_DUMP
vip_status_e nbglk_network_dump_init(
	vip_network network
);

vip_status_e nbglk_network_dump_uninit(
	vip_network network
);

vip_status_e nbglk_network_dump_data(
	vip_network network,
	vip_uint8_t *data,
	vip_uint32_t size
);

vip_status_e nbglk_network_dump_cmd(
	vip_network network,
	vip_uint8_t *command,
	vip_uint32_t size
);
#endif

#if vpmdENABLE_RECORD_INFO
void nbglk_record_info_add_list(
	nbglk_segment_t *segment,
	vip_size_t offset,
	vip_size_t size,
	vip_uint32_t layer_id,
	vip_uint32_t abs_op_id,
	vip_uint32_t op_index,
	vip_uint32_t type
);
#endif

#if vpmdENABLE_BW_PROFILING
vip_status_e nbglk_start_profiling(
	vip_network_t *network,
	nbglk_segment_t *segment
);
vip_status_e nbglk_end_profiling(
	vip_network_t *network,
	nbglk_segment_t *segment
);
#endif

#if vpmdENABLE_CNN_PROFILING
vip_status_e nbglk_layer_info(
	vip_network_t *network,
	vip_char_t *name,
	vip_uint32_t layer_id,
	vip_uint32_t op_id,
	vip_uint32_t uid,
	vip_uint8_t core_id
);

vip_uint32_t nbglk_get_num_initend_operation(
	vip_network_t *network
);

vip_status_e nbglk_start_segment_profile(
	vip_network_t *network,
	nbglk_segment_t *segment
);

vip_status_e nbglk_end_segment_profile(
	vip_network_t *network,
	nbglk_segment_t *segment
);
#endif

vip_status_e nbglk_dump_nbg_entry(
	vip_network network
);
vip_status_e nbglk_section_checksum(
	vip_network_t *network
);

#if vpmdENABLE_CHECKSUM
vip_status_e nbglk_network_checksum(
	vip_network_t *network,
	nbglk_checksum_type_e checksum_type
);

#if vpmdENABLE_CHECKSUM > 1
vip_status_e nbglk_nbg_checksum(
	void *data,
	vip_size_t size
);
#endif
#endif
#endif
