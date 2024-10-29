#ifndef _AMEBA_FATFS_H_
#define _AMEBA_FATFS_H_

#include "ff.h"

#ifdef __cplusplus
extern "C" {
#include "fatfs_sdcard_api.h"
}
#endif

#include "AmebaFatFSFile.h"

class AmebaFatFS {
public:
    AmebaFatFS(void);

    bool begin(void);
    void end(void);

    File open(const String &path);
    File open(const char *path);

    bool exists(const String &path);
    bool exists(const char *path);

    bool remove(const String &path);
    bool remove(const char *path);

    bool rename(const String &pathFrom, const String &pathTo);
    bool rename(const char *pathFrom, const char *pathTo);

    bool mkdir(const String &path);
    bool mkdir(const char *path);

    bool rmdir(const String &path);
    bool rmdir(const char *path);

    char *getRootPath(void);

    int readDir(char *path, char *result_buf, unsigned int bufsize);

    bool isDir(char *path);
    bool isFile(char *path);

    int getLastModTime(char *path, uint16_t *year, uint16_t *month, uint16_t *date, uint16_t *hour, uint16_t *minute, uint16_t *second);
    int setLastModTime(char *path, uint16_t year, uint16_t month, uint16_t date, uint16_t hour, uint16_t minute, uint16_t second);

    int status(void);
    long long int get_free_space(void);
    long long int get_used_space(void);
private:
    int getAttribute(char *path, unsigned char *attr);

    // structures containing FATFS parameters for sdcard drive
    fatfs_sd_params_t fatfs_sd;
};

#endif
