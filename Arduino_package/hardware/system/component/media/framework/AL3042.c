/**
 * The ambient light sensor in sensor board v1 is AP1522D
 * datasheat can be found here:
 *     http://www.hsinbao.com.tw/administratorHB/caproduct_data/pdfs/AP1522D%20DIP.pdf
 *
 * It requires a I2C to communicate.
 */

#ifdef CONFIG_PLATFORM_8195BHP
#include "platform_opts.h"
#include "AL3042.h"
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

void al3042_write(uint8_t reg, uint8_t value)
{
	uint8_t data[2] = {reg, value};
	i2c_write(&i2cmaster, MBED_I2C_SLAVE_ADDR, (char const *) data, 2, 1);
	xSemaphoreTake(i2c_tx_done_sema, portMAX_DELAY);
}

uint8_t al3042_read(uint8_t reg)
{
	uint8_t value;
	i2c_write(&i2cmaster, MBED_I2C_SLAVE_ADDR, (char const *)&reg, 1, 1);
	xSemaphoreTake(i2c_tx_done_sema, portMAX_DELAY);

	i2c_read(&i2cmaster, MBED_I2C_SLAVE_ADDR, (char *)&value, 1, 1);
	xSemaphoreTake(i2c_rx_done_sema, portMAX_DELAY);
	return value;
}

void al3042_read_burst(uint8_t reg, uint8_t *data, uint32_t len)
{
	i2c_write(&i2cmaster, MBED_I2C_SLAVE_ADDR, (char const *)&reg, 1, 1);
	xSemaphoreTake(i2c_tx_done_sema, portMAX_DELAY);

	i2c_read(&i2cmaster, MBED_I2C_SLAVE_ADDR, (char *) data, len, 1);
	xSemaphoreTake(i2c_rx_done_sema, portMAX_DELAY);
}
extern void i2c_set_user_callback(i2c_t *obj, I2CCallback i2ccb, void(*i2c_callback)(void *));


void al3042_init(void)
{
	i2c_rx_done_sema = xSemaphoreCreateBinary();
	i2c_tx_done_sema = xSemaphoreCreateBinary();

	memset(&i2cmaster, 0, sizeof(i2c_t));
	i2c_init(&i2cmaster, MBED_I2C_MTR_SDA, MBED_I2C_MTR_SCL);
	i2c_frequency(&i2cmaster, MBED_I2C_BUS_CLK);
	i2c_set_user_callback(&i2cmaster, I2C_RX_COMPLETE, i2c_master_rxc_callback);
	i2c_set_user_callback(&i2cmaster, I2C_TX_COMPLETE, i2c_master_txc_callback);
	al3042_write(AL3042_WAIT_TIME, (AL3042_WAIT_TIME_UINT_NUM | AL3042_WAIT_TIME_UINT_20MS));
	al3042_write(AL3042_MODE_ENABLE, AL3042_EN_ALS);
}

int al3042_light_sensor_init(void *param)
{
	al3042_init();
	return 0;
}

int al3042_get_ALS(void)
{
	int reg_text[2];
	int atime;
	int gain;
	int gain_table[8] = {1, 4, 20, 125, 2, 8, 40, 250};
	float lux, lux0, lux1, lux2;

	al3042_write(AL3042_ATIME, AL3042_ALS_TIME);
	al3042_write(AL3042_GAIN, AL3042_AGAIN_20X);
	atime = al3042_read(AL3042_ATIME);
	gain = al3042_read(AL3042_GAIN);
	reg_text[0] = al3042_read(AL3042_CH0_ADATA_L);
	reg_text[1] = al3042_read(AL3042_CH0_ADATA_H);

	//lux = (reg_text[1]<<8 | reg_text[0]) * 2.53 * (((float)64) / ((float)(atime+1))) * ( ((float)8) / ((float)gain_table[gain]));
	lux = (reg_text[1] << 8 | reg_text[0]) * 2.53 * (((float)64) / ((float)(atime + 1))) * ((float)8);
	return lux;
}
#endif // #ifdef CONFIG_PLATFORM_8195BHP

