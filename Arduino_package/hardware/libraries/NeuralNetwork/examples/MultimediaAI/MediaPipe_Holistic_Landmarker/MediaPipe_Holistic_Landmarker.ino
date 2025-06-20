/*

This example shows the application of MediaPipe Holistic Landmarker on HTTP JPEG stream

 Example guide:
 https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/Neural%20Network/Multimedia%20AI/MediaPipe%20Holistic%20Landmarker.html

Credit : ChungYi Fu (Kaohsiung, Taiwan)

*/

#include <WiFi.h>
WiFiSSLClient client;

#include "VideoStream.h"
VideoSetting config(VIDEO_VGA, CAM_FPS, VIDEO_JPEG, 1);

char ssid[] = "Network_SSID";
char pass[] = "Password";
char ssid_ap[] = "AP_Network_SSID";
char pass_ap[] = "AP_Password";
char channel_ap[] = "2";

uint32_t img_addr = 0;
uint32_t img_len = 0;

WiFiServer server(80);
WiFiServer server81(81);

#include "Base64.h"

String Feedback = "", bleData = "", Command = "", cmd = "", p1 = "", p2 = "", p3 = "", p4 = "", p5 = "", p6 = "", p7 = "", p8 = "", p9 = "";
byte receiveState = 0, cmdState = 1, pState = 1, questionState = 0, equalState = 0, semicolonState = 0;

void executeCommand()
{
    if (cmd == "ip") {
        IPAddress ip = WiFi.localIP();
        Feedback = String(ip[0]) + "." + String(ip[1]) + "." + String(ip[2]) + "." + String(ip[3]);
    } else if (cmd == "mac") {
        byte mac[6];
        WiFi.macAddress(mac);
        Feedback = "STA MAC: " + String(mac[0], HEX) + ":" + String(mac[1], HEX) + ":" + String(mac[2], HEX) + ":" + String(mac[3], HEX) + ":" + String(mac[4], HEX) + ":" + String(mac[5], HEX);
    } else if (cmd == "digitalwrite") {
        pinMode(p1.toInt(), OUTPUT);
        digitalWrite(p1.toInt(), p2.toInt());
    } else if (cmd == "digitalread") {
        Feedback = String(digitalRead(p1.toInt()));
    } else if (cmd == "analogwrite") {
        pinMode(p1.toInt(), OUTPUT);
        analogWrite(p1.toInt(), p2.toInt());
    } else if (cmd == "analogread") {
        Feedback = String(analogRead(p1.toInt()));
    } else if (cmd == "resetwifi") {
        for (int i = 0; i < 2; i++) {
            WiFi.begin(const_cast<char *>(p1.c_str()), const_cast<char *>(p2.c_str()));
            Serial.print("Connecting to ");
            Serial.println(p1);
            long int StartTime = millis();
            while (WiFi.status() != WL_CONNECTED) {
                delay(500);
                if ((StartTime + 5000) < (long int)millis()) {
                    break;
                }
            }
            Serial.println("");
            IPAddress ip = WiFi.localIP();
            Feedback = String(ip[0]) + "." + String(ip[1]) + "." + String(ip[2]) + "." + String(ip[3]) + " port: 80, 81";
        }
    } else if (cmd == "print") {
        Serial.print(p1);
    } else if (cmd == "println") {
        Serial.println(p1);
    } else if (cmd == "delay") {
        delay(p1.toInt());
    } else {
        if (cmd == String("message")) {
            Serial.println("Posture detected!");
        } else {
            Feedback = String("Command is not defined.");
        }
    }
}

String Ip2String(IPAddress ip)
{
    return String(ip[0]) + String(".") + String(ip[1]) + String(".") + String(ip[2]) + String(".") + String(ip[3]);
}

void initWiFi()
{
    for (int i = 0; i < 2; i++) {
        if (String(ssid) == "") {
            break;
        }
        WiFi.begin(ssid, pass);

        delay(1000);
        Serial.println("");
        Serial.print("Connecting to ");
        Serial.println(ssid);

        long int StartTime = millis();
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            if ((StartTime + 5000) < (long int)millis()) {
                break;
            }
        }

        if (WiFi.status() == WL_CONNECTED) {
            Serial.println("");
            Serial.print("Main Page IP: http://");
            Serial.println(WiFi.localIP());
            Serial.print("Stream Only IP: http://");
            Serial.print(WiFi.localIP());
            Serial.println(":81");
            break;
        }
    }
    if (String(ssid_ap) != "" && WiFi.status() != WL_CONNECTED) {
        WiFi.apbegin(ssid_ap, pass_ap, channel_ap, 0);
    }
    Serial.println("");
    config.setRotation(0);
    Camera.configVideoChannel(0, config);
    Camera.videoInit();
    Camera.channelBegin(0);
    server.begin();
    server81.begin();
}

void getRequest(void *param)
{
    (void)param;
    while (1) {
        Command = "";
        cmd = "";
        p1 = "";
        p2 = "";
        p3 = "";
        p4 = "";
        p5 = "";
        p6 = "";
        p7 = "";
        p8 = "";
        p9 = "";
        receiveState = 0, cmdState = 1, pState = 1, questionState = 0, equalState = 0, semicolonState = 0;

        WiFiClient client = server.available();

        if (client) {
            String currentLine = "";

            while (client.connected()) {
                if (client.available()) {
                    char c = client.read();

                    getCommand(c);

                    if (c == '\n') {
                        if (currentLine.length() == 0) {
                            client.println("HTTP/1.1 200 OK");
                            client.println("Access-Control-Allow-Headers: Origin, X-Requested-With, Content-Type, Accept");
                            client.println("Access-Control-Allow-Methods: GET,POST,PUT,DELETE,OPTIONS");
                            client.println("Content-Type: text/html; charset=utf-8");
                            client.println("Access-Control-Allow-Origin: *");
                            client.println("X-Content-Type-Options: nosniff");
                            client.println("Cache-Control: no-cache");
                            client.println("Connection: close");
                            client.println();
                            if (Feedback == "") {
                                Feedback = "<!DOCTYPE html><head><meta charset='utf-8'><meta name='viewport' content='width=device-width, initial-scale=1'><script src='https://ajax.googleapis.com/ajax/libs/jquery/1.8.0/jquery.min.js'></script><script src='https://fustyles.github.io/webduino/holistic_20201012/holistic.js'></script><script src='https://fustyles.github.io/webduino/holistic_20201012/holistic_esp32cam_stream.js'></script><script src='https://fustyles.github.io/webduino/GameElements_20190131/gameelements.js'></script><script src='https://cdn.jsdelivr.net/npm/@mediapipe/holistic@0.4/holistic.js' crossorigin='anonymous'></script></head><body><script>const delay=(seconds)=>{return new Promise((resolve)=>{setTimeout(resolve,seconds*1000);});};const main=async()=>{holistic_video('block','1','1','1','1','1','1');  holistic_video('block','1','1','1','1','1','1');  console.log('Raise your left hand and tilt it 45 degree while putting your right hand in front of your chest and look for the surprise message showed in the serial monitor connected to your board');  var _E5_B7_A6_E6_89_8B_E8_85_95x;  var _E5_B7_A6_E6_89_8B_E8_85_95y;  var _E5_8F_B3_E6_89_8B_E8_85_95x;  var _E5_8F_B3_E6_89_8B_E8_85_95y;  var _E9_BC_BB_E5_AD_90x;  var _E9_BC_BB_E5_AD_90y;  var _E5_8F_B3_E8_82_A9_E8_86_80x;  var _E5_8F_B3_E8_82_A9_E8_86_80y;  var _E5_B7_A6_E8_82_A9_E8_86_80x;  var _E5_B7_A6_E8_82_A9_E8_86_80y;  var _E5_85_A9_E6_89_8B_E8_85_95_E9_80_A3_E7_B7_9A_E8_A7_92_E5_BA_A6; recognitionFinish = async function() {holistic_state(0);  _E5_B7_A6_E6_89_8B_E8_85_95x = holistic_pose_position('15','x');  _E5_B7_A6_E6_89_8B_E8_85_95y = holistic_pose_position('15','y');  _E5_8F_B3_E6_89_8B_E8_85_95x = holistic_pose_position('16','x');  _E5_8F_B3_E6_89_8B_E8_85_95y = holistic_pose_position('16','y');  _E9_BC_BB_E5_AD_90x = holistic_pose_position('0','x');  _E9_BC_BB_E5_AD_90y = holistic_pose_position('0','y');  _E5_8F_B3_E8_82_A9_E8_86_80x = holistic_pose_position('12','x');  _E5_8F_B3_E8_82_A9_E8_86_80y = holistic_pose_position('12','y');  _E5_B7_A6_E8_82_A9_E8_86_80x = holistic_pose_position('11','x');  _E5_B7_A6_E8_82_A9_E8_86_80y = holistic_pose_position('11','y');  _E5_85_A9_E6_89_8B_E8_85_95_E9_80_A3_E7_B7_9A_E8_A7_92_E5_BA_A6 = holistic_angle(_E5_B7_A6_E6_89_8B_E8_85_95x,_E5_B7_A6_E6_89_8B_E8_85_95y,_E5_8F_B3_E6_89_8B_E8_85_95y,_E5_8F_B3_E6_89_8B_E8_85_95x);  if (_E5_85_A9_E6_89_8B_E8_85_95_E9_80_A3_E7_B7_9A_E8_A7_92_E5_BA_A6) {    if (_E5_85_A9_E6_89_8B_E8_85_95_E9_80_A3_E7_B7_9A_E8_A7_92_E5_BA_A6 <= 60 && _E5_85_A9_E6_89_8B_E8_85_95_E9_80_A3_E7_B7_9A_E8_A7_92_E5_BA_A6 >= 20 && _E5_B7_A6_E6_89_8B_E8_85_95x > _E9_BC_BB_E5_AD_90x && _E5_B7_A6_E6_89_8B_E8_85_95y > _E9_BC_BB_E5_AD_90y && _E5_8F_B3_E6_89_8B_E8_85_95x < _E9_BC_BB_E5_AD_90x && _E5_8F_B3_E6_89_8B_E8_85_95y < _E9_BC_BB_E5_AD_90y && (_E5_B7_A6_E6_89_8B_E8_85_95y - _E5_B7_A6_E8_82_A9_E8_86_80y) / (_E5_B7_A6_E8_82_A9_E8_86_80y - _E9_BC_BB_E5_AD_90y) >= -0.5 && (_E5_B7_A6_E6_89_8B_E8_85_95y - _E5_B7_A6_E8_82_A9_E8_86_80y) / (_E5_B7_A6_E8_82_A9_E8_86_80y - _E9_BC_BB_E5_AD_90y) <= 1) {      var fetchData_;      fetch(('?'+String('message')))      .then(function (response) {          return response.text();      })      .then(function (data) {          fetchData_=data;              })      .catch(      (error) => {          console.log(`Error: ${error}`);      }      );}  }holistic_state(1);}};main();</script></body></html>";
                            }
                            for (unsigned int index = 0; index < Feedback.length(); index = index + 1024) {
                                client.print(Feedback.substring(index, index + 1024));
                            }
                            Feedback = "";
                            break;
                        } else {
                            currentLine = "";
                        }
                    } else if (c != '\r') {
                        currentLine += c;
                    }

                    if ((currentLine.indexOf("/?") != -1) && (currentLine.indexOf(" HTTP") != -1)) {
                        if (Command.indexOf("stop") != -1) {
                            client.println();
                            client.println();
                            client.stop();
                        }
                        currentLine = "";
                        Feedback = "";
                        executeCommand();
                    }
                }
            }
            delay(1);
            client.stop();
        }
    }
}

void getCommand(char c)
{
    if (c == '?') {
        receiveState = 1;
    }
    if ((c == ' ') || (c == '\r') || (c == '\n')) {
        receiveState = 0;
    }

    if (receiveState == 1) {
        Command = Command + String(c);

        if (c == '=') {
            cmdState = 0;
        }
        if (c == ';') {
            pState++;
        }

        if ((cmdState == 1) && ((c != '?') || (questionState == 1))) {
            cmd = cmd + String(c);
        }
        if ((cmdState == 0) && (pState == 1) && ((c != '=') || (equalState == 1))) {
            p1 = p1 + String(c);
        }
        if ((cmdState == 0) && (pState == 2) && (c != ';')) {
            p2 = p2 + String(c);
        }
        if ((cmdState == 0) && (pState == 3) && (c != ';')) {
            p3 = p3 + String(c);
        }
        if ((cmdState == 0) && (pState == 4) && (c != ';')) {
            p4 = p4 + String(c);
        }
        if ((cmdState == 0) && (pState == 5) && (c != ';')) {
            p5 = p5 + String(c);
        }
        if ((cmdState == 0) && (pState == 6) && (c != ';')) {
            p6 = p6 + String(c);
        }
        if ((cmdState == 0) && (pState == 7) && (c != ';')) {
            p7 = p7 + String(c);
        }
        if ((cmdState == 0) && (pState == 8) && (c != ';')) {
            p8 = p8 + String(c);
        }
        if ((cmdState == 0) && (pState >= 9) && ((c != ';') || (semicolonState == 1))) {
            p9 = p9 + String(c);
        }

        if (c == '?') {
            questionState = 1;
        }
        if (c == '=') {
            equalState = 1;
        }
        if ((pState >= 9) && (c == ';')) {
            semicolonState = 1;
        }
    }
}

void getRequest81(void *param)
{
    (void)param;
    while (1) {
        WiFiClient client81 = server81.available();

        if (client81) {
            String currentLine = "";

            while (client81.connected()) {
                if (client81.available()) {
                    char c = client81.read();
                    if (c == '\n') {
                        if (currentLine.length() == 0) {
                            String head = "--Taiwan\r\nContent-Type: image/jpeg\r\n\r\n";
                            client81.println("HTTP/1.1 200 OK");
                            client81.println("Access-Control-Allow-Origin: *");
                            client81.println("Connection: keep-alive");
                            client81.println("Content-Type: multipart/x-mixed-replace; boundary=Taiwan");
                            client81.println();
                            while (client81.connected()) {
                                Camera.getImage(0, &img_addr, &img_len);
                                uint8_t *fbBuf = (uint8_t *)img_addr;
                                size_t fbLen = img_len;
                                client81.print(head);
                                for (size_t n = 0; n < fbLen; n = n + 1024) {
                                    if (n + 1024 < fbLen) {
                                        client81.write(fbBuf, 1024);
                                        fbBuf += 1024;
                                    } else if (fbLen % 1024 > 0) {
                                        size_t remainder = fbLen % 1024;
                                        client81.write(fbBuf, remainder);
                                    }
                                }
                                client81.print("\r\n");
                            }
                            break;
                        } else {
                            currentLine = "";
                        }
                    } else if (c != '\r') {
                        currentLine += c;
                    }

                    if (currentLine.indexOf(" HTTP") != -1) {
                        currentLine = "";
                    }
                }
            }
            delay(1);
            client81.stop();
        }
    }
}

void setup()
{
    Serial.begin(115200);
    delay(10);
    initWiFi();

    if (xTaskCreate(getRequest, (const char *)"getRequest", 1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS) {
        Serial.println("Create getRequest task failed");
    }
    if (xTaskCreate(getRequest81, (const char *)"getRequest81", 1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS) {
        Serial.println("Create getRequest81 task failed");
    }
}

void loop()
{
}
