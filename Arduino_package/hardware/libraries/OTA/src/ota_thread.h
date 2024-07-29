#ifndef OTA_THREAD_H
#define OTA_THREAD_H

#include <Arduino.h>
#include <httpd/httpd.h>

// Function declarations
void start_OTA_threads();
void thread1_task(const void *argument);
void thread2_task(const void *argument);


#endif    // OTA_THREAD_H
