/*

 Example guide: https://www.amebaiot.com/en/amebapro2-arduino-ntpclient/
 */

#include <NTPClient.h>
#include <WiFi.h>
#include <WiFiUdp.h>

char ssid[] = "Network_SSID";
char pass[] = "Password";

WiFiUDP ntpUDP;

// You can specify the time server pool and the offset (in seconds, can be
// changed later with setTimeOffset() ). Additionally you can specify the
// update interval (in milliseconds, can be changed using setUpdateInterval() ).
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);

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
