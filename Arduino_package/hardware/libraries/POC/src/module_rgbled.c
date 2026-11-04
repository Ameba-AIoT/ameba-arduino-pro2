/******************************************************************************
*
* RGB LED (WS2812B) sink module for the AmebaPro2 mmf2 pipeline.
*
* Receives RGB888 frames from a video channel and splits each frame into four
* equal quadrants. The midpoint pixel of each quadrant drives one quarter of
* the strip:
*
*     LEDs 0            .. n/4 - 1   <- top left
*     LEDs n/4          .. n/2 - 1   <- top right
*     LEDs n/2          .. 3n/4 - 1  <- bottom left
*     LEDs 3n/4         .. n - 1     <- bottom right
*
* With a strip length that is not a multiple of four the last quarter is one
* LED longer, e.g. 17 LEDs -> 4 / 4 / 4 / 5.
*
* The strip is refreshed at most once per RGBLED_UPDATE_INTERVAL_MS. Frames
* keep being sampled on every callback; only the transfer is rate limited.
******************************************************************************/

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"

#include "mmf2_module.h"
#include "module_rgbled.h"
#include "avcodec.h"
#include "hal_cache.h"

/* The strip is driven from this module's handle(), which runs in the siso task
 * created for the video->rgbled link, so the transfer cannot be preempted by
 * the sketch's own tasks.
 */
static void *rgbled_strip = NULL;

void rgbled_bind(void *strip)
{
	rgbled_strip = strip;
}

/* Read quadrant `quad`'s midpoint pixel.
 *
 * The RGB tap emits RGB888 as three planes, not interleaved: red at offset 0,
 * green at width * height, blue at 2 * width * height. The buffer is still
 * width * height * 3 bytes in total, but consecutive bytes within a plane are
 * neighbouring samples of the same channel, so reading three of them and
 * calling them R/G/B yields three nearly identical values.
 */
static void rgbled_get_quadrant_color(const uint8_t *frame, uint32_t width, uint32_t height,
                                      uint8_t quad, uint8_t *r, uint8_t *g, uint8_t *b)
{
	uint32_t half_w = width / 2;
	uint32_t half_h = height / 2;
	uint32_t x = half_w / 2;
	uint32_t y = half_h / 2;

	/* Midpoint of the quadrant, measured from the frame origin. */
	if (quad & 1) {
		x += half_w;    /* right half */
	}
	if (quad & 2) {
		y += half_h;    /* bottom half */
	}

	uint32_t offset = (y * width) + x;
	uint32_t plane = width * height;

	*r = frame[offset];
	*g = frame[plane + offset];
	*b = frame[2 * plane + offset];
}

/* Push the four quadrant colours onto the strip.
 *
 * The split is computed so the four ranges always add up to num_leds. For 17
 * that gives 4 / 4 / 4 / 5.
 */
static void rgbled_update_strip(rgbled_ctx_t *ctx)
{
	uint16_t num_leds = ctx->params.num_leds;

	if (rgbled_strip == NULL || num_leds == 0) {
		return;
	}

	for (uint16_t q = 0; q < RGBLED_QUADRANTS; q++) {
		uint16_t first = (uint16_t)(((uint32_t)num_leds * q) / RGBLED_QUADRANTS);
		uint16_t end = (uint16_t)(((uint32_t)num_leds * (q + 1)) / RGBLED_QUADRANTS);

		if (end > first) {
			rgbled_strip_fill_range(rgbled_strip,
			                        ctx->quad_r[q], ctx->quad_g[q], ctx->quad_b[q],
			                        first, (uint16_t)(end - first));
		}
	}

	rgbled_strip_show(rgbled_strip);
	ctx->updates++;
	ctx->last_update_tick = xTaskGetTickCount();
	ctx->has_updated = 1;
}

static int rgbled_handle(void *p, void *input, void *output)
{
	rgbled_ctx_t *ctx = (rgbled_ctx_t *)p;
	mm_queue_item_t *input_item = (mm_queue_item_t *)input;
	const uint8_t *frame;
	uint32_t width, height;

	(void)output;

	if (input_item == NULL || input_item->type != AV_CODEC_ID_RGB888) {
		return 0;
	}

	width = ctx->params.width;
	height = ctx->params.height;

	/* The quadrant midpoints need at least a 2x2 frame, and the buffer must
	 * hold all three planes, so a mis-sized frame cannot walk off the end.
	 */
	if (width < 2 || height < 2) {
		return 0;
	}
	if (input_item->size < (uint32_t)(width * height * 3)) {
		return 0;
	}

	/* The frame was written by the ISP, so the CPU's view of it is stale until
	 * the cache is invalidated. The other ISP-buffer consumers in this SDK do
	 * the same before touching the pixels.
	 */
	dcache_invalidate_by_addr((uint32_t *)input_item->data_addr, (int32_t)input_item->size);

	frame = (const uint8_t *)input_item->data_addr;
	for (uint8_t q = 0; q < RGBLED_QUADRANTS; q++) {
		rgbled_get_quadrant_color(frame, width, height, q,
		                          &ctx->quad_r[q], &ctx->quad_g[q], &ctx->quad_b[q]);
	}

	ctx->frames++;

	/* Sample on every frame, refresh the strip once per interval. Comparing
	 * tick deltas (wrapping subtraction) avoids any absolute-clock assumptions.
	 */
	if (!ctx->has_updated ||
	    (xTaskGetTickCount() - ctx->last_update_tick) >= pdMS_TO_TICKS(RGBLED_UPDATE_INTERVAL_MS)) {
		rgbled_update_strip(ctx);
	}

	return 0;
}

static int rgbled_control(void *p, int cmd, int arg)
{
	rgbled_ctx_t *ctx = (rgbled_ctx_t *)p;
	int ret = 0;

	switch (cmd) {
	case CMD_RGBLED_SET_PARAMS:
		memcpy(&ctx->params, (rgbled_params_t *)arg, sizeof(rgbled_params_t));
		/* Force the first handled frame to refresh the strip immediately. */
		ctx->has_updated = 0;
		break;
	case CMD_RGBLED_APPLY:
		/* nothing to apply, the module has no hardware of its own */
		break;
	case CMD_RGBLED_GET_LAST_COLOR:
		/* Kept for compatibility: reports the top-left quadrant. */
		*((uint32_t *)arg) = ((uint32_t)ctx->quad_r[RGBLED_QUAD_TL] << 16) |
		                     ((uint32_t)ctx->quad_g[RGBLED_QUAD_TL] << 8) |
		                     (uint32_t)ctx->quad_b[RGBLED_QUAD_TL];
		break;
	case CMD_RGBLED_GET_QUADRANT_COLORS: {
		/* Four 0x00RRGGBB values in TL, TR, BL, BR order. */
		uint32_t *out = (uint32_t *)arg;

		if (out == NULL) {
			ret = -1;
			break;
		}
		for (uint8_t q = 0; q < RGBLED_QUADRANTS; q++) {
			out[q] = ((uint32_t)ctx->quad_r[q] << 16) |
			         ((uint32_t)ctx->quad_g[q] << 8) |
			         (uint32_t)ctx->quad_b[q];
		}
		break;
	}
	default:
		ret = -1;
		break;
	}

	return ret;
}

static void *rgbled_destroy(void *p)
{
	rgbled_ctx_t *ctx = (rgbled_ctx_t *)p;

	if (ctx) {
		free(ctx);
	}

	return NULL;
}

static void *rgbled_create(void *parent)
{
	rgbled_ctx_t *ctx = (rgbled_ctx_t *)malloc(sizeof(rgbled_ctx_t));

	if (!ctx) {
		printf("[rgbled] create fail\r\n");
		return NULL;
	}

	memset(ctx, 0, sizeof(rgbled_ctx_t));
	ctx->parent = parent;

	return ctx;
}

/* Called by the mmf2 framework to allocate an output item. This module only
 * consumes frames, so there is no output buffer to hand out.
 */
static void *rgbled_new_item(void *p)
{
	(void)p;
	return NULL;
}

static void *rgbled_del_item(void *p, void *d)
{
	(void)p;
	(void)d;
	return NULL;
}

mm_module_t rgbled_module = {
	.create = rgbled_create,
	.destroy = rgbled_destroy,
	.control = rgbled_control,
	.handle = rgbled_handle,

	.new_item = rgbled_new_item,
	.del_item = rgbled_del_item,

	.output_type = MM_TYPE_NONE,
	.module_type = MM_TYPE_VDSP,
	.name = "rgbled"
};
