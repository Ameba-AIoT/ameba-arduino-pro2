/******************************************************************************
*
* Copyright(c) 2007 - 2023 Realtek Corporation. All rights reserved.
*
******************************************************************************/

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "mmf2_module.h"
#include "module_queue.h"
#include "FreeRTOS.h"
#include "avcodec.h"

static void queue_free(QueueHandle_t *q) {
	mm_queue_item_t queue_item;
	if(*q) {
		while (uxQueueMessagesWaiting(*q)) {
			if (xQueueReceive(*q, &queue_item, 0xFFFFFFFF) == pdTRUE) {
				free((void *)queue_item.data_addr);
			}
		}
		vQueueDelete(*q);
		*q = NULL;
	}
}

static int queue_handle(void *p, void *input, void *output)
{
	queue_ctx_t *ctx = (queue_ctx_t *)p;	
	mm_context_t *mctx = (mm_context_t *)ctx->parent;
	mm_queue_item_t *input_item = (mm_queue_item_t *)input;
	mm_queue_item_t *output_item = NULL;
	mm_queue_item_t queue_item;

	QueueHandle_t queue = NULL;
	if ((input_item->type == AV_CODEC_ID_H264) || (input_item->type == AV_CODEC_ID_H265)) {
		queue = ctx->video_queue;
	} else if ((input_item->type == AV_CODEC_ID_MP4A_LATM) || (input_item->type == AV_CODEC_ID_PCMU) || (input_item->type == AV_CODEC_ID_PCMA)) {
		queue = ctx->audio_queue;
	}
	if (queue) {
		if (!uxQueueSpacesAvailable(queue)) { //if queue full send to next module
			if (xQueueReceive(queue, &queue_item, 10) == pdTRUE) {
				if (xQueueReceive(mctx->output_recycle, &output_item, 30) == pdTRUE) {
					output_item->data_addr = queue_item.data_addr;
					output_item->size = queue_item.size;
					output_item->type = queue_item.type;
					output_item->timestamp = queue_item.timestamp;
					xQueueSend(mctx->output_ready, &output_item, 0xFFFFFFFF);
				} else {
					printf("queue send timeout %d\r\n", uxQueueMessagesWaiting(mctx->output_recycle));
					free((void *)queue_item.data_addr);
				}
			}
		}

		queue_item.data_addr = (uint32_t) malloc(input_item->size);
		memcpy((void *)queue_item.data_addr, (void *)input_item->data_addr, input_item->size);
		queue_item.size = input_item->size;
		queue_item.type = input_item->type;
		queue_item.timestamp = input_item->timestamp;
		//printf("input add %d size %d, type %d\r\n", queue_item.data_addr, queue_item.size, queue_item.type);
		if(xQueueSendToBack(queue, &queue_item, 10) != pdTRUE) {
			free((void *)queue_item.data_addr);
		}

	}

	return 0;
}

static int queue_control(void *p, int cmd, int arg)
{
	queue_ctx_t *ctx = (queue_ctx_t *)p;

	switch (cmd) {
	case CMD_QUEUE_SET_VQUEUE_LEN:
		ctx->video_queue_len = arg;
		if (ctx->video_queue_len) {
			if (ctx->video_queue) {
				queue_free(&ctx->video_queue);
			}
			ctx->video_queue = xQueueCreate(ctx->video_queue_len, sizeof(mm_queue_item_t));
			if (ctx->video_queue == NULL) {
				printf("video_queue create fail \r\n");
				return 0;
			}
		}
		break;
	case CMD_QUEUE_SET_AQUEUE_LEN:
		ctx->audio_queue_len = arg;
		if (ctx->audio_queue_len) {
			if (ctx->audio_queue) {
				queue_free(&ctx->audio_queue);
			}
			ctx->audio_queue = xQueueCreate(ctx->audio_queue_len, sizeof(mm_queue_item_t));
			if (ctx->audio_queue == NULL) {
				printf("audio_queue create fail \r\n");
				return 0;
			}
		}
		break;
	}

	return 0;
}

static void *queue_new_item(void *p)
{
	queue_ctx_t *ctx = (queue_ctx_t *)p;
	//dynamic create item in queue_handle
	return NULL;
}

static void *queue_del_item(void *p, void *d)
{
	(void)p;
	if (d) {
		free(d);
	}
	return NULL;
}

static void *queue_destroy(void *p)
{
	queue_ctx_t *ctx = (queue_ctx_t *)p;
	mm_queue_item_t queue_item;
	if (ctx) {
		if(ctx->video_queue) {
			queue_free(&ctx->video_queue);
		}		
		if(ctx->audio_queue) {
			queue_free(&ctx->audio_queue);
		}
		free(ctx);
	}
	return NULL;
}

static void *queue_create(void *parent)
{
	queue_ctx_t *ctx = (queue_ctx_t *)malloc(sizeof(queue_ctx_t));
	if (!ctx) {
		return NULL;
	}
	memset(ctx, 0, sizeof(queue_ctx_t));
	ctx->parent = parent;
	ctx->video_queue = NULL;
	ctx->audio_queue = NULL;

	return ctx;
}


mm_module_t queue_module = {
	.create = queue_create,
	.destroy = queue_destroy,
	.control = queue_control,
	.handle = queue_handle,

	.new_item = queue_new_item,
	.del_item = queue_del_item,

	.output_type = MM_TYPE_AVSINK,
	.module_type = MM_TYPE_AVSINK,
	.name = "QUEUE"
};
