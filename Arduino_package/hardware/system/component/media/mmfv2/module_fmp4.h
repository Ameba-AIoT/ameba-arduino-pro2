#ifndef _MODULE_FMP4_H
#define _MODULE_FMP4_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "mmf2_module.h"

#include "fmp4-writer.h"
#include "mov-format.h"
#include "mov-reader.h"
#include "mpeg4-aac.h"
#include "mpeg4-avc.h"

#define CMD_FMP4_SET_WIDTH      MM_MODULE_CMD(0x00)
#define CMD_FMP4_SET_HEIGHT     MM_MODULE_CMD(0x01)
#define CMD_FMP4_SET_FILENAME   MM_MODULE_CMD(0x02)
#define CMD_FMP4_FILE_OPEN      MM_MODULE_CMD(0x03)
#define CMD_FMP4_FILE_CLOSE     MM_MODULE_CMD(0x04)
#define CMD_FMP4_APPLY          MM_MODULE_CMD(0x05)


struct mov_h264_test_t {
	struct mpeg4_avc_t avc;

	int track;
	int width;
	int height;
	uint32_t pts, dts;
	const uint8_t *ptr;

	int vcl;
};

struct mov_aac_test_t {
	int track;
	uint32_t pts;
};


typedef struct fmp4_ctx_s {
	void *parent;

	fmp4_writer_t *fmp4;

	struct mov_h264_test_t mov_h264_ctx;
	struct mov_aac_test_t mov_aac_ctx;

	FILE *wfp;
	char fmp4_ram_filename[32];

	int s_buffer_len, s_extra_data_len;
	uint8_t *s_buffer, *s_extra_data;

	bool add_audio_track_done;
	bool add_video_track_done;
} fmp4_ctx_t;

extern mm_module_t fmp4_module;

#endif  //_MODULE_FMP4_H
