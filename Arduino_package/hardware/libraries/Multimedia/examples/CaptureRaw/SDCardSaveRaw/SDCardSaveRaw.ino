/*  This example uses the camera to capture a raw image in NV16 format,
    and saves the image to SD Card.

 Example guide:
 TBD
*/
#include "VideoStream.h"
#include "StreamIO.h"
#include "Filesaver.h"
#include "AmebaFatFS.h"

#define CHANNEL  0
#define FILENAME "raw_image"

VideoSetting config(20);    // preset 20 for raw stream

uint32_t img_addr = 0;
uint32_t img_len = 0;

AmebaFatFS fs;

Filesaver filesaver;

StreamIO videoRawStreamer(1, 1);    // 1 Input Video -> 1 Output Filesaver

void setup()
{
    Serial.begin(115200);

    fs.begin();

    Camera.configVideoChannel(CHANNEL, config);
    Camera.videoInit();

    filesaver.setFileName(FILENAME);
    filesaver.rawImgSaveSDBegin();

    Camera.channelBegin(CHANNEL);

    videoRawStreamer.registerInput(Camera.getStream(CHANNEL));
    videoRawStreamer.registerOutput(filesaver);

    if (videoRawStreamer.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    delay(1000);
}

void loop()
{
    delay(1000);
}
