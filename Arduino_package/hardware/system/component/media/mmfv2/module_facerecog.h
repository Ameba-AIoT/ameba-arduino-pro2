#ifndef MODULE_FACERECOG_H
#define MODULE_FACERECOG_H

#include "mmf2_module.h"
#include "nn_api.h"

#define CMD_FRC_SET_PARAMS			MM_MODULE_CMD(0x00)
#define CMD_FRC_SET_ROI				MM_MODULE_CMD(0x01)
#define CMD_FRC_SET_IMG_WIDTH		MM_MODULE_CMD(0x02)
#define CMD_FRC_SET_IMG_HEIGHT		MM_MODULE_CMD(0x03)
#define CMD_FRC_SET_OSD_DRAW		MM_MODULE_CMD(0x04)

#define CMD_FRC_REGISTER_MODE 		MM_MODULE_CMD(0x10)
#define CMD_FRC_RECOGNITION_MODE 	MM_MODULE_CMD(0x11)
#define CMD_FRC_LOAD_FEATURES 		MM_MODULE_CMD(0x12)
#define CMD_FRC_SAVE_FEATURES 		MM_MODULE_CMD(0x13)
#define CMD_FRC_RESET_FEATURES 		MM_MODULE_CMD(0x14)

typedef void (*frc_osd_draw_t)(int x, int y, int w, int h, char *str, int op_mode);


typedef struct frc_param_s {
	struct cvRect_S roi;
	int    in_width;
	int	   in_height;

	frc_osd_draw_t draw;
} frc_param_t;


extern mm_module_t facerecog_module;

#endif
