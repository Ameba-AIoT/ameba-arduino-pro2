/*
 * FreeRTOS POSIX V1.2.1
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */

/**
 * @file FreeRTOS_POSIX_clock.c
 * @brief Implementation of clock functions in time.h
 */

/* C standard library includes. */
#include <stddef.h>
#include <string.h>

/* FreeRTOS+POSIX includes. */
#include "FreeRTOS_POSIX.h"
#include "FreeRTOS_POSIX/errno.h"
#include "FreeRTOS_POSIX/time.h"
#include "FreeRTOS_POSIX/utils.h"

#include "sntp/sntp.h"

/* Declaration of snprintf. The header stdio.h is not included because it
 * includes conflicting symbols on some platforms. */
extern int snprintf( char * s,
                     size_t n,
                     const char * format,
                     ... );

/* _WEAK */ int rtsTimezone;
extern int rtsTimezone; //define in librtscamkit.a default value is 8*3600(bejing)

/*-----------------------------------------------------------*/

clock_t clock( void )
{
    /* This function is currently unsupported. It will always return -1. */

    return ( clock_t ) -1;
}

/*-----------------------------------------------------------*/

int clock_getcpuclockid( pid_t pid,
                         clockid_t * clock_id )
{
    /* Silence warnings about unused parameters. */
    ( void ) pid;
    ( void ) clock_id;

    /* This function is currently unsupported. It will always return -1 and
     * set errno to EPERM. */
    errno = EPERM;

    return -1;
}

/*-----------------------------------------------------------*/

int clock_getres( clockid_t clock_id,
                  struct timespec * res )
{
    /* Silence warnings about unused parameters. */
    ( void ) clock_id;

    /* Convert FreeRTOS tick resolution as timespec. */
    if( res != NULL )
    {
        res->tv_sec = 0;
        res->tv_nsec = NANOSECONDS_PER_TICK;
    }

    return 0;
}

/*-----------------------------------------------------------*/
int __clock_gettime(struct timespec * tp)
{
	unsigned int update_tick = 0;
	long long update_sec = 0, update_usec = 0, current_sec = 0;
	long current_usec = 0;
	unsigned int current_tick = xTaskGetTickCount();

	sntp_get_lasttime(&update_sec, &update_usec, &update_tick);
	//if(update_tick) {
		long tick_diff_sec, tick_diff_ms;

		tick_diff_sec = (current_tick - update_tick) / configTICK_RATE_HZ;
		tick_diff_ms = (current_tick - update_tick) % configTICK_RATE_HZ / portTICK_RATE_MS;
		update_sec += tick_diff_sec;
		update_usec += (tick_diff_ms * 1000);
        current_sec = update_sec + update_usec / 1000000;
        current_usec = update_usec % 1000000;
	//}
	//else {
		//current_sec = current_tick / configTICK_RATE_HZ;
	//}
	tp->tv_sec = current_sec;
    tp->tv_nsec = current_usec*1000;
	//sntp_set_lasttime(update_sec,update_usec,update_tick);
    //printf("update_sec %d update_usec %d update_tick %d tvsec %d\r\n",update_sec,update_usec,update_tick,tp->tv_sec);
}

int clock_gettime( clockid_t clock_id,
                   struct timespec * tp )
{
    TimeOut_t xCurrentTime = { 0 };
    int iStatus = 0;

    /* Intermediate variable used to convert TimeOut_t to struct timespec.
     * Also used to detect overflow issues. It must be unsigned because the
     * behavior of signed integer overflow is undefined. */
    uint64_t ullTickCount = 0ULL;

    /* Silence warnings about unused parameters. */
    ( void ) clock_id;

    /* Check tp. */
    if( tp == NULL )
    {
        /* POSIX does not specify this function setting errno for invalid
         * parameters, so just set the return value. */
        iStatus = -1;
    }

    if( iStatus == 0 )
    {
        switch (clock_id) {
        case CLOCK_REALTIME:
            __clock_gettime(tp);  
        break;
        case CLOCK_MONOTONIC:
            /* Get the current tick count and overflow count. vTaskSetTimeOutState()
             * is used to get these values because they are both static in tasks.c. */
            vTaskSetTimeOutState( &xCurrentTime );

            /* Adjust the tick count for the number of times a TickType_t has overflowed.
             * portMAX_DELAY should be the maximum value of a TickType_t. */
            ullTickCount = ( uint64_t ) ( xCurrentTime.xOverflowCount ) << ( sizeof( TickType_t ) * 8 );

            /* Add the current tick count. */
            ullTickCount += xCurrentTime.xTimeOnEntering;

            /* Convert ullTickCount to timespec. */
            UTILS_NanosecondsToTimespec( ( int64_t ) ullTickCount * NANOSECONDS_PER_TICK, tp );
        break;
        default:
            iStatus = -1;
        }
    }
    

    return iStatus;
}

/*-----------------------------------------------------------*/

int clock_nanosleep( clockid_t clock_id,
                     int flags,
                     const struct timespec * rqtp,
                     struct timespec * rmtp )
{
    int iStatus = 0;
    TickType_t xSleepTime = 0;
    struct timespec xCurrentTime = { 0 };

    /* Silence warnings about unused parameters. */
    ( void ) clock_id;
    ( void ) rmtp;
    ( void ) flags; /* This is only ignored if INCLUDE_vTaskDelayUntil is 0. */

    /* Check rqtp. */
    if( UTILS_ValidateTimespec( rqtp ) == false )
    {
        iStatus = EINVAL;
    }

    /* Get current time */
    if( ( iStatus == 0 ) && ( clock_gettime( CLOCK_REALTIME, &xCurrentTime ) != 0 ) )
    {
        iStatus = EINVAL;
    }

    if( iStatus == 0 )
    {
        /* Check for absolute time sleep. */
        if( ( flags & TIMER_ABSTIME ) == TIMER_ABSTIME )
        {
            /* Get current time */
            if( clock_gettime( CLOCK_REALTIME, &xCurrentTime ) != 0 )
            {
                iStatus = EINVAL;
            }

            /* Get number of ticks until absolute time. */
            if( ( iStatus == 0 ) && ( UTILS_AbsoluteTimespecToDeltaTicks( rqtp, &xCurrentTime, &xSleepTime ) == 0 ) )
            {
                /* Delay until absolute time if vTaskDelayUntil is available. */
                #if ( INCLUDE_vTaskDelayUntil == 1 )

                    /* Get the current tick count. This variable isn't declared
                     * at the top of the function because it's only used and needed
                     * if vTaskDelayUntil is available. */
                    TickType_t xCurrentTicks = xTaskGetTickCount();

                    /* Delay until absolute time. */
                    vTaskDelayUntil( &xCurrentTicks, xSleepTime );
                #else

                    /* If vTaskDelayUntil isn't available, ignore the TIMER_ABSTIME flag
                     * and sleep for a relative time. */
                    vTaskDelay( xSleepTime );
                #endif
            }
        }
        else
        {
            /* If TIMER_ABSTIME isn't specified, convert rqtp to ticks and
             * sleep for a relative time. */
            if( UTILS_TimespecToTicks( rqtp, &xSleepTime ) == 0 )
            {
                vTaskDelay( xSleepTime );
            }
        }
    }

    return iStatus;
}

/*-----------------------------------------------------------*/
/* _WEAK */ void clock_set_rtc_time(uint32_t seconds)
{
  
}
int clock_settime( clockid_t clock_id,
                   const struct timespec * tp )
{
#if 0
    /* Silence warnings about unused parameters. */
    ( void ) clock_id;
    ( void ) tp;

    /* This function is currently unsupported. It will always return -1 and
     * set errno to EPERM. */
    errno = EPERM;
    return -1;
#else
    ( void ) clock_id;
    sntp_set_lasttime(tp->tv_sec,tp->tv_nsec/1000,xTaskGetTickCount());
    clock_set_rtc_time(tp->tv_sec);
    return 0;
#endif
    
}

/*-----------------------------------------------------------*/
void setTimezone(int tz)
{
    rtsTimezone = tz;
}
int getTimezone(void)
{
    return rtsTimezone;
}

#if defined (__ICCARM__)
struct tm * localtime_r( const time_t * timer,
                         struct tm * result )
{
#if 0
    /* Silence warnings about unused parameters. */
    ( void ) timer;
    ( void ) result;

    /* This function is only supported if the "custom" FreeRTOS+POSIX tm struct
     * is used. */
    #if ( posixconfigENABLE_TM == 0 )
        errno = ENOTSUP;

        return NULL;
    #else

        /* Zero the tm, then store the FreeRTOS tick count. The input parameter
         * timer isn't used. */
        ( void ) memset( result, 0x00, sizeof( struct tm ) );
        result->tm_tick = ( time_t ) xTaskGetTickCount();

        return result;
    #endif
#endif
      struct tm* tmp = NULL;
      time_t tm_tmp = *timer;
      tm_tmp += rtsTimezone;
      tmp = localtime(&tm_tmp);
      tmp->tm_year += 1900;
      tmp->tm_mon += 1;
      if (tmp)
      {
          memcpy(result, tmp, sizeof(struct tm));
          tmp = result;
      }
      return tmp;
}
#endif

/*-----------------------------------------------------------*/

int nanosleep( const struct timespec * rqtp,
               struct timespec * rmtp )
{
    int iStatus = 0;
    TickType_t xSleepTime = 0;

    /* Silence warnings about unused parameters. */
    ( void ) rmtp;

    /* Check rqtp. */
    if( UTILS_ValidateTimespec( rqtp ) == false )
    {
        errno = EINVAL;
        iStatus = -1;
    }

    if( iStatus == 0 )
    {
        /* Convert rqtp to ticks and delay. */
        if( UTILS_TimespecToTicks( rqtp, &xSleepTime ) == 0 )
        {
            vTaskDelay( xSleepTime );
        }
    }

    return iStatus;
}

/*-----------------------------------------------------------*/
#if ( posixconfigENABLE_TM == 1 )
size_t strftime( char * s,
                 size_t maxsize,
                 const char * format,
                 const struct tm * timeptr )
{
    int iStatus = 0;
    size_t bytesPrinted = 0;

    /* Silence warnings about unused parameters. */
    ( void ) format;

    /* Print the time in the buffer. */
    iStatus = snprintf( s, maxsize, "%ld", ( long int ) timeptr->tm_tick );

    /* Check for encoding and size errors. */
    if( ( iStatus > 0 ) && ( ( size_t ) iStatus < maxsize ) )
    {
        bytesPrinted = ( size_t ) iStatus;
    }

    return bytesPrinted;
}
#endif
/*-----------------------------------------------------------*/

time_t time( time_t * tloc )
{
#if 0
    /* Read the current FreeRTOS tick count and convert it to seconds. */
    time_t xCurrentTime = ( time_t ) ( xTaskGetTickCount() / configTICK_RATE_HZ );
#else
    time_t xCurrentTime;
    struct timespec tp;
    
    __clock_gettime(&tp);
    xCurrentTime = tp.tv_sec;
#endif
    /* Set the output parameter if provided. */
    if( tloc != NULL )
    {
        *tloc = xCurrentTime;
    }
    
    return xCurrentTime;
}

/*-----------------------------------------------------------*/
