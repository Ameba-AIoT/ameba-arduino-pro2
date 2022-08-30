#ifndef _MODULE_FILESAVER_H
#define _MODULE_FILESAVER_H

#include <FreeRTOS.h>
#include <freertos_service.h>
#include <task.h>
#include <stdint.h>

#include "module_vipnn.h"

#define CMD_FILESAVER_SET_PARAMS            MM_MODULE_CMD(0x00)  // set parameter
#define CMD_FILESAVER_GET_PARAMS            MM_MODULE_CMD(0x01)  // get parameter
#define CMD_FILESAVER_SET_SAVE_FILE_PATH    MM_MODULE_CMD(0x02)  // set save file path

#define CMD_FILESAVER_SET_TYPE_HANDLER      MM_MODULE_CMD(0x10)  // set type handler function
#define CMD_FILESAVER_APPLY                 MM_MODULE_CMD(0x20)  // for hardware module

typedef void (*type_handler_t)(char *, uint32_t, uint32_t);


typedef struct filesaver_param_s {
	uint32_t dummy;

} filesaver_params_t;

typedef struct filesaver_ctx_s {
	void *parent;

	filesaver_params_t params;

	char output_file_path[64];

	type_handler_t type_handler;

} filesaver_ctx_t;

extern mm_module_t filesaver_module;

#endif