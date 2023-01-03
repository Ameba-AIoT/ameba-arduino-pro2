#ifndef __HIFI_RADIO_INTERRUPT_H__
#define __HIFI_RADIO_INTERRUPT_H__
#include "ameba_gdma.h"
#include "tx_oqpsk.h"
extern u8 GDMA_IrqNum[];
extern uint32_t  g_rx_data[];
extern volatile u32 g_irq_cnt;

#if 1
#define RX_CCA_PD_LOOP_CNT 8
#define TX_GDMA_BLOCK_SIZE 32    //128 / 64 / 32 / 16 / 4
#define TX_GDMA_BLOCK_DEPTH 8     //32 / 16 / 8  / 4  / 1 / TX_GDMA_BLOCK_SIZE >> GDMA_InitStruct->GDMA_SrcDataWidth
#define RX_GDMA_BLOCK_SIZE 128    //128 / 64 / 32 / 16 / 4
#define RX_GDMA_BLOCK_DEPTH 32    //32 / 16 / 8  / 4  / 1 / RX_GDMA_BLOCK_SIZE >> GDMA_InitStruct->GDMA_SrcDataWidth
#define RX_CONVERT_BUF_SIZE_PER_DMA 96 // RX_GDMA_BLOCK_DEPTH*3
#else
#define RX_CCA_PD_LOOP_CNT 4
#define TX_GDMA_BLOCK_SIZE 32    //128 / 64 / 32 / 16 / 4
#define TX_GDMA_BLOCK_DEPTH 8     //32 / 16 / 8  / 4  / 1 / TX_GDMA_BLOCK_SIZE >> GDMA_InitStruct->GDMA_SrcDataWidth
#define RX_GDMA_BLOCK_SIZE 64    //128 / 64 / 32 / 16 / 4
#define RX_GDMA_BLOCK_DEPTH 16    //32 / 16 / 8  / 4  / 1 / RX_GDMA_BLOCK_SIZE >> GDMA_InitStruct->GDMA_SrcDataWidth
#define RX_CONVERT_BUF_SIZE_PER_DMA 48 // RX_GDMA_BLOCK_DEPTH*3
#endif

#define RX_DATA_SIZE 19200 //600 blocks * 128byte  19200 == sample_size

void run_gdma_tests(void);
void mem_dump(uint32_t *Data, int32_t n4byte);

void gdma_start_multiblock_rx(void);
void gdma_start_multiblock_tx(uint32_t block_num);
void gdma_init_multiblock_rx(u32 src_addr, u32 dst_addr, u32 block_size, u32 block_num);
void gdma_multiblock_test(void);
uint32_t gdma_get_multiblock_rx_idx(void);
void gdma_init_multiblock_tx(uint32_t src_addr, uint32_t dst_addr, uint32_t block_size);
void gdma_start_multiblock_tx(uint32_t block_num);


#endif /*  */
