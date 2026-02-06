#include "WiFi.h"
#include "WebSocketViewer.h"
#include "StreamIO.h"
#include "VideoStream.h"
#include "RTSP.h"

#include "gpio_api.h"
#include "us_ticker_api.h"
#include "wait_api.h"

#define CHANNEL      0
#define enableWiFiAP 1    // set 0 to use external WiFi network
#define GPIO_LED_S1  PS_1
#define GPIO_LED_S4  PS_4
#define GPIO_LED_E0  PE_0

VideoSetting config(VIDEO_FHD, 30, VIDEO_H264, 0);
RTSP rtsp;
WebSocketViewer ws_viewer;
StreamIO videoStreamer(1, 1);

#if enableWiFiAP
// UTF-8 encoding can also be used for SSID with emoji characters
// Emoji characters can be converted into UTF-8 at https://mothereff.in/utf-8
// char ssid[] = "\xe2\x9c\x8c\xef\xb8\x8f Ameba \xe2\x9c\x8c\xef\xb8\x8f";
char ssid[] = "AP_Network_SSID";    // Set the AP SSID
char pass[] = "AP_Password";        // Set the AP password
char channel[] = "11";              // Set the AP channel
int status = WL_IDLE_STATUS;        // Indicator of Wifi status
int ssid_status = 0;                // Set SSID status, 1 hidden, 0 not hidden

#else
char ssid[] = "Network_SSID";    // your network SSID (name)
char pass[] = "Password";        // your network password
int status = WL_IDLE_STATUS;
#endif

void setup()
{
    Serial.begin(115200);
    while (!Serial) {
        ;    // wait for serial port to connect. Needed for native USB port only
    }

#if enableWiFiAP
    int checker = 0;
    Serial.println(ssid);
    checker = atoi(channel);
    status = WiFi.apbegin(ssid, pass, channel, ssid_status);
    if (checker < 1 || checker > 13) {
        Serial.println("WARNING: channel is out of 1-13 range, defaulted to channel 1");
    }
    delay(10000);

    Serial.println("AP mode already started");
    Serial.println();
    printWifiData();
    printCurrentNet();
#else
    // attempt to connect to Wifi network:
    while (status != WL_CONNECTED) {
        Serial.print("Attempting to connect to WPA SSID: ");
        Serial.println(ssid);
        status = WiFi.begin(ssid, pass);

        // wait 2 seconds for connection:
        delay(2000);
    }
#endif

    ws_viewer.loadWebResources(0);
    config.enableWebsocketViewer();
    // Recommended bitrate - 2 Mbps
    config.setBitrate(2 * 1024 * 1024);
    Camera.configVideoChannel(CHANNEL, config);
    Camera.videoInit();
    ws_viewer.init();

    videoStreamer.registerInput(Camera.getStream(CHANNEL));
    videoStreamer.registerOutput(ws_viewer);
    if (videoStreamer.begin() != 0) {
        Serial.println("StreamIO link start failed");
    }

    Camera.channelBegin(CHANNEL);
    ws_viewer.begin();

    enableLightGPIO();    // Remove this if the flashlight GPIOs are not PS_1, PS_4 and PE_0.
}

void loop()
{
}


void printWifiData()
{
    // print your WiFi IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    // print your subnet mask:
    IPAddress subnet = WiFi.subnetMask();
    Serial.print("NetMask: ");
    Serial.println(subnet);

    // print your gateway address:
    IPAddress gateway = WiFi.gatewayIP();
    Serial.print("Gateway: ");
    Serial.println(gateway);
    Serial.println();
}

void printCurrentNet()
{
    // print the SSID of the AP:
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // print the MAC address of AP:
    byte bssid[6];
    WiFi.BSSID(bssid);
    Serial.print("BSSID: ");
    Serial.print(bssid[0], HEX);
    Serial.print(":");
    Serial.print(bssid[1], HEX);
    Serial.print(":");
    Serial.print(bssid[2], HEX);
    Serial.print(":");
    Serial.print(bssid[3], HEX);
    Serial.print(":");
    Serial.print(bssid[4], HEX);
    Serial.print(":");
    Serial.println(bssid[5], HEX);

    // print the encryption type:
    byte encryption = WiFi.encryptionType();
    Serial.print("Encryption Type:");
    Serial.println(encryption, HEX);
    Serial.println();
}


void enableLightGPIO()
{
    gpio_t gpio_led_s1;
    gpio_t gpio_led_s4;
    gpio_t gpio_led_e0;

    // Init LED control pin
    gpio_init(&gpio_led_s1, GPIO_LED_S1);
    gpio_dir(&gpio_led_s1, PIN_OUTPUT);    // Direction: Output
    gpio_mode(&gpio_led_s1, PullNone);     // No pull

    gpio_init(&gpio_led_s4, GPIO_LED_S4);
    gpio_dir(&gpio_led_s4, PIN_OUTPUT);    // Direction: Output
    gpio_mode(&gpio_led_s4, PullNone);     // No pull

    gpio_init(&gpio_led_e0, GPIO_LED_E0);
    gpio_dir(&gpio_led_e0, PIN_OUTPUT);    // Direction: Output
    gpio_mode(&gpio_led_e0, PullNone);     // No pull

    gpio_write(&gpio_led_s1, 1);
    gpio_write(&gpio_led_s4, 1);
    gpio_write(&gpio_led_e0, 1);
}
