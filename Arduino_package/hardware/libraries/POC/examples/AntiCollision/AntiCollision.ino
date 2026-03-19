/*
  Read an 8x8 array of distances from the VL53L5CX
  By: Nathan Seidle
  SparkFun Electronics
  Date: October 26, 2021
  License: MIT. See license file for more information but you can
  basically do whatever you want with this code.

  Modified 02 Jul 2025
  by Realtek SG

  Example Guide:
https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/POC/Anti-Collision.html
*/
#include <Wire.h>
#include <SparkFun_VL53L5CX_libraries/SparkFun_VL53L5CX_Library.h>
#include "WiFi.h"
#include "StreamIO.h"
#include "VideoStream.h"
#include "RTSP.h"
#include "NNObjectDetection.h"
#include "VideoStreamOverlay.h"
#include "ObjectClassList.h"

#define CHANNEL   0
#define CHANNELNN 3

// Lower resolution for NN processing
#define NNWIDTH  576
#define NNHEIGHT 320

// ToF sensor's estiamted resolution 880 x 520
#define tof_resolution_xmin 520
#define tof_resolution_xmax 1400
#define tof_resolution_ymin 220
#define tof_resolution_ymax 740

SparkFun_VL53L5CX sensor;
VL53L5CX_ResultsData data;

VideoSetting config(VIDEO_FHD, 30, VIDEO_H264, 0);
VideoSetting configNN(NNWIDTH, NNHEIGHT, 10, VIDEO_RGB, 0);
NNObjectDetection ObjDet;
RTSP rtsp;
StreamIO videoStreamer(1, 1);
StreamIO videoStreamerNN(1, 1);

char ssid[] = "Network_SSID";    // your network SSID (name)
char pass[] = "Password";        // your network password
int status = WL_IDLE_STATUS;

IPAddress ip;
int rtsp_portnum;

int imageResolution = 0;
int imageWidth = 0;
char data_str[40];
int current_xmin, current_ymin;
int text_color;

void setup()
{
    Serial.begin(115200);

    Serial.println("Initializing sensor board. This can take up to 10s. Please wait.");
    Wire.begin();
    Wire.setClock(400000);

    if (sensor.begin() == false) {
        Serial.println(F("Sensor not found - check your wiring. Freezing"));
        while (1)
            ;
    }
    sensor.setResolution(8 * 8);                 // Enable all 64 pads
    imageResolution = sensor.getResolution();    // Query sensor for current resolution - either 4x4 or 8x8
    imageWidth = sqrt(imageResolution);          // Calculate printing width

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
    ObjDet.configVideo(configNN);
    ObjDet.modelSelect(OBJECT_DETECTION, DEFAULT_YOLOV4TINY, NA_MODEL, NA_MODEL);
    ObjDet.begin();

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
    videoStreamerNN.registerOutput(ObjDet);
    if (videoStreamerNN.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    // Start video channel for NN
    Camera.channelBegin(CHANNELNN);

    sensor.startRanging();

    // Start OSD drawing on RTSP video channel
    OSD.configVideo(CHANNEL, config);
    OSD.begin();
}

void loop()
{
    // Poll sensor for new data
    poll_VL53L5CX();
    delay(100);    // Small delay between polling
}

void poll_VL53L5CX()
{
    // Poll sensor for new data
    if (sensor.isDataReady() == true) {
        if (sensor.getRangingData(&data))    // Read distance data into array
        {
            OSD.createBitmap(CHANNEL, 0);
            OSD.createBitmap(CHANNEL, 1);

            current_ymin = tof_resolution_ymin + 32;

            for (int y = 0; y <= imageWidth * (imageWidth - 1); y += imageWidth) {
                current_xmin = tof_resolution_xmin + 3;

                for (int x = 0; x <= imageWidth - 1; x++) {
                    snprintf(data_str, sizeof(data_str), "%d", data.distance_mm[x + y]);

                    if (data.distance_mm[x + y] < 1000) {
                        text_color = OSD_COLOR_RED;
                    } else if (data.distance_mm[x + y] < 2000) {
                        text_color = OSD_COLOR_ORANGE;
                    } else if (data.distance_mm[x + y] < 3000) {
                        text_color = OSD_COLOR_YELLOW;
                    } else {
                        text_color = OSD_COLOR_GREEN;
                    }

                    if (y <= 4 * imageWidth) {
                        OSD.drawText(CHANNEL, current_xmin, current_ymin - OSD.getTextHeight(CHANNEL), data_str, text_color, 0);
                    } else {
                        OSD.drawText(CHANNEL, current_xmin, current_ymin - OSD.getTextHeight(CHANNEL), data_str, text_color, 1);
                    }

                    current_xmin += 116;
                }
                current_ymin += 69;
            }

            OSD.drawRect(CHANNEL, tof_resolution_xmin, tof_resolution_ymin, tof_resolution_xmax, tof_resolution_ymax, 5, OSD_COLOR_BLACK, 1);    // Bounding box for ToF resolution

            detect_object();

            OSD.update(CHANNEL, 0);
            OSD.update(CHANNEL, 1);
        }
    }
}

void detect_object()
{
    std::vector<ObjectDetectionResult> results = ObjDet.getResult();

    uint16_t im_h = config.height();
    uint16_t im_w = config.width();

    // printf("Total number of objects detected = %d\r\n", ObjDet.getResultCount());
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
                OSD.drawRect(CHANNEL, xmin, ymin, xmax, ymax, 3, OSD_COLOR_WHITE, 1);

                // Print identification text
                char text_str[20];
                snprintf(text_str, sizeof(text_str), "%s %d", itemList[obj_type].objectName, item.score());
                OSD.drawText(CHANNEL, xmin, ymin - OSD.getTextHeight(CHANNEL), text_str, OSD_COLOR_CYAN, 1);
            }
        }
    }
}
