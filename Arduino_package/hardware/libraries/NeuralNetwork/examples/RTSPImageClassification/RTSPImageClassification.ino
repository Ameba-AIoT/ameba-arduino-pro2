/*
 Example guide:
 https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/Neural%20Network/Image%20Classification.html

 NN Model Selection
 Select Neural Network(NN) task and models using .modelSelect(nntask, objdetmodel, facedetmodel, facerecogmodel, audclassmodel, imgclassmodel).
 Replace with NA_MODEL if they are not necessary for your selected NN Task.

 NN task
 =======
 OBJECT_DETECTION/ FACE_DETECTION/ FACE_RECOGNITION/ AUDIO CLASSIFICATION/ IMAGE CLASSIFICATION

 Models
 =======
 YOLOv3 model               DEFAULT_YOLOV3TINY   / CUSTOMIZED_YOLOV3TINY
 YOLOv4 model               DEFAULT_YOLOV4TINY   / CUSTOMIZED_YOLOV4TINY
 YOLOv7 model               DEFAULT_YOLOV7TINY   / CUSTOMIZED_YOLOV7TINY
 SCRFD model                DEFAULT_SCRFD        / CUSTOMIZED_SCRFD
 MobileFaceNet model        DEFAULT_MOBILEFACENET/ CUSTOMIZED_MOBILEFACENET
 YAMNET model               DEFAULT_YAMNET       / CUSTOMIZED_YAMNET
 Custom CNN model           DEFAULT_IMGCLASS     / CUSTOMIZED_IMGCLASS
 MobileNetV2 model          DEFAULT_IMGCLASS_MOBILENETV2     / CUSTOMIZED_IMGCLASS_MOBILENETV2
 No model                   NA_MODEL
 */

#include "WiFi.h"
#include "StreamIO.h"
#include "VideoStream.h"
#include "RTSP.h"
#include "NNImageClassification.h"
#include "VideoStreamOverlay.h"
#include "ClassificationClassList.h"

// Enable only the model comes with metadata embedded, else ClassList need to be updated
#define USE_MODEL_META_DATA_EN 1

// Color of images used to train the cnn model (RGB or Grayscale)
#define IMAGERGB 0

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
    imgclass.configInputImageColor(IMAGERGB);    // only valid use for custom CNN model (e.g sequential)
    imgclass.useModelMetaData(USE_MODEL_META_DATA_EN);
    imgclass.setResultCallback(ICPostProcess_MobileNetV2);                                                               // MobileNetV2 model callback function: ICPostProcess_MobileNetV2, custom CNN model (e.g sequential) callback function: ICPostProcess
    imgclass.modelSelect(IMAGE_CLASSIFICATION, NA_MODEL, NA_MODEL, NA_MODEL, NA_MODEL, DEFAULT_IMGCLASS_MOBILENETV2);    // if using MobileNetV2 model: DEFAULT_IMGCLASS_MOBILENETV2/CUSTOMIZED_IMGCLASS_MOBILENETV2, custom CNN model (e.g sequential): DEFAULT_IMGCLASS/CUSTOMIZED_IMGCLASS
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

    // Start OSD drawing on RTSP video channel
    OSD.configVideo(CHANNEL, config);
    OSD.begin();
}

void loop()
{
    // Do nothing
}

// User callback function for MobileNetV2 model
void ICPostProcess_MobileNetV2(std::vector<ImageClassificationResult> results)
{
    OSD.createBitmap(CHANNEL);
    for (int i = 0; i < imgclass.getResultCount(); i++) {
        ImageClassificationResult imgclass_item = results[i];
        int class_id = (int)imgclass_item.classID();
        int prob = 0;
        if (imgclassMobileNetV2ItemList[class_id].filter) {
            char text_str[40];
            prob = imgclass_item.score();
            if (USE_MODEL_META_DATA_EN) {
                snprintf(text_str, sizeof(text_str), "class:%s %d", imgclass.getClassNameFromMeta(imgclass.model_meta_data, class_id, (int)(prob)), (int)(prob));
            } else {
                snprintf(text_str, sizeof(text_str), "class:%s %d", imgclassMobileNetV2ItemList[class_id].imgclassName, imgclass_item.score());
                printf("class:%s %d\r\n", imgclassMobileNetV2ItemList[class_id].imgclassName, imgclass_item.score());
            }
            OSD.drawText(CHANNEL, 20, 20, text_str, OSD_COLOR_CYAN);
        }
    }
    OSD.update(CHANNEL);
}

// User callback function for custom CNN (e.g sequential)
void ICPostProcess(std::vector<ImageClassificationResult> results)
{
    if (imgclass.getResultCount() > 0) {
        // uncomment if you would like to see all the probabilities for all classes
        // printf("---- probabilities for all classes ----\r\n");
        // for (int i = 0; i < imgclass.getResultCount(); i++) {
        //     ImageClassificationResult imgclass_item = results[i];
        //     int class_id = (int)imgclass_item.classID();
        //     if (imgclassItemList[class_id].filter) {
        //         printf("class:%s %d\r\n", imgclassItemList[class_id].imgclassName, imgclass_item.score());
        //     }
        // }

        OSD.createBitmap(CHANNEL);
        char text_str[40];
        ImageClassificationResult top_imgclass_item = results[0];
        int top_class_id = (int)top_imgclass_item.classID();
        if (imgclassItemList[top_class_id].filter) {
            snprintf(text_str, sizeof(text_str), "class:%s %d", imgclassItemList[top_class_id].imgclassName, top_imgclass_item.score());
            printf("top class detected: %s %d\r\n", imgclassItemList[top_class_id].imgclassName, top_imgclass_item.score());
        }
        OSD.drawText(CHANNEL, 20, 20, text_str, OSD_COLOR_CYAN);
        OSD.update(CHANNEL);
    }
}
