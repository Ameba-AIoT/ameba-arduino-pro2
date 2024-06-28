/******************************************************************************
 *
 * Copyright(c) 2007 - 2024 Realtek Corporation. All rights reserved.
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
#ifndef _RTL871X_BYTEORDER_H_
#define _RTL871X_BYTEORDER_H_

#include <drv_conf.h>


#  include <byteorder/little_endian.h>


u16 _htons(u16 x);
u16 _ntohs(u16 x);
u32 _htonl(u32 x);
u32 _ntohl(u32 x);

#endif /* _RTL871X_BYTEORDER_H_ */

