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

#ifndef AMEBA_BASE_MEDIA_AUDIO_AUDIO_UTILS_INCLUDE_FORMAT_H
#define AMEBA_BASE_MEDIA_AUDIO_AUDIO_UTILS_INCLUDE_FORMAT_H

#include <stdint.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

size_t audio_bytes_per_sample(uint32_t format);
void memcpy_by_audio_format(void *dst, uint32_t dst_format,
							const void *src, uint32_t src_format, size_t count);

__END_DECLS

#endif  // AMEBA_BASE_MEDIA_AUDIO_AUDIO_UTILS_INCLUDE_FORMAT_H
