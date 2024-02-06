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

#ifdef __cplusplus
extern "C" {
#endif

extern void voe_t2ff_prealloc(void);

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
        vPortYield();
    }
    vTaskDelete(NULL);
}

int main(void)
{
    ameba_init();
    initVariant();
    voe_t2ff_prealloc();

    if (xTaskCreate(main_task, ((const char *)"main task"), MAIN_THREAD_STACK_SIZE, NULL, 1, NULL) != pdPASS) {
        printf("\r\n[ERROR] %s xTaskCreate(main task) failed\n", __FUNCTION__);
    }
    vTaskStartScheduler();

    while (1)
        ;

    return 0;
}

#ifdef __cplusplus
}
#endif
