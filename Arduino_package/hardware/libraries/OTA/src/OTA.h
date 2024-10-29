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


private:
    static void thread1_task(const void *argument);
    static void thread2_task(const void *argument);

    static void sendPostRequest();
};
#endif    // OTA_H
