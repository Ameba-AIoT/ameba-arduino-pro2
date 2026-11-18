#ifndef UPLOAD_SNR
#define UPLOAD_SNR 1
#endif

#include "ftl_common_api.h"
#include "tuning-server.h"
#include "VideoStream.h"

void video_set_uvcd_iq(unsigned int addr);
void video_set_uvcd_sensor(unsigned int addr);

// Tuning helper functions
void dump_buff(unsigned char *buf, int size)
{
    for (int i = 0; i < size; i++) {
        if (i > 0 && i % 16 == 0) {
            printf("\r\n");
        }
        printf("0x%02X ", buf[i]);
    }
    printf("\r\n");
}

#if UPLOAD_SNR
static char pro2_upload_id[] = "PRO2UPLOAD";
#else
enum {
    GPIO_PIN_NAME = 0,
    GPIO_DIR,
    GPIO_MODE,
    GPIO_SET_VALUE,
    GPIO_GET_VALUE,
    PWM_PIN_NAME,
    PWM_PERIOD_US,
    PWM_SET_VALUE,
    PWM_GET_VALUE,
    SET_TYPE,    // TYPE is GPIO or PWM
};

enum {
    _GPIO = 1,
    _PWM = 2,
};

#include "../hal/pwmout_api.h"    // mbed
#include "gpio_api.h"
#define MAX_DEVICES 10
static gpio_t device_gpio[MAX_DEVICES] = {0};
static pwmout_t device_pwm[MAX_DEVICES] = {0};
static unsigned char device_type[MAX_DEVICES] = {0};
#endif


void tuning_customized_get_size_cmd(void *cmd, unsigned char *reg_buf)
{
#if UPLOAD_SNR
    unsigned char *uccmd = (unsigned char *)cmd;
    if (uccmd[4] == 0xFF) {
        printf("[%s] 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X.\r\n", __FUNCTION__, uccmd[0], uccmd[1], uccmd[2], uccmd[3], uccmd[4], uccmd[5], uccmd[6], uccmd[7]);
        uint32_t *ireg_buf = (uint32_t *)reg_buf;
        *ireg_buf = strlen(pro2_upload_id);
    }

#else
    unsigned short *pwbuf = (unsigned short *)reg_buf;
    printf("[%s] ID:%d CMD:%d VALUE:%d.\r\n", __FUNCTION__, pwbuf[0], pwbuf[1], pwbuf[2]);
    if (pwbuf[0] < 0 || pwbuf[0] >= MAX_DEVICES) {
        printf("[%s] id range is 0~%d.\r\n", __FUNCTION__, MAX_DEVICES - 1);
    }
    int id = pwbuf[0];
    int cmmd = pwbuf[1];
    int val = pwbuf[2];

    switch (cmmd) {
        case GPIO_GET_VALUE:
            printf("GPIO_GET_VALUE(Size).\r\n");
            if (device_type[id] == _GPIO) {
                uint32_t *ireg_buf = (uint32_t *)reg_buf;
                *ireg_buf = 4;
            }
            break;
        case PWM_GET_VALUE:
            printf("PWM_GET_VALUE(Size).\r\n");
            if (device_type[id] == _PWM) {
                uint32_t *ireg_buf = (uint32_t *)reg_buf;
                *ireg_buf = 4;
            }
            break;

        default:
            break;
    }
#endif
}

void tuning_customized_get_cmd(void *cmd, unsigned char *reg_buf)
{
#if UPLOAD_SNR
    unsigned char *uccmd = (unsigned char *)cmd;
    if (uccmd[4] == 0xFF) {
        printf("[%s] 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X 0x%X.\r\n", __FUNCTION__, uccmd[0], uccmd[1], uccmd[2], uccmd[3], uccmd[4], uccmd[5], uccmd[6], uccmd[7]);
        memcpy(reg_buf, pro2_upload_id, strlen(pro2_upload_id));
    }
#else
    unsigned short *pwbuf = (unsigned short *)reg_buf;
    printf("[%s] ID:%d CMD:%d VALUE:%d.\r\n", __FUNCTION__, pwbuf[0], pwbuf[1], pwbuf[2]);
    if (pwbuf[0] < 0 || pwbuf[0] >= MAX_DEVICES) {
        printf("[%s] id range is 0~%d.\r\n", __FUNCTION__, MAX_DEVICES - 1);
    }
    int id = pwbuf[0];
    int cmmd = pwbuf[1];
    int val = pwbuf[2];

    switch (cmmd) {
        case GPIO_GET_VALUE:
            printf("GPIO_GET_VALUE.\r\n");
            if (device_type[id] == _GPIO) {
                uint32_t *ireg_buf = (uint32_t *)reg_buf;
                int dVal = gpio_read(&device_gpio[id]);
                *ireg_buf = dVal;
            }
            break;
        case PWM_GET_VALUE:
            printf("PWM_GET_VALUE.\r\n");
            if (device_type[id] == _PWM) {
                uint32_t *ireg_buf = (uint32_t *)reg_buf;
                float fbrightness = pwmout_read(&device_pwm[id]) * 100.0f;
                *ireg_buf = (uint32_t)fbrightness;
            }
            break;

        default:
            break;
    }
#endif
}
void tuning_customized_set_cmd(void *cmd, unsigned char *reg_buf)
{
#if UPLOAD_SNR
    struct tuning_cmd *tuningcmd = (struct tuning_cmd *)cmd;
    printf("[%s] opcode:%u status:%u addr:%lu len:%lu.\r\n", __FUNCTION__, tuningcmd->opcode, tuningcmd->status, (unsigned long)tuningcmd->addr, (unsigned long)tuningcmd->len);
    printf("[%s] Buffer.\r\n", __FUNCTION__);
    if (reg_buf[3] == 0xFE) {
        dump_buff(reg_buf, 20 * 16);

        ftl_common_write(TUNING_IQ_FW, reg_buf, tuningcmd->len);
        unsigned char *ptmp = (unsigned char *)malloc(tuningcmd->len);
        ftl_common_read(TUNING_IQ_FW, ptmp, tuningcmd->len);
        printf("IQ read-write compare: %d.\r\n", memcmp(reg_buf, ptmp, tuningcmd->len));
    } else if (reg_buf[31] == 0xFD) {
        dump_buff(reg_buf, tuningcmd->len);

        ftl_common_write(TUNING_IQ_FW + 240 * 1024, reg_buf, tuningcmd->len);
        unsigned char *ptmp = (unsigned char *)malloc(tuningcmd->len);
        ftl_common_read(TUNING_IQ_FW + 240 * 1024, ptmp, tuningcmd->len);
        printf("sensor read-write compare: %d.\r\n", memcmp(reg_buf, ptmp, tuningcmd->len));
    }

#else
    unsigned short *pwbuf = (unsigned short *)reg_buf;
    printf("[%s] ID:%d CMD:%d VALUE:%d.\r\n", __FUNCTION__, pwbuf[0], pwbuf[1], pwbuf[2]);
    if (pwbuf[0] < 0 || pwbuf[0] >= MAX_DEVICES) {
        printf("[%s] id range is 0~%d.\r\n", MAX_DEVICES - 1);
    }
    int id = pwbuf[0];
    int cmmd = pwbuf[1];
    int val = pwbuf[2];

    switch (cmmd) {
        case GPIO_PIN_NAME:
            printf("GPIO_PORT.\r\n");
            if (device_type[id] == _GPIO) {
                gpio_init(&device_gpio[id], val);
            }
            break;
        case GPIO_DIR:
            printf("GPIO_DIR.\r\n");
            if (device_type[id] == _GPIO) {
                gpio_dir(&device_gpio[id], val);
            }
            break;
        case GPIO_MODE:
            printf("GPIO_MODE.\r\n");
            if (device_type[id] == _GPIO) {
                gpio_mode(&device_gpio[id], val);
            }
            break;
        case GPIO_SET_VALUE:
            printf("GPIO_SET_VALUE.\r\n");
            if (device_type[id] == _GPIO) {
                gpio_write(&device_gpio[id], val);
            }
            break;
        case PWM_PIN_NAME:
            printf("PWM_PORT.\r\n");
            if (device_type[id] == _PWM) {
                pwmout_init(&device_pwm[id], val);
            }
            break;
        case PWM_PERIOD_US:
            printf("PWM_PERIOD_US.\r\n");
            if (device_type[id] == _PWM) {
                pwmout_period_us(&device_pwm[id], val);
            }
            break;
        case PWM_SET_VALUE:
            printf("PWM_SET_VALUE.\r\n");
            if (device_type[id] == _PWM) {
                float fbrightness = (float)val / 100.0f;
                pwmout_write(&device_pwm[id], fbrightness);
            }
            break;
        case SET_TYPE:
            printf("SET_TYPE.\r\n");
            if (val == _GPIO || val == _PWM) {
                printf("original type: %d   set type: %d.\r\n", device_type[id], val);
                device_type[id] = val;
            }
            break;

        default:
            break;
    }
#endif
}


void detect_iq_fw(int *iq_bin_start)
{
    int fw_size = 0;
    tuning_set_iq_heap(iq_bin_start);
    video_set_uvcd_iq((unsigned int)iq_bin_start);

    ftl_common_read(TUNING_IQ_FW, (u8 *)&fw_size, sizeof(int));
    int check = ((fw_size >> 24) & 0xFF);
    printf("[%s] fw_size: 0x%X   check: 0x%X.\r\n", __FUNCTION__, fw_size, check);
    fw_size &= 0x00FFFFFF;
    if (fw_size > 10 * 1024 && fw_size < TUNING_IQ_MAX_SIZE) {
        ftl_common_read(TUNING_IQ_FW, (u8 *)iq_bin_start, sizeof(int) + fw_size);
        *iq_bin_start &= 0x00FFFFFF;

        printf("[%s] fw_size: %d.\r\n", __FUNCTION__, fw_size);
        dump_buff((unsigned char *)iq_bin_start, 20 * 16);
    } else {
        printf("IQ is not in 0x%06X\r\n", TUNING_IQ_FW);
    }
}

void detect_sensor_fw(int *sensor_bin_start)
{
    int snr_drv_size = 0;

    ftl_common_read(TUNING_IQ_FW + 240 * 1024 + 28, (u8 *)&snr_drv_size, sizeof(int));
    int check = ((snr_drv_size >> 24) & 0xFF);
    printf("[%s] snr_drv_size: 0x%X   check: 0x%X.\r\n", __FUNCTION__, snr_drv_size, check);
    snr_drv_size &= 0x00FFFFFF;
    video_set_uvcd_sensor((unsigned int)sensor_bin_start);
    if (snr_drv_size > 512 && snr_drv_size < 16 * 1024 && check == 0xFD) {
        ftl_common_read(TUNING_IQ_FW + 240 * 1024, (u8 *)sensor_bin_start, 32 + snr_drv_size);
        *(sensor_bin_start + 7) &= 0x00FFFFFF;

        printf("[%s] snr_drv_size: %d.\r\n", __FUNCTION__, snr_drv_size);
        dump_buff((unsigned char *)sensor_bin_start, snr_drv_size);
    } else {
        printf("Sensor driver is not in 0x%06X\r\n", TUNING_IQ_FW + 240 * 1024);
    }
}
