#include <osdep_service.h>
#include <wifi_constants.h>
#include "wifi_conf.h"
#include "lwip_netconf.h"
#include <ota_8735b.h>
#include "ota_drv.h"

int _port;
char *_server;
const char *resource = "api/uploadfile";    // DO NOT MODIFY


// DO NOT MODIFY
const char *OtaState[] = {
    "OTA_STATE_IDLE",
    "OTA_STATE_RECEIVED_START_SIGNAL",
    "OTA_STATE_DOWNLOAD_FIRMWARE_IN_PROGRESS",
    "OTA_STATE_DOWNLOAD_FIRMWARE_COMPLETED",
    "OTA_STATE_REBOOT"};

void http_update_ota_task(void *param)
{
    (void)param;

    int ret = -1;

    g_otaState = OtaState[2];

    ret = http_update_ota((char *)_server, _port, (char *)resource);

    g_otaState = OtaState[3];

    // printf("\n\r[%s] Update task exit", __FUNCTION__);
    if (!ret) {
        // printf("\n\r[%s] Ready to reboot", __FUNCTION__);
        g_otaState = OtaState[4];
        ota_platform_reset();
    }
    vTaskDelete(NULL);
}

void ota_http(void)
{
    if (xTaskCreate(http_update_ota_task, (const char *)"http_update_ota_task", 1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS) {
        printf("\n\r[%s] Create update task failed", __FUNCTION__);
    }
}
