/******************************************************************************
*
* Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
*
******************************************************************************/
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "mmf2_module.h"
#include "module_aad.h"
#include "FDK_audio.h"

#ifndef AAC_MAX_NCHANS
#define AAC_MAX_NCHANS 2
#endif
#ifndef AAC_MAX_NSAMPS
#define AAC_MAX_NSAMPS 2048
#endif


// AAD raw type config function
#define SHOW_AAD_CONFIG 0
#define BYTE_NUMBIT 8           // bits in byte (char)
#define MAX_AADCONFIG_SIZE 10   // 80 bits in Audio Specific Config
static const uint32_t AADSamplingRateTable[] =
{ 96000, 88200, 64000, 48000, 44100, 32000, 24000, 22050, 16000, 12000, 11025, 8000, 7350, 0, 0, 0};
static uint32_t sampleratetable_size = sizeof(AADSamplingRateTable) / sizeof(uint32_t);
#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

static int AADWriteByte(AAD_Config *aad_conf, uint32_t data, uint32_t numBit)
{
	uint32_t numUsed, idx;

	idx = (aad_conf->currentBit / BYTE_NUMBIT) % aad_conf->size;
	numUsed = aad_conf->currentBit % BYTE_NUMBIT;
	aad_conf->data[idx] |= (data & ((1 << numBit) - 1)) << (BYTE_NUMBIT - numUsed - numBit);
	aad_conf->currentBit += numBit;
	aad_conf->numBit = aad_conf->currentBit;

	return 0;
}

static int AADPutBit(AAD_Config *aad_conf, uint32_t data, uint32_t numBit)
{
	uint32_t num, maxNum, curNum;
	uint32_t bits;

	if (numBit == 0) {
		return 0;
	}

	/* write bits in packets according to buffer byte boundaries */
	num = 0;
	maxNum = BYTE_NUMBIT - aad_conf->currentBit % BYTE_NUMBIT;
	while (num < numBit) {
		curNum = min(numBit - num, maxNum);
		bits = data >> (numBit - num - curNum);
		if (AADWriteByte(aad_conf, bits, curNum)) {
			return 1;
		}
		num += curNum;
		maxNum = BYTE_NUMBIT;
	}

	return 0;
}

static AAD_Config *CreateAADConfig(void)
{
	//Initial the AAD config
	AAD_Config *aad_conf = malloc(sizeof(AAD_Config));
	if (aad_conf) {
		aad_conf->size = MAX_AADCONFIG_SIZE;
		aad_conf->data = malloc(sizeof(uint8_t) * aad_conf->size);
		if (!aad_conf->data) {
			free(aad_conf);
			return NULL;
		}
		memset(aad_conf->data, 0, sizeof(uint8_t) * aad_conf->size);
		aad_conf->numBit = 0;
		aad_conf->currentBit = 0;

		//Todo:
		//extend the audio specific config with var bits
		//var bits: AOT Specific Config
		return aad_conf;
	} else {
		return NULL;
	}
}

static void Reset_AADConfig(AAD_Config *aad_conf)
{
	if (aad_conf) {
		aad_conf->size = MAX_AADCONFIG_SIZE;
		memset(aad_conf->data, 0, sizeof(uint8_t) * aad_conf->size);
		aad_conf->numBit = 0;
		aad_conf->currentBit = 0;
	}
}

//create Audio Specific Config (ASC)
static void Set_AADConfig(AAD_Config *aad_conf, AUDIO_OBJECT_TYPE aad_objtype, uint32_t aad_samplerate, uint32_t aad_channel)
{
	uint32_t input_aad_samplerate = 0;
	int input_samplerate_index = 0;
	int output_samplerate_index = 0;
	if (aad_conf) {
		//5 bits: object type
		if (aad_objtype <= AOT_ESCAPE) {
			//Signal AOT uses less than 5 bits
			AADPutBit(aad_conf, aad_objtype, 5);
		} else {
			//Signal AOT uses more than 5 bits
			//set first 5 bits to 1 (==31)
			AADPutBit(aad_conf, 0x1F, 5);
			//6 bits: object type - 32
			AADPutBit(aad_conf, (aad_objtype - 32), 6);
		}
		//4 bits: frequency index
		//search the samplerate is in index or not
		if (aad_objtype == AOT_SBR || aad_objtype == AOT_PS) {
			input_aad_samplerate = aad_samplerate / 2;
		} else {
			input_aad_samplerate = aad_samplerate;
		}
		for (input_samplerate_index = 0; input_samplerate_index < sampleratetable_size; input_samplerate_index++) {
			if (input_aad_samplerate == AADSamplingRateTable[input_samplerate_index]) {
				break;
			}
		}
		if (input_aad_samplerate && (input_samplerate_index != sampleratetable_size)) {
			AADPutBit(aad_conf, input_samplerate_index, 4);
		} else {
			//set first 4 bits to 1 (==15)
			AADPutBit(aad_conf, 0xF, 4);
			//direct set the aad samplrate
			AADPutBit(aad_conf, input_aad_samplerate, 24);
		}
		//4 bits: channel configuration
		//Todo: transfer to AUDIO_CHANNEL_TYPE to support more channel
		AADPutBit(aad_conf, aad_channel, 4);

		if (aad_objtype == AOT_SBR || aad_objtype == AOT_PS) {
			//4 bits: extension frequency index (output sample rate)
			//search the samplerate is in index or not
			for (output_samplerate_index = 0; output_samplerate_index < sampleratetable_size; output_samplerate_index++) {
				if (aad_samplerate == AADSamplingRateTable[output_samplerate_index]) {
					break;
				}
			}
			if (aad_samplerate && (output_samplerate_index != sampleratetable_size)) {
				AADPutBit(aad_conf, output_samplerate_index, 4);
			} else {
				//set first 4 bits to 1 (==15)
				AADPutBit(aad_conf, 0xF, 4);
				//direct set the aad samplrate
				AADPutBit(aad_conf, aad_samplerate, 24);
			}
			//Now only verify HE-AAC v1 (LC + SBR), HE-AAC v2 (LC + SBR + PS)
			AADPutBit(aad_conf, AOT_AAC_LC, 5);
			// AOT_ER_BSAC need add 4 bits channle information
		}

		//Todo:
		//var bits: AOT Specific Config
	}
#if defined(SHOW_AAD_CONFIG) && SHOW_AAD_CONFIG
	printf("AAD Config\r\n");
	uint8_t *aadconf = (uint8_t *)aad_conf->data;
	for (int i = 0; i < aad_conf->size; i++) {
		printf("%02x,", aadconf[i]);
	}
	printf("\r\n");
#endif
}

static AAD_Config *CloseAADConfig(AAD_Config *aad_conf)
{
	if (aad_conf) {
		if (aad_conf->data) {
			free(aad_conf->data);
		}
		free(aad_conf);
	}
	return NULL;
}

//------------------------------------------------------------------------------
static void printf_aac_info(CStreamInfo *aacinfo)
{
	if (aacinfo) {
		printf("AAC Infomation:\r\n");
		printf("sampleRate: %d\r\n", aacinfo->sampleRate);
		printf("frameSize: %d\r\n", aacinfo->frameSize);
		printf("numChannels: %d\r\n", aacinfo->numChannels);
		printf("aacSampleRate: %d\r\n", aacinfo->aacSampleRate);
		printf("profile: %d\r\n", aacinfo->profile);
		printf("aot: %d\r\n", aacinfo->aot);
		printf("channelConfig: %d\r\n", aacinfo->channelConfig);
		printf("bitRate: %d\r\n", aacinfo->bitRate);
		printf("aacSamplesPerFrame: %d\r\n", aacinfo->aacSamplesPerFrame);
		printf("aacNumChannels: %d\r\n", aacinfo->aacNumChannels);
		printf("extAot: %d\r\n", aacinfo->extAot);
		printf("extSamplingRate: %d\r\n", aacinfo->extSamplingRate);
		printf("outputDelay: %d\r\n", aacinfo->outputDelay);
		printf("flags: %d\r\n", aacinfo->flags);
		printf("epConfig: %d\r\n", aacinfo->epConfig);
		printf("numLostAccessUnits: %d\r\n", aacinfo->numLostAccessUnits);
		printf("numTotalBytes: %lld\r\n", aacinfo->numTotalBytes);
		printf("numBadBytes: %lld\r\n", aacinfo->numBadBytes);
		printf("numTotalAccessUnits: %lld\r\n", aacinfo->numTotalAccessUnits);
		printf("numBadAccessUnits: %lld\r\n", aacinfo->numBadAccessUnits);
		printf("drcProgRefLev: %d\r\n", aacinfo->drcProgRefLev);
		printf("drcPresMode: %d\r\n", aacinfo->drcPresMode);
	}
}


// AAD packet parser function
static void aad_rtp_raw_parser(void *p, void *input, int len)
{
	aad_ctx_t *ctx = (aad_ctx_t *)p;

	// parse input data to data cache, skip 4 bytes
	memcpy(ctx->data_cache + ctx->data_cache_len, (void *)((uint32_t)input + 4), len - 4);
	ctx->data_cache_len += len - 4;
}

static void aad_bypass_parser(void *p, void *input, int len)
{
	aad_ctx_t *ctx = (aad_ctx_t *)p;

	memcpy(ctx->data_cache + ctx->data_cache_len, input, len);
	ctx->data_cache_len += len;
}

//static void aad_ts_parser(void *p, void *input, int len)
//{
//mm_printf("[AAD ERR] Not support TS parser\n\r");
//abort();
//}

//AAD open function
static int aadhandle_Open(aad_ctx_t *ctx)
{
	int ret = 0;

	switch (ctx->params.object_type) {
	case AAD_AOT_LC:
	case AAD_AOT_SBR:
	case AAD_AOT_PS:
		if (ctx->params.trans_type == AAD_TYPE_ADTS) {
			ctx->trans_type = TT_MP4_ADTS;
			ctx->parser = aad_bypass_parser;
		} else if (ctx->params.trans_type == AAD_TYPE_RAW) {
			ctx->trans_type = TT_MP4_RAW;
			ctx->parser = aad_bypass_parser;
		} else if (ctx->params.trans_type == AAD_TYPE_RTP_RAW) {
			ctx->trans_type = TT_MP4_RAW;
			ctx->parser = aad_rtp_raw_parser;
		} else {
			printf("unsupport aad transport type %d\r\n", ctx->params.trans_type);
			ret = -1;
			goto endofopen;
		}
		break;
	case AAD_AOT_ER_LD:
	case AAD_AOT_ER_ELD:
		if (ctx->params.trans_type == AAD_TYPE_ADTS) {
			printf("ADTS only support LC based audio object type\r\n");
			ret = -1;
			goto endofopen;
		} else if (ctx->params.trans_type == AAD_TYPE_RAW) {
			ctx->trans_type = TT_MP4_RAW;
			ctx->parser = aad_bypass_parser;
		} else if (ctx->params.trans_type == AAD_TYPE_RTP_RAW) {
			ctx->trans_type = TT_MP4_RAW;
			ctx->parser = aad_rtp_raw_parser;
		} else {
			printf("unsupport aad transport type %d\r\n", ctx->params.trans_type);
			ret = -1;
			goto endofopen;
		}
		break;
	default:
		printf("unknown aad audio object type %d\r\n", ctx->params.trans_type);
		ret = -1;
		goto endofopen;
		break;
	}
	ctx->object_type = ctx->params.object_type;
	ctx->aad = aacDecoder_Open(ctx->trans_type, 1);
	aacDecoder_SetParam(ctx->aad, AAC_PCM_MAX_OUTPUT_CHANNELS, 1);
	//If the transport type is raw type, create the config for decode
	if (ctx->trans_type == TT_MP4_RAW) {
		Reset_AADConfig(ctx->aadconfig);
		Set_AADConfig(ctx->aadconfig, ctx->object_type, ctx->params.sample_rate, ctx->params.channel);
		AAC_DECODER_ERROR err = aacDecoder_ConfigRaw(ctx->aad, &(ctx->aadconfig->data), &(ctx->aadconfig->size));
		if (err) {
			printf("AAD aacDecoder_ConfigRaw err = 0x%x\r\n", err);
			ret = -1;
			goto endofopen;
		}
#if defined(SHOW_AAD_CONFIG) && SHOW_AAD_CONFIG
		printf_aac_info(aacDecoder_GetStreamInfo(ctx->aad));
#endif
	}

endofopen:
	return ret;
}

int aad_handle(void *p, void *input, void *output)
{
	aad_ctx_t *ctx = (aad_ctx_t *)p;
	mm_queue_item_t *input_item = (mm_queue_item_t *)input;
	mm_queue_item_t *output_item = (mm_queue_item_t *)output;

	uint8_t *inbuf;
	uint32_t bytesLeft, byteValid;
	int ret = 0;
	int process_index = 0;

	if (ctx->stop == 1) {
		//printf("stop\r\n");
		return 0;
	}

	if (input_item->size == 0)	{
		return -1;
	}

	if (ctx->data_cache_len + input_item->size >= ctx->data_cache_size) {
		// This should never happened
		mm_printf("aac data cache overflow %d %d\r\n", ctx->data_cache_len, input_item->size);
		return -1;
	}

	ctx->parser((void *)ctx, (void *)input_item->data_addr, input_item->size);

	inbuf = ctx->data_cache;
	bytesLeft = ctx->data_cache_len;
	byteValid = bytesLeft;

	//fill in the aac frames
	while (bytesLeft) {
		//fill the input buffer into the internal buffer
		//AAC decoder handle, pBuffer, bufferSize(the actual size in pBuffer), bytesValid(will be update)
		ret = aacDecoder_Fill(ctx->aad, &inbuf, &bytesLeft, &byteValid);
		//printf("bytesLeft = %d, byteValid = %d\r\n", bytesLeft, byteValid);

		if (ret != AAC_DEC_OK) {
			mm_printf("Filled failed:0x%x\r\n", ret);
			break;
		} else if (bytesLeft == byteValid) {
			// the aac decoder internal buffer is full, keeping the external buffer
			break;
		} else {
			memmove(inbuf, inbuf + ctx->data_cache_len - byteValid, byteValid);
			ctx->data_cache_len = byteValid;
		}
		ret = aacDecoder_DecodeFrame(ctx->aad, (short *)ctx->decode_buf, AAC_MAX_NCHANS * AAC_MAX_NSAMPS * sizeof(int16_t) * 2, ctx->aadflag);
		if (ret == AAC_DEC_OK) {
			CStreamInfo *frameInfo = aacDecoder_GetStreamInfo(ctx->aad);
			//printf_aac_info(aacDecoder_GetStreamInfo(ctx->aad));

			//if the next frame will exceed output buffer, stop the process
			if ((process_index + frameInfo->numChannels * frameInfo->frameSize * sizeof(int16_t)) > (AAC_MAX_NSAMPS * sizeof(int16_t) * 2)) {
				break;
			}
			// TODO: it might need resample if use different sample rate & channel number
			memcpy((void *)(output_item->data_addr + process_index), ctx->decode_buf, frameInfo->numChannels * frameInfo->frameSize * sizeof(int16_t));
			process_index += frameInfo->numChannels * frameInfo->frameSize * sizeof(int16_t);
		} else {
			// if decode successfully or the bit is not enough keep the loop
			if (ret != AAC_DEC_NOT_ENOUGH_BITS) {
				mm_printf("decode err:0x%x\r\n", ret);
#if defined(SHOW_AAD_CONFIG) && SHOW_AAD_CONFIG
				printf_aac_info(aacDecoder_GetStreamInfo(ctx->aad));
#endif
				break;
			}

		}
		bytesLeft = byteValid;
	}
	//printf("process_index = %d\r\n", process_index);

	output_item->size = process_index;
	output_item->timestamp = input_item->timestamp;
	output_item->index = 0;
	output_item->type = 0;

	return output_item->size;
}

static int aadmodule_apply(void *p)
{
	aad_ctx_t *ctx = (aad_ctx_t *)p;
	int ret = 0;
	if (ctx) {
		ret = aadhandle_Open(ctx);
		if (ret) {
			mm_printf("[AAD ERR] aadhandle_Open fail\r\n");
			ctx->stop = 1;
		} else {
			ctx->stop = 0;
		}
		return ret;
	}
	return -1;
}

int aad_control(void *p, int cmd, int arg)
{
	aad_ctx_t *ctx = (aad_ctx_t *)p;
	int ret = 0;

	switch (cmd) {
	case CMD_AAD_SET_PARAMS:
		memcpy(&ctx->params, ((aad_params_t *)arg), sizeof(aad_params_t));
		break;
	case CMD_AAD_GET_PARAMS:
		memcpy(((aad_params_t *)arg), &ctx->params, sizeof(aad_params_t));
		break;
	case CMD_AAD_SAMPLERATE:
		ctx->params.sample_rate = arg;
		break;
	case CMD_AAD_CHANNEL:
		ctx->params.channel = arg;
		break;
	case CMD_AAD_TRANSPORT_TYPE:
		ctx->params.trans_type = arg;
		break;
	case CMD_AAD_STOP:
		ctx->stop = 1;
		break;
	case CMD_AAD_RESET:
		ctx->stop = 1;
		aacDecoder_Close(ctx->aad);
		ctx->aad = NULL;
		ctx->data_cache_len = 0;
		ret = aadmodule_apply(ctx);
		break;
	case CMD_AAD_APPLY:
		ret = aadmodule_apply(ctx);
		break;
	}

	return ret;
}

void *aad_destroy(void *p)
{
	aad_ctx_t *ctx = (aad_ctx_t *)p;

	if (ctx && ctx->aadconfig) {
		ctx->aadconfig = CloseAADConfig(ctx->aadconfig);
	}

	if (ctx && ctx->aad) {
		aacDecoder_Close(ctx->aad);
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

void *aad_create(void *parent)
{
	aad_ctx_t *ctx = (aad_ctx_t *)malloc(sizeof(aad_ctx_t));
	if (!ctx) {
		return NULL;
	}
	memset(ctx, 0, sizeof(aad_ctx_t));
	ctx->parent = parent;
	ctx->stop = 1;

	ctx->data_cache_size = 4096;
	ctx->data_cache = malloc(ctx->data_cache_size);
	if (!ctx->data_cache) {
		goto aad_create_fail;
	}
	memset(ctx->data_cache, 0, ctx->data_cache_size);
	// AAC_MAX_NCHANS (2) AAC_MAX_NSAMPS (1024) defined in aacdec.h
	ctx->decode_buf = malloc(AAC_MAX_NCHANS * AAC_MAX_NSAMPS * sizeof(int16_t) * 2);
	if (!ctx->decode_buf) {
		goto aad_create_fail;
	}
	memset(ctx->decode_buf, 0, AAC_MAX_NCHANS * AAC_MAX_NSAMPS * sizeof(int16_t) * 2);
	ctx->aadconfig = CreateAADConfig();
	if (!ctx->aadconfig) {
		goto aad_create_fail;
	}

	ctx->data_cache_len = 0;
	return ctx;

aad_create_fail:
	aad_destroy((void *)ctx);
	return NULL;
}

void *aad_new_item(void *p)
{
	//aad_ctx_t *ctx = (aad_ctx_t *)p;

	return malloc(AAC_MAX_NCHANS * AAC_MAX_NSAMPS * sizeof(int16_t) * 2);
}

void *aad_del_item(void *p, void *d)
{
	//aad_ctx_t *ctx = (aad_ctx_t *)p;

	if (d) {
		free(d);
	}
	return NULL;
}


mm_module_t aad_module = {
	.create = aad_create,
	.destroy = aad_destroy,
	.control = aad_control,
	.handle = aad_handle,

	.new_item = aad_new_item,
	.del_item = aad_del_item,

	.output_type = MM_TYPE_ASINK | MM_TYPE_ADSP,
	.module_type = MM_TYPE_ADSP,
	.name = "AAD"
};
