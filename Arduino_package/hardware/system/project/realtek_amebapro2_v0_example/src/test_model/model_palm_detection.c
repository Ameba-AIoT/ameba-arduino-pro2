//------------------------------------------------------
// MediaPipe Palm Detection
//------------------------------------------------------
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "nn_api.h"
#include "mmf2_module.h"
#include "module_vipnn.h"
#include "hal_cache.h"
#include "pre_process.h"
#include "img_process/img_process.h"
#include "nn_utils/iou.h"
#include "nn_utils/nms.h"
#include "nn_utils/quantize.h"
#include "nn_utils/tensor.h"
#include "nn_utils/sigmoid.h"
#include <isp_ctrl_api.h>
#include "arm_math.h"
#include <fwfs.h>

#define PALM_LANDMARK_NUM   (7)

#include "./palm_detection_anchorbox.h"
static float palm_detection_confidence_thresh = 0.5;
static float palm_detection_nms_thresh = 0.5;
static uint32_t palm_detect_in_width = 0;
static uint32_t palm_detect_in_height = 0;
static img_t img_in, img_out = {0};

void palm_detection_set_network_init_info(void *m)
{
	nnmodel_t *model = (nnmodel_t *)m;
	palm_detect_in_width  = model->input_param.dim[0].size[0];
	palm_detect_in_height = model->input_param.dim[0].size[1];
}

int palm_detection_preprocess(void *data_in, nn_data_param_t *data_param, void *tensor_in, nn_tensor_param_t *tensor_param)
{
	void **tensor = (void **)tensor_in;
	img_out.data   = (unsigned char *)tensor[0];
	img_in.width  = data_param->img.width;
	img_in.height = data_param->img.height;
	img_out.width  = palm_detect_in_width;
	img_out.height = palm_detect_in_height;
	
	img_in.data   = (unsigned char *)data_in;

	if (img_in.width == img_out.width && img_in.height == img_out.height) {
		// return PP_USE_INPUT to use video RGB buffer to do inference
		return PP_USE_INPUT;
	} else {
		//only support image in = out size
		printf("[%s] error: only support %dx%d\r\n", __func__, palm_detect_in_width, palm_detect_in_height);
		return PP_ERROR;
		//img_scaled_into_letterbox(&img_in, &img_out);
		//dcache_clean_by_addr((uint32_t *)img_out.data, img_out.width * img_out.height * 3);
	}

	return PP_USE_RESULT;
}

static box_t hand_box[MAX_HAND_DETECT_NUM];
static box_t *p_hand_box[MAX_HAND_DETECT_NUM];
static int detect_hand_num = 0;

static int decode_bbox(box_t *bboxrect, int idx)
{
	float cx = bboxrect->x + palm_detection_anchorbox_192_192[idx * 4] * palm_detect_in_width;
	float cy = bboxrect->y + palm_detection_anchorbox_192_192[idx * 4 + 1] * palm_detect_in_height;
	bboxrect->x = cx - bboxrect->w / 2;
	bboxrect->y = cy - bboxrect->h / 2;

	if (bboxrect->x < 0 || bboxrect->y < 0
		|| (bboxrect->x + bboxrect->w) >= palm_detect_in_width
		|| bboxrect->y + bboxrect->h >= palm_detect_in_height) {
		return -1;
	}

	for (int i = 0; i < PALM_LANDMARK_NUM; i++) {
		bboxrect->landmarks[i * 2] = bboxrect->landmarks[i * 2] + palm_detection_anchorbox_192_192[idx * 4] * palm_detect_in_width;
		bboxrect->landmarks[i * 2 + 1] = bboxrect->landmarks[i * 2 + 1] + palm_detection_anchorbox_192_192[idx * 4 + 1] * palm_detect_in_height;
	}

	return 0;
}

typedef struct data_format_s {
	nn_tensor_format_t *format;
	nn_tensor_dim_t *dim;
} data_format_t;

int palm_detection_postprocess(void *tensor_out, nn_tensor_param_t *param, void *res)
{
	void **tensor = (void **)tensor_out;
	data_format_t palm_fmt, scores_fmt;

	uint8_t *palm = (uint8_t *)tensor[0];   // shape: (2016,18)
	uint8_t *scores = (uint8_t *)tensor[1]; // shape: (2016,1)

	palm_fmt.format = &param->format[0];
	palm_fmt.dim = &param->dim[0];
	int palm_out_size = palm_fmt.dim->size[0];
	scores_fmt.format = &param->format[1];
	scores_fmt.dim = &param->dim[1];

	uint8_t datasize = 0;
	switch (scores_fmt.format->type) {
	case VIP_BUFFER_QUANTIZE_DYNAMIC_FIXED_POINT:
		// s16
		datasize = 2;
		break;
	case VIP_BUFFER_QUANTIZE_TF_ASYMM:
		// u8
		datasize = 1;
		break;
	default:
		printf("Unknown tensor format\r\n");
		return 0;
	}

	palmdetect_res_t *palm_detection_res = (palmdetect_res_t *)res;

	/*
	    out_reg shape is [number of anchors, 18]
	    Second dimension 0 - 4 are bounding box offset, width and height: dx, dy, w ,h
	    Second dimension 4 - 17 are 7 hand keypoint x and y coordinates: x1,y1,x2,y2,...x7,y7
	*/
	memset(hand_box, 0x0, sizeof(hand_box));
	detect_hand_num = 0;
	for (int i = 0; i < scores_fmt.dim->size[1]; i++) {
		float score = sigmoid(q2f(&scores[i * datasize], scores_fmt.format));
		if (score > palm_detection_confidence_thresh) {
			box_t bboxrect;
			memset(&bboxrect, 0x0, sizeof(box_t));
			bboxrect.score = score;
			bboxrect.x = q2f(&palm[i * palm_out_size * datasize], palm_fmt.format);
			bboxrect.y = q2f(&palm[(i * palm_out_size + 1) * datasize], palm_fmt.format);
			bboxrect.w =  q2f(&palm[(i * palm_out_size + 2) * datasize], palm_fmt.format);
			bboxrect.h =  q2f(&palm[(i * palm_out_size + 3) * datasize], palm_fmt.format);
			for (int li = 0; li < palm_out_size - 4; li++) {
				bboxrect.landmarks[li] = q2f(&palm[i * palm_out_size * datasize + (li + 4) * datasize], palm_fmt.format);
			}
			if (decode_bbox(&bboxrect, i) == 0) {
				memcpy(&hand_box[detect_hand_num++], &bboxrect, sizeof(box_t));
			}
		}
	}

	do_nms(1, detect_hand_num, palm_detection_nms_thresh, hand_box, p_hand_box, IOU);

	int obj_num = 0;
	for (int i = 0; i < detect_hand_num; i++) {
		box_t *b = &hand_box[i];
		if (b->invalid == 0) {
			palm_detection_res[obj_num].result[0] = 0;  // palm only
			palm_detection_res[obj_num].result[1] = b->score;
			palm_detection_res[obj_num].result[2] = b->x;	// top_x
			palm_detection_res[obj_num].result[3] = b->y;	// top_y
			palm_detection_res[obj_num].result[4] = b->x + b->w; // bottom_x
			palm_detection_res[obj_num].result[5] = b->y + b->h; // bottom_y

			for (int j = 0; j < PALM_LANDMARK_NUM; j++) {
				palm_detection_res[obj_num].landmark.pos[j].x = (int)b->landmarks[2 * j];
				palm_detection_res[obj_num].landmark.pos[j].y = (int)b->landmarks[2 * j + 1];
				//printf("landmark %d: (%ld, %ld)\r\n", j, palm_detection_res[obj_num].landmark.pos[j].x, palm_detection_res[obj_num].landmark.pos[j].y);
			}

			obj_num++;
		}
	}

	//printf("palm_detection_res.obj_num:%d\r\n", obj_num);

	return obj_num;
}


void palm_detection_set_confidence_thresh(void *confidence_thresh)
{
	palm_detection_confidence_thresh = *(float *)confidence_thresh;
	printf("set palm_detection confidence thresh to %f\n\r", *(float *)confidence_thresh);
}

void palm_detection_set_nms_thresh(void *nms_thresh)
{
	palm_detection_nms_thresh = *(float *)nms_thresh;
	printf("set palm_detection NMS thresh to %f\n\r", *(float *)nms_thresh);
}



//---------------------------------------------------------------------------------------------------
void *palm_detection_get_network_filename(void)
{
	return (void *)"NN_MDL/palm_detection.nb";	// fix name for NN model binary
}


nnmodel_t palm_detection_fwfs = {
	.nb             = palm_detection_get_network_filename,
	.set_init_info	= palm_detection_set_network_init_info,
	.preprocess     = palm_detection_preprocess,
	.postprocess    = palm_detection_postprocess,
	.model_src      = MODEL_SRC_FILE,
	.set_confidence_thresh  = palm_detection_set_confidence_thresh,
	.set_nms_thresh         = palm_detection_set_nms_thresh,

	.name           = "PALM_DETECTION",
};

