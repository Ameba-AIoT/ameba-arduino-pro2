#ifndef _VIDEO_BOOT_H_
#define _VIDEO_BOOT_H_

#include <stdint.h>
#include "fw_img_export.h"

#define ISP_COMMON_BUF  900*1024
#define ENC_COMMON_BUF  500*1024
#define ENABLE_OSD_BUF  900*1024
#define ENABLE_MD_BUF   500*1024
#define ENABLE_HDR_BUF  500*1024

#define ISP_CREATE_BUF 200*1024
#define ENC_CREATE_BUF 420*1024
#define SNAPSHOT_BUF   300*1024

#define V1_ENC_BUF_SIZE  8 //sec
#define V2_ENC_BUF_SIZE  8 //sec
#define V3_ENC_BUF_SIZE  8 //sec
#define VIDEO_RSVD_DIVISION 8

#define STREAM_V1 0
#define STREAM_V2 1
#define STREAM_V3 2
#define STREAM_V4 3

#define VIDEO_MAX_NUM 4

#define FCS_SYSTEM_REV_SIZE 32
#define FCS_USER_REV_SIZE   32

#define VIDEO_BOOT_STRUCT_MAX_SIZE ((2*1024) - (32*2))

#define MAX_FCS_CHANNEL 2

#define FCS_TALBE_NUM  11 //The parameter can't be changed

typedef struct video_boot_param_s {
	uint32_t stream_id;
	uint32_t type;
	uint32_t resolution;
	uint32_t width;
	uint32_t height;
	uint32_t bps;
	uint32_t fps;
	uint32_t gop;
	uint32_t rc_mode;
	uint32_t jpeg_qlevel;
	uint32_t rotation;
	uint32_t out_buf_size;
	uint32_t out_rsvd_size;
	uint32_t direct_output;
	uint32_t use_static_addr;
	uint32_t fcs;
	uint32_t use_roi;
	struct video_boot_roi_s {
		uint32_t xmin;
		uint32_t ymin;
		uint32_t xmax;
		uint32_t ymax;
	} roi;
	uint32_t level;
	uint32_t profile;
	uint32_t cavlc;
} video_boot_params_t;

typedef struct isp_boot_info_s {
	uint32_t sensor_width;
	uint32_t sensor_height;
	uint32_t sensor_fps;
	uint32_t osd_enable;
	uint32_t md_enable;
	uint32_t hdr_enable;
	uint32_t osd_buf_size;
	uint32_t md_buf_size;
} isp_boot_info_t;
//Please don't change the structure sequence because the data structure is shared by lib boot.
typedef struct video_boot_stream_cfg {
	video_boot_params_t video_params[VIDEO_MAX_NUM];
	isp_boot_info_t isp_info;
	uint32_t voe_heap_addr;
	uint32_t voe_heap_size;
	uint8_t video_enable[VIDEO_MAX_NUM];
	uint8_t video_snapshot[VIDEO_MAX_NUM];
	uint8_t video_drop_frame[VIDEO_MAX_NUM];
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
	uint32_t fcs_als_thr[FCS_TALBE_NUM];
	uint32_t fcs_isp_ae_table_exposure[FCS_TALBE_NUM];
	uint32_t fcs_isp_ae_table_gain[FCS_TALBE_NUM];
	uint32_t fcs_isp_awb_table_rgain[FCS_TALBE_NUM];
	uint32_t fcs_isp_awb_table_bgain[FCS_TALBE_NUM];
	uint32_t fcs_isp_mode_table[FCS_TALBE_NUM];
	uint32_t fcs_isp_iq_id;//0
	uint8_t  fcs_isp_reserved_buf[FCS_SYSTEM_REV_SIZE];//Reserved for fcs system data
	uint8_t  fcs_user_buffer[FCS_USER_REV_SIZE];//User can use the buffer to transfer to application
	uint32_t fcs_start_time;//bootloader to fcs user boot function
	uint32_t fcs_voe_time;//bootloader to voe init function
} video_boot_stream_t;
#endif

