//------------------------------------------------------
// MobileNetV2
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
#include "nn_utils/quantize.h"
#include <arm_math.h>

//#define UNITTEST

#ifdef UNITTEST
#include "img_sample/rose.h"
static float golden_output[] = {-0.680908, -0.783936, -1.216309, 3.449463, -2.153320};
#endif

static void *mbnv2_get_network_filename(void)
{
	return (void *)"NN_MDL/mobilenetv2.nb";	// fix name for NN model binary
}

static void *mbnv2_get_network_filename_sdcard(void)
{
	//copy mobilenetv2.nb to NN_MDL/ folder in sdcard
	return (void *)"sd:/NN_MDL/mobilenetv2.nb";
}

/*
Pretrained MobileNetV2 model is trained on ImageNet dataset.
Preprocess of ImageNet is complex and Acuity isn't able to support.
So we need to do it manually.
*/
static float mean[3] = {0.485, 0.456, 0.406};
static float std[3] = {0.229, 0.224, 0.225};
static float *img_resized = NULL;
static void normalize_imagenet(float *img_normalized, uint8_t *img, uint32_t width, uint32_t height, float *mean, float *std)
{
	if (img_normalized == NULL || img == NULL || mean == NULL || std == NULL || width == 0 || height == 0) {
		printf("invalid param\r\n");
		return;
	}

    uint32_t planar_size = width * height;
    uint8_t (*img_planar)[planar_size] = (uint8_t (*)[planar_size])img;
    float (*img_dst)[planar_size] = (float(*)[planar_size])img_normalized;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < planar_size; j++) {
            img_dst[i][j] = img_planar[i][j]; //uint8_t to float
        }
        arm_scale_f32(img_dst[i], (1/255.0), img_dst[i], planar_size);
        arm_offset_f32(img_dst[i], -mean[i], img_dst[i], planar_size);
        arm_scale_f32(img_dst[i], 1/std[i], img_dst[i], planar_size);
    }
}

#ifdef ARDUINO_SDK
int mbnv2_preprocess(void *data_in, nn_data_param_t *data_param, void *tensor_in, nn_tensor_param_t *tensor_param)
#else
static int mbnv2_preprocess(void *data_in, nn_data_param_t *data_param, void *tensor_in, nn_tensor_param_t *tensor_param)
#endif
{
	void **tensor = (void **)tensor_in;

	img_t img_in, img_out;

	img_in.width  = data_param->img.width;
	img_in.height = data_param->img.height;
	img_out.width  = tensor_param->dim[0].size[0];
	img_out.height = tensor_param->dim[0].size[1];
	int channel = tensor_param->dim[0].size[2];
	int dst_data_count = img_out.width*img_out.height*channel;

#ifdef UNITTEST
	//test with golden data (flower classification) 
	//mobilenetv2_int16.nb sha256: 898411e30095a71d9fccc8031c56a8e5157f629927da1e6aac124b7ec74292cb
	memcpy(tensor[0], rose, dst_data_count * sizeof(float));
	dcache_clean_by_addr((uint32_t *)tensor[0], dst_data_count * sizeof(float));
#else
	img_in.data = (uint8_t *)data_in;
	
	if (img_in.width == img_out.width && img_in.height == img_out.height) {
		img_out.data = (uint8_t *)tensor[0];
		normalize_imagenet((float*)img_out.data, img_in.data, img_in.width, img_in.height, mean, std);
		dcache_clean_by_addr((uint32_t *)img_out.data, dst_data_count * sizeof(float));
	} else {
		//resize src image to dst
		printf("resize image from %dx%d to %dx%d\r\n", img_in.width, img_in.height, img_out.width, img_out.height);
		if (img_resized == NULL) //only malloc once
			img_resized = malloc(dst_data_count * sizeof(uint8_t));
		
		if (img_resized == NULL) {
			printf("malloc fail\r\n");
			return PP_ERROR;
		}
		img_out.data = (uint8_t *)img_resized;
		img_scaled_into_letterbox(&img_in, &img_out);
		normalize_imagenet((float*)tensor[0], img_out.data, img_out.width, img_out.height, mean, std);
		dcache_clean_by_addr((uint32_t *)tensor[0], dst_data_count * sizeof(float));
	}
#endif

	return PP_USE_RESULT;
}

typedef struct data_format_s {
	nn_tensor_format_t *format;
	nn_tensor_dim_t *dim;
} data_format_t;

static int argmax(float *data, int size)
{
    float max = data[0];
    int index = 0;
    for (int i = 1; i < size; i++) {
        if (data[i] > max) {
            max = data[i];
            index = i;
        }
    }
    return index;
}

static void softmax(float *data, float *outout, uint32_t n)
{
    float sum = 0;
    for (int i = 0; i < n; i++) {
        outout[i] = exp(data[i]);
        sum += outout[i];
    }
    for (int i = 0; i < n; i++) {
        outout[i] /= sum;
    }
}

#ifdef ARDUINO_SDK
int mbnv2_postprocess(void *tensor_out, nn_tensor_param_t *param, void *res)
#else
static int mbnv2_postprocess(void *tensor_out, nn_tensor_param_t *param, void *res)
#endif
{
	void **tensor = (void **)tensor_out;
	classification_res_t *class_res = (classification_res_t *)res;
	data_format_t output_fmt;
	output_fmt.format = &param->format[0];
	output_fmt.dim = &param->dim[0];
	int class_num = output_fmt.dim->size[0];
	float *output_f = malloc(class_num * sizeof(float));
	float *output_softmax = malloc(class_num * sizeof(float));
	int item_size = 1; //UNIT8 or INT8
	if (output_fmt.format->buf_type == VIP_BUFFER_FORMAT_FP16 || 
	    output_fmt.format->buf_type == VIP_BUFFER_FORMAT_INT16) {
		item_size = 2;
	}
	uint8_t *output_q = (uint8_t *)tensor[0];
	for (int i = 0; i < class_num; i++) {
		output_f[i] = q2f((output_q + i*item_size), output_fmt.format);
		//printf("%f ", (float) output_f[i]);
	}
	//printf("\r\n");

#ifdef UNITTEST
	for (int i = 0; i < class_num; i++) {
		if (fabs(output_f[i] - golden_output[i]) > 0.1) {
			printf("golden output mismatch!!\r\n");
			return 0;
		}
	}
	printf("[golden output match]\r\n");
#endif

	int index = argmax(output_f, class_num);
	class_res->clsid = index;
	softmax(output_f, output_softmax, class_num);
	/*for (int i = 0; i < class_num; i++) {
		printf("%f ", (float) output_softmax[i]);
	}
	printf("\r\n\r\n");*/
	class_res->prob = output_softmax[index];
	free(output_f);
	free(output_softmax);

	//for classification, always return 1
	return 1;
}


nnmodel_t mobilenetv2 = {
	.nb 			= mbnv2_get_network_filename,
	.preprocess 	= mbnv2_preprocess,
	.postprocess 	= mbnv2_postprocess,
	.model_src 		= MODEL_SRC_FILE,

	.name = "MobileNetV2"
};

nnmodel_t mobilenetv2_sdcard = {
	.nb 			= mbnv2_get_network_filename_sdcard,
	.preprocess 	= mbnv2_preprocess,
	.postprocess 	= mbnv2_postprocess,
	.model_src 		= MODEL_SRC_FILE,

	.name = "MobileNetV2"
};
