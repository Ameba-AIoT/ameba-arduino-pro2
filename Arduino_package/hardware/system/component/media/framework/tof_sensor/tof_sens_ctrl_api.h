#ifndef VL53L5CX_RTL8735B_I2C_H_
#define VL53L5CX_RTL8735B_I2C_H_

#include "PinNames.h"
#include "basic_types.h"
#include "diag.h"
#include "i2c_api.h"
#include "pinmap.h"
#include "ex_api.h"
#include "vl53l5cx_api.h"
#include "amebapro2/amebapro2_i2c_wrapper.h"

typedef struct tof_sens_ctx_s {
	// I2C
	tof_i2c_config_t tof_i2c_cfg;
	tof_i2c_ctx_t tof_i2c_ctx;

	// ToF specific config
	uint8_t image_res;

	// VL53L5CX ToF Sensor
	VL53L5CX_ResultsData     vl53l5cx_data;  // measurement results
	VL53L5CX_Configuration   vl53l5cx_sensor;  // device configuration/handle
} tof_sens_ctx_t;

#define TOF_SENS_RESOLUTION_4X4 VL53L5CX_RESOLUTION_4X4
#define TOF_SENS_RESOLUTION_8X8 VL53L5CX_RESOLUTION_8X8

#define REVISION_ID 0x02
#define DEVICE_ID   0xf0

bool tof_sens_init(tof_sens_ctx_t *tof_sens_ctx, VL53L5CX_Configuration *p_dev);
bool tof_sens_deinit(tof_sens_ctx_t *tof_sens_ctx, VL53L5CX_Configuration *p_dev);
bool tof_sens_set_resolution(VL53L5CX_Configuration *p_dev, uint8_t resolution);
uint8_t tof_sens_get_resolution(VL53L5CX_Configuration *p_dev, uint8_t *resolution);
bool tof_sens_start_ranging(VL53L5CX_Configuration *p_dev);
bool tof_sens_stop_ranging(VL53L5CX_Configuration *p_dev);
int tof_sens_data_ready(VL53L5CX_Configuration *p_dev);
bool tof_sens_get_ranging_data(VL53L5CX_Configuration *p_dev, VL53L5CX_ResultsData *pRangingData);

#endif