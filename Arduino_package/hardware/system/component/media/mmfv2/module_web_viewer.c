/******************************************************************************
*
* Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
*
******************************************************************************/

#include <stdint.h>
#include "platform_stdlib.h"
#include "rtsp/rtsp_api.h"
#include "mmf2_module.h"
#include "module_web_viewer.h"
//------------------------------------------------------------------------------
int webview_handle(void *p, void *input, void *output)
{
	int ret = 0;
	wview_ctx_t *ctx = (wview_ctx_t *)p;
	mm_queue_item_t *input_item = (mm_queue_item_t *)input;
	if (input_item->type == AV_CODEC_ID_H264) {
		wsh264_send_frame(0, (uint8_t *)input_item->data_addr, input_item->size);
	}
	return ret;
}

int webview_control(void *p, int cmd, int arg)
{
	wview_ctx_t *ctx = (wview_ctx_t *)p;
	switch (cmd) {
	case CMD_WEB_VIEWER_APPLY:
		start_websocket_viewer();
		break;
	case CMD_WEB_VIEWER_SET_BUF:
		ws_viewer_set_buf(arg);
		break;
	case CMD_WEB_VIEWER_SET_LEN:
		ws_viewer_set_len(arg);
		break;
	}
	return 0;
}

void *webview_destroy(void *p)
{
	wview_ctx_t *ctx = (wview_ctx_t *)p;
	if (ctx) {
		free(ctx);
	}
	return NULL;
}

void *webview_create(void *parent)
{
	wview_ctx_t *ctx = malloc(sizeof(wview_ctx_t));
	if (!ctx) {
		return NULL;
	}
	return ctx;
}

mm_module_t websocket_viewer_module = {
	.create = webview_create,
	.destroy = webview_destroy,
	.control = webview_control,
	.handle = webview_handle,

	.new_item = NULL,
	.del_item = NULL,

	.output_type = MM_TYPE_NONE,     // no output
	.module_type = MM_TYPE_VSINK,    // module type is video algorithm
	.name = "WEB_VIEWER"
};
