#include "Arduino.h"
#include "AmebaFatFSFile.h"

#ifdef __cplusplus
extern "C" {
#include "helix_mp3_drv.h"
}
#endif
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
    const char *extension = strrchr(filename, '.');
    _file = (FIL *)malloc(sizeof(FIL));
    if (_file == NULL) {
        res = FR_INT_ERR;
        printf("\r\n[ERROR] open file (%s) malloc fail.\n", filename);
        return false;
    }

    if (strcmp(extension, ".mp3") == 0) {
        res = f_open(_file, filename, FA_OPEN_EXISTING | FA_READ);
        convertMp3ToArray();
    } else {
        res = f_open(_file, filename, FA_OPEN_ALWAYS | FA_READ | FA_WRITE);
    }

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

void File::convertMp3ToArray(void)
{
    uint32_t mp3_size = 0;
    unsigned char *mp3_data = NULL;

    if (_file != NULL) {
        // Read ID3 header
        unsigned char id3_header[10];
        f_lseek(_file, 0);    // Move to the beginning
        UINT bytesRead;
        FRESULT res = f_read(_file, id3_header, 10, &bytesRead);

        if (res != FR_OK || bytesRead != 10) {
            printf("\r\n[ERROR] Failed to read ID3v2 header. (res=%d)\n", res);
            return;
        }

        // Check for ID3v2
        if (id3_header[0] == 'I' && id3_header[1] == 'D' && id3_header[2] == '3') {
            uint32_t id3v2_size = ((id3_header[6] & 0x7F) << 21) | ((id3_header[7] & 0x7F) << 14) | ((id3_header[8] & 0x7F) << 7) | (id3_header[9] & 0x7F);
            f_lseek(_file, id3v2_size + 10);    // Move past ID3v2
        } else {
            f_lseek(_file, 0);
        }

        // Calculate MP3 size
        mp3_size = f_size(_file) - f_tell(_file);


        // Allocate memory for MP3 data
        mp3_data = (unsigned char *)malloc(mp3_size);
        if (mp3_data == NULL) {
            printf("\r\n[ERROR] Memory allocation failed for MP3 data.\n");
            return;
        }

        // Read MP3 data
        res = f_read(_file, mp3_data, mp3_size, &bytesRead);

        if (res != FR_OK || bytesRead != mp3_size) {
            printf("\r\n[ERROR] Failed to read MP3 data. (res=%d, bytesRead=%lu)\n", res, bytesRead);
            free(mp3_data);
            return;
        }
        audio_play_binary_array(mp3_data, mp3_size);
        free(mp3_data);
        mp3_data = NULL;
    } else {
        printf("\r\n[ERROR] No file opened to convert.\n");
    }
}
