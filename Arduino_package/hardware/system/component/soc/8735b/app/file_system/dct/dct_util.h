/******************************************************************************
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

#ifndef __RTK_DCT_UTIL_H__
#define __RTK_DCT_UTIL_H__

#include <osdep_service.h>

int32_t	dct_flash_init(void);
int32_t	dct_flash_read(uint32_t address, uint8_t *buffer, uint32_t length);
int32_t	dct_flash_write(uint32_t address, uint8_t *buffer, uint32_t length);
int32_t	dct_flash_erase(uint32_t address, uint32_t length);
void	dct_mutex_init(_mutex *mutex);
void	dct_mutex_free(_mutex *mutex);
int32_t dct_mutex_lock(_mutex *mutex, uint32_t timeout_ms);
void	dct_mutex_unlock(_mutex *mutex);


#endif // __RTK_DCT_UTIL_H__
