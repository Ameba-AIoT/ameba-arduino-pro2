/******************************************************************************
*
* Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
*
******************************************************************************/

#include <stdint.h>
#include <stdlib.h>
#include "module_md.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "hal_video.h"//draw rect
#include "avcodec.h"
#include "img_process/img_process.h"

static md_config_t md_default_config = {
	.adapt_mode = 0, //default close adapt mode
	.adapt_level = 1.1,
	.adapt_step = 30,
	.adapt_thr_max = 10,
	.bg_mode = 0, //normal background update
	.detect_interval = 1, //detect every frame
	.his_resolution = 5,
	.his_threshold = 50,
	.his_step = 200,
	.md_obj_sensitivity = 90,
	.md_time_filter_interval = 3, //filter fast motion that cannot be tract in 3 frames
	.md_trigger_block_threshold = 0, //default trigger if any motion detct
	.block_base_thr = 1,
	.block_lum_thr = 3,
};

static int md_handle_stop(md_ctx_t *ctx)
{
	if (ctx->md_status != MD_STATUS_STOP) {
		ctx->md_status = MD_SET_STOP;
		int md_stop_count = 0;
		while (ctx->md_status != MD_STATUS_STOP) {
			vTaskDelay(1);
			md_stop_count++;
			if (md_stop_count > 1000) {
				printf("[MD] handle stop timeout.\r\n");
				return 0;
			}
		}
	}
	printf("[MD] handle stop.\r\n");
	return 1;
}

static int md_handle(void *p, void *input, void *output)
{
	md_ctx_t *ctx = (md_ctx_t *)p;
	mm_queue_item_t *input_item = (mm_queue_item_t *)input;
	mm_queue_item_t *output_item = (mm_queue_item_t *)output;
	int i, j, k, l;

	switch (ctx->md_status) {
	case MD_SET_STOP:
		ctx->md_status = MD_STATUS_STOP;
		return 0;
	case MD_STATUS_STOP:
		return 0;
	}

	//printf("width = %d,height = %d\n",ctx->params->image_width, ctx->params->image_height);
	//printf("image size = %d\n",input_item->size);

	//check if AE stable
	if (ctx->en_ae_stable) {
		if (!ctx->ae_stable.stable) {
			ctx->ae_stable.stable = eip_check_ae_stable(&ctx->ae_stable);
			if (!ctx->ae_stable.stable) {
				printf("[MD] AE not stable\n\r");
				return 0;
			}
		}
	}

	if (ctx->motion_detect_ctx->count % ctx->md_config.detect_interval == 0) {
		//unsigned long tick1 = mm_read_mediatime_ms();
		eip_gen_Y_data((eip_param_t *)&ctx->params, (unsigned char *)input_item->data_addr, input_item->type, &ctx->Y_data);
		eip_gen_statistic_data((eip_param_t *)&ctx->params, &ctx->Y_data, &statis_info);
		//printf("\r\neip_gen_statistic_data after %dms.\n", (mm_read_mediatime_ms() - tick1));
	}
	if (ctx->motion_detect_ctx->count % 128 == 0) {
		float md_fps = (float)128 * 1000.0 / (float)(input_item->timestamp - ctx->md_time0);
		ctx->md_time0 = input_item->timestamp;
		printf("[MD] FPS = %0.2f\n\r", md_fps);
	}
	if (ctx->motion_detect_ctx->count == 0) {
		md_initial(ctx->motion_detect_ctx, &ctx->params, &ctx->md_config);
		md_initial_bgmodel(ctx->motion_detect_ctx, &ctx->params, &ctx->Y_data);
		md_show_config(ctx->motion_detect_ctx, &ctx->params, &ctx->md_config);
	}
	if (ctx->motion_detect_ctx->count % ctx->md_config.detect_interval == 0) {
		//unsigned long tick1 = mm_read_mediatime_ms();
		motion_detect(ctx->motion_detect_ctx, &ctx->params, &ctx->md_config, &ctx->Y_data, &ctx->md_result);
		//printf("\r\nmotion_detect after %dms.\n", (mm_read_mediatime_ms() - tick1));
		if (ctx->motion_detect_ctx->count >= ctx->md_config.detect_interval * 1024) { //Need to be a multiple of 128
			ctx->motion_detect_ctx->count = ctx->md_config.detect_interval;
		}
		if (ctx->disp_postproc) {
			ctx->disp_postproc(&ctx->md_result);
		}
	}
	ctx->motion_detect_ctx->count ++;

	if (ctx->md_out_en) {
		int motion = ctx->motion_detect_ctx->md_trigger_block;
		if (motion > ctx->md_config.md_trigger_block_threshold) {
			//printf("Motion Detected!\r\n");
			output_item->timestamp = input_item->timestamp;
			output_item->size = input_item->size;
			output_item->type = input_item->type;
			img_dma_copy((unsigned char *)output_item->data_addr, (unsigned char *) input_item->data_addr, input_item->size);
			return output_item->size;
		}
	}
	return 0;
}

static int md_control(void *p, int cmd, int arg)
{
	int ret = 0;
	md_ctx_t *ctx = (md_ctx_t *)p;

	switch (cmd) {
	case CMD_MD_SET_PARAMS:
		if (((md_param_t *)arg)->md_row != ctx->params.md_row && ((md_param_t *)arg)->md_col != ctx->params.md_col) {
			//Stop eip handle before change params.
			if (ctx->md_status != MD_STATUS_STOP) {
				printf("[MD] cannot change params when running\r\n");
				return -1;
			}
			//please check md mask settings
			memcpy(&(ctx->params), (void *)arg, sizeof(md_param_t));
			ctx->motion_detect_ctx->count = 0;
		} else {
			memcpy(&(ctx->params), (void *)arg, sizeof(eip_param_t));
		}
		break;
	case CMD_MD_SET_MD_CONFIG:
		if (((md_config_t *)arg)->his_resolution != ctx->md_config.his_resolution) {
			//Stop md handle before change his resolution.
			if (ctx->md_status != MD_STATUS_STOP) {
				printf("[MD] cannot change md config when running\r\n");
				return -1;
			}
			if (((md_config_t *)arg)->his_resolution > 2 && ((md_config_t *)arg)->his_resolution <= 6) {
				memcpy(&ctx->md_config, (md_config_t *)arg, sizeof(md_config_t));
				ctx->motion_detect_ctx->count = 0;
			} else {
				printf("[MD] invalid his resolution.\r\n");
				return -1;
			}
		} else {
			memcpy(&ctx->md_config, (md_config_t *)arg, sizeof(md_config_t));
		}
		break;
	case CMD_MD_GET_MD_CONFIG:
		memcpy((void *)arg, &ctx->md_config, sizeof(md_config_t));
		break;
	case CMD_MD_SET_MD_MASK:
		memcpy(ctx->md_config.md_mask, (char *)arg, sizeof(char) * MD_MASK_ROW * MD_MASK_COL);
		printf("[MD] Set MD Mask: \r\n");
		for (int j = 0; j < MD_MASK_ROW; j++) {
			for (int k = 0; k < MD_MASK_COL; k++) {
				printf("%d ", ctx->md_config.md_mask[j * MD_MASK_COL + k]);
			}
			printf("\r\n");
		}
		printf("\r\n");
		break;
	case CMD_MD_GET_MD_MASK:
		memcpy((void *)arg, ctx->md_config.md_mask, sizeof(char) * MD_MASK_ROW * MD_MASK_COL);
		break;
	case CMD_MD_GET_MD_RESULT:
		memcpy((void *)arg, &ctx->md_result, sizeof(ctx->md_result));
		break;
	case CMD_MD_SET_OUTPUT:
		ctx->md_out_en = (bool)arg;
		((mm_context_t *)ctx->parent)->module->output_type = MM_TYPE_VSINK;
		break;
	case CMD_MD_SET_DISPPOST:
		ctx->disp_postproc = (md_disp_postprcess)arg;
		break;
	case CMD_MD_SET_TRIG_BLK:
		ctx->md_config.md_trigger_block_threshold = arg;
		break;
	case CMD_MD_EN_AE_STABLE:
		ctx->en_ae_stable = arg;
		if (ctx->en_ae_stable) {
			ctx->ae_stable.stable = 0;
			ctx->ae_stable.last_ae_etgain = 0;
			ctx->ae_stable.timestamp = 0;
		}
		break;
	case CMD_MD_SET_DETECT_INTERVAL:
		ctx->md_config.detect_interval = arg;
		break;
	case CMD_MD_SET_ADAPT_THR_MODE:
		ctx->md_config.adapt_mode = arg;
		break;
	case CMD_MD_SET_BGMODE:
		if (arg >= 0 && arg <= 1) {
			ctx->md_config.bg_mode = arg;
		} else {
			printf("[MD] md bgmode set out of range (0-1).\r\n");
		}
		break;
	case CMD_MD_SET_TIME_FILTER_INTERVAL:
		if (ctx->md_config.md_time_filter_interval > 0 && ctx->md_config.md_time_filter_interval < MD_MAX_TIME_FILTER_INTERVAL) {
			ctx->md_config.md_time_filter_interval = arg;
			memset(ctx->motion_detect_ctx->_objs, 0, sizeof(ctx->motion_detect_ctx->_objs));
		}
		break;
	case CMD_MD_SET_MD_SENSITIVITY:
		if (arg >= 0 && arg <= 100) {
			ctx->md_config.md_obj_sensitivity = arg;
		} else {
			printf("[MD] md sensitivity set out of range (0-100).\r\n");
		}
		break;
	case CMD_MD_GET_MD_SENSITIVITY:
		*(int *)arg = ctx->md_config.md_obj_sensitivity;
		break;
	case CMD_MD_SET_STATUS:
		if (arg == MD_STATUS_STOP) {
			md_handle_stop(ctx);
			ctx->motion_detect_ctx->count = 0;
		} else if (arg == MD_STATUS_START) {
			ctx->md_status = MD_STATUS_START;
		}
		break;
	case CMD_MD_SHOW_CONFIG:
		printf("[MD] %dx%d -> %dx%d\r\n", ctx->params.image_width, ctx->params.image_height, ctx->params.md_col, ctx->params.md_row);
		md_show_config(ctx->motion_detect_ctx, &ctx->params, &ctx->md_config);
		break;
	}

	return ret;
}

static void *md_destroy(void *p)
{
	md_ctx_t *ctx = (md_ctx_t *)p;

	if (ctx) {
		if (ctx->motion_detect_ctx) {
			md_deinitial(ctx->motion_detect_ctx);
			free(ctx->motion_detect_ctx);
		}
		free(ctx);
	}
	return NULL;
}

static void *md_create(void *parent)
{
	md_ctx_t *ctx = (md_ctx_t *)malloc(sizeof(md_ctx_t));
	if (!ctx) {
		printf("[Error] Allocate md_ctx fail\n\r");
		goto md_error;
	}
	memset(ctx, 0, sizeof(md_ctx_t));

	ctx->en_ae_stable = 1;

	ctx->motion_detect_ctx = NULL;
	ctx->motion_detect_ctx = (md_context_t *) malloc(sizeof(md_context_t));
	if (ctx->motion_detect_ctx == NULL) {
		printf("[Error] Allocate motion_detect_ctx fail\n\r");
		goto md_error;
	}
	memset(ctx->motion_detect_ctx, 0, sizeof(md_context_t));

	memcpy(&ctx->md_config, &md_default_config, sizeof(md_config_t));

	for (int i = 0; i < MD_MAX_COL * MD_MAX_ROW; i++) {
		ctx->motion_detect_ctx->md_his_background[i] = NULL;
	}
	for (int i = 0; i < MD_MASK_ROW * MD_MASK_COL; i++) {
		ctx->md_config.md_mask[i] = 1;
	}
	ctx->disp_postproc = NULL;
	ctx->md_status = MD_STATUS_STOP;

	ctx->parent = parent;

	return ctx;

md_error:
	if (ctx) {
		free(ctx);
	}

	return NULL;
}

static void *md_new_item(void *p)
{
	md_ctx_t *ctx = (md_ctx_t *)p;

	return (void *)malloc(ctx->params.image_width * ctx->params.image_height * 3);
}

static void *md_del_item(void *p, void *d)
{
	(void)p;
	if (d) {
		free(d);
	}
	return NULL;
}
eip_statis_infor_t statis_info;
mm_module_t md_module = {
	.create = md_create,
	.destroy = md_destroy,
	.control = md_control,
	.handle = md_handle,

	.new_item = md_new_item,
	.del_item = md_del_item,

	.output_type = MM_TYPE_NONE,
	.module_type = MM_TYPE_VDSP,
	.name = "md"
};
