//------------------------------------------------------
// NanoDet-Plus  https://github.com/RangiLyu/nanodet
//------------------------------------------------------
// Citation:
// RangiLyu. (2021). NanoDet-Plus: Super fast and high accuracy lightweight anchor-free object detection model.
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

static float nanodet_confidence_thresh = 0.5;    // default
static float nanodet_nms_thresh = 0.3;      // default
static int nanodet_in_width, nanodet_in_height;
static const int reg_max = 7; // 'reg_max' set in the training config. Default: 7.

static void *nanodet_plus_m_get_network_filename(void)
{
	return (void *)"NN_MDL/nanodet_plus_m.nb";
}

void nanodet_set_network_init_info(void *m)
{
	nnmodel_t *model = (nnmodel_t *)m;
	nanodet_in_width  = model->input_param.dim[0].size[0];
	nanodet_in_height = model->input_param.dim[0].size[1];
}

static int nanodet_preprocess(void *data_in, nn_data_param_t *data_param, void *tensor_in, nn_tensor_param_t *tensor_param)
{
	void **tensor = (void **)tensor_in;
	rect_t *roi = &data_param->img.roi;

	img_t img_in, img_out;

	img_in.width  = data_param->img.width;
	img_in.height = data_param->img.height;
	img_out.width  = tensor_param->dim[0].size[0];
	img_out.height = tensor_param->dim[0].size[1];

	img_in.data   = (unsigned char *)data_in;
	img_out.data   = (unsigned char *)tensor[0];
	//printf("src %d %d, dst %d %d\n\r", img_in.width, img_in.height, img_out.width, img_out.height);
	//printf("roi %d %d %d %d \n\r", roi->xmin, roi->ymin, roi->xmax, roi->ymax);

	if (img_in.width == img_out.width && img_in.height == img_out.height) {
		// return PP_USE_INPUT to use video RGB buffer to do inference
		return PP_USE_INPUT;
	} else {
		// resize src ROI area to dst
		img_resize_planar(&img_in, roi, &img_out);
		dcache_clean_by_addr((uint32_t *)img_out.data, img_out.width * img_out.height * 3);
	}

	return PP_USE_RESULT;
}

typedef struct CenterPrior_s {
	int x;
	int y;
	int stride;
} CenterPrior_t;

static CenterPrior_t *pCenterPriors = NULL;

static void generate_grid_center_priors(const int target_w, const int target_h, int *strides, int stride_size)
{
	int center_priors_cnt = 0;
	for (int i = 0; i < stride_size; i++) {
		int stride = strides[i];
		int feat_w = ceil((float)nanodet_in_width / stride);
		int feat_h = ceil((float)nanodet_in_height / stride);
		for (int y = 0; y < feat_h; y++) {
			for (int x = 0; x < feat_w; x++) {
				CenterPrior_t *ct = &pCenterPriors[center_priors_cnt];
				ct->x = x;
				ct->y = y;
				ct->stride = stride;
				center_priors_cnt++;
			}
		}
	}
}

static void activation_function_softmax(float *src, float *dst, int length)
{
	float alpha = 0;
	for (int i = 0; i < length; i++) {
		alpha = max(alpha, *(src + i));
	}

	float denominator = 0;
	for (int i = 0; i < length; ++i) {
		dst[i] = fast_exp(src[i] - alpha);
		denominator += dst[i];
	}
	for (int i = 0; i < length; ++i) {
		dst[i] /= denominator;
	}
}

static void nanodet_decode_bbox(float *dfl_det, int label, float score, int x, int y, int stride)
{
	float ct_x = x * stride;
	float ct_y = y * stride;

	float dis_pred[4];
	for (int i = 0; i < 4; i++) {
		float dis = 0;
		float dis_after_sm[reg_max + 1];
		activation_function_softmax(dfl_det + i * (reg_max + 1), dis_after_sm, reg_max + 1);
		for (int j = 0; j < (reg_max + 1); j++) {
			dis += j * dis_after_sm[j];
		}
		dis *= stride;
		dis_pred[i] = dis;
	}

	float xmin = (ct_x - dis_pred[0]) / nanodet_in_width;
	float ymin = (ct_y - dis_pred[1]) / nanodet_in_height;
	float xmax = (ct_x + dis_pred[2]) / nanodet_in_width;
	float ymax = (ct_y + dis_pred[3]) / nanodet_in_height;
	xmin = max(xmin, 0);
	ymin = max(ymin, 0);
	xmax = min(xmax, 1);
	ymax = min(ymax, 1);

	res_box[box_idx].class_idx = label;
	res_box[box_idx].prob = score;
	res_box[box_idx].x = xmin;
	res_box[box_idx].y = ymin;
	res_box[box_idx].w = xmax - xmin;
	res_box[box_idx].h = ymax - ymin;
	box_idx++;
}

static void nanodet_decode(void *preds, CenterPrior_t *pCenterPriors, int center_priors_cnt, int num_class, nn_tensor_format_t *tensor_fmt)
{
	int num_points = center_priors_cnt;
	int num_channels = num_class + (reg_max + 1) * 4;

	for (int idx = 0; idx < num_points; idx++) {
		int cur_label = 0;

		switch (tensor_fmt->buf_type) {
		default:
		case VIP_BUFFER_FORMAT_UINT8: {
			uint8_t *tmp_pred_u8 = (uint8_t *)preds + idx * num_channels;
			for (int label = 0; label < num_class; label++) {
				if (tmp_pred_u8[label] > tmp_pred_u8[cur_label]) {
					cur_label = label;
				}
			}
			break;
		}
		case VIP_BUFFER_FORMAT_INT8: {
			int8_t *tmp_pred_s8 = (int8_t *)preds + idx * num_channels;
			for (int label = 0; label < num_class; label++) {
				if (tmp_pred_s8[label] > tmp_pred_s8[cur_label]) {
					cur_label = label;
				}
			}
			break;
		}
		case VIP_BUFFER_FORMAT_INT16: {
			int16_t *tmp_pred_s16 = (int16_t *)preds + idx * num_channels;
			for (int label = 0; label < num_class; label++) {
				if (tmp_pred_s16[label] > tmp_pred_s16[cur_label]) {
					cur_label = label;
				}
			}
			break;
		}
		case VIP_BUFFER_FORMAT_FP16: {
			__fp16 *tmp_pred_f16 = (__fp16 *)preds + idx * num_channels;
			for (int label = 0; label < num_class; label++) {
				if (tmp_pred_f16[label] > tmp_pred_f16[cur_label]) {
					cur_label = label;
				}
			}
			break;
		}
		case VIP_BUFFER_FORMAT_FP32: {
			float *tmp_pred_f32 = (float *)preds + idx * num_channels;
			for (int label = 0; label < num_class; label++) {
				if (tmp_pred_f32[label] > tmp_pred_f32[cur_label]) {
					cur_label = label;
				}
			}
			break;
		}
		}

		float score = get_tensor_value(preds, idx * num_channels + cur_label, tensor_fmt);

		if (score > nanodet_confidence_thresh) {
			int bbox_pred_start_idx = idx * num_channels + num_class;
			int bbox_pred_cnt = (reg_max + 1) * 4;  // 32
			float bbox_pred[bbox_pred_cnt];
			for (int i = 0; i < bbox_pred_cnt; i++) {
				bbox_pred[i] = get_tensor_value(preds, bbox_pred_start_idx + i, tensor_fmt);
			}
			nanodet_decode_bbox(bbox_pred, cur_label, score, pCenterPriors[idx].x, pCenterPriors[idx].y, pCenterPriors[idx].stride);
		}
	}
}

static int nanodet_postprocess(void *tensor_out, nn_tensor_param_t *param, void *res)
{
	void **tensor = (void **)tensor_out;

	objdetect_res_t *od_res = (objdetect_res_t *)res;

	/* preds is a tensor with shape [num_points, num_channels] */
	int num_channels = param->dim[0].size[0];  // 112
	int num_points = param->dim[0].size[1];  // 3598 for 416x416, 2125 for 320x320
	int classes = num_channels - (reg_max + 1) * 4;  // 80

	// generate grid center priors
	if (!pCenterPriors) {
		pCenterPriors = (CenterPrior_t *)malloc(num_points * sizeof(CenterPrior_t));
		if (!pCenterPriors) {
			printf("fail to allocate memory for pCenterPriors\r\n");
			return -1;
		}
		int strides[4] = {8, 16, 32, 64};
		generate_grid_center_priors(nanodet_in_width, nanodet_in_height, strides, sizeof(strides) / sizeof(int));
	}

	// reset box & index
	box_idx = 0;
	memset(res_box, 0, sizeof(res_box));

	// decode
	nanodet_decode((void *)tensor[0], pCenterPriors, num_points, classes, &param->format[0]);

	// NMS
	do_nms(classes, box_idx, nanodet_nms_thresh, res_box, p_res_box, DIOU);

	// dump result
	/*
	for (int i = 0; i < box_idx; i++) {
		box_t *b = &res_box[i];
		printf("x y w h = %f %f %f %f\n\r", b->x, b->y, b->w, b->h);
		printf("x y w h = %3.0f %3.0f %3.0f %3.0f\n\r", b->x * nanodet_in_width, b->y * nanodet_in_height, b->w * nanodet_in_width, b->h * nanodet_in_height);
		printf("p %2.6f, class %d, invalid %d\n\r", b->prob, b->class_idx, b->invalid);
	}
	*/

	// fill result
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

static void nanodet_release(void)
{
	if (pCenterPriors) {
		free(pCenterPriors);
		pCenterPriors = NULL;
	}
}

static void nanodet_set_confidence_thresh(void *confidence_thresh)
{
	nanodet_confidence_thresh = *(float *)confidence_thresh;
	printf("set nanodet confidence thresh to %f\n\r", *(float *)confidence_thresh);
}

static void nanodet_set_nms_thresh(void *nms_thresh)
{
	nanodet_nms_thresh = *(float *)nms_thresh;
	printf("set nanodet NMS thresh to %f\n\r", *(float *)nms_thresh);
}

nnmodel_t nanodet_plus_m = {
	.nb 			= nanodet_plus_m_get_network_filename,
	.set_init_info  = nanodet_set_network_init_info,
	.preprocess 	= nanodet_preprocess,
	.postprocess 	= nanodet_postprocess,
	.model_src 		= MODEL_SRC_FILE,
	.set_confidence_thresh   = nanodet_set_confidence_thresh,
	.set_nms_thresh     = nanodet_set_nms_thresh,
	.release        = nanodet_release,

	.name = "NanoDet_plus_m"
};

