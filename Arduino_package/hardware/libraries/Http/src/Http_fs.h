#ifndef __HTTP_FS_H__
#define __HTTP_FS_H__

#include "VideoStream.h"
#include "AmebaFatFS.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "http_fs_drv.h"

#ifdef __cplusplus
}
#endif

class Http_fs: public MMFModule {
public:
    Http_fs(void);
    ~Http_fs(void);

    void begin(void);
    void mp4DirectoryInit(void);
    void end(void);

private:
    void del_old_file(void);
    DIR m_dir;
    httpfs_params_t http_fsParams;
    char sd_filename[64];
    char sd_dirname[32];
    fatfs_sd_params_t fatfs_sd;
};

#endif
