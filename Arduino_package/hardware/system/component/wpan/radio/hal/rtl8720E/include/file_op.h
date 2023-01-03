#ifndef __FILE_OP_H__
#define __FILE_OP_H__
#include <stdlib.h>
#include <stdio.h>
#include "common.h"

#define LOG_FILE_NAME "logfile.txt"
int32_t int16_complex_to_buf(const char *file_name, int16_t *buf, int32_t num);
int32_t int32_complex_to_buf(const char *file_name, ae_int32x2 *buf, int32_t num);
int32_t int32_to_buf(const char *file_name, int32_t *buf, int32_t num);
int32_t int16_to_buf(const char *file_name, int16_t *buf, int32_t num);
int32_t print_buf_int32x2(int32_t *buf, int32_t len);
int32_t print_buf_int32(int32_t *buf, int32_t len);
int32_t print_buf_int16x2(int16_t *buf, int32_t len);
int32_t print_buf_int16(int16_t *buf, int32_t len);
void debug_log_clear(void);
void debug_log(const char *format, ...);
#endif
