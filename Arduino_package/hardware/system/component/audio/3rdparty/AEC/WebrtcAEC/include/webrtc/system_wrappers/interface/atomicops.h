// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file under third_party_mods/chromium or at:
// http://src.chromium.org/svn/trunk/src/LICENSE

#ifndef WEBRTC_SYSTEM_WRAPPERS_INTERFACE_ATOMICOPS_H_
#define WEBRTC_SYSTEM_WRAPPERS_INTERFACE_ATOMICOPS_H_

#if defined(_MSC_VER)
#include <stddef.h>  /* intptr_t */
#endif

#include "typedefs.h"

namespace webrtc {

// Extracted from Chromium's src/base/atomicops.h.

//
// The routines exported by this module are subtle.  If you use them, even if
// you get the code right, it will depend on careful reasoning about atomicity
// and memory ordering; it will be less readable, and harder to maintain.  If
// you plan to use these routines, you should have a good reason, such as solid
// evidence that performance would otherwise suffer, or there being no
// alternative.  You should assume only properties explicitly guaranteed by the
// specifications in this file.  You are almost certainly _not_ writing code
// just for the x86; if you assume x86 semantics, x86 hardware bugs and
// implementations on other archtectures will cause your code to break.  If you
// do not know what you are doing, avoid these routines, and use a Mutex.
//
// It is incorrect to make direct assignments to/from an atomic variable.
// You should use one of the Load or Store routines.  The NoBarrier
// versions are provided when no barriers are needed:
//   NoBarrier_Store()
//   NoBarrier_Load()
// Although there are currently no compiler enforcement, you are encouraged
// to use these.
//

namespace subtle {

typedef int32_t Atomic32;
#ifdef WEBRTC_ARCH_64_BITS
typedef intptr_t Atomic64;
#endif  // WEBRTC_ARCH_64_BITS

// Use AtomicWord for a machine-sized pointer.  It will use the Atomic32 or
// Atomic64 routines below, depending on your architecture.
typedef intptr_t AtomicWord;

// Atomically execute:
//      result = *ptr;
//      if (*ptr == old_value)
//        *ptr = new_value;
//      return result;
//
// I.e., replace "*ptr" with "new_value" if "*ptr" used to be "old_value".
// Always return the old value of "*ptr"
//
// This routine implies no memory barriers.
Atomic32 NoBarrier_CompareAndSwap(volatile Atomic32* ptr,
                                  Atomic32 old_value,
                                  Atomic32 new_value);

// Atomically store new_value into *ptr, returning the previous value held in
// *ptr.  This routine implies no memory barriers.
Atomic32 NoBarrier_AtomicExchange(volatile Atomic32* ptr, Atomic32 new_value);

// Atomically increment *ptr by "increment".  Returns the new value of
// *ptr with the increment applied.  This routine implies no memory barriers.
Atomic32 NoBarrier_AtomicIncrement(volatile Atomic32* ptr, Atomic32 increment);

Atomic32 Barrier_AtomicIncrement(volatile Atomic32* ptr,
                                 Atomic32 increment);

// These following lower-level operations are typically useful only to people
// implementing higher-level synchronization operations like spinlocks,
// mutexes, and condition-variables.  They combine CompareAndSwap(), a load, or
// a store with appropriate memory-ordering instructions.  "Acquire" operations
// ensure that no later memory access can be reordered ahead of the operation.
// "Release" operations ensure that no previous memory access can be reordered
// after the operation.  "Barrier" operations have both "Acquire" and "Release"
// semantics.   A MemoryBarrier() has "Barrier" semantics, but does no memory
// access.
Atomic32 Acquire_CompareAndSwap(volatile Atomic32* ptr,
                                Atomic32 old_value,
                                Atomic32 new_value);
Atomic32 Release_CompareAndSwap(volatile Atomic32* ptr,
                                Atomic32 old_value,
                                Atomic32 new_value);

void MemoryBarrier();
void NoBarrier_Store(volatile Atomic32* ptr, Atomic32 value);
void Acquire_Store(volatile Atomic32* ptr, Atomic32 value);
void Release_Store(volatile Atomic32* ptr, Atomic32 value);

Atomic32 NoBarrier_Load(volatile const Atomic32* ptr);
Atomic32 Acquire_Load(volatile const Atomic32* ptr);
Atomic32 Release_Load(volatile const Atomic32* ptr);

// 64-bit atomic operations (only available on 64-bit processors).
#ifdef WEBRTC_ARCH_64_BITS
Atomic64 NoBarrier_CompareAndSwap(volatile Atomic64* ptr,
                                  Atomic64 old_value,
                                  Atomic64 new_value);
Atomic64 NoBarrier_AtomicExchange(volatile Atomic64* ptr, Atomic64 new_value);
Atomic64 NoBarrier_AtomicIncrement(volatile Atomic64* ptr, Atomic64 increment);
Atomic64 Barrier_AtomicIncrement(volatile Atomic64* ptr, Atomic64 increment);

Atomic64 Acquire_CompareAndSwap(volatile Atomic64* ptr,
                                Atomic64 old_value,
                                Atomic64 new_value);
Atomic64 Release_CompareAndSwap(volatile Atomic64* ptr,
                                Atomic64 old_value,
                                Atomic64 new_value);
void NoBarrier_Store(volatile Atomic64* ptr, Atomic64 value);
void Acquire_Store(volatile Atomic64* ptr, Atomic64 value);
void Release_Store(volatile Atomic64* ptr, Atomic64 value);
Atomic64 NoBarrier_Load(volatile const Atomic64* ptr);
Atomic64 Acquire_Load(volatile const Atomic64* ptr);
Atomic64 Release_Load(volatile const Atomic64* ptr);
#endif  // WEBRTC_ARCH_64_BITS

}  // namespace webrtc::subtle
}  // namespace webrtc

// Include our platform specific implementation.
#if defined(WEBRTC_WIN) && defined(_MSC_VER) && defined(WEBRTC_ARCH_X86_FAMILY)
#include "webrtc/system_wrappers/interface/atomicops_internals_x86_msvc.h"
#elif defined(WEBRTC_MAC)
#include "webrtc/system_wrappers/interface/atomicops_internals_mac.h"
#elif defined(__GNUC__) && defined(__ARMEL__)
#include "webrtc/system_wrappers/interface/atomicops_internals_gcc.h"
#elif defined(__GNUC__) && defined(WEBRTC_ARCH_X86_FAMILY)
#include "webrtc/system_wrappers/interface/atomicops_internals_x86_gcc.h"
#elif defined(__GNUC__) && defined(__MIPSEL__)
#include "webrtc/system_wrappers/interface/atomicops_internals_mips_gcc.h"
#else
#error "Atomic operations are not supported on your platform"
#endif

// On some platforms we need additional declarations to make
// AtomicWord compatible with our other Atomic* types.
#if defined(WEBRTC_MAC) || defined(__OpenBSD__)
#include "webrtc/system_wrappers/interface/atomicops_internals_atomicword_compat.h"
#endif

#endif  // WEBRTC_SYSTEM_WRAPPERS_INTERFACE_ATOMICOPS_H_
