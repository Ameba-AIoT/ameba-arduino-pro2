#include <stdio.h>
#include "vfs.h"
#include "ff.h"
#include "time.h"
#include "fatfs_ext/inc/ff_driver.h"
#include "fatfs_sdcard_api.h"
#include "fatfs_ramdisk_api.h"
#include "fatfs_flash_api.h"
#include "sd.h"
int fatfs_get_interface(int interface)
{
	int drv_id = 0;
	if (interface == VFS_INF_SD || interface == VFS_INF_EMMC) {
		drv_id = FATFS_getDrivernum("SD");
	} else if (interface == VFS_INF_RAM) {
		drv_id = FATFS_getDrivernum("RAM");
	} else if (interface == VFS_INF_FLASH) {
		drv_id = FATFS_getDrivernum("FLASH");
	} else {
		return -1;
	}
	return drv_id;
}

int fatfs_open(const char *filename, const char *mode, vfs_file *finfo)
{
	FIL *fil = malloc(sizeof(FIL));
	uint8_t mode_mapping = 0;
	FRESULT res = 0;
	if (fil == NULL) {
		return -1;
	}

	if (strchr(mode, 'r')) {
		mode_mapping |= FA_READ;
	}
	if (strchr(mode, 'w')) {
		if (strchr(mode, 'x')) {
			mode_mapping |= (FA_CREATE_NEW | FA_WRITE);
		} else {
			mode_mapping |= (FA_CREATE_ALWAYS | FA_WRITE);
		}
	}
	if (strchr(mode, 'a')) {
		mode_mapping |= (FA_OPEN_APPEND | FA_WRITE);
	}
	if (strchr(mode, '+')) {
		mode_mapping |= (FA_READ | FA_WRITE);
	}

	res = f_open(fil, filename, mode_mapping);
	if (res != 0) {
		free(fil);
		return -1;
	}
	finfo->file = (void *)fil;
	return res;
}

int fatfs_read(unsigned char *buf, unsigned int size, unsigned int count, vfs_file *finfo)
{
	FIL *fil = (FIL *)finfo->file;
	size_t br;
	FRESULT res = f_read(fil, buf, size * count, (UINT *)&br);
	if (res > 0) {
		return -1;
	}
	return br / size;
}

int fatfs_write(unsigned char *buf, unsigned int size, unsigned int count, vfs_file *finfo)
{
	FIL *fil = (FIL *)finfo->file;
	size_t bw;
	FRESULT res = f_write(fil, buf, size * count, (UINT *)&bw);
	if (res > 0) {
		return -1;
	}
	return bw / size;
}

int fatfs_close(vfs_file *finfo)
{
	FIL *fil = (FIL *)finfo->file;
	FRESULT res = f_close(fil);
	free(fil);
	if (res > 0) {
		return -1;
	}
	return 0;
}

int fatfs_seek(long int offset, int origin, vfs_file *finfo)
{
	FIL *fil = (FIL *)finfo->file;
	int size = f_size(fil);
	int curr = f_tell(fil);
	FRESULT res = FR_INT_ERR;
	switch (origin) {
	case SEEK_SET:
		res = f_lseek(fil, offset);
		break;
	case SEEK_CUR:
		res = f_lseek(fil, curr + offset);
		break;
	case SEEK_END:
		res = f_lseek(fil, size - offset);
		break;
	}
	if (res > 0) {
		return -1;
	}
	return 0;
}

void fatfs_rewind(vfs_file *finfo)
{
	FIL *fil = (FIL *)finfo->file;
	f_lseek(fil, 0);
}

int fatfs_fgetops(vfs_file *finfo)
{
	FIL *fil = (FIL *)finfo->file;
	int value = 0;
	value = f_tell(fil);
	return value;
}

int fatfs_fsetops(unsigned int offset, vfs_file *finfo)
{
	FIL *fil = (FIL *)finfo->file;
	int value = 0;
	value = f_lseek(fil, offset);
	return value;
}

int fatfs_fflush(vfs_file *finfo)
{
	FIL *fil = (FIL *)finfo->file;
	FRESULT res = f_sync(fil);
	return -res;
}

int fatfs_remove(const char *name)
{
	FRESULT res = f_unlink(name);
	return -res;
}

int fatfs_rename(const char *old_name, const char *new_name)
{
	FRESULT res = f_rename(old_name, new_name);
	return -res;
}

int fatfs_feof(vfs_file *finfo)
{
	FIL *fil = (FIL *)finfo->file;
	return f_eof(fil);
}

int fatfs_ferror(vfs_file *finfo)
{
	FIL *fil = (FIL *)finfo->file;
	return f_error(fil);
}

int fatfs_ftell(vfs_file *finfo)
{
	FIL *fil = (FIL *)finfo->file;
	return f_tell(fil);
}

int fatfs_ftruncate(vfs_file *finfo, off_t length)
{
	FIL *fil = (FIL *)finfo->file;
	FRESULT res = FR_INT_ERR;
	res = f_lseek(fil, length);
	if (res > 0) {
		return -1;
	}
	res = f_truncate(fil);
	if (res > 0) {
		return -1;
	}
	return 0;
}

int fatfs_opendir(const char *name, vfs_file *finfo)
{
	DIR *pdir = malloc(sizeof(DIR));
	FRESULT res = 0;
	if (pdir == NULL) {
		return -1;
	}
	finfo->file = (void *)pdir;
	res = f_opendir(pdir, name);
	return res;
}
extern struct dirent *vfs_get_dir(void);
struct dirent *fatfs_readdir(vfs_file *finfo)
{
	DIR *pdir = (DIR *)finfo->file;
	FRESULT res;
	char *fn;
	if (pdir == NULL) {
		return NULL;
	}
	struct dirent *ent = vfs_get_dir();
	if (ent == NULL) {
		return NULL;
	}
	FILINFO m_fileinfo;
#if _USE_LFN
	static char lfn[_MAX_LFN + 1];
	m_fileinfo.lfname = lfn;
	m_fileinfo.lfsize = sizeof(lfn);
#endif
	res = f_readdir(pdir, &m_fileinfo);
	if (res != FR_OK) {
		//free(ent);
		printf("readdir: error (%d)\n\r", res);
		return NULL;
	}

	if (m_fileinfo.fname[0] == 0) {
		//free(ent);
		return NULL;
	}
#if _USE_LFN
	fn = *m_fileinfo.lfname ? m_fileinfo.lfname : m_fileinfo.fname;
#else
	fn = m_fileinfo.fname;
#endif
	ent->d_ino = 0;
	ent->d_off = 0;
	ent->d_reclen = m_fileinfo.fsize;
	if (m_fileinfo.fattrib & AM_DIR) {
		ent->d_type = DT_DIR;    // directory
	} else {
		ent->d_type = DT_REG;    // regular file
	}
#if _USE_LFN
	fn = *m_fileinfo.lfname ? m_fileinfo.lfname : m_fileinfo.fname;
#else
	fn = m_fileinfo.fname;
#endif
	snprintf(ent->d_name, PATH_MAX + 1, "%s", fn);
	return ent;
}

struct dirent *_fatfs_readdir(DIR *pdir)
{
	FRESULT res;
	char *fn;
	if (pdir == NULL) {
		return NULL;
	}
	struct dirent *ent = malloc(sizeof(struct dirent));
	if (ent == NULL) {
		return NULL;
	}
	FILINFO m_fileinfo;
#if _USE_LFN
	static char lfn[_MAX_LFN + 1];
	m_fileinfo.lfname = lfn;
	m_fileinfo.lfsize = sizeof(lfn);
#endif
	res = f_readdir(pdir, &m_fileinfo);
	if (res != FR_OK) {
		free(ent);
		printf("readdir: error (%d)\n\r", res);
		return NULL;
	}

	if (m_fileinfo.fname[0] == 0) {
		free(ent);
		return NULL;
	}
#if _USE_LFN
	fn = *m_fileinfo.lfname ? m_fileinfo.lfname : m_fileinfo.fname;
#else
	fn = m_fileinfo.fname;
#endif
	ent->d_ino = 0;
	ent->d_off = 0;
	ent->d_reclen = m_fileinfo.fsize;
	if (m_fileinfo.fattrib & AM_DIR) {
		ent->d_type = DT_DIR;    // directory
	} else {
		ent->d_type = DT_REG;    // regular file
	}
#if _USE_LFN
	fn = *m_fileinfo.lfname ? m_fileinfo.lfname : m_fileinfo.fname;
#else
	fn = m_fileinfo.fname;
#endif
	snprintf(ent->d_name, PATH_MAX + 1, "%s", fn);
	return ent;
}

int fatfs_closedir(vfs_file *finfo)
{
	DIR *pdir = (DIR *)finfo->file;
	FRESULT res = f_closedir(pdir);
	free(pdir);
	if (res > 0) {
		return -1;
	} else {
		return 0;
	}
}

int _fatfs_closedir(DIR *pdir)
{
	FRESULT res = f_closedir(pdir);
	if (res > 0) {
		return -1;
	} else {
		return 0;
	}
}

int fatfs_mkdir(const char *pathname)
{
	FRESULT res = f_mkdir(pathname);
	return -res;
}

int fatfs_rmdir(const char *path)
{
	FRESULT res = f_unlink(path);
	return -res;
}

int fatfs_access(const char *pathname, int mode)
{
	FRESULT res;
	FILINFO finfo;

	res = f_stat(pathname, &finfo);

	printf("%s, check 0x%x\n\r", pathname, mode);

	if (res != FR_OK) {
		return -1;
	}



	if (mode & R_OK) {
		return 0;
	}

	if (mode & W_OK) {
		if (finfo.fattrib & AM_RDO) {
			return -1;
		} else {
			return 0;
		}
	}

	if (mode & X_OK) {
		if (finfo.fattrib & AM_RDO) {
			return -1;
		} else {
			return 0;
		}
	}
	return 0;
}

int fatfs_stat(char *path, struct stat *buf)
{
	FILINFO finfo;

	FRESULT res = f_stat(path, &finfo);
	if (res == FR_NO_FILE) {
		return -1;
	}

	buf->st_dev = 0;
	buf->st_ino = 0;

	mode_t st_mode = 0;
	if (finfo.fattrib & AM_DIR) {
		if (finfo.fattrib & AM_RDO) {
			st_mode |= (S_IFDIR | 0x555);
		} else {
			st_mode |= (S_IFDIR | 0x777);
		}
	} else {
		if (finfo.fattrib & AM_RDO) {
			st_mode |= (S_IFREG | 0x555);
		} else {
			st_mode |= (S_IFREG | 0x777);
		}
	}

	buf->st_mode = st_mode;
	buf->st_nlink = 0;
	buf->st_uid = 0;
	buf->st_gid = 0;
	buf->st_rdev = 0;
	buf->st_size = finfo.fsize;
	buf->st_blksize = 0;
	buf->st_blocks = 0;

	struct tm tm  = {0};
	int year = (finfo.fdate >> 9) + 1980;
	int month = (finfo.fdate >> 5) & 15;
	int day = finfo.fdate & 31;
	int hour = finfo.ftime >> 11;
	int minute = (finfo.ftime >> 5) & 63;
	char timestr[512];
	snprintf(timestr, sizeof(timestr), "%d/%d/%d %d:%d", year, month, day, hour, minute);

	tm.tm_year = year - 1900; /* years since 1900 */
	tm.tm_mon = month - 1;
	tm.tm_mday = day;
	tm.tm_hour = hour;
	tm.tm_min = minute;

	time_t t = mktime(&tm);

	//printf("time %s --> %d\n\r", timestr, t);
	buf->st_atime = t;
	buf->st_mtime = t;
	buf->st_ctime = t;
	return 0;
}

int fatfs_scandir(const char *dirp, struct dirent ***namelist,
				  int (*filter)(const struct dirent *),
				  int (*compar)(const struct dirent **, const struct dirent **))
{
	int res;
	DIR *m_dir;
	//FILINFO m_fileinfo;
	//char path[1024];
	//char file[512];
	struct dirent *entry;
	//struct dirent **list = *namelist;
	struct dirent **list = NULL;
	int count = 0;
	int namelist_size = MAX_NAMELIST_SIZE;

	m_dir = malloc(sizeof(DIR));
	if (m_dir == NULL) {
		return -1;
	}

	list = (struct dirent **)malloc(MAX_NAMELIST_SIZE * sizeof(struct dirent *));

	if (!list) {
		free(m_dir);
		return -1;
	}

	res = f_opendir(m_dir, dirp);
	if (res > 0) {
		printf("opendir error (%d)\n\r", res);
		free(m_dir);
		free(list);
		return -1;
	}
	//m_dir = __wrap_opendir(dirp);
	//sprintf(path, "%s", dirp);
	if (m_dir) {
		for (;;) {
			// read directory
			entry = _fatfs_readdir(m_dir);
			if (entry != NULL) {
				if (filter && !filter(entry)) {
					free(entry);
					continue;
				}
			}
			if (!entry) {
				break;
			}
			//printf("%s  ", entry->d_name);
			list[count] = (struct dirent *)malloc(sizeof(struct dirent));
			memcpy(list[count], entry, sizeof(struct dirent));
			free(entry);
			count += 1;
			if (count >= namelist_size) {
				namelist_size += MAX_NAMELIST_SIZE;
				printf("reallocate size %d\r\n", namelist_size);
				struct dirent **list_new = (struct dirent **)realloc(list, namelist_size * sizeof(struct dirent *));
				if (!list_new) {
					printf("failed to realloc the list_new\r\n");
					if (list) {
						for (int j = 0; j < count; j++) {
							free(list[j]);
						}

					}
					count = -1;
					break;
				} else {
					list = list_new;
				}
			}
		}
	}
	if (count >= 0) {
		*namelist = list;
		if (compar) {
			qsort((void *)*namelist, count, sizeof(struct dirent *), (qsort_compar)compar);
		}
	} else {
		if (list) {
			free(list);
			list = NULL;
		}
	}
	//close directory
	res = _fatfs_closedir(m_dir);
	if (res < 0) {
		printf("_littlefs_closedir fail %d\r\n", res);
		if (m_dir) {
			free(m_dir);
		}
		if (list) {
			for (int j = 0; j < count; j++) {
				free(list[j]);
			}
			free(list);
		}
		return res;
	}
	if (m_dir) {
		free(m_dir);
	}
	return count;
}

int fatfs_putc(int character, vfs_file *finfo)
{
	FIL *fil = (FIL *)finfo->file;
	FRESULT res = f_putc((unsigned char)character, fil);
	if (res > 0) {
		return EOF;
	}
	return character;
}
int fatfs_puts(const char *str, vfs_file *finfo)
{
	FIL *fil = (FIL *)finfo->file;
	FRESULT res = f_puts(str, fil);
	if (res > 0) {
		return EOF;
	}
	return res;
}
char *fatfs_gets(char *str, int num, vfs_file *finfo)
{
	FIL *fil = (FIL *)finfo->file;
	char *res = f_gets(str, num, fil);
	if (res == 0) {
		return NULL;
	}
	return str;
}

int fatfs_mount(int interface)
{
	int ret = 0;
	if (interface == VFS_INF_SD || interface == VFS_INF_EMMC) {
		if (interface == VFS_INF_SD) {
			emmc_set_enable(0);
			printf("sd mount\r\n");
		} else {
			emmc_set_enable(1);
			printf("emmc mount\r\n");
		}
		ret = fatfs_sd_init();
	} else if (interface == VFS_INF_RAM) {
		printf("ram mount\r\n");
		ret = fatfs_ram_init();
	} else if (interface == VFS_INF_FLASH) {
		printf("flash mount\r\n");
		ret = fatfs_flash_init();
	} else {
		printf("It don't support the interface %d\r\n", interface);
		return -1;
	}
	return ret;
}

int fatfs_ummount(int interface)
{
	int ret = 0;
	if (interface == VFS_INF_SD || interface == VFS_INF_EMMC) {
		if (interface == VFS_INF_SD) {
			printf("sd unmount\r\n");
		} else {
			printf("emmc unmount\r\n");
		}
		ret = fatfs_sd_close();
	} else if (interface == VFS_INF_RAM) {
		printf("ram unmount\r\n");
		ret = fatfs_ram_close();
	} else if (interface == VFS_INF_FLASH) {
		printf("flash unmount\r\n");
		ret = fatfs_flash_close();
	} else {
		printf("It don't support the interface %d\r\n", interface);
		return -1;
	}
	return ret;
}

int fatfs_format(int interface)
{
	int ret = 0;
	if (interface == VFS_INF_SD || interface == VFS_INF_EMMC) {
		if (interface == VFS_INF_SD) {
			printf("sd format\r\n");
		} else {
			printf("emmc format\r\n");
		}
		ret = fatfs_sd_format(NULL);
	} else if (interface == VFS_INF_RAM) {
		printf("ram format\r\n");
		ret = fatfs_ram_format(NULL);
	} else if (interface == VFS_INF_FLASH) {
		printf("flash format\r\n");
		ret = fatfs_flash_format(NULL);
	} else {
		printf("It don't support the interface %d\r\n", interface);
		return -1;
	}
	if (ret) {
		ret = -1;
	}
	return ret;
}

vfs_opt fatfs_drv = {
	.open = fatfs_open,
	.read = fatfs_read,
	.write = fatfs_write,
	.close = fatfs_close,
	.seek  = fatfs_seek,
	.rewind = fatfs_rewind,
	.fgetpos = fatfs_fgetops,
	.fsetpos = fatfs_fsetops,
	.fflush = fatfs_fflush,
	.remove = fatfs_remove,
	.rename = fatfs_rename,
	.eof   = fatfs_feof,
	.error = fatfs_ferror, //ferror
	.tell  = fatfs_ftell,
	.ftruncate = fatfs_ftruncate,
	.opendir = fatfs_opendir,
	.readdir = fatfs_readdir,
	.closedir = fatfs_closedir,
	.mkdir = fatfs_mkdir,
	.rmdir = fatfs_rmdir,
	.stat = fatfs_stat,
	.access = fatfs_access,
	.scandir = fatfs_scandir,
	.fputc = fatfs_putc,
	.fputs = fatfs_puts,
	.fgets = fatfs_gets,
	.mount = fatfs_mount,
	.unmount = fatfs_ummount,
	.format = fatfs_format,
	.get_interface = fatfs_get_interface,
	.TAG	= "fatfs"
};
