/**
*********************************************************************************************************
*               Copyright(c) 2015, Realtek Semiconductor Corporation. All rights reserved.
**********************************************************************************************************
* @file     at_cmd.h
* @brief
* @details
* @author   jane
* @date     2015-03-29
* @version  v0.2
*********************************************************************************************************
*/
//#include "rtl876x.h"

#ifndef  _BT_DATATRANS_AT_CMD_H_
#define  _BT_DATATRANS_AT_CMD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "bt_datatrans_app_flags.h"
#include <basic_types.h>


#define AT_CMD_MAX_LENGTH 76
#define AT_CMD_MIN_LENGTH 4
#define AT_CMD_MAX_NUMBER 20

extern const char AtCmdResponseCONNTIMEOUT[];

#define AT_CMD_HEADER_LENGTH    2
#define AT_CMD_AT_LENGTH        4

#define AT_CMD_RESET_LENGTH     10
#define AT_CMD_ROLE_LENGTH      9
#define AT_CMD_VERSION_LENGTH   12
#define AT_CMD_BAUD_LENGTH      9
#define AT_CMD_NAME_LENGTH      9
#define AT_CMD_DEFAULT_LENGTH   12

#define AT_CMD_INQ_LENGTH       8
#define AT_CMD_SINQ_LENGTH      9
#define AT_CMD_CONN_LENGTH      10
#define AT_CMD_DISC_LENGTH      9 /*AT+DISC=con_id*/
#define AT_CMD_PAIR_LENGTH      9

#define AT_CMD_ADVMOD_LENGTH    11
#define AT_CMD_ADVEN_LENGTH     10
#define AT_CMD_SCANRLT_LENGTH   12

typedef void (*AtCMDCallback_t)(void);
typedef struct _CMD_TABLE_
{
    char    *CMD;
    uint8_t CMD_Length;
    bool    ContainPara;
    uint8_t NextCMD;
    AtCMDCallback_t CMD_CB;
} CMD_TABLE;

void Setsendbuffer(uint16_t bufferlen);
void DataTrans_HandleATCMD(void);

void AtCmdSendResponse(const char *p_resp, uint16_t len);

void AtCmdParse(void);
void AtCmdSendResponseOK(void);
void AtCmdSendResponseInqEnd(void);
void AtCmdSendResponseInqEnd(void);
void AtCmdSendResponsePinDis(void);

void AtCmdHandleReset(void);
void AtCmdHandleBaud(void);
void AtCmdHandleName(void);

#if CENTRAL_MODE
void AtCmdHandleInq(void);
void AtCmdHandleSInq(void);
void AtCmdHandleConn(void);
#endif

void AtCmdHandleRole(void);
void AtCmdHandlePair(void);

#ifdef __cplusplus
}
#endif

#endif

