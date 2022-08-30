#ifndef ISP_OSD_EXAMPLE_H_
#define ISP_OSD_EXAMPLE_H_

#define RECT_NUM 6

struct result_obj {
	int idx;
	int class;
	int score;
	int left;
	int top;
	int right;
	int bottom;
};

struct result_frame {
	int num;
	struct result_obj obj[6];
};

int osd_update_rect_result(struct result_frame nn_results);
int osd_get_status(void);
int osd_set_tag(int tag_number, char **tag);
void example_isp_osd(int idx, int ch_id, int txt_w, int txt_h, int scale);

#endif //ISP_OSD_EXAMPLE_H_