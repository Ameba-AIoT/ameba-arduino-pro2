#include <fatfs_ext/inc/ff_driver.h>
#include "platform_stdlib.h"

ff_disk_drv  disk = {0};
static _mutex ff_init_mutex = NULL;

static void ff_lock(void)
{
	if (ff_init_mutex == NULL) {
		rtw_mutex_init(&ff_init_mutex);
	}
	rtw_mutex_get(&ff_init_mutex);
}

static void ff_unlock(void)
{
	if (ff_init_mutex == NULL) {
		rtw_mutex_init(&ff_init_mutex);
	}
	rtw_mutex_put(&ff_init_mutex);
}
// return drv_num assigned
int FATFS_RegisterDiskDriver(ll_diskio_drv *drv)
{
	int index = 0;
	int drv_num = -1;
	ff_lock();
	if (disk.nbr < _VOLUMES) {
		for (index = 0; index < _VOLUMES; index++) {
			if (!disk.drv[index]) {
				drv->drv_num = index;	// record driver number for a specific disk
				disk.drv[index] = drv;
				disk.nbr++;
				drv_num = index;
				break;
			}
		}
	}
	ff_unlock();
	printf("FATFS Register: disk driver %d\n\r", drv_num);
	return drv_num;
}

int FATFS_UnRegisterDiskDriver(unsigned char drv_num)
{
	int index = 0;
	int ret = -1;
	ff_lock();
	if (disk.nbr >= 1) {
		for (index = 0; index < _VOLUMES; index++) {
			if (disk.drv[index]) {
				if (disk.drv[index]->drv_num == drv_num) {
					disk.drv[index] = NULL;
					disk.nbr--;
					ret = 0;
					goto EXIT;
				}
			}
		}
	}
EXIT:
	ff_unlock();
	return ret; // return result 0:successful 1:fail
}


/**
  * @brief  Gets number of linked drivers to the FatFs module.
  * @param  None
  * @retval Number of attached drivers.
  */
int FATFS_getDrivernum(const char *TAG)
{
	ll_diskio_drv *drv;
	unsigned int index;

	for (index = 0; index < disk.nbr; index++) {
		drv = disk.drv[index];
		if (!strcmp((char const *)drv->TAG, (char const *)TAG)) {
			return drv->drv_num;
		}
	}
	return -1;
}
