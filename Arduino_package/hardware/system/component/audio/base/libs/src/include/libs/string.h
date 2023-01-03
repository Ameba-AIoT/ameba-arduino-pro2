#ifndef AMEBA_BASE_LIBS_SRC_INCLUDE_LIBS_STRING_H
#define AMEBA_BASE_LIBS_SRC_INCLUDE_LIBS_STRING_H

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

size_t strlcpy(char *dst, const char *src, size_t dsize);
size_t strlcat(char *dst, const char *src, size_t dsize);

size_t strnlen(const char *str, size_t maxlen);

#ifdef __cplusplus
}
#endif

#endif // AMEBA_BASE_LIBS_SRC_INCLUDE_LIBS_STRING_H
