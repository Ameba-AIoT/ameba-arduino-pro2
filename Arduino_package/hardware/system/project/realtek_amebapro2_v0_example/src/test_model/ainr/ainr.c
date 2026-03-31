#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "hal_cache.h"
#include "sensor.h"

#include <vfs.h>
#include <ainr.h>
#include <ulaw_lut.h>

#if MODEL_INPUT_SIZE_H == 256
nnlite_model_t ainr_imx681 = {
	.type       = NNLITE_CREATE_NETWORK_TYPE_FWFS,
	.filename   = "NN_MDL/ainr_mulaw_512_imx681.nb",
	.modelname  = "ainr"
};
nnlite_model_t planar_to_nchw_blc = {
	.type       = NNLITE_CREATE_NETWORK_TYPE_FWFS,
	.filename   = "NN_MDL/planar_to_nchw_512_lut.nb",
	.modelname  = "planar_to_nchw_blc"
};
#elif MODEL_INPUT_SIZE_H == 512
nnlite_model_t ainr_imx681 = {
	.type       = NNLITE_CREATE_NETWORK_TYPE_FWFS,
	.filename   = "NN_MDL/ainr_mulaw_1024_imx681.nb",
	.modelname  = "ainr"
};

nnlite_model_t planar_to_nchw_blc = {
	.type       = NNLITE_CREATE_NETWORK_TYPE_FWFS,
	.filename   = "NN_MDL/planar_to_nchw_1024_lut.nb",
	.modelname  = "planar_to_nchw_blc"
};
#endif

static inline uint16_t get_pixel_from_planar_with_padding(int y, int x, int src_full_h, int src_full_w, const uint8_t *src_msb_plane,
		const uint8_t *src_lsb_plane, int blc)
{
	if (y < 0) {
		y = -y - 1;
	} else if (y >= src_full_h) {
		y = 2 * (src_full_h - 1) - y;
	}

	if (x < 0) {
		x = -x - 1;
	} else if (x >= src_full_w) {
		x = 2 * (src_full_w - 1) - x;
	}

	size_t index = (size_t)y * src_full_w + x;
	uint16_t value = (uint16_t)(src_msb_plane[index] << 8) | src_lsb_plane[index];

	if (blc > 0) {
		value = (value > blc) ? (value - blc) : 0;
	}

	return value;
}

void pack_bayer_to_planar(uint8_t *planar_dst, const uint16_t *packed_bayer_src, int dataLen)
{
	int num_pixels = dataLen / 2;
	for (int i = 0; i < num_pixels; i++) {
		uint16_t pixel_value = packed_bayer_src[i];

		uint8_t msb = (pixel_value >> 8) & 0xFF;
		uint8_t lsb = pixel_value & 0xFF;

		planar_dst[i] = msb;
		planar_dst[i + num_pixels] = lsb;
	}
}

static void update_time_stats(time_eval *t, uint32_t end_time)
{
	t->end_time = end_time;
	t->elapsed_time = t->end_time - t->start_time;
	t->count++;
	t->total_time += t->elapsed_time;
	t->min_time = (t->count == 1) ? t->elapsed_time :
				  (t->elapsed_time < t->min_time) ?
				  t->elapsed_time : t->min_time;
	t->max_time = (t->count == 1) ? t->elapsed_time :
				  (t->elapsed_time > t->max_time) ?
				  t->elapsed_time : t->max_time;
}

void ainr_dump_time_stats(ainr_ctx_t *ctx)
{
	ainr_time_stats_t *stats = &(ctx->time_stats);
	printf("AINR Time Stats:\n");
	printf("  Patch to NCHW Processing: (min: %lu ms, max: %lu ms, avg: %lu ms, count: %lu, total: %lu ms)\n",
		   stats->patch_to_nchw.min_time,
		   stats->patch_to_nchw.max_time,
		   stats->patch_to_nchw.count ? stats->patch_to_nchw.total_time / stats->patch_to_nchw.count : 0,
		   stats->patch_to_nchw.count,
		   stats->patch_to_nchw.total_time);
	printf("  Planar to NCHW: (min: %lu ms, max: %lu ms, avg: %lu ms, count: %lu, total: %lu ms)\n",
		   stats->planar_to_nchw.min_time,
		   stats->planar_to_nchw.max_time,
		   stats->planar_to_nchw.count ? stats->planar_to_nchw.total_time / stats->planar_to_nchw.count : 0,
		   stats->planar_to_nchw.count,
		   stats->planar_to_nchw.total_time);
	printf("  NN Inference: (min: %lu ms, max: %lu ms, avg: %lu ms, count: %lu, total: %lu ms)\n",
		   stats->nn_inference.min_time,
		   stats->nn_inference.max_time,
		   stats->nn_inference.count ? stats->nn_inference.total_time / stats->nn_inference.count : 0,
		   stats->nn_inference.count,
		   stats->nn_inference.total_time);
	printf("  Mixup & uLaw Decode: (min: %lu ms, max: %lu ms, avg: %lu ms, count: %lu, total: %lu ms)\n",
		   stats->mixup_decode.min_time,
		   stats->mixup_decode.max_time,
		   stats->mixup_decode.count ? stats->mixup_decode.total_time / stats->mixup_decode.count : 0,
		   stats->mixup_decode.count,
		   stats->mixup_decode.total_time);
	printf("  Tile Processing: (min: %lu ms, max: %lu ms, avg: %lu ms, count: %lu, total: %lu ms)\n",
		   stats->tile.min_time,
		   stats->tile.max_time,
		   stats->tile.count ? stats->tile.total_time / stats->tile.count : 0,
		   stats->tile.count,
		   stats->tile.total_time);

	unsigned long total_time = stats->patch_to_nchw.total_time +
							   stats->nn_inference.total_time +
							   stats->mixup_decode.total_time +
							   stats->tile.total_time;
	printf("  Total Time: %lu ms\n", total_time);
}

ainr_ctx_t *ainr_init(void)
{
#if USE_SENSOR != SENSOR_IMX681
	printf("[ainr] sensor dont support ainr\r\n");
	return NULL;
#endif

	ainr_ctx_t *ctx = (ainr_ctx_t *)malloc(sizeof(ainr_ctx_t));
	if (ctx == NULL) {
		printf("Failed to allocate memory for AINR context\r\n");
		return NULL;
	}
#if USE_SENSOR == SENSOR_IMX681
	ctx->nnlite_ctx = nnlite_deploy_model(&ainr_imx681);
	if (ctx->nnlite_ctx == NULL) {
		printf("Failed to deploy AINR model\r\n");
		free(ctx);
		return NULL;
	}
	ctx->planar_to_nchw_ctx = nnlite_deploy_model(&planar_to_nchw_blc);
	if (ctx->planar_to_nchw_ctx == NULL) {
		printf("Failed to deploy planar_to_nchw_blc model\r\n");
		nnlite_destroy_model(ctx->nnlite_ctx);
		free(ctx);
		return NULL;
	}
	ctx->image_h = sensor_params[SENSOR_IMX681_12M].sensor_height;
	ctx->image_w = sensor_params[SENSOR_IMX681_12M].sensor_width;
#endif

	printf("AINR initialized.\r\n");
	return ctx;
}

void ainr_deinit(ainr_ctx_t *ctx)
{
	if (ctx == NULL) {
		printf("AINR context is NULL.\r\n");
		return;
	}
	free(ctx);
	ctx = NULL;
	printf("AINR deinitialized.\r\n");
}

int planar_to_nchw_ppu(ainr_ctx_t *ctx, const uint8_t *src_msb_plane, const uint8_t *src_lsb_plane, uint8_t *dst_nchw_patch, int patch_h, int patch_w, int blc)
{

	const int channel_plane_size = patch_h * patch_w;

#if 0
	const int temp_patch_w = patch_w * 2;

	uint16_t *gr_plane = dst_nchw_patch;
	uint16_t *r_plane  = dst_nchw_patch + channel_plane_size;
	uint16_t *b_plane  = dst_nchw_patch + 2 * channel_plane_size;
	uint16_t *gb_plane = dst_nchw_patch + 3 * channel_plane_size;

	for (int y_p = 0; y_p < patch_h; ++y_p) {
		for (int x_p = 0; x_p < patch_w; ++x_p) {
			int src_y_base = y_p * 2;
			int src_x_base = x_p * 2;

			uint8_t gr_msb = src_msb_plane[(src_y_base) * temp_patch_w + (src_x_base)];
			uint8_t gr_lsb = src_lsb_plane[(src_y_base) * temp_patch_w + (src_x_base)];
			uint8_t r_msb  = src_msb_plane[(src_y_base) * temp_patch_w + (src_x_base + 1)];
			uint8_t r_lsb  = src_lsb_plane[(src_y_base) * temp_patch_w + (src_x_base + 1)];
			uint8_t b_msb  = src_msb_plane[(src_y_base + 1) * temp_patch_w + (src_x_base)];
			uint8_t b_lsb  = src_lsb_plane[(src_y_base + 1) * temp_patch_w + (src_x_base)];
			uint8_t gb_msb = src_msb_plane[(src_y_base + 1) * temp_patch_w + (src_x_base + 1)];
			uint8_t gb_lsb = src_lsb_plane[(src_y_base + 1) * temp_patch_w + (src_x_base + 1)];

			uint16_t gr_val = (uint16_t)(gr_msb << 8) | gr_lsb;
			if (blc > 0) {
				gr_val = (gr_val > blc) ? (gr_val - blc) : 0;
			}
			uint16_t r_val  = (uint16_t)(r_msb << 8) | r_lsb;
			if (blc > 0) {
				r_val = (r_val > blc) ? (r_val - blc) : 0;
			}
			uint16_t b_val  = (uint16_t)(b_msb << 8) | b_lsb;
			if (blc > 0) {
				b_val = (b_val > blc) ? (b_val - blc) : 0;
			}
			uint16_t gb_val = (uint16_t)(gb_msb << 8) | gb_lsb;
			if (blc > 0) {
				gb_val = (gb_val > blc) ? (gb_val - blc) : 0;
			}

			gr_val = (gr_val > 4095) ? 4095 : gr_val;
			r_val  = (r_val > 4095)  ? 4095 : r_val;
			b_val  = (b_val > 4095)  ? 4095 : b_val;
			gb_val = (gb_val > 4095) ? 4095 : gb_val;

			int dst_idx = y_p * patch_w + x_p;
			gr_plane[dst_idx] = gr_val;
			r_plane[dst_idx]  = r_val;
			b_plane[dst_idx]  = b_val;
			gb_plane[dst_idx] = gb_val;

		}
	}
#else
	int16_t blc_tensor[4];
	blc_tensor[0] = blc_tensor[1] = blc_tensor[2] = blc_tensor[3] = blc;

	ctx->time_stats.planar_to_nchw.start_time = xTaskGetTickCount();
	nnlite_deploy_in_tensor(ctx->planar_to_nchw_ctx, 0, (void *)src_msb_plane, (patch_h * 2) * (patch_w * 2) * sizeof(uint8_t), TENSOR_ZERO_COPY);
	nnlite_deploy_in_tensor(ctx->planar_to_nchw_ctx, 1, (void *)src_lsb_plane, (patch_h * 2) * (patch_w * 2) * sizeof(uint8_t), TENSOR_ZERO_COPY);
	nnlite_deploy_in_tensor(ctx->planar_to_nchw_ctx, 2, blc_tensor, sizeof(blc_tensor), 0);
	nnlite_deploy_out_tensor(ctx->planar_to_nchw_ctx, 0, dst_nchw_patch, channel_plane_size * 4 * sizeof(uint8_t), TENSOR_ZERO_COPY);

	nnlite_run_model(ctx->planar_to_nchw_ctx);

	nnlite_destroy_in_tensor(ctx->planar_to_nchw_ctx);
	nnlite_flush_out_tensor(ctx->planar_to_nchw_ctx);
	update_time_stats(&(ctx->time_stats.planar_to_nchw), xTaskGetTickCount());

#endif
	return 0;
}

static void ainr_patch_to_nchw(ainr_ctx_t *ctx, uint8_t *dst_nchw_patch, int patch_h, int patch_w, const uint8_t *src_msb_plane, const uint8_t *src_lsb_plane, int src_full_h, int src_full_w, int y_nchw, int x_nchw, int blc)
{

	const int temp_patch_h = patch_h * 2;
	const int temp_patch_w = patch_w * 2;
	const size_t temp_plane_size = (size_t)temp_patch_h * temp_patch_w;
	const size_t temp_buffer_size = temp_plane_size * 2;

	uint8_t *temp_planar_buffer = (uint8_t *)malloc(temp_buffer_size);
	if (temp_planar_buffer == NULL) {
		printf("Error: Failed to allocate memory for temporary planar patch!\r\n");
		return;
	}
	uint8_t *temp_msb_plane = temp_planar_buffer;
	uint8_t *temp_lsb_plane = temp_planar_buffer + temp_plane_size;


	const int src_y_start = (y_nchw - OVERLAP_H) * 2;
	const int src_x_start = (x_nchw - OVERLAP_W) * 2;

	for (int y_t = 0; y_t < temp_patch_h; ++y_t) {
		int current_src_y = src_y_start + y_t;
		size_t dst_row_offset = (size_t)y_t * temp_patch_w;


		if (current_src_y >= 0 && current_src_y < src_full_h &&
			src_x_start >= 0 && (src_x_start + temp_patch_w) <= src_full_w) {

			size_t src_row_offset = (size_t)current_src_y * src_full_w + src_x_start;
			memcpy(temp_msb_plane + dst_row_offset, src_msb_plane + src_row_offset, temp_patch_w);
			memcpy(temp_lsb_plane + dst_row_offset, src_lsb_plane + src_row_offset, temp_patch_w);
		} else {
			int reflected_src_y = current_src_y;
			if (reflected_src_y < 0) {
				reflected_src_y = -reflected_src_y - 1;
			} else if (reflected_src_y >= src_full_h) {
				reflected_src_y = 2 * (src_full_h - 1) - reflected_src_y;
			}


			int safe_src_x_start = (src_x_start > 0) ? src_x_start : 0;
			int safe_src_x_end = (src_x_start + temp_patch_w < src_full_w) ? (src_x_start + temp_patch_w) : src_full_w;
			int safe_len = safe_src_x_end - safe_src_x_start;


			int left_padding_len = safe_src_x_start - src_x_start;
			for (int x_t = 0; x_t < left_padding_len; ++x_t) {
				int src_x = src_x_start + x_t;

				int reflected_src_x = -src_x - 1;

				size_t src_index = (size_t)reflected_src_y * src_full_w + reflected_src_x;
				size_t temp_index = dst_row_offset + x_t;
				temp_msb_plane[temp_index] = src_msb_plane[src_index];
				temp_lsb_plane[temp_index] = src_lsb_plane[src_index];
			}


			if (safe_len > 0) {
				size_t src_offset = (size_t)reflected_src_y * src_full_w + safe_src_x_start;
				size_t dst_offset = dst_row_offset + left_padding_len;
				memcpy(temp_msb_plane + dst_offset, src_msb_plane + src_offset, safe_len);
				memcpy(temp_lsb_plane + dst_offset, src_lsb_plane + src_offset, safe_len);
			}


			int right_padding_start = left_padding_len + safe_len;
			for (int x_t = right_padding_start; x_t < temp_patch_w; ++x_t) {
				int src_x = src_x_start + x_t;

				int reflected_src_x = 2 * (src_full_w - 1) - src_x;

				size_t src_index = (size_t)reflected_src_y * src_full_w + reflected_src_x;
				size_t temp_index = dst_row_offset + x_t;
				temp_msb_plane[temp_index] = src_msb_plane[src_index];
				temp_lsb_plane[temp_index] = src_lsb_plane[src_index];
			}
		}
	}


	planar_to_nchw_ppu(ctx, temp_msb_plane, temp_lsb_plane, dst_nchw_patch, patch_h, patch_w, blc);
	free(temp_planar_buffer);
}

static void ainr_nchw_to_packed_bayer(uint16_t *dst_packed_bayer, int dst_h, int dst_w, const uint16_t *src_nchw_patch, int patch_h, int patch_w, int y_nchw, int x_nchw, int blc)
{
	int core_h = patch_h - 2 * OVERLAP_H;
	int core_w = patch_w - 2 * OVERLAP_W;

	int channel_plane_size = patch_h * patch_w;
	const uint16_t *gr_plane = src_nchw_patch;
	const uint16_t *r_plane  = src_nchw_patch + channel_plane_size;
	const uint16_t *b_plane  = src_nchw_patch + 2 * channel_plane_size;
	const uint16_t *gb_plane = src_nchw_patch + 3 * channel_plane_size;

	for (int y_p = 0; y_p < core_h; ++y_p) {
		int dst_y_base = (y_nchw + y_p) * 2;
		if (dst_y_base >= dst_h - 1) {
			continue;
		}

		for (int x_p = 0; x_p < core_w; ++x_p) {
			int dst_x_base = (x_nchw + x_p) * 2;
			if (dst_x_base >= dst_w - 1) {
				continue;
			}

			int src_idx = (y_p + OVERLAP_H) * patch_w + (x_p + OVERLAP_W);

			uint16_t gr_val = gr_plane[src_idx];
			uint16_t r_val  = r_plane[src_idx];
			uint16_t b_val  = b_plane[src_idx];
			uint16_t gb_val = gb_plane[src_idx];

			if (blc > 0) {
				gr_val += blc;
				r_val  += blc;
				b_val  += blc;
				gb_val += blc;
			}

			gr_val = (gr_val > 4095) ? 4095 : gr_val;
			r_val  = (r_val > 4095)  ? 4095 : r_val;
			b_val  = (b_val > 4095)  ? 4095 : b_val;
			gb_val = (gb_val > 4095) ? 4095 : gb_val;

			dst_packed_bayer[(dst_y_base) * dst_w + (dst_x_base)]     = gr_val;
			dst_packed_bayer[(dst_y_base) * dst_w + (dst_x_base + 1)] = r_val;
			dst_packed_bayer[(dst_y_base + 1) * dst_w + (dst_x_base)] = b_val;
			dst_packed_bayer[(dst_y_base + 1) * dst_w + (dst_x_base + 1)] = gb_val;
		}
	}
}


static int denoise_tiled(ainr_ctx_t *ctx, uint16_t *denoised_packed_bayer_output, const uint8_t *src_msb_plane, const uint8_t *src_lsb_plane, int blc)
{
	printf("Starting memory-optimized tiled denoising...\n");
	const int full_h = ctx->image_h;
	const int full_w = ctx->image_w;

	const int h_packed = full_h / 2;
	const int w_packed = full_w / 2;

	const int stride_h = MODEL_INPUT_SIZE_H - 2 * OVERLAP_H;
	const int stride_w = MODEL_INPUT_SIZE_W - 2 * OVERLAP_W;

	size_t patch_elements = (size_t)MODEL_INPUT_SIZE_H * MODEL_INPUT_SIZE_W * PACKED_CHANNELS;
	uint8_t *patch_input_encoded_u8 = (uint8_t *)malloc(patch_elements * sizeof(uint8_t));
	uint8_t *patch_denoised_u8      = (uint8_t *)malloc(patch_elements * sizeof(uint8_t));
	uint16_t *patch_input_u16        = (uint16_t *)malloc(patch_elements * sizeof(uint16_t));
	uint16_t *patch_denoised_decoded = (uint16_t *)malloc(patch_elements * sizeof(uint16_t));

	if (!patch_input_encoded_u8 || !patch_denoised_u8 || !patch_input_u16 || !patch_denoised_decoded) {
		printf("Error: Memory allocation for patch buffers failed!\r\n");
		free(patch_input_encoded_u8);
		free(patch_denoised_u8);
		free(patch_input_u16);
		free(patch_denoised_decoded);
		return -1;
	}

	uint32_t t1 = xTaskGetTickCount();
	for (int y_orig = 0; y_orig < h_packed; y_orig += stride_h) {
		for (int x_orig = 0; x_orig < w_packed; x_orig += stride_w) {

			ctx->time_stats.patch_to_nchw.start_time = xTaskGetTickCount();
			ainr_patch_to_nchw(ctx, patch_input_encoded_u8, MODEL_INPUT_SIZE_H, MODEL_INPUT_SIZE_W, src_msb_plane, src_lsb_plane, full_h, full_w, y_orig, x_orig, blc);
			update_time_stats(&(ctx->time_stats.patch_to_nchw), xTaskGetTickCount());

			ctx->time_stats.nn_inference.start_time = xTaskGetTickCount();
			nnlite_deploy_in_tensor(ctx->nnlite_ctx, 0, patch_input_encoded_u8, patch_elements, TENSOR_ZERO_COPY);
			nnlite_deploy_out_tensor(ctx->nnlite_ctx, 0, patch_denoised_u8, patch_elements, TENSOR_ZERO_COPY);
			nnlite_run_model(ctx->nnlite_ctx);
			nnlite_flush_out_tensor(ctx->nnlite_ctx);
			update_time_stats(&(ctx->time_stats.nn_inference), xTaskGetTickCount());

			ctx->time_stats.mixup_decode.start_time = xTaskGetTickCount();
#if MIXUP_FACTOR == MIXUP_FACTOR_025
			ainr_mixup_and_decode_fast(patch_denoised_u8, patch_input_encoded_u8, patch_denoised_decoded, patch_elements);
#else
#error "[ainr] invalid mix factor"
#endif
			update_time_stats(&(ctx->time_stats.mixup_decode), xTaskGetTickCount());
			ctx->time_stats.tile.start_time = xTaskGetTickCount();
			ainr_nchw_to_packed_bayer(denoised_packed_bayer_output, full_h, full_w, patch_denoised_decoded, MODEL_INPUT_SIZE_H, MODEL_INPUT_SIZE_W, y_orig, x_orig, blc);
			update_time_stats(&(ctx->time_stats.tile), xTaskGetTickCount());

			nnlite_destroy_in_tensor(ctx->nnlite_ctx);
			nnlite_destroy_out_tensor(ctx->nnlite_ctx);
		}
	}
	printf("Processing took %" PRIu32 " ms\r\n", xTaskGetTickCount() - t1);

	free(patch_input_encoded_u8);
	free(patch_denoised_u8);
	free(patch_input_u16);
	free(patch_denoised_decoded);
	printf("Memory-optimized tiled denoising finished successfully.\n");

	return 0;
}

int ainr_process_frame(ainr_ctx_t *ctx, const void *input_planar_buffer, void *output_packed_bayer_buffer, size_t buffer_size, int blc)
{
	if (ctx == NULL) {
		printf("[ainr] ainr not init\r\n");
		return -1;
	}
	printf("\n--- Processing frame from memory ---\n");

	const uint8_t *msb_plane = (const uint8_t *)input_planar_buffer;
	const uint8_t *lsb_plane = msb_plane + (buffer_size / 2);

	memset(&(ctx->time_stats), 0, sizeof(ctx->time_stats));

	uint32_t ts = xTaskGetTickCount();
	int result = denoise_tiled(ctx, (uint16_t *)output_packed_bayer_buffer, msb_plane, lsb_plane, blc);
	printf("Denoising completed in %" PRIu32 " ms\r\n", xTaskGetTickCount() - ts);
	ainr_dump_time_stats(ctx);

	if (result != 0) {
		printf("An error occurred during denoising.\n");
		return -1;
	}

	return 0;
}

static void generate_output_filename(const char *input_filename, char *output_filename, size_t output_size)
{
	const char *dot = strrchr(input_filename, '.');

	if (dot) {
		int base_len = dot - input_filename;
		snprintf(output_filename, output_size, "%.*s_denoised%s", base_len, input_filename, dot);
	} else {
		snprintf(output_filename, output_size, "%s_denoised.raw", input_filename);
	}
}

void ainr_example_init(void)
{
	int ret = 0;
	ainr_ctx_t *ainr_ctx = NULL;
	void *raw_planar_data = NULL;
	void *output_packed_bayer = NULL;
	uint32_t rawfile_size = 0;

	vfs_init(NULL);
	ret = vfs_user_register("sd", VFS_FATFS, VFS_INF_SD);
	if (ret < 0) {
		printf("vfs_user_register fail (%d)\n\r", ret);
		return;
	}

	ainr_ctx = ainr_init();
	if (ainr_ctx == NULL) {
		printf("ainr_init() failed.\r\n");
		goto cleanup_and_exit;
	}

	const char *list_filepath = "sd:/ainr/rawfilelist.txt";
	FILE *list_file = fopen(list_filepath, "r");
	if (list_file == NULL) {
		printf("Failed to open file list: %s\r\n", list_filepath);
		goto cleanup_and_exit;
	}
	printf("Successfully opened file list: %s\r\n", list_filepath);

	char line_buffer[128];
	char input_path[256];
	char output_path[384];

	while (fgets(line_buffer, sizeof(line_buffer), list_file)) {
		line_buffer[strcspn(line_buffer, "\r\n")] = 0;

		if (strlen(line_buffer) == 0) {
			continue;
		}

		char output_filename[256];
		generate_output_filename(line_buffer, output_filename, sizeof(output_filename));

		snprintf(input_path, sizeof(input_path), "sd:/ainr/%s", line_buffer);
		snprintf(output_path, sizeof(output_path), "sd:/ainr/%s", output_filename);

		FILE *rawfile = fopen(input_path, "rb");
		if (rawfile == NULL) {
			printf("Failed to open raw file: %s, skipping.\r\n", input_path);
			continue;
		}
		fseek(rawfile, 0, SEEK_END);
		rawfile_size = ftell(rawfile);
		fseek(rawfile, 0, SEEK_SET);

		raw_planar_data = malloc(rawfile_size);
		if (raw_planar_data == NULL) {
			printf("Failed to allocate memory for raw data, skipping.\r\n");
			fclose(rawfile);
			continue;
		}
		fread(raw_planar_data, 1, rawfile_size, rawfile);
		fclose(rawfile);
		printf("Loaded %s into memory (%" PRIu32 " bytes).\n", input_path, rawfile_size);

		output_packed_bayer = calloc(rawfile_size, 1);
		if (output_packed_bayer == NULL) {
			printf("Failed to allocate memory for output image, skipping.\r\n");
			free(raw_planar_data);
			raw_planar_data = NULL;
			continue;
		}

		if (ainr_process_frame(ainr_ctx, raw_planar_data, output_packed_bayer, rawfile_size, 256) != 0) {
			printf(">>>> Failed to process %s in memory, skipping. <<<<\r\n", line_buffer);
		} else {
			FILE *fp = fopen(output_path, "wb");
			if (fp == NULL) {
				printf("Failed to open output file for writing: %s\r\n", output_path);
			} else {
				fwrite(output_packed_bayer, 1, rawfile_size, fp);
				fclose(fp);
				printf("Denoised image saved to: %s\n", output_path);
			}
		}

		free(raw_planar_data);
		raw_planar_data = NULL;
		free(output_packed_bayer);
		output_packed_bayer = NULL;
	}

	fclose(list_file);
	printf("\nAll files processed.\r\n");

cleanup_and_exit:
	if (ainr_ctx) {
		ainr_deinit(ainr_ctx);
	}
	return;
}
