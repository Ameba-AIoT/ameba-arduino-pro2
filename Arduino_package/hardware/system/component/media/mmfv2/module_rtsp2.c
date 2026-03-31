/******************************************************************************
*
* Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
*
******************************************************************************/

#include <stdint.h>
#include "platform_stdlib.h"
#include "rtsp/rtsp_api.h"
#include "lwipconf.h"
#include "mmf2_module.h"
#include "module_rtsp2.h"
#include "video_api.h"
//------------------------------------------------------------------------------
//#define SEPERATE_VIDEO_NALU_PAYLOAD //This function only for AmebaPro
static int channel_idx = 0;
static u32 stream_flow_id_bitmap = 0;
static _mutex stream_flow_id_bitmap_lock = NULL;

int rtsp2_handle(void *p, void *input, void *output)
{
	int ret = 0;
	rtsp2_ctx_t *ctx = (rtsp2_ctx_t *)p;

	mm_queue_item_t *input_item = (mm_queue_item_t *)input;
	(void)output;

	struct rtsp_context *rtsp = (struct rtsp_context *)ctx->rtsp;

	struct stream_context *stream_ctx = NULL;
	struct rtp_object *payload = NULL;

	// get channel
	for (int i = 0; i < rtsp->nb_streams; i++) {
		if (rtsp->stream_ctx[i].rtpobj.codec_id == input_item->type) {
			stream_ctx = &rtsp->stream_ctx[i];
			break;
		}
	}

	if (stream_ctx == NULL) {
		mm_printf("stream_ctx = NULL!\n\r");
		ret = -EFAULT;
		goto rtsp2_handle_end;
	}

	if (rtsp->state != RTSP_PLAYING && ctx->block_type == RTSP2_NON_BLOCK_TYPE) {
		goto rtsp2_handle_end;
	}
#ifndef SEPERATE_VIDEO_NALU_PAYLOAD
	// wait output not empty and get one
	// Get payload from rtsp module
	do {
		payload = rtp_object_out_stream_queue(stream_ctx);
		if (payload == NULL)	{
			vTaskDelay(1);
		}
	} while (payload == NULL);

	// insert payload to rtsp_ctx stream
	//printf("%d\n\r", mm_read_mediatime_ms());
	/*fill payload*/
	payload->index = input_item->index;
	payload->data = (uint8_t *)input_item->data_addr;
	payload->len = input_item->size;
	//payload->timestamp = (rtw_get_current_time()-rtsp_tick_offset)*90;
	payload->timestamp = input_item->timestamp;//rtsp_get_current_tick();
	if (payload->timestamp == 0) {
		payload->timestamp = mm_read_mediatime_ms();
	}


	//printf("ts: %8x\n\r", payload->timestamp);
	/* because we will fill&send a complete frame in single rtp object, set both fs & fe to 1 and fd to 0*/
	rtp_object_set_fs(payload, 1);
	rtp_object_set_fe(payload, 1);
	rtp_object_set_fd(payload, 0);
	/* set payload state to READY to enable rtp task process this rtp object;*/
	payload->state = RTP_OBJECT_READY;

	rtp_object_in_stream_queue(payload, stream_ctx);

	// TODO: use inter task communication
	// wait payload state to IDLE or USED
	//rtsp2_mod_wait_complete();
	while (list_empty(&stream_ctx->output_queue)) {
		vTaskDelay(1);
	}
#else
	int type = -1;
	int scan_result = 0;
	video_encoder_nalu_payload_info_t info;
	if (input_item->type == AV_CODEC_ID_H264) {
		type = VIDEO_H264;
	} else if (input_item->type == AV_CODEC_ID_H265) {
		type = VIDEO_HEVC;
	}
	if (type >= 0) {
		scan_result = video_get_encoder_nalu_payload_info((uint8_t *)input_item->data_addr, input_item->size, type, &info);
	}

	if ((input_item->type == AV_CODEC_ID_H264 || input_item->type == AV_CODEC_ID_H265) && (scan_result >= 0)) {
		for (int i = 0; i < info.nalu_count; i++) {
			do {
				payload = rtp_object_out_stream_queue(stream_ctx);
				if (payload == NULL)	{
					vTaskDelay(1);
				}
			} while (payload == NULL);
			payload->index = input_item->index;
			payload->data = (uint8_t *)input_item->data_addr + info.nalu_info[i].offset;
			payload->len = info.nalu_info[i].size;//input_item->size;

			payload->timestamp = input_item->timestamp;//rtsp_get_current_tick();
			if (payload->timestamp == 0) {
				payload->timestamp = mm_read_mediatime_ms();
			}


			//printf("ts: %8x\n\r", payload->timestamp);
			/* because we will fill&send a complete frame in single rtp object, set both fs & fe to 1 and fd to 0*/
			rtp_object_set_fs(payload, 1);
			rtp_object_set_fe(payload, 1);
			rtp_object_set_fd(payload, 0);
			/* set payload state to READY to enable rtp task process this rtp object;*/
			payload->state = RTP_OBJECT_READY;

			rtp_object_in_stream_queue(payload, stream_ctx);

			// TODO: use inter task communication
			// wait payload state to IDLE or USED
			//rtsp2_mod_wait_complete();
			while (list_empty(&stream_ctx->output_queue)) {
				vTaskDelay(1);
			}
		}
	} else {
		do {
			payload = rtp_object_out_stream_queue(stream_ctx);
			if (payload == NULL)	{
				vTaskDelay(1);
			}
		} while (payload == NULL);
		payload->index = input_item->index;
		payload->data = (uint8_t *)input_item->data_addr;
		payload->len = input_item->size;

		payload->timestamp = input_item->timestamp;//rtsp_get_current_tick();
		if (payload->timestamp == 0) {
			payload->timestamp = mm_read_mediatime_ms();
		}
		//printf("ts: %8x\n\r", payload->timestamp);
		/* because we will fill&send a complete frame in single rtp object, set both fs & fe to 1 and fd to 0*/
		rtp_object_set_fs(payload, 1);
		rtp_object_set_fe(payload, 1);
		rtp_object_set_fd(payload, 0);
		/* set payload state to READY to enable rtp task process this rtp object;*/
		payload->state = RTP_OBJECT_READY;

		rtp_object_in_stream_queue(payload, stream_ctx);

		// TODO: use inter task communication
		// wait payload state to IDLE or USED
		//rtsp2_mod_wait_complete();
		while (list_empty(&stream_ctx->output_queue)) {
			vTaskDelay(1);
		}
	}
#endif
rtsp2_handle_end:
	return ret;
}

extern void rtp_stream_statistics_sync(struct stream_context *stream_ctx);
int rtsp2_control(void *p, int cmd, int arg)
{
	rtsp2_ctx_t *ctx = (rtsp2_ctx_t *)p;
	struct rtsp_context *rtsp = ctx->rtsp;
	struct stream_context *stream_ctx = &rtsp->stream_ctx[channel_idx];

	switch (cmd) {
	case CMD_RTSP2_SELECT_STREAM:
		if ((arg == 0) || (arg == 1)) {
			channel_idx = arg;
		} else {
			mm_printf("[RTSP ERR] RTSP stream index should be 0 or 1, Set to default 0\r\n");
			channel_idx = 0;
			return -1;
		}
		break;
	case CMD_RTSP2_SET_PARAMS: {
		uint32_t codec_id = AV_CODEC_ID_UNKNOWN;
		rtsp2_params_t *params = (rtsp2_params_t *)arg;
		memcpy(&ctx->params[channel_idx], (void *)arg, sizeof(rtsp2_params_t));
		if (params->type == AVMEDIA_TYPE_VIDEO) {
			stream_ctx->framerate = params->u.v.fps;
			stream_ctx->bitrate   = params->u.v.bps;

			if (params->u.v.ts_flag == TIME_SYNC_DIS) {
				time_sync_disable();
			} else if (params->u.v.ts_flag == TIME_SYNC_EN) {
				time_sync_enable();
			}

			set_sps_string(params->u.v.sps);
			set_pps_string(params->u.v.pps);
			set_profile_lv_string(params->u.v.lv);

			codec_id = params->u.v.codec_id;
		} else if (params->type == AVMEDIA_TYPE_AUDIO) {
			if (params->u.a.codec_id == AV_CODEC_ID_OPUS) {
				stream_ctx->samplerate = params->u.a.samplerate;
				stream_ctx->channel = params->u.a.channel;
				stream_ctx->bitrate = params->u.a.max_average_bitrate;
				if (params->u.a.frame_size == 0) {
					stream_ctx->tsin_by_fs = 120 * (20 * 2 / 5); //use 20 frame size
				} else {
					stream_ctx->tsin_by_fs = 120 * (params->u.a.frame_size * 2 / 5); //divide by 2.5
				}
				printf("stream_ctx->tsin_by_fs = %ld\r\n", stream_ctx->tsin_by_fs);
				codec_id = params->u.a.codec_id;
			} else {
				if (params->u.a.codec_id == AV_CODEC_ID_PCMU || params->u.a.codec_id == AV_CODEC_ID_PCMA) {
					stream_ctx->tsin_by_fs = 320 / 2; //Audio half of audio framesize
				}
				stream_ctx->samplerate = params->u.a.samplerate;
				stream_ctx->channel = params->u.a.channel;
				codec_id = params->u.a.codec_id;
			}
		}
		if (codec_id != AV_CODEC_ID_UNKNOWN) {
#ifndef ENABLE_SIP_MMFV2
			get_codec_by_id(stream_ctx->codec, codec_id);
			if (params->u.a.codec_id == AV_CODEC_ID_PCMU || params->u.a.codec_id == AV_CODEC_ID_PCMA || params->u.a.codec_id == AV_CODEC_ID_MP4A_LATM) {
				stream_ctx->codec->clock_rate = params->u.a.samplerate;
			}
			stream_ctx->media_type = rtsp_parse_stream_media_type(stream_ctx->codec);
			rtp_load_o_handler_by_codec_id(&stream_ctx->rtpobj.payload, codec_id);
			// CHECK : how to handle this error condition
			if (stream_ctx->rtpobj.payload.rtp_object_handler == NULL) {
				return -EINVAL;
			}
			stream_ctx->rtp_timestamp = mm_read_mediatime_ms();
#endif
		}
	}
	break;
	case CMD_RTSP2_GET_PARAMS:
		memcpy((rtsp2_params_t *)arg, &ctx->params[channel_idx], sizeof(rtsp2_params_t));
		break;
	case CMD_RTSP2_SET_STREAMMING:
		if (arg == ON) {
			rtsp_start(rtsp);
			// insert to input queue
			for (int i = 0; i < rtsp->nb_streams; i++) {
				rtp_object_in_stream_queue(&rtsp->stream_ctx[i].rtpobj.payload, &rtsp->stream_ctx[i]);
			}
		} else {
			rtsp_stop(rtsp);
		}
		break;
	case CMD_RTSP2_SET_FRAMERATE:
		ctx->params[channel_idx].u.v.fps = arg;
		stream_ctx->framerate = arg;
		stream_ctx->statistics.delay_threshold = RTSP_DEPEND_CLK_HZ / stream_ctx->framerate;
		break;
	case CMD_RTSP2_SET_BITRATE:
		ctx->params[channel_idx].u.v.bps = arg;
		stream_ctx->bitrate = arg;
		break;
	case CMD_RTSP2_SET_SAMPLERATE:
		ctx->params[channel_idx].u.a.samplerate = arg;
		stream_ctx->samplerate = arg;
		break;
	case CMD_RTSP2_SET_CHANNEL:
		ctx->params[channel_idx].u.a.channel = arg;
		stream_ctx->channel = arg;
		break;
	// for H264
	case CMD_RTSP2_SET_SPS:
		set_sps_string((char *)arg);
		break;
	case CMD_RTSP2_SET_PPS:
		set_pps_string((char *)arg);
		break;
	case CMD_RTSP2_SET_LEVEL:
		set_profile_lv_string((char *)arg);
		break;
	case CMD_RTSP2_SET_APPLY:
		if (stream_flow_id_bitmap_lock == NULL) {
			rtw_mutex_init(&stream_flow_id_bitmap_lock);
		}
		if (stream_ctx->stream_id < 0) {
			stream_ctx->stream_id = rtsp_get_number(STREAM_FLOW_ID_BASE, &stream_flow_id_bitmap, &stream_flow_id_bitmap_lock);
		}
		rtp_stream_statistics_sync(stream_ctx);
		stream_ctx->rtpobj.codec_id = stream_ctx->codec->codec_id;
		break;
	case CMD_RTSP2_SET_CODEC:
		get_codec_by_id(stream_ctx->codec, arg);
		stream_ctx->media_type = rtsp_parse_stream_media_type(stream_ctx->codec);
		rtp_load_o_handler_by_codec_id(&stream_ctx->rtpobj.payload, arg);
		// CHECK : how to handle this error condition
		if (stream_ctx->rtpobj.payload.rtp_object_handler == NULL) {
			return -EINVAL;
		}
		stream_ctx->rtp_timestamp = mm_read_mediatime_ms();
		break;
	case CMD_RTSP2_SET_CUSTOM_CODEC:
		rtp_set_o_handler(&stream_ctx->rtpobj.payload, (int (*)(struct stream_context *, struct rtp_object *))arg);
		break;
	case CMD_RTSP2_SET_FLAG:
		if (arg == TIME_SYNC_DIS) {
			time_sync_disable();
		} else if (arg == TIME_SYNC_EN) {
			time_sync_enable();
		}
		break;
	case CMD_RTSP2_SET_START_CB:
		rtsp->cb_start = (int (*)(void *))arg;
		break;
	case CMD_RTSP2_SET_STOP_CB:
		rtsp->cb_stop = (int (*)(void *))arg;
		break;
	case CMD_RTSP2_SET_PAUSE_CB:
		rtsp->cb_pause = (int (*)(void *))arg;
		break;
	case CMD_RTSP2_SET_CUSTOM_CB:
		rtsp->cb_custom = (int (*)(void *))arg;
		break;
	case CMD_RTSP2_USE_RTP_TICK_INC:
		stream_ctx->use_rtp_tick_inc = arg;
		break;
	case CMD_RTSP2_SET_PORT:
		rtsp->connect_ctx.server_port = arg;
		break;
	case CMD_RTSP2_SET_DROP_TIME:
		set_rtp_drop_threshold(stream_ctx, arg);
		break;
	case CMD_RTSP2_SET_BLOCK_TYPE:
		ctx->block_type = arg;
		break;
	case CMD_RTSP2_SET_SYNC_MODE:
		time_sync_enable();
		break;
	case CMD_RTSP2_SET_URL:
		set_rtsp_url(rtsp, (char *)arg);
		break;
	case CMD_RTSP2_SET_INTERFACE:
		rtsp->interface = arg;
		break;
	case CMD_RTSP2_SET_DROP_FRAME_EN:
		set_drop_frame_enable(stream_ctx, arg);
		break;
	case CMD_RTSP2_SET_DROP_FRAME_FORCEI:
		set_drop_frame_forcei(stream_ctx, arg);
		break;
	case CMD_RTSP2_SET_H264_CTX:
		set_h264_ctx(stream_ctx, (void *)arg);
		break;
	case CMD_RTSP2_SET_PACKET_RETRY:
		set_packet_retry(stream_ctx, arg);
		break;
	case CMD_CMD_RTSP2_SET_TIME_OFFSET:
		stream_ctx->time_offset = arg;
		break;
	default:
		break;
	}

	return 0;
}

void *rtsp2_destroy(void *p)
{
	rtsp2_ctx_t *ctx = (rtsp2_ctx_t *)p;

	if (ctx && ctx->rtsp) {
		if (stream_flow_id_bitmap_lock) {
			struct rtsp_context *rtsp = ctx->rtsp;
			for (int i = 0; i < 2; i++) {
				struct stream_context *stream_ctx = &rtsp->stream_ctx[i];
				if (stream_ctx && stream_ctx->stream_id >= 0) {
					rtsp_put_number(stream_ctx->stream_id, STREAM_FLOW_ID_BASE, &stream_flow_id_bitmap, &stream_flow_id_bitmap_lock);
					stream_ctx->stream_id = -1;
				}
			}

		}
		for (int i = 0; i < ctx->rtsp->nb_streams; i++) {
			if (ctx->rtsp->stream_ctx[i].codec) {
				free(ctx->rtsp->stream_ctx[i].codec);
				ctx->rtsp->stream_ctx[i].codec = NULL;
			}

			rtp_object_deinit(&ctx->rtsp->stream_ctx[i].rtpobj.payload);
		}

		rtsp_close(ctx->rtsp);
		rtsp_context_free(ctx->rtsp);
	}
	if (ctx)	{
		free(ctx);
		ctx = NULL;
	}

	return NULL;
}

void *rtsp2_create(void *parent)
{
	int timeout = 10;

	rtsp2_ctx_t *ctx = malloc(sizeof(rtsp2_ctx_t));
	if (!ctx) {
		return NULL;
	}
	memset(ctx, 0, sizeof(rtsp2_ctx_t));
	ctx->parent = parent;

	ctx->rtsp = rtsp_context_create(2);
	if (!ctx->rtsp)	{
		goto rtsp_create_fail;
	}

	/*open rtsp service task*/
	if (rtsp_open(ctx->rtsp) < 0) {
		goto rtsp_create_fail;
	}

	// init payload object
	for (int i = 0; i < ctx->rtsp->nb_streams; i++) {
		rtp_object_init(&ctx->rtsp->stream_ctx[i].rtpobj.payload);
		ctx->rtsp->stream_ctx[i].codec = malloc(sizeof(struct codec_info));
		if (!ctx->rtsp->stream_ctx[i].codec) {
			goto rtsp_create_fail;
		}
	}

	return ctx;
rtsp_create_fail:
	rtsp2_destroy((void *)ctx);
	return NULL;
}

mm_module_t rtsp2_module = {
	.create = rtsp2_create,
	.destroy = rtsp2_destroy,
	.control = rtsp2_control,
	.handle = rtsp2_handle,

	.new_item = NULL,
	.del_item = NULL,

	.output_type = MM_TYPE_NONE,     // no output
	.module_type = MM_TYPE_VSINK,    // module type is video algorithm
	.name = "RTSP"
};
