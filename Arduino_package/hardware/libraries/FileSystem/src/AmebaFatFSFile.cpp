#include "Arduino.h"
#include "AmebaFatFSFile.h"

File::File(void) {
    _file = NULL;
}

File::File(const char *filename) {
    _file = NULL;
    open(filename);
}

bool File::open(const char *filename) {
    FRESULT ret = FR_OK;

    _file = (FIL*) malloc(sizeof(FIL));
    if (_file == NULL) {
        ret = FR_INT_ERR;
        printf("open file (%s) malloc fail.\r\n", filename);
        return false;
    }

    ret = f_open(_file, filename, FA_OPEN_ALWAYS | FA_READ | FA_WRITE);

    if (ret != FR_OK) {
        printf("open file (%s) fail. (ret=%d)\r\n", filename, ret);
        if (_file != NULL) {
            free(_file);
            _file = NULL;
        }
        return false;
    }
    // Copy file name
    char const* name = strrchr(filename, '/');
    strncpy(_name, name+1, MAX_FILENAME_LEN);
    return true;
}

void File::close(void) {
    if (_file != NULL) {
        f_close(_file);
        free(_file);
        _file = NULL;
    }
}

size_t File::write(uint8_t c) {
    return write(&c, 1);
}

size_t File::write(const uint8_t *buf, size_t size) {
    FRESULT ret = FR_OK;
    uint32_t writesize = 0;

    if (_file != NULL) {
        ret = f_write(_file, (const void *)buf, size, &writesize);
        if (ret != FR_OK) {
            printf("File write error.\r\n");
        }
    }

    return writesize;
}

size_t File::write(const char *str) {
    if (str == NULL) return 0;
    return write((const uint8_t *)str, strlen(str));
}

size_t File::write(const char *buf, size_t size) {
    return write((const uint8_t *)buf, size);
}

int File::read(void) {
    FRESULT ret = FR_OK;
    char c = -1;
    uint32_t readsize = 0;

    if (_file != NULL) {
        ret = f_read(_file, &c, 1, &readsize);
        if (ret != FR_OK) {
            printf("File read error.\r\n");
        }
    }

    return c;
}

int File::read(void *buf, size_t nbyte) {
    FRESULT ret = FR_OK;
    uint32_t readsize = 0;

    if (_file != NULL) {
        ret = f_read(_file, buf, nbyte, &readsize);
        if (ret != FR_OK) {
            printf("File read error.\r\n");
        }
    }

    return readsize;
}

int File::peek(void) {
    int c = -1;
    uint32_t pos = 0;

    if (_file != NULL) {
        pos = f_tell(_file);
        c = read();
        f_lseek(_file, pos);
    }

    return c;
}

int File::available(void) {
    int ret = 0;

    if (_file != NULL) {
        uint32_t size = f_size(_file);
        uint32_t pos  = f_tell(_file);
        ret = size - pos;
    }

    return ret;
}

void File::flush(void) {
    if (_file != NULL) {
        f_sync(_file);
    }
}

bool File::seek(uint32_t pos) {
    FRESULT ret = FR_OK;

    if (_file != NULL) {
        ret = f_lseek(_file, pos);
    }

    return (ret == FR_OK);
}

uint32_t File::position(void) {
    uint32_t pos = 0;

    if (_file != NULL) {
        pos = f_tell(_file);
    }

    return pos;
}

uint32_t File::size(void) {
    uint32_t size = 0;

    if (_file != NULL) {
        size = f_size(_file);
    }

    return size;
}

File::operator bool() {
    return (_file != NULL);
}

bool File::isOpen(void) {
    return (_file != NULL);
}

const char* File::name(void) {
    if (_file != NULL) {
        return _name;
    }

    return NULL;
}
