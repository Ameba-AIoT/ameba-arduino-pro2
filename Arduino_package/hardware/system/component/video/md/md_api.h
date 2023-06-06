#ifndef MD_API_H
#define MD_API_H

#include <stdio.h>
#include "eip_api.h"

#define MD_MAX_ROW 32 //fix value
#define MD_MAX_COL 32 //fix value
#define MD_FPS 10 //fix value

#define MD_MAX_TIME_FILTER_INTERVAL 5
#define MD_MAX_GOBJ 32

#define MD_HISTOGRAM_MAX 100

typedef struct motion_detect_threshold_s {
	//motion detect base threshold : smaller value, higher sensitive
	float Tbase; // 0 ~ 40
	//motion detect threshold : smaller value, higher sensitive to light change
	float Tlum; // 0 ~ 5
} motion_detect_threshold_t;

typedef struct motion_detect_bgmodel_s {
	int update[MD_MAX_COL * MD_MAX_ROW];
	float RValue[MD_MAX_COL * MD_MAX_ROW];
	float GValue[MD_MAX_COL * MD_MAX_ROW];
	float BValue[MD_MAX_COL * MD_MAX_ROW];
	float YValue[MD_MAX_COL * MD_MAX_ROW];
} motion_detect_bgmodel_t;

typedef struct md_param_s {
	int image_width;
	int image_height;
	int md_row;
	int md_col;
} md_param_t;

typedef struct md_pos_s {
	float xmin, ymin, xmax, ymax;
} md_pos_t;

typedef struct md_result_s {
	char matrix[MD_MAX_COL * MD_MAX_ROW];
	int motion_cnt;
	md_pos_t md_pos[MD_MAX_GOBJ];
	int event_cnt;
} md_result_t;

typedef struct md_adap_param_s {
	int mode; //0: off, 1: normal mode, 2: raising mode
	float md_adapt_level;
	int md_adapt_step;
} md_adap_param_t;

typedef struct md_his_param_s {
	int threshold; //40 ~ 70
	int resolution; //4 or 5
} md_his_param_t;

typedef struct md_config_s {
	//adaptive parameter
	int adapt_mode; //0: off, 1: normal mode, 2: raising mode
	float adapt_level;
	int adapt_step; //adapt step frames

	//his parameter
	int his_threshold; //40 ~ 70
	int his_resolution; //4 or 5 //cannot set in run time

	int en_AE_stable; //0: off, 1: on
	int bg_mode; //0: normal, 1: de-noise

	int detect_interval; //detect every n frames
	int md_time_filter_interval; // 3 ~ 5 //filter fast motion that cannot be tract in n frames
	int md_trigger_block_threshold; // motion blocks to trigger nn
	int md_obj_sensitivity;	// 0~100
} md_config_t;

typedef struct group_obj_s {
	int valid;
	struct {
		int xmin, ymin, xmax, ymax;
	} pos;
	int area;
	int gid;
} group_obj_t;

typedef struct md_context_s {
	int count;
	int md_trigger_block;
	int AE_stable;
	char md_mask[MD_MAX_COL * MD_MAX_ROW];

	float md_adapt_thr[MD_MAX_COL * MD_MAX_ROW];
	int md_adapt_thr_raise_window[MD_FPS][MD_MAX_COL * MD_MAX_ROW];

	uint8_t md_his_idx[MD_MAX_COL * MD_MAX_ROW];
	int *md_his_background[MD_MAX_COL * MD_MAX_ROW];

	short *md_sensitivity_map;
	md_result_t md_result;
	group_obj_t _objs[MD_MAX_TIME_FILTER_INTERVAL][MD_MAX_GOBJ];
	int _result_idx;
	int _event_windows[MD_FPS];
	int _event_idx;

	motion_detect_bgmodel_t md_bgmodel;
	eip_YRBG_data_t YRGB_data;
	motion_detect_threshold_t *md_threshold;
} md_context_t;

void md_initial(md_context_t *md_ctx, md_param_t *md_param, md_config_t *md_config);
void md_initial_bgmodel(md_context_t *md_ctx, md_param_t *md_param);
void md_deinitial(md_context_t *md_ctx);
void motion_detect(md_context_t *md_ctx, md_param_t *md_param, md_config_t *md_config);

#endif	// MD_API_H
