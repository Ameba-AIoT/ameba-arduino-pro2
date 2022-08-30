#ifndef HAL_OSD_CODE_H
#define HAL_OSD_CODE_H

#define RT_CODE_BASE_FATAL		-100
#define RT_CODE_BASE_COMMON		-200
#define RT_CODE_BASE_SHELL		-300	// in rt_shell.x
#define RT_CODE_BASE_MTD		-400	// in rt_mtd.x
#define RT_CODE_BASE_FS			-500	// file system

// ----------------------------------------------------------------------------
// VERY IMPORTANT!!!
//  the below are compatible with rts_errno.h by rename RTS_XXX to RT_XXX.
//  since rtscore is ported in the project, please keep these error code defined
//  value same with rts_errno.h
// ----------------------------------------------------------------------------
#define RT_OK						0
#define RT_FAIL						-1
#define RT_E_NULL_POINT				-10
#define RT_E_NO_MEMORY				-11
#define RT_E_NOT_REALIZED			-12
#define RT_E_EXIST					-13
#define RT_E_NOT_EXIST				-14
#define RT_E_NOT_FOUND				-15
#define RT_E_NOT_REGISTERED			-16
#define RT_E_NOT_READY				-17
#define RT_E_EMPTY					-18
#define RT_E_NOT_EMPTY				-19
#define RT_E_FULL					-20
#define RT_E_INVALID_ARG			-21
#define RT_E_INVALID_TYPE			-22
#define RT_E_NOT_MATCH				-23
#define RT_E_OPEN_FAIL				-24
#define RT_E_CLOSE_FAIL				-25
#define RT_E_NOT_OPEN				-26
#define RT_E_GET_FAIL				-27
#define RT_E_SET_FAIL				-28
#define RT_E_NOT_SUPPORT			-29
#define RT_E_INITIALIZED			-30
#define RT_E_NOT_INITIALIZED		-31
#define RT_E_INUSE					-32
#define RT_E_WRITE_FAIL				-33
#define RT_E_READ_FAIL				-34
#define RT_E_LOCK_FAIL				-35
#define RT_E_INVALID_LENGTH			-36
#define RT_E_TIMEOUT				-37
#define RT_E_THREAD_FAIL			-38
#define RT_E_OVERFLOW				-39
#define RT_E_BIG					-40
#define RT_E_PERM					-41
#define RT_E_NO_ENT					-42
#define RT_E_IO						-43
#define RT_E_AGAIN					-44
#define RT_E_NO_DEV					-45
#define RT_E_NO_SYS					-46
#define RT_E_IOCTL					-47
#define RT_E_LESS_DATA				-48
#define RT_E_OUT_OF_RANGE			-49
#define RT_E_MMAP_FAIL				-50
#define RT_E_MUNMAP_FAIL			-51
#define RT_E_INVALID_DATA			-52
#define RT_E_NO_REALIZED			-53
#define RT_E_INVALID_VERSION		-54
#define RT_E_UNKNOWN				-55
#define RT_E_RECEIVE_FAIL			-56
#define RT_E_SEND_FAIL				-57
#define RT_E_DISCONNECT				-58
#define RT_E_SAVE_FAIL				-59
#define RT_E_CMP_FAIL				-60
#define RT_E_ERASE_FAIL				-61
#define RT_E_RESET_FAIL				-62
#define RT_E_DISABLE				-63
#define RT_E_NOT_EQUAL				-64
#define RT_E_EQUAL					-65
#define RT_E_CMD_ERROR				-66
#define RT_E_INVALID_CMD			-67
#define RT_E_MISMATCH				-68
#define RT_E_BUF_OVERFLOW			-69
#define RT_E_NOT_CROSS				-70
#define RT_E_NOT_PARALLEL			-71
#define RT_E_PARALLEL				-72
#define RT_E_CONFILCT				-73
#define RT_E_BUSY					-74
#define RT_E_CHANGED				-75

// fatal (serious) error
#define RT_E_INTERNAL_ERR		(RT_CODE_BASE_FATAL -  1)	// program internal error (programmer's error)
#define RT_E_HW_ERR				(RT_CODE_BASE_FATAL -  2)

// common error
#define RT_E_INIT_FAIL			(RT_CODE_BASE_COMMON -  1)
#define RT_E_NOT_INIT			(RT_CODE_BASE_COMMON -  2)
#define RT_E_ALREADY_INIT		(RT_CODE_BASE_COMMON -  3)
#define RT_E_ALREADY_OPEN		(RT_CODE_BASE_COMMON -  4)
#define RT_E_CREATE_FAIL		(RT_CODE_BASE_COMMON -  5)
#define RT_E_DELETE_FAIL		(RT_CODE_BASE_COMMON -  6)
#define RT_E_OPERATE_FAIL		(RT_CODE_BASE_COMMON -  7)
#define RT_E_LENGTH_MISMATCH	(RT_CODE_BASE_COMMON -  8)
#define RT_E_OP_NOT_ALLOW		(RT_CODE_BASE_COMMON -  9)
#define RT_E_NOT_ENOUGH_BUF		(RT_CODE_BASE_COMMON - 10)
#define RT_E_HW_NOT_INIT		(RT_CODE_BASE_COMMON - 11)
#define RT_E_ALREADY_DEINIT		(RT_CODE_BASE_COMMON - 12)
#define RT_E_ALREADY_START		(RT_CODE_BASE_COMMON - 13)
#define RT_E_ALREADY_STOP		(RT_CODE_BASE_COMMON - 14)
#define RT_E_WRONG_ALIGNMENT	(RT_CODE_BASE_COMMON - 15)
#define RT_E_NOT_START			(RT_CODE_BASE_COMMON - 16)
#define RT_E_DEINIT_FAIL		(RT_CODE_BASE_COMMON - 17)
#define	RT_E_NULL_OBJECT		(RT_CODE_BASE_COMMON - 18)
#define	RT_E_NULL_STRING		(RT_CODE_BASE_COMMON - 19)
#define RT_E_ALREADY_CREATE		(RT_CODE_BASE_COMMON - 20)
#define RT_E_ENCODE_FAIL		(RT_CODE_BASE_COMMON - 21)
#define RT_E_DECODE_FAIL		(RT_CODE_BASE_COMMON - 21)

#define RT_E_INVALID_PRECOND	(RT_CODE_BASE_COMMON - 50)	// invalid pre-condition
#define RT_E_INVALID_ENV_VAR	(RT_CODE_BASE_COMMON - 51)
#define RT_E_INVALID_PATH		(RT_CODE_BASE_COMMON - 52)
#define RT_E_INVALID_FORMAT		(RT_CODE_BASE_COMMON - 53)
#define RT_E_INVALID_SIZE		(RT_CODE_BASE_COMMON - 54)
#define RT_E_INVALID_ID			(RT_CODE_BASE_COMMON - 55)
#define RT_E_INVALID_STATE		(RT_CODE_BASE_COMMON - 56)
#define RT_E_INVALID_INDEX		(RT_CODE_BASE_COMMON - 57)
#define RT_E_INVALID_MODE		(RT_CODE_BASE_COMMON - 58)

// NOTE: plz ref to FRESULT in /drv/fs/plat_fatfs/r0.10c/include/ff.h
#define FRESULT_TO_RT_CODE(x)	((x) ? RT_CODE_BASE_FS-(x) : 0)
#define RT_CODE_TO_FRESULT(x)	((x) ? RT_CODE_BASE_FS-(x) : 0)
// for 1~19, plz do not modify!!
#define RT_E_FS_DISK_ERR			(RT_CODE_BASE_FS -  1)	// (1) A hard error occurred in the low level disk I/O layer
#define RT_E_FS_INT_ERR				(RT_CODE_BASE_FS -  2)	// (2) Assertion failed
#define RT_E_FS_NOT_READY			(RT_CODE_BASE_FS -  3)	// (3) The physical drive cannot work
#define RT_E_FS_NO_FILE				(RT_CODE_BASE_FS -  4)	// (4) Could not find the file
#define RT_E_FS_NO_PATH				(RT_CODE_BASE_FS -  5)	// (5) Could not find the path
#define RT_E_FS_INVALID_NAME		(RT_CODE_BASE_FS -  6)	// (6) The path name format is invalid
#define RT_E_FS_DENIED				(RT_CODE_BASE_FS -  7)	// (7) Access denied due to prohibited access or directory full
#define RT_E_FS_EXIST				(RT_CODE_BASE_FS -  8)	// (8) Access denied due to prohibited access
#define RT_E_FS_INVALID_OBJECT		(RT_CODE_BASE_FS -  9)	// (9) The file/directory object is invalid
#define RT_E_FS_WRITE_PROTECTED		(RT_CODE_BASE_FS - 10)	// (10) The physical drive is write protected
#define RT_E_FS_INVALID_DRIVE		(RT_CODE_BASE_FS - 11)	// (11) The logical drive number is invalid
#define RT_E_FS_NOT_ENABLED			(RT_CODE_BASE_FS - 12)	// (12) The volume has no work area
#define RT_E_FS_NO_FILESYSTEM		(RT_CODE_BASE_FS - 13)	// (13) There is no valid FAT volume
#define RT_E_FS_MKFS_ABORTED		(RT_CODE_BASE_FS - 14)	// (14) The f_mkfs() aborted due to any parameter error
#define RT_E_FS_TIMEOUT				(RT_CODE_BASE_FS - 15)	// (15) Could not get a grant to access the volume within defined period
#define RT_E_FS_LOCKED				(RT_CODE_BASE_FS - 16)	// (16) The operation is rejected according to the file sharing policy
#define RT_E_FS_NOT_ENOUGH_CORE		(RT_CODE_BASE_FS - 17)	// (17) LFN working buffer could not be allocated
#define RT_E_FS_TOO_MANY_OPEN_FILES	(RT_CODE_BASE_FS - 18)	// (18) Number of open files > _FS_SHARE
#define RT_E_FS_INVALID_PARAMETER	(RT_CODE_BASE_FS - 19)	// (19) Given parameter is invalid
//
#define RT_E_FS_REG_DISK_DRV		(RT_CODE_BASE_FS - 101)
#define RT_E_FS_MOUNT				(RT_CODE_BASE_FS - 102)
#define RT_E_FS_EOF					(RT_CODE_BASE_FS - 103)

#endif	// HAL_OSD_CODE_H
