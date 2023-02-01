#include "WiFi.h"
#include "VideoStream.h"
#include "StreamIO.h"
#include "RTSP.h"
#include "MotionDetection.h"
#include "VideoStreamOverlay.h"

#define CHANNEL 0       // High resolution video channel for streaming
#define CHANNELMD 3     // RGB format video for motion detection only avaliable on channel 3
#define MDRES 16        // Motion detection grid resolution

VideoSetting config(VIDEO_FHD, 30, VIDEO_H264, 0);      // High resolution video for streaming
VideoSetting configMD(VIDEO_VGA, 10, VIDEO_RGB, 0);     // Low resolution RGB video for motion detection
RTSP rtsp;
StreamIO videoStreamer(1, 1);
StreamIO videoStreamerMD(1, 1);
MotionDetection MD(MDRES, MDRES);

char ssid[] = "yourNetwork";    // your network SSID (name)
char pass[] = "Password";       // your network password
int status = WL_IDLE_STATUS;

void mdPostProcess(char* md_result) {
    // Motion detection results is expressed as an MDRES x MDRES array
    // With 0 or 1 in each element indicating presence of motion
    // Iterate through all elements to check for motion
    // and calculate largest rectangle containing motion
    int motion = 0, j, k;
    int jmin = MDRES - 1, jmax = 0;
    int kmin = MDRES - 1, kmax = 0;
    for (j = 0; j < MDRES; j++) {
        for (k = 0; k < MDRES; k++) {
            printf("%d ", md_result[j * MDRES + k]);
            if (md_result[j * MDRES + k]) {
                motion = 1;
                if (j < jmin) {
                    jmin = j;
                }
                if (k < kmin) {
                    kmin = k;
                }
                if (j > jmax) {
                    jmax = j;
                }
                if (k > kmax) {
                    kmax = k;
                }
            }
        }
        printf("\r\n");
    }
    printf("\r\n");

    OSD.clearAll(CHANNEL);
    if (motion) {
        // Scale rectangle dimensions according to high resolution video stream and draw with OSD
        int xmin = (int)(kmin * config.width() / MDRES) + 1;
        int ymin = (int)(jmin * config.height() / MDRES) + 1;
        int xmax = (int)((kmax + 1) * config.width() / MDRES) - 1;
        int ymax = (int)((jmax + 1) * config.height() / MDRES) - 1;
        OSD.drawRect(CHANNEL, xmin, ymin, xmax, ymax, 3, OSD_COLOR_GREEN);
    }
    OSD.update(CHANNEL);
}

void setup() {
    Serial.begin(115200);

    // attempt to connect to Wifi network:
    while (status != WL_CONNECTED) {
        Serial.print("Attempting to connect to WPA SSID: ");
        Serial.println(ssid);
        status = WiFi.begin(ssid, pass);

        // wait 2 seconds for connection:
        delay(2000);
    }

    // Configure camera video channels for required resolutions and format outputs
    Camera.configVideoChannel(CHANNEL, config);
    Camera.configVideoChannel(CHANNELMD, configMD);
    Camera.videoInit();

    // Configure RTSP for high resolution video stream information
    rtsp.configVideo(config);
    rtsp.begin();

    // Configure OSD for drawing on high resolution video stream
    OSD.configVideo(CHANNEL, config);
    OSD.begin();

    // Configure motion detection for low resolution RGB video stream
    MD.configVideo(configMD);
    MD.setResultCallback(mdPostProcess);
    MD.begin();

    // Configure StreamIO object to stream data from high res video channel to RTSP
    videoStreamer.registerInput(Camera.getStream(CHANNEL));
    videoStreamer.registerOutput(rtsp);
    if (videoStreamer.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    // Start data stream from high resolution video channel
    Camera.channelBegin(CHANNEL);
    Serial.println("Video RTSP Streaming Start");

    // Configure StreamIO object to stream data from low res video channel to motion detection
    videoStreamerMD.registerInput(Camera.getStream(CHANNELMD));
    videoStreamerMD.setStackSize();
    videoStreamerMD.registerOutput(MD);
    if (videoStreamerMD.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    // Start data stream from low resolution video channel
    Camera.channelBegin(CHANNELMD);

}

void loop() {
    // Do nothing
}
