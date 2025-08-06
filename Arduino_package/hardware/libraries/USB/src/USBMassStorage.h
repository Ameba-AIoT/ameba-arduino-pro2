#ifndef __USBMASSSTORAGE_H__
#define __USBMASSSTORAGE_H__

#include <Arduino.h>

class USBMassStorage {

public:
    void USBInit(void);
    void SDIOInit(void);
    int USBStatus(void);
    void initializeDisk(void);
    void loadUSBMassStorageDriver(void);
    void USBDeinit(void);
    int isConnected(void);

private:
    struct msc_opts *disk_operations = NULL;
};
#endif
