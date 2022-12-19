#ifndef AMEBA_BASE_OSAL_OSAL_C_ADAPTER_POSIX_OSAL_POSIX_TYPES_H
#define AMEBA_BASE_OSAL_OSAL_C_ADAPTER_POSIX_OSAL_POSIX_TYPES_H

#include <stdint.h>

#include "FreeRTOS.h"
#include "semphr.h"

namespace ameba
{

typedef struct {
	SemaphoreHandle_t handle;
} freertos_mutex_t;

typedef struct {
	SemaphoreHandle_t cond_wait_sem;
	uint32_t waiting_threads;
} freertos_cond_t;

typedef struct {
	StaticSemaphore_t semaphore;
	int32_t value;  // semaphore count.
} freertos_sem_t;

} // namespace ameba

#endif // AMEBA_BASE_OSAL_OSAL_C_ADAPTER_POSIX_OSAL_POSIX_TYPES_H
