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

#ifndef _GC_VIP_CPU_H
#define _GC_VIP_CPU_H
#include "gc_vip_lite.h"
#include "gc_vip_lite_network.h"

#if vpmdENABLE_SUPPORT_CPU_LAYER

#if defined(__linux__) || defined(_WIN32)
#include <math.h>
#endif

#define F16_EXPONENT_BITS           0x1F
#define F16_EXPONENT_SHIFT          10
#define F16_MANTISSA_BITS           ((1 << F16_EXPONENT_SHIFT) - 1)
#define F16_MANTISSA_SHIFT          (23 - F16_EXPONENT_SHIFT)
#define F16_EXPONENT_BIAS           15
#define gcvip_enum_base(vendor, id)    (((vendor) << 20) | (id << 12))

#define gcvip_math_abs(x)               (((x) < 0)    ? -(x) :  (x))
#define gcvip_math_max(x, y)            (((x) >= (y)) ? (x)   : (y))
#define gcvip_math_min(x, y)            (((x) <= (y)) ?  (x) :  (y))

#if defined(__linux__) || defined(_WIN32)
#define gcvip_math_exp(x) (vip_float_t)(exp(x))
#else
vip_float64_t gcvip_math_exp(vip_float64_t x);
#endif


typedef enum _gcvip_nn_round_mode_e {
	GCVIP_NN_ROUNDING_MODE_SIMPLE_ROUNDING = 0,
	GCVIP_NN_ROUNDING_MODE_RTNE,
	GCVIP_NN_ROUNDING_MODE_RTZ,
	GCVIP_NN_ROUNDING_MODE_RTNI,
} gcvip_nn_round_mode_e;

enum gcvip_sw_operation_type_e {
	GCVIP_SW_OPERATION_NONE             = 0,
	GCVIP_SW_OPERATION_RPN              = 1,
	GCVIP_SW_OPERATION_USER_CPU         = 2,
	GCVIP_SW_OPERATION_RPN_SORT_NMS     = 3,
};

typedef struct _gcvip_layer_buffer {
	vip_uint8_t    *buffer;
	vip_uint32_t    dim_count;
	vip_uint32_t    dims[MAX_NUM_DIMS];
	vip_enum        data_format;
	vip_enum        data_type;
	vip_enum        quant_format;
	vip_int32_t     fixpoint_zeropoint;
	vip_float_t     tfscale;
} gcvip_layer_buffer_t, *gcvip_layer_buffer;

typedef struct _gcvip_sw_layer_rpn {
	gcvip_lite_segment_base_s base;

	gcvip_layer_buffer_t    score;
	gcvip_layer_buffer_t    bbox;
	gcvip_layer_buffer_t    anchor;
	gcvip_layer_buffer_t    img_info;
	gcvip_layer_buffer_t    roi_output;
	gcvip_layer_buffer_t    score_output;
	gcvip_layer_buffer_t    feature_stride;
	gcvip_layer_buffer_t    min_size;
	gcvip_layer_buffer_t    pre_nms_topn;
	gcvip_layer_buffer_t    post_nms_topn;
	gcvip_layer_buffer_t    nms_thresh;
} gcvip_sw_layer_rpn_t;

typedef struct _gcvip_sw_layer_rpn_sort_nms {
	gcvip_lite_segment_base_s base;

	gcvip_layer_buffer_t      proposal;
	gcvip_layer_buffer_t      roi_output;
	gcvip_layer_buffer_t      score_output;
	gcvip_layer_buffer_t      pre_nms_topn;
	gcvip_layer_buffer_t      post_nms_topn;
	gcvip_layer_buffer_t      nms_thresh;
} gcvip_sw_layer_rpn_sort_nms_t;

typedef struct _gcvip_sw_user_t {
	gcvip_lite_segment_base_s  base;

	gcvip_layer_buffer_t       *buffers;
	vip_uint32_t               buffer_num;
}
gcvip_sw_layer_user_t;


/*
@brief Save data to buffer.
*/
vip_status_e gcvip_save_dataext(
	vip_int32_t format,
	vip_enum quant_format,
	vip_int32_t index,
	vip_float64_t data,
	vip_ptr dst_data,
	vip_int8_t fixedPointPos,
	vip_int32_t zeroPoint,
	vip_float_t scale,
	vip_enum roundMode
);

/*
@brief Get data from buffer.
*/
vip_float_t gcvip_get_dataext(
	vip_int32_t format,
	vip_enum quant_format,
	vip_uint32_t index,
	vip_uint8_t_ptr data,
	vip_int8_t fixPointPos,
	vip_int32_t zeroPoint,
	vip_float_t scale
);

/*
@brief Rlease resouce create in patch_sw function flow.
@param segment The segment object.
*/
vip_status_e gcvip_sw_release_resource(
	gcvip_lite_segment_t *segment
);

/*
@brief Run software layer.
@param network The network object.
@param segment The segment object.
*/
vip_status_e gcvip_sw_do_layer(
	vip_network_t *network,
	gcvip_lite_segment_t *segment
);

/*
@brief Parser NBG file to prepare software layer.
@param network The network object.
@param segment The segment object.
*/
vip_status_e gcvip_sw_prepare_layer(
	vip_network_t *network,
	gcvip_lite_segment_t *segment
);

#endif
#endif
