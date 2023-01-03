#ifndef AMEBA_BASE_LIBS_SRC_INCLUDE_LIBS_STRINGS_H
#define AMEBA_BASE_LIBS_SRC_INCLUDE_LIBS_STRINGS_H


#ifdef __cplusplus
extern "C" {
#endif

int strcasecmp(const char *s1, const char *s2);
int strncasecmp(const char *s1, const char *s2, size_t n);

#ifdef __cplusplus
}
#endif

#endif  // AMEBA_BASE_LIBS_SRC_INCLUDE_LIBS_STRINGS_H
