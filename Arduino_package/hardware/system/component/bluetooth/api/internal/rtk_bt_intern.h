/*
 *******************************************************************************
 * Copyright(c) 2021, Realtek Semiconductor Corporation. All rights reserved.
 *******************************************************************************
 */

#ifndef __RTK_BT_INTERN_H__
#define __RTK_BT_INTERN_H__

#include <rtk_bt_defs.h>
#include <rtk_bt_msg_intern.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RTK_BT_TEST_RETURN_FAIL(condition)      \
    do {                                        \
        if (condition)                          \
            return RTK_BT_FAIL;                 \
    } while (0)

#define RTK_BT_TEST_RETURN_NULL(condition)      \
    do {                                        \
        if (condition)                          \
            return NULL;                        \
    } while (0)

#define RTK_BT_TEST_RETURN(condition)           \
    do {                                        \
        if (condition)                          \
            return;                             \
    } while (0)

#define BT_TIMEOUT_NONE        0
#define BT_TIMEOUT_FORVER      0xffffffffUL
/* USE RTK_BT_PID_NUM as TASK EXIT FLAG  */
#define RTK_BT_TASK_EXIT_FLAG RTK_BT_PID_NUM

/**
 *******************************************************************************
 * Bluetooth paramters memory operations
 *******************************************************************************
 */
/**
 * @brief     Bluetooth sync api callback preset.
 *
 * @param[in] sync: Sync paramter, here is semephore
 * 
 * @return    - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 */
rtk_bt_err_t rtk_bt_sync_cb_preset(void** sync);

/**
 * @brief     Bluetooth sync api callback function.
 *
 * @param[in] sync: Sync paramter, here is semephore
 *
 */
void rtk_bt_sync_cb(void* sync);

/**
 * @brief     Bluetooth sync api wait callback.
 *
 * @param[in] sync: Sync paramter, here is semephore
 * @param[in] need_wait: Whether need wait
 * 
 * @return    - RTK_BT_OK  : Succeed
 *            - RTK_BT_FAIL: Failed
 *
 */
rtk_bt_err_t rtk_bt_sync_cb_wait_reset(void** sync, uint8_t need_wait);

/**
 *******************************************************************************
 * Bluetooth paramters memory operations
 *******************************************************************************
 */
/**
 * @brief     BT paramters deep copy function.
 *
 * @param[in] msg: BT message
 * @param[in] param: Pointer to BT paramters
 *
 */
typedef void* (*rtk_deep_copy_t)(rtk_bt_msg_t* msg, void* param);

/**
 * @brief     BT paramters deep free function.
 *
 * @param[in] msg: BT message
 *
 */
typedef void (*rtk_deep_free_t)(rtk_bt_msg_t* msg);

/**
 * @brief     Get Bt paramters deep copy function.
 *
 * @param[in] pid: Profile id
 *
 * @return    - NULL: Failed
 *            - Other: Succeed
 */
rtk_deep_copy_t rtk_bt_param_get_copy(uint8_t pid);

/**
 * @brief     Get Bt paramters deep free function.
 *
 * @param[in] pid: Profile id
 *
 * @return    - NULL: Failed
 *            - Other: Succeed
 */
rtk_deep_free_t rtk_bt_param_get_free(uint8_t pid);

/**
 *******************************************************************************
 * Bluetooth list structure definition (ONLY for BT API use for now)
 *******************************************************************************
 */
struct _rtk_node {
	struct _rtk_node *next;
};
typedef struct _rtk_node rtk_node_t;

struct _rtk_list {
	rtk_node_t *head;
	rtk_node_t *tail;
};
typedef struct _rtk_list rtk_list_t;

/**
 * @brief Initialize a list
 *
 * @param list A pointer on the list to initialize
 */
static inline void rtk_list_init(rtk_list_t *list)
{
	list->head = NULL;
	list->tail = NULL;
}

/**
 * @brief Initialize a node
 *
 * @param node A pointer on the node to initialize
 */
static inline void rtk_list_node_init(rtk_node_t *node)
{
	node->next = NULL;
}

/**
 * @brief Test if the given list is empty
 *
 * @param list A pointer on the list to test
 *
 * @return 1 if it's empty, 0 otherwise
 */
static inline uint8_t rtk_list_is_empty(rtk_list_t *list)
{
    return (NULL == list->head);
}

/**
 * @brief Append a node to the given list
 *
 * This and other rtk_list__*() functions are not thread safe.
 *
 * @param list A pointer on the list to affect
 * @param node A pointer on the node to append
 */
static inline void rtk_list_append(rtk_list_t *list, rtk_node_t *node)
{
    if (NULL == list->head)
    {
        list->head = node;
        list->tail = node;
    }
    else
    {
        list->tail->next = node;
        list->tail = node;
    }
}

/**
 * @brief Fetch and remove the first node of the given list
 *
 * This and other rtk_list_*() functions are not thread safe.
 *
 * @param list A pointer on the list to affect
 *
 * @return A pointer to the first node of the list (or NULL if empty)
 */
static inline rtk_node_t *rtk_list_get(rtk_list_t *list)
{
    rtk_node_t* node = NULL;

    if (list->head)
    {
        node = list->head;
        if (list->head == list->tail)
        {
            list->head = NULL;
            list->tail = NULL;
        }
        else
        {
            list->head = list->head->next;
        }
    }

    return node;
}

/**
 * @brief Peek the first node from the list
 *
 * @param list A point on the list to peek the first node from
 *
 * @return A pointer on the first node of the list (or NULL if none)
 */
static inline rtk_node_t *rtk_list_peek_head(rtk_list_t *list)
{
	return list->head;
}

/**
 * @brief Peek the next node from current node
 *
 * @param node A pointer on the node where to peek the next node
 *
 * @return a pointer on the next node (or NULL if none)
 */
static inline rtk_node_t *rtk_list_peek_next(rtk_node_t *node)
{
    return node != NULL ? node->next : NULL;
}

/**
 * @brief Provide the primitive to iterate on a list
 * Note: the loop is unsafe and thus __sn should not be removed
 *
 * User _MUST_ add the loop statement curly braces enclosing its own code:
 *
 *     RTK_LIST_FOR_EACH_NODE(l, n) {
 *         <user code>
 *     }
 *
 * This and other RTK_LIST_*() macros are not thread safe.
 *
 * @param __sl A pointer on a sys_sflist_t to iterate on
 * @param __sn A rtk_node_t pointer to peek each node of the list
 */
#define RTK_LIST_FOR_EACH_NODE(__sl, __sn)              \
    for (__sn = rtk_list_peek_head(__sl); __sn != NULL; \
         __sn = rtk_list_peek_next(__sn))

/**
 * @brief Find and remove a node from a list
 *
 * This and other rtk_flist_*() functions are not thread safe.
 *
 * @param list A pointer on the list to affect
 * @param op A function pointer for operation
 *
 * @return A pointer on the found node
 */
typedef uint8_t (*rtk_list_op)(rtk_node_t *node, void* data);
static inline rtk_node_t *rtk_list_find_and_remove(rtk_list_t *list,
                                                   rtk_list_op op, void* data)
{
    rtk_node_t* node = NULL;
    rtk_node_t* prev = NULL;

    RTK_LIST_FOR_EACH_NODE(list, node)
    {
        if (op(node, data))
        {
            if (node == list->head)
                list->head = node->next;
            if (node == list->tail)
                list->tail = prev;
            if (prev)
                prev->next = node->next;
            return node;
        }

        prev = node;
        node = node->next;
    }

    return NULL;
}

static inline rtk_node_t *rtk_list_cmp_and_get(rtk_list_t *list,
                                               rtk_list_op op, void* data)
{
    rtk_node_t* node = NULL;

    if (list->head && op(list->head, data))
    {
        node = list->head;
        if (list->head == list->tail)
        {
            list->head = NULL;
            list->tail = NULL;
        }
        else
        {
            list->head = list->head->next;
        }
    }

    return node;
}

#ifndef offsetof
#define offsetof(type, member) ((long)&((type *)0)->member)
#endif

/**
 * @brief Get a pointer to a container structure from an element
 *
 * Example:
 *
 *	struct foo {
 *		int bar;
 *	};
 *
 *	struct foo my_foo;
 *	int *ptr = &my_foo.bar;
 *
 *	struct foo *container = CONTAINER_OF(ptr, struct foo, bar);
 *
 * Above, @p container points at @p my_foo.
 *
 * @param ptr pointer to a structure element
 * @param type name of the type that @p ptr is an element of
 * @param field the name of the field within the struct @p ptr points to
 * @return a pointer to the structure that contains @p ptr
 */
#ifndef CONTAINER_OF
#define CONTAINER_OF(ptr, type, field) \
    ((type *)(((char *)(ptr)) - offsetof(type, field)))
#endif

/**
 *******************************************************************************
 * Bluetooth Debug
 *******************************************************************************
 */
/* k_panic(); */
#define RTK_BT_ASSERT(test)                        \
    do                                             \
    {                                              \
        if (!(test))                               \
        {                                          \
                                                   \
        }                                          \
    } while (false)

#ifdef __cplusplus
}
#endif

#endif /* __RTK_BT_INTERN_H__ */