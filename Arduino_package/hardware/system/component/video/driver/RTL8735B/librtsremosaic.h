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

const char* get_libremosaic_version(void);

#endif