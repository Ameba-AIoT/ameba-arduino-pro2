#ifndef _VIDEO_BOOT_H_
#define _VIDEO_BOOT_H_

#include <stdint.h>
#include "fw_img_export.h"

// USE_NEW_HEAP_ALLOCATE
#define ENABLE_HDR_MD_BUF   600*1024

#define ISP_COMMON_MAIN_BUF         800*1024
#define ISP_COMMON_MAIN_SW_MARGIN   40*1024
#define ISP_COMMON_EXTRA_BUF        100*1024
#define ISP_COMMON_EXTRA_SW_MARGIN  50*1024

#define ENC_COMMON_MAIN_BUF         859*1024
#define ENC_COMMON_MAIN_SW_MARGIN   799*1024
#define ENC_COMMON_EXTRA_BUF        391*1024
#define ENC_COMMON_EXTRA_SW_MARGIN  331*1024

#define JPG_COMMON_MAIN_BUF     27*1024
#define JPG_COMMON_EXTRA_BUF    27*1024
#define JPG_BUF_SIZE            5 //picture

// USE_OLD_HEAP_ALLOCATE
#define ENABLE_MD_BUF   500*1024
#define ENABLE_HDR_BUF  500*1024

#define ISP_CREATE_BUF 750*1024
#define ENC_CREATE_BUF (859+59)*1024

//SNAPSHOT AND OSD
#define SNAPSHOT_BUF   300*1024
#define OSD_CREATE_BUF (10*1024+24*480) //default 24 blocks, each one require 480 bytes

#define V1_ENC_BUF_SIZE  8 //sec
#define V2_ENC_BUF_SIZE  8 //sec
#define V3_ENC_BUF_SIZE  8 //sec
#define VIDEO_RSVD_DIVISION 8

#define STREAM_V1 0
#define STREAM_V2 1
#define STREAM_V3 2
#define STREAM_V4 3

#define STREAM_ID_V1 0
#define STREAM_ID_V2 1
#define STREAM_ID_V3 2
#define STREAM_ID_V4 4
#define STREAM_ID_VEXTRA 3

#define VIDEO_MAX_NUM 4

#define FCS_SYSTEM_REV_SIZE 32
#define FCS_USER_REV_SIZE   32

#define VIDEO_BOOT_STRUCT_MAX_SIZE ((2*1024) - (32*2))

#define MAX_FCS_CHANNEL 4

#define FCS_TALBE_NUM  11 //The parameter can't be changed

#define VIDEO_BOOT_META_USER_SIZE 0X40

#define VIDEO_BOOT_META_REV_BUF  0x1000

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
	uint32_t minQp;
	uint32_t maxQp;
	uint32_t fcs_vui_disable;
} video_boot_params_t;
#define PRIVATE_MAX_NUM 5
#define PRIVATE_MASK_GRID 0X00
#define PRIVATE_MASK_RECT_ID_0 0X01
#define PRIVATE_MASK_RECT_ID_1 0X02
#define PRIVATE_MASK_RECT_ID_2 0X03
#define PRIVATE_MASK_RECT_ID_3 0X04
typedef struct video_boot_private_mask_s {
	uint32_t enable;
	uint32_t color;
	uint32_t en[PRIVATE_MAX_NUM];
	uint32_t start_x[PRIVATE_MAX_NUM];//2-align
	uint32_t start_y[PRIVATE_MAX_NUM];//2-align
	uint32_t w[PRIVATE_MAX_NUM];//16-align when grid-mode
	uint32_t h[PRIVATE_MAX_NUM];
	uint32_t cols;//8-align
	uint32_t rows;
	uint8_t bitmap[160];
} video_boot_private_mask_t;

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

typedef struct fcs_rate_control {
	uint32_t sampling_time;
	uint32_t maximun_bitrate;
	uint32_t minimum_bitrate;
	uint32_t target_bitrate;
} fcs_rate_ctrl_t;

typedef struct  {
	uint32_t enable;
	uint32_t init_flicker;
	uint32_t init_saturation;
	int32_t init_brightness;
	uint32_t init_contrast;
	uint32_t init_hue;
	uint32_t init_wdr_mode;
	uint32_t init_wdr_level;
	uint32_t init_hdr_mode;
	uint32_t init_mirrorflip;
} video_boot_isp_initial_items_t;

//Please don't change the structure sequence because the data structure is shared by lib boot.
typedef struct video_boot_stream_cfg {
	video_boot_params_t video_params[VIDEO_MAX_NUM];
	fcs_rate_ctrl_t auto_rate_control[2];
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
	uint32_t fcs_isp_init_daynight_mode;//0 day mode ; 1 night mode
	uint32_t fcs_isp_gray_mode;//0 color mode ; 1 gray mode
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
	video_boot_private_mask_t private_mask;
	uint32_t meta_enable;//
	uint32_t meta_size;//enalbe the meta size for
	video_boot_isp_initial_items_t init_isp_items;
	uint32_t fcs_meta_offset;
	uint32_t fcs_meta_total_size;
	uint32_t extra_fcs_meta_enable_extend;
	uint32_t extra_fcs_meta_extend_offset;
	uint32_t extra_fcs_meta_extend_total_size;
} video_boot_stream_t;

void video_boot_setup_slot_num(int stream_id, int slot_number);
#endif

