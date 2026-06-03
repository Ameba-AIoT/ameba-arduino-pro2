/*
 * TwoWire.h - TWI/I2C library for Arduino Due
 * Copyright (c) 2011 Cristian Maglie <c.maglie@arduino.cc>
 * All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "Arduino.h"
#include "Wire.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include "PinNames.h"
#include "i2c_api.h"
#include "i2c_ex_api.h"
#include "wait_api.h"
#include "ex_api.h"
#include "i2c_slave.h"

i2c_t i2cwire0;
i2c_t i2cwire1;

#ifdef __cplusplus
}
#endif

TwoWire::TwoWire(void *pWireObj, uint32_t dwSDAPin, uint32_t dwSCLPin)
{
    this->SDA_pin = dwSDAPin;
    this->SCL_pin = dwSCLPin;
    this->user_onReceive = NULL;
    this->user_onRequest = NULL;
    this->pI2C = pWireObj;
    this->is_slave = false;

    this->rxBufferIndex = 0;
    this->rxBufferLength = 0;
    this->txAddress = 0;
    this->txBufferLength = 0;
    this->twiClock = this->TWI_CLOCK;
}

int I2C_DATA_LENGTH = 1;    // 125
volatile int flag_mst_tx = 0;
volatile int flag_mst_rx = 0;
volatile int flag_slv_tx = 0;
volatile int flag_slv_rx = 0;
volatile int flag_rd_req = 0;

void TwoWire::begin()
{
    if (_initStatus) {
        // Already initialized, so do nothing or maybe re-config only
        return;
    }

    // Zero out the i2c_t structure like raw mbed API does
    memset(((i2c_t *)this->pI2C), 0x00, sizeof(i2c_t));

    amb_ard_pin_check_fun(SDA_pin, PIO_I2C);
    amb_ard_pin_check_fun(SCL_pin, PIO_I2C);

    SDA_pin = (PinName)g_APinDescription[SDA_pin].pinname;
    SCL_pin = (PinName)g_APinDescription[SCL_pin].pinname;

    // SWD_DATA, SWD_CLK, deinit
    if ((SCL_pin == PA_0 || (SDA_pin == PA_1) {
        if (_swd_pin_check == 0) {
            hal_sys_dbg_port_cfg(DBG_PORT_OFF, TMS_IO_S0_CLK_S0);
            _swd_pin_check = 1;
        }
    }

    i2c_init(((i2c_t *)this->pI2C), ((PinName)this->SDA_pin), ((PinName)this->SCL_pin));
    i2c_frequency(((i2c_t *)this->pI2C), this->twiClock);

    // Set up callbacks once at initialization (like raw mbed API does)
    i2c_set_user_callback(((i2c_t *)this->pI2C), I2C_TX_COMPLETE, i2c_master_txc_callback);
    i2c_set_user_callback(((i2c_t *)this->pI2C), I2C_RX_COMPLETE, i2c_master_rxc_callback);

    _initStatus = true;
}

void TwoWire::begin(uint8_t address)
{
    // Zero out the i2c_t structure
    memset(((i2c_t *)this->pI2C), 0x00, sizeof(i2c_t));

    amb_ard_pin_check_fun(SDA_pin, PIO_I2C);
    amb_ard_pin_check_fun(SCL_pin, PIO_I2C);

    SDA_pin = (PinName)g_APinDescription[SDA_pin].pinname;
    SCL_pin = (PinName)g_APinDescription[SCL_pin].pinname;

    // SWD_DATA, SWD_CLK, deinit
    if ((SCL_pin == PA_0 || (SDA_pin == PA_1) {
        if (_swd_pin_check == 0) {
            hal_sys_dbg_port_cfg(DBG_PORT_OFF, TMS_IO_S0_CLK_S0);
            _swd_pin_check = 1;
        }
    }

    // Init I2C as slave using native mbed API
    // dbg_printf("\r\n[INFO] TwoWire::begin() - Calling i2c_slave_init with SDA pin %lu, SCL pin %lu, address 0x%02X\n", this->SDA_pin, this->SCL_pin, address);
    i2c_slave_init((i2c_t *)this->pI2C, (uint32_t)this->SDA_pin, (uint32_t)this->SCL_pin, address, BUFFER_LENGTH);

    is_slave = true;

    // Initialize rx buffer state
    rxBufferIndex = 0;
    rxBufferLength = 0;

    // Attach callbacks
    // dbg_printf("\r\n[INFO] i2c_slave_init - Attaching callbacks\n");
    i2c_set_user_callback((i2c_t *)this->pI2C, I2C_RX_COMPLETE, i2c_slave_rxc_callback);
    i2c_set_user_callback((i2c_t *)this->pI2C, I2C_TX_COMPLETE, i2c_slave_txc_callback);
    i2c_set_user_callback((i2c_t *)this->pI2C, I2C_RD_REQ_COMMAND, i2c_slave_rd_req_callback);

    // NAK handling sequence
    // dbg_printf("\r\n[INFO] i2c_slave_init - Setting up NAK handling\n");
    i2c_slave_set_for_data_nak((i2c_t *)this->pI2C, 1);
    wait_us(5000);
    i2c_slave_set_for_data_nak((i2c_t *)this->pI2C, 0);
}

void TwoWire::begin(int address)
{
    begin((uint8_t)address);
}

void TwoWire::end()
{
    i2c_reset((i2c_t *)this->pI2C);
    _initStatus = false;
}

void TwoWire::setClock(uint32_t frequency)
{
    twiClock = frequency;
    i2c_frequency(((i2c_t *)this->pI2C), this->twiClock);
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity, uint8_t sendStop)
{
    if (quantity > BUFFER_LENGTH) {
        quantity = BUFFER_LENGTH;
    }

    // Clear RX complete flag before starting transfer
    flag_mst_rx = 0;

    // i2c_read() is interrupt-driven on this platform.
    // It starts the transfer and returns immediately.
    // The RX complete callback fires when the transfer is done.
    i2c_read(((i2c_t *)this->pI2C), ((int)address), reinterpret_cast<char *>(this->rxBuffer), ((int)quantity), ((int)sendStop));

    // Wait for RX complete callback with timeout
    uint32_t timeout_rx = _timeout_rx;

    do {
        timeout_rx--;
        wait_us(this->rxBufferLength * 100);    // Wait time proportional to expected data length
    } while (flag_mst_rx == 0 && timeout_rx > 0);

    // set rx buffer iterator vars
    rxBufferIndex = 0;
    rxBufferLength = quantity;

    return quantity;
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t quantity)
{
    return requestFrom(((uint8_t)address), ((uint8_t)quantity), ((uint8_t) true));
}

uint8_t TwoWire::requestFrom(int address, int quantity)
{
    return requestFrom(((uint8_t)address), ((uint8_t)quantity), ((uint8_t) true));
}

uint8_t TwoWire::requestFrom(int address, int quantity, int sendStop)
{
    return requestFrom(((uint8_t)address), ((uint8_t)quantity), ((uint8_t)sendStop));
}

void TwoWire::beginTransmission(uint8_t address)
{
    // save address of target and empty buffer
    // If target address changes, wait for 50us to avoid losing next data packet, tested ok down to 10us

    // Top comment is original comment, currently for I2C Scanner, this delay is creating a huge scan time, removed to make the scanning much faster.
    // Seems like unnecessary delay: To be tested by QC.
    if (txAddress != address) {
        txAddress = address;
        //    delay(50);
    }
    txBufferLength = 0;
}

void TwoWire::beginTransmission(int address)
{
    beginTransmission(((uint8_t)address));
}

//  Originally, 'endTransmission' was an f(void) function.
//  It has been modified to take one parameter indicating
//  whether or not a STOP should be performed on the bus.
//  Calling endTransmission(false) allows a sketch to
//  perform a repeated start.
//
//  WARNING: Nothing in the library keeps track of whether
//  the bus tenure has been properly ended with a STOP. It
//  is very possible to leave the bus in a hung state if
//  no call to endTransmission(true) is made. Some I2C
//  devices will behave oddly if they do not see a STOP.
uint8_t TwoWire::endTransmission(uint8_t sendStop)
{
    int length;
    uint8_t error = 0;
    i2c_reset((i2c_t *)this->pI2C);    // Reset I2C to clear any previous state before starting new transmission
    // Clear TX complete flag before starting transfer
    flag_mst_tx = 0;

    i2c_init(((i2c_t *)this->pI2C), ((PinName)this->SDA_pin), ((PinName)this->SCL_pin));
    i2c_frequency(((i2c_t *)this->pI2C), this->twiClock);
    i2c_set_user_callback(((i2c_t *)this->pI2C), I2C_TX_COMPLETE, i2c_master_txc_callback);
    i2c_set_user_callback(((i2c_t *)this->pI2C), I2C_RX_COMPLETE, i2c_master_rxc_callback);

    if (sendStop == false) {
        i2c_restart_enable(((i2c_t *)this->pI2C));
    }

    // dbg_printf("\r\n[DEBUG] endTransmission: addr=0x%02X, len=%d, stop=%d\n",
    //        this->txAddress, this->txBufferLength, sendStop);

    // i2c_write() is interrupt-driven on this platform.
    // It starts the transfer and returns immediately.
    // The TX complete callback fires when the transfer is done.
    length = i2c_write(((i2c_t *)this->pI2C), ((int)this->txAddress), reinterpret_cast<char *>(this->txBuffer), ((int)this->txBufferLength), ((int)sendStop));

    // dbg_printf("\r\n[DEBUG] endTransmission: i2c_write returned %d\n", length);

    // Wait for TX complete callback with timeout
    uint32_t timeout_tx = _timeout_tx;
    do {
        timeout_tx--;
        wait_us(this->txBufferLength * 200);    // Wait time proportional to expected data length
    } while (flag_mst_tx == 0 && timeout_tx > 0);

    // dbg_printf("\r\n[DEBUG] endTransmission: flag_mst_tx=%d after wait\n", flag_mst_tx);

    if (sendStop == false) {
        i2c_restart_disable(((i2c_t *)this->pI2C));
    }
    if (txBufferLength > 0 && length <= 0) {
        error = 2;    // Error: Data was not sent (length <= 0 indicates a failure in starting the transfer)
    } else if (flag_mst_tx == 0) {
        error = 1;    // Error: TX complete callback did not fire within timeout
    } else {
        error = 0;    // Success
    }

    txBufferLength = 0;    // empty buffer

    return error;
}

// This provides backwards compatibility with the original
// definition, and expected behaviour, of endTransmission
uint8_t TwoWire::endTransmission(void)
{
    return endTransmission(true);
}

void TwoWire::i2c_master_txc_callback(void *userdata)
{
    // dbg_printf("\r\n[DEBUG] i2c_master_txc_callback called - setting flag_tx to 1\n");
    flag_mst_tx = 1;
}

void TwoWire::i2c_master_rxc_callback(void *userdata)
{
    // dbg_printf("\r\n[DEBUG] i2c_master_rxc_callback called - setting flag_rx to 1\n");
    flag_mst_rx = 1;
}

void TwoWire::i2c_slave_txc_callback(void *userdata)
{
    flag_slv_tx = 1;
}

void TwoWire::i2c_slave_rxc_callback(void *userdata)
{
    // dbg_printf("\r\n[DEBUG] i2c_slave_rxc_callback called - setting flag_rx to 1\n");
    flag_slv_rx = 1;
}

void TwoWire::i2c_slave_rd_req_callback(void *userdata)
{
    // dbg_printf("\r\n[DEBUG] i2c_slave_rd_req_callback called - setting flag_rd_req to 1\n");
    flag_rd_req = 1;
}

size_t TwoWire::write(uint8_t data)
{
    if (is_slave) {
        if (txSlaveBufferLength >= BUFFER_LENGTH) {
            return 0;
        }
        txSlaveBuffer[txSlaveBufferLength++] = data;
    } else {
        if (txBufferLength >= BUFFER_LENGTH) {
            return 0;
        }
        txBuffer[txBufferLength++] = data;
    }

    return 1;
}

size_t TwoWire::write(const uint8_t *data, size_t quantity)
{
    if (is_slave) {
        for (size_t i = 0; i < quantity; ++i) {
            if (txSlaveBufferLength >= BUFFER_LENGTH) {
                return i;
            }
            txSlaveBuffer[txSlaveBufferLength++] = data[i];
        }
    } else {
        // In master mode, write() is called before endTransmission(), so we buffer the data and send it all at once in endTransmission().
        for (size_t i = 0; i < quantity; ++i) {
            if (txBufferLength >= BUFFER_LENGTH) {
                return i;
            }
            txBuffer[txBufferLength++] = data[i];
        }
    }
    return quantity;
}

int TwoWire::available(void)
{
    // dbg_printf("\r\n[INFO] available() called - rxBufferIndex=%d, rxBufferLength=%d\n", rxBufferIndex, rxBufferLength);
    // For slave mode, poll for incoming data from master
    if (!is_slave) {
        return (rxBufferLength - rxBufferIndex);
    } else if (is_slave && pI2C && flag_slv_rx == 0) {
        memset(this->rxSlaveBuffer, 0, _slvRXLen);
        i2c_slave_read((i2c_t *)pI2C, reinterpret_cast<char *>(this->rxSlaveBuffer), _slvRXLen);

        while (flag_slv_rx == 0) {
            // Wait for the RX complete callback to set the flag
            wait_us(100);
        }
        // dbg_printf("\r\n[DEBUG] available() - i2c_slave_read returned %d bytes\n", len);

        rxSlaveBufferLength = _slvRXLen;    // Use the length set by slaveReadLen() instead of the raw length from i2c_slave_read()
        // dbg_printf("\r\n[INFO] available() - Received %d bytes from master, copied to rxBuffer\n", _slvRXLen);
        rxSlaveBufferIndex = 0;
        if (user_onReceive) {
            // dbg_printf("\r\n[DEBUG] available() - Calling user_onReceive callback with length %d\n", _slvRXLen);
            user_onReceive(_slvRXLen);
        }
    }
    return (rxSlaveBufferLength - rxSlaveBufferIndex);
}

int TwoWire::read(void)
{
    if (!is_slave && rxBufferIndex < rxBufferLength) {
        return rxBuffer[rxBufferIndex++];
    } else if (is_slave && rxSlaveBufferIndex < rxSlaveBufferLength) {
        return rxSlaveBuffer[rxSlaveBufferIndex++];
    }
    return -1;
}

int TwoWire::peek(void)
{
    if (!is_slave && rxBufferIndex < rxBufferLength) {
        return rxBuffer[rxBufferIndex];
    } else if (is_slave && rxSlaveBufferIndex < rxSlaveBufferLength) {
        return rxSlaveBuffer[rxSlaveBufferIndex];
    }
    return -1;
}

void TwoWire::flush(void)
{
    // Do nothing, use endTransmission(..) to force
    // data transfer.
}

void TwoWire::slaveWrite(void)
{
    flag_rd_req = 0;    // Clear read request flag

    i2c_slave_set_for_rd_req((i2c_t *)this->pI2C, 1);
    while (flag_rd_req == 0) {
        // Wait for master to request data
        wait_us(100);
    }

    // dbg_printf("\r\n[DEBUG] slaveWrite - user_onRequest=%p\n", user_onRequest);
    if (!user_onRequest) {
        dbg_printf("\r\n[DEBUG] slaveWrite - No user callback, returning\n");
        return;
    }
    txSlaveBufferLength = 0;

    user_onRequest();    // user callback normally write data into txbuffer

    flag_slv_tx = 0;    // Clear TX complete flag before any transmission

    // dbg_dbg_printf("\r\n[DEBUG] slaveWrite - Calling i2c_slave_write with %d bytes\n", txSlaveBufferLength);
    i2c_slave_write((i2c_t *)this->pI2C, reinterpret_cast<char *>(this->txSlaveBuffer), ((int)this->txSlaveBufferLength));
    while (flag_slv_tx == 0) {
        // Wait for TX complete callback to set the flag
        wait_us(100);
    }
}

void TwoWire::onReceive(void (*function)(int))
{
    user_onReceive = function;
}

void TwoWire::onRequest(void (*function)(void))
{
    user_onRequest = function;
}

void TwoWire::slaveReadLen(int len)
{
    _slvRXLen = len;
}

void TwoWire::slaveClrRxFlag(void)
{
    flag_slv_rx = 0;
}

void TwoWire::setWireTimeout(uint32_t timeout)
{
    _timeout_tx_offset = timeout;
    _timeout_tx += timeout;
    _timeout_rx_offset = timeout;
    _timeout_rx += timeout;
    _timeout_flag = true;
    dbg_printf("\r\n[INFO]Timeout is set by user\n");
}

bool TwoWire::getWireTimeoutFlag(void)
{
    return (_timeout_flag);
}

void TwoWire::clearWireTimeoutFlag(void)
{

    if (_timeout_flag) {
        _timeout_tx -= _timeout_tx_offset;
        _timeout_rx -= _timeout_rx_offset;
        _timeout_tx_offset = 0;
        _timeout_rx_offset = 0;
        _timeout_flag = false;
        dbg_printf("\r\n[INFO] User-set timeout is cleared\n");
    } else {
        dbg_printf("\r\n[ERROR] No timeout is set\n");
    }
}

TwoWire Wire = TwoWire((void *)(&i2cwire0), I2C_SDA, I2C_SCL);
TwoWire Wire1 = TwoWire((void *)(&i2cwire1), I2C1_SDA, I2C1_SCL);
