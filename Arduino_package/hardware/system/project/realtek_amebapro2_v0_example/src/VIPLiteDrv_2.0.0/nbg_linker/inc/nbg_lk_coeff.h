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

#ifndef _NBG_LK_COEFF_H
#define _NBG_LK_COEFF_H

#include <vip_lite_config.h>
#include <vip_lite.h>

vip_status_e nbglk_coeff_get_property(
	vip_network network,
	vip_uint32_t patch_index,
	vip_uint8_t **base_logical,
	vip_address_t *base_physical,
	vip_size_t *offset,
	vip_size_t *size
);

#if vpmdPRELOAD_COEFF
typedef enum _nbglk_coeff_preload_patch_nn_property {
	NBGLK_COEFF_PATH_NN_NONE           = 0,
	NBGLK_COEFF_PATH_NN_CMD            = 1,
	NBGLK_COEFF_PATH_NN_KERNEL_HEADER  = 2,
	NBGLK_COEFF_PATH_NN_MAX,
} nbglk_coeff_preload_patch_nn_property_e;

typedef enum _nbglk_coeff_location {
	NBGLK_COEFF_LOC_USER_SPECIFIED_0    = 0,
	/* NBGLK_COEFF_LOC_USER_SPECIFIED_1 ~ NBGLK_COEFF_LOC_USER_SPECIFIED_X */
	NBGLK_COEFF_LOC_DDR                 = 100,
	NBGLK_COEFF_LOC_VIP_SRAM            = 101,
} nbglk_coeff_location_e;

typedef struct _nbglk_coeff_property {
	vip_uint8_t     op_type;        /* nbg_operation_type_e */
	vip_uint8_t     src_type;       /* nbg_source_type_e */
	vip_uint8_t     location;       /* nbglk_coeff_location_e */
	vip_uint8_t     shared;         /* indicate current coeff is shared with another coeff */
	vip_size_t      size;           /* size of current coeff */
	vip_size_t      src_offset;     /* the offset in memory before preload */
	vip_size_t      dst_offset;     /* the offset in memory after preload:
                                       after preload done and source memory is free,
                                       dst_offset convert to src_offset */
	vip_uint32_t    shared_index;   /* valid when current coeff share coeff with another. index of shared coeff */
} nbglk_coeff_property_t;

vip_status_e nbglk_coeff_preload_patch_nn(
	vip_network network,
	vip_int32_t coeff_index,
	vip_uint8_t *patch_addr,
	nbglk_coeff_preload_patch_nn_property_e prop
);

#define HEADER_ALIGN_SIZE       64
vip_status_e nbglk_coeff_property_init(
	vip_network network
);

vip_status_e nbglk_coeff_cpu_preload(
	vip_network network
);

#if vpmdPRELOAD_COEFF > 1
vip_status_e nbglk_coeff_npu_preload_init(
	vip_network network
);

vip_status_e nbglk_coeff_npu_preload_uninit(
	vip_network network
);
#endif
#endif

#endif
