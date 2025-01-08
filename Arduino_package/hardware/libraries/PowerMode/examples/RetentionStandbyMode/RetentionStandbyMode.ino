/*
 This sketch shows how to use power mode standby with retention

 Example guide:
 tbd
 */

#include "PowerMode.h"

// wake up by AON timer     :   0
// wake up by AON GPIO      :   1
// wake up by PON GPIO      :   2
// wake up by Gtimer0       :   3 //Only support 4MHz clock source
#define WAKEUP_SOURCE 0
#define RETENTION     1

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
// set wake up PON GPIO pin : 0 to 11
#define WAKUPE_SETTING 0
#elif (WAKEUP_SOURCE == 3)
// set wake up Gtimer0 sleep duration, 5s
#define SLEEP_DURATION 5
#define WAKUPE_SETTING SLEEP_DURATION
#else
#define WAKUPE_SETTING 0
#endif

// Retained variable in SRAM
__attribute__((section(".retention.data"))) char retention_string[64] __attribute__((aligned(32)));
__attribute__((section(".retention.data"))) uint32_t sum __attribute__((aligned(32)));
void setup()
{
    Serial.begin(115200);
    Serial.println(" Arduino Retention Standby Mode Demo!");

    // Check if the retention string indicates a previous retention state
    if (strcmp(retention_string, "Retention_string: Ameba Pro2") == 0) {
        // Print the retention string after waking up
        Serial.println("Waking up after standby:");
        Serial.println("System running normally after standby and read back retention...");
        Serial.println(retention_string);
        Serial.print("Total = ");
        Serial.println(sum);
        delay(5000);
    } else if (strcmp(retention_string, "Ameba Pro2") != 0) {
        // Initialize retention string
        strncpy(retention_string, "Retention_string: Ameba Pro2", sizeof(retention_string) - 1);
        PowerMode.cleanInvalidateCache(retention_string, sizeof(retention_string));

        // Initialize retention_sum
        sum = 1;
        PowerMode.cleanInvalidateCache((uint32_t *)&sum, sizeof(sum));

        PowerMode.begin(STANDBY_MODE, WAKEUP_SOURCE, RETENTION, WAKUPE_SETTING);

        for (int i = 5; i > 0; i--) {
            Serial.print("Enter Standby Mode by ");
            Serial.print(i, DEC);
            Serial.println(" seconds.");
            delay(1000);
        }
        PowerMode.start();
    }
}

void loop()
{
    // do nothing
    delay(5000);
}
