#include "StreamIO.h"
#include "WiFi.h"
#include "audio.h"
#include "video.h"
#include "rtsp.h"

CameraSetting camset;
VideoClass cam;
AudioRawClass audio;
AACClass aac;
RTSPClass rtsp;
StreamIOClass camio1_1In1Out(1, 1); // SISO for Audio -> AAC
StreamIOClass camio2_2In1Out(2, 1); // MISO for Video + Audio -> RTSP

char ssid[] = "yourNetwork";  //  your network SSID (name)
char pass[] = "password";     // your network password
int status = WL_IDLE_STATUS;  // the Wifi radio's status

void setup() {
    Serial.begin(115200);

    // check for WiFi status:
    status = WiFi.status();

    // attempt to connect to Wifi network:
    while (status != WL_CONNECTED) {
        Serial.print("Attempting to connect to WPA SSID: ");
        Serial.println(ssid);
        // Connect to WPA/WPA2 network:
        status = WiFi.begin(ssid, pass);

        // wait 2 seconds for connection:
        delay(2000);
    }

    cam.init(camset);
    cam.open(camset);

    audio.init();
    audio.open();
    aac.init();

    rtsp.enableAudio();
    rtsp.init(camset);
    rtsp.open();

    camio1_1In1Out.create();
    camio1_1In1Out.registerInput(audio.getIO());
    camio1_1In1Out.registerOutput(aac.getIO());
    if (camio1_1In1Out.start() != 0) {
        Serial.println("stream io link 1 start failed");
    }

    camio2_2In1Out.create();
    camio2_2In1Out.registerInput1(cam.getIO());
    camio2_2In1Out.registerInput2(aac.getIO());
    camio2_2In1Out.registerOutput(rtsp.getIO());
    if (camio2_2In1Out.start() != 0) {
        Serial.println("stream io link 2 start failed");
    }

    cam.start(camset);
}

void loop() {
    // Do nothing
}
