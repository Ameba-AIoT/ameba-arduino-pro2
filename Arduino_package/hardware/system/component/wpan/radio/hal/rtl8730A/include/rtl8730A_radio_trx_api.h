#ifndef RTL8730A_ZIGBEE_TRX_API_H
#define RTL8730A_ZIGBEE_TRX_API_H

#ifdef  _cplusplus
extern "C" {
#endif
#include "ameba_soc.h"


#ifdef CONFIG_RLE1080_A_CUT
#define RX_CCA_PD_LOOP_CNT 6
	/*all these use macro to decrease computation*/
#define TX_GDMA_BLOCK_SIZE 64    //64 / 32 / 16 / 4
#define TX_GDMA_BLOCK_DEPTH 16   //16 / 8  / 4  / 1 / TX_GDMA_BLOCK_SIZE >> GDMA_InitStruct->GDMA_SrcDataWidth
#define RX_GDMA_BLOCK_SIZE 64    //64 / 32 / 16 / 4
#define RX_GDMA_BLOCK_DEPTH 16   //16 / 8  / 4  / 1 / RX_GDMA_BLOCK_SIZE >> GDMA_InitStruct->GDMA_SrcDataWidth
#define RX_CONVERT_BUF_SIZE_PER_DMA 48 // RX_GDMA_BLOCK_DEPTH*3
#else
#define RX_CCA_PD_LOOP_CNT 12
	/*all these use macro to decrease computation*/
#define TX_GDMA_BLOCK_SIZE 32    //128 / 64 / 32 / 16 / 4
#define TX_GDMA_BLOCK_DEPTH 8     //32 / 16 / 8  / 4  / 1 / TX_GDMA_BLOCK_SIZE >> GDMA_InitStruct->GDMA_SrcDataWidth
#define RX_GDMA_BLOCK_SIZE 128    //128 / 64 / 32 / 16 / 4
#define RX_GDMA_BLOCK_DEPTH 32    //32 / 16 / 8  / 4  / 1 / RX_GDMA_BLOCK_SIZE >> GDMA_InitStruct->GDMA_SrcDataWidth
#define RX_CONVERT_BUF_SIZE_PER_DMA 96 // RX_GDMA_BLOCK_DEPTH*3
#endif

#define OQPSK_TIME_DEBUG 0
#define RX_PKT_RECV_TIME_DEBUG 0
#define RX_MODULE_TIME_DEBUG 0

#define RX_ERR_PKT_DEBUG 0  // record error packet index

#define RX_PD_DEBUG 0
#define RX_DAGC_DEBUG 0
#define RX_CFO_DEBUG 0
#define RX_SBD_DEBUG 0
#define RX_CE_DEBUG 0
#define RX_INTP_DEBUG 0
#define RX_PHASE_DEBUG 0
#define RX_ML_DEBUG 0

#define RX_DATA_DUMP 0
#define RX_SFD_DUMP 0
#define RX_CRC_FAIL_DUMP 0
#define RX_CRC_OK_DUMP 0

	void rtl8730A_zgb_tx_flow(void);
	void rtl8730A_zgb_rx_flow(void);
	//void hal_radio_reg_dump(void);


#ifdef  _cplusplus
}
#endif
#endif

