#include <stdint.h>


#ifndef _LIBRTSREMOSAIC_H_
#define _LIBRTSREMOSAIC_H_

typedef enum {
	GR,
	R,
	B,
	GB
} rts_remosaic_start_ch_t;

typedef enum {
	REMOSAIC_DISABLE,
	REMOSAIC_ENABLE
} rts_remosiac_en_t;

typedef enum {
	REMOSAIC_DIRECT_MODE,
	REMOSAIC_DETECT_MODE
} rts_remosaic_mode_t;

int cap_raw_tiling_with_remosaic(uint8_t *input_buf, uint8_t *outbuf[2],
				 uint16_t in_w, uint16_t in_h,
				 uint16_t x_overlap,
				 rts_remosiac_en_t remosaic_en,
				 rts_remosaic_mode_t remosaic_mode,
				 rts_remosaic_start_ch_t start_ch_4cell);

int cap_raw_tiling_with_remosaic_4c(
	const uint8_t * const restrict input_buf, uint8_t * restrict out_buf[4],
	const uint16_t in_w, const uint16_t in_h,
	const uint16_t x_overlap, const uint16_t y_overlap,
	const rts_remosiac_en_t remosaic_en,
	const rts_remosaic_mode_t remosaic_mode,
	const rts_remosaic_start_ch_t start_ch_4cell);

const char* get_libremosaic_version(void);

#endif