// Point the camera at a target face and enter the following commands into the serial monitor,
// Register face:           "REG={Name}"            Ensure that there is only one face detected in frame
// Exit registration mode:  "EXIT"                  Stop trying to register a face before it is successfully registered
// Reset registered faces:  "RESET"                 Forget all previously registered faces
// Backup registered faces to flash:    "BACKUP"    Save registered faces to flash
// Restore registered faces from flash: "RESTORE"   Load registered faces from flash
// This example takes snapshot of unrecognised personnel after the Face Registration mode is turned off when an external button is pushed.

#include "WiFi.h"
#include "StreamIO.h"
#include "VideoStream.h"
#include "RTSP.h"
#include "NNFaceDetection.h"
#include "NNFaceRecognition.h"
#include "VideoStreamOverlay.h"
#include "AmebaFatFS.h"

// CHANNELVID: RTSP; CHANNELJPEG: MP4; CHANNELNN: Face Detection + Face Recognition
#define CHANNELVID 0
#define CHANNELJPEG 1
#define CHANNELNN 3
// Define ON and OFF to replace HIGH and LOW
#define ON 1
#define OFF 0
// Customised resolution for NN
#define NNWIDTH 576
#define NNHEIGHT 320
// Pin Definition
#define RED_LED 3
#define GREEN_LED 4
#define BUTTON_PIN 5
// Limit for Unknown Snapshot
#define MAX_UNKNOWN_COUNT 5

// Video Config
VideoSetting configVID(VIDEO_FHD, 30, VIDEO_H264, 0);
VideoSetting configJPEG(VIDEO_FHD, CAM_FPS, VIDEO_JPEG, 1);
VideoSetting configNN(NNWIDTH, NNHEIGHT, 10, VIDEO_RGB, 0);
NNFaceDetection facedet;
NNFaceRecognition facerecog;
RTSP rtsp;
StreamIO videoStreamer(1, 1);
StreamIO videoStreamerFDFR(1, 1);
StreamIO videoStreamerRGBFD(1, 1);

// Variables
char ssid[] = "RealKungFu";  // your network SSID (name)
char pass[] = "RealTech";    // your network password
int status = WL_IDLE_STATUS;
bool buttonState = false;
uint32_t img_addr = 0;
uint32_t img_len = 0;
bool regFace = true;
bool unknownDetected = false;
bool roundBegan = false;
int unknownCount = 0;

// File Initialisation
AmebaFatFS fs;

void setup() {
  // GPIO Initialisation
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
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
  Camera.configVideoChannel(CHANNELVID, configVID);
  Camera.configVideoChannel(CHANNELJPEG, configJPEG);
  Camera.configVideoChannel(CHANNELNN, configNN);
  Camera.videoInit();

  // Configure RTSP with corresponding video format information
  rtsp.configVideo(configVID);
  rtsp.begin();

  // Configure face detection with corresponding video format information
  facedet.configVideo(configNN);
  facedet.configFaceRecogCascadedMode(TRUE);
  facedet.begin();

  // Configure Face Recognition model
  facerecog.begin();
  facerecog.setResultCallback(FRPostProcess);

  // Configure StreamIO object to stream data from video channel to RTSP
  videoStreamer.registerInput(Camera.getStream(CHANNELVID));
  videoStreamer.registerOutput(rtsp);
  if (videoStreamer.begin() != 0) {
    Serial.println("StreamIO link start failed");
  }
  // Start data stream from video channel
  Camera.channelBegin(CHANNELVID);
  Camera.channelBegin(CHANNELJPEG);

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
  OSD.configVideo(CHANNELVID, configVID);
  OSD.begin();
}

void loop() {
  if (regFace == true) {                  // Face Recognition mode when image first uploaded
    digitalWrite(RED_LED, ON);            // Blink the LED for 3 Seconds
    digitalWrite(GREEN_LED, ON);
    delay(500);
    digitalWrite(RED_LED, OFF);
    digitalWrite(GREEN_LED, OFF);
    delay(500);
    if (Serial.available() > 0) {         // Serial Monitor Commands for Face Recognition
      String input = Serial.readString();
      input.trim();

      if (input.startsWith(String("REG="))) {
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
    buttonState = digitalRead(BUTTON_PIN);  
    if (buttonState == ON) regFace = false; // When button is being pressed, regFace becomes false
  } else {
    // Do something
  }
}

// User callback function for post processing of face recognition results
void FRPostProcess(std::vector<FaceRecognitionResult> results) {
  uint16_t im_h = configVID.height();
  uint16_t im_w = configVID.width();

  printf("Total number of faces detected = %d\r\n", results.size());
  OSD.clearAll(CHANNELVID);

  resultSize = results.size();

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
        if (regFace == false) {                                                 // Enter if statement after Face Recognition mode ended
          unknownDetected = true;
          unknownCount++;
          if (unknownCount < (MAX_UNKNOWN_COUNT + 1)) {                         // Ensure unregconised snapshot taken under MAX_UNKNOWN_COUNT
            facerecog.registerFace("Stranger" + String(unknownCount));          // Register first MAX_UNKNOWN_COUNT of unrecognised face under named Stranger <No.> to prevent recapture of same unrecognised person twice
            fs.begin();
            File file = fs.open(String(fs.getRootPath()) + "Stranger" + String(unknownCount) + ".jpg"); // Capture snapshot of Stranger under name Stranger <No.>
            delay(1000);
            Camera.getImage(CHANNELJPEG, &img_addr, &img_len);
            file.write((uint8_t*)img_addr, img_len);
            file.close();
            fs.end();
          }
        }
      } else {
        osd_color = OSD_COLOR_GREEN;
      }
      // Draw boundary box
      printf("Face %d name %s:\t%d %d %d %d\n\r", i, item.name(), xmin, xmax, ymin, ymax);
      OSD.drawRect(CHANNELVID, xmin, ymin, xmax, ymax, 3, osd_color);

      // Print identification text above boundary box
      char text_str[40];
      snprintf(text_str, sizeof(text_str), "Face:%s", item.name());
      OSD.drawText(CHANNELVID, xmin, ymin - OSD.getTextHeight(CHANNELVID), text_str, osd_color);
    }
    if ((regFace == false) && (unknownDetected == true)) {                      // RED LED remain lit up when unknown detected
      digitalWrite(RED_LED, ON);
      digitalWrite(GREEN_LED, OFF);
    } else if ((regFace == false) && (unknownDetected == false)) {              // GREEN LED lit up when no unknown faces detected, Strangers are no longer considered unknown faces.
      digitalWrite(RED_LED, OFF);
      digitalWrite(GREEN_LED, ON);
    }
    unknownDetected = false;
  }
  OSD.update(CHANNELVID);
}
