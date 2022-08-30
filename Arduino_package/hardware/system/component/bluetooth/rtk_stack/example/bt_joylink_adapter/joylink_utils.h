#ifndef __JOYLINK_UTILS_H__
#define __JOYLINK_UTILS_H__

#include "joylink_platform.h"

/**
 * brief:
 *
 * @Param: pBytes
 * @Param: srcLen
 * @Param: pDstStr
 * @Param: dstLen
 *
 * @Returns:
 */
int jl_util_reverse_buf(const uint8_t *src, uint8_t *dst, int32_t len);

int jl_util_byte2hexstr(const uint8_t *pBytes, int32_t srcLen, uint8_t *pDstStr, int32_t dstLen);


int jl_util_byte2hexcapstr(const uint8_t *pBytes, int32_t srcLen, uint8_t *pDstStr, int32_t dstLen);

/**
 * brief:
 *
 * @Param: buf
 * @Param: buf_len
 * @Param: value
 * @Param: value_len
 *
 * @Returns:
 */
int jl_util_str2byte(const uint8_t *buf, int32_t buf_len, void *value, int32_t value_len);


/**
 * brief:
 *
 * @Param: hexStr
 * @Param: buf
 * @Param: bufLen
 *
 * @Returns:
 */
int jl_util_hexStr2bytes(const char *hexStr, uint8_t *buf, int32_t bufLen);


/**
 * @name:jl_util_random_buf
 *
 * @param: dest
 * @param: size
 *
 * @returns:
 */
int32_t jl_util_random_buf(uint8_t *dest, unsigned size);

/**
 * @name:jl_util_print_buffer
 *
 * @param: msg
 * @param: is_fmt
 * @param: num_line
 * @param: buff
 * @param: len
 */
void jl_util_print_buffer(const char *msg, int32_t is_fmt, int32_t num_line, const char *buff, int32_t len);


#define JL_UTILS_P_FMT        (1)
#define JL_UTILS_P_NO_FMT     (0)

#define joylink_util_fmt_p(msg, buff, len) jl_util_print_buffer(msg, JL_UTILS_P_FMT, 20, (char *)buff, len)

#endif /* __JOYLINK_UTILS_H__ */
