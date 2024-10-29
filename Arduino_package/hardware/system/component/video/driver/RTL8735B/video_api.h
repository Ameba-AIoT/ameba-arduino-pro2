#ifndef _VIDEO_API_H_
#define _VIDEO_API_H_

#include <stdint.h>
#include <osdep_service.h>
#include "hal_video.h"

#define VIDEO_SET_RCPARAM		0x10
#define VIDEO_FORCE_IFRAME		0x11
#define VIDEO_BPS               0x12
#define VIDEO_GOP				0x13
#define VIDEO_ISPFPS			0x14
#define VIDEO_FPS               0x15
#define VIDEO_ISP_SET_RAWFMT    0x16
//#define VIDEO_OSD				0x17
#define VIDEO_PRINT_INFO        0x18
#define VIDEO_DEBUG             0x19
#define VIDEO_RC_CTRL			0x1a


#define VIDEO_HEVC_OUTPUT       0x20
#define VIDEO_H264_OUTPUT       0x21
#define VIDEO_JPEG_OUTPUT       0x22
#define VIDEO_NV12_OUTPUT       0x23
#define VIDEO_RGB_OUTPUT        0x24
#define VIDEO_NV16_OUTPUT       0x25

#define VIDEO_LOG_OFF		4
#define VIDEO_LOG_ERR		3
#define VIDEO_LOG_MSG		2
#define VIDEO_LOG_INF		1
#define VIDEO_LOG_ALL		0

#define VIDEO_H264_META_OFFSET 0x07
#define VIDEO_JPEG_META_OFFSET 0x04
#define VIDEO_HEVC_META_OFFSET 0x08

#define VIDEO_META_USER_SIZE 0x40

#define VIDEO_VPS_MAX_SIZE 0x80
#define VIDEO_SPS_MAX_SIZE 0X80
#define VIDEO_PPS_MAX_SIZE 0X20
#define VIDEO_PROFILE_MAX_SIZE 0X08

#define VIDEO_META_REV_BUF  0x1000
#define VIDEO_START_CODE_DUMMY 0x03
#define VIDEO_META_UUID_SIZE 0x10
#define VIDEO_META_3A_TAG_SIZE 0x04
#define NALU_PAYLOAD_MAX_SIZE 0X0A

/*ENCODE TYPE*/
//type : 0:HEVC 1:H264 2:JPEG 3:NV12 4:RGB 5:HEVC+JPEG 6:H264+JPEG
enum encode_type {
	VIDEO_HEVC = 0,
	VIDEO_H264,
	VIDEO_JPEG,
	VIDEO_NV12,
	VIDEO_RGB,
	VIDEO_NV16,
	VIDEO_HEVC_JPEG,
	VIDEO_H264_JPEG
};

//#define USE_ISP_RETENTION_DATA
#ifdef USE_ISP_RETENTION_DATA
typedef struct isp_retention_data_s {
	uint32_t checksum;
	uint32_t ae_exposure;
	uint32_t ae_gain;
	uint32_t awb_rgain;
	uint32_t awb_bgain;
	//uint32_t als_value; //user can check als to decide using isp init setting or not
} isp_retention_data_t;
#endif

enum isp_init_option {
	SAVE_TO_STRUCTURE = 0,
	SAVE_TO_FLASH,
	SAVE_TO_RETENTION
};

typedef struct encode_rc_parm_s {
	unsigned int rcMode;
	unsigned int iQp;		// for fixed QP
	unsigned int pQp;		// for fixed QP
	unsigned int minQp;		// for CBR/VBR
	unsigned int minIQp;	// for CBR/VBR
	unsigned int maxQp;		// for CBR/VBR
	unsigned int maxIQp;	// for CBR/VBR
} encode_rc_parm_t;

typedef struct encode_rc_adv_parm_s {
	unsigned int rc_adv_enable;
	unsigned int maxBps;		// for VBR
	unsigned int minBps;		// for VBR

	int intraQpDelta;
	int mbQpAdjustment;
	unsigned int mbQpAutoBoost;
} encode_rc_adv_parm_t;

typedef struct encode_roi_parm_s {
	unsigned int enable;
	unsigned int left;		// for fixed QP
	unsigned int right;		// for fixed QP
	unsigned int top;		// for CBR/VBR
	unsigned int bottom;	// for CBR/VBR
} encode_roi_parm_t;


typedef struct video_state_s {
	uint32_t timer_1;
	uint32_t timer_2;
	uint32_t drop_frame;
} video_state_t;

typedef struct isp_info_s {
	uint32_t sensor_width;
	uint32_t sensor_height;
	uint32_t sensor_fps;
	uint32_t osd_enable;
	uint32_t md_enable;
	uint32_t hdr_enable;
	uint32_t osd_buf_size;
	uint32_t md_buf_size;
	uint32_t frame_done_time;
} isp_info_t;

typedef struct video_sps_pps_info_s {
	int vps_len;
	int sps_len;
	int pps_len;
	unsigned char vps[VIDEO_VPS_MAX_SIZE];
	unsigned char sps[VIDEO_SPS_MAX_SIZE];
	unsigned char pps[VIDEO_PPS_MAX_SIZE];
	char sps_base64[VIDEO_SPS_MAX_SIZE];
	char pps_base64[VIDEO_PPS_MAX_SIZE];
	char vps_base64[VIDEO_VPS_MAX_SIZE];
	char profile_level_id[VIDEO_PROFILE_MAX_SIZE];
	int status;//1 get the info; 0 Not get info
	int enable;
} video_sps_pps_info_t;

typedef struct jpeg_crop_parm_s {
	uint32_t enable;
	uint32_t xmin;
	uint32_t ymin;
	uint32_t xmax;
	uint32_t ymax;
} jpeg_crop_parm_t;

#define MASK_MAX_NUM 5
#define MASK_GRID 0X00
#define MASK_RECT_ID_0 0X01
#define MASK_RECT_ID_1 0X02
#define MASK_RECT_ID_2 0X03
#define MASK_RECT_ID_3 0X04
typedef struct video_pre_init_params_s {
	uint32_t meta_enable;
	uint32_t meta_size;
	uint32_t dn_init_enable;
	uint32_t dn_init_mode;
	uint32_t isp_init_enable;
	video_isp_initial_items_t init_isp_items;
	uint32_t fast_mask_en;
	struct private_mask_s {
		uint32_t enable;
		uint32_t color;
		uint32_t en[MASK_MAX_NUM];
		uint32_t start_x[MASK_MAX_NUM];//2-align
		uint32_t start_y[MASK_MAX_NUM];//2-align
		uint32_t w[MASK_MAX_NUM];//16-align when grid-mode
		uint32_t h[MASK_MAX_NUM];
		uint32_t cols;//8-align
		uint32_t rows;
		uint8_t bitmap[160];
	} fast_mask;
	uint32_t voe_dbg_disable;
	uint32_t isp_ae_enable;
	uint32_t isp_ae_init_exposure;
	uint32_t isp_ae_init_gain;
	uint32_t isp_awb_enable;
	uint32_t isp_awb_init_rgain;
	uint32_t isp_awb_init_bgain;
	uint32_t video_drop_enable;
	uint32_t video_drop_frame;
	uint32_t video_meta_offset;//the meta offset size
	uint32_t video_meta_total_size;//the meta total size
	uint8_t video_meta_uuid[VIDEO_META_UUID_SIZE];//
	uint32_t video_meta_extend_offset;//the extend meta offset size
	uint32_t video_meta_extend_total_size;//the extend meta total size
	uint32_t meta_enable_extend;//Add the 3A info at I frame
	uint32_t meta_gop_duration;//Setup times to the I frame by gop duration.
} video_pre_init_params_t;

typedef struct private_mask_single_s {
	uint32_t en;
	uint32_t grid_mode;
	uint32_t id;//0~3 only for rect-mode
	uint32_t color;
	uint32_t start_x;//2-align
	uint32_t start_y;//2-align
	uint32_t w;//16-align when grid-mode
	uint32_t h;
	uint32_t cols;//8-align
	uint32_t rows;
	uint32_t bitmap[40];
} private_mask_single_t;

typedef struct video_param_s {
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
	struct video_roi_s {
		uint32_t xmin;
		uint32_t ymin;
		uint32_t xmax;
		uint32_t ymax;
	} roi;
	uint32_t level;
	uint32_t profile;
	uint32_t cavlc;
	/* uint32_t fast_mask_en; */
	video_sps_pps_info_t sps_pps_info;
	uint32_t out_mode;
	uint32_t ext_fmt;   //external input format: 0:I420 1:NV12 2:NV21 11:RGB888 12:BGR888
	uint32_t minQp;
	uint32_t maxQp;
	uint32_t fast_osd_en;
	uint32_t scale_up_en;  //1.only support in ch0  2.width and height should both larger than sensor size  3.cannot be used with ROI crop  4.max scale up resolution is 2688x1944
	uint32_t vui_disable;//Disable the VUI feature that the sps/pps won't be changed.
	uint32_t meta_enable;
	jpeg_crop_parm_t jpeg_crop_parm;
	uint32_t middle_crop_en;//Middle crop functio only support in ch0
} video_params_t;

typedef struct voe_info_s {
	uint32_t voe_heap_addr;
	uint32_t voe_heap_size;
	video_params_t video_info[MAX_CHANNEL];
	uint32_t stream_is_open[MAX_CHANNEL];
	uint32_t voe_mcrop_enable;
} voe_info_t;

typedef struct mult_sensor_info_s {
	uint32_t sensor_index;
	uint32_t sensor_finish;
} mult_sensor_info_t;

typedef struct video_meta_s {
	uint32_t type;
	uint32_t video_addr;
	uint32_t video_len;
	uint32_t meta_offset;
	uint32_t meta_size;
	isp_meta_t *isp_meta_data;
	isp_statis_meta_t *isp_statis_meta;
	uint8_t  *user_buf;
	uint32_t user_buf_len;
} video_meta_t;

typedef struct video_meta_read_s {
	unsigned char uuid[VIDEO_META_UUID_SIZE];
	isp_statis_meta_t isp_statis_meta;
	isp_meta_t isp_meta_data;
	unsigned char magic_num[VIDEO_META_3A_TAG_SIZE];
	af_statis_t af_result;
	ae_statis_t ae_result;
	awb_statis_t awb_result;
	unsigned char *user_input;
	int user_length;
} video_meta_read_t;

typedef struct nalu_payload_info_s {
	int offset;
	int size;
	int type;
} nalu_payload_info_t;

typedef struct video_encoder_nalu_paylaod_info_s {
	nalu_payload_info_t nalu_info[NALU_PAYLOAD_MAX_SIZE];
	int nalu_count;
} video_encoder_nalu_payload_info_t;

int video_ctrl(int ch, int cmd, int arg);

int video_set_roi_region(int ch, int x, int y, int width, int height, int value);

hal_video_adapter_t *video_init(int iq_start_addr, int sensor_start_addr);

void *video_deinit(void);

void *video_poweroff(void);

void video_set_isp_info(isp_info_t *info);

int video_buf_calc(int v1_enable, int v1_w, int v1_h, int v1_bps, int v1_shapshot,
				   int v2_enable, int v2_w, int v2_h, int v2_bps, int v2_shapshot,
				   int v3_enable, int v3_w, int v3_h, int v3_bps, int v3_shapshot,
				   int v4_enable, int v4_w, int v4_h);

int video_buf_heap_calc(int v1_enable, int v1_w, int v1_h, int v1_bps, int v1_enctype, int v1_jpg_only_shapshot,
						int v2_enable, int v2_w, int v2_h, int v2_bps, int v2_enctype, int v2_jpg_only_shapshot,
						int v3_enable, int v3_w, int v3_h, int v3_bps, int v3_enctype, int v3_jpg_only_shapshot,
						int v4_enable, int v4_w, int v4_h);

int video_extra_buf_calc(int originl_heapsize, int vext_enable, int vext_w, int vext_h, int vext_bps, int vext_shapshot);

void video_buf_release(void);

//int video_set_voe_heap(int heap_addr, int heap_size, int use_malloc);

int video_open(video_params_t *v_stream, output_callback_t output_cb, void *ctx);

int video_close(int ch);

int video_get_stream_info(int id);

int video_encbuf_clean(int ch, int codec);

int video_encbuf_release(int ch, int codec, int mode);

int video_ispbuf_release(int ch, int addr);

int isp_ctrl_cmd(int argc, char **argv);

int iq_tuning_cmd(int argc, char **argv);

int video_i2c_cmd(int argc, char **argv);

void video_init_peri(void);

void video_deinit_peri(void);

void video_set_debug_level(int value);//Default level -> VIDEO_LOG_MSG

void video_set_uvcd_iq(unsigned int addr);

void video_set_uvcd_sensor(unsigned int addr);

unsigned char *video_get_iq_buf(void);

int video_get_video_sensor_status(void);

void video_get_fcs_info(void *isp_fcs_info);

int video_fcs_write_sensor_id(int SensorName);

void video_set_video_snesor_info(mult_sensor_info_t *info);

int video_reset_fw(int ch, int id);

int voe_get_sensor_info(int id, int *iq_data, int *sensor_data);

void voe_t2ff_prealloc(void);

int voe_boot_fsc_status(void);

int voe_boot_fsc_id(void);

void video_set_fcs_queue_info(int start_time, int end_time);

void video_get_fcs_queue_info(int *start_time, int *end_time);

int video_get_maxqp(int ch);

int video_set_private_mask(int ch, struct private_mask_s *pmask);

void video_set_private_mask_single(int ch, private_mask_single_t *pmask);

int video_get_buffer_info(int ch, int *enc_size, int *out_buf_size, int *out_rsvd_size);

int video_get_sps_pps(unsigned char *frame_buf, unsigned int frame_size, int ch, video_sps_pps_info_t *info);

void voe_get_cmd_timout_info(uint32_t *cmd, int *timeout);

void voe_set_cmd_timout(int min_timeout, int max_timeout);
uint32_t video_get_video_timer_cur_time(void);

uint32_t video_get_system_ts_from_isp_ts(uint32_t cur_system_ts, uint32_t cur_isp_ts, int channel);

int video_ext_in(int ch, uint32_t addr);

void video_get_version(void);

int video_get_fcs_cost_time(void);//The unit is ms for fcs cost time from bootloader to frame done

int video_get_sps_pps_vps(unsigned char *frame_buf, unsigned int frame_size, int ch, video_sps_pps_info_t *info);

void video_pre_init_setup_parameters(video_pre_init_params_t *parm);

video_pre_init_params_t* video_get_pre_init_setup_params(void);

void video_pre_init_load_params(enum isp_init_option save_option);

void video_pre_init_save_cur_params(int meta_enable, video_meta_t *meta_data,
									enum isp_init_option save_option); //save_to_flash 0: only save to pre init structure, 1: save to flash, 2: save to sram retention

int video_pre_init_get_meta_enable(void);

void video_sei_write(video_meta_t *m_parm);

void video_sei_read(video_meta_read_t *meta_read, unsigned char *video_input, video_meta_t *m_parm);

int video_get_meta_offset(int meta_size);

int video_open_status(void);//0:No video open 1:video open

int video_get_encoder_nalu_payload_info(unsigned char *frame_buf, unsigned int frame_size, int codec_type, video_encoder_nalu_payload_info_t *info);

//////////////////////
#define VOE_NAND_FLASH_OFFSET 0x8000000
#define FW_1 0x01
#define FW_2 0x02
#endif

