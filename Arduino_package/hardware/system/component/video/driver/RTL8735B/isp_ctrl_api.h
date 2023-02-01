#ifndef _ISP_CTRL_API_H_
#define _ISP_CTRL_API_H_

struct ctrl_range {
	int min;
	int max;
};

#define V4L2_CID_BASE 0
#define V4L2_CID_BRIGHTNESS (V4L2_CID_BASE+0)
#define V4L2_CID_CONTRAST (V4L2_CID_BASE+1)
#define V4L2_CID_SATURATION (V4L2_CID_BASE+2)
#define V4L2_CID_HUE (V4L2_CID_BASE+3)
#define V4L2_CID_NONE (V4L2_CID_BASE+4)
#define V4L2_CID_AUDIO_VOLUME (V4L2_CID_BASE+5)
#define V4L2_CID_AUDIO_BALANCE (V4L2_CID_BASE+6)
#define V4L2_CID_AUDIO_BASS (V4L2_CID_BASE+7)
#define V4L2_CID_AUDIO_TREBLE (V4L2_CID_BASE+8)
#define V4L2_CID_AUDIO_MUTE (V4L2_CID_BASE+9)
#define V4L2_CID_AUDIO_LOUDNESS (V4L2_CID_BASE+10)
#define V4L2_CID_BLACK_LEVEL (V4L2_CID_BASE+11) /* Deprecated */
#define V4L2_CID_AUTO_WHITE_BALANCE (V4L2_CID_BASE+12)
#define V4L2_CID_DO_WHITE_BALANCE (V4L2_CID_BASE+13)
#define V4L2_CID_RED_BALANCE (V4L2_CID_BASE+14)
#define V4L2_CID_BLUE_BALANCE (V4L2_CID_BASE+15)
#define V4L2_CID_GAMMA (V4L2_CID_BASE+16)
#define V4L2_CID_EXPOSURE (V4L2_CID_BASE+17)
#define V4L2_CID_AUTOGAIN (V4L2_CID_BASE+18)
#define V4L2_CID_GAIN (V4L2_CID_BASE+19)
#define V4L2_CID_HFLIP (V4L2_CID_BASE+20)
#define V4L2_CID_VFLIP (V4L2_CID_BASE+21)
#define V4L2_CID_HCENTER (V4L2_CID_BASE+22)
#define V4L2_CID_VCENTER (V4L2_CID_BASE+23)
#define V4L2_CID_POWER_LINE_FREQUENCY (V4L2_CID_BASE+24)
#define V4L2_CID_HUE_AUTO (V4L2_CID_BASE+25)
#define V4L2_CID_WHITE_BALANCE_TEMPERATURE (V4L2_CID_BASE+26)
#define V4L2_CID_SHARPNESS (V4L2_CID_BASE+27)


#define V4L2_CID_USER_BASE 0x0000
#define RTS_V4L2_CID_BASE (V4L2_CID_USER_BASE | 0xf000)
#define RTS_V4L2_CID_GREEN_BALANCE (RTS_V4L2_CID_BASE + 0)
#define RTS_V4L2_CID_IQ_TABLE (RTS_V4L2_CID_BASE + 1)
#define RTS_V4L2_CID_DAY_NIGHT (RTS_V4L2_CID_BASE + 2)
enum rts_isp_day_night {
	RTS_ISP_DAY,
	RTS_ISP_NIGHT,
};
#define RTS_V4L2_CID_DYNAMIC_FPS (RTS_V4L2_CID_BASE + 3)
#define RTS_V4L2_CID_DYNAMIC_IQ (RTS_V4L2_CID_BASE + 4)
#define RTS_V4L2_CID_TEMPORAL_DENOISE (RTS_V4L2_CID_BASE + 5)
#define RTS_V4L2_CID_DEHAZE (RTS_V4L2_CID_BASE + 6)
#define RTS_V4L2_CID_DEHAZE_LEVEL (RTS_V4L2_CID_BASE + 7)
#define RTS_V4L2_CID_LDC (RTS_V4L2_CID_BASE + 8)
#define RTS_V4L2_CID_GRAY (RTS_V4L2_CID_BASE + 9)
#define RTS_V4L2_CID_AUTO_CCM (RTS_V4L2_CID_BASE + 10)
#define RTS_V4L2_CID_CCM_MATRIX (RTS_V4L2_CID_BASE + 11)
#define RTS_V4L2_CID_WDR_MODE (RTS_V4L2_CID_BASE + 12)
enum rts_isp_wdr_mode {
	RTS_ISP_WDR_INNER_DISABLE,
	RTS_ISP_WDR_INNER_MANUAL,
	RTS_ISP_WDR_INNER_AUTO,
};
#define RTS_V4L2_CID_WDR_LEVEL (RTS_V4L2_CID_BASE + 13)
#define RTS_V4L2_CID_AUTO_GAMMA (RTS_V4L2_CID_BASE + 14)
#define RTS_V4L2_CID_GAMMA_CURVE (RTS_V4L2_CID_BASE + 15)
#define RTS_V4L2_CID_AUTO_YGAMMA (RTS_V4L2_CID_BASE + 16)
#define RTS_V4L2_CID_YGAMMA_CURVE (RTS_V4L2_CID_BASE + 17)
#define RTS_V4L2_CID_OUTPUT_POSITION (RTS_V4L2_CID_BASE + 18)
#define RTS_V4L2_CID_COLOR_RANGE (RTS_V4L2_CID_BASE + 19)
enum rts_isp_color_range {
	RTS_ISP_COLOR_RANGE_BT601_STUDIO_SWING,
	RTS_ISP_COLOR_RANGE_BT601_FULL_SWING,
	RTS_ISP_COLOR_RANGE_BT709_STUDIO_SWING,
	RTS_ISP_COLOR_RANGE_BT709_FULL_SWING,
};
#define RTS_V4L2_CID_NR_LEVEL (RTS_V4L2_CID_BASE + 20)
#define RTS_V4L2_CID_DE_LEVEL (RTS_V4L2_CID_BASE + 21)
#define RTS_V4L2_CID_SNR_CROP_X (RTS_V4L2_CID_BASE + 22)
#define RTS_V4L2_CID_SNR_CROP_Y (RTS_V4L2_CID_BASE + 23)
#define RTS_V4L2_CID_Y_GAIN (RTS_V4L2_CID_BASE + 24)
#define RTS_V4L2_CID_SMART_IR_MODE (RTS_V4L2_CID_BASE + 25)
#define RTS_V4L2_CID_SMART_IR_MANUAL_LEVEL (RTS_V4L2_CID_BASE + 26)
#define RTS_V4L2_CID_DAYNIGHT_DETECTION (RTS_V4L2_CID_BASE + 27)

void isp_ctrl_enable_log(int enable);
void isp_set_brightness(int val);
void isp_get_brightness(int *pval);
void isp_set_contrast(int val);
void isp_get_contrast(int *pval);
void isp_set_saturation(int val);
void isp_get_saturation(int *pval);
void isp_set_hue(int val);
void isp_get_hue(int *pval);
void isp_set_awb_ctrl(int val);
void isp_get_awb_ctrl(int *pval);
void isp_set_red_balance(int val);
void isp_get_red_balance(int *pval);
void isp_set_blue_balance(int val);
void isp_get_blue_balance(int *pval);
void isp_set_gamma(int val);
void isp_get_gamma(int *pval);
void isp_set_exposure_time(int val);
void isp_get_exposure_time(int *pval);
void isp_set_exposure_mode(int val);
void isp_get_exposure_mode(int *pval);
void isp_set_ae_gain(int val);
void isp_get_ae_gain(int *pval);
void isp_set_power_line_freq(int val);
void isp_get_power_line_freq(int *pval);
void isp_set_wb_temperature(int val);
void isp_get_wb_temperature(int *pval);
void isp_set_sharpness(int val);
void isp_get_sharpness(int *pval);
void isp_set_green_balance(int val);
void isp_get_green_balance(int *pval);
void isp_set_iq_table(int val);
void isp_get_iq_table(int *pval);
void isp_set_day_night(int val);
void isp_get_day_night(int *pval);
void isp_get_dynamic_fps(int *pval);
void isp_set_dynamic_iq(int val);
void isp_get_dynamic_iq(int *pval);
void isp_set_tnr(int val);
void isp_get_tnr(int *pval);
void isp_set_dehaze(int val);
void isp_get_dehaze(int *pval);
void isp_set_dehaze_level(int val);
void isp_get_dehaze_level(int *pval);
void isp_set_ldc(int val);
void isp_get_ldc(int *pval);
void isp_set_gray_mode(int val);
void isp_get_gray_mode(int *pval);
void isp_set_auto_ccm(int val);
void isp_get_auto_ccm(int *pval);
void isp_set_wdr_mode(int val);
void isp_get_wdr_mode(int *pval);
void isp_set_wdr_level(int val);
void isp_get_wdr_level(int *pval);
void isp_set_auto_gamma(int val);
void isp_get_auto_gamma(int *pval);
void isp_set_auto_ygamma(int val);
void isp_get_auto_ygamma(int *pval);
void isp_set_output_position(int val);
void isp_get_output_position(int *pval);
void isp_get_color_range(int *pval);
void isp_set_denoise_level(int val);
void isp_get_denoise_level(int *pval);
void isp_set_detail_enhance_level(int val);
void isp_get_detail_enhance_level(int *pval);
void isp_set_snr_crop_x(int val);
void isp_get_snr_crop_x(int *pval);
void isp_set_snr_crop_y(int val);
void isp_get_snr_crop_y(int *pval);
void isp_set_smart_ir_mode(int val);
void isp_get_smart_ir_mode(int *pval);
void isp_set_smart_ir_manual_level(int val);
void isp_get_smart_ir_manual_level(int *pval);
void isp_get_day_night_detection(int *pval);
void isp_set_gray_mode(int val);
void isp_get_gray_mode(int *pval);

#endif
