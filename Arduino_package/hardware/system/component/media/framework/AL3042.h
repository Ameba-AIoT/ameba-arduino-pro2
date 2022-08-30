#ifndef __AL3042_H__
#define __AL3042_H__

#ifdef CONFIG_PLATFORM_8195BHP

// Peripheral configurations
#define MBED_I2C_MTR_SDA              PG_8//EVB:PH_2 //Doorbell:PG_8	
#define MBED_I2C_MTR_SCL              PG_9//EVB:PH_3 //Doorbell:PG_9	

#define MBED_I2C_SLAVE_ADDR           0x1c//ap1522d:0x10	//AL3042:1c
#define MBED_I2C_BUS_CLK              100000  //hz

#ifndef BIT
#define BIT(n)                   (1<<n)
#endif

#define AL3042_POWER_ON              	(1)
#define AL3042_POWER_DOWN            	(0)
#define AL3042_ENABLE                	(1)
#define AL3042_DISABLE               	(0)

// AL3042 Registers
#define AL3042_MODE_ENABLE              (0x00)
#define AL3042_INT_STATUS				(0x01)
#define AL3042_INT_CONTROL				(0x02)
#define AL3042_WAIT_TIME				(0X06)
#define AL3042_GAIN						(0X07)
#define AL3042_ALS_PERSISTENCE			(0x08)
#define AL3042_ATIME					(0x0A)
#define AL3042_INT_LOW_THD_LOW			(0x1A)
#define AL3042_INT_LOW_THD_HIGH			(0x1B)
#define AL3042_INT_HIGH_THD_LOW			(0x1C)
#define AL3042_INT_HIGH_THD_HIGH		(0x1D)
#define AL3042_CH0_ADATA_L				(0x2C)
#define AL3042_CH0_ADATA_H				(0x2D)
#define AL3042_CH1_ADATA_L				(0x2E)
#define AL3042_CH1_ADATA_H				(0x2F)
#define AL3042_LDATA_L					(0x30)
#define AL3042_LDATA_H					(0x31)
#define AL3042_LOW_THRESHOLD_L			(0x32)
#define AL3042_LOW_THRESHOLD_H			(0x33)
#define AL3042_HIGH_THRESHOLD_L			(0x32)
#define AL3042_HIGH_THRESHOLD_H			(0x33)
#define AL3042_LUM_COE					(0x40)

//AL3042 System Control(Register: 0x00)
#define AL3042_DIS_EN_ALS				(0x00)
#define AL3042_EN_ALS					(0x01)
#define AL3042_SWRST					(0x04)
//#define AP1522D_MODE_PD               	(BIT(1))
//#define AP1522D_MODE_TEM_EN           	(BIT(2))
//#define AP1522D_MODE_H_SELB           	(BIT(4))

//AL3042 Interrupt Flag(Register: 0x01)
#define AL3042_INT_FLAG_AINT			(BIT(0))
#define AL3042_INT_FLAG_ERRFLAG			(BIT(5))
#define AL3042_INT_FLAG_PORINT			(BIT(7))

#define AL3042_POWER_ON_RESET_CLEAR		(0x00)& AL3042_INT_FLAG_PORINT
#define AL3042_POWER_ON_RESET_OCCUR		(0x01)& AL3042_INT_FLAG_PORINT
#define AL3042_ERRFLAG_DATA_VALID		(0x00)& AL3042_INT_FLAG_ERRFLAG
#define AL3042_ERRFLAG_DATA_INVALID		(0x10)& AL3042_INT_FLAG_ERRFLAG
#define AL3042_AINT_CLEAR				(0x00)& AL3042_INT_FLAG_AINT
#define AL3042_AINT_TRIGGER				(0x40)& AL3042_INT_FLAG_AINT

//AL3042 Interrupt Control(Register: 0x02)
#define AL3042_ALS_SUSPEND_DIS			0x00
#define AL3042_ALS_SUSPEND_EN			0x01

//AL3042 Waiting Time(Register: 0x06)
#define AL3042_WAIT_TIME_UINT_NUM		(0x0F)
#define AL3042_WAIT_TIME_UINT_20MS		(0x00)
#define AL3042_WAIT_TIME_UINT_2MS		(0x80)

//AL3042 ALS Control(Register: 0x07)
#define AL3042_AGAIN_1X               	(0x00)
#define AL3042_AGAIN_4X               	(0x01)
#define AL3042_AGAIN_20X               	(0x02)
#define AL3042_AGAIN_125X               (0x03)
#define AL3042_AXGAIN_HALF				(0x04) //0 : Half sensing area x1
#define AL3042_AXGAIN_FULL				(0x05) //1 : Full sensing area x2

//AL3042 ALS persistence(Register: 0x08)
#define AL3042_APERS					(0x01)

//AL3042 ALS Time(Register: 0x0A)
#define AL3042_ALS_TIME					(0xFF)  //ALS max count = min(65535,1024*(AL3042_ALS_TIME+1)-1)
//TALS = 2.87 + 2.390*(ATIME+1)ms

#define AL3042_SUCCESS						0
#define AL3042_ERR_I2C						-1
#define AL3042_ERR_STATUS					-3
#define AL3042_ERR_SETUP_FAILURE			-4
#define AL3042_ERR_GETGSENSORDATA			-5
#define AL3042_ERR_IDENTIFICATION			-6

#endif

void al3042_init(void);
int al3042_get_ALS(void);

#endif // #ifdef CONFIG_PLATFORM_8195BHP