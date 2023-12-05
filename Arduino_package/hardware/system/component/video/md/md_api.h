#ifndef MD_API_H
#define MD_API_H

#include <stdio.h>
#include "eip_api.h"

/*Please do not modify this file. "md_api.h" is referenced by libmd.a*/

#define MD_MAX_ROW EIP_MAX_ROW //fix value
#define MD_MAX_COL EIP_MAX_COL //fix value
#define MD_MASK_ROW 32 //fix value
#define MD_MASK_COL 32 //fix value
#define MD_FPS 10 //fix value

#define MD_MAX_TIME_FILTER_INTERVAL 5
#define MD_MAX_GOBJ 64

typedef struct motion_detect_threshold_s {
	//motion detect base threshold : smaller value, higher sensitive
	float Tbase; // 0 ~ 40
	//motion detect threshold : smaller value, higher sensitive to light change
	float Tlum; // 0 ~ 5
} motion_detect_threshold_t;

typedef struct motion_detect_bgmodel_s {
	int update[MD_MAX_COL * MD_MAX_ROW];
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
	int motion_cnt;
	md_pos_t md_pos[MD_MAX_GOBJ];
	int event_cnt;
} md_result_t;

typedef struct md_config_s {
	//adaptive parameter
	int adapt_mode; //0: off, 1: normal mode, 2: raising mode
	float adapt_level;
	int adapt_step; //adapt step frames
	int adapt_thr_max; // adapt max threshold

	//his parameter
	int his_threshold; //40 ~ 70
	int his_resolution; //4 or 5 //cannot set in run time
	int his_step; // 100-200 //his step frames

	int bg_mode; //0: normal, 1: de-noise

	int detect_interval; //detect every n frames
	int md_time_filter_interval; // 3 ~ 5 //filter fast motion that cannot be tract in n frames
	int md_trigger_block_threshold; // motion blocks to trigger nn
	float block_base_thr; // 0 ~ 5 //motion detect base threshold : smaller value, higher sensitive
	float block_lum_thr; // 0 ~ 5 //motion detect threshold : smaller value, higher sensitive to light change

	char md_mask[MD_MASK_ROW * MD_MASK_COL];

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

	float md_adapt_thr[MD_MAX_COL * MD_MAX_ROW];
	int md_adapt_thr_raise_window[MD_FPS][MD_MAX_COL * MD_MAX_ROW];

	uint8_t md_his_idx[MD_MAX_COL * MD_MAX_ROW];
	uint8_t *md_his_background[MD_MAX_COL * MD_MAX_ROW];

	short *md_sensitivity_map;
	short *md_area_thr_map;

	char md_trigger_matrix[MD_MAX_COL * MD_MAX_ROW];
	group_obj_t _objs[MD_MAX_TIME_FILTER_INTERVAL][MD_MAX_GOBJ];
	int _result_idx;
	int _event_windows[MD_FPS];
	int _event_idx;

	motion_detect_bgmodel_t md_bgmodel;

} md_context_t;

void md_initial(md_context_t *md_ctx, md_param_t *md_param, md_config_t *md_config);
void md_initial_bgmodel(md_context_t *md_ctx, md_param_t *md_param, eip_Y_data_t *Y_data);
void md_show_config(md_context_t *md_ctx, md_param_t *md_param, md_config_t *md_config);
void md_deinitial(md_context_t *md_ctx);
void motion_detect(md_context_t *md_ctx, md_param_t *md_param, md_config_t *md_config, eip_Y_data_t *Y_data, md_result_t *md_result);

#endif	// MD_API_H
