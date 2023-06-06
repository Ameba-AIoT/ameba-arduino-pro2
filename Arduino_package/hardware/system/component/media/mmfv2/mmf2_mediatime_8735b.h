#ifndef MMF2_MEDIATIME_8735B_H
#define MMF2_MEDIATIME_8735B_H

// use system time is only test on the 8735B
uint64_t mm_read_mediatime_us_fromisr(void);
uint32_t mm_read_mediatime_ms_fromisr(void);

uint64_t mm_read_mediatime_us(void);
uint32_t mm_read_mediatime_ms(void);

void mm_set_mediatime_in_us(uint64_t mediatime_in_us);
void mm_set_mediatime_in_ms(uint32_t mediatime_in_ms);

#endif