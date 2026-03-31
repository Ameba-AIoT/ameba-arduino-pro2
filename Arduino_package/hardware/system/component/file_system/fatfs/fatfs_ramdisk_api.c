#include "platform_opts.h"
#if FATFS_DISK_RAM
#include "platform_stdlib.h"
#include "ff.h"
#include "fatfs_ramdisk_api.h"
#include "integer.h"
#include "stdint.h"
#include "stdio.h"
#include "fatfs_ext/inc/ff_driver.h"
#if defined(CONFIG_PLATFORM_8195BHP)
#include "timer_api.h"
#include "task.h"
#endif

////**** Implement the basic functions for RAM FatFs ****////
#define RAM_DISK_SIZE       (1024 * 1024 * 10)
#define SECTOR_SIZE_RAM     512
#define SECTOR_COUNT_RAM    (RAM_DISK_SIZE / SECTOR_SIZE_RAM) // File system volumes = SECTOR_SIZE_RAM * SECTOR_COUNT_RAM

static char *diskMem = NULL;

//#define FATFS_RAM_FROM_PC  //It is to resolve sync problem from pc and device

DSTATUS RAM_disk_initialize(void)
{
	return RES_OK;
}

DSTATUS RAM_disk_status(void)
{
	return RES_OK;
}

DSTATUS RAM_disk_deinitialize(void)
{
	return RES_OK;
}

/* Read sector(s) --------------------------------------------*/
DRESULT RAM_disk_read(BYTE *buff, DWORD sector, UINT count)
{
	memcpy(buff, diskMem + sector * SECTOR_SIZE_RAM, count * SECTOR_SIZE_RAM);
	return RES_OK;
}

/* Write sector(s) --------------------------------------------*/
#if _USE_WRITE == 1
DRESULT RAM_disk_write(BYTE const *buff, DWORD sector, UINT count)
{
	memcpy(diskMem + sector * SECTOR_SIZE_RAM, buff, count * SECTOR_SIZE_RAM);
	return RES_OK;
}
#endif


/* IOCTL sector(s) --------------------------------------------*/
#if _USE_IOCTL == 1
DRESULT RAM_disk_ioctl(BYTE cmd, void *buff)
{
	DRESULT result;

	switch (cmd) {
	case CTRL_SYNC:
		result = RES_OK;
		break;

	case GET_BLOCK_SIZE:
	case CTRL_ERASE_SECTOR:
		result = RES_PARERR;
		break;

	case GET_SECTOR_SIZE:
		*(WORD *)buff = SECTOR_SIZE_RAM;
		result = RES_OK;
		break;

	case GET_SECTOR_COUNT:
		*(DWORD *)buff = SECTOR_COUNT_RAM;
		result = RES_OK;
		break;

	default:
		result = RES_ERROR;
		break;
	}

	return (result);
}
#endif


ll_diskio_drv RAM_disk_Driver = {
	.disk_initialize = RAM_disk_initialize,
	.disk_status = RAM_disk_status,
	.disk_read = RAM_disk_read,
	.disk_deinitialize = RAM_disk_deinitialize,
#if _USE_WRITE == 1
	.disk_write = RAM_disk_write,
#endif
#if _USE_IOCTL == 1
	.disk_ioctl = RAM_disk_ioctl,
#endif
	.TAG	= "RAM"
};
/*For usb operation.........................................*/
int usb_ram_init(void)
{
	int ret = 0;
	return ret;
}
int usb_ram_deinit(void)
{
	int ret = 0;
	return ret;
}
int usb_ram_getcapacity(uint32_t *sector_count)
{
	*sector_count = SECTOR_COUNT_RAM;
	return 0;
}
int usb_ram_readblocks(uint32_t sector, uint8_t *data, uint32_t count)
{
	RAM_disk_read(data, sector, count);
	return 0;
}
int usb_ram_writeblocks(uint32_t sector, const uint8_t *data, uint32_t count)
{
	RAM_disk_write(data, sector, count);
	return 0;
}


////**** API for the usage of the FatFs on RAM ****////

static fatfs_ram_params_t fatfs_ram_param;
static uint8_t fatfs_ram_init_done = 0;
static FIL     fatfs_ram_file;

int fatfs_ram_close()
{

	if (fatfs_ram_init_done) {
		if (f_mount(NULL, fatfs_ram_param.drv, 1) != FR_OK) {
			printf("FATFS unmount ram logical drive fail.\n");
		}

		if (FATFS_UnRegisterDiskDriver(fatfs_ram_param.drv_num)) {
			printf("Unregister ram disk driver from FATFS fail.\n");
		}

		fatfs_ram_init_done = 0;

		if (diskMem) {
			free(diskMem);
		}
	}
	return 0;
}

int fatfs_ram_init(void)
{

	int ret = 0;

	if (!fatfs_ram_init_done) {
		diskMem = (char *)malloc(sizeof(char) * SECTOR_SIZE_RAM * SECTOR_COUNT_RAM);

		if (!diskMem) {
			ret = -1;
			goto fatfs_init_err;
		}

		memset(diskMem, 0, sizeof(char)*SECTOR_SIZE_RAM * SECTOR_COUNT_RAM);

		int Fatfs_ok = 0;
		FRESULT res1, res2;
		char path[64];
		char ram_test_fn[64] = "ram_drive_test.txt";

		// Register disk driver to Fatfs
		printf("Register ram disk driver to Fatfs.\n\r");
		fatfs_ram_param.drv_num = FATFS_RegisterDiskDriver(&RAM_disk_Driver);

		if (fatfs_ram_param.drv_num < 0) {
			printf("Register ram disk driver to FATFS fail.\n\r");
		} else {
			Fatfs_ok = 1;
			fatfs_ram_param.drv[0] = fatfs_ram_param.drv_num + '0';
			fatfs_ram_param.drv[1] = ':';
			fatfs_ram_param.drv[2] = '/';
			fatfs_ram_param.drv[3] = 0;

			printf("Ram drive path: %s\n\r", fatfs_ram_param.drv);
		}
		if (!Fatfs_ok) {
			ret = -1;
			goto fatfs_init_err;
		}
		res1 = f_mount(&fatfs_ram_param.fs, fatfs_ram_param.drv, 1);
		// test ram
		printf("Test ram drive (file: %s)\n\n\r", ram_test_fn);
		strcpy(path, fatfs_ram_param.drv);
		sprintf(&path[strlen(path)], "%s", ram_test_fn);
		res2 = f_open(&fatfs_ram_file, path, FA_OPEN_ALWAYS | FA_READ | FA_WRITE);
		if (res1 || res2) {
			MKFS_PARM opt;
			opt.fmt = FM_ANY;
			opt.au_size = 0;
			ret = f_mkfs(fatfs_ram_param.drv, &opt, diskMem, 512);     // NULL
			if (ret != FR_OK) {
				printf("Create FAT volume on Ram fail. (%d)\n\r", ret);
				goto fatfs_init_err;
			}
			if (f_mount(&fatfs_ram_param.fs, fatfs_ram_param.drv, 0) != FR_OK) {
				printf("FATFS mount logical drive on Ram fail.\n\r");
				goto fatfs_init_err;
			}
			printf("ram mkfs and mount OK\n\r");
		} else {
			printf("ram mount OK\n\r");
		}
		fatfs_ram_init_done = 1;
	} else {
		ret = -2;
	}

	return 0;

fatfs_init_err:
	fatfs_ram_close();
	return ret;
}

int fatfs_ram_get_param(fatfs_ram_params_t *param)
{
	if (fatfs_ram_init_done) {
		memcpy(param, &fatfs_ram_param, sizeof(fatfs_ram_params_t));
		return 0;
	} else {
		memset(param, 0, sizeof(fatfs_ram_params_t));
		return -1;
	}
}

int fatfs_get_ram_free_space(void)
{
	FATFS *pfs = NULL;
	DWORD fre_clust;
	unsigned char  res;
	float sector_size = 0;
	float free_size = 0;
	sector_size = 512;
	char	logical_drv[4] = {0}; /* root diretor */
	logical_drv[0] = fatfs_ram_param.drv_num + '0';
	logical_drv[1] = ':';
	logical_drv[2] = 0;
	logical_drv[3] = 0;
	if (fatfs_ram_init_done) {
		res = f_getfree(logical_drv, &fre_clust, &pfs);
		if (res) {
			return res;
		} else {
			//TOT_SIZE = (pfs->n_fatent - 2) * pfs->csize/2; //
			free_size = (fre_clust * pfs->csize) * (sector_size / 1024 / 1024); //
		}
	}
	return (int)free_size;//MB
}

int fatfs_get_ram_total_szie(void)
{
	FATFS *pfs = NULL;
	DWORD fre_clust;
	unsigned char  res;
	float TOT_SIZE = 0;
	char	logical_drv[4] = {0}; /* root diretor */
	logical_drv[0] = fatfs_ram_param.drv_num + '0';
	logical_drv[1] = ':';
	logical_drv[2] = 0;
	logical_drv[3] = 0;
	if (fatfs_ram_init_done) {
		res = f_getfree(logical_drv, &fre_clust, &pfs);
		if (res) {
			return res;
		} else {
			TOT_SIZE = (pfs->n_fatent - 2) * pfs->csize / 2; //
			//free_size = (fre_clust * pfs->csize)*(sector_size/1024/1024); //
		}
	}
	return (int)TOT_SIZE;//KB
}

long long int fatfs_ram_get_free_space_byte(void)
{
	FATFS *pfs = NULL;
	DWORD fre_clust;
	long long int fre_clust_temp, csize_temp;
	long long int free_size = 0;
	unsigned char  res;
	long long int sector_size = 0;

	sector_size = 512;
	char	logical_drv[4] = {0}; /* root diretor */
	logical_drv[0] = fatfs_ram_param.drv_num + '0';
	logical_drv[1] = ':';
	logical_drv[2] = 0;
	logical_drv[3] = 0;
	if (fatfs_ram_init_done) {
		res = f_getfree(logical_drv, &fre_clust, &pfs);
		if (res) {
			return res;
		} else {
			//TOT_SIZE = (pfs->n_fatent - 2) * pfs->csize/2; //
			fre_clust_temp = fre_clust;
			csize_temp     = pfs->csize;
			free_size = (fre_clust_temp * csize_temp) * sector_size; //*(sector_size); //
		}
	}

	return free_size;//Byte
}

FRESULT ram_scan_files(
	char *path        /* Start node to be scanned (also used as work area) */
)
{
	FRESULT res;
	FILINFO fno;
	DIR dir;
	char *fn;   /* This function is assuming non-Unicode cfg. */
#if _USE_LFN
	static char lfn[_MAX_LFN + 1];
	fno.lfname = lfn;
	fno.lfsize = sizeof(lfn);
#endif
	char cur_path[512] = {0};
	res = f_opendir(&dir, path);                       /* Open the directory */
	if (res == FR_OK) {
		sprintf(cur_path, path);
		for (;;) {
			res = f_readdir(&dir, &fno);                   /* Read a directory item */
			if (res != FR_OK || fno.fname[0] == 0) {
				break;    /* Break on error or end of dir */
			}
			if (fno.fname[0] == '.') {
				continue;    /* Ignore dot entry */
			}
#if _USE_LFN
			fn = *fno.lfname ? fno.lfname : fno.fname;
#else
			fn = fno.fname;
#endif
			if (fno.fattrib & AM_DIR) {                    /* It is a directory */
				sprintf(&cur_path[strlen(path)], "/%s", fn);
				ram_scan_files(cur_path);
			} else {                                       /* It is a file. */
				printf("%s/%s\r\n", path, fn);
			}
		}
	}
	f_closedir(&dir);
	return res;
}

void fatfs_ram_reset(void)
{
	if (f_mount(NULL, fatfs_ram_param.drv, 1) != FR_OK) {
		printf("FATFS unmount ram logical drive fail.\n");
	}
	if (f_mount(&fatfs_ram_param.fs, fatfs_ram_param.drv, 1) != FR_OK) {
		printf("FATFS mount ram logical drive fail.\n");
	}
	printf("Fatfs ram reset to sync the pc and device\r\n");
}

void fatfs_ram_list_files(void)
{
	char buff[256] = {0};
	char	logical_drv[4] = {0}; /* root diretor */
	logical_drv[0] = fatfs_ram_param.drv_num + '0';
	logical_drv[1] = ':';
	logical_drv[2] = '/';
	logical_drv[3] = 0;
#ifdef FATFS_RAM_FROM_PC
	fatfs_ram_reset();
#endif
	if (fatfs_ram_init_done) {
		strcpy(buff, logical_drv);
		ram_scan_files(buff);
	}
}

FRESULT fatfs_ram_remove_file(char *name)
{
	FRESULT ret = 0;
	ret = f_unlink(name);
	return ret;
}
int fatfs_ram_format(void *parm)
{
	int ret = 0;
	(void)parm;
	if (fatfs_ram_init_done) {
		MKFS_PARM opt;
		opt.fmt = FM_ANY;
		opt.au_size = 0;
		ret = f_mkfs(fatfs_ram_param.drv, &opt, diskMem, 512);     // NULL
		if (ret != FR_OK) {
			printf("Create FAT volume on Ram fail. (%d)\n\r", ret);
		} else {
			ret = f_mount(&fatfs_ram_param.fs, fatfs_ram_param.drv, 0);
			if (ret != FR_OK) {
				printf("Create FAT volume on Ram fail. (%d)\n\r", ret);
			} else {
				printf("ram mkfs and mount OK\n\r");
			}
		}
	}
	return ret;
}

#endif //FATFS_DISK_RAM