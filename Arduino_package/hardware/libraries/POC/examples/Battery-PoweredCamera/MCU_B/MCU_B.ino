#include "PowerMode.h"

#include "StreamIO.h"
#include "VideoStream.h"
#include "RTSP.h"
#include "VideoStreamOverlay.h"
#include "MP4Recording.h"

#define WAKEUP_SOURCE       3
#define RETENTION           0
#define PIN_NUMBER          0
#define CHANNEL             0
#define END_RECORDING_DELAY 50

String detected = "detected";
int noActivityCount = 0;
MP4Recording mp4;
VideoSetting config(VIDEO_FHD, 30, VIDEO_H264, 0);
StreamIO videoStreamer(1, 1);
time_t now;
struct tm ts;

void setup()
{
    Serial.begin(115200);
    Serial2.begin(115200);
    while (!Serial || !Serial2) {
        ;    // wait for serial port to connect. Needed for native USB port only
    }

    PowerMode.begin(STANDBY_MODE, WAKEUP_SOURCE, RETENTION, PIN_NUMBER);

    config.setBitrate(2 * 1024 * 1024);
    Camera.configVideoChannel(CHANNEL, config);
    Camera.videoInit();

    // Configure MP4 with identical video format information
    // Configure MP4 recording settings
    mp4.configVideo(config);
    mp4.setRecordingFileCount(1);
    mp4.setRecordingDuration(3600);
    mp4.setRecordingDataType(STORAGE_VIDEO);    // Set MP4 to record video only

    videoStreamer.registerInput(Camera.getStream(CHANNEL));
    videoStreamer.registerOutput(mp4);
    if (videoStreamer.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    Camera.channelBegin(CHANNEL);
    delay(1000);
}

char input;
// Change your file name here. The final name will look like "MotionDetected *timestamp*"
char mp4_file_name[80];


void loop()
{
    if (Serial2.available() > 0) {
        input = Serial2.read();
        switch (input) {
            case 'D':
                // Serial.println("Motion Detected");
                break;
            case 'N':
                // Serial.println("Nothing Detected");
                break;
            default:
                break;
        }
    }

    if (input == 'D' && noActivityCount < END_RECORDING_DELAY) {
        noActivityCount = 0;
        input = NULL;
        if (mp4.getRecordingState() == 0) {
            // Get current time
            time(&now);
            // Format time, "HOUR MINUTE SECONDS dd-mm-YYYY"
            ts = *localtime(&now);
            strftime(mp4_file_name, sizeof(mp4_file_name), "MotionDetected %H %M %S %d-%m-%Y", &ts);
            mp4.setRecordingFileName(mp4_file_name);
            mp4.begin();
            Serial2.print('R');
        }
    } else {
        noActivityCount++;
        if (noActivityCount == END_RECORDING_DELAY) {
            Serial.println("\r\nEntering Standby Mode\r\n");
            if (mp4.getRecordingState() > 0) {
                mp4.end();
                Serial2.print('S');
                delay(50);
            }
            noActivityCount = 0;
            PowerMode.start();
        }
    }
    delay(100);
}
