/*

 MQTT GenAIVision example

 This sketch demonstrates the use of MQTT with Generative AI.
  - connects to an MQTT server
  - publishes "hello from AMB82 Mini" on initialization to the topic "outTopic/Msg"
  - subscribes to the topic "inTopic/Prompt", printing out any messages it receives. It assumes the received payloads are strings not binary, message after "p/" will be taken as a prompt
  - captures image and publish to "outTopic/Img"
  - send image and prompt to Gen AI server for processing
  - collect response from Gen AI server and publish to "outTopic/Rsp"

 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.

 Example guide: https://ameba-arduino-doc.readthedocs.io/en/latest/amebapro2/Example_Guides/MQTT/Generative%20AI%20Vision%20with%20MQTT.html

 */

#include <WiFi.h>
#include <PubSubClient.h>
#include "Base64.h"
#include "VideoStream.h"
#include "NNGenAIVision.h"

WiFiClient wifiClient;
WiFiClient wifiClientR;
WiFiSSLClient sslClient;
PubSubClient client(wifiClient);
PubSubClient rclient(wifiClientR);
NNGenAIVision llm;

VideoSetting config(768, 768, CAM_FPS, VIDEO_JPEG, 1);
#define CHANNEL 0

uint32_t img_addr = 0;
uint32_t img_len = 0;

char ssid[] = "Network_SSID5";    // your network SSID (name)
char pass[] = "Password";         // your network password
int status = WL_IDLE_STATUS;      // Indicator of Wifi status

char mqttServer[] = "mqttgo.io";    // broker.mqttgo.io
char clientId[] = "amebaClient";
char rclientId[] = "amebaClientR";
char publishTopicMsg[] = "outTopic/Msg";
char publishTopicImg[] = "outTopic/Img";
char publishTopicRsp[] = "outTopic/Rsp";
char publishPayload[] = "hello from AMB82 Mini";
char subscribeTopic[] = "inTopic/Prompt";

String openAI_key = "";    // paste your generated openAI API key here
String Gemini_key = "";    // paste your generated Gemini API key here
String Llama_key = "";     // paste your generated Llama API key here

String prompt_msg;

int img_max_packet_size = MQTT_MAX_PACKET_SIZE;
static int flag = 0;

void callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    if ((char)payload[0] == 'p' && (char)payload[1] == '/') {
        for (unsigned int i = 2; i < length; i++) {
            prompt_msg += (char)(payload[i]);
            Serial.print((char)(payload[i]));
        }
        Serial.println();
        flag = 1;
        Serial.println("Command received");
    } else {
        for (unsigned int i = 0; i < length; i++) {
            Serial.print((char)(payload[i]));
        }
        Serial.println();
    }
}

void setup()
{
    // Initialize serial and wait for port to open:
    Serial.begin(115200);

    // Attempt to connect to WiFi network
    while (status != WL_CONNECTED) {
        Serial.print("\r\nAttempting to connect to SSID: ");
        Serial.println(ssid);
        // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
        status = WiFi.begin(ssid, pass);

        // wait 10 seconds for connection:
        delay(10000);
    }

    wifiClient.setNonBlockingMode();
    wifiClientR.setNonBlockingMode();
    client.setServer(mqttServer, 1883);
    rclient.setServer(mqttServer, 1883);
    rclient.setCallback(callback);

    // Allow Hardware to sort itself out
    delay(1500);

    config.setRotation(0);
    Camera.configVideoChannel(CHANNEL, config);
    Camera.videoInit();
    Camera.channelBegin(CHANNEL);
    Camera.printInfo();

    while (!(client.connected())) {
        Serial.print("\r\nAttempting MQTT connection...");
        // Attempt to connect
        if (client.connect(clientId)) {
            Serial.println("connected");
            // Once connected, publish an announcement
            client.publish(publishTopicMsg, publishPayload);
        } else {
            Serial.println("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }

    while (!(rclient.connected())) {
        Serial.print("\r\nAttempting MQTT connection...");
        // Attempt to connect
        if (rclient.connect(rclientId)) {
            Serial.println("connected");
            // Once connected, subscribe to listen
            rclient.subscribe(subscribeTopic);
        } else {
            Serial.println("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }

    if (xTaskCreate(thread1_task, (const char *)"thread1_task", 1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS) {
        printf("\n\r[%s] Create task 1 failed", __FUNCTION__);
    };
    if (xTaskCreate(thread2_task, (const char *)"thread2_task", 1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS) {
        printf("\n\r[%s] Create task 2 failed", __FUNCTION__);
    };
}

void loop()
{
    // do nothing
}

void thread1_task(void *param)
{
    (void)param;
    while (1) {
        while (!(client.connected())) {
            Serial.print("\r\nAttempting MQTT connection...");
            // Attempt to connect
            if (client.connect(clientId)) {
                Serial.println("connected");
                // Once connected, publish an announcement
                client.publish(publishTopicMsg, publishPayload);
            } else {
                Serial.println("failed, rc=");
                Serial.print(client.state());
                Serial.println(" try again in 5 seconds");
                // Wait 5 seconds before retrying
                delay(5000);
            }
        }
        while (!(rclient.connected())) {
            Serial.print("\r\nAttempting MQTT connection...");
            // Attempt to connect
            if (rclient.connect(rclientId)) {
                Serial.println("connected");
                // Once connected, subscribe to listen
                rclient.subscribe(subscribeTopic);
            } else {
                Serial.println("failed, rc=");
                Serial.print(rclient.state());
                Serial.println(" try again in 5 seconds");
                // Wait 5 seconds before retrying
                delay(5000);
            }
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        rclient.loop();
    }
}

void thread2_task(void *param)
{
    (void)param;
    while (1) {
        if (flag == 1) {
            Serial.println("taking pic...");
            Camera.getImage(0, &img_addr, &img_len);

            // AI vision prompt
            // openAI vision prompt
            // String response = llm.openaivision(openAI_key, prompt_msg, img_addr, img_len, client);

            // Gemini vision prompt
            String response = llm.geminivision(Gemini_key, prompt_msg, img_addr, img_len, sslClient);

            // Llama vision prompt
            // llm.llamavision(Llama_key, prompt_msg, img_addr, img_len, client);

            const char *c_resp = response.c_str();

            // publish image
            Serial.println("publishing pic...");
            client.beginPublish(publishTopicImg, img_len, false);

            for (int i = 0; i < (int)img_len; i += img_max_packet_size) {
                int chunk_size = min(img_max_packet_size, (int)img_len - i);
                client.write((uint8_t *)img_addr + i, chunk_size);
            }
            delay(2000);
            bool isPublished = client.endPublish();
            if (isPublished) {
                Serial.println("Publish image to MQTT server successful");
            } else {
                Serial.println("Publish image to MQTT server failed");
            }

            vTaskDelay(2000 / portTICK_PERIOD_MS);
            client.loop();

            // publish response
            Serial.println("publishing response...");
            client.beginPublish(publishTopicRsp, response.length(), false);

            for (int i = 0; i < (int)response.length(); i++) {
                Serial.print(response[i]);
                client.write((uint8_t)response[i]);
                vTaskDelay(10 / portTICK_PERIOD_MS);
            }
            Serial.println();
            if (client.endPublish()) {
                Serial.println("Publish response to MQTT server successful");
            } else {
                Serial.println("Publish response failed");
            }
            flag = 0;
        }
        vTaskDelay(2000 / portTICK_PERIOD_MS);
        client.loop();
    }
}
