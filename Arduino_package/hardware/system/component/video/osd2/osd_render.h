#ifndef OSD_RENDER_H_
#define OSD_RENDER_H_

#include "canvas.h"
#include "hal_osd_util.h"
#include "osd_util_custom.h"

#define OSD_OBJ_MAX_CH 3 //fix value
#define OSD_OBJ_MAX_NUM RTS_OSD2_CH_BLK_MAX_NUMBER //fix value
#define OSD_PT_MAX_NUM 5
#define MAX_DRAW_MSG 50
#define MAX_QUEUE_MSG 500

#define CANVAS_CREATE_BMP 		0x01
#define CANVAS_MSG_DRAW			0x02
#define CANVAS_MSG_TEXT 		0x03
#define CANVAS_MSG_RECT 		0x04
#define CANVAS_MSG_POINT		0x05
#define CANVAS_MSG_LINE			0x06

typedef union {
	canvas_text_t text;
	canvas_rect_t rect;
	canvas_pt_t point;
	canvas_line_t line;
	canvas_bmp_t bmp;
	int ready2update;
} canvas_draw_data_t;

typedef struct canvas_msg_s {
	int ch;
	int idx;
	int msg_type;
	canvas_draw_data_t draw_data;
	canvas_color_t color;
} canvas_msg_t;

typedef struct osd_render_obj_s {
	osd_pict_st osd2_pic;
	canvas_bmp_t bitmap[2];
	int buff_used_index;
	canvas_msg_t canvas_draw_msg[MAX_DRAW_MSG];
	int canvas_draw_msg_count;
} osd_render_obj_t;

typedef struct osd_render_info_s {
	int ready2draw;
	int channel_en[3];
	int channel_txt_w[3], channel_txt_h[3];
	int channel_xmax[3], channel_ymax[3];
	osd_render_obj_t render_obj[OSD_OBJ_MAX_CH * OSD_OBJ_MAX_NUM];
} osd_render_info_t;

int canvas_create_bitmap(int ch, int idx, enum rts_osd2_blk_fmt bmp_format);
int canvas_update(int ch, int idx, int ready2update);
int canvas_set_point(int ch, int idx, int x, int y, int point_width, uint32_t color);
int canvas_set_line(int ch, int idx, int xstart, int ystart, int xend, int yend, int line_width, uint32_t color);
int canvas_set_rect(int ch, int idx, int xmin, int ymin, int xmax, int ymax, int line_width, uint32_t color);
int canvas_set_text(int ch, int idx, int xmin, int ymin, char *text_string, uint32_t color);
void osd_render_dev_init(int *ch_enable, int *char_resize_w, int *char_resize_h);
void osd_render_dev_deinit(int ch);
void osd_render_dev_deinit_all(void);
void osd_render_task_start(int *ch_visible, int *ch_width, int *ch_height);
void osd_render_task_stop(void);
int canvas_send_msg(canvas_msg_t *canvas_msg);
#endif //OSD_RENDER_H_