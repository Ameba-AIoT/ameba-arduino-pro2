/******************************************************************************
*
* Copyright(c) 2007 - 2023 Realtek Corporation. All rights reserved.
*
******************************************************************************/

#include <stdint.h>
#include <stdlib.h>
#include "module_eip.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "hal_video.h"//draw rect
#include "avcodec.h"
#include "img_process/img_process.h"

static eip_config_t eip_default_config = {
	.en_ae_stable = 1,
	.en_md = 0,
	.en_auto_wdr = 0,
};

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

eip_auto_wdr_config_t eip_auto_wdr_default_config = {
	.wdr_weight_thr1 = 240,
	.wdr_weight_thr2 = 160,
	.wdr_weight_thr3 = 60,
	.wdr_max_level = 70,
	.wdr_min_level = 50,
	.wdr_duration = 3000,
};

static int eip_handle_stop(eip_ctx_t *ctx)
{
	if (ctx->eip_status != EIP_STATUS_STOP) {
		ctx->eip_status = EIP_SET_STOP;
		int stop_count = 0;
		while (ctx->eip_status != EIP_STATUS_STOP) {
			vTaskDelay(1);
			stop_count++;
			if (stop_count > 1000) {
				printf("[EIP] handle stop timeout.\r\n");
				return 0;
			}
		}
	}
	//printf("[EIP] handle stop.\r\n");
	return 1;
}

static int eip_handle(void *p, void *input, void *output)
{
	eip_ctx_t *ctx = (eip_ctx_t *)p;
	mm_queue_item_t *input_item = (mm_queue_item_t *)input;
	mm_queue_item_t *output_item = (mm_queue_item_t *)output;
	int i, j, k, l;

	switch (ctx->eip_status) {
	case EIP_SET_STOP:
		ctx->eip_status = EIP_STATUS_STOP;
		return 0;
	case EIP_STATUS_STOP:
		return 0;
	}

	//check if AE stable
	if (ctx->eip_config.en_ae_stable) {
		if (!ctx->ae_stable.stable) {
			ctx->ae_stable.stable = eip_check_ae_stable(&ctx->ae_stable);
			if (!ctx->ae_stable.stable) {
				printf("[EIP] AE not stable\n\r");
				return 0;
			}
		}
	}

	eip_gen_Y_data(&ctx->params, (unsigned char *)input_item->data_addr, input_item->type, &ctx->Y_data);
	eip_gen_statistic_data(&ctx->params, (eip_Y_data_t *)&ctx->Y_data, &ctx->eip_statis_info);

	if (ctx->eip_config.en_md) {
		if (ctx->motion_detect_ctx->count % 128 == 0) {
			float md_fps = (float)128 * 1000.0 / (float)(input_item->timestamp - ctx->md_time0);
			ctx->md_time0 = input_item->timestamp;
			printf("[MD] FPS = %0.2f\n\r", md_fps);
		}
		if (ctx->motion_detect_ctx->count == 0) {
			md_initial(ctx->motion_detect_ctx, (md_param_t *) &ctx->params, &(ctx->md_config));
			md_initial_bgmodel(ctx->motion_detect_ctx, (md_param_t *)&ctx->params, &ctx->Y_data);
			md_show_config(ctx->motion_detect_ctx, (md_param_t *)&ctx->params, &ctx->md_config);
		}
		if (ctx->motion_detect_ctx->count % ctx->md_config.detect_interval == 0) {
			//unsigned long tick1 = mm_read_mediatime_ms();
			motion_detect(ctx->motion_detect_ctx, (md_param_t *)&ctx->params, &ctx->md_config, &ctx->Y_data, &ctx->md_result);
			//printf("\r\nmotion_detect after %dms.\n", (mm_read_mediatime_ms() - tick1));
			if (ctx->motion_detect_ctx->count >= ctx->md_config.detect_interval * 1024) { //Need to be a multiple of 128
				ctx->motion_detect_ctx->count = ctx->md_config.detect_interval;
			}
			if (ctx->md_disp_postproc) {
				ctx->md_disp_postproc(&ctx->md_result);
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
	}

	return 0;
}

static int eip_control(void *p, int cmd, int arg)
{
	int ret = 0;
	eip_ctx_t *ctx = (eip_ctx_t *)p;

	switch (cmd) {
	case CMD_EIP_SET_PARAMS:
		//Stop eip handle before change params.
		if (ctx->eip_status != EIP_STATUS_STOP) {
			printf("[EIP] cannot change params when running\r\n");
			return -1;
		}
		memcpy(&(ctx->params), (void *)arg, sizeof(eip_param_t));
		if (ctx->eip_config.en_md) {
			ctx->motion_detect_ctx->count = 0;
		}
		break;
	case CMD_EIP_SET_CONFIG:
		memcpy(&(ctx->eip_config), (void *)arg, sizeof(eip_config_t));
		if (ctx->eip_config.en_md) {
			ctx->motion_detect_ctx->count = 0;
		} else {
			if (eip_handle_stop(ctx)) {
				md_deinitial(ctx->motion_detect_ctx);
				ctx->eip_status = EIP_STATUS_START;
			} else {
				printf("[MD] deinit failed\r\n");
				return -1;
			}
		}
		break;
	case CMD_EIP_GET_CONFIG:
		memcpy((void *)arg, &(ctx->eip_config), sizeof(eip_config_t));
		break;
	case CMD_EIP_AE_STABLE_EN:
		ctx->eip_config.en_ae_stable = arg;
		if (ctx->eip_config.en_ae_stable) {
			ctx->ae_stable.stable = 0;
			ctx->ae_stable.last_ae_etgain = 0;
			ctx->ae_stable.timestamp = 0;
		}
		break;
	case CMD_EIP_SET_MD_EN:
		ctx->eip_config.en_md = arg;
		if (ctx->eip_config.en_md) {
			ctx->motion_detect_ctx->count = 0;
		} else {
			if (eip_handle_stop(ctx)) {
				md_deinitial(ctx->motion_detect_ctx);
				ctx->eip_status = EIP_STATUS_START;
			} else {
				printf("[MD] deinit failed\r\n");
				return -1;
			}
		}
		break;
	case CMD_EIP_SET_MD_CONFIG:
		if (((md_config_t *)arg)->his_resolution != ctx->md_config.his_resolution) {
			//Stop md handle before change his resolution.
			if (ctx->eip_status != EIP_STATUS_STOP) {
				printf("[MD] cannot change his resolution when running\r\n");
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
	case CMD_EIP_GET_MD_CONFIG:
		memcpy((void *)arg, &(ctx->md_config), sizeof(md_config_t));
		break;
	case CMD_EIP_SET_MD_MASK:
		memcpy(ctx->md_config.md_mask, (char *)arg, sizeof(char) * MD_MASK_COL * MD_MASK_ROW);
		printf("[MD] Set MD Mask: \r\n");
		for (int j = 0; j < MD_MASK_ROW; j++) {
			for (int k = 0; k < MD_MASK_COL; k++) {
				printf("%d ", ctx->md_config.md_mask[j * MD_MASK_COL + k]);
			}
			printf("\r\n");
		}
		printf("\r\n");
		break;
	case CMD_EIP_GET_MD_MASK:
		memcpy((void *)arg, ctx->md_config.md_mask, sizeof(char) * MD_MASK_COL * MD_MASK_ROW);
		break;
	case CMD_EIP_SET_MD_SENSITIVITY:
		if (arg >= 0 && arg <= 100) {
			ctx->md_config.md_obj_sensitivity = arg;
		} else {
			printf("[MD] md sensitivity set out of range (0-100).\r\n");
		}
		break;
	case CMD_EIP_GET_MD_SENSITIVITY:
		*(int *)arg = ctx->md_config.md_obj_sensitivity;
		break;
	case CMD_EIP_GET_MD_RESULT:
		memcpy((void *)arg, &ctx->md_result, sizeof(ctx->md_result));
		break;
	case CMD_EIP_SET_MD_DISPPOST:
		ctx->md_disp_postproc = (md_disp_postprcess)arg;
		break;
	case CMD_EIP_SET_MD_OUTPUT:
		ctx->md_out_en = (bool)arg;
		if (ctx->md_out_en) {
			((mm_context_t *)ctx->parent)->module->output_type = MM_TYPE_VSINK;
		} else {
			((mm_context_t *)ctx->parent)->module->output_type = MM_TYPE_NONE;
		}
		break;
	case CMD_EIP_GET_STATIS_INFO:
		memcpy((void *)arg, &ctx->eip_statis_info, sizeof(ctx->eip_statis_info));
		printf("[EIP] avgY = %d\r\n[EIP]", ctx->eip_statis_info.avg_YRGB[IDX_Y]);
		for (int i = 0; i < HISTOGRAM_COUNT; i++) {
			printf("%d, ", ctx->eip_statis_info.histogram[i]);
		}
		printf("\r\n");
		break;
	case CMD_EIP_SET_AUTO_WDR_EN:
		ctx->eip_config.en_auto_wdr = arg;
		if (ctx->eip_config.en_auto_wdr) {
			eip_auto_wdr_task_start(&(ctx->eip_statis_info), &(ctx->eip_auto_wdr));
		} else {
			eip_auto_wdr_task_stop(&(ctx->eip_auto_wdr));
		}
		break;
	case CMD_EIP_SET_AUTO_WDR_CONFIG:
		memcpy(&(ctx->eip_auto_wdr.wdr_config), (void *)arg, sizeof(eip_auto_wdr_config_t));
		break;
	case CMD_EIP_GET_AUTO_WDR_CONFIG:
		memcpy((void *)arg, &(ctx->eip_auto_wdr.wdr_config), sizeof(eip_auto_wdr_config_t));
		break;
	case CMD_EIP_SET_STATUS:
		if (arg == EIP_STATUS_STOP) {
			if (!eip_handle_stop(ctx)) {
				printf("[EIP] stop failed.\r\n");
				return -1;
			}
			ctx->motion_detect_ctx->count = 0;
			if (!ctx->eip_auto_wdr.task_stop_flag) {
				eip_auto_wdr_task_stop(&(ctx->eip_auto_wdr));
			}
		} else if (arg == EIP_STATUS_START) {
			ctx->eip_status = EIP_STATUS_START;
		}
		break;
	case CMD_EIP_SHOW_CONFIG:
		printf("[EIP] %dx%d -> %dx%d\r\n", ctx->params.image_width, ctx->params.image_height, ctx->params.eip_col, ctx->params.eip_row);
		if (ctx->eip_config.en_ae_stable) {
			printf("[EIP] ae stable %d\r\n", ctx->ae_stable.stable);
		}
		if (ctx->eip_config.en_md) {
			md_show_config(ctx->motion_detect_ctx, (md_param_t *)&ctx->params, &ctx->md_config);
		}
		if (ctx->eip_config.en_auto_wdr) {
			eip_auto_wdr_show_info(&(ctx->eip_auto_wdr));
		}
		break;
	}

	return ret;
}

static void *eip_destroy(void *p)
{
	eip_ctx_t *ctx = (eip_ctx_t *)p;

	if (ctx) {
		/*md destroy*/
		if (ctx->motion_detect_ctx) {
			md_deinitial(ctx->motion_detect_ctx);
			free(ctx->motion_detect_ctx);
			ctx->motion_detect_ctx = NULL;
		}

		if (!ctx->eip_auto_wdr.task_stop_flag) {
			eip_auto_wdr_task_stop(&(ctx->eip_auto_wdr));
		}

		free(ctx);
	}
	return NULL;
}

static void *eip_create(void *parent)
{
	eip_ctx_t *ctx = (eip_ctx_t *)malloc(sizeof(eip_ctx_t));
	if (!ctx) {
		printf("[Error] Allocate eip_ctx fail\n\r");
		goto eip_error;
	}
	memset(ctx, 0, sizeof(eip_ctx_t));

	memcpy(&ctx->eip_config, &eip_default_config, sizeof(eip_config_t));

	/*md create*/
	ctx->motion_detect_ctx = NULL;
	if (ctx->motion_detect_ctx == NULL) {
		ctx->motion_detect_ctx = (md_context_t *) malloc(sizeof(md_context_t));
	}
	if (ctx->motion_detect_ctx == NULL) {
		printf("[Error] Allocate motion_detect_ctx fail\n\r");
		goto eip_error;
	}
	memset(ctx->motion_detect_ctx, 0, sizeof(md_context_t));
	memcpy(&ctx->md_config, &md_default_config, sizeof(md_config_t));
	for (int i = 0; i < MD_MASK_COL * MD_MASK_ROW; i++) {
		ctx->md_config.md_mask[i] = 1;
	}
	for (int i = 0; i < MD_MAX_COL * MD_MAX_ROW; i++) {
		ctx->motion_detect_ctx->md_his_background[i] = NULL;
	}
	ctx->md_disp_postproc = NULL;

	memcpy(&(ctx->eip_auto_wdr.wdr_config), &eip_auto_wdr_default_config, sizeof(eip_auto_wdr_config_t));
	ctx->eip_auto_wdr.task_stop_sema = NULL;
	ctx->eip_auto_wdr.task_stop_flag = 1;
	ctx->eip_status = EIP_STATUS_STOP;

	ctx->parent = parent;

	return ctx;

eip_error:
	if (ctx) {
		free(ctx);
	}
	return NULL;
}

static void *eip_new_item(void *p)
{
	eip_ctx_t *ctx = (eip_ctx_t *)p;
	if (ctx) {
		return (void *)malloc(ctx->params.image_width * ctx->params.image_height * 3);
	}
	return NULL;
}

static void *eip_del_item(void *p, void *d)
{
	(void)p;
	if (d) {
		free(d);
	}
	return NULL;
}

mm_module_t eip_module = {
	.create = eip_create,
	.destroy = eip_destroy,
	.control = eip_control,
	.handle = eip_handle,

	.new_item = eip_new_item,
	.del_item = eip_del_item,

	.output_type = MM_TYPE_NONE,
	.module_type = MM_TYPE_VDSP,
	.name = "md"
};
