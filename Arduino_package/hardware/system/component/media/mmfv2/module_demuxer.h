#ifndef _MODULE_DEMUXER_H
#define _MODULE_DEMUXER_H

#include <stdint.h>
#include "fatfs_sdcard_api.h"
#include "mp4_demuxer.h"
#include "avcodec.h"

//DEMUXER CTX STATE
#define DEMUXER_IDLE    0x00
#define DEMUXER_OPEN    0x01
#define DEMUXER_START   0x02
#define DEMUXER_PAUSE   0x04
#define DEMUXER_END     0x08
#define DEMUXER_STOP    0x10


//STREAM TYPE
#define STREAM_AUDIO    0x01
#define STREAM_VIDEO    0x10
#define STREAM_ALL      0x11

#define CMD_DEMUXER_SET_PARAMS     	    MM_MODULE_CMD(0x00)  // set parameter
#define CMD_DEMUXER_GET_PARAMS     	    MM_MODULE_CMD(0x01)  // get parameter

#define CMD_DEMUXER_SET_FILE_NAME       MM_MODULE_CMD(0x03)
#define CMD_DEMUXER_MEMORY_SIZE         MM_MODULE_CMD(0x04)
#define CMD_DEMUXER_BLOCK_SIZE          MM_MODULE_CMD(0x05)
#define CMD_DEMUXER_INIT_MEM_POOL       MM_MODULE_CMD(0x06)
#define CMD_DEMUXER_OPEN                MM_MODULE_CMD(0x07)
#define CMD_DEMUXER_CLOSE               MM_MODULE_CMD(0x08)
#define CMD_DEMUXER_STREAM_PAUSE        MM_MODULE_CMD(0x09)
#define CMD_DEMUXER_STREAM_RESUME       MM_MODULE_CMD(0x10)
#define CMD_DEMUXER_STREAM_START		MM_MODULE_CMD(0x11)

#define CMD_DEMUXER_STOP			    MM_MODULE_CMD(0x12)
#define CMD_DEMUXER_GET_STATUS			MM_MODULE_CMD(0x13)

#define CMD_DEMUXER_APPLY			MM_MODULE_CMD(0x20)  // for hardware module



typedef struct demuxer_param_s {
	uint32_t start_time; //ms (file start time)
	uint8_t  stream_type;
	uint32_t loop_mode;
	char record_file_name[32]; //user setting the file location
	//uint32_t fatfs_buf_size;

	uint32_t mem_total_size;
	uint32_t mem_block_size;
} demuxer_params_t;

typedef struct demuxer_ctx_s {
	void *parent;
	mp4_demux *mp4_demuxer_ctx;

	demuxer_params_t params;

	fatfs_sd_params_t fatfs_params;

	char file_name[128]; //this filename is for demuxer use
	//FIL     v_file;
	//FIL     a_file;

	uint32_t demuxer_a_state; //keep the audio state
	uint32_t demuxer_v_state; //keep the video state

	uint32_t cur_a_index;
	uint32_t cur_v_index;

	uint32_t first_timestamp; //first frame timestamp
	uint32_t start_timestamp; //start at timestamp

	void *mem_pool;

	TaskHandle_t 	audio_handler;
	TaskHandle_t 	video_handler;
	xSemaphoreHandle  demuxer_sema;

	uint32_t audio_duration;
	uint32_t audio_timestamp;
	uint32_t real_audio_timestamp;
	uint32_t video_duration;
	uint32_t video_timestamp;
	uint32_t real_video_timestamp;

	uint32_t audio_format;

} demuxer_ctx_t;

extern mm_module_t demuxer_module;
#endif