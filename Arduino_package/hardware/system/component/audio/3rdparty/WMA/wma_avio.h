#ifndef AVIO_H
#define AVIO_H

#ifdef __cplusplus
extern "C" {
#endif

//#include "wma_common.h"
#include "ff.h"
#include <fatfs_ext/inc/ff_driver.h>
#include <disk_if/inc/sdcard.h>
//typedef int64_t offset_t;
typedef unsigned long long uint64_t;//for pc, this is defined in "inttypes.h" of c99 standard
typedef struct ByteIOContext
{
    unsigned char *buffer;
    int buffer_size;
    unsigned char *buf_ptr,  *buf_end;
    FIL* file_ptr;	
//    void *opaque;
//    int(*read_packet)(void *opaque, uint8_t *buf, int buf_size);
//    offset_t(*seek)(void *opaque, offset_t offset, int whence);
//    offset_t pos; /* position in the file of the current buffer */
//    int eof_reached; /* true if eof reached */
//    int write_flag; /* true if open for writing */
//    int error; ///< contains the error code or 0 if no error happened
} ByteIOContext;

int get_buffer(ByteIOContext *s, unsigned char *buf, int size);
int get_byte(ByteIOContext *s);
void ByteIOContext_Initialize(ByteIOContext* pb, FIL* file_ptr);
int fill_ByteIOContext(ByteIOContext *s);
int avio_r8(ByteIOContext *s);
unsigned int avio_rl16(ByteIOContext *s);
unsigned int avio_rl24(ByteIOContext *s);
unsigned int avio_rl32(ByteIOContext *s);
uint64_t avio_rl64(ByteIOContext *s);
int ptr_seek(ByteIOContext* s, unsigned int index);
int ptr_seek_current(ByteIOContext* s, unsigned int index);
int ptr_tell(ByteIOContext* s);
#ifdef __cplusplus
}
#endif

#endif
