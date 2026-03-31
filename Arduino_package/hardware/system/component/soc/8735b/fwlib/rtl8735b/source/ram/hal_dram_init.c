#include "cmsis.h"
#include "rtl8735b_dpi_type.h"
#include "rtl8735b_dramc_type.h"
#include "hal_dram_init.h"
#include "hal_timer.h"
#include "hal_api.h"
#include "hal_sys_ctrl.h"
#include "hal_dram_scan.h"

#define VERBOSE     0
#if defined(VERBOSE) && VERBOSE == 0
#undef DBG_DRAM_INFO
#define DBG_DRAM_INFO(...)
#endif

//#define TM_TTFF_MEASURE

#if defined(TM_TTFF_MEASURE)
#define dbg_printf(...)                     do {  } while(0)
#endif

#define ROUND_UP(divider, divisor) (((divider)%(divisor)) ? (((divider)/(divisor))+1) : ((divider)/(divisor)))

unsigned short pll_frequence_table[6][13] = {
	/*{ cco_band,          cco_kvco,         dpi_icp,        dpi_loop_pi_isel,
	    dpi_lpf_cp,        dpi_lpf_sr,       dpi_pdiv,       dpi_pll_ldo_vsel,
	    dp_pll_sel_cpmode, dpi_post_pi_bias, dpi_post_pi_rl, dpi_post_pi_rs,
	    dpi_v11_ldo_vsel}*/
	{3, 1, 3, 2, 1, 3, 0, 0, 1, 0, 3, 0, 0}, //533 MHz
	{1, 1, 3, 1, 1, 3, 0, 0, 1, 0, 2, 0, 0}, //400 MHz
	{1, 1, 3, 1, 1, 3, 0, 0, 1, 0, 2, 0, 0}, //333 MHz
	{0, 0, 3, 0, 1, 3, 0, 0, 1, 0, 2, 0, 0}, //200 MHz
	{3, 1, 3, 1, 1, 3, 0, 0, 1, 0, 3, 0, 0}, //480 MHz
	{3, 1, 3, 2, 1, 3, 0, 0, 1, 0, 3, 0, 0}  //Else
};

#if IS_CUT_TEST(CONFIG_CHIP_VER) || CONFIG_PXP || SIMU_DDR_PXP_INIT_FLOW_EN
struct rxi316_dram_info rxi316_ddr2_dev = {
	DDR_2,
	PAGE_2K,
	BANK_4,
	BST_LEN_8,
	SENQUENTIAL,
	HYBR_256MB,
	DQ_16,
	10  // dram_colu_bits
}; //rxi316_ ddr2_dev
#else

struct rxi316_dram_info rxi316_ddr2_dev_64MB = {
	DDR_2,
	PAGE_2K,
	BANK_4,
	BST_LEN_8,
	SENQUENTIAL,
	HYBR_256MB,
	DQ_16,
	10  // dram_colu_bits
}; //rxi316_ ddr2_dev

struct rxi316_dram_info rxi316_ddr2_dev = {
	DDR_2,
	PAGE_2K,
	BANK_8,
	BST_LEN_8,
	SENQUENTIAL,
	HYBR_256MB,
	DQ_16,
	10  // dram_colu_bits
}; //rxi316_ ddr2_dev

#endif

struct rxi316_dram_info rxi316_ddr3_dev = {
	DDR_3,
	PAGE_2K,
	BANK_8,
	BST_LEN_8,
	SENQUENTIAL,
	HYBR_256MB,
	DQ_16,
	10  // dram_colu_bits
}; // rxi316_ddr3_dev

struct rxi316_dram_mode_reg_info rxi316_ddr2_mode_reg = {
	6,   // dram_wr_lat  //query - WL, CAS = 7
	7,   // dram_rd_lat  //query -RL, CAS = 7
	0,   // dram_add_lat  //query - AL
	0,   // parity_lat
	8,   // 5 or 6 tphy_wd=(DFI_RATIO == 2)? ((wl+1-AC_SHARE) / DFI_RATIO) : (wl  / DFI_RATIO)  //query - wl, 0629, CAS = 7
	4,   // tphy_rd=(DFI_RATIO == 2)? ((rl+1-AC_SHARE) / DFI_RATIO) : (rl  / DFI_RATIO)  //query - rl, 0629, CAS = 7
	0,   // without write preamble
	0,   // without write pstamble
	0,   // without read pstamble
	0,   // mode reg 0 or value
	0,   // mode reg 1 or value
	0,   // mode reg 2 or value
	0,   // mode reg 3 or value
	0,   // mode reg 4 or value
	0,   // mode reg 5 or value
	0,   // mode reg 6 or value
	0,   // mode reg 11 or value
	0,   // mode reg 12 or value
	0,   // mode reg 13 or value
	0,   // mode reg 14 or value
	0    // mode reg 22 or value
}; // rxi316_ddr2_mode_reg_1066mhz

struct rxi316_dram_mode_reg_info rxi316_ddr3_mode_reg = {
	6,   // dram_wr_lat
	8,  // dram_rd_lat
	0,   // dram_add_lat
	0,   // parity_lat
	8,   // tphy_wd=(DFI_RATIO == 2)? ((wl+1-AC_SHARE) / DFI_RATIO) : (wl  / DFI_RATIO)
	4,  // tphy_rd=(DFI_RATIO == 2)? ((rl+1-AC_SHARE) / DFI_RATIO) : (rl  / DFI_RATIO)
	0,   // without write preamble
	0,   // without write pstamble
	0,   // without read pstamble
	0,   // mode reg 0 or value
	0,   // mode reg 1 or value
	0,   // mode reg 2 or value
	0,   // mode reg 3 or value
	0,   // mode reg 4 or value
	0,   // mode reg 5 or value
	0,   // mode reg 6 or value
	0,   // mode reg 11 or value
	0,   // mode reg 12 or value
	0,   // mode reg 13 or value
	0,   // mode reg 14 or value
	0    // mode reg 22 or value
}; // rxi316_ddr3_mode_reg_1333mhz

struct rxi316_dram_timing_info rxi316_ddr2_timing = {
	105000,     //trfc_ps; //G0102
	1950000,    // trefi_ps, 7800000 if T < 85
	13125,      // trcd_ps; //G0102
	13125,      // trp_ps; //G0102
	45000,      // tras_ps;
	10000,      // trrd_ps;
	15000,      // twr_ps;
	4,          // twtr_tck;  //G0102 - dram_tck
	2,          // tmrd_tck;
	7500,       // trtp_ps;
	2,          // trtp_tck;  //G0102
	2,          // tccd_tck;
	58125,      // trc_ps;  //G0102
	0,          // tccd_s_tck(without tccd_s);
	0,          // twtr_s_tck(without twtr_s);
	0,          // trrd_s_tck(without trrd_s);
	45000,      // tfaw_ps;  //G0102
	11250,       // tcke_ps;  //G0102
	11250,       // txp_ps; //G0102
	325,          // tdqsck_ps;  //G0102
	0,          // tzqcs_tck(without zqc);
	13125,          // trpab_ps(trpab = trppb);  //G0102
	0,          // tppd_tck(without tppd);
	8,          // nWR = 6 (twr_ps/tck_min=15000/1875)  //G0102
	0           // RTP = (((DRAM_BST / 2)-2)/DFI_RATIO) + round_up(TRTP, DRAM_FRQX2)  //G0102 - assigning to 0 as this is calculated inside rxi316_dram_init.c for DDR2 regardless of the value assigned from here
}; // rxi316_ddr2_timing_1066mhz

struct rxi316_dram_timing_info rxi316_ddr3_timing = {  //G0102
	160000,     // trfc_ps;
	1950000,    // trefi_ps; 7800000 if T < 85
	13500,      // trcd_ps; //G0102
	13500,      // trp_ps; //G0102
	36000,      // tras_ps; //G0102
	7500,       // trrd_ps;
	15000,      // twr_ps;
	4,          // twtr_tck; //G0102
	4,         // tmrd_tck; //G0102
	7500,       // trtp_ps;
	4,          // trtp_tck;
	4,          // tccd_tck;
	49500,      // trc_ps; //G0102
	0,          // tccd_s_tck(without tccd_s);
	0,          // twtr_s_tck(without twtr_s);
	0,          // trrd_s_tck(without trrd_s);
	45000,      // tfaw_ps; //G0102
	5625,       // tcke_ps; //G0102
	6000,       // txp_ps;
	255,          // tdqsck_ps; //G0102
	64,         // tzqcs_tck;
	0,          // trpab_ps(trpab = trppb);  //G0102 - not used for DDR2,3
	0,          // tppd_tck;  //G0102 - not used for DDR2,3
	10,         // nWR = 10 (twr_ps/tck_min=15000/1500) //G0102
	0           // RTP = TRTP > (TRTP_TCK*DRAM_FRQ)?round_up(TRTP, DRAM_FRQX2):round_up(TRTP_TCK , DFI_RATIO);  //G0102 - not used for DDR2,3
}; // rxi316_ddr3_timing_1333mhz

#if IS_CUT_TEST(CONFIG_CHIP_VER) || CONFIG_PXP || SIMU_DDR_PXP_INIT_FLOW_EN
struct bus_addr_remap_info ddr2_bus_addr_remap_info = {
	UNREAMP,         // bus_addr[0]
	UNREAMP,         // bus_addr[1]
	UNREAMP,         // bus_addr[2]
	COLU2_REMAP,     // bus_addr[3]
	COLU3_REMAP,     // bus_addr[4]
	COLU4_REMAP,     // bus_addr[5]
	COLU5_REMAP,     // bus_addr[6]
	COLU6_REMAP,     // bus_addr[7]
	COLU7_REMAP,     // bus_addr[8]
	COLU8_REMAP,     // bus_addr[9]
	COLU9_REMAP,     // bus_addr[10]
	BANK0_REMAP,     // bus_addr[11]
	BANK1_REMAP,     // bus_addr[12]
	ROW0_REMAP,      // bus_addr[13]
	ROW1_REMAP,      // bus_addr[14]
	ROW2_REMAP,      // bus_addr[15]
	ROW3_REMAP,      // bus_addr[16]
	ROW4_REMAP,      // bus_addr[17]
	ROW5_REMAP,      // bus_addr[18]
	ROW6_REMAP,      // bus_addr[19]
	ROW7_REMAP,      // bus_addr[20]
	ROW8_REMAP,      // bus_addr[21]
	ROW9_REMAP,      // bus_addr[22]
	ROW10_REMAP,     // bus_addr[23]
	ROW11_REMAP,     // bus_addr[24]
	ROW12_REMAP,     // bus_addr[25]
	UNREAMP,         // bus_addr[26]
	UNREAMP,         // bus_addr[27]
	UNREAMP,         // bus_addr[28]
	UNREAMP,         // bus_addr[29]
	UNREAMP,         // bus_addr[30]
	UNREAMP          // bus_addr[31]
}; //ddr2_dq16_bus_addr_remap_info
#else

struct bus_addr_remap_info ddr2_bus_addr_remap_info_64MB = {
	UNREAMP,         // bus_addr[0]
	UNREAMP,         // bus_addr[1]
	UNREAMP,         // bus_addr[2]
	COLU2_REMAP,     // bus_addr[3]
	COLU3_REMAP,     // bus_addr[4]
	COLU4_REMAP,     // bus_addr[5]
	COLU5_REMAP,     // bus_addr[6]
	COLU6_REMAP,     // bus_addr[7]
	COLU7_REMAP,     // bus_addr[8]
	COLU8_REMAP,     // bus_addr[9]
	COLU9_REMAP,     // bus_addr[10]
	BANK0_REMAP,     // bus_addr[11]
	BANK1_REMAP,     // bus_addr[12]
	ROW0_REMAP,      // bus_addr[13]
	ROW1_REMAP,      // bus_addr[14]
	ROW2_REMAP,      // bus_addr[15]
	ROW3_REMAP,      // bus_addr[16]
	ROW4_REMAP,      // bus_addr[17]
	ROW5_REMAP,      // bus_addr[18]
	ROW6_REMAP,      // bus_addr[19]
	ROW7_REMAP,      // bus_addr[20]
	ROW8_REMAP,      // bus_addr[21]
	ROW9_REMAP,      // bus_addr[22]
	ROW10_REMAP,     // bus_addr[23]
	ROW11_REMAP,     // bus_addr[24]
	ROW12_REMAP,     // bus_addr[25]
	UNREAMP,         // bus_addr[26]
	UNREAMP,         // bus_addr[27]
	UNREAMP,         // bus_addr[28]
	UNREAMP,         // bus_addr[29]
	UNREAMP,         // bus_addr[30]
	UNREAMP          // bus_addr[31]
}; //ddr2_dq16_bus_addr_remap_info

struct bus_addr_remap_info ddr2_bus_addr_remap_info = {
	UNREAMP,         // bus_addr[0]
	UNREAMP,         // bus_addr[1]
	UNREAMP,         // bus_addr[2]
	COLU2_REMAP,     // bus_addr[3]
	COLU3_REMAP,     // bus_addr[4]
	COLU4_REMAP,     // bus_addr[5]
	COLU5_REMAP,     // bus_addr[6]
	COLU6_REMAP,     // bus_addr[7]
	COLU7_REMAP,     // bus_addr[8]
	COLU8_REMAP,     // bus_addr[9]
	COLU9_REMAP,     // bus_addr[10]
	BANK0_REMAP,     // bus_addr[11]
	BANK1_REMAP,     // bus_addr[12]
	BANK2_REMAP,     // bus_addr[13]
	ROW0_REMAP,      // bus_addr[14]
	ROW1_REMAP,      // bus_addr[15]
	ROW2_REMAP,      // bus_addr[16]
	ROW3_REMAP,      // bus_addr[17]
	ROW4_REMAP,      // bus_addr[18]
	ROW5_REMAP,      // bus_addr[19]
	ROW6_REMAP,      // bus_addr[20]
	ROW7_REMAP,      // bus_addr[21]
	ROW8_REMAP,      // bus_addr[22]
	ROW9_REMAP,      // bus_addr[23]
	ROW10_REMAP,     // bus_addr[24]
	ROW11_REMAP,     // bus_addr[25]
	ROW12_REMAP,     // bus_addr[26]
	UNREAMP,         // bus_addr[27]
	UNREAMP,         // bus_addr[28]
	UNREAMP,         // bus_addr[29]
	UNREAMP,         // bus_addr[30]
	UNREAMP          // bus_addr[31]
}; //ddr2_dq16_bus_addr_remap_info
#endif

struct bus_addr_remap_info ddr3_bus_addr_remap_info = {
	UNREAMP,         // bus_addr[0]
	UNREAMP,         // bus_addr[1]
	UNREAMP,         // bus_addr[2]
	COLU2_REMAP,     // bus_addr[3]
	COLU3_REMAP,     // bus_addr[4]
	COLU4_REMAP,     // bus_addr[5]
	COLU5_REMAP,     // bus_addr[6]
	COLU6_REMAP,     // bus_addr[7]
	COLU7_REMAP,     // bus_addr[8]
	COLU8_REMAP,     // bus_addr[9]
	COLU9_REMAP,     // bus_addr[10]
	BANK0_REMAP,     // bus_addr[11]
	BANK1_REMAP,     // bus_addr[12]
	BANK2_REMAP,     // bus_addr[13]
	ROW0_REMAP,      // bus_addr[14]
	ROW1_REMAP,      // bus_addr[15]
	ROW2_REMAP,      // bus_addr[16]
	ROW3_REMAP,      // bus_addr[17]
	ROW4_REMAP,      // bus_addr[18]
	ROW5_REMAP,      // bus_addr[19]
	ROW6_REMAP,      // bus_addr[20]
	ROW7_REMAP,      // bus_addr[21]
	ROW8_REMAP,      // bus_addr[22]
	ROW9_REMAP,      // bus_addr[23]
	ROW10_REMAP,     // bus_addr[24]
	ROW11_REMAP,     // bus_addr[25]
	ROW12_REMAP,     // bus_addr[26]
	UNREAMP,         // bus_addr[27]
	UNREAMP,         // bus_addr[28]
	UNREAMP,         // bus_addr[29]
	UNREAMP,         // bus_addr[30]
	UNREAMP          // bus_addr[31]
}; //ddr3_dq16_bus_addr_remap_info

struct bus_addr_remap_info ddr3_bus_addr_remap_info_256MB = {
	UNREAMP,         // bus_addr[0]
	UNREAMP,         // bus_addr[1]
	UNREAMP,         // bus_addr[2]
	COLU2_REMAP,     // bus_addr[3]
	COLU3_REMAP,     // bus_addr[4]
	COLU4_REMAP,     // bus_addr[5]
	COLU5_REMAP,     // bus_addr[6]
	COLU6_REMAP,     // bus_addr[7]
	COLU7_REMAP,     // bus_addr[8]
	COLU8_REMAP,     // bus_addr[9]
	COLU9_REMAP,     // bus_addr[10]
	BANK0_REMAP,     // bus_addr[11]
	BANK1_REMAP,     // bus_addr[12]
	BANK2_REMAP,     // bus_addr[13]
	ROW0_REMAP,      // bus_addr[14]
	ROW1_REMAP,      // bus_addr[15]
	ROW2_REMAP,      // bus_addr[16]
	ROW3_REMAP,      // bus_addr[17]
	ROW4_REMAP,      // bus_addr[18]
	ROW5_REMAP,      // bus_addr[19]
	ROW6_REMAP,      // bus_addr[20]
	ROW7_REMAP,      // bus_addr[21]
	ROW8_REMAP,      // bus_addr[22]
	ROW9_REMAP,      // bus_addr[23]
	ROW10_REMAP,     // bus_addr[24]
	ROW11_REMAP,     // bus_addr[25]
	ROW12_REMAP,     // bus_addr[26]
	ROW13_REMAP,     // bus_addr[27]
	UNREAMP,         // bus_addr[28]
	UNREAMP,         // bus_addr[29]
	UNREAMP,         // bus_addr[30]
	UNREAMP          // bus_addr[31]
}; //ddr3_dq16_bus_addr_remap_info



struct slot_starve_reg_info slot_starve_info = {
	// cr_slot_park
	0,         // cr_wslot_def  0:read_slot 1:write_slot
	0x10,      // cr_idle_window
	// cr_slot_starve
	0x0,       // cr_lpw_starve
	0x0,       // cr_hpr_starve
	0x5,       // cr_lpr_starve
	0xbf,      // cr_base_starve
	// cr_slot_cntr
	0x08,      // cr_lpw_isu_limit
	0x08,      // cr_hpr_isu_limit
	0x08,      // cr_lpr_isu_limit
	// cr_cbctl0
	8,        //cr_lpr_freeslot_num= ((((`RCMD_BUF_DEPTH)/4)*3) -1)
	0xf,       //cr_lpr_rmw_run_len
	// cr_cbctl1
	1,         //cr_dis_wmg
	1,         //cr_pageopen
	0xf,       //cr_wmg_num_threshold
	0xf,       //cr_lpw_rmw_run_len
	// cr_cbstarve0
	0xFFFFFFFF,     //cr_lpr_max_starve=32'h400
	// cr_cbstarve1
	0xFFFFFFFF,     //cr_hpr_max_starve=32'h400
	// cr_cbstarve2
	0xFFFFFFFF,     //cr_lpw_max_starve=32'h400
	// cr_cbstarve3
	0xFFFFFFFF,     //cr_lpr_rmw_max_starve=32'h400
	// cr_cbstarve4
	0xFFFFFFFF,     //cr_lpw_rmw_max_starve=32'h400
	// cr_bank_sch_ctrl
	0,         //cr_ba_sel_times
	0,         //cr_bg_sel_times
	0          //cr_ra_sel_times
};


struct rxi316_dram_ctrl_info rxi316_ddr2_dramc_info = {
	0x316,      // idr
	// cr_dcr
	0,          // rank2
	0,          // wr_dbi
	0,          // rd_dbi
	0,          // par
	0,          // gear_down
	0,          // bg2
	0,          // bg_remap
	0,          // zqc
	// cr_iocr
	0,          // odt_2pins;
	0,          // cke_nop;
	0,          // stc_cke;  // default 0: dynamic cke for power saving; 1: for performance profile
	0,          // stc_odt;
	0,          // cmd_2t_en; (dfi_ratio=2,cmd_2t_en=1)
	0,          // rtw_2t_dis;
	0,          // half_csn;
	2,          // rd_pipe;
	0,          // dual_ch_en;
	0,          // addr_share_en;
	0,          // ac_share_en;
	// cr_drr
	1,          // ref_num
	0,          // ref_dis
	0,          // zqcl_inv
	// cr_tpr0
	1,          // tpd_en
	// cr_tpr2
	1,          // zqc_inv or init_ref_num for DDR1/DDR2/LPDDR1
	0,          // lpddr2/lpddr3 init mrr

	// cr_wrap_chop_bd
	CR_CHOP_SIZE_64B, // chop_size

	// cr_addr_remap
	&ddr2_bus_addr_remap_info,
	//&ddr3_dq32_bus_addr_remap_info,

	// cr_performance tuning
	&slot_starve_info
}; // rxi316_ddr3_dramc_info

struct rxi316_dram_ctrl_info rxi316_ddr3_dramc_info = {
	0x316,      // idr
	// cr_dcr
	0,          // rank2
	0,          // wr_dbi
	0,          // rd_dbi
	0,          // par
	0,          // gear_down
	0,          // bg2
	0,          // bg_remap
	0,          // zqc
	// cr_iocr
	0,          // odt_2pins;
	0,          // cke_nop;
	0,          // stc_cke;  // default 0: dynamic cke for power saving; 1: for performance profile
	0,          // stc_odt;
	1,          // cmd_2t_en; (dfi_ratio=2,cmd_2t_en=1)
	0,          // rtw_2t_dis;
	0,          // half_csn;
	2,          // rd_pipe;
	0,          // dual_ch_en;
	0,          // addr_share_en;
	0,          // ac_share_en;
	// cr_drr
	1,          // ref_num
	0,          // ref_dis
	0,          // zqcl_inv
	// cr_tpr0
	1,          // tpd_en
	// cr_tpr2
	1,          // zqc_inv or init_ref_num for DDR1/DDR2/LPDDR1
	0,          // lpddr2/lpddr3 init mrr

	// cr_wrap_chop_bd
	CR_CHOP_SIZE_64B, // chop_size

	// cr_addr_remap
	&ddr3_bus_addr_remap_info,
	//&ddr3_dq32_bus_addr_remap_info,

	// cr_performance tuning
	&slot_starve_info
}; // rxi316_ddr3_dramc_info


struct rxi316_dram_device_info rxi316_ddr2_info_m = {
	//=== DRAM Device ===//
	&rxi316_ddr2_dev,

	//=== DRAM Mode Registers ===//
	&rxi316_ddr2_mode_reg,      // DDR2-1066

	//=== DRAM Timing Parameters ===//
	&rxi316_ddr2_timing,        // DDR2-1066

	//=== DRAMC Info ===//
	//default bus_addr_remap_info is DQ16, changed to DQ32 if needed
	&rxi316_ddr2_dramc_info,

	//=== DRAM Clock Period(ps) ===//
	1000000 / 533,              // DDR-1066: 1876ps

	//DFI_RATIO_1                 //DFI_RATIO_1
	DFI_RATIO_2                 //DFI_RATIO_2
};

struct rxi316_dram_device_info rxi316_ddr3_info_m = {
	//=== DRAM Device ===//
	&rxi316_ddr3_dev,

	//=== DRAM Mode Registers ===//
	&rxi316_ddr3_mode_reg,      // DDR2-1066

	//=== DRAM Timing Parameters ===//
	&rxi316_ddr3_timing,        // DDR2-1066

	//=== DRAMC Info ===//
	//default bus_addr_remap_info is DQ16, changed to DQ32 if needed
	&rxi316_ddr3_dramc_info,

	//=== DRAM Clock Period(ps) ===//
	1000000 / 667,              // DDR-1333: 1500ps

	//DFI_RATIO_1                 //DFI_RATIO_1
	DFI_RATIO_2                 //DFI_RATIO_2
};

u32 ddr3_new_process;

void hal_dramc_ftend_init(DRAM_FE_TypeDef *dram_ft_dev)
{
	// port 0 enable
	dram_ft_dev->pn_portctrl_0 = 0;
	// port 1 enable
	dram_ft_dev->pn_portctrl_1 = 0;
	// port 2 enable
	dram_ft_dev->pn_portctrl_2 = 0;
	// port 3 enable
	dram_ft_dev->pn_portctrl_3 = 0;
	// port 4 enable
	dram_ft_dev->pn_portctrl_4 = 0;
	// port 5 enable
	dram_ft_dev->pn_portctrl_5 = 0;

	//Maximum number of free slots reserved for LP read commands in channel 0.
	dram_ft_dev->cm_fe_rrb_0 = 0x8;

	dram_ft_dev->pn_rqos_0 = 0x2100a09;
	dram_ft_dev->pn_wqos_0 = 0x2100a09;
	dram_ft_dev->pn_rqos_1 = 0x2100a09;
	dram_ft_dev->pn_wqos_1 = 0x2100a09;
	dram_ft_dev->pn_rqos_2 = 0x2100a09;
	dram_ft_dev->pn_wqos_2 = 0x2100a09;
	dram_ft_dev->pn_rqos_3 = 0x2100a09;
	dram_ft_dev->pn_wqos_3 = 0x2100a09;
	dram_ft_dev->pn_rqos_4 = 0x2100a09;
	dram_ft_dev->pn_wqos_4 = 0x2100a09;
	dram_ft_dev->pn_rqos_5 = 0x2100a09;
	dram_ft_dev->pn_wqos_5 = 0x2100a09;

	HAL_WRITE32(0x40004000, 0x414, 0xFFF0FF);//RXI3100 Read QoS,
	HAL_WRITE32(0x40004000, 0x418, 0xFFF0FF);//RXI3100 Write QoS,

}

void hal_dramc_perf_tune(DRAMC_TypeDef *dramc_dev, struct rxi316_dram_device_info *rxi316_dram_info)
{
	uint32_t colu_bfo = 2;
	uint32_t bank_bfo = 2;
	uint32_t row_bfo  = 5;
	uint32_t rank_bfo = 2;
	uint32_t bg_bfo   = 2;
	uint32_t ch_bfo   = 2;
	uint32_t dq_bfo;

	uint32_t bus_addr[32];
	int      i;

	int      colu_remap_bits;
	int      bank_remap_bits; // bank+rank+bg
	int      dram_colu_bits;
	int      dram_bank_bits;  // bank+rank+bg

	uint32_t axi_row0_remap, axi_row1_remap, axi_row2_remap, axi_row3_remap, axi_row4_remap, axi_row5_remap, axi_row6_remap, axi_row7_remap;
	uint32_t axi_row8_remap, axi_row9_remap, axi_row10_remap, axi_row11_remap, axi_row12_remap, axi_row13_remap, axi_row14_remap, axi_row15_remap;
	uint32_t axi_row16_remap;
	uint32_t axi_bank0_remap, axi_bank1_remap, axi_bank2_remap;
	uint32_t axi_colu2_remap, axi_colu3_remap, axi_colu4_remap, axi_colu5_remap, axi_colu6_remap, axi_colu7_remap, axi_colu8_remap, axi_colu9_remap;
	uint32_t axi_colu10_remap, axi_colu11_remap;
	uint32_t axi_rank_remap;
	uint32_t axi_ch_remap;
	uint32_t axi_bg0_remap, axi_bg1_remap;

	uint32_t cr_row0_remap, cr_row1_remap, cr_row2_remap, cr_row3_remap, cr_row4_remap, cr_row5_remap, cr_row6_remap, cr_row7_remap;
	uint32_t cr_row8_remap, cr_row9_remap, cr_row10_remap, cr_row11_remap, cr_row12_remap, cr_row13_remap, cr_row14_remap, cr_row15_remap;
	uint32_t cr_row16_remap;
	uint32_t cr_bank0_remap, cr_bank1_remap, cr_bank2_remap;
	uint32_t cr_colu2_remap, cr_colu3_remap, cr_colu4_remap, cr_colu5_remap, cr_colu6_remap, cr_colu7_remap, cr_colu8_remap, cr_colu9_remap;
	uint32_t cr_colu10_remap, cr_colu11_remap;
	uint32_t cr_rank_remap;
	uint32_t cr_ch_remap;
	uint32_t cr_bg0_remap, cr_bg1_remap;

	if (rxi316_dram_info->dev->dq_width == DQ_32) {
		dq_bfo = 2;
	} else if (rxi316_dram_info->dev->dq_width == DQ_16) {
		dq_bfo = 1;
	} else if (rxi316_dram_info->dev->dq_width == DQ_8) {
		dq_bfo = 0;
	} else { // DQ_48
		dq_bfo = 2;
	}

	bus_addr[0 ]  = rxi316_dram_info->dramc_info->bus_addr_bit->bus_addr_0 ;
	bus_addr[1 ]  = rxi316_dram_info->dramc_info->bus_addr_bit->bus_addr_1 ;
	bus_addr[2 ]  = rxi316_dram_info->dramc_info->bus_addr_bit->bus_addr_2 ;
	bus_addr[3 ]  = rxi316_dram_info->dramc_info->bus_addr_bit->bus_addr_3 ;
	bus_addr[4 ]  = rxi316_dram_info->dramc_info->bus_addr_bit->bus_addr_4 ;
	bus_addr[5 ]  = rxi316_dram_info->dramc_info->bus_addr_bit->bus_addr_5 ;
	bus_addr[6 ]  = rxi316_dram_info->dramc_info->bus_addr_bit->bus_addr_6 ;
	bus_addr[7 ]  = rxi316_dram_info->dramc_info->bus_addr_bit->bus_addr_7 ;
	bus_addr[8 ]  = rxi316_dram_info->dramc_info->bus_addr_bit->bus_addr_8 ;
	bus_addr[9 ]  = rxi316_dram_info->dramc_info->bus_addr_bit->bus_addr_9 ;
	bus_addr[10]  = rxi316_dram_info->dramc_info->bus_addr_bit->bus_addr_10;
	bus_addr[11]  = rxi316_dram_info->dramc_info->bus_addr_bit->bus_addr_11;
	bus_addr[12]  = rxi316_dram_info->dramc_info->bus_addr_bit->bus_addr_12;
	bus_addr[13]  = rxi316_dram_info->dramc_info->bus_addr_bit->bus_addr_13;
	bus_addr[14]  = rxi316_dram_info->dramc_info->bus_addr_bit->bus_addr_14;
	bus_addr[15]  = rxi316_dram_info->dramc_info->bus_addr_bit->bus_addr_15;
	bus_addr[16]  = rxi316_dram_info->dramc_info->bus_addr_bit->bus_addr_16;
	bus_addr[17]  = rxi316_dram_info->dramc_info->bus_addr_bit->bus_addr_17;
	bus_addr[18]  = rxi316_dram_info->dramc_info->bus_addr_bit->bus_addr_18;
	bus_addr[19]  = rxi316_dram_info->dramc_info->bus_addr_bit->bus_addr_19;
	bus_addr[20]  = rxi316_dram_info->dramc_info->bus_addr_bit->bus_addr_20;
	bus_addr[21]  = rxi316_dram_info->dramc_info->bus_addr_bit->bus_addr_21;
	bus_addr[22]  = rxi316_dram_info->dramc_info->bus_addr_bit->bus_addr_22;
	bus_addr[23]  = rxi316_dram_info->dramc_info->bus_addr_bit->bus_addr_23;
	bus_addr[24]  = rxi316_dram_info->dramc_info->bus_addr_bit->bus_addr_24;
	bus_addr[25]  = rxi316_dram_info->dramc_info->bus_addr_bit->bus_addr_25;
	bus_addr[26]  = rxi316_dram_info->dramc_info->bus_addr_bit->bus_addr_26;
	bus_addr[27]  = rxi316_dram_info->dramc_info->bus_addr_bit->bus_addr_27;
	bus_addr[28]  = rxi316_dram_info->dramc_info->bus_addr_bit->bus_addr_28;
	bus_addr[29]  = rxi316_dram_info->dramc_info->bus_addr_bit->bus_addr_29;
	bus_addr[30]  = rxi316_dram_info->dramc_info->bus_addr_bit->bus_addr_30;
	bus_addr[31]  = rxi316_dram_info->dramc_info->bus_addr_bit->bus_addr_31;

	// initial valu 32: unremap to bus_addr[31:0]
	axi_row0_remap   = axi_row1_remap   = axi_row2_remap  = axi_row3_remap  =
			axi_row4_remap   = axi_row5_remap   = axi_row6_remap  = axi_row7_remap  =
								   axi_row8_remap   = axi_row9_remap   = axi_row10_remap = axi_row11_remap =
										   axi_row12_remap  = axi_row13_remap  = axi_row14_remap = axi_row15_remap =
												   axi_row16_remap  = 32;
	axi_bank0_remap  = axi_bank1_remap  = axi_bank2_remap = 32;
	axi_colu2_remap  = axi_colu3_remap  = axi_colu4_remap = axi_colu5_remap =
			axi_colu6_remap  = axi_colu7_remap  = axi_colu8_remap = axi_colu9_remap =
								   axi_colu10_remap = axi_colu11_remap = 32;
	axi_rank_remap   = 32;
	axi_ch_remap     = 32;
	axi_bg0_remap    = 32;
	axi_bg1_remap    = 32;

	colu_remap_bits = 0;
	bank_remap_bits = 0; // bank+rank+bg
	dram_colu_bits  = 0;
	dram_bank_bits  = 0; // bank+rank+bg

	// decode row/bank/colu/rank/bg/ch remap to bus_addr[n]
	for (i = 0; i < 32; i++) {
		if (bus_addr[i] == 0) {
			axi_colu2_remap = i;
			colu_remap_bits = colu_remap_bits + 1;
		} else if (bus_addr[i] == 1) {
			axi_colu3_remap = i;
			colu_remap_bits = colu_remap_bits + 1;
		} else if (bus_addr[i] == 2) {
			axi_colu4_remap = i;
			colu_remap_bits = colu_remap_bits + 1;
		} else if (bus_addr[i] == 3) {
			axi_colu5_remap = i;
			colu_remap_bits = colu_remap_bits + 1;
		} else if (bus_addr[i] == 4) {
			axi_colu6_remap = i;
			colu_remap_bits = colu_remap_bits + 1;
		} else if (bus_addr[i] == 5) {
			axi_colu7_remap = i;
			colu_remap_bits = colu_remap_bits + 1;
		} else if (bus_addr[i] == 6) {
			axi_colu8_remap = i;
			colu_remap_bits = colu_remap_bits + 1;
		} else if (bus_addr[i] == 7) {
			axi_colu9_remap = i;
			colu_remap_bits = colu_remap_bits + 1;
		} else if (bus_addr[i] == 8) {
			axi_colu10_remap = i;
			colu_remap_bits  = colu_remap_bits + 1;
		} else if (bus_addr[i] == 9) {
			axi_colu11_remap = i;
			colu_remap_bits  = colu_remap_bits + 1;
		} else if (bus_addr[i] == 10) {
			axi_bank0_remap = i;
			bank_remap_bits = bank_remap_bits + 1;
		} else if (bus_addr[i] == 11) {
			axi_bank1_remap = i;
			bank_remap_bits = bank_remap_bits + 1;
		} else if (bus_addr[i] == 12) {
			axi_bank2_remap = i;
			bank_remap_bits = bank_remap_bits + 1;
		} else if (bus_addr[i] == 13) {
			axi_bg0_remap = i;
			bank_remap_bits = bank_remap_bits + 1;
		} else if (bus_addr[i] == 14) {
			axi_bg1_remap = i;
			bank_remap_bits = bank_remap_bits + 1;
		} else if (bus_addr[i] == 15) {
			axi_rank_remap = i;
			bank_remap_bits = bank_remap_bits + 1;
		} else if (bus_addr[i] == 16) {
			axi_row0_remap = i;
		} else if (bus_addr[i] == 17) {
			axi_row1_remap = i;
		} else if (bus_addr[i] == 18) {
			axi_row2_remap = i;
		} else if (bus_addr[i] == 19) {
			axi_row3_remap = i;
		} else if (bus_addr[i] == 20) {
			axi_row4_remap = i;
		} else if (bus_addr[i] == 21) {
			axi_row5_remap = i;
		} else if (bus_addr[i] == 22) {
			axi_row6_remap = i;
		} else if (bus_addr[i] == 23) {
			axi_row7_remap = i;
		} else if (bus_addr[i] == 24) {
			axi_row8_remap = i;
		} else if (bus_addr[i] == 25) {
			axi_row9_remap = i;
		} else if (bus_addr[i] == 26) {
			axi_row10_remap = i;
		} else if (bus_addr[i] == 27) {
			axi_row11_remap = i;
		} else if (bus_addr[i] == 28) {
			axi_row12_remap = i;
		} else if (bus_addr[i] == 29) {
			axi_row13_remap = i;
		} else if (bus_addr[i] == 30) {
			axi_row14_remap = i;
		} else if (bus_addr[i] == 31) {
			axi_row15_remap = i;
		}
	}

	dram_colu_bits = rxi316_dram_info->dev->dram_colu_bits;
	if (rxi316_dram_info->dev->bank == BANK_2) {
		dram_bank_bits = 1;
	} else if (rxi316_dram_info->dev->bank == BANK_4) {
		dram_bank_bits = 2;
	} else if (rxi316_dram_info->dev->bank == BANK_8) {
		dram_bank_bits = 3;
	} else if (rxi316_dram_info->dev->bank == BANK_16) {
		dram_bank_bits = 4;
	} else {
		dram_bank_bits = 3;
	}

	if (colu_remap_bits != (dram_colu_bits - 2)) {
		DBG_DRAM_INFO("> [ADDR REMAP ERROR]: colu_remap_bits != dram_colu_bits!!!\r\n");
	}
	if (bank_remap_bits != dram_bank_bits) {
		DBG_DRAM_INFO("> [ADDR REMAP ERROR]: bank_remap_bits != dram_bank_bits!!!\r\n");
	}

	// decode cr_reg value
	cr_row0_remap   = (axi_row0_remap   != 32) ? (axi_row0_remap   - row_bfo  - dq_bfo - 0) : 15;
	cr_row1_remap   = (axi_row1_remap   != 32) ? (axi_row1_remap   - row_bfo  - dq_bfo - 1) : 15;
	cr_row2_remap   = (axi_row2_remap   != 32) ? (axi_row2_remap   - row_bfo  - dq_bfo - 2) : 15;
	cr_row3_remap   = (axi_row3_remap   != 32) ? (axi_row3_remap   - row_bfo  - dq_bfo - 3) : 15;
	cr_row4_remap   = (axi_row4_remap   != 32) ? (axi_row4_remap   - row_bfo  - dq_bfo - 4) : 15;
	cr_row5_remap   = (axi_row5_remap   != 32) ? (axi_row5_remap   - row_bfo  - dq_bfo - 5) : 15;
	cr_row6_remap   = (axi_row6_remap   != 32) ? (axi_row6_remap   - row_bfo  - dq_bfo - 6) : 15;
	cr_row7_remap   = (axi_row7_remap   != 32) ? (axi_row7_remap   - row_bfo  - dq_bfo - 7) : 15;
	cr_row8_remap   = (axi_row8_remap   != 32) ? (axi_row8_remap   - row_bfo  - dq_bfo - 8) : 15;
	cr_row9_remap   = (axi_row9_remap   != 32) ? (axi_row9_remap   - row_bfo  - dq_bfo - 9) : 15;
	cr_row10_remap  = (axi_row10_remap  != 32) ? (axi_row10_remap  - row_bfo  - dq_bfo - 10) : 15;
	cr_row11_remap  = (axi_row11_remap  != 32) ? (axi_row11_remap  - row_bfo  - dq_bfo - 11) : 15;
	cr_row12_remap  = (axi_row12_remap  != 32) ? (axi_row12_remap  - row_bfo  - dq_bfo - 12) : 15;
	cr_row13_remap  = (axi_row13_remap  != 32) ? (axi_row13_remap  - row_bfo  - dq_bfo - 13) : 15;
	cr_row14_remap  = (axi_row14_remap  != 32) ? (axi_row14_remap  - row_bfo  - dq_bfo - 14) : 15;
	cr_row15_remap  = (axi_row15_remap  != 32) ? (axi_row15_remap  - row_bfo  - dq_bfo - 15) : 15;
	cr_row16_remap  = (axi_row16_remap  != 32) ? (axi_row16_remap  - row_bfo  - dq_bfo - 16) : 15;

	cr_bank0_remap  = (axi_bank0_remap  != 32) ? (axi_bank0_remap  - bank_bfo - dq_bfo) : 31;
	cr_bank1_remap  = (axi_bank1_remap  != 32) ? (axi_bank1_remap  - bank_bfo - dq_bfo) : 31;
	cr_bank2_remap  = (axi_bank2_remap  != 32) ? (axi_bank2_remap  - bank_bfo - dq_bfo) : 31;

	cr_colu2_remap  = (axi_colu2_remap  != 32) ? (axi_colu2_remap  - colu_bfo - dq_bfo - 0) : 15;
	cr_colu3_remap  = (axi_colu3_remap  != 32) ? (axi_colu3_remap  - colu_bfo - dq_bfo - 1) : 15;
	cr_colu4_remap  = (axi_colu4_remap  != 32) ? (axi_colu4_remap  - colu_bfo - dq_bfo - 2) : 15;
	cr_colu5_remap  = (axi_colu5_remap  != 32) ? (axi_colu5_remap  - colu_bfo - dq_bfo - 3) : 15;
	cr_colu6_remap  = (axi_colu6_remap  != 32) ? (axi_colu6_remap  - colu_bfo - dq_bfo - 4) : 15;
	cr_colu7_remap  = (axi_colu7_remap  != 32) ? (axi_colu7_remap  - colu_bfo - dq_bfo - 5) : 15;
	cr_colu8_remap  = (axi_colu8_remap  != 32) ? (axi_colu8_remap  - colu_bfo - dq_bfo - 6) : 15;
	cr_colu9_remap  = (axi_colu9_remap  != 32) ? (axi_colu9_remap  - colu_bfo - dq_bfo - 7) : 15;
	cr_colu10_remap = (axi_colu10_remap != 32) ? (axi_colu10_remap - colu_bfo - dq_bfo - 8) : 15;
	cr_colu11_remap = (axi_colu11_remap != 32) ? (axi_colu11_remap - colu_bfo - dq_bfo - 9) : 15;

	cr_rank_remap   = (axi_rank_remap   != 32) ? (axi_rank_remap   - rank_bfo - dq_bfo) : 31;
	cr_ch_remap     = (axi_ch_remap     != 32) ? (axi_ch_remap     - ch_bfo   - dq_bfo) : 31;
	cr_bg0_remap    = (axi_bg0_remap    != 32) ? (axi_bg0_remap    - bg_bfo   - dq_bfo) : 31;
	cr_bg1_remap    = (axi_bg1_remap    != 32) ? (axi_bg1_remap    - bg_bfo   - dq_bfo) : 31;

	// ---->cr_row_remap0 setting
	dramc_dev->row_remap0 = (
								(cr_row0_remap  << ADDR_ROW0_REMAP_BFO) |
								(cr_row1_remap  << ADDR_ROW1_REMAP_BFO) |
								(cr_row2_remap  << ADDR_ROW2_REMAP_BFO) |
								(cr_row3_remap  << ADDR_ROW3_REMAP_BFO) |
								(cr_row4_remap  << ADDR_ROW4_REMAP_BFO) |
								(cr_row5_remap  << ADDR_ROW5_REMAP_BFO) |
								(cr_row6_remap  << ADDR_ROW6_REMAP_BFO) |
								(cr_row7_remap  << ADDR_ROW7_REMAP_BFO)
							);

	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("RXI316_BE_CR_00000400_INIT_VAL = 0x%08x\r\n", dramc_dev->row_remap0);
	DBG_DRAM_INFO("CR_ROW_REMAP0                  = 0x%08x\r\n", dramc_dev->row_remap0);
	DBG_DRAM_INFO("> cr_row0_remap                = 0x%x\r\n",   cr_row0_remap);
	DBG_DRAM_INFO("> cr_row1_remap                = 0x%x\r\n",   cr_row1_remap);
	DBG_DRAM_INFO("> cr_row2_remap                = 0x%x\r\n",   cr_row2_remap);
	DBG_DRAM_INFO("> cr_row3_remap                = 0x%x\r\n",   cr_row3_remap);
	DBG_DRAM_INFO("> cr_row4_remap                = 0x%x\r\n",   cr_row4_remap);
	DBG_DRAM_INFO("> cr_row5_remap                = 0x%x\r\n",   cr_row5_remap);
	DBG_DRAM_INFO("> cr_row6_remap                = 0x%x\r\n",   cr_row6_remap);
	DBG_DRAM_INFO("> cr_row7_remap                = 0x%x\r\n",   cr_row7_remap);

	// ---->cr_row_remap1 setting
	dramc_dev->row_remap1 = (
								(cr_row8_remap  << ADDR_ROW8_REMAP_BFO) |
								(cr_row9_remap  << ADDR_ROW9_REMAP_BFO) |
								(cr_row10_remap << ADDR_ROW10_REMAP_BFO) |
								(cr_row11_remap << ADDR_ROW11_REMAP_BFO) |
								(cr_row12_remap << ADDR_ROW12_REMAP_BFO) |
								(cr_row13_remap << ADDR_ROW13_REMAP_BFO) |
								(cr_row14_remap << ADDR_ROW14_REMAP_BFO) |
								(cr_row15_remap << ADDR_ROW15_REMAP_BFO)
							);

	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("RXI316_BE_CR_00000404_INIT_VAL = 0x%08x\r\n", dramc_dev->row_remap1);
	DBG_DRAM_INFO("CR_ROW_REMAP1                  = 0x%08x\r\n", dramc_dev->row_remap1);
	DBG_DRAM_INFO("> cr_row8_remap                = 0x%x\r\n",   cr_row8_remap);
	DBG_DRAM_INFO("> cr_row9_remap                = 0x%x\r\n",   cr_row9_remap);
	DBG_DRAM_INFO("> cr_row10_remap               = 0x%x\r\n",   cr_row10_remap);
	DBG_DRAM_INFO("> cr_row11_remap               = 0x%x\r\n",   cr_row11_remap);
	DBG_DRAM_INFO("> cr_row12_remap               = 0x%x\r\n",   cr_row12_remap);
	DBG_DRAM_INFO("> cr_row13_remap               = 0x%x\r\n",   cr_row13_remap);
	DBG_DRAM_INFO("> cr_row14_remap               = 0x%x\r\n",   cr_row14_remap);
	DBG_DRAM_INFO("> cr_row15_remap               = 0x%x\r\n",   cr_row15_remap);

	// ---->cr_row_remap2 setting
	dramc_dev->row_remap2 = (cr_row16_remap << ADDR_ROW16_REMAP_BFO);

	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("RXI316_BE_CR_00000408_INIT_VAL = 0x%08x\r\n", dramc_dev->row_remap2);
	DBG_DRAM_INFO("CR_ROW_REMAP2                  = 0x%08x\r\n", dramc_dev->row_remap2);
	DBG_DRAM_INFO("> cr_row16_remap               = 0x%x\r\n",   cr_row16_remap);

	// ---->cr_bank_remap0 setting
	dramc_dev->bank_remap0 = (
								 (cr_bank0_remap  << ADDR_BANK0_REMAP_BFO) |
								 (cr_bank1_remap  << ADDR_BANK1_REMAP_BFO) |
								 (cr_bank2_remap  << ADDR_BANK2_REMAP_BFO)
							 );

	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("RXI316_BE_CR_0000040C_INIT_VAL = 0x%08x\r\n", dramc_dev->bank_remap0);
	DBG_DRAM_INFO("CR_BANK_REMAP0                 = 0x%08x\r\n", dramc_dev->bank_remap0);
	DBG_DRAM_INFO("> cr_bank0_remap               = 0x%x\r\n",   cr_bank0_remap);
	DBG_DRAM_INFO("> cr_bank1_remap               = 0x%x\r\n",   cr_bank1_remap);
	DBG_DRAM_INFO("> cr_bank2_remap               = 0x%x\r\n",   cr_bank2_remap);

	// ---->cr_colu_remap0 setting
	dramc_dev->colu_remap0 = (
								 (cr_colu2_remap  << ADDR_COLU2_REMAP_BFO) |
								 (cr_colu3_remap  << ADDR_COLU3_REMAP_BFO) |
								 (cr_colu4_remap  << ADDR_COLU4_REMAP_BFO) |
								 (cr_colu5_remap  << ADDR_COLU5_REMAP_BFO) |
								 (cr_colu6_remap  << ADDR_COLU6_REMAP_BFO) |
								 (cr_colu7_remap  << ADDR_COLU7_REMAP_BFO) |
								 (cr_colu8_remap  << ADDR_COLU8_REMAP_BFO) |
								 (cr_colu9_remap  << ADDR_COLU9_REMAP_BFO)
							 );

	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("RXI316_BE_CR_00000410_INIT_VAL = 0x%08x\r\n", dramc_dev->colu_remap0);
	DBG_DRAM_INFO("CR_COLU_REMAP0                 = 0x%08x\r\n", dramc_dev->colu_remap0);
	DBG_DRAM_INFO("> cr_colu2_remap               = 0x%x\r\n",   cr_colu2_remap);
	DBG_DRAM_INFO("> cr_colu3_remap               = 0x%x\r\n",   cr_colu3_remap);
	DBG_DRAM_INFO("> cr_colu4_remap               = 0x%x\r\n",   cr_colu4_remap);
	DBG_DRAM_INFO("> cr_colu5_remap               = 0x%x\r\n",   cr_colu5_remap);
	DBG_DRAM_INFO("> cr_colu6_remap               = 0x%x\r\n",   cr_colu6_remap);
	DBG_DRAM_INFO("> cr_colu7_remap               = 0x%x\r\n",   cr_colu7_remap);
	DBG_DRAM_INFO("> cr_colu8_remap               = 0x%x\r\n",   cr_colu8_remap);
	DBG_DRAM_INFO("> cr_colu9_remap               = 0x%x\r\n",   cr_colu9_remap);

	// ---->cr_colu_remap1 setting
	dramc_dev->colu_remap1 = (
								 (cr_colu10_remap  << ADDR_COLU10_REMAP_BFO) |
								 (cr_colu11_remap  << ADDR_COLU11_REMAP_BFO)
							 );

	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("RXI316_BE_CR_00000414_INIT_VAL = 0x%08x\r\n", dramc_dev->colu_remap1);
	DBG_DRAM_INFO("CR_COLU_REMAP1                 = 0x%08x\r\n", dramc_dev->colu_remap1);
	DBG_DRAM_INFO("> cr_colu10_remap              = 0x%x\r\n",   cr_colu10_remap);
	DBG_DRAM_INFO("> cr_colu11_remap              = 0x%x\r\n",   cr_colu11_remap);

	// ---->cr_rank_remap0 setting
	dramc_dev->rank_remap0 = (cr_rank_remap  << ADDR_RANK_REMAP_BFO);

	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("RXI316_BE_CR_00000418_INIT_VAL = 0x%08x\r\n", dramc_dev->rank_remap0);
	DBG_DRAM_INFO("CR_RANK_REMAP0                 = 0x%08x\r\n", dramc_dev->rank_remap0);
	DBG_DRAM_INFO("> cr_rank_remap                = 0x%x\r\n",   cr_rank_remap);

	// ---->cr_ch_remap0 setting
	dramc_dev->ch_remap0   = (cr_ch_remap  << ADDR_CH_REMAP_BFO);

	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("RXI316_BE_CR_0000041C_INIT_VAL = 0x%08x\r\n", dramc_dev->ch_remap0);
	DBG_DRAM_INFO("CR_CH_REMAP0                   = 0x%08x\r\n", dramc_dev->ch_remap0);
	DBG_DRAM_INFO("> cr_ch_remap                  = 0x%x\r\n",   cr_ch_remap);

	// ---->cr_bg_remap0 setting
	dramc_dev->bg_remap0 = (
							   (cr_bg0_remap  << ADDR_BG0_REMAP_BFO) |
							   (cr_bg1_remap  << ADDR_BG1_REMAP_BFO)
						   );

	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("RXI316_BE_CR_00000420_INIT_VAL = 0x%08x\r\n", dramc_dev->bg_remap0);
	DBG_DRAM_INFO("CR_BG_REMAP0                   = 0x%08x\r\n", dramc_dev->bg_remap0);
	DBG_DRAM_INFO("> cr_bg0_remap                 = 0x%x\r\n",   cr_bg0_remap);
	DBG_DRAM_INFO("> cr_bg1_remap                 = 0x%x\r\n",   cr_bg1_remap);

	// ---->cr_slot_park setting
	dramc_dev->slot_park = (
							   (rxi316_dram_info->dramc_info->slot_starve_reg->cr_wslot_def   << SLOT_PERF_PARK_BFO) |
							   (rxi316_dram_info->dramc_info->slot_starve_reg->cr_idle_window << SLOT_IDLE_WINDOW_BFO)
						   );

	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("RXI316_BE_CR_00000460_INIT_VAL = 0x%08x\r\n", dramc_dev->slot_park);
	DBG_DRAM_INFO("CR_SLOT_PARK                   = 0x%08x\r\n", dramc_dev->slot_park);
	DBG_DRAM_INFO("> WSLOT_DEF                    = 0x%x\r\n",   rxi316_dram_info->dramc_info->slot_starve_reg->cr_wslot_def);
	DBG_DRAM_INFO("> IDLE_WINDOW                  = 0x%x\r\n",   rxi316_dram_info->dramc_info->slot_starve_reg->cr_idle_window);

	// ---->cr_slot_starve setting
	dramc_dev->slot_starve = (
								 (rxi316_dram_info->dramc_info->slot_starve_reg->cr_lpw_starve  << SLOT_LPW_STARVE_CYC_BFO) |
								 (rxi316_dram_info->dramc_info->slot_starve_reg->cr_hpr_starve  << SLOT_HPR_STARVE_CYC_BFO) |
								 (rxi316_dram_info->dramc_info->slot_starve_reg->cr_lpr_starve  << SLOT_LPR_STARVE_CYC_BFO) |
								 (rxi316_dram_info->dramc_info->slot_starve_reg->cr_base_starve << SLOT_BASE_STARVE_CYC_BFO)
							 );

	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("RXI316_BE_CR_00000464_INIT_VAL = 0x%08x\r\n", dramc_dev->slot_starve);
	DBG_DRAM_INFO("CR_SLOT_STARVE                 = 0x%08x\r\n", dramc_dev->slot_starve);
	DBG_DRAM_INFO("> LPW_STARVE                   = 0x%x\r\n",   rxi316_dram_info->dramc_info->slot_starve_reg->cr_lpw_starve);
	DBG_DRAM_INFO("> HPR_STARVE                   = 0x%x\r\n",   rxi316_dram_info->dramc_info->slot_starve_reg->cr_hpr_starve);
	DBG_DRAM_INFO("> LPR_STARVE                   = 0x%x\r\n",   rxi316_dram_info->dramc_info->slot_starve_reg->cr_lpr_starve);
	DBG_DRAM_INFO("> BASE_STARVE                  = 0x%x\r\n",   rxi316_dram_info->dramc_info->slot_starve_reg->cr_base_starve);

	// ---->cr_slot_cntr setting
	dramc_dev->slot_cntr = (
							   (rxi316_dram_info->dramc_info->slot_starve_reg->cr_lpw_isu_limit << SLOT_LPW_IUS_LMT_BFO) |
							   (rxi316_dram_info->dramc_info->slot_starve_reg->cr_hpr_isu_limit << SLOT_HPR_IUS_LMT_BFO) |
							   (rxi316_dram_info->dramc_info->slot_starve_reg->cr_lpr_isu_limit << SLOT_LPR_IUS_LMT_BFO)
						   );

	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("RXI316_BE_CR_00000468_INIT_VAL = 0x%08x\r\n", dramc_dev->slot_cntr);
	DBG_DRAM_INFO("CR_SLOT_CNTR                   = 0x%08x\r\n", dramc_dev->slot_cntr);
	DBG_DRAM_INFO("> LPW_ISU_LMT                  = 0x%x\r\n",   rxi316_dram_info->dramc_info->slot_starve_reg->cr_lpw_isu_limit);
	DBG_DRAM_INFO("> HPR_ISU_LMT                  = 0x%x\r\n",   rxi316_dram_info->dramc_info->slot_starve_reg->cr_hpr_isu_limit);
	DBG_DRAM_INFO("> LPR_ISU_LMT                  = 0x%x\r\n",   rxi316_dram_info->dramc_info->slot_starve_reg->cr_lpr_isu_limit);

	// ---->cr_cbctl0 setting
	dramc_dev->cbctl0 = (
							(rxi316_dram_info->dramc_info->slot_starve_reg->cr_lpr_freeslot_num << CBCTL0_LPR_FREESLOT_NUM_BFO) |
							(rxi316_dram_info->dramc_info->slot_starve_reg->cr_lpr_rmw_run_len  << CBCTL0_LPR_RMW_RUN_LEN_BFO)
						);

	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("RXI316_BE_CR_00000480_INIT_VAL = 0x%08x\r\n", dramc_dev->cbctl0);
	DBG_DRAM_INFO("CR_CBCTL0                      = 0x%08x\r\n", dramc_dev->cbctl0);
	DBG_DRAM_INFO("> LPR_FREESLOT_NUM             = 0x%x\r\n",   rxi316_dram_info->dramc_info->slot_starve_reg->cr_lpr_freeslot_num);
	DBG_DRAM_INFO("> LPR_RMW_RUN_LEN              = 0x%x\r\n",   rxi316_dram_info->dramc_info->slot_starve_reg->cr_lpr_rmw_run_len);

	// ---->cr_cbctl1 setting
	dramc_dev->cbctl1 = (
							(rxi316_dram_info->dramc_info->slot_starve_reg->cr_dis_wmg           << CBCTL1_DIS_WMG_BFO)           |
							(rxi316_dram_info->dramc_info->slot_starve_reg->cr_pageopen          << CBCTL1_PAGEOPEN_BFO)          |
							(rxi316_dram_info->dramc_info->slot_starve_reg->cr_wmg_num_threshold << CBCTL1_WMG_NUM_THRESHOLD_BFO) |
							(rxi316_dram_info->dramc_info->slot_starve_reg->cr_lpw_rmw_run_len   << CBCTL1_LPW_RMW_RUN_LEN_BFO)
						);

	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("RXI316_BE_CR_00000484_INIT_VAL = 0x%08x\r\n", dramc_dev->cbctl1);
	DBG_DRAM_INFO("CR_CBCTL1                      = 0x%08x\r\n", dramc_dev->cbctl1);
	DBG_DRAM_INFO("> DIS_WMG                      = 0x%x\r\n",   rxi316_dram_info->dramc_info->slot_starve_reg->cr_dis_wmg);
	DBG_DRAM_INFO("> PAGEOPEN                     = 0x%x\r\n",   rxi316_dram_info->dramc_info->slot_starve_reg->cr_pageopen);
	DBG_DRAM_INFO("> WMG_NUM_THRESHOLD            = 0x%x\r\n",   rxi316_dram_info->dramc_info->slot_starve_reg->cr_wmg_num_threshold);
	DBG_DRAM_INFO("> LPW_RMW_RUN_LEN              = 0x%x\r\n",   rxi316_dram_info->dramc_info->slot_starve_reg->cr_lpw_rmw_run_len);

	// ---->cr_cbstarve0 setting
	dramc_dev->cbstarve0 = (rxi316_dram_info->dramc_info->slot_starve_reg->cr_lpr_max_starve);

	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("RXI316_BE_CR_00000488_INIT_VAL = 0x%08x\r\n", dramc_dev->cbstarve0);
	DBG_DRAM_INFO("CR_CBSTARVE0                   = 0x%08x\r\n", dramc_dev->cbstarve0);
	DBG_DRAM_INFO("> LPR_MAX_STARVE               = 0x%x\r\n",   rxi316_dram_info->dramc_info->slot_starve_reg->cr_lpr_max_starve);

	// ---->cr_cbstarve1 setting
	dramc_dev->cbstarve1 = (rxi316_dram_info->dramc_info->slot_starve_reg->cr_hpr_max_starve);

	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("RXI316_BE_CR_0000048C_INIT_VAL = 0x%08x\r\n", dramc_dev->cbstarve1);
	DBG_DRAM_INFO("CR_CBSTARVE1                   = 0x%08x\r\n", dramc_dev->cbstarve1);
	DBG_DRAM_INFO("> HPR_MAX_STARVE               = 0x%x\r\n",   rxi316_dram_info->dramc_info->slot_starve_reg->cr_hpr_max_starve);

	// ---->cr_cbstarve2 setting
	dramc_dev->cbstarve2 = (rxi316_dram_info->dramc_info->slot_starve_reg->cr_lpw_max_starve);

	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("RXI316_BE_CR_00000490_INIT_VAL = 0x%08x\r\n", dramc_dev->cbstarve2);
	DBG_DRAM_INFO("CR_CBSTARVE2                   = 0x%08x\r\n", dramc_dev->cbstarve2);
	DBG_DRAM_INFO("> LPW_MAX_STARVE               = 0x%x\r\n",   rxi316_dram_info->dramc_info->slot_starve_reg->cr_lpw_max_starve);

	// ---->cr_cbstarve3 setting
	dramc_dev->cbstarve3 = (rxi316_dram_info->dramc_info->slot_starve_reg->cr_lpr_rmw_max_starve);

	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("RXI316_BE_CR_00000494_INIT_VAL = 0x%08x\r\n", dramc_dev->cbstarve3);
	DBG_DRAM_INFO("CR_CBSTARVE3                   = 0x%08x\r\n", dramc_dev->cbstarve3);
	DBG_DRAM_INFO("> LPR_RMW_MAX_STARVE           = 0x%x\r\n",   rxi316_dram_info->dramc_info->slot_starve_reg->cr_lpr_rmw_max_starve);

	// ---->cr_cbstarve4 setting
	dramc_dev->cbstarve4 = (rxi316_dram_info->dramc_info->slot_starve_reg->cr_lpw_rmw_max_starve);

	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("RXI316_BE_CR_00000498_INIT_VAL = 0x%08x\r\n", dramc_dev->cbstarve4);
	DBG_DRAM_INFO("CR_CBSTARVE4                   = 0x%08x\r\n", dramc_dev->cbstarve4);
	DBG_DRAM_INFO("> LPW_RMW_MAX_STARVE           = 0x%x\r\n",   rxi316_dram_info->dramc_info->slot_starve_reg->cr_lpw_rmw_max_starve);

	// ---->cr_bank_sch_ctrl setting
	dramc_dev->bank_sch_ctrl = (
								   (rxi316_dram_info->dramc_info->slot_starve_reg->cr_ba_sel_times  << BANK_SCH_BA_SEL_LMT_BFO) |
								   (rxi316_dram_info->dramc_info->slot_starve_reg->cr_bg_sel_times  << BANK_SCH_BG_SEL_LMT_BFO) |
								   (rxi316_dram_info->dramc_info->slot_starve_reg->cr_ra_sel_times  << BANK_SCH_RA_SEL_LMT_BFO)
							   );

	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("RXI316_BE_CR_000004A0_INIT_VAL = 0x%08x\r\n", dramc_dev->bank_sch_ctrl);
	DBG_DRAM_INFO("CR_BANK_SCH_CTRL               = 0x%08x\r\n", dramc_dev->bank_sch_ctrl);
	DBG_DRAM_INFO("> BA_SEL_LMT                   = 0x%x\r\n",   rxi316_dram_info->dramc_info->slot_starve_reg->cr_ba_sel_times);
	DBG_DRAM_INFO("> BG_SEL_LMT                   = 0x%x\r\n",   rxi316_dram_info->dramc_info->slot_starve_reg->cr_bg_sel_times);
	DBG_DRAM_INFO("> RA_SEL_LMT                   = 0x%x\r\n",   rxi316_dram_info->dramc_info->slot_starve_reg->cr_ra_sel_times);

} // rxi316_perf_tune


void hal_dramc_init(DRAMC_TypeDef *dramc_dev, struct rxi316_dram_device_info *rxi316_dram_info)
{
	// DRAM info
	uint32_t     pctl_period, dfi_rate;//adj_pctl_period;
	// CR_DRAM_SIZE
	uint32_t     dram_size;
	// CR_MISC
	uint32_t     page_size;
	enum         rxi316_dram_bank_size    bank_size;
	enum         rxi316_dram_bst_len      bst_size;
	enum         rxi316_hybr_dq_size      hybr_size;
	// CR_WRAP_CHOP_BD
	enum         cr_chop_size      chop_size;
	// CR_DCR
	uint32_t     cr_rank2, cr_wr_dbi, cr_rd_dbi, cr_par, cr_gear_down, cr_bg2, cr_bg_remap, cr_zqc;
	uint32_t     dq_width;
	// CR_MRx
	uint32_t     dram_bstlen, dram_rl, dram_wl, dram_type;
	// CR_MRINFO
	uint32_t     cas_wr, cas_rd;
	uint32_t     cas_add, mrinfo_add_lat;
	uint32_t     mrinfo_dqsck_max, mrinfo_wr_lat, mrinfo_rd_lat;
	uint32_t     sdram_wr, mrinfo_nwr, mrinfo_rtp;
	// CR_IOCR
	uint32_t     tphy_rd, tphy_wd, tphy_wl, dual_ch_en, addr_share_en, ac_share_en;
	uint32_t     odt_2pins, cke_nop, stc_cke, stc_odt, cmd_2t_en, rtw_2t_dis, half_csn, rd_pipe;
	// CR_DRR
	uint32_t     trfc_tck, trefi_tck, ref_num, ref_dis, zqcl_inv;
	// CR_TPR0~CR_TPR2
	uint32_t     trp_tck, trp_tck_tmp, tras_tck, tras_tck_tmp, twr_tck, trtp_tck, tcke_tck, tpd_en, tzqcs_tck;
	uint32_t     trrd_tck, trc_tck, trcd_tck, tccd_tck, tccd_l_tck, twtr_tck, trtw_tck, tfaw_tck;
	uint32_t     tmrd_tck, zqc_inv, rst_tus_tck, tus_tck, tns_tck;
	// CR_TPR3
	uint32_t     trpab_pb_ps, trpab_pb_tck, tras_msb, tfaw_msb;
	uint32_t     dpin_cmd_lat, trcd_msb, twtr_msb, trtw_msb, trfc_msb, twr_msb, tppd_tck;
	uint32_t     tccd_s_tck, twtr_s_tck, trrd_s_tck, tccd_kw_tck, tccd_r_tck;
	// CR_TPR4~CR_TPR5
	uint32_t     trp_msb;
	uint32_t     odt_hold_default, odt_hold, odt_dly;
	// CR_MR0
	uint32_t     mr0_bl;
	enum         rxi316_dram_bst_type     bst_type;
	uint32_t     mr0_cas, mr0_wr, mr0_bit2, mr0_bit12, mr0_bit13;
	// CR_MR1
	uint32_t     dll_en, mr1_bit2, mr1_bl, dram_al, mr1_wr_lpddr23, mr1_wr_lpddr4, rtt_norm;
	// CR_MR2
	uint32_t     mr2_cas, mr2_cwl, mr2_bit4, dyc_odt_en ;
	// CR_MR0~CR_MR 22
	uint32_t     mr0_or_val, mr1_or_val, mr2_or_val;


	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("************  DRAM Information  ***********\r\n");

	dfi_rate = 1 << (uint32_t)(rxi316_dram_info->dfi_rate);
	pctl_period = (rxi316_dram_info->ddr_period_ps) * (dfi_rate); // according DFI_RATE to setting
	//adj_pctl_period = (1000000 / 533) * (dfi_rate); // according DFI_RATE to setting
	dram_type = rxi316_dram_info->dev->device_type;

	if (rxi316_dram_info->dev ->bst_len == BST_LEN_4) {
		dram_bstlen = 4;
	} else if (rxi316_dram_info->dev ->bst_len == BST_LEN_8) {
		dram_bstlen = 8;
	} else { // BST_16
		dram_bstlen = 16;
	}

	dram_wl = rxi316_dram_info->mode_reg->dram_wr_lat;
	dram_rl = rxi316_dram_info->mode_reg->dram_rd_lat;
	dram_al = rxi316_dram_info->mode_reg->dram_add_lat;


	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("> DRAM_PERIOD   = %d ps\r\n", rxi316_dram_info->ddr_period_ps);
	DBG_DRAM_INFO("> PCTL_PERIOD   = %d ps\r\n", pctl_period);
	DBG_DRAM_INFO("> DRAM_TYPE     = %d\r\n", dram_type);
	DBG_DRAM_INFO("> DRAM_BSTLEN   = %d\r\n", dram_bstlen);
	DBG_DRAM_INFO("> DRAM WL       = %d\r\n", dram_wl);
	DBG_DRAM_INFO("> DRAM RL       = %d\r\n", dram_rl);
	DBG_DRAM_INFO("> DRAM AL       = %d\r\n", dram_al);



	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("************  CR Information  ************\r\n");
	DBG_DRAM_INFO("base address = %x\r\n", &(dramc_dev->dram_size));

	// ----> cr_dram_size setting
	dram_size = 0xfffffff;
	dramc_dev->dram_size = dram_size;


	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("RXI316_BE_CR_00000230_INIT_VAL = 0x%08x\r\n", dramc_dev->dram_size);
	DBG_DRAM_INFO("CR_MISC                        = 0x%08x\r\n", dramc_dev->dram_size);
	DBG_DRAM_INFO("> DRAM_SIZE                    = 0x%x\r\n",   dram_size);

	// ----> cr_misc setting
	if (rxi316_dram_info->dev->dq_width == DQ_32) {
		page_size = (rxi316_dram_info->dev->dram_colu_bits) + 2 - 8;
	} else if (rxi316_dram_info->dev->dq_width == DQ_16) {
		page_size = (rxi316_dram_info->dev->dram_colu_bits) + 1 - 8;
	} else if (rxi316_dram_info-> dev-> dq_width == DQ_8) {
		page_size = (rxi316_dram_info->dev->dram_colu_bits) + 0 - 8;
	} else {
		page_size = (rxi316_dram_info->dev->dram_colu_bits) + 2 - 8;
	}

	bank_size = (rxi316_dram_info->dev->bank);
	bst_size  = (rxi316_dram_info->dev->bst_len);
	hybr_size = (rxi316_dram_info->dev->hybr_size);

	dramc_dev->misc = (
						  (page_size   << WRAP_MISC_PAGE_SIZE_BFO) |
						  (bank_size   << WRAP_MISC_BANK_SIZE_BFO) |
						  (bst_size    << WRAP_MISC_BST_SIZE_BFO) |
						  (hybr_size   << WRAP_MISC_HYBR_SIZE_BFO)
					  );

	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("RXI316_BE_CR_00000224_INIT_VAL = 0x%08x\r\n", dramc_dev->misc);
	DBG_DRAM_INFO("CR_MISC                        = 0x%08x\r\n", dramc_dev->misc);
	DBG_DRAM_INFO("> PAGE_SIZE                    = 0x%x\r\n",   page_size);
	DBG_DRAM_INFO("> BANK_SIZE                    = 0x%x\r\n",   bank_size);
	DBG_DRAM_INFO("> BST_SIZE                     = 0x%x\r\n",   bst_size);
	DBG_DRAM_INFO("> HYBR_SIZE                    = 0x%x\r\n",   hybr_size);

	// ----> cr_wrap_chop_bd setting
	chop_size = rxi316_dram_info->dramc_info->chop_size;
	dramc_dev->wrap_chop_bd = (
								  (chop_size   << WRAP_CHOP_SIZE_BFO)
							  );

	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("RXI316_BE_CR_00000228_INIT_VAL = 0x%08x\r\n", dramc_dev->wrap_chop_bd);
	DBG_DRAM_INFO("CR_WRAP_CHOP_BD                = 0x%08x\r\n", dramc_dev->wrap_chop_bd);
	DBG_DRAM_INFO("> CR_CHOP_SIZE                 = 0x%x\r\n",   chop_size);

	// ----> cr_dcr setting
	dram_type    = (rxi316_dram_info->dev->device_type);
	dq_width     = 1 << (uint32_t)(rxi316_dram_info->dev->dq_width);
	cr_rank2     = rxi316_dram_info->dramc_info->rank2;
	cr_wr_dbi    = rxi316_dram_info->dramc_info->wr_dbi;
	cr_rd_dbi    = rxi316_dram_info->dramc_info->rd_dbi;
	cr_par       = rxi316_dram_info->dramc_info->par;
	cr_gear_down = rxi316_dram_info->dramc_info->gear_down;
	cr_bg2       = rxi316_dram_info->dramc_info->bg2;
	cr_bg_remap  = rxi316_dram_info->dramc_info->bg_remap;
	cr_zqc       = rxi316_dram_info->dramc_info->zqc;
	dramc_dev->dcr = (
						 (dram_type   << PCTL_DCR_DDR_BFO) |
						 (dq_width    << PCTL_DCR_DQ_WID_BFO) |
						 (dfi_rate    << PCTL_DCR_DFI_RATE_BFO) |
						 (cr_rank2    << PCTL_DCR_RANK2_BFO) |
						 (cr_wr_dbi   << PCTL_DCR_WR_DBI_BFO) |
						 (cr_rd_dbi   << PCTL_DCR_RD_DBI_BFO) |
						 (cr_par      << PCTL_DCR_PAR_BFO) |
						 (cr_gear_down << PCTL_DCR_GEAR_DOWN_BFO) |
						 (cr_bg2      << PCTL_DCR_BG2_BFO) |
						 (cr_bg_remap << PCTL_DCR_BG_REMAP_BFO) |
						 (cr_zqc      << PCTL_DCR_ZQC_BFO)
					 );

	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("RXI316_BE_CR_00000004_INIT_VAL = 0x%08x\r\n", dramc_dev->dcr);
	DBG_DRAM_INFO("CR_DCR                         = 0x%08x\r\n", dramc_dev->dcr);
	DBG_DRAM_INFO("> DDR TYPE                     = 0x%x\r\n",   dram_type);
	DBG_DRAM_INFO("> DQ WIDTH                     = 0x%x\r\n",   dq_width);
	DBG_DRAM_INFO("> DFI RATE                     = 0x%x\r\n",   dfi_rate);
	DBG_DRAM_INFO("> RANK2                        = 0x%x\r\n",   cr_rank2);
	DBG_DRAM_INFO("> WR_DBI                       = 0x%x\r\n",   cr_wr_dbi);
	DBG_DRAM_INFO("> RD_DBI                       = 0x%x\r\n",   cr_rd_dbi);
	DBG_DRAM_INFO("> PAR                          = 0x%x\r\n",   cr_par);
	DBG_DRAM_INFO("> GEAR_DOWN                    = 0x%x\r\n",   cr_gear_down);
	DBG_DRAM_INFO("> BG2                          = 0x%x\r\n",   cr_bg2);
	DBG_DRAM_INFO("> BG_REMAP                     = 0x%x\r\n",   cr_bg_remap);
	DBG_DRAM_INFO("> ZQC                          = 0x%x\r\n",   cr_zqc);

	// ----> cr_iocr setting
	odt_2pins     = rxi316_dram_info->dramc_info->odt_2pins;
	cke_nop       = rxi316_dram_info->dramc_info->cke_nop;
	stc_cke       = rxi316_dram_info->dramc_info->stc_cke;
	stc_odt       = rxi316_dram_info->dramc_info->stc_odt;
	cmd_2t_en     = rxi316_dram_info->dramc_info->cmd_2t_en;
	rtw_2t_dis    = rxi316_dram_info->dramc_info->rtw_2t_dis;
	half_csn      = rxi316_dram_info->dramc_info->half_csn;
	rd_pipe       = rxi316_dram_info->dramc_info->rd_pipe;
	tphy_wl       = 0; // not support in rtk_phy
	tphy_wd       = ROUND_UP(rxi316_dram_info->mode_reg->tphy_wd, dfi_rate);
	tphy_rd       = ROUND_UP(rxi316_dram_info->mode_reg->tphy_rd, dfi_rate);
	dual_ch_en    = rxi316_dram_info->dramc_info->dual_ch_en;
	addr_share_en = rxi316_dram_info->dramc_info->addr_share_en;
	ac_share_en   = rxi316_dram_info->dramc_info->ac_share_en;

	dramc_dev->iocr = (
						  (odt_2pins     << PCTL_IOCR_ODT_2PINS_BFO) |
						  (cke_nop       << PCTL_IOCR_CKE_NOP_BFO) |
						  (stc_cke       << PCTL_IOCR_STC_CKE_BFO) |
						  (stc_odt       << PCTL_IOCR_STC_ODT_BFO) |
						  (cmd_2t_en     << PCTL_IOCR_CMD_2T_EN_BFO) |
						  (rtw_2t_dis    << PCTL_IOCR_RTW_2T_DIS_BFO) |
						  (half_csn      << PCTL_IOCR_HALF_CSN_BFO) |
						  (rd_pipe       << PCTL_IOCR_RD_PIPE_BFO) |
						  (tphy_wd       << PCTL_IOCR_TPHY_WD_BFO) |
						  (tphy_wl       << PCTL_IOCR_TPHY_WL_BFO) |
						  (tphy_rd       << PCTL_IOCR_TPHY_RD_EN_BFO) |
						  (dual_ch_en    << PCTL_IOCR_DC_CH1_BFO) |
						  (addr_share_en << PCTL_IOCR_ADDR_SHARE_BFO) |
						  (ac_share_en   << PCTL_IOCR_AC_SHARE_BFO)
					  );

	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("RXI316_BE_CR_00000008_INIT_VAL = 0x%08x\r\n", dramc_dev->iocr);
	DBG_DRAM_INFO("CR_IOCR                        = 0x%08x\r\n", dramc_dev->iocr);
	DBG_DRAM_INFO("> ODT_2PINS                    = 0x%x\r\n",   odt_2pins);
	DBG_DRAM_INFO("> CKE_NOP                      = 0x%x\r\n",   cke_nop);
	DBG_DRAM_INFO("> STC_CKE                      = 0x%x\r\n",   stc_odt);
	DBG_DRAM_INFO("> STC_ODT                      = 0x%x\r\n",   stc_cke);
	DBG_DRAM_INFO("> CMD_2T_EN                    = 0x%x\r\n",   cmd_2t_en);
	DBG_DRAM_INFO("> RTW_2T_DIS                   = 0x%x\r\n",   rtw_2t_dis);
	DBG_DRAM_INFO("> HALF_CSN                     = 0x%x\r\n",   half_csn);
	DBG_DRAM_INFO("> RD_PIPE                      = 0x%x\r\n",   rd_pipe);
	DBG_DRAM_INFO("> TPHY_WD                      = 0x%x\r\n",   tphy_wd);
	DBG_DRAM_INFO("> TPHY_WL                      = 0x%x\r\n",   tphy_wl);
	DBG_DRAM_INFO("> TPHY_RD                      = 0x%x\r\n",   tphy_rd);
	DBG_DRAM_INFO("> DC_CH1                       = 0x%x\r\n",   dual_ch_en);
	DBG_DRAM_INFO("> ADDR_SHARE                   = 0x%x\r\n",   addr_share_en);
	DBG_DRAM_INFO("> AC_SHARE                     = 0x%x\r\n",   ac_share_en);

	// ----> cr_mr0 setting
	mr0_bl       = 0;
	mr0_bit2     = 0;
	mr0_bit12    = 0;
	mr0_bit13    = 0;
	mr0_cas      = 0;
	mr0_wr       = 0;
	mr0_or_val   = rxi316_dram_info->mode_reg-> mr0_or_val;
	if (dram_bstlen == 8) {
		if ((rxi316_dram_info->dev->device_type) == DDR_2) {
			mr0_bl  = 3;
		} else {
			mr0_bl  = 0;
		}
	} else if (dram_bstlen == 4) {
		if ((rxi316_dram_info->dev->device_type) == DDR_3 ||
			(rxi316_dram_info->dev->device_type) == DDR_2) {
			mr0_bl  = 2;
		}
	}

	bst_type = (rxi316_dram_info->dev->bst_type);

	if ((rxi316_dram_info->dev->device_type) == DDR_2) {
		mr0_cas  = dram_rl;
	} else if ((rxi316_dram_info->dev->device_type) == DDR_3) {
		if (dram_rl < 5) {
			mr0_bit2 = 0;
			mr0_cas  = 1;
		} else {
			if (dram_rl < 12) {
				mr0_bit2 = 0;
				mr0_cas = dram_rl - 4;
			} else {
				mr0_bit2 = 1;
				mr0_cas = dram_rl - 12;
			}
		}
	}

	sdram_wr = rxi316_dram_info->timing->nWR;
	if ((rxi316_dram_info->dev->device_type) == DDR_2) { // nWR setting
		if ((sdram_wr  >= 2) && (sdram_wr  <= 8)) { // 2~8
			mr0_wr = sdram_wr - 1 ;
		}
	} else if ((rxi316_dram_info->dev->device_type) == DDR_3) {
		if (sdram_wr  < 5) {  // 5
			mr0_wr = 1;
		} else if ((sdram_wr  >= 5) && (sdram_wr  <= 8)) { // 5~8
			mr0_wr = sdram_wr  - 4;
		} else if ((sdram_wr  >= 9) && (sdram_wr <= 14)) { // 9~14
			mr0_wr = sdram_wr / 2 ;
		} else { // 15, 16
			mr0_wr = 0;
		}
	}
	// DDR1, LPDDR1 without nWR

	if ((rxi316_dram_info->dev->device_type) != DDR_2) {
		mr0_bit12 = 1;
	}

	dramc_dev->mr0 = (
						 (mr0_bl      << PCTL_MR0_BL_BFO)        |
						 (mr0_bit2    << 2)                      |
						 (bst_type    << PCTL_MR0_BST_TYPE_BFO)  |
						 (mr0_cas     << PCTL_MR0_CAS_BFO)       |
						 (mr0_wr      << PCTL_MR0_WR_BFO)        |
						 (mr0_bit12   << 12)                     |
						 (mr0_bit13   << 13)                     |
						 (mr0_or_val)
					 );

	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("RXI316_BE_CR_00000034_INIT_VAL = 0x%08x\r\n", dramc_dev->mr0);
	DBG_DRAM_INFO("CR_MR0                         = 0x%08x\r\n", dramc_dev->mr0);
	DBG_DRAM_INFO("> MR0_BL                       = 0x%x\r\n",   mr0_bl);
	DBG_DRAM_INFO("> BST_TYPE                     = 0x%x\r\n",   bst_type);
	DBG_DRAM_INFO("> MR0_CAS                      = 0x%x\r\n",   mr0_cas);
	DBG_DRAM_INFO("> MR0_WR                       = 0x%x\r\n",   mr0_wr);

	// ----> cr_mr1 setting

	dll_en   = 0; // 1:enable DLL, 0:disable
	mr1_bit2 = 0;
	mr1_bl   = 0;
	mr1_wr_lpddr23 = 0;
	mr1_wr_lpddr4  = 0;
	rtt_norm   = 0; // Enable DDR4 RTT_NORM for RZQ/4
	mr1_or_val = rxi316_dram_info->mode_reg->mr1_or_val;

	// nWR setting
	sdram_wr = rxi316_dram_info->timing->nWR;

	//D.I.C(output driver impedance control) = RZQ/3, Rtt_Norm = RZQ/2
	if ((rxi316_dram_info->dev->device_type) == DDR_3) {
		mr1_bit2 = 0;
		mr1_wr_lpddr23 = 3;
	}

	dramc_dev->mr1 = (
						 (dll_en          << PCTL_MR1_DLL_EN_BFO)   |    // mr1[0]
						 (mr1_bit2        << 2)   |                      // mr1[2]
						 (mr1_bl          << PCTL_MR1_BL_BFO)   |        // mr1[2:0]
						 (dram_al         << PCTL_MR1_ADD_LAT_BFO)   |   // mr1[4:3]
						 (mr1_wr_lpddr23  << PCTL_MR1_WR_LP23_BFO)   |   // mr1[7:5]
						 (mr1_wr_lpddr4   << PCTL_MR1_WR_LP4_BFO)   |    // mr1[6:4]
						 (rtt_norm        << PCTL_MR1_RTT_NORM_EN_BFO) | // mr1[10:8]
						 (mr1_or_val)
					 );

	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("RXI316_BE_CR_00000038_INIT_VAL = 0x%08x\r\n", dramc_dev->mr1);
	DBG_DRAM_INFO("CR_MR1                         = 0x%08x\r\n", dramc_dev->mr1);
	DBG_DRAM_INFO("> DLL_EN                       = 0x%x\r\n",   dll_en);
	DBG_DRAM_INFO("> ADD_LAT                      = 0x%x\r\n",   dram_al);
	DBG_DRAM_INFO("> MR1_WR_LPDDR23               = 0x%x\r\n",   mr1_wr_lpddr23);
	DBG_DRAM_INFO("> MR1_WR_LPDDR4                = 0x%x\r\n",   mr1_wr_lpddr4);
	DBG_DRAM_INFO("> RTT_NORM                     = 0x%x\r\n",   rtt_norm);

	// ----> cr_mr2 setting
	mr2_cas    = 0;
	mr2_cwl    = 0;
	mr2_bit4   = 0;
	mr2_or_val = rxi316_dram_info->mode_reg-> mr2_or_val;
	if ((rxi316_dram_info->dev->device_type) == DDR_3) {
		mr2_cwl = dram_wl - 5;
	}

	if ((rxi316_dram_info->dev->device_type) == DDR_2) {
		dyc_odt_en = 0; // Disable dynamic odt
	} else {
		if (rxi316_dram_info->dramc_info->stc_odt) {
			dyc_odt_en = 0; // Disable dynamic odt
		} else {
			dyc_odt_en = 1; // Enable dynamic odt
		}
	}

	dramc_dev->mr2 = (
						 (mr2_cas         << PCTL_MR2_CAS_BFO) |          // mr2[3:0]
						 (mr2_cwl         << PCTL_MR2_CWL_BFO) |          // mr2[5:3]
						 (mr2_bit4        << 4) |                         // mr2[4]
						 (dyc_odt_en      << PCTL_MR2_DYC_ODT_EN_BFO) |   // mr2[10:9]
						 (mr2_or_val)
					 );

	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("RXI316_BE_CR_0000003C_INIT_VAL = 0x%08x\r\n", dramc_dev->mr2);
	DBG_DRAM_INFO("CR_MR2                         = 0x%08x\r\n", dramc_dev->mr2);
	DBG_DRAM_INFO("> MR2_CAS                      = 0x%x\r\n",   mr2_cas);
	DBG_DRAM_INFO("> MR2_CWL                      = 0x%x\r\n",   mr2_cwl);
	DBG_DRAM_INFO("> DYC_ODT_EN                   = 0x%x\r\n",   dyc_odt_en);

	// ----> cr_mrinfo setting
	mrinfo_dqsck_max = 0;

	cas_wr = (rxi316_dram_info->mode_reg->dram_wr_lat) +
			 (rxi316_dram_info->mode_reg->dram_par_lat);

	cas_rd = (rxi316_dram_info->mode_reg->dram_rd_lat) +
			 (rxi316_dram_info->mode_reg->dram_par_lat);

	cas_add = (rxi316_dram_info->mode_reg->dram_add_lat);

	mrinfo_wr_lat  = ROUND_UP(cas_wr, dfi_rate);
	mrinfo_rd_lat  = ROUND_UP(cas_rd, dfi_rate);
	mrinfo_add_lat = ROUND_UP(cas_add, dfi_rate);

	// nWR setting
	sdram_wr = rxi316_dram_info->timing->nWR; // 8
	mrinfo_nwr = 0;
	if ((rxi316_dram_info->dev->device_type) == DDR_2 || // sdram_wr= 2 ~ 8
		(rxi316_dram_info->dev->device_type) == DDR_3) { // sdram_wr= 3~8
		// nWR setting
		mrinfo_nwr = ROUND_UP(sdram_wr, dfi_rate); // 4
	}

	// tRTP setting
	trtp_tck = ROUND_UP(rxi316_dram_info->timing->trtp_ps, pctl_period);

	if (dram_type == DDR_2) {
		trtp_tck = dram_al + (((dram_bstlen / 2) - 2) / dfi_rate) + trtp_tck;
	} else {
		trtp_tck = dram_al + trtp_tck;
	}

	// nRTP setting
	mrinfo_rtp = trtp_tck;

	dramc_dev->mrinfo = (
							(mrinfo_wr_lat    << PCTL_MRINFO_WR_LAT_BFO) |
							(mrinfo_rd_lat    << PCTL_MRINFO_RD_LAT_BFO) |
							(mrinfo_add_lat   << PCTL_MRINFO_ADD_LAT_BFO) |
							(mrinfo_dqsck_max << PCTL_MRINFO_TDQSCK_MAX_BFO) |
							(mrinfo_nwr       << PCTL_MRINFO_NWR_BFO)        |
							(mrinfo_rtp       << PCTL_MRINFO_RTP_BFO)
						);

	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("RXI316_BE_CR_00000030_INIT_VAL = 0x%08x\r\n", dramc_dev->mrinfo);
	DBG_DRAM_INFO("CR_MRINFO                      = 0x%08x\r\n", dramc_dev->mrinfo);
	DBG_DRAM_INFO("> WR_LAT                       = 0x%x\r\n",   mrinfo_wr_lat);
	DBG_DRAM_INFO("> RD_LAT                       = 0x%x\r\n",   mrinfo_rd_lat);
	DBG_DRAM_INFO("> ADD_LAT                      = 0x%x\r\n",   mrinfo_add_lat);
	DBG_DRAM_INFO("> tDQSCK_MAX                   = 0x%x\r\n",   mrinfo_dqsck_max);
	DBG_DRAM_INFO("> nWR                          = 0x%x\r\n",   mrinfo_nwr);
	DBG_DRAM_INFO("> RTP                          = 0x%x\r\n",   mrinfo_rtp);

	// ----> cr_drr setting
	trfc_tck = ROUND_UP(rxi316_dram_info->timing->trfc_ps, pctl_period);

	/*DDR2 & DDR3 should use 533 MHz to calculate trefi, if use lower speed, this value should be modified*/
	trefi_tck = ROUND_UP(rxi316_dram_info->timing->trefi_ps, pctl_period) - 200;
	/*For 400MHz / 480MHz setting*/
	//trefi_tck = 0x550;

	ref_num = 1;
	ref_dis  = rxi316_dram_info->dramc_info->ref_dis;
	zqcl_inv = rxi316_dram_info->dramc_info->zqcl_inv;

	dramc_dev->drr = (
						 ((trfc_tck & 0xff)  << PCTL_DRR_TRFC_BFO) |
						 (trefi_tck          << PCTL_DRR_TREF_BFO) |
						 (ref_num            << PCTL_DRR_REF_NUM_BFO) |
						 (ref_dis            << PCTL_DRR_REF_DIS_BFO) |
						 (zqcl_inv           << PCTL_DRR_ZQCL_INV_BFO)
					 );

	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("RXI316_BE_CR_00000010_INIT_VAL = 0x%08x\r\n", dramc_dev->drr);
	DBG_DRAM_INFO("CR_DRR                         = 0x%08x\r\n", dramc_dev->drr);
	DBG_DRAM_INFO("> tRFC                         = 0x%x\r\n",   trfc_tck);
	DBG_DRAM_INFO("> tRFE                         = 0x%x\r\n",   trefi_tck);
	DBG_DRAM_INFO("> REF_NUM                      = 0x%x\r\n",   ref_num);
	DBG_DRAM_INFO("> REF_DIS                      = 0x%x\r\n",   ref_dis);
	DBG_DRAM_INFO("> ZQCL_INV                     = 0x%x\r\n",   zqcl_inv);

	// ----> cr_tpr0 setting
	tras_tck = ROUND_UP(rxi316_dram_info->timing->tras_ps, pctl_period);
	twr_tck  = ROUND_UP(rxi316_dram_info->timing->twr_ps, pctl_period);
	trp_tck  = ROUND_UP(rxi316_dram_info->timing->trp_ps, pctl_period);

	if (rxi316_dram_info->timing->tcke_ps > rxi316_dram_info->timing->txp_ps) {
		tcke_tck = ROUND_UP(rxi316_dram_info->timing->tcke_ps, pctl_period);
	} else {
		tcke_tck = ROUND_UP(rxi316_dram_info->timing->txp_ps, pctl_period);
	}

	tpd_en    = rxi316_dram_info->dramc_info->tpd_en;
	tzqcs_tck = ROUND_UP(rxi316_dram_info->timing->tzqcs_tck, dfi_rate);

	dramc_dev->tpr0 = (
						  (trp_tck   & 0xf   << PCTL_TPR0_TRP_BFO) |
						  ((tras_tck & 0x1f) << PCTL_TPR0_TRAS_BFO) |
						  ((twr_tck  & 0xf)  << PCTL_TPR0_TWR_BFO) |
						  (trtp_tck          << PCTL_TPR0_TRTP_BFO) |
						  (tcke_tck          << PCTL_TPR0_TCKE_BFO) |
						  (tpd_en            << PCTL_TPR0_TPD_EN_BFO) |
						  (tzqcs_tck         << PCTL_TPR0_TZQCS_BFO)
					  );

	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("RXI316_BE_CR_00000014_INIT_VAL = 0x%08x\r\n", dramc_dev->tpr0);
	DBG_DRAM_INFO("CR_TPR0                        = 0x%08x\r\n", dramc_dev->tpr0);
	DBG_DRAM_INFO("> tRP                          = 0x%x\r\n",   trp_tck);
	DBG_DRAM_INFO("> tRAS                         = 0x%x\r\n",   tras_tck);
	DBG_DRAM_INFO("> tWR                          = 0x%x\r\n",   twr_tck);
	DBG_DRAM_INFO("> tRTP                         = 0x%x\r\n",   trtp_tck);
	DBG_DRAM_INFO("> tCKE                         = 0x%x\r\n",   tcke_tck);
	DBG_DRAM_INFO("> tPD_EN                       = 0x%x\r\n",   tpd_en);
	DBG_DRAM_INFO("> tZQCS                        = 0x%x\r\n",   tzqcs_tck);

	// ----> cr_tpr1 setting
	// trrd,trc,trcd,tccd,twtr,trtw,tfaw_lsb
	trrd_tck     = ROUND_UP(rxi316_dram_info->timing->trrd_ps, pctl_period);
	tras_tck_tmp = ROUND_UP(rxi316_dram_info->timing->tras_ps, pctl_period);
	trp_tck_tmp  = ROUND_UP(rxi316_dram_info->timing->trp_ps, pctl_period);
	trc_tck      = ROUND_UP(rxi316_dram_info->timing->trc_ps, pctl_period);

	if ((tras_tck_tmp + trp_tck_tmp) > trc_tck) {
		trc_tck = tras_tck_tmp + trp_tck_tmp;
	}

	trcd_tck = (ROUND_UP(rxi316_dram_info->timing->trcd_ps, pctl_period)) - 1; // cmd_sch: bank_sch more 1t
	tccd_tck = ROUND_UP(rxi316_dram_info->timing->tccd_tck, dfi_rate);
	twtr_tck = ROUND_UP(rxi316_dram_info->timing->twtr_tck, dfi_rate);

	// trtw expression
	// ==== trtw clock cycles in dram domain
	trtw_tck = 0;
	if (dram_type == DDR_2) {
		trtw_tck = dram_bstlen / 2 + 2;
		trtw_tck = ROUND_UP(trtw_tck, dfi_rate);
	} else if (dram_type == DDR_3) {
		trtw_tck = dram_rl + dram_bstlen / 2 + 2 - dram_wl;
		trtw_tck = ROUND_UP(trtw_tck, dfi_rate) + 1;
	}

	tfaw_tck = ROUND_UP(rxi316_dram_info->timing->tfaw_ps, pctl_period);

	tccd_l_tck = 0;

	dramc_dev->tpr1 = (
						  (trrd_tck           << PCTL_TPR1_TRRD_BFO) |
						  (trc_tck            << PCTL_TPR1_TRC_BFO) |
						  ((trcd_tck & 0xf)   << PCTL_TPR1_TRCD_BFO) |
						  (tccd_tck           << PCTL_TPR1_TCCD_BFO) |
						  ((twtr_tck & 0x7)   << PCTL_TPR1_TWTR_BFO) |
						  ((trtw_tck & 0xf)   << PCTL_TPR1_TRTW_BFO) |
						  ((tfaw_tck & 0x1f)  << PCTL_TPR1_TFAW_BFO) |
						  (tccd_l_tck         << 29)
					  );

	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("RXI316_BE_CR_00000018_INIT_VAL = 0x%08x\r\n", dramc_dev->tpr1);
	DBG_DRAM_INFO("CR_TPR1                        = 0x%08x\r\n", dramc_dev->tpr1);
	DBG_DRAM_INFO("> tRRD                         = 0x%x\r\n",   trrd_tck);
	DBG_DRAM_INFO("> tRC                          = 0x%x\r\n",   trc_tck);
	DBG_DRAM_INFO("> tRCD                         = 0x%x\r\n",   trcd_tck);
	DBG_DRAM_INFO("> tCCD                         = 0x%x\r\n",   tccd_tck);
	DBG_DRAM_INFO("> tWTR                         = 0x%x\r\n",   twtr_tck);
	DBG_DRAM_INFO("> tRTW                         = 0x%x\r\n",   trtw_tck);
	DBG_DRAM_INFO("> tFAW                         = 0x%x\r\n",   tfaw_tck);

	// ----> cr_tpr2 setting
	// trrd,trc,trcd,tccd,twtr,trtw,tfaw_lsb

	if ((rxi316_dram_info->dev->device_type) == DDR_2) {
		zqc_inv = 2; // init refresh num or zq short cmd interval times(by enable zqc:dcr[30])
	} else {
		zqc_inv = rxi316_dram_info->dramc_info->zqc_inv; // init refresh num or zq short cmd interval times(by enable zqc:dcr[30])
	}

	tmrd_tck = 0;
	if ((rxi316_dram_info->dev->device_type) == DDR_3) {
		tmrd_tck = rxi316_dram_info->timing->tmrd_tck;
	} else if ((rxi316_dram_info->dev->device_type) == DDR_2) {
		tmrd_tck = ROUND_UP(rxi316_dram_info->timing->tmrd_tck, pctl_period);
	}

	// rst_tus, tus, tns
	rst_tus_tck = 0;
	tus_tck = 0;
	tns_tck = 0;
	if (dram_type == DDR_2) { // DDR2
		rst_tus_tck = 0;
		tus_tck     = ((200000000 / pctl_period) >> 10) + 1;      // 200us
		tns_tck     = ((400000   / pctl_period) >> 7) + 1;        // 400ns
	} else if (dram_type == DDR_3) {
		rst_tus_tck = ((200000000 / pctl_period) >> 10) + 1;      // 200us
		tus_tck     = ((500000000 / pctl_period) >> 10) + 1;      // 500us
		tns_tck     = ((trfc_tck + (10000 / pctl_period)) >> 7) + 1; // max (5tck, tRFC+10ns)
	}

	dramc_dev->tpr2 = (
						  (zqc_inv      << PCTL_TPR2_INIT_REF_NUM_BFO) |
						  (tmrd_tck     << PCTL_TPR2_TMRD_BFO) |
						  (tns_tck      << PCTL_TPR2_INIT_NS_BFO) |
						  (tus_tck      << PCTL_TPR2_INIT_US_BFO) |
						  (rst_tus_tck  << PCTL_TPR2_INIT_RST_US_BFO)
					  );

	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("RXI316_BE_CR_0000001C_INIT_VAL = 0x%08x\r\n", dramc_dev->tpr2);
	DBG_DRAM_INFO("CR_TPR2                        = 0x%08x\r\n", dramc_dev->tpr2);
	DBG_DRAM_INFO("> ZQC_INV(INT_REF_NUM)         = 0x%x\r\n",   zqc_inv);
	DBG_DRAM_INFO("> tMRD                         = 0x%x\r\n",   tmrd_tck);
	DBG_DRAM_INFO("> tNS                          = 0x%x\r\n",   tns_tck);
	DBG_DRAM_INFO("> tUS                          = 0x%x\r\n",   tus_tck);
	DBG_DRAM_INFO("> RST_tUS                      = 0x%x\r\n",   rst_tus_tck);

	// ----> cr_tpr3 setting
	trpab_pb_ps = 0;
	trpab_pb_tck = ROUND_UP(trpab_pb_ps, pctl_period);

	tras_msb = (tras_tck & 0x20) >> 5; // tras_msb, mask tras lsb[4:0]

	tfaw_tck = ROUND_UP(rxi316_dram_info->timing->tfaw_ps, pctl_period);
	tfaw_msb = (tfaw_tck & 0x20) >> 5; // tfaw_msb, mask tfaw_lsb[4:0]

	dpin_cmd_lat = 0;

	trcd_msb = (trcd_tck & 0x10)  >> 4; // trcd_msb, mask trcd_lsb[3:0]
	twtr_msb = (twtr_tck & 0x8)   >> 3; // twtr_msb, mask twtr_lsb[2:0]
	trtw_msb = (trtw_tck & 0x10)  >> 4; // trtw_msb, mask trtw_lsb[3:0]
	trfc_msb = (trfc_tck & 0x100) >> 8; // trfc_msb, mask trfc_lsb[7:0]
	twr_msb  = (twr_tck  & 0x10)  >> 4; // twr msb

	tppd_tck = 0;

	tccd_s_tck = ROUND_UP(rxi316_dram_info->timing->tccd_s_tck, dfi_rate);
	twtr_s_tck = ROUND_UP(rxi316_dram_info->timing->twtr_s_tck, dfi_rate);
	trrd_s_tck = ROUND_UP(rxi316_dram_info->timing->trrd_s_tck, dfi_rate);

	// tccd_r: control rank tccd timing(for dqs preamable confict), using tccd_tck + 1
	if ((dram_bstlen / dfi_rate) > rxi316_dram_info->timing->tccd_tck) {
		trrd_s_tck = ROUND_UP(((dram_bstlen / dfi_rate) - rxi316_dram_info->timing->tccd_tck),  dfi_rate);
	}

	tccd_r_tck = 0;
	tccd_kw_tck = 0;

	dramc_dev->tpr3 = (
						  (trpab_pb_tck  << PCTL_TPR3_TRPAB_PB_BFO) |
						  (tras_msb      << PCTL_TPR3_TRAS_MSB_BFO) |
						  (tfaw_msb      << PCTL_TPR3_TFAW_MSB_BFO) |
						  (dpin_cmd_lat  << PCTL_TPR3_DPIN_LAT_BFO) |
						  (trcd_msb      << PCTL_TPR3_TRCD_MSB_BFO) |
						  (twtr_msb      << PCTL_TPR3_TWTR_MSB_BFO) |
						  (trtw_msb      << PCTL_TPR3_TRTW_MSB_BFO) |
						  (trfc_msb      << PCTL_TPR3_TRFC_MSB_BFO) |
						  (twr_msb       << PCTL_TPR3_TWR_MSB_BFO) |
						  (tppd_tck      << PCTL_TPR3_TPPD_BFO) |
						  (tccd_s_tck    << PCTL_TPR3_TCCD_S_BFO) |
						  (twtr_s_tck    << PCTL_TPR3_TWTR_S_BFO) |
						  (trrd_s_tck    << PCTL_TPR3_TRRD_S_BFO) |
						  (tccd_kw_tck   << PCTL_TPR3_TCCD_KW_BFO) |
						  (tccd_r_tck    << PCTL_TPR3_TCCD_R_BFO)
					  );

	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("RXI316_BE_CR_00000020_INIT_VAL = 0x%08x\r\n", dramc_dev->tpr3);
	DBG_DRAM_INFO("CR_TPR3                        = 0x%08x\r\n", dramc_dev->tpr3);
	DBG_DRAM_INFO("> tRPAB_PB                     = 0x%x\r\n",   trpab_pb_tck);
	DBG_DRAM_INFO("> tRAS_MSB                     = 0x%x\r\n",   tras_msb);
	DBG_DRAM_INFO("> tFAW_MSB                     = 0x%x\r\n",   tfaw_msb);
	DBG_DRAM_INFO("> DPIN_CMD_LAT                 = 0x%x\r\n",   dpin_cmd_lat);
	DBG_DRAM_INFO("> tRCD_MSB                     = 0x%x\r\n",   trcd_msb);
	DBG_DRAM_INFO("> tWTR_MSB                     = 0x%x\r\n",   twtr_msb);
	DBG_DRAM_INFO("> tRTW_MSB                     = 0x%x\r\n",   trtw_msb);
	DBG_DRAM_INFO("> tRFC_MSB                     = 0x%x\r\n",   trfc_msb);
	DBG_DRAM_INFO("> tWR_MSB                      = 0x%x\r\n",   twr_msb);
	DBG_DRAM_INFO("> tPPD                         = 0x%x\r\n",   tppd_tck);
	DBG_DRAM_INFO("> tCCD_S                       = 0x%x\r\n",   tccd_s_tck);
	DBG_DRAM_INFO("> tWTR_S                       = 0x%x\r\n",   twtr_s_tck);
	DBG_DRAM_INFO("> tRRD_S                       = 0x%x\r\n",   trrd_s_tck);
	DBG_DRAM_INFO("> tCCD_KW                      = 0x%x\r\n",   tccd_kw_tck);
	DBG_DRAM_INFO("> tCCD_R                       = 0x%x\r\n",   tccd_r_tck);

	// ----> cr_tpr4 setting
	trp_msb = (trp_tck & 0x10)  >> 4; // trp_msb, mask trp_lsb[3:0]
	dramc_dev->tpr4 = (
						  (trp_msb  << PCTL_TPR4_TRP_MSB_BFO)
					  );

	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("RXI316_BE_CR_00000090_INIT_VAL = 0x%08x\r\n", dramc_dev->tpr4);
	DBG_DRAM_INFO("CR_TPR4                        = 0x%08x\r\n", dramc_dev->tpr4);
	DBG_DRAM_INFO("> tRP_MSB                      = 0x%x\r\n",   trp_msb);

	// ----> cr_tpr5 setting
	odt_hold_default  = dram_bstlen / 2 + 2;
	odt_dly           = 0;

	if (dfi_rate == 1) {
		odt_hold = odt_hold_default;
	} else { // dfi2 use 2tpreabmle
		odt_hold = odt_hold_default + 1;
	}

	dramc_dev->tpr5 = (
						  (odt_hold  << PCTL_TPR5_ODT_HOLD_BFO) |
						  (odt_dly   << PCTL_TPR5_ODT_DLY_BFO)
					  );

	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("RXI316_BE_CR_00000094_INIT_VAL = 0x%08x\r\n", dramc_dev->tpr5);
	DBG_DRAM_INFO("CR_TPR5                        = 0x%08x\r\n", dramc_dev->tpr5);
	DBG_DRAM_INFO("> ODT_HOLD                     = 0x%x\r\n",   odt_hold);
	DBG_DRAM_INFO("> ODT_DLY                      = 0x%x\r\n",   odt_dly);

	// ----> cr_imr setting
	dramc_dev->imr = 0xffff;

	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("RXI316_BE_CR_000000CC_INIT_VAL = 0x%08x\r\n", dramc_dev->imr);
	DBG_DRAM_INFO("CR_IMR                         = 0x%08x\r\n", dramc_dev->imr);

	// set all_mode idle
	dramc_dev->csr = 0x700;

	// start to init
	dramc_dev->ccr = 0x1;
	// wait init_done: read cr_ccr[0] == 1
	while (((dramc_dev->ccr) & 0x1) != 0x1);

	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("RXI316_BE_CR_00000000_INIT_VAL = 0x%08x\r\n", dramc_dev->ccr);
	DBG_DRAM_INFO("CR_CCR                         = 0x%08x\r\n", dramc_dev->ccr);

	// enter mem_mode
	dramc_dev->csr = 0x600;
	// check mode state
	while (((dramc_dev->csr) & 0x7ff) != 0x600);

	DBG_DRAM_INFO("===========================================\r\n");
	DBG_DRAM_INFO("RXI316_BE_CR_0000000C_INIT_VAL = 0x%08x\r\n", dramc_dev->csr);
	DBG_DRAM_INFO("CR_CSR                         = 0x%08x\r\n", dramc_dev->csr);
} // rxi316_dram_init

void cpu_read_modify_write(volatile uint32_t *addr, u32 data, u32 data_mask)
{
	u32 rmw_data = HAL_READ32(addr, 0x0);

	rmw_data = (rmw_data & (~data_mask)) | (data & data_mask);
	HAL_WRITE32(addr, 0x0, rmw_data);
}

#if CONFIG_PXP || SIMU_DDR_PXP_INIT_FLOW_EN // PXP , asic simu run flow
void hal_ddr2_phy_init(uint32_t dram_period_ps)
{
	DPI_TypeDef *dpi_dev_map = (DPI_TypeDef *) DPI_REG_BASE_ADDR;
	u32 rmw_data;

	hal_delay_us(1);
	cpu_read_modify_write(&dpi_dev_map->DPI_CRT_RST_CTL, 0x100, 0x100);

	hal_delay_us(1);
	cpu_read_modify_write(&dpi_dev_map->DPI_CRT_RST_CTL, 0x30, 0x30);

	dpi_dev_map->DPI_AFIFO_STR_0 = 0x22222222;//CL7

	cpu_read_modify_write(&dpi_dev_map->DPI_AFIFO_STR_1, 0x300000, 0x300000);

	cpu_read_modify_write(&dpi_dev_map->DPI_CRT_RST_CTL, 0x1, 0x1);

	rmw_data = dpi_dev_map->DPI_SSC1;
	rmw_data &= ~(DPI_MASK_GRAN_SET | DPI_MASK_DOT_GRAN);
	rmw_data |= (0x1CC | (0x4 << DPI_SHIFT_DOT_GRAN));
	dpi_dev_map->DPI_SSC1 = rmw_data;

	rmw_data = dpi_dev_map->DPI_SSC2;
	rmw_data &= ~(DPI_MASK_F_CODE | DPI_MASK_F_CODE_T);
	rmw_data |= (0x222 | (0x2AA << DPI_SHIFT_F_CODE_T));
	dpi_dev_map->DPI_SSC2 = rmw_data;

	rmw_data = dpi_dev_map->DPI_SSC3;
	rmw_data &= ~(DPI_MASK_N_CODE | DPI_MASK_N_CODE_T);
	rmw_data |= (0xA | (0xA << DPI_SHIFT_N_CODE_T));
	dpi_dev_map->DPI_SSC3 = rmw_data;

	//Set DCC/DLL
	cpu_read_modify_write(&dpi_dev_map->DPI_DCC_CMD, 0x3, 0x20000007);
	cpu_read_modify_write(&dpi_dev_map->DPI_DCC_CS, 0x3, 0x20000007);
	cpu_read_modify_write(&dpi_dev_map->DPI_DCC_CS1, 0x3, 0x20000007);
	cpu_read_modify_write(&dpi_dev_map->DPI_DCC_DQS_0, 0x3, 0x20000007);
	cpu_read_modify_write(&dpi_dev_map->DPI_DCC_DQS_1, 0x3, 0x20000007);
	cpu_read_modify_write(&dpi_dev_map->DPI_DCC_DQS_2, 0x3, 0x20000007);
	cpu_read_modify_write(&dpi_dev_map->DPI_DCC_DQS_3, 0x3, 0x20000007);
	cpu_read_modify_write(&dpi_dev_map->DPI_DCC_DQ_0, 0x3, 0x20000007);
	cpu_read_modify_write(&dpi_dev_map->DPI_DCC_DQ_1, 0x3, 0x20000007);
	cpu_read_modify_write(&dpi_dev_map->DPI_DCC_DQ_2, 0x3, 0x20000007);
	cpu_read_modify_write(&dpi_dev_map->DPI_DCC_DQ_3, 0x3, 0x20000007);
	cpu_read_modify_write(&dpi_dev_map->DPI_DCC_CK_0, 0x3, 0x20000007);
	cpu_read_modify_write(&dpi_dev_map->DPI_DCC_CK_1, 0x3, 0x20000007);

	cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI1, 0x80000, 0x1F0000);
	cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI2, 0x80808, 0x1F1F1F);
	hal_delay_us(10);

	cpu_read_modify_write(&dpi_dev_map->DPI_CRT_CTL, 0x102, 0x08080132);
	cpu_read_modify_write(&dpi_dev_map->DPI_CRT_CTL, 0x40000000, 0x40000000);
	hal_delay_us(1);
	cpu_read_modify_write(&dpi_dev_map->DPI_CRT_RST_CTL, 0x2, 0x2);

	hal_delay_us(100);

	cpu_read_modify_write(&dpi_dev_map->DPI_CRT_RST_CTL, 0x0, 0x8);
	cpu_read_modify_write(&dpi_dev_map->DPI_CRT_RST_CTL, 0xC, 0xC);
	hal_delay_us(1);

	cpu_read_modify_write(&dpi_dev_map->DPI_SSC3, 0x4000000, 0x4000000);
	cpu_read_modify_write(&dpi_dev_map->DPI_SSC3, 0x0, 0x4000000);
	cpu_read_modify_write(&dpi_dev_map->DPI_SSC0, 0xA, 0xA);

	cpu_read_modify_write(&dpi_dev_map->DPI_PLL_CTL1, 0x80000000, 0x80000000);
	hal_delay_us(1);

	rmw_data = dpi_dev_map->DPI_PLL_CTL3;
	rmw_data &= ~(DPI_MASK_ICP | DPI_MASK_LOOP_PI_ISEL | DPI_MASK_POST_PI_BIAS | DPI_MASK_POST_PI_RL);
	rmw_data |= (0x3 << DPI_SHIFT_ICP) | (0x3 << DPI_SHIFT_LOOP_PI_ISEL) | (0x1 << DPI_SHIFT_POST_PI_BIAS) | (0x1 << DPI_SHIFT_POST_PI_RL);
	dpi_dev_map->DPI_PLL_CTL3 = rmw_data;

	hal_delay_us(50);

	/*dfi_mck_slice_all*/
	cpu_read_modify_write(&dpi_dev_map->DPI_PLL_CTL0, 0x0, 0xFFE);
	hal_delay_us(1);
	cpu_read_modify_write(&dpi_dev_map->DPI_PLL_CTL1, 0x0, 0x20000);
	hal_delay_us(1);
	cpu_read_modify_write(&dpi_dev_map->DPI_PLL_CTL0, 0xFFF, 0xFFE);
	hal_delay_us(1);
	cpu_read_modify_write(&dpi_dev_map->DPI_PLL_CTL1, 0x70000, 0x70000);
	hal_delay_us(1);

	/*Wait PLL ready*/
	while ((HAL_READ32(REG_SYS_DDRPHY_CTRL, 0x0) & 0x8) != 0x8);

	/*Enable PAD*/
	cpu_read_modify_write(REG_SYS_DDRPHY_CTRL, 0x2, 0x2);

	cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_2, 0x10C00000, 0x10C00000);
	cpu_read_modify_write(&dpi_dev_map->DPI_CRT_CTL, 0x0, 0x40800);
	cpu_read_modify_write(&dpi_dev_map->DPI_CRT_CTL, 0x0, 0x4);
	dpi_dev_map->DPI_CMD_ADR_PH = 0x7C055555;

	/*CL7*/
	cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x1002, 0x203F03);
	dpi_dev_map->DPI_READ_CTRL_0_0 = 0x5;
	dpi_dev_map->DPI_READ_CTRL_0_1 = 0x5;
	cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_1, 0xC, 0xC);
}

void hal_ddr3_phy_init(uint32_t dram_period_ps)
{
	DPI_TypeDef *dpi_dev_map = (DPI_TypeDef *) DPI_REG_BASE_ADDR;
	u32 rmw_data;

	hal_delay_us(1);
	cpu_read_modify_write(&dpi_dev_map->DPI_CRT_RST_CTL, 0x100, 0x100);

	hal_delay_us(1);
	cpu_read_modify_write(&dpi_dev_map->DPI_CRT_RST_CTL, 0x30, 0x30);

	dpi_dev_map->DPI_AFIFO_STR_0 = 0x22222222;

	cpu_read_modify_write(&dpi_dev_map->DPI_AFIFO_STR_1, 0x300000, 0x300000);

	cpu_read_modify_write(&dpi_dev_map->DPI_CRT_RST_CTL, 0x1, 0x1);

	rmw_data = dpi_dev_map->DPI_SSC1;
	rmw_data &= ~(DPI_MASK_GRAN_SET | DPI_MASK_DOT_GRAN);
	rmw_data |= (0x1CC | (0x4 << DPI_SHIFT_DOT_GRAN));
	dpi_dev_map->DPI_SSC1 = rmw_data;

	rmw_data = dpi_dev_map->DPI_SSC2;
	rmw_data &= ~(DPI_MASK_F_CODE | DPI_MASK_F_CODE_T);
	rmw_data |= (0x222 | (0x2AA << DPI_SHIFT_F_CODE_T));
	dpi_dev_map->DPI_SSC2 = rmw_data;

	rmw_data = dpi_dev_map->DPI_SSC3;
	rmw_data &= ~(DPI_MASK_N_CODE | DPI_MASK_N_CODE_T);
	rmw_data |= (0xA | (0xA << DPI_SHIFT_N_CODE_T));
	dpi_dev_map->DPI_SSC3 = rmw_data;

	//Set DCC/DLL
	cpu_read_modify_write(&dpi_dev_map->DPI_DCC_CMD, 0x3, 0x20000007);
	cpu_read_modify_write(&dpi_dev_map->DPI_DCC_CS, 0x3, 0x20000007);
	cpu_read_modify_write(&dpi_dev_map->DPI_DCC_CS1, 0x3, 0x20000007);
	cpu_read_modify_write(&dpi_dev_map->DPI_DCC_DQS_0, 0x3, 0x20000007);
	cpu_read_modify_write(&dpi_dev_map->DPI_DCC_DQS_1, 0x3, 0x20000007);
	cpu_read_modify_write(&dpi_dev_map->DPI_DCC_DQS_2, 0x3, 0x20000007);
	cpu_read_modify_write(&dpi_dev_map->DPI_DCC_DQS_3, 0x3, 0x20000007);
	cpu_read_modify_write(&dpi_dev_map->DPI_DCC_DQ_0, 0x3, 0x20000007);
	cpu_read_modify_write(&dpi_dev_map->DPI_DCC_DQ_1, 0x3, 0x20000007);
	cpu_read_modify_write(&dpi_dev_map->DPI_DCC_DQ_2, 0x3, 0x20000007);
	cpu_read_modify_write(&dpi_dev_map->DPI_DCC_DQ_3, 0x3, 0x20000007);
	cpu_read_modify_write(&dpi_dev_map->DPI_DCC_CK_0, 0x3, 0x20000007);
	cpu_read_modify_write(&dpi_dev_map->DPI_DCC_CK_1, 0x3, 0x20000007);

	cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI1, 0x80000, 0x1F0000);
	cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI2, 0x80808, 0x1F1F1F);
	hal_delay_us(10);

	cpu_read_modify_write(&dpi_dev_map->DPI_CRT_CTL, 0x80021, 0x080813F3);
	cpu_read_modify_write(&dpi_dev_map->DPI_CRT_CTL, 0x40000000, 0x40000000);
	hal_delay_us(1);
	cpu_read_modify_write(&dpi_dev_map->DPI_CRT_RST_CTL, 0x2, 0x2);

	hal_delay_us(100);

	cpu_read_modify_write(&dpi_dev_map->DPI_CRT_RST_CTL, 0x0, 0x8);
	cpu_read_modify_write(&dpi_dev_map->DPI_CRT_RST_CTL, 0xC, 0xC);
	hal_delay_us(1);

	cpu_read_modify_write(&dpi_dev_map->DPI_SSC3, 0x4000000, 0x4000000);
	cpu_read_modify_write(&dpi_dev_map->DPI_SSC3, 0x0, 0x4000000);
	cpu_read_modify_write(&dpi_dev_map->DPI_SSC0, 0xA, 0xA);

	cpu_read_modify_write(&dpi_dev_map->DPI_PLL_CTL1, 0x80000000, 0x80000000);
	hal_delay_us(1);

	rmw_data = dpi_dev_map->DPI_PLL_CTL3;
	rmw_data &= ~(DPI_MASK_ICP | DPI_MASK_LOOP_PI_ISEL | DPI_MASK_POST_PI_BIAS | DPI_MASK_POST_PI_RL);
	rmw_data |= (0x3 << DPI_SHIFT_ICP) | (0x3 << DPI_SHIFT_LOOP_PI_ISEL) | (0x1 << DPI_SHIFT_POST_PI_BIAS) | (0x1 << DPI_SHIFT_POST_PI_RL);
	dpi_dev_map->DPI_PLL_CTL3 = rmw_data;

	hal_delay_us(50);

	/*dfi_mck_slice_all*/
	cpu_read_modify_write(&dpi_dev_map->DPI_PLL_CTL0, 0x0, 0xFFE);
	hal_delay_us(1);
	cpu_read_modify_write(&dpi_dev_map->DPI_PLL_CTL1, 0x0, 0x20000);
	hal_delay_us(1);
	cpu_read_modify_write(&dpi_dev_map->DPI_PLL_CTL0, 0xFFF, 0xFFE);
	hal_delay_us(1);
	cpu_read_modify_write(&dpi_dev_map->DPI_PLL_CTL1, 0x70000, 0x70000);
	hal_delay_us(1);

	/*Wait PLL ready*/
	while ((HAL_READ32(REG_SYS_DDRPHY_CTRL, 0x0) & 0x8) != 0x8);

	/*Enable PAD*/
	cpu_read_modify_write(REG_SYS_DDRPHY_CTRL, 0x2, 0x2);

	cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_2, 0x10C00000, 0x10C00000);
	cpu_read_modify_write(&dpi_dev_map->DPI_CRT_CTL, 0x0, 0x40800);
	cpu_read_modify_write(&dpi_dev_map->DPI_CRT_CTL, 0x0, 0x4);
	dpi_dev_map->DPI_CMD_ADR_PH = 0x7C055555;

	cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x1002, 0x203F03);
	dpi_dev_map->DPI_READ_CTRL_0_0 = 0x7;
	dpi_dev_map->DPI_READ_CTRL_0_1 = 0x7;
	dpi_dev_map->DPI_READ_CTRL1 = 0x4;
	cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_1, 0xC, 0xC);
}

#else
void hal_ddr2_phy_init(uint32_t dram_period_ps)
{
	DPI_TypeDef *dpi_dev_map = (DPI_TypeDef *) DPI_REG_BASE_ADDR;
	u32 ddr_freq = 1000000 / dram_period_ps;
	u32 freq;

	dbg_printf("ddr_freq = %d\r\n", ddr_freq);

	hal_delay_us(1);
	/*Release Bandgap reset*/
	dpi_dev_map->DPI_CRT_RST_CTL |= DPI_BIT_PLL_BG_RST_N;

	hal_delay_us(1);
	/*Release PLL LDO reset*/
	dpi_dev_map->DPI_CRT_RST_CTL |= DPI_BIT_PLL_LDO_RST_N;

	hal_delay_us(1);
	/*Enable PLL internal LDO*/
	dpi_dev_map->DPI_CRT_RST_CTL |= (DPI_BIT_POW_LDO_PLL | DPI_BIT_POW_LDO_V11);

	dpi_dev_map->DPI_AFIFO_STR_0 = 0x44444444;//533, CAS = 7
	cpu_read_modify_write(&dpi_dev_map->DPI_AFIFO_STR_1, 0x300043,
						  DPI_MASK_CMD_RD_STR_NUM | DPI_MASK_CMD_EX_RD_STR_NUM | DPI_BIT_BYPASS_EN_TX | DPI_BIT_BYPASS_EN_RX);
	cpu_read_modify_write(&dpi_dev_map->DPI_AFIFO_STR_2, 0x2222,
						  DPI_MASK_RX_RD_STR_NUM_0 | DPI_MASK_RX_RD_STR_NUM_1 | DPI_MASK_RX_RD_STR_NUM_2 | DPI_MASK_RX_RD_STR_NUM_3);//533, CAS = 7

	dram_init_clk_frequency_dss(ddr_freq, 0);

	//Set DCC/DLL
	cpu_read_modify_write(&dpi_dev_map->DPI_DCC_CMD, 0x3, DPI_MASK_DCC_CMD_DUTY_PRESETA | DPI_BIT_DCC_CMD_DUTY_SEL);
	cpu_read_modify_write(&dpi_dev_map->DPI_DCC_CS, 0x3, DPI_MASK_DCC_CMD_DUTY_PRESETA | DPI_BIT_DCC_CMD_DUTY_SEL);
	cpu_read_modify_write(&dpi_dev_map->DPI_DCC_DQS_0, 0x3, DPI_MASK_DCC_CMD_DUTY_PRESETA | DPI_BIT_DCC_CMD_DUTY_SEL);
	cpu_read_modify_write(&dpi_dev_map->DPI_DCC_DQS_1, 0x3, DPI_MASK_DCC_CMD_DUTY_PRESETA | DPI_BIT_DCC_CMD_DUTY_SEL);
	cpu_read_modify_write(&dpi_dev_map->DPI_DCC_DQ_0, 0x3, DPI_MASK_DCC_CMD_DUTY_PRESETA | DPI_BIT_DCC_CMD_DUTY_SEL);
	cpu_read_modify_write(&dpi_dev_map->DPI_DCC_DQ_1, 0x3, DPI_MASK_DCC_CMD_DUTY_PRESETA | DPI_BIT_DCC_CMD_DUTY_SEL);
	cpu_read_modify_write(&dpi_dev_map->DPI_DCC_CK_0, 0x3, DPI_MASK_DCC_CMD_DUTY_PRESETA | DPI_BIT_DCC_CMD_DUTY_SEL);

	cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI1, 0x80000, 0x1F0000);
	cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI2, 0x80808, 0x1F1F1F);
	hal_delay_us(10);

	cpu_read_modify_write(&dpi_dev_map->DPI_CRT_CTL, 0x102, 0x08080132);

	dpi_dev_map->DPI_CRT_CTL |= DPI_BIT_MCK_CKE_SEL;
	hal_delay_us(1);

	dpi_dev_map->DPI_CRT_RST_CTL |= DPI_BIT_PLL_SSC_DIG_RST_N;
	hal_delay_us(100);

	dpi_dev_map->DPI_CRT_RST_CTL &= ~DPI_BIT_PTR_RST_N;
	dpi_dev_map->DPI_CRT_RST_CTL |= (DPI_BIT_PTR_RST_N | DPI_BIT_RST_N);
	hal_delay_us(500);

	dpi_dev_map->DPI_PLL_CTL1 |= DPI_BIT_MCK_MC_EN;
	hal_delay_us(1);

	if (ddr_freq == 533) {
		freq = 0;
	} else if (ddr_freq == 400) {
		freq = 1;
	} else if (ddr_freq == 333) {
		freq = 2;
	} else if (ddr_freq == 200) {
		freq = 3;
	} else if (ddr_freq == 480) {
		freq = 4;
	} else {
		freq = 5;
	}

	dram_set_pll_frequency(ddr_freq, &pll_frequence_table[freq][0]);

	hal_delay_us(50);

	/*dfi_mck_slice_all*/
	//cpu_read_modify_write(&dpi_dev_map->DPI_PLL_CTL0, 0x0, 0xFFE);
	cpu_read_modify_write(&dpi_dev_map->DPI_PLL_CTL0, 0x0, DPI_MASK_MCK_CLK_EN);
	hal_delay_us(1);

	//cpu_read_modify_write(&dpi_dev_map->DPI_PLL_CTL1, 0x0, 0x20000);
	cpu_read_modify_write(&dpi_dev_map->DPI_PLL_CTL1, 0x0, DPI_MASK_CLK_OE);
	hal_delay_us(1);

	//cpu_read_modify_write(&dpi_dev_map->DPI_PLL_CTL0, 0xFFF, 0xFFE);
	cpu_read_modify_write(&dpi_dev_map->DPI_PLL_CTL0, 0xFFF, DPI_MASK_MCK_CLK_EN);
	hal_delay_us(1);

	//cpu_read_modify_write(&dpi_dev_map->DPI_PLL_CTL1, 0x70000, 0x70000);
	cpu_read_modify_write(&dpi_dev_map->DPI_PLL_CTL1, 0x7 << DPI_SHIFT_CLK_OE, DPI_MASK_CLK_OE);
	hal_delay_us(1);

	/*Wait PLL ready*/
	while ((HAL_READ32(REG_SYS_DDRPHY_CTRL, 0x0) & 0x8) != 0x8);

	/*Enable PAD*/
	cpu_read_modify_write((volatile uint32_t *)REG_SYS_DDRPHY_CTRL, 0x2, 0x2);

	// No CA Pad 0x18, CA Pad 0x11
	dpi_dev_map->DPI_OCDP0_SET0 = 0x11111111;
	dpi_dev_map->DPI_OCDP1_SET0 = 0x18111111;
	dpi_dev_map->DPI_OCDN0_SET0 = 0x11111111;
	dpi_dev_map->DPI_OCDN1_SET0 = 0x18111111;
	dpi_dev_map->DPI_OCDP0_SET1 = 0x11111111;
	dpi_dev_map->DPI_OCDP1_SET1 = 0x18111111;
	dpi_dev_map->DPI_OCDN0_SET1 = 0x11111111;
	dpi_dev_map->DPI_OCDN1_SET1 = 0x18111111;

	dpi_dev_map->DPI_DQ_OCD_SEL_0 = 0xFFFF7777;
	dpi_dev_map->DPI_DQ_OCD_SEL_1 = 0xFFFF7777;
	dpi_dev_map->DPI_DQS_OCD_SEL_0 = 0x77777777;
	dpi_dev_map->DPI_DQS_OCD_SEL_1 = 0x77777777;
	dpi_dev_map->DPI_CKE_OCD_SEL = 0xffffff77;
	dpi_dev_map->DPI_ADR_OCD_SEL = 0x77ff77ff;
	dpi_dev_map->DPI_CK_OCD_SEL = 0x77777777;

#if 0
	dram_r480_calibration(DDR_2);
	dram_zq_calibration(DDR_2);

	dpi_dev_map->DPI_DQ_ODT_SEL_0 = 0xFFFF4444;
	dpi_dev_map->DPI_DQ_ODT_SEL_1 = 0xFFFF4444;
	dpi_dev_map->DPI_DQ_OCD_SEL_0 = 0xFFFF0000;
	dpi_dev_map->DPI_DQ_OCD_SEL_1 = 0xFFFF0000;
	dpi_dev_map->DPI_DQS_P_ODT_SEL_0 = 0xffff0011;
	dpi_dev_map->DPI_DQS_P_ODT_SEL_1 = 0xffff0011;
	dpi_dev_map->DPI_DQS_N_ODT_SEL_0 = 0xffff1100;
	dpi_dev_map->DPI_DQS_N_ODT_SEL_1 = 0xffff1100;
	dpi_dev_map->DPI_DQS_OCD_SEL_0 = 0x0;
	dpi_dev_map->DPI_DQS_OCD_SEL_1 = 0x0;
	dpi_dev_map->DPI_CKE_OCD_SEL = 0xffff3333;
	dpi_dev_map->DPI_ADR_OCD_SEL = 0x33ff33ff;
	dpi_dev_map->DPI_CK_OCD_SEL = 0x55555555;
	dpi_dev_map->DPI_OCD_SEL_0 = 0x22222222;
	dpi_dev_map->DPI_OCD_SEL_1 = 0x22222222;
	dpi_dev_map->DPI_OCD_SEL_2 = 0x22222222;
	dpi_dev_map->DPI_OCD_SEL_3 = 0x22222222;
	dpi_dev_map->DPI_OCD_SEL_4 = 0x22222222;
	dpi_dev_map->DPI_OCD_SEL_5 = 0x22222222;
	dpi_dev_map->DPI_OCD_SEL_6 = 0x22222222;
	dpi_dev_map->DPI_OCD_SEL_7 = 0x22222222;
	dpi_dev_map->DPI_OCD_SEL_8 = 0x22222222;
	dpi_dev_map->DPI_ODT_SEL_0 = 0xffffff33;
	dpi_dev_map->DPI_CKE_ODT_SEL = 0xffff2222;
	dpi_dev_map->DPI_ADR_ODT_SEL = 0x22ff2277;
	dpi_dev_map->DPI_CLK_ODT_SEL = 0x00003333;
#endif
	cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_2, 0x10C00000, 0x10C00000);
	cpu_read_modify_write(&dpi_dev_map->DPI_CRT_CTL, 0x0, 0x40800);
	cpu_read_modify_write(&dpi_dev_map->DPI_CRT_CTL, 0x0, 0x4);

	/*Update immediately*/
	cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x2 << DPI_SHIFT_FW_SET_MODE, DPI_MASK_FW_SET_MODE);////CHUN-CHI
	dpi_dev_map->DPI_CMD_ADR_PH = 0x7C055555;

	dpi_dev_map->DPI_DQ_IO_CTL_1 &= ~DPI_BIT_DM_IE_FRC_EN;
	dpi_dev_map->DPI_DQ_IO_CTL_1_1 &= ~DPI_BIT_DM_IE_FRC_EN;

	cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x1000, 0x303F00);
	cpu_read_modify_write(&dpi_dev_map->DPI_READ_CTRL_0_0, 0x7 << DPI_SHIFT_TM_DQS_EN_FTUN, DPI_MASK_TM_DQS_EN_FTUN | DPI_MASK_TM_DQS_EN);////CHUN-CHI
	cpu_read_modify_write(&dpi_dev_map->DPI_READ_CTRL_0_1, 0x7 << DPI_SHIFT_TM_DQS_EN_FTUN, DPI_MASK_TM_DQS_EN_FTUN | DPI_MASK_TM_DQS_EN);////CHUN-CHI
	cpu_read_modify_write(&dpi_dev_map->DPI_READ_CTRL1, 0x6 << DPI_SHIFT_TM_RD_FIFO, DPI_MASK_TM_RD_FIFO);//533, CAS = 7

#if IS_CUT_TEST(CONFIG_CHIP_VER)
	/*DCK*/
	cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI0, 0x17 << DPI_SHIFT_POST_PI_SEL0, DPI_MASK_POST_PI_SEL0);
	dpi_dev_map->DPI_PLL_CTL1 |= (1 << 0);

	/*DCS*/
	cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI2, 0x1F << DPI_SHIFT_POST_PI_SEL10, DPI_MASK_POST_PI_SEL10);
	dpi_dev_map->DPI_PLL_CTL1 |= (1 << 10);

	/*DQS0, DQS1*/
	cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI0, 0x1D << DPI_SHIFT_POST_PI_SEL2, DPI_MASK_POST_PI_SEL2);
	cpu_read_modify_write(&dpi_dev_map->DPI_AFIFO_STR_0, 0x3 << DPI_SHIFT_DQS_RD_STR_NUM_0, DPI_MASK_DQS_RD_STR_NUM_0);//533, CAS = 7
	cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI0, 0x1D << DPI_SHIFT_POST_PI_SEL3, DPI_MASK_POST_PI_SEL3);
	cpu_read_modify_write(&dpi_dev_map->DPI_AFIFO_STR_0, 0x3 << DPI_SHIFT_DQS_RD_STR_NUM_1, DPI_MASK_DQS_RD_STR_NUM_1);//533, CAS = 7

	/*If pi value is 0 ~ 15, oesync = 0, if pi value is 16 ~ 31, oesync = 1*/
	dpi_dev_map->DPI_PLL_CTL1 |= (1 << 2);
	dpi_dev_map->DPI_PLL_CTL1 |= (1 << 3);

	/*DQ0, DQ1*/
	cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI1, 0x5 << DPI_SHIFT_POST_PI_SEL6, DPI_MASK_POST_PI_SEL6);
	cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI2, 0x6 << DPI_SHIFT_POST_PI_SEL7, DPI_MASK_POST_PI_SEL7);
#else
	/*DCK*/
	cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI0, 0x16 << DPI_SHIFT_POST_PI_SEL0, DPI_MASK_POST_PI_SEL0);
	dpi_dev_map->DPI_PLL_CTL1 |= (1 << 0);

	/*DCS*/
	cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI2, 0x0 << DPI_SHIFT_POST_PI_SEL10, DPI_MASK_POST_PI_SEL10);

	/*DQS0, DQS1*/
	cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI0, 0x1E << DPI_SHIFT_POST_PI_SEL2, DPI_MASK_POST_PI_SEL2);
	cpu_read_modify_write(&dpi_dev_map->DPI_AFIFO_STR_0, 0x3 << DPI_SHIFT_DQS_RD_STR_NUM_0, DPI_MASK_DQS_RD_STR_NUM_0);//533, CAS = 7
	cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI0, 0x1B << DPI_SHIFT_POST_PI_SEL3, DPI_MASK_POST_PI_SEL3);
	cpu_read_modify_write(&dpi_dev_map->DPI_AFIFO_STR_0, 0x3 << DPI_SHIFT_DQS_RD_STR_NUM_1, DPI_MASK_DQS_RD_STR_NUM_1);//533, CAS = 7

	/*If pi value is 0 ~ 15, oesync = 0, if pi value is 16 ~ 31, oesync = 1*/
	dpi_dev_map->DPI_PLL_CTL1 |= (1 << 2);
	dpi_dev_map->DPI_PLL_CTL1 |= (1 << 3);

	/*DQ0, DQ1*/
	cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI1, 0x6 << DPI_SHIFT_POST_PI_SEL6, DPI_MASK_POST_PI_SEL6);
	cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI2, 0x4 << DPI_SHIFT_POST_PI_SEL7, DPI_MASK_POST_PI_SEL7);
#endif
	/*DQ DLY*/
	dpi_dev_map->DPI_DQ_DLY_0 = 0x88888888;
	dpi_dev_map->DPI_DQ_DLY_0_1 = 0x88888888;
	dpi_dev_map->DPI_DQ_DLY_1 = 0x888;
	dpi_dev_map->DPI_DQ_DLY_1_1 = 0x888;

	/*FW set write delay chain of data slice*/
	dpi_dev_map->DPI_DPI_CTRL_1 |= (DPI_BIT_FW_SET_WR_DLY | DPI_BIT_WRITE_EN_0);

	/*FW set read delay chain of data slice*/
	dpi_dev_map->DPI_DPI_CTRL_1 |= (DPI_BIT_FW_SET_RD_DLY | DPI_BIT_WRITE_EN_1);

	cpu_read_modify_write(&dpi_dev_map->DPI_READ_CTRL_0_0, 0x9 << DPI_SHIFT_DQS_RC1IN_DLY_SEL, DPI_MASK_DQS_RC1IN_DLY_SEL);
	cpu_read_modify_write(&dpi_dev_map->DPI_READ_CTRL_0_1, 0xC << DPI_SHIFT_DQS_RC1IN_DLY_SEL, DPI_MASK_DQS_RC1IN_DLY_SEL);

	/*Pick the center point of available windows*/
	dpi_dev_map->DPI_DQS_IN_DLY0 = 0x10101010;
	dpi_dev_map->DPI_DQS_IN_DLY0_1 = 0x10101010;

	dpi_dev_map->DPI_DQS_IN_DLY1 = 0x10101010;
	dpi_dev_map->DPI_DQS_IN_DLY1_1 = 0x10101010;

	dpi_dev_map->DPI_DQS_IN_DLY2 = 0x10101010;
	dpi_dev_map->DPI_DQS_IN_DLY2_1 = 0x10101010;

	dpi_dev_map->DPI_DQS_IN_DLY3 = 0x10101010;
	dpi_dev_map->DPI_DQS_IN_DLY3_1 = 0x10101010;

	dpi_dev_map->DPI_DPI_CTRL_1 |= (DPI_BIT_FW_SET_RD_DLY | DPI_BIT_WRITE_EN_1);
	cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x0 << DPI_SHIFT_FW_SET_MODE, DPI_MASK_FW_SET_MODE);
}

void hal_ddr3_phy_init(uint32_t dram_period_ps)
{
	DPI_TypeDef *dpi_dev_map = (DPI_TypeDef *) DPI_REG_BASE_ADDR;
	u32 ddr_freq = 1000000 / dram_period_ps;
	u32 freq;

	dbg_printf("ddr_freq = %d\r\n", ddr_freq);

	hal_delay_us(1);
	/*Release Bandgap reset*/
	dpi_dev_map->DPI_CRT_RST_CTL |= DPI_BIT_PLL_BG_RST_N;

	hal_delay_us(1);
	/*Release PLL LDO reset*/
	dpi_dev_map->DPI_CRT_RST_CTL |= DPI_BIT_PLL_LDO_RST_N;

	hal_delay_us(1);
	/*Enable PLL internal LDO*/
	dpi_dev_map->DPI_CRT_RST_CTL |= (DPI_BIT_POW_LDO_PLL | DPI_BIT_POW_LDO_V11);


	//dpi_dev_map->DPI_AFIFO_STR_0 = 0x33333333;
	dpi_dev_map->DPI_AFIFO_STR_0 = 0x44444444;//533, CAS = 7
	cpu_read_modify_write(&dpi_dev_map->DPI_AFIFO_STR_1, 0x300043,
						  DPI_MASK_CMD_RD_STR_NUM | DPI_MASK_CMD_EX_RD_STR_NUM | DPI_BIT_BYPASS_EN_TX | DPI_BIT_BYPASS_EN_RX);
	cpu_read_modify_write(&dpi_dev_map->DPI_AFIFO_STR_2, 0x2222,
						  DPI_MASK_RX_RD_STR_NUM_0 | DPI_MASK_RX_RD_STR_NUM_1 | DPI_MASK_RX_RD_STR_NUM_2 | DPI_MASK_RX_RD_STR_NUM_3);//533, CAS = 7

	dram_init_clk_frequency_dss(ddr_freq, 0);

	//Set DCC/DLL
	cpu_read_modify_write(&dpi_dev_map->DPI_DCC_CMD, 0x3, DPI_MASK_DCC_CMD_DUTY_PRESETA | DPI_BIT_DCC_CMD_DUTY_SEL);
	cpu_read_modify_write(&dpi_dev_map->DPI_DCC_CS, 0x3, DPI_MASK_DCC_CMD_DUTY_PRESETA | DPI_BIT_DCC_CMD_DUTY_SEL);
	cpu_read_modify_write(&dpi_dev_map->DPI_DCC_DQS_0, 0x3, DPI_MASK_DCC_CMD_DUTY_PRESETA | DPI_BIT_DCC_CMD_DUTY_SEL);
	cpu_read_modify_write(&dpi_dev_map->DPI_DCC_DQS_1, 0x3, DPI_MASK_DCC_CMD_DUTY_PRESETA | DPI_BIT_DCC_CMD_DUTY_SEL);
	cpu_read_modify_write(&dpi_dev_map->DPI_DCC_DQ_0, 0x3, DPI_MASK_DCC_CMD_DUTY_PRESETA | DPI_BIT_DCC_CMD_DUTY_SEL);
	cpu_read_modify_write(&dpi_dev_map->DPI_DCC_DQ_1, 0x3, DPI_MASK_DCC_CMD_DUTY_PRESETA | DPI_BIT_DCC_CMD_DUTY_SEL);
	cpu_read_modify_write(&dpi_dev_map->DPI_DCC_CK_0, 0x3, DPI_MASK_DCC_CMD_DUTY_PRESETA | DPI_BIT_DCC_CMD_DUTY_SEL);

	cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI1, 0x80000, 0x1F0000);
	cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI2, 0x80808, 0x1F1F1F);
	hal_delay_us(10);

	cpu_read_modify_write(&dpi_dev_map->DPI_CRT_CTL, 0x80021, 0x080813F3);

	dpi_dev_map->DPI_CRT_CTL |= DPI_BIT_MCK_CKE_SEL;
	hal_delay_us(1);

	dpi_dev_map->DPI_CRT_RST_CTL |= DPI_BIT_PLL_SSC_DIG_RST_N;
	hal_delay_us(100);

	dpi_dev_map->DPI_CRT_RST_CTL &= ~DPI_BIT_PTR_RST_N;
	dpi_dev_map->DPI_CRT_RST_CTL |= (DPI_BIT_PTR_RST_N | DPI_BIT_RST_N);
	hal_delay_us(1);

	dpi_dev_map->DPI_PLL_CTL1 |= DPI_BIT_MCK_MC_EN;
	hal_delay_us(1);

	if (ddr_freq == 533) {
		freq = 0;
	} else if (ddr_freq == 400) {
		freq = 1;
	} else if (ddr_freq == 333) {
		freq = 2;
	} else if (ddr_freq == 200) {
		freq = 3;
	} else if (ddr_freq == 480) {
		freq = 4;
	} else {
		freq = 5;
	}

	dram_set_pll_frequency(ddr_freq, &pll_frequence_table[freq][0]);

	hal_delay_us(50);

	/*dfi_mck_slice_all*/
	//cpu_read_modify_write(&dpi_dev_map->DPI_PLL_CTL0, 0x0, 0xFFE);
	cpu_read_modify_write(&dpi_dev_map->DPI_PLL_CTL0, 0x0, DPI_MASK_MCK_CLK_EN);
	hal_delay_us(1);

	//cpu_read_modify_write(&dpi_dev_map->DPI_PLL_CTL1, 0x0, 0x20000);
	cpu_read_modify_write(&dpi_dev_map->DPI_PLL_CTL1, 0x0, DPI_MASK_CLK_OE);
	hal_delay_us(1);

	//cpu_read_modify_write(&dpi_dev_map->DPI_PLL_CTL0, 0xFFF, 0xFFE);
	cpu_read_modify_write(&dpi_dev_map->DPI_PLL_CTL0, 0xFFF, DPI_MASK_MCK_CLK_EN);
	hal_delay_us(1);

	//cpu_read_modify_write(&dpi_dev_map->DPI_PLL_CTL1, 0x70000, 0x70000);
	cpu_read_modify_write(&dpi_dev_map->DPI_PLL_CTL1, 0x7 << DPI_SHIFT_CLK_OE, DPI_MASK_CLK_OE);
	hal_delay_us(1);

	/*Wait PLL ready*/
	while ((HAL_READ32(REG_SYS_DDRPHY_CTRL, 0x0) & 0x8) != 0x8);

	/*Enable PAD*/
	cpu_read_modify_write((volatile uint32_t *)REG_SYS_DDRPHY_CTRL, 0x2, 0x2);

	//Set 0 OCD force value = 0x18(89ohm)
	//Set 1 OCD force value = 0x11(120ohm)
	//Set 2 OCD force vaule = 0x0A(200ohm||200ohm)
	//Set 3 OCD force value = 0x22(50ohm)
	//0x26 default OCD value for all Sets
	dpi_dev_map->DPI_OCDP0_SET0 = 0x220A1118;
	dpi_dev_map->DPI_OCDN0_SET0 = 0x220A1118;
	dpi_dev_map->DPI_OCDP0_SET1 = 0x220A1118;
	dpi_dev_map->DPI_OCDN0_SET1 = 0x220A1118;

	//Set 0 ODT force value = 0x00(DEFAULT)
	dpi_dev_map->DPI_ODT_TTCP0_SET0 = 0x00000000;
	dpi_dev_map->DPI_ODT_TTCN0_SET0 = 0x00000000;
	dpi_dev_map->DPI_ODT_TTCP0_SET1 = 0x00000000;
	dpi_dev_map->DPI_ODT_TTCN0_SET1 = 0x00000000;

	/*DQ/DQS/CLK ODT Selection, 目前選擇Set 0*/
	dpi_dev_map->DPI_DQ_ODT_SEL_0 = 0xFFFF0000;
	dpi_dev_map->DPI_DQ_ODT_SEL_1 = 0xFFFF0000;
	dpi_dev_map->DPI_DQS_P_ODT_SEL_0 = 0xFFFF0000;
	dpi_dev_map->DPI_DQS_P_ODT_SEL_1 = 0xFFFF0000;
	dpi_dev_map->DPI_DQS_N_ODT_SEL_0 = 0xFFFF0000;
	dpi_dev_map->DPI_DQS_N_ODT_SEL_1 = 0xFFFF0000;
	dpi_dev_map->DPI_CLK_ODT_SEL = 0xFFFF0000;

	/*DQ/DQS/CLK OCD Selection目前選擇Set 0*/
	dpi_dev_map->DPI_DQ_OCD_SEL_0 = 0xFFFF0000;
	dpi_dev_map->DPI_DQ_OCD_SEL_1 = 0xFFFF0000;
	dpi_dev_map->DPI_DQS_OCD_SEL_0 = 0x00000000;
	dpi_dev_map->DPI_DQS_OCD_SEL_1 = 0x00000000;
	dpi_dev_map->DPI_CK_OCD_SEL = 0x00000000;

	/*CA PAD OCD Selection目前選擇Set 1, 可以修改force value調整檔位(0x18)*/
	if (ddr3_new_process) { //20 nm ddr3l requires stronger CKE driving.
		dpi_dev_map->DPI_CKE_OCD_SEL = 0xFFFF3333;

	} else {
		dpi_dev_map->DPI_CKE_OCD_SEL = 0xFFFF1111;
	}

	dpi_dev_map->DPI_ADR_OCD_SEL = 0x11FF11FF;
	dpi_dev_map->DPI_OCD_SEL_0 = 0x11111111;
	dpi_dev_map->DPI_OCD_SEL_1 = 0x11111111;
	dpi_dev_map->DPI_OCD_SEL_2 = 0x11111111;
	dpi_dev_map->DPI_OCD_SEL_3 = 0x11111111;
	dpi_dev_map->DPI_OCD_SEL_4 = 0x11111111;
	dpi_dev_map->DPI_OCD_SEL_5 = 0x11111111;
	dpi_dev_map->DPI_OCD_SEL_6 = 0x11111111;
	dpi_dev_map->DPI_OCD_SEL_7 = 0x11111111;
	dpi_dev_map->DPI_OCD_SEL_8 = 0x11111111;
	dpi_dev_map->DPI_ODT_SEL_0 = 0xFFFFFF22;
	dpi_dev_map->DPI_CKE_ODT_SEL = 0xFFFF1111;
	dpi_dev_map->DPI_ADR_ODT_SEL = 0x11FF1111;

#if 0
	dram_r480_calibration(DDR_3);
	dram_zq_calibration(DDR_3);

	dpi_dev_map->DPI_DQ_ODT_SEL_0 = 0xFFFF4444;
	dpi_dev_map->DPI_DQ_ODT_SEL_1 = 0xFFFF4444;
	dpi_dev_map->DPI_DQ_OCD_SEL_0 = 0xFFFF0000;
	dpi_dev_map->DPI_DQ_OCD_SEL_1 = 0xFFFF0000;
	dpi_dev_map->DPI_DQS_P_ODT_SEL_0 = 0xffff0011;
	dpi_dev_map->DPI_DQS_P_ODT_SEL_1 = 0xffff0011;
	dpi_dev_map->DPI_DQS_N_ODT_SEL_0 = 0xffff1100;
	dpi_dev_map->DPI_DQS_N_ODT_SEL_1 = 0xffff1100;
	dpi_dev_map->DPI_DQS_OCD_SEL_0 = 0x0;
	dpi_dev_map->DPI_DQS_OCD_SEL_1 = 0x0;
	dpi_dev_map->DPI_CKE_OCD_SEL = 0xffff3333;
	dpi_dev_map->DPI_ADR_OCD_SEL = 0x33ff33ff;
	dpi_dev_map->DPI_CK_OCD_SEL = 0x55555555;
	dpi_dev_map->DPI_OCD_SEL_0 = 0x22222222;
	dpi_dev_map->DPI_OCD_SEL_1 = 0x22222222;
	dpi_dev_map->DPI_OCD_SEL_2 = 0x22222222;
	dpi_dev_map->DPI_OCD_SEL_3 = 0x22222222;
	dpi_dev_map->DPI_OCD_SEL_4 = 0x22222222;
	dpi_dev_map->DPI_OCD_SEL_5 = 0x22222222;
	dpi_dev_map->DPI_OCD_SEL_6 = 0x22222222;
	dpi_dev_map->DPI_OCD_SEL_7 = 0x22222222;
	dpi_dev_map->DPI_OCD_SEL_8 = 0x22222222;
	dpi_dev_map->DPI_ODT_SEL_0 = 0xffffff33;
	dpi_dev_map->DPI_CKE_ODT_SEL = 0xffff2222;
	dpi_dev_map->DPI_ADR_ODT_SEL = 0x22ff2277;
	dpi_dev_map->DPI_CLK_ODT_SEL = 0x00003333;
#endif
	cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_2, 0x10C00000, 0x10C00000);
	cpu_read_modify_write(&dpi_dev_map->DPI_CRT_CTL, 0x0, 0x40800);
	cpu_read_modify_write(&dpi_dev_map->DPI_CRT_CTL, 0x0, 0x4);

	/*Update immediately*/
	cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x2 << DPI_SHIFT_FW_SET_MODE, DPI_MASK_FW_SET_MODE);////CHUN-CHI
	dpi_dev_map->DPI_CMD_ADR_PH = 0x7C055555;

	dpi_dev_map->DPI_DQ_IO_CTL_1 &= ~DPI_BIT_DM_IE_FRC_EN;
	dpi_dev_map->DPI_DQ_IO_CTL_1_1 &= ~DPI_BIT_DM_IE_FRC_EN;

	cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x1002, 0x203F03);
	cpu_read_modify_write(&dpi_dev_map->DPI_READ_CTRL_0_0, 0x9 << DPI_SHIFT_TM_DQS_EN_FTUN, DPI_MASK_TM_DQS_EN_FTUN | DPI_MASK_TM_DQS_EN);////CHUN-CHI
	cpu_read_modify_write(&dpi_dev_map->DPI_READ_CTRL_0_1, 0x9 << DPI_SHIFT_TM_DQS_EN_FTUN, DPI_MASK_TM_DQS_EN_FTUN | DPI_MASK_TM_DQS_EN);////CHUN-CHI
	dpi_dev_map->DPI_READ_CTRL1 = 0x6;

	if (ddr3_new_process) {
		/*DCK*/
		cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI0, 0xD << DPI_SHIFT_POST_PI_SEL0, DPI_MASK_POST_PI_SEL0);
		dpi_dev_map->DPI_PLL_CTL1 |= (1 << 0);

		/*DCS*/
		cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI2, 0x17 << DPI_SHIFT_POST_PI_SEL10, DPI_MASK_POST_PI_SEL10);
		dpi_dev_map->DPI_PLL_CTL1 |= (1 << 10);

		/*DQS0, DQS1*/
		cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI0, 0x1E << DPI_SHIFT_POST_PI_SEL2, DPI_MASK_POST_PI_SEL2);
		cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI0, 0x1D << DPI_SHIFT_POST_PI_SEL3, DPI_MASK_POST_PI_SEL3);

		/*DQ0, DQ1*/
		cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI1, 0x6 << DPI_SHIFT_POST_PI_SEL6, DPI_MASK_POST_PI_SEL6);
		cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI2, 0x5 << DPI_SHIFT_POST_PI_SEL7, DPI_MASK_POST_PI_SEL7);
	} else {
		/*DCK*/
		cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI0, 0x12 << DPI_SHIFT_POST_PI_SEL0, DPI_MASK_POST_PI_SEL0);
		dpi_dev_map->DPI_PLL_CTL1 |= (1 << 0);

		/*DCS*/
		cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI2, 0x1A << DPI_SHIFT_POST_PI_SEL10, DPI_MASK_POST_PI_SEL10);
		dpi_dev_map->DPI_PLL_CTL1 |= (1 << 10);

		/*DQS0, DQS1*/
		cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI0, 0x1 << DPI_SHIFT_POST_PI_SEL2, DPI_MASK_POST_PI_SEL2);
		cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI0, 0x0 << DPI_SHIFT_POST_PI_SEL3, DPI_MASK_POST_PI_SEL3);

		/*DQ0, DQ1*/
		cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI1, 0x9 << DPI_SHIFT_POST_PI_SEL6, DPI_MASK_POST_PI_SEL6);
		cpu_read_modify_write(&dpi_dev_map->DPI_PLL_PI2, 0x8 << DPI_SHIFT_POST_PI_SEL7, DPI_MASK_POST_PI_SEL7);
	}

	/*DQ DLY*/
	dpi_dev_map->DPI_DQ_DLY_0 = 0x88888888;
	dpi_dev_map->DPI_DQ_DLY_0_1 = 0x88888888;
	dpi_dev_map->DPI_DQ_DLY_1 = 0x888;
	dpi_dev_map->DPI_DQ_DLY_1_1 = 0x888;

	/*FW set write delay chain of data slice*/
	dpi_dev_map->DPI_DPI_CTRL_1 |= (DPI_BIT_FW_SET_WR_DLY | DPI_BIT_WRITE_EN_0);

	/*FW set read delay chain of data slice*/
	dpi_dev_map->DPI_DPI_CTRL_1 |= (DPI_BIT_FW_SET_RD_DLY | DPI_BIT_WRITE_EN_1);

	cpu_read_modify_write(&dpi_dev_map->DPI_READ_CTRL_0_0, 0x8 << DPI_SHIFT_DQS_RC1IN_DLY_SEL, DPI_MASK_DQS_RC1IN_DLY_SEL);
	cpu_read_modify_write(&dpi_dev_map->DPI_READ_CTRL_0_1, 0x9 << DPI_SHIFT_DQS_RC1IN_DLY_SEL, DPI_MASK_DQS_RC1IN_DLY_SEL);

	/*Pick the center point of available windows*/
	dpi_dev_map->DPI_DQS_IN_DLY0 = 0x10101010;
	dpi_dev_map->DPI_DQS_IN_DLY0_1 = 0x10101010;

	dpi_dev_map->DPI_DQS_IN_DLY1 = 0x10101010;
	dpi_dev_map->DPI_DQS_IN_DLY1_1 = 0x10101010;

	dpi_dev_map->DPI_DQS_IN_DLY2 = 0x10101010;
	dpi_dev_map->DPI_DQS_IN_DLY2_1 = 0x10101010;

	dpi_dev_map->DPI_DQS_IN_DLY3 = 0x10101010;
	dpi_dev_map->DPI_DQS_IN_DLY3_1 = 0x10101010;

	dpi_dev_map->DPI_DPI_CTRL_1 |= (DPI_BIT_FW_SET_RD_DLY | DPI_BIT_WRITE_EN_1);
	cpu_read_modify_write(&dpi_dev_map->DPI_DPI_CTRL_0, 0x0 << DPI_SHIFT_FW_SET_MODE, DPI_MASK_FW_SET_MODE);
}
#endif

void hal_dram_scramble_ctrl(u8 ctrl)
{
	if (ctrl == ENABLE) {
		/*Set scramble seed, all DRAM region will be scrambled*/
		HAL_WRITE32(DRAMC_FUNC_BASE_ADDR, 0x270, 0x6231DCE5);

		/*Set SCE Start base address for scramble*/
		HAL_WRITE32(DRAMC_FUNC_BASE_ADDR, 0x200, 0);

		/*Set SCE End base address for scramble*/
		HAL_WRITE32(DRAMC_FUNC_BASE_ADDR, 0x204, 0xFFFFF000);

		/*Enable scramble function*/
		HAL_WRITE32(DRAMC_FUNC_BASE_ADDR, 0x204, 0xFFFFF001);
	} else {
		/*Disable scramble function*/
		HAL_WRITE32(DRAMC_FUNC_BASE_ADDR, 0x204, 0xFFFFF000);
	}

}

void hal_init_dram()
{
	u32 chip_id = 0;
	u8 dram_type = 0;
	u8 dram_vendor = 0;
	u8 dram_package_type = 0;
	DRAMC_TypeDef *dramc_dev = (DRAMC_TypeDef *) DRAMC_CTRL_BASE_ADDR;
	DRAM_FE_TypeDef *dram_ft_dev = (DRAM_FE_TypeDef *) DRAMC_FRONTEND_BASE_ADDR;
	SYSON_S_TypeDef *syson_s = SYSON_S;
	AON_TypeDef *aon = AON;

	/*Initialize clock & function control*/
	syson_s->SYSON_S_REG_SYS_LPDDR1_CTRL = 0;
	syson_s->SYSON_S_REG_SYS_DDRPHY_CTRL = 0;


	/*Enable clock & function, PAD is not enabled yet*/
	syson_s->SYSON_S_REG_SYS_LPDDR1_CTRL = SYSON_S_BIT_HS_LPDDR1_EN | SYSON_S_BIT_HS_LPDDR1_CLK_EN;
	syson_s->SYSON_S_REG_SYS_DDRPHY_CTRL = SYSON_S_BIT_HS_DDRPHY_CRT_RST | SYSON_S_BIT_DDRPHY_RBUS_EN | SYSON_S_BIT_DDRPHY_VCCON | SYSON_S_BIT_HS_DDRPHY_RBUS_CLK_EN
										   | SYSON_S_BIT_HS_DDRPHY_CRT_CLK_EN;

#if CONFIG_PXP || SIMU_DDR_PXP_INIT_FLOW_EN // PXP , asic simu run flow
	/*PXP*/
#if DRAM_TYPE_DDR2
	dbg_printf("DRAM_TYPE is DDR2.\r\n");
	dram_type = DDR_2;
#else
	dbg_printf("DRAM_TYPE is DDR3L.\r\n");
	dram_type = DDR_3;
#endif
#else
	/*ASIC*/
	hal_sys_get_chip_id(&chip_id);
	aon->AON_REG_AON_FAST_RESUME = chip_id;

#if IS_CUT_TEST(CONFIG_CHIP_VER)
	/*Test Chip*/
	if (((chip_id >> 16) & 0x3) == 0x3) {
		dbg_printf("DRAM_TYPE is DDR2.\r\n");
		dram_type = DDR_2;
	} else {
		dbg_printf("DRAM_TYPE is DDR3L.\r\n");
		dram_type = DDR_3;
	}
#else

	/*MP Chip*/
	if (((chip_id >> 16) & 0x3) == 0x3) {
		/*Keep bit 4 & bit 5 settings*/
		if ((((chip_id >> 2) & 0x3) == 0x3)
			|| (((chip_id >> 2) & 0x3) == 0x0)) {
			if (((chip_id >> 4) & 0x3) == 0x0) {
				rxi316_ddr2_info_m.dev = &rxi316_ddr2_dev_64MB;
				(rxi316_ddr2_info_m.dramc_info)->bus_addr_bit = &ddr2_bus_addr_remap_info_64MB;
				dbg_printf("DRAM_TYPE is DDR2 64MB.\r\n");
			} else {
				dbg_printf("DRAM_TYPE is DDR2 128MB.\r\n");
			}
		} else if (((chip_id >> 2) & 0x3) == 0x1) {
			rxi316_ddr2_info_m.dev = &rxi316_ddr2_dev_64MB;
			(rxi316_ddr2_info_m.dramc_info)->bus_addr_bit = &ddr2_bus_addr_remap_info_64MB;
			dbg_printf("DRAM_TYPE is DDR2 64MB.\r\n");
		} else {
			dbg_printf("DRAM_TYPE is DDR2 128MB.\r\n");
		}

		dram_type = DDR_2;
	} else {
		if ((((chip_id >> 2) & 0x3) == 0x3)
			|| (((chip_id >> 2) & 0x3) == 0x0)) {
			if (((chip_id >> 4) & 0x3) == 0x2) {
				dbg_printf("DRAM_TYPE is DDR3L 128MB.\r\n");
			} else {
				(rxi316_ddr3_info_m.dramc_info)->bus_addr_bit = &ddr3_bus_addr_remap_info_256MB;
				dbg_printf("DRAM_TYPE is DDR3L 256MB.\r\n");
			}
		} else {
			dbg_printf("DRAM_TYPE is DDR3L 128MB.\r\n");
		}
		dram_type = DDR_3;
	}

	if (((chip_id >> 18) & 0x3) == 0x2) {
		dram_package_type = DRAM_PACKAGE_8X11;
	} else {
		dram_package_type = DRAM_PACKAGE_10X10;
	}

	if (((chip_id >> 28) & 0x3) == 0x2) {
		dram_vendor = DRAM_VENDOR_ESMT;
	} else {
		dram_vendor = DRAM_VENDOR_WINBOND;
	}

	ddr3_new_process = 0;
	if (dram_type == DDR_3) {
		if (dram_vendor == DRAM_VENDOR_WINBOND) {
			if (dram_package_type == DRAM_PACKAGE_8X11)  {
				ddr3_new_process = 1;
			}
		}
	}
#endif
#endif

	if (dram_type == DDR_2) {
		hal_ddr2_phy_init(1000000 / 533);

		hal_dramc_perf_tune(dramc_dev, &rxi316_ddr2_info_m);

		hal_dramc_init(dramc_dev, &rxi316_ddr2_info_m);
	} else {
		hal_ddr3_phy_init(1000000 / 533);

		hal_dramc_perf_tune(dramc_dev, &rxi316_ddr3_info_m);

		hal_dramc_init(dramc_dev, &rxi316_ddr3_info_m);
	}

	hal_dramc_ftend_init(dram_ft_dev);
}


