/*
 * Copyright (c) 2022 Realtek, LLC.
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

#ifndef AMEBA_BASE_CUTILS_SRC_RTRBTREE_H
#define AMEBA_BASE_CUTILS_SRC_RTRBTREE_H

#ifdef __cplusplus
extern "C" {
#endif

#define RB_RED        0
#define RB_BLACK      1

#define RB_PARENT(r)           ((RBNode *)((r)->rb_parent_color & ~3))
#define RB_COLOR(r)            ((r)->rb_parent_color & 1)
#define RB_IS_RED(r)           (!RB_COLOR(r))
#define RB_IS_BLACK(r)         RB_COLOR(r)
#define RB_SET_BLACK(r)        do { (r)->rb_parent_color |= 1; } while (0)
#define RB_SET_RED(r)          do { (r)->rb_parent_color &= ~1; } while (0)
#define RB_ROOT                (RBNode) { NULL, }
#define RB_EMPTY_ROOT(root)    ((root)->rb_node == NULL)
#define RB_EMPTY_NODE(node)    (RB_PARENT(node) == node)
#define RB_CLEAR_NODE(node)    (RTRBTree_SetParent(node, node))

#define RB_ENTRY(ptr, type, member) ({          \
    const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
    (type *)( (char *)__mptr - offsetof(type,member) );})

typedef struct RBNode {
	unsigned long rb_parent_color;
	struct RBNode *rb_left;
	struct RBNode *rb_right;
} RBNode;

typedef struct {
	RBNode *rb_node;
} RBRoot;

void RTRBTree_SetParent(RBNode *rb, RBNode *p);
void RTRBTree_SetColor(RBNode *rb, int color);

void RTRBTree_InitNode(RBNode *rb);

void RTRBTree_InsertColor(RBRoot *root, RBNode *node);
void RTRBTree_Erase(RBRoot *root, RBNode *node);

typedef void (*RB_Augment_F)(RBNode *node, void *data);
void RTRBTree_AugmentInsert(RBNode *node, RB_Augment_F func, void *data);
RBNode *RTRBTree_AugmentEraseBegin(RBNode *node);
void RTRBTree_AugmentEraseEnd(RBNode *node, RB_Augment_F func, void *data);

RBNode *RTRBTree_First(RBRoot *root);
RBNode *RTRBTree_Last(RBRoot *root);
RBNode *RTRBTree_Next(RBNode *node);
RBNode *RTRBTree_Prev(RBNode *node);

void RTRBTree_ReplaceNode(RBNode *victim, RBNode *new, RBRoot *root);
void RTRBTree_LinkNode(RBNode *node, RBNode *parent, RBNode **rb_link);

#ifdef __cplusplus
}
#endif

#endif /* AMEBA_BASE_CUTILS_SRC_RTRBTREE_H */
