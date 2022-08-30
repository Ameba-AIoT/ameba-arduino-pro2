/*
 *-----------------------------------------------------------------------------
 * The confidential and proprietary information contained in this file may
 * only be used by a person authorised under and to the extent permitted
 * by a subsisting licensing agreement from ARM Limited.
 *
 *            (C) COPYRIGHT 2011-2014  ARM Limited.
 *                ALL RIGHTS RESERVED
 *
 * This entire notice must be reproduced on all copies of this file
 * and copies of this file may only be made by a person if such person is
 * permitted to do so under the terms of a subsisting license agreement
 * from ARM Limited.
 *
 *      SVN Information
 *
 *      Checked In          : $Date: 2014-02-10 14:26:41 +0000 (Mon, 10 Feb 2014) $
 *
 *      Revision            : $Revision: 269837 $
 *
 *      Release Information : CORTEX-M7-r1p0-00eac0
 *-----------------------------------------------------------------------------
 */

#ifndef __TM9_CP3_H__
#define __TM9_CP3_H__

#ifdef __cplusplus
extern "C" {
#endif
#include "basic_types.h"
#include "hal.h"

/******************************************************************************/
/*                  V8M TM9 CP3 registers structures                        */
/******************************************************************************/

/*----------------------- Embedded Trace Macrocell ---------------------------*/
typedef struct {
	__IOM uint32_t revision_nymber_reg;             /*!< Offset: 0x000  Revision Number Register                                       */

	union {
		__IOM uint32_t cpu_number_reg;                /*!< Offset: 0x004  CPU Number Register                                        */

		struct {
			__IOM uint32_t cfg_cpu_num : 10;
		} cp3_number_reg_b;
	} ;

	__IOM uint32_t actlr1;                            /*!< Offset: 0x008                                         */
	__IOM uint32_t actlr2;                            /*!< Offset: 0x00C                                         */

	union {
		__IOM uint32_t cp3_control0_reg;                /*!< Offset: 0x010  CP3 Control Register 0 (CNTCTRL0)                               */

		struct {
			__IOM uint32_t lo_cunt0_event_id : 8;
			__IOM uint32_t lo_cunt1_event_id : 8;
			__IOM uint32_t lo_cunt2_event_id : 8;
			__IOM uint32_t lo_cunt3_event_id : 8;
		} cp3_control0_reg_b;
	} ;

	union {
		__IOM uint32_t cp3_control1_reg;                /*!< Offset: 0x014  CP3 Control Register 1 (CNTCTRL1)                               */

		struct {
			__IOM uint32_t hi_cunt0_event_id : 8;
			__IOM uint32_t hi_cunt1_event_id : 8;
			__IOM uint32_t hi_cunt2_event_id : 8;
			__IOM uint32_t hi_cunt3_event_id : 8;
		} cp3_control1_reg_b;
	} ;

	union {
		__IOM uint32_t cp3_control2_reg;                /*!< Offset: 0x018  CP3 Control Register 2 (CNTCTRL2)                               */

		struct {
			__IOM uint32_t lo_cunt0_dual_mode_en : 1;
			__IOM uint32_t lo_cunt1_dual_mode_en : 1;
			__IOM uint32_t lo_cunt2_dual_mode_en : 1;
			__IOM uint32_t lo_cunt3_dual_mode_en : 1;
			__IOM uint32_t cnt_idx : 3;
			__IOM uint32_t rsvd: 9;
			__IOM uint32_t counter_en: 1;
		} cp3_control2_reg_b;
	} ;

	__IOM uint32_t cp3_data;                           /*!< Offset: 0x01C  CP3 Data Register (CNTDATA)                                       */

} CP3_Type;

#define CP3_CNT0_LO_CUNT0_Pos            0                                      /*!< CP3 CONTROL0 LOW COUNT EVENT SETTING: EVENT of Low Counter0 Position            */
#define CP3_CNT0_LO_CUNT0_Msk            (0xFFUL << CP3_CNT0_LO_CUNT0_Pos)      /*!< CP3 CONTROL0 LOW COUNT EVENT SETTING: EVENT of Low Counter0 Mask                */

#define CP3_CNT0_LO_CUNT1_Pos            8                                      /*!< CP3 CONTROL0 LOW COUNT EVENT SETTING: EVENT of Low Counter1 Position            */
#define CP3_CNT0_LO_CUNT1_Msk            (0xFFUL << CP3_CNT0_LO_CUNT1_Pos)      /*!< CP3 CONTROL0 LOW COUNT EVENT SETTING: EVENT of Low Counter1 Mask                */

#define CP3_CNT0_LO_CUNT2_Pos            16                                     /*!< CP3 CONTROL0 LOW COUNT EVENT SETTING: EVENT of Low Counter2 Position            */
#define CP3_CNT0_LO_CUNT2_Msk            (0xFFUL << CP3_CNT0_LO_CUNT2_Pos)      /*!< CP3 CONTROL0 LOW COUNT EVENT SETTING: EVENT of Low Counter2 Mask                */

#define CP3_CNT0_LO_CUNT3_Pos            24                                     /*!< CP3 CONTROL0 LOW COUNT EVENT SETTING: EVENT of Low Counter3 Position            */
#define CP3_CNT0_LO_CUNT3_Msk            (0xFFUL << CP3_CNT0_LO_CUNT3_Pos)      /*!< CP3 CONTROL0 LOW COUNT EVENT SETTING: EVENT of Low Counter4 Mask                */

#define CP3_CNT1_HI_CUNT0_Pos            0                                      /*!< CP3 CONTROL1 HIGH COUNT EVENT SETTING: EVENT of High Counter0 Position            */
#define CP3_CNT1_HI_CUNT0_Msk            (0xFFUL << CP3_CNT1_HI_CUNT0_Pos)      /*!< CP3 CONTROL1 HIGH COUNT EVENT SETTING: EVENT of High Counter0 Mask                */

#define CP3_CNT1_HI_CUNT1_Pos            8                                      /*!< CP3 CONTROL1 HIGH COUNT EVENT SETTING: EVENT of High Counter1 Position            */
#define CP3_CNT1_HI_CUNT1_Msk            (0xFFUL << CP3_CNT1_HI_CUNT1_Pos)      /*!< CP3 CONTROL1 HIGH COUNT EVENT SETTING: EVENT of High Counter1 Mask                */

#define CP3_CNT1_HI_CUNT2_Pos            16                                     /*!< CP3 CONTROL1 HIGH COUNT EVENT SETTING: EVENT of High Counter2 Position            */
#define CP3_CNT1_HI_CUNT2_Msk            (0xFFUL << CP3_CNT1_HI_CUNT2_Pos)      /*!< CP3 CONTROL1 HIGH COUNT EVENT SETTING: EVENT of High Counter2 Mask                */

#define CP3_CNT1_HI_CUNT3_Pos            24                                     /*!< CP3 CONTROL1 HIGH COUNT EVENT SETTING: EVENT of High Counter3 Position            */
#define CP3_CNT1_HI_CUNT3_Msk            (0xFFUL << CP3_CNT1_HI_CUNT3_Pos)      /*!< CP3 CONTROL1 HIGH COUNT EVENT SETTING: EVENT of High Counter4 Mask                */

#define CP3_CNT2_COUNTER_EN_Pos          16                                     /*!< CP3 CONTROL2 COUNTER ENABLE: Counter Enable Position            */
#define CP3_CNT2_COUNTER_EN_Msk          (0x1UL << CP3_CNT2_COUNTER_EN_Pos)     /*!< CP3 CONTROL2 COUNTER ENABLE: Counter Enable Mask                */

#define CP3_CNT2_CNT_IDX_Pos             4                                      /*!< CP3 CONTROL2 COUNTER ENABLE: Counter Enable Position            */
#define CP3_CNT2_CNT_IDX_Msk             (0x7UL << CP3_CNT2_CNT_IDX_Pos)        /*!< CP3 CONTROL2 COUNTER ENABLE: Counter Enable Mask                */

#define CP3_CNT2_CNT3_DUALMODE_Pos       3                                      /*!< CP3 CONTROL2 COUNTER3 DUAL MODE ENABLE: Counter3 Dual Mode Enable Position            */
#define CP3_CNT2_CNT3_DUALMODE_Msk       (0x1UL << CP3_CNT2_CNT3_DUALMODE_Pos)  /*!< CP3 CONTROL2 COUNTER3 DUAL MODE ENABLE: Counter3 Dual Mode Enable Mask                */

#define CP3_CNT2_CNT2_DUALMODE_Pos       2                                      /*!< CP3 CONTROL2 COUNTER3 DUAL MODE ENABLE: Counter2 Dual Mode Enable Position            */
#define CP3_CNT2_CNT2_DUALMODE_Msk       (0x1UL << CP3_CNT2_CNT2_DUALMODE_Pos)  /*!< CP3 CONTROL2 COUNTER3 DUAL MODE ENABLE: Counter2 Dual Mode Enable Mask                */

#define CP3_CNT2_CNT1_DUALMODE_Pos       1                                      /*!< CP3 CONTROL2 COUNTER3 DUAL MODE ENABLE: Counter1 Dual Mode Enable Position            */
#define CP3_CNT2_CNT1_DUALMODE_Msk       (0x1UL << CP3_CNT2_CNT1_DUALMODE_Pos)  /*!< CP3 CONTROL2 COUNTER3 DUAL MODE ENABLE: Counter1 Dual Mode Enable Mask                */

#define CP3_CNT2_CNT0_DUALMODE_Pos       0                                      /*!< CP3 CONTROL2 COUNTER3 DUAL MODE ENABLE: Counter0 Dual Mode Enable Position            */
#define CP3_CNT2_CNT0_DUALMODE_Msk       (0x1UL << CP3_CNT2_CNT0_DUALMODE_Pos)  /*!< CP3 CONTROL2 COUNTER3 DUAL MODE ENABLE: Counter0 Dual Mode Enable Mask                */

/******************************************************************************/
/*          CoreSight and other Peripheral memory map                         */
/******************************************************************************/
/* CoreSight Components */
#define CP3_BASE                  0xE0042000UL


/******************************************************************************/
/*                         Declaration                                        */
/******************************************************************************/
#define CP3                       ((CP3_Type     *) CP3_BASE)

/*===================
    Count Event ID
===================
=================== */
#define STOP_COUNTER                                         0x00 //Stop counter                    
#define COUNT_INSTRUCTION_FETCHES                            0x01 //Count instruction fetches       
#define COUNT_CYCLES                                         0x02 //count cycles                    
#define COUNT_COMPLETED_INSTRUCTIONS                         0x03 //count completed instructions    
#define COUNT_ZERO_INST_COMMIT_CYCLES                        0x04 //count zero inst commit cycles   
#define COUNT_PA_ONLY_INST_COMMIT_CYCLES                     0x05 //count PA only inst commit cycles
#define COUNT_PB_ONLY_INST_COMMIT_CYCLES                     0x06 //count PB only inst commit cycles
#define COUNT_DUAL_INST_COMMIT_CYCLES                        0x07 //count dual inst commit cycles                                            
#define COUNT_STORE_INSTRUCTIONS                             0x09 //count store instructions                        
#define COUNT_LOAD_INSTRUCTIONS                              0x0a //count load instructions                         
#define COUNT_LOAD_OR_STORE_INSTRUCTIONS                     0x0b //count load/store instructions                      
#define COUNT_LESS_1_OVER_4_IBUF_ENTRIES_ARE_USED            0x0e //count <= 1/4 IBuf_entries are used                     
#define COUNT_LARGE_1_OVER_2_IBUF_ENTRIES_ARE_USED           0x0f //count > 1/2 IBuf_entries are used                        
#define COUNT_IBUF_FULL_CYCLES                               0x10 //count IBuf full cycles                          
#define COUNT_BRANCH_INSTRUCTIONS                            0x16 //count branch instructions                       
#define COUNT_BRANCH_PREDICTION_MISSES                       0x17 //count branch prediction misses                  
#define COUNT_BTB_MISS                                       0x19 //count BTB miss                                  
#define COUNT_BTB_TARGET_MISSES                              0x1a //count BTB target misses                         
#define COUNT_CBP_MISSES                                     0x1b //count CBP misses                                
#define COUNT_RS_POP                                         0x1c //count RS Pop                                    
#define COUNT_RS_MISSES                                      0x1d //count RS misses                                 
#define COUNT_MEMORY_STALL                                   0x1f //count memory stall                              
#define COUNT_BACK_END_PIPE_HOLD                             0x20 //count back-end pipe hold                        
#define COUNT_LOAD_TO_USE_STALL                              0x21 //count load-to-use stall                         
#define COUNT_DCU_NOT_ACCEPT_COREPIPE_COMMAND_STALL          0x22 //count dcu not accept corepipe command sta       
#define COUNT_PRECISE_LOAD_OR_STORE_INSTRUCTION_STALL        0x23 //count precise load/store instruction stal          
#define COUNT_LOAD_INDEX_QUEUE_FULL_STALL                    0x24 //count load-index queue full stall               
#define COUNT_GPR_UPDATE_STALL                               0x25 //count gpr update stall                          
#define COUNT_ALL_STALL                                      0x27 //count all stall                                 
#define COUNT_FRONT_END_PIPE_HOLD                            0x29 //count front-end pipe hold                       
#define COUNT_BRANCH_PREDICTOR_STALL                         0x2b //count branch predictor stall                    
#define COUNT_ICU_STALL                                      0x2c //count icu stall                                 
#define COUNT_INSTRUCTION_BUFFER_STALL                       0x2d //count instruction buffer stall                  
#define COUNT_INSTRUCTION_STALL                              0x2e //count instruction stall                         
#define COUNT_BRANCH_MISS_PREDICTION_PENALTY                 0x2f //count branch miss prediction penalty            
#define COUNT_ICACHE_HITS                                    0x30 //count ICache hits                               
#define COUNT_ICACHE_MISSES                                  0x31 //count ICache misses                             
#define COUNT_ICACHE_MISS_CYCLES                             0x32 //count ICache miss cycles                        
#define COUNT_DCACHE_HITS                                    0x33 //count DCache hits                               
#define COUNT_DCACHE_MISSES                                  0x34 //count DCache misses                             
#define COUNT_DCACHE_CACHEABLE_BUSY                          0x35 //count DCache cacheable busy                     
#define COUNT_DCACHE_UNCACHEABLE_BUSY                        0x36 //count DCache uncacheable busy                   
#define COUNT_L2CACHE_HIT_NOT_SUPPORTED                      0x37 //count L2Cache hit not supported                 
#define COUNT_L2CACHE_MISS_NOT_SUPPORTED                     0x38 //count L2Cache miss not supported                
#define COUNT_UNCACHED_READ                                  0x39 //count uncached read                             
#define COUNT_UNCACHED_WRITE                                 0x3a //count uncached write                            
#define COUNT_DCACHE_CACHEABLE_READ_MISSES                   0x3b //count DCache cacheable read misses              
#define COUNT_DCACHE_CACHEABLE_READ_HITS                     0x3c //count DCache cacheable read hits                
#define COUNT_LOAD_UES_REQUESTS                              0x3d //count load-ues requests                         
#define COUNT_LOAD_USE_READ_HIT                              0x3e //count load-use read hit                         
#define COUNT_LOAD_USE_WRITE_HIT                             0x3f //count load-use write hit                        
#define COUNT_DCU_REQUEST_COUNTS                             0x40 //count dcu request counts                        
#define COUNT_DCU_RESPONSE_WAIT_CYCLES                       0x41 //count dcu response wait cycles                  
#define COUNT_LESS_1_OVER_4_DCU_OSB_ENTRIES_ARE_USED         0x42 //count <= 1/4 dcu osb entries are used                  
#define COUNT_LARGE_1_OVER_2_DCU_OSB_ENTRIES_ARE_USED        0x43 //count > 1/2 dcu osb entries are used                     
#define COUNT_DCU_OSB_FULL_CYCLES                            0x44 //count dcu osb full cycles                       
#define COUNT_LESS_1_OVER_4_DCU_LDQ_ENTRIES_ARE_USED         0x45 //count <= 1/4 dcu ldq entries are used                  
#define COUNT_LARGE_1_OVER_2_DCU_LDQ_ENTRIES_ARE_USED        0x46 //count > 1/2 dcu ldq entries are used                     
#define COUNT_DCU_LDQ_FULL_CYCLES                            0x47 //count dcu ldq full cycles                       
#define COUNT_LESS_1_OVER_4_DCU_WBQ_ENTRIES_ARE_USED         0x48 //count <= 1/4 dcu wbq entries are used                  
#define COUNT_LARGE_1_OVER_2_DCU_WBQ_ENTRIES_ARE_USED        0x49 //count > 1/2 dcu wbq entries are used                     
#define COUNT_DCU_WBQ_FULL_CYCLES                            0x4a //count dcu wbq full cycles                       
#define COUNT_DMA_TO_ITCM_ACCESS_COUNTS                      0x5d //count dma to itcm access counts                 
#define COUNT_DMA_TO_DTCM_ACCESS_COUNTS                      0x5e //count dma to dtcm access counts                 
#define COUNT_DMA_TO_DEFAULT_SLAVE_ACCESS_COUNTS             0x60 //count dma to default slave access counts        
#define COUNT_CORE_TO_ITCM0_ACCESS_COUNTS                    0x61 //count core to itcm0 access counts               
#define COUNT_CORE_TO_DTCM0_ACCESS_COUNTS                    0x63 //count core to dtcm0 access counts               
#define COUNT_AXI_BUS_READS                                  0x66 //count AXI bus reads                             
#define COUNT_AXI_BUS_WRITE                                  0x67 //count AXI bus write                             
#define COUNT_AXI_BUS_UNCACHED_DATA_READ                     0x68 //count AXI bus uncached data read                
#define COUNT_AXI_BUS_UNCACHED_DATA_WRITE                    0x69 //count AXI bus uncached data write               
#define COUNT_AXI_BUS_CACHED_DATA_READ                       0x6a //count AXI bus cached data read                  
#define COUNT_AXI_BUS_CACHED_DATA_WRITE                      0x6b //count AXI bus cached data write                 
#define COUNT_AXI_BUS_INSTRUCTION_READ                       0x6c //count AXI bus instruction read                  
#define COUNT_AXI_BUS_DATA_READ_CYCLE                        0x6d //count AXI bus data read cycle                   
#define COUNT_AXI_BUS_DATA_WRITE_CYCLE                       0x6e //count AXI bus data write cycle                  
#define COUNT_AXI_BUS_UNCACHED_DATA_READ_CYCLE               0x6f //count AXI bus uncached data read cycle          
#define COUNT_AXI_BUS_UNCACHED_DATA_WRITE_CYCLE              0x70 //count AXI bus uncached data write cycle         
#define COUNT_AXI_BUS_INSTRUCTION_READ_CYCLE                 0x71 //count AXI bus instruction read cycle            
#define COUNT_WBUF_MERGE_COUNT                               0x83 //count WBuf merge count                          
#define COUNT_WBUF_UC_MERGE_COUNT                            0x84 //count WBuf UC merge count                       


#define CNT0_DUAL_MODE_POS      1
#define CNT1_DUAL_MODE_POS      2
#define CNT2_DUAL_MODE_POS      4
#define CNT3_DUAL_MODE_POS      8

/*===================
    cnt_idx Table
===================
=================== */
#define COUNTER0_LO                0
#define COUNTER0_HI                1
#define COUNTER1_LO                2
#define COUNTER1_HI                3
#define COUNTER2_LO                4
#define COUNTER2_HI                5
#define COUNTER3_LO                6
#define COUNTER3_HI                7


__STATIC_INLINE void CP3_Enable_Counter(void)
{
	CP3_Type *cp3 = CP3;

	cp3->cp3_control2_reg_b.counter_en = 1;
}

__STATIC_INLINE void CP3_Disable_Counter(void)
{
	CP3_Type *cp3 = CP3;

	cp3->cp3_control2_reg_b.counter_en = 0;

}

__STATIC_INLINE void CP3_Set_Lo_Counter(uint8_t lo_cnt0_event_id, uint8_t lo_cnt1_event_id, uint8_t lo_cnt2_event_id, uint8_t lo_cnt3_event_id)
{
	CP3_Type *cp3 = CP3;

	cp3->cp3_control0_reg_b.lo_cunt0_event_id = lo_cnt0_event_id;
	cp3->cp3_control0_reg_b.lo_cunt1_event_id = lo_cnt1_event_id;
	cp3->cp3_control0_reg_b.lo_cunt2_event_id = lo_cnt2_event_id;
	cp3->cp3_control0_reg_b.lo_cunt3_event_id = lo_cnt3_event_id;

}

__STATIC_INLINE void CP3_Set_High_Counter(uint8_t hi_cnt0_event_id, uint8_t hi_cnt1_event_id, uint8_t hi_cnt2_event_id, uint8_t hi_cnt3_event_id)
{
	CP3_Type *cp3 = CP3;

	cp3->cp3_control1_reg_b.hi_cunt0_event_id = hi_cnt0_event_id;
	cp3->cp3_control1_reg_b.hi_cunt1_event_id = hi_cnt1_event_id;
	cp3->cp3_control1_reg_b.hi_cunt2_event_id = hi_cnt2_event_id;
	cp3->cp3_control1_reg_b.hi_cunt3_event_id = hi_cnt3_event_id;

}

__STATIC_INLINE void CP3_Set_Counter_Dual_Mode(uint8_t dual_mode_map)
{
	CP3_Type *cp3 = CP3;

	if (dual_mode_map & CNT0_DUAL_MODE_POS) {
		cp3->cp3_control2_reg_b.lo_cunt0_dual_mode_en = 1;
	} else {
		cp3->cp3_control2_reg_b.lo_cunt0_dual_mode_en = 0;
	}

	if (dual_mode_map & CNT1_DUAL_MODE_POS) {
		cp3->cp3_control2_reg_b.lo_cunt1_dual_mode_en = 1;
	} else {
		cp3->cp3_control2_reg_b.lo_cunt1_dual_mode_en = 0;
	}

	if (dual_mode_map & CNT2_DUAL_MODE_POS) {
		cp3->cp3_control2_reg_b.lo_cunt2_dual_mode_en = 1;
	} else {
		cp3->cp3_control2_reg_b.lo_cunt2_dual_mode_en = 0;
	}

	if (dual_mode_map & CNT3_DUAL_MODE_POS) {
		cp3->cp3_control2_reg_b.lo_cunt3_dual_mode_en = 1;
	} else {
		cp3->cp3_control2_reg_b.lo_cunt3_dual_mode_en = 0;
	}

}

__STATIC_INLINE uint32_t CP3_Read_Counter(uint32_t cnt_idx)
{
	CP3_Type *cp3 = CP3;

	cp3->cp3_control2_reg_b.cnt_idx = cnt_idx;

	return cp3->cp3_data;
}

__STATIC_INLINE void CP3_Write_Counter(uint32_t cnt_idx, uint32_t data)
{
	CP3_Type *cp3 = CP3;

	cp3->cp3_control2_reg_b.cnt_idx = cnt_idx;

	cp3->cp3_data = data;
}

__STATIC_INLINE uint32_t CP3_ReadAndClean_Counter(uint32_t cnt_idx)
{
	uint32_t data;

	CP3_Type *cp3 = CP3;

	cp3->cp3_control2_reg_b.cnt_idx = cnt_idx;

	data = cp3->cp3_data;

	cp3->cp3_data = 0;

	return data;
}


#ifdef __cplusplus
}
#endif

#endif
