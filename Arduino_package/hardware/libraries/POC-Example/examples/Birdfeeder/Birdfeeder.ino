#include "WiFi.h"
#include "StreamIO.h"
#include "VideoStream.h"
#include "RTSP.h"
#include "AmebaFatFS.h"
#include "NNObjectDetection.h"
#include "VideoStreamOverlay.h"
#include "ObjectClassList.h"
#include "time.h"

#define CHANNELRTSP 0
#define CHANNELSNAP 1
#define CHANNELNN   3

// Lower resolution for NN processing
#define NNWIDTH  576
#define NNHEIGHT 320

#define ROTATE_NONE                    0
#define ROTATE_90DEG_CLOCKWISE         1
#define ROTATE_90DEG_COUNTER_CLOCKWISE 2
#define ROTATE_VERTICAL_FLIP           3

// Default preset configurations for each video channel:
// Channel 0 : 1920 x 1080 30FPS H264
// Channel 1 : 1280 x 720  30FPS H264
// Channel 2 : 1280 x 720  30FPS MJPEG
VideoSetting config(VIDEO_FHD, 30, VIDEO_H264, 0);
VideoSetting configSNAP(VIDEO_FHD, CAM_FPS, VIDEO_JPEG, 1);
VideoSetting configNN(NNWIDTH, NNHEIGHT, 10, VIDEO_RGB, 0);
RTSP rtsp;
NNObjectDetection ObjDet;
StreamIO videoStreamer(1, 1);
StreamIO videoStreamerNN(1, 1);

uint32_t img_addr = 0;
uint32_t img_len = 0;
AmebaFatFS fs;

time_t now;
struct tm ts;
char buf[80];

int rotate_input = 0;
int currentRotation = 0;

char ssid[] = "Network_SSID";    // your network SSID (name)
char pass[] = "Password";        // your network password
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
    // Adjust the bitrate based on your WiFi network quality
    config.setBitrate(2 * 1024 * 1024);    // Recommend to use 2Mbps for RTSP streaming to prevent network congestion
    Camera.configVideoChannel(CHANNELRTSP, config);
    Camera.configVideoChannel(CHANNELSNAP, configSNAP);
    Camera.configVideoChannel(CHANNELNN, configNN);

    Camera.videoInit();

    // Configure RTSP with identical video format information
    rtsp.configVideo(config);
    rtsp.begin();

    ObjDet.configVideo(configNN);
    ObjDet.modelSelect(OBJECT_DETECTION, DEFAULT_YOLOV4TINY, NA_MODEL, NA_MODEL);
    ObjDet.begin();

    // Configure StreamIO object to stream data from video channel to RTSP
    videoStreamer.registerInput(Camera.getStream(CHANNELRTSP));
    videoStreamer.registerOutput(rtsp);
    if (videoStreamer.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    // Start data stream from video channel
    Camera.channelBegin(CHANNELRTSP);
    Camera.channelBegin(CHANNELSNAP);


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

    // Start OSD drawing on RTSP video channel
    OSD.configVideo(CHANNELRTSP, config);
    OSD.configVideo(CHANNELSNAP, configSNAP);
    OSD.begin();

    delay(1000);
    printInfo();

    pinMode(ROTATE_NONE, INPUT_IRQ_RISE);
    digitalSetIrqHandler(ROTATE_NONE, interruptHandler);

    pinMode(ROTATE_90DEG_CLOCKWISE, INPUT_IRQ_RISE);
    digitalSetIrqHandler(ROTATE_90DEG_CLOCKWISE, interruptHandler);

    pinMode(ROTATE_90DEG_COUNTER_CLOCKWISE, INPUT_IRQ_RISE);
    digitalSetIrqHandler(ROTATE_90DEG_COUNTER_CLOCKWISE, interruptHandler);

    pinMode(ROTATE_VERTICAL_FLIP, INPUT_IRQ_RISE);
    digitalSetIrqHandler(ROTATE_VERTICAL_FLIP, interruptHandler);
}

void loop()
{
    if (rotate_input != currentRotation) {
        rotate_video(rotate_input);
        currentRotation = rotate_input;
    }

    std::vector<ObjectDetectionResult> results = ObjDet.getResult();

    uint16_t im_h = config.height();
    uint16_t im_w = config.width();

    // printf("Total number of objects detected = %d\r\n", ObjDet.getResultCount());
    OSD.createBitmap(CHANNELRTSP);
    OSD.createBitmap(CHANNELSNAP);

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
                OSD.drawRect(CHANNELRTSP, xmin, ymin, xmax, ymax, 3, OSD_COLOR_BLACK);
                OSD.drawRect(CHANNELSNAP, xmin, ymin, xmax, ymax, 3, OSD_COLOR_BLACK);
                // Print identification text
                char text_str[20];
                snprintf(text_str, sizeof(text_str), "%s", itemList[obj_type].objectName);
                time(&now);
                // Format time, "ddd yyyy-mm-dd hh:mm:ss zzz"
                ts = *localtime(&now);
                strftime(buf, sizeof(buf), "%H %M %S %d-%m-%Y ", &ts);
                strcat(buf, text_str);
                strcat(buf, ".jpg");
                captureJPEG(buf);
                OSD.drawText(CHANNELRTSP, xmin, ymin - OSD.getTextHeight(CHANNELRTSP), text_str, OSD_COLOR_CYAN);
                OSD.drawText(CHANNELSNAP, xmin, ymin - OSD.getTextHeight(CHANNELSNAP), text_str, OSD_COLOR_CYAN);
            }
        }
    }
    OSD.update(CHANNELRTSP);
    OSD.update(CHANNELSNAP);

    // delay to wait for new results
    delay(100);
}

void printInfo(void)
{
    Serial.println(" ");
    Serial.println("------------------------------");
    Serial.println("- Summary of Streaming -");
    Serial.println("------------------------------");
    Camera.printInfo();

    IPAddress ip = WiFi.localIP();

    Serial.println("- RTSP -");
    Serial.print("rtsp://");
    Serial.print(ip);
    Serial.print(":");
    rtsp.printInfo();
}

void captureJPEG(String FILENAME)
{
    fs.begin();
    File file = fs.open(String(fs.getRootPath()) + String(FILENAME));

    delay(1000);
    Camera.getImage(CHANNELSNAP, &img_addr, &img_len);
    file.write((uint8_t *)img_addr, img_len);
    file.close();
    fs.end();
}

void interruptHandler(uint32_t id, uint32_t event)
{
    rotate_input = id;
}

void rotate_video(int id)
{
    config.setRotation(id);
    configSNAP.setRotation(id);
    Camera.configVideoChannel(CHANNELRTSP, config);
    Camera.updateVideoParams(CHANNELRTSP);
    Camera.configVideoChannel(CHANNELSNAP, configSNAP);
    Camera.updateVideoParams(CHANNELSNAP);
}
