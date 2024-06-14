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

spi_t spi_obj0;
spi_t spi_obj1;

SPIClass::SPIClass(spi_t *pSpiObj, int mosi_pin, int miso_pin, int clk_pin, int ss_pin)
{
    pSpiMaster = pSpiObj;
    pSpiSlave = pSpiObj;

    /* These 4 pins should belong same spi pinmux*/
    _pinMOSI = mosi_pin;
    _pinMISO = miso_pin;
    _pinCLK = clk_pin;
    _pinSS = ss_pin;

    initStatus = false;
    _dataBits = 8;                 // default databits is 8 bits
    _dataMode = SPI_DATA_MODE0;    // default datamode is mode 0
    _defaultFrequency = SPI_DEFAULT_FREQ;
    // _pinUserSS = -1;

    _SPI_Mode = SPI_MODE_MASTER;
}

void SPIClass::begin(void)
{
    amb_ard_pin_check_fun(_pinMOSI, PIO_SPI);
    amb_ard_pin_check_fun(_pinMISO, PIO_SPI);
    amb_ard_pin_check_fun(_pinCLK, PIO_SPI);
    amb_ard_pin_check_fun(_pinSS, PIO_SPI);

    _pinMOSI = (PinName)g_APinDescription[_pinMOSI].pinname;
    _pinMISO = (PinName)g_APinDescription[_pinMISO].pinname;
    _pinCLK = (PinName)g_APinDescription[_pinCLK].pinname;
    _pinSS = (PinName)g_APinDescription[_pinSS].pinname;

    spi_init(
        pSpiMaster,
        (PinName)(_pinMOSI),
        (PinName)(_pinMISO),
        (PinName)(_pinCLK),
        (PinName)(_pinSS));
    spi_format(pSpiMaster, _dataBits, _dataMode, 0);
    spi_frequency(pSpiMaster, _defaultFrequency);

    // Mark SPI init status
    initStatus = true;
}

void SPIClass::begin(int ss_pin)
{
    _pinSS = ss_pin;

    amb_ard_pin_check_fun(_pinMOSI, PIO_SPI);
    amb_ard_pin_check_fun(_pinMISO, PIO_SPI);
    amb_ard_pin_check_fun(_pinCLK, PIO_SPI);
    amb_ard_pin_check_fun(_pinSS, PIO_SPI);

    _pinMOSI = (PinName)g_APinDescription[_pinMOSI].pinname;
    _pinMISO = (PinName)g_APinDescription[_pinMISO].pinname;
    _pinCLK = (PinName)g_APinDescription[_pinCLK].pinname;
    _pinSS = (PinName)g_APinDescription[_pinSS].pinname;

    spi_init(
        pSpiMaster,
        (PinName)(_pinMOSI),
        (PinName)(_pinMISO),
        (PinName)(_pinCLK),
        (PinName)(_pinSS));
    spi_format(pSpiMaster, _dataBits, _dataMode, 0);
    spi_frequency(pSpiMaster, _defaultFrequency);

    // Mark SPI init status
    initStatus = true;
}

void SPIClass::begin(char SPI_mode)
{
    _SPI_Mode = SPI_mode;
    if (_SPI_Mode == SPI_MODE_MASTER) {
        begin();
    } else if (_SPI_Mode == SPI_MODE_SLAVE) {
        amb_ard_pin_check_fun(_pinMOSI, PIO_SPI);
        amb_ard_pin_check_fun(_pinMISO, PIO_SPI);
        amb_ard_pin_check_fun(_pinCLK, PIO_SPI);
        amb_ard_pin_check_fun(_pinSS, PIO_SPI);

        _pinMOSI = (PinName)g_APinDescription[_pinMOSI].pinname;
        _pinMISO = (PinName)g_APinDescription[_pinMISO].pinname;
        _pinCLK = (PinName)g_APinDescription[_pinCLK].pinname;
        _pinSS = (PinName)g_APinDescription[_pinSS].pinname;

        spi_init(
            pSpiSlave,
            (PinName)(_pinMOSI),
            (PinName)(_pinMISO),
            (PinName)(_pinCLK),
            (PinName)(_pinSS));
        spi_format(pSpiSlave, _dataBits, _dataMode, 1);

        // Mark SPI init status
        initStatus = true;
    } else {
        printf("\r\n[ERROR] SPI begin: SPI mode \n");
        return;
    }
}

void SPIClass::begin(int ss_pin, char SPI_mode)
{
    _SPI_Mode = SPI_mode;
    if (_SPI_Mode == SPI_MODE_MASTER) {
        begin(ss_pin);
    } else if (_SPI_Mode == SPI_MODE_SLAVE) {
        _pinSS = ss_pin;

        amb_ard_pin_check_fun(_pinMOSI, PIO_SPI);
        amb_ard_pin_check_fun(_pinMISO, PIO_SPI);
        amb_ard_pin_check_fun(_pinCLK, PIO_SPI);
        amb_ard_pin_check_fun(_pinSS, PIO_SPI);

        _pinMOSI = (PinName)g_APinDescription[_pinMOSI].pinname;
        _pinMISO = (PinName)g_APinDescription[_pinMISO].pinname;
        _pinCLK = (PinName)g_APinDescription[_pinCLK].pinname;
        _pinSS = (PinName)g_APinDescription[_pinSS].pinname;

        spi_init(
            pSpiSlave,
            (PinName)(_pinMOSI),
            (PinName)(_pinMISO),
            (PinName)(_pinCLK),
            (PinName)(_pinSS));
        spi_format(pSpiSlave, _dataBits, _dataMode, 1);

        // Mark SPI init status
        initStatus = true;
    } else {
        printf("\r\n[ERROR] SPI begin: SPI mode \n");
        return;
    }
}

void SPIClass::beginTransaction(uint8_t ss_pin, SPISettings settings)
{
    _bitOrder = settings._bitOrderSetting;

#if 0
    spi_free(pSpiMaster);
    spi_init(
        pSpiMaster,
        (PinName)g_APinDescription[_pinMOSI].pinname, 
        (PinName)g_APinDescription[_pinMISO].pinname, 
        (PinName)g_APinDescription[_pinCLK].pinname, 
        (PinName)g_APinDescription[_pinSS].pinname
    );
    spi_format(pSpiMaster, 8, settings._settingdataMode, 0);
#else
    phal_ssi_adaptor_t phal_ssi_adaptor = &(pSpiMaster->hal_ssi_adaptor);
    hal_spi_format(phal_ssi_adaptor, (8 - 1), settings._dataModeSetting);
#endif

    spi_frequency(pSpiMaster, settings._clockSetting);
}

void SPIClass::beginTransaction(SPISettings settings)
{
    beginTransaction(_pinSS, settings);
}

void SPIClass::endTransaction(void)
{
    // if (_pinUserSS >= 0) {
    //     digitalWrite(_pinUserSS, 1);
    //     _pinUserSS = -1;
    // }
}

byte SPIClass::transfer(uint8_t data, SPITransferMode mode)
{    // transfer 1 byte data without SS
    (void)mode;
    spi_master_write(pSpiMaster, data);
    // printf("\r\n[INFO] Master write: %02X\n", _data);
    return 0;
}

byte SPIClass::transfer(byte pin, uint8_t data, SPITransferMode mode)
{    // transfer 1 byte data with SS
    if (pin != _pinSS) {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, 0);
    }
    spi_master_write(pSpiMaster, data);
    // printf("\r\n[INFO] Master write: %02X\n", _data);

    return 0;
}

void SPIClass::transfer(byte pin, void *buf, SIZE_T count, SPITransferMode mode)
{
    if (pin != _pinSS) {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, 0);
    }

    spi_master_write_read_stream(pSpiMaster, (char *)buf, (char *)buf, (uint32_t)count);

    if ((pin != _pinSS) && (mode == SPI_LAST)) {
        digitalWrite(pin, 1);
    }
}

void SPIClass::transfer(void *buf, SIZE_T count, SPITransferMode mode)
{
    transfer(_pinSS, buf, count, mode);
}

uint16_t SPIClass::transfer16(byte pin, uint16_t data, SPITransferMode mode)
{
    union {
        uint16_t val;
        struct {
            uint8_t lsb;
            uint8_t msb;
        };
    } t;

    t.val = data;

    if (_bitOrder == LSBFIRST) {
        t.lsb = transfer(pin, t.lsb, SPI_CONTINUE);
        t.msb = transfer(pin, t.msb, mode);
    } else {
        t.msb = transfer(pin, t.msb, SPI_CONTINUE);
        t.lsb = transfer(pin, t.lsb, mode);
    }
    // printf("\r\n[INFO] Master write: %04X\n", t.val);

    data = t.val;
    return data;
}

uint16_t SPIClass::transfer16(uint16_t data, SPITransferMode mode)
{
    return transfer16(_pinSS, data, mode);
}

int SPIClass::slaveRead(void)
{
    return spi_slave_read(pSpiSlave);
}

void SPIClass::setBitOrder(uint8_t pin, BitOrder order)
{
    (void)pin;

    _bitOrder = order;
}

void SPIClass::setBitOrder(BitOrder order)
{
    setBitOrder(_pinSS, order);
}

void SPIClass::setDataMode(uint8_t bits, uint8_t dataMode, char SPI_mode)
{
    _dataBits = bits;
    _dataMode = dataMode;
    _SPI_Mode = SPI_mode;

    if (initStatus) {
        if (_SPI_Mode == SPI_MODE_MASTER) {
            spi_format(pSpiMaster, _dataBits, _dataMode, 0);
        } else if (_SPI_Mode == SPI_MODE_SLAVE) {
            spi_format(pSpiSlave, _dataBits, _dataMode, 1);
        }
    }
}

void SPIClass::setClockDivider(uint8_t pin, uint8_t divider)
{
    (void)pin;
    (void)divider;
    // no effect on Ameba
}

void SPIClass::setClockDivider(uint8_t div)
{
    (void)div;
    // no effect on Ameba
}

void SPIClass::setDefaultFrequency(int frequency)
{
    _defaultFrequency = frequency;
}

void SPIClass::end(char SPI_mode)
{
    _SPI_Mode = SPI_mode;

    if (_SPI_Mode == SPI_MODE_MASTER) {
        spi_free(pSpiMaster);
    } else if (_SPI_Mode == SPI_MODE_SLAVE) {
        spi_free(pSpiSlave);
    }
}

SPIClass SPI((&spi_obj0), SPI_MOSI, SPI_MISO, SPI_SCLK, SPI_SS);
SPIClass SPI1((&spi_obj1), SPI1_MOSI, SPI1_MISO, SPI1_SCLK, SPI1_SS);
