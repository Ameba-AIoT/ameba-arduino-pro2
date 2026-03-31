/******************************************************************************
*
* Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
*
* Licensed under the Apache License, Version 2.0 (the License); you may
* not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an AS IS BASIS, WITHOUT
* WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
******************************************************************************/
#include <stdint.h>
#include <string.h>
#include "avcodec.h"
#include "mmf2_module.h"
#include "module_fmp4.h"
#include "mov-buffer.h"
//------------------------------------------------------------------------------
#define BUFFER_SIZE_BY_BITRATE(n)	(n)*1024*1024/8

static void h264_fmp4_write(void *param, const void *data, int bytes);
static void aac_fmp4_write(void *param, const uint8_t *ptr, int bytes);

int fmp4_handle(void *p, void *input, void *output)
{
	int ret = 0;
	fmp4_ctx_t *ctx = (fmp4_ctx_t *)p;
	mm_queue_item_t *input_item = (mm_queue_item_t *)input;

	if (input_item->type == AV_CODEC_ID_H264) {
		ctx->mov_h264_ctx.ptr = (uint8_t *)input_item->data_addr;
		ctx->mov_h264_ctx.pts = (uint32_t)input_item->timestamp;
		ctx->mov_h264_ctx.dts = (uint32_t)input_item->timestamp;
		//printf("\r\nVideo timestamp = %d", ctx->mov_h264_ctx.pts);
		h264_fmp4_write(ctx, (uint8_t *)input_item->data_addr, input_item->size);
	} else if (input_item->type == AV_CODEC_ID_MP4A_LATM) {
		ctx->mov_aac_ctx.pts = (uint32_t)input_item->timestamp;
		//printf("\r\nAudio timestamp = %d", ctx->mov_aac_ctx.pts);
		aac_fmp4_write(ctx, (uint8_t *)input_item->data_addr, input_item->size);
	}
	return ret;
}

static void h264_fmp4_write(void *param, const void *data, int bytes)
{
	fmp4_ctx_t *ctx = (fmp4_ctx_t *)param;

	int vcl = 0;
	int update = 0;
	int n = h264_annexbtomp4(&ctx->mov_h264_ctx.avc, data, bytes, ctx->s_buffer, ctx->s_buffer_len, &vcl, &update);

	if (ctx->mov_h264_ctx.track < 0) {
		if (ctx->mov_h264_ctx.avc.nb_sps < 1 || ctx->mov_h264_ctx.avc.nb_pps < 1) {
			//ctx->ptr = end;
			printf("waiting for sps/pps\r\n");
			return;
		}

		int extra_data_size = mpeg4_avc_decoder_configuration_record_save(&ctx->mov_h264_ctx.avc, ctx->s_extra_data, ctx->s_extra_data_len);
		if (extra_data_size <= 0) {
			// invalid AVCC
			printf("error: invalid AVCC\r\n");
			return;
		}

		// TODO: waiting for key frame ???
		ctx->mov_h264_ctx.track = fmp4_writer_add_video(ctx->fmp4, MOV_OBJECT_H264, ctx->mov_h264_ctx.width, ctx->mov_h264_ctx.height, ctx->s_extra_data,
								  extra_data_size);
		if (ctx->mov_h264_ctx.track < 0) {
			printf("error: fmp4 writer add video fail\r\n");
			return;
		}

		ctx->add_video_track_done = 1;
	}

	if (ctx->add_video_track_done && ctx->add_audio_track_done) {
		fmp4_writer_write(ctx->fmp4, ctx->mov_h264_ctx.track, ctx->s_buffer, n, ctx->mov_h264_ctx.pts, ctx->mov_h264_ctx.dts, 1 == vcl ? MOV_AV_FLAG_KEYFREAME : 0);
	}

}

static void aac_fmp4_write(void *param, const uint8_t *ptr, int bytes)
{
	fmp4_ctx_t *ctx = (fmp4_ctx_t *)param;

	int rate = 1;
	struct mpeg4_aac_t aac;

	uint8_t *end = (uint8_t *)(ptr + bytes);

	while (ptr + 7 < end) {
		mpeg4_aac_adts_load(ptr, end - ptr, &aac);
		if (-1 == ctx->mov_aac_ctx.track) {
			int extra_data_size = mpeg4_aac_audio_specific_config_save(&aac, ctx->s_extra_data, ctx->s_extra_data_len);
			if (extra_data_size <= 0) {
				printf("error: invalid AAC\r\n");
				return;
			}
			rate = mpeg4_aac_audio_frequency_to((enum mpeg4_aac_frequency)aac.sampling_frequency_index);
			if (rate == 0) {
				printf("error: aac rate is 0\r\n");
				return;
			}
			ctx->mov_aac_ctx.track = fmp4_writer_add_audio(ctx->fmp4, MOV_OBJECT_AAC, aac.channel_configuration, 16, rate, ctx->s_extra_data, extra_data_size);
			if (ctx->mov_aac_ctx.track < 0) {
				printf("error: fmp4 writer add audio fail\r\n");
				return;
			}

			ctx->add_audio_track_done = 1;
		}

		int framelen = ((ptr[3] & 0x03) << 11) | (ptr[4] << 3) | (ptr[5] >> 5);
		if (ctx->add_video_track_done && ctx->add_audio_track_done) {
			fmp4_writer_write(ctx->fmp4, ctx->mov_aac_ctx.track, ptr + 7, framelen - 7, ctx->mov_aac_ctx.pts, ctx->mov_aac_ctx.pts, 0);
		}
		ptr += framelen;
	}

}

static int mov_file_read(void *fp, void *data, uint64_t bytes)
{
	if (bytes == fread(data, 1, bytes, (FILE *)fp)) {
		return 0;
	}
	return 0 != ferror((FILE *)fp) ? ferror((FILE *)fp) : -1 /*EOF*/;
}

static int mov_file_write(void *fp, const void *data, uint64_t bytes)
{
	return bytes == fwrite(data, 1, bytes, (FILE *)fp) ? 0 : ferror((FILE *)fp);
}

static int mov_file_seek(void *fp, uint64_t offset)
{
	return fseek((FILE *)fp, offset, SEEK_SET);
}

static uint64_t mov_file_tell(void *fp)
{
	return ftell((FILE *)fp);
}

const struct mov_buffer_t *mov_file_buffer(void)
{
	static struct mov_buffer_t s_io = {
		mov_file_read,
		mov_file_write,
		mov_file_seek,
		mov_file_tell,
	};
	return &s_io;
}

int fmp4_control(void *p, int cmd, int arg)
{
	fmp4_ctx_t *ctx = (fmp4_ctx_t *)p;

	switch (cmd) {
	case CMD_FMP4_SET_WIDTH:
		ctx->mov_h264_ctx.width = (int)arg;
		break;
	case CMD_FMP4_SET_HEIGHT:
		ctx->mov_h264_ctx.height = (int)arg;
		break;
	case CMD_FMP4_SET_FILENAME:
		memset(ctx->fmp4_ram_filename, 0x00, sizeof(ctx->fmp4_ram_filename));
		memcpy((char *)ctx->fmp4_ram_filename, (char *)arg, strlen((char *)arg));
		break;
	case CMD_FMP4_FILE_OPEN:
		ctx->wfp = fopen(ctx->fmp4_ram_filename, "wb+");
		if (ctx->wfp == NULL) {
			printf("Fail to open file\r\n");
			return -1;
		}
		ctx->fmp4 = fmp4_writer_create(mov_file_buffer(), ctx->wfp, MOV_FLAG_FASTSTART);

		ctx->mov_h264_ctx.track = -1;
		ctx->mov_aac_ctx.track = -1;

		ctx->add_audio_track_done = 0;
		ctx->add_video_track_done = 0;
		break;
	case CMD_FMP4_FILE_CLOSE:
		if (ctx->fmp4) {
			fmp4_writer_destroy(ctx->fmp4);
			ctx->fmp4 = NULL;
		}
		if (ctx->wfp) {
			fclose(ctx->wfp);
			ctx->wfp = NULL;
		}
		ctx->add_audio_track_done = 0;
		ctx->add_video_track_done = 0;
		break;
	case CMD_FMP4_APPLY:

		break;
	default:
		break;
	}

	return 0;
}

void *fmp4_destroy(void *p)
{
	fmp4_ctx_t *ctx = (fmp4_ctx_t *)p;

	if (ctx) {
		if (ctx->s_buffer) {
			free(ctx->s_buffer);
			ctx->s_buffer = NULL;
		}
		if (ctx->s_extra_data) {
			free(ctx->s_extra_data);
			ctx->s_extra_data = NULL;
		}
		if (ctx->wfp) {
			fclose(ctx->wfp);
			ctx->wfp = NULL;
		}
		if (ctx->fmp4) {
			fmp4_writer_destroy(ctx->fmp4);
		}
		free(ctx);
	}
	return NULL;
}

void *fmp4_create(void *parent)
{
	fmp4_ctx_t *ctx = malloc(sizeof(fmp4_ctx_t));
	if (!ctx) {
		goto error;
	}
	memset(ctx, 0, sizeof(fmp4_ctx_t));
	ctx->parent = parent;

	ctx->s_buffer_len = BUFFER_SIZE_BY_BITRATE(4);
	ctx->s_buffer = (uint8_t *)malloc(sizeof(uint8_t) * BUFFER_SIZE_BY_BITRATE(4));
	if (ctx->s_buffer == NULL) {
		printf("Fail to allicate memory for s_buffer\r\n");
		goto error;
	}
	ctx->s_extra_data_len = 1024;
	ctx->s_extra_data = (uint8_t *)malloc(ctx->s_extra_data_len);
	if (ctx->s_extra_data == NULL) {
		printf("Fail to allicate memory for s_extra_data\r\n");
		goto error;
	}

	return ctx;

error:
	if (ctx) {
		if (ctx->s_buffer) {
			free(ctx->s_buffer);
			ctx->s_buffer = NULL;
		}
		if (ctx->s_extra_data) {
			free(ctx->s_extra_data);
			ctx->s_extra_data = NULL;
		}
		free(ctx);
	}
	return NULL;
}

mm_module_t fmp4_module = {
	.create = fmp4_create,
	.destroy = fmp4_destroy,
	.control = fmp4_control,
	.handle = fmp4_handle,

	.new_item = NULL,
	.del_item = NULL,

	.output_type = MM_TYPE_NONE,
	.module_type = MM_TYPE_AVSINK,
	.name = "FMP4"
};
