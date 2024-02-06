#ifndef _AMEBA_FATFS_FILE_H_
#define _AMEBA_FATFS_FILE_H_

#include <Stream.h>
#include "ff.h"

#define MAX_FILENAME_LEN 255

class File: public Stream {
public:
    File(void);
    File(const char *filename);

    bool open(const char *filename);
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

    friend class AmebaFatFS;

private:
    FIL *_file;
    char _name[MAX_FILENAME_LEN + 1];
};

#endif
