#include <platform_opts.h>
#include <build_info.h>
#include "hal_osd_util.h"
#include "osd_pict_custom.h"
#include "osd_api.h"
#include "isp_osd_example.h"

static osd_pict_st posd2_pic_0, posd2_pic_1, posd2_pic_2;
static void init_osd_bitmap_pos(osd_pict_st *bmp_info, int chn_id, uint32_t start_x, uint32_t start_y, uint32_t width, uint32_t height)
{
	bmp_info->chn_id = chn_id;
	bmp_info->osd2.start_x = start_x;
	bmp_info->osd2.start_y = start_y;
	bmp_info->osd2.end_x = bmp_info->osd2.start_x + width;
	bmp_info->osd2.end_y = bmp_info->osd2.start_y + height;
}
static void init_osd_bitmap_blk(osd_pict_st *bmp_info, int blk_idx, enum rts_osd2_blk_fmt blk_fmt, uint32_t clr_1bpp)
{
	bmp_info->osd2.blk_idx = blk_idx;
	bmp_info->osd2.blk_fmt = blk_fmt;
	bmp_info->osd2.color_1bpp = clr_1bpp;//0xAABBGGRR
}
static void init_osd_bitmap_buf(osd_pict_st *bmp_info, uint8_t *buf, uint32_t buf_len)
{
	bmp_info->osd2.buf = buf;
	bmp_info->osd2.len = buf_len;
}
static const int ach_id[5] = {0, 1, 2, 3, 4};
void isp_osd_lite(int ch_id)
{
	int ch = ch_id;
	printf("Text/Logo OSD Test\r\n");

	printf("[osd] Heap available:%d\r\n", xPortGetFreeHeapSize());
	rts_osd_init(ch, 8, 16, (int)(8.0f * 3600));

	if (ch == 0) {
		init_osd_bitmap_pos(&posd2_pic_0, ch, 150, 200, PICT4_WIDTH, PICT4_HEIGHT);
		init_osd_bitmap_pos(&posd2_pic_1, ch, 150 + PICT4_WIDTH + 50, 200, PICT3_WIDTH, PICT3_HEIGHT);
		init_osd_bitmap_pos(&posd2_pic_2, ch, 150 + PICT4_WIDTH + 50 + PICT3_WIDTH + 50, 200, PICT2_WIDTH, PICT2_HEIGHT);
	} else if (ch == 1) {
		init_osd_bitmap_pos(&posd2_pic_0, ch, 150 + PICT4_WIDTH + 50 + PICT3_WIDTH + 50, 200, PICT4_WIDTH, PICT4_HEIGHT);
		init_osd_bitmap_pos(&posd2_pic_1, ch, 150, 300, PICT3_WIDTH, PICT3_HEIGHT);
		init_osd_bitmap_pos(&posd2_pic_2, ch, 150 + PICT4_WIDTH + 50, 400, PICT2_WIDTH, PICT2_HEIGHT);
	} else if (ch == 2) {
		init_osd_bitmap_pos(&posd2_pic_0, ch, 150 + PICT4_WIDTH + 50, 200, PICT4_WIDTH, PICT4_HEIGHT);
		init_osd_bitmap_pos(&posd2_pic_1, ch, 150 + PICT4_WIDTH + 50 + PICT3_WIDTH + 50, 350, PICT3_WIDTH, PICT3_HEIGHT);
		init_osd_bitmap_pos(&posd2_pic_2, ch, 150, 450, PICT2_WIDTH, PICT2_HEIGHT);
	}
	init_osd_bitmap_blk(&posd2_pic_0, 2, PICT4_BLK_FMT, 0);
	init_osd_bitmap_buf(&posd2_pic_0, PICT4_NAME, PICT4_SIZE);
	init_osd_bitmap_blk(&posd2_pic_1, 3, PICT3_BLK_FMT, 0);
	init_osd_bitmap_buf(&posd2_pic_1, PICT3_NAME, PICT3_SIZE);
	init_osd_bitmap_blk(&posd2_pic_2, 4, PICT2_BLK_FMT, 0x000000FF);
	init_osd_bitmap_buf(&posd2_pic_2, PICT2_NAME, PICT2_SIZE);

	rts_osd_set_info(rts_osd2_type_pict, &posd2_pic_0);
	rts_osd_set_info(rts_osd2_type_pict, &posd2_pic_1);
	rts_osd_set_info(rts_osd2_type_pict, &posd2_pic_2);

	printf("[osd] Heap available:%d\r\n", xPortGetFreeHeapSize());

	if (xTaskCreate(rts_osd_task, "OSD", 10 * 1024, (void *)(ach_id + ch), tskIDLE_PRIORITY + 1, NULL) != pdPASS) {
		printf("\n\r%s xTaskCreate failed", __FUNCTION__);
	}
}
