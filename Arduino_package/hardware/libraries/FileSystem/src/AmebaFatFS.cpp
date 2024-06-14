#include "Arduino.h"
#include "AmebaFatFS.h"

#ifdef __cplusplus
extern "C" {
#include "rtl8735b.h"
}
#endif

extern phal_sdhost_adapter_t psdioh_adapter;

AmebaFatFS::AmebaFatFS(void)
{
    // init to no card initialized
    fatfs_sd.drv_num = -1;
}

bool AmebaFatFS::begin(void)
{
    FRESULT res;

    res = (FRESULT)fatfs_sd_init();
    if (res != 0) {
        printf("\r\n[ERROR] fatfs_sd_init fail (%d)\n", res);
        fatfs_sd_close();
        return (res == FR_OK);
    }
    fatfs_sd_get_param(&fatfs_sd);

    return (res == FR_OK);
}

void AmebaFatFS::end(void)
{
    fatfs_sd_close();
    memset(&fatfs_sd, 0, sizeof(fatfs_sd_params_t));
    fatfs_sd.drv_num = -1;
}

File AmebaFatFS::open(const String &path)
{
    return open(path.c_str());
}

File AmebaFatFS::open(const char *path)
{
    if (fatfs_sd.drv_num < 0) {
        return File();
    }

    return File(path);
}

bool AmebaFatFS::exists(const String &path)
{
    return exists(path.c_str());
}

bool AmebaFatFS::exists(const char *path)
{
    if (fatfs_sd.drv_num < 0) {
        return 0;
    }

    FRESULT res;
    FILINFO finfo;

    res = f_stat(path, &finfo);
    return (res == FR_OK);
}

bool AmebaFatFS::remove(const String &path)
{
    return remove(path.c_str());
}

bool AmebaFatFS::remove(const char *path)
{
    if (fatfs_sd.drv_num < 0) {
        return 0;
    }

    FRESULT res = FR_OK;

    res = f_unlink(path);
    return (res == FR_OK);
}

bool AmebaFatFS::rename(const String &pathFrom, const String &pathTo)
{
    return rename(pathFrom.c_str(), pathTo.c_str());
}

bool AmebaFatFS::rename(const char *pathFrom, const char *pathTo)
{
    if (fatfs_sd.drv_num < 0) {
        return 0;
    }

    FRESULT res = FR_OK;

    res = f_rename(pathFrom, pathTo);
    return (res == FR_OK);
}

bool AmebaFatFS::mkdir(const String &path)
{
    return mkdir(path.c_str());
}

bool AmebaFatFS::mkdir(const char *path)
{
    if (fatfs_sd.drv_num < 0) {
        return 0;
    }

    FRESULT res = FR_OK;
    res = f_mkdir(path);
    return (res == FR_OK);
}

bool AmebaFatFS::rmdir(const String &path)
{
    return rmdir(path.c_str());
}

bool AmebaFatFS::rmdir(const char *path)
{
    if (fatfs_sd.drv_num < 0) {
        return 0;
    }

    FRESULT res = FR_OK;

    res = f_unlink(path);
    return (res == FR_OK);
}

char *AmebaFatFS::getRootPath(void)
{
    if (fatfs_sd.drv_num < 0) {
        return NULL;
    } else {
        return fatfs_sd.drv;
    }
}

int AmebaFatFS::readDir(char *path, char *result_buf, unsigned int bufsize)
{
    FRESULT res = FR_OK;
    FILINFO fileinfo;
    DIR dir;

    char *filename;
    unsigned int filelen;
    int bufidx = 0;

#if _USE_LFN && ((!defined(FATFS_R_13C)) && (!defined(FATFS_R_14B)))
    char fname_lfn[(_MAX_LFN + 1)];
    fileinfo.lfname = fname_lfn;
    fileinfo.lfsize = sizeof(fname_lfn);
#endif

    do {
        if (fatfs_sd.drv_num < 0) {
            res = FR_DISK_ERR;
            break;
        }

        res = f_opendir(&dir, path);
        if (res != FR_OK) {
            break;
        }

        memset(result_buf, 0, bufsize);

        while (1) {
            // call f_readdir repeatedly until all files in directory have been processed.
            res = f_readdir(&dir, &fileinfo);
            if ((res != FR_OK) || (fileinfo.fname[0] == 0)) {
                break;
            }

#if _USE_LFN && ((!defined(FATFS_R_13C)) && (!defined(FATFS_R_14B)))
            if (*fileinfo.lfname) {
                filename = fileinfo.lfname;
                filelen = fileinfo.lfsize;
            } else
#endif
            {
                filename = fileinfo.fname;
                filelen = strlen(filename);
            }

            if (*filename == '.' || (filename[0] == '.' && filename[1] == '.')) {
                continue;
            }

            // print file names into buffer
            // if (fileinfo.fattrib & AM_DIR) {
            if ((bufidx + filelen + 1) < bufsize) {
#ifdef Arduino_STD_PRINTF
                bufidx += sprintf((result_buf + bufidx), "%s", filename) + 1;
#else
                bufidx += sprintf((result_buf + bufidx), "%s", filename);
#endif
                // bufidx++;
            }
            //}
        }
    } while (0);

    return (-res);
}

bool AmebaFatFS::isDir(char *path)
{
    unsigned char attr;
    if (getAttribute(path, &attr) >= 0) {
        if (attr & AM_DIR) {
            return 1;
        }
    }
    return 0;
}

bool AmebaFatFS::isFile(char *path)
{
    unsigned char attr;
    if (getAttribute(path, &attr) >= 0) {
        if (attr & AM_ARC) {
            return 1;
        }
    }
    return 0;
}

int AmebaFatFS::getLastModTime(char *path, uint16_t *year, uint16_t *month, uint16_t *date, uint16_t *hour, uint16_t *minute, uint16_t *second)
{
    FRESULT res = FR_OK;
    FILINFO fileinfo;
#if _USE_LFN && ((!defined(FATFS_R_13C)) && (!defined(FATFS_R_14B)))
    char fname_lfn[(_MAX_LFN + 1)];
    fileinfo.lfname = fname_lfn;
    fileinfo.lfsize = sizeof(fname_lfn);
#endif

    do {
        if (fatfs_sd.drv_num < 0) {
            res = FR_DISK_ERR;
            break;
        }

        res = f_stat(path, &fileinfo);
        if (res != FR_OK) {
            break;
        }

        *year = (fileinfo.fdate >> 9) + 1980;
        *month = (fileinfo.fdate >> 5) & 0x0F;
        *date = (fileinfo.fdate & 0x1F);
        *hour = (fileinfo.ftime >> 11);
        *minute = (fileinfo.ftime >> 5) & 0x3F;
        *second = (fileinfo.ftime & 0x1F) * 2;

    } while (0);

    return (-res);
}

int AmebaFatFS::setLastModTime(char *path, uint16_t year, uint16_t month, uint16_t date, uint16_t hour, uint16_t minute, uint16_t second)
{
    FRESULT res = FR_OK;

    // #if FF_USE_CHMOD && !FF_FS_READONLY // f_utime is not available if these macros are not set
    FILINFO fileinfo;

#if _USE_LFN && ((!defined(FATFS_R_13C)) && (!defined(FATFS_R_14B)))
    char fname_lfn[(_MAX_LFN + 1)];
    fileinfo.lfname = fname_lfn;
    fileinfo.lfsize = sizeof(fname_lfn);
#endif

    do {
        if (fatfs_sd.drv_num < 0) {
            res = FR_DISK_ERR;
            break;
        }

        fileinfo.fdate = 0x0000 | ((year - 1980) << 9) | ((month & 0x0F) << 5) | (date & 0x1F);
        fileinfo.ftime = 0x0000 | ((hour & 0x1F) << 11) | ((minute & 0x3F) << 5) | ((second / 2) & 0x1F);
        res = f_utime(path, &fileinfo);
        if (res != FR_OK) {
            break;
        }
    } while (0);

    // #endif
    return (-res);
}

int AmebaFatFS::status(void)
{
    return fatfs_sd_is_inited();
}

int AmebaFatFS::getAttribute(char *path, unsigned char *attr)
{
    FRESULT res = FR_OK;
    FILINFO fileinfo;
#if _USE_LFN && ((!defined(FATFS_R_13C)) && (!defined(FATFS_R_14B)))
    char fname_lfn[(_MAX_LFN + 1)];
    fileinfo.lfname = fname_lfn;
    fileinfo.lfsize = sizeof(fname_lfn);
#endif

    do {
        if (fatfs_sd.drv_num < 0) {
            res = FR_DISK_ERR;
            break;
        }

        res = f_stat(path, &fileinfo);
        if (res != FR_OK) {
            break;
        }

        *attr = fileinfo.fattrib;
    } while (0);
    return (-res);
}
