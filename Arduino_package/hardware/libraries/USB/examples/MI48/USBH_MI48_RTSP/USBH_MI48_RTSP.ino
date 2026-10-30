#include <WiFi.h>
#include "VideoStream.h"
#include "StreamIO.h"
#include "RTSP.h"
#include "MI48ThermalCamera.h"

#define MI48_VIDEO_TYPE       VIDEO_JPEG
#define MI48_VIDEO_WIDTH      64
#define MI48_VIDEO_HEIGHT     64
#define MI48_VIDEO_FPS        5
#define MI48_VIDEO_CHANNEL    1
#define MI48_VIDEO_BPS        (512 * 1024)
#define MI48_VIDEO_RESOLUTION VIDEO_VGA
#define MI48_VIDEO_EXT_FMT    1    // 1 = NV12
#define MI48_VIDEO_RAINBOW    1    // 1 = rainbow-colour, 0 = grayscale

char ssid[] = "Network_SSID";
char pass[] = "Password";

MI48ThermalCamera thermal;
RTSP rtsp;
StreamIO videoStreamer(1, 1);
VideoSetting config(VIDEO_VGA, MI48_VIDEO_FPS, VIDEO_JPEG, 0);
static bool streaming = false;

void setup()
{
    Serial.begin(115200);
    delay(1000);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print("Connecting to ");
        Serial.println(ssid);
        WiFi.begin(ssid, pass);
        delay(2000);
    }

    if (!thermal.begin(MI48_VIDEO_WIDTH, MI48_VIDEO_HEIGHT, MI48_VIDEO_FPS, MI48_VIDEO_CHANNEL, MI48_VIDEO_BPS,
                       MI48_VIDEO_TYPE, MI48_VIDEO_RESOLUTION, MI48_VIDEO_EXT_FMT, MI48_VIDEO_RAINBOW)) {
        Serial.println("USB/external JPEG initialization failed. Reset to retry.");
        return;
    }

    config.setWidth(MI48_VIDEO_WIDTH);
    config.setHeight(MI48_VIDEO_HEIGHT);
    rtsp.configVideo(config);
    rtsp.begin();

    videoStreamer.registerInput(thermal);
    videoStreamer.registerOutput(rtsp);
    if (videoStreamer.begin() != 0) {
        Serial.println("StreamIO start failed. Reset to retry.");
        return;
    }
    
    if (!thermal.start()) {
        Serial.println("Thermal capture task failed. Reset to retry.");
        return;
    }
    streaming = true;
    printInfo();
}

void loop()
{
    thermal.poll();       // drain USB + feed parser
    thermal.process();    // decode + NV12 + JPEG one frame
    if (streaming) {
        static uint32_t lastPrint = 0;
        if (millis() - lastPrint >= 2000) {
            lastPrint = millis();
            Serial.print("JPEG frames queued: ");
            Serial.println(thermal.frameCount());
        }
    }
    delay(1);
}

void printInfo()
{
    IPAddress ip = WiFi.localIP();
    Serial.print("Open in VLC: rtsp://");
    Serial.print(ip);
    Serial.print(":");
    Serial.println(rtsp.getPort());
    Serial.print("Thermal MJPEG: ");
    Serial.print(MI48_VIDEO_WIDTH);
    Serial.print("x");
    Serial.print(MI48_VIDEO_HEIGHT);
    Serial.print(" at up to ");
    Serial.print(MI48_VIDEO_FPS);
    Serial.println(" fps");
}
