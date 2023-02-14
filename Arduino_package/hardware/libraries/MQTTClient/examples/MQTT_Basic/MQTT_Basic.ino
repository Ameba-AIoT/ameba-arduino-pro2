#include <WiFi.h>
#include <PubSubClient.h>

char ssid[] = "yourNetwork"; //  your network SSID (name)
char pass[] = "Password";    // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS;

char mqttServer[]     = "test.mosquitto.org";
char clientId[]       = "amebaClient";
char publishTopic[]   = "outTopic";
char publishPayload[] = "hello world";
char subscribeTopic[] = "inTopic";

void callback(char* topic, byte* payload, unsigned int length) {
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

void reconnect() {
    // Loop until we're reconnected
    while (!(client.connected())) {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        if (client.connect(clientId)) {
            Serial.println("connected");
            //Once connected, publish an announcement
            client.publish(publishTopic, publishPayload);
            client.subscribe(subscribeTopic);
        } else {
            Serial.println("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            //Wait 5 seconds before retrying
            delay(5000);
            }
    }
        }

void setup() {
    //Initialize serial and wait for port to open:
    Serial.begin(115200);
    // wait for serial port to connect. Needed for native USB port only
    while (!Serial) {
        ;
    }

    //Attempt to connect to WiFi network
    while (status != WL_CONNECTED) {
        Serial.print("Attempting to connect to SSID: ");
        Serial.println(ssid);
        // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
        status = WiFi.begin(ssid, pass);

        // wait 10 seconds for connection:
        delay(10000);
    }

    client.setServer(mqttServer, 1883);
    client.setCallback(callback);

    //Allow Hardware to sort itself out
    delay(1500);
}

void loop() {
    if (!(client.connected())) {
        reconnect();
    }
    client.loop();
};
