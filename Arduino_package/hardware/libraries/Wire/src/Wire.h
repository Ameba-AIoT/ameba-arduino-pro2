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
 * Lesser General Public License for more details.ameba
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef TwoWire_h
#define TwoWire_h

#include "Stream.h"
#ifdef __cplusplus
extern "C" {
#endif

#include "i2c_api.h"

#ifdef __cplusplus
}
#endif

#define BUFFER_LENGTH 128

typedef void (*user_onRequest)(void);
typedef void (*user_onReceive)(int);

class TwoWire: public Stream {
public:
    TwoWire(void *pWireObj, uint32_t dwSDAPin, uint32_t dwSCLPin);

    void begin();
    void begin(uint8_t);
    void begin(int);

    void end();

    void setClock(uint32_t);

    uint8_t requestFrom(uint8_t, uint8_t);
    uint8_t requestFrom(uint8_t, uint8_t, uint8_t);
    uint8_t requestFrom(uint8_t, uint8_t, uint32_t, uint8_t, uint8_t);
    uint8_t requestFrom(int, int);
    uint8_t requestFrom(int, int, int);

    void beginTransmission(uint8_t);
    void beginTransmission(int);
    uint8_t endTransmission(void);
    uint8_t endTransmission(uint8_t);
    static void i2c_master_rxc_callback(void *userdata);
    static void i2c_master_txc_callback(void *userdata);

    static void i2c_slave_txc_callback(void *userdata);
    static void i2c_slave_rxc_callback(void *userdata);
    static void i2c_slave_rd_req_callback(void *userdata);

    virtual size_t write(uint8_t);
    virtual size_t write(const uint8_t *, size_t);

    virtual int available(void);
    virtual int read(void);
    virtual int peek(void);
    virtual void flush(void);

    inline size_t write(unsigned long n)
    {
        return write((uint8_t)n);
    }
    inline size_t write(long n)
    {
        return write((uint8_t)n);
    }
    inline size_t write(unsigned int n)
    {
        return write((uint8_t)n);
    }
    inline size_t write(int n)
    {
        return write((uint8_t)n);
    }
    using Print::write;

    void onReceive(void (*)(int));
    void onRequest(void (*)(void));

    void slaveWrite(void);
    void slaveReadLen(int len);
    void slaveClrRxFlag(void);
    void setWireTimeout(uint32_t timeout = 1000);
    bool getWireTimeoutFlag(void);
    void clearWireTimeoutFlag(void);

private:
    bool is_slave;

    // RX Buffer
    uint8_t rxBuffer[BUFFER_LENGTH];
    uint8_t rxBufferIndex;
    uint8_t rxBufferLength;

    // TX Buffer
    uint8_t txAddress;
    uint8_t txBuffer[BUFFER_LENGTH];
    uint8_t txBufferLength;

    // Slave RX Buffer
    uint8_t rxSlaveBuffer[BUFFER_LENGTH];
    uint8_t rxSlaveBufferIndex;
    uint8_t rxSlaveBufferLength;

    // Slave TX Buffer
    uint8_t txSlaveAddress;
    uint8_t txSlaveBuffer[BUFFER_LENGTH];
    uint8_t txSlaveBufferLength;

    // Callback user functions
    void (*user_onRequest)(void);
    void (*user_onReceive)(int);

    uint32_t SDA_pin;
    uint32_t SCL_pin;

    void *pI2C;

    // TWI clock frequency
    static const uint32_t TWI_CLOCK = 100000;
    uint32_t twiClock;

    // Timeouts
    uint32_t _timeout_tx = 5000;
    uint32_t _timeout_rx = 500000;
    uint32_t _timeout_tx_offset = 0;
    uint32_t _timeout_rx_offset = 0;
    bool _timeout_flag;

    bool _initStatus;    // flag to mark I2C init status
    uint8_t _address = 0;
    int _slvRXLen = 0;
    int _swd_pin_check = 0;
};

#if defined(BOARD_AMB82_MINI)
extern TwoWire Wire;
extern TwoWire Wire1;
#elif defined(BOARD_AMB82_ZERO)
extern TwoWire Wire;
extern TwoWire Wire1;
extern TwoWire Wire2;
#else
#error check the board supported
#endif

#endif
