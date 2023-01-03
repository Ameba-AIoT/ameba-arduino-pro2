#ifndef _HAL_DRAM_SCAN_H_
#define _HAL_DRAM_SCAN_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define DRAM_MEM_BASE 0x70000000
#define DRAM_SCAN 0

#if DRAM_SCAN
uint8_t dram_normal_patterns(uint32_t dram_start, uint32_t dram_size, uint32_t area_size);
uint8_t dram_addr_rot(uint32_t dram_start, uint32_t dram_size, uint32_t area_size);
uint8_t dram_com_addr_rot(uint32_t dram_start, uint32_t dram_size, uint32_t area_size);
uint8_t dram_byte_access(uint32_t dram_start, uint32_t dram_size, uint32_t area_size);
uint8_t dram_half_word_access(uint32_t dram_start, uint32_t dram_size, uint32_t area_size);
uint8_t dram_walking_of_1(uint32_t dram_start, uint32_t dram_size, uint32_t area_size);
uint8_t dram_walking_of_0(uint32_t dram_start, uint32_t dram_size, uint32_t area_size);
uint8_t memcpy_test(uint32_t dram_start, uint32_t dram_size, uint32_t area_size);
uint8_t dram_access_test(void);
uint8_t dram_access_long_run_test(void);
void dram_odt_alwayson(void);
void dram_scan_rd_dly(u32 reg_index, u32 byte_index);
void dram_scan_rd_dly(u32 reg_index, u32 byte_index);
void dram_calibration_dck_hold_map(void);
void dram_calibration_dck_setup_map(void);
void dram_calibration_dcs_hold_map(void);
void dram_calibration_dcs_setup_map(void);
void dram_calibration_dqs_map(void);
void dram_calibration_dq_map(void);
void dram_calibration_rx_dqsen_map(void);
void dram_calibration_rx_fifo_map(void);
void dram_calibration_rx_dq_map(void);
void dram_calibration_tx_dq_map(void);
#endif
void dram_r480_calibration(u8 dram_type);
void dram_zq_calibration(u8 dram_type);
void dram_set_pll_frequency(u32 ddr_freq, unsigned short *pll_table);
void dram_init_clk_frequency_dss(uint32_t ddr_freq, uint32_t down_spread_percent);
#endif

