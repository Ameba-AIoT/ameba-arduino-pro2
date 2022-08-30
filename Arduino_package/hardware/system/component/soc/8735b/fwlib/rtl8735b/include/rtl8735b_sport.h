/**************************************************************************//**
 * @file     rtl8735bh_sport.h
 * @brief    The HAL related definition and macros for the SPORT device.
 *           Includes Registers and data type definition.
 * @version  V1.00
 * @date     2016-07-20
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2017 Realtek Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************/

#ifndef _RTL8735BH_SPORT_H_
#define _RTL8735BH_SPORT_H_

#ifdef __cplusplus
extern "C" {
#endif


#include "basic_types.h"
#include "rtl8735b_sport_type.h"
#include "rtl8735b_syson_s_type.h"
#include "rtl8735b.h"
#include "hal_irq.h"


/**
  \brief  Define the SPORT port ID.
*/
enum  sport_id_e {
	SPORT_id   =   0x0,
	SPORT_Max_Id  =   0x1
};
typedef uint8_t sport_id_t;

/**
  \brief  Define the SPORT clock source.
*/
enum  sport_clk_src_e {
	SPORT_40MHZ     =   0x0,
	SPORT_98p304KHZ =   0x1,
	SPORT_45p158KHZ =   0x2
};
typedef uint8_t sport_clk_src_t;

/**
  \brief  Define the SPORT sample rate.
*/
enum sport_rate_e {
	R_8KHZ    = 0x07,
	R_11p025KHZ = 0x0d,
	R_12KHZ   = 0x0b,
	R_16KHZ   = 0x05,
	R_24KHZ   = 0x0a,
	R_22p05KHZ  = 0x0c,
	R_32KHZ   = 0x03,
	R_44p1KHZ = 0x08,
	R_48KHZ   = 0x00,
	R_88p2KHZ = 0x09,
	R_96KHZ   = 0x01,

	R_1KHZ    = 0x10,
	R_4KHZ    = 0x11,
	R_192KHZ  = 0x12,
	R_384KHZ  = 0x13,
	R_7p35KHZ = 0x14,
	R_14p7KHZ = 0x15,
	R_29p4KHZ = 0x16,
	R_58p8KHZ = 0x17,
	R_176p4KHZ  = 0x18
};
typedef uint32_t sport_rate_t;

/**
  \brief SPORT Device Mode.
*/
enum  sport_dev_mode_e {
	SPORT_MASTER_MODE =   0x0,
	SPORT_SLAVE_MODE  =   0x1
};
typedef uint8_t sport_dev_mode_t;

/**
  \brief SPORT Work Mode.
*/
enum  sport_wk_mode_e {
	SPORT_DMA_MODE =   0x0,
	SPORT_FIFO_MODE  =   0x1
};
typedef uint8_t sport_wk_mode_t;

/**
  \brief SPORT Channel Select.
*/
enum  sport_sel_ch_e {
	SPORT_L_R = 0x0,
	SPORT_R_L = 0x1,
	SPORT_L_L = 0x2,
	SPORT_R_R = 0x3
};
typedef uint8_t sport_sel_ch_t;

/**
  \brief SPORT Format.
*/
enum  sport_format_e {
	SPORT_I2S          =   0x0,
	SPORT_LEFT_JUST    =   0x1,
	SPORT_PCM_MODE_A   =   0x2,
	SPORT_PCM_MODE_B   =   0x3
};
typedef uint8_t sport_format_t;

/**
  \brief SPORT Data Length.
*/
enum  sport_dl_e {
	SPORT_DL_16BIT = 0x00,
	SPORT_DL_20BIT = 0x01,
	SPORT_DL_24BIT = 0x02,
	SPORT_DL_32BIT = 0x04
};
typedef uint8_t sport_dl_t;

/**
  \brief SPORT Channel Length.
*/
enum  sport_cl_e {
	SPORT_CL_16BIT = 0x00,
	SPORT_CL_20BIT = 0x01,
	SPORT_CL_24BIT = 0x02,
	SPORT_CL_32BIT = 0x04
};
typedef uint8_t sport_cl_t;

/**
  \brief SPORT Data MSB or LSB.
*/
enum  sport_ml_e {
	SPORT_MSB_FIRST = 0x00,
	SPORT_LSB_FIRST = 0x01
};
typedef uint8_t sport_ml_t;

/**
  \brief SPORT Mclk Rate
*/
enum  sport_mclk_e {
	SPORT_SRC_DIV_2 = 0x00,
	SPORT_SRC_DIV_1 = 0x01,
	SPORT_SRC_DIV_4 = 0x02
};
typedef uint8_t sport_mclk_t;

/**
  \brief SPORT TDM Mode
*/
enum  sport_tdm_e {
	SPORT_NO_TDM = 0x00,
	SPORT_4_TDM = 0x01,
	SPORT_6_TDM = 0x02,
	SPORT_8_TDM = 0x03
};
typedef uint8_t sport_tdm_t;

/**
  \brief SPORT Channel Number
*/
enum sport_ch_e {
	CH_1_MONO   = 0x00,
	CH_2_STEREO = 0x01,
	CH_4        = 0x02,
	CH_6        = 0x03,
	CH_8        = 0x04
};
typedef uint8_t sport_ch_t;

/**
  \brief SPORT Burst Size
*/
enum sport_burst_size_e {
	SPORT_BURST_16  = 0x00,
	SPORT_BURST_8   = 0x01,
	SPORT_BURST_4   = 0x02
};
typedef uint8_t sport_burst_size_t;

/**
  \brief  SPORT TX and RX DMA
*/
enum sport_trx_e {
	SPORT_TX0 = 0x00,
	SPORT_TX1 = 0x01,
	SPORT_RX0 = 0x02,
	SPORT_RX1 = 0x03,
};
typedef uint8_t sport_trx_t;

/**
  \brief  SPORT Page Number
*/
enum {
	SPORT_USELESS_PAGE    =   0x0,
	SPORT_2PAGE           =   0x1,
	SPORT_3PAGE           =   0x2,
	SPORT_4PAGE           =   0x3
};
typedef uint8_t sport_page_num;

/**
  \brief  SPORT Page
*/
enum {
	SPORT_PAGE_0    =   0x1,
	SPORT_PAGE_1    =   0x2,
	SPORT_PAGE_2    =   0x4,
	SPORT_PAGE_3    =   0x8
};
typedef uint8_t sport_page;

/**
  \brief  SPORT Fixed Bclk Select
*/
enum {
	SPORT_BCLK_1D4    =   0x0,
	SPORT_BCLK_1D2    =   0x1
};
typedef uint8_t sport_fixed_bclk_t;

/**
  \brief  The sport tx parameter structure
*/
typedef struct hal_sport_tx_params_s {
	sport_ch_t    sport_tx_ch;      /* TX channel number*/
	sport_cl_t    sport_tx_cl;      /* TX channel length*/
	sport_dl_t    sport_tx0_dl;     /* TX data length for FIFO_0 */
	sport_dl_t    sport_tx1_dl;     /* TX data length for FIFO_1*/
	sport_rate_t  sport_tx_rate;    /* TX sample rate*/
} hal_sport_tx_params_t, *phal_sport_tx_params_t;

/**
  \brief  The sport rx parameter structure
*/
typedef struct hal_sport_rx_params_s {
	sport_ch_t    sport_rx_ch;      /* RX channel number*/
	sport_cl_t    sport_rx_cl;      /* RX channel length*/
	sport_dl_t    sport_rx0_dl;     /* RX data length for FIFO_0 */
	sport_dl_t    sport_rx1_dl;     /* RX data length for FIFO_1*/
	sport_rate_t  sport_rx_rate;    /* RX sample rate*/
} hal_sport_rx_params_t, *phal_sport_rx_params_t;

/**
  \brief  The sport buffer parameter structure
*/
typedef struct hal_sport_buf_params_s {
	u8      *tx0_buf;       /* TX FIFO_0 buffer*/
	u8      *rx0_buf;       /* RX FIFO_0 buffer*/
	u8      *tx1_buf;       /* TX FIFO_1 buffer*/
	u8      *rx1_buf;       /* RX FIFO_1 buffer*/
	u32     page_num;       /* Buffer page number*/
	u32     page_size;      /* Buffer page size*/
} hal_sport_buf_params_t, *phal_sport_buf_params_t;

/**
  \brief  The sport page interrupts
*/
typedef struct hal_sport_page_intr_s {
	u8    sport_p0ok;       /* Page 0 OK Interrupt Enabler*/
	u8    sport_p1ok;       /* Page 1 OK Interrupt Enabler*/
	u8    sport_p2ok;       /* Page 2 OK Interrupt Enabler*/
	u8    sport_p3ok;       /* Page 3 OK Interrupt Enabler*/
	u8    sport_p0unava;    /* PAGE 0 unavailable Interrupt Enable*/
	u8    sport_p1unava;    /* PAGE 1 unavailable Interrupt Enable*/
	u8    sport_p2unava;    /* PAGE 2 unavailable Interrupt Enable*/
	u8    sport_p3unava;    /* PAGE 3 unavailable Interrupt Enabler*/
	u8    sport_p0err;      /* PAGE 0 error Interrupt Enable*/
	u8    sport_p1err;      /* PAGE 1 error Interrupt Enable*/
	u8    sport_p2err;      /* PAGE 2 error Interrupt Enable*/
	u8    sport_p3err;      /* PAGE 3 error Interrupt Enabler*/
	u8    sport_fifo_err;   /* FIFO Underflow or Overflow Interrupt Enable*/
} hal_sport_page_intr_t, *phal_sport_page_intr_t;

/**
  \brief  The sport TX FIFO interrupts
*/
typedef struct hal_sport_tx_fifo_intr_s {
	u8    sport_th_tx0;     /* TX0 Threshold  Interrupt Enabler*/
	u8    sport_full_tx0;   /* TX0 Full Interrupt Enabler*/
	u8    sport_empty_tx0;  /* TX0 Empty Interrupt Enabler*/
	u8    sport_idle_tx0;   /* TX0 Idle OK Interrupt Enabler*/
	u8    sport_th_tx1;     /* TX1 Threshold  Interrupt Enabler*/
	u8    sport_full_tx1;   /* TX1 Full Interrupt Enabler*/
	u8    sport_empty_tx1;  /* TX1 Empty Interrupt Enabler*/
	u8    sport_idle_tx1;   /* TX1 Idle OK Interrupt Enabler*/
} hal_sport_tx_fifo_intr_t, *phal_sport_tx_fifo_intr_t;

/**
  \brief  The sport RX FIFO interrupts
*/
typedef struct hal_sport_rx_fifo_intr_s {
	u8    sport_th_rx0;     /* RX0 Threshold  Interrupt Enabler*/
	u8    sport_full_rx0;   /* R0 Full Interrupt Enabler*/
	u8    sport_empty_rx0;  /* RX0 Empty Interrupt Enabler*/
	u8    sport_th_rx1;     /* RX1 Threshold  Interrupt Enabler*/
	u8    sport_full_rx1;   /* RX1 Full Interrupt Enabler*/
	u8    sport_empty_rx1;  /* RX1 Empty Interrupt Enabler*/
} hal_sport_rx_fifo_intr_t, *phal_sport_rx_fifo_intr_t;

typedef struct hal_sport_init_dat_s {
	u32                 sport_data_byte_cnt;  /*SPORT transfer byte count*/

	u8                  *sport_tx0_data;       /*SPORT Tx data pointer*/
	u8                  *sport_rx0_data;       /*SPORT Rx data pointer*/
	u8                  *sport_tx1_data;       /*SPORT Tx data pointer*/
	u8                  *sport_rx1_data;       /*SPORT Rx data pointer*/

	u8                  sport_tx0_idx;         /*SPORT TX0 page index */
	u8                  sport_rx0_idx;         /*SPORT RX0 page index */
	u8                  sport_tx1_idx;         /*SPORT TX1 page index */
	u8                  sport_rx1_idx;         /*SPORT RX1 page index */
	u8                  sport_hw_tx0_idx;      /*SPORT HW TX0 page index */
	u8                  sport_hw_rx0_idx;      /*SPORT HW RX0 page index */
	u8                  sport_hw_tx1_idx;      /*SPORT HW TX1 page index */
	u8                  sport_hw_rx1_idx;      /*SPORT HW RX1 page index */
} hal_sport_init_dat_t, *phal_sport_init_dat_t;

/**
  \brief  SPORT call back function for the interrupt event.
*/
typedef void (*sport_irq_user_cb_t)(u32 *arg, u8 *pbuf);


typedef struct hal_sport_adapter_s {
	SPORT_Type *base_addr;      /*! The SPORT register base address */

	hal_sport_init_dat_t init_dat;          /*! SPORT initial data struct */
	sport_irq_user_cb_t sport_irq_user_cb;  /*! Pointer to SPORT User Callback */
	u32 *sport_user_arg;                    /*! Pointer to SPORT User argument */

	sport_irq_user_cb_t sport_tx0_irq_user_cb;  /*! TX0 Pointer to SPORT User Callback */
	u32 *sport_tx0_user_arg;                    /*! TX0 Pointer to SPORT User argument */
	sport_irq_user_cb_t sport_tx1_irq_user_cb;  /*! TX1 Pointer to SPORT User Callback */
	u32 *sport_tx1_user_arg;                    /*! TX1 Pointer to SPORT User argument */
	sport_irq_user_cb_t sport_rx0_irq_user_cb;  /*! RX0 Pointer to SPORT User Callback */
	u32 *sport_rx0_user_arg;                    /*! RX0 Pointer to SPORT User argument */
	sport_irq_user_cb_t sport_rx1_irq_user_cb;  /*! RX1 Pointer to SPORT User Callback */
	u32 *sport_rx1_user_arg;                    /*! RX1 Pointer to SPORT User argument */

	sport_irq_user_cb_t sport_dma_err_irq_user_cb;  /*! RX1 Pointer to SPORT User Callback */
	u32 *sport_dma_err_user_arg;                    /*! RX1 Pointer to SPORT User argument */
	u32 dma_err_sta;

	u32 *ptx0_page_list[4];      /*! The TX0 DAM buffer: pointer of each page */
	u32 *prx0_page_list[4];      /*! The RX0 DAM buffer: pointer of each page */
	u32 *ptx1_page_list[4];      /*! The TX1 DAM buffer: pointer of each page */
	u32 *prx1_page_list[4];      /*! The RX0 DAM buffer: pointer of each page */

	u8 tx_channel_factor;
	u8 rx_channel_factor;

	u8 tx_ch_len_factor;
	u8 rx_ch_len_factor;

	u8 dcache_memory_en;        /*! check the memory is cache or not  */

	u8 sport_mode_record;       /*! Record FIFO or DMA mode  */

	uint32_t tx0_dma_err;       /*!< TX0 DMA error counter    */
	uint32_t rx0_dma_err;       /*!< RX0 DMA error counter    */
	uint32_t tx1_dma_err;       /*!< TX1 DMA error counter    */
	uint32_t rx1_dma_err;       /*!< RX1 DMA error counter    */
	uint32_t tx_fifo_err;       /*!< TX FIFO error counter    */
	uint32_t rx_fifo_err;       /*!< RX FIFO error counter    */

	void (*dcache_invalidate_by_addr)(uint32_t *addr, int32_t dsize);   /*! callback function to do the D-cache invalidate  */
	void (*dcache_clean_by_addr)(uint32_t *addr, int32_t dsize);        /*! callback function to do the D-cache clean  */
} hal_sport_adapter_t, *phal_sport_adapter_t;


/**
  \brief  The data structure to handle multiple SPORT adapters.
*/
typedef struct hal_sport_group_adapter_s {
	volatile uint32_t critical_lv;                  /*!< to record SPORT HAL enter critical section level */
	hal_sport_adapter_t *psport_adapter[SPORT_Max_Id];    /*!< All the SPORT adapters of this platform */
	irq_handler_t   irq_fun[SPORT_Max_Id];            /*!< the IRQ handler for different SPORT adapters */
} hal_sport_group_adapter_t, *phal_sport_group_adapter_t;


void hal_rtl_sport_irqhandler_ram(void);
void hal_rtl_sport_irq_reg(void);
void hal_rtl_sport_irq_unreg(void);
HAL_Status hal_rtl_sport_init(hal_sport_adapter_t *psport_adapter);
HAL_Status hal_rtl_sport_deinit(hal_sport_adapter_t *psport_adapter);
void hal_rtl_sport_reset(hal_sport_adapter_t *psport_adapter);
void hal_rtl_sport_reset_tx_fifo(hal_sport_adapter_t *psport_adapter);
void hal_rtl_sport_reset_rx_fifo(hal_sport_adapter_t *psport_adapter);
void hal_rtl_sport_bclk_reset(hal_sport_adapter_t *psport_adapter);
void hal_rtl_sport_dma_reset(hal_sport_adapter_t *psport_adapter);
void hal_rtl_sport_clean_tx_page_own(hal_sport_adapter_t *psport_adapter);
void hal_rtl_sport_clean_rx_page_own(hal_sport_adapter_t *psport_adapter);
void hal_rtl_sport_set_master(hal_sport_adapter_t *psport_adapter, sport_dev_mode_t dev_mode);
void hal_rtl_sport_set_loopback(hal_sport_adapter_t *psport_adapter, BOOL loopback_en);
void hal_rtl_sport_mode(hal_sport_adapter_t *psport_adapter, sport_wk_mode_t wk_mode);
void hal_rtl_sport_tx_ch(hal_sport_adapter_t *psport_adapter, sport_sel_ch_t sport_sel_ch);
void hal_rtl_sport_rx_ch(hal_sport_adapter_t *psport_adapter, sport_sel_ch_t sport_sel_ch);
void hal_rtl_sport_format(hal_sport_adapter_t *psport_adapter, sport_format_t sport_format);
void hal_rtl_sport_rx_same_format(hal_sport_adapter_t *psport_adapter, BOOL rx_en);
void hal_rtl_sport_rx_format(hal_sport_adapter_t *psport_adapter, sport_format_t sport_format);
void hal_rtl_sport_tx0_mono(hal_sport_adapter_t *psport_adapter, BOOL type_sel);
void hal_rtl_sport_tx1_mono(hal_sport_adapter_t *psport_adapter, BOOL type_sel);
void hal_rtl_sport_rx_same_mono_stereo(hal_sport_adapter_t *psport_adapter, BOOL rx_en);
void hal_rtl_sport_rx0_mono(hal_sport_adapter_t *psport_adapter, BOOL type_sel);
void hal_rtl_sport_rx1_mono(hal_sport_adapter_t *psport_adapter, BOOL type_sel);
void hal_rtl_sport_tx0_data_length(hal_sport_adapter_t *psport_adapter, sport_dl_t dl);
void hal_rtl_sport_tx1_data_length(hal_sport_adapter_t *psport_adapter, sport_dl_t dl);
void hal_rtl_sport_rx_same_data_length(hal_sport_adapter_t *psport_adapter, BOOL rx_en);
void hal_rtl_sport_rx0_data_length(hal_sport_adapter_t *psport_adapter, sport_dl_t dl);
void hal_rtl_sport_rx1_data_length(hal_sport_adapter_t *psport_adapter, sport_dl_t dl);
void hal_rtl_sport_tx_channel_length(hal_sport_adapter_t *psport_adapter, sport_cl_t cl);
void hal_rtl_sport_rx_same_channel_length(hal_sport_adapter_t *psport_adapter, BOOL rx_en);
void hal_rtl_sport_rx_channel_length(hal_sport_adapter_t *psport_adapter, sport_cl_t cl);
void hal_rtl_sport_tx_rate(hal_sport_adapter_t *psport_adapter, sport_rate_t sport_sample_rate);
void hal_rtl_sport_rx_rate(hal_sport_adapter_t *psport_adapter, sport_rate_t sport_sample_rate);
void hal_rtl_sport_tx_data_dir(hal_sport_adapter_t *psport_adapter, sport_ml_t tx0_ml, sport_ml_t tx1_ml);
void hal_rtl_sport_rx_data_dir(hal_sport_adapter_t *psport_adapter, sport_ml_t rx0_ml, sport_ml_t rx1_ml);
void hal_rtl_sport_tx_lr_swap(hal_sport_adapter_t *psport_adapter, BOOL tx0_en, BOOL tx1_en);
void hal_rtl_sport_rx_lr_swap(hal_sport_adapter_t *psport_adapter, BOOL rx0_en, BOOL rx1_en);
void hal_rtl_sport_tx_byte_swap(hal_sport_adapter_t *psport_adapter, BOOL tx0_en, BOOL tx1_en);
void hal_rtl_sport_rx_byte_swap(hal_sport_adapter_t *psport_adapter, BOOL rx0_en, BOOL rx1_en);
void hal_rtl_sport_bclk_inverse(hal_sport_adapter_t *psport_adapter, BOOL inverse_en);
void hal_rtl_sport_set_mclk(hal_sport_adapter_t *psport_adapter, sport_mclk_t sport_mclk, BOOL mclk_en);
void hal_rtl_sport_sel_tx_tdm(hal_sport_adapter_t *psport_adapter, sport_tdm_t sport_tdm);
void hal_rtl_sport_sel_rx_tdm(hal_sport_adapter_t *psport_adapter, sport_tdm_t sport_tdm);
void hal_rtl_sport_set_tx0_consum(hal_sport_adapter_t *psport_adapter, u8 sport_layer);
void hal_rtl_sport_set_tx1_consum(hal_sport_adapter_t *psport_adapter, u8 sport_layer);
void hal_rtl_sport_set_rx0_consum(hal_sport_adapter_t *psport_adapter, u8 sport_layer);
void hal_rtl_sport_set_rx1_consum(hal_sport_adapter_t *psport_adapter, u8 sport_layer);
void hal_rtl_sport_tx_fifo_0(hal_sport_adapter_t *psport_adapter, BOOL ch1ch0_en, BOOL ch2ch3_en);
void hal_rtl_sport_tx_fifo_1(hal_sport_adapter_t *psport_adapter, BOOL ch4ch5_en, BOOL ch6ch7_en);
void hal_rtl_sport_rx_fifo_0(hal_sport_adapter_t *psport_adapter, BOOL ch1ch0_en, BOOL ch2ch3_en);
void hal_rtl_sport_rx_fifo_1(hal_sport_adapter_t *psport_adapter, BOOL ch4ch5_en, BOOL ch6ch7_en);
void hal_rtl_sport_set_tx_lrck(hal_sport_adapter_t *psport_adapter, u8 bclk_cnt);
void hal_rtl_sport_set_rx_lrck(hal_sport_adapter_t *psport_adapter, u8 bclk_cnt);
void hal_rtl_sport_tx_params(hal_sport_adapter_t *psport_adapter, hal_sport_tx_params_t *psport_tx_params);
void hal_rtl_sport_rx_params(hal_sport_adapter_t *psport_adapter, hal_sport_rx_params_t *psport_rx_params);
void hal_rtl_sport_tx_fifo_th(hal_sport_adapter_t *psport_adapter, u8 tx_th);
void hal_rtl_sport_rx_fifo_th(hal_sport_adapter_t *psport_adapter, u8 rx_th);
void hal_rtl_sport_set_dma_burst(hal_sport_adapter_t *psport_adapter, sport_burst_size_t burst_size);
void hal_rtl_sport_autoload_dma_burst(hal_sport_adapter_t *psport_adapter);
void hal_rtl_sport_set_dma_intr(hal_sport_adapter_t *psport_adapter, sport_trx_t trx, hal_sport_page_intr_t *ppage_intr);
void hal_rtl_sport_set_tx_fifo_intr(hal_sport_adapter_t *psport_adapter, hal_sport_tx_fifo_intr_t *ptx_fifo_intr);
void hal_rtl_sport_set_rx_fifo_intr(hal_sport_adapter_t *psport_adapter, hal_sport_rx_fifo_intr_t *prx_fifo_intr);
void hal_rtl_sport_dma_params(hal_sport_adapter_t *psport_adapter, u16 page_size, sport_page_num page_num);
void hal_rtl_sport_tx_start(hal_sport_adapter_t *psport_adapter, BOOL en);
void hal_rtl_sport_rx_start(hal_sport_adapter_t *psport_adapter, BOOL en);
void hal_rtl_sport_tx_dma_start(hal_sport_adapter_t *psport_adapter, BOOL en);
u32 hal_rtl_sport_get_tx_dma_start_sta(hal_sport_adapter_t *psport_adapter);
void hal_rtl_sport_rx_dma_start(hal_sport_adapter_t *psport_adapter, BOOL en);
u32 hal_rtl_sport_get_rx_dma_start_sta(hal_sport_adapter_t *psport_adapter);
void hal_rtl_sport_dma_buffer(hal_sport_adapter_t *psport_adapter, hal_sport_buf_params_t *pbuf_params);
int *hal_rtl_sport_get_tx0_page(hal_sport_adapter_t *psport_adapter);
int *hal_rtl_sport_get_tx1_page(hal_sport_adapter_t *psport_adapter);
void hal_rtl_sport_tx0_page_send(hal_sport_adapter_t *psport_adapter, u32 *pbuf);
void hal_rtl_sport_tx1_page_send(hal_sport_adapter_t *psport_adapter, u32 *pbuf);
u32 hal_rtl_sport_rx0_page_recv(hal_sport_adapter_t *psport_adapter);
u32 hal_rtl_sport_rx1_page_recv(hal_sport_adapter_t *psport_adapter);
u32 hal_rtl_sport_get_tx_fifo_err(hal_sport_adapter_t *psport_adapter);
u32 hal_rtl_sport_get_rx_fifo_err(hal_sport_adapter_t *psport_adapter);
void hal_rtl_sport_clr_tx_fifo_err(hal_sport_adapter_t *psport_adapter);
void hal_rtl_sport_clr_rx_fifo_err(hal_sport_adapter_t *psport_adapter);
void hal_rtl_sport_fifo_cb_handler(hal_sport_adapter_t *psport_adapter, sport_irq_user_cb_t callback, u32 *arg);
void hal_rtl_sport_tx0_dma_cb_handler(hal_sport_adapter_t *psport_adapter, sport_irq_user_cb_t callback, u32 *arg);
void hal_rtl_sport_tx1_dma_cb_handler(hal_sport_adapter_t *psport_adapter, sport_irq_user_cb_t callback, u32 *arg);
void hal_rtl_sport_rx0_dma_cb_handler(hal_sport_adapter_t *psport_adapter, sport_irq_user_cb_t callback, u32 *arg);
void hal_rtl_sport_rx1_dma_cb_handler(hal_sport_adapter_t *psport_adapter, sport_irq_user_cb_t callback, u32 *arg);
void hal_rtl_sport_dma_err_cb_handler(hal_sport_adapter_t *psport_adapter, sport_irq_user_cb_t callback, u32 *arg);
void hal_rtl_sport_fixed_bclk(hal_sport_adapter_t *psport_adapter, BOOL fixed_en, sport_fixed_bclk_t fixed_bclk_sel);
void hal_rtl_sport_rx_same_fs(hal_sport_adapter_t *psport_adapter, BOOL en);

/**
  \brief  The data structure of the stubs function for the sport HAL functions in ROM
*/
typedef struct hal_sport_func_stubs_s {
	void (*hal_sport_irqhandler_ram)(void);
	void (*hal_sport_irq_reg)(void);
	void (*hal_sport_irq_unreg)(void);
	HAL_Status(*hal_sport_init)(hal_sport_adapter_t *psport_adapter);
	HAL_Status(*hal_sport_deinit)(hal_sport_adapter_t *psport_adapter);
	void (*hal_sport_reset)(hal_sport_adapter_t *psport_adapter);
	void (*hal_sport_reset_tx_fifo)(hal_sport_adapter_t *psport_adapter);
	void (*hal_sport_reset_rx_fifo)(hal_sport_adapter_t *psport_adapter);
	void (*hal_sport_bclk_reset)(hal_sport_adapter_t *psport_adapter);
	void (*hal_sport_dma_reset)(hal_sport_adapter_t *psport_adapter);
	void (*hal_sport_clean_tx_page_own)(hal_sport_adapter_t *psport_adapter);
	void (*hal_sport_clean_rx_page_own)(hal_sport_adapter_t *psport_adapter);
	void (*hal_sport_set_master)(hal_sport_adapter_t *psport_adapter, sport_dev_mode_t dev_mode);
	void (*hal_sport_set_loopback)(hal_sport_adapter_t *psport_adapter, BOOL loopback_en);
	void (*hal_sport_mode)(hal_sport_adapter_t *psport_adapter, sport_wk_mode_t wk_mode);
	void (*hal_sport_tx_ch)(hal_sport_adapter_t *psport_adapter, sport_sel_ch_t sport_sel_ch);
	void (*hal_sport_rx_ch)(hal_sport_adapter_t *psport_adapter, sport_sel_ch_t sport_sel_ch);
	void (*hal_sport_format)(hal_sport_adapter_t *psport_adapter, sport_format_t sport_format);
	void (*hal_sport_rx_same_format)(hal_sport_adapter_t *psport_adapter, BOOL rx_en);
	void (*hal_sport_rx_format)(hal_sport_adapter_t *psport_adapter, sport_format_t sport_format);
	void (*hal_sport_tx0_mono)(hal_sport_adapter_t *psport_adapter, BOOL type_sel);
	void (*hal_sport_tx1_mono)(hal_sport_adapter_t *psport_adapter, BOOL type_sel);
	void (*hal_sport_rx_same_mono_stereo)(hal_sport_adapter_t *psport_adapter, BOOL rx_en);
	void (*hal_sport_rx0_mono)(hal_sport_adapter_t *psport_adapter, BOOL type_sel);
	void (*hal_sport_rx1_mono)(hal_sport_adapter_t *psport_adapter, BOOL type_sel);
	void (*hal_sport_tx0_data_length)(hal_sport_adapter_t *psport_adapter, sport_dl_t dl);
	void (*hal_sport_tx1_data_length)(hal_sport_adapter_t *psport_adapter, sport_dl_t dl);
	void (*hal_sport_rx_same_data_length)(hal_sport_adapter_t *psport_adapter, BOOL rx_en);
	void (*hal_sport_rx0_data_length)(hal_sport_adapter_t *psport_adapter, sport_dl_t dl);
	void (*hal_sport_rx1_data_length)(hal_sport_adapter_t *psport_adapter, sport_dl_t dl);
	void (*hal_sport_tx_channel_length)(hal_sport_adapter_t *psport_adapter, sport_cl_t cl);
	void (*hal_sport_rx_same_channel_length)(hal_sport_adapter_t *psport_adapter, BOOL rx_en);
	void (*hal_sport_rx_channel_length)(hal_sport_adapter_t *psport_adapter, sport_cl_t cl);
	void (*hal_sport_tx_rate)(hal_sport_adapter_t *psport_adapter, sport_rate_t sport_sample_rate);
	void (*hal_sport_rx_rate)(hal_sport_adapter_t *psport_adapter, sport_rate_t sport_sample_rate);
	void (*hal_sport_tx_data_dir)(hal_sport_adapter_t *psport_adapter, sport_ml_t tx0_ml, sport_ml_t tx1_ml);
	void (*hal_sport_rx_data_dir)(hal_sport_adapter_t *psport_adapter, sport_ml_t rx0_ml, sport_ml_t rx1_ml);
	void (*hal_sport_tx_lr_swap)(hal_sport_adapter_t *psport_adapter, BOOL tx0_en, BOOL tx1_en);
	void (*hal_sport_rx_lr_swap)(hal_sport_adapter_t *psport_adapter, BOOL rx0_en, BOOL rx1_en);
	void (*hal_sport_tx_byte_swap)(hal_sport_adapter_t *psport_adapter, BOOL tx0_en, BOOL tx1_en);
	void (*hal_sport_rx_byte_swap)(hal_sport_adapter_t *psport_adapter, BOOL rx0_en, BOOL rx1_en);
	void (*hal_sport_bclk_inverse)(hal_sport_adapter_t *psport_adapter, BOOL inverse_en);
	void (*hal_sport_set_mclk)(hal_sport_adapter_t *psport_adapter, sport_mclk_t sport_mclk, BOOL mclk_en);
	void (*hal_sport_sel_tx_tdm)(hal_sport_adapter_t *psport_adapter, sport_tdm_t sport_tdm);
	void (*hal_sport_sel_rx_tdm)(hal_sport_adapter_t *psport_adapter, sport_tdm_t sport_tdm);
	void (*hal_sport_set_tx0_consum)(hal_sport_adapter_t *psport_adapter, u8 sport_layer);
	void (*hal_sport_set_tx1_consum)(hal_sport_adapter_t *psport_adapter, u8 sport_layer);
	void (*hal_sport_set_rx0_consum)(hal_sport_adapter_t *psport_adapter, u8 sport_layer);
	void (*hal_sport_set_rx1_consum)(hal_sport_adapter_t *psport_adapter, u8 sport_layer);
	void (*hal_sport_tx_fifo_0)(hal_sport_adapter_t *psport_adapter, BOOL ch1ch0_en, BOOL ch2ch3_en);
	void (*hal_sport_tx_fifo_1)(hal_sport_adapter_t *psport_adapter, BOOL ch4ch5_en, BOOL ch6ch7_en);
	void (*hal_sport_rx_fifo_0)(hal_sport_adapter_t *psport_adapter, BOOL ch1ch0_en, BOOL ch2ch3_en);
	void (*hal_sport_rx_fifo_1)(hal_sport_adapter_t *psport_adapter, BOOL ch4ch5_en, BOOL ch6ch7_en);
	void (*hal_sport_set_tx_lrck)(hal_sport_adapter_t *psport_adapter, u8 bclk_cnt);
	void (*hal_sport_set_rx_lrck)(hal_sport_adapter_t *psport_adapter, u8 bclk_cnt);
	void (*hal_sport_tx_params)(hal_sport_adapter_t *psport_adapter, hal_sport_tx_params_t *psport_tx_params);
	void (*hal_sport_rx_params)(hal_sport_adapter_t *psport_adapter, hal_sport_rx_params_t *psport_rx_params);
	void (*hal_sport_tx_fifo_th)(hal_sport_adapter_t *psport_adapter, u8 tx_th);
	void (*hal_sport_rx_fifo_th)(hal_sport_adapter_t *psport_adapter, u8 rx_th);
	void (*hal_sport_set_dma_burst)(hal_sport_adapter_t *psport_adapter, sport_burst_size_t burst_size);
	void (*hal_sport_autoload_dma_burst)(hal_sport_adapter_t *psport_adapter);
	void (*hal_sport_set_dma_intr)(hal_sport_adapter_t *psport_adapter, sport_trx_t trx, hal_sport_page_intr_t *ppage_intr);
	void (*hal_sport_set_tx_fifo_intr)(hal_sport_adapter_t *psport_adapter, hal_sport_tx_fifo_intr_t *ptx_fifo_intr);
	void (*hal_sport_set_rx_fifo_intr)(hal_sport_adapter_t *psport_adapter, hal_sport_rx_fifo_intr_t *prx_fifo_intr);
	void (*hal_sport_dma_params)(hal_sport_adapter_t *psport_adapter, u16 page_size, sport_page_num page_num);
	void (*hal_sport_tx_start)(hal_sport_adapter_t *psport_adapter, BOOL en);
	void (*hal_sport_rx_start)(hal_sport_adapter_t *psport_adapter, BOOL en);
	void (*hal_sport_tx_dma_start)(hal_sport_adapter_t *psport_adapter, BOOL en);
	u32(*hal_sport_get_tx_dma_start_sta)(hal_sport_adapter_t *psport_adapter);
	void (*hal_sport_rx_dma_start)(hal_sport_adapter_t *psport_adapter, BOOL en);
	u32(*hal_sport_get_rx_dma_start_sta)(hal_sport_adapter_t *psport_adapter);
	void (*hal_sport_dma_buffer)(hal_sport_adapter_t *psport_adapter, hal_sport_buf_params_t *pbuf_params);
	int *(*hal_sport_get_tx0_page)(hal_sport_adapter_t *psport_adapter);
	int *(*hal_sport_get_tx1_page)(hal_sport_adapter_t *psport_adapter);
	void (*hal_sport_tx0_page_send)(hal_sport_adapter_t *psport_adapter, u32 *pbuf);
	void (*hal_sport_tx1_page_send)(hal_sport_adapter_t *psport_adapter, u32 *pbuf);
	u32(*hal_sport_rx0_page_recv)(hal_sport_adapter_t *psport_adapter);
	u32(*hal_sport_rx1_page_recv)(hal_sport_adapter_t *psport_adapter);
	u32(*hal_sport_get_tx_fifo_err)(hal_sport_adapter_t *psport_adapter);
	u32(*hal_sport_get_rx_fifo_err)(hal_sport_adapter_t *psport_adapter);
	void (*hal_sport_clr_tx_fifo_err)(hal_sport_adapter_t *psport_adapter);
	void (*hal_sport_clr_rx_fifo_err)(hal_sport_adapter_t *psport_adapter);
	void (*hal_sport_fifo_cb_handler)(hal_sport_adapter_t *psport_adapter, sport_irq_user_cb_t callback, u32 *arg);
	void (*hal_sport_tx0_dma_cb_handler)(hal_sport_adapter_t *psport_adapter, sport_irq_user_cb_t callback, u32 *arg);
	void (*hal_sport_tx1_dma_cb_handler)(hal_sport_adapter_t *psport_adapter, sport_irq_user_cb_t callback, u32 *arg);
	void (*hal_sport_rx0_dma_cb_handler)(hal_sport_adapter_t *psport_adapter, sport_irq_user_cb_t callback, u32 *arg);
	void (*hal_sport_rx1_dma_cb_handler)(hal_sport_adapter_t *psport_adapter, sport_irq_user_cb_t callback, u32 *arg);
	void (*hal_sport_dma_err_cb_handler)(hal_sport_adapter_t *psport_adapter, sport_irq_user_cb_t callback, u32 *arg);
	void (*hal_sport_fixed_bclk)(hal_sport_adapter_t *psport_adapter, BOOL fixed_en, sport_fixed_bclk_t fixed_bclk_sel);
	void (*hal_sport_rx_same_fs)(hal_sport_adapter_t *psport_adapter, BOOL en);
} hal_sport_func_stubs_t;

/**
 *  @brief Get the DMA interrupt status of TX0.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  TX0 interrupt status
 */
__STATIC_INLINE
u32 hal_rtl_sport_get_tx0_dma_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	return psport_reg->SPORT_SP_TX0_DMA_INT_STA;

}

/**
 *  @brief Get the DMA interrupt status of TX1.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  TX1 interrupt status
 */
__STATIC_INLINE
u32 hal_rtl_sport_get_tx1_dma_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	return psport_reg->SPORT_SP_TX1_DMA_INT_STA;

}

/**
 *  @brief Get the DMA interrupt status of RX0.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  RX0 interrupt status
 */
__STATIC_INLINE
u32 hal_rtl_sport_get_rx0_dma_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	return psport_reg->SPORT_SP_RX0_DMA_INT_STA;

}

/**
 *  @brief Get the DMA interrupt status of RX1.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  RX1 interrupt status
 */
__STATIC_INLINE
u32 hal_rtl_sport_get_rx1_dma_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	return psport_reg->SPORT_SP_RX1_DMA_INT_STA;

}

/**
 *  @brief Get the DMA error interrupt status of TX0.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  TX0 error interrupt status
 */
__STATIC_INLINE
u32 hal_rtl_sport_get_tx0_dma_err_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	return (psport_reg->SPORT_SP_TX0_DMA_INT_STA & 0xF0F00);

}

/**
 *  @brief Get the DMA error interrupt status of TX1.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  TX1 error interrupt status
 */
__STATIC_INLINE
u32 hal_rtl_sport_get_tx1_dma_err_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	return (psport_reg->SPORT_SP_TX1_DMA_INT_STA & 0xF0F00);

}

/**
 *  @brief Get the DMA error interrupt status of RX0.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  RX0 error interrupt status
 */
__STATIC_INLINE
u32 hal_rtl_sport_get_rx0_dma_err_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	return (psport_reg->SPORT_SP_RX0_DMA_INT_STA & 0xF0F00);

}

/**
 *  @brief Get the DMA error interrupt status of RX1.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  RX1 error interrupt status
 */
__STATIC_INLINE
u32 hal_rtl_sport_get_rx1_dma_err_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	return (psport_reg->SPORT_SP_RX1_DMA_INT_STA & 0xF0F00);

}

/**
 *  @brief Get the DMA page interrupt status of TX0.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  TX0 page interrupt status
 */
__STATIC_INLINE
u32 hal_rtl_sport_get_tx0_dma_page_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	return (psport_reg->SPORT_SP_TX0_DMA_INT_STA & 0x0f);

}

/**
 *  @brief Get the DMA page interrupt status of TX1.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  TX1 page interrupt status
 */
__STATIC_INLINE
u32 hal_rtl_sport_get_tx1_dma_page_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	return (psport_reg->SPORT_SP_TX1_DMA_INT_STA & 0x0f);

}

/**
 *  @brief Get the DMA page interrupt status of RX0.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  RX0 page interrupt status
 */
__STATIC_INLINE
u32 hal_rtl_sport_get_rx0_dma_page_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	return (psport_reg->SPORT_SP_RX0_DMA_INT_STA & 0x0f);

}

/**
 *  @brief Get the DMA page interrupt status of RX1.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  RX1 page interrupt status
 */
__STATIC_INLINE
u32 hal_rtl_sport_get_rx1_dma_page_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	return (psport_reg->SPORT_SP_RX1_DMA_INT_STA & 0x0f);

}

/**
 *  @brief Clear the DMA interrupt status of TX0.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  void
 */
__STATIC_INLINE
void hal_rtl_sport_clr_tx0_dma_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	u32 temp_reg;

	temp_reg = psport_reg->SPORT_SP_TX0_DMA_INT_STA;

	psport_reg->SPORT_SP_TX0_DMA_INT_STA = temp_reg;

}

/**
 *  @brief Clear the DMA interrupt status of TX1.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  void
 */
__STATIC_INLINE
void hal_rtl_sport_clr_tx1_dma_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	u32 temp_reg;

	temp_reg = psport_reg->SPORT_SP_TX1_DMA_INT_STA;

	psport_reg->SPORT_SP_TX1_DMA_INT_STA = temp_reg;

}

/**
 *  @brief Clear the DMA interrupt status of RX0.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  void
 */
__STATIC_INLINE
void hal_rtl_sport_clr_rx0_dma_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	u32 temp_reg;

	temp_reg = psport_reg->SPORT_SP_RX0_DMA_INT_STA;

	psport_reg->SPORT_SP_RX0_DMA_INT_STA = temp_reg;

}

/**
 *  @brief Clear the DMA interrupt status of RX1.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  void
 */
__STATIC_INLINE
void hal_rtl_sport_clr_rx1_dma_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	u32 temp_reg;

	temp_reg = psport_reg->SPORT_SP_RX1_DMA_INT_STA;

	psport_reg->SPORT_SP_RX1_DMA_INT_STA = temp_reg;

}

/**
 *  @brief Clear the DMA page n status of TX0.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] page Set page n
 *
 *  @returns  void
 */
__STATIC_INLINE
void hal_rtl_sport_clr_tx0_page_intr(hal_sport_adapter_t *psport_adapter, sport_page page)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	psport_reg->SPORT_SP_TX0_DMA_INT_STA &= page;

}

/**
 *  @brief Clear the DMA page n status of TX1.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] page Set page n
 *
 *  @returns  void
 */
__STATIC_INLINE
void hal_rtl_sport_clr_tx1_page_intr(hal_sport_adapter_t *psport_adapter, sport_page page)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	psport_reg->SPORT_SP_TX1_DMA_INT_STA &= page;

}

/**
 *  @brief Clear the DMA page n status of RX0.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] page Set page n
 *
 *  @returns  void
 */
__STATIC_INLINE
void hal_rtl_sport_clr_rx0_page_intr(hal_sport_adapter_t *psport_adapter, sport_page page)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	psport_reg->SPORT_SP_RX0_DMA_INT_STA &= page;

}

/**
 *  @brief Clear the DMA page n status of RX1.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] page Set page n
 *
 *  @returns  void
 */
__STATIC_INLINE
void hal_rtl_sport_clr_rx1_page_intr(hal_sport_adapter_t *psport_adapter, sport_page page)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	psport_reg->SPORT_SP_RX1_DMA_INT_STA &= page;

}

/**
 *  @brief Get the SPORT page number.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  The SPORT page number
 */
__STATIC_INLINE
u32 hal_rtl_sport_get_page_number(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	return (psport_reg->SPORT_SP_DMA_CON & SPORT_MASK_SP_PAGE_NUM) >> SPORT_SHIFT_SP_PAGE_NUM;

}

/**
 *  @brief Set TX0 FIFO data.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] tx0_data Set TX0 data
 *
 *  @returns  void
 */
__STATIC_INLINE
void hal_rtl_sport_set_tx0_fifo(hal_sport_adapter_t *psport_adapter, u32 tx0_data)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	psport_reg->SPORT_SP_TX_FIFO_0 = tx0_data;

}

/**
 *  @brief Set TX1 FIFO data.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] tx1_data Set TX1 data
 *
 *  @returns  void
 */
__STATIC_INLINE
void hal_rtl_sport_set_tx1_fifo(hal_sport_adapter_t *psport_adapter, u32 tx1_data)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	psport_reg->SPORT_SP_TX_FIFO_1 = tx1_data;

}

/**
 *  @brief Get RX0 FIFO data.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] rx0_data Get RX0 data
 *
 *  @returns  FIFO value
 */
__STATIC_INLINE
u32 hal_rtl_sport_get_rx0_fifo(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	return psport_reg->SPORT_SP_RX_FIFO_0;

}

/**
 *  @brief Get RX1 FIFO data.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *  @param[in] rx1_data Get RX1 data
 *
 *  @returns  FIFO value
 */
__STATIC_INLINE
u32 hal_rtl_sport_get_rx1_fifo(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	return psport_reg->SPORT_SP_RX_FIFO_1;

}

/**
 *  @brief Get TX FIFO_0 depth status.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  When TX FIFO_0 is empty, this value shows 32.
 */
__STATIC_INLINE
u32 hal_rtl_sport_get_tx0_depth_cnt(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	return (psport_reg->SPORT_SP_FIFO_CNT_STA & SPORT_MASK_SP_TX_DEPTH_CNT_0) >> SPORT_SHIFT_SP_TX_DEPTH_CNT_0;

}

/**
 *  @brief Get RX FIFO_0 depth status.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  When RX FIFO_0 is full, this value shows 32.
 */
__STATIC_INLINE
u32 hal_rtl_sport_get_rx0_depth_cnt(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	return (psport_reg->SPORT_SP_FIFO_CNT_STA & SPORT_MASK_SP_RX_DEPTH_CNT_0) >> SPORT_SHIFT_SP_RX_DEPTH_CNT_0;

}

/**
 *  @brief Get TX FIFO_1 depth status.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  When TX FIFO_1 is empty, this value shows 32.
 */
__STATIC_INLINE
u32 hal_rtl_sport_get_tx1_depth_cnt(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	return (psport_reg->SPORT_SP_FIFO_CNT_STA & SPORT_MASK_SP_TX_DEPTH_CNT_1) >> SPORT_SHIFT_SP_TX_DEPTH_CNT_1;

}

/**
 *  @brief Get RX FIFO_1 depth status.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  When RX FIFO_1 is full, this value shows 32.
 */
__STATIC_INLINE
u32 hal_rtl_sport_get_rx1_depth_cnt(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	return (psport_reg->SPORT_SP_FIFO_CNT_STA & SPORT_MASK_SP_RX_DEPTH_CNT_1) >> SPORT_SHIFT_SP_RX_DEPTH_CNT_1;

}

/**
 *  @brief Clear TX0 TH interrupt.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  void
 */
__STATIC_INLINE
void hal_rtl_sport_clr_tx0_th_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	psport_reg->SPORT_SP_FIFO_INTR_CON |= SPORT_BIT_SP_CLR_TX_FIFO_TH_INTR_0;
	psport_reg->SPORT_SP_FIFO_INTR_CON &= ~(SPORT_BIT_SP_CLR_TX_FIFO_TH_INTR_0);
}

/**
 *  @brief Clear RX0 TH interrupt.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  void
 */
__STATIC_INLINE
void hal_rtl_sport_clr_rx0_th_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	psport_reg->SPORT_SP_FIFO_INTR_CON |= SPORT_BIT_SP_CLR_RX_FIFO_TH_INTR_0;
	psport_reg->SPORT_SP_FIFO_INTR_CON &= ~(SPORT_BIT_SP_CLR_RX_FIFO_TH_INTR_0);
}

/**
 *  @brief Clear TX0 full interrupt.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  void
 */
__STATIC_INLINE
void hal_rtl_sport_clr_tx0_full_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	psport_reg->SPORT_SP_FIFO_INTR_CON |= SPORT_BIT_SP_CLR_TX_FIFO_FULL_INTR_0;
	psport_reg->SPORT_SP_FIFO_INTR_CON &= ~(SPORT_BIT_SP_CLR_TX_FIFO_FULL_INTR_0);
}

/**
 *  @brief Clear RX0 full interrupt.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  void
 */
__STATIC_INLINE
void hal_rtl_sport_clr_rx0_full_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	psport_reg->SPORT_SP_FIFO_INTR_CON |= SPORT_BIT_SP_CLR_RX_FIFO_FULL_INTR_0;
	psport_reg->SPORT_SP_FIFO_INTR_CON &= ~(SPORT_BIT_SP_CLR_RX_FIFO_FULL_INTR_0);
}

/**
 *  @brief Clear TX0 empty interrupt.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  void
 */
__STATIC_INLINE
void hal_rtl_sport_clr_tx0_empty_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	psport_reg->SPORT_SP_FIFO_INTR_CON |= SPORT_BIT_SP_CLR_TX_FIFO_EMPTY_0;
	psport_reg->SPORT_SP_FIFO_INTR_CON &= ~(SPORT_BIT_SP_CLR_TX_FIFO_EMPTY_0);
}

/**
 *  @brief Clear RX0 empty interrupt.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  void
 */
__STATIC_INLINE
void hal_rtl_sport_clr_rx0_empty_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	psport_reg->SPORT_SP_FIFO_INTR_CON |= SPORT_BIT_SP_CLR_RX_FIFO_EMPTY_0;
	psport_reg->SPORT_SP_FIFO_INTR_CON &= ~(SPORT_BIT_SP_CLR_RX_FIFO_EMPTY_0);
}

/**
 *  @brief Clear TX0 idle interrupt.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  void
 */
__STATIC_INLINE
void hal_rtl_sport_clr_tx0_idle_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	psport_reg->SPORT_SP_FIFO_INTR_CON |= SPORT_BIT_SP_CLR_TX_IDLE_INTR_0;
	psport_reg->SPORT_SP_FIFO_INTR_CON &= ~(SPORT_BIT_SP_CLR_TX_IDLE_INTR_0);
}

/**
 *  @brief Clear TX1 TH interrupt.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  void
 */
__STATIC_INLINE
void hal_rtl_sport_clr_tx1_th_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	psport_reg->SPORT_SP_FIFO_INTR_CON |= SPORT_BIT_SP_CLR_TX_FIFO_TH_INTR_1;
	psport_reg->SPORT_SP_FIFO_INTR_CON &= ~(SPORT_BIT_SP_CLR_TX_FIFO_TH_INTR_1);
}

/**
 *  @brief Clear RX1 TH interrupt.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  void
 */
__STATIC_INLINE
void hal_rtl_sport_clr_rx1_th_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	psport_reg->SPORT_SP_FIFO_INTR_CON |= SPORT_BIT_SP_CLR_RX_FIFO_TH_INTR_1;
	psport_reg->SPORT_SP_FIFO_INTR_CON &= ~(SPORT_BIT_SP_CLR_RX_FIFO_TH_INTR_1);
}

/**
 *  @brief Clear TX1 full interrupt.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  void
 */
__STATIC_INLINE
void hal_rtl_sport_clr_tx1_full_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	psport_reg->SPORT_SP_FIFO_INTR_CON |= SPORT_BIT_SP_CLR_TX_FIFO_FULL_INTR_1;
	psport_reg->SPORT_SP_FIFO_INTR_CON &= ~(SPORT_BIT_SP_CLR_TX_FIFO_FULL_INTR_1);
}

/**
 *  @brief Clear RX1 full interrupt.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  void
 */
__STATIC_INLINE
void hal_rtl_sport_clr_rx1_full_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	psport_reg->SPORT_SP_FIFO_INTR_CON |= SPORT_BIT_SP_CLR_RX_FIFO_FULL_INTR_1;
	psport_reg->SPORT_SP_FIFO_INTR_CON &= ~(SPORT_BIT_SP_CLR_RX_FIFO_FULL_INTR_1);
}

/**
 *  @brief Clear TX1 empty interrupt.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  void
 */
__STATIC_INLINE
void hal_rtl_sport_clr_tx1_empty_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	psport_reg->SPORT_SP_FIFO_INTR_CON |= SPORT_BIT_SP_CLR_TX_FIFO_EMPTY_1;
	psport_reg->SPORT_SP_FIFO_INTR_CON &= ~(SPORT_BIT_SP_CLR_TX_FIFO_EMPTY_1);
}

/**
 *  @brief Clear RX1 empty interrupt.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  void
 */
__STATIC_INLINE
void hal_rtl_sport_clr_rx1_empty_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	psport_reg->SPORT_SP_FIFO_INTR_CON |= SPORT_BIT_SP_CLR_RX_FIFO_EMPTY_1;
	psport_reg->SPORT_SP_FIFO_INTR_CON &= ~(SPORT_BIT_SP_CLR_RX_FIFO_EMPTY_1);
}

/**
 *  @brief Clear TX1 idle interrupt.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  void
 */
__STATIC_INLINE
void hal_rtl_sport_clr_tx1_idle_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	psport_reg->SPORT_SP_FIFO_INTR_CON |= SPORT_BIT_SP_CLR_TX_IDLE_INTR_1;
	psport_reg->SPORT_SP_FIFO_INTR_CON &= ~(SPORT_BIT_SP_CLR_TX_IDLE_INTR_1);
}

/**
 *  @brief Get the FIFO interrupt status.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns FIFO interrupt status.
 */
__STATIC_INLINE
u32 hal_rtl_sport_get_fifo_intr_sta(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;

	return (psport_reg->SPORT_SP_FIFO_INTR_STA & 0x3FFF);
}

/**
 *  @brief Get TX0 TH interrupt.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  FIFO TX0 TH interrupt status.
 */
__STATIC_INLINE
u32 hal_rtl_sport_get_tx0_th_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	u32 temp_reg;

	temp_reg = psport_reg->SPORT_SP_FIFO_INTR_CON;
	temp_reg = psport_reg->SPORT_SP_FIFO_INTR_STA & (((temp_reg >> 17) & 0x3F80) | ((temp_reg >> 16) & 0x7F));

	return ((temp_reg & SPORT_BIT_SP_TX_FIFO_TH_INTR_0) >> SPORT_SHIFT_SP_TX_FIFO_TH_INTR_0);
}

/**
 *  @brief Get RX0 TH interrupt.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  FIFO RX0 TH interrupt status.
 */
__STATIC_INLINE
u32 hal_rtl_sport_get_rx0_th_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	u32 temp_reg;

	temp_reg = psport_reg->SPORT_SP_FIFO_INTR_CON;
	temp_reg = psport_reg->SPORT_SP_FIFO_INTR_STA & (((temp_reg >> 17) & 0x3F80) | ((temp_reg >> 16) & 0x7F));

	return ((temp_reg & SPORT_BIT_SP_RX_FIFO_TH_INTR_0) >> SPORT_SHIFT_SP_RX_FIFO_TH_INTR_0);
}

/**
 *  @brief Get TX0 full interrupt.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  FIFO TX0 full interrupt status.
 */
__STATIC_INLINE
u32 hal_rtl_sport_get_tx0_full_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	u32 temp_reg;

	temp_reg = psport_reg->SPORT_SP_FIFO_INTR_CON;
	temp_reg = psport_reg->SPORT_SP_FIFO_INTR_STA & (((temp_reg >> 17) & 0x3F80) | ((temp_reg >> 16) & 0x7F));

	return ((temp_reg & SPORT_BIT_SP_TX_FIFO_FULL_INTR_0) >> SPORT_SHIFT_SP_TX_FIFO_FULL_INTR_0);
}

/**
 *  @brief Get RX0 full interrupt.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  FIFO RX0 full interrupt status.
 */
__STATIC_INLINE
u32 hal_rtl_sport_get_rx0_full_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	u32 temp_reg;

	temp_reg = psport_reg->SPORT_SP_FIFO_INTR_CON;
	temp_reg = psport_reg->SPORT_SP_FIFO_INTR_STA & (((temp_reg >> 17) & 0x3F80) | ((temp_reg >> 16) & 0x7F));

	return ((temp_reg & SPORT_BIT_SP_RX_FIFO_FULL_INTR_0) >> SPORT_SHIFT_SP_RX_FIFO_FULL_INTR_0);
}

/**
 *  @brief Get TX0 empty interrupt.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  FIFO TX0 empty interrupt status.
 */
__STATIC_INLINE
u32 hal_rtl_sport_get_tx0_empty_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	u32 temp_reg;

	temp_reg = psport_reg->SPORT_SP_FIFO_INTR_CON;
	temp_reg = psport_reg->SPORT_SP_FIFO_INTR_STA & (((temp_reg >> 17) & 0x3F80) | ((temp_reg >> 16) & 0x7F));

	return ((temp_reg & SPORT_BIT_SP_TX_FIFO_EMPTY_INTR_0) >> SPORT_SHIFT_SP_TX_FIFO_EMPTY_INTR_0);
}

/**
 *  @brief Get RX0 empty interrupt.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  RX0 empty interrupt status.
 */
__STATIC_INLINE
u32 hal_rtl_sport_get_rx0_empty_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	u32 temp_reg;

	temp_reg = psport_reg->SPORT_SP_FIFO_INTR_CON;
	temp_reg = psport_reg->SPORT_SP_FIFO_INTR_STA & (((temp_reg >> 17) & 0x3F80) | ((temp_reg >> 16) & 0x7F));

	return ((temp_reg & SPORT_BIT_SP_RX_FIFO_EMPTY_INTR_0) >> SPORT_SHIFT_SP_RX_FIFO_EMPTY_INTR_0);
}

/**
 *  @brief Get TX0 idle interrupt.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  TX0 idle interrupt status.
 */
__STATIC_INLINE
u32 hal_rtl_sport_get_tx0_idle_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	u32 temp_reg;

	temp_reg = psport_reg->SPORT_SP_FIFO_INTR_CON;
	temp_reg = psport_reg->SPORT_SP_FIFO_INTR_STA & (((temp_reg >> 17) & 0x3F80) | ((temp_reg >> 16) & 0x7F));

	return ((temp_reg & SPORT_BIT_SP_TX_IDLE_INTR_0) >> SPORT_SHIFT_SP_TX_IDLE_INTR_0);
}

/**
 *  @brief Get TX1 TH interrupt.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  TX1 TH interrupt status.
 */
__STATIC_INLINE
u32 hal_rtl_sport_get_tx1_th_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	u32 temp_reg;

	temp_reg = psport_reg->SPORT_SP_FIFO_INTR_CON;
	temp_reg = psport_reg->SPORT_SP_FIFO_INTR_STA & (((temp_reg >> 17) & 0x3F80) | ((temp_reg >> 16) & 0x7F));

	return ((temp_reg & SPORT_BIT_SP_TX_FIFO_TH_INTR_1) >> SPORT_SHIFT_SP_TX_FIFO_TH_INTR_1);
}

/**
 *  @brief Get RX1 TH interrupt.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  RX1 TH interrupt status.
 */
__STATIC_INLINE
u32 hal_rtl_sport_get_rx1_th_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	u32 temp_reg;

	temp_reg = psport_reg->SPORT_SP_FIFO_INTR_CON;
	temp_reg = psport_reg->SPORT_SP_FIFO_INTR_STA & (((temp_reg >> 17) & 0x3F80) | ((temp_reg >> 16) & 0x7F));

	return ((temp_reg & SPORT_BIT_SP_RX_FIFO_TH_INTR_1) >> SPORT_SHIFT_SP_RX_FIFO_TH_INTR_1);
}

/**
 *  @brief Get TX1 full interrupt.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  TX1 full interrupt status.
 */
__STATIC_INLINE
u32 hal_rtl_sport_get_tx1_full_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	u32 temp_reg;

	temp_reg = psport_reg->SPORT_SP_FIFO_INTR_CON;
	temp_reg = psport_reg->SPORT_SP_FIFO_INTR_STA & (((temp_reg >> 17) & 0x3F80) | ((temp_reg >> 16) & 0x7F));

	return ((temp_reg & SPORT_BIT_SP_TX_FIFO_FULL_INTR_1) >> SPORT_SHIFT_SP_TX_FIFO_FULL_INTR_1);
}

/**
 *  @brief Get RX1 full interrupt.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  RX1 full interrupt status.
 */
__STATIC_INLINE
u32 hal_rtl_sport_get_rx1_full_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	u32 temp_reg;

	temp_reg = psport_reg->SPORT_SP_FIFO_INTR_CON;
	temp_reg = psport_reg->SPORT_SP_FIFO_INTR_STA & (((temp_reg >> 17) & 0x3F80) | ((temp_reg >> 16) & 0x7F));

	return ((temp_reg & SPORT_BIT_SP_RX_FIFO_FULL_INTR_1) >> SPORT_SHIFT_SP_RX_FIFO_FULL_INTR_1);
}

/**
 *  @brief Get TX1 empty interrupt.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  TX1 empty interrupt status.
 */
__STATIC_INLINE
u32 hal_rtl_sport_get_tx1_empty_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	u32 temp_reg;

	temp_reg = psport_reg->SPORT_SP_FIFO_INTR_CON;
	temp_reg = psport_reg->SPORT_SP_FIFO_INTR_STA & (((temp_reg >> 17) & 0x3F80) | ((temp_reg >> 16) & 0x7F));

	return ((temp_reg & SPORT_BIT_SP_TX_FIFO_EMPTY_INTR_1) >> SPORT_SHIFT_SP_TX_FIFO_EMPTY_INTR_1);
}

/**
 *  @brief Get RX1 empty interrupt.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  RX1 empty interrupt status.
 */
__STATIC_INLINE
u32 hal_rtl_sport_get_rx1_empty_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	u32 temp_reg;

	temp_reg = psport_reg->SPORT_SP_FIFO_INTR_CON;
	temp_reg = psport_reg->SPORT_SP_FIFO_INTR_STA & (((temp_reg >> 17) & 0x3F80) | ((temp_reg >> 16) & 0x7F));

	return ((temp_reg & SPORT_BIT_SP_RX_FIFO_EMPTY_INTR_1) >> SPORT_SHIFT_SP_RX_FIFO_EMPTY_INTR_1);
}

/**
 *  @brief Get TX1 idle interrupt.
 *
 *  @param[in] psport_adapter The SPORT adapter.
 *
 *  @returns  TX1 idle interrupt status.
 */
__STATIC_INLINE
u32 hal_rtl_sport_get_tx1_idle_intr(hal_sport_adapter_t *psport_adapter)
{
	SPORT_TypeDef *psport_reg = (SPORT_TypeDef *)psport_adapter->base_addr;
	u32 temp_reg;

	temp_reg = psport_reg->SPORT_SP_FIFO_INTR_CON;
	temp_reg = psport_reg->SPORT_SP_FIFO_INTR_STA & (((temp_reg >> 17) & 0x3F80) | ((temp_reg >> 16) & 0x7F));

	return ((temp_reg & SPORT_BIT_SP_TX_IDLE_INTR_1) >> SPORT_SHIFT_SP_TX_IDLE_INTR_1);
}




#ifdef __cplusplus
}
#endif

#endif  // #ifndef _RTL8735BH_SPORT_H_

