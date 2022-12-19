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

#ifndef AMEBA_BASE_LOG_COMMON_H
#define AMEBA_BASE_LOG_COMMON_H

#include <stdint.h>


#define MAX_LOG_LEN 1024  /* maximum length of a log, include '\0' */
#define MAX_TAG_LEN 32  /* log tag size, include '\0' */
#define RET_SUCCESS 0
#define RET_FAIL (-1)
#define IS_ONE(number, n) ((number>>n)&0x01)
#define ONE_KB (1UL<<10)
#define ONE_MB (1UL<<20)
#define ONE_GB (1UL<<30)
#define ONE_TB (1ULL<<40)

#define DOMAIN_NUMBER_BASE (16)

/*
 * header of log message from libhilog to hilogd
 */
typedef struct __attribute__((__packed__)) AmebalogMsg {
	uint16_t len;
	uint16_t version : 3;
	uint16_t type : 4;  /* APP,CORE,INIT,SEC etc */
	uint16_t level : 3;
	uint16_t tag_len : 6; /* include '\0' */
	uint32_t tv_sec;
	uint32_t tv_nsec;
	uint32_t pid;
	uint32_t tid;
	uint32_t domain;
	char tag[]; /* shall be end with '\0' */
} AmebalogMsg;

typedef struct AmebalogShowFormatBuffer {
	uint16_t length;
	uint16_t level;
	uint16_t type;
	uint16_t tag_len;
	uint32_t pid;
	uint32_t tid;
	uint32_t domain;
	uint32_t tv_sec;
	uint32_t tv_nsec;
	char *data;
} AmebalogShowFormatBuffer;

#define CONTENT_LEN(pMsg) (pMsg->len - sizeof(AmebalogMsg) - pMsg->tag_len) /* include '\0' */
#define CONTENT_PTR(pMsg) (pMsg->tag + pMsg->tag_len)

#endif // AMEBA_BASE_LOG_COMMON_H
