/*

 MQTT Image example

 This sketch demonstrates the image sending capabilities of the library.
  - connects to an MQTT server
  - publishes "hello world" to the topic "outTopic/Msg"
  - subscribes to the topic "inTopic/Msg", printing out any messages it receives. It assumes the received payloads are strings not binary
  - captures image and publish to "outTopic/Img"

 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.

 Example guide: TBD

 */

#include <WiFi.h>
#include <PubSubClient.h>
#include "Base64.h"
#include "VideoStream.h"

VideoSetting config(768, 768, CAM_FPS, VIDEO_JPEG, 1);
#define CHANNEL 0

uint32_t img_addr = 0;
uint32_t img_len = 0;

char ssid[] = "Network_SSID5";    // your network SSID (name)
char pass[] = "Password";         // your network password
int status = WL_IDLE_STATUS;      // Indicator of Wifi status

char mqttServer[] = "mqttgo.io";
char clientId[] = "amebaClient";
char publishTopic[] = "outTopic/Msg";
char publishPayload[] = "hello world";
char subscribeTopic[] = "inTopic/Msg";

void callback(char* topic, byte* payload, unsigned int length)
{
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (unsigned int i = 0; i < length; i++) {
        Serial.print((char)(payload[i]));
    }
    Serial.println();
}

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void reconnect()
{
    // Loop until we're reconnected
    while (!(client.connected())) {
        Serial.print("\r\nAttempting MQTT connection...");
        // Attempt to connect
        if (client.connect(clientId)) {
            Serial.println("connected");
            // Once connected, publish an announcement and resubscribe
            client.publish(publishTopic, publishPayload);
            client.subscribe(subscribeTopic);
        } else {
            Serial.println("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

void setup()
{
    // Initialize serial and wait for port to open:
    Serial.begin(115200);
    // wait for serial port to connect.
    while (!Serial) {
        ;
    }

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
    client.setServer(mqttServer, 1883);
    client.setCallback(callback);

    // Allow Hardware to sort itself out
    delay(1500);
    if (!(client.connected())) {
        reconnect();
    }

    config.setRotation(0);
    Camera.configVideoChannel(CHANNEL, config);
    Camera.videoInit();
    Camera.channelBegin(CHANNEL);
    Camera.printInfo();

    delay(5000);
}

void loop()
{
    client.publish("outTopic/Msg", "hello from AMB82 mini");
    Camera.getImage(0, &img_addr, &img_len);

    int max_packet_size = MQTT_MAX_PACKET_SIZE;

    client.beginPublish("outTopic/Img", img_len, false);

    for (int i = 0; i < (int)img_len; i += max_packet_size) {
        int chunk_size = min(max_packet_size, (int)img_len - i);
        client.write((uint8_t*)img_addr + i, chunk_size);
    }

    bool isPublished = client.endPublish();

    if (isPublished) {
        Serial.println("Publish image to MQTT server successful");
    } else {
        Serial.println("Publish image to MQTT server failed");
    }

    client.loop();
}
