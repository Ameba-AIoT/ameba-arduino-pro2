#include "StreamIO.h"
#include "WiFi.h"
#include "video.h"
#include "rtsp.h"

CameraSetting camset;
VideoClass cam;
RTSPClass rtsp;
StreamIOClass camio1_1In1Out(1, 1);  // Single Input Single Output

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

    rtsp.init(camset);
    rtsp.open();

    camio1_1In1Out.create();
    camio1_1In1Out.registerInput(cam.getIO());
    camio1_1In1Out.registerOutput(rtsp.getIO());
    if (camio1_1In1Out.start() != 0) {
        Serial.println("stream io link start failed");
    }

    cam.start(camset);
}

void loop() {
    // Do nothing
}
