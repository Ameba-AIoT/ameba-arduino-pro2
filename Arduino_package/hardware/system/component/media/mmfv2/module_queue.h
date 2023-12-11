#ifndef _MODULE_QUEUE_H
#define _MODULE_QUEUE_H

#include <stdint.h>
#include "mmf2_module.h"

#define CMD_QUEUE_SET_VQUEUE_LEN			MM_MODULE_CMD(0x00)
#define CMD_QUEUE_SET_AQUEUE_LEN			MM_MODULE_CMD(0x01)

typedef struct queue_ctx_s {
	void *parent;
	int video_queue_len;
	int audio_queue_len;
	xQueueHandle video_queue;
	xQueueHandle audio_queue;
} queue_ctx_t;

extern mm_module_t queue_module;

#endif
