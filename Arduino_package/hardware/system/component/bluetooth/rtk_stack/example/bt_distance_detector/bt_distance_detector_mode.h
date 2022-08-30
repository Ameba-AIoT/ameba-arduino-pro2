#ifndef _BT_DISTANCE_DETECTOR_MODE_H_
#define _BT_DISTANCE_DETECTOR_MODE_H_
#include <stdint.h>

typedef enum
{
    NORMAL_MODE,
    HIGH_DETECTION_MODE,
    LOW_POWER_MODE,
} DEVICE_MODE_F;

typedef struct
{
    uint32_t previous;
    uint32_t current;
}beacon_num_t;

typedef struct
{
    uint8_t high_timer_flag;      //high detection mode timer flag
    uint8_t low_power_timer_flag; //low power mode timer flag
    uint8_t beacon_count;         // beacons count within 500ms
    uint8_t time_step;            //count every 500ms -> 2s
    beacon_num_t two_second;      // beacon num within 2s
    DEVICE_MODE_F device_mode_flag;
}device_mode_t;

typedef struct
{
    uint16_t long_time_step;      //count 20 times for 500ms
    beacon_num_t ten_second;
}node_info_t;

extern void *low_power_mode_timer;
extern void *high_datection_mode_timer;
extern void *beacon_num_check_timer;

extern device_mode_t device_mode;

extern void bt_distance_detector_timer_init(void);
extern void bt_distance_detector_timer_deinit(void);

#endif
