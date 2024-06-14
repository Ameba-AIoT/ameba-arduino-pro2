/*
 This sketch shows how to use power mode deepsleep

 Example guide:
 https://www.amebaiot.com/en/amebapro2-arduino-deepsleep/
 */

#include "PowerMode.h"

// wake up by AON timer :   0
// wake up by AON GPIO  :   1
// wake up by RTC       :   2
#define WAKEUP_SOURCE 0

#if (WAKEUP_SOURCE == 0)
// set AON timer Clock, 1: 4MHz, 0: 100kHz
#define CLOCK 0
// set AON timer sleep duration, 5s
#define SLEEP_DURATION 5
uint32_t PM_AONtimer_setting[2] = {CLOCK, SLEEP_DURATION};
#define WAKUPE_SETTING (uint32_t)(PM_AONtimer_setting)
#elif (WAKEUP_SOURCE == 1)
// set wake up AON GPIO pin :   21 / 22
#define WAKUPE_SETTING 21
#elif (WAKEUP_SOURCE == 2)
// set wake up RTC alarm as 5 seconds
#define ALARM_DAY      0
#define ALARM_HOUR     0
#define ALARM_MIN      0
#define ALARM_SEC      5
uint32_t PM_rtc_Alarm[4] = {ALARM_DAY, ALARM_HOUR, ALARM_MIN, ALARM_SEC};
#define WAKUPE_SETTING (uint32_t)(PM_rtc_Alarm)
#else
#define WAKUPE_SETTING 0
#endif

void setup()
{
    Serial.begin(115200);
    Serial.println("DeepSleep Mode Demo!");
    PowerMode.begin(DEEPSLEEP_MODE, WAKEUP_SOURCE, WAKUPE_SETTING);

    for (int i = 5; i > 0; i--) {
        Serial.print("Enter DeepSleep Mode by ");
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
