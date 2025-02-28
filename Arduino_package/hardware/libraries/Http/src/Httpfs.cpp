#include <Arduino.h>
#include "Httpfs.h"

Httpfs::Httpfs(void)
{
    memset(httpfsParams.fileext, 0, sizeof(httpfsParams.fileext));
    strncpy(httpfsParams.fileext, "mp4", sizeof(httpfsParams.fileext));

    memset(httpfsParams.filedir, 0, sizeof(httpfsParams.filedir));
    strncpy(httpfsParams.filedir, "HTTPFS_VIDEO", sizeof(httpfsParams.filedir));

    memset(httpfsParams.request_string, 0, sizeof(httpfsParams.request_string));
    strncpy(httpfsParams.request_string, "/video_get.mp4", sizeof(httpfsParams.request_string));

    httpfsParams.fatfs_buf_size = 1024;
}

Httpfs::~Httpfs(void)
{
    if (_p_mmf_context == NULL) {
        return;
    }
    end();
    if (httpfsDeinit(_p_mmf_context) == NULL) {
        _p_mmf_context = NULL;
    } else {
        printf("\r\n[ERROR] Httpfs deinit failed\n");
    }
}

void Httpfs::begin(void)
{
    _p_mmf_context = httpfsInit();

    if (_p_mmf_context == NULL) {
        printf("\r\n[ERROR] Need Httpfs init first\n");
        return;
    }
    httpfsSetParams(_p_mmf_context, &httpfsParams);
    httpfsSetRespCB(_p_mmf_context);
    httpfsApply(_p_mmf_context);
}

void Httpfs::mp4DirectoryInit(void)
{
    fatfs_sd_get_param(&fatfs_sd);
    sprintf(sd_dirname, "%s", "HTTPFS_VIDEO");
    sprintf(sd_filename, "%s/%s", sd_dirname, "AmebaPro2_Recording");
    if (f_opendir(&m_dir, sd_dirname) == 0) {
        f_closedir(&m_dir);
    } else {
        f_mkdir(sd_dirname);
    }

    if (fatfs_get_free_space() < 50) {
        del_old_file();
    }

    if (fatfs_get_free_space() < 50) {
        rt_printf("ERROR: free space < 50MB\n\r");
    }
}

void Httpfs::end(void)
{
    if (_p_mmf_context == NULL) {
        printf("\r\n[ERROR] Need Httpfs init first\n");
    }
    httpfsDeinit(_p_mmf_context);
}

void Httpfs::del_old_file(void)
{
    DIR m_dir;
    FILINFO m_fileinfo;
    char *filename;
    char old_filename[64] = {0};
    char old_filepath[96] = {0};
    WORD filedate = 0, filetime = 0, old_filedate = 0, old_filetime = 0;
#if _USE_LFN
    char fname_lfn[32];
    m_fileinfo.lfname = fname_lfn;
    m_fileinfo.lfsize = sizeof(fname_lfn);
#endif

    if (f_opendir(&m_dir, sd_dirname) == 0) {
        while (1) {
            if ((f_readdir(&m_dir, &m_fileinfo) != 0) || m_fileinfo.fname[0] == 0) {
                break;
            }

#if _USE_LFN
            filename = *m_fileinfo.lfname ? m_fileinfo.lfname : m_fileinfo.fname;
#else
            filename = m_fileinfo.fname;
#endif
            if (strcmp(filename, ".") == 0 || strcmp(filename, "..") == 0) {
                continue;
            }

            if (!(m_fileinfo.fattrib & AM_DIR)) {
                filedate = m_fileinfo.fdate;
                filetime = m_fileinfo.ftime;

                if ((strlen(old_filename) == 0) || (filedate < old_filedate) || ((filedate == old_filedate) && (filetime < old_filetime))) {

                    old_filedate = filedate;
                    old_filetime = filetime;
                    strcpy(old_filename, filename);
                }
            }
        }

        f_closedir(&m_dir);

        if (strlen(old_filename)) {
            sprintf(old_filepath, "%s/%s", sd_dirname, old_filename);
            printf("del %s\n\r", old_filepath);
            f_unlink(old_filepath);
        }
    }
}
