#ifndef MODULE_FACERECOG_H
#define MODULE_FACERECOG_H

#include "mmf2_module.h"
#include "module_vipnn.h"

#define CMD_FRC_SET_PARAMS			MM_MODULE_CMD(0x00)
#define CMD_FRC_SET_THRES100		MM_MODULE_CMD(0x01)
#define CMD_FRC_SET_OSD_DRAW		MM_MODULE_CMD(0x04)

#define CMD_FRC_REGISTER_MODE 		MM_MODULE_CMD(0x10)
#define CMD_FRC_RECOGNITION_MODE 	MM_MODULE_CMD(0x11)
#define CMD_FRC_LOAD_FEATURES 		MM_MODULE_CMD(0x12)
#define CMD_FRC_SAVE_FEATURES 		MM_MODULE_CMD(0x13)
#define CMD_FRC_RESET_FEATURES 		MM_MODULE_CMD(0x14)
#define CMD_FRC_UNREGISTER_MODE 	MM_MODULE_CMD(0x15)


#define MAX_FRC_REG_NUM		20

typedef void (*draw_func_t)(void *, void *);

typedef struct frc_param_s {
	float sim_thres;

} frc_param_t;

typedef struct frc_bbox_s {
	float xmin, ymin, xmax, ymax;
} frc_bbox_t;

typedef struct frc_draw_s {
	int obj_cnt;
	int pic_width;
	int pic_height;

	char *obj_name[MAX_FRC_REG_NUM];
	frc_bbox_t bbox[MAX_FRC_REG_NUM];
} frc_draw_t;


typedef enum {
	FRC_RECOGNITION = 0,
	FRC_REGISTER,
	FRC_UNREGISTER
} frc_mode_t;


typedef struct face_data_s {
	int reg_feature_num;
	face_feature_res_t reg_feature[MAX_FRC_REG_NUM + 1];
	char  reg_name[MAX_FRC_REG_NUM][32];
	uint32_t crc32;
} face_data_t;


typedef struct frc_ctx_s {
	frc_param_t params;

	// save and load face data
	face_data_t face_data;

	frc_mode_t mode;
	char tmp_reg_name[32];

	draw_func_t draw;
	frc_draw_t  draw_ctx;
} frc_ctx_t;

extern mm_module_t facerecog_module;

#endif
