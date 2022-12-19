#ifndef _IMG_PROCESS_H_
#define _IMG_PROCESS_H_

typedef struct img_s {
	unsigned int width;
	unsigned int height;
	unsigned char *data;
} img_t;

typedef struct rect_s {
	int xmin;
	int ymin;
	int xmax;
	int ymax;
} rect_t;

typedef struct rotate_s {
	int cx, cy;
	float angle;
} rotate_t;

/*
 * brief: resize the planar image
 *
 * [in] im_in : original image
 * [in] roi : roi of original image
 * [out] im_out : output resized image
 */
int img_resize_planar(img_t *im_in, rect_t *roi, img_t *im_out);

/*
 * brief: resize the planar image with stb image api
 *
 * [in] img_in : original image
 * [out] img_out : output resized image
 */
void img_stb_resize_planar(img_t *img_in, img_t *img_out);

/*
 * brief: rotate and scale the image
 *
 * [in] im_in : original image
 * [in] roi : roi of original image
 * [in] rotate_cfg : angle to rotate
 * [out] im_out : output rotated/scaled image
 * [in] aligned_c: aligned center (set it to NULL if not used)
 */
int img_rotation_fix(img_t *im_in, rect_t *roi, rotate_t *rotate_cfg, img_t *im_out, float (*aligned_c)[2]);

/*
 * brief: copy img data by DMA
 *
 * [out] dst : pointer to the destination
 * [in] src : pointer to the source of data
 * [in] size : number of bytes to copy.
 */
void *img_dma_copy(uint8_t *dst, uint8_t *src, uint32_t size);

/*
 * brief: create image
 *
 * [in] w : pointer to the destination
 * [in] h : pointer to the source of data
 * [in] pbuf : pointer to the allocated data buffer. If set it to NULL, memory will be allocated in function
 * [out] ret : created image
 */
img_t img_create_image(int w, int h, uint8_t *pbuf);

/*
 * brief: free image data buffer if allocated
 *
 * [in] im : image with data buffer need to free
 */
void img_free_image(img_t im);

/*
 * brief: scale the input image to output image with padding
 *
 * [in] p_im_in : source image
 * [out] p_im_out : target image
 */
void img_scaled_into_letterbox(img_t *p_im_in, img_t *p_im_out);

#endif /* _IMG_PROCESS_H_ */