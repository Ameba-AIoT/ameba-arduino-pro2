/**
 * The ambient light sensor in sensor board v1 is AP1522D
 * datasheat can be found here:
 *     http://www.hsinbao.com.tw/administratorHB/caproduct_data/pdfs/AP1522D%20DIP.pdf
 *
 * It requires a I2C to communicate.
 */

#include <string.h>
#include "platform_opts.h"

#include "sensor_service.h"
#include "ambient_light_sensor.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "i2c_api.h"
#include "ex_api.h"

static i2c_t   i2cmaster;

static xSemaphoreHandle i2c_rx_done_sema = NULL;
static xSemaphoreHandle i2c_tx_done_sema = NULL;

static void i2c_master_rxc_callback(void *userdata)
{
	xSemaphoreGiveFromISR(i2c_rx_done_sema, NULL);
}

static void i2c_master_txc_callback(void *userdata)
{
	xSemaphoreGiveFromISR(i2c_tx_done_sema, NULL);
}

void ap1522d_write(uint8_t reg, uint8_t value)
{
	uint8_t data[2] = {reg, value};

	i2c_write(&i2cmaster, MBED_I2C_SLAVE_ADDR, (char const *) data, 2, 1);
	xSemaphoreTake(i2c_tx_done_sema, portMAX_DELAY);
}

uint8_t ap1522d_read(uint8_t reg)
{
	uint8_t value;

	i2c_write(&i2cmaster, MBED_I2C_SLAVE_ADDR, (char const *)&reg, 1, 1);
	xSemaphoreTake(i2c_tx_done_sema, portMAX_DELAY);

	i2c_read(&i2cmaster, MBED_I2C_SLAVE_ADDR, (char *)&value, 1, 1);
	xSemaphoreTake(i2c_rx_done_sema, portMAX_DELAY);

	return value;
}

void ap1522d_read_burst(uint8_t reg, uint8_t *data, uint32_t len)
{
	i2c_write(&i2cmaster, MBED_I2C_SLAVE_ADDR, (char const *)&reg, 1, 1);
	xSemaphoreTake(i2c_tx_done_sema, portMAX_DELAY);

	i2c_read(&i2cmaster, MBED_I2C_SLAVE_ADDR, (char *) data, len, 1);
	xSemaphoreTake(i2c_rx_done_sema, portMAX_DELAY);
}
extern void i2c_set_user_callback(i2c_t *obj, I2CCallback i2ccb, void(*i2c_callback)(void *));

void ap1522d_init(void)
{
	i2c_rx_done_sema = xSemaphoreCreateBinary();
	i2c_tx_done_sema = xSemaphoreCreateBinary();

	memset(&i2cmaster, 0, sizeof(i2c_t));
	i2c_init(&i2cmaster, MBED_I2C_MTR_SDA, MBED_I2C_MTR_SCL);
	i2c_frequency(&i2cmaster, MBED_I2C_BUS_CLK);
	i2c_set_user_callback(&i2cmaster, I2C_RX_COMPLETE, i2c_master_rxc_callback);
	i2c_set_user_callback(&i2cmaster, I2C_TX_COMPLETE, i2c_master_txc_callback);

	ap1522d_write(AP1522D_REG_MODE, 0x00);
	vTaskDelay(1);
}


void ap1522d_power(int poweron)
{
	uint8_t value;

	value = ap1522d_read(AP1522D_REG_MODE);

	if (poweron) {
		value &= ~AP1522D_MODE_PD;
	} else {
		value |= AP1522D_MODE_PD;
	}

	ap1522d_write(AP1522D_REG_MODE, value);
}

int ap1522d_ready(void)
{
	if (ap1522d_read(AP1522D_REG_STATUS) & AP1522D_STATUS_R_RDY) {
		return 1;
	} else {
		return 0;
	}
}

void ap1522d_reset(int enable)
{
	uint8_t value;

	value = ap1522d_read(AP1522D_REG_MODE);

	if (enable) {
		value |= AP1522D_MODE_RESET;
	} else {
		value &= ~AP1522D_MODE_RESET;
	}

	ap1522d_write(AP1522D_REG_MODE, value);
}

void ap1522d_get_sense_n_dark(unsigned int *sense, unsigned int *dark)
{
	uint8_t value;
	uint8_t data_low[4];
	uint8_t data_high[4];

	value = ap1522d_read(AP1522D_REG_MODE);
	value &= ~AP1522D_MODE_H_SELB;
	ap1522d_write(AP1522D_REG_MODE, value);

	ap1522d_read_burst(AP1522D_REG_SENSE_N_DARK_BASE, data_high, 4);

	value |= AP1522D_MODE_H_SELB;
	ap1522d_write(AP1522D_REG_MODE, value);

	ap1522d_read_burst(AP1522D_REG_SENSE_N_DARK_BASE, data_low, 4);

	*sense = (data_high[1] << 24) | (data_high[0] << 16) | (data_low[1] << 8) | data_low[0];
	*dark  = (data_high[3] << 24) | (data_high[2] << 16) | (data_low[3] << 8) | data_low[2];
}

void ap1522d_set_gain(int gain)
{
	uint8_t value;
	switch (gain) {
	case 1:
		value = AP1522D_GAIN_1X;
		break;
	case 2:
		value = AP1522D_GAIN_2X;
		break;
	case 4:
		value = AP1522D_GAIN_4X;
		break;
	case 8:
		value = AP1522D_GAIN_8X;
		break;
	case 16:
		value = AP1522D_GAIN_16X;
		break;
	case 32:
		value = AP1522D_GAIN_32X;
		break;
	case 64:
		value = AP1522D_GAIN_64X;
		break;
	case 128:
		value = AP1522D_GAIN_128X;
		break;
	default:
		value = AP1522D_GAIN_64X;
		break;
	}
	ap1522d_write(AP1522D_REG_GAIN, value);
}

int ap1522d_get_gain(void)
{
	uint8_t value;
	int gain;

	value = ap1522d_read(AP1522D_REG_GAIN);

	switch (value & 0x07) {
	case AP1522D_GAIN_1X:
		gain = 1;
		break;
	case AP1522D_GAIN_2X:
		gain = 2;
		break;
	case AP1522D_GAIN_4X:
		gain = 4;
		break;
	case AP1522D_GAIN_8X:
		gain = 8;
		break;
	case AP1522D_GAIN_16X:
		gain = 16;
		break;
	case AP1522D_GAIN_32X:
		gain = 32;
		break;
	case AP1522D_GAIN_64X:
		gain = 64;
		break;
	case AP1522D_GAIN_128X:
		gain = 128;
		break;
	}

	return gain;
}

void ap1522d_set_tig(float tig)
{
	uint8_t value;

	if (tig <= 1.536) {
		value = AP1522D_TIG_1P536MS;
	} else if (tig <= 3.072) {
		value = AP1522D_TIG_3P072MS;
	} else if (tig <= 50) {
		value = AP1522D_TIG_50MS;
	} else if (tig <= 100) {
		value = AP1522D_TIG_100MS;
	} else if (tig <= 200) {
		value = AP1522D_TIG_200MS;
	} else {
		value = AP1522D_TIG_400MS;
	}
	ap1522d_write(AP1522D_REG_TIG_SEL, value);
}

float ap1522d_get_tig(void)
{
	uint8_t value;
	float gain;

	value = ap1522d_read(AP1522D_REG_TIG_SEL);

	switch (value) {
	case AP1522D_TIG_1P536MS:
		gain = 1.536;
		break;
	case AP1522D_TIG_3P072MS:
		gain = 3.072;
		break;
	case AP1522D_TIG_50MS:
		gain = 50;
		break;
	case AP1522D_TIG_100MS:
		gain = 100;
		break;
	case AP1522D_TIG_200MS:
		gain = 200;
		break;
	case AP1522D_TIG_400MS:
		gain = 400;
		break;
	default:
		gain = 1.536;
		break; // this should never happended
	}

	return gain;
}

int ap1522d_calculate_lux(unsigned int sense, unsigned int dark, int gain, float tig)
{
	int lux;

	if (sense < dark) {
		return 0;
	}

	lux = (int)((sense - dark) * ((128 / gain) * (400 / tig) * 3.7765 / 1000));

	return lux;
}



int ambient_light_sensor_init(void *param)
{
	ap1522d_init();
	return 0;
}

int ambient_light_sensor_power(int enable)
{
	ap1522d_power(enable);
	return 0;
}

int ambient_light_sensor_get_lux(int sensibility)
{
	int gain = 32;
	float tig = 100.0f;
	unsigned int sense, dark;
	int lux;

	ap1522d_reset(AP1522D_ENABLE);

	ap1522d_set_gain(gain);
	ap1522d_set_tig(tig);

	ap1522d_reset(AP1522D_DISABLE);

	do {
		vTaskDelay(20);
	} while (!ap1522d_ready());

	ap1522d_get_sense_n_dark(&sense, &dark);
	gain = ap1522d_get_gain();
	tig = ap1522d_get_tig();
	lux = ap1522d_calculate_lux(sense, dark, gain, tig);

	return lux;
}