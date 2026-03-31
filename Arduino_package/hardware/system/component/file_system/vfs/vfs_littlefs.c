#include <stdio.h>
//#include "fatfs_wrap.h"
#include "time.h"

#include "FreeRTOS.h"
#include <cmsis.h>
#include "task.h"
#include <stdint.h>
#include <stdlib.h>
#include "section_config.h"
#include "lfs.h"
#include "lfs_util.h"
#include "snand_api.h"
#include "ftl_common_api.h"
#include "vfs.h"
#include "lfs_reent.h"
static lfs_t lfs;

/* FLASH_FILESYS_SIZE defined in platform_opts.h */
#define NOR_BLOCK_COUNT         (FLASH_FILESYS_SIZE / NOR_FLASH_SECTOR)
#define NAND_FLASH_BLOCK_COUNT  (FLASH_FILESYS_SIZE / NAND_FLASH_BLOCK_SIZE)

int vfs_ftl_block_read(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size);
int vfs_ftl_block_prog(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, const void *buffer, lfs_size_t size);
int vfs_ftl_block_erase(const struct lfs_config *c, lfs_block_t block);
int vfs_ftl_block_sync(const struct lfs_config *c);

struct lfs_config vfs_ftl_cfg = {
	// block device operations
	.read  = vfs_ftl_block_read,
	.prog  = vfs_ftl_block_prog,
	.erase = vfs_ftl_block_erase,
	.sync  = vfs_ftl_block_sync,
	.lock  =  lfs_system_lock,
	.unlock = lfs_system_unlock,

	// block device configuration
	.read_size = 0,
	.prog_size = 0,
	.block_size = 0,
	.block_count = 0,
	.cache_size = 0,
	.block_cycles = 100,
	.lookahead_size = 0
	//.lookahead_buffer = 256,
};

int vfs_ftl_block_read(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size)
{
	int ret = 0;
	if (sys_get_boot_sel() == FTL_NAND_FLASH) {
		ret = ftl_common_read(((NAND_APP_BASE / vfs_ftl_cfg.block_size) + block) * c->block_size + off, buffer, size);
	} else {
		ftl_common_read(block * c->block_size + FLASH_APP_BASE + off, buffer, size);
	}
	if (ret == 0) {
		ret = LFS_ERR_OK;
	} else {
		ret = LFS_ERR_IO;
	}
	return ret;
}
int vfs_ftl_block_prog(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, const void *buffer, lfs_size_t size)
{
	int ret = 0;
	if (sys_get_boot_sel() == FTL_NAND_FLASH) {
		ret = ftl_common_write(((NAND_APP_BASE / vfs_ftl_cfg.block_size) + block) * c->block_size + off, (unsigned char *)buffer, size);
	} else {
		ftl_common_write(block * c->block_size + FLASH_APP_BASE + off, (unsigned char *)buffer, size);
	}
	if (ret == 0) {
		ret = LFS_ERR_OK;
	} else {
		ret = LFS_ERR_IO;
	}
	return ret;
}
int vfs_ftl_block_erase(const struct lfs_config *c, lfs_block_t block)
{
	int ret = 0;
	if (sys_get_boot_sel() == FTL_NAND_FLASH) {
		ret = ftl_common_erase(((NAND_APP_BASE / vfs_ftl_cfg.block_size) + block) * c->block_size);
	} else {
		ftl_common_erase(block * c->block_size + FLASH_APP_BASE);
	}
	if (ret == 0) {
		ret = LFS_ERR_OK;
	} else {
		ret = LFS_ERR_IO;
	}
	return ret;
}
int vfs_ftl_block_sync(const struct lfs_config *c)
{
	return 0;
}

int vfs_little_fs_init(void)
{
	int ret = 0;
	int type, page_size, block_size, block_cnt = 0;
	ftl_common_info(&type, &page_size, &block_size, &block_cnt);
	printf("type %d page_size %d block_size %d block_cnt %d\r\n", type, page_size, block_size, block_cnt);

	if (type == 0) {
		printf("It is nor flash\r\n");
		vfs_ftl_cfg.read_size = page_size;
		vfs_ftl_cfg.prog_size = page_size;
		vfs_ftl_cfg.block_size = page_size;
		vfs_ftl_cfg.block_count = NOR_BLOCK_COUNT;
		vfs_ftl_cfg.cache_size = page_size;
		vfs_ftl_cfg.block_cycles = 100;
		vfs_ftl_cfg.lookahead_size = page_size;
	} else {
		printf("It is nand flash\r\n");
		//cfg = &nand_cfg;
		vfs_ftl_cfg.read_size = page_size;
		vfs_ftl_cfg.prog_size = page_size;
		vfs_ftl_cfg.block_size = block_size;
		vfs_ftl_cfg.block_count = NAND_FLASH_BLOCK_COUNT;
		vfs_ftl_cfg.cache_size = page_size;
		vfs_ftl_cfg.block_cycles = 100;
		vfs_ftl_cfg.lookahead_size = page_size;
	}

	// mount the filesystem
	ret = lfs_mount(&lfs, &vfs_ftl_cfg);
	// reformat if we can't mount the filesystem
	// this should only happen on the first boot
	if (ret) {
		ret = lfs_format(&lfs, &vfs_ftl_cfg);
		if (ret) {
			printf("lfs_format fail %d\r\n", ret);
			goto EXIT;
		}
		ret = lfs_mount(&lfs, &vfs_ftl_cfg);
		if (ret < 0) {
			printf("lfs_mount fail %d\r\n", ret);
			goto EXIT;
		}
	}
	return 0;
EXIT:
	return -1;
}

int littlefs_format(int interface)
{
	int ret = 0;
	int type, page_size, block_size, block_cnt = 0;
	ftl_common_info(&type, &page_size, &block_size, &block_cnt);
	printf("type %d page_size %d block_size %d block_cnt %d\r\n", type, page_size, block_size, block_cnt);

	if (type == 0) {
		printf("It is nor flash\r\n");
		vfs_ftl_cfg.read_size = page_size;
		vfs_ftl_cfg.prog_size = page_size;
		vfs_ftl_cfg.block_size = page_size;
		vfs_ftl_cfg.block_count = NOR_BLOCK_COUNT;//You need to setup the nor sector count
		vfs_ftl_cfg.cache_size = page_size;
		vfs_ftl_cfg.block_cycles = 100;
		vfs_ftl_cfg.lookahead_size = page_size;
	} else {
		printf("It is nand flash\r\n");
		//cfg = &nand_cfg;
		vfs_ftl_cfg.read_size = page_size;
		vfs_ftl_cfg.prog_size = page_size;
		vfs_ftl_cfg.block_size = block_size;
		vfs_ftl_cfg.block_count = NAND_FLASH_BLOCK_COUNT;
		vfs_ftl_cfg.cache_size = page_size;
		vfs_ftl_cfg.block_cycles = 100;
		vfs_ftl_cfg.lookahead_size = page_size;
	}
	ret = lfs_format(&lfs, &vfs_ftl_cfg);
	if (ret < 0) {
		printf("lfs_format fail %d\r\n", ret);
		goto EXIT;
	}
	ret = lfs_mount(&lfs, &vfs_ftl_cfg);
	if (ret < 0) {
		printf("lfs_mount fail %d\r\n", ret);
		goto EXIT;
	}
	return 0;
EXIT:
	return -1;
}

int fmodeflags(const char *mode)
{
	int flags;
	if (strchr(mode, '+')) {
		flags = VFS_O_RDWR;
	} else if (*mode == 'r') {
		flags = VFS_O_RDONLY;
	} else {
		flags = VFS_O_WRONLY;
	}
	if (strchr(mode, 'x')) {
		flags |= VFS_O_EXCL;
	}
	if (strchr(mode, 'e')) {
		flags |= VFS_O_CLOEXEC;
	}
	if (*mode != 'r') {
		flags |= VFS_O_CREAT;
	}
	if (*mode == 'w') {
		flags |= VFS_O_TRUNC;
	}
	if (*mode == 'a') {
		flags |= VFS_O_APPEND;
	}
	return flags;
}

int littlefs_open(const char *filename, const char *mode, vfs_file *finfo)
{
	int ret = 0;
	int flags = fmodeflags(mode);
	int mode_flag = 0;
	lfs_file_t *file = malloc(sizeof(lfs_file_t));
	if (file == NULL) {
		return -1;
	}

	if ((flags & 3) == VFS_O_RDONLY) {
		mode_flag |= LFS_O_RDONLY;
	}
	if ((flags & 3) == VFS_O_WRONLY) {
		mode_flag |= LFS_O_WRONLY;
	}
	if ((flags & 3) == VFS_O_RDWR) {
		mode_flag |= LFS_O_RDWR;
	}
	if (flags & VFS_O_CREAT) {
		mode_flag |= LFS_O_CREAT;
	}
	if (flags & VFS_O_EXCL) {
		mode_flag |= LFS_O_EXCL;
	}
	if (flags & VFS_O_TRUNC) {
		mode_flag |= LFS_O_TRUNC;
	}
	if (flags & VFS_O_APPEND) {
		mode_flag |= LFS_O_APPEND;
	}

	ret = lfs_file_open(&lfs, file, filename, mode_flag);
	if (ret < 0) {
		free(file);
		return ret;
	}
	printf("Open file mode 0x%x\n\r", mode_flag);
	finfo->file = (void *)file;
	return ret;
}

int littlefs_read(unsigned char *buf, unsigned int size, unsigned int count, vfs_file *finfo)
{
	int ret = 0;
	lfs_file_t *file = (lfs_file_t *)finfo->file;
	ret = lfs_file_read(&lfs, file, buf, size * count);
	if (ret < 0) {
		return ret;
	}
	return ret / size;
}

int littlefs_write(unsigned char *buf, unsigned int size, unsigned int count, vfs_file *finfo)
{
	int ret = 0;
	lfs_file_t *file = (lfs_file_t *)finfo->file;
	ret = lfs_file_write(&lfs, file, buf, size * count);
	if (ret < 0) {
		return ret;
	}
	return ret / size;
}

int littlefs_close(vfs_file *finfo)
{
	int ret = 0;
	lfs_file_t *file = (lfs_file_t *)finfo->file;
	if (file) {
		ret = lfs_file_close(&lfs, file);
		free(file);
	}
	return ret;
}

int littlefs_seek(long int offset, int origin, vfs_file *finfo)
{
	int ret = 0;
	lfs_file_t *file = (lfs_file_t *)finfo->file;
	switch (origin) {
	case SEEK_SET:
		ret = lfs_file_seek(&lfs, file, offset, LFS_SEEK_SET);
		break;
	case SEEK_CUR:
		ret = lfs_file_seek(&lfs, file, offset, LFS_SEEK_CUR);
		break;
	case SEEK_END:
		ret = lfs_file_seek(&lfs, file, offset, LFS_SEEK_END);
		break;
	}
	return ret < 0 ? ret : 0;
}

void littlefs_rewind(vfs_file *finfo)
{
	int ret = 0;
	lfs_file_t *file = (lfs_file_t *)finfo->file;
	ret = lfs_file_rewind(&lfs, file);
}

int littlefs_fgetops(vfs_file *finfo)
{
	int location = 0;
	lfs_file_t *file = (lfs_file_t *)finfo->file;
	location = lfs_file_tell(&lfs, file);
	return location;
}

int littlefs_fsetops(unsigned int offset, vfs_file *finfo)
{
	int ret = 0;
	lfs_file_t *file = (lfs_file_t *)finfo->file;
	ret = lfs_file_seek(&lfs, file, offset, LFS_SEEK_SET);
	return ret;
}

int littlefs_fflush(vfs_file *finfo)
{
	int ret = 0;
	lfs_file_t *file = (lfs_file_t *)finfo->file;
	ret = lfs_file_sync(&lfs, file);
	return ret;
}

int littlefs_remove(const char *name)
{
	int ret = 0;
	ret = lfs_remove(&lfs, name);
	return ret;
}

int littlefs_rename(const char *old_name, const char *new_name)
{
	int ret = 0;
	ret = lfs_rename(&lfs, old_name, new_name);
	return ret;
}

int littlefs_feof(vfs_file *finfo)
{
	int location = 0;//lfs_file_size
	int size = 0;
	lfs_file_t *file = (lfs_file_t *)finfo->file;
	location = lfs_file_tell(&lfs, file);
	size = lfs_file_size(&lfs, file);
	if ((size - location) <= 0) {
		printf("End of file\r\n");
		return 1;
	} else {
		printf("Remain %d\r\n", size - location);
		return 0;
	}
}

int littlefs_ferror(vfs_file *finfo)
{
	return 0;
}

int littlefs_ftell(vfs_file *finfo)
{
	int location = 0;
	lfs_file_t *file = (lfs_file_t *)finfo->file;
	location = lfs_file_tell(&lfs, file);
	return location;
}

int littlefs_ftruncate(vfs_file *finfo, off_t length)
{
	int ret = 0;
	lfs_file_t *file = (lfs_file_t *)finfo->file;
	ret = lfs_file_truncate(&lfs, file, length);
	if (ret < 0) {
		return -1;
	}
	return 0;
}

int littlefs_opendir(const char *name, vfs_file *finfo)
{
	lfs_dir_t *dir = malloc(sizeof(lfs_dir_t));
	if (dir == NULL) {
		return -1;
	}
	memset(dir, 0, sizeof(lfs_dir_t));

	int err = lfs_dir_open(&lfs, dir, name);
	if (err) {
		free(dir);
		return err;
	}
	finfo->file = (void *)dir;
	return err;
}
extern struct dirent *vfs_get_dir(void);
struct dirent *littlefs_readdir(vfs_file *finfo)
{
	lfs_dir_t *dir = (lfs_dir_t *)finfo->file;
	struct stat s;
	struct lfs_info info;
	struct dirent *ent = vfs_get_dir();
	if (ent == NULL) {
		return NULL;
	}
	memset(ent, 0, sizeof(struct dirent));
	int err = lfs_dir_read(&lfs, dir, &info);
	if (err <= 0) {
		return NULL;
	}
	if (info.name[0] == 0) {
		return NULL;
	}
	ent->d_ino = 0;
	ent->d_off = 0;
	ent->d_reclen = info.size;
	if (info.type == LFS_TYPE_DIR) {
		ent->d_type = DT_DIR;
	} else {
		ent->d_type = DT_REG;
	}
	snprintf(ent->d_name, PATH_MAX + 1, "%s", info.name);
	return ent;
}

struct dirent *_littlefs_readdir(lfs_dir_t *dir)
{
	struct stat s;
	struct lfs_info info;
	struct dirent *ent = malloc(sizeof(struct dirent));
	if (ent == NULL) {
		return NULL;
	}
	memset(ent, 0, sizeof(struct dirent));
	int err = lfs_dir_read(&lfs, dir, &info);

	if (err <= 0) {
		free(ent);
		return NULL;
	}
	if (info.name[0] == 0) {
		free(ent);
		return NULL;
	}
	ent->d_ino = 0;
	ent->d_off = 0;
	ent->d_reclen = info.size;
	if (info.type == LFS_TYPE_DIR) {
		ent->d_type = DT_DIR;
	} else {
		ent->d_type = DT_REG;
	}
	snprintf(ent->d_name, PATH_MAX + 1, "%s", info.name);
	return ent;
}

int littlefs_closedir(vfs_file *finfo)
{
	int ret = 0;
	lfs_dir_t *dir = (lfs_dir_t *)finfo->file;
	ret = lfs_dir_close(&lfs, dir);
	free(dir);
	if (ret < 0) {
		printf("Close directory fail: %d\r\n", ret);
	}
	return ret;
}

int _littlefs_closedir(lfs_dir_t *dir)
{
	int ret = 0;
	ret = lfs_dir_close(&lfs, dir);
	if (ret < 0) {
		printf("Close directory fail: %d\r\n", ret);
	}
	return ret;
}

int littlefs_mkdir(const char *pathname)
{
	int ret = 0;
	ret = lfs_mkdir(&lfs, pathname);
	if (ret < 0) {
		printf("lfs_mkdir fail %d\r\n", ret);
	}
	return ret;
}

int littlefs_rmdir(const char *path)
{
	int ret = 0;
	ret = lfs_remove(&lfs, path);
	return ret;
}

int littlefs_access(const char *pathname, int mode)
{
	struct lfs_info info;
	int ret = 0;
	ret = lfs_stat(&lfs, pathname, &info);
	if (ret < 0) {
		return -1;
	} else {
		return ret;
	}
}

int littlefs_stat(char *path, struct stat *buf)
{
	struct lfs_info info;
	int ret = 0;
	ret = lfs_stat(&lfs, path, &info);
	if (ret < 0) {
		return -1;
	}
	buf->st_dev = 0;
	buf->st_ino = 0;
	mode_t st_mode = 0;
	if (info.type == LFS_TYPE_DIR) {
		st_mode |= (S_IFDIR | 0x777);
	} else {
		st_mode |= (S_IFREG | 0x777);
	}

	buf->st_mode = st_mode;
	buf->st_nlink = 0;
	buf->st_uid = 0;
	buf->st_gid = 0;
	buf->st_rdev = 0;
	buf->st_size = info.size;
	buf->st_blksize = 0;
	buf->st_blocks = 0;
	buf->st_atime = 0;
	buf->st_mtime = 0;
	buf->st_ctime = 0;
	return ret;
}

int littlefs_scandir(const char *dirp, struct dirent ***namelist,
					 int (*filter)(const struct dirent *),
					 int (*compar)(const struct dirent **, const struct dirent **))
{
	lfs_dir_t *dir = malloc(sizeof(lfs_dir_t));
	//char path[1024] = {0};
	int ret = 0;
	struct dirent *entry;
	//struct dirent **list = *namelist;
	struct dirent **list = NULL;
	int count = 0;
	int namelist_size = MAX_NAMELIST_SIZE;

	if (dir == NULL) {
		return -1;
	}

	memset(dir, 0, sizeof(lfs_dir_t));
	int err = lfs_dir_open(&lfs, dir, dirp);
	if (err) {
		free(dir);
		return err;
	}

	list = (struct dirent **)malloc(MAX_NAMELIST_SIZE * sizeof(struct dirent *));

	if (!list) {
		free(dir);
		return -1;
	}

	//snprintf(path, sizeof(path), "%s", dirp);
	for (;;) {
		// read directory
		entry = _littlefs_readdir(dir);
		if (entry != NULL) {
			if (filter && !filter(entry)) {
				free(entry);
				continue;
			}
		}
		if (!entry) {
			break;
		}
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
	ret = _littlefs_closedir(dir);
	if (ret != 0) {
		printf("_littlefs_closedir fail %d\r\n", ret);
		if (dir) {
			free(dir);
		}
		if (list) {
			for (int j = 0; j < count; j++) {
				free(list[j]);
			}
			free(list);
		}
		return ret;
	}

	if (dir) {
		free(dir);
	}
	return count;
}

int littlefs_putc(int character, vfs_file *finfo)
{
	return -1;
}
int littlefs_puts(const char *str, vfs_file *finfo)
{
	return -1;
}
char *littlefs_gets(char *str, int num, vfs_file *finfo)
{
	return NULL;
}

int littlefs_mount(int interface)
{
	int ret = 0;
	ret = vfs_little_fs_init();
	printf("Littlefs mount\r\n");
	return ret;
}

int littlefs_unmount(int interface)
{
	int ret = 0;
	ret = lfs_unmount(&lfs);
	printf("Littlefs unmount\r\n");
	return ret;
}

vfs_opt littlefs_drv = {
	.open = littlefs_open,
	.read = littlefs_read,
	.write = littlefs_write,
	.close = littlefs_close,
	.seek  = littlefs_seek,
	.rewind = littlefs_rewind,
	.fgetpos = littlefs_fgetops,
	.fsetpos = littlefs_fsetops,
	.fflush = littlefs_fflush,
	.remove = littlefs_remove,
	.rename = littlefs_rename,
	.eof   = littlefs_feof,
	.error = littlefs_ferror, //ferror
	.tell  = littlefs_ftell,
	.ftruncate = littlefs_ftruncate,
	.opendir = littlefs_opendir,
	.readdir = littlefs_readdir,
	.closedir = littlefs_closedir,
	.mkdir = littlefs_mkdir,
	.rmdir = littlefs_rmdir,
	.stat = littlefs_stat,
	.access = littlefs_access,
	.scandir = littlefs_scandir,
	.fputc = littlefs_putc,
	.fputs = littlefs_puts,
	.fgets = littlefs_gets,
	.mount = littlefs_mount,
	.unmount = littlefs_unmount,
	.format = littlefs_format,
	.TAG	= "littlefs"
};