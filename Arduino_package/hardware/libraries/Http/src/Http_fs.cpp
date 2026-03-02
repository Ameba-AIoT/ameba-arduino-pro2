#include <Arduino.h>
#include "Http_fs.h"

Http_fs::Http_fs(void)
{
    memset(http_fsParams.fileext, 0, sizeof(http_fsParams.fileext));
    strncpy(http_fsParams.fileext, "mp4", sizeof(http_fsParams.fileext));

    memset(http_fsParams.filedir, 0, sizeof(http_fsParams.filedir));
    strncpy(http_fsParams.filedir, "HTTP_FS_VIDEO", sizeof(http_fsParams.filedir));

    memset(http_fsParams.request_string, 0, sizeof(http_fsParams.request_string));
    strncpy(http_fsParams.request_string, "/video_get.mp4", sizeof(http_fsParams.request_string));

    http_fsParams.fatfs_buf_size = 1024;
}

Http_fs::~Http_fs(void)
{
    if (_p_mmf_context == NULL) {
        return;
    }
    end();
    if (http_fs_Deinit(_p_mmf_context) == NULL) {
        _p_mmf_context = NULL;
    } else {
        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] Http_fs deinit failed\n");
    }
}

void Http_fs::begin(void)
{
    _p_mmf_context = http_fs_Init();

    if (_p_mmf_context == NULL) {
        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] Need Http_fs init first\n");
        return;
    }
    http_fs_SetParams(_p_mmf_context, &http_fsParams);
    http_fs_SetRespCB(_p_mmf_context);
    http_fs_Apply(_p_mmf_context);
}

void Http_fs::mp4DirectoryInit(void)
{
    fatfs_sd_get_param(&fatfs_sd);
    sprintf(sd_dirname, "%s", "HTTP_FS_VIDEO");
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
        rt_printf("[ERROR] free space < 50MB\n\r");
    }
}

void Http_fs::end(void)
{
    if (_p_mmf_context == NULL) {
        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] Need Http_fs init first\n");
    }
    http_fs_Deinit(_p_mmf_context);
}

void Http_fs::del_old_file(void)
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
            amb_ard_printf(ARD_LOG_INF, "[INFO] del %s\n\r", old_filepath);
            f_unlink(old_filepath);
        }
    }
}
