#ifndef __HTTPFS_H__
#define __HTTPFS_H__

#include "VideoStream.h"
#include "AmebaFatFS.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "httpfs_drv.h"

#ifdef __cplusplus
}
#endif

class Httpfs: public MMFModule {
public:
    Httpfs(void);
    ~Httpfs(void);

    void begin(void);
    void mp4DirectoryInit(void);
    void end(void);

private:
    void del_old_file(void);
    DIR m_dir;
    httpfs_params_t httpfsParams;
    char sd_filename[64];
    char sd_dirname[32];
    fatfs_sd_params_t fatfs_sd;
};

#endif
