#include "CameraIO.h"
#include "WiFi.h"
#include "camera.h"
#include "rtsp.h"

CameraSetting camset;
CameraClass cam;
RTSPClass rtsp;
CameraIOClass camio1_1In1Out(1, 1);  // Single Input Single Output

char ssid[] = "yourNetwork";  //  your network SSID (name)
char pass[] = "password";     // your network password
int status = WL_IDLE_STATUS;  // the Wifi radio's status

void setup() {
    Serial.begin(115200);

    if (WiFi.status() == WL_NO_SHIELD) {
        Serial.println("WiFi shield not present");
        // don't continue:
        while (true)
            ;
    }

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
        Serial.println("camera io link start failed");
    }

    cam.start(camset);
}

void loop() {
    // do nothing
}
