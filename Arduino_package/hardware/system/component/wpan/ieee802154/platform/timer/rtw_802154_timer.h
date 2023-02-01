
/**
 * @brief Module that defines the Low Power Timer Abstraction Layer for the 802.15.4 driver.
 *
 */

#ifndef RTW_802154_LP_TIMER_API_H_
#define RTW_802154_LP_TIMER_API_H_

#include <stdbool.h>
#include <stdint.h>
#include "rtw_802154_timer_wrapper.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup rtw_802154_timer Low Power Timer Abstraction Layer for the 802.15.4 driver
 * @{
 * @ingroup rtw_802154_timer
 * @brief Low Power Timer Abstraction Layer interface for the 802.15.4 driver.
 *
 * The Low Power Timer Abstraction Layer is an abstraction layer of the timer that is meant
 * to be used by the Realtek 802.15.4 driver. This timer is intended to provide low latency
 * (max. 100 microseconds) to allow the implementation of the following features in the driver code:
 * * Timing out when waiting for an ACK frame
 * * SIFS and LIFS
 * * CSMA/CA
 * * CSL
 * * Auto polling by rx-off-when-idle devices
 *
 * @note Most of the Low Power Timer Abstraction Layer API is not intended to be called directly
 *       by the 802.15.4 driver modules. This API is used by the Timer Scheduler module included
 *       in the driver. Other modules should use the Timer Scheduler API. The exception are
 *       initialization and deinitialization functions @ref rtw_802154_timer_init() and
 *       @ref rtw_802154_timer_deinit(), as these functions are called from the global initialization
 *       and deinitialization functions @ref rtw_802154_init() and @ref rtw_802154_deinit().
 */

#ifndef RTW_802154_XTAL_ACCURACY
#define RTW_802154_XTAL_ACCURACY       40
#endif// The crystal used on AmebaD2 is ? (20ppm accuracy)

static inline uint64_t rtw_802154_rtc_get_current_us(void);
static inline uint64_t rtw_802154_rtc_get_target_time(uint32_t t0, uint32_t dt, uint64_t now);
uint64_t rtw_802154_rtc_get_us(void);
uint64_t rtw_802154_rtc_get_ms(void);
uint32_t rtw_802154_rtc_get_remain_us(uint32_t t0, uint32_t dt);
uint32_t rtw_802154_rtc_get_remain_ms(uint32_t t0, uint32_t dt);
static void rtw_802154_rtc_overflow_callback(void *para);
void rtw_802154_rtc_init(void);
void rtw_802154_rtc_deinit(void);
void rtw_802154_timer_init(void);
void rtw_802154_timer_deinit(void);
uint64_t rtw_802154_timer_time_get(void);
uint32_t rtw_802154_timer_granularity_get(void);
void rtw_802154_timer_start(uint32_t t0, uint32_t dt);
void rtw_802154_timer_stop(void);
extern void rtw_802154_timer_fired(void);

/**
 *@}
 **/

#ifdef __cplusplus
}
#endif

#endif /* RTW_802154_LP_TIMER_API_H_ */
