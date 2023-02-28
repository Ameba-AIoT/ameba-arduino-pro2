#include "WDT.h"

void wdt_dummy_task(void) {
    hal_delay_ms(1000);
}

WDT::WDT(int aon_wdt_check) {
    AON_WDT = aon_wdt_check;
};

WDT::~WDT(){};

//#define AON_WDT     0

#if 0
/**
 *  @brief   Initial the watch dog time setting
 *
 *  @param   timeout_ms: the watch-dog timer timeout value, in ms.(Min Value 1000 and Max value 65535)
 *           default action of timeout is to reset the whole system.
 *  @return  None
 *
 */
void WDT::init(uint32_t timeout_ms) {
    watchdog_init(timeout_ms);
}

/**
 *  @brief   Start the watchdog counting
 *
 *  @param   None
 *  @return  None
 *
 */
void WDT::start(void) {
    watchdog_start();
}

/**
 *  @brief   Stop the watchdog counting
 *
 *  @param   None
 *  @return  None
 *
 */
void WDT::stop(void) {
    watchdog_stop();
}

/**
 *  @brief   Refresh the watchdog counting to prevent WDT timeout
 *
 *  @param   None
 *  @return  None
 *
 */
void WDT::refresh(void) {
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
void WDT::init_irq(wdt_irq_handler handler, uint32_t id) {
    watchdog_irq_init(handler, id);
}



#else


/**
 *  @brief   Initial the watch dog time setting
 *
 *  @param   timeout_ms: the watch-dog timer timeout value, in ms.(Min Value 1000 and Max value 65535)
 *           default action of timeout is to reset the whole system.
 *  @return  None
 *
 */
void WDT::init(uint32_t timeout_ms) {
    if (AON_WDT) {
        hal_aon_wdt_enable(0, timeout_ms);
    } else {
        hal_wdt_reset(0x17);
        hal_wdt_init((timeout_ms * 1000));
    }
}

/**
 *  @brief   Start the watchdog counting
 *
 *  @param   None
 *  @return  None
 *
 */
void WDT::start(void) {
    if (AON_WDT) {
        hal_wdt_aon_enable();
    } else {
        hal_wdt_enable();
    }
}

/**
 *  @brief   Stop the watchdog counting
 *
 *  @param   None
 *  @return  None
 *
 */
void WDT::stop(void) {
    if (AON_WDT) {
        hal_wdt_aon_disable();
    } else {
        hal_wdt_disable();
    }
}

/**
 *  @brief   Refresh the watchdog counting to prevent WDT timeout
 *
 *  @param   None
 *  @return  None
 *
 */
void WDT::refresh(void) {
    if (AON_WDT) {
        hal_wdt_aon_disable();
        hal_wdt_aon_enable();
    } else {
        hal_wdt_refresh();
    }
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
void WDT::init_irq(wdt_irq_handler handler, uint32_t id) {
    if (AON_WDT) {
        dbg_printf("\r\nThe AON WDT dosen't supprt IRQ Mode\r\n");
    } else {
        hal_wdt_reg_irq((irq_handler_t)handler, (void *)id);
    }
}



#endif
