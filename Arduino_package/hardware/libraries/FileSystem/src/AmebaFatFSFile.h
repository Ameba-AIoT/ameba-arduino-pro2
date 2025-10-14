#ifndef _AMEBA_FATFS_FILE_H_
#define _AMEBA_FATFS_FILE_H_

#include <Stream.h>
#include "ff.h"

#define MAX_FILENAME_LEN 255
#define MP3              1
class File: public Stream {
public:
    File(void);
    File(const char *filename);
    File(const char *filename, int fileType);

    bool open(const char *filename);
    bool open(const char *filename, int fileType);
    void close(void);

    virtual size_t write(uint8_t c);
    virtual size_t write(const uint8_t *buf, size_t size);
    size_t write(const char *str);
    size_t write(const char *buf, size_t size);

    virtual int read(void);
    int read(void *buf, size_t size);

    virtual int peek(void);
    virtual int available(void);
    virtual void flush(void);

    bool seek(uint32_t pos);
    uint32_t position(void);
    uint32_t size(void);

    operator bool();

    bool isOpen(void);
    const char *name(void);

    void convertMp3ToArray(void);

    void setMp3DigitalVol(uint8_t digitalVol);

    void playMp3(void);

    void sdstartota(const char *filename);

    bool readFile(unsigned char *&file_data, uint32_t &file_size);

    friend class AmebaFatFS;

private:
    FIL *_file;
    char _name[MAX_FILENAME_LEN + 1];
    uint8_t _audio_vol = 0xAF / 2;
};

#endif
