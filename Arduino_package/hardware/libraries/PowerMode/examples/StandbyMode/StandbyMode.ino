/*
 This sketch shows how to use power mode standby with multiple wakeup sources

 Example guide:
 https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/PowerMode/Standby%20Mode.html
*/

#include "PowerMode.h"

/*
 =======================================================================
 CONFIGURATION FLAG - Set to 1 for multiple wakeup sources, 0 for single
 =======================================================================
*/
#define USE_MULTIPLE_WAKEUP_SOURCES 1

/*
 =========================================================================
 SINGLE WAKEUP SOURCE CONFIGURATION (when USE_MULTIPLE_WAKEUP_SOURCES = 0)
 =========================================================================
// wake up by AON timer     :   0
// wake up by AON GPIO      :   1
// wake up by RTC           :   2
// wake up by PON GPIO      :   3
// wake up by UART/Serial1  :   4 //Only support 4MHz clock source
// wake up by Gtimer0       :   5 //Only support 4MHz clock source
*/
#define WAKEUP_SOURCE 2
#define RETENTION     0

#if (USE_MULTIPLE_WAKEUP_SOURCES == 0)
// Single wakeup source settings
#if (WAKEUP_SOURCE == 0)
// set AON timer Clock, 1: 4MHz, 0: 100kHz
#define CLOCK 0
// set AON timer sleep duration, 5s
#define SLEEP_DURATION 5
uint32_t PM_AONtimer_setting[2] = {CLOCK, SLEEP_DURATION};
#define WAKUPE_SETTING (uint32_t)(PM_AONtimer_setting)
#elif (WAKEUP_SOURCE == 1)
// set wake up AON GPIO pin : 21 / 22
#define WAKUPE_SETTING 21
#elif (WAKEUP_SOURCE == 2)
// set wake up RTC alarm as 5 seconds
#define ALARM_DAY      0
#define ALARM_HOUR     0
#define ALARM_MIN      0
#define ALARM_SEC      5
uint32_t PM_rtc_Alarm[4] = {ALARM_DAY, ALARM_HOUR, ALARM_MIN, ALARM_SEC};
#define WAKUPE_SETTING (uint32_t)(PM_rtc_Alarm)
#elif (WAKEUP_SOURCE == 3)
// set wake up PON GPIO pin : 0 to 11
#define WAKUPE_SETTING 0
#elif (WAKEUP_SOURCE == 5)
// set wake up Gtimer0 sleep duration, 5s
#define SLEEP_DURATION 5
#define WAKUPE_SETTING SLEEP_DURATION
#else
#define WAKUPE_SETTING 0
#endif
#else

/*
 ============================================================================
 MULTIPLE WAKEUP SOURCES CONFIGURATION (when USE_MULTIPLE_WAKEUP_SOURCES = 1)
 ============================================================================
 To use multiple wakeup sources, use bitwise OR of wakeup source flags:
   SLP_AON_TIMER (BIT0) - AON Timer wakeup
   SLP_AON_GPIO  (BIT1) - AON GPIO wakeup
   SLP_RTC       (BIT2) - RTC wakeup
   SLP_PON_GPIO  (BIT4) - PON GPIO wakeup
   SLP_UART      (BIT6) - UART wakeup
   SLP_GTIMER    (BIT7) - GTimer wakeup
*/

// Example: Wake up by both AON Timer AND GTimer
#define MULTI_WAKEUP_SOURCE (SLP_AON_TIMER | SLP_AON_GPIO)

// Settings array for multiple wakeup sources:
// Index 0: SLP_AON_TIMER settings (clock, duration) - pointer to array
// Index 1: SLP_AON_GPIO/SLP_PON_GPIO settings (pin number)
// Index 2: SLP_RTC settings (day, hour, min, sec) - pointer to array
// Index 3: SLP_GTIMER settings (duration in seconds)

// AON Timer settings: {clock, duration}
#define CLOCK               0    // 0: 100kHz, 1: 4MHz
#define SLEEP_DURATION      5    // 5 seconds
uint32_t PM_AONtimer_setting[2] = {CLOCK, SLEEP_DURATION};

// AON GPIO pin: 21 (PA_1) or 22 (PA_2)
#define AON_GPIO_PIN        21

// PON GPIO pin: 0 to 11
#define PON_GPIO_PIN        0

// RTC alarm settings: {day, hour, min, sec}
#define ALARM_DAY           0
#define ALARM_HOUR          0
#define ALARM_MIN           0
#define ALARM_SEC           5
uint32_t PM_rtc_Alarm[4] = {ALARM_DAY, ALARM_HOUR, ALARM_MIN, ALARM_SEC};

// GTimer duration in seconds
#define GTIMER_DURATION     5

// Settings array for multiple wakeup sources
uint32_t PM_wakeup_settings[MAX_WAKEUP_SOURCES] = {
    (uint32_t)PM_AONtimer_setting,    // Index 0: AON Timer settings
    AON_GPIO_PIN,                     // Index 1: AON GPIO pin (or PON GPIO pin)
    (uint32_t)PM_rtc_Alarm,           // Index 2: RTC settings
    GTIMER_DURATION                   // Index 3: GTimer duration
};

#define RETENTION 0
#endif

void setup()
{
    Serial.begin(115200);
    Serial.println("Standby Mode Demo!");

#if (USE_MULTIPLE_WAKEUP_SOURCES == 0)
    // Single wakeup source
    PowerMode.begin(STANDBY_MODE, WAKEUP_SOURCE, RETENTION, WAKUPE_SETTING);
#else
    // Multiple wakeup sources
    PowerMode.begin(STANDBY_MODE, MULTI_WAKEUP_SOURCE, RETENTION, PM_wakeup_settings);
#endif

    for (int i = 5; i > 0; i--) {
        Serial.print("Enter Standby Mode by ");
        Serial.print(i, DEC);
        Serial.println(" seconds.");
        delay(1000);
    }

    PowerMode.start();
    // the default RTC start at 1970.1.1 00:00:00
    // customize the start time by PowerMode.start(1970, 1, 1, 0, 0, 0);

    Serial.println("You won't see this log");
    while (1)
        ;
}

void loop()
{
    delay(1000);
}
