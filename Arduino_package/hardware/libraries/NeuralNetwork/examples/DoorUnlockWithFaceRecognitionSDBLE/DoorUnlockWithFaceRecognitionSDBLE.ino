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
#include "NNFaceDetectionRecognition.h"
#include "VideoStreamOverlay.h"
#include <AmebaServo.h>
#include "AmebaFatFS.h"
#include "BLEDevice.h"

#define CHANNELVID  0 // Channel for RTSP streaming
#define CHANNELJPEG 1 // Channel for taking snapshots
#define CHANNELNN   3 // RGB format video for NN only avaliable on channel 3

// Customised resolution for NN
#define NNWIDTH  576
#define NNHEIGHT 320

// Define BLE UUID
#define UART_SERVICE_UUID "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

// BLE Buffer Size
#define STRING_BUF_SIZE 100

// Pin Definition
#define RED_LED    3
#define GREEN_LED  4
#define BUTTON_PIN 5
#define SERVO_PIN  8

VideoSetting configVID(VIDEO_FHD, 30, VIDEO_H264, 0);
VideoSetting configJPEG(VIDEO_FHD, CAM_FPS, VIDEO_JPEG, 1);
VideoSetting configNN(NNWIDTH, NNHEIGHT, 10, VIDEO_RGB, 0);
NNFaceDetectionRecognition facerecog;
RTSP rtsp;
StreamIO videoStreamer(1, 1);
StreamIO videoStreamerFDFR(1, 1);
StreamIO videoStreamerRGBFD(1, 1);
AmebaServo myservo;
BLEService UartService(UART_SERVICE_UUID);
BLECharacteristic Rx(CHARACTERISTIC_UUID_RX);
BLECharacteristic Tx(CHARACTERISTIC_UUID_TX);
BLEAdvertData advdata;
BLEAdvertData scndata;
bool notify = false;

char ssid[] = "yourNetwork";  // your network SSID (name)
char pass[] = "Password";     // your network password
int status = WL_IDLE_STATUS;

int resultSize = 0;
bool doorOpen = false;
bool doorLatch = false;
bool buttonState = false;
bool systemOn = false;
uint32_t img_addr = 0;
uint32_t img_len = 0;
String fileName;
long counter = 0;

// File Initialization
AmebaFatFS fs;

void setup() {
  // GPIO Initialisation
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  myservo.attach(SERVO_PIN);
  
  Serial.begin(115200);

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);

    // wait 2 seconds for connection:
    delay(2000);
  }

  // BLE Setup
  BLE.setDeviceName("AMEBA_BLE_FACERECOG");
  advdata.addFlags();
  advdata.addCompleteName("AMEBA_BLE_FACERECOG");
  scndata.addCompleteServices(BLEUUID(UART_SERVICE_UUID));

  Rx.setWriteProperty(true);
  Rx.setWritePermissions(GATT_PERM_WRITE);
  Rx.setWriteCallback(writeCB);
  Rx.setBufferLen(STRING_BUF_SIZE);
  Tx.setReadProperty(true);
  Tx.setReadPermissions(GATT_PERM_READ);
  Tx.setNotifyProperty(true);
  Tx.setCCCDCallback(notifCB);
  Tx.setBufferLen(STRING_BUF_SIZE);

  UartService.addCharacteristic(Rx);
  UartService.addCharacteristic(Tx);

  BLE.init();
  BLE.configAdvert()->setAdvData(advdata);
  BLE.configAdvert()->setScanRspData(scndata);
  BLE.configServer(1);
  BLE.addService(UartService);

  // Configure camera video channels with video format information
  Camera.configVideoChannel(CHANNELVID, configVID);
  Camera.configVideoChannel(CHANNELJPEG, configJPEG);
  Camera.configVideoChannel(CHANNELNN, configNN);
  Camera.videoInit();

  // Configure RTSP with corresponding video format information
  rtsp.configVideo(configVID);
  rtsp.begin();
  
  // Configure Face Recognition model
  facerecog.configVideo(configNN);
  facerecog.modelSelect(FACE_RECOGNITION, NA_MODEL, DEFAULT_SCRFD, DEFAULT_MOBILEFACENET);
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

  // Configure StreamIO object to stream data from RGB video channel to face detection
  videoStreamerRGBFD.registerInput(Camera.getStream(CHANNELNN));
  videoStreamerRGBFD.setStackSize();
  videoStreamerRGBFD.setTaskPriority();
  videoStreamerRGBFD.registerOutput(facerecog);
  if (videoStreamerRGBFD.begin() != 0) {
    Serial.println("StreamIO link start failed");
  }
  // Start video channel for NN
  Camera.channelBegin(CHANNELNN);

  // Start OSD drawing on RTSP video channel
  OSD.configVideo(CHANNELVID, configVID);
  OSD.begin();
  
  // Start BLE
  BLE.beginPeripheral();
  // Servo moves to position the angle 180 degree (LOCK CLOSE)
  myservo.write(180);
}

void loop() {
  buttonState = digitalRead(BUTTON_PIN);
  if ((buttonState == ON) && (systemOn == false)) {  // When button is being pressed, systemOn becomes true
    Tx.writeString("Door Bell Pressed.\n");          // Send notification to connected BLE Device
    if (BLE.connected(0) && notify) {
      Tx.notify(0);
    }
    for (int count = 0; count < 3; count++) {
      digitalWrite(RED_LED, HIGH);
      digitalWrite(GREEN_LED, HIGH);
      delay(500);
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, LOW);
      delay(500);
    }
    systemOn = true;
  } else {
    //Both LED remains on when button not pressed
    if (systemOn == false) {
      systemOn = false;
      digitalWrite(RED_LED, HIGH);
      digitalWrite(GREEN_LED, HIGH);
    }
  }
  if (buttonState == OFF) systemOn = false;
  else {
    if (Rx.readString() == String("Open\n")) {
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);
      fileName = String("Authorized");  // File name for Authorized Door Opening
      doorOpen = true;
      Rx.writeString("Done\n"); // Write a new string to Rx to prevent Rx.readstring() to keep reading "Open"
    } else if (Rx.readString() == String("Snapshot\n")) { // When BLE Command "Snapshot" being received
      fs.begin();
      File file = fs.open(String(fs.getRootPath()) + "SnapshotTaken" + String(++counter) + ".jpg"); // File name for Snapshot taken
      delay(1000);
      Camera.getImage(CHANNELJPEG, &img_addr, &img_len);
      file.write((uint8_t*)img_addr, img_len);
      file.close();
      fs.end();
      Rx.writeString("Done\n"); // Write a new string to Rx to prevent Rx.readstring() to keep reading "Snapshot"
    }
  }
  if (Serial.available() > 0) {
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
  // Take snapshot and open door for 10 seconds
  if ((doorOpen == true) && (systemOn == true)) {
    fs.begin();
    File file = fs.open(String(fs.getRootPath()) + fileName + String(++counter) + ".jpg");
    delay(1000);
    Camera.getImage(CHANNELJPEG, &img_addr, &img_len);
    file.write((uint8_t*)img_addr, img_len);
    file.close();
    fs.end();
    myservo.write(0);
    Serial.println("Opening Door!");
    delay(10000);
    myservo.write(180);
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    doorOpen = false;
  }

  delay(1000);
  OSD.createBitmap(CHANNELVID);
  OSD.update(CHANNELVID);
}

// User callback function for post processing of face recognition results
void FRPostProcess(std::vector<FaceRecognitionResult> results) {
  uint16_t im_h = configVID.height();
  uint16_t im_w = configVID.width();

  printf("Total number of faces detected = %d\r\n", results.size());

  OSD.createBitmap(CHANNELVID);
  resultSize = results.size();

  if (results.size() > 0) {
    if (systemOn == true) {
      if (results.size() > 1) { // Door remain close when more than one face detected
        if (doorOpen == false) {
          digitalWrite(RED_LED, HIGH);
          digitalWrite(GREEN_LED, LOW);
        }
      } else {
        FaceRecognitionResult singleItem = results[0];
        if (String(singleItem.name()) == String("unknown")) {  // Door remain close when unknown face detected
          if (doorOpen == false) {
            digitalWrite(RED_LED, HIGH);
            digitalWrite(GREEN_LED, LOW);
          }
        } else { // Door open when a single registered face detected
          digitalWrite(RED_LED, LOW);
          digitalWrite(GREEN_LED, HIGH);
          doorOpen = true;
          fileName = String(singleItem.name());
        }
      }
    }

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
      OSD.drawRect(CHANNELVID, xmin, ymin, xmax, ymax, 3, osd_color);

      // Print identification text above boundary box
      char text_str[40];
      snprintf(text_str, sizeof(text_str), "Face:%s", item.name());
      OSD.drawText(CHANNELVID, xmin, ymin - OSD.getTextHeight(CHANNELVID), text_str, osd_color);
    }
  }
  OSD.update(CHANNELVID);
}

// Callback function for Rx (Optional)
void writeCB(BLECharacteristic* chr, uint8_t connID) {
  printf("Characteristic %s write by connection %d :\n", chr->getUUID().str(), connID);
  if (chr->getDataLen() > 0) {
    Serial.print("Received string: ");
    Serial.print(chr->readString());
    Serial.println();
  }
}

// Callback function for Tx (Optional)
void notifCB(BLECharacteristic* chr, uint8_t connID, uint16_t cccd) {
  if (cccd & GATT_CLIENT_CHAR_CONFIG_NOTIFY) {
    printf("Notifications enabled on Characteristic %s for connection %d \n", chr->getUUID().str(), connID);
    notify = true;
  } else {
    printf("Notifications disabled on Characteristic %s for connection %d \n", chr->getUUID().str(), connID);
    notify = false;
  }
}
