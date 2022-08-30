#ifndef _BT_DISTANCE_DETECTOR_HANDLE_MESSAGE_H_
#define _BT_DISTANCE_DETECTOR_HANDLE_MESSAGE_H_
#include "stdint.h"
#include <stdbool.h>

#define BT_DISTANCE_DETECTOR_MAX_NODE_COUNT             20 //max num of devices
#define BT_DISTANCE_DETECTOR_RSSI_SAMPLE_COUNT          10 //max rssi value samples of each device

#define DISTANCE_DETECTION_ALPHA                        0.6 //0.6~0.7
#define DISTANCE_DETECTION_ENVIRONMENTAL_FACTOR         2   //(2~4) local experiment as n=2

#define BT_DISTANCE_DETECTOR_FLASH    1 //if save iBeacon info to flash

typedef struct
{
    uint8_t dev_addr[6];
    int8_t dev_rssi;      //!< actual rssi value
    int8_t txpower;
    uint8_t flag;         //!< 0: send msg from app main task, 1: send msg from 60s-timer
}device_msg_t;

typedef struct
{
    uint32_t used;         //!< if the entry has been used

    int8_t txpower;        //!< RSSI measured at a distance of one meter
    uint8_t addr[6];       //!< device mac address
    uint8_t padding;

    int8_t previous_rssi;  //!< last measured rssi (not weighted value)
    uint8_t rssi_count;    //!< elements num of filter_rssi[]
    uint16_t beacon_num;   //!< numbers of beacon in a period of time

    int8_t filter_rssi[BT_DISTANCE_DETECTOR_RSSI_SAMPLE_COUNT]; //!< weighted rssi value
}Beacon_data_t;

typedef struct
{
    uint16_t node_num; //!< the number of storage entrys
    uint16_t padding;  //!< 2 bytes for padding alignment
    Beacon_data_t *sBeacon;
}scan_tag_msg_t;

extern scan_tag_msg_t scan_tag_msg;

extern void bt_distance_detector_flash_init(void);
extern void bt_distance_detector_flash_restore(void);
extern void bt_distance_detector_scan_result_init(uint16_t node_num);
extern void bt_distance_detector_scan_result_deinit(void);
extern void bt_distance_detector_scan_result_clear(void);
extern int bt_distance_detector_scan_result_check(uint8_t *dev_addr, int8_t rssi, int8_t txpower);
extern double bt_distance_detector_calculate_result(uint8_t node_index);
extern bool bt_distance_detector_check_msg(device_msg_t dev_info);
extern void bt_distance_detector_beacon_num_check(void);

#endif
