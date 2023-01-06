#include "Arduino.h"
#include "AmebaFatFS.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "rtl8735b.h"

#ifdef __cplusplus
}
#endif

extern phal_sdhost_adapter_t psdioh_adapter;

AmebaFatFS::AmebaFatFS(void) {
    // init to no card intialized
    fatfs_sd.drv_num = -1;
}

bool AmebaFatFS::begin(void) {
    FRESULT res;

    res = (FRESULT)fatfs_sd_init();
    if (res != 0) {
        printf("fatfs_sd_init fail (%d)\r\n", res);
        return (res == FR_OK);
    }
    fatfs_sd_get_param(&fatfs_sd);

    return (res == FR_OK);
}

void AmebaFatFS::end(void) {
    fatfs_sd_close();
    memset(&fatfs_sd, 0, sizeof(fatfs_sd_params_t));
    fatfs_sd.drv_num = -1;
}

File AmebaFatFS::open(const String& path) {
    return open(path.c_str());
}

File AmebaFatFS::open(const char* path) {
    if (fatfs_sd.drv_num < 0) {
        return File();
    }

    return File(path);
}

bool AmebaFatFS::exists(const String& path) {
    return exists(path.c_str());
}

bool AmebaFatFS::exists(const char* path) {
    if (fatfs_sd.drv_num < 0) {
        return 0;
    }

    FRESULT ret;
    FILINFO finfo;

    ret = f_stat(path, &finfo);
    return (ret == FR_OK);
}

bool AmebaFatFS::remove(const String& path) {
    return remove(path.c_str());
}

bool AmebaFatFS::remove(const char* path) {
    if (fatfs_sd.drv_num < 0) {
        return 0;
    }

    FRESULT ret = FR_OK;

    ret = f_unlink(path);
    return (ret == FR_OK);
}

bool AmebaFatFS::rename(const String& pathFrom, const String& pathTo) {
    return rename(pathFrom.c_str(), pathTo.c_str());
}

bool AmebaFatFS::rename(const char* pathFrom, const char* pathTo) {
    if (fatfs_sd.drv_num < 0) {
        return 0;
    }

    FRESULT ret = FR_OK;

    ret = f_rename(pathFrom, pathTo);
    return (ret == FR_OK);
}

bool AmebaFatFS::mkdir(const String &path) {
    return mkdir(path.c_str());
}

bool AmebaFatFS::mkdir(const char *path) {
    if (fatfs_sd.drv_num < 0) {
        return 0;
    }

    FRESULT ret = FR_OK;
    ret = f_mkdir(path);
    return (ret == FR_OK);
}

bool AmebaFatFS::rmdir(const String &path) {
    return rmdir(path.c_str());
}

bool AmebaFatFS::rmdir(const char *path) {
    if (fatfs_sd.drv_num < 0) {
        return 0;
    }

    FRESULT ret = FR_OK;

    ret = f_unlink(path);
    return (ret == FR_OK);
}

char *AmebaFatFS::getRootPath(void) {
    if (fatfs_sd.drv_num < 0) {
        return NULL;
    } else {
        return fatfs_sd.drv;
    }
}

int AmebaFatFS::readDir(char *path, char *result_buf, unsigned int bufsize) {
    FRESULT ret = FR_OK;
    FILINFO fno;
    DIR dir;

    char *fn;
    unsigned int fnlen;
    int bufidx = 0;

#if _USE_LFN && ((!defined(FATFS_R_13C)) && (!defined(FATFS_R_14B)))
    char lfn[(_MAX_LFN + 1)];
    fno.lfname = lfn;
    fno.lfsize = sizeof(lfn);
#endif

    do {
        if (fatfs_sd.drv_num < 0) {
            ret = FR_DISK_ERR;
            break;
        }

        ret = f_opendir(&dir, path);
        if (ret != FR_OK) {
            break;
        }

        memset(result_buf, 0, bufsize);

        while (1) {
            // call f_readdir repeatedly until all files in directory have been processed.
            ret = f_readdir(&dir, &fno);
            if ((ret != FR_OK) || (fno.fname[0] == 0)) {
                break;
            }

#if _USE_LFN && ((!defined(FATFS_R_13C)) && (!defined(FATFS_R_14B)))
            if (*fno.lfname)
            {
                fn = fno.lfname;
                fnlen = fno.lfsize;
            }
            else
#endif
            {
                fn = fno.fname;
                fnlen = strlen(fn);
            }

            // print file names into buffer
            if ((bufidx + fnlen + 1) < bufsize) {
                bufidx += sprintf((result_buf + bufidx), "%s", fn);
                //bufidx++;
            }
        }
    } while (0);

    return (-ret);
}

bool AmebaFatFS::isDir(char *path) {
    unsigned char attr;
    if (getAttribute(path, &attr) >= 0) {
        if (attr & AM_DIR) {
            return 1;
        }
    }
    return 0;
}

bool AmebaFatFS::isFile(char *path) {
    unsigned char attr;
    if (getAttribute(path, &attr) >= 0) {
        if (attr & AM_ARC) {
            return 1;
        }
    }
    return 0;
}

int AmebaFatFS::getLastModTime(char *path, uint16_t *year, uint16_t *month, uint16_t *date, uint16_t *hour, uint16_t *minute, uint16_t *second) {
    FRESULT ret = FR_OK;
    FILINFO fno;
#if _USE_LFN && ((!defined(FATFS_R_13C)) && (!defined(FATFS_R_14B)))
    char lfn[(_MAX_LFN + 1)];
    fno.lfname = lfn;
    fno.lfsize = sizeof(lfn);
#endif

    do {
        if (fatfs_sd.drv_num < 0) {
            ret = FR_DISK_ERR;
            break;
        }

        ret = f_stat(path, &fno);
        if (ret != FR_OK) {
            break;
        }

        *year   = (fno.fdate >> 9) + 1980;
        *month  = (fno.fdate >> 5) & 0x0F;
        *date   = (fno.fdate & 0x1F);
        *hour   = (fno.ftime >> 11);
        *minute = (fno.ftime >> 5) & 0x3F;
        *second = (fno.ftime & 0x1F) * 2;

    } while (0);

    return (-ret);
}

int AmebaFatFS::setLastModTime(char *path, uint16_t year, uint16_t month, uint16_t date, uint16_t hour, uint16_t minute, uint16_t second) {
    FRESULT ret = FR_OK;

//#if FF_USE_CHMOD && !FF_FS_READONLY // f_utime is not available if these macros are not set
    FILINFO fno;

#if _USE_LFN && ((!defined(FATFS_R_13C)) && (!defined(FATFS_R_14B)))
    char lfn[(_MAX_LFN + 1)];
    fno.lfname = lfn;
    fno.lfsize = sizeof(lfn);
#endif

    do {
        if (fatfs_sd.drv_num < 0) {
            ret = FR_DISK_ERR;
            break;
        }

        fno.fdate = 0x0000 | ((year - 1980) <<  9) | ((month  & 0x0F) << 5) | (date & 0x1F);
        fno.ftime = 0x0000 | ((hour & 0x1F) << 11) | ((minute & 0x3F) << 5) | ((second/2) & 0x1F) ;
        ret = f_utime(path, &fno);
        if (ret != FR_OK) {
            break;
        }
    } while (0);
    
//#endif
    return (-ret);
}

int AmebaFatFS::status(void) {
    return fatfs_sd_is_inited();
}

int AmebaFatFS::getAttribute(char *path, unsigned char *attr) {
    FRESULT ret = FR_OK;
    FILINFO fno;
#if _USE_LFN && ((!defined(FATFS_R_13C)) && (!defined(FATFS_R_14B)))
    char lfn[(_MAX_LFN + 1)];
    fno.lfname = lfn;
    fno.lfsize = sizeof(lfn);
#endif

    do {
        if (fatfs_sd.drv_num < 0) {
            ret = FR_DISK_ERR;
            break;
        }

        ret = f_stat(path, &fno);
        if (ret != FR_OK) {
            break;
        }

        *attr = fno.fattrib;
    } while (0);

    return -ret;
}
