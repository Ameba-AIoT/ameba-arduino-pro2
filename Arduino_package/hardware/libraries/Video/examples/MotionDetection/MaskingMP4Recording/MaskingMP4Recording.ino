// This example acts as a Security System based on Motion Detection, which would start to record a 
// 30 seconds long MP4 video everytime motion is detected. (Alarm function could be initiated as well, but on default disabled)
#include "WiFi.h"
#include "VideoStream.h"
#include "StreamIO.h"
#include "AudioStream.h"
#include "MP4Recording.h"
#include "RTSP.h"
#include "MotionDetection.h"
#include "VideoStreamOverlay.h"

#define CHANNELVID 0  // Channel for RTSP streaming
#define CHANNELMP4 1  // Channel for MP4 recording
#define CHANNELMD  3  // RGB format video for motion detection only avaliable on channel 3

// Pin Definition
#define GREEN_LED  4
//#define BUZZER_PIN 7

VideoSetting configVID(VIDEO_HD, CAM_FPS, VIDEO_H264, 0);  // HD resolution video for streaming
VideoSetting configMP4(VIDEO_FHD, CAM_FPS, VIDEO_H264, 0); // FHD resolution video for streaming
VideoSetting configMD(VIDEO_VGA, 10, VIDEO_RGB, 0);        // Low resolution RGB video for motion detection
RTSP rtsp;
Audio audio;
AAC aac;
MP4Recording mp4;
StreamIO audioStreamer(1, 1);    // 1 Input Audio -> 1 Output AAC
StreamIO videoStreamer(1, 1);    // 1 Input Video -> 1 Output RTSP
StreamIO videoStreamerMD(1, 1);  // 1 Input RGB Video -> 1 Output MD
StreamIO avMixMP4Streamer(2, 1); // 2 Input Video + Audio -> 1 Output MP4
MotionDetection MD;

bool motionDetected = false;
bool recordingMotion = false;
int recordingCount = 0;

char ssid[] = "yourNetwork"; // your network SSID (name)
char pass[] = "Password";    // your network password
int status = WL_IDLE_STATUS;

void setup() {
    // GPIO Initialization
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

    // Configure audio peripheral for audio data output
    // Configure AAC audio encoder
    audio.begin();
    aac.begin();

    // Configure RTSP with corresponding video format information
    rtsp.configVideo(configVID);
    rtsp.begin();

    // Configure motion detection for low resolution RGB video stream
    MD.configVideo(configMD);
    MD.begin();
    MD.setDetectionMask(mask);

    // Configure MP4 with identical video format information
    // Configure MP4 recording settings
    mp4.configVideo(configMP4);
    mp4.setRecordingDuration(30);
    mp4.setRecordingFileCount(1);

    // Configure StreamIO object to stream data from audio channel to AAC encoder
    audioStreamer.registerInput(audio);
    audioStreamer.registerOutput(aac);
    if (audioStreamer.begin() != 0) {
      Serial.println("StreamIO link start failed");
    }

    // Configure StreamIO object to stream data from high res video channel to RTSP
    videoStreamer.registerInput(Camera.getStream(CHANNELVID));
    videoStreamer.registerOutput(rtsp);
    if (videoStreamer.begin() != 0) {
      Serial.println("StreamIO link start failed");
    }
    
    // Configure StreamIO object to stream data from low res video channel to motion detection
    videoStreamerMD.registerInput(Camera.getStream(CHANNELMD));
    videoStreamerMD.setStackSize();
    videoStreamerMD.registerOutput(MD);
    if (videoStreamerMD.begin() != 0) {
      Serial.println("StreamIO link start failed");
    }
    
    // Configure StreamIO object to stream data from video channel and AAC encoder to MP4 recording
    avMixMP4Streamer.registerInput1(Camera.getStream(CHANNELMP4));
    avMixMP4Streamer.registerInput2(aac);
    avMixMP4Streamer.registerOutput(mp4);
    if (avMixMP4Streamer.begin() != 0) {
      Serial.println("StreamIO link start failed");
    }
    
    // Start data stream from video channels
    Camera.channelBegin(CHANNELMD);
    Camera.channelBegin(CHANNELVID);
    Camera.channelBegin(CHANNELMP4);

    // Configure OSD for drawing on video stream
    OSD.configVideo(CHANNELVID, configVID);
    OSD.begin();
}

void loop() {
    // Motion detection results is expressed as an array
    // With 0 or 1 in each element indicating presence of motion
    // Iterate through all elements to check for motion
    // and calculate largest rectangle containing motion
    std::vector<MotionDetectionResult> md_results = MD.getResult();
    
    OSD.createBitmap(CHANNELVID);
    if (MD.getResultCount() > 0) {
        digitalWrite(GREEN_LED, HIGH);
        motionDetected = true;

        // Start recording MP4 to SD card
        if (recordingMotion == false) {
            recordingCount++;
            mp4.setRecordingFileName("MotionDetection" + String(recordingCount));
            mp4.begin();
            // tone(BUZZER_PIN, 1000, 500);
            recordingMotion = true;
        }

        for (uint16_t i = 0; i < MD.getResultCount(); i++) {
            MotionDetectionResult result = md_results[i];

            // Scale rectangle dimensions according to high resolution video stream and draw with OSD
            int xmin = (int)(result.xMin() * configVID.width());
            int ymin = (int)(result.yMin() * configVID.height());
            int xmax = (int)(result.xMax() * configVID.width());
            int ymax = (int)(result.yMax() * configVID.height());
            OSD.drawRect(CHANNELVID, xmin, ymin, xmax, ymax, 3, COLOR_GREEN);
        }
    } else {
        OSD.createBitmap(CHANNELVID);
    }
    
    // GREEN LED turn off when no motion detected
    if (motionDetected == false) {
        digitalWrite(GREEN_LED, LOW);
    }
    
    // If not in recording state, recordingMotion = false
    if (!mp4.getRecordingState()) {
        recordingMotion = false;
    }
    motionDetected = false;
    OSD.update(CHANNELVID);
    delay(100);
}