/*
 In this example, the device is setup to function as a USB Mass Storage and uses SD card as its physical memory medium.
 USB host end can recognize device and write data to and read data from SD card via USB interface.
 Connect to PC and use the device.

 Example guide:
 https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/USB/USB%20Mass%20Storage.html
*/

#include "USBMassStorage.h"

USBMassStorage USBMS;

#define PRINT_USB_OTG_CONNECTION_STATUS 0

int connection_status = 0;

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

    if (PRINT_USB_OTG_CONNECTION_STATUS) {
        connection_status = USBMS.isConnected();
        Serial.print("USB OTG connection status: ");
        Serial.println(connection_status);
    }
}
