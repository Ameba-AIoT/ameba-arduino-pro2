/*  This example uses the camera to capture JPEG images at regular intervals,
    and saves the images to SD Card.

 Example guide:
 https://www.amebaiot.com/en/amebapro2-arduino-video-jpeg-sdcard/
*/
#include "VideoStream.h"
#include "AmebaFatFS.h"

#define CHANNEL  0
#define FILENAME "image"
#define INTERVAL 1000

// Use a pre-defined resolution, or choose to configure your own resolution
VideoSetting config(VIDEO_FHD, CAM_FPS, VIDEO_JPEG, 1);

uint32_t img_addr = 0;
uint32_t img_len = 0;
uint32_t count = 0;

AmebaFatFS fs;

void setup()
{
    Serial.begin(115200);

    Camera.configVideoChannel(CHANNEL, config);
    Camera.videoInit();
    Camera.channelBegin(CHANNEL);

    fs.begin();
}

void loop()
{
    delay(INTERVAL);

    File file = fs.open(String(fs.getRootPath()) + String(FILENAME) + String(count) + String(".jpg"));
    Camera.getImage(CHANNEL, &img_addr, &img_len);
    file.write((uint8_t *)img_addr, img_len);
    printf("Saved %s\r\n", file.name());
    file.close();
    count++;
}
