#ifndef RTL8730A_ZIGBEE_GDMA_H
#define RTL8730A_ZIGBEE_GDMA_H

#ifdef  _cplusplus
extern "C" {
#endif

#include "ameba_soc.h"

	void gdma_init_tx(void);
	void gdma_init_rx(void);
	void gdma_cpy_tx(u32 src_addr, u32 src_offset, u32 dst_addr, u32 dst_offset, u32 cpy_len);
	void gdma_cpy_rx(u32 src_addr, u32 src_offset, u32 dst_addr, u32 dst_offset, u32 cpy_len);
	void data_convert_test(void);

	static __inline void zgb_rx_data_convert(uint32_t *src_data, int32_t *dst_data_re, int32_t *dst_data_im, int32_t convert_len)

	{
		int32_t idx_1 = 0;
		for (int32_t i = 0; i < convert_len; i++) {
			dst_data_re[idx_1] = ((int32_t)((src_data[i] & 0x3ff) << 22)) >> 22;  //I_0
			dst_data_im[idx_1++] = ((int32_t)((src_data[i] & 0xffc00) << 12)) >> 22;  //Q_0

			dst_data_re[idx_1] = ((int32_t)((src_data[i++] & 0x3ff00000) << 2)) >> 22;  //I_1
			dst_data_im[idx_1++] = ((int32_t)((src_data[i] & 0x3ff) << 22)) >> 22;  //Q_1

			dst_data_re[idx_1] = ((int32_t)((src_data[i] & 0xffc00) << 12)) >> 22;  //I_2
			dst_data_im[idx_1++] = ((int32_t)((src_data[i] & 0x3ff00000) << 2)) >> 22;  //Q_2
		}
		return;
	}

#ifdef  _cplusplus
}
#endif
#endif

