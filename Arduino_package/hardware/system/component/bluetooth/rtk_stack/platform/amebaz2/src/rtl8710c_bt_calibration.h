#ifndef _RTL8710C_BT_CALIBRATION_H_
#define _RTL8710C_BT_CALIBRATION_H_


typedef struct {
	uint32_t IQK_xx;
	uint32_t IQK_yy;
	uint16_t IDAC;
	uint16_t QDAC;
	uint16_t IDAC2;
	uint16_t QDAC2;
}BT_Cali_TypeDef;

/**
  * @brief Do BT IQK and LOK, do not call this function in formal SDK
  * @param store, whether need store the calibration data in flash
  * @retval SUCESS or FAIL
  * @note calibration data will write to 0x0800_1FF0
  */
uint32_t bt_iqk_8710c(BT_Cali_TypeDef *cal_data,BOOLEAN store);

/**
  * @brief only used for BT debug
  */
uint32_t bt_adda_dck_8710c(void);

/**
  * @brief Write DCK data to RFC
  * @param  calibration data
  * @retval NA
  */
uint32_t bt_dck_write(uint8_t q_dck, uint8_t i_dck);

/**
  * @brief Write LOK data to RFC
  * @param  calibration data
  * @retval NA
  */
uint32_t bt_lok_write(uint16_t idac, uint16_t qdac, uint16_t idac2, uint16_t qdac2);

/**
  * @brief BT FLATK
  * @param  calibration data
  * @retval NA
  */
uint32_t bt_flatk_8710c(uint16_t txgain_flatk);

#endif //_RTL8710C_BT_CALIBRATION_H_
