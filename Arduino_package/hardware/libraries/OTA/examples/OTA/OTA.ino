/*
 Example guide:
 https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/OTA/Ameba%20Over-the-Air%20Firmware%20Update.html

 This example supports both HTTP and HTTPS OTA.
 - HTTP:  Use port 3000 (default), no certificate needed on server
 - HTTPS: Use port 443, run setup-https.sh on server side

 Server setup: cd ameba-OTA-UI && bash setup-https.sh
*/

#include "OTA.h"
#include "WiFi.h"

// -- Protocol selection ----------------------------------------------------
// Set to 0 for HTTP  (port 3000, no SSL)
// Set to 1 for HTTPS (port 443, SSL enabled � requires server.key + server.crt)
#define OTA_USE_HTTPS 0

// -- Network settings ------------------------------------------------------
char ssid[] = "Network_SSID5";    // your network SSID (name)
char pass[] = "Password";         // your network password
int status = WL_IDLE_STATUS;

#if OTA_USE_HTTPS
int port = 443;                   // HTTPS port (default)
char* server = "192.168.3.14";    // your server ip address
OTA ota;
#else
int port = 3000;                  // HTTP  port (default)
char* server = "192.168.3.14";    // your server ip address
OTA ota;
#endif

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

    // Set up the threads
#if OTA_USE_HTTPS
    Serial.println("[OTA] Using HTTPS mode");
    ota.start_OTA_threads(port, server, true);
#else
    Serial.println("[OTA] Using HTTP mode");
    ota.start_OTA_threads(port, server);
#endif
}

void loop()
{
    // Empty or add non-blocking code here
}
