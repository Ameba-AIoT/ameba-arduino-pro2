/******************************************************************************
*
* Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
*
******************************************************************************/

#include <stdint.h>
#include "platform_stdlib.h"
#include "wifi_conf.h"
#include <lwip_netconf.h>
#include "rtsp/rtp_api.h"

#include "mmf2_module.h"
#include "module_rtp.h"

// RTP internal cache
#define RTP_CACHE_DEPTH   6
typedef struct rtp_cache_s {
	uint8_t *buf;
	int len;
} rtp_cache_t;

//------------------------------------------------------------------------------

int rtp_wait_wifi_connection(void)
{
	rtw_wifi_setting_t setting = {0};

	wifi_get_setting(WLAN0_IDX, &setting);
	printf("\n\rwlan mode:%d", setting.mode);

	switch (setting.mode) {
	case (RTW_MODE_AP): //AP mode
		while (!wifi_is_running(WLAN0_IDX)) {
			vTaskDelay(1000);
		}
		break;
	case (RTW_MODE_STA): //STA mode
		while (!((wifi_get_join_status() == RTW_JOINSTATUS_SUCCESS) && (*(u32 *)LwIP_GetIP(0) != IP_ADDR_INVALID))) {
			vTaskDelay(1000);
		}
		break;
	default:
		printf("\n\rillegal wlan state!rtp client cannot start");
		return -1;
	}

	wifi_get_setting(WLAN0_IDX, &setting);
	printf("\n\rwlan mode:%d", setting.mode);
	vTaskDelay(1000);
	return 0;
}

void rtp_cache_handler(void *p)
{
	rtp_ctx_t *ctx = (rtp_ctx_t *)p;

	rtp_cache_t *cache = NULL;
#if defined(RTP_DEBUG)
	uint16_t last_seq = 0;
#endif
	rtp_hdr_t rtp_header;
	int offset;

	while (1) {
		// wait until cache over 50%
		//if(uxQueueSpacesAvailable(ctx->cache_ready) >= ctx->params.cache_depth/2) {
		//vTaskDelay(5);
		//continue;
		//}

		if (xQueueReceive(ctx->cache_ready, &cache, 0xFFFFFFFF) != pdTRUE) {
			continue;    // should not happen
		}

		offset = rtp_parse_header(cache->buf, &rtp_header, 1);

#if defined(RTP_DEBUG)
		if (last_seq == 0) {
			last_seq = ntohs(rtp_header.seq);
		} else {
			if ((ntohs(rtp_header.seq) - last_seq) > 1) {
				rt_printf("\n\r(%d-%d)", last_seq, ntohs(rtp_header.seq));
			}
			last_seq = ntohs(rtp_header.seq);
		}
#endif

		if ((rtp_header.pt == ctx->params.valid_pt) ||
			((ctx->params.valid_pt == 0xFFFFFFFF) && ((rtp_header.pt == RTP_PT_PCMU) || (rtp_header.pt == RTP_PT_DYN_BASE) || (rtp_header.pt == RTP_PT_MPA)))) {
			mm_context_t *mctx = (mm_context_t *)ctx->parent;
			mm_queue_item_t *output_item;
			if (xQueueReceive(mctx->output_recycle, &output_item, 0xFFFFFFFF) == pdTRUE) {
				memcpy((void *)output_item->data_addr, (void *)(cache->buf + offset), cache->len - offset);
				output_item->size = cache->len - offset;
				output_item->type = rtp_header.pt;
				output_item->timestamp = rtp_header.ts;
				xQueueSend(mctx->output_ready, (void *)&output_item, 0xFFFFFFFF);
			}
		}

		xQueueSend(ctx->cache_recycle, (void *)&cache, 0);

	}
}

int rtp_cache_deinit(rtp_ctx_t *ctx)
{
	rtp_cache_t *tmp;

	if (ctx->cache_handler) {
		vTaskDelete(ctx->cache_handler);
	}

	if (ctx->cache_ready && ctx->cache_recycle) {
		while (xQueueReceive(ctx->cache_ready, (void *)&tmp, 0) == pdTRUE) {
			if (tmp) {
				free(tmp);
			}
			tmp = NULL;
			xQueueSend(ctx->cache_recycle, (void *)&tmp, 0);
		}
		while (xQueueReceive(ctx->cache_recycle, (void *)&tmp, 0) == pdTRUE) {
			if (tmp) {
				free(tmp);
			}
			tmp = NULL;
			xQueueSend(ctx->cache_ready, (void *)&tmp, 0);
		}
	}

	if (ctx->cache_ready) {
		vQueueDelete(ctx->cache_ready);
	}
	if (ctx->cache_recycle) {
		vQueueDelete(ctx->cache_recycle);
	}

	ctx->cache_ready = NULL;
	ctx->cache_recycle = NULL;
	ctx->cache_handler = NULL;

	return 0;
}

int rtp_cache_init(rtp_ctx_t *ctx)
{
	rtp_cache_t *tmp;

	// create cache queue
	ctx->cache_ready = xQueueCreate(ctx->params.cache_depth, sizeof(rtp_cache_t *));
	if (!ctx->cache_ready) {
		goto rtp_cache_init_exit;
	}
	ctx->cache_recycle = xQueueCreate(ctx->params.cache_depth, sizeof(rtp_cache_t *));
	if (!ctx->cache_recycle) {
		goto rtp_cache_init_exit;
	}

	for (int i = 0; i < ctx->params.cache_depth; i++) {
		tmp = malloc(sizeof(rtp_cache_t) + ctx->params.frame_size + 16);
		if (!tmp) {
			mm_printf("FAIL: Queue item malloc fail\n\r");
			goto rtp_cache_init_exit;
		}
		memset(tmp, 0, sizeof(rtp_cache_t));
		tmp->buf = (uint8_t *)&tmp[1];

		if (xQueueSend(ctx->cache_recycle, (void *)&tmp, 0) != pdPASS) {
			mm_printf("FAIL: Queue send fail\n\r");
			goto rtp_cache_init_exit;
		}
	}
	if (xTaskCreate(rtp_cache_handler, ((const char *)"rtp_cache"), 512, (void *)ctx, 2, &ctx->cache_handler) != pdPASS) {
		goto rtp_cache_init_exit;
	}

	return 0;
rtp_cache_init_exit:
	rtp_cache_deinit(ctx);

	return -1;
}

int rtp_client_start(rtp_ctx_t *ctx)
{
	int ret = 0;

	if (ctx->rtp_shutdown) {
		return ret;
	}

	struct sockaddr_in rtp_addr;
	socklen_t addrlen = sizeof(struct sockaddr_in);
	fd_set read_fds;
	struct timeval listen_timeout;

	int opt = 1;

	rtp_cache_t *cache;
	// rtp cache init
	if (rtp_cache_init(ctx) < 0) {
		goto rtp_client_start_exit;
	}

	if (rtp_wait_wifi_connection() < 0) {
		goto rtp_client_start_exit;
	}

	if ((ctx->connect_ctx.socket_id = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		mm_printf("\n\rcreate rtp client socket failed!");
		goto rtp_client_start_exit;//???
	}

	if ((setsockopt(ctx->connect_ctx.socket_id, SOL_SOCKET, SO_REUSEADDR, (const char *)&opt, sizeof(opt))) < 0) {
		mm_printf("\r\n Error on setting socket option");
		goto rtp_client_start_exit;
	}
	memset(&rtp_addr, 0, addrlen);
	rtp_addr.sin_family = AF_INET;
	rtp_addr.sin_addr.s_addr = INADDR_ANY;
	rtp_addr.sin_port = htons(ctx->connect_ctx.server_port);
	if (bind(ctx->connect_ctx.socket_id, (struct sockaddr *)&rtp_addr, addrlen) < 0) {
		mm_printf("bind failed\r\n");
		goto rtp_client_start_exit;
	}

	ctx->socket_closed = 0;
	while (!ctx->rtp_shutdown) {
		FD_ZERO(&read_fds);
		listen_timeout.tv_sec = LISTEN_TIME_S;
		listen_timeout.tv_usec = LISTEN_TIME_US;
		FD_SET(ctx->connect_ctx.socket_id, &read_fds);
		if (select(MAX_SELECT_SOCKET, &read_fds, NULL, NULL, &listen_timeout)) {
			if (xQueueReceive(ctx->cache_recycle, &cache, 0xFFFFFFFF) != pdTRUE) {
				continue;
			}

			cache->len = recvfrom(ctx->connect_ctx.socket_id, cache->buf, ctx->params.frame_size, 0, (struct sockaddr *)&rtp_addr, &addrlen);

			xQueueSend(ctx->cache_ready, (void *)&cache, 0xFFFFFFFF);
		}
	}
rtp_client_start_exit:
	mm_printf("RTP stop\n\r");
	if (ctx->connect_ctx.socket_id >= 0) {
		close(ctx->connect_ctx.socket_id);
	}
	ctx->socket_closed = 1;
	rtp_cache_deinit(ctx);
	return ret;
}


void rtp_client_task(void *param)
{
	rtp_ctx_t *ctx = (rtp_ctx_t *)param;

	ctx->socket_closed = 1;
	while (1) {
		if (rtw_down_timeout_sema(&ctx->up_sema, 100)) {
			if (rtp_client_start(ctx) < 0) {
				goto rtp_client_exit;
			}
		}
	}
rtp_client_exit:
	ctx->rtp_shutdown = 0;
	vTaskDelete(NULL);
}

int rtp_control(void *p, int cmd, int arg)
{
	rtp_ctx_t *ctx = (rtp_ctx_t *)p;

	switch (cmd) {
	case CMD_RTP_SET_PARAMS:
		memcpy(&ctx->params, (void *)arg, sizeof(rtp_params_t));
		break;
	case CMD_RTP_GET_PARAMS:
		memcpy((void *)arg, &ctx->params, sizeof(rtp_params_t));
		break;
	case CMD_RTP_APPLY:
		if (ctx->params.port == 0) {
			ctx->params.port = DEFAULT_RTP_PORT;
		}
		if (ctx->params.frame_size == 0) {
			ctx->params.frame_size = AUDIO_BUF_SIZE;
		}
		if (ctx->params.cache_depth == 0) {
			ctx->params.cache_depth = RTP_CACHE_DEPTH;
		}

		ctx->connect_ctx.server_port = ctx->params.port;
		break;
	case CMD_RTP_STREAMING:
		if (arg == 1) {	// stream on
			ctx->rtp_shutdown = 0;
			rtw_up_sema(&ctx->up_sema);
		} else {			// stream off
			ctx->rtp_shutdown = 1;
			// sleep until socket is closed
			rt_printf("wait rtp off");
			while (!ctx->socket_closed) {
				rt_printf(".");
				vTaskDelay(10);
			}
			rt_printf("done\n\r");
		}
		break;
	}
	return 0;
}

int rtp_handle(void *ctx, void *input, void *output)
{
	return 0;
}

void *rtp_destroy(void *p)
{
	rtp_ctx_t *ctx = (rtp_ctx_t *)p;

	if (ctx) {
		rtp_cache_deinit(ctx);

		if (ctx->rtp_shutdown == 0) {
			rtp_control((void *)ctx, CMD_RTP_STREAMING, 0);
		}

		if (ctx && ctx->up_sema) {
			rtw_free_sema(&ctx->up_sema);
		}
		if (ctx && ctx->task) {
			vTaskDelete(ctx->task);
		}
		free(ctx);
	}
	return NULL;
}

void *rtp_create(void *parent)
{
	rtp_ctx_t *ctx = malloc(sizeof(rtp_ctx_t));
	if (!ctx) {
		return NULL;
	}
	memset(ctx, 0, sizeof(rtp_ctx_t));

	ctx->parent = parent;

	/* set default port */
	ctx->connect_ctx.socket_id = -1;
	ctx->connect_ctx.server_port = 0;
	ctx->rtp_shutdown = 1;

	rtw_init_sema(&ctx->up_sema, 0);

	if (xTaskCreate(rtp_client_task, ((const char *)"rtp_client"), 512, (void *)ctx, 2, &ctx->task) != pdPASS) {
		goto rtp_create_fail;
	}

	return ctx;

rtp_create_fail:
	rtp_destroy((void *)ctx);
	return NULL;
}

void *rtp_new_item(void *p)
{
	rtp_ctx_t *ctx = (rtp_ctx_t *)p;
	return malloc(ctx->params.frame_size);
}

void *rtp_del_item(void *p, void *d)
{
	if (d) {
		free(d);
	}
	return NULL;
}

mm_module_t rtp_module = {
	.create = rtp_create,
	.destroy = rtp_destroy,
	.control = rtp_control,
	.handle = rtp_handle,

	.new_item = rtp_new_item,
	.del_item = rtp_del_item,

	.output_type = MM_TYPE_ADSP,     // no output
	.module_type = MM_TYPE_ASRC,     // module type is video algorithm
	.name = "RTP"
};
