#include <Arduino.h>

#include "Filesaver.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "filesaver_drv.h"

#ifdef __cplusplus
}
#endif

Filesaver *Filesaver::global_instance = NULL;

Filesaver::Filesaver(void)
{

    global_instance = this;

    if (_p_mmf_context == NULL) {
        _p_mmf_context = filesaver_Init();
    }
    if (_p_mmf_context == NULL) {
        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] Filesaver Init failed\n");
        return;
    }
}

Filesaver::~Filesaver(void)
{
    if (_p_mmf_context == NULL) {
        return;
    }
    if (filesaver_Deinit(_p_mmf_context) == NULL) {
        _p_mmf_context = NULL;
    } else {
        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] Filesaver deinit failed\n");
    }

    // Clear the pointer on destruction
    if (global_instance == this) {
        global_instance = NULL;
    }
}

void Filesaver::setFileName(char *filename)
{
    if (_p_mmf_context == NULL) {
        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] Need to init Filesaver first\n");
        return;
    }
    strcpy(file_name, filename);
}

void Filesaver::staticImgSaveCB(char *file_path, uint32_t data_addr, uint32_t data_size)
{
    if (global_instance) {
        global_instance->rawImgSaveCB(file_path, data_addr, data_size);
    }
}

void Filesaver::rawImgSaveSDBegin()
{
    if (_p_mmf_context == NULL) {
        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] Need to init Filesaver first\n");
        return;
    }
    sprintf(savefilepath, "%s_%02d.raw", file_name, file_count++);
    filesaver_SetFilePath(_p_mmf_context, savefilepath);
    filesaver_SetTypeHandler(_p_mmf_context, &Filesaver::staticImgSaveCB);
    amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] Filesaver initialized\n");
}

void Filesaver::rawImgSaveCB(char *file_path, uint32_t data_addr, uint32_t data_size)
{
    int bw = 0;
    rawReform((unsigned char *)data_addr, data_size);
    if (f_open(&m_file1, savefilepath, FA_OPEN_ALWAYS | FA_READ | FA_WRITE) == FR_OK) {
        if (data_size > 0) {
            printf("file_path:%s  data_addr:%ld  data_size:%ld \r\n", file_path, data_addr, data_size);
            f_write(&m_file1, (void *)data_addr, data_size, (u32 *)&bw);
            f_close(&m_file1);
        }
    }
    sprintf(savefilepath, "%s_%02d.raw", file_name, file_count++);
    filesaver_SetFilePath(_p_mmf_context, savefilepath);
}

void Filesaver::rawReform(unsigned char *pData, int dataLen)
{
    int dim = dataLen / 2;
    unsigned char *pTmp = (unsigned char *)malloc(dataLen);
    memcpy(pTmp, pData, dataLen);
    int nIndex = 0;
    for (int j = 0; j < dim; j++) {
        int nValue = (pTmp[nIndex] << 8) | pTmp[nIndex + dim];

        pData[2 * nIndex] = nValue & 0xff;
        pData[2 * nIndex + 1] = (nValue >> 8) & 0xff;
        nIndex++;
    }
    free(pTmp);
}
