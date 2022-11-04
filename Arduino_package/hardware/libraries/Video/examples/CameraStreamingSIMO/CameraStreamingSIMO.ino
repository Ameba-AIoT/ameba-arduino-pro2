#include "CameraIO.h"
#include "camera.h"
#include "rtsp.h"
#include "WiFi.h"

CameraSetting camset;
CameraClass cam;
CameraIOClass camio1_1In2Out(1, 2); // Single Input Multiple Output
RTSPClass rtsp;
RTSPClass rtsp1;

char ssid[] = "yourNetwork";     //  your network SSID (name)
char pass[] = "password";        // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

void setup() {

    Serial.begin(115200);

    if (WiFi.status() == WL_NO_SHIELD) {
        Serial.println("WiFi shield not present");
        // don't continue:
        while (true);
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

    // init camera
    cam.init(&camset);
    cam.open(&camset);

    // init rtsp
    rtsp.init(&camset);
    rtsp.open();
    rtsp1.init(&camset);
    rtsp1.open();

    // create camera io linker
    camio1_1In2Out.create();
    camio1_1In2Out.registerInput(cam.getIO());
    camio1_1In2Out.registerOutput1(rtsp.getIO());
    camio1_1In2Out.registerOutput2(rtsp1.getIO());

    if(camio1_1In2Out.start() != 0) {
        Serial.println("camera io link start failed");
    }
    cam.start(&camset);
}

void loop() {
}
