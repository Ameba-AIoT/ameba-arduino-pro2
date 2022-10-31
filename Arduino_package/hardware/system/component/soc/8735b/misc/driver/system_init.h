#ifndef SYSTEM_INIT_H
#define SYSTEM_INIT_H

#ifndef system_init
#define system_init(fn) \
static void* init_##fn __attribute__((used, section(".init_array")))  = (void*)fn;
#endif

#ifndef system_delay_init
#define system_delay_init(fn) \
static void delay_##fn##_task(void *dummy){ (void)dummy; fn(); vTaskDelete(NULL);}\
void delay_##fn(void){ xTaskCreate(delay_##fn##_task, "d_"#fn, 512, NULL, 1, NULL); } \
static void* delay_init_##fn __attribute__((used, section(".init_array")))  = (void*)delay_##fn;
#endif

#endif