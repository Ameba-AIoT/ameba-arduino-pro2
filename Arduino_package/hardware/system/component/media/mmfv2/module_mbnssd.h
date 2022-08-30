#ifndef MODULE_MBNSSD_H
#define MODULE_MBNSSD_H

#include "mmf2_module.h"
#include "nn_api.h"

#define CMD_SSD_SET_PARAMS			MM_MODULE_CMD(0x00)
#define CMD_SSD_SET_ROI				MM_MODULE_CMD(0x01)
#define CMD_SSD_SET_IMG_WIDTH		MM_MODULE_CMD(0x02)
#define CMD_SSD_SET_IMG_HEIGHT		MM_MODULE_CMD(0x03)
#define CMD_SSD_SET_OSD_DRAW		MM_MODULE_CMD(0x04)

typedef void (*ssd_osd_draw_t)(int x, int y, int w, int h, char *str, int op_mode);

typedef struct mbnssd_param_s {
	struct cvRect_S roi;
	int    in_width;
	int	   in_height;

	ssd_osd_draw_t draw;
} mbnssd_param_t;


extern mm_module_t mbnssd_module;

#endif
