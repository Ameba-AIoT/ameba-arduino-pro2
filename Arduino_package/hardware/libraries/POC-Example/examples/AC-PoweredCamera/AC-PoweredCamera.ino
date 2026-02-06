#include "WiFi.h"
#include "WebSocketViewer.h"
#include "StreamIO.h"
#include "VideoStream.h"
#include "RTSP.h"
#include "MP4Recording.h"
#include "time.h"
#include "string.h"
#include "MotionDetection.h"
#include "NNObjectDetection.h"
#include "VideoStreamOverlay.h"
#include "ObjectClassList.h"

#define CHANNEL   0
#define CHANNELNN 3
// Lower resolution for NN processing
#define NNWIDTH  576
#define NNHEIGHT 320

VideoSetting config(VIDEO_FHD, 30, VIDEO_H264, 0);
VideoSetting configNN(NNWIDTH, NNHEIGHT, 10, VIDEO_RGB, 0);
RTSP rtsp;
WebSocketViewer ws_viewer;
NNObjectDetection ObjDet;
MP4Recording mp4;
StreamIO videoStreamer(1, 2);
StreamIO videoStreamerNN(1, 1);
StreamIO videoStreamerMD(1, 1);
MotionDetection MD;

// UTF-8 encoding can also be used for SSID with emoji characters
// Emoji characters can be converted into UTF-8 at https://mothereff.in/utf-8
// char ssid[] = "\xe2\x9c\x8c\xef\xb8\x8f Ameba \xe2\x9c\x8c\xef\xb8\x8f";
char ssid[] = "AP_Network_SSID";    // Set the AP SSID
char pass[] = "AP_Password";        // Set the AP password
char channel[] = "11";              // Set the AP channel
int status = WL_IDLE_STATUS;        // Indicator of Wifi status
int ssid_status = 0;                // Set SSID status, 1 hidden, 0 not hidden
String start_input;
int int_input;
time_t now;
struct tm ts;
char buf[80];
int noActivityCount = 0;

void setup()
{

    Serial.begin(115200);
    while (!Serial) {
        ;    // wait for serial port to connect. Needed for native USB port only
    }

    int checker = 0;

    Serial.println(ssid);
    checker = atoi(channel);
    status = WiFi.apbegin(ssid, pass, channel, ssid_status);
    if (checker < 1 || checker > 13) {
        Serial.println("WARNING: channel is out of 1-13 range, defaulted to channel 1");
    }
    delay(10000);

    Serial.println("AP mode already started");
    Serial.println();
    printWifiData();
    printCurrentNet();

    ws_viewer.loadWebResources(0);
    config.enableWebsocketViewer();
    // Recommended bitrate - 2 Mbps
    config.setBitrate(2 * 1024 * 1024);
    Camera.configVideoChannel(CHANNEL, config);
    Camera.configVideoChannel(CHANNELNN, configNN);
    Camera.videoInit();
    ws_viewer.init();

    // Configure MP4 with identical video format information
    // Configure MP4 recording settings
    mp4.configVideo(config);
    mp4.setRecordingFileCount(1);
    mp4.setRecordingDuration(3600);
    mp4.setRecordingDataType(STORAGE_VIDEO);    // Set MP4 to record video only

    // Configure motion detection for low resolution RGB video stream
    MD.configVideo(configNN);
    MD.begin();

    videoStreamer.registerInput(Camera.getStream(CHANNEL));
    videoStreamer.registerOutput1(ws_viewer);
    videoStreamer.registerOutput2(mp4);
    if (videoStreamer.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }


    // Configure object detection with corresponding video format information
    // Select Neural Network(NN) task and models
    ObjDet.configVideo(configNN);
    ObjDet.modelSelect(OBJECT_DETECTION, DEFAULT_YOLOV4TINY, NA_MODEL, NA_MODEL);
    ObjDet.begin();


    videoStreamerMD.registerInput(Camera.getStream(CHANNELNN));
    videoStreamerMD.setStackSize();
    videoStreamerMD.setTaskPriority();
    videoStreamerMD.registerOutput(MD);
    if (videoStreamerMD.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }
    // Configure StreamIO object to stream data from RGB video channel to object detection
    videoStreamerNN.registerInput(Camera.getStream(CHANNELNN));
    videoStreamerNN.setStackSize();
    videoStreamerNN.setTaskPriority();
    videoStreamerNN.registerOutput(ObjDet);
    if (videoStreamerNN.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    Camera.channelBegin(CHANNEL);
    Camera.channelBegin(CHANNELNN);
    // Start OSD drawing on RTSP video channel
    OSD.configVideo(CHANNEL, config);
    OSD.begin();

    ws_viewer.begin();
}

void loop()
{
    if (ObjDet.getResultCount() > 0 || MD.getResultCount() > 0) {
        if (mp4.getRecordingState() == 0) {
            // Get current time
            time(&now);
            // Format time, "ddd yyyy-mm-dd hh:mm:ss zzz"
            ts = *localtime(&now);
            strftime(buf, sizeof(buf), "%H:%M %d-%m-%Y", &ts);
            printf("%s\n", buf);
            strftime(buf, sizeof(buf), "%H %M %d-%m-%Y", &ts);
            delay(100);
            mp4.setRecordingFileName(buf);
            mp4.begin();
        }
        noActivityCount = 0;
    } else {
        noActivityCount++;
        if (mp4.getRecordingState() > 0 && noActivityCount >= 100) {
            mp4.end();
            // Get current time
            time(&now);
            // Format time, "ddd yyyy-mm-dd hh:mm:ss zzz"
            ts = *localtime(&now);
            strftime(buf, sizeof(buf), "%H:%M %d-%m-%Y", &ts);
            printf("%s\n", buf);
        }
    }
    OSD.createBitmap(CHANNEL);

    std::vector<MotionDetectionResult> md_results = MD.getResult();
    if (MD.getResultCount() > 0) {
        for (uint16_t i = 0; i < MD.getResultCount(); i++) {
            MotionDetectionResult result = md_results[i];
            int xmin = (int)(result.xMin() * config.width());
            int xmax = (int)(result.xMax() * config.width());
            int ymin = (int)(result.yMin() * config.height());
            int ymax = (int)(result.yMax() * config.height());
            // printf("%d:\t%d %d %d %d\n\r", i, xmin, xmax, ymin, ymax);
            OSD.drawRect(CHANNEL, xmin, ymin, xmax, ymax, 3, COLOR_GREEN);
        }
    }
    OSD.update(CHANNEL);

    std::vector<ObjectDetectionResult> results = ObjDet.getResult();

    uint16_t im_h = config.height();
    uint16_t im_w = config.width();

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
                // printf("Item %d %s:\t%d %d %d %d\n\r", i, itemList[obj_type].objectName, xmin, xmax, ymin, ymax);
                OSD.drawRect(CHANNEL, xmin, ymin, xmax, ymax, 3, OSD_COLOR_WHITE);
                // Print identification text
                char text_str[20];
                snprintf(text_str, sizeof(text_str), "%s %d", itemList[obj_type].objectName, item.score());
                OSD.drawText(CHANNEL, xmin, ymin - OSD.getTextHeight(CHANNEL), text_str, OSD_COLOR_CYAN);
            }
        }
    }

    OSD.update(CHANNEL);

    // delay to wait for new results
    delay(100);
}

void printWifiData()
{
    // print your WiFi IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    // print your subnet mask:
    IPAddress subnet = WiFi.subnetMask();
    Serial.print("NetMask: ");
    Serial.println(subnet);

    // print your gateway address:
    IPAddress gateway = WiFi.gatewayIP();
    Serial.print("Gateway: ");
    Serial.println(gateway);
    Serial.println();
}

void printCurrentNet()
{
    // print the SSID of the AP:
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // print the MAC address of AP:
    byte bssid[6];
    WiFi.BSSID(bssid);
    Serial.print("BSSID: ");
    Serial.print(bssid[0], HEX);
    Serial.print(":");
    Serial.print(bssid[1], HEX);
    Serial.print(":");
    Serial.print(bssid[2], HEX);
    Serial.print(":");
    Serial.print(bssid[3], HEX);
    Serial.print(":");
    Serial.print(bssid[4], HEX);
    Serial.print(":");
    Serial.println(bssid[5], HEX);

    // print the encryption type:
    byte encryption = WiFi.encryptionType();
    Serial.print("Encryption Type:");
    Serial.println(encryption, HEX);
    Serial.println();
}
