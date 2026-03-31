//------------------------------------------------------
// Yolov3-tiny & Yolov4-tiny & Yolov7-tiny (Darknet)
//------------------------------------------------------
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "img_process/img_process.h"
#include "nn_utils/sigmoid.h"
#include "nn_utils/iou.h"
#include "nn_utils/nms.h"
#include "nn_utils/quantize.h"
#include "nn_utils/tensor.h"
#include "mmf2_module.h"
#include "module_vipnn.h"
#include "hal_cache.h"
#include "avcodec.h"

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

//MAX_DETECT_OBJ_NUM defined in module_vipnn.h
static box_t res_box[MAX_DETECT_OBJ_NUM];
static box_t *p_res_box[MAX_DETECT_OBJ_NUM];
static int box_idx;

static float yolo_confidence_thresh = 0.5;    // default
static float yolo_nms_thresh = 0.3;      // default
static int yolo_new_coords = 0;  // 0 --> yolov3 & yolov4,  1 --> yolov7
static float *pAnchor = NULL;
static int yolo_in_width, yolo_in_height;

// yolov4-tiny & yolov3-tiny
// https://github.com/AlexeyAB/darknet/blob/master/cfg/yolov4-tiny.cfg
static float anchor_yolov3v4_2layer[6][2] = {
	{81, 82}, {135, 169}, {344, 319},		// 13x13
	{23, 27}, {37, 58}, {81, 82},			// 26x26
};

// yolov4-tiny-3l (3 output layer)
// https://github.com/AlexeyAB/darknet/blob/master/cfg/yolov4-tiny-3l.cfg
static float anchor_yolo_3layer[9][2] = {
	{142, 110}, {192, 243}, {459, 401},		// 13x13
	{36, 75}, {76, 55}, {72, 146},			// 26x26
	{12, 16}, {19, 36}, {40, 28},			// 52x52
};

// yolov7-tiny-3l (3 output layer)
// https://github.com/AlexeyAB/darknet/blob/master/cfg/yolov7-tiny.cfg
static float anchor_yolov7_3layer[9][2] = {
	{10, 13}, {16, 30}, {33, 23},			// 52x52
	{30, 61}, {62, 45}, {59, 119},			// 26x26
	{116, 90}, {156, 198}, {373, 326},		// 13x13
};

void *yolov3_get_network_filename(void)
{
	return (void *)"NN_MDL/yolov3_tiny.nb";
}

void *yolov4_get_network_filename(void)
{
	return (void *)"NN_MDL/yolov4_tiny.nb";
}

void *yolov7_get_network_filename(void)
{
	return (void *)"NN_MDL/yolov7_tiny.nb";
}

void yolov3_set_network_init_info(void *m)
{
	yolo_new_coords = 0;
	pAnchor = &anchor_yolov3v4_2layer[0][0]; // setup anchor

	nnmodel_t *model = (nnmodel_t *)m;
	yolo_in_width  = model->input_param.dim[0].size[0];
	yolo_in_height = model->input_param.dim[0].size[1];
}

void yolov4_set_network_init_info(void *m)
{
	yolo_new_coords = 0;
	pAnchor = &anchor_yolov3v4_2layer[0][0]; // setup anchor

	nnmodel_t *model = (nnmodel_t *)m;
	yolo_in_width  = model->input_param.dim[0].size[0];
	yolo_in_height = model->input_param.dim[0].size[1];
}

void yolov7_set_network_init_info(void *m)
{
	yolo_new_coords = 1;
	pAnchor = &anchor_yolov7_3layer[0][0]; // setup anchor

	nnmodel_t *model = (nnmodel_t *)m;
	yolo_in_width  = model->input_param.dim[0].size[0];
	yolo_in_height = model->input_param.dim[0].size[1];
}

static int yolo_rgb_preprocess(void *data_in, nn_data_param_t *data_param, void *tensor_in, nn_tensor_param_t *tensor_param)
{
	void **tensor = (void **)tensor_in;
	rect_t *roi = &data_param->img.roi;

	img_t img_in, img_out;
	img_in.data   = (uint8_t *)data_in;
	img_in.width  = data_param->img.width;
	img_in.height = data_param->img.height;
	img_out.width  = yolo_in_width;
	img_out.height = yolo_in_height;

	img_out.data   = (uint8_t *)tensor[0];
	//printf("src %d %d, dst %d %d\n\r", img_in.width, img_in.height, img_out.width, img_out.height);
	//printf("roi %d %d %d %d \n\r", roi->xmin, roi->ymin, roi->xmax, roi->ymax);

	if (img_in.width == img_out.width && img_in.height == img_out.height) {
		// return PP_USE_INPUT to use video RGB buffer to do inference
		return PP_USE_INPUT;
	} else {
		img_resize_planar(&img_in, roi, &img_out);  // resize src ROI area to dst
		dcache_clean_by_addr((uint32_t *)img_out.data, img_out.width * img_out.height * 3);
	}
	return PP_USE_RESULT;
}

static int yolo_nv12_preprocess(void *data_in, nn_data_param_t *data_param, void *tensor_in, nn_tensor_param_t *tensor_param)
{
	void **tensor = (void **)tensor_in;
	rect_t *roi = &data_param->img.roi;

	img_t img_in, img_out;
	img_in.data   = (uint8_t *)data_in;
	img_in.width  = data_param->img.width;
	img_in.height = data_param->img.height;
	img_out.width  = yolo_in_width;
	img_out.height = yolo_in_height;

	img_out.yuv.y_data   = (uint8_t *)tensor[0];
	img_out.yuv.uv_data   = (uint8_t *)tensor[1];

	int y_len = tensor_param->dim[0].size[0] * tensor_param->dim[0].size[1];
	int uv_len = tensor_param->dim[1].size[0] * tensor_param->dim[1].size[1];
	if (img_in.width == yolo_in_width && img_in.height == yolo_in_height) {
		// return PP_USE_INPUT to use video RGB buffer to do inference
		return PP_USE_INPUT;
	} else {
		img_nv12_resize_bilinear(&img_in, &img_out);
		dcache_clean_by_addr((uint32_t *)img_out.yuv.y_data, y_len);
		dcache_clean_by_addr((uint32_t *)img_out.yuv.uv_data, uv_len);
	}
	return PP_USE_RESULT;
}

int yolo_preprocess(void *data_in, nn_data_param_t *data_param, void *tensor_in, nn_tensor_param_t *tensor_param)
{
	if (data_param->codec_type == AV_CODEC_ID_RGB888 && tensor_param->count == 1) {

		return yolo_rgb_preprocess(data_in, data_param, tensor_in, tensor_param);

	} else if (data_param->codec_type == AV_CODEC_ID_NV12 && tensor_param->count == 2) {

		return yolo_nv12_preprocess(data_in, data_param, tensor_in, tensor_param);

	} else {
		printf("[%s] warn: unexpected image input type for yolo\r\n", __func__);
		return PP_ERROR;
	}
}

typedef struct data_format_s {
	nn_tensor_format_t *format;
	nn_tensor_dim_t *dim;
} data_format_t;

static int yolo_get_data_idx(data_format_t *fmt, int i, int j, int n, int ei, int class_num)
{
	int w = fmt->dim->size[0];
	int h = fmt->dim->size[1];
	return (((5 + class_num) * n + ei) * h * w + w * j + i);
}

static void *yolo_get_data_addr(void *data, data_format_t *fmt, int i, int j, int n, int ei, int class_num)
{
	int idx = yolo_get_data_idx(fmt, i, j, n, ei, class_num);
	return get_tensor_addr(data, idx, fmt->format);
}

static float yolo_get_data(void *data, data_format_t *fmt, int i, int j, int n, int ei, int class_num)
{
	int idx = yolo_get_data_idx(fmt, i, j, n, ei, class_num);
	return get_tensor_value(data, idx, fmt->format);
}

static int yolo_filter_class(void *data, data_format_t *fmt, int i, int j, int n, int *class_idx, float threshold, int class_num)
{
	int count = 0;
	switch (fmt->format->buf_type) {
	case VIP_BUFFER_FORMAT_INT16: {
		int16_t th16 = f_to_s16(threshold, fmt->format->fix_point_pos);
		for (int x = 0; x < class_num; x++) {
			int16_t tmp = *(int16_t *)yolo_get_data_addr(data, fmt, i, j, n, 5 + x, class_num);
			if (tmp > th16) {
				class_idx[count] = x;
				count++;
			}
		}
		break;
	}
	case VIP_BUFFER_FORMAT_INT8: {
		int8_t th8 = f_to_s8(threshold, fmt->format->fix_point_pos);
		for (int x = 0; x < class_num; x++) {
			int8_t tmp = *(int8_t *)yolo_get_data_addr(data, fmt, i, j, n, 5 + x, class_num);
			if (tmp > th8) {
				class_idx[count] = x;
				count++;
			}
		}
		break;
	}
	case VIP_BUFFER_FORMAT_UINT8: {
		uint8_t th8 = f_to_u8(threshold, fmt->format->zero_point, fmt->format->scale);
		for (int x = 0; x < class_num; x++) {
			uint8_t tmp = *(uint8_t *)yolo_get_data_addr(data, fmt, i, j, n, 5 + x, class_num);
			if (tmp > th8) {
				class_idx[count] = x;
				count++;
			}
		}
		break;
	}
	case VIP_BUFFER_FORMAT_FP16: {
		__fp16 th16f = f_to_bf16(threshold);
		for (int x = 0; x < class_num; x++) {
			__fp16 tmp = *(__fp16 *)yolo_get_data_addr(data, fmt, i, j, n, 5 + x, class_num);
			if (tmp > th16f) {
				class_idx[count] = x;
				count++;
			}
		}
		break;
	}
	default: {
		float th32f = threshold;
		for (int x = 0; x < class_num; x++) {
			float tmp = *(float *)yolo_get_data_addr(data, fmt, i, j, n, 5 + x, class_num);
			if (tmp > th32f) {
				class_idx[count] = x;
				count++;
			}
		}
		break;
	}
	}

	//if(count > 0)WTF

	//	printf("count %d\n\r", count);

	return count;
}

static int __decode_yolo(data_format_t *fmt, void *out, int i, int j, int n, void *p_anchor)
{
	int max_i = 0;
	float p = 0;  // --> objectness
	float cp = 0; // --> class prob
	int class_idx[80];
	int class_cnt = 0;
	int pass_cnt = 0;

	float (*anchor)[2] = (float (*)[2])p_anchor;

	//yolo_13_t *out13 = (yolo_13_t*)out;
	int grid_w = fmt->dim->size[0];
	int grid_h = fmt->dim->size[1];

	int classes = fmt->dim->size[2] / 3 - 5;

	if (yolo_new_coords) {
		p = yolo_get_data(out, fmt, i, j, n, 4, classes);
	} else {
		p = sigmoid(yolo_get_data(out, fmt, i, j, n, 4, classes));
	}

	if (p < yolo_confidence_thresh) {
		return 0;
	}
	//int max_i = __find_max_index13(out, i, j, n, 80);

	if (yolo_new_coords) {
		class_cnt = yolo_filter_class(out, fmt, i, j, n, class_idx, 0.5, classes);
	} else {
		class_cnt = yolo_filter_class(out, fmt, i, j, n, class_idx, inv_sigmoid(0.5), classes);
	}

	for (int ci = 0; ci < class_cnt; ci++) {
		max_i = class_idx[ci];
		if (yolo_new_coords) {
			cp = yolo_get_data(out, fmt, i, j, n, 5 + max_i, classes);
		} else {
			cp = sigmoid(yolo_get_data(out, fmt, i, j, n, 5 + max_i, classes));
		}

		if (cp * p >= yolo_confidence_thresh && box_idx < MAX_DETECT_OBJ_NUM) {

			float tx, ty, tw, th;
			float cx, cy, w, h;
			if (yolo_new_coords) {
				tx = yolo_get_data(out, fmt, i, j, n, 0, classes);
				ty = yolo_get_data(out, fmt, i, j, n, 1, classes);
				tw = yolo_get_data(out, fmt, i, j, n, 2, classes);
				th = yolo_get_data(out, fmt, i, j, n, 3, classes);

				cx = (i + tx * 2 - 0.5) / grid_w;
				cy = (j + ty * 2 - 0.5) / grid_h;
				w = tw * tw * 4 * anchor[n][0] / yolo_in_width;
				h = th * th * 4 * anchor[n][1] / yolo_in_height;
			} else {
				tx = sigmoid(yolo_get_data(out, fmt, i, j, n, 0, classes));
				ty = sigmoid(yolo_get_data(out, fmt, i, j, n, 1, classes));
				tw = yolo_get_data(out, fmt, i, j, n, 2, classes);
				th = yolo_get_data(out, fmt, i, j, n, 3, classes);

				cx = (i + tx) / grid_w;
				cy = (j + ty) / grid_h;
				w = exp(tw) * anchor[n][0] / yolo_in_width;
				h = exp(th) * anchor[n][1] / yolo_in_height;
			}

			float x = cx - w / 2;
			float y = cy - h / 2;
			x = max(x, 0);
			x = min(x, 1);
			y = max(y, 0);
			y = min(y, 1);

			//printf("x y w h = %f %f %f %f\n\r", x, y, w, h);
			//printf("x y w h = %3.0f %3.0f %3.0f %3.0f\n\r", x*yolo_in_width, y*yolo_in_height, w*yolo_in_width, h*yolo_in_height);
			//printf("tx %2.6f ty %2.6f tw %2.6f th %2.6f , p %2.6f, cp %2.6f, c %d, cn %d\n\r", tx, ty, tw, th, p, cp, max_i, class_cnt);

			res_box[box_idx].class_idx = max_i;
			res_box[box_idx].prob = cp * p;
			res_box[box_idx].x = x;
			res_box[box_idx].y = y;
			res_box[box_idx].w = w;
			res_box[box_idx].h = h;
			box_idx++;
			pass_cnt++;
		}
	}

	return pass_cnt;
}

int yolo_postprocess(void *tensor_out, nn_tensor_param_t *param, void *res)
{
	void **tensor = (void **)tensor_out;

	int classes = param->dim[0].size[2] / 3 - 5;  // tensor depth = (5 + classes) * 3
	int output_count = param->count;

	objdetect_res_t *od_res = (objdetect_res_t *)res;

	// reset box index
	box_idx = 0;
	memset(res_box, 0, sizeof(res_box));

	// check anchor is set
	if (pAnchor == NULL) {
		return 0;
	}

	data_format_t fmt;
	for (int n = 0; n < output_count; n++) {
		uint8_t *bb0 = (uint8_t *)tensor[n];
		fmt.format = &param->format[n];
		fmt.dim = &param->dim[n];
		int w = fmt.dim->size[0];
		int h = fmt.dim->size[1];

		//printf("BB0 %d x %d\n\r", w, h);
		for (int i = 0; i < w; i++) {
			for (int j = 0; j < h; j++) {
				int ret = 0;
				ret += __decode_yolo(&fmt, bb0, i, j, 0, (void *)&pAnchor[n * 3 * 2]);
				ret += __decode_yolo(&fmt, bb0, i, j, 1, (void *)&pAnchor[n * 3 * 2]);
				ret += __decode_yolo(&fmt, bb0, i, j, 2, (void *)&pAnchor[n * 3 * 2]);
				//if (ret > 0) {
				//	printf("%d %d\n\r-------\n\r", i, j);
				//}
			}
		}
	}

	do_nms(classes, box_idx, yolo_nms_thresh, res_box, p_res_box, DIOU);

	// dump result
	/*
	for (int i = 0; i < box_idx; i++) {
		box_t *b = &res_box[i];
		printf("x y w h = %f %f %f %f\n\r", b->x, b->y, b->w, b->h);
		printf("x y w h = %3.0f %3.0f %3.0f %3.0f\n\r", b->x * yolo_in_width, b->y * yolo_in_height, b->w * yolo_in_width, b->h * yolo_in_height);
		printf("p %2.6f, obj %2.6f, cp %2.6f, class %d, invalid %d\n\r", b->prob, b->objectness, b->class_prob, b->class_idx, b->invalid);
	}
	*/
	// init start idx
	int od_num = 0;
	for (int i = 0; i < box_idx; i++) {
		box_t *obj = &res_box[i];

		if (obj->invalid == 0) {
			od_res[od_num].result[0] = obj->class_idx;
			od_res[od_num].result[1] = obj->prob;
			od_res[od_num].result[2] = obj->x;	// top_x
			od_res[od_num].result[3] = obj->y;	// top_y
			od_res[od_num].result[4] = obj->x + obj->w; // bottom_x
			od_res[od_num].result[5] = obj->y + obj->h; // bottom_y
			od_num++;
		}
	}

	return od_num;
}

void yolo_set_confidence_thresh(void *confidence_thresh)
{
	yolo_confidence_thresh = *(float *)confidence_thresh;
	printf("set yolo confidence thresh to %f\n\r", *(float *)confidence_thresh);
}

void yolo_set_nms_thresh(void *nms_thresh)
{
	yolo_nms_thresh = *(float *)nms_thresh;
	printf("set yolo NMS thresh to %f\n\r", *(float *)nms_thresh);
}

nnmodel_t yolov3_tiny = {
	.nb 			= yolov3_get_network_filename,
	.set_init_info  = yolov3_set_network_init_info,
	.preprocess 	= yolo_preprocess,
	.postprocess 	= yolo_postprocess,
	.model_src 		= MODEL_SRC_FILE,
	.set_confidence_thresh   = yolo_set_confidence_thresh,
	.set_nms_thresh     = yolo_set_nms_thresh,

	.name = "YOLOv3t"
};

nnmodel_t yolov4_tiny = {
	.nb 			= yolov4_get_network_filename,
	.set_init_info  = yolov4_set_network_init_info,
	.preprocess 	= yolo_preprocess,
	.postprocess 	= yolo_postprocess,
	.model_src 		= MODEL_SRC_FILE,
	.set_confidence_thresh   = yolo_set_confidence_thresh,
	.set_nms_thresh     = yolo_set_nms_thresh,

	.name = "YOLOv4t"
};

nnmodel_t yolov7_tiny = {
	.nb 			= yolov7_get_network_filename,
	.set_init_info  = yolov7_set_network_init_info,
	.preprocess 	= yolo_preprocess,
	.postprocess 	= yolo_postprocess,
	.model_src 		= MODEL_SRC_FILE,
	.set_confidence_thresh   = yolo_set_confidence_thresh,
	.set_nms_thresh     = yolo_set_nms_thresh,

	.name = "YOLOv7t"
};


//----------------------------------------------------------
// Yolo-Fastest  https://github.com/dog-qiuqiu/Yolo-Fastest
//----------------------------------------------------------
// Citation: 
// dog-qiuqiu. (2021, July 24). dog-qiuqiu/Yolo-Fastest: yolo-fastest-v1.1.0 (Version v.1.1.0). Zenodo.
//----------------------------------------------------------

static float anchor_yolo_fastest_2layer[6][2] = {
	{115, 73}, {119,199}, {242,238},
	{12, 18}, {37, 49}, {52,132},
};

void yolo_fastest_set_network_init_info(void *m)
{
	yolo_new_coords = 0;
	pAnchor = &anchor_yolo_fastest_2layer[0][0]; // setup anchor

	nnmodel_t *model = (nnmodel_t *)m;
	yolo_in_width  = model->input_param.dim[0].size[0];
	yolo_in_height = model->input_param.dim[0].size[1];
}

void *yolo_fastest_get_network_filename_init(void)
{
	return (void *)"NN_MDL/yolo_fastest.nb";	// fix name for NN model binary
}

nnmodel_t yolo_fastest = {
	.nb 			= yolo_fastest_get_network_filename_init,
	.set_init_info  = yolo_fastest_set_network_init_info,
	.preprocess 	= yolo_preprocess,
	.postprocess 	= yolo_postprocess,
	.model_src 		= MODEL_SRC_FILE,
	.set_confidence_thresh   = yolo_set_confidence_thresh,
	.set_nms_thresh     = yolo_set_nms_thresh,

	.name = "YOLO_fastest"
};

