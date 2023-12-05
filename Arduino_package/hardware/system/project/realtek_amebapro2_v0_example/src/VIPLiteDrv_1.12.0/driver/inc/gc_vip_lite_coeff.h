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

#ifndef _GC_VIP_LITE_COEFF_H
#define _GC_VIP_LITE_COEFF_H

#include <gc_vip_common.h>
#include <vip_lite.h>

vip_status_e gcvip_coeff_get_property(
	vip_network network,
	vip_uint32_t patch_index,
	vip_uint8_t **base_logical,
	vip_uint32_t *base_physical,
	vip_uint32_t *offset,
	vip_uint32_t *size
);

#if vpmdPRELOAD_COEFF
typedef enum _gcvip_coeff_preload_patch_nn_property {
	GCVIP_COEFF_PATH_NN_NONE           = 0,
	GCVIP_COEFF_PATH_NN_CMD            = 1,
	GCVIP_COEFF_PATH_NN_KERNEL_HEADER  = 2,
	GCVIP_COEFF_PATH_NN_MAX,
} gcvip_coeff_preload_patch_nn_property_e;

vip_status_e gcvip_coeff_preload_patch_nn(
	vip_network network,
	vip_int32_t coeff_index,
	vip_uint8_t *patch_addr,
	gcvip_coeff_preload_patch_nn_property_e prop
);

#define HEADER_ALIGN_SIZE       64
vip_status_e gcvip_coeff_property_init(
	vip_network network
);

vip_status_e gcvip_coeff_cpu_preload(
	vip_network network
);

#if vpmdPRELOAD_COEFF > 1
vip_status_e gcvip_coeff_npu_preload_in_init(
	vip_network network
);

vip_status_e gcvip_coeff_npu_preload_in_uninit(
	vip_network network
);

vip_status_e gcvip_coeff_npu_preload_in(
	vip_network network
);

vip_status_e gcvip_coeff_npu_preload_out(
	vip_network network
);

vip_status_e gcvip_coeff_npu_preload_vipsram(
	vip_network network
);
#endif
#endif

#endif
