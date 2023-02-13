#include "WiFi.h"
#include "VideoStream.h"
#include "StreamIO.h"
#include "RTSP.h"
#include "MotionDetection.h"
#include "VideoStreamOverlay.h"

#define CHANNEL 0       // High resolution video channel for streaming
#define CHANNELMD 3     // RGB format video for motion detection only avaliable on channel 3
#define MDRESX 32       // Motion detection grid resolution
#define MDRESY 18

VideoSetting config(VIDEO_FHD, 30, VIDEO_H264, 0);      // High resolution video for streaming
VideoSetting configMD(VIDEO_VGA, 10, VIDEO_RGB, 0);     // Low resolution RGB video for motion detection
RTSP rtsp;
StreamIO videoStreamer(1, 1);
StreamIO videoStreamerMD(1, 1);
MotionDetection MD(MDRESY, MDRESX);
MotionDetectionPostProcess MDproc;

char ssid[] = "yourNetwork";    // your network SSID (name)
char pass[] = "Password";       // your network password
int status = WL_IDLE_STATUS;

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

    // Configure motion detection for low resolution RGB video stream
    MD.configVideo(configMD);
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

    // Configure OSD for drawing on high resolution video stream
    OSD.configVideo(CHANNEL, config);
    OSD.begin();
}

void loop() {
    char* result = MD.getResult();
    uint16_t count = MDproc.labelAdjacentRegions(result, MDRESY, MDRESX);

    // Print out motion detection result grid
    for (uint8_t r = 0; r < MDRESY; r++) {
        for (uint8_t c = 0; c < MDRESX; c++) {
            if (result[r * MDRESX + c] != 0) {
                printf(" %x", result[r * MDRESX + c]);
            } else {
                printf(" .");
            }
            printf(" ");
        }
        printf("\r\n");
    }
    printf("================================================================================================\r\n");

    OSD.clearAll(CHANNEL);
    if (count > 0) {
        // Draw largest box containing all regions with detected motion
        int xmin = (int)(MDproc.getRegion(0).xMin() * config.width());
        int ymin = (int)(MDproc.getRegion(0).yMin() * config.height());
        int xmax = (int)(MDproc.getRegion(0).xMax() * config.width());
        int ymax = (int)(MDproc.getRegion(0).yMax() * config.height());
        OSD.drawRect(CHANNEL, xmin, ymin, xmax, ymax, 3, OSD_COLOR_RED);

        for (uint16_t i = 1; i < count; i++) {
            if (MDproc.getRegion(i).size() > 1) {
                // Draw a box for each region with detected motion larger than 1 block in size
                int xmin = (int)(MDproc.getRegion(i).xMin() * config.width());
                int ymin = (int)(MDproc.getRegion(i).yMin() * config.height());
                int xmax = (int)(MDproc.getRegion(i).xMax() * config.width());
                int ymax = (int)(MDproc.getRegion(i).yMax() * config.height());
                OSD.drawRect(CHANNEL, xmin, ymin, xmax, ymax, 3, OSD_COLOR_GREEN);
            }
        }
    }
    OSD.update(CHANNEL);
    delay(100);
}
