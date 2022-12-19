/*
*******************************************************************************
* Copyright(c) 2022, Realtek Semiconductor Corporation. All rights reserved.
*******************************************************************************
*/

#ifndef __RTK_STACK_GATT_H__
#define __RTK_STACK_GATT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <dlist.h>
#include <rtk_stack_config.h>

typedef struct{
	struct list_head pending_list;
	void * pending_list_mutex;
	struct list_head sending_list;
	void *sending_list_mutex;
}rtk_bt_gatt_ind_and_ntf_queue_t;

typedef struct {
	struct list_head service_list;
	void *service_mutex;
	uint8_t srv_registering;
	rtk_bt_gatt_ind_and_ntf_queue_t notify_queue[GAP_MAX_LINKS];
	rtk_bt_gatt_ind_and_ntf_queue_t indicate_queue[GAP_MAX_LINKS];	
	uint16_t credits;
}rtk_bt_gatts_app_priv_t;

typedef enum {
    SRV_UNUSED = 0,
    SRV_ALLOC_FOR_INCLUDE,
    SRV_WAIT_FOR_REG,
    SRV_REGISTERING,
	SRV_REGISTERED,
} rtk_bt_gatts_srv_reg_status_t;

typedef struct{
	struct list_head list;
	uint16_t conn_handle;
	uint8_t app_id;
	uint16_t seq;
	uint16_t index;
	uint16_t len;
	uint8_t *data;
} rtk_bt_gatts_req_t;



#ifdef __cplusplus
}
#endif

#endif  /* __RTK_STACK_GATT_H__ */