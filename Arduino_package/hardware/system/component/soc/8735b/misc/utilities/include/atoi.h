/**************************************************************************//**
 * @file     atoi.h
 * @brief    The ASCII to value functions definition.
 * @version  V1.00
 * @date     2016-09-30
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2023 Realtek Corporation. All rights reserved.
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
 *
 ******************************************************************************/

#ifndef _ATOI_H_
#define _ATOI_H_

#include <stddef.h>

int _atoi(const char *num);
unsigned int _atoui(const char *num);
long _atol(const char *num);
unsigned long _atoul(const char *num);
unsigned long long _atoull(const char *num);

#endif  // _ATOI_H_
