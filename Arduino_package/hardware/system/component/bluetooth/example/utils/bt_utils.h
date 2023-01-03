/*
 *******************************************************************************
 * Copyright(c) 2022, Realtek Semiconductor Corporation. All rights reserved.
 *******************************************************************************
 */

#ifndef __ATCMD_BT_UTILS_H__
#define __ATCMD_BT_UTILS_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef HI_WORD
#define HI_WORD(x)      ((uint8_t)((x & 0xFF00) >> 8))
#endif

#ifndef LO_WORD
#define LO_WORD(x)      ((uint8_t)(x))
#endif

#ifndef UUID128_STR
#define UUID128_STR "%08x-%04x-%04x-%04x-%04x%08x"
#endif

#ifndef UUID128_VAL
#define UUID128_VAL(uuid128) \
    *(uint32_t*)(uuid128+12), *(uint16_t*)(uuid128+10), \
    *(uint16_t*)(uuid128+8), *(uint16_t*)(uuid128+6), \
    *(uint16_t*)(uuid128+4), *(uint32_t*)uuid128
#endif

typedef int (*cmd_func_t)(int argc, char *argv[]);

#define APP_PROMOTE(...)                                                                \
    do {                                                                                \
        printf("\r\n");                                                                 \
        printf("############################################################\r\n");     \
        printf(__VA_ARGS__);                                                            \
        printf("############################################################\r\n");     \
        printf("\r\n");                                                                 \
    } while (0)

typedef struct {
    char *cmd_name;
    cmd_func_t cmd_func;
    uint16_t argc_min;
    uint16_t argc_max;
} cmd_table_t;

typedef struct cmd_help_tbl {
    char *name;
    char *discriptor;
    struct cmd_help_tbl *sub_tbl;
} cmd_help_table_t;

// int bt_hex2num(char c);

// int bt_hex2byte(const char *hex);

// int bt_hexstr2bin(const char *hex, uint8_t *buf, size_t len);

void atcmd_bt_common(int argc, char *argv[], const cmd_table_t *cmd_table, char *tag);

void ble_addr_to_str(void *paddr, char *str, uint32_t len);

// int bt_hexstr2bin_bigendian(const char *hex, uint8_t *buf, size_t len);

int hexnum_str_to_int(char *str);

bool hexdata_str_to_bd_addr(char *str, uint8_t *addr_buf, uint8_t buf_len);

bool hexnum_str_to_array(char *str, uint8_t *byte_arr, uint8_t arr_len);

bool hexdata_str_to_array(char *str, uint8_t *byte_arr, uint8_t arr_len);

#ifdef __cplusplus
}
#endif

#endif /* __ATCMD_BT_UTILS_H__ */