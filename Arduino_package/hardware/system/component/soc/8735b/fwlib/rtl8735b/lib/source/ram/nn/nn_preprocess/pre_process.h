#include "nn_api.h"

int nn_resize_rgb888(
	cvImage  *src,
	cvImage  *dst,
	cvRect_S *roi,
	unsigned int reverse_channel
);

