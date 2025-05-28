/******************************************************************************\
|* Copyright (c) 2017-2024 by Vivante Corporation.  All Rights Reserved.      *|
|*                                                                            *|
|* The material in this file is confidential and contains trade secrets of    *|
|* of Vivante Corporation.  This is proprietary information owned by Vivante  *|
|* Corporation.  No part of this work may be disclosed, reproduced, copied,   *|
|* transmitted, or used in any way for any purpose, without the express       *|
|* written permission of Vivante Corporation.                                 *|
|*                                                                            *|
\******************************************************************************/


#ifndef _NBG_LK_LIST_H
#define _NBG_LK_LIST_H

#include <vip_lite_common.h>

/*
 * This is a simple doubly linked list implementation.
 */
typedef struct _nbglk_list_head {
	struct _nbglk_list_head *next;
	struct _nbglk_list_head *prev;
} nbglk_list_head_t;

#define NBGLK_LIST_HEAD_INIT(name) { &(name), &(name) }
#define NBGLK_LIST_HEAD(name) \
    nbglk_list_head_t name = NBGLK_LIST_HEAD_INIT(name)

void NBGLK_INIT_LIST_HEAD(nbglk_list_head_t *list);
void nbglk_list_add(nbglk_list_head_t *new, nbglk_list_head_t *head);
void nbglk_list_add_tail(nbglk_list_head_t *new, nbglk_list_head_t *head);
void nbglk_list_del(nbglk_list_head_t *entry);
vip_uint32_t nbglk_list_empty(nbglk_list_head_t *head);
vip_bool_e nbglk_list_is_last(nbglk_list_head_t *list, nbglk_list_head_t *head);
void nbglk_list_replace(nbglk_list_head_t *old, nbglk_list_head_t *new);
vip_bool_e nbglk_list_is_first(nbglk_list_head_t *list, nbglk_list_head_t *head);
vip_bool_e nbglk_list_is_init(nbglk_list_head_t *head);

#define NBGLK_LIST_ENTRY(type, pos, member) \
    (type *)(pos)

#define NBGLK_LIST_FIRST_ENTRY(type, head, member) \
    NBGLK_LIST_ENTRY(type, (head)->next, member)

#define NBGLK_LIST_NEXT_ENTRY(type, pos, member) \
    NBGLK_LIST_ENTRY(type, ((pos)->member).next, member)

#define NBGLK_LIST_FOR_EACH_ENTRY(type, pos, head, member) \
    for (pos = NBGLK_LIST_FIRST_ENTRY(type, head, member); \
        &(pos->member) != (head); \
        pos = NBGLK_LIST_NEXT_ENTRY(type, pos, member))

#define NBGLK_LIST_FOR_EACH_ENTRY_SAFE(type, pos, n, head, member) \
    for (pos = NBGLK_LIST_FIRST_ENTRY(type, head, member), \
        n = NBGLK_LIST_NEXT_ENTRY(type, pos, member); \
            &(pos->member) != (head); \
            pos = n, n = NBGLK_LIST_NEXT_ENTRY(type, n, member))

#endif
