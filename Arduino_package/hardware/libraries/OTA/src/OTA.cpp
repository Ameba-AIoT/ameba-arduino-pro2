#define ARDUINOJSON_STRING_LENGTH_SIZE_4

#include <Arduino.h>
#include "OTA.h"
#include <WiFi.h>
#include <ArduinoJson.h>

extern "C" {
#include "ota_drv.h"
}

#define SERVER_DEAD_TIMEOUT_MIN 5

const char *g_otaState = OtaState[0];
JsonDocument doc;
static char buffer[1024];
uint32_t thread1_id, thread2_id, stack_size1, stack_size2;
int priority1;

WiFiClient OTA::wifiClient;
char OTA::jsonString[256];
uint32_t OTA::_last_reconnect;

OTA::OTA():
    _ota_wifi(&WiFi)
{}

OTA::~OTA()
{}

uint8_t OTA::check_wifi(void)
{
    if (!_ota_wifi) {
        return WL_DISCONNECTED;
    }

    // WL_DISCONNECTED, WL_CONNECTED
    return _ota_wifi->status();
}

void OTA::reConnection(void)
{
    // printf("reConnection millis: %d \r\n", millis());
    // printf("reConnection _last_reconnect: %d \r\n", _last_reconnect);

    if ((millis() - _last_reconnect) > (SERVER_DEAD_TIMEOUT_MIN * 60 * 1000)) {
        wifiClient.stop();
        _last_reconnect = millis();
        amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] [OTA] Reconnect! \n");
    }
}

void OTA::sendPostRequest(void)
{
    if (wifiClient.connected() == 0) {
        if (wifiClient.connect(_server, _port) == 0) {
            amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] [OTA] Connection to server failed \n");
            return;
        }
    }

    // Send POST request
    wifiClient.println("POST /api/connectedclients HTTP/1.1");
    wifiClient.println("Host: " + String(_server));
    wifiClient.println("Content-Type: application/json");    // Use appropriate content type
    // wifiClient.println("Content-Length: " + String(jsonString.length()));    // Specify the length of the content
    wifiClient.print("Content-Length: ");
    wifiClient.println(strlen(jsonString));

    wifiClient.println("Connection: keep-alive");
    // wifiClient.println("Connection: close");
    wifiClient.println();    // Empty line indicates the end of headers
    wifiClient.print(jsonString);

    // wifiClient.stop();
}

void OTA::thread1_task(const void *argument)
{
    for (;;) {
        sendPostRequest();
        reConnection();
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}

void OTA::thread2_task(const void *argument)
{
    WiFiServer server(5000);
    server.begin();
    while (1) {
        WiFiClient client = server.available();

        while (client.connected()) {

            _last_reconnect = millis();

            memset(buffer, 0, 1024);
            int n = client.read((uint8_t *)(&buffer[0]), sizeof(buffer));
            if (n > 0) {
                for (int i = 0; i < n; i++) {
                    // Serial.print(buffer[i]);
                }
                n = client.write(buffer, n);
                if (n <= 0) {
                    break;
                }
                if (strstr(buffer, "start_ota")) {
                    // Serial.print("\n[OTA] Received start OTA signal from UI.");
                    if (g_otaState == OtaState[0]) {
                        ota_http();
                    }
                }
            }
            delay(500);
            client.stop();
        }
    }
}

void OTA::start_OTA_threads(int port, char *server)
{
    start_OTA_threads(port, server, WiFi);
}

void OTA::start_OTA_threads(int port, char *server, WiFiClass &ota_wifi)
{
    _ota_wifi = &ota_wifi;
    _last_reconnect = millis();
    if (check_wifi() == WL_DISCONNECTED) {
        amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] [OTA] There is no WiFi connection! \n");
        return;
    }

    _port = port;
    _server = server;

    doc["OTA_state"] = g_otaState;
    // serializeJson(doc, jsonString);
    serializeJson(doc, jsonString, sizeof(jsonString));

    priority1 = osPriorityNormal;
    stack_size1 = 1024;
    thread1_id = os_thread_create_arduino(thread1_task, NULL, priority1, stack_size1);
    // thread1_id = os_thread_create_name_arduino(thread1_task, NULL, priority1, stack_size1, "ota_thread1");

    // First thread is to do keep alive connectivity check (post requests every 5s)
    if (thread1_id) {
        amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] [OTA] Keep-alive connectivity thread created successfully. \n");
    } else {
        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] [OTA] Failed to create keep-alive connectivity thread. \n");
    }

    stack_size2 = 2048;
    thread2_id = os_thread_create_arduino(thread2_task, NULL, priority1, stack_size2);
    // thread2_id = os_thread_create_name_arduino(thread2_task, NULL, priority1, stack_size2, "ota_thread2");

    // Second thread is to get the signal to start OTA process.
    if (thread2_id) {
        amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] [OTA] Start OTA process thread created successfully. \n");
    } else {
        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] [OTA] Failed to create Start OTA process thread. \n");
    }
}
