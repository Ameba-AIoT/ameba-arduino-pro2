#ifndef _VFS_H
#define _VFS_H
#ifdef __cplusplus
extern "C" {
#endif

#include "stdio.h"
#include "time.h"

#define PATH_MAX 4096
#define MAX_FS_SIZE 4
#define MAX_USER_SIZE 4
#define MAX_READDIR_NUM 10
#define MAX_NAMELIST_SIZE 1000
typedef int(*qsort_compar)(const void *, const void *);

#define VFS_O_ACCMODE	0x00000003
#define VFS_O_RDONLY	0x00000000
#define VFS_O_WRONLY	0x00000001
#define VFS_O_RDWR		0x00000002
#define VFS_O_CREAT		0x00000100
#define VFS_O_EXCL		0X00000200
#define VFS_O_TRUNC		0x00001000
#define VFS_O_APPEND	0x00002000
#define VFS_O_CLOEXEC	0x02000000

#define VFS_FATFS       0X00
#define VFS_LITTLEFS    0X01

#define VFS_INF_SD      0x00
#define VFS_INF_RAM     0x01
#define VFS_INF_FLASH   0x02
#define VFS_INF_EMMC    0x03


#if !defined(S_IFDIR)
#define S_IFDIR 0x0040000
#endif
#if !defined(S_IFREG)
#define S_IFREG 0x0100000
#endif
#define DT_DIR S_IFDIR
#define DT_REG S_IFREG

#if __GNUC__ < 6
#ifndef __mode_t_defined
#define __mode_t __MODE_T_TYPE
#define __MODE_T_TYPE __U32_TYPE
#define __U32_TYPE unsigned int
typedef __mode_t mode_t;
#define __mode_t_defined
#endif
#endif

#ifdef feof
#undef feof
#endif

#ifdef DIR
#undef DIR
#endif
typedef void *DIR;
struct dirent {
	/* Always zero */
	long d_ino;

	/* File position within stream */
	long d_off;

	/* Structure size */
	unsigned short d_reclen;

	/* Length of name without \0 */
	size_t d_namlen;

	/* File type */
	int d_type;

	/* File name */
	char d_name[PATH_MAX + 1];
};
typedef struct dirent dirent;
#if __GNUC__ < 6
#if __GNUC__ < 5
typedef int dev_t;
typedef unsigned int ino_t;
//typedef int mode_t;
typedef int nlink_t;
typedef int uid_t;
typedef int gid_t;
typedef long int off_t;
#endif
typedef signed int blksize_t;
typedef signed int blkcnt_t;
#endif

struct stat {
	dev_t     st_dev;     /* ID of device containing file */
	ino_t     st_ino;     /* inode number */
	mode_t    st_mode;    /* protection */
	nlink_t   st_nlink;   /* number of hard links */
	uid_t     st_uid;     /* user ID of owner */
	gid_t     st_gid;     /* group ID of owner */
	dev_t     st_rdev;    /* device ID (if special file) */
	off_t     st_size;    /* total size, in bytes */
	blksize_t st_blksize; /* blocksize for file system I/O */
	blkcnt_t  st_blocks;  /* number of 512B blocks allocated */
	time_t    st_atime;   /* time of last access */
	time_t    st_mtime;   /* time of last modification */
	time_t    st_ctime;   /* time of last status change */
};

typedef struct _vfs_file {
	int vfs_id;//Reserve
	int interface_id;//Reserve
	void *file;
	char name[1024];
} vfs_file;

typedef struct {
	int (*open)(const char *filename, const char *mode, vfs_file *finfo);
	int (*read)(unsigned char *buf, unsigned int size, unsigned int count, vfs_file *file);
	int (*write)(unsigned char *buf, unsigned int size, unsigned int count, vfs_file *file);
	int (*close)(vfs_file *file);
	int (*seek)(long int offset, int origin, vfs_file *file);
	void (*rewind)(vfs_file *file);
	int (*fgetpos)(vfs_file *file);
	int (*fsetpos)(unsigned int offset, vfs_file *file);
	int (*fflush)(vfs_file *file);
	int (*remove)(const char *filename);
	int (*rename)(const char *old_name, const char *new_name);
	int (*eof)(vfs_file *file);
	int (*error)(vfs_file *file); //ferror
	int (*tell)(vfs_file *file);
	int (*ftruncate)(vfs_file *file, off_t length);
	int (*fputc)(int character, vfs_file *file);
	int (*fputs)(const char *str, vfs_file *file);
	char *(*fgets)(char *str, int num, vfs_file *file);
	int (*opendir)(const char *name, vfs_file *file);
	struct dirent   *(*readdir)(vfs_file *file);
	int (*closedir)(vfs_file *file);
	int (*scandir)(const char *dirp, struct dirent ***namelist, int (*filter)(const struct dirent *), int (*compar)(const struct dirent **,
				   const struct dirent **));
	int (*rmdir)(const char *path);
	int (*mkdir)(const char *pathname);
	int (*access)(const char *pathname, int mode);
	int (*stat)(char *path, struct stat *buf);
	int (*mount)(int interface);
	int (*unmount)(int interface);
	int (*get_interface)(int interface);
	int (*format)(int interface);
	const char	*TAG;
	unsigned char drv_num;
	void *fs;
	int vfs_type;
} vfs_opt;

typedef struct {
	int vfs_type;
	int vfs_type_id;
	int vfs_interface_type;
	const char *tag;
} user_config;

typedef struct {
	vfs_opt	*drv[MAX_FS_SIZE];
	unsigned int nbr;//Number file system
	unsigned int ibr;//Number interface
	user_config user[MAX_USER_SIZE];
} vfs_drv;

extern vfs_drv  vfs;//extern vfs_drv  vfs;
extern vfs_opt fatfs_drv;
extern vfs_opt littlefs_drv;

void vfs_init(void *parm);
void vfs_deinit(void *parm);
int vfs_user_register(const char *prefix, int vfs_type, int interface);
int vfs_user_unregister(const char *prefix, int vfs_type, int interface);
int vfs_scan_vfs(int vfs_type);
int vfs_register(vfs_opt *drv, int vfs_type);
int find_vfs_number(const char *name, int *prefix_len, int *user_id);
int vfs_user_mount(const char *prefix);
int vfs_user_format(const char *prefix, int vfs_type, int interface);
int vfs_status(void);
/* access function */
#define	F_OK		0	/* test for existence of file */
#define	X_OK		0x01	/* test for execute or search permission */
#define	W_OK		0x02	/* test for write permission */
#define	R_OK		0x04	/* test for read permission */

DIR *opendir(const char *name);
struct dirent *readdir(DIR *dirp);
int closedir(DIR *dirp);
int scandir(const char *dirp, struct dirent ***namelist,
			int (*filter)(const struct dirent *),
			int (*compar)(const struct dirent **, const struct dirent **));
int rmdir(const char *path);
int mkdir(const char *pathname, mode_t mode);
int access(const char *pathname, int mode);
int stat(const char *path, struct stat *buf);
int alphasort(const struct dirent **a, const struct dirent **b);
int ftruncate(FILE *fd, off_t length);

#ifdef __cplusplus
}
#endif
#endif