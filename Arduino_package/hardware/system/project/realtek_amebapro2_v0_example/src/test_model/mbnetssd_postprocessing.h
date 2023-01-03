#ifndef MBNETSSD_POSTPORCESSING_H
#define MBNETSSD_POSTPORCESSING_H

#include <stdbool.h>
#include <mmf2_module.h>
#include "module_vipnn.h"

#define FRAMEWORK_CAFFE 		0
#define FRAMEWORK_TENSORFLOW 	1

typedef struct mbnetssd_post_cfg_s {
	//nn_tensor_format_t *fmt[2];
	//nn_tensor_dim_t *dim[2];
	nn_tensor_param_t *param;
	const float *anchorbox;
	float confidence_thresh;
	float nms_thresh;
	int  framework;

	// ? by model?
	int  *filter_class;
	int  filter_cnt;
	const char  **classname;

	// get from dim
	int class_cnt;
	int anchor_cnt;
} mbnetssd_post_cfg_t;

void mbnetssd_postprocessing(mbnetssd_post_cfg_t *cfg, void *tensor0, void *tensor1, float *detect_result, int *detect_obj_num);
void mbnetssd_show_results(mbnetssd_post_cfg_t *cfg, float *detect_result, int *detect_obj_num);

#endif