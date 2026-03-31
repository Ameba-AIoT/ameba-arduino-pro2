/******************************************************************************
*
* Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
*
******************************************************************************/

#include <stdint.h>
#include <math.h>
#include "platform_stdlib.h"
#include "osdep_service.h"
#include "avcodec.h"
#include "mmf2_module.h"
#include "module_array.h"
#include "opus.h"

//------------------------------------------------------------------------------
void frame_timer_handler(uint32_t hid);
//int video_timer_delay_ms = 0;

#ifndef CONFIG_PLATFORM_8735B
#define TIMER_FUNCTION
#endif

float dB_aPOW[64];

static void array_timer_thread(void *param)
{
	array_ctx_t *ctx = (array_ctx_t *)param;
	while (1) {
		if (ctx->video_timer_delay_ms) {
			vTaskDelay(ctx->video_timer_delay_ms);
			frame_timer_handler((uint32_t)ctx);
		} else {
			printf("[ARRAY ERR] Invalid ctx->video_timer_delay_ms = %d\r\n", ctx->video_timer_delay_ms);
			break;
		}
	}
	ctx->task = NULL;
	vTaskDelete(NULL);
}

void timer_task_enable(void *parm)
{
	array_ctx_t *ctx = (array_ctx_t *)parm;
	if (ctx->task_priority == 0) {
		ctx->task_priority = tskIDLE_PRIORITY + 1;
	}
	if (xTaskCreate(array_timer_thread, ((const char *)"array_timer_thread"), 2048, ctx, ctx->task_priority, &ctx->task) != pdPASS) {
		printf("\n\r%s xTaskCreate failed", __FUNCTION__);
	}
}

uint32_t array_get_opus_frame_size(array_ctx_t *ctx, unsigned char *ptr_start, unsigned char *ptr_end)
{
	if (ptr_start >= ptr_end) {
		return 0;
	} else if ((ptr_end - ptr_start) < ctx->params.u.a.frame_size) {
		return (ptr_end - ptr_start);
	} else {
		return ctx->params.u.a.frame_size;
	}
}

uint32_t array_get_aac_frame_size(unsigned char *ptr_start, unsigned char *ptr_end)
{
	if (ptr_start >= ptr_end) {
		return 0;
	}
	unsigned char *ptr = ptr_start;
	while (ptr < ptr_end) {
		if (ptr[0] == 0xff && (ptr[1] >> 4) == 0x0f) {
			break;
		}
		ptr++;
	}
	if (ptr >= ptr_end)	{
		return (ptr_end - ptr_start);
	}
	unsigned char *temp = ptr + 3;
	u32 ausize = ((*temp & 0x03) << 11) | (*(temp + 1) << 3) | ((*(temp + 2) & 0xe0) >> 5);
	ptr += ausize;
	if (ptr >= ptr_end) {
		return (ptr_end - ptr_start);
	} else {
		while (ptr < ptr_end) {
			if (ptr[0] == 0xff && (ptr[1] >> 4) == 0x0f) {
				return (ptr - ptr_start);
			}
			ptr++;
		}
		return (ptr_end - ptr_start);
	}
}

uint32_t array_get_h264_frame_size(unsigned char *ptr_start, unsigned char *ptr_end, uint8_t nal_len)
{
	if (ptr_start >= ptr_end) {
		return 0;
	}

	int skip_flag = 1;
	unsigned char *ptr = ptr_start;
	while (ptr < ptr_end) {
		if (ptr[0] == 0 && ptr[1] == 0) {
			if ((nal_len == 4 && ptr[2] == 0 && ptr[3] == 1)
				|| (nal_len == 3 && ptr[2] == 1)) {
				if ((ptr[nal_len] & 0x1f) != 0x07 && (ptr[nal_len] & 0x1f) != 0x08) {	// not SPS or PPS
					if (skip_flag == 0) {
						return (ptr - ptr_start);
					} else {
						skip_flag = 0;
					}
				} else if ((ptr[nal_len] & 0x1f) == 0x08) {	// PPS, get next (one more) frame before return
					skip_flag = 1;
				}
			}
		}
		ptr++;
	}

	return (ptr_end - ptr_start);
}

uint32_t array_get_h265_frame_size(unsigned char *ptr_start, unsigned char *ptr_end, uint8_t nal_len)
{
	if (ptr_start >= ptr_end) {
		return 0;
	}

	int skip_flag = 1;
	unsigned char *ptr = ptr_start;
	while (ptr < ptr_end) {
		if (ptr[0] == 0 && ptr[1] == 0) {
			if ((nal_len == 4 && ptr[2] == 0 && ptr[3] == 1)
				|| (nal_len == 3 && ptr[2] == 1)) {

				if ((ptr[nal_len] & 0x7E >> 1) != 32 && (ptr[nal_len] & 0x7E >> 1) != 33) {
					if (skip_flag == 0) {
						return (ptr - ptr_start);
					} else {
						skip_flag = 0;
					}
				} else if ((ptr[nal_len] & 0x7E >> 1) == 34) {	// PPS, get next (one more) frame before return
					skip_flag = 1;
				}
			}
		}
		ptr++;
	}

	return (ptr_end - ptr_start);
}

void frame_timer_handler(uint32_t hid)
{
	array_ctx_t *ctx = (array_ctx_t *)hid;

	if (ctx->stop) {
		return;
	}
#ifdef TIMER_FUNCTION
	BaseType_t xTaskWokenByReceive = pdFALSE;
	BaseType_t xHigherPriorityTaskWoken;
#endif
#ifdef TIMER_FUNCTION
	uint32_t timestamp = mm_read_mediatime_ms_fromisr();
#else
	uint32_t timestamp = mm_read_mediatime_ms();
#endif

	mm_context_t *mctx = (mm_context_t *)ctx->parent;
	mm_queue_item_t *output_item;

	if (ctx->array.data_offset >= ctx->array.data_len) {
		if (ctx->params.mode == ARRAY_MODE_ONCE) {
			ctx->stop = 1;
			ctx->array.data_offset = 0;
#ifdef TIMER_FUNCTION
			gtimer_stop(&ctx->frame_timer);
#endif
			return;
		} else {
			if (ctx->array_sweepdb_en) {
				if (ctx->dB_Sweep == 0) {
					ctx->array_sweep_flag = 1;
				} else if (ctx->dB_Sweep == 57) {
					ctx->array_sweep_flag = 0;
				}
				if (ctx->array_sweep_flag) {
					ctx->dB_Sweep += 3;
				} else {
					ctx->dB_Sweep -= 3;
				}
			}
			//printf("dB_sweep = %d\r\n", ctx->dB_Sweep);
			ctx->array.data_offset = 0;
		}
	}
#ifdef TIMER_FUNCTION
	int is_output_ready = xQueueReceiveFromISR(mctx->output_recycle, &output_item, &xTaskWokenByReceive) == pdTRUE;
#else
	int is_output_ready = xQueueReceive(mctx->output_recycle, &output_item, 1000) == pdTRUE;
#endif
	if (is_output_ready) {
		int remain_len = ctx->array.data_len - ctx->array.data_offset;

		output_item->type = ctx->params.codec_id;
		output_item->timestamp = timestamp;
		output_item->data_addr = ctx->array.data_addr + ctx->array.data_offset;
		if (ctx->params.type == AVMEDIA_TYPE_AUDIO) {
			if (ctx->params.codec_id == AV_CODEC_ID_PCMU || ctx->params.codec_id == AV_CODEC_ID_PCMA || ctx->params.codec_id == AV_CODEC_ID_PCM_RAW) {
				output_item->size = (remain_len > ctx->params.u.a.frame_size) ? ctx->params.u.a.frame_size : remain_len;
				if (ctx->params.codec_id == AV_CODEC_ID_PCM_RAW && ctx->array_sweepdb_en && ctx->array_copy.data_addr) {
					memcpy((void *)(ctx->array_copy.data_addr + ctx->array.data_offset), (void *)(ctx->array.data_addr + ctx->array.data_offset), output_item->size);
					output_item->data_addr = ctx->array_copy.data_addr + ctx->array.data_offset;
					short *pcm_pro_buf = (short *)output_item->data_addr;
					for (int i = 0; i < output_item->size / 2; i++) {
						pcm_pro_buf[i] = (short)((float)pcm_pro_buf[i] * dB_aPOW[ctx->dB_Sweep]);
					}
				} else {
					output_item->data_addr = ctx->array.data_addr + ctx->array.data_offset;
				}
			} else if (ctx->params.codec_id == AV_CODEC_ID_MP4A_LATM) {
				output_item->size = array_get_aac_frame_size((unsigned char *)(ctx->array.data_addr + ctx->array.data_offset),
									(unsigned char *)(ctx->array.data_addr + ctx->array.data_len));
			} else if (ctx->params.codec_id == AV_CODEC_ID_OPUS) {
				output_item->size = array_get_opus_frame_size(ctx, (unsigned char *)(ctx->array.data_addr + ctx->array.data_offset),
									(unsigned char *)(ctx->array.data_addr + ctx->array.data_len));
				int numofsamples = opus_packet_get_nb_samples((const unsigned char *)output_item->data_addr, output_item->size, ctx->params.u.a.samplerate);
				ctx->video_timer_delay_ms = numofsamples / (ctx->params.u.a.samplerate / 1000);
				if (!(ctx->video_timer_delay_ms % 5 == 0 && ctx->video_timer_delay_ms > 0 && ctx->video_timer_delay_ms <= 120)) {
					ctx->video_timer_delay_ms = 20;
				}
			} else {
				mm_printf("TODO: unhandled codec_id:%d\n\r", ctx->params.codec_id);
				return;
			}
		} else if (ctx->params.type == AVMEDIA_TYPE_VIDEO) {
			if (ctx->params.codec_id == AV_CODEC_ID_H264) {
				output_item->size = array_get_h264_frame_size((unsigned char *)(ctx->array.data_addr + ctx->array.data_offset),
									(unsigned char *)(ctx->array.data_addr + ctx->array.data_len), ctx->params.u.v.h264_nal_size);
				//mm_printf("h264 output\r\n");
			} else if (ctx->params.codec_id == AV_CODEC_ID_H265) {
				output_item->size = array_get_h265_frame_size((unsigned char *)(ctx->array.data_addr + ctx->array.data_offset),
									(unsigned char *)(ctx->array.data_addr + ctx->array.data_len), ctx->params.u.v.h264_nal_size);
			} else if (ctx->params.codec_id == AV_CODEC_ID_RGB888) {
				output_item->size = ctx->array.data_len;
			} else {
				mm_printf("TODO: unhandled codec_id:%d\n\r", ctx->params.codec_id);
				return;
			}
		}
#ifdef TIMER_FUNCTION
		xQueueSendFromISR(mctx->output_ready, (void *)&output_item, &xHigherPriorityTaskWoken);
#else
		xQueueSend(mctx->output_ready, (void *)&output_item, 0);
#endif
		ctx->array.data_offset += output_item->size;
	}
#ifdef TIMER_FUNCTION
	if (xHigherPriorityTaskWoken || xTaskWokenByReceive) {
		taskYIELD();
	}
#endif
}

int array_control(void *p, int cmd, int arg)
{
	array_ctx_t *ctx = (array_ctx_t *)p;

	switch (cmd) {
	case CMD_ARRAY_SET_PARAMS:
		memcpy(&ctx->params, (void *)arg, sizeof(array_params_t));
		break;
	case CMD_ARRAY_GET_PARAMS:
		memcpy((void *)arg, &ctx->params, sizeof(array_params_t));
		break;
	case CMD_ARRAY_SET_ARRAY:
		memcpy(&ctx->array, (void *)arg, sizeof(array_t));
		if (ctx->array_copy.data_addr) {
			free((void *)ctx->array_copy.data_addr);
			ctx->array_copy.data_addr = 0;
		}
		ctx->array_copy.data_addr = (uint32_t)malloc(ctx->array.data_len);
		ctx->array_copy.data_len = ctx->array.data_len;
		break;
	case CMD_ARRAY_SET_MODE:
		ctx->params.mode = (uint8_t)arg;
		break;
	case CMD_ARRAY_SET_TASK_TASKPRIORITY:
#ifdef TIMER_FUNCTION
		printf("The array use timer irq function\r\n");
#else
		if (arg > 0) {
			ctx->task_priority = arg;
		}
		if (ctx->task_priority > 5) {
			printf("Warnin, the array task priority set %d > 5\r\n", ctx->task_priority);
		}
		if (ctx->task) {
			printf("array task exist reset the array task priority to %d\r\n", ctx->task_priority);
			vTaskPrioritySet(ctx->task, ctx->task_priority);
		}
#endif
		break;
	case CMD_ARRAY_RECOUNT_PERIOD:
		if (ctx->params.type == AVMEDIA_TYPE_VIDEO) {
			ctx->frame_timer_period = 1000000 / ctx->params.u.v.fps;
		} else if (ctx->params.type == AVMEDIA_TYPE_AUDIO) {
			if (ctx->params.codec_id == AV_CODEC_ID_PCMU || ctx->params.codec_id == AV_CODEC_ID_PCMA) {
				ctx->frame_timer_period = (int)(1000000 / ((float)ctx->params.u.a.samplerate / ctx->params.u.a.frame_size));
			} else if (ctx->params.codec_id == AV_CODEC_ID_PCM_RAW) {
				ctx->frame_timer_period = (int)(1000000 / ((float)ctx->params.u.a.samplerate * 2 / ctx->params.u.a.frame_size));
			} else if (ctx->params.codec_id == AV_CODEC_ID_MP4A_LATM) {
				ctx->frame_timer_period = (int)(1000000 / ((float)ctx->params.u.a.samplerate / 1024));
			}
		} else {
			return -1;
		}

		if (ctx->frame_timer_period == 0 && ctx->params.codec_id != AV_CODEC_ID_OPUS) {
			printf("Error, frame_timer_period can't be 0\n\r");
			return -1;
		}
		printf("Recount frame_timer_period success\n\r");
		if (ctx->params.codec_id == AV_CODEC_ID_OPUS) {
			ctx->video_timer_delay_ms = 20;
		} else {
			ctx->video_timer_delay_ms = ctx->frame_timer_period / 1000;
		}
		break;
	case CMD_ARRAY_APPLY:
		for (int i = 0; i < 64; i++) {
			dB_aPOW[i] = pow(10.0f, (float)((float)(-i) / 20.0f));
		}
		if (ctx->params.type == AVMEDIA_TYPE_VIDEO) {
			ctx->frame_timer_period = 1000000 / ctx->params.u.v.fps;
		} else if (ctx->params.type == AVMEDIA_TYPE_AUDIO) {
			if (ctx->params.codec_id == AV_CODEC_ID_PCMU || ctx->params.codec_id == AV_CODEC_ID_PCMA) {
				ctx->frame_timer_period = (int)(1000000 / ((float)ctx->params.u.a.samplerate / ctx->params.u.a.frame_size));
			} else if (ctx->params.codec_id == AV_CODEC_ID_PCM_RAW) {
				ctx->frame_timer_period = (int)(1000000 / ((float)ctx->params.u.a.samplerate * 2 / ctx->params.u.a.frame_size));
			} else if (ctx->params.codec_id == AV_CODEC_ID_MP4A_LATM) {
				ctx->frame_timer_period = (int)(1000000 / ((float)ctx->params.u.a.samplerate / 1024));
			}
		} else {
			return -1;
		}

		if (ctx->frame_timer_period == 0 && ctx->params.codec_id != AV_CODEC_ID_OPUS) {
			printf("Error, frame_timer_period can't be 0\n\r");
			return -1;
		}
#ifdef TIMER_FUNCTION
		gtimer_init(&ctx->frame_timer, 0xff);
#else
		if (ctx->params.codec_id == AV_CODEC_ID_OPUS) {
			ctx->video_timer_delay_ms = 20;
		} else {
			ctx->video_timer_delay_ms = ctx->frame_timer_period / 1000;
		}
#endif

		break;
	case CMD_ARRAY_PCM_SWEEP:
		if (arg > 0) {
			ctx->dB_Sweep = 0;
			ctx->array_sweepdb_en = 1;
			ctx->array_sweep_flag = 1;
		} else {
			ctx->dB_Sweep = 0;
			ctx->array_sweepdb_en = 0;
		}
		break;
	case CMD_ARRAY_GET_STATE:
		*(int *)arg = ((ctx->stop) ? 0 : 1);
		break;
	case CMD_ARRAY_STREAMING:
		if (arg == 1) {	// stream on
			if (ctx->stop) {
				ctx->array.data_offset = 0;
				//printf("ctx->frame_timer_period =%d\n\r",ctx->frame_timer_period);
#ifdef TIMER_FUNCTION
				gtimer_start_periodical(&ctx->frame_timer, ctx->frame_timer_period, (void *)frame_timer_handler, (uint32_t)ctx);
#else
				if (ctx->task == NULL) {
					timer_task_enable(ctx);
				}
#endif
				ctx->stop = 0;
			}
		} else {			// stream off
			if (!ctx->stop) {
#ifdef TIMER_FUNCTION
				gtimer_stop(&ctx->frame_timer);
#endif
				ctx->stop = 1;
			}
		}
		break;
	}
	return 0;
}

int array_handle(void *ctx, void *input, void *output)
{
	return 0;
}

void *array_destroy(void *p)
{
	array_ctx_t *ctx = (array_ctx_t *)p;

	if (ctx) {
		if (ctx->stop == 0) {
			array_control((void *)ctx, CMD_ARRAY_STREAMING, 0);
		}

		if (ctx->up_sema) {
			rtw_free_sema(&ctx->up_sema);
		}
		if (ctx->task) {
			vTaskDelete(ctx->task);
			ctx->task = NULL;
		}

		if (ctx->array_copy.data_addr) {
			free((void *)(ctx->array_copy.data_addr));
		}

		free(ctx);
	}
	return NULL;
}

void *array_create(void *parent)
{
	array_ctx_t *ctx = malloc(sizeof(array_ctx_t));
	if (!ctx) {
		return NULL;
	}
	memset(ctx, 0, sizeof(array_ctx_t));

	ctx->parent = parent;

	ctx->stop = 1;
	rtw_init_sema(&ctx->up_sema, 0);

	return ctx;

//array_create_fail:
	//array_destroy((void*)ctx);
	//return NULL;
}

void *array_new_item(void *p)
{
	return NULL;
}

void *array_del_item(void *p, void *d)
{
	return NULL;
}

mm_module_t array_module = {
	.create = array_create,
	.destroy = array_destroy,
	.control = array_control,
	.handle = array_handle,

	.new_item = array_new_item,
	.del_item = array_del_item,

	.output_type = MM_TYPE_ASINK | MM_TYPE_ADSP | MM_TYPE_VSINK | MM_TYPE_VDSP,
	.module_type = MM_TYPE_ASRC | MM_TYPE_VSRC,
	.name = "ARRAY"
};