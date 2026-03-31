//------------------------------------------------------
// MediaPipe Hand Landmark Model
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
#include <model_hand_landmark.h>

#define PALM_RATIO (1.45)

#ifdef ARDUINO_SDK
void hand_landmark_input_setup(void *last_res, int i, nn_data_param_t *input_param)
#else
static void hand_landmark_input_setup(void *last_res, int i, nn_data_param_t *input_param)
#endif
{
	palmdetect_res_t *palmdet_res = (palmdetect_res_t *)last_res;

	//width:NN_WIDTH, height:NN_HEIGHT
	//printf("%s: width:%d, height:%d\r\n", __func__, input_param->img.width, input_param->img.height);

	//Based on the ROI of the palm detected by the 192x192 palm detection model
	input_param->img.roi.xmin = palmdet_res[i].result[2];
	input_param->img.roi.ymin = palmdet_res[i].result[3];
	input_param->img.roi.xmax = palmdet_res[i].result[4];
	input_param->img.roi.ymax = palmdet_res[i].result[5];

	//printf("%s():roi of palm:%d %d %d %d\r\n", __func__, input_param->img.roi.xmin, input_param->img.roi.ymin, input_param->img.roi.xmax, input_param->img.roi.ymax);

	//Place the information of the 7 landmarks of the palm into input_param.
	for (int x = 0; x < 7; x++) {
		input_param->img.landmark.pos[x].x = palmdet_res[i].landmark.pos[x].x;
		input_param->img.landmark.pos[x].y = palmdet_res[i].landmark.pos[x].y;
	}
	input_param->priv = (void *)&palmdet_res[i];
}

static img_t img_in, img_out;
typedef struct data_format_s {
	nn_tensor_format_t *format;
	nn_tensor_dim_t *dim;
} data_format_t;

// Normalize angle to an equivalent angle in the range from `-π` to `π` radians.
static float normalize_radians(float angle)
{
	return angle - 2 * M_PI * floor((angle - (-M_PI)) / (2 * M_PI));
}

//Enlarge the palm box to include the fingers, control the magnification ratio, and include all fingers before performing inference with the hand_landmark model.
static void calibrate_hand_roi(int cx, int cy, int16_t w, int16_t h, rect_t *roi, float ratio)
{
	int16_t long_side = w > h ? w : h;
	long_side *= ratio;
	roi->xmin = cx - long_side;
	if (roi->xmin < 0) {
		roi->xmin = 0;
	}
	roi->ymin = cy - long_side;
	if (roi->ymin < 0) {
		roi->ymin = 0;
	}
	roi->xmax = cx + long_side;
	if (roi->xmax >= img_in.width) {
		roi->xmax = img_in.width - 1;
	}
	roi->ymax = cy + long_side;
	if (roi->ymax >= img_in.height) {
		roi->ymax = img_in.height - 1;
	}
}

static rotate_t rcfg = {0};
static rect_t hand_roi = {0};
int hand_landmark_preprocess(void *data_in, nn_data_param_t *data_param, void *tensor_in, nn_tensor_param_t *tensor_param)
{
	void **tensor = (void **)tensor_in;
	rect_t *roi = (rect_t *)&data_param->img.roi;
	landmarki_t *landmark = &data_param->img.landmark;
	uint32_t data_in_size = 0;
	//printf("palm landmark:%ld %ld\r\n", landmark->pos[2].x, landmark->pos[2].y);

	img_in.width  = data_param->img.width;
	img_in.height = data_param->img.height;
	img_out.width  = tensor_param->dim[0].size[0];
	img_out.height = tensor_param->dim[0].size[1];
	int channel_num = tensor_param->dim[0].size[2];
	img_in.data   = (unsigned char *)data_in;
	img_out.data   = (unsigned char *)tensor[0];

	//img_in:NN_WIDTH NN_WIDTH img_out:224 224
	//printf("%s: img_in:%d %d img_out:%d %d\r\n", __func__, img_in.width, img_in.height, img_out.width, img_out.height);

	data_in_size = img_out.width * img_out.height * channel_num * sizeof(uint8_t);

	//palm detection model 找到手掌的 7 個 landmark
	//The first point is the base of the palm, and the second point is below the middle finger.
	//Connect them into a line, and make sure the angle of this line points upward as much as possible.
	int len_adj = (landmark->pos[2].x - landmark->pos[0].x); //x1 - x0
	int len_opp = (landmark->pos[2].y - landmark->pos[0].y); //y1 - y0

	//Use the point below the middle finger as the rotation center, and after rotating, the middle finger points upwards.
	rcfg.cx = landmark->pos[2].x; //middle finger x
	rcfg.cy = landmark->pos[2].y; //middle finger y
	rcfg.angle = M_PI / 2.0 - atan2f((float) - len_opp, (float)len_adj);
	rcfg.angle = normalize_radians(rcfg.angle);
	//printf("angle:%f\r\n", rcfg.angle);

	//printf("%s(): roi:%d %d %d %d\r\n", __func__, roi->xmin, roi->ymin, roi->xmax, roi->ymax);
	//Move the center point of the palm ROI to the point below the middle finger, then enlarge it to include all the fingers.
	calibrate_hand_roi(rcfg.cx, rcfg.cy,
					   roi->xmax - roi->xmin,
					   roi->ymax - roi->ymin,
					   &hand_roi, PALM_RATIO);
	float arcface_lm[1][2] = {
		{(float)(img_out.width / 2), (float)(img_out.height / 2)}
	};
	//Start rotating and enlarging the image to 224x224, which serves the same purpose as face alignment here.
	img_rotation_fix((img_t *)&img_in, &hand_roi, &rcfg, (img_t *)&img_out, &arcface_lm[0]);
	dcache_clean_by_addr((uint32_t *)img_out.data, data_in_size);
	return 0;
}

int hand_landmark_postprocess(void *tensor_out, nn_tensor_param_t *param, void *res)
{
	void **tensor = (void **)tensor_out;
	data_format_t llm_fmt, handconf_fmt, handedness_fmt;
	uint8_t *llm = (void *)tensor[0];
	uint8_t *handconf_tensor = (void *)tensor[1];
	uint8_t *handedness_tensor = (void *)tensor[2];
	llm_fmt.format = &param->format[0];
	llm_fmt.dim = &param->dim[0];
	handconf_fmt.format = &param->format[1];
	handconf_fmt.dim = &param->dim[1];
	handedness_fmt.format = &param->format[2];
	handedness_fmt.dim = &param->dim[2];

	uint8_t datasize = 1;
	switch (handconf_fmt.format->type) {
	case VIP_BUFFER_QUANTIZE_DYNAMIC_FIXED_POINT:
		// s16
		datasize = 2;
		break;
	case VIP_BUFFER_QUANTIZE_TF_ASYMM:
		// u8
		datasize = 1;
		break;
	default:
		// bf16
		datasize = 2;
		break;
	}

	handland_res_t *hand_landmark_res = (handland_res_t *)res;
	hand_landmark_res->handedness = HANDEDNESS_NOTFOUND;

	float handconf = q2f(&handconf_tensor[0], handconf_fmt.format);
	float handedness = q2f(&handedness_tensor[0], handedness_fmt.format);
	//printf("handconf %f handedness %f\r\n", handconf, handedness);
	if (handconf > 0.8) {
		if (handedness < 0.3) {
			//printf("Left hand detected %f %f\r\n", handconf, handedness);
			hand_landmark_res->handedness = HANDEDNESS_LEFT;
		} else if (handedness > 0.7) {
			//printf("Right hand detected %f %f\r\n", handconf, handedness);
			hand_landmark_res->handedness = HANDEDNESS_RIGHT;
		} else {
			//printf("handedness not sure %f %f\r\n", handconf, handedness);
			hand_landmark_res->handedness = HANDEDNESS_NOTSURE;
		}

		//hand landmark model 會 output 21 個 3D landmark, z 軸目前用不到
		for (int i = 0; i < HAND_LANDMARK_NUM; i++) {
			hand_landmark_res->landmark3d.pos[i].x = roundf(q2f(&llm[i * 3 * datasize], llm_fmt.format));
			hand_landmark_res->landmark3d.pos[i].y = roundf(q2f(&llm[(i * 3 + 1) * datasize], llm_fmt.format));
			hand_landmark_res->landmark3d.pos[i].z = roundf(q2f(&llm[(i * 3 + 2) * datasize], llm_fmt.format));
			//printf("llm %d(%f,%f,%f)\r\n", i, hand_landmark_res->landmark3d.pos[i].x, hand_landmark_res->landmark3d.pos[i].y, hand_landmark_res->landmark3d.pos[i].z);
		}

		//Retain the information, and later when drawing OSD, you need to convert the coordinates back to ensure the OSD is drawn on the hand.
		hand_landmark_res->theta = rcfg.angle;
		hand_landmark_res->ratio = PALM_RATIO;
		hand_landmark_res->w = hand_roi.xmax - hand_roi.xmin;
		hand_landmark_res->h = hand_roi.ymax - hand_roi.ymin;
		hand_landmark_res->offset_x = hand_roi.xmin;
		hand_landmark_res->offset_y = hand_roi.ymin;
	}
	return 0;
}
void hand_landmark_set_confidence_thresh(void *confidence_thresh)
{
	//UNUSED
}
void hand_landmark_set_nms_thresh(void *nms_thresh)
{
	//UNUSED
}
void *hand_landmark_get_network_filename(void)
{
	return (void *)"NN_MDL/hand_landmark.nb";	// fix name for NN model binary
}
nnmodel_t hand_landmark_fwfs = {
	.nb             = hand_landmark_get_network_filename,
	.preprocess     = hand_landmark_preprocess,
	.postprocess    = hand_landmark_postprocess,
	.model_src      = MODEL_SRC_FILE,
	.set_confidence_thresh  = hand_landmark_set_confidence_thresh,
	.set_nms_thresh     = hand_landmark_set_nms_thresh,
	.cas_in_setup	= hand_landmark_input_setup,
	.name           = "HAND_LANDMARK"
};
