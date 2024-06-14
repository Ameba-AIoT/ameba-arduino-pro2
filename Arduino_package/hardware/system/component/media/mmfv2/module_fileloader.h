#ifndef _MODULE_FILELOADER_H
#define _MODULE_FILELOADER_H

#include <FreeRTOS.h>
#include <freertos_service.h>
#include <task.h>
#include <stdint.h>

#include "vfs.h"
#include "tftp.h"

#define CMD_FILELOADER_SET_PARAMS               MM_MODULE_CMD(0x00)  // set parameter
#define CMD_FILELOADER_GET_PARAMS               MM_MODULE_CMD(0x01)  // get parameter
#define CMD_FILELOADER_SET_TEST_FILE_PATH       MM_MODULE_CMD(0x02)  // set test file path
#define CMD_FILELOADER_SET_FILE_NUM             MM_MODULE_CMD(0x03)  // set tested file num
#define CMD_FILELOADER_SET_DECODE_PROCESS       MM_MODULE_CMD(0x04)  // set the decode process function before data sent to next module
#define CMD_FILELOADER_SET_READ_MODE            MM_MODULE_CMD(0x05)
#define CMD_FILELOADER_SET_FILELIST_NAME        MM_MODULE_CMD(0x06)
#define CMD_FILELOADER_SET_FILELIST_SKIPLINE    MM_MODULE_CMD(0x07)

#define CMD_FILELOADER_SET_TFTP_MODE		    MM_MODULE_CMD(0x10)
#define CMD_FILELOADER_SET_FTP_MODE		    	MM_MODULE_CMD(0x11)

#define CMD_FILELOADER_SET_TFTP_IP				MM_MODULE_CMD(0x18)
#define CMD_FILELOADER_SET_REMOTE_IP		    MM_MODULE_CMD(0x18)
#define CMD_FILELOADER_SET_REMOTE_PORT		    MM_MODULE_CMD(0x19)
#define CMD_FILELOADER_SET_REMOTE_USER		    MM_MODULE_CMD(0x1a)
#define CMD_FILELOADER_SET_REMOTE_PASS		    MM_MODULE_CMD(0x1b)
#define CMD_FILELOADER_SET_REMOTE_DIR		    MM_MODULE_CMD(0x1c)
#define CMD_FILELOADER_SET_REMOTE_PARAMS	    MM_MODULE_CMD(0x1d)

#define CMD_FILELOADER_GET_LOADED_FILE_COUNT    MM_MODULE_CMD(0x1f)

#define CMD_FILELOADER_APPLY                    MM_MODULE_CMD(0x20)  // for hardware module

#define DEFAULT_G711_LEN        160
#define DEFAULT_AAC_LEN         2048
#define DEFAULT_NN_INPUT_LEN    2560*1440*3*2 //640*640*3

#define DEFAULT_FILE_LEN        DEFAULT_NN_INPUT_LEN

typedef enum {
	SEQUENCE_MODE,  // read file in number sequence
	FILELIST_MODE,  // read the file 1 by 1 which are listed in .txt file
} read_mode_t;

typedef int (*decode_in_place_t)(void *, void *);


typedef struct fileloader_param_s {
	uint32_t codec_id;

} fileloader_params_t;

typedef struct media_ctx_s {
	void *handler;

	void *list_ctx;
} media_ctx_t;

typedef struct media_access_s {
	void (*media_init)(void *);
	void (*media_deinit)(void *);
	void *(*media_list_init)(void *p, char *listname);
	int (*media_load_file)(void *p, uint8_t **frame, uint32_t *size, char *filepath);
	int (*media_get_listname)(char *buf, int size, void *ctx);
} media_access_t;

#define MA_SD	0
#define MA_TFTP	1
#define MA_FTP	2

typedef struct fileloader_ctx_s {
	void *parent;
	TaskHandle_t task;

	fileloader_params_t params;

	char sd_dataset_file_path_in[64];

	int load_file_num;

	decode_in_place_t decode_in_place;

	read_mode_t read_mode;

	int 		   ma_mode;
	media_ctx_t    *mactx;
	media_access_t *ma;

	char file_list_name[64];
	FILE *ff;

} fileloader_ctx_t;

extern mm_module_t fileloader_module;

#endif