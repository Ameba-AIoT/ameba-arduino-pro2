/*
 Example guide:
 https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/NTP/Retrieve%20Universal%20Time%20%28UTC%29%20by%20NTPClient%20library.html
*/

#include <NTPClient.h>
#include <WiFi.h>
#include <WiFiUdp.h>

char ssid[] = "Network_SSID";
char pass[] = "Password";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void setup()
{
    Serial.begin(115200);

    WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    timeClient.begin();
}

void loop()
{
    timeClient.update();

    Serial.println(timeClient.getFormattedTime());

    delay(1000);
}
