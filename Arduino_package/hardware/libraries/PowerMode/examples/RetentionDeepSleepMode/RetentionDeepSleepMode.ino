/*
 This sketch shows how to use power mode deepsleep with retention and multiple wakeup sources

 Example guide:
 https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/PowerMode/Retention%20DeepSleep%20Mode.html
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
*/
// wake up retention by AON timer :   0
// wake up retention by AON GPIO  :   1
#define WAKEUP_SOURCE 0
#define RETENTION     1

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
// set wake up AON GPIO pin :   21 / 22
#define WAKUPE_SETTING 21
#else
#define WAKUPE_SETTING 0
#endif

#else

/*
 ============================================================================
 MULTIPLE WAKEUP SOURCES CONFIGURATION (when USE_MULTIPLE_WAKEUP_SOURCES = 1)
 ============================================================================
 To use multiple wakeup sources, use bitwise OR of wakeup source flags:
   DS_AON_TIMER (BIT0) - AON Timer wakeup
   DS_AON_GPIO  (BIT1) - AON GPIO wakeup
 Note: DS_RTC is not supported with retention
*/

// Example: Wake up by both AON Timer AND AON GPIO
#define MULTI_WAKEUP_SOURCE (DS_AON_TIMER | DS_AON_GPIO)

// Settings array for multiple wakeup sources:
// Index 0: DS_AON_TIMER settings (clock, duration) - pointer to array
// Index 1: DS_AON_GPIO settings (pin number)
// Index 2: DS_RTC settings (day, hour, min, sec) - pointer to array
// Index 3: DS_COMP settings

// AON Timer settings: {clock, duration}
#define CLOCK               0    // 0: 100kHz, 1: 4MHz
#define SLEEP_DURATION      5    // 5 seconds
uint32_t PM_AONtimer_setting[2] = {CLOCK, SLEEP_DURATION};

// AON GPIO pin: 21 (PA_1) or 22 (PA_2)
#define AON_GPIO_PIN        21

// Settings array for multiple wakeup sources
uint32_t PM_wakeup_settings[MAX_WAKEUP_SOURCES] = {
    (uint32_t)PM_AONtimer_setting,    // Index 0: AON Timer settings
    AON_GPIO_PIN,                     // Index 1: AON GPIO pin
    0,                                // Index 2: RTC (not used with retention)
    0                                 // Index 3: COMP (not used)
};

#define RETENTION 1
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

#if (USE_MULTIPLE_WAKEUP_SOURCES == 0)
        // Single wakeup source
        PowerMode.begin(DEEPSLEEP_MODE, WAKEUP_SOURCE, RETENTION, WAKUPE_SETTING);
#else
        // Multiple wakeup sources
        PowerMode.begin(DEEPSLEEP_MODE, MULTI_WAKEUP_SOURCE, RETENTION, PM_wakeup_settings);
#endif

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
