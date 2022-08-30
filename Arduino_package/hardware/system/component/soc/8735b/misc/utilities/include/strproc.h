/**************************************************************************//**
 * @file     strproc.h
 * @brief    The string processing API.
 * @version  V1.00
 * @date     2016-09-30
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2017 Realtek Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************/

#ifndef _STRPROC_H_
#define _STRPROC_H_

#ifdef  __cplusplus
extern "C" {
#endif

#include "cmsis_compiler.h"
#include <stddef.h> /* for size_t */
#include <stdarg.h>

/**
 * @addtogroup util_strproc String Process
 * @ingroup 8710c_util
 * @{
 * @brief The string processing API.
 */

/**
  \brief  The data structure of the stubs functions of the string processing functions in ROM.
*/
typedef struct strproc_func_stubs_s {
	char *(*strcat)(char *dest,  char const *src);
	char *(*strchr)(const char *s, int c);
	int (*strcmp)(char const *cs, char const *ct);
	int (*strncmp)(char const *cs, char const *ct, size_t count);
	int (*strnicmp)(char const *s1, char const *s2, size_t len);
	char *(*strcpy)(char *dest, char const *src);
	char *(*strncpy)(char *dest, char const *src, size_t count);
	size_t (*strlcpy)(char *dst, char const *src, size_t s);
	size_t (*strlen)(char const *s);
	size_t (*strnlen)(char const *s, size_t count);
	char *(*strncat)(char *dest, char const *src, size_t count);
	char *(*strpbrk)(char const *cs, char const *ct);
	size_t (*strspn)(char const *s, char const *accept);
	char *(*strstr)(char const *s1, char const *s2);
	char *(*strtok)(char *s, char const *ct);
	size_t (*strxfrm)(char *dest, const char *src, size_t n);
	char *(*strsep)(char **s, const char *ct);
	double (*strtod)(const char *str, char **endptr);
	float (*strtof)(const char *str, char **endptr);
	long double (*strtold)(const char *str, char **endptr);
	long (*strtol)(const char *nptr, char **endptr, int base);
	long long (*strtoll)(const char *nptr, char **endptr, int base);
	unsigned long (*strtoul)(const char *nptr, char **endptr, int base);
	unsigned long long (*strtoull)(const char *nptr, char **endptr, int base);
	int (*atoi)(const char *num);
	unsigned int (*atoui)(const char *num);
	long (*atol)(const char *num);
	unsigned long (*atoul)(const char *num);
	unsigned long long (*atoull)(const char *num);
	double (*atof)(const char *str);

	uint32_t reserved[16];  // reserved space for next ROM code version function table extending.
} strproc_func_stubs_t;

#if defined(ROM_REGION)
char *_strcat(char *dest,  char const *src);
char *_strchr(const char *s, int c);
int _strcmp(char const *cs, char const *ct);
int _strncmp(char const *cs, char const *ct, size_t count);
int _strnicmp(char const *s1, char const *s2, size_t len);
char *_strcpy(char *dest, char const *src);
char *_strncpy(char *dest, char const *src, size_t count);
size_t _strlcpy(char *dst, char const *src, size_t s);
size_t _strlen(char const *s);
size_t _strnlen(char const *s, size_t count);
char *_strncat(char *dest, char const *src, size_t count);
char *_strpbrk(char const *cs, char const *ct);
size_t _strspn(char const *s, char const *accept);
char *_strstr(char const *s1, char const *s2);
char *_strtok(char *s, char const *ct);
size_t _strxfrm(char *dest, const char *src, size_t n);
char *_strsep(char **s, const char *ct);

double _strtod(const char *str, char **endptr);
float _strtof(const char *str, char **endptr);
long double _strtold(const char *str, char **endptr);
double _atof(const char *str);

long _strtol(const char *nptr, char **endptr, int base);
long long _strtoll(const char *nptr, char **endptr, int base);
unsigned long _strtoul(const char *nptr, char **endptr, int base);
unsigned long long _strtoull(const char *nptr, char **endptr, int base);

#else   // else of "#if defined(ROM_REGION)"

extern const strproc_func_stubs_t strproc_stubs;

/**
  \brief   String concatenation
  \details Appends the src string to the dest string, overwriting the
           terminating null byte ('\0') at the end of dest, and
           then adds a terminating null byte.
           The strings may not overlap, and the dest string must have
           enough space for the result.  If dest is not large enough,
           program behavior is unpredictable.
  \param[in]   dest    The destination string buffer address.
  \param[in]   src    The source string address.
  \return   A pointer to the resulting string dest.
*/
__STATIC_INLINE char *strcat(char *dest,  char const *src)
{
	return strproc_stubs.strcat(dest, src);
}

/**
  \brief Returns a pointer to the first occurrence of the character c
         in the string s.
  \param[in]   s    The destination string buffer address.
  \param[in]   c    The character to find.
  \return   A pointer to the matched character or
            NULL if the character is not found.
*/
__STATIC_INLINE char *strchr(const char *s, int c)
{
	return strproc_stubs.strchr(s, c);
}

/**
  \brief   Compare two strings
  \details Compares the two strings cs and ct. It returns an integer less than,
           equal to, or greater than zero if cs is found, respectively, to be less than,
           to match, or be greater than ct.
  \param[in]   cs    The first string buffer address for the comparison.
  \param[in]   ct    The second string buffer address for the comparison.
  \return   < 0: cs is found to be less than ct.
  \return   = 0: cs is found to match than ct.
  \return   > 0: cs is found to be greater than ct.
*/
__STATIC_INLINE int strcmp(char const *cs, char const *ct)
{
	return strproc_stubs.strcmp(cs, ct);
}

/**
  \brief   Compare two strings with only compares the first (at most) n bytes.
  \details Compares the two strings with only compares the first (at most) n bytes of cs and ct.
           It returns an integer less than, equal to, or greater than zero if cs is found,
           respectively, to be less than, to match, or be greater than ct.
  \param[in]   cs    The first string buffer address for the comparison.
  \param[in]   ct    The second string buffer address for the comparison.
  \return   < 0: cs is found to be less than ct.
  \return   = 0: cs is found to match than ct.
  \return   > 0: cs is found to be greater than ct.
*/
__STATIC_INLINE int strncmp(char const *cs, char const *ct, size_t count)
{
	return strproc_stubs.strncmp(cs, ct, count);
}

/**
 * strnicmp - Case insensitive, length-limited string comparison
 * @s1: One string
 * @s2: The other string
 * @len: the maximum number of characters to compare
 */

/**
  \brief   Case insensitive, length-limited string comparison.
  \param[in]   s1    The first string buffer address for the comparison.
  \param[in]   s2    The other string buffer address for the comparison.
  \param[in]   len   The maximum number of characters to compare.
  \return   < 0: cs is found to be less than ct.
  \return   = 0: cs is found to match than ct.
  \return   > 0: cs is found to be greater than ct.
*/
__STATIC_INLINE int strnicmp(char const *s1, char const *s2, size_t len)
{
	return strproc_stubs.strnicmp(s1, s2, len);
}

/**
  \brief    Copy string
  \details  Copies the string pointed to by src, including the terminating null byte ('\0'),
            to the buffer pointed to by dest. The strings may not overlap, and the destination
            string dest must be large enough to receive the copy.
  \param[in]   dest   The destination string buffer address.
  \param[in]   src    The source string address.
  \return   Return a pointer to the destination string dest.
*/
__STATIC_INLINE char *strcpy(char *dest, char const *src)
{
	return strproc_stubs.strcpy(dest, src);
}

/**
  \brief    Copy string with limited bytes.
  \details  Copies the string pointed to by src, including the terminating null byte ('\0'),
            to the buffer pointed to by dest with limited N bytes.
            The strings may not overlap, and the destination string dest must be large enough
            to receive the copy.
  \param[in]   dest   The destination string buffer address.
  \param[in]   src    The source string address.
  \param[in]   count  The maximum bytes to be copied.
  \return   Return a pointer to the destination string dest.
*/
__STATIC_INLINE char *strncpy(char *dest, char const *src, size_t count)
{
	return strproc_stubs.strncpy(dest, src, count);
}

/**
  \brief    Copies up to (s - 1) characters from the NUL-terminated string src to dst.
  \param[in]   dst    The destination string address.
  \param[in]   src    The source string address.
  \param[in]   s      Maximum (s - 1) bytes to be copied.
  \return   The total length of the string copied.
*/
__STATIC_INLINE size_t strlcpy(char *dst, char const *src, size_t s)
{
	return strproc_stubs.strlcpy(dst, src, s);
}

/**
  \brief    Calculates the length of the string s, excluding the terminating null byte.
  \param[in]   s    The input string.
  \return   The number of bytes in the input string.
*/
__STATIC_INLINE size_t strlen(char const *s)
{
	return strproc_stubs.strlen(s);
}

/**
  \brief    Determine the length of a fixed-size string.
  \details  Determine  the number of characters in the string
            pointed to by s, excluding the terminating null byte ('\0'),
            but at most count.
  \param[in]   s        The input string.
  \param[in]   count    The most length.
  \return   The number of bytes in the string s if that is less than count.
  \return   Return "count" if there is no null terminating ('\0') among the
            first "count" characters pointed to by s.
*/
__STATIC_INLINE size_t strnlen(char const *s, size_t count)
{
	return strproc_stubs.strnlen(s, count);
}

/**
  \brief    Concatenate two strings.
  \details  Appends the src string to the dest string with will use at most
            "count" bytes from src, overwriting the terminating null byte ('\0')
            at the end of dest, and then adds a terminating null byte.
            The strings may not overlap, and the dest string must have enough space
            for the result. If dest is not large enough, program behavior is unpredictable.
  \param[in]   dest   The destination string buffer address.
  \param[in]   src    The source string address.
  \param[in]   count  The most length of bytes from the string src to be copied.
  \return   A pointer to the resulting string dest.
*/
__STATIC_INLINE char *strncat(char *dest, char const *src, size_t count)
{
	return strproc_stubs.strncat(dest, src, count);
}

/**
  \brief    Search a string for any of a set of bytes.
  \details  Locates the first occurrence in the string cs
            of any of the bytes in the string ct.
  \param[in]   cs   The string pattern for the searching.
  \param[in]   ct   The target string to be located for the searching.
  \return   A pointer to the byte in cs that matches one of the bytes
            in ct, or NULL if no such byte is found.
*/
__STATIC_INLINE char *strpbrk(char const *cs, char const *ct)
{
	return strproc_stubs.strpbrk(cs, ct);
}

/**
  \brief    Get length of a prefix substring.
  \details  Calculates the length (in bytes) of the initial segment
            of s which consists entirely of bytes in accept.
  \param[in]   s   The target string.
  \param[in]   accept   The string of the match pattern.
  \return   The number of bytes in the initial segment of s which consist only of bytes from accept.
*/
__STATIC_INLINE size_t strspn(char const *s, char const *accept)
{
	return strproc_stubs.strspn(s, accept);
}

/**
  \brief    Locate a substring.
  \details  Finds the first occurrence of the substring s2 in the string s1.
            The terminating null bytes are not compared.
  \param[in]   s1  The target string.
  \param[in]   s2  The string of the searching pattern.
  \return   A pointer to the beginning of the substring, or NULL if the substring is not found.
*/
__STATIC_INLINE char *strstr(char const *s1, char const *s2)
{
	return strproc_stubs.strstr(s1, s2);
}

/**
  \brief    Extract tokens from strings.
  \details  Breaks a string into a sequence of zero or more nonempty tokens.
            On the first call to strtok(), the string to be parsed should be
            specified in s.  In each subsequent call that should parse the
            same string, s must be NULL.
  \param[in]   s  The target string for the tokens to be get from.
  \param[in]   ct  Specifies a set of bytes that delimit the tokens in the parsed string.
               The caller may specify different strings in delim in successive calls that
               parse the same string.
  \return   A pointer to the next token, or NULL if there are no more tokens.
*/
__STATIC_INLINE char *strtok(char *s, char const *ct)
{
	return strproc_stubs.strtok(s, ct);
}

/**
  \brief    String transformation.
  \details  Transforms the src string into a form such that the result of strcmp()
            on two strings that have been transformed with strxfrm() is the same as
            the result of strcoll() on the two strings before their transformation.
            The first n bytes of the transformed string are placed in dest.
  \param[in]   dest The buffer to store the transformed string.
  \param[in]   src  The target string to be transformed.
  \return   The number of bytes required to store the transformed string in dest
            excluding the terminating NULL byte. If the value returned is n or more,
            the contents of dest are indeterminate.
*/
__STATIC_INLINE size_t strxfrm(char *dest, const char *src, size_t n)
{
	return strproc_stubs.strxfrm(dest, src, n);
}

/**
  \brief    Extract token from string.
  \details  If *s is NULL, this function returns NULL and does nothing else.
            Otherwise, this function finds the first token in the string *s,
            that is delimited by one of the bytes in the string ct.
            This token is terminated by overwriting the delimiter with a null byte,
            and *s is updated to point past the token.
            In case no delimiter was found, the token is taken to be the entire
            string *s, and *s is made NULL.
  \param[in]   s    The target string to be extracted token from.
  \param[in]   ct   The string pattern to find.
  \return   A pointer to the token, that is, it returns the original value of *s.
*/
__STATIC_INLINE char *strsep(char **s, const char *ct)
{
	return strproc_stubs.strsep(s, ct);
}

/**
  \brief    Convert ASCII string to floating-point number.
  \details  Convert the initial portion of the string pointed to by str
            to double representation.
  \param[in]   str    The target string to be converted.
  \param[out]  endptr   If endptr is not NULL, a pointer to the character after the
                        last character used in the conversion is stored in the location
                        referenced by endptr.
  \return   The converted value, if any. If no conversion is performed, 0 is returned.
*/
__STATIC_INLINE double strtod(const char *str, char **endptr)
{
	return strproc_stubs.strtod(str, endptr);
}

/**
  \brief    Convert ASCII string to floating-point number.
  \details  Convert the initial portion of the string pointed to by str
            to float representation.
  \param[in]   str    The target string to be converted.
  \param[out]  endptr   If endptr is not NULL, a pointer to the character after the
                        last character used in the conversion is stored in the location
                        referenced by endptr.
  \return   The converted value, if any. If no conversion is performed, 0 is returned.
*/
__STATIC_INLINE float strtof(const char *str, char **endptr)
{
	return strproc_stubs.strtof(str, endptr);
}

/**
  \brief    Convert ASCII string to floating-point number.
  \details  Convert the initial portion of the string pointed to by str
            to long double representation.
  \param[in]   str    The target string to be converted.
  \param[out]  endptr   If endptr is not NULL, a pointer to the character after the
                        last character used in the conversion is stored in the location
                        referenced by endptr.
  \return   The converted value, if any. If no conversion is performed, 0 is returned.
*/
__STATIC_INLINE long double strtold(const char *str, char **endptr)
{
	return strproc_stubs.strtold(str, endptr);
}

/**
  \brief    Convert a string to a double.
  \details  Converts the initial portion of the string pointed to by str to double.
  \param[in]   str    The target string to be converted.
  \return   The converted value.
*/
__STATIC_INLINE double atof(const char *str)
{
	return strproc_stubs.atof(str);
}

/**
  \brief    Convert a string to a long integer.
  \details  Converts the initial part of the string in nptr to a long integer value
            according to the given base, which must be 10 or 16, or be the special value 0.
  \param[in]   nptr    The target string to be converted.
  \param[out]  endptr   If endptr is not NULL, it stores the address of the first invalid character in *endptr.
                        If *nptr is not '\0' but **endptr is '\0' on return, the entire string is valid.
  \param[in]   base    The conversion base, which must be 10 or 16, or be the special value 0.
  \return   The converted value.
*/
__STATIC_INLINE long strtol(const char *nptr, char **endptr, int base)
{
	return strproc_stubs.strtol(nptr, endptr, base);
}

/**
  \brief    Convert a string to a long long integer.
  \details  Converts the initial part of the string in nptr to a long long integer value
            according to the given base, which must be 10 or 16, or be the special value 0.
  \param[in]   nptr    The target string to be converted.
  \param[out]  endptr   If endptr is not NULL, it stores the address of the first invalid character in *endptr.
                        In particular, if *nptr is not '\0' but **endptr is '\0' on return, the entire string is valid.
  \param[in]   base    The conversion base, which must be 10 or 16, or be the special value 0.
  \return   The converted value.
*/
__STATIC_INLINE long long strtoll(const char *nptr, char **endptr, int base)
{
	return strproc_stubs.strtoll(nptr, endptr, base);
}

/**
  \brief    Convert a string to an unsigned long integer.
  \details  Converts the initial part of the string in nptr to an unsigned long int value
            according to the given base.
  \param[in]   nptr    The target string to be converted.
  \param[out]  endptr   If endptr is not NULL, it stores the address of the first invalid character in *endptr.
                        If *nptr is not '\0' but **endptr is '\0' on return, the entire string is valid.
  \param[in]   base    The conversion base, which must be 10 or 16, or be the special value 0.
  \return   The converted value.
*/
__STATIC_INLINE unsigned long strtoul(const char *nptr, char **endptr, int base)
{
	return strproc_stubs.strtoul(nptr, endptr, base);
}

/**
  \brief    Convert a string to an unsigned long long integer.
  \details  Converts the initial part of the string in nptr to an unsigned long long int value
            according to the given base.
  \param[in]   nptr    The target string to be converted.
  \param[out]  endptr   If endptr is not NULL, it stores the address of the first invalid character in *endptr.
                        If *nptr is not '\0' but **endptr is '\0' on return, the entire string is valid.
  \param[in]   base    The conversion base, which must be 10 or 16, or be the special value 0.
  \return   The converted value.
*/
__STATIC_INLINE unsigned long long strtoull(const char *nptr, char **endptr, int base)
{
	return strproc_stubs.strtoull(nptr, endptr, base);
}

/**
  \brief    Convert a string to an integer.
  \details  Converts the initial portion of the string pointed to by num to integer.
  \param[in]   num    The target string to be converted.
  \return   The converted value.
*/
__STATIC_INLINE int atoi(const char *num)
{
	return strproc_stubs.atoi(num);
}

/**
  \brief    Convert a string to an unsigned integer.
  \details  Converts the initial portion of the string pointed to by num to unsigned integer.
  \param[in]   num    The target string to be converted.
  \return   The converted value.
*/
__STATIC_INLINE unsigned int atoui(const char *num)
{
	return strproc_stubs.atoui(num);
}

/**
  \brief    Convert a string to an long integer.
  \details  Converts the initial portion of the string pointed to by num to long integer.
  \param[in]   num    The target string to be converted.
  \return   The converted value.
*/
__STATIC_INLINE long atol(const char *num)
{
	return strproc_stubs.atol(num);
}

/**
  \brief    Convert a string to an unsigned long integer.
  \details  Converts the initial portion of the string pointed to by num to unsigned long integer.
  \param[in]   num    The target string to be converted.
  \return   The converted value.
*/
__STATIC_INLINE unsigned long atoul(const char *num)
{
	return strproc_stubs.atoul(num);
}

/**
  \brief    Convert a string to an unsigned long long integer.
  \details  Converts the initial portion of the string pointed to by num to unsigned long long integer.
  \param[in]   num    The target string to be converted.
  \return   The converted value.
*/
__STATIC_INLINE unsigned long long atoull(const char *num)
{
	return strproc_stubs.atoull(num);
}
#endif  // defined(ROM_REGION)

/** @} */ /* End of group util_strproc */

#ifdef  __cplusplus
}
#endif

#endif
