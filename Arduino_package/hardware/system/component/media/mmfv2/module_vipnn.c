/******************************************************************************
*
* Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
*
******************************************************************************/
#include "platform_opts.h"
#include <stdint.h>
#include <stdlib.h>
#include "rtl8735b.h"
#include <hal_cache.h>
#include <hal_sys_ctrl.h>
#include "mmf2_module.h"
#include "osdep_service.h"
#include "module_vipnn.h"
#include "avcodec.h"
#include "device_lock.h"
#include "nn_file_op.h"

#include "nn_utils/tensor.h"
#include "nn_api.h"

// TODO move to vipnn context
#define DBG_LEVEL	LOG_MSG

#define LOG_OFF		4
#define LOG_ERR		3
#define LOG_MSG		2
#define LOG_INF		1
#define LOG_ALL		0
#define LOG_DBG		-1

#ifdef ARDUINO_SDK
int enable_log = 0;

void set_logging(int enable) 
{
    enable_log = enable;  // Change enable_log value at runtime
}
#endif

#ifdef ARDUINO_SDK
#define dprintf(level, ...) if (enable_log == 1 && (level >= DBG_LEVEL || (level == LOG_DBG && level == DBG_LEVEL))) do{printf(__VA_ARGS__);}while(0)
#else
#define dprintf(level, ...) if((level >= DBG_LEVEL) || (level==LOG_DBG && level==DBG_LEVEL)) do{printf(__VA_ARGS__);}while(0)
#endif

static int vipnn_inited = 0;
static int vipnn_module_cnt = 0;

#define TICK_INIT()
#define TICK_GET() (uint32_t)mm_read_mediatime_ms()

#define NN_MEASURE_INIT(n)	do{ctx->measure.tick[n] = 0; TICK_INIT();}while(0)
#define NN_MEASURE_START(n) do{ctx->measure.tick[n] = TICK_GET();}while(0)
#define NN_MEASURE_STOP(n)  do{ctx->measure.tick[n] = TICK_GET() - ctx->measure.tick[n];}while(0)
#if DBG_LEVEL <= LOG_MSG
#define NN_MEASURE_PRINT(n) do{printf("%s tick[%d] = %d\n\r", ctx->params.model->name, n, ctx->measure.tick[n]);}while(0)
#else
#define NN_MEASURE_PRINT(n) do{}while(0)
#endif

#define ONERROR(status, string, exit_anchor)    \
    do {                                        \
        if (status != VIP_SUCCESS) {            \
            printf("error: %s\n", string);      \
            goto exit_anchor;                   \
        }                                       \
    } while (0)

#define CHK(condition, exit_anchor) \
    do {                            \
        if (!(condition)) {         \
            goto exit_anchor;       \
        }                           \
    } while (0)

#define CHK_MSG(condition, exit_anchor, errorMessage, ...)  \
    do {                                                    \
        if (!(condition)) {                                 \
            printf(errorMessage, ##__VA_ARGS__);            \
            goto exit_anchor;                               \
        }                                                   \
    } while (0)

int vipnn_deoply_network(void *p);
void *vipnn_new_item(void *p);
void *vipnn_del_item(void *p, void *d);
int vipnn_create_buffer_from_input(void *p, void *input);
void *vipnn_allocate_videomemory(size_t size);
void vipnn_free_videomemory(void *ptr);

/*
void vipnn_mark(char *model_name, int num)
{
	mm_printf("vnn %s %d\n\r",model_name, num);
}
*/

//#define vipnn_mark() mm_printf("vnn %s %d\n\r",ctx->params.model->name, __LINE__);
#define vipnn_mark()

static int vipnn_handle(void *p, void *input, void *output)
{
	vipnn_ctx_t *ctx = (vipnn_ctx_t *)p;
	mm_queue_item_t *input_item = (mm_queue_item_t *)input;
	mm_queue_item_t *output_item = (mm_queue_item_t *)output;

	vip_status_e status = VIP_SUCCESS;
	int vip_input_created = 0;

	// check the model has been applied before inference
	CHK_MSG(ctx->status == VIPNN_APPLIED, clean_up, "error: vipnn not applied\r\n");

	int post_res_cnt = 0;
	void *out_tensor[6];

	dprintf(LOG_INF, "in %p out %p\n\r", input, output);
	dprintf(LOG_INF, "run %s model\n\r", ctx->params.model->name);

	if (ctx->measure.time0 == 0) {
		ctx->measure.time0 = (int)mm_read_mediatime_ms();
	}

	vipnn_mark();

	vipnn_out_buf_t *last_model_output = (vipnn_out_buf_t *)input_item->data_addr;
	void *input_data = (void *)input_item->data_addr;
	int input_size = input_item->size;
	nn_data_param_t *input_param = ctx->params.in_param;
	int loop_cnt = 1;

	// check model input type match to source type
	if (input_param != NULL) {
		CHK_MSG(input_param->codec_type == input_item->type, clean_up, "%s error: model input type[%d] not match to source type[%d]\n\r", ctx->params.model->name,
				input_param->codec_type, input_item->type);
	}
	if (ctx->cas_mode != 0) {
		dprintf(LOG_INF, "cascade mode\n\r");
		dprintf(LOG_INF, "cascade: input = %x\n\r", last_model_output);
		dprintf(LOG_INF, "cascade: obj = %d\n\r", last_model_output->res_cnt);
	}

	// cascade mode and last model object number = 0, stop inference
	if (ctx->cas_mode != 0) {
		CHK(last_model_output->res_cnt != 0, clean_up);
	}

	if (ctx->cas_mode == 2) {
		loop_cnt = last_model_output->res_cnt;
	}

	dprintf(LOG_INF, "loop cnt = %d\n\r", loop_cnt);

	if (loop_cnt > MAX_OUT_BUFFER_CNT) {
		loop_cnt = MAX_OUT_BUFFER_CNT;
		dprintf(LOG_INF, "set loop cnt to %d\n\r", MAX_OUT_BUFFER_CNT);
	}

	vipnn_out_buf_t *out = NULL;//(vipnn_out_buf_t *)(output_item->data_addr);

	if (output_item == NULL || output_item->data_addr == 0) {
		dprintf(LOG_INF, "[vipnn] use tmp buffer\n\r");
		out = ctx->tmp_item;
	} else {
		out = (vipnn_out_buf_t *)(output_item->data_addr);
	}

	out->res_cnt = 0;

	for (int i = 0; i < loop_cnt; i++) {
		// update input_param and input_data ==> input image and roi here

		nn_data_param_t cas_input_param;
		if (ctx->cas_mode != 0) {
			cas_input_param.codec_type = last_model_output->input_param->codec_type;
			cas_input_param.img.width = last_model_output->input_param->img.width;
			cas_input_param.img.height = last_model_output->input_param->img.height;
			cas_input_param.img.rgb = 0;

			if (ctx->params.model->cas_in_setup) {
				ctx->params.model->cas_in_setup(&last_model_output->res[0], i, &cas_input_param);
			} else {
				cas_input_param.img.roi.xmin = 0;
				cas_input_param.img.roi.ymin = 0;
				cas_input_param.img.roi.xmax = cas_input_param.img.width;
				cas_input_param.img.roi.ymax = cas_input_param.img.height;
			}

			input_data = last_model_output->input_data;
			input_param = &cas_input_param;
		} else {
			input_param->priv = (void *)input_data;
		}

		dprintf(LOG_INF, "input %x w %d h %d\n\r", input_data, input_param->img.width, input_param->img.height);

		int pre_ret = PP_USE_INPUT;
		if (ctx->params.model->preprocess) {
			if (ctx->params.in_param) {
				ctx->params.in_param->size_in_byte = input_size;
			}
			pre_ret = ctx->params.model->preprocess(input_data, input_param, (void *)ctx->pre_tensor, &ctx->params.model->input_param);
		}

		switch (pre_ret) {
		case PP_ERROR:
			CHK_MSG(false, clean_up, "%s pre-process fail\n\r", ctx->params.model->name);
			break;
		case PP_SKIP_INF:
			CHK(false, clean_up);
			break;
		case PP_USE_RESULT:
			for (int i = 0; i < ctx->input_count; i++) {
				device_mutex_lock(RT_DEV_LOCK_NN);
				status = vip_create_buffer_from_handle(&ctx->vip_param_in[i], (void *)ctx->pre_tensor[i], ctx->pre_tensor_size[i], &ctx->input_buffers[i]);
				device_mutex_unlock(RT_DEV_LOCK_NN);
				ONERROR(status, "error: vip_create_buffer_from_handle fail.", clean_up);
			}
			vip_input_created = 1;
			break;
		case PP_USE_INPUT:
			CHK_MSG(vipnn_create_buffer_from_input(ctx, input_item) == 0, clean_up, "error: vipnn_create_buffer_from_input fail\n\r");
			vip_input_created = 1;
			break;
		}

		// set input here, output has been set in vipnn_deoply_network()
		for (int i = 0; i < ctx->input_count; i++) {
			device_mutex_lock(RT_DEV_LOCK_NN);
			status = vip_set_input(ctx->network, i, ctx->input_buffers[i]);
			device_mutex_unlock(RT_DEV_LOCK_NN);
			ONERROR(status, "error: vip_set_input fail.", clean_up);
		}

		vipnn_mark();

		// run network
		device_mutex_lock(RT_DEV_LOCK_NN);
		status = vip_run_network(ctx->network);
		device_mutex_unlock(RT_DEV_LOCK_NN);
		ONERROR(status, "error: vip_run_network fail.", clean_up);

		// query inference time and cycle
		vip_inference_profile_t inf_info;
		device_mutex_lock(RT_DEV_LOCK_NN);
		vip_query_network(ctx->network, VIP_NETWORK_PROP_PROFILING, &inf_info);
		device_mutex_unlock(RT_DEV_LOCK_NN);
		dprintf(LOG_MSG, "%s tick[%ld]\n\r", ctx->params.model->name, inf_info.inference_time);
		dprintf(LOG_INF, "cycle[%ld]\n\r", inf_info.total_cycle);

		// always destroy vip input buffer after inference
		if (vip_input_created) {
			for (int i = 0; i < ctx->input_count; i++) {
				device_mutex_lock(RT_DEV_LOCK_NN);
				status = vip_destroy_buffer(ctx->input_buffers[i]);
				device_mutex_unlock(RT_DEV_LOCK_NN);
				ONERROR(status, "error: vip_destroy_buffer fail.", clean_up);
			}
			vip_input_created = 0;
		}

		vipnn_mark();
		for (int i = 0; i < ctx->output_count; i++) {
			device_mutex_lock(RT_DEV_LOCK_NN);
			status = vip_flush_buffer(ctx->output_buffers[i], VIP_BUFFER_OPER_TYPE_INVALIDATE);
			device_mutex_unlock(RT_DEV_LOCK_NN);
			ONERROR(status, "error: vip_flush_buffer fail.", clean_up);
		}

		vipnn_mark();
		// get output and do postprocessing
		for (int i = 0; i < ctx->output_count; i++) {
			device_mutex_lock(RT_DEV_LOCK_NN);
			out_tensor[i] = (void *)vip_map_buffer(ctx->output_buffers[i]);
			device_mutex_unlock(RT_DEV_LOCK_NN);
		}

		vipnn_mark();

		if (ctx->params.model->postprocess) {
			dprintf(LOG_INF, "out %p, res %p\n\r", out, &out->res[0]);

			// cascade mode: pass last model result to post-processing
			if (ctx->cas_mode != 0) {
				ctx->params.model->output_param.priv = (void *)(((uint8_t *)&last_model_output->res[0]) + i * last_model_output->res_size);
			} else {
				ctx->params.model->output_param.priv = NULL;
			}

			dprintf(LOG_INF, "out %p, res %p\n\r", &out->res[0], (void *)((uint8_t *)&out->res[0] + out->res_cnt * ctx->params.out_res_size));
			post_res_cnt = ctx->params.model->postprocess(out_tensor, &ctx->params.model->output_param,
						   (void *)((uint8_t *)&out->res[0] + out->res_cnt * ctx->params.out_res_size));

			out->res_cnt += post_res_cnt;
		}

		vipnn_mark();

		if (ctx->module_out_en) {
			out->input_data = input_data;
			if (ctx->cas_mode != 0) {
				out->input_param = last_model_output->input_param;
			} else {
				out->input_param = input_param;
			}
		}

		if (ctx->module_out_en && ctx->params.save_out_tensor) {
			out->tensors.vipnn_out_tensor_num = ctx->output_count;
			for (int i = 0; i < ctx->output_count; i++) {
				out->tensors.vipnn_out_tensor[i] = out_tensor[i];
				switch (ctx->vip_param_out[i].quant_format) {
				case VIP_BUFFER_QUANTIZE_DYNAMIC_FIXED_POINT:
					out->tensors.quant_format[i] = VIP_BUFFER_QUANTIZE_DYNAMIC_FIXED_POINT;
					out->tensors.quant_data[i].dfp.fixed_point_pos = ctx->vip_param_out[i].quant_data.dfp.fixed_point_pos;
					out->tensors.vipnn_out_tensor_size[i] = sizeof(int16_t);
					break;
				case VIP_BUFFER_QUANTIZE_TF_ASYMM:
					out->tensors.quant_format[i] = VIP_BUFFER_QUANTIZE_TF_ASYMM;
					out->tensors.quant_data[i].affine.scale = ctx->vip_param_out[i].quant_data.affine.scale;
					out->tensors.quant_data[i].affine.zeroPoint = ctx->vip_param_out[i].quant_data.affine.zeroPoint;
					out->tensors.vipnn_out_tensor_size[i] = sizeof(uint8_t);
					break;
				default:
					//printf(", none-quant\n\r");
					out->tensors.vipnn_out_tensor_size[i] = sizeof(__fp16);
				}
				for (int k = 0; k < ctx->params.model->output_param.dim[i].num; k++) {
					out->tensors.vipnn_out_tensor_size[i] = out->tensors.vipnn_out_tensor_size[i] * ctx->params.model->output_param.dim[i].size[k];
				}
			}
		}
	}

	vipnn_mark();

	if (ctx->disp_postproc) {
		ctx->disp_postproc(out, input_param);
	}

	vipnn_mark();

	ctx->measure.count++;
	if (ctx->measure.count % 16 == 0) {
		float nn_fps = (float)ctx->measure.count * 1000.0 / (float)(xTaskGetTickCount() - ctx->measure.time0);
		dprintf(LOG_MSG, ">>> %s FPS = %0.2f\n\r", ctx->params.model->name, nn_fps);
		dprintf(LOG_INF, ">>> %s count %d tick %d\n\r", ctx->params.model->name, nn_fps, ctx->measure.count, xTaskGetTickCount() - ctx->measure.time0);
	}
	vipnn_mark();

	/*------------------------------------------------------*/
	if (ctx->module_out_en && (out->res_cnt > 0 || ctx->params.save_out_tensor)) {
		output_item->size = sizeof(vipnn_out_buf_t) + ctx->params.out_res_size * ctx->params.out_res_max_cnt;
		//memcpy(output_item->data_addr, &tensor_out_next, output_item->size);
		output_item->timestamp = input_item->timestamp;
		output_item->type = AV_CODEC_ID_NN_RAW;
		memcpy(output_item->name, input_item->name, sizeof(output_item->name));

		return output_item->size;
	}

	vipnn_mark();

clean_up:
	if (vip_input_created) {
		for (int i = 0; i < ctx->input_count; i++) {
			device_mutex_lock(RT_DEV_LOCK_NN);
			status = vip_destroy_buffer(ctx->input_buffers[i]);
			device_mutex_unlock(RT_DEV_LOCK_NN);
			if (status != VIP_SUCCESS) {
				dprintf(LOG_ERR, "error: vip_destroy_buffer fail.\n\r");
			}
		}
	}

	return 0;
}

int vipnn_control(void *p, int cmd, int arg)
{
	int ret = 0;
	vipnn_ctx_t *ctx = (vipnn_ctx_t *)p;

	switch (cmd) {
	case CMD_VIPNN_SET_MODEL:
		ctx->params.model = (nnmodel_t *)arg;
		break;
	case CMD_VIPNN_SET_IN_PARAMS:
		ctx->params.in_param = (nn_data_param_t *)arg;
		if (!ctx->params.in_param->codec_type) {
			ctx->params.in_param->codec_type = AV_CODEC_ID_UNKNOWN;
		}
		break;
	case CMD_VIPNN_SET_DISPPOST:
		ctx->disp_postproc = (disp_postprcess_t)arg;
		break;
	case CMD_VIPNN_GET_STATUS:
		*(vipnn_status_t *)arg = ctx->status;
		break;
	case CMD_VIPNN_SET_CONFIDENCE_THRES:
		if (ctx->params.model->set_confidence_thresh) {
			ctx->params.model->set_confidence_thresh((void *)arg);
		}
		break;
	case CMD_VIPNN_SET_NMS_THRES:
		if (ctx->params.model->set_nms_thresh) {
			ctx->params.model->set_nms_thresh((void *)arg);
		}
		break;
	case CMD_VIPNN_SET_DESIRED_CLASS:
		if (ctx->params.model->set_desired_class) {
			ctx->params.model->set_desired_class((nn_desired_class_t *)arg);
		}
		break;
	case CMD_VIPNN_SET_OUTPUT:
		ctx->module_out_en = (bool)arg;
		((mm_context_t *)ctx->parent)->module->output_type = MM_TYPE_VSINK;
		break;
	case CMD_VIPNN_SET_OUTPUT_TYPE:
		ctx->module_out_type = (vipnn_out_type_t)arg;
		break;
	case CMD_VIPNN_SET_CASCADE:
		ctx->cas_mode = arg;
		break;
	case CMD_VIPNN_SET_RES_SIZE:
		ctx->params.out_res_size = arg;
		break;
	case CMD_VIPNN_SET_RES_MAX_CNT:
		ctx->params.out_res_max_cnt = arg;
		break;
	case CMD_VIPN_SET_SAVE_OUT_TENSOR:
		ctx->params.save_out_tensor = arg;
		break;
	case CMD_VIPNN_SET_USR_OUTPUT_BUF:
		ctx->params.usr_output = (usr_output_tensor_t *)arg;
		break;
	case CMD_VIPNN_APPLY:
		ctx->tmp_item = vipnn_new_item(ctx);
		if (!ctx->tmp_item) {
			dprintf(LOG_ERR, "%s out of resource %d\n\r", ctx->params.model->name, __LINE__);
			ret = -1;
			break;
		}
		dprintf(LOG_MSG, "Deploy %s\n\r", ctx->params.model->name);
		device_mutex_lock(RT_DEV_LOCK_NN);
		ret = vipnn_deoply_network(ctx);
		device_mutex_unlock(RT_DEV_LOCK_NN);
		if (ret == 0) {
			ctx->status = VIPNN_APPLIED;
		}
		break;
	}

	return ret;
}

int vipnn_create_buffer_from_input(void *p, void *input)
{
	vipnn_ctx_t *ctx = (vipnn_ctx_t *)p;
	mm_queue_item_t *input_item = (mm_queue_item_t *)input;
	void *input_data = (void *)input_item->data_addr;
	int input_size = input_item->size;

	vip_status_e status = VIP_SUCCESS;

	if (input_item->type == AV_CODEC_ID_RGB888 && ctx->params.model->input_param.count == 1) {
		device_mutex_lock(RT_DEV_LOCK_NN);
		status = vip_create_buffer_from_handle(&ctx->vip_param_in[0], input_data, input_size, &ctx->input_buffers[0]);
		device_mutex_unlock(RT_DEV_LOCK_NN);
		ONERROR(status, "error: vip_create_buffer_from_handle fail.", error);
	} else if (input_item->type == AV_CODEC_ID_NV12 && ctx->params.model->input_param.count == 2) {
		uint8_t *y_addr = (uint8_t *)input_data;
		uint32_t y_data_len = input_size * 2 / 3;
		device_mutex_lock(RT_DEV_LOCK_NN);
		status = vip_create_buffer_from_handle(&ctx->vip_param_in[0], (void *)y_addr, y_data_len, &ctx->input_buffers[0]);
		device_mutex_unlock(RT_DEV_LOCK_NN);
		ONERROR(status, "error: vip_create_buffer_from_handle fail.", error);
		device_mutex_lock(RT_DEV_LOCK_NN);
		status = vip_create_buffer_from_handle(&ctx->vip_param_in[1], (void *)(y_addr + y_data_len), input_size - y_data_len, &ctx->input_buffers[1]);
		device_mutex_unlock(RT_DEV_LOCK_NN);
		ONERROR(status, "error: vip_create_buffer_from_handle fail.", error);
	} else {
		for (int i = 0; i < ctx->input_count; i++) {
			device_mutex_lock(RT_DEV_LOCK_NN);
			status = vip_create_buffer_from_handle(&ctx->vip_param_in[i], input_data, input_size, &ctx->input_buffers[i]);
			device_mutex_unlock(RT_DEV_LOCK_NN);
			ONERROR(status, "error: vip_create_buffer_from_handle fail.", error);
		}
	}
	return 0;

error:
	return -1;
}

void vipnn_deinited(void *p)
{
	vipnn_ctx_t *ctx = (vipnn_ctx_t *)p;

	vip_finish_network(ctx->network);

	vip_destroy_network(ctx->network);

	// destroy vip output buffer here, vip intput buffer has been destroyed after inference
	for (int i = 0; i < ctx->output_count; i++) {
		vip_unmap_buffer(ctx->output_buffers[i]);
		vip_destroy_buffer(ctx->output_buffers[i]);
	}

	for (int i = 0; i < ctx->input_count; i++) {
		if (ctx->pre_tensor[i]) {
			vipnn_free_videomemory(ctx->pre_tensor[i]);
			ctx->pre_tensor[i] = NULL;
		}
	}

	if (ctx->params.model->release) {
		ctx->params.model->release();
	}

	if (ctx->params.model->model_content) {
		vipnn_free_videomemory(ctx->params.model->model_content);
		ctx->params.model->model_content = NULL;
	}

	ctx->status = VIPNN_DEINITED;
}

void *vipnn_destroy(void *p)
{
	vipnn_ctx_t *ctx = (vipnn_ctx_t *)p;

	if (ctx) {
		if (ctx->status != VIPNN_DEINITED) {
			device_mutex_lock(RT_DEV_LOCK_NN);
			vipnn_deinited(ctx);
			device_mutex_unlock(RT_DEV_LOCK_NN);
		}

		if (ctx->tmp_item) {
			vipnn_del_item(ctx, ctx->tmp_item);
		}

		free(ctx);

		vipnn_module_cnt--;
		if (vipnn_module_cnt == 0 && vipnn_inited == 1) {
			printf("vip_destroy done\r\n");
			vipnn_inited = 0;
		}
	}
	return NULL;
}

void vipnn_dump_network_io_params(void *p)
{
	vipnn_ctx_t *ctx = (vipnn_ctx_t *)p;

	printf("---------------------------------\n\r");
	printf("input count %d, output count %d\n\r", ctx->input_count, ctx->output_count);
	for (int i = 0; i < ctx->input_count; i++) {
		printf("input param %d\n\r", i);
		printf("\tdata_format  %x\n\r", ctx->vip_param_in[i].data_format);
		printf("\tmemory_type  %x\n\r", ctx->vip_param_in[i].memory_type);
		printf("\tnum_of_dims  %x\n\r", ctx->vip_param_in[i].num_of_dims);
		//printf("\tquant_data   %x\n\r", ctx->vip_param_in[i].quant_data);
		printf("\tquant_format %x\n\r", ctx->vip_param_in[i].quant_format);
		printf("\tquant_data  ");
		switch (ctx->vip_param_in[i].quant_format) {
		case VIP_BUFFER_QUANTIZE_DYNAMIC_FIXED_POINT:
			printf(", dfp=%d\n\r", ctx->vip_param_in[i].quant_data.dfp.fixed_point_pos);
			break;
		case VIP_BUFFER_QUANTIZE_TF_ASYMM:
			printf(", scale=%f, zero_point=%d\n\r", ctx->vip_param_in[i].quant_data.affine.scale,
				   ctx->vip_param_in[i].quant_data.affine.zeroPoint);
			break;
		default:
			printf(", none-quant\n\r");
		}
		//printf("\tsizes        %x\n\r", ctx->vip_param_in[i].sizes);
		printf("\tsizes        ");
		for (int x = 0; x < 6; x++) {
			printf("%ld ", ctx->vip_param_in[i].sizes[x]);
		}
		printf("\n\r");
	}
	for (int i = 0; i < ctx->output_count; i++) {
		printf("output param %d\n\r", i);
		printf("\tdata_format  %x\n\r", ctx->vip_param_out[i].data_format);
		printf("\tmemory_type  %x\n\r", ctx->vip_param_out[i].memory_type);
		printf("\tnum_of_dims  %x\n\r", ctx->vip_param_out[i].num_of_dims);
		//printf("\tquant_data   %x\n\r", ctx->vip_param_out[i].quant_data);
		printf("\tquant_format %x\n\r", ctx->vip_param_out[i].quant_format);
		printf("\tquant_data  ");
		switch (ctx->vip_param_out[i].quant_format) {
		case VIP_BUFFER_QUANTIZE_DYNAMIC_FIXED_POINT:
			printf(", dfp=%d\n\r", ctx->vip_param_out[i].quant_data.dfp.fixed_point_pos);
			break;
		case VIP_BUFFER_QUANTIZE_TF_ASYMM:
			printf(", scale=%f, zero_point=%d\n\r", ctx->vip_param_out[i].quant_data.affine.scale,
				   ctx->vip_param_out[i].quant_data.affine.zeroPoint);
			break;
		default:
			printf(", none-quant\n\r");
		}
		//printf("\tsizes        %x\n\r", ctx->vip_param_out[i].sizes);
		printf("\tsizes        ");
		for (int x = 0; x < 6; x++) {
			printf("%ld ", ctx->vip_param_out[i].sizes[x]);
		}
		printf("\n\r");
	}
	printf("---------------------------------\n\r");
}

static vip_int32_t init_io_buffers(void *p)
{
	vipnn_ctx_t *ctx = (vipnn_ctx_t *)p;
	vip_network network = ctx->network;
	vip_status_e status = VIP_SUCCESS;

	int i = 0;

	vip_query_network(network, VIP_NETWORK_PROP_INPUT_COUNT, &ctx->input_count);
	if (ctx->input_count > MAX_IO_NUM) {
		dprintf(LOG_ERR, "error, input count is more than max value=%d\n\r", MAX_IO_NUM);
		return -1;
	}

	vip_query_network(network, VIP_NETWORK_PROP_OUTPUT_COUNT, &ctx->output_count);
	if (ctx->output_count > MAX_IO_NUM) {
		dprintf(LOG_ERR, "error, output count is more than max value=%d\n\r", MAX_IO_NUM);
		return -1;
	}

	for (i = 0; i < ctx->input_count; i++) {
		vip_buffer_create_params_t *param = &ctx->vip_param_in[i];
		memset(param, 0, sizeof(vip_buffer_create_params_t));
		param->memory_type = VIP_BUFFER_MEMORY_TYPE_DEFAULT;
		vip_query_input(network, i, VIP_BUFFER_PROP_DATA_FORMAT, &param->data_format);
		vip_query_input(network, i, VIP_BUFFER_PROP_NUM_OF_DIMENSION, &param->num_of_dims);
		vip_query_input(network, i, VIP_BUFFER_PROP_SIZES_OF_DIMENSION, param->sizes);
		vip_query_input(network, i, VIP_BUFFER_PROP_QUANT_FORMAT, &param->quant_format);
		switch (param->quant_format) {
		case VIP_BUFFER_QUANTIZE_DYNAMIC_FIXED_POINT:
			vip_query_input(network, i, VIP_BUFFER_PROP_FIXED_POINT_POS,
							&param->quant_data.dfp.fixed_point_pos);
			break;
		case VIP_BUFFER_QUANTIZE_TF_ASYMM:
			vip_query_input(network, i, VIP_BUFFER_PROP_TF_SCALE,
							&param->quant_data.affine.scale);
			vip_query_input(network, i, VIP_BUFFER_PROP_TF_ZERO_POINT,
							&param->quant_data.affine.zeroPoint);
		default:
			break;
		}

		dprintf(LOG_MSG, "input %d dim %d %d %d %d, data format=%d, quant_format=%d",
				i, param->sizes[0], param->sizes[1], param->sizes[2], param->sizes[3], param->data_format,
				param->quant_format);

		switch (param->quant_format) {
		case VIP_BUFFER_QUANTIZE_DYNAMIC_FIXED_POINT:
			dprintf(LOG_MSG, ", dfp=%d\n\r", param->quant_data.dfp.fixed_point_pos);
			break;
		case VIP_BUFFER_QUANTIZE_TF_ASYMM:
			dprintf(LOG_MSG, ", scale=%f, zero_point=%d\n\r", param->quant_data.affine.scale,
					param->quant_data.affine.zeroPoint);
			break;
		default:
			dprintf(LOG_MSG, ", none-quant\n\r");
		}
		// vip input buffer will be created from RGB/NV12 data buffer directly before inference, so the data copy can be saved

		//dprintf(LOG_MSG, "input buffer %d = %p, vid memory %x \n\r", i, ctx->input_buffers[i], ctx->input_buffers[i]->memory.physical);
	}

	for (i = 0; i < ctx->output_count; i++) {
		vip_buffer_create_params_t *param = &ctx->vip_param_out[i];
		memset(param, 0, sizeof(vip_buffer_create_params_t));
		param->memory_type = VIP_BUFFER_MEMORY_TYPE_DEFAULT;
		vip_query_output(network, i, VIP_BUFFER_PROP_DATA_FORMAT, &param->data_format);
		vip_query_output(network, i, VIP_BUFFER_PROP_NUM_OF_DIMENSION, &param->num_of_dims);
		vip_query_output(network, i, VIP_BUFFER_PROP_SIZES_OF_DIMENSION, param->sizes);
		vip_query_output(network, i, VIP_BUFFER_PROP_QUANT_FORMAT, &param->quant_format);
		switch (param->quant_format) {
		case VIP_BUFFER_QUANTIZE_DYNAMIC_FIXED_POINT:
			vip_query_output(network, i, VIP_BUFFER_PROP_FIXED_POINT_POS,
							 &param->quant_data.dfp.fixed_point_pos);
			break;
		case VIP_BUFFER_QUANTIZE_TF_ASYMM:
			vip_query_output(network, i, VIP_BUFFER_PROP_TF_SCALE,
							 &param->quant_data.affine.scale);
			vip_query_output(network, i, VIP_BUFFER_PROP_TF_ZERO_POINT,
							 &param->quant_data.affine.zeroPoint);
			break;
		default:
			break;
		}
		dprintf(LOG_MSG, "ouput %d dim %d %d %d %d, data format=%d",
				i, param->sizes[0], param->sizes[1], param->sizes[2], param->sizes[3], param->data_format);

		switch (param->quant_format) {
		case VIP_BUFFER_QUANTIZE_DYNAMIC_FIXED_POINT:
			dprintf(LOG_MSG, ", dfp=%d\n\r", param->quant_data.dfp.fixed_point_pos);
			break;
		case VIP_BUFFER_QUANTIZE_TF_ASYMM:
			dprintf(LOG_MSG, ", scale=%f, zero_point=%d\n\r", param->quant_data.affine.scale,
					param->quant_data.affine.zeroPoint);
			break;
		default:
			dprintf(LOG_MSG, ", none-quant\n\r");
		}

		if (ctx->params.usr_output) {
			status = vip_create_buffer_from_handle(param, ctx->params.usr_output->pbuf[i], ctx->params.usr_output->size[i], &ctx->output_buffers[i]);
		} else {
			status = vip_create_buffer(param, sizeof(vip_buffer_create_params_t), &ctx->output_buffers[i]);
		}
		ONERROR(status, "error: vip create buffer fail.", error);
		//dprintf(LOG_MSG, "output buffer %d = %p, vid memory %x \n\r", i, ctx->output_buffers[i], ctx->output_buffers[i]->memory.physical);
	}

	vipnn_dump_network_io_params(ctx);
	return 0;

error:
	return -1;
}

#define VIPNN_MEMORY_ALIGN_SIZE 4096

void *vipnn_allocate_videomemory(size_t size)
{
	extern vip_status_e viphal_allocate_videomemory(vip_uint8_t **logical,
			vip_uint32_t *mem_id, vip_address_t *physical, vip_uint32_t size,
			vip_uint32_t align, vip_uint32_t alloc_flag);
	uint8_t *logical = VIP_NULL;
	vip_address_t physical = 0;
	vip_uint32_t mem_id;
	vip_status_e status = VIP_SUCCESS;
	status = viphal_allocate_videomemory(&logical, &mem_id, &physical,
										 size + VIPNN_MEMORY_ALIGN_SIZE, VIPNN_MEMORY_ALIGN_SIZE,
										 0x008 | 0x080);  //VIPDRV_VIDEO_MEM_ALLOC_CONTIGUOUS | VIPDRV_VIDEO_MEM_ALLOC_NO_MMU_PAGE
	ONERROR(status, "error: viphal_allocate_videomemory fail.", error);
	*(uint32_t *)logical = mem_id;
	return (void *)((uint8_t *)logical + VIPNN_MEMORY_ALIGN_SIZE);

error:
	return NULL;
}

void vipnn_free_videomemory(void *ptr)
{
	extern vip_status_e viphal_free_videomemory(vip_uint32_t mem_id);
	uint8_t *logical = (uint8_t *)ptr - VIPNN_MEMORY_ALIGN_SIZE;
	vip_uint32_t mem_id = *(uint32_t *)logical;
	vip_status_e status = VIP_SUCCESS;
	status = viphal_free_videomemory(mem_id);
	if (status != VIP_SUCCESS) {
		printf("error: gcvip_user_free_videomemory fail.\r\n");
	}
}

/* signed/encrypted model bin = | model bin | IV[16] | sha256 hash[32] | ed25519 signature[64] |
 * encrypted only model bin = | model bin | IV[16] | */
#include "hal_crypto.h"
#include "hal_eddsa.h"

int vipnn_hash_check(unsigned char *hash, unsigned char *model, uint32_t model_len)
{
	/* SHA256 HASH check */
	uint8_t sha256_hash[32];
	uint32_t sha_length_done = 0;
	device_mutex_lock(RT_DEV_LOCK_CRYPTO);
	hal_crypto_sha2_256_init();
	while ((model_len - sha_length_done) > CRYPTO_MAX_MSG_LENGTH) {
		hal_crypto_sha2_256_update(model + sha_length_done, CRYPTO_MAX_MSG_LENGTH);
		sha_length_done += CRYPTO_MAX_MSG_LENGTH;
	}
	hal_crypto_sha2_256_update(model + sha_length_done, model_len - sha_length_done);
	hal_crypto_sha2_256_final(sha256_hash);
	device_mutex_unlock(RT_DEV_LOCK_CRYPTO);
	CHK_MSG(memcmp(sha256_hash, hash, sizeof(sha256_hash)) == 0, error, "error: mdoel hash check fail.\r\n");
	printf("[NN hash] check pass\r\n");

	return 0;

error:
	return -1;
}

int vipnn_signature_check(unsigned char *signature, unsigned char *msg, unsigned char *pubkey, uint32_t msg_len)
{
	int ret = 0;
	/* EDDSA ED25519 signature check */
	device_mutex_lock(RT_DEV_LOCK_CRYPTO);
	ret = hal_eddsa_engine_init(EDDSA_HASH_CRYPTO_HW_SEL_EN);
	device_mutex_unlock(RT_DEV_LOCK_CRYPTO);
	CHK_MSG(ret == SUCCESS, error, "error: hal_eddsa_engine_init fail.\r\n");
	device_mutex_lock(RT_DEV_LOCK_CRYPTO);
	ret = hal_eddsa_sign_verify(signature, msg, pubkey, msg_len, EDDSA_FLOW_AUTOFLOW, ENABLE);
	device_mutex_unlock(RT_DEV_LOCK_CRYPTO);
	CHK_MSG(ret == SUCCESS, error, "error: hal_eddsa_sign_verify fail.\r\n");
	printf("[NN signature] check pass\r\n");
	return 0;

error:
	return -1;
}

/* Use FW private key to sign model by default, so we need FW public key to validate the signature */
int vipnn_get_fw_manifest_pubkey(unsigned char pubkey[32])
{
	void *partition_fp = NULL;
	const char *partition_name = NULL;
	int cur_fw_idx = hal_sys_get_ld_fw_idx();
	if (cur_fw_idx == 1) {
		partition_name = "FW1";
	} else if (cur_fw_idx == 2) {
		partition_name = "FW2";
	}
	CHK_MSG(partition_name != NULL, error, "error: current fw index is wrong\r\n");

	partition_fp = pfw_open(partition_name, M_RAW | M_RDONLY);
	CHK_MSG(partition_fp != NULL, error, "error: pfw_open fail.\r\n");
	pfw_seek(partition_fp, 0x124, SEEK_SET);  //seek to public key offset in fw manifest
	CHK_MSG(pfw_read(partition_fp, pubkey, 32) >= 0, error, "error: read public key fail.\r\n");
	pfw_close(partition_fp);
	return 0;

error:
	if (partition_fp) {
		pfw_close(partition_fp);
	}
	return -1;
}

#include "efuse_api.h"
/* Use OTP user key to encrypt model by default, so we need to load this key */
int vipnn_get_otp_seckey(unsigned char seckey[32])
{
	int ret = 0;
	/* read user OTP key from efuse */
	device_mutex_lock(RT_DEV_LOCK_EFUSE);
	ret = efuse_crypto_key_get(seckey, 0);
	device_mutex_unlock(RT_DEV_LOCK_EFUSE);
	CHK_MSG(ret == 0, error, "ERROR: efuse_crypto_key_get fail\r\n");
	return 0;

error:
	return -1;
}

typedef struct mdlsig_info_s {
	unsigned char sha256[32];
	unsigned char signature[64];
} mdlsig_info_t;

/* read model by nn file abstraction layer */
int vipnn_load_model(nnmodel_t *model, int *size)
{
	void *fd = nn_f_open(model->nb(), M_NORMAL);
	CHK_MSG(fd != NULL, error, "error: nn_f_open fail.\r\n");
	nn_f_seek(fd, 0, SEEK_END);
	int model_size = nn_f_tell(fd);
	CHK_MSG(model_size > 0, error, "error: wrong model size.\r\n");
	nn_f_seek(fd, 0, SEEK_SET);
	model->model_content = vipnn_allocate_videomemory(model_size);
	CHK_MSG(model->model_content != NULL, error, "error: vipnn_allocate_videomemory fail.\r\n");
	CHK_MSG(nn_f_read(fd, model->model_content, model_size) >= 0, error, "error: nn_f_read fail to read model.\r\n");
	nn_f_close(fd);
	dcache_clean_invalidate_by_addr((uint32_t *)model->model_content, model_size);

	/* check signature and hash of signed model */
#if CONFIG_NN_HASH_SIGNATURE_CHECK
	/* signature check */
	unsigned char pubkey[32];
	CHK_MSG(vipnn_get_fw_manifest_pubkey(pubkey) == 0, error, "error: vipnn_get_fw_manifest_pubkey fail.\r\n");
	mdlsig_info_t *signed_info = (mdlsig_info_t *)((uint8_t *)model->model_content + model_size - sizeof(mdlsig_info_t));
	CHK_MSG(vipnn_signature_check(signed_info->signature, signed_info->sha256, pubkey, sizeof(signed_info->sha256)) == 0, error,
			"error: vipnn_signature_check fail.\r\n");
	/* hash check */
	model_size -= sizeof(mdlsig_info_t);
	CHK_MSG(vipnn_hash_check(signed_info->sha256, model->model_content, model_size) == 0, error, "error: vipnn_hash_check fail.\r\n");
#endif

	/* decrypt model by key in OTP */
#if CONFIG_NN_AES_ENCRYPTION
	unsigned char aes_cbc_seckey[32];
	CHK_MSG(vipnn_get_otp_seckey(aes_cbc_seckey) == 0, error, "error: vipnn_get_otp_seckey fail\r\n");
	model_size -= 16;  /* minus iv length */
	uint8_t *iv = (uint8_t *)model->model_content + model_size;  /* iv appended after model */
	extern int nn_aes_key_injection(uint8_t *key, uint8_t *iv);
	CHK_MSG(nn_aes_key_injection(aes_cbc_seckey, iv) == 0, error, "error: nn_aes_key_injection fail\r\n");

	fd = nn_f_open(model->nb(), M_NORMAL);  /* if model encrypted and key injected, model will be decrypted while opening */
	CHK_MSG(fd != NULL, error, "error: nn_f_open fail.\r\n");
	nn_f_seek(fd, 0, SEEK_SET);
	const int enc_len = 512;
	CHK_MSG(nn_f_read(fd, model->model_content, enc_len) >= 0, error, "error: nn_f_read fail to read model.\r\n");
	nn_f_close(fd);  /* will reset injected key while closing */
	dcache_clean_invalidate_by_addr((uint32_t *)model->model_content, enc_len);
#endif

	*size = model_size;
	return 0;

error:
	if (fd) {
		nn_f_close(fd);
	}
	return -1;
}

int vipnn_deoply_network(void *p)
{
	vipnn_ctx_t *ctx = (vipnn_ctx_t *)p;
	vip_status_e status = VIP_SUCCESS;

	if (ctx->params.model->model_src == MODEL_SRC_MEM) {
		void *nn_model = ctx->params.model->nb();
		status = vip_create_network(nn_model, ctx->params.model->nb_size(), VIP_CREATE_NETWORK_FROM_MEMORY, &ctx->network);
		ctx->params.model->freemodel(nn_model);
	} else if (ctx->params.model->model_src == MODEL_SRC_FILE) {
		int nb_size = 0;
		CHK_MSG(vipnn_load_model(ctx->params.model, &nb_size) == 0, vipnn_deploy_error, "error: load model fail\r\n");
		status = vip_create_network(&ctx->params.model->model_content, nb_size, VIP_CREATE_NETWORK_FROM_FLASH, &ctx->network);
	} else {
		CHK_MSG(false, vipnn_deploy_error, "error: unsupported model source type\r\n");
	}
	ONERROR(status, "error: vip_create_network.", vipnn_deploy_error);

	dprintf(LOG_INF, "network %p\n\r", ctx->network);

	status = vip_query_network(ctx->network, VIP_NETWORK_PROP_NETWORK_NAME, ctx->network_name);
	ONERROR(status, "error: vip_query_network VIP_NETWORK_PROP_NETWORK_NAME.", vipnn_deploy_error);
	dprintf(LOG_INF, "network name:%s\n\r", ctx->network_name);

	if (init_io_buffers(ctx) < 0) {
		dprintf(LOG_ERR, "error: init_io_buffers.\n\r");
		goto vipnn_deploy_error;
	}

	status = vip_prepare_network(ctx->network);
	ONERROR(status, "error: vip_prepare_network.", vipnn_deploy_error);

	// output buffer can be set here because it may not be changed every inference
	// input buffer should be set before each inference because RGB/NV12 data address may be changed for each inference
	for (int i = 0; i < ctx->output_count; i++) {
		status = vip_set_output(ctx->network, i, ctx->output_buffers[i]);
		ONERROR(status, "error: vip_set_output.", vipnn_deploy_error);
	}

	// fill model info
	ctx->params.model->input_param.count = ctx->input_count;
	for (int i = 0; i < ctx->input_count; i++) {
		ctx->params.model->input_param.dim[i].num = ctx->vip_param_in[i].num_of_dims;
		memcpy(ctx->params.model->input_param.dim[i].size, ctx->vip_param_in[i].sizes, 6 * sizeof(uint32_t));
		ctx->params.model->input_param.format[i].buf_type = ctx->vip_param_in[i].data_format;
		ctx->params.model->input_param.format[i].type = ctx->vip_param_in[i].quant_format;
		switch (ctx->vip_param_in[i].quant_format) {
		case VIP_BUFFER_QUANTIZE_DYNAMIC_FIXED_POINT:
			ctx->params.model->input_param.format[i].fix_point_pos = ctx->vip_param_in[i].quant_data.dfp.fixed_point_pos;
			break;
		case VIP_BUFFER_QUANTIZE_TF_ASYMM:
			ctx->params.model->input_param.format[i].scale = ctx->vip_param_in[i].quant_data.affine.scale;
			ctx->params.model->input_param.format[i].zero_point = ctx->vip_param_in[i].quant_data.affine.zeroPoint;
			break;
		}
		dprintf(LOG_INF, "in %d, size %d %d\n\r", i, ctx->params.model->input_param.dim[i].size[0], ctx->params.model->input_param.dim[i].size[1]);
	}

	ctx->params.model->output_param.count = ctx->output_count;
	for (int i = 0; i < ctx->output_count; i++) {
		ctx->params.model->output_param.dim[i].num = ctx->vip_param_out[i].num_of_dims;
		memcpy(ctx->params.model->output_param.dim[i].size, ctx->vip_param_out[i].sizes, 6 * sizeof(uint32_t));
		ctx->params.model->output_param.format[i].buf_type = ctx->vip_param_out[i].data_format;
		ctx->params.model->output_param.format[i].type = ctx->vip_param_out[i].quant_format;
		switch (ctx->vip_param_out[i].quant_format) {
		case VIP_BUFFER_QUANTIZE_DYNAMIC_FIXED_POINT:
			ctx->params.model->output_param.format[i].fix_point_pos = ctx->vip_param_out[i].quant_data.dfp.fixed_point_pos;
			break;
		case VIP_BUFFER_QUANTIZE_TF_ASYMM:
			ctx->params.model->output_param.format[i].scale = ctx->vip_param_out[i].quant_data.affine.scale;
			ctx->params.model->output_param.format[i].zero_point = ctx->vip_param_out[i].quant_data.affine.zeroPoint;
			break;
		}
	}

	if (ctx->params.model->set_init_info) {
		ctx->params.model->set_init_info(ctx->params.model);
	}

	for (int i = 0; i < ctx->input_count; i++) {
		ctx->pre_tensor_size[i] = get_element_size(&ctx->params.model->input_param.format[i]);
		for (int k = 0; k < ctx->params.model->input_param.dim[i].num; k++) {
			ctx->pre_tensor_size[i] *= ctx->params.model->input_param.dim[i].size[k];
		}
		ctx->pre_tensor[i] = vipnn_allocate_videomemory(ctx->pre_tensor_size[i]);
		CHK_MSG(ctx->pre_tensor[i] != NULL, vipnn_deploy_error, "error: vipnn_allocate_videomemory fail\r\n");
	}

	return 0;
vipnn_deploy_error:
	vipnn_deinited(ctx);
	return -1;
}

void vipnn_hardware_init(void)
{
	hal_sys_peripheral_en(NN_SYS, ENABLE);
	hal_sys_set_clk(NN_SYS, NN_500M);
	//hal_sys_set_clk(NN_SYS, NN_250M);
	dprintf(LOG_INF, "hal_rtl_sys_get_clk %x \n", hal_sys_get_clk(NN_SYS));
}

void *vipnn_create(void *parent)
{
	vipnn_ctx_t *ctx = (vipnn_ctx_t *)malloc(sizeof(vipnn_ctx_t));
	memset(ctx, 0, sizeof(vipnn_ctx_t));

	ctx->parent = parent;

	vip_status_e status = VIP_SUCCESS;

	if (vipnn_inited == 0) {
		vipnn_hardware_init();

		device_mutex_lock(RT_DEV_LOCK_NN);
		status = vip_init();
		device_mutex_unlock(RT_DEV_LOCK_NN);
		ONERROR(status, "VIP Init failed.", vipnn_error);

		vipnn_inited = 1;
	}

	device_mutex_lock(RT_DEV_LOCK_NN);
	uint32_t nnlib_ver = vip_get_version();
	device_mutex_unlock(RT_DEV_LOCK_NN);
	dprintf(LOG_MSG, "VIPLite Drv version %ld.%ld.%ld\n\r", (nnlib_ver >> 16) & 0xff, (nnlib_ver >> 8) & 0xff, nnlib_ver & 0xff);

	ctx->params.fps = 1;
	ctx->params.out_res_max_cnt = 16;
	ctx->params.out_res_size = 128;

	ctx->status = VIPNN_INITED;
	ctx->tmp_item = NULL;

	vipnn_module_cnt++;

	return ctx;

vipnn_error:

	return NULL;
}

void *vipnn_new_item(void *p)
{
	vipnn_ctx_t *ctx = (vipnn_ctx_t *)p;
	// out buffer structure + result array
	//dprintf(LOG_INF, "new item res size %d cnt %d\n\r", ctx->params.out_res_size, ctx->params.out_res_max_cnt);
	vipnn_out_buf_t *tmp = (vipnn_out_buf_t *)malloc(sizeof(vipnn_out_buf_t) + ctx->params.out_res_size * ctx->params.out_res_max_cnt);
	if (tmp) {
		tmp->res_size = ctx->params.out_res_size;
		tmp->res_max_cnt = ctx->params.out_res_max_cnt;
	}
	return (void *)tmp;
}

void *vipnn_del_item(void *p, void *d)
{
	(void)p;
	if (d) {
		free(d);
	}
	return NULL;
}


mm_module_t vipnn_module = {
	.create = vipnn_create,
	.destroy = vipnn_destroy,
	.control = vipnn_control,
	.handle = vipnn_handle,

	.new_item = vipnn_new_item,
	.del_item = vipnn_del_item,

	.output_type = MM_TYPE_NONE,
	.module_type = MM_TYPE_VDSP,
	.name = "vip nn"
};