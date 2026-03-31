#include "sensor_service.h"
#include "FreeRTOS.h"
#include "task.h"
#include "platform_stdlib.h"
#include "isp_api.h"
#include "isp_ctrl_api.h"

#define SW_ALS		0
#define HW_ALS		1
#define ALS_TYPE 	SW_ALS	/* Choose ALS type */
#define AUTO_PWM_EN	0	/* Enable Auto PWM flow */
#define DEBUG_OSD	0	/* Enable debug message through OSD */
#define SERVICE_DURATION  3000	/* Delay time for each als detection cycle (unit:ms) */
#define AE_CHECK_DURATION 500	/* Delay time for ae stable detection (unit:ms) */
#define ss_dprintf(level, ...) if(level <= ss_dbg_level) printf(__VA_ARGS__)

static int ss_dbg_level = 0;	/* Level for sensor service debug message, refer to ss_dbg_level */
static int en_auto_pwm = 0;	/* Enable for auto-pwm function */
static int sw_lux = 0;		/* Lux information from isp */
static float hw_lux = 0;	/* Lux information from hw-als */
static int led_brightness = 0;	/* Ref value to led pwm*/
/*
* sensor service v2.0 should sync with sw-als v2.2
*/
static char ss_version[] = "v2.0";

//show sw-als version
static void ss_get_version(void)
{
	printf("[SENSOR_SERVICE] version:%s\n", ss_version);
}

/*
* switch function through mode changing
* case 1(als_mode_rgb): switch to RGB mode
* case 2(als_mode_ir_entry): switch to IR mode
* case 3(als_mode_ir_stable): Adjust IR LED PWM during IR mode
*/
int day_night_mode_switch(int enable, int led_level)
{
	int ret = 0;
	led_brightness = led_level;
	if (enable == ALS_MODE_RGB) {
		ss_dprintf(SS_LOG_SWITCH, "[SENSOR_SERVICE] Switch to RGB Mode\n");
		ir_ctrl_set_brightness_d(led_level);
		ir_cut_enable(1 - enable);
		isp_set_day_night(enable);
		isp_get_day_night(&ret);
		if (ret != enable) {
			isp_set_day_night(enable);
		}
		vTaskDelay(200);
		isp_set_gray_mode(enable);
		if (ret != enable) {
			isp_set_gray_mode(enable);
		}
	} else if (enable == ALS_MODE_IR_ENTRY) {
		ss_dprintf(SS_LOG_SWITCH, "[SENSOR_SERVICE] Switch to IR Mode\n");
		isp_set_gray_mode(enable);
		isp_get_day_night(&ret);
		if (ret != enable) {
			isp_set_gray_mode(enable);
		}
		ir_cut_enable(1 - enable);
		ir_ctrl_set_brightness_d(led_level);
		vTaskDelay(200);
		isp_set_day_night(enable);
		if (ret != enable) {
			isp_set_day_night(enable);
		}
	} else if (enable == ALS_MODE_IR_STABLE) {
		ir_ctrl_set_brightness_d(led_level);
	}
	return ret;
}

void ss_cmd(int type, int index, int *value)
{
	if (type == SS_GET_CMD) {
		if (index == SS_CMD_DEBUG_LEVEL) {
			*value = ss_dbg_level;
		} else if (index == SS_CMD_AUTO_PWM) {
			*value = en_auto_pwm;
		} else if (index == SS_CMD_IR_STRENGTH) {
			*value = led_brightness;
		} else if (index == SS_CMD_HW_LUX) {
			*value = (int)hw_lux;
		} else if (index == SS_CMD_SW_LUX) {
			*value = sw_lux;
		} else if (index == SS_CMD_VERSION) {
			ss_get_version();
		}
	} else {
		if (index == SS_CMD_DEBUG_LEVEL) {
			ss_dbg_level = *value;
		} else if (index == SS_CMD_AUTO_PWM) {
			en_auto_pwm = *value;
		}
	}
}

#define DEF_LED_IDX	2
static void autopwm_set_param(auto_pwm_config_t *auto_pwm_config)
{
	auto_pwm_config->led_step[0] = LED_MIN_STRENGTH;
	auto_pwm_config->led_step[1] = (LED_MAX_STRENGTH + LED_MIN_STRENGTH) >> 1;
	auto_pwm_config->led_step[2] = LED_MAX_STRENGTH;
	auto_pwm_config->led_idx = DEF_LED_IDX;
	auto_pwm_config->thr_darker = 200;
	auto_pwm_config->thr_brighter = 1000;
}

void autopwm_get_param(auto_pwm_config_t *auto_pwm_config)
{
	printf("[AUTO_PWM] ==== PARAMETER ====\n");
	printf("[AUTO_PWM] COUNT_LED_STEP = %d\n", COUNT_LED_STEP);
	printf("[AUTO_PWM] LED_IDX = %d\n", auto_pwm_config->led_idx);
	printf("[AUTO_PWM] THR_DARKER = %d\n", auto_pwm_config->thr_darker);
	printf("[AUTO_PWM] THR_BRIGHTER = %d\n", auto_pwm_config->thr_brighter);
	printf("[AUTO_PWM] ==== Step ====\n");
	for (int i = 0; i < COUNT_LED_STEP; i++) {
		printf("[AUTO_PWM] LED_STEP[%d] = %d\n", i, auto_pwm_config->led_step[i]);
	}
}

static void autopwm_flow(auto_pwm_config_t auto_pwm_config, short *led_idx)
{
	int pre_led_brightness = led_brightness;
	/*IR mode with en_auto_pwm, trigger ir-led adjustment*/
	if (en_auto_pwm) {
		if (sw_lux < auto_pwm_config.thr_darker) {
			if (*led_idx == 0) {
				ss_dprintf(SS_LOG_ALL, "[AUTO_PWM][STABLE] EN(%d), LED(%d)\n", en_auto_pwm, led_brightness);
			} else {
				*led_idx -= 1;
				if (*led_idx <= 0) {
					*led_idx = 0;
				}
				pre_led_brightness = auto_pwm_config.led_step[*led_idx] ;
				ss_dprintf(SS_LOG_SWITCH, "[AUTO_PWM][ADJUST] EN(%d), LED(%d)\n", en_auto_pwm, pre_led_brightness);
			}
		} else if (sw_lux > auto_pwm_config.thr_brighter) {
			if (*led_idx == (COUNT_LED_STEP - 1)) {
				ss_dprintf(SS_LOG_ALL, "[AUTO_PWM][STABLE] EN(%d), LED(%d)\n", en_auto_pwm, led_brightness);
			} else {
				*led_idx += 1;
				if (*led_idx >= COUNT_LED_STEP) {
					*led_idx = COUNT_LED_STEP - 1;
				}
				pre_led_brightness = auto_pwm_config.led_step[*led_idx] ;
				ss_dprintf(SS_LOG_SWITCH, "[AUTO_PWM][ADJUST] EN(%d), LED(%d)\n", en_auto_pwm, pre_led_brightness);
			}
		}
		/*IR mode without en_auto_ir, reset ir-led to default value*/
	} else if ((!en_auto_pwm) && (pre_led_brightness != auto_pwm_config.led_step[DEF_LED_IDX])) {
		*led_idx = DEF_LED_IDX;
		pre_led_brightness = auto_pwm_config.led_step[DEF_LED_IDX];
		ss_dprintf(1, "[AUTO_PWM][FORCE] EN(%d), LED(%d)\n", en_auto_pwm, pre_led_brightness);
	}
	/*if current pwm is not equal to pre pwm, update ir-led strength*/
	if (pre_led_brightness != led_brightness) {
		led_brightness = pre_led_brightness;
		day_night_mode_switch(ALS_MODE_IR_STABLE, led_brightness);
	}
}

#if(DEBUG_OSD)
#include "osd_api.h"
#include "osd_render.h"
#define LIVESTREAM_CHANNEL 0

void sensor_service_osd(void)
{
	char text_str_1ed[80], text_str_lux[80];
	canvas_create_bitmap(LIVESTREAM_CHANNEL, 0, RTS_OSD2_BLK_FMT_1BPP);
	canvas_create_bitmap(LIVESTREAM_CHANNEL, 1, RTS_OSD2_BLK_FMT_1BPP);
	snprintf(text_str_1ed, sizeof(text_str_1ed), "EN:%d LED:%d", en_auto_pwm, led_brightness);
#if (ALS_TYPE == HW_ALS)
	snprintf(text_str_lux, sizeof(text_str_lux), "HW-LUX:%d", (int)hw_lux);
#else
	snprintf(text_str_lux, sizeof(text_str_lux), "SW-LUX:%d", sw_lux);
#endif
	canvas_set_text(LIVESTREAM_CHANNEL, 0, 10, 10, text_str_1ed, COLOR_CYAN);
	canvas_set_text(LIVESTREAM_CHANNEL, 1, 10, 50, text_str_lux, COLOR_CYAN);
	canvas_update(LIVESTREAM_CHANNEL, 0, 1);
	canvas_update(LIVESTREAM_CHANNEL, 1, 1);
}
#endif

#if(ALS_TYPE == HW_ALS)
#define THR_COLOR_TO_GRAY	15
#define THR_GRAY_TO_COLOR	30

/*
* User should init IR-CUT / IR-LED / HW-ALS before apply sensor_thread
* If using RTK EVB, check default setting: platform_opts.h -> CONFIG_RTK_EVB_IR_CTRL
* or through ATCMD for initialization: ATIR=init_ir, ATIR=init_als
*/
void sensor_thread(void *param)
{
	int gray_mode = 0;
	int scale = 180;
	short led_idx;

	char if_ae_stable = AE_UNSTABLE;
#if (AUTO_PWM_EN)
	auto_pwm_config_t auto_pwm_config;
	autopwm_set_param(&auto_pwm_config);
	autopwm_get_param(&auto_pwm_config);
	led_idx = auto_pwm_config.led_idx;
#endif

#if(DEBUG_OSD)
	int ch_enable[3] = {1, 0, 0};
	int char_resize_w[3] = {32, 32, 0}, char_resize_h[3] = {32, 32, 0};
	int ch_width[3] = {1280, 0, 0}, ch_height[3] = {720, 0, 0};
	osd_render_dev_init(ch_enable, char_resize_w, char_resize_h);
	osd_render_task_start(ch_enable, ch_width, ch_height);
#endif

	while (1) {
		/*hw-als switch algorithm*/
		hw_lux = (ambient_light_sensor_get_lux(50) * scale) / 100;
		if (!gray_mode && (hw_lux <= THR_COLOR_TO_GRAY)) {
			ss_dprintf(SS_LOG_SWITCH, "[SENSOR_SERVICE] RGB2IR:gray_mode(%d), hw_lux(%3.1f) <= THR_COLOR_TO_GRAY(%d)\n", gray_mode, hw_lux, (int)THR_COLOR_TO_GRAY);
			gray_mode = ALS_MODE_IR_ENTRY;
#if (AUTO_PWM_EN)
			if (!en_auto_pwm) {
				led_idx = DEF_LED_IDX;
			} else {
				led_idx = auto_pwm_config.led_idx;
			}
			day_night_mode_switch(gray_mode, auto_pwm_config.led_step[led_idx]);
#else
			day_night_mode_switch(gray_mode, LED_MAX_STRENGTH);
#endif
		} else if (gray_mode && (hw_lux > THR_GRAY_TO_COLOR)) {
			ss_dprintf(SS_LOG_SWITCH, "[SENSOR_SERVICE] IR2RGB:gray_mode(%d), hw_lux(%3.1f) >= THR_GRAY_TO_COLOR(%d)\n", gray_mode, hw_lux, (int)THR_GRAY_TO_COLOR);
			gray_mode = ALS_MODE_RGB;
#if (AUTO_PWM_EN)
			if (en_auto_pwm) {
				auto_pwm_config.led_idx = led_idx;
			}
#endif
			day_night_mode_switch(gray_mode, 0);
		} else {
			ss_dprintf(SS_LOG_ALL, "[SENSOR_SERVICE] STABLE:gray_mode(%d), hw_lux(%3.1f)\n", gray_mode, hw_lux);
		}

#if (AUTO_PWM_EN)
		/*auto-pwm algorithm*/
		if (gray_mode) {
			if (en_auto_pwm) {
				if_ae_stable = isp_get_ae_if_stable(&sw_lux, AE_CHECK_DURATION);
				ss_dprintf(SS_LOG_ALL, "[SENSOR_SERVICE] if_ae_stable(%d), sw-lux(%d)\n", if_ae_stable, sw_lux);
				if (if_ae_stable == AE_UNSTABLE) {
					gray_mode = ALS_MODE_IR_ENTRY;
				} else {
					gray_mode = ALS_MODE_IR_STABLE;
					autopwm_flow(auto_pwm_config, &led_idx);
					auto_pwm_config.led_idx = led_idx;
				}
			} else  {
				if (led_idx != DEF_LED_IDX) {
					led_idx = DEF_LED_IDX;
					gray_mode = ALS_MODE_IR_STABLE;
					day_night_mode_switch(gray_mode, auto_pwm_config.led_step[led_idx]);
				}
			}
		}
#endif
#if(DEBUG_OSD)
		sensor_service_osd();
#endif
		vTaskDelay(SERVICE_DURATION);
	}
}
#else
void als_set_param(als_config_t *als_config)
{
	char mask[ALS_MAX_COL * ALS_MAX_ROW] = {
		0, 0, 1, 0, 0,
		0, 1, 1, 1, 0,
		1, 1, 1, 1, 1,
		0, 1, 1, 1, 0,
		0, 0, 1, 0, 0
	};
	als_config->thr_color_to_gray = 12000;
	als_config->thr_gray_to_color = 4000;
	als_config->thr_color_ratio = 192;
	als_config->thr_valid_block = 6;
	for (int i = 0; i < ALS_MAX_COL * ALS_MAX_ROW; i++) {
		als_config->mask[i] = mask[i];
	}
}

void als_get_param(als_config_t *als_config)
{
	printf("[SW_ALS] ==== PARAMETER ====\n");
	printf("[SW_ALS] THR_COLOR_TO_GRAY=%d\n", als_config->thr_color_to_gray);
	printf("[SW_ALS] THR_GRAY_TO_COLOR=%d\n", als_config->thr_gray_to_color);
	printf("[SW_ALS] THR_COLOR_RATIO  =%d\n", als_config->thr_color_ratio);
	printf("[SW_ALS] THR_VALID_BLOCK  =%d\n", als_config->thr_valid_block);
	printf("[SW_ALS] ==== MASK ====\n");
	for (int i = 0; i < ALS_MAX_ROW; i++) {
		printf("[SW_ALS] ");
		for (int j = 0; j < ALS_MAX_ROW; j++) {
			printf("%2d ", als_config->mask[i * 5 + j]);
		}
		printf("\n");
	}
}

/*
 * User should init IR-CUT / IR-LED before apply sensor_thread
*/
void sensor_thread(void *param)
{
	als_data_t als_data;
	als_config_t als_config;
	short led_idx;
	char if_ae_stable = AE_UNSTABLE;
	int gray_mode = ALS_MODE_RGB;
	als_set_param(&als_config);
	als_get_param(&als_config);
#if (AUTO_PWM_EN)
	auto_pwm_config_t auto_pwm_config;
	autopwm_set_param(&auto_pwm_config);
	autopwm_get_param(&auto_pwm_config);
	led_idx = auto_pwm_config.led_idx;
#endif
#if(DEBUG_OSD)
	int ch_enable[3] = {1, 0, 0};
	int char_resize_w[3] = {32, 32, 0}, char_resize_h[3] = {32, 32, 0};
	int ch_width[3] = {1280, 1280, 0}, ch_height[3] = {720, 720, 0};
	osd_render_dev_init(ch_enable, char_resize_w, char_resize_h);
	osd_render_task_start(ch_enable, ch_width, ch_height);
#endif

	while (1) {
		/*sw-als switch algorithm*/
		if_ae_stable = isp_get_ae_if_stable(&sw_lux, AE_CHECK_DURATION);
		ss_dprintf(SS_LOG_ALL, "[SENSOR_SERVICE] if_ae_stable(%d), sw_lux(%d)\n", if_ae_stable, sw_lux);
		if (if_ae_stable == AE_UNSTABLE && gray_mode == ALS_MODE_IR_STABLE) {
			gray_mode = ALS_MODE_IR_ENTRY;
			ss_dprintf(SS_LOG_ALL, "[SENSOR_SERVICE] UNSTABLE\r\n");
		} else if (!gray_mode && (sw_lux >= als_config.thr_color_to_gray)) {
			ss_dprintf(SS_LOG_SWITCH, "[SENSOR_SERVICE] RGB2IR:gray_mode(%d), sw_lux(%d) >= thr_color_to_gray(%d)\n", gray_mode, sw_lux, als_config.thr_color_to_gray);
			gray_mode = ALS_MODE_IR_ENTRY;
#if (AUTO_PWM_EN)
			if (!en_auto_pwm) {
				day_night_mode_switch(gray_mode, LED_MAX_STRENGTH);
			} else {
				day_night_mode_switch(gray_mode, auto_pwm_config.led_step[auto_pwm_config.led_idx]);
			}
#else
			day_night_mode_switch(gray_mode, LED_MAX_STRENGTH);
#endif
		} else if (gray_mode && (sw_lux <= als_config.thr_gray_to_color) && (sw_lux >= 0)) {
			als_get_statist(&als_data);
			if (als_if_switch(&als_config, &als_data)) {
				gray_mode = ALS_MODE_RGB;
				ss_dprintf(SS_LOG_SWITCH, "[SENSOR_SERVICE] IR2RGB:gray_mode(%d), sw_lux(%d) <= thr_gray_to_color(%d), als_if_switch(1)\n", gray_mode, sw_lux,
						   als_config.thr_gray_to_color);
#if (AUTO_PWM_EN)
				if (en_auto_pwm) {
					auto_pwm_config.led_idx = led_idx;
				}
#endif
				day_night_mode_switch(gray_mode, 0);
			} else {
				ss_dprintf(SS_LOG_ALL, "[SENSOR_SERVICE] STABLE:gray_mode(%d), sw_lux(%d) <= thr_gray_to_color(%d), als_if_switch(0)\n", gray_mode, sw_lux,
						   als_config.thr_gray_to_color);
			}
		}
#if (AUTO_PWM_EN)
		/*auto-pwm algorithm*/
		if (if_ae_stable == AE_STABLE && gray_mode) {
			if (en_auto_pwm) {
				autopwm_flow(auto_pwm_config, &led_idx);
			}
		} else  {
			if (led_idx != DEF_LED_IDX) {
				led_idx = DEF_LED_IDX;
				gray_mode = ALS_MODE_IR_STABLE;
				day_night_mode_switch(gray_mode, auto_pwm_config.led_step[led_idx]);
			}
		}
#endif
#if(DEBUG_OSD)
		sensor_service_osd();
#endif
		vTaskDelay(SERVICE_DURATION);
	}
}
#endif

void init_sensor_service(void)
{
	if (xTaskCreate(sensor_thread, ((const char *)"sensor_thread"), 1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS) {
		printf("\r\n sensor_thread: Create Task Error\n");
	}
}
