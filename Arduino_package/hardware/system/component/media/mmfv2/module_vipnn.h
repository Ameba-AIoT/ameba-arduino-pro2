#ifndef _MODULE_RTKNN_H
#define _MODULE_RTKNN_H

#include <stdint.h>
#include <vip_lite.h>
#include "img_process/img_process.h"

#define CMD_VIPNN_SET_MODEL             MM_MODULE_CMD(0x00)  // set model
#define CMD_VIPNN_SET_IN_PARAMS    	    MM_MODULE_CMD(0x01)  // set input imaage parameter

#define CMD_VIPNN_SET_DISPPOST          MM_MODULE_CMD(0x03)  // set display callback
#define CMD_VIPNN_GET_STATUS            MM_MODULE_CMD(0x04)  // get vipnn module status

#define CMD_VIPNN_SET_CONFIDENCE_THRES  MM_MODULE_CMD(0x06)  // set confidence threshold for object detection 
#define CMD_VIPNN_SET_NMS_THRES         MM_MODULE_CMD(0x07)  // set NMS threshold for object detection 

#define CMD_VIPNN_SET_OUTPUT     	    MM_MODULE_CMD(0x15)  // enable module output
#define CMD_VIPNN_SET_CASCADE     	    MM_MODULE_CMD(0x16)  // enable cascaded mode

#define CMD_VIPNN_APPLY				    MM_MODULE_CMD(0x20)  // for hardware module

#define VIPNN_MODEL_FILE 0
#define VIPNN_MODEL_MEM  1

#define MAX_OUT_BUFFER_CNT 16

typedef struct landmark_s {
	struct __post_s {
		float x, y;
	} pos[5];
} landmark_t;
//----------------------------------------------------------------------------
typedef struct landmarki_s {
	struct __posi_s {
		uint32_t x, y;
	} pos[5];
} landmarki_t;
//----------------------------------------------------------------------------
typedef struct detobj_s {
	float class;
	float score;
	float top_x, top_y;
	float bot_x, bot_y;
} detobj_t;

typedef struct detobji_s {
	uint32_t class;
	uint32_t score;
	uint32_t top_x, top_y;
	uint32_t bot_x, bot_y;
} detobji_t;

//----------------------------------------------------------------------------
typedef struct nn_tensor_format_s {
	int type;
	int buf_type;
	float scale;
	int zero_point;		//asymmatric	uint8
	int fix_point_pos;	//symmatric		int16
} nn_tensor_format_t;

typedef struct nn_tensor_dim_s {
	int num;
	uint32_t size[6];
} nn_tensor_dim_t;

typedef struct nn_tensor_param_s {
	int count;

	nn_tensor_format_t format[16];
	nn_tensor_dim_t dim[16];
} nn_tensor_param_t;

typedef struct nn_data_param_s {
	union {
		struct nn_img_params_s {
			// img width height order
			int width, height, rgb;
			// roi
			rect_t roi;
			landmarki_t landmark;
		} img;
		struct nn_aud_params_s {
			int num_of_samples;
			int bit_pre_sample;
			int sample_rate;
			int channel;
		} aud;
	};
	// DONT use this
	void *priv;
	// DONT use this
	int size_in_byte;
} nn_data_param_t;

typedef void (*disp_postprcess_t)(void *, void *);
typedef int (*nn_preprocess_t)(void *data_in, nn_data_param_t *data_param, void *tensor_in, nn_tensor_param_t *tensor_param);
typedef void *(*nn_postprocess_t)(void *tensor_out, nn_tensor_param_t *param);
typedef void *(*nn_get_nb_t)(void);
typedef int (*nn_get_nb_size_t)(void);
typedef void (*nn_free_model_t)(void *);
typedef void (*nn_set_confidence_thresh_t)(void *confidence_thresh);
typedef void (*nn_set_nms_thresh_t)(void *nms_thresh);

#define MODEL_SRC_MEM	0
#define MODEL_SRC_FILE	1
typedef struct nnmodel_s {
	// user implement
	//void *network_binary;
	nn_get_nb_t 		nb;
	nn_get_nb_size_t 	nb_size;
	nn_preprocess_t 	preprocess;
	nn_postprocess_t 	postprocess;
	nn_free_model_t		freemodel;
	int					model_src;

	// setup by nn modoule
	nn_tensor_param_t input_param;
	nn_tensor_param_t output_param;

	// setup thresh in post-processing
	nn_set_confidence_thresh_t set_confidence_thresh;
	nn_set_nms_thresh_t set_nms_thresh;

	const char *name;
} nnmodel_t;
//------------------------------------------------------------------------------

typedef struct vipnn_measure_s {
	int32_t tick[8];
	// for FPS
	int time0;
	int count;
} vipnn_measure_t;

typedef struct vipnn_param_s {
	int model_type;
	char model_file[64];
	uint8_t *model_mem;
	uint32_t model_size;

	int fps;

	int in_width, in_height;
	rect_t roi;

	int m_width, m_height;		// should read from model, not user setting

	nn_data_param_t *in_param;
	nnmodel_t *model;
} vipnn_params_t;

typedef enum {
	VIPNN_INITED = 0,
	VIPNN_APPLIED = 1,
	VIPNN_DEINITED = 2
} vipnn_status_t;


typedef enum {
	VIPNN_CMODE_NONE = 0,		// not cascaded model
	VIPNN_CMODE_ONE_ROI = 1,	// cascaded model, only processing first roi
	VIPNN_CMODE_ALL_ROI = 2		// cascaded model, processing all roi
} vipnn_cascaded_mode_t;

typedef int (*vipnn_preproc_t)(void *, void *, void *, void *, uint32_t);
typedef int (*vipnn_postproc_t)(void *, void *, void *);

#define MAX_IO_NUM              20

typedef struct vipnn_ctx_s {
	void *parent;

	vip_network network;
	vip_buffer_create_params_t vip_param_in[MAX_IO_NUM];
	vip_buffer_create_params_t vip_param_out[MAX_IO_NUM];

	vip_buffer input_buffers[MAX_IO_NUM];
	vip_buffer output_buffers[MAX_IO_NUM];

	vipnn_params_t params;

	vipnn_status_t status;

	char network_name[64];

	int input_count;
	int output_count;

	vipnn_preproc_t pre_process;
	vipnn_postproc_t post_process;


	disp_postprcess_t disp_postproc;

	vipnn_cascaded_mode_t cas_mode;
	bool module_out_en;

	vipnn_measure_t measure;
} vipnn_ctx_t;

#define MAX_DETECT_OBJ_NUM 1024
typedef struct objdetect_res_s {
	int obj_num;
	union {
		float result[MAX_DETECT_OBJ_NUM * 6];
		detobj_t res[MAX_DETECT_OBJ_NUM];
	};
} objdetect_res_t;

typedef struct facedetect_res_s {
	int obj_num;
	union {
		float result[MAX_DETECT_OBJ_NUM * 6];
		detobj_t res[MAX_DETECT_OBJ_NUM];
	};
	landmark_t landmark[MAX_DETECT_OBJ_NUM];
} facedetect_res_t;


#define MAX_FACE_DETECT_NUM 16
#define MAX_FACE_FEATURE_DIM 128
typedef struct face_feature_res_s {
	float result[MAX_FACE_FEATURE_DIM];
} face_feature_res_t;

#define RES_TYPE_OD	0
#define RES_TYPE_FD	1
#define RES_TYPE_FR	2
typedef struct vipnn_res_s {
	union {
		objdetect_res_t od_res;      	// for object detection
		facedetect_res_t fd_res;		//
		face_feature_res_t frec_res;   	// for face recognition
	};
	int type;
} vipnn_res_t;

typedef struct vipnn_out_buf_s {
	uint32_t    vipnn_out_tensor_num;
	void        *vipnn_out_tensor[6];
	uint32_t    vipnn_out_tensor_size[6];
	vipnn_res_t vipnn_res;

	// backup origin input
	void 				*input_data;
	nn_data_param_t		input_param;

	// backup input tensor
	//uint32_t    vipnn_in_tensor_num;
	//void			*in_tensor;
	//nn_tensor_dim_t in_tensor_dim;

	uint32_t    quant_format[6];
	union {
		struct {
			vip_int32_t fixed_point_pos;
		} dfp;
		struct {
			vip_float_t        scale;
			vip_int32_t        zeroPoint;
		} affine;
	}
	quant_data[6];
} vipnn_out_buf_t;

extern mm_module_t vipnn_module;

#endif
