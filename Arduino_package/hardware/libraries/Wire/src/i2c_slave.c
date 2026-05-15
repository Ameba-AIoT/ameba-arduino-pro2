#include "PinNames.h"
#include "pinmap.h"
#include "wiring_constants.h"
#include "i2c_slave.h"
#include "i2c_ex_api.h"

// HAL-level includes
#include "hal_i2c.h"
#include "rtl8735b_i2c.h"

// Global instance for the I2C slave
static i2c_slave_struct_t _i2c_slave = {
    NULL,    // i2c_dev
    NULL,    // arg
    0,       // slave_addr
    NULL,    // rqst_callback
    NULL,    // recv_callback
    {0},     // txBuffer
    0,       // txBufferLength
    {0},     // rxBuffer
    0,       // rxBufferLength
    0,       // rx_ready
    0        // tx_ready
};

// I2C slave initialization - properly enable slave mode
bool i2c_slave_init(i2c_t *obj, uint32_t SDA, uint32_t SCL, uint8_t addr, size_t buffer_len)
{
    i2c_slave_struct_t *i2c = &_i2c_slave;

    (void)buffer_len;    // unused

    // Store the I2C device and address
    i2c->i2c_dev = obj;
    i2c->slave_addr = addr;

    // dbg_printf("\r\n[INFO] i2c_slave_init - Initializing I2C slave with SDA pin %lu, SCL pin %lu, address 0x%02X\n", SDA, SCL, addr);

    // Initialize I2C
    // dbg_printf("\r\n[INFO] i2c_slave_init - Initializing I2C\n");
    i2c_init(obj, (PinName)SDA, (PinName)SCL);
    i2c_frequency(obj, 100000);

    // Set slave address
    // dbg_printf("\r\n[INFO] i2c_slave_init - Setting slave address to 0x%02X\n", addr);
    i2c_slave_address(obj, 0, addr, 0xFF);

    // Enable slave mode
    // dbg_printf("\r\n[INFO] i2c_slave_init - Enabling slave mode\n");
    i2c_slave_mode(obj, 1);

    // dbg_printf("\r\n[INFO] i2c_slave_init - Initialization complete\n");

    return true;
}
