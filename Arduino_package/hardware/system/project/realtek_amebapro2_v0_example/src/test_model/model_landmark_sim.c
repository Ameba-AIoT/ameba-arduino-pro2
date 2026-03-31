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

#define DBG_LEVEL	LOG_ERR

#define LOG_OFF		4
#define LOG_ERR		3
#define LOG_MSG		2
#define LOG_INF		1
#define LOG_ALL		0

#define dprintf(level, ...) if(level >= DBG_LEVEL) printf(__VA_ARGS__)


void *lmsim_get_network_filename(void)
{
	return (void *)"NN_MDL/yamnet_s_hybrid.nb";	// use yamnet_s to do a dummy inference
}

static void lmsim_input_setup(void *last_res, int i, nn_data_param_t *input_param)
{
	/* setup roi and landmark */
	facedetect_res_t *fd_res = (facedetect_res_t *)last_res;

	// setup roi by result array
	int xmin, ymin, xmax, ymax;

	dprintf(LOG_MSG, "[lmsim setup] %p, %d\n\r", fd_res, i);

	dprintf(LOG_MSG, "[lmsim setup] w %d\n\r", input_param->img.width);
	dprintf(LOG_MSG, "[lmsim setup] h %d\n\r", input_param->img.height);
	for (int k = 0; k < 6; k++) {
		dprintf(LOG_MSG, "[lmsim setup] result %d %f\n\r", k, fd_res[i].result[k]);
	}

	// result[2...4] ==> bbox
	float tmp;
	tmp = fd_res[i].result[2];
	if (tmp <= 1.0) {
		xmin = (int)(tmp * input_param->img.width);
	} else {
		xmin = (int)(tmp);
	}

	tmp = fd_res[i].result[3];
	if (tmp <= 1.0) {
		ymin = (int)(tmp * input_param->img.height);
	} else {
		ymin = (int)(tmp);
	}

	tmp = fd_res[i].result[4];
	if (tmp <= 1.0) {
		xmax = (int)(tmp * input_param->img.width);
	} else {
		xmax = (int)(tmp);
	}

	tmp = fd_res[i].result[5];
	if (tmp <= 1.0) {
		ymax = (int)(tmp * input_param->img.height);
	} else {
		ymax = (int)(tmp);
	}

	// fill roi in landmark input setup
	input_param->img.roi.xmin = xmin;
	input_param->img.roi.ymin = ymin;
	input_param->img.roi.xmax = xmax;
	input_param->img.roi.ymax = ymax;
	input_param->priv = (void *)&fd_res[i];

	dprintf(LOG_MSG, "[lmsim setup] update pic w %d, h %d\n\r", input_param->img.width, input_param->img.height);
	dprintf(LOG_MSG, "[lmsim setup] update ROI %d %d %d %d\n\r", input_param->img.roi.xmin, input_param->img.roi.ymin, input_param->img.roi.xmax,
			input_param->img.roi.ymax);
}

//--------PRE PROCESS-------------------------------------------
static int lmsim_preprocess(void *data_in, nn_data_param_t *data_param, void *tensor_in, nn_tensor_param_t *tensor_param)
{
	void **tensor = (void **)tensor_in;
	rect_t *roi = (rect_t *)&data_param->img.roi;

	img_t img_in, img_out;

	img_in.width  = data_param->img.width;
	img_in.height = data_param->img.height;
	img_out.width  = tensor_param->dim[0].size[0];
	img_out.height = tensor_param->dim[0].size[1];

	img_in.data = (uint8_t *)data_in;
	img_out.data = (uint8_t *)tensor[0];
	dprintf(LOG_MSG, "[lmsim pre]src %d %d, dst %d %d\n\r", img_in.width, img_in.height, img_out.width, img_out.height);
	dprintf(LOG_MSG, "[lmsim pre]roi %d %d %d %d \n\r", roi->xmin, roi->ymin, roi->xmax, roi->ymax);

	// scale to input tensor size
	if (img_in.width == img_out.width && img_in.height == img_out.height) {
		dprintf(LOG_INF, "[lmsim pre]same size, just copy!\n\r");
		//memcpy(img_out.data, img_in.data, img_out.width * img_out.height * 3);
		img_dma_copy(img_out.data, img_in.data, img_out.width * img_out.height * 3);
	} else {
		dprintf(LOG_INF, "[lmsim pre]resize to NN input size!\n\r");
		img_resize_planar(&img_in, roi, &img_out);
	}

	dcache_clean_by_addr((uint32_t *)img_out.data, img_out.width * img_out.height * 3);
	return PP_USE_RESULT;
}


//--------POST PROCESS-------------------------------------------
static int lmsim_postprocess(void *tensor_out, nn_tensor_param_t *param, void *res)
{
	// res: result array start address

	// simulation: copy scrfd landmark
	//int max_cnt = ctx->params.out_res_max_cnt;
	facedetect_res_t *lm_res = (facedetect_res_t *)res;

	// last model result is in param->priv
	facedetect_res_t *fd_res = (facedetect_res_t *)param->priv;

	dprintf(LOG_MSG, "[lmsim post] res %f %f %f %f %f %f\n\r", fd_res->result[0], fd_res->result[1], fd_res->result[2], fd_res->result[3], fd_res->result[4],
			fd_res->result[5]);

	memcpy(lm_res->result, fd_res->result, sizeof(fd_res->result));
	memcpy(&lm_res->landmark, &fd_res->landmark, sizeof(fd_res->landmark));

	return 1;

}


nnmodel_t lmsim_fwfs = {
	.nb 			= lmsim_get_network_filename,
	.preprocess 	= lmsim_preprocess,
	.postprocess 	= lmsim_postprocess,
	.cas_in_setup	= lmsim_input_setup,
	.model_src 		= MODEL_SRC_FILE,

	.name = "LANDMARK_SIM"
};

