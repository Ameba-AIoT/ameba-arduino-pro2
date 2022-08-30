

#ifndef _LIMITS_H_
#define _LIMITS_H_

/* Number of bits in a `char'.  */
#define CHAR_BIT 8

/* Minimum and maximum values a `signed char' can hold.  */
#define SCHAR_MIN (-128)
#define SCHAR_MAX 127

/* Maximum value an `unsigned char' can hold.  (Minimum is 0).  */
#define UCHAR_MAX 255
#define UCHAR_MIN 0

/* Minimum and maximum values a `char' can hold.  */
#define CHAR_MIN (-128)
#define CHAR_MAX 127

/* Minimum and maximum values a `signed short int' can hold.  */
/* For the sake of 16 bit hosts, we may not use -32768 */
#define SHRT_MIN (-32767-1)
#define SHRT_MAX 32767

/* Maximum value an `unsigned short int' can hold.  (Minimum is 0).  */
#define USHRT_MAX 65535

/* Minimum and maximum values a `signed int' can hold.  */
#ifndef __INT_MAX__
#define __INT_MAX__ 2147483647
#endif
#define INT_MIN (-INT_MAX-1)
#define INT_MAX __INT_MAX__

/* Maximum value an `unsigned int' can hold.  (Minimum is 0).  */
#define UINT_MAX (INT_MAX * 2U + 1)

/* Minimum and maximum values a `signed long int' can hold.
   (Same as `int').  */
#ifndef __LONG_MAX__
#define __LONG_MAX__ 2147483647L
#endif
#define LONG_MIN (-LONG_MAX-1)
#define LONG_MAX __LONG_MAX__

/* Maximum value an `unsigned long int' can hold.  (Minimum is 0).  */
#define ULONG_MAX (LONG_MAX * 2UL + 1)

#ifndef __LONG_LONG_MAX__
#define __LONG_LONG_MAX__ 9223372036854775807LL
#endif
/* Minimum and maximum values a `signed long long int' can hold.  */
#define LLONG_MIN (-LLONG_MAX-1)
#define LLONG_MAX __LONG_LONG_MAX__

/* Maximum value an `unsigned long long int' can hold.  (Minimum is 0).  */
#define ULLONG_MAX (LLONG_MAX * 2ULL + 1)

/* Minimum and maximum values a `signed long long int' can hold.  */
#define LONG_LONG_MIN (-LONG_LONG_MAX-1)
#define LONG_LONG_MAX __LONG_LONG_MAX__

/* Maximum value an `unsigned long long int' can hold.  (Minimum is 0).  */
#define ULONG_LONG_MAX (LONG_LONG_MAX * 2ULL + 1)

#endif /* _LIMITS_H_  */


