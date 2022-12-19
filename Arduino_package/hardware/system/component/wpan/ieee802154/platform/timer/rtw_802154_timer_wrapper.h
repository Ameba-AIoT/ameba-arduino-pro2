#ifndef RTW_802154_SIMU_RTC_H_
#define RTW_802154_SIMU_RTC_H_

#include <stdbool.h>
#include <stdint.h>
#include "basic_types.h"
#include "osdep_service.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONFIG_PLATFORM_AMEBAD2
#define  RTW_802154_GTIMER_INDEX_RTC  (0)   //Testchip TIM0~7 is 32k 
#define  RTW_802154_GTIMER_INDEX_802154  (1)
#define  RTW_802154_GTIMER_INDEX_ALARM_US  (2)
#define  RTW_802154_GTIMER_INDEX_ALARM_MS  (3)
#define  RTW_802154_XTAL_ACCURACY       40
#define  RTW_802154_GTIMER_TICKS_TO_US(ticks) ((float)ticks * 1000000 / 32768)
#define  RTW_802154_GTIMER_US_TO_TICKS(us) ((float)us * 32768 / 1000000)
#elif defined(CONFIG_PLATFORM_AMEBALITE)
#define  RTW_802154_GTIMER_INDEX_RTC  (10)
#define  RTW_802154_GTIMER_INDEX_802154  (11)
#define  RTW_802154_GTIMER_INDEX_ALARM_US  (12)
#define  RTW_802154_GTIMER_INDEX_ALARM_MS  (13)
#define  RTW_802154_XTAL_ACCURACY       40
#define  RTW_802154_GTIMER_TICKS_TO_US(us) (us)
#define  RTW_802154_GTIMER_US_TO_TICKS(ticks) (ticks)
#else
#error "undefine 802154 GTIMER INDEX!!!!!!!!!!!"
#endif

#if !defined(RTW_802154_GTIMER_INDEX_RTC)\
	|| !defined(RTW_802154_GTIMER_INDEX_802154)\
	|| !defined(RTW_802154_GTIMER_INDEX_ALARM_US)\
	|| !defined(RTW_802154_GTIMER_INDEX_ALARM_MS)
#error "undefine 802154 GTIMER INDEX!!!!!!!!!!!"
#endif

#define  RTW_802154_ALARM_MS_USE_GTIMER 1
#define  RTW_802154_ALARM_TIMER_PROCESS 1 //avoid TaskletScheduler::PostTasklet fail, alarm timer callback will run in thread task instead of irq or gtimer task if define 1
#define  USE_GTIMER_API  0
#define  USE_GTIMER_CALLBACK_TASK 0

/*
time accuracy
100us timer
USE_GTIMER_API  0 USE_GTIMER_CALLBACK_TASK 0 125us>
USE_GTIMER_API  1 USE_GTIMER_CALLBACK_TASK 0 129us>
USE_GTIMER_API  0 USE_GTIMER_CALLBACK_TASK 1 137us>
USE_GTIMER_API  1 USE_GTIMER_CALLBACK_TASK 1 143us
*/
#define RTW_RTC_MAX_COUNT  (0xEFFFFFFF)//0xEFFFFFFF to avoid overflow if 1M
#if 0
#define TICKS_PER_OVERFLOW     (RTW_RTC_MAX_COUNT+1)
#else
#define US_PER_OVERFLOW     RTW_RTC_MAX_COUNT
#endif
#define EPOCH_32BIT               (1ULL << 32)
#define EPOCH_FROM_TIME(time)        ((time) & ((uint64_t)UINT32_MAX << 32))
#define RTW_802154_TIMER_US_PER_TICK  RTW_802154_GTIMER_TICKS_TO_US((uint64_t)1)//if 1M clock, need to be 1

typedef enum {
	RTW_GTIMER_RTC_TIMER = 0,
	RTW_GTIMER_802154_TIMER,
	RTW_GTIMER_ALARM_US_TIMER,
	RTW_GTIMER_ALARM_MS_TIMER,

	RTW_GTIMER_TIMER_MAX,
} rtw_gtimer_type;

typedef void (*rtw_802154_gtimer_irq_handler)(void *para);

#if USE_GTIMER_CALLBACK_TASK
typedef struct {
	_xqueue gtimer_queue;
	struct task_struct gtimer_callback_task;
} rtw_gtimer_callback_t;
#endif

void rtw_802154_gtimer_callback_init(void);
void rtw_802154_gtimer_callback_deinit(void);
void rtw_802154_gtimer_init(void);
void rtw_802154_gtimer_deinit(void);
void rtw_802154_gtimer_wrapper_init(rtw_gtimer_type timer, void *handler, bool timer_task_execute);
void rtw_802154_gtimer_wrapper_deinit(rtw_gtimer_type timer);
void rtw_802154_gtimer_wrapper_stop(rtw_gtimer_type timer);
void rtw_802154_gtimer_wrapper_start_periodical(rtw_gtimer_type timer, uint32_t remaining_us, void *para);
void rtw_802154_gtimer_wrapper_start_one_shot(rtw_gtimer_type timer, uint32_t remaining_us, void *para);
uint64_t rtw_802154_gtimer_wrapper_read_us(rtw_gtimer_type timer);

#ifdef __cplusplus
}
#endif

#endif /* RTW_802154_SIMU_RTC_H_ */

