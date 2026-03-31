/******************************************************************************
*
* Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
*
******************************************************************************/

#include <stdint.h>
#include "mmf2_module.h"
#include "module_uvcd.h"
#include "uvc/inc/usbd_uvc_desc.h"
//------------------------------------------------------------------------------
#define num 1

struct uvc_format *uvc_format_ptr = NULL;

static struct usbd_uvc_buffer uvc_payload[num];



void uvcd_change_format_resolution(void *ctx)
{
	//struct uvc_format *uvc_forma_ctx = (struct uvc_format *)ctx;
	//rtw_up_senma_from_isr(&uvc_format_ptr->uvcd_change_sema);
	rtw_up_sema_from_isr(&uvc_format_ptr->uvcd_change_sema);
}

void *uvcd_create(void *parent)
{
	//struct uvc_dev *uvc_ctx = get_private_usbd_uvc();
	int i = 0;
	int status = 0;
	uvcd_ctx_t *uvc_ctx = malloc(sizeof(uvcd_ctx_t));

	if (!uvc_ctx)	{
		return NULL;
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

	if (usbd_uvc_init() < 0) {
		printf("usbd uvc init error\r\n");
		goto exit;
	}


	for (i = 0; i < num; i++) {
		uvc_video_put_out_stream_queue(&uvc_payload[i]);
	}
	//uvc_ctx->change_parm_cb = uvcd_change_format_resolution;
	usbd_uvc_set_change_parm_cb((int)uvcd_change_format_resolution);
	return (void *)uvc_ctx;
	/* return (void *)uvc_ctx; */
exit:
	if (uvc_ctx) {
		free(uvc_ctx);
	}
	return NULL;
}

int uvcd_handle(void *p, void *input, void *output)
{
	int ret = 0;
	//uvcd_ctx *ctx = (uvcd_ctx *) p;
	struct uvc_dev *uvc_ctx = (struct uvc_dev *)p;
	mm_queue_item_t *input_item = (mm_queue_item_t *)input;
	struct usbd_uvc_buffer *payload = NULL;//&rtp_payload;
	//printf("input address = %x\r\n\r\n",input_item->data_addr);


	//printf("uvcd_mod_handle\r\n");
	if (usbd_uvc_get_status() == 0) {
		goto end;
	}

	do {
		payload = uvc_video_out_stream_queue();
		if (payload == NULL) {
			printf("NULL\r\n");
			vTaskDelay(1);
		}
	} while (payload == NULL);


	payload->mem = (unsigned char *) input_item->data_addr;
	payload->bytesused = input_item->size;
	uvc_video_put_in_stream_queue(payload);
	//rtw_down_sema(&uvc_ctx->video.output_queue_sema);
	usbd_wait_frame_down();
end:
	return ret;
}

int uvcd_control(void *p, int cmd, int arg)
{
	struct uvc_dev *uvc_ctx = (struct uvc_dev *)p;
	switch (cmd) {
	case CMD_UVCD_CALLBACK_SET://Prot A and B
		usbd_uvc_ext_set_cb(arg);//uvc_ctx->uvcd_ext_set_cb = (void (*)(void *, unsigned int))arg;
		break;
	case CMD_UVCD_CALLBACK_GET:
		usbd_uvc_ext_get_cb(arg);
		//uvc_ctx->uvcd_ext_get_cb = (void (*)(void *, unsigned int))arg;
		break;
	case CMD_UVCD_STOP:
		usbd_uvc_stop();
		break;
	}
	return 0;
}

void *uvcd_destroy(void *p)
{
	// struct uvc_dev *uvc_ctx = (struct uvc_dev *)p;
	usbd_uvc_deinit();
	extern void _usb_deinit(void);
	_usb_deinit();

	//if(ctx)	free(ctx);
	return NULL;
}

mm_module_t uvcd_module = {
	.create = uvcd_create,
	.destroy = uvcd_destroy,
	.control = uvcd_control,
	.handle = uvcd_handle,

	.new_item = NULL,
	.del_item = NULL,

	.output_type = MM_TYPE_NONE,     // no output
	.module_type = MM_TYPE_VSINK,    // module type is video algorithm
	.name = "UVCD"
};