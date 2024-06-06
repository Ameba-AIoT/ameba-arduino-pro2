#ifndef _MODULE_VIDEO_H
#define _MODULE_VIDEO_H

#include <stdint.h>
#include <osdep_service.h>
#include "mmf2_module.h"
#include "video_api.h"

#define CMD_VIDEO_SET_PARAMS     	MM_MODULE_CMD(0x00)  // set parameter
#define CMD_VIDEO_GET_PARAMS     	MM_MODULE_CMD(0x01)  // get parameter
#define CMD_VIDEO_SET_HEIGHT		MM_MODULE_CMD(0x02)
#define CMD_VIDEO_SET_WIDTH			MM_MODULE_CMD(0x03)
#define CMD_VIDEO_BITRATE			MM_MODULE_CMD(0x04)
#define CMD_VIDEO_FPS				MM_MODULE_CMD(0x05)
#define CMD_VIDEO_GOP				MM_MODULE_CMD(0x06)
#define CMD_VIDEO_MEMORY_SIZE		MM_MODULE_CMD(0x07)
#define CMD_VIDEO_BLOCK_SIZE		MM_MODULE_CMD(0x08)
#define CMD_VIDEO_MAX_FRAME_SIZE	MM_MODULE_CMD(0x09)
#define CMD_VIDEO_RCMODE			MM_MODULE_CMD(0x0a)
#define CMD_VIDEO_SET_RCPARAM		MM_MODULE_CMD(0x0b)
#define CMD_VIDEO_GET_RCPARAM		MM_MODULE_CMD(0x0c)
#define CMD_VIDEO_INIT_MEM_POOL		MM_MODULE_CMD(0x0d)
#define CMD_VIDEO_FORCE_IFRAME		MM_MODULE_CMD(0x0e)
#define CMD_VIDEO_ISPFPS			MM_MODULE_CMD(0x0f)
#define CMD_VIDEO_SET_RCADVPARAM	MM_MODULE_CMD(0x10)
#define CMD_VIDEO_GET_RCADVPARAM	MM_MODULE_CMD(0x11)
#define CMD_VIDEO_SET_ROIPARM		MM_MODULE_CMD(0x12)
#define CMD_VIDEO_SET_ROI			MM_MODULE_CMD(0x13)
#define CMD_VIDEO_SET_QPCHROMA_OFFSET    MM_MODULE_CMD(0x14)
#define CMD_VIDEO_SET_FORCE_DROP_FRAME   MM_MODULE_CMD(0x15)


#define CMD_VIDEO_STREAMID		    MM_MODULE_CMD(0x16)
#define CMD_VIDEO_FORMAT			MM_MODULE_CMD(0x17)
#define CMD_VIDEO_DUMP_STATE		MM_MODULE_CMD(0x18)
#define CMD_VIDEO_BPS               MM_MODULE_CMD(0x19)
#define CMD_VIDEO_SNAPSHOT          MM_MODULE_CMD(0x1a)
#define CMD_VIDEO_SNAPSHOT_CB       MM_MODULE_CMD(0x1b)
#define CMD_VIDEO_YUV               MM_MODULE_CMD(0x1c)
#define CMD_ISP_SET_RAWFMT          MM_MODULE_CMD(0x1d)
#define CMD_VIDEO_PRINT_INFO        MM_MODULE_CMD(0x1e)
#define CMD_VIDEO_SET_MULTI_RCCTRL	MM_MODULE_CMD(0x1f)



#define CMD_VIDEO_APPLY				MM_MODULE_CMD(0x20)  // apply setting
#define CMD_VIDEO_UPDATE			MM_MODULE_CMD(0x21)  // update new setting
#define CMD_VIDEO_STREAM_STOP		MM_MODULE_CMD(0x23)  // stop stream

#define CMD_VIDEO_SET_VOE_HEAP      MM_MODULE_CMD(0x24)
#define CMD_VIDEO_SET_TIMESTAMP_OFFSET      MM_MODULE_CMD(0x25)

#define CMD_SNAPSHOT_ENCODE_CB		MM_MODULE_CMD(0x30)


#define CMD_VIDEO_MD_SET_ROI		MM_MODULE_CMD(0x31)
#define CMD_VIDEO_MD_SET_SENSITIVITY	MM_MODULE_CMD(0x32)
#define CMD_VIDEO_MD_START			MM_MODULE_CMD(0x33)
#define CMD_VIDEO_MD_STOP			MM_MODULE_CMD(0x34)

#define CMD_VIDEO_META_CB		    MM_MODULE_CMD(0x35)
#define CMD_VIDEO_SET_PRIVATE_MASK  MM_MODULE_CMD(0x36)

#define CMD_VIDEO_SET_RATE_CONTROL		MM_MODULE_CMD(0x40)
#define CMD_VIDEO_GET_CURRENT_BITRATE	MM_MODULE_CMD(0x41)
#define CMD_VIDEO_GET_REMAIN_QUEUE_LENGTH	MM_MODULE_CMD(0x42)
#define CMD_VIDEO_GET_MAX_QP		MM_MODULE_CMD(0x43)
#define CMD_VIDEO_SET_MAX_QP		MM_MODULE_CMD(0x44)

#define CMD_VIDEO_SET_SPS_PPS_INFO  MM_MODULE_CMD(0x45)
#define CMD_VIDEO_GET_SPS_PPS_INFO  MM_MODULE_CMD(0x46)

#define CMD_VIDEO_SET_RATE_CONTROL_FPS_STAGE		MM_MODULE_CMD(0x47)

#define CMD_VIDEO_SET_EXT_INPUT     MM_MODULE_CMD(0x50)

#define CMD_VIDEO_SPS_CB            MM_MODULE_CMD(0x51)

#define CMD_VIDEO_PRE_INIT_PARM     MM_MODULE_CMD(0x52)
#define CMD_VIDEO_PRE_INIT_LOAD  	MM_MODULE_CMD(0x53)
#define CMD_VIDEO_PRE_INIT_SAVE  	MM_MODULE_CMD(0x54)

#define MMF_VIDEO_DEFAULT_META_CB	(0xFFFFFFFF)

typedef struct rate_control {
	uint32_t sampling_time;
	uint32_t maximun_bitrate;
	uint32_t minimum_bitrate;
	uint32_t target_bitrate;
} rate_ctrl_t;

typedef struct rate_control_param {
	int rate_ctrl_en;
	uint32_t sample_bitrate;
	uint32_t current_bitrate;
	uint32_t current_framerate;
	uint32_t current_maxqp;
	rate_ctrl_t rate_ctrl;
	uint32_t minimum_framerate;
	uint32_t ori_framerate;
	uint32_t fps_stage[3];
	uint32_t fps_stage_idx;
} rate_ctrl_param_t;

typedef struct video_ctx_s {
	void *parent;

	hal_video_adapter_t *v_adp;
	void *mem_pool;

	video_params_t params;
	int (*snapshot_cb)(uint32_t, uint32_t);
	void (*change_parm_cb)(void *);
	video_state_t state;
	uint32_t timestamp_offset;
	video_meta_t meta_data;
	void (*meta_cb)(void *);
	void (*sps_pps_cb)(void *);
	rate_ctrl_param_t rate_ctrl_p;
} video_ctx_t;

extern mm_module_t video_module;


int video_voe_presetting(int v1_enable, int v1_w, int v1_h, int v1_bps, int v1_shapshot,
						 int v2_enable, int v2_w, int v2_h, int v2_bps, int v2_shapshot,
						 int v3_enable, int v3_w, int v3_h, int v3_bps, int v3_shapshot,
						 int v4_enable, int v4_w, int v4_h);

int video_voe_presetting_by_params(const void *v1_params, int v1_jpg_only_shapshot, const void *v2_params, int v2_jpg_only_shapshot, const void *v3_params,
								   int v3_jpg_only_shapshot, const void *v4_params);

void video_voe_release(void);
void video_set_sensor_id(int SensorName);
void video_setup_sensor(void *sensor_setup_cb);
void video_show_fps(int enable);
int video_get_cb_fps(int chn);
void video_set_fps_dropframe_mode(int drop_frame);
#endif