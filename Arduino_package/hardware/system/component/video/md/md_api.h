#ifndef MD_API_H
#define MD_API_H

#define MD_MAX_ROW 32 //fix value
#define MD_MAX_COL 32 //fix value

//dynamic increase sensitivity when too light or too dark
#define  BRIGHT_THRESHOLD  180
#define  DARK_THRESHOLD    35
#if DARK_THRESHOLD > BRIGHT_THRESHOLD
#error "Motion Detection: DARK_THRESHOLD shouldn't greater than BRIGHT_THRESHOLD"
#endif

//turn off motion detect while too dark
#define TURN_OFF_THRESHOLD 0

typedef struct motion_detect_threshold_s {
	//motion detect base threshold : smaller value, higher sensitive
	float Tbase; // 0 ~ 40
	//motion detect threshold : smaller value, higher sensitive to light change
	float Tlum; // 0 ~ 5
} motion_detect_threshold_t;

typedef struct motion_detect_YRBG_data_s {
	unsigned char RValueNow[MD_MAX_COL * MD_MAX_ROW];
	unsigned char GValueNow[MD_MAX_COL * MD_MAX_ROW];
	unsigned char BValueNow[MD_MAX_COL * MD_MAX_ROW];
	unsigned char YValueNow[MD_MAX_COL * MD_MAX_ROW];
} motion_detect_YRBG_data_t;

typedef struct motion_detect_bgmodel_s {
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

typedef struct motion_detect_adj_s {
	int md_adj_threshold_block;
	int md_adj_map[MD_MAX_COL * MD_MAX_ROW];
	int md_visited_map[MD_MAX_COL * MD_MAX_ROW];
	int counter;
	int point_list[MD_MAX_COL * MD_MAX_ROW * 2];
} motion_detect_adj_t;

typedef struct md_context_s {
	int count;
	int detect_interval;
	int left_motion;
	int right_motion;
	int middle_motion;
	int en_AE_stable;
	int AE_stable;
	int en_dyn_thr_flag;
	float max_threshold_shift;
	float max_turn_off;
	char md_result[MD_MAX_COL * MD_MAX_ROW];
	char md_mask[MD_MAX_COL * MD_MAX_ROW];
	int md_trigger_block_threshold;
	float Tauto;
	motion_detect_adj_t md_adj;
	motion_detect_bgmodel_t md_bgmodel;
	motion_detect_YRBG_data_t YRGB_data;
	motion_detect_threshold_t *md_threshold;
} md_context_t;

void md_initial_bgmodel(md_context_t *md_ctx, md_param_t *md_param);
void md_get_YRGB_value(md_context_t *md_ctx, md_param_t *md_param, unsigned char *RGB_buffer);
void motion_detect(md_context_t *md_ctx, md_param_t *md_param);

#endif	// MD_API_H
