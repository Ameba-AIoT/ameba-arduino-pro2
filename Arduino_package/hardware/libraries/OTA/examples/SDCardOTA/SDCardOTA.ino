/*  This example demonstrates how to perform an OTA firmware update using a binary file stored on an SD card.
    The device reads the OTA file from the SD card and updates its firmware automatically.

 Example guide:
 https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/OTA/Ameba%20SDCard%20OTA%20Firmware%20Update.html
*/
#include "AmebaFatFS.h"
#include "AmebaFatFSFile.h"

AmebaFatFS fs;
String filename = "ota.bin";

void setup()
{
    Serial.begin(115200);

    fs.begin();

    String fullPath = String(fs.getRootPath()) + filename;

    File file;
    file.sdstartota(fullPath.c_str());
}

void loop()
{
    // Empty or add non-blocking code here
}
