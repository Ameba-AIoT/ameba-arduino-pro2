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

/**
 * @addtogroup OSAL
 * @{
 *
 * @brief Declares the structures and interfaces for the Operating System Abstraction Layer (OSAL) module.
 *
 * The OSAL module provide a unified interfaces that adapter to different OS. The interfaces include the
 * memory management, thread, mutex, semaphore, time.
 *
 * @since 1.0
 * @version 1.0
 */

/**
 * @file misc.h
 *
 * @brief Declares commonly used misc macros.
 *
 * @since 1.0
 * @version 1.0
 */

#ifndef AMEBA_BASE_OSAL_OSAL_CXX_INTERFACES_OSAL_CXX_MISC_H
#define AMEBA_BASE_OSAL_OSAL_CXX_INTERFACES_OSAL_CXX_MISC_H

#ifndef NELEM
#define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))
#endif

#endif // AMEBA_BASE_OSAL_OSAL_CXX_INTERFACES_OSAL_CXX_MISC_H
/** @} */