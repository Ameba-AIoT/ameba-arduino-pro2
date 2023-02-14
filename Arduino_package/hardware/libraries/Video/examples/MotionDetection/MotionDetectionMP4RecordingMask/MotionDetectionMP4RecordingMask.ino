// This example acts as a Security System based on Motion Detection, which would start to record a 30 seconds long MP4 video every time motion is sensed (Alarm function could be initiated as well, but on default disabled)
#include "WiFi.h"
#include "VideoStream.h"
#include "StreamIO.h"
#include "AudioStream.h"
#include "MP4Recording.h"
#include "RTSP.h"
#include "MotionDetection.h"
#include "VideoStreamOverlay.h"

// CHANNELVID: RTSP; CHANNELMP4: MP4; CHANNELMD: Motion Detection
#define CHANNELVID 0  // High resolution video channel for streaming
#define CHANNELMP4 1
#define CHANNELMD 3  // RGB format video for motion detection only avaliable on channel 3
#define MDRES 16     // Motion detection grid resolution
// Pin Definition
#define GREEN_LED 4
//#define BUZZER_PIN 7
// Define ON and OFF to replace HIGH and LOW
#define ON 1
#define OFF 0

// Video Config
VideoSetting configVID(VIDEO_FHD, 30, VIDEO_H264, 0);  // High resolution video for streaming
VideoSetting configMP4(CHANNELMP4);
VideoSetting configMD(VIDEO_VGA, 10, VIDEO_RGB, 0);  // Low resolution RGB video for motion detection
RTSP rtsp;
Audio audio;
AAC aac;
MP4Recording mp4;
StreamIO videoStreamer(1, 1);
StreamIO videoStreamerMD(1, 1);
StreamIO audioStreamer(1, 1);  // 1 Input Audio -> 1 Output AAC
StreamIO avMixStreamer(2, 1);  // 2 Input Video + Audio -> 1 Output MP4
MotionDetection MD(MDRES, MDRES);

// Variables
char ssid[] = "RealKungFu";  // your network SSID (name)
char pass[] = "RealTech";    // your network password
int status = WL_IDLE_STATUS;
bool motionDetected = false;
bool currentMotion = false;
int recordingCount = 0;
// Set a mask which would disable the motion detection for the left half of the screen
char mask[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1
};

void setup() {
  // GPIO Initialisation
  pinMode(GREEN_LED, OUTPUT);
  Serial.begin(115200);

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);

    // wait 2 seconds for connection:
    delay(2000);
  }

  // Configure camera video channels for required resolutions and format outputs
  Camera.configVideoChannel(CHANNELVID, configVID);
  Camera.configVideoChannel(CHANNELMP4, configMP4);
  Camera.configVideoChannel(CHANNELMD, configMD);
  Camera.videoInit();

  // Configure RTSP for high resolution video stream information
  rtsp.configVideo(configVID);
  rtsp.begin();

  // Configure OSD for drawing on high resolution video stream
  OSD.configVideo(CHANNELVID, configVID);
  OSD.begin();

  // Configure motion detection for low resolution RGB video stream
  MD.configVideo(configMD);
  MD.begin();
  MD.setDetectionMask(mask);
  // Configure audio peripheral for audio data output
  audio.begin();
  // Configure AAC audio encoder
  aac.begin();

  // Configure MP4 with identical video format information
  // Configure MP4 recording settings
  mp4.configVideo(configMP4);
  mp4.setRecordingDuration(30);
  mp4.setRecordingFileCount(1);

  // Configure StreamIO object to stream data from high res video channel to RTSP
  videoStreamer.registerInput(Camera.getStream(CHANNELVID));
  videoStreamer.registerOutput(rtsp);
  if (videoStreamer.begin() != 0) {
    Serial.println("StreamIO link start failed");
  }

  // Start data stream from high resolution video channel
  Camera.channelBegin(CHANNELVID);
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

  // Configure StreamIO object to stream data from audio channel to AAC encoder
  audioStreamer.registerInput(audio);
  audioStreamer.registerOutput(aac);
  if (audioStreamer.begin() != 0) {
    Serial.println("StreamIO link start failed");
  }

  // Configure StreamIO object to stream data from video channel and AAC encoder to MP4 recording
  avMixStreamer.registerInput1(Camera.getStream(CHANNELMP4));
  avMixStreamer.registerInput2(aac);
  avMixStreamer.registerOutput(mp4);
  if (avMixStreamer.begin() != 0) {
    Serial.println("StreamIO link start failed");
  }

  // Start data stream from video channel
  Camera.channelBegin(CHANNELMP4);
}

void loop() {
  char* md_result = MD.getResult();
  // Motion detection results is expressed as an MDRES x MDRES array
  // With 0 or 1 in each element indicating presence of motion
  // Iterate through all elements to check for motion
  // and calculate largest rectangle containing motion
  int motion = 0, j, k;
  int jmin = MDRES - 1, jmax = 0;
  int kmin = MDRES - 1, kmax = 0;
  for (j = 0; j < MDRES; j++) {
    for (k = 0; k < MDRES; k++) {
      printf("%d ", md_result[j * MDRES + k]);
      if (md_result[j * MDRES + k]) {
        motion = 1;
        if (j < jmin) {
          jmin = j;
        }
        if (k < kmin) {
          kmin = k;
        }
        if (j > jmax) {
          jmax = j;
        }
        if (k > kmax) {
          kmax = k;
        }
      }
    }
    printf("\r\n");
  }
  printf("\r\n");

  OSD.clearAll(CHANNELVID);
  if (motion) {                                                                 // Enter if statement when motion detected
    digitalWrite(GREEN_LED, ON);                                                // GREEN LED lit up
    motionDetected = true;
    // Start recording MP4 data to SD card
    if (currentMotion == false) {                                               // Enter if statment if not in recording state
      recordingCount++;
      mp4.setRecordingFileName("MotionDetection" + String(recordingCount));
      mp4.begin();
      // tone(BUZZER_PIN, 1000, 500);
      currentMotion = true;
    }
    // Scale rectangle dimensions according to high resolution video stream and draw with OSD
    int xmin = (int)(kmin * configVID.width() / MDRES) + 1;
    int ymin = (int)(jmin * configVID.height() / MDRES) + 1;
    int xmax = (int)((kmax + 1) * configVID.width() / MDRES) - 1;
    int ymax = (int)((jmax + 1) * configVID.height() / MDRES) - 1;
    OSD.drawRect(CHANNELVID, xmin, ymin, xmax, ymax, 3, OSD_COLOR_GREEN);
  }
  if (motionDetected == false) digitalWrite(GREEN_LED, OFF);                      // GREEN LED turn off when no motion detected
  if (!mp4.getRecordingState()) currentMotion = false;                            // If not in recording state, currentMotion = false
  motionDetected = false;
  OSD.update(CHANNELVID);
  delay(100);
}
