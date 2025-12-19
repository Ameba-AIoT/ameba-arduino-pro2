#ifndef AINR_H
#define AINR_H
#include <nnlite_api.h>

#define PACKED_CHANNELS 4
// MODEL_INPUT_SIZE_H=256 → DDR: 4 MB, Time: ~4.5 s
// MODEL_INPUT_SIZE_H=512 → DDR: 12 MB, Time: ~2.5 s
#define MODEL_INPUT_SIZE_H 512
#define MODEL_INPUT_SIZE_W MODEL_INPUT_SIZE_H
#define OVERLAP_H 4
#define OVERLAP_W 4
#define MIXUP_FACTOR MIXUP_FACTOR_025
#define MIXUP_FACTOR_025 1

typedef struct {
	unsigned long start_time;
	unsigned long end_time;
	unsigned long elapsed_time;
	unsigned long min_time;
	unsigned long max_time;
	unsigned long total_time;
	unsigned long count;
} time_eval;

typedef struct {
	time_eval nn_inference;
	time_eval planar_to_nchw;
	time_eval mixup_decode;
	time_eval patch_to_nchw;
	time_eval tile;
} ainr_time_stats_t;

typedef struct {
	nnlite_ctx_t *nnlite_ctx;
	nnlite_ctx_t *planar_to_nchw_ctx;
	ainr_time_stats_t time_stats;
	int image_w;
	int image_h;
} ainr_ctx_t;

void ainr_example_init(void);
ainr_ctx_t *ainr_init(void);
void ainr_deinit(ainr_ctx_t *ctx);
int ainr_process_frame(ainr_ctx_t *ctx, const void *input_planar_buffer, void *output_packed_bayer_buffer, size_t buffer_size, int blc);
void ainr_dump_time_stats(ainr_ctx_t *ctx);
void pack_bayer_to_planar(uint8_t *planar_dst, const uint16_t *packed_bayer_src, int dataLen);
#endif