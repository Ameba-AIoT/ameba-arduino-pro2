#ifndef _AMBIENT_LIGHT_SENSOR_H_
#define _AMBIENT_LIGHT_SENSOR_H_

//#define QFN_128_BOARD
// Peripheral configurations
#ifdef QFN_128_BOARD
#define MBED_I2C_MTR_SDA              PIN_E4
#define MBED_I2C_MTR_SCL              PIN_E3
#else
#define MBED_I2C_MTR_SDA              PIN_E4
#define MBED_I2C_MTR_SCL              PIN_E3
#endif

#define MBED_I2C_SLAVE_ADDR           0x10
#define MBED_I2C_BUS_CLK              100000  //hz

#ifndef BIT
#define BIT(n)                   (1<<n)
#endif

#define AP1522D_POWER_ON              (1)
#define AP1522D_POWER_DOWN            (0)
#define AP1522D_ENABLE                (1)
#define AP1522D_DISABLE               (0)

// AP1522D Registers
#define AP1522D_REG_MODE              (0x03)
#define AP1522D_REG_TIG_SEL           (0x04)
#define AP1522D_REG_GAIN              (0x05)
#define AP1522D_REG_STATUS            (0x20)
#define AP1522D_REG_SENSE_N_DARK_BASE (0x21)

#define AP1522D_MODE_RESET            (BIT(0))
#define AP1522D_MODE_PD               (BIT(1))
#define AP1522D_MODE_TEM_EN           (BIT(2))
#define AP1522D_MODE_H_SELB           (BIT(4))

#define AP1522D_GAIN_1X               (0x00)
#define AP1522D_GAIN_2X               (0x01)
#define AP1522D_GAIN_4X               (0x02)
#define AP1522D_GAIN_8X               (0x03)
#define AP1522D_GAIN_16X              (0x04)
#define AP1522D_GAIN_32X              (0x05)
#define AP1522D_GAIN_64X              (0x06)
#define AP1522D_GAIN_128X             (0x07)

#define AP1522D_TIG_1P536MS           (0x00)
#define AP1522D_TIG_3P072MS           (0x01)
#define AP1522D_TIG_50MS              (0x20)
#define AP1522D_TIG_100MS             (0x41)
#define AP1522D_TIG_200MS             (0x82)
#define AP1522D_TIG_400MS             (0xFF)

#define AP1522D_STATUS_R_RDY          (BIT(0))

void  ap1522d_init();
void  ap1522d_power(int poweron);
void  ap1522d_reset(int enable);

int   ap1522d_ready();

void  ap1522d_get_sense_n_dark(unsigned int *sense, unsigned int *dark);

void  ap1522d_set_gain(int gain);
int   ap1522d_get_gain();

void  ap1522d_set_tig(float tig);
float ap1522d_get_tig();

int   ap1522d_calculate_lux(unsigned int sense, unsigned int dark, int gain, float tig);


#endif