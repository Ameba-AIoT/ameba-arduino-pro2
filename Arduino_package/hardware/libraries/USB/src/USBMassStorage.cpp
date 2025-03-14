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
    if (status != USBD_INIT_OK) {
        if (status == USBD_NOT_ATTACHED) {
            printf("\r\n NO USB device attached\n");
        } else {
            printf("\r\n USB init fail\n");
        }
    } else {
        printf("\r\n USB device attached\n");
    }
    return status;
}

void USBMassStorage::initializeDisk(void)
{

    disk_operations = (msc_opts *)malloc(sizeof(struct msc_opts));
    if (disk_operations == NULL) {
        printf("\r\n disk_operation malloc fail\n");
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
        printf("USB MSC driver load fail.\n");
    } else {
        printf("USB MSC driver load done, Available heap [0x%x]\n", xPortGetFreeHeapSize());
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
