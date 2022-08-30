#ifndef _MODULE_MD_H
#define _MODULE_MD_H

#include <stdint.h>
#include "mmf2_module.h"
#include "hal_isp.h"

#define CMD_MD_SET_PARAMS             	MM_MODULE_CMD(0x00)
#define CMD_MD_SET_MD_THRESHOLD      	MM_MODULE_CMD(0x01)
#define CMD_MD_GET_MD_THRESHOLD      	MM_MODULE_CMD(0x02)
#define CMD_MD_SET_MD_MASK      		MM_MODULE_CMD(0x03)
#define CMD_MD_GET_MD_MASK      		MM_MODULE_CMD(0x04)
#define CMD_MD_GET_MD_RESULT       		MM_MODULE_CMD(0x05)
#define CMD_MD_SET_OUTPUT				MM_MODULE_CMD(0x06)
#define CMD_MD_SET_DISPPOST				MM_MODULE_CMD(0x07)
#define CMD_MD_SET_TRIG_BLK				MM_MODULE_CMD(0x08)

//motion detect every n frames
#define MOTION_DETECT_INTERVAL 2
#define col 16
#define row 16

typedef struct motion_detect_threshold_s {
	//motion detect base threshold : smaller value, higher sensitive
	double Tbase; // 0 ~ 20
	//motion detect threshold : smaller value, higher sensitive to light change
	double Tlum; // 0 ~ 5
} motion_detect_threshold_t;

typedef struct motion_detect_YRBG_data_s {
	unsigned char RValueNow[col * row];
	unsigned char GValueNow[col * row];
	unsigned char BValueNow[col * row];
	unsigned char YValueNow[col * row];
} motion_detect_YRBG_data_t;

typedef struct motion_detect_bgmodel_s {
	double RValue[col * row];
	double GValue[col * row];
	double BValue[col * row];
	double YValue[col * row];
} motion_detect_bgmodel_t;

typedef struct md_context_s {
	int count;
	int left_motion;
	int right_motion;
	int middle_motion;
	int AE_stable;
	float max_threshold_shift;
	float max_turn_off;
	int md_result[col * row];
	int md_mask[col * row];
	int md_trigger_block_threshold;
	double Tauto;
	motion_detect_bgmodel_t md_bgmodel;
	motion_detect_YRBG_data_t YRGB_data;
	motion_detect_threshold_t *md_threshold;
} md_context_t;

//enable dynamic threshold or not
#define DYNAMIC_THRESHOLD 0

//start MD after AE stable
#define MD_AFTER_AE_STABLE 1

#define MD_SW 0

//dynamic increase sensitivity when too light or too dark
#define  BRIGHT_THRESHOLD  180
#define  DARK_THRESHOLD    35
#if DARK_THRESHOLD > BRIGHT_THRESHOLD
#error "Motion Detection: DARK_THRESHOLD shouldn't greater than BRIGHT_THRESHOLD"
#endif

//turn off motion detect while too dark
#define  TURN_OFF_THRESHOLD 8

typedef void (*md_disp_postprcess)(void *);

typedef struct md_param_s {
	int width;
	int height;
} md_param_t;

typedef struct md_ctx_s {
	void *parent;
	md_param_t *params;
	md_context_t *motion_detect_ctx;
	md_disp_postprcess disp_postproc;
	bool md_out_en;
} md_ctx_t;

extern mm_module_t md_module;

#endif
