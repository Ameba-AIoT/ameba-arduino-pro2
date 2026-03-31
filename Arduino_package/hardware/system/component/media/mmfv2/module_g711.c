/******************************************************************************
*
* Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
*
******************************************************************************/

#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "avcodec.h"

#include "mmf2_module.h"

#include "module_g711.h"

// extern from g711_codec.c
extern uint8_t encodeA(short pcm_val);
extern short decodeA(uint8_t a_val);
extern uint8_t encodeU(short pcm_val);
extern short decodeU(uint8_t u_val);

//------------------------------------------------------------------------------
int g711_handle(void *p, void *input, void *output)
{
	g711_ctx_t *ctx = (g711_ctx_t *)p;
	mm_queue_item_t *input_item = (mm_queue_item_t *)input;
	mm_queue_item_t *output_item = (mm_queue_item_t *)output;

	if (ctx->params.mode == G711_ENCODE) {
		//mm_printf("PCM ENC\n\r");
		short *input_buf = (short *)input_item->data_addr;
		uint8_t *output_buf = (uint8_t *)output_item->data_addr;
		if (ctx->params.codec_id == AV_CODEC_ID_PCMU) {
			for (int i = 0; i < input_item->size / sizeof(short); i++) {
				output_buf[i] = encodeU(input_buf[i]);
			}
		} else if (ctx->params.codec_id == AV_CODEC_ID_PCMA) {
			for (int i = 0; i < input_item->size / sizeof(short); i++) {
				output_buf[i] = encodeA(input_buf[i]);
			}
		} else {
			return -1;
		}

		output_item->size = input_item->size / sizeof(short);
	} else if (ctx->params.mode == G711_DECODE) {
		//mm_printf("PCM DEC\n\r");
		uint8_t *input_buf = (uint8_t *)input_item->data_addr;
		short *output_buf = (short *)output_item->data_addr;
		if (ctx->params.codec_id == AV_CODEC_ID_PCMU) {
			for (int i = 0; i < input_item->size; i++) {
				output_buf[i] = decodeU(input_buf[i]);
			}
		} else if (ctx->params.codec_id == AV_CODEC_ID_PCMA) {
			for (int i = 0; i < input_item->size; i++) {
				output_buf[i] = decodeA(input_buf[i]);
			}
		} else {
			return -1;
		}
		output_item->size = input_item->size * sizeof(short);
	} else {
		return -1;
	}

	output_item->timestamp = input_item->timestamp;
	output_item->type = ctx->params.codec_id;


	return output_item->size;
}

int g711_control(void *p, int cmd, int arg)
{
	g711_ctx_t *ctx = (g711_ctx_t *)p;

	switch (cmd) {
	case CMD_G711_SET_PARAMS:
		memcpy(&ctx->params, ((g711_params_t *)arg), sizeof(g711_params_t));
		break;
	case CMD_G711_GET_PARAMS:
		memcpy(((g711_params_t *)arg), &ctx->params, sizeof(g711_params_t));
		break;
	case CMD_G711_CODECID:
		ctx->params.codec_id = arg;
		break;
	case CMD_G711_LENGTH:
		ctx->params.buf_len = arg;
		break;
	case CMD_G711_CODECMODE:
		ctx->params.mode = arg;
		break;
	case CMD_G711_APPLY:
		// nothing to do
		break;
	}

	return 0;
}

void *g711_destroy(void *p)
{
	g711_ctx_t *ctx = (g711_ctx_t *)p;

	if (ctx) {
		free(ctx);
	}

	return NULL;
}

void *g711_create(void *parent)
{
	g711_ctx_t *ctx = (g711_ctx_t *)malloc(sizeof(g711_ctx_t));
	if (!ctx) {
		return NULL;
	}
	memset(ctx, 0, sizeof(g711_ctx_t));
	ctx->parent = parent;

	return ctx;
}

void *g711_new_item(void *p)
{
	g711_ctx_t *ctx = (g711_ctx_t *)p;

	return (void *)malloc(ctx->params.buf_len);
}

void *g711_del_item(void *p, void *d)
{
	(void)p;
	if (d) {
		free(d);
	}
	return NULL;
}


mm_module_t g711_module = {
	.create = g711_create,
	.destroy = g711_destroy,
	.control = g711_control,
	.handle = g711_handle,

	.new_item = g711_new_item,
	.del_item = g711_del_item,

	.output_type = MM_TYPE_ASINK | MM_TYPE_ADSP,
	.module_type = MM_TYPE_ADSP,
	.name = "G711"
};
