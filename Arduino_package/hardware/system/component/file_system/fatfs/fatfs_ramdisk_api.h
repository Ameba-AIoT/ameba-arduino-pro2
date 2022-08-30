#ifndef _FATFS_RAM_API_H
#define _FATFS_RAM_API_H
#include "ff.h"

typedef struct fatfs_ram_param_s {
	int drv_num;
	char drv[4];
	FATFS fs;
} fatfs_ram_params_t;

int fatfs_ram_init(void);
int fatfs_ram_close(void);
int fatfs_ram_get_param(fatfs_ram_params_t *param);
int fatfs_get_ram_free_space(void);
int fatfs_get_ram_total_szie(void);
long long int fatfs_ram_get_free_space_byte(void);
FRESULT ram_scan_files(char *path);
void fatfs_ram_list_files(void);
FRESULT fatfs_ram_remove_file(char *name);

int usb_ram_init(void);
int usb_ram_deinit(void);
int usb_ram_getcapacity(u32 *sector_count);
int usb_ram_readblocks(u32 sector, u8 *data, u32 count);
int usb_ram_writeblocks(u32 sector, const u8 *data, u32 count);
#endif //_FATFS_RAM_API_H