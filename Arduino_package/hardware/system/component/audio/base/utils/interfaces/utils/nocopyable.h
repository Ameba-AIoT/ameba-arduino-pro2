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

#ifndef AMEBA_BASE_UTILS_NOCOPYABLE_H
#define AMEBA_BASE_UTILS_NOCOPYABLE_H

namespace ameba
{

#define DISALLOW_COPY_AND_MOVE(className) \
    DISALLOW_COPY(className); \
    DISALLOW_MOVE(className)

#define DISALLOW_COPY(className) \
    className(const className&) = delete; \
    className& operator= (const className&) = delete

#define DISALLOW_MOVE(className) \
    className(className&&) = delete; \
    className& operator= (className&&) = delete

} // namespace ameba

#endif // AMEBA_BASE_UTILS_NOCOPYABLE_H