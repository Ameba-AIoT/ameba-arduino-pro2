/*******************************************************
 * BLEV7RC_CAR_VIDEO.ino - BLE Remote Control Car Arduino Code
 *
 * Author: Kevin Chen
 * Date: 2023/8/15
 *
 * Version: 1.0.0
 *
 * This code was written by Kevin Chen.
 *
 * This is an open-source program, and it can be freely used, modified, and distributed under the following conditions:
 *
 * 1. The original copyright notice must not be removed or modified.
 * 2. Projects or products using this code must acknowledge the original author's name and the source in applicable documentation, websites, or other related materials.
 * 3. Any derivative work based on this code must state its origin and retain the original copyright notice in its documentation.
 * 4. This code must not be used for any activities that may infringe upon the rights of others, be unlawful, or harmful, whether in a commercial or non-commercial environment.
 *
 * This code is provided "as is" with no warranty, expressed or implied. The author is not liable for any losses or damages caused by using the code.
 *
 * Users of BLEV7RC_CAR_VIDEO.ino assume all risks associated with its use, and the author shall not be held responsible for any consequences.
 *
 * For more information about our company, please visit: www.makdev.net
 *
 * Example guide:
 * https://www.amebaiot.com/en/amebapro2-arduino-ble-v7rc/
 *******************************************************/

#include "BLEDevice.h"
#include "WiFi.h"
#include "StreamIO.h"
#include "VideoStream.h"
#include "RTSP.h"

#define UART_SERVICE_UUID      "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

#define STRING_BUF_SIZE 100
#define MaxNumValue     2

#define value1 0
#define value2 1

#define MotoA_1A 16    // GPIO
#define MotoA_1B 7     // PWM
#define MotoB_1A 17    // GPIO
#define MotoB_1B 8     // PWM

#define CHANNEL 1

// Default preset configurations for each video channel:
// Channel 0 : 1920 x 1080 30FPS H264
// Channel 1 : 1280 x 720  30FPS H264
// Channel 2 : 1920 x 1080 30FPS MJPEG

// VideoSetting config(CHANNEL);
VideoSetting config(VIDEO_D1, CAM_FPS, VIDEO_H264, 0);
RTSP rtsp1;
RTSP rtsp2;
StreamIO videoStreamer(1, 2);    // 1 Input Video -> 1 Output RTSP

char ssid[] = "Network_SSID";    // your network SSID (name)
char pass[] = "Password";        // your network password
int status = WL_IDLE_STATUS;

typedef struct {
    bool reciveCMDFlag;
    int ReciveValue;
} _rCMD;

BLEService UartService(UART_SERVICE_UUID);
BLECharacteristic Rx(CHARACTERISTIC_UUID_RX);
BLECharacteristic Tx(CHARACTERISTIC_UUID_TX);
BLEAdvertData advdata;
BLEAdvertData scndata;
bool notify = false;
uint8_t Count;

String CMDRefer[5] = {"SS2", "SS4", "SRT", "SR2", "SRV"};
_rCMD bleReciveData[MaxNumValue];

void forward()
{
    digitalWrite(MotoA_1A, 1);
    analogWrite(MotoA_1B, 5);

    digitalWrite(MotoB_1A, 1);
    analogWrite(MotoB_1B, 5);

    delay(50);
}

void backward()
{
    digitalWrite(MotoA_1A, 0);
    analogWrite(MotoA_1B, 250);

    digitalWrite(MotoB_1A, 0);
    analogWrite(MotoB_1B, 250);

    delay(50);
}

void turnRight()
{
    digitalWrite(MotoA_1A, 1);
    analogWrite(MotoA_1B, 5);

    digitalWrite(MotoB_1A, 0);
    analogWrite(MotoB_1B, 250);

    delay(50);
}

void turnLeft()
{
    digitalWrite(MotoA_1A, 0);
    analogWrite(MotoA_1B, 250);

    digitalWrite(MotoB_1A, 1);
    analogWrite(MotoB_1B, 5);

    delay(50);
}

void BrakeAll()
{
    digitalWrite(MotoA_1A, 0);
    analogWrite(MotoA_1B, 0);

    digitalWrite(MotoB_1A, 0);
    analogWrite(MotoB_1B, 0);

    delay(50);
}

void readCB(BLECharacteristic* chr, uint8_t connID)
{
    printf("Characteristic %s read by connection %d \n", chr->getUUID().str(), connID);
}

void writeCB(BLECharacteristic* chr, uint8_t connID)
{
    // printf("Characteristic %s write by connection %d :\n", chr->getUUID().str(), connID);
    if (chr->getDataLen() > 0) {
        ParseCMDString(chr->readString());
        // Serial.print("Received string: ");
        // Serial.print(chr->readString());
        // Serial.println();
    }
}

void notifCB(BLECharacteristic* chr, uint8_t connID, uint16_t cccd)
{
    if (cccd & GATT_CLIENT_CHAR_CONFIG_NOTIFY) {
        printf("Notifications enabled on Characteristic %s for connection %d \n", chr->getUUID().str(), connID);
        notify = true;
    } else {
        printf("Notifications disabled on Characteristic %s for connection %d \n", chr->getUUID().str(), connID);
        notify = false;
    }
}

void ParseCMDString(String cmd)
{
    int comdLength = cmd.length();
    int chkx;
    int CMDMaxNUM = sizeof(CMDRefer) / sizeof(String);

    for (chkx = 0; chkx < CMDMaxNUM; chkx++) {
        if (cmd.indexOf(CMDRefer[chkx].c_str()) > -1) {
            break;
        }
    }

    if (chkx >= CMDMaxNUM && cmd.charAt(comdLength - 1) != '#') {
        return;
    }

    if (cmd.indexOf("SRT") > -1) {
        int x = 3;
        int ValueIndex = 0;

        while (x < (comdLength - 1)) {
            if ((x + 3) < comdLength) {
                String _NumString = cmd.substring(x, (x + 4));
                // Serial.println(_NumString);
                if (ValueIndex < MaxNumValue) {
                    if (bleReciveData[ValueIndex].ReciveValue != _NumString.toInt()) {
                        bleReciveData[ValueIndex].ReciveValue = _NumString.toInt();
                        bleReciveData[ValueIndex].reciveCMDFlag = true;
                    }
                }
            }
            ValueIndex++;
            x += 4;
        }
    }
}

void printInfo(void)
{
    Serial.println("------------------------------");
    Serial.println("- Summary of Streaming -");
    Serial.println("------------------------------");
    Camera.printInfo();

    IPAddress ip = WiFi.localIP();

    Serial.println("- RTSP -");
    Serial.print("rtsp://");
    Serial.print(ip);
    Serial.print(":");
    rtsp1.printInfo();

    Serial.print("rtsp://");
    Serial.print(ip);
    Serial.print(":");
    rtsp2.printInfo();
}

void setup()
{
    Serial.begin(115200);

    advdata.addFlags(GAP_ADTYPE_FLAGS_LIMITED | GAP_ADTYPE_FLAGS_BREDR_NOT_SUPPORTED);
    advdata.addCompleteName("AMB82-TANK");
    scndata.addCompleteServices(BLEUUID(UART_SERVICE_UUID));

    Rx.setWriteNRProperty(true);
    Rx.setWritePermissions(GATT_PERM_WRITE);
    Rx.setWriteCallback(writeCB);
    Rx.setBufferLen(STRING_BUF_SIZE);

    Tx.setReadProperty(true);
    Tx.setReadPermissions(GATT_PERM_READ);
    Tx.setReadCallback(readCB);
    Tx.setNotifyProperty(true);
    Tx.setCCCDCallback(notifCB);
    Tx.setBufferLen(STRING_BUF_SIZE);

    UartService.addCharacteristic(Rx);
    UartService.addCharacteristic(Tx);

    BLE.init();
    BLE.configAdvert()->setAdvData(advdata);
    BLE.configAdvert()->setScanRspData(scndata);
    BLE.configServer(1);
    BLE.addService(UartService);

    BLE.beginPeripheral();

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
    Camera.videoInit();

    // Configure RTSP with identical video format information
    rtsp1.configVideo(config);
    rtsp1.begin();
    rtsp2.configVideo(config);
    rtsp2.begin();

    // Configure StreamIO object to stream data from video channel to RTSP
    videoStreamer.registerInput(Camera.getStream(CHANNEL));
    videoStreamer.registerOutput1(rtsp1);
    videoStreamer.registerOutput2(rtsp2);
    if (videoStreamer.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    // Start data stream from video channel
    Camera.channelBegin(CHANNEL);

    delay(1000);
    printInfo();

    pinMode(MotoA_1A, OUTPUT);
    pinMode(MotoA_1B, OUTPUT);
    pinMode(MotoB_1A, OUTPUT);
    pinMode(MotoB_1B, OUTPUT);

    digitalWrite(MotoA_1A, 0);
    digitalWrite(MotoA_1B, 0);
    digitalWrite(MotoB_1A, 0);
    digitalWrite(MotoB_1B, 0);
}

void loop()
{
    while (Count < MaxNumValue) {
        if (bleReciveData[Count].reciveCMDFlag) {
            bleReciveData[Count].reciveCMDFlag = false;

            if (abs(bleReciveData[value1].ReciveValue - 1500) < 100 && abs(bleReciveData[value2].ReciveValue - 1500) < 100) {
                BrakeAll();
            } else if (abs(bleReciveData[value1].ReciveValue - 1500) > abs(bleReciveData[value2].ReciveValue - 1500)) {
                if (bleReciveData[value1].ReciveValue > 1500) {
                    turnRight();
                } else {
                    turnLeft();
                }
            } else {
                if (bleReciveData[value2].ReciveValue > 1500) {
                    forward();
                } else {
                    backward();
                }
            }
        }
        Count++;
    }
    Count = 0;
    delay(1);
}
