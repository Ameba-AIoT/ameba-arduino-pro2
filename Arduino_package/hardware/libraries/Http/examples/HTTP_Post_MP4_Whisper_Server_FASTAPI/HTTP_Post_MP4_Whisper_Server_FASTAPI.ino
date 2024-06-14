/*
Example guide:
TBD
*/

#include <Arduino.h>
#include "WiFi.h"
#include "AmebaFatFS.h"
#include "Base64.h"
#include "ArduinoJson.h"

#define FILENAME "TestRecordingAudioOnly.mp4"

char ssid[] = "Network_SSID";    // your network SSID (name)
char pass[] = "Password";        // your network password
int status = WL_IDLE_STATUS;

char server[] = "192.168.3.4";    // your server IP running HTTP server on PC

AmebaFatFS fs;
WiFiClient wifiClient;

char buf[512];
char *p;

void setup()
{
    Serial.begin(115200);

    // Connection to internet
    while (status != WL_CONNECTED) {
        Serial.print("Attempting to connect to WPA SSID: ");
        Serial.println(ssid);
        status = WiFi.begin(ssid, pass);
        delay(2000);
    }

    // list files under root directory
    fs.begin();

    memset(buf, 0, sizeof(buf));
    fs.readDir(fs.getRootPath(), buf, sizeof(buf));
    String filepath = String(fs.getRootPath()) + String(FILENAME);
    /* the filenames are separated with '\0', so we scan one by one */
    p = buf;
    while (strlen(p) > 0) {
        /* list out file name image will be saved as "TestRecordingAudioOnly.mp4"*/
        if (strstr(p, FILENAME) != NULL) {
            Serial.println("[INFO] Found 'TestRecordingAudioOnly.mp4' in the string.");
            Serial.println("[INFO] Processing file...");
        } else {
            // Serial.println("Substring 'image.jpg' not found in the
            // string.");
        }
        p += strlen(p) + 1;
    }

    uint8_t *fileinput;
    File file = fs.open(filepath);
    unsigned int fileSize = file.size();
    fileinput = (uint8_t *)malloc(fileSize + 1);
    file.read(fileinput, fileSize);
    fileinput[fileSize] = '\0';
    file.close();
    fs.end();

    // Encode the file data as Base64
    int encodedLen = base64_enc_len(fileSize);
    char *encodedData = (char *)malloc(encodedLen);
    base64_encode(encodedData, (char *)fileinput, fileSize);

    JsonDocument doc;

    doc["base64_string"] = encodedData;

    String jsonString;

    serializeJson(doc, jsonString);

    // Serial.println(jsonString);

    if (wifiClient.connect(server, 8000)) {
        wifiClient.println("POST /audio HTTP/1.1");
        wifiClient.println("Host: " + String(server));
        wifiClient.println("Content-Type: application/json");                    // Use appropriate content type
        wifiClient.println("Content-Length: " + String(jsonString.length()));    // Specify the length of the content
        wifiClient.println("Connection: keep-alive");
        wifiClient.println();            // Empty line indicates the end of headers
        wifiClient.print(jsonString);    // Send the Base64 encoded audio data directly
        Serial.println("Binary sent");
    }
}

void loop()
{
    // if there are incoming bytes available
    // from the server, read them and print them:
    while (wifiClient.available()) {
        char c = wifiClient.read();
        Serial.write(c);
    }

    // if the server's disconnected, stop the client:
    if (!wifiClient.connected()) {
        Serial.println();
        Serial.println("disconnecting from server.");
        wifiClient.stop();

        // do nothing forevermore:
        while (true)
            ;
    }
}
