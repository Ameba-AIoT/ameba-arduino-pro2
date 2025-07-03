/*
 MQTT Publishing in the callback
  - connects to an MQTT server, providing username and password
  - subscribes to the topic "inTopic"
  - when a message is received, republishes it to "outTopic"

  This example shows how to publish messages within the
  callback function. The callback function header needs to
  be declared before the PubSubClient constructor and the
  actual callback defined afterwards.
  This ensures the client reference in the callback function
  is valid.

 Example guide:
 https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/MQTT/Set%20up%20MQTT%20Client-Broker%20Authenticated%20Connection%20with%20Publish%20in%20Callback.html
*/

#include <WiFi.h>
#include <PubSubClient.h>

char ssid[] = "Network_SSID";    // your network SSID (name)
char pass[] = "Password";        // your network password
int status = WL_IDLE_STATUS;     // Indicator of Wifi status

char clientIdBackup[32];

char mqttServer[] = "cloud.amebaiot.com";
char clientId[] = "amebaClient";
char clientUser[] = "testuser";
char clientPass[] = "testpass";
char publishTopic[] = "outTopic";
char publishPayload[] = "hello world";
char subscribeTopic[] = "inTopic";

void callback(char* topic, byte* payload, unsigned int length);

WiFiClient wifiClient;
PubSubClient client(mqttServer, 1883, callback, wifiClient);

// Callback function
void callback(char* topic, byte* payload, unsigned int length)
{
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    Serial.println();

    // In order to republish this payload, a copy must be made
    // as the original payload buffer will be overwritten whilst
    // constructing the PUBLISH packet.

    // Allocate the correct amount of memory for the payload copy
    byte* p = (byte*)(malloc(length));
    // Copy the payload to the new buffer
    memcpy(p, payload, length);
    client.publish(publishTopic, p, length);
    // Free the memory
    free(p);
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
    if (client.connect(clientId, clientUser, clientPass)) {
        Serial.print("Client ID: ");
        Serial.println(clientId);
        client.publish(publishTopic, publishPayload, false);
        client.subscribe(subscribeTopic);
    } else {
        sprintf(clientIdBackup, "amebaClient-%lu", millis());
        if (client.connect(clientIdBackup, clientUser, clientPass)) {
            Serial.println("Static ID unable to use. Generate unique ID...");
            Serial.print("Client ID: ");
            Serial.println(clientIdBackup);
            client.publish(publishTopic, publishPayload, false);
            client.subscribe(subscribeTopic);
        }
    }
}

void loop()
{
    client.loop();
}
