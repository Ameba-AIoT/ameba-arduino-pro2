/*
 This sketch shows how to use power mode deepsleep with retention

 Example guide:
 https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/PowerMode/Retention%20DeepSleep%20Mode.html
*/

#include "PowerMode.h"

// wake up retention by AON timer :   0
// wake up retention by AON GPIO  :   1
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
// set wake up AON GPIO pin :   21 / 22
#define WAKUPE_SETTING 21
#else
#define WAKUPE_SETTING 0
#endif
// Retained variable in SRAM
__attribute__((section(".retention.data"))) char retention_string[64] __attribute__((aligned(32)));
__attribute__((section(".retention.data"))) uint32_t sum __attribute__((aligned(32)));
void setup()
{
    Serial.begin(115200);
    Serial.println(" Arduino Retention DeepSleep Mode Demo!");

    // Check if the retention string indicates a previous retention state
    if (strcmp(retention_string, "Retention_string: Ameba Pro2") == 0) {
        // Print the retention string after waking up
        Serial.println("Waking up after standby:");
        Serial.println("System running normally after deepsleep and read back retention...");
        Serial.println(retention_string);
        Serial.print("Total = ");
        Serial.println(sum);
        delay(5000);

    } else if (strcmp(retention_string, "Ameba Pro2") != 0) {
        // Initialize retention string
        strncpy(retention_string, "Retention_string: Ameba Pro2", sizeof(retention_string) - 1);
        PowerMode.cleanInvalidateCache(retention_string, sizeof(retention_string));

        // Initialize retention sum
        sum = 1;
        PowerMode.cleanInvalidateCache((uint32_t *)&sum, sizeof(sum));

        PowerMode.begin(DEEPSLEEP_MODE, WAKEUP_SOURCE, RETENTION, WAKUPE_SETTING);

        for (int i = 5; i > 0; i--) {
            Serial.print("Enter DeepSleep Mode by ");
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
