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

#ifndef AMEBA_BASE_CUTILS_INCLUDE_CUTILS_RT_INTERFACES_H
#define AMEBA_BASE_CUTILS_INCLUDE_CUTILS_RT_INTERFACES_H

#include <stddef.h>

#include "osal_c/osal_types.h"

#ifdef __cplusplus
extern "C" {
#endif


#define RT_SELF(object, T, IfaceType)  \
    ((T *)(((uint8_t *)(object)) - offsetof(T, IfaceType##_base)))

#define RT_IMPLEMENTS(IfaceType) IfaceType IfaceType##_base
#define RT_EXTENDS(ClassType)    ClassType ClassType##_base

#define RT_BASE(object, BaseType) (object)->BaseType##_base

#define RT_INTERFACE(object) ((object)->iface)

#define RT_INTERFACE_MAP(ClassType, IfaceType)  \
    static const IfaceType##Interface ClassType##_##IfaceType##Interface

#define RT_DECLARE_INTERFACE_MAP(ClassType, IfaceType)  \
    RT_INTERFACE_MAP(ClassType, IfaceType);

#define RT_BEGIN_INTERFACE_MAP(ClassType, IfaceType)  \
    RT_INTERFACE_MAP(ClassType, IfaceType) = {

#define RT_END_INTERFACE_MAP };


#define RT_SETUP_INTERFACE(object, ClassType, IfaceType)  \
    (object)->IfaceType##_base.iface = &ClassType##_##IfaceType##Interface


#ifdef __cplusplus
}
#endif

#endif // AMEBA_BASE_CUTILS_INCLUDE_CUTILS_RT_INTERFACES_H