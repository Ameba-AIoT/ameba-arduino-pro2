/*
  main.cpp - Main loop for Arduino sketches
  Copyright (c) 2005-2013 Arduino Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#define ARDUINO_MAIN
#include "Arduino.h"
#include "cmsis_os.h"
#include "diag.h"
#if (Arduino_LOGS_HARD_MUTE)
#include "serial_api.h"
#include "stdio_port_func.h"
#endif
#include <rtw_debug.h>
extern u8 OtherDebugPortEnable;

#if defined(Arduino_WATCHDOG)
#include "wdt_api.h"

static volatile uint32_t LoopLastTick = 0;    // to signal that main loop is alive for the watchdog
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern void voe_t2ff_prealloc(void);

#if (Arduino_LOGS_HARD_MUTE)
extern hal_uart_adapter_t log_uart;

void log_uart_putc_empty(void *adapter)
{
    return;
}

int log_uart_getc_empty(void *adapter)
{
    return TRUE;
}

#endif

// Weak empty variant initialization function.
// May be redefined by variant files.
void initVariant() __attribute__((weak));
void initVariant()
{}

void main_task(void *)
{
    delay(1);
    setup();

    for (;;) {
        loop();
        if (serialEventRun) {
            serialEventRun();
        }

#if defined(Arduino_WATCHDOG)
        LoopLastTick = xTaskGetTickCount();
#endif
        vPortYield();
    }
    vTaskDelete(NULL);
}

#if defined(Arduino_WATCHDOG)
static void watchdog_task(void *arg)
{
    // Start WDT
    watchdog_init_arduino(WDT_TIMEOUT_MS, 0);
    watchdog_start();
    amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] WDT started\n");

    TickType_t lastTick = xTaskGetTickCount();    // the number of ticks since the scheduler started
    for (;;) {
        vTaskDelay(pdMS_TO_TICKS(WDT_PERIOD_MS));

        TickType_t now = xTaskGetTickCount();
        if (now == lastTick) {    // don't feed
            continue;
        }
        lastTick = now;

        uint32_t dt_ms = (now - LoopLastTick) * portTICK_PERIOD_MS;    // ms elapsed since the last watchdog heartbeat (converted to ms)

        if (dt_ms <= LOOP_TIMEOUT_MS) {
            watchdog_refresh();
            // amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] WDT refreshed\n");
        }
    }
}
#endif

int main(void)
{
    ameba_init();

#if (Arduino_SHOW_WIFI_LOGS)
    OtherDebugPortEnable = 0;
#else
    OtherDebugPortEnable = 1;
#endif

#if (Arduino_LOGS_HARD_MUTE)    // Off all logs (including printf)
    stdio_port_deinit_s();
    stdio_port_deinit_ns();
    stdio_port_init_s((void *)&log_uart, (stdio_putc_t)&log_uart_putc_empty, (stdio_getc_t)&log_uart_getc_empty);
    stdio_port_init_ns((void *)&log_uart, (stdio_putc_t)&log_uart_putc_empty, (stdio_getc_t)&log_uart_getc_empty);
    hal_uart_deinit(&log_uart);
#endif

    initVariant();
    voe_t2ff_prealloc();

    if (xTaskCreate(main_task, ((const char *)"main task"), MAIN_THREAD_STACK_SIZE, NULL, 1, NULL) != pdPASS) {
        printf("\r\n[ERROR] %s xTaskCreate(main task) failed\n", __FUNCTION__);
    }

#if defined(Arduino_WATCHDOG)
    // start watchdog task (higher than main so it runs reliably)
    if (xTaskCreate(watchdog_task, ((const char *)"watchdog task"), 1024, NULL, 2, NULL) != pdPASS) {
        printf("\r\n[ERROR] %s xTaskCreate(watchdog_task) failed\n", __FUNCTION__);
    }
#endif

    set_initial_tick_count();
    vTaskStartScheduler();

    while (1)
        ;

    return 0;
}

#ifdef __cplusplus
}
#endif
