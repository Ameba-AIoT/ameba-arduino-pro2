#ifndef OSD_CUSTOM_H
#define OSD_CUSTOM_H

#if !defined (CONFIG_VOE_PLATFORM) || !CONFIG_VOE_PLATFORM // Run on TM9
#include "cmsis.h"
#else
#include "cmsis_voe.h"
#include "voe.h"
#endif
#include "osd_util_custom.h"
#include "hal_video.h"


typedef struct {
	int		chn_id;
	int		blk_idx;
	rt_font_st font;

	uint32_t	start_x;
	uint32_t	start_y;

	uint32_t	rotate;
	char	*str;

	uint8_t *buf;
	uint32_t buf_len;

} osd_text_info_st;

int osd_update_custom_init(void);
int osd_update_custom(osd_text_info_st *text_info, osd_pict_st *p, BOOL ready2update, BOOL fast_start, int fontlib_idx);
int osd_update_custom_deinit(void);
int osd_start(int ch, BOOL fast_start);
int osd_update(enc2out_t *enc2out);
void osd_stop(void);

#endif	// OSD_CUSTOM_H
