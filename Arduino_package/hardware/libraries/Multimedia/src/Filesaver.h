#ifndef __FILESAVER_H__
#define __FILESAVER_H__

#include "mmf2_module.h"
#include "VideoStream.h"
#include "AudioStream.h"
#include "ff.h"

class Filesaver: public MMFModule {
public:
    Filesaver(void);
    ~Filesaver(void);

    void setFileName(char *filename);
    void rawImgSaveSDBegin();

private:
    char file_name[64];
    char savefilepath[128];
    int file_count = 0;
    FIL m_file1;

    static Filesaver *global_instance;

    static void staticImgSaveCB(char *file_path, uint32_t data_addr, uint32_t data_size);


    void rawImgSaveCB(char *file_path, uint32_t data_addr, uint32_t data_size);
    void rawReform(unsigned char *pData, int dataLen);
};

#endif
