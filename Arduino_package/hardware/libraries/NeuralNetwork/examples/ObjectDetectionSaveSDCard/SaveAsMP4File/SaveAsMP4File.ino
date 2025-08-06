/*
 Example guide:
 https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/Neural%20Network/Object%20Detection%20results%20save%20on%20SD%20Card.html

 NN Model Selection
 Select Neural Network(NN) task and models using .modelSelect(nntask, objdetmodel, facedetmodel, facerecogmodel).
 Replace with NA_MODEL if they are not necessary for your selected NN Task.

 NN task
 =======
 OBJECT_DETECTION/ FACE_DETECTION/ FACE_RECOGNITION

 Models
 =======
 YOLOv3 model         DEFAULT_YOLOV3TINY   / CUSTOMIZED_YOLOV3TINY
 YOLOv4 model         DEFAULT_YOLOV4TINY   / CUSTOMIZED_YOLOV4TINY
 YOLOv7 model         DEFAULT_YOLOV7TINY   / CUSTOMIZED_YOLOV7TINY
 SCRFD model          DEFAULT_SCRFD        / CUSTOMIZED_SCRFD
 MobileFaceNet model  DEFAULT_MOBILEFACENET/ CUSTOMIZED_MOBILEFACENET
 No model             NA_MODEL
 */

#include "WiFi.h"
#include "StreamIO.h"
#include "VideoStream.h"
#include "AudioStream.h"
#include "AudioEncoder.h"
#include "MP4Recording.h"
#include "RTSP.h"
#include "MotionDetection.h"
#include "VideoStreamOverlay.h"
#include "NNObjectDetection.h"
#include "ObjectClassList.h"

// Default preset configurations for each video channel:
// Channel 0 : 1920 x 1080 30FPS H264
// Channel 1 : 1280 x 720  30FPS H264

// Default audio preset configurations:
// 0 :  8kHz Mono Analog Mic
// 1 : 16kHz Mono Analog Mic
// 2 :  8kHz Mono Digital PDM Mic
// 3 : 16kHz Mono Digital PDM Mic

#define CHANNEL   0    // Channel for RTSP streaming & MP4 recording
#define CHANNELNN 3    // RGB format video for object detection only available on channel 3

AudioSetting configA(0);
VideoSetting config(VIDEO_FHD, CAM_FPS, VIDEO_H264, 0);
VideoSetting configNN(VIDEO_VGA, 10, VIDEO_RGB, 0);
Audio audio;
AAC aac;
MP4Recording mp4;
RTSP rtsp;
NNObjectDetection ObjDet;

StreamIO videoStreamerNN(1, 1);    // 1 Input RGB Video -> 1 Output Object Detection
StreamIO audioStreamer(1, 1);      // 1 Input Audio -> 1 Output AAC
StreamIO avMixStreamer(2, 2);      // 2 Input Video + Audio -> 2 Output MP4 + RTSP

int recordingCount = 0;

char ssid[] = "Network_SSID";    // your network SSID (name)
char pass[] = "Password";        // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS;

void setup()
{
    Serial.begin(115200);

    // attempt to connect to Wifi network:
    while (status != WL_CONNECTED) {
        Serial.print("Attempting to connect to WPA SSID: ");
        Serial.println(ssid);
        status = WiFi.begin(ssid, pass);

        // wait 2 seconds for connection:
        delay(2000);
    }

    // Configure camera video channel with video format information
    Camera.configVideoChannel(CHANNEL, config);
    Camera.configVideoChannel(CHANNELNN, configNN);
    Camera.videoInit();

    // Configure audio peripheral for audio data output
    audio.configAudio(configA);
    audio.begin();
    // Configure AAC audio encoder
    aac.configAudio(configA);
    aac.begin();

    // Configure RTSP with identical video format information and enable audio streaming
    rtsp.configVideo(config);
    rtsp.configAudio(configA, CODEC_AAC);
    rtsp.begin();

    // Configure object detection with corresponding video format information
    // Select Neural Network(NN) task and models
    config.setBitrate(2 * 1024 * 1024);    // Recommend to use 2Mbps for RTSP streaming to prevent network congestion
    ObjDet.configVideo(configNN);
    ObjDet.modelSelect(OBJECT_DETECTION, DEFAULT_YOLOV4TINY, NA_MODEL, NA_MODEL);
    ObjDet.begin();

    // Configure MP4 with identical video format information
    // Configure MP4 recording settings
    mp4.configVideo(config);
    mp4.configAudio(configA, CODEC_AAC);
    mp4.setRecordingDuration(10);
    mp4.setRecordingFileCount(1);

    // Configure StreamIO object to stream data from audio channel to AAC encoder
    audioStreamer.registerInput(audio);
    audioStreamer.registerOutput(aac);
    if (audioStreamer.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    // Configure StreamIO object to stream data from video channel and AAC encoder to MP4 recording
    avMixStreamer.registerInput1(Camera.getStream(CHANNEL));
    avMixStreamer.registerInput2(aac);
    avMixStreamer.registerOutput1(rtsp);
    avMixStreamer.registerOutput2(mp4);
    if (avMixStreamer.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    // Start data stream from video channel
    Camera.channelBegin(CHANNEL);

    // Configure StreamIO object to stream data from low res video channel to object detection
    videoStreamerNN.registerInput(Camera.getStream(CHANNELNN));
    videoStreamerNN.setStackSize();
    videoStreamerNN.setTaskPriority();
    videoStreamerNN.registerOutput(ObjDet);
    if (videoStreamerNN.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    // Start data stream from low resolution video channel
    Camera.channelBegin(CHANNELNN);

    // Configure OSD for drawing on video stream
    OSD.configVideo(CHANNEL, config);
    OSD.begin();
}

void loop()
{
    std::vector<ObjectDetectionResult> results = ObjDet.getResult();

    uint16_t im_h = config.height();
    uint16_t im_w = config.width();

    OSD.createBitmap(CHANNEL);
    if (ObjDet.getResultCount() > 0) {
        for (uint16_t i = 0; i < ObjDet.getResultCount(); i++) {
            int obj_type = results[i].type();
            if (itemList[obj_type].filter) {    // check if item should be ignored
                ObjectDetectionResult item = results[i];
                // Result coordinates are floats ranging from 0.00 to 1.00
                // Multiply with RTSP resolution to get coordinates in pixels
                int xmin = (int)(item.xMin() * im_w);
                int xmax = (int)(item.xMax() * im_w);
                int ymin = (int)(item.yMin() * im_h);
                int ymax = (int)(item.yMax() * im_h);

                // Draw boundary box
                printf("Item %d %s:\t%d %d %d %d\n\r", i, itemList[obj_type].objectName, xmin, xmax, ymin, ymax);
                OSD.drawRect(CHANNEL, xmin, ymin, xmax, ymax, 3, OSD_COLOR_WHITE);

                // Print identification text
                char text_str[20];
                snprintf(text_str, sizeof(text_str), "%s %d", itemList[obj_type].objectName, item.score());
                OSD.drawText(CHANNEL, xmin, ymin - OSD.getTextHeight(CHANNEL), text_str, OSD_COLOR_CYAN);
            }
        }
        if (!mp4.getRecordingState()) {    // if MP4 not in recording mode
            recordingCount++;
            mp4.setRecordingFileName("ObjectDetection" + String(recordingCount));
            mp4.begin();
        }
    }

    OSD.update(CHANNEL);
    delay(100);
}
