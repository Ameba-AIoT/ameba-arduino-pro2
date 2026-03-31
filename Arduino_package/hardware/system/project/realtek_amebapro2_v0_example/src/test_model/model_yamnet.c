//------------------------------------------------------
// YAMNET
//------------------------------------------------------
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sys_api.h"
#include "mmf2_module.h"
#include "module_vipnn.h"
#include "hal_cache.h"

#ifdef ARDUINO_SDK
void *yamnet_get_network_filename(void)
#else
static void *yamnet_get_network_filename(void)
#endif
{
	return (void *)"NN_MDL/yamnet_fp16.nb";	// fix name for NN model binary
}

#define MEAN_COUNT	  2	 // 4 times = ~ 1.9s
#define OVERLAP_RATIO 50 // 50 = 50%
static short *src_temp = NULL;
static int src_temp_cnt = 0;
static int tensor_in_cnt = 0;
static int overlap_cnt = -1;
static void *class_score = NULL;
static int class_update_idx = 0;

#ifdef ARDUINO_SDK
int yamnet_preprocess(void *data_in, nn_data_param_t *data_param, void *tensor_in, nn_tensor_param_t *tensor_param)
#else
static int yamnet_preprocess(void *data_in, nn_data_param_t *data_param, void *tensor_in, nn_tensor_param_t *tensor_param)
#endif
{
	void **tensor = (void **)tensor_in;

	short *src = (short *)data_in;
	int src_sample_cnt = data_param->size_in_byte / (data_param->aud.bit_pre_sample / 8);

	//printf("in %d, level %d\n\r", src_sample_cnt, tensor_in_cnt);

	__fp16 *input   = (__fp16 *)tensor[0];
	int tensor_require_cnt = tensor_param->dim[0].size[0] * tensor_param->dim[0].size[1];

	if (overlap_cnt < 0) {
		overlap_cnt = tensor_require_cnt * OVERLAP_RATIO / 100;
		memset(input, 0, tensor_require_cnt * sizeof(__fp16));
	}

	if (tensor_in_cnt == 0) {
		// copy overlap count from tail to head
		memmove(input, &input[tensor_require_cnt - overlap_cnt], overlap_cnt * sizeof(__fp16));
		tensor_in_cnt = overlap_cnt;
	}

	if (!src_temp) {
		src_temp = (short *)malloc(src_sample_cnt * sizeof(short));
		if (!src_temp) {
			printf("yamnet : out of resource\n\r");
		}
	}

	int proc_size = (tensor_require_cnt - tensor_in_cnt) > src_sample_cnt ? src_sample_cnt : (tensor_require_cnt - tensor_in_cnt);

	if (src_temp_cnt) {
		//printf("src temp cnt %d\n\r", src_temp_cnt);
		for (int i = 0; i < src_temp_cnt; i++) {
			input[tensor_in_cnt + i] = (__fp16)src_temp[i] / 32768.0;
		}
		tensor_in_cnt += src_temp_cnt;
		src_temp_cnt = 0;
	}

	for (int i = 0; i < proc_size; i++) {
		input[tensor_in_cnt + i] = (__fp16)src[i] / 32768.0;
	}

	tensor_in_cnt += proc_size;

	if (tensor_in_cnt == tensor_require_cnt) {
		src_temp_cnt = src_sample_cnt - proc_size;
		if (src_temp && src_temp_cnt > 0) {
			memcpy(src_temp, &src[proc_size], src_temp_cnt * sizeof(short));
		}

		// may have alignment issue
		dcache_clean_by_addr((uint32_t *)input, tensor_require_cnt * sizeof(__fp16));
		tensor_in_cnt = 0;
		return PP_USE_RESULT;	// DO inference
	}


	return PP_SKIP_INF;	// SKIP,
}

typedef struct data_format_s {
	nn_tensor_format_t *format;
	nn_tensor_dim_t *dim;
} data_format_t;

static int prob_comparator(const void *pa, const void *pb)
{
	yamnet_res_t *a = (yamnet_res_t *)pa;
	yamnet_res_t *b = (yamnet_res_t *)pb;
	float diff = a->prob - b->prob;
	if (diff < 0) {
		return 1;
	} else if (diff > 0) {
		return -1;
	}
	return 0;
}

#ifdef ARDUINO_SDK
int yamnet_postprocess(void *tensor_out, nn_tensor_param_t *param, void *res)
#else
static int yamnet_postprocess(void *tensor_out, nn_tensor_param_t *param, void *res)
#endif
{
	void **tensor = (void **)tensor_out;
	__fp16 *prob = (__fp16 *)tensor[0];
	int sort_cnt = 0;

	yamnet_res_t *audio_res = (yamnet_res_t *)res;

	data_format_t fmt;

	fmt.format = &param->format[0];
	fmt.dim = &param->dim[0];
	int class_cnt = fmt.dim->size[0];

	sort_cnt = 0;
	for (int i = 0; i < class_cnt; i++) {
		if ((float)prob[i] > 0.5) {
			audio_res[sort_cnt].prob = (float)prob[i];
			audio_res[sort_cnt].clsid = i;
			sort_cnt++;
		}
	}

	if (sort_cnt > 0) {
		qsort(audio_res, sort_cnt, sizeof(yamnet_res_t), prob_comparator);
	}
	return sort_cnt;
}


nnmodel_t yamnet = {
	.nb 			= yamnet_get_network_filename,
	.preprocess 	= yamnet_preprocess,
	.postprocess 	= yamnet_postprocess,
	.model_src 		= MODEL_SRC_FILE,

	.name = "YAMNET"
};
