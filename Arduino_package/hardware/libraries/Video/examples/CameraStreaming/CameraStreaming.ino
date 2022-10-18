#include "CameraIO.h"
#include "camera.h"
#include "rtsp.h"
#include "WiFi.h"

void *datalinker = NULL;
void *pVideo     = NULL;
void *pRTSP      = NULL;

CameraIOClass camio(1, 1);
CameraClass cam;
RTSPClass rtsp;

char ssid[] = "yourNetwork";     // your network SSID (name)
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
    pVideo = cam.init();
    cam.open(pVideo);

    // init rtsp
    pRTSP = rtsp.init();
    rtsp.open(pRTSP);

    // create camera io linker
    datalinker = camio.create();

    // add input
    camio.registerInput(datalinker, pVideo);
    
    // add output
    camio.registerOutput(datalinker, pRTSP);
    
    if(camio.start(datalinker) != 0) {
        Serial.println("camera io link start failed");
    }    
    cam.start(pVideo);
}


void loop() {
// do nothing
}

