/*
 This sketch shows how to open/close file and perform read/write to it.

 Example guide:
 https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/File%20System/Display%20Free%20and%20Use%20space%20of%20SD%20card.html
*/

#include "AmebaFatFS.h"

AmebaFatFS fs;
void setup()
{
    fs.begin();

    uint64_t used_bytes = fs.get_used_space();
    uint64_t free_bytes = fs.get_free_space();

    printReadableSize(used_bytes, "Used space on SD card");
    printReadableSize(free_bytes, "Free space on SD card");

    fs.end();
}

void loop()
{
    delay(1000);
}

void printReadableSize(uint64_t bytes, const char* label)
{
    double value = (double)bytes;
    const char* unit = "B";

    if (value >= 1024.0) {
        value /= 1024.0;
        unit = "KB";
    }
    if (value >= 1024.0) {
        value /= 1024.0;
        unit = "MB";
    }
    if (value >= 1024.0) {
        value /= 1024.0;
        unit = "GB";
    }

    printf("%s: %llu bytes (%.2f %s)\r\n", label, bytes, value, unit);
}
