#ifndef _RTL8735B_FLASH_SEC_TYPE_H_
#define _RTL8735B_FLASH_SEC_TYPE_H_

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_STS_REG
 * @brief  Flash SEC Engine Status Register          (@ 0X000)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_REMAP_ADDR_ERR               7
#define FLASH_SEC_BIT_REMAP_ADDR_ERR                 ((u32)0x00000001 << 7)                              /*!<R 0  Indicate the flash address after adding offset size cross 256 Mbytes boundaries. */
#define FLASH_SEC_SHIFT_REMAP_REGN_ERR               6
#define FLASH_SEC_BIT_REMAP_REGN_ERR                 ((u32)0x00000001 << 6)                              /*!<R 0  Indicate the flash read address hits multiple remmaping region. */
#define FLASH_SEC_SHIFT_INTR_ERR_INIT                5
#define FLASH_SEC_BIT_INTR_ERR_INIT                  ((u32)0x00000001 << 5)                              /*!<R 0  Indicate the transaction was received before the key initialization is completed. */
#define FLASH_SEC_SHIFT_INTR_ERR_APB                 4
#define FLASH_SEC_BIT_INTR_ERR_APB                   ((u32)0x00000001 << 4)                              /*!<R 0  Indicate whether the setting configuration failed. When a transaction is in progress, all settings except clear interrupt are invalid. */
#define FLASH_SEC_SHIFT_INTR_ERR_RESP                3
#define FLASH_SEC_BIT_INTR_ERR_RESP                  ((u32)0x00000001 << 3)                              /*!<R 0  Indicate a error response is received from slave. */
#define FLASH_SEC_SHIFT_INTR_ERR_TAG                 2
#define FLASH_SEC_BIT_INTR_ERR_TAG                   ((u32)0x00000001 << 2)                              /*!<R 0  Indicate a GCM tag mismatch error occurred. */
#define FLASH_SEC_SHIFT_KEY_INIT_DONE                1
#define FLASH_SEC_BIT_KEY_INIT_DONE                  ((u32)0x00000001 << 1)                              /*!<R 0  Indicates whether the initialization of the key is completed. Only used in AES GCM and ECB_MIX mode. */
#define FLASH_SEC_SHIFT_IDLE                         0
#define FLASH_SEC_BIT_IDLE                           ((u32)0x00000001 << 0)                              /*!<R 1  Indicates whether there is any outstanding transaction. */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_CID_REG
 * @brief  Flash SEC Engine Component Identification Register (@ 0X004)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_LINE_SIZE                    12
#define FLASH_SEC_MASK_LINE_SIZE                     ((u32)0x00000007 << 12)                             /*!<R 0  Cache line size. Indicate how many 128 bits blocks are used to calculate the tag. 3'b000: 16 Bytes = 1 AES Block 3'b001: 32 Bytes = 2 AES Block 3'b010: 64 Bytes = 4 AES Block 3'b011: 128 Bytes = 8 AES Block */
#define FLASH_SEC_SHIFT_KEY_SRC                      11
#define FLASH_SEC_BIT_KEY_SRC                        ((u32)0x00000001 << 11)                             /*!<R 0  Indicate the key source. 1'b0: From dedicated key port(only support this configuration currently) */
#define FLASH_SEC_SHIFT_SPRT_GCM                     10
#define FLASH_SEC_BIT_SPRT_GCM                       ((u32)0x00000001 << 10)                             /*!<R 0  Indicate whether the AES GCM mode is supported. */
#define FLASH_SEC_SHIFT_SPRT_ECB_MIX                 9
#define FLASH_SEC_BIT_SPRT_ECB_MIX                   ((u32)0x00000001 << 9)                              /*!<R 0  Indicate whether the AES ECB MIX mode is supported. */
#define FLASH_SEC_SHIFT_SPRT_CTR                     8
#define FLASH_SEC_BIT_SPRT_CTR                       ((u32)0x00000001 << 8)                              /*!<R 0  Indicate whether the AES CTR mode is supported. */
#define FLASH_SEC_SHIFT_IV_NUMBER                    4
#define FLASH_SEC_MASK_IV_NUMBER                     ((u32)0x0000000F << 4)                              /*!<R 0  Number of supported IVs pattern registers. */
#define FLASH_SEC_SHIFT_REGN_NUMBER                  0
#define FLASH_SEC_MASK_REGN_NUMBER                   ((u32)0x0000000F << 0)                              /*!<R 0  Number of supported decryption regions. */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_ERR_ADDR_REG
 * @brief  Flash SEC Engine Error Address Log Register (@ 0X008)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_ERR_ADDR                     0
#define FLASH_SEC_MASK_ERR_ADDR                      ((u32)0xFFFFFFFF << 0)                              /*!<R 0  Recorded flash address when AES GCM Tag mismatch error or receiving an error response. */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_CLR_INT_REG
 * @brief  Flash SEC Engine Clear Interrupt Register (@ 0X010)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_CLR_INTR                     0
#define FLASH_SEC_BIT_CLR_INTR                       ((u32)0x00000001 << 0)                              /*!<W 0  Interrupt clear control. It has to write 1'b1 to this register every time when the error exception occurs. */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_CTRL_REG
 * @brief  Flash SEC Engine Control Register         (@ 0X014)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_ICG_CTRL_4                   20
#define FLASH_SEC_BIT_ICG_CTRL_4                     ((u32)0x00000001 << 20)                             /*!<R/W 0  Disable key-reg auto clock gatting. */
#define FLASH_SEC_SHIFT_ICG_CTRL_3                   19
#define FLASH_SEC_BIT_ICG_CTRL_3                     ((u32)0x00000001 << 19)                             /*!<R/W 0  Disable apb-ctrl auto clock gatting. */
#define FLASH_SEC_SHIFT_ICG_CTRL_2                   18
#define FLASH_SEC_BIT_ICG_CTRL_2                     ((u32)0x00000001 << 18)                             /*!<R/W 0  Disable aes-engine auto clock gatting. */
#define FLASH_SEC_SHIFT_ICG_CTRL_1                   17
#define FLASH_SEC_BIT_ICG_CTRL_1                     ((u32)0x00000001 << 17)                             /*!<R/W 0  Disable fetch-unit auto clock gatting. */
#define FLASH_SEC_SHIFT_ICG_CTRL_0                   16
#define FLASH_SEC_BIT_ICG_CTRL_0                     ((u32)0x00000001 << 16)                             /*!<R/W 0  Disable line-buffer auto clock gatting. */
#define FLASH_SEC_SHIFT_AES_EN                       8
#define FLASH_SEC_BIT_AES_EN                         ((u32)0x00000001 << 8)                              /*!<R/W 0  Determine whether to enable the AES Engine. 1'b0: Disable decryption engine(except remapping function) 1'b1: Enable decryption engine and line buffer */
#define FLASH_SEC_SHIFT_KEY_SIZE                     5
#define FLASH_SEC_MASK_KEY_SIZE                      ((u32)0x00000003 << 5)                              /*!<R/W 0  Determine the size of AES Cipher key. 2'b00: 128 bits 2'b01: 192 bits 2'b10: 256 bits 2'b11: reserved */
#define FLASH_SEC_SHIFT_AXI_WORD_SWAP                4
#define FLASH_SEC_BIT_AXI_WORD_SWAP                  ((u32)0x00000001 << 4)                              /*!<R/W 0  Determine the endian of the ciphertext in slave memory. If set to 1'b1, can swap word order. */
#define FLASH_SEC_SHIFT_AXI_BYTE_SWAP                3
#define FLASH_SEC_BIT_AXI_BYTE_SWAP                  ((u32)0x00000001 << 3)                              /*!<R/W 0  Determine the endian of the ciphertext in slave memory. If set to 1'b1, can swap byte order. */
#define FLASH_SEC_SHIFT_TAG_SIZE                     0
#define FLASH_SEC_MASK_TAG_SIZE                      ((u32)0x00000003 << 0)                              /*!<R/W 0  AES GCM Tag size. The size of the AES GCM tag will affect the length of each tag command. 2'b00: 32 bits(4 bytes) 2'b01: 64 bits(8 bytes) 2'b10: 128 bits(16 bytes) 2'b11: reserved */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_MAINTAIN_OP_REG
 * @brief  Flash SEC Engine Maintenance Operation Register (@ 0X018)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_CLEAN_CACHE_LINE             2
#define FLASH_SEC_BIT_CLEAN_CACHE_LINE               ((u32)0x00000001 << 2)                              /*!<W 0  Manually clear the line buffer. Write 1'b1 to clear all after Flash data update. */
#define FLASH_SEC_SHIFT_DEC_KEY_INIT                 1
#define FLASH_SEC_BIT_DEC_KEY_INIT                   ((u32)0x00000001 << 1)                              /*!<W 0  Only used in ECB_MIX mode. Whenever the key is changed, write 1'b1 to initialize the decryption key. When keys are updated by external port, Flash SEC engine will trigger this bit automatically. The status of completion can be determined by reading bit 1 of the status register. */
#define FLASH_SEC_SHIFT_GCM_KEY_INIT                 0
#define FLASH_SEC_BIT_GCM_KEY_INIT                   ((u32)0x00000001 << 0)                              /*!<W 0  Only used in GCM mode. Whenever the key is changed, write 1'b1 to initialize the GMAC key. When keys are updated by external port, Flash SEC engine will trigger this bit automatically. The status of completion can be determined by reading bit 1 of the status register. */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_LOCK_CTRL_REG
 * @brief  Flash SEC Engine Write Lock Control Register (@ 0X01C)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_SEC_LOCK_EN                  0
#define FLASH_SEC_MASK_SEC_LOCK_EN                   ((u32)0x000000FF << 0)                              /*!<R/W 0  When set 0xDC to this field, all registers excep #sec_clr_int_reg and #sec_maintain_op_reg are not allowed to be written. Once the lock is set, the way to unlock is reset the Flash SEC engine. If SW wants to modified the setting of control registers, it should keep this lock unset. */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_GCM_TAG_BASE_REG
 * @brief  Flash SEC Engine AES GCM TAG Base Address Register (@ 0X020)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_TAG_BASE                     0
#define FLASH_SEC_MASK_TAG_BASE                      ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  AES GCM Encrypted Tag Flash base address for reference to the Flash SEC engine. */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_CIPHER_REGION0_BASE_REG
 * @brief  Flash SEC Engine Cipher Region0 Base Address Register (@ 0X040)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_REGN_0_BASE                  12
#define FLASH_SEC_MASK_REGN_0_BASE                   ((u32)0x000FFFFF << 12)                             /*!<R/W 0  Region 0_cipher base address. */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_CIPHER_REGION0_END_REG
 * @brief  Flash SEC Engine Cipher Region0 End Address Register (@ 0X044)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_REGN_0_END                   12
#define FLASH_SEC_MASK_REGN_0_END                    ((u32)0x000FFFFF << 12)                             /*!<R/W 0  Region 0 cipher end address. */
#define FLASH_SEC_SHIFT_REGN_0_IV_NUM                8
#define FLASH_SEC_MASK_REGN_0_IV_NUM                 ((u32)0x00000007 << 8)                              /*!<R/W 0  IV pattern used in region 0. Apply which IV pattern registers to this region.(Number corresponds to IV pattern registers) */
#define FLASH_SEC_SHIFT_REGN_0_MODE                  1
#define FLASH_SEC_MASK_REGN_0_MODE                   ((u32)0x00000003 << 1)                              /*!<R/W 0  Cipher Mode used in region 0. 2'b00: GCM mode 2'b01: CTR mode 2'b10: ECB_MIX mode 2'b11: Reserved */
#define FLASH_SEC_SHIFT_REGN_0_ENABLE                0
#define FLASH_SEC_BIT_REGN_0_ENABLE                  ((u32)0x00000001 << 0)                              /*!<R/W 0  Enable region 0 cipher setting. */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_CIPHER_REGION1_BASE_REG
 * @brief  Flash SEC Engine Cipher Region1 Base Address Register (@ 0X048)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_REGN_1_BASE                  12
#define FLASH_SEC_MASK_REGN_1_BASE                   ((u32)0x000FFFFF << 12)                             /*!<R/W 0  Region 1_cipher base address. */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_CIPHER_REGION1_END_REG
 * @brief  Flash SEC Engine Cipher Region1 End Address Register (@ 0X04C)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_REGN_1_END                   12
#define FLASH_SEC_MASK_REGN_1_END                    ((u32)0x000FFFFF << 12)                             /*!<R/W 0  Region 1 cipher end address. */
#define FLASH_SEC_SHIFT_REGN_1_IV_NUM                8
#define FLASH_SEC_MASK_REGN_1_IV_NUM                 ((u32)0x00000007 << 8)                              /*!<R/W 0  IV pattern used in region 1. Apply which IV pattern registers to this region.(Number corresponds to IV pattern registers) */
#define FLASH_SEC_SHIFT_REGN_1_MODE                  1
#define FLASH_SEC_MASK_REGN_1_MODE                   ((u32)0x00000003 << 1)                              /*!<R/W 0  Cipher Mode used in region 1. 2'b00: GCM mode 2'b01: CTR mode 2'b10: ECB_MIX mode 2'b11: Reserved */
#define FLASH_SEC_SHIFT_REGN_1_ENABLE                0
#define FLASH_SEC_BIT_REGN_1_ENABLE                  ((u32)0x00000001 << 0)                              /*!<R/W 0  Enable region 1 cipher setting. */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_CIPHER_REGION2_BASE_REG
 * @brief  Flash SEC Engine Cipher Region2 Base Address Register (@ 0X050)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_REGN_2_BASE                  12
#define FLASH_SEC_MASK_REGN_2_BASE                   ((u32)0x000FFFFF << 12)                             /*!<R/W 0  Region 2_cipher base address. */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_CIPHER_REGION2_END_REG
 * @brief  Flash SEC Engine Cipher Region2 End Address Register (@ 0X054)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_REGN_2_END                   12
#define FLASH_SEC_MASK_REGN_2_END                    ((u32)0x000FFFFF << 12)                             /*!<R/W 0  Region 2 cipher end address. */
#define FLASH_SEC_SHIFT_REGN_2_IV_NUM                8
#define FLASH_SEC_MASK_REGN_2_IV_NUM                 ((u32)0x00000007 << 8)                              /*!<R/W 0  IV pattern used in region 2. Apply which IV pattern registers to this region.(Number corresponds to IV pattern registers) */
#define FLASH_SEC_SHIFT_REGN_2_MODE                  1
#define FLASH_SEC_MASK_REGN_2_MODE                   ((u32)0x00000003 << 1)                              /*!<R/W 0  Cipher Mode used in region 2. 2'b00: GCM mode 2'b01: CTR mode 2'b10: ECB_MIX mode 2'b11: Reserved */
#define FLASH_SEC_SHIFT_REGN_2_ENABLE                0
#define FLASH_SEC_BIT_REGN_2_ENABLE                  ((u32)0x00000001 << 0)                              /*!<R/W 0  Enable region 2 cipher setting. */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_CIPHER_REGION3_BASE_REG
 * @brief  Flash SEC Engine Cipher Region3 Base Address Register (@ 0X058)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_REGN_3_BASE                  12
#define FLASH_SEC_MASK_REGN_3_BASE                   ((u32)0x000FFFFF << 12)                             /*!<R/W 0  Region 3_cipher base address. */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_CIPHER_REGION3_END_REG
 * @brief  Flash SEC Engine Cipher Region3 End Address Register (@ 0X05C)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_REGN_3_END                   12
#define FLASH_SEC_MASK_REGN_3_END                    ((u32)0x000FFFFF << 12)                             /*!<R/W 0  Region 3 cipher end address. */
#define FLASH_SEC_SHIFT_REGN_3_IV_NUM                8
#define FLASH_SEC_MASK_REGN_3_IV_NUM                 ((u32)0x00000007 << 8)                              /*!<R/W 0  IV pattern used in region 3. Apply which IV pattern registers to this region.(Number corresponds to IV pattern registers) */
#define FLASH_SEC_SHIFT_REGN_3_MODE                  1
#define FLASH_SEC_MASK_REGN_3_MODE                   ((u32)0x00000003 << 1)                              /*!<R/W 0  Cipher Mode used in region 3. 2'b00: GCM mode 2'b01: CTR mode 2'b10: ECB_MIX mode 2'b11: Reserved */
#define FLASH_SEC_SHIFT_REGN_3_ENABLE                0
#define FLASH_SEC_BIT_REGN_3_ENABLE                  ((u32)0x00000001 << 0)                              /*!<R/W 0  Enable region 3 cipher setting. */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_CIPHER_REGION4_BASE_REG
 * @brief  Flash SEC Engine Cipher Region4 Base Address Register (@ 0X060)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_REGN_4_BASE                  12
#define FLASH_SEC_MASK_REGN_4_BASE                   ((u32)0x000FFFFF << 12)                             /*!<R/W 0  Region 4_cipher base address. */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_CIPHER_REGION4_END_REG
 * @brief  Flash SEC Engine Cipher Region4 End Address Register (@ 0X064)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_REGN_4_END                   12
#define FLASH_SEC_MASK_REGN_4_END                    ((u32)0x000FFFFF << 12)                             /*!<R/W 0  Region 4 cipher end address. */
#define FLASH_SEC_SHIFT_REGN_4_IV_NUM                8
#define FLASH_SEC_MASK_REGN_4_IV_NUM                 ((u32)0x00000007 << 8)                              /*!<R/W 0  IV pattern used in region 4. Apply which IV pattern registers to this region.(Number corresponds to IV pattern registers) */
#define FLASH_SEC_SHIFT_REGN_4_MODE                  1
#define FLASH_SEC_MASK_REGN_4_MODE                   ((u32)0x00000003 << 1)                              /*!<R/W 0  Cipher Mode used in region 4. 2'b00: GCM mode 2'b01: CTR mode 2'b10: ECB_MIX mode 2'b11: Reserved */
#define FLASH_SEC_SHIFT_REGN_4_ENABLE                0
#define FLASH_SEC_BIT_REGN_4_ENABLE                  ((u32)0x00000001 << 0)                              /*!<R/W 0  Enable region 4 cipher setting. */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_CIPHER_REGION5_BASE_REG
 * @brief  Flash SEC Engine Cipher Region5 Base Address Register (@ 0X068)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_REGN_5_BASE                  12
#define FLASH_SEC_MASK_REGN_5_BASE                   ((u32)0x000FFFFF << 12)                             /*!<R/W 0  Region 5_cipher base address. */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_CIPHER_REGION5_END_REG
 * @brief  Flash SEC Engine Cipher Region5 End Address Register (@ 0X06C)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_REGN_5_END                   12
#define FLASH_SEC_MASK_REGN_5_END                    ((u32)0x000FFFFF << 12)                             /*!<R/W 0  Region 5 cipher end address. */
#define FLASH_SEC_SHIFT_REGN_5_IV_NUM                8
#define FLASH_SEC_MASK_REGN_5_IV_NUM                 ((u32)0x00000007 << 8)                              /*!<R/W 0  IV pattern used in region 5. Apply which IV pattern registers to this region.(Number corresponds to IV pattern registers) */
#define FLASH_SEC_SHIFT_REGN_5_MODE                  1
#define FLASH_SEC_MASK_REGN_5_MODE                   ((u32)0x00000003 << 1)                              /*!<R/W 0  Cipher Mode used in region 5. 2'b00: GCM mode 2'b01: CTR mode 2'b10: ECB_MIX mode 2'b11: Reserved */
#define FLASH_SEC_SHIFT_REGN_5_ENABLE                0
#define FLASH_SEC_BIT_REGN_5_ENABLE                  ((u32)0x00000001 << 0)                              /*!<R/W 0  Enable region 5 cipher setting. */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_CIPHER_REGION6_BASE_REG
 * @brief  Flash SEC Engine Cipher Region6 Base Address Register (@ 0X070)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_REGN_6_BASE                  12
#define FLASH_SEC_MASK_REGN_6_BASE                   ((u32)0x000FFFFF << 12)                             /*!<R/W 0  Region 6_cipher base address. */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_CIPHER_REGION6_END_REG
 * @brief  Flash SEC Engine Cipher Region6 End Address Register (@ 0X074)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_REGN_6_END                   12
#define FLASH_SEC_MASK_REGN_6_END                    ((u32)0x000FFFFF << 12)                             /*!<R/W 0  Region 6 cipher end address. */
#define FLASH_SEC_SHIFT_REGN_6_IV_NUM                8
#define FLASH_SEC_MASK_REGN_6_IV_NUM                 ((u32)0x00000007 << 8)                              /*!<R/W 0  IV pattern used in region 6. Apply which IV pattern registers to this region.(Number corresponds to IV pattern registers) */
#define FLASH_SEC_SHIFT_REGN_6_MODE                  1
#define FLASH_SEC_MASK_REGN_6_MODE                   ((u32)0x00000003 << 1)                              /*!<R/W 0  Cipher Mode used in region 6. 2'b00: GCM mode 2'b01: CTR mode 2'b10: ECB_MIX mode 2'b11: Reserved */
#define FLASH_SEC_SHIFT_REGN_6_ENABLE                0
#define FLASH_SEC_BIT_REGN_6_ENABLE                  ((u32)0x00000001 << 0)                              /*!<R/W 0  Enable region 6 cipher setting. */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_CIPHER_REGION7_BASE_REG
 * @brief  Flash SEC Engine Cipher Region7 Base Address Register (@ 0X078)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_REGN_7_BASE                  12
#define FLASH_SEC_MASK_REGN_7_BASE                   ((u32)0x000FFFFF << 12)                             /*!<R/W 0  Region 7 cipher base address. */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_CIPHER_REGION7_END_REG
 * @brief  Flash SEC Engine Cipher Region7 End Address Register (@ 0X07C)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_REGN_7_END                   12
#define FLASH_SEC_MASK_REGN_7_END                    ((u32)0x000FFFFF << 12)                             /*!<R/W 0  Region 7 cipher end address. */
#define FLASH_SEC_SHIFT_REGN_7_IV_NUM                8
#define FLASH_SEC_MASK_REGN_7_IV_NUM                 ((u32)0x00000007 << 8)                              /*!<R/W 0  IV pattern used in region 7. Apply which IV pattern registers to this region.(Number corresponds to IV pattern registers) */
#define FLASH_SEC_SHIFT_REGN_7_MODE                  1
#define FLASH_SEC_MASK_REGN_7_MODE                   ((u32)0x00000003 << 1)                              /*!<R/W 0  Cipher Mode used in region 7. 2'b00: GCM mode 2'b01: CTR mode 2'b10: ECB_MIX mode 2'b11: Reserved */
#define FLASH_SEC_SHIFT_REGN_7_ENABLE                0
#define FLASH_SEC_BIT_REGN_7_ENABLE                  ((u32)0x00000001 << 0)                              /*!<R/W 0  Enable region 7 cipher setting. */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_CIPHER_IV0_LOW_REG
 * @brief  Flash SEC Engine Cipher IV0 Low Pattern Register (@ 0X080)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_IV_0_LOW                     0
#define FLASH_SEC_MASK_IV_0_LOW                      ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  IV 0 Low Pattern value. IV is 16 bytes = iv_0_high(32) + iv_0_low(32) + flash_addr(32) + flash_addr_cnt(32) IV is 12 bytes = iv_0_high(32) + iv_0_low(32) + flash_addr(32) */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_CIPHER_IV0_HIGH_REG
 * @brief  Flash SEC Engine Cipher IV0 High Pattern Register (@ 0X084)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_IV_0_HIGH                    0
#define FLASH_SEC_MASK_IV_0_HIGH                     ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  IV 0 High Pattern value. IV is 16 bytes = iv_0_high(32) + iv_0_low(32) + flash_addr(32) + flash_addr_cnt(32) IV is 12 bytes = iv_0_high(32) + iv_0_low(32) + flash_addr(32) */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_CIPHER_IV1_LOW_REG
 * @brief  Flash SEC Engine Cipher IV1 Low Pattern Register (@ 0X088)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_IV_1_LOW                     0
#define FLASH_SEC_MASK_IV_1_LOW                      ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  IV 1 Low Pattern value. IV is 16 bytes = iv_1_high(32) + iv_1_low(32) + flash_addr(32) + flash_addr_cnt(32) IV is 12 bytes = iv_1_high(32) + iv_1_low(32) + flash_addr(32) */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_CIPHER_IV1_HIGH_REG
 * @brief  Flash SEC Engine Cipher IV1 High Pattern Register (@ 0X08C)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_IV_1_HIGH                    0
#define FLASH_SEC_MASK_IV_1_HIGH                     ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  IV 1 High Pattern value. IV is 16 bytes = iv_1_high(32) + iv_1_low(32) + flash_addr(32) + flash_addr_cnt(32) IV is 12 bytes = iv_1_high(32) + iv_1_low(32) + flash_addr(32) */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_CIPHER_IV2_LOW_REG
 * @brief  Flash SEC Engine Cipher IV2 Low Pattern Register (@ 0X090)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_IV_2_LOW                     0
#define FLASH_SEC_MASK_IV_2_LOW                      ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  IV 2 Low Pattern value. IV is 16 bytes = iv_2_high(32) + iv_2_low(32) + flash_addr(32) + flash_addr_cnt(32) IV is 12 bytes = iv_2_high(32) + iv_2_low(32) + flash_addr(32) */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_CIPHER_IV2_HIGH_REG
 * @brief  Flash SEC Engine Cipher IV2 High Pattern Register (@ 0X094)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_IV_2_HIGH                    0
#define FLASH_SEC_MASK_IV_2_HIGH                     ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  IV 2 High Pattern value. IV is 16 bytes = iv_2_high(32) + iv_2_low(32) + flash_addr(32) + flash_addr_cnt(32) IV is 12 bytes = iv_2_high(32) + iv_2_low(32) + flash_addr(32) */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_CIPHER_IV3_LOW_REG
 * @brief  Flash SEC Engine Cipher IV3 Low Pattern Register (@ 0X098)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_IV_3_LOW                     0
#define FLASH_SEC_MASK_IV_3_LOW                      ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  IV 3 Low Pattern value. IV is 16 bytes = iv_3_high(32) + iv_3_low(32) + flash_addr(32) + flash_addr_cnt(32) IV is 12 bytes = iv_3_high(32) + iv_3_low(32) + flash_addr(32) */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_CIPHER_IV3_HIGH_REG
 * @brief  Flash SEC Engine Cipher IV3 High Pattern Register (@ 0X09C)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_IV_3_HIGH                    0
#define FLASH_SEC_MASK_IV_3_HIGH                     ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  IV 3 High Pattern value. IV is 16 bytes = iv_3_high(32) + iv_3_low(32) + flash_addr(32) + flash_addr_cnt(32) IV is 12 bytes = iv_3_high(32) + iv_3_low(32) + flash_addr(32) */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_CIPHER_IV4_LOW_REG
 * @brief  Flash SEC Engine Cipher IV4 Low Pattern Register (@ 0X0A0)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_IV_4_LOW                     0
#define FLASH_SEC_MASK_IV_4_LOW                      ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  IV 4 Low Pattern value. IV is 16 bytes = iv_4_high(32) + iv_4_low(32) + flash_addr(32) + flash_addr_cnt(32) IV is 12 bytes = iv_4_high(32) + iv_4_low(32) + flash_addr(32) */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_CIPHER_IV4_HIGH_REG
 * @brief  Flash SEC Engine Cipher IV4 High Pattern Register (@ 0X0A4)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_IV_4_HIGH                    0
#define FLASH_SEC_MASK_IV_4_HIGH                     ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  IV 4 High Pattern value. IV is 16 bytes = iv_4_high(32) + iv_4_low(32) + flash_addr(32) + flash_addr_cnt(32) IV is 12 bytes = iv_4_high(32) + iv_4_low(32) + flash_addr(32) */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_CIPHER_IV5_LOW_REG
 * @brief  Flash SEC Engine Cipher IV5 Low Pattern Register (@ 0X0A8)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_IV_5_LOW                     0
#define FLASH_SEC_MASK_IV_5_LOW                      ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  IV 5 Low Pattern value. IV is 16 bytes = iv_5_high(32) + iv_5_low(32) + flash_addr(32) + flash_addr_cnt(32) IV is 12 bytes = iv_5_high(32) + iv_5_low(32) + flash_addr(32) */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_CIPHER_IV5_HIGH_REG
 * @brief  Flash SEC Engine Cipher IV5 High Pattern Register (@ 0X0AC)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_IV_5_HIGH                    0
#define FLASH_SEC_MASK_IV_5_HIGH                     ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  IV 5 High Pattern value. IV is 16 bytes = iv_5_high(32) + iv_5_low(32) + flash_addr(32) + flash_addr_cnt(32) IV is 12 bytes = iv_5_high(32) + iv_5_low(32) + flash_addr(32) */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_CIPHER_IV6_LOW_REG
 * @brief  Flash SEC Engine Cipher IV6 Low Pattern Register (@ 0X0B0)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_IV_6_LOW                     0
#define FLASH_SEC_MASK_IV_6_LOW                      ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  IV 6 Low Pattern value. IV is 16 bytes = iv_6_high(32) + iv_6_low(32) + flash_addr(32) + flash_addr_cnt(32) IV is 12 bytes = iv_6_high(32) + iv_6_low(32) + flash_addr(32) */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_CIPHER_IV6_HIGH_REG
 * @brief  Flash SEC Engine Cipher IV6 High Pattern Register (@ 0X0B4)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_IV_6_HIGH                    0
#define FLASH_SEC_MASK_IV_6_HIGH                     ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  IV 6 High Pattern value. IV is 16 bytes = iv_6_high(32) + iv_6_low(32) + flash_addr(32) + flash_addr_cnt(32) IV is 12 bytes = iv_6_high(32) + iv_6_low(32) + flash_addr(32) */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_CIPHER_IV7_LOW_REG
 * @brief  Flash SEC Engine Cipher IV7 Low Pattern Register (@ 0X0B8)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_IV_7_LOW                     0
#define FLASH_SEC_MASK_IV_7_LOW                      ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  IV 7 Low Pattern value. IV is 16 bytes = iv_7_high(32) + iv_7_low(32) + flash_addr(32) + flash_addr_cnt(32) IV is 12 bytes = iv_7_high(32) + iv_7_low(32) + flash_addr(32) */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_CIPHER_IV7_HIGH_REG
 * @brief  Flash SEC Engine Cipher IV7 High Pattern Register (@ 0X0BC)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_IV_7_HIGH                    0
#define FLASH_SEC_MASK_IV_7_HIGH                     ((u32)0xFFFFFFFF << 0)                              /*!<R/W 0  IV 7 High Pattern value. IV is 16 bytes = iv_7_high(32) + iv_7_low(32) + flash_addr(32) + flash_addr_cnt(32) IV is 12 bytes = iv_7_high(32) + iv_7_low(32) + flash_addr(32) */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_REMAP0_ADDR_REG
 * @brief  Flash SEC Engine Remap Region0 Address Register (@ 0X100)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_REMAP_BASE_0_ADDR            16
#define FLASH_SEC_MASK_REMAP_BASE_0_ADDR             ((u32)0x0000FFFF << 16)                             /*!<R/W 0  Remap region 0 base address[27:12]. Region Base Addr[31:0] = {flash_addr[31:28] + remap_base_addr + 12'b0}. The region address is 4KB aligned, and remap region size not cross 256MB. */
#define FLASH_SEC_SHIFT_REMAP_END_0_ADDR             0
#define FLASH_SEC_MASK_REMAP_END_0_ADDR              ((u32)0x0000FFFF << 0)                              /*!<R/W 0  Remap region 0 end address[27:12]. Region End Addr[31:0] = {flash_addr[31:28] + remap_end_addr + 12'b0}. The region address is 4KB aligned, and remap region size not cross 256MB. */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_REMAP0_OFFSET_REG
 * @brief  Flash SEC Engine Remap Region0 Offset Register (@ 0X104)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_REMAP_0_OFFSET               16
#define FLASH_SEC_MASK_REMAP_0_OFFSET                ((u32)0x0000FFFF << 16)                             /*!<R/W 0  Remap region 0 offset[27:12]. Region offset[31:0] = {4'b0 + remap_offset + 12'b0}. The output address is [Access address - region_base_addr + region_offset]. */
#define FLASH_SEC_SHIFT_REMAP_0_ENABLE               0
#define FLASH_SEC_BIT_REMAP_0_ENABLE                 ((u32)0x00000001 << 0)                              /*!<R/W 0  Remap region 0 enable. */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_REMAP1_ADDR_REG
 * @brief  Flash SEC Engine Remap Region1 Address Register (@ 0X108)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_REMAP_BASE_1_ADDR            16
#define FLASH_SEC_MASK_REMAP_BASE_1_ADDR             ((u32)0x0000FFFF << 16)                             /*!<R/W 0  Remap region 1 base address[27:12]. Region Base Addr[31:0] = {flash_addr[31:28] + remap_base_addr + 12'b0}. The region address is 4KB aligned, and remap region size not cross 256MB. */
#define FLASH_SEC_SHIFT_REMAP_END_1_ADDR             0
#define FLASH_SEC_MASK_REMAP_END_1_ADDR              ((u32)0x0000FFFF << 0)                              /*!<R/W 0  Remap region 1 end address[27:12]. Region End Addr[31:0] = {flash_addr[31:28] + remap_end_addr + 12'b0}. The region address is 4KB aligned, and remap region size not cross 256MB. */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_REMAP1_OFFSET_REG
 * @brief  Flash SEC Engine Remap Region1 Offset Register (@ 0X10C)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_REMAP_1_OFFSET               16
#define FLASH_SEC_MASK_REMAP_1_OFFSET                ((u32)0x0000FFFF << 16)                             /*!<R/W 0  Remap region 1 offset[27:12]. Region offset[31:0] = {4'b0 + remap_offset + 12'b0}. The output address is [Access address - region_base_addr + region_offset]. */
#define FLASH_SEC_SHIFT_REMAP_1_ENABLE               0
#define FLASH_SEC_BIT_REMAP_1_ENABLE                 ((u32)0x00000001 << 0)                              /*!<R/W 0  Remap region 1 enable. */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_REMAP2_ADDR_REG
 * @brief  Flash SEC Engine Remap Region2 Address Register (@ 0X110)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_REMAP_BASE_2_ADDR            16
#define FLASH_SEC_MASK_REMAP_BASE_2_ADDR             ((u32)0x0000FFFF << 16)                             /*!<R/W 0  Remap region 2 base address[27:12]. Region Base Addr[31:0] = {flash_addr[31:28] + remap_base_addr + 12'b0}. The region address is 4KB aligned, and remap region size not cross 256MB. */
#define FLASH_SEC_SHIFT_REMAP_END_2_ADDR             0
#define FLASH_SEC_MASK_REMAP_END_2_ADDR              ((u32)0x0000FFFF << 0)                              /*!<R/W 0  Remap region 2 end address[27:12]. Region End Addr[31:0] = {flash_addr[31:28] + remap_end_addr + 12'b0}. The region address is 4KB aligned, and remap region size not cross 256MB. */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_REMAP2_OFFSET_REG
 * @brief  Flash SEC Engine Remap Region2 Offset Register (@ 0X114)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_REMAP_2_OFFSET               16
#define FLASH_SEC_MASK_REMAP_2_OFFSET                ((u32)0x0000FFFF << 16)                             /*!<R/W 0  Remap region 2 offset[27:12]. Region offset[31:0] = {4'b0 + remap_offset + 12'b0}. The output address is [Access address - region_base_addr + region_offset]. */
#define FLASH_SEC_SHIFT_REMAP_2_ENABLE               0
#define FLASH_SEC_BIT_REMAP_2_ENABLE                 ((u32)0x00000001 << 0)                              /*!<R/W 0  Remap region 2 enable. */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_REMAP3_ADDR_REG
 * @brief  Flash SEC Engine Remap Region3 Address Register (@ 0X118)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_REMAP_BASE_3_ADDR            16
#define FLASH_SEC_MASK_REMAP_BASE_3_ADDR             ((u32)0x0000FFFF << 16)                             /*!<R/W 0  Remap region 3 base address[27:12]. Region Base Addr[31:0] = {flash_addr[31:28] + remap_base_addr + 12'b0}. The region address is 4KB aligned, and remap region size not cross 256MB. */
#define FLASH_SEC_SHIFT_REMAP_END_3_ADDR             0
#define FLASH_SEC_MASK_REMAP_END_3_ADDR              ((u32)0x0000FFFF << 0)                              /*!<R/W 0  Remap region 3 end address[27:12]. Region End Addr[31:0] = {flash_addr[31:28] + remap_end_addr + 12'b0}. The region address is 4KB aligned, and remap region size not cross 256MB. */
/** @} */

/**************************************************************************//**
 * @defgroup FLASH_SEC_SEC_REMAP3_OFFSET_REG
 * @brief  Flash SEC Engine Remap Region3 Offset Register (@ 0X11C)
 * @{
 *****************************************************************************/
#define FLASH_SEC_SHIFT_REMAP_3_OFFSET               16
#define FLASH_SEC_MASK_REMAP_3_OFFSET                ((u32)0x0000FFFF << 16)                             /*!<R/W 0  Remap region 3 offset[27:12]. Region offset[31:0] = {4'b0 + remap_offset + 12'b0}. The output address is [Access address - region_base_addr + region_offset]. */
#define FLASH_SEC_SHIFT_REMAP_3_ENABLE               0
#define FLASH_SEC_BIT_REMAP_3_ENABLE                 ((u32)0x00000001 << 0)                              /*!<R/W 0  Remap region 3 enable. */
/** @} */

/**************************************************************************//**
 * @defgroup rtl8735b_FLASH_SEC
 * @{
 * @brief rtl8735b_FLASH_SEC Register Declaration
 *****************************************************************************/
typedef struct {
	__I  uint32_t FLASH_SEC_SEC_STS_REG ;                  /*!<  Flash SEC Engine Status Register register,  Address offset: 0x000 */
	__I  uint32_t FLASH_SEC_SEC_CID_REG ;                  /*!<  Flash SEC Engine Component Identification Register register,  Address offset: 0x004 */
	__I  uint32_t FLASH_SEC_SEC_ERR_ADDR_REG ;             /*!<  Flash SEC Engine Error Address Log Register register,  Address offset: 0x008 */
	__O  uint32_t FLASH_SEC_SEC_RESV0_REG ;                /*!<  Flash SEC Engine Reserved 0 Register register,  Address offset: 0x00C */
	__O  uint32_t FLASH_SEC_SEC_CLR_INT_REG ;              /*!<  Flash SEC Engine Clear Interrupt Register register,  Address offset: 0x010 */
	__IO uint32_t FLASH_SEC_SEC_CTRL_REG ;                 /*!<  Flash SEC Engine Control Register register,  Address offset: 0x014 */
	__O  uint32_t FLASH_SEC_SEC_MAINTAIN_OP_REG ;          /*!<  Flash SEC Engine Maintenance Operation Register register,  Address offset: 0x018 */
	__IO uint32_t FLASH_SEC_SEC_LOCK_CTRL_REG ;            /*!<  Flash SEC Engine Write Lock Control Register register,  Address offset: 0x01C */
	__IO uint32_t FLASH_SEC_SEC_GCM_TAG_BASE_REG ;         /*!<  Flash SEC Engine AES GCM TAG Base Address Register register,  Address offset: 0x020 */
	__IO uint32_t RSVD0[7];                                /*!<  Reserved,  Address offset:0x24-0x3C */
	__IO uint32_t FLASH_SEC_SEC_CIPHER_REGION0_BASE_REG ;  /*!<  Flash SEC Engine Cipher Region0 Base Address Register register,  Address offset: 0x040 */
	__IO uint32_t FLASH_SEC_SEC_CIPHER_REGION0_END_REG ;   /*!<  Flash SEC Engine Cipher Region0 End Address Register register,  Address offset: 0x044 */
	__IO uint32_t FLASH_SEC_SEC_CIPHER_REGION1_BASE_REG ;  /*!<  Flash SEC Engine Cipher Region1 Base Address Register register,  Address offset: 0x048 */
	__IO uint32_t FLASH_SEC_SEC_CIPHER_REGION1_END_REG ;   /*!<  Flash SEC Engine Cipher Region1 End Address Register register,  Address offset: 0x04C */
	__IO uint32_t FLASH_SEC_SEC_CIPHER_REGION2_BASE_REG ;  /*!<  Flash SEC Engine Cipher Region2 Base Address Register register,  Address offset: 0x050 */
	__IO uint32_t FLASH_SEC_SEC_CIPHER_REGION2_END_REG ;   /*!<  Flash SEC Engine Cipher Region2 End Address Register register,  Address offset: 0x054 */
	__IO uint32_t FLASH_SEC_SEC_CIPHER_REGION3_BASE_REG ;  /*!<  Flash SEC Engine Cipher Region3 Base Address Register register,  Address offset: 0x058 */
	__IO uint32_t FLASH_SEC_SEC_CIPHER_REGION3_END_REG ;   /*!<  Flash SEC Engine Cipher Region3 End Address Register register,  Address offset: 0x05C */
	__IO uint32_t FLASH_SEC_SEC_CIPHER_REGION4_BASE_REG ;  /*!<  Flash SEC Engine Cipher Region4 Base Address Register register,  Address offset: 0x060 */
	__IO uint32_t FLASH_SEC_SEC_CIPHER_REGION4_END_REG ;   /*!<  Flash SEC Engine Cipher Region4 End Address Register register,  Address offset: 0x064 */
	__IO uint32_t FLASH_SEC_SEC_CIPHER_REGION5_BASE_REG ;  /*!<  Flash SEC Engine Cipher Region5 Base Address Register register,  Address offset: 0x068 */
	__IO uint32_t FLASH_SEC_SEC_CIPHER_REGION5_END_REG ;   /*!<  Flash SEC Engine Cipher Region5 End Address Register register,  Address offset: 0x06C */
	__IO uint32_t FLASH_SEC_SEC_CIPHER_REGION6_BASE_REG ;  /*!<  Flash SEC Engine Cipher Region6 Base Address Register register,  Address offset: 0x070 */
	__IO uint32_t FLASH_SEC_SEC_CIPHER_REGION6_END_REG ;   /*!<  Flash SEC Engine Cipher Region6 End Address Register register,  Address offset: 0x074 */
	__IO uint32_t FLASH_SEC_SEC_CIPHER_REGION7_BASE_REG ;  /*!<  Flash SEC Engine Cipher Region7 Base Address Register register,  Address offset: 0x078 */
	__IO uint32_t FLASH_SEC_SEC_CIPHER_REGION7_END_REG ;   /*!<  Flash SEC Engine Cipher Region7 End Address Register register,  Address offset: 0x07C */
	__IO uint32_t FLASH_SEC_SEC_CIPHER_IV0_LOW_REG ;       /*!<  Flash SEC Engine Cipher IV0 Low Pattern Register register,  Address offset: 0x080 */
	__IO uint32_t FLASH_SEC_SEC_CIPHER_IV0_HIGH_REG ;      /*!<  Flash SEC Engine Cipher IV0 High Pattern Register register,  Address offset: 0x084 */
	__IO uint32_t FLASH_SEC_SEC_CIPHER_IV1_LOW_REG ;       /*!<  Flash SEC Engine Cipher IV1 Low Pattern Register register,  Address offset: 0x088 */
	__IO uint32_t FLASH_SEC_SEC_CIPHER_IV1_HIGH_REG ;      /*!<  Flash SEC Engine Cipher IV1 High Pattern Register register,  Address offset: 0x08C */
	__IO uint32_t FLASH_SEC_SEC_CIPHER_IV2_LOW_REG ;       /*!<  Flash SEC Engine Cipher IV2 Low Pattern Register register,  Address offset: 0x090 */
	__IO uint32_t FLASH_SEC_SEC_CIPHER_IV2_HIGH_REG ;      /*!<  Flash SEC Engine Cipher IV2 High Pattern Register register,  Address offset: 0x094 */
	__IO uint32_t FLASH_SEC_SEC_CIPHER_IV3_LOW_REG ;       /*!<  Flash SEC Engine Cipher IV3 Low Pattern Register register,  Address offset: 0x098 */
	__IO uint32_t FLASH_SEC_SEC_CIPHER_IV3_HIGH_REG ;      /*!<  Flash SEC Engine Cipher IV3 High Pattern Register register,  Address offset: 0x09C */
	__IO uint32_t FLASH_SEC_SEC_CIPHER_IV4_LOW_REG ;       /*!<  Flash SEC Engine Cipher IV4 Low Pattern Register register,  Address offset: 0x0A0 */
	__IO uint32_t FLASH_SEC_SEC_CIPHER_IV4_HIGH_REG ;      /*!<  Flash SEC Engine Cipher IV4 High Pattern Register register,  Address offset: 0x0A4 */
	__IO uint32_t FLASH_SEC_SEC_CIPHER_IV5_LOW_REG ;       /*!<  Flash SEC Engine Cipher IV5 Low Pattern Register register,  Address offset: 0x0A8 */
	__IO uint32_t FLASH_SEC_SEC_CIPHER_IV5_HIGH_REG ;      /*!<  Flash SEC Engine Cipher IV5 High Pattern Register register,  Address offset: 0x0AC */
	__IO uint32_t FLASH_SEC_SEC_CIPHER_IV6_LOW_REG ;       /*!<  Flash SEC Engine Cipher IV6 Low Pattern Register register,  Address offset: 0x0B0 */
	__IO uint32_t FLASH_SEC_SEC_CIPHER_IV6_HIGH_REG ;      /*!<  Flash SEC Engine Cipher IV6 High Pattern Register register,  Address offset: 0x0B4 */
	__IO uint32_t FLASH_SEC_SEC_CIPHER_IV7_LOW_REG ;       /*!<  Flash SEC Engine Cipher IV7 Low Pattern Register register,  Address offset: 0x0B8 */
	__IO uint32_t FLASH_SEC_SEC_CIPHER_IV7_HIGH_REG ;      /*!<  Flash SEC Engine Cipher IV7 High Pattern Register register,  Address offset: 0x0BC */
	__IO uint32_t RSVD1[16];                               /*!<  Reserved,  Address offset:0xC0-0xFC */
	__IO uint32_t FLASH_SEC_SEC_REMAP0_ADDR_REG ;          /*!<  Flash SEC Engine Remap Region0 Address Register register,  Address offset: 0x100 */
	__IO uint32_t FLASH_SEC_SEC_REMAP0_OFFSET_REG ;        /*!<  Flash SEC Engine Remap Region0 Offset Register register,  Address offset: 0x104 */
	__IO uint32_t FLASH_SEC_SEC_REMAP1_ADDR_REG ;          /*!<  Flash SEC Engine Remap Region1 Address Register register,  Address offset: 0x108 */
	__IO uint32_t FLASH_SEC_SEC_REMAP1_OFFSET_REG ;        /*!<  Flash SEC Engine Remap Region1 Offset Register register,  Address offset: 0x10C */
	__IO uint32_t FLASH_SEC_SEC_REMAP2_ADDR_REG ;          /*!<  Flash SEC Engine Remap Region2 Address Register register,  Address offset: 0x110 */
	__IO uint32_t FLASH_SEC_SEC_REMAP2_OFFSET_REG ;        /*!<  Flash SEC Engine Remap Region2 Offset Register register,  Address offset: 0x114 */
	__IO uint32_t FLASH_SEC_SEC_REMAP3_ADDR_REG ;          /*!<  Flash SEC Engine Remap Region3 Address Register register,  Address offset: 0x118 */
	__IO uint32_t FLASH_SEC_SEC_REMAP3_OFFSET_REG ;        /*!<  Flash SEC Engine Remap Region3 Offset Register register,            Address offset: 0x11C */
} FLASH_SEC_TypeDef;
/** @} */

#endif
