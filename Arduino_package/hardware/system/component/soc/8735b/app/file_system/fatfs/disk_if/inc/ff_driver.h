/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FF_DRIVER_H
#define __FF_DRIVER_H

/* Includes ------------------------------------------------------------------*/
#include "ff.h"
#include "diskio.h"
#include "cmsis.h"

typedef struct {
	DSTATUS(*disk_initialize)(void);                       /*!< Initialize Disk Drive */
	DSTATUS(*disk_deinitialize)(void);                       /*!< Deinitialize Disk Drive */
	DSTATUS(*disk_status)(void);                           /*!< Get Disk Status */
	DRESULT(*disk_read)(BYTE *, DWORD, UINT);              /*!< Read Sector(s) */
#if FF_FS_READONLY == 0
	DRESULT(*disk_write)(const BYTE *, DWORD, UINT);       /*!< Write Sector(s) */
#endif
	DRESULT(*disk_ioctl)(BYTE, void *);                    /*!< I/O control operation */
	unsigned char  *TAG;
	unsigned char drv_num;
} ff_diskio_drv_t;

extern const char *VolumeStr[FF_VOLUMES];

extern ff_diskio_drv_t *ff_drivers[FF_VOLUMES];


#if defined(CONFIG_SDHOST_EN) && (CONFIG_SDHOST_EN == 1)
#define FATFS_DISK_SD               1
extern ff_diskio_drv_t ff_disk_sd_driver;
#endif

extern ff_diskio_drv_t ff_disk_dummy_driver;

#if 0
typedef struct {
	ll_diskio_drv   **drv;
	unsigned int            nbr;
} ff_disk_drv;
extern ff_disk_drv  disk;
int FATFS_RegisterDiskDriver(ll_diskio_drv *disk_drv);
int FATFS_UnRegisterDiskDriver(unsigned char drv_num);
int FATFS_getDrivernum(unsigned char *TAG);
#endif

#endif
