#include "osdep_service.h"
#include "FreeRTOS.h"
#include "task.h"
#include "ota_8735b.h"
#include "sockets.h"
#include "sys_api.h"
#include "fwfs.h"

static TaskHandle_t taskOTA = NULL;

#define STACK_SIZE		1024
#define TASK_PRIORITY	tskIDLE_PRIORITY + 1

#define PROGRESS_BAR_WIDTH 40
#include <time.h>
static void ota_draw_progress(const char *desc, int curr, int max)
{
	static char buf[PROGRESS_BAR_WIDTH + 1];

	static time_t last_time;
	time_t curr_time = time(NULL);
	int last_progress = -1;
	int progress;
	int x;

	/* check for not known maximum */
	if (max < curr) {
		max = curr;
	}
	/* make none out of none give zero */
	if (max == 0 && curr == 0) {
		max = 1;
	}

	progress = (PROGRESS_BAR_WIDTH * curr) / max;
	if (progress > PROGRESS_BAR_WIDTH) {
		progress = PROGRESS_BAR_WIDTH;
	}

	for (x = 0; x != PROGRESS_BAR_WIDTH; x++) {
		if (x < progress) {
			buf[x] = '=';
		} else {
			buf[x] = ' ';
		}
	}
	buf[x] = 0;

	printf("\r%s\t[%s] %3lld%% %12d/%12d bytes", desc, buf, (100ULL * curr) / max, curr, max);
	if (progress == PROGRESS_BAR_WIDTH) {
		printf("\n\r%s done.\n\r", desc);
	}
}


// Checksum check before make fw valid
// Please make sure target OTA firmware did contains 4 bytes checksum value, or the checksum check would always fail
// User can check target firmware postbuild routine.
#define USE_CHECKSUM 1

typedef struct update_cfg_fwfs_s {
	update_cfg_local_t local;
	char *part_name;
} update_cfg_fwfs_t;

static void update_ota_local_task(void *param)
{
	int server_socket = -1;
	uint8_t *buf;
	int read_bytes = 0;
	uint32_t idx = 0;
	update_cfg_local_t *cfg = &((update_cfg_fwfs_t *)param)->local;
	char *part_name = ((update_cfg_fwfs_t *)param)->part_name;
	uint32_t file_info[3];
	int ret = -1 ;
	uint8_t cur_fw_idx = 0, target_fw_idx = 0;
	uint32_t ota_len = 0;
	_file_checksum file_checksum;
	file_checksum.u = 0;
	uint32_t buf_size = 4096;
	uint8_t boot_sel = -1;
	uint32_t total_blocks = 0, cur_block = 0;

#if defined(configENABLE_TRUSTZONE) && (configENABLE_TRUSTZONE == 1)
	rtw_create_secure_context(configMINIMAL_SECURE_STACK_SIZE);
#endif
	printf("\n\r[%s] NN model update task start", __FUNCTION__);

	buf = malloc(4096);
	if (!buf) {
		printf("\n\r[%s] Alloc buffer failed", __FUNCTION__);
		goto update_ota_exit;
	}

	// Connect server
	server_socket = update_ota_connect_server(cfg);
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
		printf("\n\r[%s] tx checksum  0x%x", __FUNCTION__, file_info[0]);
		printf("\n\r[%s] tx file size 0x%x", __FUNCTION__, file_info[2]);
		if (file_info[2] == 0) {
			printf("\n\r[%s] No file size", __FUNCTION__);
			goto update_ota_exit;
		} else {
			ota_len = file_info[2];
			total_blocks = (ota_len + buf_size - 1) / buf_size;
		}
	}

	// open firmware
	void *fp = pfw_open(part_name, M_RAW | M_RDWR);
	if (!fp) {
		goto update_ota_exit;
	}


	// Write New FW sector
	printf("\n\r[%s] Start to read data %d bytes\r\n", __FUNCTION__, ota_len);
	while (1) {
		int rest_len = ota_len - idx;
		int data_len = rest_len > buf_size ? buf_size : rest_len;

		memset(buf, 0, buf_size);
		read_bytes = 0;
		while (read_bytes < data_len) {
			read_bytes += read(server_socket, &buf[read_bytes], data_len - read_bytes);
			if (read_bytes < 0) {
				printf("\n\r[%s] Read socket failed", __FUNCTION__);
				goto update_ota_exit;
			}
		}
		if (read_bytes == 0) {
			break;    // Read end
		}

		if ((idx + read_bytes) > ota_len) {
			printf("\n\r[%s] Redundant bytes received", __FUNCTION__);
			read_bytes = ota_len - idx;
			data_len = read_bytes;
		}

		// check final block
		cur_block = idx / buf_size;
		if (cur_block == (total_blocks - 1)) {
			data_len -= 4; // remove final 4 bytes checksum
			//	memset(buf + data_len, 0xFF, buf_size - data_len);
		}

		int wr_status = pfw_write(fp, buf, data_len);

		if (wr_status < 0) {
			printf("\n\r[%s] ota flash failed", __FUNCTION__);
			goto update_ota_exit;
		}

		idx += read_bytes;

		ota_draw_progress("programming", idx, ota_len);

#if USE_CHECKSUM
		// checksum attached at file end
		if (idx == ota_len) {
			file_checksum.c[0] = buf[read_bytes - 4];
			file_checksum.c[1] = buf[read_bytes - 3];
			file_checksum.c[2] = buf[read_bytes - 2];
			file_checksum.c[3] = buf[read_bytes - 1];

			printf("attached checksum %x\n\r", file_checksum.u);
		}
#endif

		if (idx == ota_len) {
			break;
		}
	}
	printf("\n\rupdate finished\r\n");
	pfw_close(fp);
	ret = 0;

#if USE_CHECKSUM
	int chksum = 0;
	int chklen = ota_len - 4;		// skip 4byte ota length
	void *chkfp = pfw_open(part_name, M_RAW | M_RDWR);
	if (!chkfp) {
		goto update_ota_exit;
	}
	while (chklen > 0) {
		int rdlen = chklen > 4096 ? 4096 : chklen;
		pfw_read(chkfp, buf, rdlen);
		for (int i = 0; i < rdlen; i++) {
			chksum += buf[i];
		}
		chklen -= rdlen;
	}

	printf("checksum Remote %x, Flash %x\n\r", file_checksum.u, chksum);
	if (file_checksum.u != chksum) {
		pfw_seek(chkfp, 0, SEEK_SET);
		memset(buf, 0, 4096);
		pfw_write(chkfp, buf, 4096);
	}
	pfw_close(chkfp);
#endif

update_ota_exit:
	if (buf) {
		free(buf);
	}

	if (server_socket >= 0) {
		close(server_socket);
	}
	if (param) {
		free(param);
	}
	taskOTA = NULL;
	printf("\n\r[%s] Update task exit", __FUNCTION__);

	if (!ret) {
		printf("\n\r[%s] Ready to reboot", __FUNCTION__);
		osDelay(100);
		ota_platform_reset();
	}
	vTaskDelete(NULL);
	return;
}

int ota_update_fwfs(char *fw_name, char *ip, int port)
{
	update_cfg_fwfs_t *pUpdateCfg;

	if (taskOTA) {
		printf("\n\r[%s] Update task has created.", __FUNCTION__);
		return 0;
	}
	pUpdateCfg = malloc(sizeof(update_cfg_fwfs_t));
	if (pUpdateCfg == NULL) {
		printf("\n\r[%s] Alloc update cfg failed", __FUNCTION__);
		return -1;
	}
	pUpdateCfg->local.ip_addr = inet_addr(ip);
	pUpdateCfg->local.port = ntohs(port);
	pUpdateCfg->part_name = fw_name;//"NN_MDL";

	if (xTaskCreate(update_ota_local_task, "OTA_server", STACK_SIZE, pUpdateCfg, TASK_PRIORITY, &taskOTA) != pdPASS) {
		update_free(pUpdateCfg);
		printf("\n\r[%s] Create update task failed", __FUNCTION__);
	}
	return 0;
}

/*******************COMMAND FOR FWFS OTA**********************/
#include "log_service.h"
void cmd_fwfs_update(void *arg)
{

	int argc = 0;
	char *argv[16] = {0};
	argc = parse_param(arg, argv);

	int port;
	if (argc != 4) {
		printf("\n\rUsage: %s=[PARTITION_NAME],[SERVER_IP],[PORT]", argv[0]);
		printf("\n\rExample: %s=NN_MDL,192.168.1.1,8082", argv[0]);
		return;
	}
	port = atoi(argv[3]);
	ota_update_fwfs(argv[1], argv[2], port);
}


log_item_t fwfs_ota_items[] = {
	{"FOTA", cmd_fwfs_update,}
};

void atcmd_fwfs_ota_init(void)
{
	log_service_add_table(fwfs_ota_items, sizeof(fwfs_ota_items) / sizeof(fwfs_ota_items[0]));
}

