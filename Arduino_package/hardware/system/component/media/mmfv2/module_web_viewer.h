#ifndef _MODULE_WEB_VIEWER_H
#define _MODULE_WEB_VIEWER_H

#include <stdint.h>
#include <osdep_service.h>
#include "mmf2_module.h"
#include "web_service.h"

#define CMD_WEB_VIEWER_APPLY     	MM_MODULE_CMD(0x00)  // WEBSOCKET VIEWER START
#define CMD_WEB_VIEWER_SET_BUF     	MM_MODULE_CMD(0x01)  // WEBSOCKET VIEWER BUFFER
#define CMD_WEB_VIEWER_SET_LEN     	MM_MODULE_CMD(0x02)  // WEBSOCKET VIEWER BUFFER LEN

typedef struct wview_ctx_s {
	void *parent;
} wview_ctx_t;

extern mm_module_t websocket_viewer_module;

#endif