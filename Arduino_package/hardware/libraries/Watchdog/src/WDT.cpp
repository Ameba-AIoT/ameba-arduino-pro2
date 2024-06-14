#include "WDT.h"

void wdt_dummy_task(void)
{
    hal_delay_ms(1000);
}

WDT::WDT(int aon_en)
{
    aon_wdt_check = aon_en;
}

WDT::~WDT(){};

/**
 *  @brief   Initial the watch dog time setting
 *
 *  @param   timeout_ms: the watch-dog timer timeout value, in ms.(Min Value 1000 and Max value 65535)
 *           default action of timeout is to reset the whole system.
 *  @return  None
 *
 */
void WDT::init(uint32_t timeout_ms)
{
    // watchdog_init(timeout_ms);
    watchdog_init_arduino(timeout_ms, aon_wdt_check);
}

/**
 *  @brief   Start the watchdog counting
 *
 *  @param   None
 *  @return  None
 *
 */
void WDT::start(void)
{
    watchdog_start();
}

/**
 *  @brief   Stop the watchdog counting
 *
 *  @param   None
 *  @return  None
 *
 */
void WDT::stop(void)
{
    watchdog_stop();
}

/**
 *  @brief   Refresh the watchdog counting to prevent WDT timeout
 *
 *  @param   None
 *  @return  None
 *
 */
void WDT::refresh(void)
{
    watchdog_refresh();
}

/**
 *  @brief   Switch the watchdog timer to interrupt mode and
 *           register a watchdog timer timeout interrupt handler.
 *           The interrupt handler will be called when the watch-dog
 *           timer is timeout.
 *
 *  @param   handler: the callback function for WDT timeout interrupt.
 *           id: the parameter for the callback function
 *  @return  None
 *
 */
void WDT::init_irq(wdt_irq_handler handler, uint32_t id)
{
    watchdog_irq_init(handler, id);
}
