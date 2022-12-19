#ifndef MODULE_FACERECOG_H
#define MODULE_FACERECOG_H

#include "mmf2_module.h"

#define CMD_FRC_SET_PARAMS			MM_MODULE_CMD(0x00)
#define CMD_FRC_SET_THRES100		MM_MODULE_CMD(0x01)
#define CMD_FRC_SET_OSD_DRAW		MM_MODULE_CMD(0x04)

#define CMD_FRC_REGISTER_MODE 		MM_MODULE_CMD(0x10)
#define CMD_FRC_RECOGNITION_MODE 	MM_MODULE_CMD(0x11)
#define CMD_FRC_LOAD_FEATURES 		MM_MODULE_CMD(0x12)
#define CMD_FRC_SAVE_FEATURES 		MM_MODULE_CMD(0x13)
#define CMD_FRC_RESET_FEATURES 		MM_MODULE_CMD(0x14)


#define NNMODEL_FR_FEATURE_NUM 128
#define MAX_FRC_REG_NUM		20

typedef void (*draw_func_t)(void *, void *);

typedef struct frc_param_s {
	float sim_thres;

} frc_param_t;


typedef struct frc_draw_s {
	int obj_cnt;

	char *obj_name[MAX_FRC_REG_NUM];
	void *img_param[MAX_FRC_REG_NUM];
} frc_draw_t;

extern mm_module_t facerecog_module;

#endif
