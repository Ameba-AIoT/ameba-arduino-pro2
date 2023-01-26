// Point the camera at a target face and enter the following commands into the serial monitor,
// Register face:           "REG={Name}"            Ensure that there is only one face detected in frame
// Exit registration mode:  "EXIT"                  Stop trying to register a face before it is successfully registered
// Reset registered faces:  "RESET"                 Forget all previously registered faces
// Backup registered faces to flash:    "BACKUP"    Save registered faces to flash
// Restore registered faces from flash: "RESTORE"   Load registered faces from flash

#include "WiFi.h"
#include "StreamIO.h"
#include "VideoStream.h"
#include "RTSP.h"
#include "NNFaceDetection.h"
#include "NNFaceRecognition.h"
#include "VideoStreamOverlay.h"

#define CHANNEL   0
#define CHANNELNN 3

// Customised resolution for NN
#define NNWIDTH 576
#define NNHEIGHT 320

VideoSetting config(VIDEO_FHD, 30, VIDEO_H264, 0);
VideoSetting configNN(NNWIDTH, NNHEIGHT, 10, VIDEO_RGB, 0);
NNFaceDetection facedet;
NNFaceRecognition facerecog;
RTSP rtsp;
StreamIO videoStreamer(1, 1);
StreamIO videoStreamerFDFR(1, 1);
StreamIO videoStreamerRGBFD(1, 1);

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

    // Configure camera video channels with video format information
    Camera.configVideoChannel(CHANNEL, config);
    Camera.configVideoChannel(CHANNELNN, configNN);
    Camera.videoInit();

    // Configure RTSP with corresponding video format information
    rtsp.configVideo(config);
    rtsp.begin();

    // Configure face detection with corresponding video format information
    facedet.configVideo(configNN);
    facedet.configFaceRecogCascadedMode(TRUE);
    facedet.begin();

    // Configure Face Recognition model
    facerecog.begin();
    facerecog.setResultCallback(FRPostProcess);

    // Configure StreamIO object to stream data from video channel to RTSP
    videoStreamer.registerInput(Camera.getStream(CHANNEL));
    videoStreamer.registerOutput(rtsp);
    if (videoStreamer.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }
    // Start data stream from video channel
    Camera.channelBegin(CHANNEL);

    // SISO: Face Detection -> Face Recognition
    videoStreamerFDFR.registerInput(facedet);
    videoStreamerFDFR.registerOutput(facerecog);
    if (videoStreamerFDFR.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    // Configure StreamIO object to stream data from RGB video channel to face detection
    videoStreamerRGBFD.registerInput(Camera.getStream(CHANNELNN));
    videoStreamerRGBFD.setStackSize();
    videoStreamerRGBFD.setTaskPriority();
    videoStreamerRGBFD.registerOutput(facedet);
    if (videoStreamerRGBFD.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }
    // Start video channel for NN
    Camera.channelBegin(CHANNELNN);

    // Start OSD drawing on RTSP video channel
    OSD.configVideo(CHANNEL, config);
    OSD.begin();
}

void loop() {
    if (Serial.available() > 0) {
        String input = Serial.readString();
        input.trim();

        if (input.startsWith(String("REG="))){
            String name = input.substring(4);
            facerecog.registerFace(name);
        } else if (input.startsWith(String("EXIT"))) {
            facerecog.exitRegisterMode();
        } else if (input.startsWith(String("RESET"))) {
            facerecog.resetRegisteredFace();
        } else if (input.startsWith(String("BACKUP"))) {
            facerecog.backupRegisteredFace();
        } else if (input.startsWith(String("RESTORE"))) {
            facerecog.restoreRegisteredFace();
        }
    }
}

// User callback function for post processing of face recognition results
void FRPostProcess(std::vector<FaceRecognitionResult> results) {
    uint16_t im_h = config.height();
    uint16_t im_w = config.width();

    printf("Total number of faces detected = %d\r\n", results.size());
    OSD.clearAll(CHANNEL);

    if (results.size() > 0) {
        for (uint32_t i = 0; i < results.size(); i++) {
            FaceRecognitionResult item = results[i];
            // Result coordinates are floats ranging from 0.00 to 1.00
            // Multiply with RTSP resolution to get coordinates in pixels
            int xmin = (int)(item.xMin() * im_w);
            int xmax = (int)(item.xMax() * im_w);
            int ymin = (int)(item.yMin() * im_h);
            int ymax = (int)(item.yMax() * im_h);

            uint32_t osd_color;
            if (String(item.name()) == String("unknown")) {
                osd_color = OSD_COLOR_RED;
            } else {
                osd_color = OSD_COLOR_GREEN;
            }
            // Draw boundary box
            printf("Face %d name %s:\t%d %d %d %d\n\r", i, item.name(), xmin, xmax, ymin, ymax);
            OSD.drawRect(CHANNEL, xmin, ymin, xmax, ymax, 3, osd_color);

            // Print identification text above boundary box
            char text_str[40];
            snprintf(text_str, sizeof(text_str), "Face:%s", item.name());
            OSD.drawText(CHANNEL, xmin, ymin - OSD.getTextHeight(CHANNEL), text_str, osd_color);

        }
    }
    OSD.update(CHANNEL);
}

