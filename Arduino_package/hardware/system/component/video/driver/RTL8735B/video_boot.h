#ifndef _VIDEO_BOOT_H_
#define _VIDEO_BOOT_H_

#include <stdint.h>
#include "rtl8735b_voe_cmd.h"
#include "rtl8735b_voe_type.h"
#include "rtl8735b_voe_status.h"
#include "hal.h"
#include "base_type.h"
#include "hal_voe.h"
#include "hal_video.h"
#include "video_api.h"
#include "fw_img_export.h"

#define ISP_COMMON_BUF  900*1024
#define ENC_COMMON_BUF  500*1024
#define ENABLE_OSD_BUF  900*1024
#define ENABLE_MD_BUF   500*1024
#define ENABLE_HDR_BUF  500*1024

#define ISP_CREATE_BUF 200*1024
#define ENC_CREATE_BUF 420*1024
#define SNAPSHOT_BUF   300*1024

#define V1_ENC_BUF_SIZE  16 //sec
#define V2_ENC_BUF_SIZE  16 //sec
#define V3_ENC_BUF_SIZE  16 //sec

#define STREAM_V1 0
#define STREAM_V2 1
#define STREAM_V3 2
#define STREAM_V4 3

typedef struct video_boot_stream_cfg {
	video_params_t video_params[4];
	isp_info_t isp_info;
	uint32_t voe_heap_addr;
	uint32_t voe_heap_size;
	uint8_t video_enable[4];
	uint8_t video_snapshot[4];
	uint8_t video_drop_frame[4];
	isp_multi_fcs_ld_info_t p_fcs_ld_info;
	uint32_t fcs_channel;//channel -> 0~3
	uint32_t fcs_status;// status  -> 1:successful 0:fail
	uint32_t fcs_setting_done;// status  -> 1:successful 0:fail
	uint32_t fcs_voe_fw_addr;//
	uint32_t fcs_isp_ae_enable;
	uint32_t fcs_isp_ae_init_exposure;
	uint32_t fcs_isp_ae_init_gain;
	uint32_t fcs_isp_awb_enable;
	uint32_t fcs_isp_awb_init_rgain;
	uint32_t fcs_isp_awb_init_bgain;
	uint32_t fcs_isp_init_daynight_mode;//0 night mode ; 1 day mode
	uint32_t fcs_lookup_count;
	uint32_t fcs_als_thr[11];
	uint32_t fcs_isp_ae_table_exposure[11];
	uint32_t fcs_isp_ae_table_gain[11];
	uint32_t fcs_isp_awb_table_rgain[11];
	uint32_t fcs_isp_awb_table_bgain[11];
	uint32_t fcs_isp_mode_table[11];
	uint32_t fcs_isp_iq_id;//0
} video_boot_stream_t;
#endif

