#include "Arduino.h"
#include "AmebaFatFSFile.h"

File::File(void)
{
    _file = NULL;
}

File::File(const char *filename)
{
    _file = NULL;
    open(filename);
}

bool File::open(const char *filename)
{
    FRESULT res = FR_OK;

    _file = (FIL *)malloc(sizeof(FIL));
    if (_file == NULL) {
        res = FR_INT_ERR;
        printf("\r\n[ERROR] open file (%s) malloc fail.\n", filename);
        return false;
    }

    res = f_open(_file, filename, FA_OPEN_ALWAYS | FA_READ | FA_WRITE);

    if (res != FR_OK) {
        printf("\r\n[ERROR] open file (%s) fail. (res=%d)\n", filename, res);
        if (_file != NULL) {
            free(_file);
            _file = NULL;
        }
        return false;
    }
    // Copy file name
    const char *name = strrchr(filename, '/');
    strncpy(_name, (name + 1), MAX_FILENAME_LEN);
    return true;
}

void File::close(void)
{
    if (_file != NULL) {
        f_close(_file);
        free(_file);
        _file = NULL;
    }
}

size_t File::write(uint8_t c)
{
    return write(&c, 1);
}

size_t File::write(const uint8_t *buf, size_t size)
{
    FRESULT res = FR_OK;
    uint32_t writesize = 0;

    if (_file != NULL) {
        res = f_write(_file, (const void *)buf, size, &writesize);
        if (res != FR_OK) {
            printf("\r\n[ERROR] File write.\n");
        }
    }

    return writesize;
}

size_t File::write(const char *str)
{
    if (str == NULL) {
        return 0;
    }
    return write((const uint8_t *)str, strlen(str));
}

size_t File::write(const char *buf, size_t size)
{
    return write((const uint8_t *)buf, size);
}

int File::read(void)
{
    FRESULT res = FR_OK;
    char c = -1;
    uint32_t readsize = 0;

    if (_file != NULL) {
        res = f_read(_file, &c, 1, &readsize);
        if (res != FR_OK) {
            printf("\r\n[ERROR] File read.\n");
        }
    }
    return c;
}

int File::read(void *buf, size_t nbyte)
{
    FRESULT res = FR_OK;
    uint32_t readsize = 0;

    if (_file != NULL) {
        res = f_read(_file, buf, nbyte, &readsize);
        if (res != FR_OK) {
            printf("\r\n[ERROR] File read.\n");
        }
    }
    return readsize;
}

int File::peek(void)
{
    int c = -1;
    uint32_t pos = 0;

    if (_file != NULL) {
        pos = f_tell(_file);
        c = read();
        f_lseek(_file, pos);
    }
    return c;
}

int File::available(void)
{
    int res = 0;

    if (_file != NULL) {
        uint32_t size = f_size(_file);
        uint32_t pos = f_tell(_file);
        res = size - pos;
    }
    return res;
}

void File::flush(void)
{
    if (_file != NULL) {
        f_sync(_file);
    }
}

bool File::seek(uint32_t pos)
{
    FRESULT res = FR_OK;

    if (_file != NULL) {
        res = f_lseek(_file, pos);
    }
    return (res == FR_OK);
}

uint32_t File::position(void)
{
    uint32_t pos = 0;

    if (_file != NULL) {
        pos = f_tell(_file);
    }
    return pos;
}

uint32_t File::size(void)
{
    uint32_t size = 0;

    if (_file != NULL) {
        size = f_size(_file);
    }
    return size;
}

File::operator bool()
{
    return (_file != NULL);
}

bool File::isOpen(void)
{
    return (_file != NULL);
}

const char *File::name(void)
{
    if (_file != NULL) {
        return _name;
    }
    return NULL;
}
