#include <Arduino.h>
#include "AmbientLightSensor.h"

#include "platform_stdlib.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "FreeRTOS.h"
#include "task.h"
#include "isp_api.h"
#include "isp_ctrl_api.h"
#include "osd_api.h"
#include "osd_render.h"
#include "sensor_service.h"

#ifdef __cplusplus
}
#endif

#define ss_dprintf(level, ...) \
    if (level <= ss_dbg_level) \
    printf(__VA_ARGS__)
#define DEF_LED_IDX 2
#define SW_ALS      0
#define HW_ALS      1

#define DEBUG_OSD 1
#define AUTO_PWM  1

static int ALS_TYPE = SW_ALS;
static int SERVICE_DURATION = 3000; /* Delay time for each als detection cycle (unit:ms) */
static int AE_CHECK_DURATION = 500; /* Delay time for ae stable detection (unit:ms) */
static int ss_dbg_level = 0;        /* Level for sensor service debug message, refer to ss_dbg_level */
static int en_auto_pwm = 0;         /* Enable for auto-pwm function */
static int sw_lux = 0;              /* Lux information from isp */
static float hw_lux = 0;            /* Lux information from hw-als */
static int led_brightness = 0;      /* Ref value to led pwm*/
static int THR_COLOR_TO_GRAY = 0;
static int THR_GRAY_TO_COLOR = 0;
static int DEBUG_EN = 0;

static void autopwm_set_param(auto_pwm_config_t *auto_pwm_config)
{
    auto_pwm_config->led_step[0] = LED_MIN_STRENGTH;
    auto_pwm_config->led_step[1] = (LED_MAX_STRENGTH + LED_MIN_STRENGTH) >> 1;
    auto_pwm_config->led_step[2] = LED_MAX_STRENGTH;
    auto_pwm_config->led_idx = DEF_LED_IDX;
    auto_pwm_config->thr_darker = 200;
    auto_pwm_config->thr_brighter = 1000;
}

static void autopwm_get_param(auto_pwm_config_t *auto_pwm_config)
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
                pre_led_brightness = auto_pwm_config.led_step[*led_idx];
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
                pre_led_brightness = auto_pwm_config.led_step[*led_idx];
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

#if (DEBUG_OSD)
#define LIVESTREAM_CHANNEL 0
static void sensor_service_osd(void)
{
    char text_str_1ed[80], text_str_lux[80];
    canvas_create_bitmap(LIVESTREAM_CHANNEL, 0, RTS_OSD2_BLK_FMT_1BPP);
    canvas_create_bitmap(LIVESTREAM_CHANNEL, 1, RTS_OSD2_BLK_FMT_1BPP);
    snprintf(text_str_1ed, sizeof(text_str_1ed), "EN:%d LED:%d", en_auto_pwm, led_brightness);
    if (ALS_TYPE == HW_ALS) {
        snprintf(text_str_lux, sizeof(text_str_lux), "HW-LUX:%d", (int)hw_lux);
    } else {
        snprintf(text_str_lux, sizeof(text_str_lux), "SW-LUX:%d", sw_lux);
    }
    canvas_set_text(LIVESTREAM_CHANNEL, 0, 10, 10, text_str_1ed, COLOR_CYAN);
    canvas_set_text(LIVESTREAM_CHANNEL, 1, 10, 50, text_str_lux, COLOR_CYAN);
    canvas_update(LIVESTREAM_CHANNEL, 0, 1);
    canvas_update(LIVESTREAM_CHANNEL, 1, 1);
}
#endif

void sensor_thread_hw(void *param)
{
    int gray_mode = 0;
    int scale = 180;
    short led_idx;

    char if_ae_stable = AE_UNSTABLE;
#if (AUTO_PWM)
    auto_pwm_config_t auto_pwm_config;
    autopwm_set_param(&auto_pwm_config);
    autopwm_get_param(&auto_pwm_config);
    led_idx = auto_pwm_config.led_idx;
#endif

#if (DEBUG_OSD)
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
#if (AUTO_PWM)
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
#if (AUTO_PWM)
            if (en_auto_pwm) {
                auto_pwm_config.led_idx = led_idx;
            }
#endif
            day_night_mode_switch(gray_mode, 0);
        } else {
            ss_dprintf(SS_LOG_ALL, "[SENSOR_SERVICE] STABLE:gray_mode(%d), hw_lux(%3.1f)\n", gray_mode, hw_lux);
        }

#if (AUTO_PWM)
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
            } else {
                if (led_idx != DEF_LED_IDX) {
                    led_idx = DEF_LED_IDX;
                    gray_mode = ALS_MODE_IR_STABLE;
                    day_night_mode_switch(gray_mode, auto_pwm_config.led_step[led_idx]);
                }
            }
        }
#endif
        if (DEBUG_EN) {
            sensor_service_osd();
        }
        vTaskDelay(SERVICE_DURATION);
    }
}

void als_set_param_sw(als_config_t *als_config)
{
    char mask[ALS_MAX_COL * ALS_MAX_ROW] = {
        0, 0, 1, 0, 0,
        0, 1, 1, 1, 0,
        1, 1, 1, 1, 1,
        0, 1, 1, 1, 0,
        0, 0, 1, 0, 0};
    als_config->thr_color_to_gray = THR_COLOR_TO_GRAY;
    als_config->thr_gray_to_color = THR_GRAY_TO_COLOR;
    als_config->thr_color_ratio = 192;
    als_config->thr_valid_block = 6;
    for (int i = 0; i < ALS_MAX_COL * ALS_MAX_ROW; i++) {
        als_config->mask[i] = mask[i];
    }
}

static void als_get_param(als_config_t *als_config)
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

void sensor_thread_sw(void *param)
{
    als_data_t als_data;
    als_config_t als_config;
    short led_idx;
    char if_ae_stable = AE_UNSTABLE;
    int gray_mode = ALS_MODE_RGB;
    als_set_param_sw(&als_config);
    als_get_param(&als_config);
#if (AUTO_PWM)
    auto_pwm_config_t auto_pwm_config;
    autopwm_set_param(&auto_pwm_config);
    autopwm_get_param(&auto_pwm_config);
    led_idx = auto_pwm_config.led_idx;
#endif
#if (DEBUG_OSD)
    int ch_enable[3] = {1, 0, 0};
    int char_resize_w[3] = {32, 32, 0}, char_resize_h[3] = {32, 32, 0};
    int ch_width[3] = {1280, 0, 0}, ch_height[3] = {720, 0, 0};
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
#if (AUTO_PWM)
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
#if (AUTO_PWM)
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
#if (AUTO_PWM)
        /*auto-pwm algorithm*/
        if (if_ae_stable == AE_STABLE && gray_mode) {
            if (en_auto_pwm) {
                autopwm_flow(auto_pwm_config, &led_idx);
            }
        } else {
            if (led_idx != DEF_LED_IDX) {
                led_idx = DEF_LED_IDX;
                gray_mode = ALS_MODE_IR_STABLE;
                day_night_mode_switch(gray_mode, auto_pwm_config.led_step[led_idx]);
            }
        }
#endif

        if (DEBUG_EN) {
            sensor_service_osd();
        }
    }

    vTaskDelay(SERVICE_DURATION);
}

void init_sensor_service_ALS(void)
{
    if (ALS_TYPE == SW_ALS) {
        if (xTaskCreate(sensor_thread_sw, ((const char *)"sensor_thread_sw"), 1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS) {
            printf("\r\n sensor_thread: Create Task Error\n");
        }
    } else {
        if (xTaskCreate(sensor_thread_hw, ((const char *)"sensor_thread_hw"), 1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS) {
            printf("\r\n sensor_thread: Create Task Error\n");
        }
    }
}


AmbientLightSensor::AmbientLightSensor(void)
{
}

AmbientLightSensor::AmbientLightSensor(int als_type)
{
    ALS_TYPE = als_type;
}

AmbientLightSensor::~AmbientLightSensor(void)
{
}

void AmbientLightSensor::init(void)
{
    ambient_light_sensor_init(NULL);
    ambient_light_sensor_power(1);
    init_sensor_service_ALS();
}

void AmbientLightSensor::setColorThreshold(int threshold)
{
    if (threshold == -1) {
        if (ALS_TYPE == SW_ALS) {
            THR_GRAY_TO_COLOR = 4000;
        } else {
            THR_GRAY_TO_COLOR = 30;
        }
    } else {
        THR_GRAY_TO_COLOR = threshold;
    }
}

void AmbientLightSensor::setGrayThreshold(int threshold)
{
    if (threshold == -1) {
        if (ALS_TYPE == SW_ALS) {
            THR_COLOR_TO_GRAY = 12000;
        } else {
            THR_COLOR_TO_GRAY = 15;
        }
    } else {
        THR_COLOR_TO_GRAY = threshold;
    }
}

void AmbientLightSensor::debugEnableOSD(void)
{
    DEBUG_EN = 1;
}

void AmbientLightSensor::setDebugLog(int debugLevel)
{
    ss_dbg_level = debugLevel;
}

void AmbientLightSensor::enableAutoPWM(void)
{
    en_auto_pwm = 1;
}
