#ifndef I2C_SLAVE_H
#define I2C_SLAVE_H

#include "i2c_api.h"

typedef void (*i2c_slave_request_cb_t)(void *arg);
typedef void (*i2c_slave_receive_cb_t)(uint8_t *data, size_t len, bool stop, void *arg);

typedef struct i2c_slave_struct_t {
    i2c_t *i2c_dev;
    void *arg;
    uint8_t slave_addr;
    i2c_slave_request_cb_t rqst_callback;
    i2c_slave_receive_cb_t recv_callback;
    uint8_t txBuffer[128];
    uint8_t txBufferLength;
    uint8_t rxBuffer[128];
    uint8_t rxBufferLength;
    volatile uint8_t rx_ready;
    volatile uint8_t tx_ready;
} i2c_slave_struct_t;

bool i2c_slave_init(i2c_t *obj, uint32_t SDA, uint32_t SCL, uint8_t addr, size_t buffer_len);

#endif    // I2C_SLAVE_H
