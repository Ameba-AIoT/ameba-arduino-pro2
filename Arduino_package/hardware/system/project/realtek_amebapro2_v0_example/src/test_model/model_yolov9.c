//------------------------------------------------------
// yolov9v3-tiny & yolov9v4-tiny & yolov9v7-tiny (Darknet)
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

static float yolov9_confidence_thresh = 0.3;    // default
static float yolov9_nms_thresh = 0.3;      // default
static int yolov9_in_width, yolov9_in_height;

static int *yolov9_desired_class_list;
static int yolov9_desired_class_list_len;

void *yolov9_get_network_filename(void)
{
	return (void *)"NN_MDL/yolov9_tiny.nb";
}

void yolov9_set_network_init_info(void *m)
{
	nnmodel_t *model = (nnmodel_t *)m;
	yolov9_in_width  = model->input_param.dim[0].size[0];
	yolov9_in_height = model->input_param.dim[0].size[1];
}

typedef struct data_format_s {
	nn_tensor_format_t *format;
	nn_tensor_dim_t *dim;
} data_format_t;

int yolov9_preprocess(void *data_in, nn_data_param_t *data_param, void *tensor_in, nn_tensor_param_t *tensor_param)
{
	void **tensor = (void **)tensor_in;
	rect_t *roi = &data_param->img.roi;

	img_t img_in, img_out;

	img_in.width  = data_param->img.width;
	img_in.height = data_param->img.height;
	img_out.width  = tensor_param->dim[0].size[0];
	img_out.height = tensor_param->dim[0].size[1];
	img_in.data   = (uint8_t *)data_in;
	img_out.data   = (uint8_t *)tensor[0];

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

static void yolov9_decode(void *bb_box_info, void *preds, int num_class, data_format_t *fmt_bb, data_format_t *fmt_p)
{
	int num_anchor = fmt_bb->dim->size[0]; //3549
	int num_bb = fmt_bb->dim->size[1];  //4
	for (int idx = 0; idx < num_anchor; idx++) {
		int cur_label = yolov9_desired_class_list[0] * num_anchor;

		//printf("mode: %d\n", param->format[0].buf_type);
		switch (fmt_p->format->buf_type) {
		default:
		case VIP_BUFFER_FORMAT_UINT8: {
			uint8_t *tmp_pred_u8 = (uint8_t *)preds + idx;
			for (int i = 0; i < yolov9_desired_class_list_len; i++) {
				if (tmp_pred_u8[yolov9_desired_class_list[i]*num_anchor] > tmp_pred_u8[cur_label]) {
					cur_label = yolov9_desired_class_list[i] * num_anchor;
				}
			}
			break;
		}
		case VIP_BUFFER_FORMAT_INT8: {
			int8_t *tmp_pred_s8 = (int8_t *)preds + idx;
			for (int i = 0; i < yolov9_desired_class_list_len; i++) {
				if (tmp_pred_s8[yolov9_desired_class_list[i]*num_anchor] > tmp_pred_s8[cur_label]) {
					cur_label = yolov9_desired_class_list[i] * num_anchor;
				}
			}
			break;
		}
		case VIP_BUFFER_FORMAT_INT16: {
			int16_t *tmp_pred_s16 = (int16_t *)preds + idx;
			for (int i = 0; i < yolov9_desired_class_list_len; i++) {
				if (tmp_pred_s16[yolov9_desired_class_list[i]*num_anchor] > tmp_pred_s16[cur_label]) {
					cur_label = yolov9_desired_class_list[i] * num_anchor;
				}
			}
			break;
		}
		case VIP_BUFFER_FORMAT_FP16: {
			__fp16 *tmp_pred_f16 = (__fp16 *)preds + idx;
			for (int i = 0; i < yolov9_desired_class_list_len; i++) {
				if (tmp_pred_f16[yolov9_desired_class_list[i]*num_anchor] > tmp_pred_f16[cur_label]) {
					cur_label = yolov9_desired_class_list[i] * num_anchor;
				}
			}
			break;
		}
		case VIP_BUFFER_FORMAT_FP32: {
			float *tmp_pred_f32 = (float *)preds + idx;
			for (int i = 0; i < yolov9_desired_class_list_len; i++) {
				if (tmp_pred_f32[yolov9_desired_class_list[i]*num_anchor] > tmp_pred_f32[cur_label]) {
					cur_label = yolov9_desired_class_list[i] * num_anchor;
				}
			}
			break;
		}
		}
		float score = get_tensor_value(preds, idx + cur_label, fmt_p->format);
		if (score > yolov9_confidence_thresh) {
			int bbox_pred_start_idx = idx;
			int bbox_pred_cnt = 4;  // 32
			float bbox_pred[bbox_pred_cnt];
			for (int i = 0; i < bbox_pred_cnt; i++) {
				bbox_pred[i] = get_tensor_value(bb_box_info, bbox_pred_start_idx + i * num_anchor, fmt_bb->format);
			}
			float cx = bbox_pred[0];
			float cy = bbox_pred[1];
			float ow = bbox_pred[2];
			float oh = bbox_pred[3];
			float xmin = (cx - ow * 0.5) / yolov9_in_width;
			float ymin = (cy - oh * 0.5) / yolov9_in_height;
			float xmax = (cx + ow * 0.5) / yolov9_in_width;
			float ymax = (cy + oh * 0.5) / yolov9_in_height;
			xmin = max(xmin, 0);
			ymin = max(ymin, 0);
			xmax = min(xmax, 1);
			ymax = min(ymax, 1);
			int class_id;
			class_id = cur_label / num_anchor;
			res_box[box_idx].class_idx = class_id;
			res_box[box_idx].prob = score;
			res_box[box_idx].x = xmin;
			res_box[box_idx].y = ymin;
			res_box[box_idx].w = xmax - xmin;
			res_box[box_idx].h = ymax - ymin;
			box_idx++;

		}
	}
}

int yolov9_postprocess(void *tensor_out, nn_tensor_param_t *param, void *res)
{
	void **tensor = (void **)tensor_out;

	objdetect_res_t *od_res = (objdetect_res_t *)res;
	// reset box & index
	box_idx = 0;
	memset(res_box, 0, sizeof(res_box));

	int num_anchor = param->dim[0].size[0]; //3549
	int classes = param->dim[1].size[1];  // 80

	data_format_t fmt_bb, fmt_p;
	fmt_bb.format = &param->format[0];
	fmt_bb.dim = &param->dim[0];
	fmt_p.format = &param->format[1];
	fmt_p.dim = &param->dim[1];
	yolov9_decode((void *)tensor[0], (void *)tensor[1], classes, &fmt_bb, &fmt_p);

	// NMS
	do_nms(classes, box_idx, yolov9_nms_thresh, res_box, p_res_box, DIOU);


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

void yolov9_set_confidence_thresh(void *confidence_thresh)
{
	yolov9_confidence_thresh = *(float *)confidence_thresh;
	printf("set yolov9 confidence thresh to %f\n\r", *(float *)confidence_thresh);
}

void yolov9_set_nms_thresh(void *nms_thresh)
{
	yolov9_nms_thresh = *(float *)nms_thresh;
	printf("set yolov9 NMS thresh to %f\n\r", *(float *)nms_thresh);
}

void yolov9_set_desired_class(nn_desired_class_t *desired_class_list)
{
	yolov9_desired_class_list_len = desired_class_list->len;
	yolov9_desired_class_list = desired_class_list->class_info;
	printf("len: %d\n", yolov9_desired_class_list_len);
	printf("class id: ");
	for (int i = 0; i < yolov9_desired_class_list_len; i++) {
		printf("%d ", yolov9_desired_class_list[i]);
	}
	printf("\n");
}
nnmodel_t yolov9_tiny = {
	.nb 			= yolov9_get_network_filename,
	.set_init_info  = yolov9_set_network_init_info,
	.preprocess 	= yolov9_preprocess,
	.postprocess 	= yolov9_postprocess,
	.model_src 		= MODEL_SRC_FILE,
	.set_confidence_thresh   = yolov9_set_confidence_thresh,
	.set_nms_thresh     = yolov9_set_nms_thresh,
	.set_desired_class = yolov9_set_desired_class,
	.name = "YOLOv9t"
};



