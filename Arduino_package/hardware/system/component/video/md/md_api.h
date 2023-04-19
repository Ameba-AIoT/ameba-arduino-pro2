#ifndef MD_API_H
#define MD_API_H

#define MD_MAX_ROW 32 //fix value
#define MD_MAX_COL 32 //fix value
#define MD_FPS 10 //fix value

#define MD_TIME_INTERVAL 3
#define MD_MAX_GOBJ 32

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
	int bg_mode; //0: normal, 1: de-noise
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

typedef struct md_adap_thr_s {
	int mode; //0: off, 1: normal mode, 2: raising mode
	float md_adapt_level;
	int md_adapt_step;
	float md_adaptive_threshold[MD_MAX_COL * MD_MAX_ROW];
	int thr_raise_window[MD_FPS];
} md_adap_thr_t;

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
	int detect_interval;
	int md_trigger_block;

	int en_AE_stable;
	int AE_stable;

	int en_dyn_thr_flag;
	float max_threshold_shift;
	float max_turn_off;

	char md_mask[MD_MAX_COL * MD_MAX_ROW];
	int md_trigger_block_threshold;

	int md_obj_sensitivity;		// 1~100
	short *md_sensitivity_map;
	md_result_t md_result;
	group_obj_t _objs[MD_TIME_INTERVAL][MD_MAX_GOBJ];
	int _result_idx;
	int _event_windows[MD_FPS];
	int _event_idx;

	md_adap_thr_t md_adapt;
	motion_detect_bgmodel_t md_bgmodel;
	motion_detect_YRBG_data_t YRGB_data;
	motion_detect_threshold_t *md_threshold;
} md_context_t;

void md_initial(md_context_t *md_ctx, md_param_t *md_param);
void md_initial_adaptive_threshold(md_context_t *md_ctx, md_param_t *md_param);
void md_get_YRGB_value(md_context_t *md_ctx, md_param_t *md_param, unsigned char *RGB_buffer);
void motion_detect(md_context_t *md_ctx, md_param_t *md_param);

#endif	// MD_API_H
