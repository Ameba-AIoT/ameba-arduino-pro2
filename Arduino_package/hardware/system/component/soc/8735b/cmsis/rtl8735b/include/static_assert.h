/**************************************************************************//**
 * @file     static_assert.h
 * @brief    Declare macros for compile time checking.
 *
 * @version  V1.00
 * @date     2021-07-26
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2017 Realtek Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************/

#ifndef _STATIC_ASSERT_H_
#define _STATIC_ASSERT_H_

// NOTE disable by default
#ifdef STATIC_CHECK_EN

#ifndef STATIC_ASSERT
#define STATIC_ASSERT(COND,MSG) typedef char STATIC_ASSERT_MSG(MSG, __LINE__, __COUNTER__)[(COND)?1:-1];
#define STATIC_ASSERT_MSG(MSG, LINE, COUNTER) STATIC_ASSERT_MSG_(MSG, LINE, COUNTER)
#define STATIC_ASSERT_MSG_(MSG, LINE, COUNTER) assert_##MSG##_##LINE##_##COUNTER
#endif
#else
#define STATIC_ASSERT(COND,MSG)
#endif

#endif
