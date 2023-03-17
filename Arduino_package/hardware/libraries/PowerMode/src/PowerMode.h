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

#define DEEPSLEEP_MODE                  11
#define STANDBY_MODE                    22

class PMClass {
    public:
        PMClass(void);
        ~PMClass(void);
        void begin(uint32_t sleep_mode, int wakeup_source, uint32_t wakeup_setting = 0);
        void start(void) { start(0, 1, 1, 0, 0, 0); }
        void start(int year, int month, int day, int hour, int min, int sec);

    private :
        uint32_t PM_begin_check = 0;
        uint32_t PM_wakeup_source = 0;
        uint32_t PM_clock = 0;
        uint32_t PM_sleep_duration = 0;
        uint32_t PM_wakeup_setting = 0;
};

extern PMClass PowerMode;

#endif
