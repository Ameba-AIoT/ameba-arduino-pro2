/*
 Example guide:
 https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/WiFi/Connect%20to%20WiFi.html
*/

#include <WiFi_eap.h>

// UTF-8 encoding can also be used for SSID with emoji characters
// Emoji characters can be converted into UTF-8 at https://mothereff.in/utf-8
// char ssid[] = "\xe2\x9c\x8c\xef\xb8\x8f Ameba \xe2\x9c\x8c\xef\xb8\x8f";

char eap_methord[] = "tls";      // your eap methord "tls", "peap", "ttls"
char ssid[] = "Network_SSID";    // your network SSID (name)
char identity[] = "identity";    // your network identity
char pass[] = "Password";        // your network password
int status = -1;                 // Indicator of connection

const unsigned char client_cert[] = "-----BEGIN CERTIFICATE-----\r\nxxxxxxxxxxxxxxxxxxxxxxxxxxx\r\n-----END CERTIFICATE-----\r\n";

const unsigned char client_key[] = "-----BEGIN PRIVATE KEY-----\r\nxxxxxxxxxxxxxxxxxxxxxxxxxxx\r\n-----END PRIVATE KEY-----\r\n";

const unsigned char ca_cert[] = "-----BEGIN CERTIFICATE-----\r\nxxxxxxxxxxxxxxxxxxxxxxxxxxx\r\n-----END CERTIFICATE-----\r\n";

void setup()
{
    // Initialize serial and wait for port to open:
    Serial.begin(115200);
    while (!Serial) {
        ;    // wait for serial port to connect. Needed for native USB port only
    }

    // attempt to connect to Wifi network:
    while (status != 0) {
        Serial.print("Attempting to connect to WPA2 EAP SSID: ");
        Serial.println(ssid);
        // Connect to WPA2 EAP network:
        status = WiFi_eap.begin(eap_methord, ssid, identity, pass, client_cert, client_key, ca_cert);

        // wait 10 seconds for connection:
        delay(10000);
    }

    // you're connected now, so print out the data:
    Serial.println();
    Serial.print("You're connected to the WPA2 EAP network.");
}

void loop()
{
    delay(10000);
}
