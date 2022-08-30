/**
*********************************************************************************************************
*               Copyright(c) 2015, Realtek Semiconductor Corporation. All rights reserved.
**********************************************************************************************************
* @file     hci_cmd_event.h
* @brief
* @details
* @author   parker_xue
* @date     2017-04-21
* @version  v0.2
*********************************************************************************************************
*/
//#include "rtl876x.h"

#ifndef  _BT_DATATRANS_AT_HCI_CMD_PROCESS_H_
#define  _BT_DATATRANS_AT_HCI_CMD_PROCESS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <gap.h>

extern void Device_Name_Write(uint8_t *payload, uint16_t payloadlen);
extern void Pair_Mode_Set(uint8_t pairmode);
extern void ADV_Interval_Set(uint16_t newadvi);
extern bool ADV_Enable_Disable(uint8_t adven);
extern void Role_Set(uint8_t newrole);
extern void Connect_Device_Num(uint8_t connindex);
extern void Enable_New_ADV_SCANRSP_Data(void);
extern T_APP_RESULT HandleBTReceiveData(uint8_t conn_id, uint16_t wLength, uint8_t *pValue);
//extern void Dle_Set(uint8_t *p_buf);

//extern void Set_Tx_Power(uint8_t pwr_index);
//extern void Set_CODED(uint8_t code_index);

#ifdef __cplusplus
}
#endif

#endif

