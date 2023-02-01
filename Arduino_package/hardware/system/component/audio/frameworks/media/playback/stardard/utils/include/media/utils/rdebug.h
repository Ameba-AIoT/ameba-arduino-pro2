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

#ifndef AMEBA_FWK_MEDIA_PLAYBACK_UTILS_MEDIA_UTILS_R_DEBUG_H
#define AMEBA_FWK_MEDIA_PLAYBACK_UTILS_MEDIA_UTILS_R_DEBUG_H

#include <stdint.h>
#include <string.h>

#include "log/log.h"

#include "media/utils/rstring.h"

namespace ameba::media
{

inline static const char *ToString(res_t i, const char *def = "??")
{
	switch (i) {
	case OK:
		return "OK";
	case UNKNOWN_ERROR:
		return "UNKNOWN_ERROR";
	case NO_MEMORY:
		return "NO_MEMORY";
	case INVALID_OPERATION:
		return "INVALID_OPERATION";
	case BAD_VALUE:
		return "BAD_VALUE";
	case BAD_TYPE:
		return "BAD_TYPE";
	case NAME_NOT_FOUND:
		return "NAME_NOT_FOUND";
	case NO_INIT:
		return "NO_INIT";
	case ALREADY_EXISTS:
		return "ALREADY_EXISTS";
	case DEAD_OBJECT:
		return "DEAD_OBJECT";
	case FAILED_TRANSACTION:
		return "FAILED_TRANSACTION";
	case BAD_INDEX:
		return "BAD_INDEX";
	case NOT_ENOUGH_DATA:
		return "NOT_ENOUGH_DATA";
	case WOULD_BLOCK:
		return "WOULD_BLOCK";
	default:
		return def;
	}
}

#define LITERAL_TO_STRING_INTERNAL(x)    #x
#define LITERAL_TO_STRING(x) LITERAL_TO_STRING_INTERNAL(x)

#ifdef CHECK
#undef CHECK
#endif
#define CHECK(condition)                                \
    LOG_ALWAYS_FATAL_IF(                                \
            !(condition),                               \
            "%s",                                       \
            __FILE__ ":" LITERAL_TO_STRING(__LINE__)    \
            " CHECK(" #condition ") failed.")

#define MAKE_COMPARATOR(suffix,op)                          \
    template<class A, class B>                              \
    RString Compare_##suffix(const A &a, const B &b) {      \
        RString res;                                        \
        if (!(a op b)) {                                    \
            res.Append(a);                                  \
            res.Append(" vs. ");                            \
            res.Append(b);                                  \
        }                                                   \
        return res;                                         \
    }

MAKE_COMPARATOR(EQ, ==)
MAKE_COMPARATOR(NE, !=)
MAKE_COMPARATOR(LE, <=)
MAKE_COMPARATOR(GE, >=)
MAKE_COMPARATOR(LT, <)
MAKE_COMPARATOR(GT, >)

#ifdef CHECK_OP
#undef CHECK_OP
#endif

#define CHECK_OP(x,y,suffix,op)                                         \
    do {                                                                \
        RString ___res = Compare_##suffix(x, y);                        \
        if (!___res.Empty()) {                                          \
            RString ___full =                                           \
                __FILE__ ":" LITERAL_TO_STRING(__LINE__)                \
                    " CHECK_" #suffix "( " #x "," #y ") failed: ";      \
            ___full.Append(___res);                                     \
                                                                        \
            LOG_ALWAYS_FATAL("%s", ___full.Str());                      \
        }                                                               \
    } while (false)

#ifdef CHECK_EQ
#undef CHECK_EQ
#undef CHECK_NE
#undef CHECK_LE
#undef CHECK_LT
#undef CHECK_GE
#undef CHECK_GT
#endif

#define CHECK_EQ(x,y)   CHECK_OP(x,y,EQ,==)
#define CHECK_NE(x,y)   CHECK_OP(x,y,NE,!=)
#define CHECK_LE(x,y)   CHECK_OP(x,y,LE,<=)
#define CHECK_LT(x,y)   CHECK_OP(x,y,LT,<)
#define CHECK_GE(x,y)   CHECK_OP(x,y,GE,>=)
#define CHECK_GT(x,y)   CHECK_OP(x,y,GT,>)

#define TRESPASS(...) \
        LOG_ALWAYS_FATAL(                                       \
            __FILE__ ":" LITERAL_TO_STRING(__LINE__)            \
                " Should not be here. " __VA_ARGS__);

#ifdef NDEBUG
#define CHECK_DBG CHECK
#define CHECK_EQ_DBG CHECK_EQ
#define CHECK_NE_DBG CHECK_NE
#define CHECK_LE_DBG CHECK_LE
#define CHECK_LT_DBG CHECK_LT
#define CHECK_GE_DBG CHECK_GE
#define CHECK_GT_DBG CHECK_GT
#define TRESPASS_DBG TRESPASS
#else
#define CHECK_DBG(condition)
#define CHECK_EQ_DBG(x,y)
#define CHECK_NE_DBG(x,y)
#define CHECK_LE_DBG(x,y)
#define CHECK_LT_DBG(x,y)
#define CHECK_GE_DBG(x,y)
#define CHECK_GT_DBG(x,y)
#define TRESPASS_DBG(...)
#endif

struct RDebug {
	enum Level {
		kDebugNone,             // no debug
		kDebugLifeCycle,        // lifecycle events: creation/deletion
		kDebugState,            // commands and events
		kDebugConfig,           // configuration
		kDebugInternalState,    // internal state changes
		kDebugAll,              // all
		kDebugMax = kDebugAll,

	};
};

}  // namespace ameba::media

#endif  // AMEBA_FWK_MEDIA_PLAYBACK_UTILS_MEDIA_UTILS_R_DEBUG_H