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

#ifndef AMEBA_BASE_CUTILS_INCLUDE_CUTILS_RT_DEBUG_H
#define AMEBA_BASE_CUTILS_INCLUDE_CUTILS_RT_DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

#define RT_LITERAL_TO_STRING_INTERNAL(x) #x
#define RT_LITERAL_TO_STRING(x) RT_LITERAL_TO_STRING_INTERNAL(x)

#define RT_CHECK(condition)                                             \
    LOG_ALWAYS_FATAL_IF(                                                \
            !(condition),                                               \
            "%s",                                                       \
            __FILE__ ":" RT_LITERAL_TO_STRING(__LINE__)                 \
            " CHECK(" #condition ") failed.")

#define RT_CHECK_OP(ClassType,x,y,suffix,op)                           \
    do {                                                                \
        bool ret = 1;                                                   \
        if (!((ClassType) x op (ClassType) y)) {                        \
            ret = 0;                                                    \
        }                                                               \
        if (!ret) {                                                     \
            LOG_ALWAYS_FATAL("%s:%s RT_CHECK_%s(%s, %s) failed.",       \
                    RT_LITERAL_TO_STRING(__FILE__),                     \
                    RT_LITERAL_TO_STRING(__LINE__),                     \
                    #suffix, #x, #y);                                   \
        }                                                               \
    } while (false)

#define RT_CHECK_EQ(ClassType,x,y)   RT_CHECK_OP(ClassType,x,y,EQ,==)
#define RT_CHECK_NE(ClassType,x,y)   RT_CHECK_OP(ClassType,x,y,NE,!=)
#define RT_CHECK_LE(ClassType,x,y)   RT_CHECK_OP(ClassType,x,y,LE,<=)
#define RT_CHECK_LT(ClassType,x,y)   RT_CHECK_OP(ClassType,x,y,LT,<)
#define RT_CHECK_GE(ClassType,x,y)   RT_CHECK_OP(ClassType,x,y,GE,>=)
#define RT_CHECK_GT(ClassType,x,y)   RT_CHECK_OP(ClassType,x,y,GT,>)

#define RT_TRESPASS(...)                                                \
    LOG_ALWAYS_FATAL(                                                   \
            __FILE__ ":" RT_LITERAL_TO_STRING(__LINE__)                 \
            " Should not be here. " __VA_ARGS__);


#if defined(RT_DEBUG)
#define RT_ASSERT(x) RT_CHECK(x)
#else
#define RT_ASSERT(x) ((void)0)
#endif

#define RT_TRACE_HANDLE_CREATE(handle)   RTLOGV("+++ %s(%p)", __func__, handle)
#define RT_TRACE_HANDLE_DESTROY(handle)  RTLOGV("--- %s(%p)", __func__, handle)

#ifdef __cplusplus
}
#endif

#endif // AMEBA_BASE_CUTILS_INCLUDE_CUTILS_RT_DEBUG_H
