/******************************************************************************
*
* Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
*
******************************************************************************/

#include <stdint.h>
#include "avcodec.h"

#include "memory_encoder.h"
#include "mmf2_module.h"
#include "module_aac.h"
#include "mmf2_dbg.h"

#include "psych.h"
#include "faac.h"
#include "faac_api.h"

//------------------------------------------------------------------------------
//AAD open function
static int aachandle_Open(aac_ctx_t *ctx)
{
	int ret = 0;

	if (aacEncOpen(&(ctx->fdkaac_enc), 0, ctx->params.channel) != AACENC_OK) {
		mm_printf("Unable to open encoder\r\n");
		ret = -1;
	}

	if (ctx->params.trans_type == AAC_TYPE_ADTS && (ctx->params.object_type == AAC_AOT_ER_LD || ctx->params.object_type == AAC_AOT_ER_ELD)) {
		printf("ADTS only support LC based audio object type\r\n");
		ret = -1;
		goto endofopen;
	}
	ctx->object_type = ctx->params.object_type;
	if (aacEncoder_SetParam(ctx->fdkaac_enc, AACENC_AOT, ctx->object_type) != AACENC_OK) {
		printf("Unable to set the AOT %d\r\n", ctx->object_type);
		ret = -1;
		goto endofopen;
	}
	if (ctx->params.object_type == AAC_AOT_ER_ELD) {
		if (aacEncoder_SetParam(ctx->fdkaac_enc, AACENC_SBR_MODE, -1) != AACENC_OK) {
			printf("Unable to set the SBR MODE for AAC ELD\r\n");
			ret = -1;
			goto endofopen;
		}
	}
	if (ctx->params.object_type == AAC_AOT_PS && ctx->params.channel != 2) {
		printf("Audio Object Type support stereo channel please check the setting\r\n");
		ret = -1;
		goto endofopen;
	}
	if (aacEncoder_SetParam(ctx->fdkaac_enc, AACENC_SAMPLERATE, ctx->params.sample_rate) != AACENC_OK) {
		printf("Unable to set the sample rate %d\r\n", ctx->params.sample_rate);
		ret = -1;
		goto endofopen;
	}
	if (aacEncoder_SetParam(ctx->fdkaac_enc, AACENC_CHANNELMODE, ctx->params.channel) != AACENC_OK) {
		printf("Unable to set the channel %d\r\n", ctx->params.channel);
		ret = -1;
		goto endofopen;
	}
	if (aacEncoder_SetParam(ctx->fdkaac_enc, AACENC_CHANNELORDER, 1) != AACENC_OK) {
		printf("Unable to set the wav channel order\r\n");
		ret = -1;
		goto endofopen;
	}
	/*
	if (vbr) {
	    if (aacEncoder_SetParam(ctx->fdkaac_enc, AACENC_BITRATEMODE, vbr) != AACENC_OK) {
	        printf("Unable to set the VBR bitrate mode\r\n");
		    ret = -1;
	        goto endofopen;
	    }
	} else {
	    if (aacEncoder_SetParam(ctx->fdkaac_enc, AACENC_BITRATE, bitrate) != AACENC_OK) {
	        printf("Unable to set the bitrate\r\n");
	        ret = -1;
	        goto endofopen;
	    }
	}
	*/
	if (aacEncoder_SetParam(ctx->fdkaac_enc, AACENC_BITRATE, ctx->params.bitrate) != AACENC_OK) {
		printf("Unable to set the bitrate %d\r\n", ctx->params.bitrate);
		ret = -1;
		goto endofopen;
	}
	ctx->trans_type = ctx->params.trans_type;
	if (aacEncoder_SetParam(ctx->fdkaac_enc, AACENC_TRANSMUX, ctx->trans_type) != AACENC_OK) {
		printf("Unable to set the ADTS transmux\r\n");
		ret = -1;
		goto endofopen;
	}
	//Afterburner is "a type of analysis by synthesis algorithm which increases the audio quality but also the required processing power.
	if (aacEncoder_SetParam(ctx->fdkaac_enc, AACENC_AFTERBURNER, 0) != AACENC_OK) {
		printf("Unable to set the afterburner mode\r\n");
		ret = -1;
		goto endofopen;
	}
	AACENC_ERROR err = aacEncEncode(ctx->fdkaac_enc, NULL, NULL, NULL, NULL);
	if (err != AACENC_OK) {
		printf("Unable to initialize the encoder %x\r\n", err);
		ret = -1;
		goto endofopen;
	}

	err = aacEncInfo(ctx->fdkaac_enc, &(ctx->enc_info));
	if (err != AACENC_OK) {
		printf("Unable to get the encoder ctx->enc_info %d\r\n", err);
		ret = -1;
		goto endofopen;
	}
	printf("ctx->enc_info.frameLength * 2 = %d\r\n", ctx->enc_info.frameLength * 2);

endofopen:
	return ret;
}

int aac_handle(void *p, void *input, void *output)
{
	aac_ctx_t *ctx = (aac_ctx_t *)p;
	mm_queue_item_t *input_item = (mm_queue_item_t *)input;
	mm_queue_item_t *output_item = (mm_queue_item_t *)output;

	//int samples_read, frame_size;
	int frame_size = 0;

	if (ctx->stop == 1) {
		//printf("stop\r\n");
		return 0;
	}
	output_item->timestamp = input_item->timestamp;
	// set timestamp to 1st sample (cache head)
	output_item->timestamp -= 1000 * (ctx->cache_idx / 2) / ctx->params.sample_rate;

	if (ctx->cache_idx + input_item->size >= ctx->max_cache_size) {
		mm_printf("[AAC WARN] aac data cache overflow %d + %d >= %d, drop the input\r\n", ctx->cache_idx, input_item->size, ctx->max_cache_size);
	} else {
		memcpy(ctx->cache + ctx->cache_idx, (void *)input_item->data_addr, input_item->size);
		ctx->cache_idx += input_item->size;
	}

	if (ctx->cache_idx >= ctx->params.channel * ctx->enc_info.frameLength * 2) {
		AACENC_ERROR err;
		AACENC_BufDesc in_buf = { 0 }, out_buf = { 0 };
		AACENC_InArgs in_args = { 0 };
		AACENC_OutArgs out_args = { 0 };

		int in_identifier = IN_AUDIO_DATA;
		int in_size = ctx->params.channel * ctx->enc_info.frameLength * 2;
		int in_elem_size = 2;

		in_args.numInSamples = ctx->params.channel * ctx->enc_info.frameLength;
		in_buf.numBufs = 1;
		in_buf.bufs = (void **) & (ctx->cache);
		in_buf.bufferIdentifiers = (INT *)&in_identifier;
		in_buf.bufSizes = (INT *)&in_size;
		in_buf.bufElSizes = (INT *)&in_elem_size;

		int out_identifier = OUT_BITSTREAM_DATA;
		int out_size = ctx->params.mem_frame_size;
		int out_elem_size = 1;

		out_buf.numBufs = 1;
		out_buf.bufs = (void **) & (output_item->data_addr);
		out_buf.bufferIdentifiers = (INT *)&out_identifier;
		out_buf.bufSizes = (INT *)&out_size;
		out_buf.bufElSizes = (INT *)&out_elem_size;


		err = aacEncEncode(ctx->fdkaac_enc, &in_buf, &out_buf, &in_args, &out_args);
		if (err != AACENC_OK) {
			if (err == AACENC_ENCODE_EOF) {
				printf("AACENC_ENCODE_EOF(0x%x)\r\n", err);
			}
			printf("Encoding failed 0x%x\r\n", err);
		} else {
			frame_size = out_args.numOutBytes;
		}

		ctx->cache_idx -= ctx->params.channel * ctx->enc_info.frameLength * 2;
		if (ctx->cache_idx > 0) {
			memmove(ctx->cache, ctx->cache + ctx->params.channel * ctx->enc_info.frameLength * 2, ctx->cache_idx);
		}
	}

	output_item->size = frame_size;
	output_item->type = AV_CODEC_ID_MP4A_LATM;
	output_item->index = 0;
	return frame_size;
}

static int aacmodule_apply(void *p)
{
	aac_ctx_t *ctx = (aac_ctx_t *)p;
	if (ctx) {
		if (ctx->mem_pool == NULL) {
			mm_printf("[AAC ERR] AAC memory pool not initialed yet\r\n");
			// If memory pool not initialed, force the aac process to stop
			ctx->stop = 1;
			return -1;
		}
		int ret = aachandle_Open(ctx);
		if (ret) {
			printf("[AAC ERR] aachandle_Open fail\r\n");
			// If aachandle_Open fail, force the aac process to stop
			ctx->stop = 1;
			return -1;
		}
		ctx->max_cache_size = ctx->params.channel * ctx->enc_info.frameLength * 2 + 1500;
		ctx->cache = (uint8_t *)malloc(ctx->max_cache_size);	// 1500 max audio page size
		if (!ctx->cache) {
			// This should never happened
			mm_printf("[AAC ERR] AAC cache allocate fail, heap not enough\r\n");
			// If cache allocate fail, force the aac process to stop
			ctx->stop = 1;
			return -1;
			// TODO add handing code
		}
		ctx->stop = 0;
		return 0;
	}
	return -1;
}

int aac_control(void *p, int cmd, int arg)
{
	aac_ctx_t *ctx = (aac_ctx_t *)p;
	int ret = 0;

	switch (cmd) {
	case CMD_AAC_SET_PARAMS:
		memcpy(&ctx->params, ((aac_params_t *)arg), sizeof(aac_params_t));
		break;
	case CMD_AAC_GET_PARAMS:
		memcpy(((aac_params_t *)arg), &ctx->params, sizeof(aac_params_t));
		break;
	case CMD_AAC_SAMPLERATE:
		ctx->params.sample_rate = arg;
		break;
	case CMD_AAC_CHANNEL:
		ctx->params.channel = arg;
		break;
	case CMD_AAC_BITLENGTH:
		//ctx->params.bit_length = arg;
		break;
	case CMD_AAC_MEMORY_SIZE:
		ctx->params.mem_total_size = arg;
		break;
	case CMD_AAC_BLOCK_SIZE:
		ctx->params.mem_block_size = arg;
		break;
	case CMD_AAC_MAX_FRAME_SIZE:
		ctx->params.mem_frame_size = arg;
		break;
	case CMD_AAC_INIT_MEM_POOL:
		ctx->mem_pool = memory_init(ctx->params.mem_total_size, ctx->params.mem_block_size);
		if (ctx->mem_pool == NULL) {
			mm_printf("[AAC ERR] Can't allocate AAC buffer, heap not enough\r\n");
			ret = -1;
		}
		break;
	case CMD_AAC_STOP:
		ctx->stop = 1;
		break;
	case CMD_AAC_RESET:
		ctx->stop = 1;
		aacEncClose(&(ctx->fdkaac_enc));
		ctx->fdkaac_enc = NULL;
		if (ctx->cache) {
			free(ctx->cache);
		}
		ctx->cache_idx = 0;
		ctx->max_cache_size = 0;
		printf("aac reset\r\n");
		ret = aacmodule_apply(ctx);
		break;
	case CMD_AAC_APPLY:
		ret = aacmodule_apply(ctx);
		break;
	}

	return ret;
}

void *aac_destroy(void *p)
{
	aac_ctx_t *ctx = (aac_ctx_t *)p;

	aacEncClose(&(ctx->fdkaac_enc));
	if (ctx) {
		if (ctx->cache) {
			free(ctx->cache);
		}
		ctx->cache_idx = 0;
		if (ctx->mem_pool) {
			memory_deinit(ctx->mem_pool);
		}
		free(ctx);
	}

	return NULL;
}

void *aac_create(void *parent)
{
	aac_ctx_t *ctx = malloc(sizeof(aac_ctx_t));
	if (!ctx) {
		return NULL;
	}
	memset(ctx, 0, sizeof(aac_ctx_t));
	ctx->parent = parent;
	ctx->stop = 1;

	return ctx;
}

void *aac_new_item(void *p)
{
	aac_ctx_t *ctx = (aac_ctx_t *)p;

	return memory_alloc(ctx->mem_pool, ctx->params.mem_frame_size);
}

void *aac_del_item(void *p, void *d)
{
	aac_ctx_t *ctx = (aac_ctx_t *)p;

	memory_free(ctx->mem_pool, d);
	return NULL;
}

void *aac_rsz_item(void *p, void *d, int len)
{
	aac_ctx_t *ctx = (aac_ctx_t *)p;
	return memory_realloc(ctx->mem_pool, d, len);
}

mm_module_t aac_module = {
	.create = aac_create,
	.destroy = aac_destroy,
	.control = aac_control,
	.handle = aac_handle,

	.new_item = aac_new_item,
	.del_item = aac_del_item,
	.rsz_item = aac_rsz_item,

	.output_type = MM_TYPE_ASINK,
	.module_type = MM_TYPE_ADSP,
	.name = "AAC"
};
