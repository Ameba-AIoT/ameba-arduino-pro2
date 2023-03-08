#include "rtc.h"
#include <time.h>
#include "wait_api.h"

RTCClass::RTCClass(){};
RTCClass::~RTCClass(){};

/**
  * @brief  Initializes the RTC device, include clock, RTC registers and function.
  * @param  none
  * @retval  none
  */
void RTCClass::Init(void) {
    rtc_init();
}

/**
  * @brief  Deinitializes the RTC device.
  * @param  none
  * @retval  none
  */
void RTCClass::DeInit(void) {
    rtc_free();
}

/**
  * @brief  Set the specified timestamp in seconds to RTC.
  * @param  t: Seconds from 1970.1.1 00:00:00 to specified data and time
  *              which is to be set.
  * @retval  none
  */
void RTCClass::Write(long long t) {
    rtc_write(t);
}

/**
  * @brief  Get current timestamp in seconds from RTC.
  * @param  none
  * @retval value: The current timestamp in seconds which is calculated from 
  *              1970.1.1 00:00:00.
  */
long long RTCClass::Read(void) {
    return (rtc_read());
}

/**
  * @brief  Wait for s seconds.
  */
void RTCClass::Wait(int s) {
    wait_ms(1000 * s);
}

/**
 * @brief: convert human readable time to epoch time
*/
long long RTCClass::SetEpoch(int year, int month, int day, int hour, int min, int sec) {
    struct tm t;
    long long t_of_day;

    t.tm_year = year - 1900;  // Year - 1970
    t.tm_mon = month - 1;     // Month, where 0 = jan
    t.tm_mday = day;          // Day of the month
    t.tm_hour = hour;
    t.tm_min = min;
    t.tm_sec = sec;
    t.tm_isdst = -1;  // Is DST on? 1 = yes, 0 = no, -1 = unknown
    t_of_day = mktime(&t);

    // printf("seconds since the Epoch: %d\n", (long)t_of_day);
    return t_of_day;
}

/**
 * @brief: Enable the RTC alarm.
*/
void RTCClass::EnableAlarm(int day, int hour, int min, int sec, void (*rtc_handler)(void)) {
    alarm_t alarm;
    alarm.yday = day;
    alarm.hour = hour;
    alarm.min = min;
    alarm.sec = sec;
    if(1 != rtc_set_alarm(&alarm, (alarm_irq_handler)rtc_handler)) {
        printf("Alarm set fail\r\n");
    } else {
        printf("Alarm set success\r\n");
    }
}

/**
 * @brief: Disable the RTC alarm.
*/
void RTCClass::DisableAlarm(void) {
    rtc_disable_alarm();
    printf("Alarm disabled\r\n");
}

RTCClass rtc;
