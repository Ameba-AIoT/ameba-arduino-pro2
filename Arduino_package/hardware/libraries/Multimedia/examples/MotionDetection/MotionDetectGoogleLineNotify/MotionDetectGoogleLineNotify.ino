/*  
    Example guide: 

    This example uses the on-board camera sensor (JX-F37P) to capture suspicious movements. 
    Upon detection, the system captures an image, saves it to an SD Card, uploads it to Google Drive, 
    and concurrently sends an alert through Line Notify to the user's mobile phone, ensuring swift response and heightened security.
*/

#include <Arduino.h>
#include "WiFi.h"
#include "VideoStream.h"
#include "StreamIO.h"
#include "RTSP.h"
#include "MotionDetection.h"
#include "VideoStreamOverlay.h"
#include "AmebaFatFS.h"
#include "Base64.h"

// User Configuration
#define CHANNEL 0             // Video channel for streaming & snapshot
#define CHANNELMD 3           // RGB format video for motion detection only avaliable on channel 3
#define SSID "Network_SSID5"  // Enter your WiFi SSID (name)
#define PW "Password"         // Enter your WiFi password
#define FILENAME "image.jpg"  // Save as jpg image in SD Card

// Enter your Google Script and Line Notify details
String myScript = "/macros/s/****************************/exec";  // Create your Google Apps Script and replace the "myScript" path. AKfycbyTUSAQIV1XuY7OgadvlO8n2Fyid3MnGCpFOe4oF19CJT9rU3nV1XVc915NjykUcaSx
String myFoldername = "&myFoldername=AMB82";                      // Set the Google Drive folder name to store your file
String myFilename = "&myFilename=image.jpg";                      // Set the Google Drive file name to store your data
String myImage = "&myFile=";

char ssid[] = SSID;
char pass[] = PW;
int status = WL_IDLE_STATUS;

uint32_t img_addr = 0;
uint32_t img_len = 0;

// Create objects
VideoSetting config(VIDEO_D1, CAM_FPS, VIDEO_H264_JPEG, 1);  // High resolution video for streaming
VideoSetting configMD(VIDEO_VGA, 10, VIDEO_RGB, 0);          // Low resolution RGB video for motion detection
RTSP rtsp;
StreamIO videoStreamer(1, 1);
StreamIO videoStreamerMD(1, 1);
MotionDetection MD;
AmebaFatFS fs;
WiFiSSLClient wifiClient;

int counter = 0;
char buf[512];
char *p;
bool flag_motion = false;

void setup() {
  Serial.begin(115200);

  // Wi-Fi init
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    // wait 2 seconds for connection:
    delay(2000);
  }
  WiFiCon();

  // camera init
  Camera.configVideoChannel(CHANNEL, config);      // Channel for video streaming
  Camera.configVideoChannel(CHANNELMD, configMD);  // Channel for motion detection
  Camera.videoInit();

  // Configure RTSP for high resolution video stream information
  rtsp.configVideo(config);
  rtsp.begin();

  // Configure motion detection for low resolution RGB video stream
  MD.configVideo(configMD);
  MD.begin();

  // Configure StreamIO object to stream data from high res video channel to RTSP
  videoStreamer.registerInput(Camera.getStream(CHANNEL));
  videoStreamer.registerOutput(rtsp);
  if (videoStreamer.begin() != 0) {
    Serial.println("StreamIO link start failed");
  }

  // Start data stream from high resolution video channel
  Camera.channelBegin(CHANNEL);
  Serial.println("Video RTSP Streaming Start");

  // Configure StreamIO object to stream data from low res video channel to motion detection
  videoStreamerMD.registerInput(Camera.getStream(CHANNELMD));
  videoStreamerMD.setStackSize();
  videoStreamerMD.registerOutput(MD);
  if (videoStreamerMD.begin() != 0) {
    Serial.println("StreamIO link start failed");
  }

  // Start data stream from low resolution video channel
  Camera.channelBegin(CHANNELMD);

  // Configure OSD for drawing on high resolution video stream
  OSD.configVideo(CHANNEL, config);
  OSD.begin();
  Serial.println("");
  Serial.println("================================");
  Serial.println("Motion Detecting");
  Serial.println("================================");
}

void loop() {
  // Motion detection results is expressed as an array
  // With 0 or 1 in each element indicating presence of motion
  // Iterate through all elements to check for motion
  // and calculate rectangles containing motion
  std::vector<MotionDetectionResult> md_results = MD.getResult();
  OSD.createBitmap(CHANNEL);

  if (MD.getResultCount() > 0) {
    counter++;
    for (uint16_t i = 0; i < MD.getResultCount(); i++) {
      MotionDetectionResult result = md_results[i];
      int xmin = (int)(result.xMin() * config.width());
      int xmax = (int)(result.xMax() * config.width());
      int ymin = (int)(result.yMin() * config.height());
      int ymax = (int)(result.yMax() * config.height());
      // printf("%d:\t%d %d %d %d\n\r", i, xmin, xmax, ymin, ymax);
      OSD.drawRect(CHANNEL, xmin, ymin, xmax, ymax, 3, COLOR_GREEN);
    }
    if (counter >= 5) {
      flag_motion = true;
    }
  } else {
    counter = 0;
    flag_motion = false;
  }

  if (flag_motion) {
    Serial.println("Motion Detected");  // motion detected take photo
    // SD card init
    if (!fs.begin()) {
      StreamEnd();
      pinMode(LED_B, OUTPUT);
      digitalWrite(LED_B, HIGH);
      Serial.println("");
      Serial.println("================================");
      Serial.println("[ERROR] SD Card Mount Failed !!!");
      Serial.println("================================");
      while (1)
        ;
    }

    // List root directory and put results in buf
    memset(buf, 0, sizeof(buf));
    fs.readDir(fs.getRootPath(), buf, sizeof(buf));
    String filepath = String(fs.getRootPath()) + String(FILENAME);
    File file = fs.open(filepath);
    if (!file) {
      Serial.println("");
      Serial.println("================================");
      Serial.println("[ERROR] Failed to open file for reading");
      Serial.println("================================");
      fs.end();
    }
    // Serial.println("Files under: " + String(fs.getRootPath()));
    // Serial.println("Read from file: " + filepath);
    // Serial.println("file size: " + String(file.size()));
    delay(100);

    // Taking Photo
    CamFlash();
    Camera.getImage(CHANNEL, &img_addr, &img_len);
    file.write((uint8_t *)img_addr, img_len);
    file.close();
    // upadte OSD
    OSD.update(CHANNEL);
    delay(100);
    Serial.println("===================================");
    Serial.println("[INFO] Photo Captured ...");
    Serial.println("===================================");
    
    // File Processing
    /* the filenames are separated with '\0', so we scan one by one */
    p = buf;
    while (strlen(p) > 0) {
      /* list out file name image will be saved as "image.jpg" */
      if (strstr(p, FILENAME) != NULL) {
        Serial.println("Found 'image.jpg' in the string.");
      } else {
        //Serial.println("Substring 'image.jpg' not found in the string.");
      }
      p += strlen(p) + 1;
    }

    uint8_t *fileinput;
    file = fs.open(filepath);
    unsigned int fileSize = file.size();
    fileinput = (uint8_t *)malloc(fileSize + 1);
    file.read(fileinput, fileSize);
    fileinput[fileSize] = '\0';
    file.close();
    fs.end();

    char *input = (char *)fileinput;
    String imageFile = "data:image/jpeg;base32,";
    char output[base64_enc_len(3)];
    for (unsigned int i = 0; i < fileSize; i++) {
      base64_encode(output, (input++), 3);
      if (i % 3 == 0) {
        imageFile += urlencode(String(output));
      }
    }

    // transfer file to Google Drive
    // https://github.com/fustyles/Arduino/tree/master/ESP32-CAM_GoogleDrive_Linenotify
    String Data = myFoldername + myFilename + myImage;
    const char *myDomain = "script.google.com";
    String getAll = "", getBody = "";
    Serial.println("Connect to " + String(myDomain));

    if (wifiClient.connect(myDomain, 443)) {
      Serial.println("Connection successful");

      wifiClient.println("POST " + myScript + " HTTP/1.1");
      wifiClient.println("Host: " + String(myDomain));
      wifiClient.println("Content-Length: " + String(Data.length() + imageFile.length()));
      wifiClient.println("Content-Type: application/x-www-form-urlencoded");
      wifiClient.println("Connection: keep-alive");
      wifiClient.println();

      wifiClient.print(Data);
      for (unsigned int Index = 0; Index < imageFile.length(); Index = Index + 1000) {
        wifiClient.print(imageFile.substring(Index, Index + 1000));
      }

      int waitTime = 10000;  // timeout 10 seconds
      unsigned int startTime = millis();
      boolean state = false;

      while ((startTime + waitTime) > millis()) {
        Serial.print(".");
        delay(100);
        while (wifiClient.available()) {
          char c = wifiClient.read();
          if (state == true) getBody += String(c);
          if (c == '\n') {
            if (getAll.length() == 0) state = true;
            getAll = "";
          } else if (c != '\r')
            getAll += String(c);
          startTime = millis();
        }
        if (getBody.length() > 0) break;
      }
      wifiClient.stop();
      Serial.println(getBody);
    } else {
      getBody = "Connected to " + String(myDomain) + " failed.";
      Serial.println("Connected to " + String(myDomain) + " failed.");
    }
    Serial.println("File uploading done.");
    Serial.println("===================================");

  } else {
    Serial.print(".");  // no motion detected
  }
}

// //https://github.com/zenmanenergy/ESP8266-Arduino-Examples/
// String urlencode(String str) {
//   String encodedString = "";
//   char c;
//   char code0;
//   char code1;
//   //char code2;
//   for (unsigned int i = 0; i < str.length(); i++) {
//     c = str.charAt(i);
//     if (c == ' ') {
//       encodedString += '+';
//     } else if (isalnum(c)) {
//       encodedString += c;
//     } else {
//       code1 = (c & 0xf) + '0';
//       if ((c & 0xf) > 9) {
//         code1 = (c & 0xf) - 10 + 'A';
//       }
//       c = (c >> 4) & 0xf;
//       code0 = c + '0';
//       if (c > 9) {
//         code0 = c - 10 + 'A';
//       }
//       //code2='\0';
//       encodedString += '%';
//       encodedString += code0;
//       encodedString += code1;
//       //encodedString+=code2;
//     }
//     yield();
//   }
//   return encodedString;
// }

//https://www.arduino.cc/reference/en/libraries/urlencode/
String urlencode(String str) {
  const char *msg = str.c_str();
  const char *hex = "0123456789ABCDEF";
  String encodedMsg = "";
  while (*msg != '\0') {
    if (('a' <= *msg && *msg <= 'z') || ('A' <= *msg && *msg <= 'Z') || ('0' <= *msg && *msg <= '9') || *msg == '-' || *msg == '_' || *msg == '.' || *msg == '~') {
      encodedMsg += *msg;
    } else {
      encodedMsg += '%';
      encodedMsg += hex[(unsigned char)*msg >> 4];
      encodedMsg += hex[*msg & 0xf];
    }
    msg++;
  }
  return encodedMsg;
}

void CamFlash() {
  pinMode(LED_G, OUTPUT);
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_G, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(100);                 // wait for a second
    digitalWrite(LED_G, LOW);   // turn the LED off by making the voltage LOW
    delay(100);
  }
}

void WiFiCon() {
  pinMode(LED_B, OUTPUT);
  for (int i = 0; i < 2; i++) {
    digitalWrite(LED_B, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(300);                 // wait for a second
    digitalWrite(LED_B, LOW);   // turn the LED off by making the voltage LOW
    delay(300);
  }
}

void StreamEnd() {
  videoStreamer.pause();        // pause linkers
  videoStreamerMD.pause();
  rtsp.end();                   // stop RTSP chaneel/module
  Camera.channelEnd();          // stop camera channel/module
  MD.end();                     // close module
  Camera.videoDeinit();         // video deinit
  delay(1000);
}