#ifndef _SSD_POST_PROCESS_H_
#define _SSD_POST_PROCESS_H_

#ifndef max
#define max(a,b)    (((a) > (b)) ? (a) : (b))
#endif
#ifndef min
#define min(a,b)    (((a) < (b)) ? (a) : (b))
#endif

void nn_post_process_detect(
	unsigned char id_model_sel,
	float *loc_val,
	float *conf_val,
	float *detect_result,
	int   *detect_obj_num
);

void nn_display_results(
	unsigned char id_model_sel,
	float   *detect_result,
	int     *detect_obj_num
);


#endif
