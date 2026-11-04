#ifndef _MODULE_RGBLED_H
#define _MODULE_RGBLED_H

#include <stdint.h>
#include "mmf2_module.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CMD_RGBLED_SET_PARAMS           MM_MODULE_CMD(0x00)
#define CMD_RGBLED_APPLY                MM_MODULE_CMD(0x01)
#define CMD_RGBLED_GET_LAST_COLOR       MM_MODULE_CMD(0x02)
#define CMD_RGBLED_GET_QUADRANT_COLORS  MM_MODULE_CMD(0x03)

/* The frame is split into 2x2 equal quadrants, sampled in this order:
 *   0 = top left, 1 = top right, 2 = bottom left, 3 = bottom right
 */
#define RGBLED_QUADRANTS 4
#define RGBLED_QUAD_TL   0
#define RGBLED_QUAD_TR   1
#define RGBLED_QUAD_BL   2
#define RGBLED_QUAD_BR   3

/* How often the sampled quadrant colours are pushed to the strip. */
#define RGBLED_UPDATE_INTERVAL_MS 100

typedef struct rgbled_params_s {
	uint32_t width;             /* RGB frame width in pixels */
	uint32_t height;            /* RGB frame height in pixels */
	uint16_t num_leds;          /* strip length; each quadrant drives one quarter */
} rgbled_params_t;

typedef struct rgbled_ctx_s {
	void *parent;
	rgbled_params_t params;

	/* Last sampled colour of each quadrant, indexed RGBLED_QUAD_*. */
	uint8_t quad_r[RGBLED_QUADRANTS];
	uint8_t quad_g[RGBLED_QUADRANTS];
	uint8_t quad_b[RGBLED_QUADRANTS];

	uint32_t frames;            /* frames seen by handle() */
	uint32_t updates;           /* times the strip was refreshed */

	uint32_t last_update_tick;  /* FreeRTOS tick of the last strip refresh */
	uint8_t has_updated;        /* last_update_tick is only valid once this is set */
} rgbled_ctx_t;

/* Module descriptor, opened through mm_module_open(). */
extern mm_module_t rgbled_module;

/* Bind the WS2812B strip the module drives. Pass a WS2812B* from the sketch;
 * the pointer is treated as opaque here so this file stays plain C.
 */
void rgbled_bind(void *strip);

/* Provided by RGBLed.cpp: forward to the bound WS2812B object. Kept behind
 * these calls so module_rgbled.c never needs C++ headers.
 */
void rgbled_strip_fill_range(void *strip, uint8_t r, uint8_t g, uint8_t b,
                             uint16_t first, uint16_t count);
void rgbled_strip_show(void *strip);

#ifdef __cplusplus
}
#endif

#endif
