/******************************************************************************
*
* Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
*
******************************************************************************/

#include <stdint.h>
#include "platform_stdlib.h"
#include "fatfs_sdcard_api.h"

#include "mmf2_module.h"
#include "module_demuxer.h"
#include "memory_encoder.h"
#include "mp4_demuxer.h"

#define FATFS_SD_CARD

void demuxer_audio_thread(void *p)
{
	demuxer_ctx_t *ctx = (demuxer_ctx_t *)p;
	//unsigned int audio_duration = 0;

	while (1) {
		switch (ctx->demuxer_a_state) {
Reaction:
		case DEMUXER_OPEN:
			//if loop mode wait until the video end
			vTaskDelay(1);
			break;
		case DEMUXER_END:
			//if loop mode wait until the last frame end
			//since mp4 is start based on video when it has video
			//only work when video is stop
			if (ctx->demuxer_v_state == DEMUXER_STOP) {
				if (mm_read_mediatime_ms() > ((ctx->real_audio_timestamp + ctx->audio_duration) / (ctx->mp4_demuxer_ctx->audio_sample_rate / 1000))) {
					ctx->start_timestamp = mm_read_mediatime_ms();
					ctx->cur_a_index = 0;
					ctx->first_timestamp = get_timestamp(ctx->mp4_demuxer_ctx, audio_type, ctx->cur_a_index) / (ctx->mp4_demuxer_ctx->audio_sample_rate / 1000);
					ctx->demuxer_a_state = DEMUXER_START;
					goto Reaction;
				}
			}
			vTaskDelay(1);
			break;
		case DEMUXER_STOP:
			vTaskDelay(10);
			break;
		case DEMUXER_PAUSE:
			if (ctx->demuxer_a_state == DEMUXER_START) {
				goto Reaction;
			}
			vTaskDelay(1);
			break;
		case DEMUXER_START: {
			mm_context_t *mctx = (mm_context_t *)ctx->parent;
			mm_queue_item_t *output_item;
			unsigned int audio_timestamp = 0;
			if (xQueueReceive(mctx->output_recycle, &output_item, 0xFFFFFFFF) == pdTRUE) {
				output_item->data_addr = (uint32_t)memory_alloc(ctx->mem_pool, ctx->mp4_demuxer_ctx->audio_max_size);
				if (!output_item->data_addr) {
					//mm_printf("fail to allocate data drop the frame\r\n");
					xQueueSend(mctx->output_ready, (void *)&output_item, 0xFFFFFFFF);
					goto start_end;
				}

				xSemaphoreTake(ctx->demuxer_sema, portMAX_DELAY);
				output_item->size = get_audio_frame(ctx->mp4_demuxer_ctx, (unsigned char *)output_item->data_addr, ctx->cur_a_index, (unsigned int *) & (ctx->audio_duration),
													(unsigned int *) & (ctx->audio_timestamp));
				xSemaphoreGive(ctx->demuxer_sema);

				output_item->type = ctx->audio_format;
				while (((ctx->audio_timestamp / (ctx->mp4_demuxer_ctx->audio_sample_rate / 1000)) - ctx->first_timestamp) > (mm_read_mediatime_ms() - ctx->start_timestamp)) {
					if (ctx->demuxer_a_state == DEMUXER_PAUSE) {
						memory_free(ctx->mem_pool, (uint8_t *)output_item->data_addr);
						goto Reaction;
					}
					vTaskDelay(1);
				}
				output_item->timestamp = mm_read_mediatime_ms();
				ctx->real_audio_timestamp = output_item->timestamp;
				xQueueSend(mctx->output_ready, (void *)&output_item, 0xFFFFFFFF);
				//mm_printf("Write audio data %d, audio_duration = %d, timestamp = %d\r\n",output_item->size ,ctx->audio_duration ,ctx->audio_timestamp);

				ctx->cur_a_index ++;
				if (ctx->cur_a_index == ctx->mp4_demuxer_ctx->audio_len) {
					if (ctx->params.loop_mode) {
						ctx->demuxer_a_state = DEMUXER_END;
					} else {
						ctx->demuxer_a_state = DEMUXER_STOP;
					}
				}

			}
start_end:
			vTaskDelay(1);
			break;
		}
		}
	}
}

void find_gop_last_frame(demuxer_ctx_t *ctx)
{
	unsigned int audio_timestamp = 0;
	unsigned int video_timestamp = 0;

	while (!check_video_key_frame(ctx->mp4_demuxer_ctx, (ctx->cur_v_index + 1) % ctx->mp4_demuxer_ctx->video_len)) {
		ctx->cur_v_index ++;
		ctx->cur_v_index = ctx->cur_v_index % ctx->mp4_demuxer_ctx->video_len;
	}
	video_timestamp = get_timestamp(ctx->mp4_demuxer_ctx, video_type, ctx->cur_v_index);
	if (ctx->demuxer_a_state != DEMUXER_STOP && ctx->demuxer_a_state != DEMUXER_IDLE) {
		//survey the start time index for audio depend on the video
		ctx->cur_a_index = 0;
		while (ctx->cur_a_index < ctx->mp4_demuxer_ctx->audio_len) {
			//audio_type is a macro
			audio_timestamp = get_timestamp(ctx->mp4_demuxer_ctx, audio_type, ctx->cur_a_index);
			//mm_printf("video_timestamp = %d, audio_timestamp = %d, convert = %d\r\n", video_timestamp, audio_timestamp, (audio_timestamp * 90000) / ctx->mp4_demuxer_ctx->audio_sample_rate);
			if ((audio_timestamp / (ctx->mp4_demuxer_ctx->audio_sample_rate / 1000)) >= (video_timestamp) / 90) {
				break;
			}
			ctx->cur_a_index ++;
		}
		if (ctx->cur_a_index == ctx->mp4_demuxer_ctx->audio_len) {
			mm_printf("MP4 AUDIO NOT FOUND\r\n");
			ctx->demuxer_a_state = DEMUXER_END;
		}
	}
}

void demuxer_video_thread(void *p)
{
	demuxer_ctx_t *ctx = (demuxer_ctx_t *)p;
	//int size = 0;
	//int bw = 0;
	//int i = 0;
	unsigned char key_frame = 0;
	//unsigned int video_timestamp = 0;
	//unsigned int video_duration = 0;


	while (1) {
Reaction:
		switch (ctx->demuxer_v_state) {
		case DEMUXER_OPEN:
			//if loop mode wait until the video end
			vTaskDelay(1);
			break;
		case DEMUXER_END:
			//if loop mode wait until the last frame end
			//since mp4 is start based on video when it has video
			//only work when video is stop
			if (mm_read_mediatime_ms() > ctx->real_video_timestamp + (ctx->video_duration / 90)) {
				ctx->start_timestamp = mm_read_mediatime_ms();
				ctx->cur_v_index = 0;
				ctx->first_timestamp = get_timestamp(ctx->mp4_demuxer_ctx, video_type, ctx->cur_v_index) / 90; //video base on 90KHZ
				ctx->demuxer_v_state = DEMUXER_START;
				if (ctx->demuxer_a_state == DEMUXER_END) {
					ctx->cur_a_index = 0;
					ctx->demuxer_a_state = DEMUXER_START;
				}
				goto Reaction;
			}
			vTaskDelay(1);
			break;
		case DEMUXER_STOP:
			vTaskDelay(10);
			break;
		case DEMUXER_PAUSE: {
			find_gop_last_frame(ctx);
			mm_context_t *mctx = (mm_context_t *)ctx->parent;
			mm_queue_item_t *output_item;
			//mm_printf(" mm_read_mediatime_ms() = %d, %d ", mm_read_mediatime_ms(), (ctx->real_video_timestamp + ctx->video_duration) / 90);
			if (mm_read_mediatime_ms() > ctx->real_video_timestamp + (ctx->video_duration / 90)) {
				//send the same frame
				if (xQueueReceive(mctx->output_recycle, &output_item, 0x10) == pdTRUE) {
					output_item->data_addr = (uint32_t)memory_alloc(ctx->mem_pool, ctx->mp4_demuxer_ctx->video_max_size);
					if (!output_item->data_addr) {
						//mm_printf("fail to allocate data drop the frame\r\n");
						xQueueSend(mctx->output_ready, (void *)&output_item, 0xFFFFFFFF);
						goto pause_end;
					}

					xSemaphoreTake(ctx->demuxer_sema, portMAX_DELAY);
					output_item->size = get_video_frame(ctx->mp4_demuxer_ctx, (unsigned char *)output_item->data_addr, ctx->cur_v_index, &key_frame,
														(unsigned int *) & (ctx->video_duration),
														(unsigned int *) & (ctx->video_timestamp));
					xSemaphoreGive(ctx->demuxer_sema);

					output_item->type = AV_CODEC_ID_H264; //may need change
					output_item->timestamp = mm_read_mediatime_ms();
					ctx->real_video_timestamp = output_item->timestamp;
					ctx->start_timestamp = mm_read_mediatime_ms();
					ctx->first_timestamp = get_timestamp(ctx->mp4_demuxer_ctx, video_type, ctx->cur_v_index) / 90; //video base on 90KHZ
					xQueueSend(mctx->output_ready, (void *)&output_item, 0xFFFFFFFF);
					//mm_printf("Write video data = %d key = %d video_duration = %d video_timestamp = %d\r\n",output_item->size ,key_frame, ctx->video_duration, ctx->video_timestamp);

				}
			}
pause_end:
			vTaskDelay(1);
			break;
		}
		case DEMUXER_START: {
			//mm_printf("DEMUXER_START_V\r\n");
			mm_context_t *mctx = (mm_context_t *)ctx->parent;
			mm_queue_item_t *output_item;
			if (xQueueReceive(mctx->output_recycle, &output_item, 0x10) == pdTRUE) {
				output_item->data_addr = (uint32_t)memory_alloc(ctx->mem_pool, ctx->mp4_demuxer_ctx->video_max_size);
				if (!output_item->data_addr) {
					//mm_printf("fail to allocate data drop the frame\r\n");
					xQueueSend(mctx->output_ready, (void *)&output_item, 0xFFFFFFFF);
					goto start_end;
				}

				xSemaphoreTake(ctx->demuxer_sema, portMAX_DELAY);
				output_item->size = get_video_frame(ctx->mp4_demuxer_ctx, (unsigned char *)output_item->data_addr, ctx->cur_v_index, &key_frame,
													(unsigned int *) & (ctx->video_duration),
													(unsigned int *) & (ctx->video_timestamp));
				xSemaphoreGive(ctx->demuxer_sema);

				output_item->type = AV_CODEC_ID_H264; //may need change
				while (((ctx->video_timestamp / 90) - ctx->first_timestamp) > (mm_read_mediatime_ms() - ctx->start_timestamp)) {
					if (ctx->demuxer_v_state == DEMUXER_PAUSE) {
						memory_free(ctx->mem_pool, (uint8_t *)output_item->data_addr);
						goto Reaction;
					}
					vTaskDelay(1);
				}
				output_item->timestamp = mm_read_mediatime_ms();
				ctx->real_video_timestamp = output_item->timestamp;
				xQueueSend(mctx->output_ready, (void *)&output_item, 0xFFFFFFFF);
				//mm_printf("Write video data = %d key = %d video_duration = %d video_timestamp = %d, ctx->real_video_timestamp = %d\r\n",output_item->size ,key_frame, ctx->video_duration, ctx->video_timestamp, ctx->real_video_timestamp);

				ctx->cur_v_index ++;
				if (ctx->cur_v_index == ctx->mp4_demuxer_ctx->video_len) {
					if (ctx->params.loop_mode) {
						ctx->demuxer_v_state = DEMUXER_END;
					} else {
						ctx->demuxer_v_state = DEMUXER_STOP;
					}
				}
			}
start_end:
			vTaskDelay(1);
			break;
		}
		}

	}
}

static void demuxer_prestart(demuxer_ctx_t *ctx)
{
	unsigned int video_timestamp = 0;
	unsigned int audio_timestamp = 0;

	// audio time stamp if base on video if both are able
	if (ctx->demuxer_v_state == DEMUXER_OPEN) {
		// survey the index for user wanted start time
		ctx->cur_v_index = 0;

		while (ctx->cur_v_index < ctx->mp4_demuxer_ctx->video_len) {
			//video_type is a macro
			//survey the start time index for video
			if (check_video_key_frame(ctx->mp4_demuxer_ctx, ctx->cur_v_index)) {
				video_timestamp = get_timestamp(ctx->mp4_demuxer_ctx, video_type, ctx->cur_v_index);
				if ((video_timestamp / 90) >= ctx->params.start_time) {
					break;
				}
			}
			ctx->cur_v_index ++;
		}
		if (ctx->cur_v_index >= ctx->mp4_demuxer_ctx->video_len) {
			mm_printf("start time out of MP4 VIDEO time\r\n");
			ctx->cur_v_index = ctx->mp4_demuxer_ctx->video_keyframe_buffer[0] - 1;
			video_timestamp = get_timestamp(ctx->mp4_demuxer_ctx, video_type, ctx->cur_v_index);
		}

		if (ctx->demuxer_a_state == DEMUXER_OPEN) {
			//survey the start time index for audio depend on the video
			ctx->cur_a_index = 0;
			while (ctx->cur_a_index < ctx->mp4_demuxer_ctx->audio_len) {
				//audio_type is a macro
				audio_timestamp = get_timestamp(ctx->mp4_demuxer_ctx, audio_type, ctx->cur_a_index);
				//mm_printf("video_timestamp = %d, audio_timestamp = %d, convert = %d\r\n", video_timestamp, audio_timestamp, (audio_timestamp * 90000) / ctx->mp4_demuxer_ctx->audio_sample_rate);
				if ((audio_timestamp / (ctx->mp4_demuxer_ctx->audio_sample_rate / 1000)) >= (video_timestamp) / 90) {
					break;
				}
				ctx->cur_a_index ++;
			}
			if (ctx->cur_a_index == ctx->mp4_demuxer_ctx->audio_len) {
				mm_printf("MP4 AUDIO NOT FOUND\r\n");
				ctx->demuxer_a_state = DEMUXER_END;
			}
		}
		ctx->first_timestamp = video_timestamp / 90;

	} else if (ctx->demuxer_a_state == DEMUXER_OPEN) {
		while (ctx->cur_a_index < ctx->mp4_demuxer_ctx->audio_len) {
			//audio_type is a macro
			audio_timestamp = get_timestamp(ctx->mp4_demuxer_ctx, audio_type, ctx->cur_a_index);

			if ((audio_timestamp / (ctx->mp4_demuxer_ctx->audio_sample_rate / 1000)) >= ctx->params.start_time) {
				break;
			}
			ctx->cur_a_index ++;
		}
		if (ctx->cur_a_index == ctx->mp4_demuxer_ctx->audio_len) {
			mm_printf("start time out of MP4 AUDIO time\r\n");
			ctx->cur_a_index = 0;
			audio_timestamp = get_timestamp(ctx->mp4_demuxer_ctx, audio_type, ctx->cur_a_index);
		}
		ctx->first_timestamp = audio_timestamp / (ctx->mp4_demuxer_ctx->audio_sample_rate / 1000);
	}
	ctx->start_timestamp = mm_read_mediatime_ms();
}

int demuxer_control(void *p, int cmd, int arg)
{
	demuxer_ctx_t *ctx = (demuxer_ctx_t *)p;
	int ret = 0;
	char tmp_name[32];

	switch (cmd) {
	case CMD_DEMUXER_SET_PARAMS: // setting the demuxer parameters
		memcpy(&ctx->params, (void *)arg, sizeof(demuxer_params_t));
		break;
	case CMD_DEMUXER_GET_PARAMS:
		memcpy((void *)arg, &ctx->params, sizeof(demuxer_params_t));
		break;
	case CMD_DEMUXER_SET_FILE_NAME:
		break;
	case CMD_DEMUXER_MEMORY_SIZE:
		ctx->params.mem_total_size = arg;
		break;
	case CMD_DEMUXER_BLOCK_SIZE:
		ctx->params.mem_block_size = arg;
		break;
	case CMD_DEMUXER_INIT_MEM_POOL:
		ctx->mem_pool = (void *)memory_init(ctx->params.mem_total_size, ctx->params.mem_block_size);
		if (ctx->mem_pool == NULL) {
			mm_printf("[DEMUXER ERR] Can't allocate DEMUXER buffer, heap not enough\r\n");
			ret = -1;
		}
		break;
	case CMD_DEMUXER_OPEN: // open the file with setting file name
		memset(ctx->file_name, 0, 128);
		//mm_printf("%s \r\n", ctx->fatfs_params.drv);
		//strncpy(ctx->file_name, ctx->fatfs_params.drv, strlen(ctx->fatfs_params.drv));
		//mm_printf("mp4_demuxer->filename = %s\r\n", ctx->file_name);
		//snprintf(ctx->file_name + strlen(ctx->fatfs_params.drv), (sizeof(ctx->file_name) - strlen(ctx->fatfs_params.drv)-1), "%s", ctx->params.record_file_name);
		int str_len = strlen(ctx->fatfs_params.drv) + strlen(ctx->params.record_file_name);
		ret = snprintf(ctx->file_name, sizeof(ctx->file_name), "%s%s", ctx->fatfs_params.drv, ctx->params.record_file_name);
		if (ret != str_len) {
			mm_printf("The name length exceeds the buffer %d\r\n", str_len);
			ret = -1;
			return ret;
		}
		mm_printf("mp4_demuxer->filename = %s\r\n", ctx->file_name);

		mp4_demuxer_open(ctx->mp4_demuxer_ctx, ctx->file_name);
		if (ctx->mp4_demuxer_ctx->audio_exist) {
			mm_printf("Audio source found\r\n");
			ctx->demuxer_a_state = DEMUXER_OPEN;
			if (ctx->mp4_demuxer_ctx->audio_format_type == AUDIO_AAC) {
				mm_printf("AAC Audio source\r\n");
				ctx->audio_format = AV_CODEC_ID_MP4A_LATM;
			} else if (ctx->mp4_demuxer_ctx->audio_format_type == AUDIO_ULAW) {
				mm_printf("PCMU Audio source\r\n");
				ctx->audio_format = AV_CODEC_ID_PCMU;
			} else if (ctx->mp4_demuxer_ctx->audio_format_type == AUDIO_ALAW) {
				mm_printf("PCMA Audio source\r\n");
				ctx->audio_format = AV_CODEC_ID_PCMA;
			} else {
				mm_printf("Unknown Audio source\r\n");
				ctx->audio_format = AV_CODEC_ID_UNKNOWN;
				ctx->demuxer_a_state = DEMUXER_STOP;
			}
		} else {
			mm_printf("Audio source NOT found\r\n");
			ctx->demuxer_a_state = DEMUXER_STOP;
		}
		if (ctx->mp4_demuxer_ctx->video_exist) {
			mm_printf("Video source found\r\n");
			ctx->demuxer_v_state = DEMUXER_OPEN;
		} else {
			mm_printf("Video source Not found\r\n");
			ctx->demuxer_v_state = DEMUXER_STOP;
		}
		break;
	case CMD_DEMUXER_CLOSE:
		mp4_demuxer_close(ctx->mp4_demuxer_ctx); // mp4_demuxer_close

		break;
	case CMD_DEMUXER_STREAM_PAUSE:
		if (ctx->demuxer_a_state == DEMUXER_START || (ctx->demuxer_a_state == DEMUXER_END && ctx->params.loop_mode)) {
			ctx->demuxer_a_state = DEMUXER_PAUSE;
		}
		if (ctx->demuxer_v_state == DEMUXER_START || (ctx->demuxer_v_state == DEMUXER_END && ctx->params.loop_mode)) {
			ctx->demuxer_v_state = DEMUXER_PAUSE;
		}
		break;
	case CMD_DEMUXER_STREAM_RESUME:
		if (ctx->demuxer_a_state == DEMUXER_PAUSE) {
			ctx->demuxer_a_state = DEMUXER_START;
		}
		if (ctx->demuxer_v_state == DEMUXER_PAUSE) {
			ctx->demuxer_v_state = DEMUXER_START;
		}
		break;
	case CMD_DEMUXER_STREAM_START:
		printf("CMD_DEMUXER_STREAM_START\r\n");
		demuxer_prestart(ctx);
		if (ctx->mem_pool == NULL) {
			ctx->demuxer_a_state = DEMUXER_STOP;
			ctx->demuxer_v_state = DEMUXER_STOP;
			printf("[DEMUXER ERR] DENUXER memory pool not initialed yet\r\n");
			ret = -1;
			return ret;
		}
		if (ctx->demuxer_a_state == DEMUXER_OPEN) {
			if (xTaskCreate(demuxer_audio_thread, ((const char *)"demuxer_audio"), 2048, (void *)ctx, 2, &ctx->audio_handler) != pdPASS) {
				printf("[DEMUXER ERR] ceate task audio fail\r\n");
				ctx->demuxer_a_state = DEMUXER_STOP;
				ret = -1;
			} else {
				ctx->demuxer_a_state = DEMUXER_START;
				printf("ceate task audio success\r\n");
			}
		}
		if (ctx->demuxer_v_state == DEMUXER_OPEN) {
			if (xTaskCreate(demuxer_video_thread, ((const char *)"demuxer_video"), 2048, (void *)ctx, 2, &ctx->video_handler) != pdPASS) {
				printf("[DEMUXER ERR] ceate task video fail\r\n");
				ctx->demuxer_v_state = DEMUXER_STOP;
				ret = -1;
			} else {
				ctx->demuxer_v_state = DEMUXER_START;
				printf("ceate task audio success\r\n");
			}
		}

		xSemaphoreGive(ctx->demuxer_sema);
		break;
	}
	return ret;
}

int demuxer_handle(void *ctx, void *input, void *output) // will not be used
{
	return 0;
}

void *demuxer_destroy(void *p)
{
	demuxer_ctx_t *ctx = (demuxer_ctx_t *)p;

	if (ctx)	{
		if (ctx->audio_handler) {
			vTaskDelete(ctx->audio_handler);
			ctx->audio_handler = NULL;
		}
		if (ctx->video_handler) {
			vTaskDelete(ctx->video_handler);
			ctx->video_handler = NULL;
		}
		if (ctx->demuxer_sema) {
			vSemaphoreDelete(ctx->demuxer_sema);
		}
		if (ctx->mp4_demuxer_ctx) {
			free(ctx->mp4_demuxer_ctx);
		}

		free(ctx);
	}
	return NULL;
}

void *demuxer_create(void *parent)
{
	demuxer_ctx_t *ctx = malloc(sizeof(demuxer_ctx_t));
	if (!ctx) {
		return NULL;
	}
	memset(ctx, 0, sizeof(demuxer_ctx_t));
	ctx->parent = parent;

	ctx->demuxer_sema = xSemaphoreCreateBinary();
	if (!ctx->demuxer_sema) {
		goto demuxer_create_fail;
	}

	ctx->mp4_demuxer_ctx = (mp4_demux *)malloc(sizeof(mp4_demux));
	if (ctx->mp4_demuxer_ctx == NULL) {
		mm_printf("It can't be allocated the buffer\r\n");
		goto demuxer_create_fail;
	}
	memset(ctx->mp4_demuxer_ctx, 0, sizeof(mp4_demux));

	ctx->demuxer_a_state = DEMUXER_IDLE;
	ctx->demuxer_v_state = DEMUXER_IDLE;
#ifdef FATFS_SD_CARD
	if (fatfs_sd_init() < 0) {
		mm_printf("[MODULE DEMUXER]SD INIT FAIL\r\n");
		goto demuxer_create_fail;
	}
	fatfs_sd_get_param(&ctx->fatfs_params);

	set_mp4_demuxer_fatfs_param(ctx->mp4_demuxer_ctx, &(ctx->fatfs_params));
#else
	if (fatfs_ram_init() < 0) {
		mm_printf("[MODULE DEMUXER]RAM INIT FAIL\r\n");
		goto demuxer_create_fail;
	}
	fatfs_ram_get_param((fatfs_ram_params_t *)&ctx->fatfs_params);
	set_mp4_demuxer_fatfs_param(&ctx->mp4_demuxer_ctx, &ctx->fatfs_params);
#endif

	return ctx;

demuxer_create_fail:
	demuxer_destroy((void *)ctx);
	return NULL;
}

void *demuxer_new_item(void *p)
{
	return NULL;
}

void *demuxer_del_item(void *p, void *d)
{
	demuxer_ctx_t *ctx = (demuxer_ctx_t *)p;

	if (d) {
		memory_free(ctx->mem_pool, d);
	}
	return NULL;
}

mm_module_t demuxer_module = {
	.create = demuxer_create,
	.destroy = demuxer_destroy,
	.control = demuxer_control,
	.handle = demuxer_handle,

	.new_item = demuxer_new_item,
	.del_item = demuxer_del_item,

	.output_type = MM_TYPE_ASINK | MM_TYPE_ADSP | MM_TYPE_VSINK | MM_TYPE_VDSP,
	.module_type = MM_TYPE_ASRC | MM_TYPE_VSRC,
	.name = "DEMUXER"
};
