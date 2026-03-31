/*
 * Copyright (c) 2019 xieqing. https://github.com/xieqing
 * May be freely redistributed, but copyright notice must be retained.
 */

#ifndef _AVL_BF_HEADER
#define _AVL_BF_HEADER

#ifdef __cplusplus
extern "C" {
#endif

#define AVL_DUP 1
#define AVL_MIN 1

/*
 * node->bf = height(node->right) - height(node->left)
 * balance factors can be kept up-to-date by knowning the previous balance factors and the change in height
 * it is not necesary to know the absolute height
 */

enum avlbf {
	LEFTHEAVY = -1,
	BALANCED = 0,
	RIGHTHEAVY = 1
};

enum avltraversal {
	PREORDER,
	INORDER,
	POSTORDER
};

typedef struct avlnode {
	struct avlnode *left;
	struct avlnode *right;
	struct avlnode *parent;
	char bf;
	void *data;
} avlnode;

typedef struct {
	int (*compare)(const void *, const void *);
	void (*destroy)(void *);

	avlnode root;
	avlnode nil;

	#ifdef AVL_MIN
	avlnode *min;
	#endif
	int count;
} avltree;

#define AVL_ROOT(avlt) (&(avlt)->root)
#define AVL_NIL(avlt) (&(avlt)->nil)
#define AVL_FIRST(avlt) ((avlt)->root.left)
#define AVL_MINIMAL(avlt) ((avlt)->min)

#define AVL_ISEMPTY(avlt) ((avlt)->root.left == &(avlt)->nil && (avlt)->root.right == &(avlt)->nil)
#define AVL_APPLY(avlt, func, cookie, order) avl_apply((avlt), (avlt)->root.left, (func), (cookie), (order))

avltree *avl_create(int (*compare_func)(const void *, const void *), void (*destroy_func)(void *));
void avl_destroy(avltree *avlt);

avlnode *avl_find(avltree *avlt, void *data);
avlnode *avl_successor(avltree *avlt, avlnode *node);
avlnode *avl_successor_end(avltree *avlt, avlnode *node);

avlnode *avl_insert(avltree *avlt, void *data);
void *avl_delete(avltree *avlt, avlnode *node, int keep);

#ifdef __cplusplus
}
#endif

#endif /* _AVL_BF_HEADER */
