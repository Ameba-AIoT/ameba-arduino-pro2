/*
 * In this example, the device is setup to function as a USB Mass Storage and uses SD card as its physical memory medium.
 * USB host end can recognize device and write data to and read data from SD card via USB interface.
 * Connect to PC and use the device.

 * Example guide: TBD
 */

#include "USBMassStorage.h"

USBMassStorage USBMS;

void setup()
{
    Serial.begin(115200);
    USBMS.USBInit();
    USBMS.SDIOInit();
    USBMS.USBStatus();
    USBMS.initializeDisk();
    USBMS.loadUSBMassStorageDriver();
}

void loop()
{
    delay(1000);
}
