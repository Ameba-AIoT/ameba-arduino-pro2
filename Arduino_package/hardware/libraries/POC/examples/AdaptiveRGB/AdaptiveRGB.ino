/*
Example Guide: https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/POC/AdaptiveRGB.html
*/

#include "WiFi.h"
#include "VideoStream.h"
#include "StreamIO.h"
#include "RTSP.h"
#include "RGBLed.h"

#define CHANNEL     0    // H.264 stream channel
#define RGB_CHANNEL 3    // The only channel that can output RGB888

#define RGB_WIDTH  176
#define RGB_HEIGHT 144

#define NUM_LEDS 16

// Set to 0 to drive the strip without starting an RTSP stream.
#define ENABLE_RTSP 1

char ssid[] = "Network_SSID";    // your network SSID (name)
char pass[] = "Password";        // your network password
int status = WL_IDLE_STATUS;

VideoSetting config(CHANNEL);
VideoSetting configRGB(RGB_WIDTH, RGB_HEIGHT, 10, VIDEO_RGB, 0);
RGBLed led(NUM_LEDS);
RTSP rtsp;
StreamIO videoStreamer(1, 1);    // 1 Input Video -> 1 Output RTSP
StreamIO rgbStreamer(1, 1);

static const char *const QUAD_NAME[4] = {"TL", "TR", "BL", "BR"};

void setup()
{
    Serial.begin(115200);

#if ENABLE_RTSP
    // attempt to connect to Wifi network:
    while (status != WL_CONNECTED) {
        Serial.print("Attempting to connect to WPA SSID: ");
        Serial.println(ssid);
        status = WiFi.begin(ssid, pass);
        delay(2000);
    }
#endif

    // Configure the camera. The RGB tap is opened on channel 3 regardless of
    // whether an H.264 channel is used, but arming channel 0 as well gives the
    // ISP its usual full-resolution path.
    config.setBitrate(2 * 1024 * 1024);
    forceRGBSize();
    Camera.configVideoChannel(CHANNEL, config);
    Camera.configVideoChannel(RGB_CHANNEL, configRGB);
    Camera.videoInit();

#if ENABLE_RTSP
    // Configure RTSP with the H.264 channel's format information
    rtsp.configVideo(config);
    rtsp.begin();

    videoStreamer.registerInput(Camera.getStream(CHANNEL));
    videoStreamer.registerOutput(rtsp);
    if (videoStreamer.begin() != 0) {
        Serial.println("Video RTSP stream link start failed");
    }
#endif

    // Open the strip and bind it to the module. The module reads w*h*3 planar
    // RGB and splits it into quadrants, so pass the same size the video channel
    // was configured with.
    if (!led.begin(RGB_WIDTH, RGB_HEIGHT)) {
        Serial.println("RGBLed init failed");
        return;
    }

    rgbStreamer.registerInput(Camera.getStream(RGB_CHANNEL));
    rgbStreamer.registerOutput(led);
    if (rgbStreamer.begin() != 0) {
        Serial.println("RGB stream link start failed");
        return;
    }

    // Start the data streams only after both links are up.
#if ENABLE_RTSP
    Camera.channelBegin(CHANNEL);
#endif
    Camera.channelBegin(RGB_CHANNEL);

    delay(1000);
    printInfo();
    Serial.println("Adaptive RGB running");
}

void loop()
{
    Serial.print("Frames: ");
    Serial.print(led.frameCount());
    for (uint8_t q = 0; q < 4; q++) {
        uint32_t c = led.quadrantColor(q);
        Serial.print("  ");
        Serial.print(QUAD_NAME[q]);
        Serial.print(": R");
        Serial.print((c >> 16) & 0xFF);
        Serial.print(" G");
        Serial.print((c >> 8) & 0xFF);
        Serial.print(" B");
        Serial.print(c & 0xFF);
    }
    Serial.println();

    delay(1000);
}

void printInfo(void)
{
    Serial.println(" ");
    Serial.println("------------------------------");
    Serial.println("- Summary of Streaming -");
    Serial.println("------------------------------");
    Camera.printInfo();

#if ENABLE_RTSP
    IPAddress ip = WiFi.localIP();

    Serial.println("- RTSP -");
    rtsp.printInfo(ip.get_address());
#endif
}

/* VideoSetting(w, h, ...) does not reliably keep a small custom size: the
 * bounds check in this board package can replace it with the full sensor
 * resolution (1920x1080 on the default sensor). Set the size again through the
 * plain setters, which store it unconditionally, so the RGB channel really
 * runs at RGB_WIDTH x RGB_HEIGHT. The module must be told the same size,
 * because it indexes into a width * height * 3 planar frame.
 */
void forceRGBSize(void)
{
    configRGB.setWidth(RGB_WIDTH);
    configRGB.setHeight(RGB_HEIGHT);
}
