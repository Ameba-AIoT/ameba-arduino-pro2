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
 * Copyright(c) 2007 - 2016 Realtek Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
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
