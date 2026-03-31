/******************************************************************************
*
* Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
*
******************************************************************************/
#include <stdint.h>
#include "platform_stdlib.h"
#include "mmf2_module.h"
#include "module_filesaver.h"

/*-----------------------------------------------------------------------------------*/

int filesaver_handle(void *p, void *input, void *output)
{
	filesaver_ctx_t *ctx = (filesaver_ctx_t *)p;

	mm_queue_item_t *input_item = (mm_queue_item_t *)input;

	if (strlen(ctx->output_file_path) != 0) {
		ctx->type_handler(ctx->output_file_path, input_item->data_addr, input_item->size);
	} else {
		ctx->type_handler(input_item->name, input_item->data_addr, input_item->size);
	}

	return 0;
}

/*-----------------------------------------------------------------------------------*/

int filesaver_control(void *p, int cmd, int arg)
{
	filesaver_ctx_t *ctx = (filesaver_ctx_t *)p;

	switch (cmd) {
	case CMD_FILESAVER_SET_PARAMS:
		memcpy(&ctx->params, (void *)arg, sizeof(filesaver_params_t));
		break;
	case CMD_FILESAVER_GET_PARAMS:
		memcpy((void *)arg, &ctx->params, sizeof(filesaver_params_t));
		break;
	case CMD_FILESAVER_SET_SAVE_FILE_PATH:
		memset(ctx->output_file_path, 0x00, sizeof(ctx->output_file_path));
		memcpy((char *)ctx->output_file_path, (char *)arg, strlen((char *)arg));
		break;
	case CMD_FILESAVER_SET_TYPE_HANDLER:
		ctx->type_handler = (type_handler_t)arg;
		break;
	case CMD_FILESAVER_APPLY:
		// do nothing
		break;
	}
	return 0;
}

void *filesaver_destroy(void *p)
{
	filesaver_ctx_t *ctx = (filesaver_ctx_t *)p;

	if (ctx) {
		free(ctx);
	}

	return NULL;
}

void *filesaver_create(void *parent)
{
	filesaver_ctx_t *ctx = malloc(sizeof(filesaver_ctx_t));
	if (!ctx) {
		return NULL;
	}
	memset(ctx, 0, sizeof(filesaver_ctx_t));

	ctx->parent = parent;

	return ctx;
}

mm_module_t filesaver_module = {
	.create = filesaver_create,
	.destroy = filesaver_destroy,
	.control = filesaver_control,
	.handle = filesaver_handle,

	.new_item = NULL,
	.del_item = NULL,

	.output_type = MM_TYPE_NONE,
	.module_type = MM_TYPE_AVSINK,
	.name = "FILE_SAVER"
};
