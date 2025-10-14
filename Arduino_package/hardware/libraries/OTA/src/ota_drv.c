#include "Arduino.h"

#include <osdep_service.h>
#include <wifi_constants.h>
#include "wifi_conf.h"
#include "lwip_netconf.h"
#include <ota_8735b.h>
#include "ota_drv.h"
#include "vfs.h"

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

    // amb_ard_printf(ARD_LOG_ERR, "\n\r[%s] Update task exit", __FUNCTION__);
    if (!ret) {
        // amb_ard_printf(ARD_LOG_INF, "\n\r[%s] Ready to reboot", __FUNCTION__);
        g_otaState = OtaState[4];
        ota_platform_reset();
    }
    vTaskDelete(NULL);
}

void sd_update_ota_task(void *param)
{
    char *filename = (char *)param;    // this is your safe heap copy

    vfs_init(NULL);

    if (vfs_user_register("0", VFS_FATFS, VFS_INF_SD) < 0) {
        amb_ard_printf(ARD_LOG_ERR, "[ERROR] Failed to register VFS for 0:/\n");
        vPortFree(filename);
        vTaskDelete(NULL);
        return;
    }

    amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] sd_update_ota_task using file: %s\n", filename);

    int ret = ext_storage_update_ota(filename);

    if (!ret) {
        ota_platform_reset();
    }

    vPortFree(filename);    // free after done
    vTaskDelete(NULL);
}

void ota_http(void)
{
    if (xTaskCreate(http_update_ota_task, (const char *)"http_update_ota_task", 1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS) {
        amb_ard_printf(ARD_LOG_ERR, "\n\r[%s] Create update task failed", __FUNCTION__);
    }
}

void ota_sd(const char *filename)
{
    if (!filename || filename[0] == '\0') {
        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] No OTA file name provided.\n");
        return;
    }

    // Copy filename into heap memory so it survives after function returns
    char *filename_copy = (char *)pvPortMalloc(strlen(filename) + 1);
    if (!filename_copy) {
        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] pvPortMalloc failed.\n");
        return;
    }
    strcpy(filename_copy, filename);

    amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] ota_sd scheduling task with file: %s\n", filename_copy);

    // Pass heap copy to task
    if (xTaskCreate(sd_update_ota_task, "sd_update_ota_task", 2048,
                    (void *)filename_copy, tskIDLE_PRIORITY + 1, NULL)
        != pdPASS) {
        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] Create update task failed.\n");
        vPortFree(filename_copy);
    }
}
