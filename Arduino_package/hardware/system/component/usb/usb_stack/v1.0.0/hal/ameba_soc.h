/*
 * Copyright (c) 2026 Realtek Semiconductor Corp.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _AMEBA_SOC_SHIM_H
#define _AMEBA_SOC_SHIM_H

#include <stdio.h>
#include "cmsis.h"
#include "FreeRTOS.h"
#include "task.h"
#include "ameba_usb.h"
#include "hal_timer.h"     /* hal_read_systime_us() - __STATIC_INLINE, needs this header pulled in directly */
#include "hal_cache.h"     /* dcache_clean_by_addr() / dcache_invalidate_by_addr() */
#include "osdep_service.h" /* rtw_get_random_bytes() */

#ifndef __PACKED
#define __PACKED __attribute__((packed))
#endif

#ifndef UNUSED
#define UNUSED(x) ((void)(x))
#endif

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

/*
 * rtl8735b's D-cache/RNG helpers exist under different names/signatures than
 * pro3's own chips use (see component/usb/usb_stack/v1.0.0/{device,host}: DCache_Clean,
 * DCache_Invalidate, TRNG_get_random_bytes - all undefined-reference at link
 * time otherwise). Map them onto the rtl8735b equivalents:
 *   DCache_Clean/Invalidate(addr, len)     -> dcache_{clean,invalidate}_by_addr()
 *   TRNG_get_random_bytes(buf, len)        -> rtw_get_random_bytes() (same
 *                                              Ameba-wide RNG entry point
 *                                              already used for e.g. wpa_supplicant)
 */
#define DCache_Clean(addr, len)       dcache_clean_by_addr((uint32_t *)(addr), (int32_t)(len))
#define DCache_Invalidate(addr, len)  dcache_invalidate_by_addr((uint32_t *)(addr), (int32_t)(len))
#define TRNG_get_random_bytes(buf, len) rtw_get_random_bytes((buf), (len))

/*
 * DelayUs() (used by pro3's common/usb_os.c & usb_phy.c) is only compiled
 * into freertos_service.c's _freertos_udelay_os() for a handful of OTHER
 * platforms (8711B/8721D/AMEBAD2/AMEBALITE/AMEBADPLUS) - not rtl8735b, so it
 * is genuinely absent here (not just a link-order issue like the earlier
 * hal_read_systime_us). component/usb/common_new/usb_os.c's own
 * usb_os_delay_us() already uses rtw_usleep_os() as rtl8735b's real
 * microsecond-delay primitive - same fix here.
 */
#ifndef DelayUs
#define DelayUs(us) rtw_usleep_os((int)(us))
#endif

/* rtl8735b D-cache line size - matches the alignment already used for DMA
 * buffers elsewhere in this project's USB code, e.g.
 * component/usb/host_new/uvc/usbh_uvc_stream.c's __attribute__((aligned(64))) */
#ifndef CACHE_LINE_SIZE
#define CACHE_LINE_SIZE 64U
#endif

/* CACHE_LINE_ADDR_MSK/_ALIGNMENT (used by usbh_uvc_stream.c for its DMA frame/
 * URB buffers) don't exist on this SDK generation (no component/soc/8735b/.../
 * ameba_cache.h) - reproduce them from CACHE_LINE_SIZE, matching every other
 * Ameba chip's definition verbatim. */
#ifndef CACHE_LINE_ADDR_MSK
#define CACHE_LINE_ADDR_MSK (~(CACHE_LINE_SIZE - 1U))
#endif
#ifndef CACHE_LINE_ALIGNMENT
#define CACHE_LINE_ALIGNMENT(x) (((u32)(x) + (CACHE_LINE_SIZE - 1U)) & CACHE_LINE_ADDR_MSK)
#endif

/* Exported defines ----------------------------------------------------------*/

#define RTK_LOG_ALWAYS  0
#define RTK_LOG_ERROR   1
#define RTK_LOG_WARN    2
#define RTK_LOG_INFO    3
#define RTK_LOG_DEBUG   4

#define RTK_LOGS(tag, level, fmt, ...)  do { if ((level) <= RTK_LOG_INFO) { printf("[%s] " fmt, (tag), ##__VA_ARGS__); } } while (0)
#define RTK_LOGA(tag, fmt, ...)         printf("[%s][A] " fmt, (tag), ##__VA_ARGS__)
#define RTK_LOGE(tag, fmt, ...)         printf("[%s][E] " fmt, (tag), ##__VA_ARGS__)
#define RTK_LOGW(tag, fmt, ...)         printf("[%s][W] " fmt, (tag), ##__VA_ARGS__)
#define RTK_LOGI(tag, fmt, ...)         printf("[%s][I] " fmt, (tag), ##__VA_ARGS__)
#define RTK_LOGD(tag, fmt, ...)         printf("[%s][D] " fmt, (tag), ##__VA_ARGS__)

/*
 * A handful of files in this ported tree (usbd_hal.c, usbd_pcd_isr.c,
 * usbh_hcd.c, usbh_hcd_isr.c, usbh_cdc_ecm.c, usb_diag.c) call rtos_task_xxx,
 * rtos_critical_xxx, rtos_mem_get_free_heap_size and rtos_time_delay_ms directly
 * (the os_wrapper API) instead of going through usb_os_* like the rest of
 * the stack. usb_os.c/.h already re-implement the usb_os_* subset on top of
 * FreeRTOS (see usb_os.c) - this is that same treatment for the small,
 * fixed set of raw os_wrapper calls that leak through. usb_os_task_t and
 * rtos_task_t are both TaskHandle_t, so passing a usb_os_task_t* (e.g.
 * usbh_hcd_t::main_task) into rtos_task_create() below is type-compatible.
 */

#ifndef RTK_SUCCESS
#define RTK_SUCCESS 0
#endif

#ifndef RTOS_CRITICAL_USB
#define RTOS_CRITICAL_USB 0U
#endif

#ifndef RTOS_SEMA_MAX_COUNT
#define RTOS_SEMA_MAX_COUNT 0xFFFFFFFFUL
#endif

typedef TaskHandle_t rtos_task_t;

__STATIC_INLINE int rtos_task_create(rtos_task_t *task, const char *name, void (*func)(void *), void *param,
									 u32 stack_size, u32 priority)
{
	BaseType_t ret = xTaskCreate((TaskFunction_t)func, name, (configSTACK_DEPTH_TYPE)stack_size, param,
								 (UBaseType_t)priority, task);
	return (ret == pdPASS) ? RTK_SUCCESS : -1;
}

__STATIC_INLINE void rtos_task_delete(rtos_task_t task)
{
	vTaskDelete(task);
}

__STATIC_INLINE void rtos_critical_enter(u32 id)
{
	UNUSED(id);
	taskENTER_CRITICAL();
}

__STATIC_INLINE void rtos_critical_exit(u32 id)
{
	UNUSED(id);
	taskEXIT_CRITICAL();
}

__STATIC_INLINE u32 rtos_mem_get_free_heap_size(void)
{
	return (u32)xPortGetFreeHeapSize();
}

__STATIC_INLINE void rtos_time_delay_ms(u32 ms)
{
	vTaskDelay(pdMS_TO_TICKS(ms));
}

/*
 * usbh_uvc_stream.c is the first file in this ported tree to need a counting
 * (not binary) semaphore and to call rtos_sema_take/rtos_task_delete directly
 * on it - usb_os_sema_create() (usb_os.c) only ever creates binary semaphores.
 * rtos_sema_t and usb_os_sema_t are both SemaphoreHandle_t, so this is a
 * type-compatible drop-in for the handful of os_wrapper calls that leak
 * through here, same treatment as rtos_task_create/rtos_time_delay_ms above.
 */
typedef SemaphoreHandle_t rtos_sema_t;

__STATIC_INLINE int rtos_sema_create(rtos_sema_t *sema, u32 init_count, u32 max_count)
{
	*sema = xSemaphoreCreateCounting((UBaseType_t)max_count, (UBaseType_t)init_count);
	return (*sema != NULL) ? RTK_SUCCESS : -1;
}

__STATIC_INLINE int rtos_sema_take(rtos_sema_t sema, u32 timeout_ms)
{
	TickType_t ticks = (timeout_ms == RTOS_SEMA_MAX_COUNT) ? portMAX_DELAY : pdMS_TO_TICKS(timeout_ms);
	return (xSemaphoreTake(sema, ticks) == pdTRUE) ? RTK_SUCCESS : -1;
}

#endif /* _AMEBA_SOC_SHIM_H */
