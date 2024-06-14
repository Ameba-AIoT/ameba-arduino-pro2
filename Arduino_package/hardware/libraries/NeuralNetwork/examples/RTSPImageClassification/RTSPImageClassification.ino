/*

 Example guide:
 TBD

 NN Model Selection
 Select Neural Network(NN) task and models using .modelSelect(nntask, objdetmodel, facedetmodel, facerecogmodel, audclassmodel, imgclassmodel).
 Replace with NA_MODEL if they are not necessary for your selected NN Task.

 NN task
 =======
 OBJECT_DETECTION/ FACE_DETECTION/ FACE_RECOGNITION/ AUDIO CLASSIFICATION/ IMAGE CLASSIFICATION

 Models
 =======
 YOLOv3 model         DEFAULT_YOLOV3TINY   / CUSTOMIZED_YOLOV3TINY
 YOLOv4 model         DEFAULT_YOLOV4TINY   / CUSTOMIZED_YOLOV4TINY
 YOLOv7 model         DEFAULT_YOLOV7TINY   / CUSTOMIZED_YOLOV7TINY
 SCRFD model          DEFAULT_SCRFD        / CUSTOMIZED_SCRFD
 MobileFaceNet model  DEFAULT_MOBILEFACENET/ CUSTOMIZED_MOBILEFACENET
 YAMNET model         DEFAULT_YAMNET       / CUSTOMIZED_YAMNET
 CNN model            DEFAULT_IMGCLASS     / CUSTOMIZED_IMGCLASS
 No model             NA_MODEL
 */

#include "WiFi.h"
#include "StreamIO.h"
#include "VideoStream.h"
#include "RTSP.h"
#include "NNImageClassification.h"
#include "VideoStreamOverlay.h"
#include "ClassificationClassList.h"

// Color of images used to train the cnn model (RGB or Grayscale)
#define IMAGERGB 1

#define CHANNEL   0
#define CHANNELNN 3

// Lower resolution for NN processing
// Modify according to the model's input shape size
#define NNWIDTH  224
#define NNHEIGHT 224

VideoSetting config(VIDEO_FHD, 30, VIDEO_H264, 0);
VideoSetting configNN(NNWIDTH, NNHEIGHT, 10, VIDEO_RGB, 0);
NNImageClassification imgclass;
RTSP rtsp;
StreamIO videoStreamer(1, 1);
StreamIO videoStreamerNN(1, 1);

char ssid[] = "Network_SSID";    // your network SSID (name)
char pass[] = "Password";        // your network password
int status = WL_IDLE_STATUS;

IPAddress ip;
int rtsp_portnum;

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
    ip = WiFi.localIP();

    // Configure camera video channels with video format information
    // Adjust the bitrate based on your WiFi network quality
    config.setBitrate(2 * 1024 * 1024);    // Recommend to use 2Mbps for RTSP streaming to prevent network congestion
    Camera.configVideoChannel(CHANNEL, config);
    Camera.configVideoChannel(CHANNELNN, configNN);
    Camera.videoInit();

    // Configure RTSP with corresponding video format information
    rtsp.configVideo(config);
    rtsp.begin();
    rtsp_portnum = rtsp.getPort();

    // Configure object detection with corresponding video format information
    // Select Neural Network(NN) task and models
    imgclass.configVideo(configNN);
    imgclass.configInputImageColor(IMAGERGB);
    imgclass.setResultCallback(ICPostProcess);
    imgclass.modelSelect(IMAGE_CLASSIFICATION, NA_MODEL, NA_MODEL, NA_MODEL, NA_MODEL, DEFAULT_IMGCLASS);
    imgclass.begin();

    // Configure StreamIO object to stream data from video channel to RTSP
    videoStreamer.registerInput(Camera.getStream(CHANNEL));
    videoStreamer.registerOutput(rtsp);
    if (videoStreamer.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    // Start data stream from video channel
    Camera.channelBegin(CHANNEL);

    // Configure StreamIO object to stream data from RGB video channel to object detection
    videoStreamerNN.registerInput(Camera.getStream(CHANNELNN));
    videoStreamerNN.setStackSize();
    videoStreamerNN.setTaskPriority();
    videoStreamerNN.registerOutput(imgclass);
    if (videoStreamerNN.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    // Start data stream from video channel
    Camera.channelBegin(CHANNELNN);
}

void loop()
{
    // Do nothing
}

// User callback function
void ICPostProcess(void)
{
    int class_id = imgclass.classID();
    if (imgclassItemList[class_id].filter) {    // header file
        float prob = imgclass.score();
        printf("class %d, score: %f, name: %s\r\n", class_id, prob, imgclassItemList[class_id].imgclassName);
    }
}
