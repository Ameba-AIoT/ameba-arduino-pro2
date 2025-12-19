#ifndef AMEBAPRO2_I2C_WRAPPER_H_
#define AMEBAPRO2_I2C_WRAPPER_H_

#include "PinNames.h"
#include "basic_types.h"
#include "diag.h"
#include "i2c_api.h"
#include "pinmap.h"
#include "ex_api.h"

typedef struct tof_i2c_ctx_s {
	uint8_t tx_buffer[128];
	uint8_t tx_address;
	uint8_t tx_buffer_length;

	uint8_t rx_buffer[128];
	uint8_t rx_buffer_index;
	uint8_t rx_buffer_length;

	int tx_complete_flag;
} tof_i2c_ctx_t;

typedef struct tof_i2c_config_s {
	uint32_t bus_clk_hz;
	uint8_t  i2c_addr;
	uint16_t i2c_data_length;
	uint8_t  i2c_buffer_size;
	uint8_t  i2c_max_packet_size;
	PinName  sda;
	PinName  scl;

	i2c_t i2cmaster;
} tof_i2c_config_t;

#define lowByte(w)  ((uint8_t)((w) & 0xff))
#define highByte(w) ((uint8_t)((w) >> 8))

void tof_i2c_init(tof_i2c_config_t *cfg, tof_i2c_ctx_t *ctx);
void tof_i2c_deinit(tof_i2c_config_t *cfg);
void tof_i2c_callback_set_tx_complete_flag(void *userdata);
void tof_i2c_begin_transmission(uint8_t address);
uint8_t tof_i2c_end_transmission(void);
uint8_t tof_i2c_end_transmission_non_send_stop(void);
size_t tof_i2c_write_data(uint8_t data);
int tof_i2c_read_data(void);
uint8_t tof_i2c_request_from(uint8_t address, uint8_t quantity);
int tof_i2c_available(void);
uint8_t tof_i2c_write_single_byte(uint16_t registerAddress, const uint8_t value);
uint8_t tof_i2c_read_single_byte(uint16_t registerAddress);
uint8_t tof_i2c_write_multiple_bytes(uint16_t registerAddress, uint8_t *buffer, uint16_t bufferSize);
uint8_t tof_i2c_read_multiple_bytes(uint16_t registerAddress, uint8_t *buffer, uint16_t bufferSize);

#endif