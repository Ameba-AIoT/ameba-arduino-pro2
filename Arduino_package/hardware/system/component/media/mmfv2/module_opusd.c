/******************************************************************************
*
* Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
*
******************************************************************************/
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "mmf2_module.h"
#include "module_opusd.h"

#include "opus.h"
#include <FreeRTOS.h>
#include <semphr.h>
#define MAX_SAMPLE_RATE 16000
#define OPUS_CACHE_SIZE 1024
#define OPUS_OUTPUT_SIZE(samplerate) (120 * (samplerate / 1000) * sizeof(uint16_t)) //120ms (opus packet max)

//extern xSemaphoreHandle  opus_progress_sema;

//------------------------------------------------------------------------------

void opusd_bypass_parser(void *p, void *input, int len)
{
	opusd_ctx_t *ctx = (opusd_ctx_t *)p;
	uint32_t newlen;
	if (len > 0) {
		newlen = opus_packet_unpad(input, len);
		//mm_printf("ctx->data_cache_len: %d olen: %d newlen:%d\r\n",ctx->data_cache_len, len, newlen);
		if (newlen == 1) {
			memcpy(ctx->data_cache + ctx->data_cache_len, input, newlen);
			ctx->data_cache_len += 1;
			ctx->last_frame_idx ++;
			ctx->frame_len_buf[ctx->last_frame_idx] = 0;
		} else {
			memcpy(ctx->data_cache + ctx->data_cache_len, input, newlen);
			ctx->data_cache_len += newlen;
			ctx->last_frame_idx ++;
			ctx->frame_len_buf[ctx->last_frame_idx] = newlen;
		}
	}
}

int opusd_handle(void *p, void *input, void *output)
{
	opusd_ctx_t *ctx = (opusd_ctx_t *)p;
	mm_queue_item_t *input_item = (mm_queue_item_t *)input;
	mm_queue_item_t *output_item = (mm_queue_item_t *)output;

	if (ctx->stop == 1) {
		//mm_printf("opus decoder stop\r\n");
		return 0;
	}

	if (input_item->size == 0)	{
		return -1;
	}

	if (ctx->data_cache_len + input_item->size >= ctx->data_cache_size || ctx->last_frame_idx > ctx->max_frame_in_chache) {
		// This should never happened
		mm_printf("[OPUSD ERR] opusd data cache overflow %d %d\r\n", ctx->data_cache_len, input_item->size);
		return -1;
	}

	int numofsamplesperframe = 0;
	//int numofframes = 0;
	int numofsamples = 0;
	int outputframesize = 0;
	int remain_len = 0;
	int ret;


	ctx->parser((void *)ctx, (void *)input_item->data_addr, input_item->size);
	remain_len = ctx->data_cache_len;


	while (1) {

		if (ctx->last_frame_idx < 0 || remain_len <= 0) {
			ctx->last_frame_idx = -1;
			remain_len = 0;
			break;
		}
		numofsamplesperframe = opus_packet_get_samples_per_frame((const unsigned char *)ctx->data_cache, ctx->params.sample_rate);
		numofsamples = opus_packet_get_nb_samples((const unsigned char *)ctx->data_cache, ctx->frame_len_buf[ctx->last_frame_idx], ctx->params.sample_rate);
		//mm_printf("opus decode numofsamplesperframe = %d, numofsamples = %d\r\n", numofsamplesperframe, numofsamples);
		//mm_printf("opus decode outputframesize = %d\r\n", outputframesize);
		if (outputframesize + numofsamples * ctx->params.bit_length / 8  > ctx->max_output_byte) {
			break;
		}
		if (numofsamplesperframe > 0) {
			memset(ctx->decode_buf, 0, ctx->max_output_byte);


			ret = opus_decode(ctx->opus_dec, (const unsigned char *)ctx->data_cache, ctx->frame_len_buf[ctx->last_frame_idx], (opus_int16 *)ctx->decode_buf,
							  numofsamples, 0);

			//mm_printf("ret = %d\r\n",ret);
			if (ret >= 0) {
				memcpy((void *)(output_item->data_addr + outputframesize), (void *)ctx->decode_buf, ret * ctx->params.bit_length / 8);
				memmove(ctx->data_cache, ctx->data_cache + ctx->data_cache_len - ctx->frame_len_buf[ctx->last_frame_idx], ctx->frame_len_buf[ctx->last_frame_idx]);
				if (ctx->frame_len_buf[ctx->last_frame_idx] != 0) {
					remain_len -= ctx->frame_len_buf[ctx->last_frame_idx];
				}
				outputframesize += ret * ctx->params.bit_length / 8;
				//move the frame size for the new frame//
				memmove(ctx->frame_len_buf, ctx->frame_len_buf + 1, ctx->last_frame_idx * sizeof(uint32_t));
				ctx->last_frame_idx --;
			} else {
				memmove(ctx->data_cache, ctx->data_cache + ctx->data_cache_len - ctx->frame_len_buf[ctx->last_frame_idx], ctx->frame_len_buf[ctx->last_frame_idx]);
				if (ctx->frame_len_buf[ctx->last_frame_idx] != 0) {
					remain_len -= ctx->frame_len_buf[ctx->last_frame_idx];
				}
				memmove(ctx->frame_len_buf, ctx->frame_len_buf + 1, ctx->last_frame_idx * sizeof(uint32_t));
				ctx->last_frame_idx --;
				break;
			}
		}
	}
	//mm_printf("opus decode frame_size = %d\r\n", outputframesize);
	ctx->data_cache_len = remain_len;

	output_item->size = outputframesize;
	output_item->timestamp = input_item->timestamp;
	output_item->index = 0;
	output_item->type = 0;

	return output_item->size;
}

static int opusdmodule_apply(void *p)
{
	opusd_ctx_t *ctx = (opusd_ctx_t *)p;
	if (ctx) {
		if (ctx->params.sample_rate > MAX_SAMPLE_RATE) {
			printf("[OPUSD ERR] opusd sample_rate %d > MAX_SAMPLE_RATE: %d, please adjust MAX_SAMPLE_RATE in module_opusd.c\r\n", ctx->params.sample_rate, MAX_SAMPLE_RATE);
			ctx->stop = 1;
			return -1;
		}
		ctx->data_cache_len = 0;
		if (opus_decoder_init(ctx->opus_dec, ctx->params.sample_rate, ctx->params.channel) != OPUS_OK) {
			printf("[OPUSD ERR] opusd init fail\r\n");
			ctx->stop = 1;
			return -1;
		}
		ctx->max_output_byte = OPUS_OUTPUT_SIZE(ctx->params.sample_rate);
		ctx->parser = opusd_bypass_parser;
		opus_decoder_ctl(ctx->opus_dec, OPUS_SET_SIGNAL(ctx->params.opus_application));
		opus_decoder_ctl(ctx->opus_dec, OPUS_SET_GAIN(0));
		ctx->decode_buf = malloc(1 * ctx->max_output_byte);
		if (!ctx->decode_buf) {
			printf("[OPUSD ERR] allcocate opusd decode buffer fail\r\n");
			ctx->stop = 1;
			return -1;
		}
		//opus_decoder_ctl(ctx->opus_dec, OPUS_SET_GAIN(10));
		ctx->stop = 0;
		return 0;
	}
	return -1;
}

int opusd_control(void *p, int cmd, int arg)
{
	opusd_ctx_t *ctx = (opusd_ctx_t *)p;
	int ret = 0;

	switch (cmd) {
	case CMD_OPUSD_SET_PARAMS:
		memcpy(&ctx->params, ((opusd_params_t *)arg), sizeof(opusd_params_t));
		break;
	case CMD_OPUSD_GET_PARAMS:
		memcpy(((opusd_params_t *)arg), &ctx->params, sizeof(opusd_params_t));
		break;
	case CMD_OPUSD_SAMPLERATE:
		ctx->params.sample_rate = arg;
		break;
	case CMD_OPUSD_CHANNEL:
		ctx->params.channel = arg;
		break;
	case CMD_OPUSD_STREAM_TYPE:
		ctx->params.opus_application = arg;
		break;
	case CMD_OPUSD_STOP:
		ctx->stop = 1;
		break;
	case CMD_OPUSD_RESET:
		ctx->stop = 1;
		ret = opusdmodule_apply(ctx);
		break;
	case CMD_OPUSD_APPLY:
		ret = opusdmodule_apply(ctx);
		break;
	}

	return ret;
}

void *opusd_destroy(void *p)
{
	opusd_ctx_t *ctx = (opusd_ctx_t *)p;

	if (ctx && ctx->opus_dec) {
		opus_decoder_destroy(ctx->opus_dec);
	}

	if (ctx && ctx->decode_buf) {
		free(ctx->decode_buf);
	}
	if (ctx && ctx->data_cache)	{
		free(ctx->data_cache);
	}
	if (ctx) {
		free(ctx);
	}

	return NULL;
}

void *opusd_create(void *parent)
{
	int error_code;
	opusd_ctx_t *ctx = (opusd_ctx_t *)malloc(sizeof(opusd_ctx_t));
	if (!ctx) {
		return NULL;
	}
	ctx->parent = parent;
	ctx->stop = 1;

	// no need check return value because of AACInitDecoder implement
	ctx->opus_dec = opus_decoder_create(48000, 1, &error_code);

	if (error_code != 0) { //OPUS_OK
		goto opusd_create_fail;
	}

	ctx->data_cache_size = OPUS_CACHE_SIZE;
	ctx->data_cache = malloc(ctx->data_cache_size);
	if (!ctx->data_cache) {
		goto opusd_create_fail;
	}

	ctx->max_frame_in_chache = 20;
	ctx->last_frame_idx = -1; //-1 means no frame
	ctx->frame_len_buf = malloc(ctx->max_frame_in_chache * sizeof(uint32_t));

	ctx->data_cache_len = 0;
	return ctx;

opusd_create_fail:
	opusd_destroy((void *)ctx);
	return NULL;
}

void *opusd_new_item(void *p)
{
	//opusd_ctx_t *ctx = (opusd_ctx_t *)p;
	return malloc(1 * OPUS_OUTPUT_SIZE(MAX_SAMPLE_RATE)); // opus max expected sample rate outputsizes
}

void *opusd_del_item(void *p, void *d)
{
	if (d) {
		free(d);
	}
	return NULL;
}


mm_module_t opusd_module = {
	.create = opusd_create,
	.destroy = opusd_destroy,
	.control = opusd_control,
	.handle = opusd_handle,

	.new_item = opusd_new_item,
	.del_item = opusd_del_item,

	.output_type = MM_TYPE_ASINK | MM_TYPE_ADSP,
	.module_type = MM_TYPE_ADSP,
	.name = "OPUSD"
};
