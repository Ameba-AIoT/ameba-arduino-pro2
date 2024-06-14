#ifndef EIP_API_H
#define EIP_API_H
#include <stdio.h>

/*Please do not modify this file. "eip_api.h" is referenced by libispfeature.a*/

#define EIP_MAX_ROW 32 //fix value
#define EIP_MAX_COL 64 //fix value

#define HISTOGRAM_COUNT	16

typedef enum {
	IDX_Y = 0,
	IDX_R,
	IDX_G,
	IDX_B,
	IDX_STATISTIC_COUNT
} video_statistic_t;

typedef struct eip_Y_data_s {
	unsigned char YValueNow[EIP_MAX_ROW * EIP_MAX_COL];
} eip_Y_data_t;

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

typedef struct eip_ae_atable_s {
	int stable;
	unsigned long timestamp;
	uint32_t last_ae_etgain;
} eip_ae_stable_t;

/* For RGB image, take G as luminance
   For NV12 image, take Y as luminance
   Convert image buffer into 32x32 */
void eip_gen_Y_data(eip_param_t *eip_param, unsigned char *image_buffer, uint32_t image_type, eip_Y_data_t *Y_data);
void eip_gen_statistic_data(eip_param_t *eip_param, eip_Y_data_t *Y_data, eip_statis_infor_t *eip_statis_info);
int eip_check_ae_stable(eip_ae_stable_t *ctx);
void eip_malloc_use_eram(int enable); // default malloc with sram.

#endif	// EIP_API_H
