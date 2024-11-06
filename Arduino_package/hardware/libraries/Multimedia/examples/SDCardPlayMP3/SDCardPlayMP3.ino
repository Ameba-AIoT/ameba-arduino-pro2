/*  This example decodes an MP3 file from an SD card
    and plays audio through a TRRS 3.5mm audio jack module.

 Example guide: https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/amebapro2/Example_Guides/Multimedia/Play%20MP3%20with%20SD%20card.html

*/
#include "AmebaFatFS.h"

#define FILENAME "Audio_test"
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
