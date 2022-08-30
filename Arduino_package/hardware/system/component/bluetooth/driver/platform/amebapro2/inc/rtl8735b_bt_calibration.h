#ifndef _RTL8735B_BT_CALIBRATION_H_
#define _RTL8735B_BT_CALIBRATION_H_


typedef struct {
	uint16_t IQK_xx;
	uint16_t IQK_yy;
	uint8_t IDAC_IS;
	uint8_t IDAC_QS;
	uint8_t IDAC2_IS;
	uint8_t IDAC2_QS;
}BT_Cali_TypeDef;

/**
  * @brief Do BT IQK and LOK, do not call this function in formal SDK
  * @param store, whether need store the calibration data in flash
  * @retval SUCESS or FAIL
  * @note calibration data will write to 0x0800_1FF0
  */
uint32_t bt_iqk_8735b(BT_Cali_TypeDef *cal_data,BOOLEAN store);

/**
  * @brief only used for BT debug
  */
uint32_t bt_adda_dck_8735b(void);

/**
  * @brief Write DCK data to RFC
  * @param  calibration data
  * @retval NA
  */
uint32_t bt_dck_write(uint8_t dos_i_dck, uint8_t dos_q_dck, uint8_t kosen_i_dck, uint8_t kosen_q_dck);

/**
  * @brief Write LOK data to RFC
  * @param  calibration data
  * @retval NA
  */
uint32_t bt_lok_write(uint8_t idac_is, uint8_t idac_qs, uint8_t idac2_is, uint8_t idac2_qs);

/**
  * @brief BT FLATK
  * @param  calibration data
  * @retval NA
  */
uint32_t bt_flatk_8735b(uint16_t txgain_flatk);

#endif //_RTL8735B_BT_CALIBRATION_H_
