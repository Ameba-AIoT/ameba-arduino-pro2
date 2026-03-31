#include "FreeRTOS.h"
#include "task.h"
#include <stdint.h>
#include "platform_opts.h"
#define _USB_ERRNO_H //Prevent redefine
#include "dfu/inc/usbd_dfu.h"

#include "sys_api.h"
#include "flash_api.h"
#include "ota_8735b.h"

#include <stdio.h>
#include "vfs.h"

#include "osdep_service.h"
#include <device_lock.h>
#include "log_service.h"

#define FW1_ADDRESS  0x2060
#define FW2_ADDRESS  0x2080
#define BOOT_ADDRESS 0x2020
#define ISP_ADDRESS  0x20a0
#define NNM_ADDRESS  0x20c0

#define FW1_INDEX 0X01
#define FW2_INDEX 0X02
#define BOT_INDEX 0X03
#define ISP_INDEX 0X04
#define NNM_INDEX 0X05
#define CER_INDEX 0X06

#define ISP_ID 0x89CE
#define BOOT_ID 0xD1C5
#define FW1_ID 0xC1C7
#define FW2_ID 0xB9C8
#define NNM_ID 0x81CF

#define MAX_PARTITION_NUM 16

#define FW_BUF_SIZE (20*1024*1024)

#define FW_LEN_OFFSET 0x2e0
#define PARTITION_OFFSET 0x2000

typedef struct {
	int read_bytes;
	int update_size;
	int boot_type;
	_file_checksum file_checksum;
	uint32_t cur_fw_idx;
	uint32_t target_fw_idx;
	FILE *fp;
	struct dfu_opts dfu_cb;
	unsigned char *fw_buf;
	uint32_t terminate;
} dfu_usb_operate_t;

static dfu_usb_operate_t usb_fw_dfu;
static sys_thread_t Task_FW = NULL;
extern int ota_flash_NAND(uint32_t target_fw_idx, uint32_t total_blocks, uint32_t cur_block, uint8_t *buf, uint32_t data_len, _file_checksum file_checksum);
extern int ota_flash_NOR(uint32_t target_fw_idx, uint32_t total_blocks, uint32_t cur_block, uint8_t *buf, uint32_t data_len, _file_checksum file_checksum);

static int ota_fw_upgrade(unsigned int target_fw_idx, unsigned int fw_address, unsigned int fw_size, unsigned char *fw_buf)
{
	int block_num = 0;
	int i = 0;
	int ret = 0;
	unsigned char *ptr = fw_buf;
	unsigned int checksum = 0;
	_file_checksum file_checksum;

	for (i = 0; i < fw_size ; i++) {
		checksum += fw_buf[fw_address + i];
	}
	file_checksum.u = checksum;
	if (fw_size % NAND_BLOCK_SIZE) {
		block_num = fw_size / (NAND_BLOCK_SIZE) + 1;
	} else {
		block_num = fw_size / (NAND_BLOCK_SIZE);
	}
	for (i = 0; i < fw_size / NAND_BLOCK_SIZE; i++) {
		ret = ota_flash_NAND(target_fw_idx, block_num, i, ptr + (fw_address + i * NAND_BLOCK_SIZE), NAND_BLOCK_SIZE, file_checksum);
	}
	if (fw_size % NAND_BLOCK_SIZE) {
		ret = ota_flash_NAND(target_fw_idx, block_num, i, ptr + (fw_address + i * NAND_BLOCK_SIZE), fw_size % NAND_BLOCK_SIZE, file_checksum);
	}
	return ret;
}

static int nor_flash_update(unsigned char *fw_buf, int fw_size, int index)
{
	int ret = 0;
	flash_t flash;
	device_mutex_lock(RT_DEV_LOCK_FLASH);
	flash_erase_sector(&flash, index * NOR_BLOCK_SIZE);
	printf("index %d fw_size %d\r\n", index, fw_size);
	if (flash_burst_write(&flash, index * NOR_BLOCK_SIZE, NOR_BLOCK_SIZE, fw_buf) < 0) {
		printf("\n\r[%s] flash write failed", __FUNCTION__);
		device_mutex_unlock(RT_DEV_LOCK_FLASH);
		ret = -1;
		goto exit;
	}
	device_mutex_unlock(RT_DEV_LOCK_FLASH);
exit:
	return ret;
}

static int nand_flash_get_fw(int id, int fw_index, int img_len, unsigned char *fw_buf, int *fw_address, int *fw_len)
{
	int address = 0;
	int size = 0;
	int ret = 0;
	for (int i = 1; i <= MAX_PARTITION_NUM ; i++) {
		if (fw_buf[PARTITION_OFFSET + i * 0x20 + 0X08] == (id & 0xff) && fw_buf[PARTITION_OFFSET + i * 0x20 + 0X09] == ((id >> 0x08) & 0xff)) {
			address = fw_buf[PARTITION_OFFSET + i * 0x20 + 3] << 24 | fw_buf[PARTITION_OFFSET + i * 0x20 + 2] << 16 | fw_buf[PARTITION_OFFSET + i * 0x20 + 1] << 8 |
					  fw_buf[PARTITION_OFFSET + i * 0x20] << 0;
			*fw_address = address;
			if (*fw_address < img_len) {
				if (fw_buf[address] == 'R' && fw_buf[address + 1] == 'T' && fw_buf[address + 2] == 'L') {
					size = 4096 + (fw_buf[address + FW_LEN_OFFSET + 3] << 24 | fw_buf[address + FW_LEN_OFFSET + 2] << 16 | fw_buf[address + FW_LEN_OFFSET + 1] << 8 | fw_buf[address
								   + FW_LEN_OFFSET] << 0);
					*fw_len = size;
					printf("ID %x fw_address %x fw_len %x\r\n", id, *fw_address, *fw_len);
					ret = ota_fw_upgrade(fw_index, address, size, fw_buf);
				}
			}

		}
	}
	return ret;
}

static int nand_flash_save_certificate(unsigned char *fw_buf, int fw_len)
{
	int fw_w_len = 0;
	int str_address = 0;
	int ret = 0;
	if (fw_buf[0x3f] == 0x01) {
		fw_w_len = (fw_buf[0x35] << 8) + fw_buf[0x34];
		str_address = (fw_buf[0x33] << 24) + (fw_buf[0x32] << 16) + (fw_buf[0x31] << 8) + (fw_buf[0x30] << 0);
		if (fw_len >= (str_address + fw_w_len)) {
			if (fw_buf[str_address] != 0xff) {
				printf("certificate_1 str_address = 0x%x fw_w_len = %d\r\n", str_address, fw_w_len);
				ret = ota_fw_upgrade(CER_INDEX, str_address, fw_w_len, fw_buf);
			}
		}
	}
	return ret;
}

static int nand_flash_update(unsigned char *fw_buf, int fw_len)
{
	int fw_address = 0;
	int fw_size = 0;
	int fw_w_len = 0;
	int ret = 0;
	printf("Update nand flash\r\n");
	ret = nand_flash_save_certificate(fw_buf, fw_len); //For CER
	if (ret < 0) {
		printf("fail ret %d %s %d\r\n", ret, __FUNCTION__, __LINE__);
		return -1;
	}
	ret = nand_flash_get_fw(ISP_ID, ISP_INDEX, fw_len, fw_buf, &fw_address, &fw_size); //For ISP
	if (ret < 0) {
		printf("fail ret %d %s %d\r\n", ret, __FUNCTION__, __LINE__);
		return -1;
	}
	ret = nand_flash_get_fw(BOOT_ID, BOT_INDEX, fw_len, fw_buf, &fw_address, &fw_size); //For Bootloader
	if (ret < 0) {
		printf("fail ret %d %s %d\r\n", ret, __FUNCTION__, __LINE__);
		return -1;
	}
	ret = nand_flash_get_fw(FW1_ID, FW1_INDEX, fw_len, fw_buf, &fw_address, &fw_size); //For FW1
	if (ret < 0) {
		printf("fail ret %d %s %d\r\n", ret, __FUNCTION__, __LINE__);
		return -1;
	}
	ret = nand_flash_get_fw(FW2_ID, FW2_INDEX, fw_len, fw_buf, &fw_address, &fw_size); //For FW2
	if (ret < 0) {
		printf("fail ret %d %s %d\r\n", ret, __FUNCTION__, __LINE__);
		return -1;
	}
	ret = nand_flash_get_fw(NNM_ID, NNM_INDEX, fw_len, fw_buf, &fw_address, &fw_size); //For NNM
	if (ret < 0) {
		printf("fail ret %d %s %d\r\n", ret, __FUNCTION__, __LINE__);
		return -1;
	}
	return ret;
}
//////////////DUF UPGRADE PROCEDURE/////////////////////////////////////
static int ota_upgrade_from_usb(unsigned char *buf, unsigned int size, int index)
{
	dfu_usb_operate_t *dfu = &usb_fw_dfu;
	int ret = 0;
	int wr_status = 0;
	dfu->read_bytes = size;
	if (dfu->boot_type) {
		memcpy(dfu->fw_buf + dfu->update_size, buf, size);
	} else {
		//int nor_flash_update(unsigned char *fw_buf, int fw_size, int index)
		nor_flash_update(buf, size, index);
	}
	dfu->update_size += dfu->read_bytes;
	return 0;
}

static int ota_checksum_from_usb(void *parm)
{
	(void)(parm);
	unsigned int fw_address = 0;
	unsigned int fw_size    = 0;
	int ret = 0;
	int i = 0;
	dfu_usb_operate_t *dfu = &usb_fw_dfu;
	if (dfu->boot_type == 0) { //For NOR FLASH UPGRADE
		printf("Update nor flash %x\r\n", dfu->update_size);
	} else {
		printf("Update nand flash\r\n");
		ret = nand_flash_update(dfu->fw_buf, dfu->update_size);
	}
	return ret;
}

static int ota_reset_from_usb(void *parm)
{
	(void)(parm);
	int ret = -1;
	ota_platform_reset();
	dfu_usb_operate_t *dfu = &usb_fw_dfu;
	while (1) {
		if (dfu->terminate) {
			break;
		} else {
			vTaskDelay(1000);
		}
	}
	return ret;
}
//////////////DUF UPGRADE PROCEDURE/////////////////////////////////////
//////////////WIFI Upgrade Procedure//////////
static int update_fw_connect_server(update_cfg_local_t *cfg)
{
	struct sockaddr_in server_addr;
	int server_socket;

	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket < 0) {
		printf("\n\r[%s] Create socket failed", __FUNCTION__);
		return -1;
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = cfg->ip_addr;
	server_addr.sin_port = cfg->port;

	if (connect(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
		printf("\n\r[%s] Socket connect failed", __FUNCTION__);
		return -1;
	}

	return server_socket;
}
static void update_ota_all_local_task(void *param)
{
	int server_socket = -1;
	int read_bytes = 0;
	update_cfg_local_t *cfg = (update_cfg_local_t *)param;
	uint32_t file_info[3];
	int ret = -1 ;
	uint32_t ota_len = 0;
	uint8_t boot_sel = -1;
	uint8_t *update_buf = NULL;
#if defined(configENABLE_TRUSTZONE) && (configENABLE_TRUSTZONE == 1)
	rtw_create_secure_context(configMINIMAL_SECURE_STACK_SIZE);
#endif
	printf("\n\r[%s] Update task start", __FUNCTION__);

	boot_sel = sys_get_boot_sel();

	// Connect server
	server_socket = update_fw_connect_server(cfg);
	if (server_socket == -1) {
		goto update_ota_exit;
	}

	// Get file size from DownloadServer.
	memset(file_info, 0, sizeof(file_info));
	if (file_info[0] == 0) {
		printf("\n\r[%s] Read info first", __FUNCTION__);
		read_bytes = read(server_socket, file_info, sizeof(file_info));
		if (read_bytes <= 0) {
			printf("\n\r[%s] Read socket failed or socket closed", __FUNCTION__);
			goto update_ota_exit;
		}
		// !X!X!X!X!X!X!X!X!X!X!X!X!X!X!X!X!X!X!X!X
		// !W checksum !W padding 0 !W file size !W
		// !X!X!X!X!X!X!X!X!X!X!X!X!X!X!X!X!X!X!X!X
		printf("\n\r[%s] info %d bytes", __FUNCTION__, read_bytes);
		printf("\n\r[%s] tx file size 0x%x", __FUNCTION__, file_info[2]);
		if (file_info[2] == 0) {
			printf("\n\r[%s] No file size", __FUNCTION__);
			goto update_ota_exit;
		} else {
			ota_len = file_info[2];
		}
	}

	// Write New FW sector
	printf("\n\r[%s] Start to read data %d bytes\r\n", __FUNCTION__, ota_len);
	update_buf = malloc(ota_len);
	read_bytes = 0;
	while (read_bytes < ota_len) {
		read_bytes += read(server_socket, update_buf + read_bytes, ota_len - read_bytes);
		if (read_bytes < 0) {
			printf("\n\r[%s] Read socket failed", __FUNCTION__);
			goto update_ota_exit;
		}
	}
	if (read_bytes == ota_len) {
		if (boot_sel == 0) {
			int i = 0;
			printf("Update nor flash %x\r\n", ota_len);
			for (i = 0 ; i < ota_len / NOR_BLOCK_SIZE; i++) {
				ret = nor_flash_update(update_buf + i * NOR_BLOCK_SIZE, NOR_BLOCK_SIZE, i);
				if (ret < 0) {
					goto update_ota_exit;
				}
			}
			if (ota_len % NOR_BLOCK_SIZE) {
				ret = nor_flash_update(update_buf + i * NOR_BLOCK_SIZE, ota_len % NOR_BLOCK_SIZE, i);
				if (ret < 0) {
					goto update_ota_exit;
				}
			}
		} else if (boot_sel == 1) {
			ret = nand_flash_update(update_buf, ota_len);
		}
		printf("Update finish %d %d\r\n", read_bytes, ota_len);
	} else {
		printf("Update fail %d %d\r\n", read_bytes, ota_len);
	}

update_ota_exit:
	if (server_socket >= 0) {
		close(server_socket);
	}
	if (param) {
		update_free(param);
	}
	Task_FW = NULL;
	printf("\n\r[%s] Update task exit", __FUNCTION__);
	if (!ret) {
		printf("\n\r[%s] Ready to reboot", __FUNCTION__);
		osDelay(100);
		ota_platform_reset();
	}
	vTaskDelete(NULL);
	return;
}

static int update_fw_local(char *ip, int port)
{
	update_cfg_local_t *pUpdateCfg;

	if (Task_FW) {
		printf("\n\r[%s] Update task has created.", __FUNCTION__);
		return 0;
	}
	pUpdateCfg = malloc(sizeof(update_cfg_local_t));
	if (pUpdateCfg == NULL) {
		printf("\n\r[%s] Alloc update cfg failed", __FUNCTION__);
		return -1;
	}
	pUpdateCfg->ip_addr = inet_addr(ip);
	pUpdateCfg->port = ntohs(port);

	if (xTaskCreate(update_ota_all_local_task, "OTA_server", 4096, pUpdateCfg, tskIDLE_PRIORITY + 1, &Task_FW) != pdPASS) {
		free(pUpdateCfg);
		printf("\n\r[%s] Create update task failed", __FUNCTION__);
	}
	return 0;
}
//////////////WIFI Upgrade Procedure//////////
void usb_upgrade_fw_thread(void *param)
{
	int status = 0;
	dfu_usb_operate_t *dfu = &usb_fw_dfu;

#if defined(configENABLE_TRUSTZONE) && (configENABLE_TRUSTZONE == 1)
	rtw_create_secure_context(configMINIMAL_SECURE_STACK_SIZE);
#endif

	memset(dfu, 0, sizeof(dfu_usb_operate_t));

	int8_t boot_sel = -1;

	boot_sel = sys_get_boot_sel();

	if (0 == boot_sel) {
		// boot from NOR flash
		dfu->boot_type = 0;
	} else if (1 == boot_sel) {
		// boot from NAND flash
		dfu->boot_type = 1;
	}

	dfu->dfu_cb.write = ota_upgrade_from_usb;
	dfu->dfu_cb.checksum = ota_checksum_from_usb;
	dfu->dfu_cb.reset = ota_reset_from_usb;
	dfu->fw_buf = malloc(FW_BUF_SIZE);
	if (dfu->fw_buf == NULL) {
		printf("It can't allocate the buffer\r\n");
		goto exit;
	}
	_usb_init();

	status = wait_usb_ready();
	if (status != USBD_INIT_OK) {
		if (status == USBD_NOT_ATTACHED) {
			printf("\r\n NO USB device attached\n");
		} else {
			printf("\r\n USB init fail\n");
		}
		goto exit;
	}

	status = usbd_dfu_init(&dfu->dfu_cb);

	if (status) {
		printf("USB DFU driver load fail.\n");
	} else {
		printf("USB DFU driver load done, Available heap [0x%x]\n", xPortGetFreeHeapSize());
	}
exit:
	vTaskDelete(NULL);
}
void sd_upgrade_fw_thread(void *param)
{
	unsigned char *fw_buf = NULL;
	FILE *m_file;
	struct stat fstat;
	int ret = 0;
	int i = 0;
	int boot_sel = sys_get_boot_sel();

#if defined(configENABLE_TRUSTZONE) && (configENABLE_TRUSTZONE == 1)
	rtw_create_secure_context(configMINIMAL_SECURE_STACK_SIZE);
#endif

	vfs_init(NULL);
	ret = vfs_user_register("sd", VFS_FATFS, VFS_INF_SD);
	if (ret < 0) {
		printf("It can't init sd card\r\n");
		goto EXIT;
	}
	m_file = fopen("sd:/flash_ntz.bin", "r");
	stat("sd:/flash_ntz.bin", &fstat);
	printf("file size: %d bytes\n\r", fstat.st_size);
	if (m_file == NULL) {
		printf("It can't find the flash_ntz.bin\r\n");
		goto EXIT;
	}

	fw_buf = malloc(fstat.st_size);
	if (fw_buf == NULL) {
		printf("It can't create the memory\r\n");
		goto EXIT;
	}

	fread(fw_buf, 1, fstat.st_size, m_file);

	fclose(m_file);

	if (boot_sel == 0) { //For NOR FLASH UPGRADE
		printf("Update nor flash %x\r\n", fstat.st_size);
		for (i = 0 ; i < fstat.st_size / NOR_BLOCK_SIZE; i++) {
			ret = nor_flash_update(fw_buf + i * NOR_BLOCK_SIZE, NOR_BLOCK_SIZE, i);
			if (ret < 0) {
				goto EXIT;
			}
		}
		if (fstat.st_size % NOR_BLOCK_SIZE) {
			printf("remain index %d\r\n", i);
			ret = nor_flash_update(fw_buf + i * NOR_BLOCK_SIZE, fstat.st_size % NOR_BLOCK_SIZE, i);
			if (ret < 0) {
				goto EXIT;
			}
		}
	} else {
		printf("Update nand flash\r\n");
		ret = nand_flash_update(fw_buf, fstat.st_size);
		if (ret < 0) {
			printf("nand_flash_update fail\r\n");
			goto EXIT;
		}
	}
	if (fw_buf) {
		free(fw_buf);
	}
	printf("fw upgrade successful\r\n");
	ota_platform_reset();
	while (1) {
		vTaskDelay(1000);
	}
EXIT:
	if (fw_buf) {
		free(fw_buf);
	}
	vTaskDelete(NULL);
}

void dfu_wifi_command(void *arg)
{
	int argc = 0;
	int ret = 0;
	char *argv[MAX_ARGC] = {0};
	int port = 0;
	printf("Enable the wifi fw upgrade\r\n");
	argc = parse_param(arg, argv);
	if (argc != 3) {
		printf("DFUW=ip,port\r\n");
		return;
	}
	port = atoi(argv[2]);
	printf("ip %s port %d\r\n", argv, port);
	update_fw_local(argv[1], port);
}
void dfu_usb_command(void *arg)
{
	printf("Enable the usb fw upgrade\r\n");
	if (xTaskCreate(usb_upgrade_fw_thread, ((const char *)"usb_upgrade_fw_thread"), 2048, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS) {
		printf("\n\r%s xTaskCreate(usb_upgrade_fw_thread) failed", __FUNCTION__);
	}
}
void dfu_sdcard_command(void *arg)
{
	printf("Enable the sdcard fw upgrade\r\n");
	if (xTaskCreate(sd_upgrade_fw_thread, ((const char *)"sd_upgrade_fw_thread"), 2048, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS) {
		printf("\n\r%s xTaskCreate(sd_upgrade_fw_thread) failed", __FUNCTION__);
	}
}
static log_item_t at_dfu_items[ ] = {
	{"DFUW", dfu_wifi_command,},//dfu for WIFI
	{"DFUU", dfu_usb_command,},//dfu for USB
	{"DFUS", dfu_sdcard_command,},//dfu for SD
};

void atcmd_dfu_init(void)
{
	printf("Support upgrade fw from ATCMD\r\n");
	log_service_add_table(at_dfu_items, sizeof(at_dfu_items) / sizeof(at_dfu_items[0]));
}