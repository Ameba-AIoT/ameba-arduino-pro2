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

#include "SPI.h"
#include "Arduino.h"

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

spi_t spi_obj0;
spi_t spi_obj1;

SPIClass::SPIClass(void *pSpiObj, int mosi, int miso, int clk, int ss)
{
    pSpiMaster = pSpiObj;

    /* These 4 pins should belong same spi pinmux*/
    pinMOSI = mosi;
    pinMISO = miso;
    pinCLK = clk;
    pinSS = ss;

    pinUserSS = -1;
    defaultFrequency = SPI_DEFAULT_FREQ;
}

void SPIClass::begin(void)
{
    spi_init(
        (spi_t *)pSpiMaster,
        (PinName)g_APinDescription[pinMOSI].pinname, 
        (PinName)g_APinDescription[pinMISO].pinname, 
        (PinName)g_APinDescription[pinCLK].pinname, 
        (PinName)g_APinDescription[pinSS].pinname
    );
    spi_format((spi_t *)pSpiMaster, 8, 0, 0);
    spi_frequency((spi_t *)pSpiMaster, defaultFrequency);
}

void SPIClass::begin(int ss)
{
    pinSS = (PinName)g_APinDescription[ss].pinname;

    spi_init(
        (spi_t *)pSpiMaster,
        (PinName)g_APinDescription[pinMOSI].pinname, 
        (PinName)g_APinDescription[pinMISO].pinname, 
        (PinName)g_APinDescription[pinCLK].pinname, 
        (PinName)g_APinDescription[pinSS].pinname
    );
    spi_format((spi_t *)pSpiMaster, 8, 0, 0);
    spi_frequency((spi_t *)pSpiMaster, defaultFrequency);
}

void SPIClass::beginTransaction(uint8_t pin, SPISettings settings)
{
    bitOrder = settings._bitOrder;
    spi_format((spi_t *)pSpiMaster, 8, settings._dataMode, 0);
    spi_frequency((spi_t *)pSpiMaster, settings._clock);

    pinUserSS = pin;
    pinMode(pinUserSS, OUTPUT);
    digitalWrite(pinUserSS, 0);
}

void SPIClass::beginTransaction(SPISettings settings)
{
    beginTransaction(pinSS, settings);
}

void SPIClass::endTransaction(void)
{
    if (pinUserSS >= 0) {
        digitalWrite(pinUserSS, 1);
        pinUserSS = -1;
    }
}

byte SPIClass::transfer(uint8_t _data, SPITransferMode _mode){ // transfer 1 byte data without SS
    (void)_mode;
    
    spi_master_write((spi_t *)pSpiMaster, _data);
    //printf("Master write: %02X\n\r", _data);
    return 0;
}

byte SPIClass::transfer(byte _pin, uint8_t _data, SPITransferMode _mode){ // transfer 1 byte data with SS

    if (_pin != pinSS) {
        pinMode(_pin, OUTPUT);
        digitalWrite(_pin, 0);
    }
    spi_master_write((spi_t *)pSpiMaster, _data);
    //printf("Master write: %02X\n\r", _data);
    
    return 0;
}

void SPIClass::transfer(byte _pin, void *_buf, SIZE_T _count, SPITransferMode _mode)
{
    if (_pin != pinSS) {
        pinMode(_pin, OUTPUT);
        digitalWrite(_pin, 0);
    }

    spi_master_write_read_stream((spi_t *)pSpiMaster, (char *)_buf, (char *)_buf, (uint32_t)_count);

    if ((_pin != pinSS) && (_mode == SPI_LAST)) {
        digitalWrite(_pin, 1);
    }
}

void SPIClass::transfer(void *_buf, SIZE_T _count, SPITransferMode _mode)
{
    transfer(pinSS, _buf, _count, _mode);
}

uint16_t SPIClass::transfer16(byte _pin, uint16_t _data, SPITransferMode _mode)
{
    union { uint16_t val; struct { uint8_t lsb; uint8_t msb; }; } t;
    t.val = _data;

    if (bitOrder == LSBFIRST) {
        t.lsb = transfer(_pin, t.lsb, SPI_CONTINUE);
        t.msb = transfer(_pin, t.msb, _mode);
    } else {
        t.msb = transfer(_pin, t.msb, SPI_CONTINUE);
        t.lsb = transfer(_pin, t.lsb, _mode);
    }
    //printf("Master write: %04X\n\r", t.val);
    
    _data = t.val;
    return _data;
}

uint16_t SPIClass::transfer16(uint16_t _data, SPITransferMode _mode)
{
    return transfer16(pinSS, _data, _mode);
}

void SPIClass::setBitOrder(uint8_t _pin, BitOrder _bitOrder)
{
    (void)_pin;

    bitOrder = _bitOrder;
}

void SPIClass::setDataMode(uint8_t _pin, uint8_t _mode)
{
    (void)_pin;

    spi_format((spi_t *)pSpiMaster, 8, _mode, 0);
}

void SPIClass::setClockDivider(uint8_t _pin, uint8_t _divider)
{
    (void)_pin;
    (void)_divider;

    // no effect on Ameba
}

void SPIClass::setBitOrder(BitOrder _order)
{
    setBitOrder(pinSS, _order);
}

void SPIClass::setClockDivider(uint8_t _div)
{
    (void)_div;

    // no effect on Ameba
}

void SPIClass::setDefaultFrequency(int _frequency)
{
    defaultFrequency = _frequency;
}

void SPIClass::end(void)
{
    spi_free((spi_t *)pSpiMaster);
}

SPIClass SPI((void *)(&spi_obj0), 13, 14, 15, 12);
SPIClass SPI1((void *)(&spi_obj1), 2, 0, 1, 3);
