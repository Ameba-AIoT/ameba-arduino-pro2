/*
 This sketch shows how to open/close file and perform read/write to it.

 Example guide:
 https://www.amebaiot.com/en/
 */

#include "AmebaFatFS.h"

uint64_t device_used_bytes;
uint64_t device_free_bytes;

uint16_t device_used_Mbytes;
uint16_t device_free_Mbytes;

AmebaFatFS fs;
void setup()
{
    fs.begin();
    device_used_bytes = fs.get_used_space();
    device_used_Mbytes = (uint16_t)(device_used_bytes / 1048576);    // convert bytes to Mbytes /(1024*1024)

    device_free_bytes = fs.get_free_space();
    device_free_Mbytes = (uint16_t)(device_free_bytes / 1048576);    // convert bytes to Mbytes /(1024*1024)

    printf("Use space on SD card: %llu bytes\r\n", device_used_bytes);
    printf("Use space on SD card: %u Mbytes\r\n", device_used_Mbytes);

    printf("Free space on SD card: %llu bytes\r\n", device_free_bytes);
    printf("Free space on SD card: %u Mbytes\r\n", device_free_Mbytes);
    fs.end();
}

void loop()
{
    delay(1000);
}
