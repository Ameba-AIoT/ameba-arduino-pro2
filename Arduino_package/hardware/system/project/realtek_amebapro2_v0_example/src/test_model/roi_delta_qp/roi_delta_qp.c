#include <stdlib.h>
#include <stdint.h>

#include "video_api.h"
#include "roi_delta_qp.h"

static roi_delta_qp_ctx_t *p_roi_delta_qp_ctx = NULL;

void roi_delta_qp_init(int ch, int width, int height)
{
	if (p_roi_delta_qp_ctx == NULL) {
		p_roi_delta_qp_ctx = (roi_delta_qp_ctx_t *)malloc(sizeof(roi_delta_qp_ctx_t));
		if (p_roi_delta_qp_ctx == NULL) {
			printf("[%s] fail to allocate memory \r\n", __func__);
			return;
		}
		memset(p_roi_delta_qp_ctx, 0, sizeof(roi_delta_qp_ctx_t));
	}

	p_roi_delta_qp_ctx->video_wh[ch][0] = width;
	p_roi_delta_qp_ctx->video_wh[ch][1] = height;
	p_roi_delta_qp_ctx->ch_use[ch] = 1;
	p_roi_delta_qp_ctx->status = ROI_DELTA_QP_STOP;
}

void roi_delta_qp_deinit(void)
{
	if (p_roi_delta_qp_ctx != NULL) {
		free(p_roi_delta_qp_ctx);
		p_roi_delta_qp_ctx = NULL;
	}
}

void roi_delta_qp_start(void)
{
	if (p_roi_delta_qp_ctx == NULL) {
		return;
	}

	p_roi_delta_qp_ctx->status = ROI_DELTA_QP_START;
}

void roi_delta_qp_stop(void)
{
	if (p_roi_delta_qp_ctx == NULL) {
		return;
	}

	if (p_roi_delta_qp_ctx->status == ROI_DELTA_QP_START) {
		p_roi_delta_qp_ctx->status = ROI_DELTA_QP_STOP;
		roi_delta_qp_reset_qptable();
	}
}

void roi_delta_qp_reset_qptable(void)
{
	if (p_roi_delta_qp_ctx == NULL) {
		return;
	}

	for (int ch = 0; ch < 4; ch++) {
		if (p_roi_delta_qp_ctx->ch_use[ch] == 1) {
			video_set_roi_region(ch, 0, 0, p_roi_delta_qp_ctx->video_wh[ch][0], p_roi_delta_qp_ctx->video_wh[ch][1], 0);
		}
	}
}

void roi_delta_qp_set_param(int ch, int rect_xmin, int rect_ymin, int rect_w, int rect_h, int delta_qp)
{
	if (p_roi_delta_qp_ctx == NULL) {
		return;
	}

	if (p_roi_delta_qp_ctx->status == ROI_DELTA_QP_STOP) {
		return;
	}

	if (p_roi_delta_qp_ctx->ch_use[ch] == 1) {
		video_set_roi_region(ch, rect_xmin, rect_ymin, rect_w, rect_h, delta_qp);
	}
}
