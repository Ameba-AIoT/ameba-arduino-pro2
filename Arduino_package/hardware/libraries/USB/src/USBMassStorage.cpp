#include "USBMassStorage.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "msc/inc/usbd_msc.h"
#include "sdio_combine.h"
#include "sys_api.h"

// from fatfs_sdcard_api.h
extern void sd_gpio_init(void);
extern int usb_sd_init(void);
extern int usb_sd_deinit(void);
extern int usb_sd_getcapacity(uint32_t *sector_count);
extern int usb_sd_readblocks(uint32_t sector, uint8_t *data, uint32_t count);
extern int usb_sd_writeblocks(uint32_t sector, const uint8_t *data, uint32_t count);

// from dwc_otg_driver
extern int usb_insert(void);    // 1: connect 0: disconnect

#ifdef __cplusplus
}
#endif

void USBMassStorage::USBInit(void)
{
    _usb_init();
}

void USBMassStorage::SDIOInit(void)
{
    sd_gpio_init();
    sdio_driver_init();
}

int USBMassStorage::USBStatus(void)
{
    int status = wait_usb_ready();
    amb_ard_printf(ARD_LOG_INF, "[INFO] USB init status %d\r\n", status);

    if (status != USBD_INIT_OK) {
        if (status == USBD_NOT_ATTACHED) {
            amb_ard_printf(ARD_LOG_INF, "\r\n [INFO] NO USB device attached\n");
        } else {
            amb_ard_printf(ARD_LOG_ERR, "\r\n [ERROR] USB init fail\n");
        }
    }
    return status;
}

void USBMassStorage::initializeDisk(void)
{

    disk_operations = (msc_opts *)malloc(sizeof(struct msc_opts));
    if (disk_operations == NULL) {
        amb_ard_printf(ARD_LOG_ERR, "\r\n [ERROR] disk_operation malloc fail\n");
    }

    disk_operations->disk_init = usb_sd_init;
    disk_operations->disk_deinit = usb_sd_deinit;
    disk_operations->disk_getcapacity = usb_sd_getcapacity;
    disk_operations->disk_read = usb_sd_readblocks;
    disk_operations->disk_write = usb_sd_writeblocks;
}

void USBMassStorage::loadUSBMassStorageDriver(void)
{
    int status = usbd_msc_init(MSC_NBR_BUFHD, MSC_BUFLEN, disk_operations);
    if (status) {
        amb_ard_printf(ARD_LOG_ERR, "[ERROR] USB MSC driver load fail.\n");
    } else {
        amb_ard_printf(ARD_LOG_INF, "[INFO] USB MSC driver load done, Available heap [0x%x]\n", xPortGetFreeHeapSize());
    }
}

void USBMassStorage::USBDeinit(void)
{
    usbd_msc_deinit();
    extern void _usb_deinit(void);
    _usb_deinit();
    if (disk_operations) {
        free(disk_operations);
        disk_operations = NULL;
    }
}

int USBMassStorage::isConnected(void)
{
    int connect_status = usb_insert();

    return connect_status;
}
