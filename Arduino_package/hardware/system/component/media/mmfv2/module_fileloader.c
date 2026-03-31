/******************************************************************************
*
* Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
*
******************************************************************************/
#include <stdint.h>
#include <string.h>
#include "platform_stdlib.h"
#include "avcodec.h"
#include "mmf2_module.h"
#include "module_fileloader.h"

static volatile int load_file_count = 0;

void fileloader_handler(void *p)
{
	fileloader_ctx_t *ctx = (fileloader_ctx_t *)p;
	int ret = 0;

	while (load_file_count < ctx->load_file_num) {
		mm_context_t *mctx = (mm_context_t *)ctx->parent;
		mm_queue_item_t *output_item;
		int is_output_ready = xQueueReceive(mctx->output_recycle, &output_item, 0xFFFFFFFF) == pdTRUE;
		if (is_output_ready) {
			uint8_t *test_data_addr = NULL;
			uint32_t test_data_len = 0;
			char sd_fn_in[256];
			memset(sd_fn_in, 0x00, sizeof(sd_fn_in));

			load_file_count++;

			if (ctx->params.codec_id == AV_CODEC_ID_BMP || ctx->params.codec_id == AV_CODEC_ID_JPEG) {
				if (ctx->read_mode == SEQUENCE_MODE) {
					if (ctx->params.codec_id == AV_CODEC_ID_BMP) {
						snprintf(sd_fn_in, sizeof(sd_fn_in), "%s-%04d.bmp", ctx->sd_dataset_file_path_in, load_file_count);
					} else if (ctx->params.codec_id == AV_CODEC_ID_JPEG) {
						snprintf(sd_fn_in, sizeof(sd_fn_in), "%s-%04d.jpg", ctx->sd_dataset_file_path_in, load_file_count);
					}
				} else if (ctx->read_mode == FILELIST_MODE) {
					//fgets(sd_fn_in, sizeof(sd_fn_in), ctx->ff);
					ctx->ma->media_get_listname(sd_fn_in, sizeof(sd_fn_in), ctx->mactx->list_ctx);
					printf("[image %d] %s\r\n", load_file_count, sd_fn_in);
				}

				if (ctx->ma->media_load_file == NULL) {
					printf("No registered file loading function\r\n");
					break;
				}

				ret = ctx->ma->media_load_file(ctx->mactx, &test_data_addr, &test_data_len, sd_fn_in);
				if (ret < 0 || test_data_addr == NULL || test_data_len == 0) {
					printf("Fail to load the file\r\n");
					if (test_data_addr != NULL) {
						free(test_data_addr);
					}
					break;
				}

				if (ctx->decode_in_place) {
					ret = ctx->decode_in_place((void *)test_data_addr, &test_data_len); /* ImageDecodeToRGB888planar_ConvertInPlace */
					if (ret < 0) {
						printf("Fail to decode the file\r\n");
						if (test_data_addr != NULL) {
							free(test_data_addr);
						}
						break;
					}
				}

				memcpy((uint32_t *)output_item->data_addr, (uint32_t *)test_data_addr, test_data_len);
				output_item->size = test_data_len;
				output_item->timestamp = mm_read_mediatime_ms();
				output_item->type = AV_CODEC_ID_RGB888;
				memcpy(output_item->name, sd_fn_in, sizeof(output_item->name));

			}
			/*else if(ctx->params.codec_id == AV_CODEC_ID_XXXXX) {
			*    snprintf(sd_fn_in, sizeof(sd_fn_in), "filename", ctx->sd_dataset_file_path_in, load_file_count);
			*    SD_file_load_file(&test_data_addr, &test_data_len, sd_fn_in);
			*
			*    memcpy(output_item->data_addr, test_data_addr, test_data_len);
			*    output_item->size = test_data_len;
			*    output_item->timestamp = mm_read_mediatime_ms();
			*    output_item->type = AV_CODEC_ID_XXXXX;
			*
			*}*/

			xQueueSend(mctx->output_ready, (void *)&output_item, 0xFFFFFFFF);
			if (test_data_addr != NULL) {
				free(test_data_addr);
			}
		}
	}
	printf("\r\nFiles loading done...\r\n");

	vTaskDelete(NULL);
}

void fileloader_task_enable(void *parm)
{
	fileloader_ctx_t *ctx = (fileloader_ctx_t *)parm;

	ctx->ma->media_init(ctx);

	if (strlen(ctx->file_list_name) != 0) {
		//ctx->ff =
		ctx->mactx->list_ctx = ctx->ma->media_list_init(ctx->mactx, ctx->file_list_name);
		if (ctx->mactx->list_ctx == NULL) {
			printf("Fail to init the file list\r\n");
			abort();
		}
	}

	if (xTaskCreate(fileloader_handler, ((const char *)"fileloader_handler"), 8192, parm, tskIDLE_PRIORITY + 1, &ctx->task) != pdPASS) {
		printf("\n\r%s xTaskCreate failed", __FUNCTION__);
	}
}

/*-----------------------------------------------------------------------------------*/
static void SD_file_loader_init(void *p)
{
	fileloader_ctx_t *ctx = (fileloader_ctx_t *)p;

	ctx->mactx = malloc(sizeof(media_ctx_t));

	vfs_init(NULL);
	vfs_user_register("sd", VFS_FATFS, VFS_INF_SD);

	printf("sd file loader inited \n\r");
}

static void SD_file_loader_deinit(void *p)
{
	fileloader_ctx_t *ctx = (fileloader_ctx_t *)p;
	if (ctx->mactx) {
		free(ctx->mactx);
	}

	vfs_user_unregister("sd", VFS_FATFS, VFS_INF_SD);
	vfs_deinit(NULL);

	printf("sd file loader deinited \n\r");
}

static int SD_file_load_file(void *p, uint8_t **pFrame, uint32_t *pSize, char *frameFilePath)
{
	char path_all[256];
	memset(path_all, 0, sizeof(path_all));
	snprintf(path_all, sizeof(path_all), "%s%s", "sd:/", frameFilePath);
	printf("SD_file_load_file: %s\r\n", path_all);

	FILE *m_file;
	m_file = fopen(path_all, "r+");
	if (m_file == NULL) {
		printf("file not exist!!! %s\r\n", path_all);
		return -1;
	}
	fseek(m_file, 0, SEEK_END);
	int file_size = ftell(m_file);
	printf("\r\nfile_size: %d bytes.\r\n", file_size);
	fseek(m_file, 0, SEEK_SET);

	uint8_t *file_buf = (uint8_t *)malloc(DEFAULT_NN_INPUT_LEN);
	if (file_buf == NULL) {
		printf("\r\nfile malloc fail!\r\n");
		fclose(m_file);
		return -1;
	}
	int count = fread(file_buf, file_size, 1, m_file);
	fclose(m_file);

	*pFrame = file_buf;
	*pSize = (uint32_t)(file_size * count);

	return (int)(*pSize);
}

static int SD_file_get_listname(char *buf, int size, void *ctx)
{
	return fgets(buf, size, (FILE *)ctx) == NULL ? -1 : 0;
}
/*-----------------------------------------------------------------------------------*/
static void *SD_file_list_init(void *p, char *listname)
{
	char file_name[256];
	memset(file_name, 0, sizeof(file_name));
	snprintf(file_name, sizeof(file_name), "%s%s", "sd:/", listname);
	return (void *)fopen(file_name, "r+");
}

static media_access_t ma_sd = {
	.media_init 		= SD_file_loader_init,
	.media_deinit		= SD_file_loader_deinit,
	.media_load_file 	= SD_file_load_file,
	.media_get_listname = SD_file_get_listname,
	.media_list_init 	= SD_file_list_init,
};

// index = file pos/512
// each time return 512 or less 512
// len is return buffer data size
// buffer is data content
static void *tmp_tftp_buffer;
static int tmp_len = 0;
static void tftp_recv_handler(unsigned char *buffer, int len, unsigned int index)
{
	uint8_t *tmp = (uint8_t *)tmp_tftp_buffer;
	memcpy(&tmp[tmp_len], buffer, len);
	tmp_len += len;
}

tftp tftp_rrq = {
	.recv_handle = tftp_recv_handler,
	.tftp_host = "172.21.34.35",
	.tftp_port = 69,
	.tftp_mode = "octet",
	.tftp_retry_num = 5,
	.tftp_timeout = 2,
	.tftp_op = RRQ,
};

static void tftp_file_loader_init(void *p)
{
	fileloader_ctx_t *ctx = (fileloader_ctx_t *)p;

	ctx->mactx = malloc(sizeof(media_ctx_t));

	ctx->mactx->handler = (void *)&tftp_rrq;

	printf("tftp file loader inited \n\r");
}



static void tftp_file_loader_deinit(void *p)
{
	fileloader_ctx_t *ctx = (fileloader_ctx_t *)p;
	if (ctx->mactx) {
		free(ctx->mactx);
	}

	printf("tftp file loader deinited \n\r");

}

static int tftp_file_load_file(void *p, uint8_t **pFrame, uint32_t *pSize, char *frameFilePath)
{
	media_ctx_t *mactx = (media_ctx_t *)p;
	((tftp *)mactx->handler)->tftp_file_name = frameFilePath;

	printf("tftp file loader start, remote file = %s\n\r", frameFilePath);

	uint8_t *file_buf = (uint8_t *)malloc(DEFAULT_NN_INPUT_LEN);
	if (file_buf == NULL) {
		printf("\r\nfile malloc fail!\r\n");
		return -1;
	}

	tmp_tftp_buffer = (void *)file_buf;
	tmp_len = 0;

	int ret = tftp_client_start((tftp *)mactx->handler);
	if (ret < 0) {
		return -1;
	}

	*pSize = (uint32_t)tmp_len;
	*pFrame = file_buf;

	printf("tftp file loader done, len = %d\n\r", tmp_len);

	return tmp_len;
}

#define TFTP_LIST_BUF_SIZE 640*1024
#include "section_config.h"
SECTION(".ddr.bss")
static char list_file_buf[TFTP_LIST_BUF_SIZE]; //<- move to context
static char *list_curr;
static int skip_line = 0;

// char strigbuf[128];	// inside buffer, "123\n\r456\n\r790\n\r"
// char *curr = stringbuf;
// char *str1 = sgets(&curr);	// should be 123
// char *str2 = sgets(&curr);	// should be 456
char *sgets(char **buf)
{
	char *ret = *buf;
	char *curr = *buf;
	if (*curr == 0)	{
		return NULL;
	}

	while (*curr != '\n' && *curr != '\r') {
		curr++;
	}

	while (*curr == '\n' || *curr == '\r') {
		*curr = 0;
		curr++;
	}

	*buf = curr;

	return ret;
}

char *s_seekline(char *sBuf, int line_num)
{
	char *curr = sBuf;
	for (int i = 0; i < line_num; i++) {
		while (*curr != '\n' && *curr != '\r') {
			curr++;
		}
		while (*curr == '\n' || *curr == '\r') {
			curr++;
		}
	}
	return curr;
}

static int tftp_file_get_listname(char *buf, int size, void *ctx)
{
	char *str = sgets(&list_curr);
	if (str) {
		strncpy(buf, str, size);
		return 0;
	} else {
		return -1;
	}
}

static void *tftp_file_list_init(void *p, char *listname)
{
	media_ctx_t *mactx = (media_ctx_t *)p;
	// read list file into buffer
	((tftp *)mactx->handler)->tftp_file_name = listname;

	memset(list_file_buf, 0, TFTP_LIST_BUF_SIZE);
	tmp_tftp_buffer = (void *)list_file_buf;
	tmp_len = 0;
	list_curr = list_file_buf;

	int ret = tftp_client_start((tftp *)mactx->handler);
	if (ret < 0) {
		return NULL;
	}

	// skip some lines if needed
	list_curr = s_seekline(list_file_buf, skip_line);

	return (void *)list_file_buf;
}

static media_access_t ma_tftp = {
	.media_init 		= tftp_file_loader_init,
	.media_deinit		= tftp_file_loader_deinit,
	.media_load_file 	= tftp_file_load_file,
	.media_get_listname = tftp_file_get_listname,
	.media_list_init    = tftp_file_list_init,
};

/*-----------------------------------------------------------------------------------*/
#include <FtpClient.h>
static NetBuf_t *ftpClientNetBuf = NULL;

static ftp_info_t   ftp_info = {
	.remote_ip = (char *)"172.21.34.35\0                                                  \0",
	.remote_port = 21,
	.remote_dir = (char *)"/dataset\0                                                     \0",
	.remote_user = (char *)"ftpuser\0                                                     \0",
	.remote_pass = (char *)"12345678\0                                                    \0"
};

static void ftp_file_loader_deinit(void *p)
{
	fileloader_ctx_t *ctx = (fileloader_ctx_t *)p;

	if (ctx->mactx) {
		FtpClient *client = (FtpClient *)ctx->mactx->handler;
		if (client) {
			client->ftpClientQuit(ftpClientNetBuf);
		}
		free(ctx->mactx);
	}

	printf("ftp file loader deinited \n\r");

}

static void ftp_file_loader_init(void *p)
{
	fileloader_ctx_t *ctx = (fileloader_ctx_t *)p;

	ctx->mactx = malloc(sizeof(media_ctx_t));

	FtpClient *client = getFtpClient();

	ctx->mactx->handler = (void *)client;

	printf("connecting to remote %s port %d\n\r", ftp_info.remote_ip, ftp_info.remote_port);
	int connect = client->ftpClientConnect(ftp_info.remote_ip, ftp_info.remote_port, &ftpClientNetBuf);

	if (connect == 0) {
		printf("FTP server connect fail");
		ftp_file_loader_deinit(p);
		return;
	}

	printf("user %s pass %s\n\r", ftp_info.remote_user, ftp_info.remote_pass);
	int login = client->ftpClientLogin(ftp_info.remote_user, ftp_info.remote_pass, ftpClientNetBuf);
	if (login == 0) {
		printf("FTP server login fail");
		return;
	}

	printf("change remote dir %s\n\r", ftp_info.remote_dir);
	int chdir = client->ftpClientChangeDir(ftp_info.remote_dir, ftpClientNetBuf);
	if (chdir == 0) {
		printf("FTP server change dir fail");
		return;
	}

	printf("ftp file loader inited \n\r");
}


static int ftp_file_load_file(void *p, uint8_t **pFrame, uint32_t *pSize, char *frameFilePath)
{
	media_ctx_t *mactx = (media_ctx_t *)p;

	FtpClient *client = (FtpClient *)mactx->handler;

	printf("ftp file loader start, remote file = %s\n\r", frameFilePath);

	uint8_t *file_buf = (uint8_t *)malloc(DEFAULT_NN_INPUT_LEN);
	if (file_buf == NULL) {
		printf("\r\nfile malloc fail!\r\n");
		return -1;
	}

	int len = 0;
	int ret = client->ftpClientGetBuf((char *)file_buf, &len, frameFilePath, FTP_CLIENT_BINARY, ftpClientNetBuf);

	*pSize = (uint32_t)len;
	*pFrame = file_buf;

	printf("ftp file loader done, len = %d\n\r", len);

	return len;
}

static int ftp_file_get_listname(char *buf, int size, void *ctx)
{
	char *str = sgets(&list_curr);
	if (str) {
		strncpy(buf, str, size);
		return 0;
	} else {
		return -1;
	}
}

static void *ftp_file_list_init(void *p, char *listname)
{
	media_ctx_t *mactx = (media_ctx_t *)p;
	FtpClient *client = (FtpClient *)mactx->handler;

	memset(list_file_buf, 0, TFTP_LIST_BUF_SIZE);

	int len = 0;
	int ret = client->ftpClientGetBuf(list_file_buf, &len, listname, FTP_CLIENT_BINARY, ftpClientNetBuf);

	if (ret == 0) {
		return NULL;
	}

	// skip some lines if needed
	list_curr = s_seekline(list_file_buf, skip_line);

	return (void *)list_file_buf;
}


static media_access_t ma_ftp = {
	.media_init 		= ftp_file_loader_init,
	.media_deinit		= ftp_file_loader_deinit,
	.media_load_file 	= ftp_file_load_file,
	.media_get_listname = ftp_file_get_listname,
	.media_list_init    = ftp_file_list_init,
};
/*-----------------------------------------------------------------------------------*/

int fileloader_control(void *p, int cmd, int arg)
{
	fileloader_ctx_t *ctx = (fileloader_ctx_t *)p;

	switch (cmd) {
	case CMD_FILELOADER_SET_PARAMS:
		memcpy(&ctx->params, (void *)arg, sizeof(fileloader_params_t));
		break;
	case CMD_FILELOADER_GET_PARAMS:
		memcpy((void *)arg, &ctx->params, sizeof(fileloader_params_t));
		break;
	case CMD_FILELOADER_APPLY:
		fileloader_task_enable(ctx);
		break;
	case CMD_FILELOADER_SET_TEST_FILE_PATH:
		memset(ctx->sd_dataset_file_path_in, 0x00, sizeof(ctx->sd_dataset_file_path_in));
		memcpy((char *)ctx->sd_dataset_file_path_in, (char *)arg, strlen((char *)arg));
		break;
	case CMD_FILELOADER_SET_FILE_NUM:
		ctx->load_file_num = (int)arg;
		break;
	case CMD_FILELOADER_SET_DECODE_PROCESS:
		ctx->decode_in_place = (decode_in_place_t)arg;
		break;
	case CMD_FILELOADER_SET_READ_MODE:
		ctx->read_mode = (int)arg;
		break;
	case CMD_FILELOADER_SET_FILELIST_NAME:
		memset(ctx->file_list_name, 0x00, sizeof(ctx->file_list_name));
		memcpy((char *)ctx->file_list_name, (char *)arg, strlen((char *)arg));
		//ctx->ff = fopen(ctx->file_list_name, "r+");
		break;
	case CMD_FILELOADER_SET_FILELIST_SKIPLINE:
		skip_line = (int)arg;
		break;
	case CMD_FILELOADER_SET_TFTP_MODE:
		ctx->ma = &ma_tftp;
		ctx->ma_mode = MA_TFTP;
		break;
	case CMD_FILELOADER_SET_FTP_MODE:
		ctx->ma = &ma_ftp;
		ctx->ma_mode = MA_FTP;
		break;
	//case CMD_FILELOADER_SET_TFTP_IP: // the same as REMOTE_IP
	case CMD_FILELOADER_SET_REMOTE_IP:
		if (ctx->ma_mode == MA_TFTP) {
			tftp_rrq.tftp_host = (char *)arg;
			printf("tftp host ip : %s\n\r", tftp_rrq.tftp_host);
		}
		if (ctx->ma_mode == MA_FTP) {
			strcpy(ftp_info.remote_ip, (char *)arg);
			printf("ftp host ip : %s\n\r", ftp_info.remote_ip);
		}
		break;
	case CMD_FILELOADER_SET_REMOTE_PORT:
		if (ctx->ma_mode == MA_TFTP) {
			tftp_rrq.tftp_port = arg;
			printf("tftp host port : %s\n\r", tftp_rrq.tftp_port);
		}
		if (ctx->ma_mode == MA_FTP) {
			ftp_info.remote_port = arg;
			printf("ftp host port : %d\n\r", ftp_info.remote_port);
		}
		break;
	case CMD_FILELOADER_SET_REMOTE_DIR:
		if (ctx->ma_mode == MA_FTP) {
			strcpy(ftp_info.remote_dir, (char *)arg);
			printf("ftp host dir : %s\n\r", ftp_info.remote_dir);
		}
		break;
	case CMD_FILELOADER_SET_REMOTE_USER:
		if (ctx->ma_mode == MA_FTP) {
			strcpy(ftp_info.remote_user, (char *)arg);
			printf("ftp host user : %s\n\r", ftp_info.remote_user);
		}
		break;
	case CMD_FILELOADER_SET_REMOTE_PASS:
		if (ctx->ma_mode == MA_FTP) {
			strcpy(ftp_info.remote_pass, (char *)arg);
			printf("ftp host pass : %s\n\r", ftp_info.remote_pass);
		}
		break;
	case CMD_FILELOADER_SET_REMOTE_PARAMS:
		if (ctx->ma_mode == MA_FTP) {
			memcpy(&ftp_info, (void *)arg, sizeof(ftp_info));
			printf("ftp set params\n\r");
		}
		break;
	case CMD_FILELOADER_GET_LOADED_FILE_COUNT:
		*(int *)arg = load_file_count;
		break;
	}

	return 0;
}

int fileloader_handle(void *ctx, void *input, void *output)
{
	return 0;
}

void *fileloader_destroy(void *p)
{
	fileloader_ctx_t *ctx = (fileloader_ctx_t *)p;

	if (ctx) {
		if (ctx->task) {
			vTaskDelete(ctx->task);
			ctx->task = NULL;
		}
		if (ctx->ff) {
			fclose(ctx->ff);
			ctx->ff = NULL;
		}
		if (ctx->ma) {
			if (ctx->ma->media_deinit) {
				ctx->ma->media_deinit(NULL);
			}
		}
		free(ctx);
		ctx = NULL;
	}

	return NULL;
}

void *fileloader_create(void *parent)
{
	fileloader_ctx_t *ctx = malloc(sizeof(fileloader_ctx_t));
	if (!ctx) {
		return NULL;
	}
	memset(ctx, 0, sizeof(fileloader_ctx_t));
	ctx->parent = parent;
	ctx->ma = &ma_sd;
	//ctx->ma = &ma_tftp;
	//ctx->ma = &ma_ftp;

	//SD_file_loader_init();

	return ctx;
}

void *fileloader_new_item(void *p)
{
	(void)p;
	return (void *)malloc(DEFAULT_FILE_LEN);
}

void *fileloader_del_item(void *p, void *d)
{
	(void)p;
	if (d) {
		free(d);
	}
	return NULL;
}

mm_module_t fileloader_module = {
	.create = fileloader_create,
	.destroy = fileloader_destroy,
	.control = fileloader_control,
	.handle = fileloader_handle,

	.new_item = fileloader_new_item,
	.del_item = fileloader_del_item,

	.output_type = MM_TYPE_ASINK | MM_TYPE_ADSP | MM_TYPE_VSINK | MM_TYPE_VDSP,
	.module_type = MM_TYPE_ASRC | MM_TYPE_VSRC,
	.name = "FILE_LOADER"
};

