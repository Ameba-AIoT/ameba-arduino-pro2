/**************************************************************************//**
 * @file     arith.h
 * @brief    The long/float variable arithmetic functions definition.
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

#ifndef _ARITH_H_
#define _ARITH_H_

u64 _div_u64(u64 dividend, u64 divisor);
s64 _div_s64(s64 dividend, s64 divisor);
u64 _div_u64_rem(u64 dividend, u64 divisor, u64 *remainder);
s64 _div_s64_rem(s64 dividend, s64 divisor, s64 *remainder);
u64 _mul_u64(u64 mulr, u64 mulp);
s64 _mul_s64(s64 mulr, s64 mulp);
float _div_float(float dividend, float divisor);
double _div_double(double dividend, double divisor);
float _mul_float(float mulr, float mulp);
double _mul_double(double mulr, double mulp);
float _add_float(float a, float b);
double _add_double(double a, double b);
float _sub_float(float a, float b);
double _sub_double(double a, double b);

#endif  // _ARITH_H_
