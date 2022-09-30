#ifndef MD_API_H
#define MD_API_H

#define md_col 16
#define md_row 16

//motion detect every n frames
#define MOTION_DETECT_INTERVAL 2

//enable dynamic threshold or not
#define DYNAMIC_THRESHOLD 0

//start MD after AE stable
#define MD_AFTER_AE_STABLE 1

//dynamic increase sensitivity when too light or too dark
#define  BRIGHT_THRESHOLD  180
#define  DARK_THRESHOLD    35
#if DARK_THRESHOLD > BRIGHT_THRESHOLD
#error "Motion Detection: DARK_THRESHOLD shouldn't greater than BRIGHT_THRESHOLD"
#endif

//turn off motion detect while too dark
#define  TURN_OFF_THRESHOLD 0

typedef struct motion_detect_threshold_s {
	//motion detect base threshold : smaller value, higher sensitive
	float Tbase; // 0 ~ 40
	//motion detect threshold : smaller value, higher sensitive to light change
	float Tlum; // 0 ~ 5
} motion_detect_threshold_t;

typedef struct motion_detect_YRBG_data_s {
	unsigned char RValueNow[md_col * md_row];
	unsigned char GValueNow[md_col * md_row];
	unsigned char BValueNow[md_col * md_row];
	unsigned char YValueNow[md_col * md_row];
} motion_detect_YRBG_data_t;

typedef struct motion_detect_bgmodel_s {
	float RValue[md_col * md_row];
	float GValue[md_col * md_row];
	float BValue[md_col * md_row];
	float YValue[md_col * md_row];
} motion_detect_bgmodel_t;

typedef struct md_context_s {
	int count;
	int left_motion;
	int right_motion;
	int middle_motion;
	int AE_stable;
	float max_threshold_shift;
	float max_turn_off;
	char md_result[md_col * md_row];
	char md_mask[md_col * md_row];
	int md_trigger_block_threshold;
	float Tauto;
	motion_detect_bgmodel_t md_bgmodel;
	motion_detect_YRBG_data_t YRGB_data;
	motion_detect_threshold_t *md_threshold;
} md_context_t;

void md_get_YRGB_value(md_context_t *md_ctx, int pic_width, int pic_height, unsigned char *RGB_buffer);
void initial_bgmodel(md_context_t *md_ctx);
void motion_detect(md_context_t *md_ctx);

#endif	// MD_API_H
