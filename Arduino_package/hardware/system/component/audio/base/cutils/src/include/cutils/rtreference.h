/*
 * Copyright (c) 2021 Realtek, LLC.
 * All rights reserved.
 *
 * Licensed under the Realtek License, Version 1.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License from Realtek
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef AMEBA_BASE_CUTILS_INCLUDE_CUTILS_RT_REFERENCE_H
#define AMEBA_BASE_CUTILS_INCLUDE_CUTILS_RT_REFERENCE_H

#include "log/log.h"

#include "osal_c/osal_errnos.h"
#include "cutils/rtinterfaces.h"
#include "libs/rtdebug.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CUTILS_MEM_DEBUG
#define RREF_LOGD(x, ...) RTLOGD("[%s]" x, __func__, ##__VA_ARGS__)
#else
#define RREF_LOGD(x, ...)
#endif

typedef struct RTReferenceInterface RTReferenceInterface;
typedef struct {
	const RTReferenceInterface *iface;
} RTReference;

struct RTReferenceInterface {
	rt_status_t (*AddRef)(RTReference *self);
	rt_status_t (*Release)(RTReference *self);
};


/**
 * Convenient macro to call the AddRef and Release method
 * of objects that implement the RTReference interface
 */
#define RTReference_AddRef(object) RT_INTERFACE(object)->AddRef(object)
#define RTReference_Release(object) RT_INTERFACE(object)->Release(object)

/**
 * Macro to safely reference and release a an object.
 */
#define RT_REFERENCE_OBJECT(object)             \
    do {                                        \
        if (object) {                           \
            RTReference *refp =                 \
                &RT_BASE(object, RTReference);  \
            RTReference_AddRef(refp);           \
        }                                       \
    } while(0)

#define RT_RELEASE_OBJECT(object)               \
    do {                                        \
        if (object) {                           \
            RTReference *refp =                 \
                &RT_BASE(object, RTReference);  \
            RTReference_Release(refp);          \
            object = NULL;                      \
        }                                       \
    } while(0)

/**
 * Convenient macro to implement a object reference interface
 */
#define RT_IMPLEMENT_REFERENCE_INTERFACE(ClassType, count)             \
    static rt_status_t ClassType##_AddRef(RTReference *refp)           \
    {                                                                  \
        ClassType* self = RT_SELF(refp, ClassType, RTReference);       \
        self->count++;                                                 \
        RREF_LOGD("add %s %p, %d\n", #ClassType, self, self->count);   \
        return OSAL_OK;                                                \
    }                                                                  \
    static rt_status_t ClassType##_Release(RTReference *refp)          \
    {                                                                  \
        ClassType* self = RT_SELF(refp, ClassType, RTReference);       \
        RREF_LOGD("dec %s %p, %d\n", #ClassType, self, self->count-1); \
        RT_CHECK(self->count > 0);                                     \
        if (--self->count == 0) {                                      \
            ClassType##_Destroy(self);                                 \
        }                                                              \
        return OSAL_OK;                                                \
    }                                                                  \
    RT_BEGIN_INTERFACE_MAP(ClassType, RTReference)                     \
        ClassType##_AddRef,                                            \
        ClassType##_Release                                            \
    };

#ifdef __cplusplus
}
#endif

#endif // AMEBA_BASE_CUTILS_INCLUDE_CUTILS_RT_REFERENCE_H
