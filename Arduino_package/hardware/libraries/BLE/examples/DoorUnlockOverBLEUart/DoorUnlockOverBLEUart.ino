#include "WiFi.h"
#include "StreamIO.h"
#include "VideoStream.h"
#include <AmebaServo.h>
#include "AmebaFatFS.h"
#include "BLEDevice.h"

// Channel for taking snapshots
#define CHANNELJPEG 0

// Define BLE UUID
#define UART_SERVICE_UUID "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

// BLE Buffer Size
#define STRING_BUF_SIZE 100

// Pin Definition
#define RED_LED    3
#define GREEN_LED  4
#define BUTTON_PIN 5
#define SERVO_PIN  8

VideoSetting configJPEG(VIDEO_FHD, CAM_FPS, VIDEO_JPEG, 1);
AmebaServo myservo;
BLEService UartService(UART_SERVICE_UUID);
BLECharacteristic Rx(CHARACTERISTIC_UUID_RX);
BLECharacteristic Tx(CHARACTERISTIC_UUID_TX);
BLEAdvertData advdata;
BLEAdvertData scndata;
bool notify = false;

int resultSize = 0;
bool doorOpen = false;
bool buttonState = false;
bool systemOn = false;
uint32_t img_addr = 0;
uint32_t img_len = 0;
String fileName;
long counter = 0;

// File Initialization
AmebaFatFS fs;

void setup() {
    // GPIO Initialisation
    pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(BUTTON_PIN, INPUT);
    myservo.attach(SERVO_PIN);

    Serial.begin(115200);
    
    // BLE Setup
    BLE.setDeviceName("AMEBA_BLE");
    advdata.addFlags();
    scndata.addCompleteServices(BLEUUID(UART_SERVICE_UUID));

    Rx.setWriteProperty(true);
    Rx.setWritePermissions(GATT_PERM_WRITE);
    Rx.setWriteCallback(writeCB);
    Rx.setBufferLen(STRING_BUF_SIZE);
    Tx.setReadProperty(true);
    Tx.setReadPermissions(GATT_PERM_READ);
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

    // Configure camera video channels with video format information
    Camera.configVideoChannel(CHANNELJPEG, configJPEG);
    Camera.videoInit();
    Camera.channelBegin(CHANNELJPEG);

    // Start BLE
    BLE.beginPeripheral();
    
    // Servo moves to position the angle 180 degree (LOCK CLOSE)
    myservo.write(180);
}

void loop() {
    buttonState = digitalRead(BUTTON_PIN);
    if ((buttonState == ON) && (systemOn == false)) {  // When button is being pressed, systemOn becomes true
        Tx.writeString("Door Bell Pressed.\n");        // Send notification to connected BLE Device
        if (BLE.connected(0) && notify) {
            Tx.notify(0);
        }
        for (int count = 0; count < 3; count++) {
            digitalWrite(RED_LED, HIGH);
            digitalWrite(GREEN_LED, HIGH);
            delay(500);
            digitalWrite(RED_LED, LOW);
            digitalWrite(GREEN_LED, LOW);
            delay(500);
        }
        systemOn = true;
    } else {
        //Both LED remains on when button not pressed
        systemOn = false;
        digitalWrite(RED_LED, HIGH);
        digitalWrite(GREEN_LED, HIGH);
    }
    
    if (Rx.readString() == String("Open\n")) {
        digitalWrite(RED_LED, LOW);
        digitalWrite(GREEN_LED, HIGH);
        fileName = String("Authorized");  // File name for Authorized Door Opening
        doorOpen = true;
        Rx.writeString("Done\n"); // Write a new string to Rx to prevent Rx.readstring() to keep reading "Open"
    } else if (Rx.readString() == String("Snapshot\n")) { // When BLE Command "Snapshot" being received
        fs.begin();
        File file = fs.open(String(fs.getRootPath()) + "SnapshotTaken" + String(++counter) + ".jpg"); // File name for Snapshot taken
        delay(1000);
        Camera.getImage(CHANNELJPEG, &img_addr, &img_len);
        file.write((uint8_t*)img_addr, img_len);
        file.close();
        fs.end();
        Rx.writeString("Done\n"); // Write a new string to Rx to prevent Rx.readstring() to keep reading "Snapshot"
    }

    // Take snapshot and open door for 10 seconds
    if ((doorOpen == true) && (systemOn == true)) {
        fs.begin();
        File file = fs.open(String(fs.getRootPath()) + fileName + String(++counter) + ".jpg");
        delay(1000);
        Camera.getImage(CHANNELJPEG, &img_addr, &img_len);
        file.write((uint8_t*)img_addr, img_len);
        file.close();
        fs.end();
        myservo.write(0);
        Serial.println("Opening Door!");
        delay(10000);
        myservo.write(180);
        digitalWrite(RED_LED, HIGH);
        digitalWrite(GREEN_LED, LOW);
        doorOpen = false;
    }
}

// Callback function for Rx (Optional)
void writeCB(BLECharacteristic* chr, uint8_t connID) {
    printf("Characteristic %s write by connection %d :\n", chr->getUUID().str(), connID);
    if (chr->getDataLen() > 0) {
        Serial.print("Received string: ");
        Serial.print(chr->readString());
        Serial.println();
    }
}

// Callback function for Tx (Optional)
void notifCB(BLECharacteristic* chr, uint8_t connID, uint16_t cccd) {
    if (cccd & GATT_CLIENT_CHAR_CONFIG_NOTIFY) {
      printf("Notifications enabled on Characteristic %s for connection %d \n", chr->getUUID().str(), connID);
      notify = true;
    } else {
      printf("Notifications disabled on Characteristic %s for connection %d \n", chr->getUUID().str(), connID);
      notify = false;
    }
}
