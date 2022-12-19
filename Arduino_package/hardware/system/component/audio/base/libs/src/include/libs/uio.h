/*
 * Copyright (C) 2021 The Ameba Project
 *
 * Licensed under the PanKore License, Version 1.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License from PanKore
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef AMEBA_BASE_LIBS_SRC_INCLUDE_LIBS_VASPRINTF_H
#define AMEBA_BASE_LIBS_SRC_INCLUDE_LIBS_VASPRINTF_H

#ifdef __cplusplus
extern "C" {
#endif

//
// Implementation of sys/uio.h for non-linux.
//
#include <stddef.h>

struct iovec {
	void *iov_base;
	size_t iov_len;
};

extern int readv(int fd, struct iovec *vecs, int count);
extern int writev(int fd, const struct iovec *vecs, int count);

#ifdef __cplusplus
}
#endif

#endif // AMEBA_BASE_LIBS_SRC_INCLUDE_LIBS_VASPRINTF_H
