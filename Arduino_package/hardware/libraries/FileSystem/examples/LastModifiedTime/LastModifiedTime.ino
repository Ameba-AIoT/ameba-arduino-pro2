/*
 This sketch shows how to get and set last modified time of a file.

 Example guide:
 https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/File%20System/Simple%20applications%20with%20SD%20card.html
 */

#include "AmebaFatFS.h"

AmebaFatFS fs;

char filename[] = "test.txt";

void setup()
{
    char path[128];

    uint16_t year = 2021;
    uint16_t month = 4;
    uint16_t date = 4;
    uint16_t hour = 12;
    uint16_t minute = 12;
    uint16_t second = 12;

    fs.begin();

    sprintf(path, "%s%s", fs.getRootPath(), filename);
    File file = fs.open(path);
    file.close();

    fs.setLastModTime(path, year, month, date, hour, minute, second);

    fs.getLastModTime(path, &year, &month, &date, &hour, &minute, &second);
    printf("filename:\"%s\"\r\n", path);
    printf("time mod:%04d/%02d/%02d %02d:%02d:%02d\r\n", year, month, date, hour, minute, second);

    fs.end();
}

void loop()
{
    delay(1000);
}
