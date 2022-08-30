/**
*********************************************************************************************************
*               Copyright(c) 2015, Realtek Semiconductor Corporation. All rights reserved.
**********************************************************************************************************
* @file     app_queue.h
* @brief
* @details
* @author   jane
* @date     2015-03-29
* @version  v0.2
*********************************************************************************************************
*/

#ifndef  __BT_DATATRANS_APP_QUEUE_H
#define  __BT_DATATRANS_APP_QUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

struct QueueElement                                     /* dummy definition      */
{
    struct QueueElement *Next;                          /* point to next element */
    uint8_t  data[2];                                               /* user data             */
};
typedef struct QueueElement ELEMENT_T;

typedef ELEMENT_T   *ELEMENT_P;

typedef struct
{
    ELEMENT_P First;                                 /* first element         */
    ELEMENT_P Last;                                  /* last element          */
    uint16_t      ElementCount;                      /* element count         */
} QUEUE_T, *QUEUE_P;


void  datatrans_app_queue_in(QUEUE_P QueuePtr, void *QueueElementPtr);
void *datatrans_app_queue_out(QUEUE_P QueuePtr);


#ifdef __cplusplus
}
#endif

#endif
