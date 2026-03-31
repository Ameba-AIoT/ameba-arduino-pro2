/******************************************************************************
*
* Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
*
******************************************************************************/

#include <stdint.h>
#include "avcodec.h"

#include "memory_encoder.h"
#include "mmf2_module.h"
#include "module_opusc.h"
#include "mmf2_dbg.h"
#include <FreeRTOS.h>
#include <semphr.h>

#define MAX_IDX_FRAME 5
int frame_msec_idx[MAX_IDX_FRAME] = {5, 10, 20, 40, 60};
//xSemaphoreHandle  opus_progress_sema;

//------------------------------------------------------------------------------
/*
static void set_expected_duration(void* p)
{
  	opusc_ctx_t *ctx = (opusc_ctx_t*)p;
  	opus_int32 variable_duration = ctx->params.samples_input;

	if (ctx->params.samples_input==ctx->params.sample_rate/400)
		variable_duration = OPUS_FRAMESIZE_2_5_MS;
	else if (ctx->params.samples_input==ctx->params.sample_rate/200)
		variable_duration = OPUS_FRAMESIZE_5_MS;
	else if (ctx->params.samples_input==ctx->params.sample_rate/100)
		variable_duration = OPUS_FRAMESIZE_10_MS;
	else if (ctx->params.samples_input==ctx->params.sample_rate/50)
		variable_duration = OPUS_FRAMESIZE_20_MS;
	else if (ctx->params.samples_input==ctx->params.sample_rate/25)
		variable_duration = OPUS_FRAMESIZE_40_MS;
	else if (ctx->params.samples_input==3*ctx->params.sample_rate/50)
		variable_duration = OPUS_FRAMESIZE_60_MS;
	else if (ctx->params.samples_input==4*ctx->params.sample_rate/50)
		variable_duration = OPUS_FRAMESIZE_80_MS;
	else if (ctx->params.samples_input==5*ctx->params.sample_rate/50)
		variable_duration = OPUS_FRAMESIZE_100_MS;
	else if (ctx->params.samples_input==5*ctx->params.sample_rate/50)
		variable_duration = OPUS_FRAMESIZE_120_MS;
	else
	  	variable_duration = OPUS_FRAMESIZE_ARG;

	opus_encoder_ctl(ctx->opus_enc, OPUS_SET_EXPERT_FRAME_DURATION(variable_duration));

	opus_encoder_ctl(ctx->opus_enc, OPUS_GET_EXPERT_FRAME_DURATION(&variable_duration));
}
*/

int opusc_handle(void *p, void *input, void *output)
{
	opusc_ctx_t *ctx = (opusc_ctx_t *)p;
	mm_queue_item_t *input_item = (mm_queue_item_t *)input;
	mm_queue_item_t *output_item = (mm_queue_item_t *)output;

	int frame_size = 0;
	int frame_idx = 0;

	if (ctx->stop == 1) {
		//mm_printf("opus encoder stop\r\n");
		return 0;
	}

	output_item->timestamp = input_item->timestamp;
	// set timestamp to 1st sample (cache head)
	output_item->timestamp -= 1000 * (ctx->cache_idx / 2) / ctx->params.sample_rate;

	if (ctx->cache_idx + input_item->size >= ctx->max_cache_size) {
		mm_printf("[OPUSC WARN] opusd data cache overflow %d + %d >= %d, drop the input\r\n", ctx->cache_idx, input_item->size, ctx->max_cache_size);
	} else {
		memcpy(ctx->cache + ctx->cache_idx, (void *)input_item->data_addr, input_item->size);
		ctx->cache_idx += input_item->size;
	}

	if (ctx->params.use_framesize == 0) {
		while (1) {
			if (frame_idx >= MAX_IDX_FRAME) {
				// if the frame_idx is larger than the MAX size, use the max size to encode
				frame_idx = MAX_IDX_FRAME - 1;
				break;
			} else if (ctx->cache_idx < (frame_msec_idx[frame_idx]*ctx->params.sample_rate / 1000 * ctx->params.bit_length / 8)) {
				// select the max length, achieve the acceptable frame length
				frame_idx --;
				break;
			}
			frame_idx ++;
		}

		if (frame_idx >= 0) {
			ctx->params.samples_input = frame_msec_idx[frame_idx] * ctx->params.sample_rate / 1000;
			//set_expected_duration(ctx);

			frame_size = opus_encode(ctx->opus_enc, (const opus_int16 *)ctx->cache, ctx->params.samples_input, (unsigned char *)output_item->data_addr,
									 ctx->params.max_bytes_output);

			ctx->cache_idx -= ctx->params.samples_input * 2;
			if (ctx->cache_idx > 0) {
				memmove(ctx->cache, ctx->cache + ctx->params.samples_input * 2, ctx->cache_idx);
			}
			if (frame_size <= 1) { //frame_size => negative error ,1 DTX (no-need)
				frame_size = 0;
				ctx->cache_idx -= ctx->params.samples_input * 2;
			}
		} else {
			frame_size = 0;
		}
	} else {
		if (ctx->cache_idx >= ctx->params.use_framesize * ctx->params.sample_rate / 1000 * ctx->params.bit_length / 8) {
			ctx->params.samples_input = ctx->params.use_framesize * ctx->params.sample_rate / 1000;
			frame_size = opus_encode(ctx->opus_enc, (const opus_int16 *)ctx->cache, ctx->params.samples_input, (unsigned char *)output_item->data_addr,
									 ctx->params.max_bytes_output);
			ctx->cache_idx -= ctx->params.samples_input * 2;
			if (ctx->cache_idx > 0) {
				memmove(ctx->cache, ctx->cache + ctx->params.samples_input * 2, ctx->cache_idx);
			}
			if (frame_size <= 1) { //frame_size => negative error ,1 DTX (no-need)
				frame_size = 0;
				ctx->cache_idx -= ctx->params.samples_input * 2;
			}
		} else {
			frame_size = 0;
		}
	}

	int new_frame_size;
	//mm_printf("opus encode frame_size = %d\r\n", frame_size);

	if (frame_size > 0) {
		if (ctx->padding_size >= frame_size) {
			new_frame_size = ctx->padding_size;
		} else {
			new_frame_size = (frame_size / 8 + (frame_size % 8 == 0 ? 0 : 1)) * 8;
		}
		if (opus_packet_pad((unsigned char *)output_item->data_addr, frame_size, new_frame_size)) {
			new_frame_size = 0;
		}
	} else {
		new_frame_size = 0;
	}

	output_item->size = new_frame_size;
	output_item->type = AV_CODEC_ID_OPUS;
	output_item->index = 0;
	return new_frame_size;
}

int opusc_control(void *p, int cmd, int arg)
{
	opusc_ctx_t *ctx = (opusc_ctx_t *)p;
	int ret;

	switch (cmd) {
	case CMD_OPUSC_SET_PARAMS:
		memcpy(&ctx->params, ((opusc_params_t *)arg), sizeof(opusc_params_t));
		ctx->params.max_bytes_output = 1024 * sizeof(int16_t);
		break;
	case CMD_OPUSC_GET_PARAMS:
		memcpy(((opusc_params_t *)arg), &ctx->params, sizeof(opusc_params_t));
		break;
	case CMD_OPUSC_SAMPLERATE:
		ctx->params.sample_rate = arg;
		break;
	case CMD_OPUSC_CHANNEL:
		ctx->params.channel = arg;
		break;
	case CMD_OPUSC_BITLENGTH:
		ctx->params.bit_length = arg;
		break;
	case CMD_OPUSC_STOP:
		ctx->stop = 1;
		break;
	case CMD_OPUSC_SET_PADDING_SIZE:
		ctx->padding_size = arg;
		break;
	case CMD_OPUSC_RESET:
		ctx->stop = 1;
		if (ctx->cache) {
			free(ctx->cache);
		}
		ctx->cache_idx = 0;
		ctx->max_cache_size = 0;
		printf("opusc reset\r\n");
	case CMD_OPUSC_APPLY:
		//Coding mode (OPUS_APPLICATION_VOIP/OPUS_APPLICATION_AUDIO/OPUS_APPLICATION_RESTRICTED_LOWDELAY)
		ret = opus_encoder_init(ctx->opus_enc, ctx->params.sample_rate, ctx->params.channel, ctx->params.opus_application);
		if (ret != 0) {
			mm_printf("[OPUSC ERR] Opusc init fail %d\n\r", ret);
			//while (1);
			// TODO add handing code
			return -1;
		}

		/*
		opus_progress_sema = xSemaphoreCreateBinary();
		if(!opus_progress_sema)
			goto opus_control_fail;
		if(opus_progress_sema)
			xSemaphoreGive(opus_progress_sema);
		*/

		opus_encoder_ctl(ctx->opus_enc, OPUS_SET_BITRATE(ctx->params.bitrate));
		opus_encoder_ctl(ctx->opus_enc, OPUS_SET_COMPLEXITY(ctx->params.complexity));
		opus_encoder_ctl(ctx->opus_enc, OPUS_SET_LSB_DEPTH(ctx->params.bit_length));
		opus_encoder_ctl(ctx->opus_enc, OPUS_SET_FORCE_CHANNELS(1));
		opus_encoder_ctl(ctx->opus_enc, OPUS_SET_PREDICTION_DISABLED(0));

		if (ctx->params.bitrate > 0) {
			opus_encoder_ctl(ctx->opus_enc, OPUS_SET_BITRATE(ctx->params.bitrate));
		}
		opus_encoder_ctl(ctx->opus_enc, OPUS_SET_VBR(ctx->params.enable_vbr));
		opus_encoder_ctl(ctx->opus_enc, OPUS_SET_VBR_CONSTRAINT(ctx->params.vbr_constraint));
		opus_encoder_ctl(ctx->opus_enc, OPUS_SET_PACKET_LOSS_PERC(ctx->params.packetLossPercentage));

		//opus_encoder_ctl(ctx->opus_enc, OPUS_SET_BANDWIDTH_REQUEST()); //OPUS_BANDWIDTH_NARROWBAND(4K)/MEDIUMBAND(6K)/WIDEBAND(8K)/SUPERWIDEBAND(12K)/FULLBAND(20K)
		//opus_encoder_ctl(ctx->opus_enc, OPUS_SET_MAX_BANDWIDTH(max_bw));
		//opus_encoder_ctl(ctx->opus_enc, OPUS_SET_INBAND_FEC(inband_fec));
		//opus_encoder_ctl(ctx->opus_enc, OPUS_SET_DTX(dtx));
		//opus_encoder_ctl(ctx->opus_enc, OPUS_SET_SIGNAL(signal_type));//OPUS_AUTO (default), OPUS_SIGNAL_VOICE, or OPUS_SIGNAL_MUSIC
		ctx->max_cache_size = 120 * ctx->params.sample_rate / 1000 * ctx->params.bit_length / 8;
		ctx->cache = (uint8_t *)malloc(ctx->max_cache_size);	// max audio page size 1500
		if (!ctx->cache) {
			// This should never happened
			mm_printf("[OPUSC ERR] Opusc cache Output memory, heap not enough\n\r");
			ctx->stop = 1;
			return -1;
			// TODO add handing code
		}
		ctx->stop = 0;
		break;
	}
//opus_control_fail:
	return 0;
}

void *opusc_destroy(void *p)
{
	opusc_ctx_t *ctx = (opusc_ctx_t *)p;

	if (ctx) {
		if (ctx->opus_enc) {
			opus_encoder_destroy(ctx->opus_enc);
		}

		if (ctx->cache) {
			free(ctx->cache);
		}

		free(ctx);
	}

	return NULL;
}

void *opusc_create(void *parent)
{
	int error_code;
	opusc_ctx_t *ctx = malloc(sizeof(opusc_ctx_t));
	if (!ctx) {
		return NULL;
	}
	memset(ctx, 0, sizeof(opusc_ctx_t));
	ctx->parent = parent;
	ctx->stop = 1;

	//the Opus encoder can switch to a lower audio bandwidth(?) or number of channels
	//Number of channels (1 or 2) in input signal
	mm_printf("OPUS encoder needs bytes: %d\r\n", opus_encoder_get_size(1));
	ctx->opus_enc = opus_encoder_create(48000, 1, OPUS_APPLICATION_AUDIO, &error_code);
	if (error_code != 0) { //OPUS_OK
		printf("error_code = %d\r\n", error_code);
		goto opusc_create_fail;
	}

	return ctx;
opusc_create_fail:
	if (ctx) {
		free(ctx);
	}
	return NULL;
}

void *opusc_new_item(void *p)
{

	return malloc(1 * 1024 * sizeof(int16_t));
}

void *opusc_del_item(void *p, void *d)
{
	if (d) {
		free(d);
	}
	return NULL;
}

mm_module_t opusc_module = {
	.create = opusc_create,
	.destroy = opusc_destroy,
	.control = opusc_control,
	.handle = opusc_handle,

	.new_item = opusc_new_item,
	.del_item = opusc_del_item,

	.output_type = MM_TYPE_ASINK,
	.module_type = MM_TYPE_ADSP,
	.name = "OPUSC"
};
