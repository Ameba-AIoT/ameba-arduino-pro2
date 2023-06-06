#ifndef EIP_API_H
#define EIP_API_H
#include <stdio.h>

#define EIP_MAX_ROW 32 //fix value
#define EIP_MAX_COL 32 //fix value

#define HISTOGRAM_COUNT	16

typedef enum {
	IDX_Y = 0,
	IDX_R,
	IDX_G,
	IDX_B,
	IDX_STATISTIC_COUNT
} video_statistic_t;

typedef struct eip_YRBG_data_s {
	unsigned char RValueNow[EIP_MAX_ROW * EIP_MAX_COL];
	unsigned char GValueNow[EIP_MAX_ROW * EIP_MAX_COL];
	unsigned char BValueNow[EIP_MAX_ROW * EIP_MAX_COL];
	unsigned char YValueNow[EIP_MAX_ROW * EIP_MAX_COL];
} eip_YRBG_data_t;

typedef struct eip_param_s {
	int image_width;
	int image_height;
	int eip_row;
	int eip_col;
} eip_param_t;

typedef struct eip_statis_infor_s {
	int avg_YRGB[IDX_STATISTIC_COUNT];
	int histogram[HISTOGRAM_COUNT];
} eip_statis_infor_t;

void eip_gen_YRGB_data(unsigned char *RGB_buffer, eip_param_t *eip_param, eip_YRBG_data_t *eip_YRGB); //convert RGB buffer into 32x32
void eip_gen_statistic_data(eip_param_t *eip_param, eip_YRBG_data_t *eip_YRGB, eip_statis_infor_t *eip_statis_info);

#endif	// EIP_API_H
