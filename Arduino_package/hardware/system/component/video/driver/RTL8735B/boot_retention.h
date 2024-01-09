#ifndef _BOOT_RETENTION_H_
#define _BOOT_RETENTION_H_

#include <stdint.h>

typedef struct retention_table_items_s{
	uint32_t tag;
	uint32_t data_len;
	uint32_t address;
	uint32_t checksum;
} retention_table_items_t;

typedef struct {
	retention_table_items_t isp_init_data;
	retention_table_items_t reserve_data[7];
} boot_retention_table_t;

extern boot_retention_table_t retention_table;

#endif //_BOOT_RETENTION_H_

