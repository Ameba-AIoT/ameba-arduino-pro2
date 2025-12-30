/*
 Example guide:
 https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/Multimedia/Websocket%20Viewer.html
*/

#include "WebSocketViewer.h"
#include "WiFi.h"
#include "StreamIO.h"
#include "VideoStream.h"
#include "RTSP.h"

#define CHANNEL 0

VideoSetting config(CHANNEL);
RTSP rtsp;
WebSocketViewer ws_viewer;
StreamIO videoStreamer(1, 1);

char ssid[] = "Network_SSID";
char pass[] = "Password";
int status = WL_IDLE_STATUS;

void setup()
{
    Serial.begin(115200);

    // Connect WiFi in setup
    while (status != WL_CONNECTED) {
        Serial.print("Attempting to connect to WPA SSID: ");
        Serial.println(ssid);
        status = WiFi.begin(ssid, pass);
        delay(2000);
    }

    ws_viewer.loadWebResources(0);

    config.enableWebsocketViewer();
    // Recommended bitrate - 2 Mbps
    config.setBitrate(2 * 1024 * 1024);
    Camera.configVideoChannel(CHANNEL, config);
    Camera.videoInit();
    ws_viewer.init();

    videoStreamer.registerInput(Camera.getStream(CHANNEL));
    videoStreamer.registerOutput(ws_viewer);
    if (videoStreamer.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    Camera.channelBegin(CHANNEL);
    ws_viewer.begin();
}

void loop()
{
    // nothing
}
