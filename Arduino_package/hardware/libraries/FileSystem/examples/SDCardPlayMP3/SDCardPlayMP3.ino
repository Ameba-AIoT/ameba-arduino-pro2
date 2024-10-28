/*  This example decodes an MP3 file from an SD card
    and plays audio through a TRRS 3.5mm audio jack module.

 Example guide: TBD

*/
#include "AmebaFatFS.h"

#define FILENAME "audio"
#define INTERVAL 1000

AmebaFatFS fs;

void setup()
{
    Serial.begin(115200);

    fs.begin();

    File file = fs.open(String(fs.getRootPath()) + String(FILENAME) + String(".mp3"));

    file.close();
}

void loop()
{
    delay(INTERVAL);
}
