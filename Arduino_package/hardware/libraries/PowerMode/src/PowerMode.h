#ifndef _POWERMODE_H_
#define _POWERMODE_H_

#include <Arduino.h>
#include "power_mode_api.h"
#include "gpio_api.h"
#include "gpio_ex_api.h"
#include "gpio_irq_api.h"
#include "gpio_irq_ex_api.h"
#include "sys_api.h"
#include "rtc.h"
#include "GTimer.h"
#include "serial_api.h"

#define DEEPSLEEP_MODE 11
#define STANDBY_MODE   22

// Maximum number of wakeup sources supported
#define MAX_WAKEUP_SOURCES 4

class PMClass {
public:
    PMClass(void);
    ~PMClass(void);
    // single wakeup source API
    void begin(uint32_t sleep_mode, int wakeup_source, uint32_t retention, uint32_t wakeup_setting = 0);
    // Multiple wakeup sources using bitwise OR
    // wakeup_source: bitwise OR of wakeup source flags (e.g., DS_AON_TIMER | DS_AON_GPIO)
    // wakeup_settings: pointer to array of settings, one per wakeup source bit set
    //                  Order should match the bit positions: [DS_AON_TIMER, DS_AON_GPIO, DS_RTC, DS_COMP]
    void begin(uint32_t sleep_mode, uint32_t wakeup_source, uint32_t retention, uint32_t *wakeup_settings);
    void start(void)
    {
        start(0, 1, 1, 0, 0, 0);
    }
    void start(int year, int month, int day, int hour, int min, int sec);

    void cleanInvalidateCache(void *address, size_t size);
private:
    uint32_t PM_begin_check = 0;
    uint32_t PM_wakeup_source = 0;
    uint32_t PM_clock = 0;
    uint32_t PM_sleep_duration = 0;
    uint32_t PM_wakeup_setting = 0;
    uint32_t PM_retention_setting = 0;
    // For multiple wakeup sources support
    uint32_t PM_wakeup_settings[MAX_WAKEUP_SOURCES] = {0};
    uint32_t PM_wakeup_source_count = 0;
};

extern PMClass PowerMode;

#endif
