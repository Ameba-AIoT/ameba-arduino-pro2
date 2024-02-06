/*
 * This example describes how to use watchdog api.
 * In this example, watchdog is setup to 5s timeout.
 * Watchdog won't bark if we refresh it before timeout in smallTask.
 * The timer is also reloaded after refresh.
 * Otherwise, while running bigTask, watchdog will restart system in default or call callback function if registered.

 * Example guide:
 * https://www.amebaiot.com/en/amebapro2-arduino-wdt/
 */

#include "WDT.h"

#define AON_WDT_Enable (0)
#if AON_WDT_Enable == 0
#define RUN_CALLBACK_IF_WATCHDOG_BARKS (0)
#endif

WDT wdt(AON_WDT_Enable);

void setup()
{
    Serial.begin(115200);

    // setup 5s watchdog
    wdt.init(5000);

#if AON_WDT_Enable
    // when WDT always on IRQ is not supported
#else
#if RUN_CALLBACK_IF_WATCHDOG_BARKS
    wdt.init_irq((wdt_irq_handler)my_watchdog_irq_handler, 0);
#else
    // system would restart in default when watchdog barks
#endif
#endif

    // enable watchdog timer
    wdt.start();

    Small_Task();
    Big_Task();
    while (1)
        ;
}

void loop()
{
    delay(1000);
}

void Small_Task(void)
{
    Serial.println();
    Serial.println("......Doing small task......");
    wdt_dummy_task();
    Serial.println("Small_Task finished refresh watchdog.");
    wdt.refresh();
}

void Big_Task(void)
{
    Serial.println();
    Serial.println("......Doing big task, up to 10......");
    for (int i = 1; i <= 10; i++) {
        Serial.print("doing dummy task #");
        Serial.println(i, DEC);
        wdt_dummy_task();
    }
    Serial.println("Big_Task finished refresh watchdog.");
    wdt.refresh();
}

void my_watchdog_irq_handler(uint32_t id)
{
    Serial.println("watchdog barks!!!");
    wdt.stop();
}
