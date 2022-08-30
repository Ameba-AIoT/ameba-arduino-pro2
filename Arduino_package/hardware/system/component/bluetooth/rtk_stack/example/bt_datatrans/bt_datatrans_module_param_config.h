/**
*********************************************************************************************************
*               Copyright(c) 2014, Realtek Semiconductor Corporation. All rights reserved.
**********************************************************************************************************
* @file     module_param_config.h
* @brief
* @details
* @author   parker_xue
* @date     2017-4-19
* @version  v0.1
*********************************************************************************************************
*/

#ifndef __BT_DATATRANS_MUDULE_PARAM_CONFIG_H_
#define __BT_DATATRANS_MUDULE_PARAM_CONFIG_H_

//#include "rtl876x.h"
#include "bt_datatrans_app_queue.h"
#include "bt_datatrans_at_cmd.h"
#include <basic_types.h>

#define DEFAULT_DEVICE_NAME_LEN     7
#define DEFAULT_DEVICE_NAME         "Realtek"

#define RECEIVE_BUF_MAX_LENGTH      0x2000
#define DEVICE_NAME_MAX_LENGTH      15

#define DEVICE_NAME_SIZE            16
#define PINCODE_SIZE                4
#define SERVICE_CHAR_UUID_SIZE      20
#define CONFIG_PARAM_SIZE           8
#define BAUD_SIZE                   4

#define DEVICE_NAME_OFFSET          0
#define PINCODE_OFFSET              16
#define SERVICE_CHAR_UUID_OFFSET    20
#define CONFIG_PARAM_OFFSET         40
#define BAUD_OFFSET                 48

#define TX_PACKET_MAX_LENGTH        260
#define TX_PACKET_COUNT             80
#define MAX_NUMBER_OF_TX_MESSAGE    TX_PACKET_COUNT

#define DATATRANS_BLE_KEY_LEN                 0x1c
#define DATATRANS_LE_ENCRYPT_DATA_LENGTH      0x10

//#define APP_PRIVACY_EN 0

/*
Beacon Mode:
    | Byte 0    | Byte 1  | Byte 2-3 | Byte 4  | Byte 5       | Byte 6-36 |Byte 37-42  | Byte 43 |

     signature    mode      adv_int    len_con    flow control   adv_data   direct add   reserved
*/
//typedef struct _DATATRANS_BEACON_EFUSE_CONFIG
//{
//    uint8_t datatrans_signature;

//    union
//    {
//        uint8_t app_mode_select;
//        struct
//        {
//            uint8_t adv_mode : 1;      //default is 1: auto adv
//            uint8_t baudrate : 3;      //baudrate setting
//            uint8_t adv_type : 3;      //advertising type
//            uint8_t dt_beacon_sel: 1;  //select datatrans or beacon mode
//        };
//    };

//    uint16_t adv_interval;

//    union
//    {
//        uint8_t len_config;           //datatrans length config or adv data length
//        struct
//        {
//            uint8_t device_name_len : 4;
//            uint8_t srv_uuid_len :    1;
//            uint8_t gap_role :        1;
//            uint8_t pair_mode:        2;  //only used in at cmd mode
//        };
//    };

//    union
//    {
//        uint8_t flow_ctrl;
//        struct
//        {
//            uint8_t uart_flow_disable : 1;   //1 -- disable, 0 -- enable
//            uint8_t bt_flow_disable   : 1;   //1 -- disable, 0 -- enable
//            uint8_t at_cmd_or_8761att : 1;   //1 -- at cmd,  0 -- 8761att mode
//            uint8_t auto_security_req : 1;   //1 -- send seqReq after connect
//            uint8_t not_run_datatrans : 1;   //1 -- normal app, 0 -- rom datatrans
//            uint8_t without_flash     : 1;   //1 -- no flash,   0 -- with flash
//            uint8_t reserved          : 2;
//        };
//    };

//    union
//    {
//        struct
//        {
//            uint8_t  beacon_adv_data[31];
//            uint8_t  beacon_adv_direct_add[6];//if advtype = direct adv
//            uint8_t  beacon_rsvd;
//        };//beacon mode
//        struct
//        {
//            uint8_t service_uuid[16];
//            uint8_t write_char_uuid[2];
//            uint8_t notify_char_uuid[2];
//            uint8_t flow_char_uuid[2];
//            uint8_t device_name[15];
//            uint8_t datatrans_rsvd;
//        };//datatrans mode
//    };
//} __attribute__((packed)) DATATRANS_BEACON_EFUSE_CONFIG;

#define MANUAL_ADV  0
#define AUTO_ADV    1

#define ROLE_PERIPHERAL 0
#define ROLE_CENTRAL    1
#define ROLE_BEACON     2

#define TXP_0DBM            0

//ATCMD MDOE or DATATRANS MODE
#define CMD_MODE       0
#define DATATRANS_MODE 1


typedef struct
{
    uint8_t length;
    uint8_t device_name[15];
} DEVICENAME_INFO;


typedef struct
{
    uint8_t length;
    uint8_t uuid[19];//actually max use 16 bytes
} UUID_INFO;

typedef struct
{
    uint8_t res;
    uint8_t adv_type;
    uint8_t bda[6];
} BDADDR_INFO;

typedef struct
{
    uint8_t length;
    uint8_t adv[31];
} ADVDATA;

typedef struct
{
    uint16_t write_uuid;
    uint16_t notify_uuid;
    uint16_t flow_uuid;
    uint16_t res;
} PROFILE_CHAR_UUID;

typedef struct
{
    uint16_t interval_min;
    uint16_t interval_max;
    uint16_t slave_lantency;
    uint16_t supervision_timeout;
} CONNECT_PARA;

typedef struct
{
    uint32_t role      : 2;   //0:peripheral mode; 1:central mode; 2:beacon mode
    uint32_t adv_mode  : 1;
    uint32_t sleep_mode: 1;
    uint32_t baudrateidx  : 4;

    uint32_t uart_flowctrl: 1;
    uint32_t bt_flowctrl  : 1;
    uint32_t advtype      : 1;
    uint32_t code_mode    : 2;
    uint32_t res1         : 3;

    uint32_t tx_power     : 8;
    uint32_t res2         : 8;
} MODE_INFO;

typedef struct
{

    uint16_t pair_mode    : 6;
    uint16_t paired_flag  : 1;
    uint16_t auto_security_req    : 1;
    uint16_t authen_iocap : 4;
    uint16_t res  : 4;
    union
    {
        uint16_t value;
        struct
        {
            uint8_t mitm_flag;
            uint8_t sc_flag;
        } flag;
    } authenflag;
} PAIR_INFO;

#define INFO_DEVICE_NAME_OFFSET   0
#define INFO_UUID_OFFSET          16
#define INFO_LOCAL_BDA_OFFSET     36
#define INFO_ADV_DATA_OFFSET      44
#define INFO_RSP_DATA_OFFSET      76
#define INFO_CHAR_UUID_OFFSET     108
#define INFO_CON_PARA_OFFSET      116
#define INFO_ADV_INTERVAL_OFFSET  124
#define INFO_PINCODE_OFFSET       128
#define INFO_DEVICE_MODE_OFFSET   132
#define INFO_PAIR_INFO_OFFSET     136
typedef struct
{
    DEVICENAME_INFO devicename_info;    //16
    UUID_INFO uuid_info;//20
    BDADDR_INFO local_bda;        //8
    ADVDATA advdata;              //32
    ADVDATA scanrspdata;          //32

    PROFILE_CHAR_UUID char_uuid;  //8

    CONNECT_PARA connection_para; //8
    uint16_t adv_interval;        //2
    uint16_t wake_delay;                //2
    uint32_t pincode;             //4

    MODE_INFO device_mode;        //2
    //uint16_t res2;                //2
    PAIR_INFO pair_info;
} transfer_info;


typedef struct
{
    uint8_t select_io;
    uint8_t bt_buf_free;
    uint8_t adv_param_update;
    uint8_t tx_power_upd;
    uint32_t patch_version;
    uint32_t app_version;
    uint32_t baudrate;

    uint8_t create_connection;
    uint8_t connect_by_add;
    uint8_t connect_dev_num;
    uint8_t uart_idle;

    uint8_t connect_dev_add[6];
    uint8_t stop_scan_then_adv;
    uint8_t at_dfu_mode;
    uint8_t select_mode;
    //BDADDR_INFO local_bda;        //8
} config_info;

typedef struct
{
    bool allowedDataTransEnterDlps;
    bool is_in_DLPS;
    bool is_cmd_enter_dlps;
    bool redelay_flg;
} dlps_info;

extern transfer_info dataTransInfo;
extern config_info transferConfigInfo;
//extern dlps_info  DLPSInfo;

//typedef struct
//{
//    uint8_t  len;
//    uint8_t  device_name[15];
//} device_name_struct;

//typedef struct
//{
//    uint32_t  pincode;
//} pincode_struct;

//typedef struct
//{
//    uint8_t  service_uuid[16];
//    uint16_t  service_uuid_len;
//    uint16_t  write_uuid;
//    uint16_t  notify_uuid;
//    uint16_t  flow_uuid;
//} uuid_struct;

//typedef struct
//{
//    uint8_t  pair;
//    uint8_t  uart_flow;
//    uint16_t adv_interval;
//    uint8_t  adv_mode;
//    uint8_t  tx_power;
//    uint8_t  gap_role;
//    uint8_t  bt_flow;
//} config_struct;

//typedef struct
//{
//    uint32_t  baudrate;
//} baud_struct;

//typedef struct
//{
//    uint16_t  rom_version;
//    uint16_t  patch_version;
//} ver_struct;

//typedef enum
//{
//    PERIPHERAL_ROLE     = 0xA0,
//    CENTRAL_ROLE        = 0xA1
//} GapRoleType;

typedef enum
{
    UART_HCI        = 0x00,
    I2C_HCI         = 0x01,
    SPI_HCI         = 0x02,
    UART_AT         = 0x03
} IO_MODE;

typedef enum
{
    NO_PASS_WORD      = 0x00,
    JUST_WORK         = 0x01,
    PASS_WORD         = 0x02,
    PASS_WORD_BOND    = 0x03
} PAIR_MODE;


//typedef struct
//{
//    bool  BeaconMode;
//    uint8_t ADV_type;
//    uint8_t ADV_len;
//    uint8_t ScanRsp_len;
//    uint8_t Selected_IO;
//    bool  support_8761_header;
//    bool ADV_param_update;
//    bool create_connection;
//    uint8_t connect_dev_num;
//    uint8_t connect_dev_add[6];
//    bool connect_by_add;
//    uint16_t auth_flags;
//    uint16_t seq_req_flags;
//    uint8_t  bt_buf_free;
//    uint8_t  uart_idle;
//    bool     tx_power_upd;
//} DataTransGlobalFlag;

//typedef struct
//{
//    bool       start_patch;
//    uint8_t    index;
//    uint32_t   patch_address;
//    bool       last;
//} DataTrans_Patch;

typedef struct
{
    uint8_t    buf[RECEIVE_BUF_MAX_LENGTH];
    uint16_t   WriteOffset;
    uint16_t   ReadOffset;
    uint16_t   datalen;
    uint8_t    atcmd[AT_CMD_MAX_LENGTH];
    uint16_t   atcmdlength;
    uint8_t    overflow;
} ReceiveBufStruct;

typedef struct _TXData
{
    struct    _TXData *pNext;
//    uint8_t   tx_buffer[TX_PACKET_MAX_LENGTH];
    uint8_t   *tx_buffer;
    uint16_t  length;
    uint16_t  stack_buf_offset;
    bool      is_stack_buf;

} TTxData, *PTxData;

typedef struct
{
    TTxData   Bt2UART[TX_PACKET_COUNT];
} TBT_UART_BUF, *PBT_UART_BUF;


//typedef struct datatrans_auth_info
//{
//    uint8_t bd_addr[6];
//    uint8_t remote_addr_type;
//    uint8_t key_type;
//    uint8_t link_key[DATATRANS_BLE_KEY_LEN];
//} T_DATATRANS_AUTH_INFO;

//typedef struct
//{
//    uint8_t bd_addr[6];
//    uint8_t remote_addr_type;
//    uint8_t ltk_exist;
//    uint8_t irk_exist;
//    uint8_t ltk_key[DATATRANS_BLE_KEY_LEN];
//    uint8_t irk_key[DATATRANS_BLE_KEY_LEN];
//} T_DATATRANS_KEY_INFO;

typedef struct bdaddr_info
{
    uint8_t bdaddr[6];
    uint8_t remote_addr_type;
} T_DATATRANS_REMOTE_BDADDR_INFO;

//typedef struct ble_all_key_info
//{
//    uint8_t bd_addr[6];
//    uint8_t ltk[DATATRANS_BLE_KEY_LEN];
//    uint8_t irk[DATATRANS_BLE_KEY_LEN];
//} T_DATATRANS_ALL_KEY_INFO;

//typedef struct auth_info_header
//{
//    uint8_t bd_addr[6];
//    uint8_t remote_addr_type;
//    uint8_t key_type;
//} T_DATATRANS_AUTH_INFO_HEADER;

//typedef struct t_authen_key_req_ind
//{
//    uint8_t   bd_addr[6];
//    uint8_t   remote_addr_type;
//    uint8_t   key_type;
//} T_DATATRANS_KEY_REQ_IND;


extern uint16_t                 MTU_SIZE;
extern uint8_t                  BT_Credits;
extern uint8_t                  CON_ID;
//extern device_name_struct       device_name;
//extern pincode_struct           pincode;
//extern uuid_struct              uuid;
//extern config_struct            config;
//extern baud_struct              baudrate;
//extern ver_struct               datatrans_ver;
//extern DataTransGlobalFlag      DataTranFlag;
extern ReceiveBufStruct         IO_Receive;
//extern DATATRANS_BEACON_EFUSE_CONFIG  datatrans_efuse;
//extern DataTrans_Patch          DataTrans_PatchFlag;

//extern T_DATATRANS_KEY_INFO g_ble_key_info;

extern void *TimersUartConfigChange;
extern void *TimersReset;
extern void *TimersConnTimeOut;
//extern void *TimersEnterLowPower;
extern void *TimersConnParamUpdate;
//extern void *TimersSwitchToHCI;

extern QUEUE_T  txUartDataQueueFree;
extern void *TxMessageQueueHandle;
extern void *DataTrans_Semaphore;
#if 0
#include "gap_ext_adv.h"

/** @brief  Idle advertising set */
#define APP_IDLE_ADV_SET 0xFF
/** @brief  Maximum advertising set */
#define APP_MAX_ADV_SET 4

#define LE_CODED_PHY_2M            3
#define LE_CODED_PHY_S8            2
#define LE_CODED_PHY_S2            1
#define LE_CODED_PHY_1M            0
typedef struct
{
    uint8_t             adv_handle;
    T_GAP_EXT_ADV_STATE ext_adv_state;
} T_APP_EXT_ADV_STATE;

extern T_APP_EXT_ADV_STATE ext_adv_state[APP_MAX_ADV_SET]; /**< Extended advertising state */
extern uint8_t adv_set_num;
extern uint8_t adv_handle;
#endif

void readconfig(void);
void datatrans_setdefault(void);
bool DataTrans_ConfigReadFromEfuse(void);
void DataTrans_SettingConfig(void);
void moduleParam_InitAdvAndScanRspData(void);
void moduleParam_SetSystemReset(void);
void DataTransApplicationInit(void);
void DataTransApplicationDeinit(void);
//void le_init_ext_adv_params_ext_conn(void);
//void le_init_ext_adv_enable_params(uint8_t adv_handle);
#endif /*__MUDULE_PARAM_CONFIG_H_*/
