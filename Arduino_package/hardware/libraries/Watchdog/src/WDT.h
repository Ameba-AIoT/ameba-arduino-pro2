#ifndef __WDT_H__
#define __WDT_H__

#include <Arduino.h>

#include "device.h"
#include "diag.h"
#include "main.h"
#include "wdt_api.h"

void wdt_dummy_task(void);

class WDT {
public:
    WDT(void);
    WDT(int aon_en);
    ~WDT(void);

    void init(uint32_t timeout_ms);
    void start(void);
    void stop(void);
    void refresh(void);
    void init_irq(wdt_irq_handler handler, uint32_t id);

private:
    int aon_wdt_check = 0;
};
#endif
