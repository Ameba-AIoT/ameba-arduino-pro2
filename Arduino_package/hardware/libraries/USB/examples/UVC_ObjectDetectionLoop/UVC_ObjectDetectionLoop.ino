/*

 Example guide:
 https://www.amebaiot.com/en/amebapro2-arduino-neuralnework-object-detection/

 NN Model Selection
 Select Neural Network(NN) task and models using modelSelect(nntask, objdetmodel, facedetmodel, facerecogmodel).
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

#include "StreamIO.h"
#include "VideoStream.h"
#include "UVCD.h"
#include "NNObjectDetection.h"
#include "VideoStreamOverlay.h"
#include "ObjectClassList.h"



#define STREAM_CHANNEL 0
#define CHANNELNN 3

int reconnect = 0;
int disconnect = 0;

Video camera_uvcd;
NNObjectDetection ObjDet;
UVCD usb_uvcd;

// Lower resolution for NN processing
#define NNWIDTH  576
#define NNHEIGHT 320

StreamIO videoStreamer(1, 1);    // 1 Input Video -> 1 Output USB_CAM
StreamIO videoStreamerNN(1, 1);
VideoSetting stream_config(USB_UVCD_STREAM_PRESET);
VideoSetting configNN(NNWIDTH, NNHEIGHT, 10, VIDEO_RGB, 0);

void setup()
{
    Serial.begin(115200);
    // Configure camera video channel with video format information
    camera_uvcd.configVideoChannel(STREAM_CHANNEL, stream_config);
    
    camera_uvcd.configVideoChannel(CHANNELNN, configNN);
    // Configure usb_uvcd with identical video format information
    usb_uvcd.configVideo(stream_config);
    camera_uvcd.videoInit();

// Configure object detection with corresponding video format information
    // Select Neural Network(NN) task and models
    ObjDet.configVideo(configNN);
    ObjDet.modelSelect(OBJECT_DETECTION, DEFAULT_YOLOV4TINY, NA_MODEL, NA_MODEL);
    ObjDet.begin();

 // Configure StreamIO object to stream data from camera video channel to usb_uvcd
    videoStreamer.registerInput(camera_uvcd.getStream(STREAM_CHANNEL));
    videoStreamer.registerOutput(usb_uvcd);
    if (videoStreamer.begin() != 0) {
      Serial.println("StreamIO link start failed");
    }
    // Start data stream from video channel
    camera_uvcd.channelBegin(STREAM_CHANNEL);
    
    // Configure StreamIO object to stream data from RGB video channel to object detection
    videoStreamerNN.registerInput(camera_uvcd.getStream(CHANNELNN));
    videoStreamerNN.setStackSize();
    videoStreamerNN.setTaskPriority();
    videoStreamerNN.registerOutput(ObjDet);
    if (videoStreamerNN.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    // Start video channel for NN
    camera_uvcd.channelBegin(CHANNELNN);

    // Start usb uvcd for NN 
    usb_uvcd.nnbegin(camera_uvcd.getStream(STREAM_CHANNEL), videoStreamer.linker, STREAM_CHANNEL, CHANNELNN);
}

void loop()
{
    delay(5000);
    if (!usb_uvcd.isUsbUvcConnected()) {
        Serial.println("USB UVC device disconnected");
        // Handle disconnection processes
        if (disconnect == 0) {
          disconnectNN(); 
        }
        return;
    } else {
      // Handle reconnection or restart processes
        if (reconnect == 1) {
          reconnectNN();
        }
        std::vector<ObjectDetectionResult> results = ObjDet.getResult();
        uint16_t im_h = stream_config.height();
        uint16_t im_w = stream_config.width();

        printf("Total number of objects detected = %d\r\n", ObjDet.getResultCount());

        if (ObjDet.getResultCount() > 0) {
            for (int i = 0; i < ObjDet.getResultCount(); i++) {
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
                }
            }
        }      
    }    
} 

void disconnectNN() 
{
    camera_uvcd.channelEnd(CHANNELNN); // Stop video channel from NN
    camera_uvcd.channelBegin(STREAM_CHANNEL); // Stop video channel from video channel
    reconnect = 1;
    disconnect = 1;
}

void reconnectNN() 
{
    camera_uvcd.channelBegin(CHANNELNN); // Start video channel for NN
    camera_uvcd.channelBegin(STREAM_CHANNEL); // Start video channel for video channel
    reconnect = 0;
    disconnect = 0;
}