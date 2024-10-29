#ifndef OSD_API_H
#define OSD_API_H

#include "hal_osd_util.h"
#include "hal_video.h"


struct osd_rect_info_st {
	int format;
	unsigned char line_width;
	unsigned char rect_clr_r;
	unsigned char rect_clr_g;
	unsigned char rect_clr_b;
	int rect_w;
	int rect_h;
	unsigned char type;
	unsigned char txt_clr_r;
	unsigned char txt_clr_g;
	unsigned char txt_clr_b;
} ;

enum rts_osd2_blk_type {
	rts_osd2_type_none = 0,
	rts_osd2_type_date,
	rts_osd2_type_time,
	rts_osd2_type_pict,
	rts_osd2_type_text,
	rts_osd2_type_rect,
	rts_osd2_type_pict_extn,
	rts_osd2_type_text_extn,
	rts_osd2_type_rect_extn,
	rts_osd2_type_temp
};

enum rts_osd_err_code {
	rts_osd_err_success = 0,
	rts_osd_err_fail,
	rts_osd_err_wrong_bitmap_range,
	rts_osd_err_wrong_date,
	rts_osd_err_wrong_time,
	rts_osd_err_malloc_fail,
	rts_osd_err_block_not_available,
	rts_osd_err_stream_not_available,
	rts_osd_err_parameter_null,
	rts_osd_err_reserved
};


#define OSD_TEXT_FONT_BG_ENABLE		0
#define OSD_TEXT_FONT_BG_COLOR		RGB_Green
#define OSD_TEXT_FONT_CH_COLOR		RGB_White
#define OSD_TEXT_FONT_BLOCK_ALPHA	10	// 0~15
#define OSD_TEXT_FONT_H_GAP			0
#define OSD_TEXT_FONT_V_GAP			0
#define OSD_TEXT_START_X			10
#define OSD_TEXT_START_Y			10
#define OSD_TEXT_ROTATE				RT_ROTATE_0
#define OSD_TEXT_BMP_BUF_SZ			(80*0x00000400)


enum rts_osd_err_code rts_osd_set_info(int osd_type, void *osd_info);
void rts_osd_init_wo_sntp(int chn_id, int char_resize_w, int char_resize_h, int timezone_s);
enum rts_osd_err_code rts_osd_init(int chn_id, int char_resize_w, int char_resize_h, int timezone_s);
int rts_osd_text2bmp(char *str, BITMAP_S *pbmp, int ch, int fontlib_idx);
enum rts_osd_err_code rts_osd_rect_gen(void *buf, int pic_w, int pic_h, struct osd_rect_info_st rect_info, int update_rect);
enum rts_osd_err_code rts_osd_rect_gen_with_txt(BITMAP_S *txt_bitmap, void *buf, int pic_w, int pic_h, struct osd_rect_info_st rect_info, int update_rect);
int rts_osd_get_timezone(void);
void rts_osd_set_timezone(int timezone_s);
void rts_osd_isp_refresh_datetime(void);
void rts_osd_block_hide(int chn_id, int idx);
void rts_osd_block_show(int chn_id, int idx);
int rts_osd_bitmap_update(int ch, rt_osd2_info_st *posd2_pic, BOOL ready2update);
void rts_osd_hide_bitmap(int ch, rt_osd2_info_st *posd2_pic);
int  rts_osd_get_status(int chn_id);
void rts_osd_get_txt_w_h(int chn_id, int *char_resize_w, int *char_resize_h);
int  rts_osd_release_init_protect(void);
void rts_osd_deinit(int chn_id);
void rts_osd_task(void *arg);
enum rts_osd_err_code rts_set_char_size(int chn_id, int char_resize_w, int char_resize_h);
enum rts_osd_err_code rts_set_font_char_size(int chn_id, int char_resize_w, int char_resize_h, void *font_eng, void *font_chi);
void rts_osd_set_log_type(int log_type);
enum rts_osd_err_code rts_osd_set_frame_size(int chn_id, int frame_w, int frame_h);
void rts_osd_stroke(uint8_t *dst, uint8_t *src, int width, int height, int ch_color, int stroke_color, enum rts_osd2_blk_fmt blk_fmt);
void rts_osd_sync_from_sntp(int sntp_en);
enum rts_osd_err_code rts_osd_get_available_block(int ch, int *num, int *available_block_idx);
enum rts_osd_err_code rts_osd_update_info(int osd_type, void *osd_info);
void rts_osd_fast_start_enable(int ch, BOOL en);
enum rts_osd_err_code rts_osd_pict_resize(void *pd, void *pixels, int widthSource, int heightSource, int width, int height, enum rts_osd2_blk_fmt osd_format);
unsigned int rts_osd_pict_heapsize_cal(int width, int height, enum rts_osd2_blk_fmt osd_format);
enum rts_osd_err_code rts_osd2_set_time(int hour, int minute, int seconds);
enum rts_osd_err_code rts_osd2_set_date(int year, int month, int day);

#endif	// OSD_API_H
