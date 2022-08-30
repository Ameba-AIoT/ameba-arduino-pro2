/**************************************************************************//**
 * @file     rtl819bhp_i2c.h
 * @brief    The fundamental definition for RTL8195B HP i2C module.
 * @version  V1.00
 * @date     2017-03-07
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2016 Realtek Corporation. All rights reserved.
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



#ifndef _RTL8735B_I2C_H_
#define _RTL8735B_I2C_H_

#include "rtl8735b_i2c_type.h"
#include "rtl8735b_peri_id.h"
#ifdef __cplusplus
extern "C" {
#endif
/**
 * @addtogroup hs_hal_i2c I2C
 * @{
 */

//#define LOCAL_SVD_DECLARATION
#undef LOCAL_SVD_DECLARATION
//this flag should be checked again when system integration is done.

#define TX_ABRT_TEMP_PATCH  //This flag should be removed when tx_abrt bit15 is fixed to a correct hardware in DMA mode

/// i2c module number
#define HP_I2C_NO               4
/// i2c IRQ Priority
#define HP_I2C_IRQ_PR           3
/// i2c address retry time-out
#define HP_I2C_ATRY_TO          3000
/// i2c master mode address retry function
#define HP_I2C_ADD_RETRY        1
/// i2c master mode address retry max count
#define HP_I2C_ADD_RTY_MAX      256
/// i2c default DMA TX src width
#define HP_I2C_DMA_DEFAULT_TX_SRC_WIDTH     4
/// i2c default DMA RX des width
#define HP_I2C_DMA_DEFAULT_RX_DES_WIDTH     4
/// i2c timeout check disabled
#define HP_I2C_TIMEOUT_DISABLE  0x00
/// i2c timeout check endless
#define HP_I2C_TIMEOUT_ENDLESS  0xFFFFFFFF
/// i2c TX FIFO entry number
#define HP_I2C_TX_FIFO_DEPTH    32
/// i2c RX FIFO entry number
#define HP_I2C_RX_FIFO_DEPTH    32
/// i2c DMA transfer max length
#define HP_I2C_DMA_MAX_LEN      65535
/// i2c filter CAP. low length
#define HP_I2C_FLTR_CAP_L_LEN   20
/// i2c filter CAP. main length
#define HP_I2C_FLTR_CAP_M_LEN   5
/// i2c filter Resis. low length
#define HP_I2C_FLTR_RSTS_L_LEN  20
/// i2c filter Resis. main length
#define HP_I2C_FLTR_RSTS_M_LEN  20

#define HP_VNDR_ISR_BASE        0x40002800
/** @defgroup i2c_reg_bit_macro I2C REG BIT MACRO
 *  bit-operation macros for i2c registers
 *  @{
 */
/** @} */ // end of I2C REG BIT MACRO

/** \brief i2c mode
*/
enum i2c_mode_e {
	I2CSlaveMode    =   0,                  /*!< 0: for i2c slave mode    */
	I2CMasterMode   =   1,                  /*!< 1: for i2c master mode    */
};

/** \brief i2c read/write
*/
enum i2c_read_write_e {
	I2CWrite        =   0,                  /*!< 0: for i2c write command    */
	I2CRead         =   1,                  /*!< 1: for i2c read command    */
};

/** \brief i2c address mode
*/
enum i2c_addr_mode_e {
	I2CAddress7bit     =   0,               /*!< 0: for i2c 7-bit address mode    */
	I2CAddress10bit    =   1,               /*!< 1: for i2c 10-bit address mode    */
};

/** \brief i2c speed mode
*/
enum i2c_spd_mode_e {
	I2CStandardSpeed    =   1,              /*!< 1: for i2c standard speed mode    */
	I2CFastSpeed        =   2,              /*!< 2: for i2c fast speed mode    */
	I2CHighSpeed        =   3,              /*!< 3: for i2c high speed mode    */
};

/** \brief i2c feature status
*/
enum i2c_enable_status_e {
	I2CDisable      =   0,                  /*!< 0: for i2c disable state    */
	I2CEnable       =   1,                  /*!< 1: for i2c enable state    */
	I2CForceDisable =   2,                  /*!< 2: for i2c force disable enable state    */
};

/** \brief i2c dma type
*/
enum i2c_dma_mod_e {
	I2CDmaDwc   =   0,                      /*!< 0: for i2c dwc dma mode    */
	I2CDmaReg   =   1,                      /*!< 1: for i2c register-based dma mode    */
	I2CDmaDes   =   2,                      /*!< 2: for i2c descritptor mode    */
};

/** \brief i2c general call or start byte
*/
enum i2c_gc_sb_e {
	I2CGeneralCall      =   0,                      /*!< 0: for i2c master could general call    */
	I2CStartByte        =   1,                      /*!< 1: for i2c master could START byte    */
};

/** \brief i2c bus status
*/
enum i2c_bus_status_e {
	I2CBusIdle          =   0,                      /*!< 0: for i2c bus in idle state    */
	I2CBusAddressPhase  =   1,                      /*!< 1: for i2c bus in address phase    */
	I2CBusDataPhase     =   2,                      /*!< 2: for i2c bus in data phase    */
	I2CBusClockStretch  =   3,                      /*!< 2: for i2c bus in clock stretch phase    */
};

/** \brief i2c module state
*/
enum i2c_status_e {
	I2CStatusUninitial      =   0x00,               /*!< 0x00: i2c uninitial state   */
	I2CStatusInitialized    =   0x01,               /*!< 0x01: i2c initialized state   */
	I2CStatusIdle           =   0x02,               /*!< 0x02: i2c idle state   */

	I2CStatusTxReady        =   0x03,               /*!< 0x03: i2c TX ready state   */
	I2CStatusTxing          =   0x04,               /*!< 0x04: i2c TXing state   */

	I2CStatusRxReady        =   0x05,               /*!< 0x05: i2c RX ready state   */
	I2CStatusRxing          =   0x06,               /*!< 0x06: i2c RXing state   */

	I2CStatusDisable        =   0x07,               /*!< 0x07: i2c disabled state   */
	I2CStatusError          =   0x10,               /*!< 0x10: i2c error state   */
	I2CStatusTimeOut        =   0x11,               /*!< 0x11: i2c time-out state   */
};

/** \brief i2c module operation
*/
enum i2c_operation_mode_e {
	I2CModePoll         =   0x00,                   /*!< 0x00: i2c module in poll mode   */
	I2CModeInterrupt    =   0x01,                   /*!< 0x01: i2c module in interrupt mode   */
	I2CModeDMA          =   0x02,                   /*!< 0x02: i2c module in DMA mode   */
};

/** \brief i2c module master special functions
*/
enum i2c_master_speicial_func_e {
	I2CAddressRetry     =   0x01,                   /*!< 0x01: i2c master mode could do address retry   */
	I2CMasterRestart    =   0x02,                   /*!< 0x02: i2c master mode could send RESTART   */
};

/** \brief i2c module slave special functions
*/
enum i2c_slave_speicial_func_e {
	I2CSlaveRXBySTPSTR =   0x01,                    /*!< 0x01: i2c slave mode receiving would end by STOP or START bit*/
};

/** \brief i2c module error type
*/
enum i2c_err_type_e {
	I2CErrorNone            =   0x00,               /*!< 0x00: i2c has no errors    */
	I2CErrorRxUnder         =   0x01,               /*!< 0x01: i2c has RX underflow error    */
	I2CErrorRxOver          =   0x02,               /*!< 0x02: i2c has RX overflow error    */
	I2CErrorRxDone          =   0x03,               /*!< 0x03: i2c has RX Done error    */
	I2CErrorTxOver          =   0x04,               /*!< 0x04: i2c has TX overflow error    */
	I2CErrorTxAbort         =   0x08,               /*!< 0x08: i2c has TX abort error    */
	I2CErrorSlaveTxNack     =   0x10,               /*!< 0x10: i2c has slave TX NACK error    */

	I2CErrorMasterAddrNack  =   0x12,               /*!< 0x12: i2c master sends address and gets NACK    */
	I2CErrorMasterDataNack  =   0x13,               /*!< 0x13: i2c master sends data and gets NACK    */
	I2CErrorMasterLostArb   =   0x14,               /*!< 0x14: i2c master lost bus arbitration    */

	I2CErrorRxCmdTimeOut    =   0x21,               /*!< 0x21: i2c master sends RX command and time-out happens    */
	I2CErrorRxFIFOTimeOut   =   0x22,               /*!< 0x22: i2c read RX data and time-out happens    */
	I2CErrorTxCmdTimeOut    =   0x23,               /*!< 0x23: i2c master sends TX command and time-out happens    */
	I2CErrorTxFIFOTimeOut   =   0x24,               /*!< 0x24: i2c fill TX data and time-out happens    */

	I2CErrorTxAddrTimeOut   =   0x25,               /*!< 0x25: i2c master sends TX address retry and time-out happens    */
	I2CErrorRxAddrTimeOut   =   0x26,               /*!< 0x26: i2c master sends RX address retry and time-out happens    */
	I2CErrorTarTimeOut      =   0x27,               /*!< 0x27: i2c master sets target address and time-out happens    */

	I2CErrorSlaveLostArb    =   0x30,               /*!< 0x30: i2c slave lost bus arbitration    */
	I2CErrorSlaveFlushFIFO  =   0x31,               /*!< 0x31: i2c slave flushes FIFO when getting RD Req. and TX FIFO
                                                               is NOT empty. */
	I2CErrorSlaveRDCmdInTX  =   0x32,               /*!< 0x32: i2c slave acts as a transmitter and a Read Cmd written
                                                               into TX FIFO */
};

/** \brief i2c dma channel status
*/
enum i2c_dma_ch_status_e {
	I2CDmaChNone            =   0x00,               /*!< 0x00: i2c got no channel    */
	I2CDmaChGot             =   0x01,               /*!< 0x00: i2c got a channel    */
	I2CDmaChInitialed       =   0x02,               /*!< 0x00: i2c got a channel and initialized it    */
};

/*  Macros for i2c SCL timing constant  */
/** @defgroup i2c_reg_scl_clock_constant I2C REG SCL CLOCK CONSTANT
 *  i2c SCL timing constant
 *  @{
 */
#define I2C_SS_MIN_SCL_HTIME    4000        //the unit is ns.
#define I2C_SS_MIN_SCL_LTIME    4700        //the unit is ns.

#define I2C_FS_MODIFY
#ifdef I2C_FS_MODIFY
#define I2C_FS_MIN_SCL_HTIME    900         //the unit is ns.
#define I2C_FS_MIN_SCL_LTIME    1000        //the unit is ns.
#else
#define I2C_FS_MIN_SCL_HTIME    600         //the unit is ns.
#define I2C_FS_MIN_SCL_LTIME    1300        //the unit is ns.
#endif

#define I2C_HS_MIN_SCL_HTIME_100    60      //the unit is ns, with bus loading = 100pf
#define I2C_HS_MIN_SCL_LTIME_100    120     //the unit is ns., with bus loading = 100pf

#define I2C_HS_MIN_SCL_HTIME_400    160     //the unit is ns, with bus loading = 400pf
#define I2C_HS_MIN_SCL_LTIME_400    320     //the unit is ns., with bus loading = 400pf

#define I2C_SS_HTIME_MIN        3
#define I2C_SS_LTIME_MIN        5

#define I2C_FS_HTIME_MIN        3
#define I2C_FS_LTIME_MIN        5

#define I2C_HS_HTIME_MIN        3
#define I2C_HS_LTIME_MIN        5

#define I2C_MST_SDA_HOLD_MIN    1
#define I2C_SLV_SDA_HOLD_MIN    7
/** @} */ // end of I2C REG SCL CLOCK CONSTANT

/** \brief i2c initail data structure */
typedef struct i2c_init_dat_s {
	uint8_t     index;                          /*!< Offset: 0x000   i2c index   */
	uint8_t     enable;                         /*!< Offset: 0x001   i2c enable state, updated by HAL   */
	uint8_t     master;                         /*!< Offset: 0x002   i2c master/slave state   */
	uint8_t     addr_mod;                       /*!< Offset: 0x003   i2c address mode   */

	uint8_t     spd_mod;                        /*!< Offset: 0x004   i2c speed mode   */
	uint8_t     sda_setup;                      /*!< Offset: 0x005   i2c SDA setup time   */
	uint8_t     ff_rxtl;                        /*!< Offset: 0x006   i2c RX FIFO Threshold, for RX_FULL state  */
	uint8_t     ff_txtl;                        /*!< Offset: 0x007   i2c TX FIFO Threshold, for TX_EMPTY state   */

	uint32_t    clock;                          /*!< Offset: 0x008   i2c SCL clock   */

	uint16_t    ack_addr0;                      /*!< Offset: 0x00c   i2c default target address in master mode,
                                                                 acknowledge address 0 in slave mode    */
	uint16_t    ack_addr1;                      /*!< Offset: 0x00e   i2c acknowledge address 1 in slave mode(only for slave)
                                                                 */

	uint16_t    sda_hold;                       /*!< Offset: 0x010   i2c SDA hold time   */
	uint8_t     bus_ld;                         /*!< Offset: 0x012   i2c bus loading   */
	uint8_t     dig_fltr_en;                    /*!< Offset: 0x013   i2c digital filter control   */

	uint8_t     dma_mod;                        /*!< Offset: 0x014   i2c DMA operation mode   */
	uint8_t     tx_dma_rq_lv;                   /*!< Offset: 0x015   i2c DMA TX request FIFO level   */
	uint8_t     rx_dma_rq_lv;                   /*!< Offset: 0x016   i2c DMA RX request FIFO level   */
	uint8_t     rx_dma_rq_lv_s1;                /*!< Offset: 0x017   i2c DMA RX request FIFO level for slave address 1  */

	I2C_TypeDef   *reg_base;                      /*!< Offset: 0x018   i2c register base address  */
	uint8_t     dig_fltr_lvl;                   /*!< Offset: 0x01C   i2c digital filter level  */
	uint8_t     hs_maddr;                       /*!< Offset: 0x01D   i2c high speed master code, only lsb 3 bits valid  */
	uint16_t    rsvd1;                          /*!< Offset: 0x01E   reserved 1  */
} i2c_init_dat_t, *pi2c_init_dat_t;

/** \brief i2c user callback adaptor
*/
typedef struct i2c_user_callback_adpt_s {
	VOID (*cb)(VOID *data);                         /*! i2c callback function */
	uint32_t    dat;                                /*! i2c callback function argument */
} i2c_user_callback_adpt_t, *pi2c_user_callback_adpt_t;

/** \brief i2c user callback
*/
typedef struct i2c_user_callback_s {
	i2c_user_callback_adpt_t  tx_empty;             /*! i2c transmit callback */
	i2c_user_callback_adpt_t  txc;                  /*! i2c transmit complete callback */
	i2c_user_callback_adpt_t  rx_full;              /*! i2c receive callback */
	i2c_user_callback_adpt_t  rxc;                  /*! i2c receive complete callback */
	i2c_user_callback_adpt_t  rd_req;               /*! i2c read request callback */
	i2c_user_callback_adpt_t  err;                  /*! i2c error callback */
	i2c_user_callback_adpt_t  dma_tx;               /*! i2c dma transmit callback */
	i2c_user_callback_adpt_t  dma_txc;              /*! i2c dma transmit complete callback */
	i2c_user_callback_adpt_t  dma_rx;               /*! i2c dma receive callback */
	i2c_user_callback_adpt_t  dma_rxc;              /*! i2c dma receive complete callback */
	i2c_user_callback_adpt_t  gen_call;             /*! i2c general call callback */
	i2c_user_callback_adpt_t  wake;                 /*! i2c wake up callback */
} i2c_user_callback_t, *pi2c_user_callback_t;

/** \brief i2c platform related data
*/
typedef struct i2c_platform_data_s {
#if IS_CUT_TEST(CONFIG_CHIP_VER)
	uint8_t         scl_pin;                        /*! i2c scl pin */
	uint8_t         sda_pin;                        /*! i2c scl pin */
#else
	uint32_t 		scl_pin;						/*! i2c scl pin */
	uint32_t 		sda_pin;						/*! i2c scl pin */

#endif
	uint8_t         rsvd0;                          /*! reserved 0 */
	uint8_t         tx_dma_bound;                   /*! i2c low bound to do tx-dma transmission,
                                                        if tx len is less than this bound, tx API
                                                        would change to poll mode transmission.*/
	uint8_t         rx_dma_bound;                   /*! i2c low bound to do rx-dma transmission,
                                                        if tx len is less than this bound, tx API
                                                        would change to poll mode transmission.*/
	uint32_t        tr_time_out;                    /*! i2c transmission time-out count */
} i2c_platform_data_t, *pi2c_platform_data_t;

/** \brief i2c transmit information (master/slave)
*/
typedef struct i2c_tx_info_s {
	uint16_t        addr;                           /*! i2c target address for master mode    */
	uint8_t         mst_stop;                       /*! i2c stop control for master mode    */
	uint8_t         rsvd0;                          /*! reserved 0   */
	const uint8_t *buf;                            /*! i2c trassmit data buffer pointer    */
	uint32_t        len;                            /*! i2c transmit data length    */
} i2c_tx_info_t, *pi2c_tx_info_t;

/** \brief i2c receive information (master/slave)
*/
typedef struct i2c_rx_info_s {
	uint16_t        addr;                           /*! i2c target address for master mode    */
	uint8_t         mst_stop;                       /*! i2c stop control for master mode    */
	uint8_t         rsvd0;                          /*! reserved 0   */
	uint8_t *buf;                            /*! i2c receive data buffer pointer    */
	uint32_t        len;                            /*! i2c receive data length    */
} i2c_rx_info_t, *pi2c_rx_info_t;

/** \brief i2c dma information (master/slave)
*/
typedef struct i2c_dma_info_s {
	hal_gdma_adaptor_t  *padaptor;                  /*! i2c dma adaptor     */
	irq_config_t        irq_config;                 /*! i2c dma interrupt handler     */
	uint8_t             ch_sts;                     /*! i2c dma channel status (i2c local)     */
	uint32_t            dat_len;                    /*! i2c original dma data length (i2c local)     */
} i2c_dma_info_t, *pi2c_dma_info_t;

/** \brief i2c control adapter
*/
typedef struct hal_i2c_adapter_s {
	volatile uint8_t    status;                     /*! i2c module status    */
	uint8_t             op_mode;                    /*! i2c module operation mode    */
	uint8_t             mst_spe_func;               /*! i2c module master special function    */
	uint8_t             slv_spe_func;               /*! i2c module slave special function    */
	volatile uint32_t   err_type;                   /*! i2c module error type    */
	i2c_init_dat_t      init_dat;                   /*! i2c initial data     */
	i2c_platform_data_t pltf_dat;                   /*! i2c platform data     */
	i2c_user_callback_t usr_cb;                     /*! i2c user callback     */
	irq_config_t        irq_config;                 /*! i2c interrupt handler     */
	i2c_tx_info_t       tx_dat;                     /*! i2c transmit information     */
	i2c_rx_info_t       rx_dat;                     /*! i2c receive information     */
	uint32_t            rd_cmd_no;                  /*! i2c read command number (master only)     */
	i2c_dma_info_t      tx_dma_dat;                 /*! i2c transmit dma data   */
	i2c_dma_info_t      rx_dma_dat;                 /*! i2c receive dma data   */
	void (*dcache_invalidate_by_addr)(uint32_t *addr, int32_t dsize);   /*! callback function to do the D-cache invalidate  */
	void (*dcache_clean_by_addr)(uint32_t *addr, int32_t dsize);        /*! callback function to do the D-cache clean  */
	void (*dcache_clean_invalidate_by_addr)(uint32_t *addr, int32_t dsize);       /*! callback function to do the D-cache clean
                                                                                       and invalidate */
	uint32_t            rsvd0;                      /*! reserved 0    */
} hal_i2c_adapter_t, *phal_i2c_adapter_t;

/** \brief Description of hal_i2c_write32
 *
 *    hal_i2c_write32 is used for general register write operation.
 *
 *   \param[in] uint32_t index:     i2c index
 *   \param[in] uint32_t reg:       register offset
 *   \param[in] uint32_t val:       register value
 */
static inline void hal_i2c_write32(uint8_t index, uint32_t reg, uint32_t val)
{
	switch (index) {
	case 0:
		HAL_WRITE32(I2C0_BASE, reg, val);
		break;
	case 1:
		HAL_WRITE32(I2C1_BASE, reg, val);
		break;
	case 2:
		HAL_WRITE32(I2C2_BASE, reg, val);
		break;
	case 3:
		HAL_WRITE32(I2C3_BASE, reg, val);
		break;
	default:
		break;
	}
}

/** \brief Description of hal_i2c_read32
 *
 *    hal_i2c_read32 is used for general register read operation.
 *
 *   \param[in] uint32_t index:     i2c index
 *   \param[in] uint32_t reg:       register offset
 *   \return uint32_t:          register value in 32-bit
 */
static inline uint32_t hal_i2c_read32(uint8_t index, uint32_t reg)
{
	switch (index) {
	case 0:
		return (uint32_t)(HAL_READ32(I2C0_BASE, reg));
	case 1:
		return (uint32_t)(HAL_READ32(I2C1_BASE, reg));
	case 2:
		return (uint32_t)(HAL_READ32(I2C2_BASE, reg));
	case 3:
		return (uint32_t)(HAL_READ32(I2C3_BASE, reg));
	default:
		break;
	}

	return (uint32_t)0xFFFFFFFF;
}

/** \brief Description of hal_rtl_i2c_idx_chk
 *
 *    hal_rtl_i2c_idx_chk is used for checking i2c module is available or not
 *
 *   \param[in] uint8_t idx:     I2C index
 *   \return HAL_Status.
 */
static inline hal_status_t hal_rtl_i2c_idx_chk(uint8_t idx)
{
	if ((idx > 3)) {
		DBG_I2C_ERR("Index(%d) is out of range", idx);
		return HAL_ERR_PARA;
	}

	return HAL_OK;
}

/** \brief Description of hal_rtl_i2c_slv_set_for_mst_rd_cmd
 *
 *    hal_rtl_i2c_slv_set_for_mst_rd_cmd is to set interrupt mask for Read Request interrupt which is from
 *    other masters.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return void
 */
static inline void hal_rtl_i2c_slv_set_for_mst_rd_cmd(hal_i2c_adapter_t *phal_i2c_adapter)
{
	HAL_SET_BIT(phal_i2c_adapter->init_dat.reg_base->I2C_INTR_MSK, I2C_BIT_M_RD_REQ);
}

/** \brief Description of hal_rtl_i2c_slv_clear_for_mst_rd_cmd
 *
 *    hal_rtl_i2c_slv_clear_for_mst_rd_cmd is to clear interrupt mask for Read Request interrupt which is from
 *    other masters.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return void
 */
static inline void hal_rtl_i2c_slv_clear_for_mst_rd_cmd(hal_i2c_adapter_t *phal_i2c_adapter)
{
	HAL_CLEAR_BIT(phal_i2c_adapter->init_dat.reg_base->I2C_INTR_MSK, I2C_BIT_M_RD_REQ);
}

typedef struct hal_i2c_pin_s {
	uint8_t sda;
	uint8_t scl;
	uint8_t eol;    // end of list
} hal_i2c_pin_t, *phal_i2c_pin_t;

typedef struct hal_i2c_group_adapter_s {
	hal_i2c_adapter_t *adapter[HP_I2C_NO + 1];   /*!< All the I2C adapters of this platform */
	irq_handler_t   irq_fun[HP_I2C_NO + 1];   /*!< the IRQ handler for different I2C adapters */
} hal_i2c_group_adapter_t, *phal_i2c_group_adapter_t;

/*  Macros for i2c essential operation  */
/** @defgroup i2c_reg_access_macro I2C REG ACCESS MACRO
 *  i2c register access macro
 *  @{
 */
#define HAL_I2C_WRITE32(idx, addr, value)    hal_i2c_write32(idx, (uint32_t)addr,value)
#define HAL_I2C_READ32(idx, addr)            hal_i2c_read32(idx, (uint32_t)addr)
#define READ_CLEAR_I2C_REG(base, reg_name)   base->reg_name
#define I2C_BASE_REG        ((I2C_TypeDef *) 0)
/** @} */ // end of I2C REG ACCESS MACRO

uint8_t hal_rtl_i2c_timeout_chk(hal_i2c_adapter_t *phal_i2c_adapter, uint32_t start_cnt);
void hal_rtl_i2c_dma_irq_handler(void *data);
void hal_rtl_i2c_mst_irq_handler(void *data);
void hal_rtl_i2c_slv_irq_handler(void *data);
uint8_t hal_rtl_i2c_chk_mod(hal_i2c_adapter_t *phal_i2c_adapter);
uint8_t hal_rtl_i2c_pure_init(hal_i2c_adapter_t *phal_i2c_adapter);
uint8_t hal_rtl_i2c_pure_deinit(hal_i2c_adapter_t *phal_i2c_adapter);
uint8_t hal_rtl_i2c_en_ctrl(hal_i2c_adapter_t *phal_i2c_adapter, uint8_t enable);
hal_status_t hal_rtl_i2c_set_clk(hal_i2c_adapter_t *phal_i2c_adapter);
hal_status_t hal_rtl_i2c_intr_ctrl(hal_i2c_adapter_t *phal_i2c_adapter, uint8_t set_clr, uint16_t intr_msk);
hal_status_t hal_rtl_i2c_wr(hal_i2c_adapter_t *phal_i2c_adapter, const uint8_t *dat_buf, uint32_t dat_len, uint8_t ctrl);
void hal_rtl_i2c_mst_send_rdcmd(hal_i2c_adapter_t *phal_i2c_adapter, uint32_t cmd_len, uint8_t ctrl);
uint32_t hal_rtl_i2c_dma_ctrl(hal_i2c_adapter_t *phal_i2c_adapter, uint8_t enable);
hal_status_t hal_rtl_i2c_mst_restr_ctrl(hal_i2c_adapter_t *phal_i2c_adapter, uint8_t restr_en);
hal_status_t hal_rtl_i2c_mst_gc_sb_ctrl(hal_i2c_adapter_t *phal_i2c_adapter, uint8_t enable, uint8_t gc_sb);
hal_status_t hal_rtl_i2c_slv_no_ack_ctrl(hal_i2c_adapter_t *phal_i2c_adapter, uint8_t no_ack_en);
uint8_t hal_rtl_i2c_slv_no_ack_sts(hal_i2c_adapter_t *phal_i2c_adapter);
hal_status_t hal_rtl_i2c_slv_ack_gc_ctrl(hal_i2c_adapter_t *phal_i2c_adapter, uint8_t slv_gc_en);
uint8_t hal_rtl_i2c_slv_ack_gc_sts(hal_i2c_adapter_t *phal_i2c_adapter);
hal_status_t hal_rtl_i2c_slv_to_slp(hal_i2c_adapter_t *phal_i2c_adapter);
uint8_t hal_rtl_i2c_slv_chk_mst_wr(hal_i2c_adapter_t *phal_i2c_adapter);
uint8_t hal_rtl_i2c_slv_chk_rd_req(hal_i2c_adapter_t *phal_i2c_adapter);
hal_status_t hal_rtl_i2c_pin_init(hal_i2c_adapter_t *phal_i2c_adapter);
hal_status_t hal_rtl_i2c_pin_deinit(hal_i2c_adapter_t *phal_i2c_adapter);
void hal_rtl_i2c_reg_comm_irq(hal_i2c_adapter_t *phal_i2c_adapter, irq_handler_t handler);
void hal_rtl_i2c_reg_irq(hal_i2c_adapter_t *phal_i2c_adapter, irq_handler_t handler);
uint8_t hal_rtl_i2c_unreg_irq(hal_i2c_adapter_t *phal_i2c_adapter);
hal_status_t hal_rtl_i2c_init(hal_i2c_adapter_t *phal_i2c_adapter);
hal_status_t hal_rtl_i2c_deinit(hal_i2c_adapter_t *phal_i2c_adapter);
hal_status_t hal_rtl_i2c_load_default(hal_i2c_adapter_t *phal_i2c_adapter, uint8_t index);
hal_status_t hal_rtl_i2c_set_tar(hal_i2c_adapter_t *phal_i2c_adapter, uint8_t mst_rw);
hal_status_t hal_rtl_i2c_send_addr_retry(hal_i2c_adapter_t *phal_i2c_adapter);
hal_status_t hal_rtl_i2c_send_poll(hal_i2c_adapter_t *phal_i2c_adapter);
hal_status_t hal_rtl_i2c_send_intr(hal_i2c_adapter_t *phal_i2c_adapter);
//hal_status_t hal_rtl_i2c_send_dma_init (hal_i2c_adapter_t *phal_i2c_adapter);
//hal_status_t hal_rtl_i2c_send_dma_deinit (hal_i2c_adapter_t *phal_i2c_adapter);
//hal_status_t hal_rtl_i2c_send_dma (hal_i2c_adapter_t *phal_i2c_adapter);
//hal_status_t hal_rtl_i2c_send (hal_i2c_adapter_t *phal_i2c_adapter);
hal_status_t hal_rtl_i2c_recv_addr_retry(hal_i2c_adapter_t *phal_i2c_adapter);
hal_status_t hal_rtl_i2c_recv_poll(hal_i2c_adapter_t *phal_i2c_adapter);
hal_status_t hal_rtl_i2c_recv_intr(hal_i2c_adapter_t *phal_i2c_adapter);
//hal_status_t hal_rtl_i2c_recv_dma_init (hal_i2c_adapter_t *phal_i2c_adapter);
//hal_status_t hal_rtl_i2c_recv_dma_deinit (hal_i2c_adapter_t *phal_i2c_adapter);
//hal_status_t hal_rtl_i2c_recv_dma (hal_i2c_adapter_t *phal_i2c_adapter);
//hal_status_t hal_rtl_i2c_receive (hal_i2c_adapter_t *phal_i2c_adapter);
hal_status_t hal_rtl_i2c_set_sar(hal_i2c_adapter_t *phal_i2c_adapter, uint8_t sar_idx, uint16_t slv_addr);
uint32_t hal_rtl_i2c_slv_recv_poll(hal_i2c_adapter_t *phal_i2c_adapter);
uint32_t hal_rtl_i2c_slv_recv_intr(hal_i2c_adapter_t *phal_i2c_adapter);
//uint32_t hal_rtl_i2c_slv_recv_dma (hal_i2c_adapter_t *phal_i2c_adapter);
//hal_status_t hal_rtl_i2c_slv_recv (hal_i2c_adapter_t *phal_i2c_adapter);
uint32_t hal_rtl_i2c_slv_send_poll(hal_i2c_adapter_t *phal_i2c_adapter);
uint32_t hal_rtl_i2c_slv_send_intr(hal_i2c_adapter_t *phal_i2c_adapter);
//uint32_t hal_rtl_i2c_slv_send_dma (hal_i2c_adapter_t *phal_i2c_adapter);
//hal_status_t hal_rtl_i2c_slv_send (hal_i2c_adapter_t *phal_i2c_adapter);

/**
  \brief  The data structure of the stubs function for the I2C HAL functions in ROM
*/
typedef struct hal_i2c_func_stubs_s {
	hal_pin_map *hal_i2c_scl_pin_map;
	hal_pin_map *hal_i2c_sda_pin_map;
	hal_i2c_group_adapter_t *hal_i2c_group_adpt;
	uint8_t (*hal_i2c_timeout_chk)(hal_i2c_adapter_t *phal_i2c_adapter, uint32_t start_cnt);
	uint8_t (*hal_i2c_chk_mod)(hal_i2c_adapter_t *phal_i2c_adapter);
	uint8_t (*hal_i2c_pure_init)(hal_i2c_adapter_t *phal_i2c_adapter);
	uint8_t (*hal_i2c_pure_deinit)(hal_i2c_adapter_t *phal_i2c_adapter);
	uint8_t (*hal_i2c_en_ctrl)(hal_i2c_adapter_t *phal_i2c_adapter, uint8_t enable);
	hal_status_t (*hal_i2c_set_clk)(hal_i2c_adapter_t *phal_i2c_adapter);
	hal_status_t (*hal_i2c_intr_ctrl)(hal_i2c_adapter_t *phal_i2c_adapter, uint8_t set_clr, uint16_t intr_msk);
	hal_status_t (*hal_i2c_wr)(hal_i2c_adapter_t *phal_i2c_adapter, const uint8_t *dat_buf, uint32_t dat_len, uint8_t ctrl);
	void (*hal_i2c_mst_send_rdcmd)(hal_i2c_adapter_t *phal_i2c_adapter, uint32_t cmd_len, uint8_t ctrl);
	uint32_t (*hal_i2c_dma_ctrl)(hal_i2c_adapter_t *phal_i2c_adapter, uint8_t enable);
	hal_status_t (*hal_i2c_mst_restr_ctrl)(hal_i2c_adapter_t *phal_i2c_adapter, uint8_t restr_en);
	hal_status_t (*hal_i2c_mst_gc_sb_ctrl)(hal_i2c_adapter_t *phal_i2c_adapter, uint8_t enable, uint8_t gc_sb);
	hal_status_t (*hal_i2c_slv_no_ack_ctrl)(hal_i2c_adapter_t *phal_i2c_adapter, uint8_t no_ack_en);
	uint8_t (*hal_i2c_slv_no_ack_sts)(hal_i2c_adapter_t *phal_i2c_adapter);
	hal_status_t (*hal_i2c_slv_ack_gc_ctrl)(hal_i2c_adapter_t *phal_i2c_adapter, uint8_t slv_gc_en);
	uint8_t (*hal_i2c_slv_ack_gc_sts)(hal_i2c_adapter_t *phal_i2c_adapter);
	hal_status_t (*hal_i2c_slv_to_slp)(hal_i2c_adapter_t *phal_i2c_adapter);
	uint8_t (*hal_i2c_slv_chk_mst_wr)(hal_i2c_adapter_t *phal_i2c_adapter);
	uint8_t (*hal_i2c_slv_chk_rd_req)(hal_i2c_adapter_t *phal_i2c_adapter);
	hal_status_t (*hal_i2c_pin_init)(hal_i2c_adapter_t *phal_i2c_adapter);
	hal_status_t (*hal_i2c_pin_deinit)(hal_i2c_adapter_t *phal_i2c_adapter);
	void (*hal_i2c_reg_comm_irq)(hal_i2c_adapter_t *phal_i2c_adapter, irq_handler_t handler);
	void (*hal_i2c_reg_irq)(hal_i2c_adapter_t *phal_i2c_adapter, irq_handler_t handler);
	uint8_t (*hal_i2c_unreg_irq)(hal_i2c_adapter_t *phal_i2c_adapter);

	hal_status_t (*hal_i2c_init)(hal_i2c_adapter_t *phal_i2c_adapter);
	hal_status_t (*hal_i2c_deinit)(hal_i2c_adapter_t *phal_i2c_adapter);
	hal_status_t (*hal_i2c_load_default)(hal_i2c_adapter_t *phal_i2c_adapter, uint8_t index);
	hal_status_t (*hal_i2c_set_tar)(hal_i2c_adapter_t *phal_i2c_adapter, uint8_t mst_rw);
	hal_status_t (*hal_i2c_send_addr_retry)(hal_i2c_adapter_t *phal_i2c_adapter);
	hal_status_t (*hal_i2c_send_poll)(hal_i2c_adapter_t *phal_i2c_adapter);
	hal_status_t (*hal_i2c_send_intr)(hal_i2c_adapter_t *phal_i2c_adapter);
	//hal_status_t (*hal_i2c_send_dma_init) (hal_i2c_adapter_t *phal_i2c_adapter);
	//hal_status_t (*hal_i2c_send_dma_deinit) (hal_i2c_adapter_t *phal_i2c_adapter);
	//hal_status_t (*hal_i2c_send_dma) (hal_i2c_adapter_t *phal_i2c_adapter);
	//hal_status_t (*hal_i2c_send) (hal_i2c_adapter_t *phal_i2c_adapter);
	hal_status_t (*hal_i2c_recv_addr_retry)(hal_i2c_adapter_t *phal_i2c_adapter);
	hal_status_t (*hal_i2c_recv_poll)(hal_i2c_adapter_t *phal_i2c_adapter);
	hal_status_t (*hal_i2c_recv_intr)(hal_i2c_adapter_t *phal_i2c_adapter);
	//hal_status_t (*hal_i2c_recv_dma_init) (hal_i2c_adapter_t *phal_i2c_adapter);
	//hal_status_t (*hal_i2c_recv_dma_deinit) (hal_i2c_adapter_t *phal_i2c_adapter);
	//hal_status_t (*hal_i2c_recv_dma) (hal_i2c_adapter_t *phal_i2c_adapter);
	//hal_status_t (*hal_i2c_receive) (hal_i2c_adapter_t *phal_i2c_adapter);
	hal_status_t (*hal_i2c_set_sar)(hal_i2c_adapter_t *phal_i2c_adapter, uint8_t sar_idx, uint16_t slv_addr);
	uint32_t (*hal_i2c_slv_recv_poll)(hal_i2c_adapter_t *phal_i2c_adapter);
	uint32_t (*hal_i2c_slv_recv_intr)(hal_i2c_adapter_t *phal_i2c_adapter);
	//uint32_t (*hal_i2c_slv_recv_dma) (hal_i2c_adapter_t *phal_i2c_adapter);
	//hal_status_t (*hal_i2c_slv_recv) (hal_i2c_adapter_t *phal_i2c_adapter);
	uint32_t (*hal_i2c_slv_send_poll)(hal_i2c_adapter_t *phal_i2c_adapter);
	uint32_t (*hal_i2c_slv_send_intr)(hal_i2c_adapter_t *phal_i2c_adapter);
	//uint32_t (*hal_i2c_slv_send_dma) (hal_i2c_adapter_t *phal_i2c_adapter);
	//hal_status_t (*hal_i2c_slv_send) (hal_i2c_adapter_t *phal_i2c_adapter);
	void (*hal_i2c_dma_irq_handler)(void *data);
	void (*hal_i2c_mst_irq_handler)(void *data);
	void (*hal_i2c_slv_irq_handler)(void *data);
	uint32_t reserved[19];  // reserved space for next ROM code version function table extending.
} hal_i2c_func_stubs_t;

/** @} */ /* End of group hs_hal_i2c */

#ifdef __cplusplus
}
#endif

#endif /* _RTL8735B_I2C_H_ */

