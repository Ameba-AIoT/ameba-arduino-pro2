#include "StreamIO.h"
#include "VideoStream.h"
#include "MotionDetection.h"
#include "VideoStreamOverlay.h"

#define CHANNELMD 3
// Lower resolution for MD processing
#define MDWIDTH  576
#define MDHEIGHT 320

VideoSetting config(VIDEO_FHD, 30, VIDEO_H264, 0);
VideoSetting configMD(MDWIDTH, MDHEIGHT, 10, VIDEO_RGB, 0);
StreamIO videoStreamerMD(1, 1);
MotionDetection MD;

void setup()
{

    Serial.begin(115200);
    Serial2.begin(115200);
    while (!Serial || !Serial2) {
        ;    // wait for serial port to connect. Needed for native USB port only
    }

    // Recommended bitrate - 2 Mbps
    config.setBitrate(2 * 1024 * 1024);
    Camera.configVideoChannel(0, config);
    Camera.configVideoChannel(CHANNELMD, configMD);
    Camera.videoInit();

    // Configure motion detection for low resolution RGB video stream
    MD.configVideo(configMD);
    MD.begin();

    videoStreamerMD.registerInput(Camera.getStream(CHANNELMD));
    videoStreamerMD.setStackSize();
    videoStreamerMD.setTaskPriority();
    videoStreamerMD.registerOutput(MD);
    if (videoStreamerMD.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    Camera.channelBegin(CHANNELMD);

    pinMode(0, OUTPUT);

    delay(1000);
}

char input;
int is_sleeping = 1;

void loop()
{
    if (Serial2.available() > 0) {
        input = Serial2.read();
        switch (input) {
            case 'R':
                if (is_sleeping) {
                    Serial.println("MCU_B is Recording");
                }
                is_sleeping = 0;
                break;
            case 'S':
                Serial.println("MCU_B has stopped Recording");
                Serial.println("MCU_B has entered Standby Mode");
                is_sleeping = 1;
                break;
            default:
                break;
        }
    }
    std::vector<MotionDetectionResult> md_results = MD.getResult();
    if (MD.getResultCount() > 0) {
        // Serial.println("Motion Detected");
        Serial2.print('D');
        digitalWrite(0, HIGH);
        delay(1000);
    } else {
        Serial2.print('N');
    }

    digitalWrite(0, LOW);
    delay(100);
}
