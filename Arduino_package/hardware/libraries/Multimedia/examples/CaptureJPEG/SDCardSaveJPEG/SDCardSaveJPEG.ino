/*  This example uses the camera to capture a JPEG image,
    and saves the image to SD Card.

 Example guide:
 https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/Multimedia/CaptureJPEG/Capture%20JPEG%20save%20to%20SD%20Card.html
*/
#include "VideoStream.h"
#include "AmebaFatFS.h"

#define CHANNEL  0
#define FILENAME "image.jpg"

VideoSetting config(VIDEO_FHD, CAM_FPS, VIDEO_JPEG, 1);

uint32_t img_addr = 0;
uint32_t img_len = 0;

AmebaFatFS fs;

void setup()
{
    Serial.begin(115200);

    Camera.configVideoChannel(CHANNEL, config);
    Camera.videoInit();
    Camera.channelBegin(CHANNEL);

    fs.begin();
    File file = fs.open(String(fs.getRootPath()) + String(FILENAME));

    delay(1000);
    Camera.getImage(CHANNEL, &img_addr, &img_len);
    file.write((uint8_t *)img_addr, img_len);
    file.close();
    fs.end();
}

void loop()
{
    delay(1000);
}
