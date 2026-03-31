#include "FreeRTOS.h"
#include "task.h"
#include "diag.h"
#include "hal.h"
#include "log_service.h"
#include <platform_opts_bt.h>
#include "snand_api.h"
#include "log_service.h"
#include "ftl_nand_api.h"
#include "ftl_nor_api.h"
#include "ftl_common_api.h"

void hexDump(void *addr, int len)
{
	int i;
	unsigned char buff[17];
	unsigned char *pc = (unsigned char *)addr;
	if (len == 0) {
		printf("  ZERO LENGTH\n");
		return;
	}
	if (len < 0) {
		printf("  NEGATIVE LENGTH: %i\n", len);
		return;
	}
	// Process every byte in the data.
	for (i = 0; i < len; i++) {
		// Multiple of 16 means new line (with line offset).
		if ((i % 16) == 0) {
			// Just don't print ASCII for the zeroth line.
			if (i != 0) {
				printf("  %s\n", buff);
			}

			// Output the offset.
			printf("  %04x ", i);
		}
		// Now the hex code for the specific character.
		printf(" %02x", pc[i]);
		// And store a printable ASCII character for later.
		if ((pc[i] < 0x20) || (pc[i] > 0x7e)) {
			buff[i % 16] = '.';
		} else {
			buff[i % 16] = pc[i];
		}
		buff[(i % 16) + 1] = '\0';
	}

	// Pad out last line if not exactly 16 characters.
	while ((i % 16) != 0) {
		printf("   ");
		i++;
	}
	// And print the final ASCII bit.
	printf("  %s\n", buff);
}

static inline unsigned int str_to_value(const unsigned char *str)
{
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
		return strtol((char const *)str, NULL, 16);
	} else {
		return atoi((char const *)str);
	}
}

void FAFTW(void *arg)
{
	int argc;
	volatile int error_no = 0;
	char *argv[MAX_ARGC] = {0};
	int i = 0;
	int index = 0;
	int block, page, value, size, offset, sector = 0;
	unsigned char *ptr = NULL;
	int address = 0;
	int type = 0;
	int page_size = 0;
	int block_size = 0;
	int block_cnt = 0;
	int ret = 0;

	argc = parse_param(arg, argv);
	ftl_common_info(&type, &page_size, &block_size, &block_cnt);
	printf("type %d page_size %d block_size %d block_cnt %d\r\n", type, page_size, block_size, block_cnt);
	argc = parse_param(arg, argv);
	if (type == FTL_NAND_FLASH) {
		if (argc != 6) {
			printf("Nand -> AFTW=block,page,content,size,offset\r\n");
			return;
		}
		block = str_to_value((unsigned char const *)argv[1]);
		page = str_to_value((unsigned char const *)argv[2]);
		value = str_to_value((unsigned char const *)argv[3]);
		size = str_to_value((unsigned char const *)argv[4]);
		offset = str_to_value((unsigned char const *)argv[5]);
		printf("NAND write block %d page %d content %d size %d offset %d\r\n", block, page, value, size, offset);
		ptr = malloc(size);
		if (ptr == NULL) {
			printf("Malloc failed\r\n");
			return;
		}
		address = block * block_size + page * page_size;
		printf("Address %x\r\n", address);
		memset(ptr, value, size);
		ret = ftl_common_write(address + offset, ptr, size);
		if (ptr) {
			free(ptr);
		}
	} else {
		if (argc != 5) {
			printf("Nor -> AFTW=sector,content,size,offset\r\n");
			return;
		}
		sector = str_to_value((unsigned char const *)argv[1]);
		value = str_to_value((unsigned char const *)argv[2]);
		size = str_to_value((unsigned char const *)argv[3]);
		offset = str_to_value((unsigned char const *)argv[4]);
		printf("NOR Write sector %d content %d size %d offset %d\r\n", sector, value, size, offset);
		address = sector * NOR_FLASH_SECTOR;
		printf("Address %x\r\n", address);
		ptr = malloc(size);
		if (ptr == NULL) {
			printf("Malloc failed\r\n");
			return;
		}
		memset(ptr, value, size);
		ret = ftl_common_write(address + offset, ptr, size);
		if (ptr) {
			free(ptr);
		}
	}
}

void FAFTR(void *arg)
{
	int argc;
	volatile int error_no = 0;
	char *argv[MAX_ARGC] = {0};
	int i = 0;
	int index = 0;
	int block, page, size, offset, sector = 0;
	unsigned char *ptr = NULL;
	unsigned int address = 0;
	int type = 0;
	int page_size = 0;
	int block_size = 0;
	int block_cnt = 0;
	int ret = 0;

	ftl_common_info(&type, &page_size, &block_size, &block_cnt);
	printf("type %d page_size %d block_size %d block_cnt %d\r\n", type, page_size, block_size, block_cnt);
	argc = parse_param(arg, argv);
	if (type == FTL_NAND_FLASH) {
		if (argc != 5) {
			printf("Nand -> AFTR=block,page,size,offset\r\n");
			return;
		}
		block = str_to_value((unsigned char const *)argv[1]);
		page = str_to_value((unsigned char const *)argv[2]);
		size = str_to_value((unsigned char const *)argv[3]);
		offset = str_to_value((unsigned char const *)argv[4]);
		printf("NAND Read block %d page %d size %d offset %d\r\n", block, page, size, offset);
		ptr = malloc(size);
		if (ptr == NULL) {
			printf("Malloc failed\r\n");
			return;
		}
		if (type == FTL_NAND_FLASH) {
			address = block * block_size + page * page_size;
			printf("Address %x\r\n", address);
			ret = ftl_common_read(address + offset, ptr, size);
		} else {

		}
	} else {
		if (argc != 4) {
			printf("Nor -> AFTR=sector,size,offset\r\n");
			return;
		}
		sector = str_to_value((unsigned char const *)argv[1]);
		size = str_to_value((unsigned char const *)argv[2]);
		offset = str_to_value((unsigned char const *)argv[3]);
		printf("NOR Read sector %d size %d offset %d\r\n", sector, size, offset);
		address = sector * NOR_FLASH_SECTOR;
		printf("Address %x\r\n", address);
		ptr = malloc(size);
		if (ptr == NULL) {
			printf("Malloc failed\r\n");
			return;
		}
		ret = ftl_common_read(address + offset, ptr, size);
	}
	hexDump(ptr, size);
	if (ptr) {
		free(ptr);
	}
}

void FAFTWD(void *arg)
{
	int argc;
	volatile int error_no = 0;
	char *argv[MAX_ARGC] = {0};
	int i = 0;
	int index = 0;
	int block, page, value, size, offset, sector = 0;
	unsigned char *ptr = NULL;
	int address = 0;
	int type = 0;
	int page_size = 0;
	int block_size = 0;
	int block_cnt = 0;
	int ret = 0;

	argc = parse_param(arg, argv);
	ftl_common_info(&type, &page_size, &block_size, &block_cnt);

	printf("type %d page_size %d block_size %d block_cnt %d\r\n", type, page_size, block_size, block_cnt);
	argc = parse_param(arg, argv);
	if (argc != 4) {
		printf("AFWD=addr,content,size\r\n");
		return;
	}
	address = str_to_value((unsigned char const *)argv[1]);
	value = str_to_value((unsigned char const *)argv[2]);
	size = str_to_value((unsigned char const *)argv[3]);
	if (type == 0) {
		printf("Nor write address %x content %d size %d\r\n", address, value, size);
	} else {
		printf("Nand write address %x content %d size %d\r\n", address, value, size);
	}
	ptr = malloc(size);
	if (ptr == NULL) {
		printf("Malloc failed\r\n");
		return;
	}
	memset(ptr, value, size);
	ret = ftl_common_write(address, ptr, size);
	if (ptr) {
		free(ptr);
	}
}

void FAFTRD(void *arg)
{
	int argc;
	volatile int error_no = 0;
	char *argv[MAX_ARGC] = {0};
	int i = 0;
	int index = 0;
	int block, page, size, offset, sector = 0;
	unsigned char *ptr = NULL;
	unsigned int address = 0;
	int type = 0;
	int page_size = 0;
	int block_size = 0;
	int block_cnt = 0;
	int ret = 0;

	ftl_common_info(&type, &page_size, &block_size, &block_cnt);
	printf("type %d page_size %d block_size %d block_cnt %d\r\n", type, page_size, block_size, block_cnt);
	argc = parse_param(arg, argv);
	if (argc != 3) {
		printf("AFRD=addr,size\r\n");
		return;
	}
	address = str_to_value((unsigned char const *)argv[1]);
	size = str_to_value((unsigned char const *)argv[2]);
	if (type == 0) {
		printf("NOR Read addr %x size %d\r\n", address, size);
	} else {
		printf("NAND Read addr %x size %d\r\n", address, size);
	}
	ptr = malloc(size);
	if (ptr == NULL) {
		printf("Malloc failed\r\n");
		return;
	}
	ret = ftl_common_read(address, ptr, size);
	hexDump(ptr, size);
	if (ptr) {
		free(ptr);
	}
}

void FAFTE(void *arg)
{
	int argc;
	int ret = 0;
	snand_t obj;
	volatile int error_no = 0;
	char *argv[MAX_ARGC] = {0};
	int i = 0;
	int index = 0;
	int block, page, size, sector = 0;
	unsigned char *ptr = NULL;
	int type = 0;
	int page_size = 0;
	int block_size = 0;
	int block_cnt = 0;
	unsigned int address = 0;

	argc = parse_param(arg, argv);

	ftl_common_info(&type, &page_size, &block_size, &block_cnt);
	printf("type %d page_size %d block_size %d block_cnt %d\r\n", type, page_size, block_size, block_cnt);

	if (type == FTL_NAND_FLASH) {
		if (argc != 2) {
			printf("AFTE=block\r\n");
			return;
		}
		block = str_to_value((unsigned char const *)argv[1]);
		address = block * block_size;
		ret = ftl_common_erase(address);
		printf("Erase address %x\r\n", address);
	} else {
		if (argc != 2) {
			printf("AFTE=sector\r\n");
			return;
		}
		sector = str_to_value((unsigned char const *)argv[1]);
		address = sector * NOR_FLASH_SECTOR;
		ret = ftl_common_erase(address);
		printf("Erase address %x\r\n", address);
	}
}

void FAFTIF(void *arg)
{
	printf("Get nand flash info\r\n");
	ftl_info_dump();
	ftl_info_bbm_dump();
	ftl_bad_block_scan();
}

log_item_t at_ftl_items[ ] = {
	{"AFTW", FAFTW, {NULL, NULL}},
	{"AFTR", FAFTR, {NULL, NULL}},
	{"AFTE", FAFTE, {NULL, NULL}},
	{"AFWD", FAFTWD, {NULL, NULL}},
	{"AFRD", FAFTRD, {NULL, NULL}},
	{"AFIF", FAFTIF, {NULL, NULL}},
};

void at_ftl_init(void)
{
	printf("at_ftl_init %d\r\n", sizeof(at_ftl_items) / sizeof(at_ftl_items[0]));
	log_service_add_table(at_ftl_items, sizeof(at_ftl_items) / sizeof(at_ftl_items[0]));
}

#if SUPPORT_LOG_SERVICE
log_module_init(at_ftl_init);
#endif
