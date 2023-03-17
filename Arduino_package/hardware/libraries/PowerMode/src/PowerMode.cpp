#include "PowerMode.h"

static gpio_irq_t PM_GPIO_IRQ;
static gpio_t PM_GPIO_1;
static gpio_t PM_GPIO_2;

#if 0
//static RTCClass PM_rtc;
//static serial_t PM_UART;
//static GTimerClass PM_GTimer;

volatile char rc = 0;
static void uart_send_string(serial_t *Prt_PM_UART, char *pstr) {
    unsigned int i = 0;
    while (*(pstr + i) != 0) {
        serial_putc(Prt_PM_UART, *(pstr + i));
        i++;
    }
}

static void uart_irq(uint32_t id, SerialIrq event) {
    serial_t *Prt_PM_UART = (serial_t *)id;
    if (event == RxIrq) {
        rc = serial_getc(Prt_PM_UART);
        serial_putc(Prt_PM_UART, rc);
    }
    if ((event == TxIrq) && (rc != 0)) {
        uart_send_string(Prt_PM_UART, (char *)"\r\n8735B$ \r\n");
        rc = 0;
    }
}
#endif

void PM_rtc_handler(void) {
}

void PM_gpio_irq_handler(uint32_t id, gpio_irq_event event) {
}

void PM_Gtimer_timeout_handler(uint32_t id) {
}


PMClass::PMClass(void) {};
PMClass::~PMClass(void) {};

/**
  * @brief      Initializes the PowerMode settings for device, include type of the mode, wake up sources and related source settings.
  * @param      sleep_mode: DEEPSLEEP_MODE or STANDBY_MODE
                wakeup_source: for DEEPSLEEP_MODE
                               0: AON timer, 1: AON GPIO, 2: RTC
                               for STANDBY_MODE
                               0: AON timer, 1: AON GPIO, 2: RTC, 3: PON GPIO, 4: UART/Serial1, 5: Gtimer0
                wakeup_setting: settings for different wakeup sources
                               default is 0
                               for AON timer, clock and duration, pointer to an array with clock and duration
                               for AON GPIO, pin number, 21 or 22
                               for RTC, duration, pointer to an array with day, hour, min and sec
                               for PON GPIO, pin number, 0 to 11
                               for Gtimer0, duration, in seconds
  * @retval     none
  */
void PMClass::begin(uint32_t sleep_mode, int wakeup_source, uint32_t wakeup_setting) {
    PM_wakeup_setting = wakeup_setting;

    pinMode(LED_B, OUTPUT_PULLDOWN);

    if (sleep_mode == DEEPSLEEP_MODE) {
        // deepsleep
        if (wakeup_source == 0) {
            PM_wakeup_source = DS_AON_TIMER;

            uint32_t * PM_Aontimer_setting = (uint32_t *)PM_wakeup_setting;
            PM_clock = PM_Aontimer_setting[0];
            PM_sleep_duration = PM_Aontimer_setting[1] * 1000 * 1000;
            //PA_2 & PA_3 default pullup, need to be set according to external circuit
            gpio_init(&PM_GPIO_1, PA_2);
            gpio_pull_ctrl(&PM_GPIO_1, PullDown);
            gpio_init(&PM_GPIO_2, PA_3);
            gpio_pull_ctrl(&PM_GPIO_2, PullDown);
        } else if (wakeup_source == 1){
            PM_wakeup_source = DS_AON_GPIO;

            if ((g_APinDescription[PM_wakeup_setting].pinname) == PA_1) {
                // If user needs to use SWD pins for GPIO, disable SWD debugging to free pins
                sys_jtag_off();
                gpio_init(&PM_GPIO_1, PA_2);
                gpio_pull_ctrl(&PM_GPIO_1, PullDown);
                gpio_init(&PM_GPIO_2, PA_3);
                gpio_pull_ctrl(&PM_GPIO_2, PullDown);
            } else if ((g_APinDescription[PM_wakeup_setting].pinname) == PA_2) {
                gpio_init(&PM_GPIO_2, PA_3);
                gpio_pull_ctrl(&PM_GPIO_2, PullDown);
            } else if ((g_APinDescription[PM_wakeup_setting].pinname) == PA_3) {
                gpio_init(&PM_GPIO_1, PA_2);
                gpio_pull_ctrl(&PM_GPIO_1, PullDown);
            } else {
                printf("ERROR: DeepSlesp wakeup AON GPIO pin selection fail.    \r\n");
                PM_begin_check = 0;
                return;
            }
            gpio_irq_init(&PM_GPIO_IRQ, (PinName)(g_APinDescription[PM_wakeup_setting].pinname), NULL, (uint32_t)&PM_GPIO_IRQ);
            gpio_irq_pull_ctrl(&PM_GPIO_IRQ, PullDown);
            gpio_irq_set(&PM_GPIO_IRQ, IRQ_RISE, 1);
        } else if (wakeup_source == 2){
            PM_wakeup_source = DS_RTC;
        } else {
            printf("ERROR: DeepSlesp wakeup source selection fail.    \r\n");
            PM_begin_check = 0;
            return;
        }
        PM_begin_check = 1;
    } else if (sleep_mode == STANDBY_MODE) {
        // standby
        if (wakeup_source == 0) {
            PM_wakeup_source = SLP_AON_TIMER;

            uint32_t * PM_Aontimer_setting = (uint32_t *)PM_wakeup_setting;
            PM_clock = PM_Aontimer_setting[0];
            PM_sleep_duration = PM_Aontimer_setting[1] * 1000 * 1000;

            gpio_init(&PM_GPIO_1, PA_2);
            gpio_pull_ctrl(&PM_GPIO_1, PullDown);
        } else if (wakeup_source == 1) {
            PM_wakeup_source = SLP_AON_GPIO;

            switch (g_APinDescription[PM_wakeup_setting].pinname) {
                case PA_1:
                    // If user needs to use SWD pins for GPIO, disable SWD debugging to free pins
                    sys_jtag_off();
                    break;
                case PA_2:
                case PA_3:
                    break;
                default:
                    printf("ERROR: Standby wakeup AON GPIO pin selection fail.    \r\n");
                    PM_begin_check = 0;
                    return;
            }

            // If there is no GPIO wakeup source please set a GPIO IRQ for wake up
            // gpio_irq_init(&PM_GPIO_IRQ, (PinName)(g_APinDescription[PM_wakeup_setting].pinname), NULL, (uint32_t)&PM_GPIO_IRQ);
            gpio_irq_init(&PM_GPIO_IRQ, (PinName)(g_APinDescription[PM_wakeup_setting].pinname), PM_gpio_irq_handler, (uint32_t)&PM_GPIO_IRQ);
            gpio_irq_pull_ctrl(&PM_GPIO_IRQ, PullDown);
            gpio_irq_set(&PM_GPIO_IRQ, IRQ_RISE, 1);
        } else if (wakeup_source == 2) {
            PM_wakeup_source = SLP_RTC;
        } else if (wakeup_source == 3) {
            PM_wakeup_source = SLP_PON_GPIO;

            switch (g_APinDescription[PM_wakeup_setting].pinname) {
                case PF_0:
                case PF_1:
                case PF_2:
                // case PF_3:
                // case PF_4:
                // case PF_5:
                case PF_6:
                case PF_7:
                case PF_8:
                case PF_9:
                // case PF_10:
                case PF_11:
                case PF_12:
                case PF_13:
                case PF_14:
                case PF_15:
                // case PF_16:
                // case PF_17:
                    break;
                default:
                    printf("ERROR: Standby wakeup PON GPIO pin selection fail.    \r\n");
                    PM_begin_check = 0;
                    return;
            }

            HAL_WRITE32(0x40009000, 0x18, 0x1 | HAL_READ32(0x40009000, 0x18)); //SWR 1.35V
            hal_delay_ms(5);
            gpio_irq_init(&PM_GPIO_IRQ, (PinName)(g_APinDescription[PM_wakeup_setting].pinname), PM_gpio_irq_handler, (uint32_t)&PM_GPIO_IRQ);
            gpio_irq_pull_ctrl(&PM_GPIO_IRQ, PullDown);
            gpio_irq_set(&PM_GPIO_IRQ, IRQ_RISE, 1);

            // set gpio pull control
            HAL_WRITE32(0x40009850, 0x0, 0x4f004f); //GPIOF_1/GPIOF_0
            // HAL_WRITE32(0x40009854, 0x0, 0x8f004f); //GPIOF_3/GPIOF_2
            // HAL_WRITE32(0x40009858, 0x0, 0x4f008f); //GPIOF_5/GPIOF_4
            HAL_WRITE32(0x40009854, 0x0, (((HAL_READ32(0x40009854, 0x0))&0xFFFF0000)|0x4f));        //GPIOF_2
            HAL_WRITE32(0x40009858, 0x0, (((HAL_READ32(0x40009858, 0x0))&0x0000FFFF)|0x4f0000));    //GPIOF_5
            HAL_WRITE32(0x4000985c, 0x0, 0x4f004f); //GPIOF_7/GPIOF_6
            HAL_WRITE32(0x40009860, 0x0, 0x4f004f); //GPIOF_9/GPIOF_8
            HAL_WRITE32(0x40009864, 0x0, 0x4f004f); //GPIOF_11/GPIOF_10
            HAL_WRITE32(0x40009868, 0x0, 0x4f004f); //GPIOF_13/GPIOF_12
            HAL_WRITE32(0x4000986C, 0x0, 0x4f004f); //GPIOF_15/GPIOF_14
            HAL_WRITE32(0x40009870, 0x0, 0x4f004f); //GPIOF_17/GPIOF_16
            // HAL_WRITE32(0x4000Ae04, 0x0, 0x20000); //GPIOF_17(VDD_DDR_EN) INPUT MODE

            gpio_init(&PM_GPIO_1, PA_2);
            gpio_pull_ctrl(&PM_GPIO_1, PullDown);
            gpio_init(&PM_GPIO_2, PA_3);
            gpio_pull_ctrl(&PM_GPIO_2, PullDown);
        } else if (wakeup_source == 4) {
            PM_wakeup_source = SLP_UART;
            PM_clock = 1;

            HAL_WRITE32(0x40009000, 0x18, 0x1 | HAL_READ32(0x40009000, 0x18)); //SWR 1.35V
            hal_delay_ms(5);
#if 0
            //serial_init(&PM_UART, PA_2, PA_3);
            // 0:40M, 1:4M
            serial_init_arduino(&PM_UART, PA_2, PA_3, 1);
            //printf("Check the 4M en %d   \r\n ", (PM_UART.uart_adp.reserv1));
            serial_baud(&PM_UART, 115200);
            serial_format(&PM_UART, 8, ParityNone, 1);
            serial_irq_handler(&PM_UART, uart_irq, (uint32_t)&PM_UART);
            serial_irq_set(&PM_UART, RxIrq, 1);
            serial_irq_set(&PM_UART, TxIrq, 1);
            uart_send_string(&PM_UART, (char *)"Enter Standby, wake up by Serial1 \r\n");
#else
            Serial1.begin(115200, SERIAL_8N1, 1);
            Serial1.println("Enter Standby, wake up by Serial1");
#endif
        } else if (wakeup_source == 5) {
            PM_wakeup_source = SLP_GTIMER;
            PM_clock = 1;

            gpio_init(&PM_GPIO_1, PA_2);
            gpio_pull_ctrl(&PM_GPIO_1, PullDown);
            HAL_WRITE32(0x40009000, 0x18, 0x1 | HAL_READ32(0x40009000, 0x18)); //SWR 1.35V
            hal_delay_ms(5);
        } else if (wakeup_source == 6) {
            // PWM TBD
        } else {
            printf("ERROR: Standby wakeup source selection fail.    \r\n");
            PM_begin_check = 0;
            return;
        }
        PM_begin_check = 2;
    } else {
        printf("ERROR: Power mode selection fail.    \r\n");
        PM_begin_check = 0;
    }
}

/**
  * @brief      Start the PowerMode of device.
  * @param      Optional when wake up source is RTC. Default start time is 1970.1.1 00:00:00.
                year: Start time by year. Starts from 1900.
                month: Start time by month. 0 to 11.
                day: Start time by day. 1 to 365.
                hour: Start time by hour. 0 to 23.
                min: Start time by min. 0 to 59.
                sec: Start time by sec. 0 to 59.
  * @retval     none
  */
void PMClass::start(int year, int month, int day, int hour, int min, int sec) {
    if (PM_begin_check == 1) {
        PM_begin_check = 0;
        if (PM_wakeup_source == DS_RTC) {
            rtc.Init();
            if (year == 0) {
                rtc.Write(0);
            } else {
                long long initTime = rtc.SetEpoch(year, month, day, hour, min, sec);
                rtc.Write(initTime);
            }
            uint32_t * PM_rtc_alarm = (uint32_t *)PM_wakeup_setting;
            rtc.EnableAlarm((PM_rtc_alarm[0] + day), (PM_rtc_alarm[1] + hour), (PM_rtc_alarm[2] + min), (PM_rtc_alarm[3] + sec), PM_rtc_handler);
            //rtc_set_alarm_time(10, PM_rtc_handler);
        }
        DeepSleep(PM_wakeup_source, PM_sleep_duration, PM_clock);
    } else if (PM_begin_check == 2) {
        PM_begin_check = 0;
        if (PM_wakeup_source == SLP_RTC) {
            rtc.Init();
            if (year == 0) {
                rtc.Write(0);
            } else {
                long long initTime = rtc.SetEpoch(year, month, day, hour, min, sec);
                rtc.Write(initTime);
            }
            uint32_t * PM_rtc_alarm = (uint32_t *)PM_wakeup_setting;
            rtc.EnableAlarm((PM_rtc_alarm[0] + day), (PM_rtc_alarm[1] + hour), (PM_rtc_alarm[2] + min), (PM_rtc_alarm[3] + sec), PM_rtc_handler);
        } else if (PM_wakeup_source == SLP_GTIMER) {
            //PM_GTimer.begin(0, (PM_wakeup_setting * 1000 * 1000), PM_Gtimer_timeout_handler, false, (uint32_t)NULL, 1);
            GTimer.begin(0, (PM_wakeup_setting * 1000 * 1000), PM_Gtimer_timeout_handler, false, (uint32_t)NULL, 1);
        }
        Standby(PM_wakeup_source, PM_sleep_duration, PM_clock, 0);
    } else {
        printf("ERROR: Power Mode begin check fail.    \r\n");
    }
}

PMClass PowerMode;
