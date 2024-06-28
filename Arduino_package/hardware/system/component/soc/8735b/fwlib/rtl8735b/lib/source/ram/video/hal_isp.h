/*
 * hal_isp.h
 *
 *  Created on: 2021¦~3¤ë17¤é
 *      Author: martinhuang
 */

#ifndef HAL_RTL8735B_LIB_SOURCE_RAM_VIDEO_ISP_HAL_ISP_H_
#define HAL_RTL8735B_LIB_SOURCE_RAM_VIDEO_ISP_HAL_ISP_H_

#if !defined (CONFIG_VOE_PLATFORM) || !CONFIG_VOE_PLATFORM // Run on TM9
#include "cmsis.h"
#else
#include "cmsis_voe.h"
//#include "voe.h"
#endif

#define TOTAL_STEAM_NUM 5
#define MAX_SW_BUFFER 5
//#define RTS_VIDEOIN_HEIGHT_ALIGN	16

typedef struct hal_isp_buffer {
	int	state;
	uint32_t buf_addr;
	uint32_t org_buf_addr;
} hal_isp_buffer_t;


enum ameba_stream_fmt {
	NV12_FORMAT,
	NV16_FORMAT,
	NV21_FORMAT,
	NV61_FORMAT,
	RGB888_FORMAT
};

enum ISP_3A_statis_mode {
	AF_STATIS,
	AE_STATIS,
	AWB_STATIS
};


typedef struct hal_isp_stream_stream {

	__u8 streamid;	/*initialized by user*/

	uint32_t fmt;
	uint32_t user_width;
	uint32_t user_height;

	uint32_t rate_numerator;
	uint32_t rate_denominator;
	int fnum;

	unsigned long frame_count;
	unsigned long skip_count;
	unsigned long overflow_count;
	unsigned long error_count;

	hal_isp_buffer_t bufs[MAX_SW_BUFFER];

	uint8_t hw_slot_num;	/*initialized by user*/
	uint8_t buff_num;
	uint8_t	bits_pixel;

	int buf_release_cnt[MAX_SW_BUFFER];
	int stream_running;

	uint32_t crop_x;
	uint32_t crop_y;
	uint32_t crop_w;
	uint32_t crop_h;

	uint32_t sync;
} hal_isp_stream_t;


typedef struct {


	hal_isp_stream_t video_stream[TOTAL_STEAM_NUM];


	uint16_t snr_width;
	uint16_t snr_height;

	uint16_t fr_width;
	uint16_t fr_height;

	uint16_t fr_cnt;
	uint8_t sub_module;
	uint8_t vhdr;

	uint32_t short_exp_line;

	uint16_t fps;
	uint8_t path;
	uint8_t fixp_sensor;

	uint8_t dec_format;
	uint8_t raw_source;
	uint8_t dec_id;
	uint8_t ssor_clock;

	uint32_t isp_enable;
	uint32_t vhdr_ctrl;
	uint32_t vhdr_ratio;
	uint32_t mipi_buffer;

	uint32_t t_line_blk; //ns

	uint32_t interface_clk;
	uint32_t pixel_clk;
	uint32_t isp_clk;

//    uint32_t *addr3dnr;
	uint32_t addr_md0;
	uint32_t addr_md1;

	uint32_t addr_statics;

	//u32 isp_start_init_time;
	//u32 isp_start_time;
	//u32 isp_end_time;

	void *v_adapter;

	int isp_init_done;
	int stream_condtion; // bit0: yuv_stream0, bit1: yuv_stream1, , bit2: yuv_stream2, bit4: rgb_stream,
	int isp_device_probe_done;

	int *iq_addr;		// Added By Raymond for load iq.bin

	uint8_t fcs_ready;


	uint32_t isp_init_start;
	uint32_t isp_init_end;
	uint32_t isp_open_start;
	uint32_t isp_open_end;
	uint32_t isp_start_start;
	uint32_t isp_start_end;

	uint32_t set_pwr_time;
	uint32_t set_i2c_time;
	uint32_t set_i2c_end_time;
	uint32_t sensor_start;
	uint32_t sensor_end;
	uint32_t first_frame_done;
	uint32_t voe_open_start;
	uint32_t set_frmival_time;
	uint32_t streamon_time;

	uint32_t raw_fmt;

//	uint32_t md_en;

	uint32_t sensor_rst_pin;
	uint32_t sensor_pwdn_pin;
	uint32_t sensor_pwrctrl_pin;
	uint32_t i2c_id;
	uint32_t daynight_mode;
	uint32_t init_hdr_mode;
	uint32_t init_mirrorflip_mode;

	int *cali_iq_addr;		// Add for store input calibration iq data

} __attribute__((aligned(32))) hal_isp_adapter_t;


typedef struct {

	uint32_t osd_status;
	uint32_t md_status;
	uint32_t isp_status_1;
	uint32_t stream_status[5];

	uint32_t status_reserved[8];

	uint32_t i2c_err;
	uint32_t gpio_err;
	uint32_t clk_err;
	uint32_t timer_err;

	uint32_t irq_th_status;
	uint32_t statis_th_statis;
	uint32_t isp_frdn_th_statis;
	uint32_t isp_main_th_statis;

	uint32_t isp_module_err[36];

	uint32_t reserved[16];

} __attribute__((aligned(32))) isp_status_t;

// isp_status_1 bit definition //
#define STREAM_OPEN_STATUS_SHIFT_BIT     0


typedef struct {

	uint32_t frame_count;
	uint32_t num0;
	uint32_t sum0;
	uint32_t num1;
	uint32_t sum1;
	uint32_t win_cnt;

	uint32_t reserved[2];

} __attribute__((aligned(32))) af_statis_t;

typedef struct {

	//uint16_t y_mean[256];
	uint32_t hist[256];
	uint32_t frame_count;
	uint32_t win_cnt;
	uint32_t reserved[2];

} __attribute__((aligned(32))) ae_statis_t;

typedef struct {


	//uint16_t r_mean[256]; /* 12.0 bit precision */
	//uint16_t g_mean[256]; /* 12.0 bit precision */
	//uint16_t b_mean[256]; /* 12.0 bit precision */
	uint16_t rg[256]; /* 3.8 bit precision */
	uint16_t bg[256]; /* 3.8 bit precision */
	uint32_t frame_count;
	uint32_t win_cnt;
	uint32_t reserved[2];

} __attribute__((aligned(32))) awb_statis_t;

typedef struct {

	int exposure_h;
	int gain_h;
	int exposure_l;
	int gain_l;

	int wb_r_gain;
	int wb_b_gain;
	int wb_g_gain;
	int colot_temperature;

	int y_average;
	uint32_t white_num;
	uint32_t rg_sum;
	uint32_t bg_sum;

	int hdr_mode;
	int sensor_fps;
	int max_fps;
	int frame_count;

	u32 time_stamp;

	uint32_t wdr_hist_contrast;
	uint32_t wdr_hist_contrast_origin;
	uint32_t reserved;

} isp_statis_meta_t;

#define ISP_MASK_GRID_NUM 1
#define ISP_MASK_RECT_NUM 4
#define ISP_MASK_NUM (ISP_MASK_GRID_NUM + ISP_MASK_RECT_NUM)
#define ISP_MASK_GRID_COLS 40
#define ISP_MASK_GRID_ROWS 30
#define ISP_MASK_GRID_CELLS (ISP_MASK_GRID_COLS * ISP_MASK_GRID_ROWS)

typedef struct {
	int start_x;
	int start_y;
	int cell_w;
	int cell_h;
	int cols;
	int rows;
} isp_grid_t;

typedef struct {

	int left;
	int top;
	int right;
	int bottom;

} isp_rect_t;

typedef struct {

	int start_x;
	int start_y;
	int width;
	int height;

} isp_crop_t;


typedef struct {
	isp_grid_t grid;
	uint8_t bitmap[ISP_MASK_GRID_CELLS / 8];

} isp_grid_mask_entry_t;



enum _isp_mask_action {
	ISP_MASK_KEEP,
	ISP_MASK_SET,
	ISP_MASK_CLEAR
};

typedef struct {
	uint32_t color; /* rgb888 */
	int grid_mask_set_status;
	isp_grid_mask_entry_t grid_mask;
	int rect_mask_set_status[ISP_MASK_RECT_NUM];
	isp_rect_t rect_mask[ISP_MASK_RECT_NUM];
} __attribute__((aligned(32))) isp_mask_group_t;

#define IQ_CALI_EN_AWB  (0x1 << 0)
#define IQ_CALI_EN_MLSC (0x1 << 1)
#define IQ_CALI_EN_NLSC (0x1 << 2)

struct isp_iq_cali_point {
	int32_t x;
	int32_t y;
} __attribute__((packed));

struct isp_iq_cali_nlsc {
	struct isp_iq_cali_point r_center;
	struct isp_iq_cali_point g_center;
	struct isp_iq_cali_point b_center;
	float curve_ratio;
} __attribute__((packed));

struct isp_iq_cali_mlsc_u8 {
	uint8_t matrix_r[1536];
	uint8_t matrix_g[1536];
	uint8_t matrix_b[1536];
} __attribute__((packed));

struct isp_iq_cali_awb {
	int32_t x_offset;
	int32_t y_offset;
} __attribute__((packed));

struct isp_iq_cali {
	uint8_t enable;
	struct isp_iq_cali_awb awb;
	struct isp_iq_cali_mlsc_u8 mlsc;
	struct isp_iq_cali_nlsc nlsc;
} __attribute__((packed));

#define RTSV_BRIGHTNESS           0x0000
#define RTSV_CONTRAST             0x0001
#define RTSV_SATURATION           0x0002
//#define RTSV_HUE		          0x0003
#define RTSV_AUTO_WHITE_BALANCE   0x000C
#define RTSV_RED_BALANCE          0x000E
#define RTSV_BLUE_BALANCE         0x000F
#define RTSV_GAMMA                0x0010
#define RTSV_EXPOSURE             0x0011
#define RTSV_AUTOGAIN             0x0012
#define RTSV_GAIN                 0x0013
#define RTSV_ANTI_FLICKER         0x0018   //DISABLE = 0, 50HZ = 1, 60HZ = 2, AUTO = 3
#define RTSV_DAY_NIGHT            0xF002
#define RTSV_LDC                  0xF008
#define RTSV_GRAY                 0xF009
#define RTSV_WDR_MODE             0xF00C   // 0: DISABLE, 1: MANUAL, 2: AUTO
#define RTSV_WDR_LEVEL            0xF00D
#define RTSV_SENSOR_MIRROR_FLIP   0xF020   // bit 0: MIRROR, bit 1: Flip
#define RTSV_AE_MIN_FPS           0xF021
#define RTSV_AE_MAX_FPS           0xF022

void *isp_soc_start(hal_isp_adapter_t *isp_adpt);
int isp_open_stream(hal_isp_adapter_t *isp_adpt, uint8_t stream_id);
int isp_close_stream(hal_isp_adapter_t *isp_adpt, uint8_t stream_id);
int isp_get_stream_cnt(uint8_t stream_id);
uint32_t isp_get_frame_buffer(uint8_t stream_id);
int isp_release_frame_buffer(uint8_t stream_id, uint32_t buf_addr);
int isp_locate_buffer(hal_isp_adapter_t *isp_adpt, uint8_t stream_id);
int isp_free_buffer(hal_isp_adapter_t *isp_adpt, uint8_t stream_id);
int check_isp_soc_start_done(hal_isp_adapter_t *isp_adpt);
int hal_isp_init(hal_isp_adapter_t *isp_adpt);
int hal_isp_set_raw_fmt(uint8_t streamid, uint32_t fmt);

void hal_isp_update_fcs_status(uint8_t fcs_status);

int hal_isp_set_sensor_mode(int mode, int fps); // mode 0: linear 1: hdr
int hal_isp_get_sensor_mode(int *mode, int *fps); // mode 0: linear 1: hdr

int hal_isp_get_af_statis(af_statis_t *p_af_statis);
int hal_isp_get_ae_statis(ae_statis_t *p_ae_statis);
int hal_isp_get_awb_statis(awb_statis_t *p_awb_statis);
int hal_isp_get_ctrl(uint32_t id, int *value);
int hal_isp_set_ctrl(uint32_t id, int *value);
int hal_isp_set_init_ae(int init_exposure, int init_gain);
int hal_isp_set_init_awb(int init_r_gain, int init_b_gain);
void hal_isp_set_drop_frame_num(uint32_t num);
void hal_isp_set_drop_frame_num_sw(uint32_t num);
int hal_isp_set_init_dn_mode(int dn_mode);
void hal_isp_set_direct_i2c_mode(uint32_t direct_i2c_mode);
int hal_isp_set_init_gray_mode(int gray_mode);
int hal_isp_get_real_fps(int ch, int *fps100);
int hal_isp_get_ae_weight(uint8_t *weights, int *win_num);
int hal_isp_set_ae_weight(uint8_t *weights, int win_num);
int hal_isp_set_mask(isp_mask_group_t *input_mask);
int hal_isp_config_iq_calibration(int config_flag);
void hal_isp_set_hdr_mode(uint32_t hdr_mode);
void hal_isp_set_mirrorflip_mode(uint32_t mirrorflip_mode);
int hal_isp_set_stream_fps(uint32_t ch, uint32_t fps);
void hal_isp_set_init_frame_rate(u32 val);
u32 hal_isp_get_init_frame_rate(void);

#endif /* HAL_RTL8735B_LIB_SOURCE_RAM_VIDEO_ISP_HAL_ISP_H_ */
