#ifndef OTA_H
#define OTA_H

#include <Arduino.h>
#include <httpd/httpd.h>
#include <WiFi.h>

class OTA {
public:
    OTA(void);
    ~OTA(void);

    // To start OTA firmware update process via HTTP
    void start_OTA_threads(int port, char *server);
    void start_OTA_threads(int port, char *server, WiFiClass &ota_wifi);
    uint8_t check_wifi(void);

private:
    static void thread1_task(const void *argument);
    static void thread2_task(const void *argument);

    static void sendPostRequest(void);
    static WiFiClient wifiClient;
    static char jsonString[256];
    WiFiClass *_ota_wifi;

    static void reConnection(void);
    static uint32_t _last_reconnect;
};
#endif    // OTA_H
