#ifndef FFT_64POINT_H
#define FFT_64POINT_H

#ifdef  __cplusplus
extern "C" {
#endif

struct Fft {
	uint32_t din_wl;    /* fft输入数据的总位宽 */
	uint32_t din_fl;    /* fft输入数据的小数位宽 */
	uint32_t dout_wl;    /* fft输出数据的总位宽 */
	uint32_t dout_fl;    /* fft输出数据的小数位宽 */
	int32_t num_point;    /* fft点数 */
	int32_t w;
} ;

void fft_64point_init(struct Fft *obj);
void fft_64point_run(struct Fft *obj, int32_t *din, int32_t *dout);
void fft_64point_test(void);

#ifdef  __cplusplus
}
#endif

#endif
