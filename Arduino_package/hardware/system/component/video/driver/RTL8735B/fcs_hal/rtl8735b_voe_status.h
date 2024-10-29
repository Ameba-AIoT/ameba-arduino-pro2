/**************************************************************************//**
 * @file     rtl8735b_voe_status.h
 * @brief    Define the data structure for VOE ROM Boot functions.
 * @version  V1.00
 * @date     2022-02-16
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2016 Realtek Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 *
 ******************************************************************************/

#ifndef _RTL8735B_VOE_STATUS_H_
#define _RTL8735B_VOE_STATUS_H_

#ifdef  __cplusplus
extern "C"
{
#endif


//#define _FPGA_MIPI_APHY_
//#define _USE_RAM_SIM_FCS_

/************************FCS ROM CODE USE START >>>>**************************/
#define ISP_MULTI_FCS_MAGIC_NUM 0x5343464D /* 'M', 'F', 'C', 'S' */
#define ISP_MFCS_DATA_VERSION   0x00010001    /*  Major-[31:16] */
#define MULTI_FCS_MAX           10
#define INVALID_ISP_SENSOR_SET_IDX           0xFF
#define VOE_LD_INFO_DIGEST_MAX               32            /* Bytes */
#define ISP_MULTI_FCS_HDR_SIZE_ALIGN         32            /* 32 Byte-aligned */
#define ISP_MULTI_FCS_HDR_SIZE_ALIGN_MASK    0x1F          /* 32 Byte-aligned */

#define ISP_FCS_DATA_MAGIC_NUM  0x53434649 /* 'I', 'F', 'C', 'S' */
#define ISP_FCS_DATA_VERSION	0x00010000    /*  Major-[31:16] */ //B-cut
#define ISP_FCS_DATA_VERSION_C	0x00020000    /*  Major-[31:16] */ //C-cut
#define ISP_FCS_VERION_MJR_MASK 0xFFFF0000

#define GPIO_MAX                12
#define I2C_MAX                 2

#define ISP_FCS_OK              0x0


//TM_STATUS  ROM -> bootloader bit partition
//       8 bit       //       8 bit       //  8 bit  //  8 bit  //
// TM boot err code  //	FCS TM Status  	  //   FCS Error code   //


#define TM_STS_FCS_ERR_MASK		0xFFFF
#define TM_STS_FCS_STS_SHIFT 	16
#define TM_STS_FCS_STS_MASK		0xFF
#define TM_STS_TM_BT_ERR_SHIFT 	24
#define TM_STS_TM_BT_ERR_MASK	0xFF



/****** TM_STATUS register TM side Status for FCS  ******/
//#define FCS_DATA_LOAD_OK_TM     0x0001  // only for B-cut
#define FULL_LOAD_OK_FCS_OK_TM  0x0002
#define FULL_LOAD_OK_FCS_NG_TM  0x0003
#define FULL_LOAD_OK_FCS_NK_TM  0x0004


///FCS TM Status  ( bit 23~16 )
#define FCS_DATA_LOAD_OK_TM		0x01
#define GPIO_INIT_DONE_TM		0x02
#define I2C_INIT_DONE_TM		0x04
#define SNRPLL_INIT_DONE_TM		0x08
#define ADC_INIT_DONE_TM		0x10
#define PWM_INIT_DONE_TM		0x20
#define FCS_KM_PROC_OK_TM		0x40

#define FCS_PROC_ERR_BYPASS_TM	0x80


/************************FCS ROM CODE USE END <<<<****************************/



/****** TM_STATUS register VOE Status for Normal VOE process  *******/
#define FCS_VOE_READY	        0x1018				// VOE start done

#define STATUS_VOE_EN			0x0100

#define FCS_S1                  0x1118				// 0001: enter voe_open     (KM->TM)
#define FCS_S2                  0x1318				// 0011: isp open done      (KM->TM)
#define FCS_S3                  0x1518				// 0101: 2-stage done       (TM->KM)
#define FCS_S4                  0x1718				// 0111: bring up done      (KM->TM)
//#define FCS_S5                  0x1918				// 1001: reserved


// 32 bit
// 8 bit // 8 bit // 8 bit // 8 bit
// 8 bit // status // run flow // create stream

// status 8 bits
// bit 0		VOE Enable/Disable
// bit 1-2		00:voe bring up 01:voe_open done 10:voe_start_done 11: reserved





/************************FCS ROM/BOOTLOADER CODE USE START >>>>**************************/

/****** TM_STATUS register TM side error code for FCS  ******/
#define TM_ERROR                0x1000
#define FCS_DATA_HEADER_ERR     0x1001
#define FCS_DATA_GPIO_CNT_ERR   0x1002
#define FCS_CPY_FUNC_ERR        0x1003
#define FCS_ITCM_INFO_ERR       0x1004
#define FCS_DTCM_INFO_ERR       0x1005
#define MFCS_DATA_HEADER_ERR    0x1006
#define MFCS_FCS_CNT_ID_ERR     0x1007
#define MFCS_FCS_ADDR_SZ_ERR    0x1008
#define FCS_WAIT_KM_TMOUT_ERR   0x1009
#define FCS_WAIT_SNR_TMOUT_ERR  0x100A
#define FCS_INVALID_CMD_ERR     0x100B

#define FCE_I2C_RETERR_BASE		0x1100
//add with C-cut
#define FCS_GPIO_PINMUX_ERR     0x1200
#define FCS_I2C_PINREG_ERR		0x1201
#define FCS_SNRCLK_PINMUX_ERR	0x1202
#define FCS_ADC_PININIT_ERR		0x1203
#define FCS_PWM_PINMUX_ERR		0x1204
#define FCS_ADC_REF_SET_ERR		0x1205
#define CHECK_VOE_POWER_OFF		0x1206
#define FCS_KM_PROC_NK			0x1207
#define FCS_KM_PROC_NG			0x1208
#define FCS_KM_PROC_BYPASS  	0x1209
#define FCS_PWM_PIN_ID_ERR  	0x120A



/****** KM_STATUS register KM side Status for FCS  ******/
#define FCS_INIT_ROM_RDY_KM     0x0080
#define FCS_WAIT_SNR_CLK_KM     0x0081
#define FCS_RUN_DATA_OK_KM      0x0082
#define FCS_BYPASS_WHILE1_KM	0x0083

#define FCS_RUN_DATA_NG_KM      0x2081


/****** KM_STATUS register KM side error code for FCS  ******/
#define KM_ERROR                0x2000
#define FCS_CMD_INVALID_ERR     0x2006
#define FCS_ERR_CMDID           0x2007
#define FCS_SNR_CLK_TYPE_ERR    0x2008
#define FCS_GPIO_INIT_ERR       0x2009
#define FCS_I2C_INIT_ERR        0x200A
#define FCS_ADC_INIT_ERR        0x200B
#define FCS_PWM_INIT_ERR        0x200C
#define FCS_DATA_I2C_CNT_ERR    0x200D

#define FCS_ADC_NIDLE_ERR       0x2010
#define FCS_ADC_INPROG_ERR      0x2011
#define FCS_ADC_SINREAD_ERR     0x2012
#define FCS_ADC_CALIPARA_ERR    0x2013
#define FCS_ADC_DIVBYZERO_ERR   0x2014
#define FCS_ADC_NEGVALUE_ERR    0x2015
#define FCS_ADC_OVERFLOW_ERR    0x2016

#define FCS_I2C_TRANS_ERR       0x2100
#define FCS_I2C_CMP_ERR         0x21FF
#define FCS_I2C_BSTWRITE_ERR    0x21FE
#define FCS_I2C_CB_ERR          0x21FD

#define KM_STATUS               0x40492004
#define KM_FCS_ERROR_REG        0x40492008

#define TM_STATUS               0x40009154

#define REMAP_S7_ITCM           0x04000000   //0x04000000~0x0407FFFF
#define REMAP_S7_DTCM           0x00080000   //0x20080000~0x200FFFFF

#define VOE_IROM_S              0x00000000
#define VOE_IROM_E              0x000003FF       // 1KB
#define VOE_IRAM_S              0x00040000
#define VOE_IRAM_E              0x0004FFFF       // 64KB

#define VOE_DROM_S              0x20010000
#define VOE_DROM_E              0x20013FFF       // 16KB
#define VOE_DRAM_S              0x20000000
#define VOE_DRAM_E              0x2000FFFF       // 64KB

#define VOE_DRAM_RESV_SZ		0x100		     // for fcs rom process result
#define FCS_SRAM_ADDR			0x2000F000    	 //default addr
#define FCS_RESULT_ADDR			0x2000FF00

//#define DDR_FOR_VOE_IMG_LOAD_ADDR             (0x70000000)
//#define WAIT_KM_INIT_TIMEOUT_US       5000

#define FCS_ADC_PARAM_IDX_MAX               (4)
#define FCS_ADC_PARAM_GAIN_DENO_SIZE        (2)
#define FCS_ADC_PARAM_GAIN_MOLE_SIZE        (2)
#define FCS_ADC_PARAM_OFFSET_DENO_SIZE      (2)
#define FCS_ADC_PARAM_OFFSET_MOLE_SIZE      (4)

typedef struct fcs_adc_paras_list_s {
	uint16_t otp_addr;
	uint16_t adc_para_size;
	uint8_t *p_adc_para_v;
} fcs_adc_paras_list_t, *pfcs_adc_paras_list_t;

enum {
	FCS_ADC_PARAM_GAIN_DENO_IDX        = 0x0,
	FCS_ADC_PARAM_GAIN_MOLE_IDX        = 0x1,
	FCS_ADC_PARAM_OFFSET_DENO_IDX      = 0x2,
	FCS_ADC_PARAM_OFFSET_MOLE_IDX      = 0x3,
};

typedef struct isp_multi_fcs_hdr_s {
	uint32_t magic;
	uint32_t version;
	uint32_t fcs_data_size[MULTI_FCS_MAX];
	uint32_t fcs_data_offset[MULTI_FCS_MAX];
	uint32_t wait_km_init_timeout_us;
	uint8_t  multi_fcs_cnt;
	uint8_t  active_fcs;
	uint8_t  reserved[6];
} isp_multi_fcs_hdr_t;

typedef struct isp_fcs_header_s {

	//struct isp_fcs_cmd_attribute_t cmd_attb;
	uint32_t magic;
	uint32_t version;
	uint32_t itcm_size;
	uint32_t itcm_addr;
	uint32_t dtcm_size;
	uint32_t dtcm_addr;


	uint8_t i2c_device_cnt;
	uint8_t i2c_speed_mode;
	uint16_t i2c_speed;     // unit: KHz

	uint16_t i2c_timeout;   //unit: us
	uint8_t i2c_id;
	uint8_t timer_id;

	uint8_t adc_id;   // use 1 gpio
	uint8_t pwm_id;   // same function as ir_led
	uint8_t gpio_list[GPIO_MAX];
	uint8_t gpio_cnt;


	uint8_t snr_clk_pin; // dedicated gpio
	uint8_t i2c_scl; // dedicated gpio
	uint8_t i2c_sda; // dedicated gpio
	uint8_t reserved0;

	uint8_t adc_th_num;
	uint8_t adc_th_table_num;
	uint8_t adc_value_byte;
	uint8_t adc_use_cali;

	int16_t adc_gain_deno;
	int16_t adc_gain_mole;
	int32_t adc_offset_mole;


	int16_t adc_offset_deno;
	int16_t wait_i2c_delay_us;
	uint32_t snr_timeout_us;

	uint16_t adc_trig_delay;
	uint8_t adc_ref_setting;
	uint8_t hclk_strong_driving;
	uint8_t reserved[4];



} isp_fcs_header_t;

typedef struct isp_i2c_info_s {
	uint16_t i2c_slave_addr;
	uint8_t addr_len;
	uint8_t data_len;
} isp_i2c_info_t;

#if 0
typedef struct voe_header_s {
	u16 year;               // 2B
	u8 month;               // 1B
	u8 day;                 // 1B
	u8 version[24];         // 24B
	u32 itcm_size;          // 4B
	u32 dtcm_size;
	u32 ddr_size;
} voe_header_t;
#endif

typedef struct fcs_result_s{
	uint32_t adc_final_value;
	uint8_t adc_sample;
	uint8_t adc_mode;
	uint8_t dark_mode;
	uint8_t reserv0;
	uint32_t final_cmd;
	uint32_t cmd_index;

	uint32_t fcs_addr;
	uint32_t i2c_bypass_err_cnt;
	uint32_t i2c_bypass_last_err;
	uint32_t fcs_data_version;

	uint32_t reserv[4];

}fcs_result_t;




typedef void (*voe_cpy_t)(void *, void *, size_t);

int hal_rtl_voe_fcs_process(voe_cpy_t voe_cpy, uint32_t mfcs_data_addr, uint8_t fcs_id, uint32_t total_size);

/************************FCS ROM CODE USE END <<<<****************************/

void hal_rtl_voe_fcs_write_err_status(uint32_t err_status);
void hal_rtl_voe_fcs_write_err_main_type_status(uint8_t tm_err_status);
int hal_rtl_voe_fcs_process_btldr(voe_cpy_t voe_cpy);

#ifdef  __cplusplus
}
#endif

#endif  // end of "#define _RTL8735B_VOE_STATUS_H_"

