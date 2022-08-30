#ifndef RTL8735B_DRAMC_TYPE_H
#define RTL8735B_DRAMC_TYPE_H

#define MS_PCTL_CCR_OFFSET        0x000
#define MS_PCTL_DCR_OFFSET        0x004
#define MS_PCTL_IOCR_OFFSET       0x008
#define MS_PCTL_CSR_OFFSET        0x00c
#define MS_PCTL_DRR_OFFSET        0x010
#define MS_PCTL_TPR0_OFFSET       0x014
#define MS_PCTL_TPR1_OFFSET       0x018
#define MS_PCTL_TPR2_OFFSET       0x01c
#define MS_PCTL_TPR3_OFFSET       0x020

#define MS_PCTL_CDPIN_NDGE_OFFSET 0x024
#define MS_PCTL_CDPIN_OFFSET      0x028
#define MS_PCTL_TDPIN_OFFSET      0x02c

#define MS_PCTL_MRINFO_OFFSET     0x030
#define MS_PCTL_MR0_OFFSET        0x034
#define MS_PCTL_MR1_OFFSET        0x038
#define MS_PCTL_MR2_OFFSET        0x03c
#define MS_PCTL_MR3_OFFSET        0x040
#define MS_PCTL_MR4_OFFSET        0x044
#define MS_PCTL_MR5_OFFSET        0x048
#define MS_PCTL_MR6_OFFSET        0x04c
#define MS_PCTL_MR11_OFFSET       0x050
#define MS_PCTL_MR12_OFFSET       0x054
#define MS_PCTL_MR13_OFFSET       0x058
#define MS_PCTL_MR14_OFFSET       0x05c
#define MS_PCTL_MR22_OFFSET       0x060

#define MS_PCTL_TPR4_OFFSET       0x090
#define MS_PCTL_TPR5_OFFSET       0x094
#define MS_PCTL_DPDRI_OFFSET      0x0c0
#define MS_PCTL_DPDR_OFFSET       0x0c4
#define MS_PCTL_ISR_OFFSET        0x0c8
#define MS_PCTL_IMR_OFFSET        0x0cc

#define MS_PCTL_BCR_OFFSET        0x0d0
#define MS_PCTL_BCT_OFFSET        0x0d4
#define MS_PCTL_BCM_OFFSET        0x0d8
#define MS_PCTL_BST_OFFSET        0x0dc
#define MS_PCTL_BSRAM0_OFFSET     0x0e0
#define MS_PCTL_BSRAM1_OFFSET     0x0e4
#define MS_PCTL_BER_OFFSET        0x0e8
#define MS_PCTL_BEXPC_OFFSET      0x0ec

#define MS_PCTL_SVN_ID_OFFSET     0x0f4
#define MS_PCTL_IDR_OFFSET        0x0f8
#define MS_PCTL_ELR_OFFSET        0x0fc

#define MS_PHY_DLY0               0x100
#define MS_PHY_DLY1_RST           0x104
#define MS_PHY_DLY_CLK            0x108
#define MS_PHY_DLY_ST             0x10c
#define MS_PHY_DLY_NUM            0x110
#define MS_PHY_DTR0               0x114
#define MS_PHY_DTR1               0x118
#define MS_PHY_DTAR               0x11c

#define MS_PCTL_DRAM_INFO         0x120

#define MS_DRAM_SIZE_OFFSET       0x220
#define MS_WRAP_MISC_OFFSET       0x224
#define MS_WRAP_CHOP_BD_OFFSET    0x228

#define MS_WRAP_IDR_OFFSET        0x2a0
#define MS_WRAP_VER_OFFSET        0x2a4

#define MS_PROF_ADDR_OFFSET       0x308
#define MS_PROF_DATA_OFFSET       0x30c
#define MS_SCRAM_ADDR_OFFSET      0x310
#define MS_SCRAM_DATA_OFFSET      0x314

#define MS_ROW_REMAP0_OFFSET      0x400
#define MS_ROW_REMAP1_OFFSET      0x404
#define MS_ROW_REMAP2_OFFSET      0x408
#define MS_BANK_REMAP0_OFFSET     0x40c
#define MS_COLU_REMAP0_OFFSET     0x410
#define MS_COLU_REMAP1_OFFSET     0x414
#define MS_RANK_REMAP0_OFFSET     0x418
#define MS_CH_REMAP0_OFFSET       0x41c
#define MS_BG_REMAP0_OFFSET       0x420

#define MS_SLOT_PARK_OFFSET       0x460
#define MS_SLOT_STARVE_OFFSET     0x464
#define MS_SLOT_CNTR_OFFSET       0x468

#define MS_CBCTL0_OFFSET          0x480
#define MS_CBCTL1_OFFSET          0x484
#define MS_CBSTARVE0_OFFSET       0x488
#define MS_CBSTARVE1_OFFSET       0x48c
#define MS_CBSTARVE2_OFFSET       0x490
#define MS_CBSTARVE3_OFFSET       0x494
#define MS_CBSTARVE4_OFFSET       0x498

#define MS_BANK_SCH_CTRL_OFFSET   0x4a0

#define PCTL_CCR_INIT_BFO          0
#define PCTL_CCR_INIT_BFW          1
#define PCTL_CCR_DTT_BFO           1
#define PCTL_CCR_DTT_BFW           1
#define PCTL_CCR_BTT_BFO           2
#define PCTL_CCR_BTT_BFW           1
#define PCTL_CCR_DPIT_BFO          3
#define PCTL_CCR_DPIT_BFW          1
#define PCTL_CCR_SRXT_BFO          4
#define PCTL_CCR_SRXT_BFW          1
#define PCTL_CCR_FLUSH_FIFO_BFO    8
#define PCTL_CCR_FLUSH_FIFO_BFW    1
#define PCTL_CCR_CR_UPDATE_BFO     31
#define PCTL_CCR_CR_UPDATE_BFW     1

#define PCTL_DCR_DDR_BFO           0
#define PCTL_DCR_DDR_BFW           4
#define PCTL_DCR_DQ_WID_BFO        4
#define PCTL_DCR_DQ_WID_BFW        4
#define PCTL_DCR_DFI_RATE_BFO      8
#define PCTL_DCR_DFI_RATE_BFW      3
#define PCTL_DCR_RANK2_BFO         12
#define PCTL_DCR_RANK2_BFW         1
#define PCTL_DCR_WR_DBI_BFO        16
#define PCTL_DCR_WR_DBI_BFW        1
#define PCTL_DCR_RD_DBI_BFO        17
#define PCTL_DCR_RD_DBI_BFW        1
#define PCTL_DCR_PAR_BFO           18
#define PCTL_DCR_PAR_BFW           1
#define PCTL_DCR_GEAR_DOWN_BFO     19
#define PCTL_DCR_GEAR_DOWN_BFW     1
#define PCTL_DCR_BG2_BFO           21
#define PCTL_DCR_BG2_BFW           1
#define PCTL_DCR_BG_REMAP_BFO      22
#define PCTL_DCR_BG_REMAP_BFW      1
#define PCTL_DCR_ZQC_BFO           30
#define PCTL_DCR_ZQC_BFW           1

#define PCTL_IOCR_ODT_2PINS_BFO    0
#define PCTL_IOCR_ODT_2PINS_BFW    1
#define PCTL_IOCR_CKE_NOP_BFO      1
#define PCTL_IOCR_CKE_NOP_BFW      1
#define PCTL_IOCR_STC_CKE_BFO      2
#define PCTL_IOCR_STC_CKE_BFW      1
#define PCTL_IOCR_STC_ODT_BFO      3
#define PCTL_IOCR_STC_ODT_BFW      1
#define PCTL_IOCR_CMD_2T_EN_BFO    4
#define PCTL_IOCR_CMD_2T_EN_BFW    1
#define PCTL_IOCR_RTW_2T_DIS_BFO   5
#define PCTL_IOCR_RTW_2T_DIS_BFW   1
#define PCTL_IOCR_HALF_CSN_BFO     6
#define PCTL_IOCR_HALF_CSN_BFW     1
#define PCTL_IOCR_RD_PIPE_BFO      8
#define PCTL_IOCR_RD_PIPE_BFW      4
#define PCTL_IOCR_TPHY_WD_BFO      12
#define PCTL_IOCR_TPHY_WD_BFW      5
#define PCTL_IOCR_TPHY_WL_BFO      17
#define PCTL_IOCR_TPHY_WL_BFW      3
#define PCTL_IOCR_TPHY_RD_EN_BFO   20
#define PCTL_IOCR_TPHY_RD_EN_BFW   5
#define PCTL_IOCR_DC_CH1_BFO       27
#define PCTL_IOCR_DC_CH1_BFW       1
#define PCTL_IOCR_ADDR_SHARE_BFO   28
#define PCTL_IOCR_ADDR_SHARE_BFW   1
#define PCTL_IOCR_AC_SHARE_BFO     29
#define PCTL_IOCR_AC_SHARE_BFW     1

#define PCTL_CSR_DPIN_CMD_BFO      0
#define PCTL_CSR_DPIN_CMD_BFW      2
#define PCTL_CSR_MEM_IDLE_BFO      8
#define PCTL_CSR_MEM_IDLE_BFW      1
#define PCTL_CSR_DT_IDLE_BFO       9
#define PCTL_CSR_DT_IDLE_BFW       1
#define PCTL_CSR_BIST_IDLE_BFO     10
#define PCTL_CSR_BIST_IDLE_BFW     1
#define PCTL_CSR_BT_FAIL_BFO       12
#define PCTL_CSR_BT_FAIL_BFW       1
#define PCTL_CSR_DPIN_MOD_BFO      16
#define PCTL_CSR_DPIN_MOD_BFW      3
#define PCTL_CSR_CR_GP_BFO         31
#define PCTL_CSR_CR_GP_BFW         1

#define PCTL_DRR_TRFC_BFO          0
#define PCTL_DRR_TRFC_BFW          7
#define PCTL_DRR_TREF_BFO          8
#define PCTL_DRR_TREF_BFW          16
#define PCTL_DRR_REF_NUM_BFO       24
#define PCTL_DRR_REF_NUM_BFW       4
#define PCTL_DRR_REF_DIS_BFO       28
#define PCTL_DRR_REF_DIS_BFW       1
#define PCTL_DRR_ZQCL_INV_BFO      29
#define PCTL_DRR_ZQCL_INV_BFW      3

#define PCTL_TPR0_TRP_BFO          0
#define PCTL_TPR0_TRP_BFW          4
#define PCTL_TPR0_TRAS_BFO         4
#define PCTL_TPR0_TRAS_BFW         5
#define PCTL_TPR0_TWR_BFO          9
#define PCTL_TPR0_TWR_BFW          4
#define PCTL_TPR0_TRTP_BFO         13
#define PCTL_TPR0_TRTP_BFW         4
#define PCTL_TPR0_TCKE_BFO         17
#define PCTL_TPR0_TCKE_BFW         6
#define PCTL_TPR0_TPD_EN_BFO       23
#define PCTL_TPR0_TPD_EN_BFW       1
#define PCTL_TPR0_TZQCS_BFO        24
#define PCTL_TPR0_TZQCS_BFW        8

#define PCTL_TPR1_TRRD_BFO         0
#define PCTL_TPR1_TRRD_BFW         4
#define PCTL_TPR1_TRC_BFO          4
#define PCTL_TPR1_TRC_BFW          6
#define PCTL_TPR1_TRCD_BFO         10
#define PCTL_TPR1_TRCD_BFW         4
#define PCTL_TPR1_TCCD_BFO         14
#define PCTL_TPR1_TCCD_BFW         3
#define PCTL_TPR1_TWTR_BFO         17
#define PCTL_TPR1_TWTR_BFW         3
#define PCTL_TPR1_TRTW_BFO         20
#define PCTL_TPR1_TRTW_BFW         4
#define PCTL_TPR1_TFAW_BFO         24
#define PCTL_TPR1_TFAW_BFW         5

#define PCTL_TPR2_INIT_REF_NUM_BFO 0
#define PCTL_TPR2_INIT_REF_NUM_BFW 4
#define PCTL_TPR2_TMRD_BFO         4
#define PCTL_TPR2_TMRD_BFW         4
#define PCTL_TPR2_INIT_NS_BFO      8
#define PCTL_TPR2_INIT_NS_BFW      4
#define PCTL_TPR2_INIT_US_BFO      12
#define PCTL_TPR2_INIT_US_BFW      10
#define PCTL_TPR2_INIT_RST_US_BFO  22
#define PCTL_TPR2_INIT_RST_US_BFW  10

#define PCTL_TPR3_TRPAB_PB_BFO     0
#define PCTL_TPR3_TRPAB_PB_BFW     2
#define PCTL_TPR3_TRAS_MSB_BFO     2
#define PCTL_TPR3_TRAS_MSB_BFW     1
#define PCTL_TPR3_TFAW_MSB_BFO     3
#define PCTL_TPR3_TFAW_MSB_BFW     1
#define PCTL_TPR3_DPIN_LAT_BFO     4
#define PCTL_TPR3_DPIN_LAT_BFW     3
#define PCTL_TPR3_TRCD_MSB_BFO     7
#define PCTL_TPR3_TRCD_MSB_BFW     1
#define PCTL_TPR3_TWTR_MSB_BFO     8
#define PCTL_TPR3_TWTR_MSB_BFW     1
#define PCTL_TPR3_TRTW_MSB_BFO     9
#define PCTL_TPR3_TRTW_MSB_BFW     1
#define PCTL_TPR3_TRFC_MSB_BFO     10
#define PCTL_TPR3_TRFC_MSB_BFW     1
#define PCTL_TPR3_TWR_MSB_BFO      11
#define PCTL_TPR3_TWR_MSB_BFW      1
#define PCTL_TPR3_TPPD_BFO         12
#define PCTL_TPR3_TPPD_BFW         2
#define PCTL_TPR3_TCCD_S_BFO       14
#define PCTL_TPR3_TCCD_S_BFW       3
#define PCTL_TPR3_TWTR_S_BFO       17
#define PCTL_TPR3_TWTR_S_BFW       3
#define PCTL_TPR3_TRRD_S_BFO       20
#define PCTL_TPR3_TRRD_S_BFW       4
#define PCTL_TPR3_TCCD_KW_BFO      24
#define PCTL_TPR3_TCCD_KW_BFW      4
#define PCTL_TPR3_TCCD_R_BFO       28
#define PCTL_TPR3_TCCD_R_BFW       4

#define PCTL_CMD_DPIN_NDGE_ADR_BFO   0
#define PCTL_CMD_DPIN_NDGE_ADR_BFW   17
#define PCTL_CMD_DPIN_NDGE_BANK_BFO  17
#define PCTL_CMD_DPIN_NDGE_BANK_BFW  4
#define PCTL_CMD_DPIN_NDGE_WEN_BFO   21
#define PCTL_CMD_DPIN_NDGE_WEN_BFW   1
#define PCTL_CMD_DPIN_NDGE_CAS_BFO   22
#define PCTL_CMD_DPIN_NDGE_CAS_BFW   1
#define PCTL_CMD_DPIN_NDGE_RAS_BFO   23
#define PCTL_CMD_DPIN_NDGE_RAS_BFW   1
#define PCTL_CMD_DPIN_NDGE_CSN_BFO   24
#define PCTL_CMD_DPIN_NDGE_CSN_BFW   1
#define PCTL_CMD_DPIN_NDGE_ACTN_BFO  25
#define PCTL_CMD_DPIN_NDGE_ACTN_BFW  1
#define PCTL_CMD_DPIN_NDGE_PAR_BFO   26
#define PCTL_CMD_DPIN_NDGE_PAR_BFW   1
#define PCTL_CMD_DPIN_NDGE_CSN_1_BFO 31
#define PCTL_CMD_DPIN_NDGE_CSN_1_BFW 1

#define PCTL_CMD_DPIN_ADR_BFO      0
#define PCTL_CMD_DPIN_ADR_BFW      17
#define PCTL_CMD_DPIN_BANK_BFO     17
#define PCTL_CMD_DPIN_BANK_BFW     4
#define PCTL_CMD_DPIN_WEN_BFO      21
#define PCTL_CMD_DPIN_WEN_BFW      1
#define PCTL_CMD_DPIN_CAS_BFO      22
#define PCTL_CMD_DPIN_CAS_BFW      1
#define PCTL_CMD_DPIN_RAS_BFO      23
#define PCTL_CMD_DPIN_RAS_BFW      1
#define PCTL_CMD_DPIN_CSN_BFO      24
#define PCTL_CMD_DPIN_CSN_BFW      1
#define PCTL_CMD_DPIN_ACTN_BFO     25
#define PCTL_CMD_DPIN_ACTN_BFW     1
#define PCTL_CMD_DPIN_PAR_BFO      26
#define PCTL_CMD_DPIN_PAR_BFW      1
#define PCTL_CMD_DPIN_CSN_1_BFO    31
#define PCTL_CMD_DPIN_CSN_1_BFW    1

#define PCTL_TIE_DPIN_RSTN_BFO     0
#define PCTL_TIE_DPIN_RSTN_BFW     1
#define PCTL_TIE_DPIN_CKE_BFO      1
#define PCTL_TIE_DPIN_CKE_BFW      1
#define PCTL_TIE_DPIN_ODT_BFO      2
#define PCTL_TIE_DPIN_ODT_BFW      1
#define PCTL_TIE_DPIN_TEN_BFO      3
#define PCTL_TIE_DPIN_TEN_BFW      1
#define PCTL_TIE_DPIN_ALERTN_BFO   4
#define PCTL_TIE_DPIN_ALERTN_BFW   1
#define PCTL_TIE_DPIN_RSTN_1_BFO   29
#define PCTL_TIE_DPIN_RSTN_1_BFW   1
#define PCTL_TIE_DPIN_CKE_1_BFO    30
#define PCTL_TIE_DPIN_CKE_1_BFW    1
#define PCTL_TIE_DPIN_ODT_1_BFO    31
#define PCTL_TIE_DPIN_ODT_1_BFW    1

#define PCTL_MRINFO_WR_LAT_BFO     0
#define PCTL_MRINFO_WR_LAT_BFW     5
#define PCTL_MRINFO_RD_LAT_BFO     5
#define PCTL_MRINFO_RD_LAT_BFW     5
#define PCTL_MRINFO_ADD_LAT_BFO    10
#define PCTL_MRINFO_ADD_LAT_BFW    5
#define PCTL_MRINFO_TDQSCK_MAX_BFO 15
#define PCTL_MRINFO_TDQSCK_MAX_BFW 5
#define PCTL_MRINFO_NWR_BFO        20
#define PCTL_MRINFO_NWR_BFW        5
#define PCTL_MRINFO_RTP_BFO        25
#define PCTL_MRINFO_RTP_BFW        5

#define PCTL_MR0_BL_BFO            0
#define PCTL_MR0_BL_BFW            3
#define PCTL_MR0_BST_TYPE_BFO      3
#define PCTL_MR0_BST_TYPE_BFW      1
#define PCTL_MR0_CAS_BFO           4
#define PCTL_MR0_CAS_BFW           3
#define PCTL_MR0_WR_BFO            9
#define PCTL_MR0_WR_BFW            3

#define PCTL_MR1_DLL_EN_BFO        0
#define PCTL_MR1_DLL_EN_BFW        1
#define PCTL_MR1_BL_BFO            0
#define PCTL_MR1_BL_BFW            3
#define PCTL_MR1_ADD_LAT_BFO       3
#define PCTL_MR1_ADD_LAT_BFW       2
#define PCTL_MR1_WR_LP23_BFO       5
#define PCTL_MR1_WR_LP23_BFW       3
#define PCTL_MR1_WR_LP4_BFO        4
#define PCTL_MR1_WR_LP4_BFW        3
#define PCTL_MR1_RTT_NORM_EN_BFO   8
#define PCTL_MR1_RTT_NORM_EN_BFW   3

#define PCTL_MR2_CAS_BFO           0
#define PCTL_MR2_CAS_BFW           4
#define PCTL_MR2_CWL_BFO           3
#define PCTL_MR2_CWL_BFW           3
#define PCTL_MR2_DYC_ODT_EN_BFO    9
#define PCTL_MR2_DYC_ODT_EN_BFW    2

#define PCTL_TPR4_TRP_MSB_BFO      0
#define PCTL_TPR4_TRP_MSB_BFW      1

#define PCTL_TPR5_ODT_HOLD_BFO     0
#define PCTL_TPR5_ODT_HOLD_BFW     5
#define PCTL_TPR5_ODT_DLY_BFO      8
#define PCTL_TPR5_ODT_DLY_BFW      2

#define PCTL_BCR_STOP_BFO          0
#define PCTL_BCR_STOP_BFW          1
#define PCTL_BCR_CMP_BFO           1
#define PCTL_BCR_CMP_BFW           1
#define PCTL_BCR_LOOP_BFO          2
#define PCTL_BCR_LOOP_BFW          1
#define PCTL_BCR_DIS_MASK_BFO      3
#define PCTL_BCR_DIS_MASK_BFW      1
#define PCTL_BCR_AT_STOP_BFO       4
#define PCTL_BCR_AT_STOP_BFW       1
#define PCTL_BCR_CRR_BFO           5
#define PCTL_BCR_CRR_BFW           1
#define PCTL_BCR_FLUSH_CMD_BFO     8
#define PCTL_BCR_FLUSH_CMD_BFW     1
#define PCTL_BCR_FLUSH_WD_BFO      9
#define PCTL_BCR_FLUSH_WD_BFW      1
#define PCTL_BCR_FLUSH_RGD_BFO     10
#define PCTL_BCR_FLUSH_RGD_BFW     1
#define PCTL_BCR_FLUSH_RD_BFO      11
#define PCTL_BCR_FLUSH_RD_BFW      1
#define PCTL_BCR_RELOAD_CMD_BFO    12
#define PCTL_BCR_RELOAD_CMD_BFW    1
#define PCTL_BCR_RELOAD_WD_BFO     13
#define PCTL_BCR_RELOAD_WD_BFW     1
#define PCTL_BCR_RELOAD_RGD_BFO    14
#define PCTL_BCR_RELOAD_RGD_BFW    1
#define PCTL_BCR_RD_EXPC_BFO       16
#define PCTL_BCR_RD_EXPC_BFW       14

#define PCTL_BST_ERR_FST_TH_BFO    0
#define PCTL_BST_ERR_FST_TH_BFW    12
#define PCTL_BST_ERR_CNT_BFO       16
#define PCTL_BST_ERR_CNT_BFW       14

#define PCTL_BSRAM0_CMD_LEVEL_BFO  0
#define PCTL_BSRAM0_CMD_LEVEL_BFW  12
#define PCTL_BSRAM0_WD_LEVEL_BFO   16
#define PCTL_BSRAM0_WD_LEVEL_BFW   14

#define PCTL_BSRAM1_RG_LEVEL_BFO   0
#define PCTL_BSRAM1_RG_LEVEL_BFW   14
#define PCTL_BSRAM1_RD_LEVEL_BFO   16
#define PCTL_BSRAM1_RD_LEVEL_BFW   14

#define WRAP_MISC_PAGE_SIZE_BFO    0
#define WRAP_MISC_PAGE_SIZE_BFW    4
#define WRAP_MISC_BANK_SIZE_BFO    4
#define WRAP_MISC_BANK_SIZE_BFW    2
#define WRAP_MISC_BST_SIZE_BFO     6
#define WRAP_MISC_BST_SIZE_BFW     3
#define WRAP_MISC_HYBR_SIZE_BFO    10
#define WRAP_MISC_HYBR_SIZE_BFW    2

#define WRAP_CHOP_SIZE_BFO         0
#define WRAP_CHOP_SIZE_BFW         3

// vivian add for rxi316
#define ADDR_ROW0_REMAP_BFO     0
#define ADDR_ROW0_REMAP_BFW     4
#define ADDR_ROW1_REMAP_BFO     4
#define ADDR_ROW1_REMAP_BFW     4
#define ADDR_ROW2_REMAP_BFO     8
#define ADDR_ROW2_REMAP_BFW     4
#define ADDR_ROW3_REMAP_BFO     12
#define ADDR_ROW3_REMAP_BFW     4
#define ADDR_ROW4_REMAP_BFO     16
#define ADDR_ROW4_REMAP_BFW     4
#define ADDR_ROW5_REMAP_BFO     20
#define ADDR_ROW5_REMAP_BFW     4
#define ADDR_ROW6_REMAP_BFO     24
#define ADDR_ROW6_REMAP_BFW     4
#define ADDR_ROW7_REMAP_BFO     28
#define ADDR_ROW7_REMAP_BFW     4
#define ADDR_ROW8_REMAP_BFO     0
#define ADDR_ROW8_REMAP_BFW     4
#define ADDR_ROW9_REMAP_BFO     4
#define ADDR_ROW9_REMAP_BFW     4
#define ADDR_ROW10_REMAP_BFO    8
#define ADDR_ROW10_REMAP_BFW    4
#define ADDR_ROW11_REMAP_BFO    12
#define ADDR_ROW11_REMAP_BFW    4
#define ADDR_ROW12_REMAP_BFO    16
#define ADDR_ROW12_REMAP_BFW    4
#define ADDR_ROW13_REMAP_BFO    20
#define ADDR_ROW13_REMAP_BFW    4
#define ADDR_ROW14_REMAP_BFO    24
#define ADDR_ROW14_REMAP_BFW    4
#define ADDR_ROW15_REMAP_BFO    28
#define ADDR_ROW15_REMAP_BFW    4
#define ADDR_ROW16_REMAP_BFO    0
#define ADDR_ROW16_REMAP_BFW    4

#define ADDR_BANK0_REMAP_BFO    0
#define ADDR_BANK0_REMAP_BFW    5
#define ADDR_BANK1_REMAP_BFO    5
#define ADDR_BANK1_REMAP_BFW    5
#define ADDR_BANK2_REMAP_BFO    10
#define ADDR_BANK2_REMAP_BFW    5

#define ADDR_COLU2_REMAP_BFO    0
#define ADDR_COLU2_REMAP_BFW    4
#define ADDR_COLU3_REMAP_BFO    4
#define ADDR_COLU3_REMAP_BFW    4
#define ADDR_COLU4_REMAP_BFO    8
#define ADDR_COLU4_REMAP_BFW    4
#define ADDR_COLU5_REMAP_BFO    12
#define ADDR_COLU5_REMAP_BFW    4
#define ADDR_COLU6_REMAP_BFO    16
#define ADDR_COLU6_REMAP_BFW    4
#define ADDR_COLU7_REMAP_BFO    20
#define ADDR_COLU7_REMAP_BFW    4
#define ADDR_COLU8_REMAP_BFO    24
#define ADDR_COLU8_REMAP_BFW    4
#define ADDR_COLU9_REMAP_BFO    28
#define ADDR_COLU9_REMAP_BFW    4
#define ADDR_COLU10_REMAP_BFO   0
#define ADDR_COLU10_REMAP_BFW   4
#define ADDR_COLU11_REMAP_BFO   4
#define ADDR_COLU11_REMAP_BFW   4

#define ADDR_RANK_REMAP_BFO     0
#define ADDR_RANK_REMAP_BFW     5
#define ADDR_CH_REMAP_BFO       0
#define ADDR_CH_REMAP_BFW       5
#define ADDR_BG0_REMAP_BFO      0
#define ADDR_BG0_REMAP_BFW      5
#define ADDR_BG1_REMAP_BFO      5
#define ADDR_BG1_REMAP_BFW      5

// vivian add for rxi316 performance tuning
#define SLOT_PERF_PARK_BFO            0
#define SLOT_PERF_PARK_BFW            1
#define SLOT_IDLE_WINDOW_BFO          16
#define SLOT_IDLE_WINDOW_BFW          16

#define SLOT_LPW_STARVE_CYC_BFO       0
#define SLOT_LPW_STARVE_CYC_BFW       8
#define SLOT_HPR_STARVE_CYC_BFO       8
#define SLOT_HPR_STARVE_CYC_BFW       8
#define SLOT_LPR_STARVE_CYC_BFO       16
#define SLOT_LPR_STARVE_CYC_BFW       8
#define SLOT_BASE_STARVE_CYC_BFO      24
#define SLOT_BASE_STARVE_CYC_BFW      8

#define SLOT_LPW_IUS_LMT_BFO          0
#define SLOT_LPW_IUS_LMT_BFW          8
#define SLOT_HPR_IUS_LMT_BFO          8
#define SLOT_HPR_IUS_LMT_BFW          8
#define SLOT_LPR_IUS_LMT_BFO          16
#define SLOT_LPR_IUS_LMT_BFW          8

#define CBCTL0_LPR_FREESLOT_NUM_BFO   0
#define CBCTL0_LPR_FREESLOT_NUM_BFW   7
#define CBCTL0_LPR_RMW_RUN_LEN_BFO    16
#define CBCTL0_LPR_RMW_RUN_LEN_BFW    4

#define CBCTL1_DIS_WMG_BFO            0
#define CBCTL1_DIS_WMG_BFW            1
#define CBCTL1_PAGEOPEN_BFO           1
#define CBCTL1_PAGEOPEN_BFW           1
#define CBCTL1_WMG_NUM_THRESHOLD_BFO  8
#define CBCTL1_WMG_NUM_THRESHOLD_BFW  4
#define CBCTL1_LPW_RMW_RUN_LEN_BFO    16
#define CBCTL1_LPW_RMW_RUN_LEN_BFW    4

#define BANK_SCH_BA_SEL_LMT_BFO       0
#define BANK_SCH_BA_SEL_LMT_BFW       4
#define BANK_SCH_BG_SEL_LMT_BFO       4
#define BANK_SCH_BG_SEL_LMT_BFW       4
#define BANK_SCH_RA_SEL_LMT_BFO       8
#define BANK_SCH_RA_SEL_LMT_BFW       4

//----------------BSTC-----------------//
#define PCTL_BCR_STOP_BFO          0
#define PCTL_BCR_STOP_BFW          1
#define PCTL_BCR_CMP_BFO           1
#define PCTL_BCR_CMP_BFW           1
#define PCTL_BCR_LOOP_BFO          2
#define PCTL_BCR_LOOP_BFW          1
#define PCTL_BCR_DIS_MASK_BFO      3
#define PCTL_BCR_DIS_MASK_BFW      1
#define PCTL_BCR_AT_STOP_BFO       4
#define PCTL_BCR_AT_STOP_BFW       1
#define PCTL_BCR_CRR_BFO           5
#define PCTL_BCR_CRR_BFW           1
#define PCTL_BCR_HW_PAT_BFO        7
#define PCTL_BCR_HW_PAT_BFW        1
//#define PCTL_BCR_FLUSH_CMD_BFO     8
//#define PCTL_BCR_FLUSH_CMD_BFW     1
//#define PCTL_BCR_FLUSH_WD_BFO      9
//#define PCTL_BCR_FLUSH_WD_BFW      1
//#define PCTL_BCR_FLUSH_RGD_BFO     10
//#define PCTL_BCR_FLUSH_RGD_BFW     1
//#define PCTL_BCR_FLUSH_RD_BFO      11
//#define PCTL_BCR_FLUSH_RD_BFW      1
#define PCTL_BCR_RELOAD_BFO        12
#define PCTL_BCR_RELOAD_BFW        3
#define PCTL_BCR_FLUSH_RD_EXPC_BFO 16
#define PCTL_BCR_FLUSH_RD_EXPC_BFW 14

#define PCTL_BST_ERR_FST_TH_BFO    0
#define PCTL_BST_ERR_FST_TH_BFW    12
#define PCTL_BST_ERR_CNT_BFO       16
#define PCTL_BST_ERR_CNT_BFW       14

#define PCTL_BSRAM0_CMD_LEVEL_BFO  0
#define PCTL_BSRAM0_CMD_LEVEL_BFW  12
#define PCTL_BSRAM0_WD_LEVEL_BFO   16
#define PCTL_BSRAM0_WD_LEVEL_BFW   14

#define PCTL_BSRAM1_RG_LEVEL_BFO   0
#define PCTL_BSRAM1_RG_LEVEL_BFW   14
#define PCTL_BSRAM1_RD_LEVEL_BFO   16
#define PCTL_BSRAM1_RD_LEVEL_BFW   14

#define PCTL_BEXPR_CMD_EXPC_BFO 0
#define PCTL_BEXPR_CMD_EXPC_BFW 8
#define PCTL_BEXPR_WD_EXPC_BFO  8
#define PCTL_BEXPR_WD_EXPC_BFW  14

typedef struct {
	volatile unsigned int ccr;           /* 0x000 */
	volatile unsigned int dcr;           /* 0x004 */
	volatile unsigned int iocr;          /* 0x008 */
	volatile unsigned int csr;           /* 0x00c */
	volatile unsigned int drr;           /* 0x010 */
	volatile unsigned int tpr0;          /* 0x014 */
	volatile unsigned int tpr1;          /* 0x018 */
	volatile unsigned int tpr2;          /* 0x01c */
	volatile unsigned int tpr3;          /* 0x020 */
	volatile unsigned int cdpin_ndge;    /* 0x024 */
	volatile unsigned int cdpin;         /* 0x028 */
	volatile unsigned int tdpin;         /* 0x02c */
	volatile unsigned int mrinfo;        /* 0x030 */
	volatile unsigned int mr0;           /* 0x034 */
	volatile unsigned int mr1;           /* 0x038 */
	volatile unsigned int mr2;           /* 0x03c */
	volatile unsigned int mr3;           /* 0x040 */
	volatile unsigned int mr4;           /* 0x044 */
	volatile unsigned int mr5;           /* 0x048 */
	volatile unsigned int mr6;           /* 0x04c */
	volatile unsigned int mr11;          /* 0x050 */
	volatile unsigned int mr12;          /* 0x054 */
	volatile unsigned int mr13;          /* 0x058 */
	volatile unsigned int mr14;          /* 0x05c */
	volatile unsigned int mr22;          /* 0x060 */
	volatile unsigned int reserved0[11]; /* 0x064 - 0x08c */
	volatile unsigned int tpr4;          /* 0x090 */
	volatile unsigned int tpr5;          /* 0x094 */
	volatile unsigned int reserved1[10]; /* 0x098 - 0x0bc */
	volatile unsigned int dpdri;         /* 0x0c0 */
	volatile unsigned int dpdr;          /* 0x0c4 */
	volatile unsigned int isr;           /* 0x0c8 */
	volatile unsigned int imr;           /* 0x0cc */
	volatile unsigned int bcr;           /* 0x0d0 */
	volatile unsigned int bct;           /* 0x0d4 */
	volatile unsigned int bcm;           /* 0x0d8 */
	volatile unsigned int bst;           /* 0x0dc */
	volatile unsigned int bsram0;        /* 0x0e0 */
	volatile unsigned int bsram1;        /* 0x0e4 */
	volatile unsigned int ber;           /* 0x0e8 */
	volatile unsigned int bexpc;         /* 0x0ec */
	volatile unsigned int reserved2[1];  /* 0x0f0 */
	volatile unsigned int pctl_svn_id;   /* 0x0f4 */
	volatile unsigned int pctl_idr;      /* 0x0f8 */
	volatile unsigned int err;           /* 0x0fc */
	volatile unsigned int reserved3[73];
	// WRAP CONTROL REGISTER
	volatile unsigned int misc;          /* 0x224 */
	volatile unsigned int wrap_chop_bd;  /* 0x228 */
	volatile unsigned int reserved4[1];  /* 0x22c */
	volatile unsigned int dram_size;     /* 0x230 */
	volatile unsigned int reserved5[27]; /* 0x234 - 0x29c */
	volatile unsigned int wrap_idr;      /* 0x2a0 */
	volatile unsigned int wrap_svn;      /* 0x2a4 */
	volatile unsigned int reserved6[22];
	volatile unsigned int sch_index;     /* 0x300 */
	volatile unsigned int sch_data;      /* 0x304 */
	volatile unsigned int prof_addr;     /* 0x308 */
	volatile unsigned int prof_data;     /* 0x30c */
	volatile unsigned int reserved7[60];

	// vivian add for rxi316
	// ADDR REMAP REGISTER
	volatile unsigned int  row_remap0;   /* 0x400 */
	volatile unsigned int  row_remap1;   /* 0x404 */
	volatile unsigned int  row_remap2;   /* 0x408 */
	volatile unsigned int  bank_remap0;  /* 0x40c */
	volatile unsigned int  colu_remap0;  /* 0x410 */
	volatile unsigned int  colu_remap1;  /* 0x414 */
	volatile unsigned int  rank_remap0;  /* 0x418 */
	volatile unsigned int  ch_remap0;    /* 0x41c */
	volatile unsigned int  bg_remap0;    /* 0x420 */

	// add for rxi316 performance tuning
	volatile unsigned int  reserved8[15];/* 0x424 - 0x45c */
	volatile unsigned int  slot_park;    /* 0x460 */
	volatile unsigned int  slot_starve;  /* 0x464 */
	volatile unsigned int  slot_cntr;    /* 0x468 */
	volatile unsigned int  reserved9[5]; /* 0x46c - 0x47c */
	volatile unsigned int  cbctl0;       /* 0x480 */
	volatile unsigned int  cbctl1;       /* 0x484 */
	volatile unsigned int  cbstarve0;    /* 0x488 */
	volatile unsigned int  cbstarve1;    /* 0x48c */
	volatile unsigned int  cbstarve2;    /* 0x490 */
	volatile unsigned int  cbstarve3;    /* 0x494 */
	volatile unsigned int  cbstarve4;    /* 0x498 */
	volatile unsigned int  reserved10[1];/* 0x49c */
	volatile unsigned int  bank_sch_ctrl;/* 0x4a0 */
} DRAMC_TypeDef; //ms_rxi316_portmap

typedef struct  {
	volatile unsigned int  reserved17[64];
	volatile unsigned int  cm_fe_pa_0;  /* 0x1100 */
	volatile unsigned int  cm_fe_rrb_0;  /* 0x1104 */
	volatile unsigned int  reserved11[446];
	volatile unsigned int  pn_rqos_0;/* 0x1800 + n*0x40 */
	volatile unsigned int  pn_wqos_0;/* 0x1804 + n*0x40  */
	volatile unsigned int  pn_timeout_0;/* 0x1808 + n*0x40  */
	volatile unsigned int  pn_rdqueue_0;/* 0x180C + n*0x40  */
	volatile unsigned int  pn_expiryl_0;/* 0x1810 + n*0x40  */
	volatile unsigned int  pn_expiryh_0;/* 0x1814 + n*0x40  */
	volatile unsigned int  pn_portctrl_0;/* 0x1818 + n*0x40  */
	volatile unsigned int  reserved12[9];
	volatile unsigned int  pn_rqos_1;/* 0x1800 + n*0x40 */
	volatile unsigned int  pn_wqos_1;/* 0x1804 + n*0x40  */
	volatile unsigned int  pn_timeout_1;/* 0x1808 + n*0x40  */
	volatile unsigned int  pn_rdqueue_1;/* 0x180C + n*0x40  */
	volatile unsigned int  pn_expiryl_1;/* 0x1810 + n*0x40  */
	volatile unsigned int  pn_expiryh_1;/* 0x1814 + n*0x40  */
	volatile unsigned int  pn_portctrl_1;/* 0x1818 + n*0x40  */
	volatile unsigned int  reserved13[9];
	volatile unsigned int  pn_rqos_2;/* 0x1800 + n*0x40 */
	volatile unsigned int  pn_wqos_2;/* 0x1804 + n*0x40  */
	volatile unsigned int  pn_timeout_2;/* 0x1808 + n*0x40  */
	volatile unsigned int  pn_rdqueue_2;/* 0x180C + n*0x40  */
	volatile unsigned int  pn_expiryl_2;/* 0x1810 + n*0x40  */
	volatile unsigned int  pn_expiryh_2;/* 0x1814 + n*0x40  */
	volatile unsigned int  pn_portctrl_2;/* 0x1818 + n*0x40  */
	volatile unsigned int  reserved14[9];
	volatile unsigned int  pn_rqos_3;/* 0x1800 + n*0x40 */
	volatile unsigned int  pn_wqos_3;/* 0x1804 + n*0x40  */
	volatile unsigned int  pn_timeout_3;/* 0x1808 + n*0x40  */
	volatile unsigned int  pn_rdqueue_3;/* 0x180C + n*0x40  */
	volatile unsigned int  pn_expiryl_3;/* 0x1810 + n*0x40  */
	volatile unsigned int  pn_expiryh_3;/* 0x1814 + n*0x40  */
	volatile unsigned int  pn_portctrl_3;/* 0x1818 + n*0x40  */
	volatile unsigned int  reserved15[9];
	volatile unsigned int  pn_rqos_4;/* 0x1800 + n*0x40 */
	volatile unsigned int  pn_wqos_4;/* 0x1804 + n*0x40  */
	volatile unsigned int  pn_timeout_4;/* 0x1808 + n*0x40  */
	volatile unsigned int  pn_rdqueue_4;/* 0x180C + n*0x40  */
	volatile unsigned int  pn_expiryl_4;/* 0x1810 + n*0x40  */
	volatile unsigned int  pn_expiryh_4;/* 0x1814 + n*0x40  */
	volatile unsigned int  pn_portctrl_4;/* 0x1818 + n*0x40  */
	volatile unsigned int  reserved16[9];
	volatile unsigned int  pn_rqos_5;/* 0x1800 + n*0x40 */
	volatile unsigned int  pn_wqos_5;/* 0x1804 + n*0x40  */
	volatile unsigned int  pn_timeout_5;/* 0x1808 + n*0x40  */
	volatile unsigned int  pn_rdqueue_5;/* 0x180C + n*0x40  */
	volatile unsigned int  pn_expiryl_5;/* 0x1810 + n*0x40  */
	volatile unsigned int  pn_expiryh_5;/* 0x1814 + n*0x40  */
	volatile unsigned int  pn_portctrl_5;/* 0x1818 + n*0x40  */
} DRAM_FE_TypeDef; //ms_rxi316_ft_portmap

#endif // RTL8735B_DRAMC_TYPE_H

