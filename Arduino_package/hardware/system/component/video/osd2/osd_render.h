#ifndef OSD_RENDER_H_
#define OSD_RENDER_H_

#include "canvas.h"
#include "hal_osd_util.h"

#define OSD_OBJ_MAX_CH 3 //fix value
#define OSD_OBJ_MAX_NUM 6 //fix value
#define OSD_PT_MAX_NUM 5

#define CANVAS_MSG_START 		0x01
#define CANVAS_MSG_DRAW			0x02
#define CANVAS_MSG_CLEAN_ALL 	0x03
#define CANVAS_MSG_TEXT 		0x04
#define CANVAS_MSG_RECT 		0x05
#define CANVAS_MSG_POINT		0x06

typedef struct osd_render_obj_s {
	osd_pict_st osd2_pic;
	uint8_t *buff_bmp[2];
	int buff_used_index;
} osd_render_obj_t;

typedef struct osd_render_info_s {
	int ready2draw;
	int channel_en[3];
	int channel_txt_w[3], channel_txt_h[3];
	int channel_xmax[3], channel_ymax[3];
	osd_render_obj_t render_obj[OSD_OBJ_MAX_CH * OSD_OBJ_MAX_NUM];
} osd_render_info_t;

int canvas_clean_all(int ch, int idx);
int canvas_update(int ch, int idx);
int canvas_set_point(int ch, int idx, int xmin, int ymin, int point_width, uint32_t color);
int canvas_set_rect(int ch, int idx, int xmin, int ymin, int xmax, int ymax, int line_width, uint32_t color);
int canvas_set_text(int ch, int idx, int xmin, int ymin, char *text_string, uint32_t color);
void osd_render_dev_init(int *ch_enable, int *char_resize_w, int *char_resize_h);
void osd_render_dev_deinit(int ch);
void osd_render_dev_deinit_all(void);
void osd_render_task_start(int *ch_visible, int *ch_width, int *ch_height);
void osd_render_task_stop(void);
int canvas_send_msg(canvas_msg_t *canvas_msg);
#endif //OSD_RENDER_H_