//---------------------------------------------------------
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "img_process/img_process.h"
#include "nn_utils/iou.h"
#include "nn_utils/nms.h"
#include "nn_utils/quantize.h"
#include "nn_utils/tensor.h"
#include "mmf2_module.h"
#include "module_vipnn.h"
#include "fwfs.h"
#include "hal_cache.h"
#include "avcodec.h"

#define DBG_LEVEL	LOG_ERR

#define LOG_OFF		4
#define LOG_ERR		3
#define LOG_MSG		2
#define LOG_INF		1
#define LOG_ALL		0

#define dprintf(level, ...) if(level >= DBG_LEVEL) printf(__VA_ARGS__)

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

#define MAX_FACE_CNT MAX_DETECT_OBJ_NUM
static box_t face_box[MAX_FACE_CNT];
static box_t *p_face_box[MAX_FACE_CNT];
static int face_cnt = 0;
static int face_in_width, face_in_height;

void *scrfd_get_network_filename(void)
{
	return (void *)"NN_MDL/scrfd.nb";	// fix name for NN model binary
}

void scrfd_set_network_init_info(void *m)
{
	nnmodel_t *model = (nnmodel_t *)m;
	face_in_width  = model->input_param.dim[0].size[0];
	face_in_height = model->input_param.dim[0].size[1];
}

//--------PRE PROCESS-------------------------------------------

static int scrfd_rgb_preprocess(void *data_in, nn_data_param_t *data_param, void *tensor_in, nn_tensor_param_t *tensor_param)
{
	void **tensor = (void **)tensor_in;
	rect_t *roi = &data_param->img.roi;

	img_t img_in, img_out;
	img_in.data   = (uint8_t *)data_in;
	img_in.width  = data_param->img.width;
	img_in.height = data_param->img.height;
	img_out.width  = face_in_width;
	img_out.height = face_in_height;

	img_out.data   = (uint8_t *)tensor[0];
	//printf("src %d %d, dst %d %d\n\r", img_in.width, img_in.height, img_out.width, img_out.height);
	//printf("roi %d %d %d %d \n\r", roi->xmin, roi->ymin, roi->xmax, roi->ymax);

	if (img_in.width == img_out.width && img_in.height == img_out.height) {
		// return PP_USE_INPUT to use video RGB buffer to do inference
		return PP_USE_INPUT;
	} else {
		//img_resize_planar(&img_in, roi, &img_out);  // resize src ROI area to dst
		img_scaled_into_letterbox(&img_in, &img_out);
		dcache_clean_by_addr((uint32_t *)img_out.data, img_out.width * img_out.height * 3);
	}
	return PP_USE_RESULT;
}

static int scrfd_nv12_preprocess(void *data_in, nn_data_param_t *data_param, void *tensor_in, nn_tensor_param_t *tensor_param)
{
	void **tensor = (void **)tensor_in;
	rect_t *roi = &data_param->img.roi;

	img_t img_in, img_out;
	img_in.data   = (uint8_t *)data_in;
	img_in.width  = data_param->img.width;
	img_in.height = data_param->img.height;
	img_out.width  = face_in_width;
	img_out.height = face_in_height;

	img_out.yuv.y_data   = (uint8_t *)tensor[0];
	img_out.yuv.uv_data   = (uint8_t *)tensor[1];

	int y_len = tensor_param->dim[0].size[0] * tensor_param->dim[0].size[1];
	int uv_len = tensor_param->dim[1].size[0] * tensor_param->dim[1].size[1];
	if (img_in.width == face_in_width && img_in.height == face_in_height) {
		// return PP_USE_INPUT to use video RGB buffer to do inference
		return PP_USE_INPUT;
	} else {
		img_nv12_resize_bilinear(&img_in, &img_out);
		dcache_clean_by_addr((uint32_t *)img_out.yuv.y_data, y_len);
		dcache_clean_by_addr((uint32_t *)img_out.yuv.uv_data, uv_len);
	}
	return PP_USE_RESULT;
}

int scrfd_preprocess(void *data_in, nn_data_param_t *data_param, void *tensor_in, nn_tensor_param_t *tensor_param)
{
	if (data_param->codec_type == AV_CODEC_ID_RGB888 && tensor_param->count == 1) {

		return scrfd_rgb_preprocess(data_in, data_param, tensor_in, tensor_param);

	} else if (data_param->codec_type == AV_CODEC_ID_NV12 && tensor_param->count == 2) {

		return scrfd_nv12_preprocess(data_in, data_param, tensor_in, tensor_param);

	} else {
		printf("[%s] warn: unexpected image input type for scrfd\r\n", __func__);
		return PP_ERROR;
	}
}

static void facebox_dump(int log_level)
{
	if (log_level >= DBG_LEVEL) {
		printf("--------------------------------------------------\r\n");
		printf("facebox dump\r\n");
		printf("--------------------------------------------------\r\n");
		for (int i = 0; i < face_cnt; i++) {
			printf("x,y,w,h:%6.2f %6.2f %6.2f %6.2f %6.2f\r\n", face_box[i].x, face_box[i].y, face_box[i].w, face_box[i].h, face_box[i].score);
		}
		printf("--------------------------------------------------\r\n");
	}
}

//--------POST PROCESS-------------------------------------------

static float score_thres = 0.5;
static float nms_thres = 0.3;

static void generate_bboxes_kps_single_stride(float thres, int stride, int pic_width, int pic_height,
		void *score, void *bbox, void *kps,
		nn_tensor_format_t *score_fmt, nn_tensor_format_t *bbox_fmt, nn_tensor_format_t *kps_fmt)
{
	int num_anchors = 2;
	int num_grid_w = pic_width / stride;
	int num_grid_h = pic_height  / stride;
	int num_points = num_grid_w * num_grid_h * num_anchors;	// 2 = num of anchor

	//for (unsigned int i = 0; i < num_points; ++i)
	for (int cy = 0; cy < num_grid_h; cy++) {
		for (int cx = 0; cx < num_grid_w; cx++) {
			for (int a = 0; a < num_anchors; a++) {
				int i = (cy * num_grid_w + cx) * num_anchors + a;
				float score_curr = get_tensor_value(score, i, score_fmt);
				if (score_curr > thres && face_cnt < MAX_FACE_CNT) {
					box_t *facebox_tmp = &face_box[face_cnt];
					float l = get_tensor_value(bbox, i * 4 + 0, bbox_fmt); //  q2f(bbox[i*4 + 0], bbox_fmt) ;
					float t = get_tensor_value(bbox, i * 4 + 1, bbox_fmt); //  q2f(bbox[i*4 + 1], bbox_fmt) ;
					float r = get_tensor_value(bbox, i * 4 + 2, bbox_fmt); //  q2f(bbox[i*4 + 2], bbox_fmt) ;
					float b = get_tensor_value(bbox, i * 4 + 3, bbox_fmt); //  q2f(bbox[i*4 + 3], bbox_fmt) ;
					float x1 = (cx - l) * stride / pic_width;
					float y1 = (cy - t) * stride / pic_height;
					float x2 = (cx + r) * stride / pic_width;
					float y2 = (cy + b) * stride / pic_height;
					x1 = max(x1, 0);
					y1 = max(y1, 0);
					x2 = min(x2, 1);
					y2 = min(y2, 1);
					facebox_tmp->x = x1;
					facebox_tmp->y = y1;
					facebox_tmp->w = x2 - x1;
					facebox_tmp->h = y2 - y1;
					facebox_tmp->score = score_curr;
					facebox_tmp->invalid = 0;

					for (int j = 0; j < 5; j++) {
						float kps_l = get_tensor_value(kps, i * 10 + 2 * j, kps_fmt); 	//   q2f(kps[i * 10 + 2 * j], kps_fmt) ;
						float kps_t = get_tensor_value(kps, i * 10 + 2 * j + 1, kps_fmt);  //   q2f(kps[i * 10 + 2 * j + 1], kps_fmt) ;
						facebox_tmp->landmarks[2 * j] = ((cx + kps_l) * stride) / pic_width;
						facebox_tmp->landmarks[2 * j + 1] = ((cy + kps_t) * stride) / pic_height ;
					}

					face_cnt++;
				}
			}
		}
	}
}

#ifdef ARDUINO_SDK
int scrfd_postprocess(void *tensor_out, nn_tensor_param_t *param, void *res)
#else
static int scrfd_postprocess(void *tensor_out, nn_tensor_param_t *param, void *res)
#endif
{
	int tensor_cnt = param->count;
	void **tensor = (void **)tensor_out;

	void *score_8 = (void *)tensor[0];
	void *score_16 = (void *)tensor[1];
	void *score_32 = (void *)tensor[2];

	void *bbox_8 = (void *)tensor[3];
	void *bbox_16 = (void *)tensor[4];
	void *bbox_32 = (void *)tensor[5];

	void *kps_8 = (void *)tensor[6];
	void *kps_16 = (void *)tensor[7];
	void *kps_32 = (void *)tensor[8];

	//int max_cnt = ctx->params.out_res_max_cnt;
	facedetect_res_t *fd_res = (facedetect_res_t *)res;

	dprintf(LOG_INF, "[scrfd post] res %p\n\r", fd_res);

	face_cnt = 0;
	memset(face_box, 0, sizeof(face_box));

	generate_bboxes_kps_single_stride(score_thres, 8, face_in_width, face_in_height, score_8, bbox_8, kps_8, &param->format[0], &param->format[3],
									  &param->format[6]);
	generate_bboxes_kps_single_stride(score_thres, 16, face_in_width, face_in_height, score_16, bbox_16, kps_16, &param->format[1], &param->format[4],
									  &param->format[7]);
	generate_bboxes_kps_single_stride(score_thres, 32, face_in_width, face_in_height, score_32, bbox_32, kps_32, &param->format[2], &param->format[5],
									  &param->format[8]);

	dprintf(LOG_INF, "[scrfd post]decode done.\r\n");

	// dump facebox
	facebox_dump(LOG_INF);

	// NMS
	do_nms(1, face_cnt, nms_thres, face_box, p_face_box, IOU);

	// fill result
	int obj_num = 0;
	for (int i = 0; i < face_cnt; i++) {
		box_t *b = &face_box[i];
		dprintf(LOG_INF, "p %2.6f, invalid %d\n\r", b->score, b->invalid);
		if (b->invalid == 0) {//&& (obj_num < max_cnt)) {
			fd_res[obj_num].result[0] = 0;  // face only
			fd_res[obj_num].result[1] = b->score;
			fd_res[obj_num].result[2] = b->x;	// top_x
			fd_res[obj_num].result[3] = b->y;	// top_y
			fd_res[obj_num].result[4] = b->x + b->w; // bottom_x
			fd_res[obj_num].result[5] = b->y + b->h; // bottom_y

			for (int k = 0; k < 6; k++) {
				dprintf(LOG_MSG, "[scrfd post] result %d %f\n\r", k, fd_res[obj_num].result[k]);
			}

			for (int j = 0; j < 5; j++) {
				fd_res[obj_num].landmark.pos[j].x = b->landmarks[2 * j];
				fd_res[obj_num].landmark.pos[j].y = b->landmarks[2 * j + 1];
			}

			obj_num++;
		}
	}
	return obj_num;
}

void scrfd_set_confidence_thresh(void *confidence_thresh)
{
	score_thres = *(float *)confidence_thresh;
	printf("set scrfd score thresh to %f\n\r", *(float *)confidence_thresh);
}

void scrfd_set_nms_thresh(void *nms_thresh)
{
	nms_thres = *(float *)nms_thresh;
	printf("set scrfd NMS thresh to %f\n\r", *(float *)nms_thresh);
}

nnmodel_t scrfd_fwfs = {
	.nb 			= scrfd_get_network_filename,
	.set_init_info  = scrfd_set_network_init_info,
	.preprocess 	= scrfd_preprocess,
	.postprocess 	= scrfd_postprocess,
	.model_src 		= MODEL_SRC_FILE,
	.set_confidence_thresh  = scrfd_set_confidence_thresh,
	.set_nms_thresh     = scrfd_set_nms_thresh,

	.name = "SCRFD"
};

