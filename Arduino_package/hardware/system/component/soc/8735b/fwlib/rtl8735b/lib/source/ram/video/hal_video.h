/**************************************************************************//**
 * @file     hal_video.h
 * @brief    The HAL API implementation for the Video device.
 * @version  V1.00
 * @date     2021-01-14
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2021 Realtek Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************/


#ifndef _HAL_VIDEO_H_
#define _HAL_VIDEO_H_


#if !defined (CONFIG_VOE_PLATFORM) || !CONFIG_VOE_PLATFORM // Run on TM9
#include "platform_stdlib.h"
#include "cmsis.h"
#include "hal.h"
#include "hal_voe.h"

#include "rtl8735b_voe_type.h"
#include "rtl8735b_voe_cmd.h"


#endif

#include "base_type.h"
#include "hal_video_common.h"

#include "hal_md_util.h"
#include "hal_isp.h"



#ifdef  __cplusplus
extern "C"
{
#endif


#define MAX_ENC_BUF				16
#define USER_DEFINED_QTABLE		10

#define MOVING_AVERAGE_FRAMES	120
#define MAX_CHANNEL 			5					// Channel 4 is RGB only
#define MAX_OBJECT				10



#define MODE_DISABLE			0					// disable output
#define MODE_SNAPSHOT			1					// one-shot JPEG,   for jpeg
#define MODE_ENABLE				2					// continue output
#define MODE_QUEUE				3					// queue on VOE
#define MODE_SYNC				4					// keep ISP on VOE, for channel
#define MODE_EXT				5					// external input,  for channel

//#define MV_CUINFO_EN

/**
 * @addtogroup hal_enc Encoder
 * @ingroup 8735b_hal
 * @{
 * @brief The Encoder HAL module.
 */

/*  Macros for Encoder module system related configuration  */
/** @defgroup GROUP_ENC_MODULE_SYSTEM_CONFIGURATION ENC SYSTEM CONFIGURATION
 *  enc system related configuration
 *  @{
 */


// enc2out->finish define
enum {
	NON_FRAME		= 0,
	FIRST_FRAME		= 2,
	NORMAL_FRAME	= 5,
	SLICE_FRAME     = 6,
	LAST_FRAME		= 9,
	FINISH		    = 10,
	FAIL_FRAME		= -1,
};

enum {
	MD_NONE			= 0,
	MD_START		= 1,
	MD_STOP			= 2,
};


enum isp_tuning_iq_type {
	ISP_TUNING_IQ_TABLE_ALL,
	ISP_TUNING_IQ_TABLE_BLC,
	ISP_TUNING_IQ_TABLE_NLSC,
	ISP_TUNING_IQ_TABLE_MLSC,
	ISP_TUNING_IQ_TABLE_AE,
	ISP_TUNING_IQ_TABLE_AWB,
	ISP_TUNING_IQ_TABLE_AF,
	ISP_TUNING_IQ_TABLE_CCM,
	ISP_TUNING_IQ_TABLE_GAMMA,
	ISP_TUNING_IQ_TABLE_WDR,
	ISP_TUNING_IQ_TABLE_YGC,
	ISP_TUNING_IQ_TABLE_UVTUNE,
	ISP_TUNING_IQ_TABLE_SPE,
	ISP_TUNING_IQ_TABLE_TEXTURE,
	ISP_TUNING_IQ_TABLE_DAYNIGHT,
	ISP_TUNING_IQ_TABLE_HIGH_TEMP,
	_ISP_TUNING_IQ_TABLE_NUM
};

enum isp_tuning_statis_type {
	ISP_TUNING_STATIS_ALL,
	ISP_TUNING_STATIS_RAW,
	ISP_TUNING_STATIS_AWB,
	ISP_TUNING_STATIS_AE,
	ISP_TUNING_STATIS_AF,
	ISP_TUNING_STATIS_FLICK,
	ISP_TUNING_STATIS_Y,
	_ISP_TUNING_STATIS_NUM,
};

enum isp_tuning_param_type {
	ISP_TUNING_PARAM_ALL,
	ISP_TUNING_PARAM_AE,
	ISP_TUNING_PARAM_AWB,
	ISP_TUNING_PARAM_FLICK,
	ISP_TUNING_PARAM_WDR,
	_ISP_TUNING_PARAM_NUM,
};

#define IQ_CMD_DATA_SIZE 65536

typedef void (*output_callback_t)(void *, void *, uint32_t);

typedef struct {

	int max_width;
	int max_height;
	int out_width;
	int out_height;

	int crop_x;
	int crop_y;
	int crop_width;
	int crop_height;

	int frame_count;
	u16 skip_m;
	u16 skip_n;

} isp_meta_t;


typedef struct {
	int width;				// output width
	int height;				// output height
	int codec;				// Codec Type Bit0:HEVC Bit1:h264 Bit2:JPEG Bit3:NV12 Bit4:RGB  Bit5: ISP_DONE
	int ch;

	u32 enc_len;			// output bit stream size
	u32 jpg_len;			// output bit stream size
	int *enc_addr;			// output bit stream address
	int *jpg_addr;			// output bit stream address

	int *isp_addr;			// output isp address
	int qp;					// output frame Encoder QP value
	int finish;				// output is laster frame
	int type;				// output type I/P frame	//VCENC_INTRA_FRAME/INTER_FRAME ...

	int enc_used;			// ENC buffer used size
	int jpg_used;			// JPEG buffer used size

	int enc_slot;			// ENC buffer used slot
	int jpg_slot;			// JPEG buffer used slot

	volatile int roi_time;	// ROI SW time
	volatile int enc_time;	// HW encode time on Normal , Queue avail on Buffer/Queue full return
	volatile int jpg_time;	// HW JPEG time
	int cmd;
	int cmd_status;

	u32 time_stamp;			// time_stamp current time stamp
	u32 enc_meta_offset;	// enc metadata offset size
	u32 enc_meta_size;	 	// enc metadata size
	u32 jpg_meta_offset;	// jpeg metadata offset size
	u32 jpg_meta_size;	 	// jpeg metadata size

	isp_statis_meta_t statis_data;
	isp_meta_t isp_meta_data;



} __attribute__((aligned(32))) enc2out_t;





typedef struct {
	// OSD SW workaround
	int width;
	int height;
	int table_size;

} hal_video_osd_s;

typedef struct {
	// ROI
	int	type;				// ROI type
	int *roi_table;			// ROI table for user
	int block_unit;			// ROI block unit 8, 16, 32, 64
	int table_width;
	int table_height;
	int table_size;

} __attribute__((aligned(32))) hal_video_roi_s;

typedef struct {
	i32 bps;
	i32 isp_fps;
	i32 fps;
	i32 maxqp;
	i32 minqp;
	i32 gop;

	int fixedIntraQp;
	int intraQpDelta;

	int qpMaxI;
	int qpMinI;

	int forcei;
	int rsvd_size;
} __attribute__((aligned(32))) rate_ctrl_s;



typedef struct {
	i32 objDetectNumber;
	i32 objTopX[MAX_OBJECT];
	i32 objTopY[MAX_OBJECT];
	i32 objBottomX[MAX_OBJECT];
	i32 objBottomY[MAX_OBJECT];
} __attribute__((aligned(32))) obj_ctrl_s;

struct isp_tuning_cmd {
	uint32_t		err;
	uint16_t		opcode;
	uint16_t		status;
	uint32_t		addr;
	uint32_t		len;		/* only data */
	union {
		uint8_t	data[0];
		void	*ptr[0];
	};
} __attribute__((packed));






typedef struct {
	VCEncVideoCodecFormat	codecFormat;						// Video Codec Format: HEVC/H264/JPEG
	commandLine_s			*cmd[MAX_CHANNEL];					// Channel 3 is RGB only

	volatile int			video_ch_cnt;						// VOE open channel count

	output_callback_t		out_cb[MAX_CHANNEL];				// Output stream callback function
	output_callback_t		md_out_cb;							// MD Result Output callback function



	hal_video_roi_s			*enc_roi[MAX_CHANNEL];					// roi map table

	enc2out_t 				*enc2out;
	volatile QueueHandle_t	md_queue;
	volatile QueueHandle_t  out_queue;

	xTaskHandle				tid_out;
	xTaskHandle				tid_md;

	int						out_queue_full_cnt;
	int						video_show_info;

	u32 ctx[MAX_CHANNEL];
	u32 *load_time;
	u32 *hal_version;

	isp_mask_group_t *isp_mask_group;

	__attribute__((aligned(32))) volatile int		voe_info;

} __attribute__((aligned(32))) hal_video_adapter_t;

#if !defined (CONFIG_VOE_PLATFORM) || !CONFIG_VOE_PLATFORM // Run on TM9

struct rts_isp_i2c_reg {
	u16 addr;
	u16 data;
};

#endif

typedef struct fcs_peri_info_ram_s {

	uint8_t i2c_id;
	uint8_t adc_id;   // use 1 gpio
	uint8_t pwm_id;   // same function as ir_led
	uint8_t snr_clk_pin;

	uint8_t gpio_list[12];

	uint8_t gpio_cnt;
	uint8_t i2c_scl;
	uint8_t i2c_sda;
	uint8_t fcs_peri_valid;

	uint8_t fcs_OK;
	uint8_t fcs_used;

	uint16_t fcs_data_verion;
	uint16_t fcs_data_id;

	uint8_t reserved[2];

} fcs_peri_info_ram_t, *pfcs_peri_info_ram_t;

typedef struct  {

	uint8_t scl_pin;
	uint8_t sda_pin;
	uint8_t i2c_id;

	uint8_t rst_pin;
	uint8_t pwdn_pin;
	uint8_t pwr_ctrl_pin;

	uint8_t snr_clk_pin;

	uint8_t pwm_id;
	uint8_t adc_id;

	uint8_t extra_gpio_list[10];

	uint8_t extra_gpio_cnt;

	uint8_t reserv[4];

} video_peri_info_t;


typedef struct  {

	int voe_load;
	int isp_ready;
	int fcs_done;
	int frame_done;
	int reserv[4];

} video_time_info_t;

typedef struct  {

	u32 init_flicker;
	u32 init_saturation;
	s32 init_brightness;
	u32 init_contrast;
	//u32 init_hue;
	u32 init_mipi_mode;	//0=continue mode, 1=non-continue mode
	u32 init_wdr_mode;
	u32 init_wdr_level;
	u32 init_hdr_mode;
	u32 init_mirrorflip;
	u32 reserv[15];

} video_isp_initial_items_t;




/** @} */ // end of GROUP_ENC_MODULE_SYSTEM_CONFIGURATION

#if !defined (CONFIG_VOE_PLATFORM) || !CONFIG_VOE_PLATFORM // Run on TM9

#if (CONFIG_VIDEO_EN==1)
int hal_video_init(u32 *heap_addr, int heap_size);
int hal_video_deinit(void);
#endif

hal_video_adapter_t *hal_video_get_adp(void);

int hal_video_str_parsing(char *str);
int hal_video_str2cmd(char *str1, char *str2, char *str3);
int hal_video_cmd_reset(int ch);

int hal_video_open(int ch);
int hal_video_close(int ch);

int hal_video_out_mode(int ch, int type, int mode);
int hal_video_release(int ch, int type, int mode);

int hal_video_sync(int ch);
int hal_video_ext_in(int ch, u32 addr);

int hal_video_force_i(int ch);
int hal_video_set_rc(rate_ctrl_s *rc, int ch);

int hal_video_out_cb(output_callback_t out_cb, u32 out_queue_size, u32 arg, int ch);
int hal_video_md_cb(output_callback_t md_cb);
int hal_video_wdt_cb(output_callback_t wdt_cb, u32 arg, int ch);


int hal_video_roi_region(int ch, int x, int y, int width, int height, int value);
int hal_video_obj_region(obj_ctrl_s *obj_r, int ch);

// ISP
int hal_video_isp_ctrl(int ctrl_id, int set_flag, int *value);
int hal_video_isp_buf_release(int ch, uint32_t buf_addr);
int hal_video_isp_set_rawfmt(int ch, uint32_t rawfmt);

int hal_video_i2c_read(struct rts_isp_i2c_reg *reg);
int hal_video_i2c_write(struct rts_isp_i2c_reg *reg);

int hal_video_isp_tuning(int tuning_req, struct isp_tuning_cmd *tuning_cmd);

// OSD
//int hal_video_osd_query(int ch, struct rts_video_osd2_attr **attr);
//int hal_video_osd_enable(int ch, rt_osd2_info_st *osd2, bool en);
//int hal_video_osd_update(int ch, rt_osd2_info_st *osd2, BOOL ready2update);

//MD
int hal_video_md_start(md2_adaptor_t *md_adp, md2_result_t *md_result);
//int hal_video_md_start(md2_adaptor_t *md_adp);
int hal_video_md_stop(void);
int hal_video_md_trigger(void);

// Show VOE information
int hal_video_mem_info(void);
int hal_video_buf_info(void);
int hal_video_time_info(int level, video_time_info_t *time_info);
int hal_video_print(int mode);


int hal_video_test(int ch, int value);

// hal_video_peri.c
hal_status_t hal_i2c_pin_unregister_simple(volatile hal_i2c_adapter_t *phal_i2c_adapter);
hal_status_t hal_i2c_pin_register_simple(volatile hal_i2c_adapter_t *phal_i2c_adapter);

int hal_video_set_sensor_mode(int mode, int fps);
int hal_video_get_sensor_mode(int *mode, int *fps);

int hal_video_get_AF_statis(af_statis_t *p_af_result);
int hal_video_get_AE_statis(ae_statis_t *p_ae_result);
int hal_video_get_AWB_statis(awb_statis_t *p_awb_result);

void hal_video_get_fcs_peri_info(fcs_peri_info_ram_t *pfcs_peri_info);
int hal_video_peri_update_with_fcs(video_peri_info_t *p_video_peri_info);
int hal_video_check_fcs_OK(void);
void hal_video_reset_fcs_OK(void);
int hal_video_osd_reset(int ch);
int hal_video_get_realfps(int ch, int *isp_fpsx100, int *enc_fpsx100);
int hal_video_get_ae_weight(uint8_t *weight_array, int *p_weight_num);
int hal_video_set_ae_weight(uint8_t *weight_array, int weight_num);
int hal_video_config_grid_mask(int enable, isp_grid_t grid, uint8_t *bitmap);
int hal_video_config_rect_mask(int enable, uint32_t id, isp_rect_t rect);
int hal_video_set_mask(int ch, BOOL fast_en);
int hal_video_set_dynamic_zoom(int ch, isp_crop_t corp_info);
void hal_video_set_fps(int fps, int ch);
int hal_video_get_no_video_time(void);
u32 hal_video_get_video_timer_cur_time(void);
int hal_video_config_isp_calibration(int iq_cali_flag);
int hal_video_set_isp_stream_fps(int ch, uint32_t fps);

extern hal_video_adapter_t vv_adapter;

static __inline__ int hal_video_fcs_ch(int cnt)
{
	hal_video_adapter_t *v_adp = &vv_adapter;
	v_adp->video_ch_cnt = cnt;
	return OK;
}

static __inline__ int hal_video_set_wdt(int mode, int sec)
{
#if (CONFIG_VIDEO_EN==1)
	return hal_voe_set_wdt(mode, sec);
#else
	return FAIL;
#endif
}


static __inline__ int hal_video_load_fw(voe_cpy_t voe_cpy, int *fw_addr, int *voe_ddr_addr)
{
#if (CONFIG_VIDEO_EN==1)
	return hal_voe_load_fw(voe_cpy, fw_addr, voe_ddr_addr);
#else
	return FAIL;
#endif
}


static __inline__ int hal_video_load_sensor(voe_cpy_t voe_cpy, int *fw_addr, int *voe_ddr_addr)
{
#if (CONFIG_VIDEO_EN==1)
	return hal_voe_load_sensor(voe_cpy, fw_addr, voe_ddr_addr);
#else
	return FAIL;
#endif
}


static __inline__ int hal_video_load_iq(voe_cpy_t voe_cpy, int *fw_addr, int *voe_ddr_addr)
{
#if (CONFIG_VIDEO_EN==1)
	return hal_voe_load_iq(voe_cpy, fw_addr, voe_ddr_addr);
#else
	return FAIL;
#endif

}

// VOE!@ISP/ENC buffer setting
static __inline__ int hal_video_enc_buf(int ch, int buf_size, int rsvd_size)
{
	//	hal_video_adapter_t *v_adp = (hal_video_adapter_t *)(VOE_DDR_S + VOE_CODE_SHIFT);
	hal_video_adapter_t *v_adp = &vv_adapter;
	commandLine_s *cml;

	cml = v_adp->cmd[ch];
	cml->out_buf_size = buf_size;
	cml->out_rsvd_size = rsvd_size;
	dcache_clean_invalidate_by_addr((uint32_t *)v_adp->cmd[ch], sizeof(commandLine_s));

	return OK;
}

static __inline__ int hal_video_jpg_buf(int ch, int buf_size, int rsvd_size)
{
	//	hal_video_adapter_t *v_adp = (hal_video_adapter_t *)(VOE_DDR_S + VOE_CODE_SHIFT);
	hal_video_adapter_t *v_adp = &vv_adapter;

	commandLine_s *cml;

	cml = v_adp->cmd[ch];
	cml->jpg_buf_size = buf_size;
	cml->jpg_rsvd_size = rsvd_size;
	dcache_clean_invalidate_by_addr((uint32_t *)v_adp->cmd[ch], sizeof(commandLine_s));

	return OK;
}

static __inline__ int hal_video_isp_buf_num(int ch, int buf_num)
{
	//	hal_video_adapter_t *v_adp = (hal_video_adapter_t *)(VOE_DDR_S + VOE_CODE_SHIFT);
	hal_video_adapter_t *v_adp = &vv_adapter;
	commandLine_s *cml;

	cml = v_adp->cmd[ch];
	cml->isp_buf_num = buf_num;
	dcache_clean_invalidate_by_addr((uint32_t *)v_adp->cmd[ch], sizeof(commandLine_s));
	return OK;
}

static __inline__ int hal_video_isp_set_roi(int ch, int x, int y, int w, int h)
{
	//	hal_video_adapter_t *v_adp = (hal_video_adapter_t *)(VOE_DDR_S + VOE_CODE_SHIFT);
	hal_video_adapter_t *v_adp = &vv_adapter;
	commandLine_s *cml;

	cml = v_adp->cmd[ch];
	cml->roix = x;
	cml->roiy = y;
	cml->roiw = w;
	cml->roih = h;
	dcache_clean_invalidate_by_addr((uint32_t *)v_adp->cmd[ch], sizeof(commandLine_s));
	return OK;
}


static __inline__ int hal_video_isp_set_init_ae(int ch, int initAE_flag, int init_exposure, int init_gain)
{
	//	hal_video_adapter_t *v_adp = (hal_video_adapter_t *)(VOE_DDR_S + VOE_CODE_SHIFT);
	hal_video_adapter_t *v_adp = &vv_adapter;
	commandLine_s *cml;

	cml = v_adp->cmd[ch];
	cml->set_AE_init_flag = initAE_flag;
	cml->init_gain = init_gain;
	cml->init_exposure = init_exposure;
	dcache_clean_invalidate_by_addr((uint32_t *)v_adp->cmd[ch], sizeof(commandLine_s));
	return OK;
}

static __inline__ int hal_video_isp_set_init_awb(int ch, int initAWB_flag, int init_r_gain, int init_b_gain)
{
	//	hal_video_adapter_t *v_adp = (hal_video_adapter_t *)(VOE_DDR_S + VOE_CODE_SHIFT);
	hal_video_adapter_t *v_adp = &vv_adapter;
	commandLine_s *cml;

	cml = v_adp->cmd[ch];
	cml->set_AWB_init_flag = initAWB_flag;
	cml->init_r_gain = init_r_gain;
	cml->init_b_gain = init_b_gain;
	dcache_clean_invalidate_by_addr((uint32_t *)v_adp->cmd[ch], sizeof(commandLine_s));
	return OK;
}

static __inline__ int hal_video_isp_set_sensor_gpio(int ch, u32 sensor_rst_pin, u32 sensor_pwdn_pin, u32 sensor_pwr_pin)
{
	//	hal_video_adapter_t *v_adp = (hal_video_adapter_t *)(VOE_DDR_S + VOE_CODE_SHIFT);
	hal_video_adapter_t *v_adp = &vv_adapter;
	commandLine_s *cml;

	cml = v_adp->cmd[ch];
	cml->sensor_rst_pin = sensor_rst_pin;
	cml->sensor_pwdn_pin = sensor_pwdn_pin;
	cml->sensor_pwr_pin = sensor_pwr_pin;

	dcache_clean_invalidate_by_addr((uint32_t *)v_adp->cmd[ch], sizeof(commandLine_s));
	return OK;
}

static __inline__ int hal_video_isp_set_i2c_id(u32 ch, u32 i2c_id)
{
	//	hal_video_adapter_t *v_adp = (hal_video_adapter_t *)(VOE_DDR_S + VOE_CODE_SHIFT);
	hal_video_adapter_t *v_adp = &vv_adapter;
	commandLine_s *cml;

	cml = v_adp->cmd[ch];
	cml->i2c_id = i2c_id;

	dcache_clean_invalidate_by_addr((uint32_t *)v_adp->cmd[ch], sizeof(commandLine_s));
	return OK;
}

static __inline__ int hal_video_isp_clk_set(int ch, u32 isp_clk_level, u32 mipi_clk_level)
{

	hal_video_adapter_t *v_adp = &vv_adapter;
	commandLine_s *cml;

	cml = v_adp->cmd[ch];
	cml->isp_clock_level = isp_clk_level;
	cml->mipi_clock_level = mipi_clk_level;

	dcache_clean_invalidate_by_addr((uint32_t *)v_adp->cmd[ch], sizeof(commandLine_s));
	return OK;

}
static __inline__ int hal_video_isp_drop_frame_num_set(int ch, u32 drop_frame_num)
{

	hal_video_adapter_t *v_adp = &vv_adapter;
	commandLine_s *cml;

	cml = v_adp->cmd[ch];
	cml->drop_frame_num = drop_frame_num;

	dcache_clean_invalidate_by_addr((uint32_t *)v_adp->cmd[ch], sizeof(commandLine_s));
	return OK;

}

static __inline__ int hal_video_isp_set_dn_mode(int ch, int dn_mode)
{
	hal_video_adapter_t *v_adp = &vv_adapter;
	commandLine_s *cml;

	cml = v_adp->cmd[ch];
	cml->init_daynight_mode = dn_mode;
	dcache_clean_invalidate_by_addr((uint32_t *)v_adp->cmd[ch], sizeof(commandLine_s));
	return OK;
}

static __inline__ int hal_video_isp_set_directI2C_mode(int ch, int direct_i2c_mode)
{

	hal_video_adapter_t *v_adp = &vv_adapter;
	commandLine_s *cml;

	cml = v_adp->cmd[ch];
	cml->direct_i2c_mode = direct_i2c_mode;
	dcache_clean_invalidate_by_addr((uint32_t *)v_adp->cmd[ch], sizeof(commandLine_s));
	return OK;
}


static __inline__ int hal_video_isp_set_gray_mode(int ch, int gray_mode)
{
	hal_video_adapter_t *v_adp = &vv_adapter;
	commandLine_s *cml;

	cml = v_adp->cmd[ch];
	cml->gray_mode = gray_mode;
	dcache_clean_invalidate_by_addr((uint32_t *)v_adp->cmd[ch], sizeof(commandLine_s));
	return OK;
}

static __inline__ int hal_video_isp_set_init_iq_mode(int ch, int init_iq_mode)
{
	hal_video_adapter_t *v_adp = &vv_adapter;
	commandLine_s *cml;

	cml = v_adp->cmd[ch];
	cml->all_init_iq_set_flag = init_iq_mode;
	dcache_clean_invalidate_by_addr((uint32_t *)v_adp->cmd[ch], sizeof(commandLine_s));
	return OK;
}



static __inline__ int hal_video_isp_set_isp_meta_out(int ch, int isp_meta_out)
{
	hal_video_adapter_t *v_adp = &vv_adapter;
	commandLine_s *cml;

	cml = v_adp->cmd[ch];
	cml->isp_meta_out = isp_meta_out;
	dcache_clean_invalidate_by_addr((uint32_t *)v_adp->cmd[ch], sizeof(commandLine_s));
	return OK;
}

static __inline__ int hal_video_set_mask_color(uint32_t color)
{
	hal_video_adapter_t *v_adp = &vv_adapter;
	v_adp->isp_mask_group->color = color;

	return OK;
}

static __inline__ int hal_video_reset_mask_status(void)
{
	hal_video_adapter_t *v_adp = &vv_adapter;
	v_adp->isp_mask_group->grid_mask_set_status = ISP_MASK_KEEP;
	for (int i = 0; i < ISP_MASK_RECT_NUM; i++) {
		v_adp->isp_mask_group->rect_mask_set_status[i] = ISP_MASK_KEEP;
	}
	return OK;
}

static __inline__ int hal_video_enable_load_cali_iq(int ch, int enable)
{
	hal_video_adapter_t *v_adp = &vv_adapter;
	commandLine_s *cml;

	cml = v_adp->cmd[ch];
	cml->iq_cali_init_en = enable;
	dcache_clean_invalidate_by_addr((uint32_t *)v_adp->cmd[ch], sizeof(commandLine_s));
	return OK;
}

static __inline__ int hal_video_load_cali_iq(voe_cpy_t voe_cpy, int *cali_iq_addr, int *voe_ddr_addr, u32 cali_iq_size)
{
#if (CONFIG_VIDEO_EN==1)
	return hal_voe_load_cali_iq(voe_cpy, cali_iq_addr, voe_ddr_addr, cali_iq_size);
#else
	return FAIL;
#endif

}

static __inline__ int hal_video_fast_enable_mask(int ch)
{
	hal_video_adapter_t *v_adp = &vv_adapter;
	commandLine_s *cml;

	cml = v_adp->cmd[ch];
	cml->fast_mask_en = 1;
	dcache_clean_invalidate_by_addr((uint32_t *)v_adp->cmd[ch], sizeof(commandLine_s));
	return OK;
}

static __inline__ int hal_video_set_isp_init_items(int ch, video_isp_initial_items_t *init_items)
{
	hal_video_adapter_t *v_adp = &vv_adapter;
	commandLine_s *cml;

	cml = v_adp->cmd[ch];

	cml->init_flicker = init_items->init_flicker;
	cml->init_saturation = init_items->init_saturation;
	cml->init_brightness = (u32)init_items->init_brightness;
	cml->init_contrast = init_items->init_contrast;
	//cml->init_hue = init_items->init_hue;
	cml->mipi_clk_noncontinous = init_items->init_mipi_mode;
	cml->init_wdr_mode = init_items->init_wdr_mode;
	cml->init_wdr_level = init_items->init_wdr_level;
	cml->init_hdr_mode = init_items->init_hdr_mode;
	cml->init_mirrorflip = init_items->init_mirrorflip;

	dcache_clean_invalidate_by_addr((uint32_t *)v_adp->cmd[ch], sizeof(commandLine_s));
	return OK;
}

static __inline__ int hal_video_set_mipi_clk_nonctn(int ch, int clk_noncontinuous)
{
	hal_video_adapter_t *v_adp = &vv_adapter;
	commandLine_s *cml;

	cml = v_adp->cmd[ch];
	cml->mipi_clk_noncontinous = clk_noncontinuous;
	dcache_clean_invalidate_by_addr((uint32_t *)v_adp->cmd[ch], sizeof(commandLine_s));
	return OK;
}

static __inline__ int hal_video_fcs_en(int ch, int en)
{
	hal_video_adapter_t *v_adp = &vv_adapter;
	commandLine_s *cml;

	cml = v_adp->cmd[ch];
	cml->fcs = en;
	dcache_clean_invalidate_by_addr((uint32_t *)v_adp->cmd[ch], sizeof(commandLine_s));
	return OK;
}

#endif // #if !defined (CONFIG_VOE_PLATFORM) || !CONFIG_VOE_PLATFORM // Run on TM9
/** @} */ /* End of group hal_enc */

#ifdef  __cplusplus
}
#endif

#endif  // end of "#define _HAL_VIDEO_H_"

