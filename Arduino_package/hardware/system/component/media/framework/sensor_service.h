#ifndef _SENSOR_SERVICE_H_
#define _SENSOR_SERVICE_H_

void init_sensor_service(void);

/**
 * ambient light sensor init
 *
 * @param param For future use.
 * @return 0 for success
 */
int ambient_light_sensor_init(void *param);

/**
 * Turn on ambient light sensor power.
 *
 * Some ambient light sensor has low power mode and able to save power while not in use.
 *
 * @param enable 1 for power on, 0 for power off
 * @return 0 for success
 */
int ambient_light_sensor_power(int enable);

/**
 * Get LUX (illuminance) from ambient light sensor
 *
 * @param sensibility Range:0~100. Ambient light sensor is able to adjust the integration time to get more precision lux value
 * @return 0 for success
 */
int ambient_light_sensor_get_lux(int sensibility);

/**
 * IR cut init
 *
 * @param param For future use.
 * @return 0 for success
 */
int ir_cut_init(void *param);

/**
 * enable/disable IR cut
 *
 * @param enable 1 for enable, 0 for disable
 * @return 0 for success
 */
int ir_cut_enable(int enable);

/**
 * IR ctrl init
 *
 * @param param For future use.
 * @return 0 for success
 */
int ir_ctrl_init(void *param);

/**
 * Adjust IR LED brightness
 *
 * @param brightness range:0.0~1.0
 * @return 0 for success
 */
int ir_ctrl_set_brightness(float brightness);

/**
 * Adjust IR LED dbrightness
 *
 * @param brightness range:0.0~1.0
 * @return 0 for success
 */
int ir_ctrl_set_brightness_d(int dbrightness);

/**
 * enable/disable gray mode
 *
 * In low light situation, we can turn on IR LED to get enough light.
 * But it also turns thing red. So we need enter gray mode.
 *
 * @param enable 1 for enable, 0 for disable
 * @return 0 for success
 */
int day_night_mode_switch(int enable, int led_level);

/**
 * loop routine
 *
 * If sensor implementation are block functions without and task swith, then we can put some delay here to let other task do their jobs.
 * We can also put some routine related to sensor here.
 *
 * @return 0 for success
 */
int sensor_external_loop(void);

/**
 * command for get / set for sensor_service varialbe
 *
 * @tyep: refer to ss_cmd_type
 * @index: refer to ss_cmd_index
 * @value: write / read value
 */
void ss_cmd(int type, int index, int *value);

enum ss_cmd_type {
	SS_GET_CMD = 0,
	SS_SET_CMD,
};

enum ss_dbg_level {
	SS_LOG_OFF = 0,
	SS_LOG_SWITCH,
	SS_LOG_ALL,
};

enum ss_cmd_index {
	SS_CMD_DEBUG_LEVEL = 0,
	SS_CMD_AUTO_PWM,
	SS_CMD_IR_STRENGTH,
	SS_CMD_HW_LUX,
	SS_CMD_SW_LUX,
	SS_CMD_VERSION,
};

#define COUNT_LED_STEP 3
#define LED_MAX_STRENGTH	100
#define LED_MIN_STRENGTH	50

typedef struct auto_pwm_config_s {
	int led_step[COUNT_LED_STEP];
	short led_idx;
	short thr_darker;
	short thr_brighter;
} auto_pwm_config_t;

#endif
