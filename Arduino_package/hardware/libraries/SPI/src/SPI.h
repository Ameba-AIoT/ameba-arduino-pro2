/*
 * Copyright (c) 2010 by Cristian Maglie <c.maglie@arduino.cc>
 * Copyright (c) 2014 by Paul Stoffregen <paul@pjrc.com> (Transaction API)
 * SPI Master library for arduino.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */

#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED

#include "variant.h"
#include <stdio.h>
#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "device.h"
#include "diag.h"
#include "main.h"
#include "spi_api.h"
#include "spi_ex_api.h"

#ifdef __cplusplus
}
#endif

// SPI_HAS_TRANSACTION means SPI has
//   - beginTransaction()
//   - endTransaction()
//   - usingInterrupt()
//   - SPISetting(clock, bitOrder, dataMode)
#define SPI_HAS_TRANSACTION 1

// SPI_HAS_EXTENDED_CS_PIN_HANDLING means SPI has automatic
// CS pin handling and provides the following methods:
//   - begin(pin)
//   - end(pin)
//   - setBitOrder(pin, bitorder)
//   - setDataMode(pin, datamode)
//   - setClockDivider(pin, clockdiv)
//   - transfer(pin, data, SPI_LAST/SPI_CONTINUE)
//   - beginTransaction(pin, SPISettings settings) (if transactions are available)
#define SPI_HAS_EXTENDED_CS_PIN_HANDLING 1

#define SPI_DATA_MODE0 0x00
#define SPI_DATA_MODE1 0x01
#define SPI_DATA_MODE2 0x02
#define SPI_DATA_MODE3 0x03

#define SPI_MODE0 SPI_DATA_MODE0
#define SPI_MODE1 SPI_DATA_MODE1
#define SPI_MODE2 SPI_DATA_MODE2
#define SPI_MODE3 SPI_DATA_MODE3

#define SPI_MODE_MASTER 'M'
#define SPI_MODE_SLAVE  'S'

#define SPI_DEFAULT_FREQ 200000

enum SPITransferMode {
    SPI_CONTINUE,
    SPI_LAST
};

class SPISettings {
public:
    SPISettings(uint32_t clock, BitOrder bitOrder, uint8_t dataMode)
    {
        _clockSetting = clock;
        _bitOrderSetting = bitOrder;
        _dataModeSetting = dataMode;
    }

    SPISettings(void)
    {
        SPISettings(4000000, MSBFIRST, SPI_DATA_MODE0);
    }

private:
    uint32_t _clockSetting;
    BitOrder _bitOrderSetting;
    uint8_t _dataModeSetting;

    friend class SPIClass;
};

class SPIClass {
public:
    // Construct an object and configure SPI parameters — clock speed, bit order and data mode to the preferred default value.
    SPIClass(spi_t *pSpiObj, int mosi_pin, int miso_pin, int clk_pin, int ss_pin);

    // Initialize MOSI, MISO, CLK, and SS pins on Ameba boards, select SPIClass object, and set SPI format and frequency
    void begin(void);
    void begin(int ss_pin);
    void begin(char SPI_mode);
    void begin(int ss_pin, char SPI_mode);

    // Set slave select pin and SPI initial settings
    void beginTransaction(uint8_t ss_pin, SPISettings settings);
    void beginTransaction(SPISettings settings);

    // Stop SPI transaction
    void endTransaction(void);

    // For transferring 1 byte data with and without SS
    byte transfer(uint8_t data, SPITransferMode mode = SPI_LAST);
    byte transfer(byte pin, uint8_t data, SPITransferMode mode = SPI_LAST);

    void transfer(byte pin, void *buf, size_t count, SPITransferMode mode = SPI_LAST);
    void transfer(void *buf, size_t count, SPITransferMode mode = SPI_LAST);

    // For transferring 2 bytes data with and without SS
    uint16_t transfer16(uint16_t data, SPITransferMode mode = SPI_LAST);
    uint16_t transfer16(byte pin, uint16_t data, SPITransferMode mode = SPI_LAST);

    // Retrieve data from receive buffer as slave
    int slaveRead(void);

    // Set bit order to either MSB first or LSB first
    void setBitOrder(uint8_t pin, BitOrder order);
    void setBitOrder(BitOrder order);

    // Set data mode
    void setDataMode(uint8_t pin, uint8_t dataMode, char SPI_mode = SPI_MODE_MASTER);
    // void setDataMode(uint8_t _mode);

    // Set to correct clock speed (no effect on Ameba)
    void setClockDivider(uint8_t pin, uint8_t divider);
    void setClockDivider(uint8_t div);

    // Stop SPI master/slave mode
    void end(char SPI_mode);

    /* extend api added by RTK */
    // Set default SPI frequency
    void setDefaultFrequency(int frequency);

private:
    spi_t *pSpiMaster;
    spi_t *pSpiSlave;

    int _pinMOSI;
    int _pinMISO;
    int _pinCLK;
    int _pinSS;
    int _pinUserSS;
    int _defaultFrequency;
    BitOrder _bitOrder;
    u8 _dataBits;
    u8 _dataMode;
    char _SPI_Mode;

    bool initStatus;    // flag to mark SPI init status
};

extern SPIClass SPI;
extern SPIClass SPI1;

#endif
