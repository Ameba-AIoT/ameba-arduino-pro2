#ifndef _MODULE_FILELOADER_H
#define _MODULE_FILELOADER_H

#include <FreeRTOS.h>
#include <freertos_service.h>
#include <task.h>
#include <stdint.h>

#define CMD_FILELOADER_SET_PARAMS           MM_MODULE_CMD(0x00)  // set parameter
#define CMD_FILELOADER_GET_PARAMS           MM_MODULE_CMD(0x01)  // get parameter
#define CMD_FILELOADER_SET_TEST_FILE_PATH   MM_MODULE_CMD(0x02)  // set test file path
#define CMD_FILELOADER_SET_FILE_NUM         MM_MODULE_CMD(0x03)  // set tested file num
#define CMD_FILELOADER_SET_DECODE_PROCESS   MM_MODULE_CMD(0x04)  // set the decode process function before data sent to next module

#define CMD_FILELOADER_APPLY                MM_MODULE_CMD(0x20)  // for hardware module

#define DEFAULT_G711_LEN        160
#define DEFAULT_AAC_LEN         2048
#define DEFAULT_NN_INPUT_LEN    640*640*3

#define DEFAULT_FILE_LEN        DEFAULT_NN_INPUT_LEN

typedef int (*decode_in_place_t)(void *, void *);


typedef struct fileloader_param_s {
	uint32_t type;
	uint32_t codec_id;
	uint32_t test_data_width;
	uint32_t test_data_height;

} fileloader_params_t;


typedef struct fileloader_ctx_s {
	void *parent;
	TaskHandle_t task;

	fileloader_params_t params;

	char sd_dataset_file_path_in[64];

	int load_file_num;

	decode_in_place_t decode_in_place;

} fileloader_ctx_t;

extern mm_module_t fileloader_module;

#endif