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

void PM_rtc_handler(void)
{
}

void PM_gpio_irq_handler(uint32_t id, gpio_irq_event event)
{
}

void PM_Gtimer_timeout_handler(uint32_t id)
{
}


PMClass::PMClass(void){};
PMClass::~PMClass(void){};

/**
  * @brief      Initializes the PowerMode settings for device, include type of the mode, wake up sources and related source settings.
  * @param      sleep_mode: DEEPSLEEP_MODE or STANDBY_MODE
                wakeup_source: for DEEPSLEEP_MODE
                               0: AON timer, 1: AON GPIO, 2: RTC
                               for STANDBY_MODE
                               0: AON timer, 1: AON GPIO, 2: RTC, 3: PON GPIO, 4: UART/Serial1, 5: Gtimer0
                retention: for DEEPSLEEP_MODE or STANDBY_MODE
                           0: off retention
                           1: on retention
                wakeup_setting: settings for different wakeup sources
                               default is 0
                               for AON timer, clock and duration, pointer to an array with clock and duration
                               for AON GPIO, pin number, 21 or 22
                               for RTC, duration, pointer to an array with day, hour, min and sec
                               for PON GPIO, pin number, 0 to 11
                               for Gtimer0, duration, in seconds
  * @retval     none
  */
void PMClass::begin(uint32_t sleep_mode, int wakeup_source, uint32_t retention, uint32_t wakeup_setting)
{
    PM_wakeup_setting = wakeup_setting;
    PM_retention_setting = retention;
    pinMode(LED_B, OUTPUT_PULLDOWN);

    if (sleep_mode == DEEPSLEEP_MODE) {
        // deepsleep with no retention
        if (retention == 0) {
            if (wakeup_source == 0) {
                PM_wakeup_source = DS_AON_TIMER;

                uint32_t *PM_Aontimer_setting = (uint32_t *)PM_wakeup_setting;
                PM_clock = PM_Aontimer_setting[0];
                PM_sleep_duration = PM_Aontimer_setting[1] * 1000 * 1000;
                // PA_2 & PA_3 default pullup, need to be set according to external circuit
                gpio_init(&PM_GPIO_1, PA_2);
                gpio_pull_ctrl(&PM_GPIO_1, PullDown);
                gpio_init(&PM_GPIO_2, PA_3);
                gpio_pull_ctrl(&PM_GPIO_2, PullDown);
            } else if (wakeup_source == 1) {
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
                    amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] DeepSlesp wakeup AON GPIO pin selection fail. \n");
                    PM_begin_check = 0;
                    return;
                }
                gpio_irq_init(&PM_GPIO_IRQ, (PinName)(g_APinDescription[PM_wakeup_setting].pinname), NULL, (uint32_t)&PM_GPIO_IRQ);
                gpio_irq_pull_ctrl(&PM_GPIO_IRQ, PullDown);
                gpio_irq_set(&PM_GPIO_IRQ, IRQ_RISE, 1);
            } else if (wakeup_source == 2) {
                PM_wakeup_source = DS_RTC;
            } else {
                amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] DeepSlesp wakeup source selection fail. \n");
                PM_begin_check = 0;
                return;
            }
            PM_begin_check = 1;
        } else if (retention == 1) {
            // deepsleep with retention
            if (wakeup_source == 0) {
                PM_wakeup_source = DS_AON_TIMER;
                uint32_t *PM_Aontimer_setting = (uint32_t *)PM_wakeup_setting;
                PM_clock = PM_Aontimer_setting[0];
                PM_sleep_duration = PM_Aontimer_setting[1] * 1000 * 1000;
                // PA_2 & PA_3 default pullup, need to be set according to external circuit
                gpio_init(&PM_GPIO_1, PA_2);
                gpio_pull_ctrl(&PM_GPIO_1, PullDown);
                gpio_init(&PM_GPIO_2, PA_3);
                gpio_pull_ctrl(&PM_GPIO_2, PullDown);
            } else if (wakeup_source == 1) {
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
                    amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] DeepSlesp wakeup AON GPIO pin selection fail. \n");
                    PM_begin_check = 0;
                    return;
                }
                gpio_irq_init(&PM_GPIO_IRQ, (PinName)(g_APinDescription[PM_wakeup_setting].pinname), NULL, (uint32_t)&PM_GPIO_IRQ);
                gpio_irq_pull_ctrl(&PM_GPIO_IRQ, PullDown);
                gpio_irq_set(&PM_GPIO_IRQ, IRQ_RISE, 1);
            } else {
                amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] DeepSlesp wakeup source selection fail. \n");
                PM_begin_check = 0;
                return;
            }
            PM_begin_check = 1;
        }
    } else if (sleep_mode == STANDBY_MODE) {
        // standby with no retention
        if (retention == 0) {
            if (wakeup_source == 0) {
                PM_wakeup_source = SLP_AON_TIMER;

                uint32_t *PM_Aontimer_setting = (uint32_t *)PM_wakeup_setting;
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
                        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] Standby wakeup AON GPIO pin selection fail. \n");
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
                    case PF_5:
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
                        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] Standby wakeup PON GPIO pin selection fail. \n");
                        PM_begin_check = 0;
                        return;
                }

                HAL_WRITE32(0x40009000, 0x18, 0x1 | HAL_READ32(0x40009000, 0x18));    // SWR 1.35V

                hal_delay_ms(5);
                gpio_irq_init(&PM_GPIO_IRQ, (PinName)(g_APinDescription[PM_wakeup_setting].pinname), PM_gpio_irq_handler, (uint32_t)&PM_GPIO_IRQ);
                gpio_irq_pull_ctrl(&PM_GPIO_IRQ, PullDown);
                gpio_irq_set(&PM_GPIO_IRQ, IRQ_RISE, 1);

                // set gpio pull control
                HAL_WRITE32(0x40009850, 0x0, 0x4f004f);    // GPIOF_1/GPIOF_0
                // HAL_WRITE32(0x40009854, 0x0, 0x8f004f); //GPIOF_3/GPIOF_2
                // HAL_WRITE32(0x40009858, 0x0, 0x4f008f); //GPIOF_5/GPIOF_4
                HAL_WRITE32(0x40009854, 0x0, (((HAL_READ32(0x40009854, 0x0)) & 0xFFFF0000) | 0x4f));        // GPIOF_2
                HAL_WRITE32(0x40009858, 0x0, (((HAL_READ32(0x40009858, 0x0)) & 0x0000FFFF) | 0x4f0000));    // GPIOF_5
                HAL_WRITE32(0x4000985c, 0x0, 0x4f004f);                                                     // GPIOF_7/GPIOF_6
                HAL_WRITE32(0x40009860, 0x0, 0x4f004f);                                                     // GPIOF_9/GPIOF_8
                HAL_WRITE32(0x40009864, 0x0, 0x4f004f);                                                     // GPIOF_11/GPIOF_10
                HAL_WRITE32(0x40009868, 0x0, 0x4f004f);                                                     // GPIOF_13/GPIOF_12
                HAL_WRITE32(0x4000986C, 0x0, 0x4f004f);                                                     // GPIOF_15/GPIOF_14
                HAL_WRITE32(0x40009870, 0x0, 0x4f004f);                                                     // GPIOF_17/GPIOF_16
                // HAL_WRITE32(0x4000Ae04, 0x0, 0x20000); //GPIOF_17(VDD_DDR_EN) INPUT MODE

                gpio_init(&PM_GPIO_1, PA_2);
                gpio_pull_ctrl(&PM_GPIO_1, PullDown);
                gpio_init(&PM_GPIO_2, PA_3);
                gpio_pull_ctrl(&PM_GPIO_2, PullDown);
            } else if (wakeup_source == 4) {
                PM_wakeup_source = SLP_UART;
                PM_clock = 1;

                HAL_WRITE32(0x40009000, 0x18, 0x1 | HAL_READ32(0x40009000, 0x18));    // SWR 1.35V
                hal_delay_ms(5);
#if 0
                //serial_init(&PM_UART, PA_2, PA_3);
                // 0:40M, 1:4M
                serial_init_arduino(&PM_UART, PA_2, PA_3, 1);
                //amb_ard_printf(ARD_LOG_INF, "\r\n[INFO] Check the 4M en %d \n ", (PM_UART.uart_adp.reserv1));
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
                HAL_WRITE32(0x40009000, 0x18, 0x1 | HAL_READ32(0x40009000, 0x18));    // SWR 1.35V
                hal_delay_ms(5);
            } else if (wakeup_source == 6) {
                // PWM TBD
            } else {
                amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] Standby wakeup source selection fail. \n");
                PM_begin_check = 0;
                return;
            }
            PM_begin_check = 2;

        } else if (retention == 1) {
            // standby with retention
            if (wakeup_source == 0) {
                PM_wakeup_source = SLP_AON_TIMER | SLP_GTIMER;

                uint32_t *PM_Aontimer_setting = (uint32_t *)PM_wakeup_setting;
                PM_clock = PM_Aontimer_setting[0];
                PM_sleep_duration = PM_Aontimer_setting[1] * 1000 * 1000;

                gpio_init(&PM_GPIO_1, PA_2);
                gpio_pull_ctrl(&PM_GPIO_1, PullDown);
                HAL_WRITE32(0x40009000, 0x18, 0x1 | HAL_READ32(0x40009000, 0x18));    // SWR 1.35V
                hal_delay_ms(5);
            } else if (wakeup_source == 1) {
                PM_wakeup_source = SLP_AON_GPIO | SLP_GTIMER;

                switch (g_APinDescription[PM_wakeup_setting].pinname) {
                    case PA_1:
                        // If user needs to use SWD pins for GPIO, disable SWD debugging to free pins
                        sys_jtag_off();
                        break;
                    case PA_2:
                    case PA_3:
                        break;
                    default:
                        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] Standby wakeup AON GPIO pin selection fail. \n");
                        PM_begin_check = 0;
                        return;
                }

                // If there is no GPIO wakeup source please set a GPIO IRQ for wake up
                // gpio_irq_init(&PM_GPIO_IRQ, (PinName)(g_APinDescription[PM_wakeup_setting].pinname), NULL, (uint32_t)&PM_GPIO_IRQ);
                gpio_irq_init(&PM_GPIO_IRQ, (PinName)(g_APinDescription[PM_wakeup_setting].pinname), PM_gpio_irq_handler, (uint32_t)&PM_GPIO_IRQ);
                gpio_irq_pull_ctrl(&PM_GPIO_IRQ, PullDown);
                gpio_irq_set(&PM_GPIO_IRQ, IRQ_RISE, 1);
                HAL_WRITE32(0x40009000, 0x18, 0x1 | HAL_READ32(0x40009000, 0x18));    // SWR 1.35V
                hal_delay_ms(5);
            } else if (wakeup_source == 2) {
                PM_wakeup_source = SLP_PON_GPIO | SLP_GTIMER;

                switch (g_APinDescription[PM_wakeup_setting].pinname) {
                    case PF_0:
                    case PF_1:
                    case PF_2:
                    // case PF_3:
                    // case PF_4:
                    case PF_5:
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
                        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] Standby wakeup PON GPIO pin selection fail. \n");
                        PM_begin_check = 0;
                        return;
                }

                HAL_WRITE32(0x40009000, 0x18, 0x1 | HAL_READ32(0x40009000, 0x18));    // SWR 1.35V

                hal_delay_ms(5);
                gpio_irq_init(&PM_GPIO_IRQ, (PinName)(g_APinDescription[PM_wakeup_setting].pinname), PM_gpio_irq_handler, (uint32_t)&PM_GPIO_IRQ);
                gpio_irq_pull_ctrl(&PM_GPIO_IRQ, PullDown);
                gpio_irq_set(&PM_GPIO_IRQ, IRQ_RISE, 1);

                // set gpio pull control
                HAL_WRITE32(0x40009850, 0x0, 0x4f004f);    // GPIOF_1/GPIOF_0
                // HAL_WRITE32(0x40009854, 0x0, 0x8f004f); //GPIOF_3/GPIOF_2
                // HAL_WRITE32(0x40009858, 0x0, 0x4f008f); //GPIOF_5/GPIOF_4
                HAL_WRITE32(0x40009854, 0x0, (((HAL_READ32(0x40009854, 0x0)) & 0xFFFF0000) | 0x4f));        // GPIOF_2
                HAL_WRITE32(0x40009858, 0x0, (((HAL_READ32(0x40009858, 0x0)) & 0x0000FFFF) | 0x4f0000));    // GPIOF_5
                HAL_WRITE32(0x4000985c, 0x0, 0x4f004f);                                                     // GPIOF_7/GPIOF_6
                HAL_WRITE32(0x40009860, 0x0, 0x4f004f);                                                     // GPIOF_9/GPIOF_8
                HAL_WRITE32(0x40009864, 0x0, 0x4f004f);                                                     // GPIOF_11/GPIOF_10
                HAL_WRITE32(0x40009868, 0x0, 0x4f004f);                                                     // GPIOF_13/GPIOF_12
                HAL_WRITE32(0x4000986C, 0x0, 0x4f004f);                                                     // GPIOF_15/GPIOF_14
                HAL_WRITE32(0x40009870, 0x0, 0x4f004f);                                                     // GPIOF_17/GPIOF_16
                // HAL_WRITE32(0x4000Ae04, 0x0, 0x20000); //GPIOF_17(VDD_DDR_EN) INPUT MODE

                gpio_init(&PM_GPIO_1, PA_2);
                gpio_pull_ctrl(&PM_GPIO_1, PullDown);
                gpio_init(&PM_GPIO_2, PA_3);
                gpio_pull_ctrl(&PM_GPIO_2, PullDown);
            } else if (wakeup_source == 3) {
                PM_wakeup_source = SLP_GTIMER;    // BIT7 bitwise BIT7 = BIT7 (SLP_GTIMER)
                PM_clock = 1;

                gpio_init(&PM_GPIO_1, PA_2);
                gpio_pull_ctrl(&PM_GPIO_1, PullDown);
                HAL_WRITE32(0x40009000, 0x18, 0x1 | HAL_READ32(0x40009000, 0x18));    // SWR 1.35V
                hal_delay_ms(5);
            } else {
                amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] Standby wakeup source selection fail. \n");
                PM_begin_check = 0;
                return;
            }
            PM_begin_check = 2;
        }
    } else {
        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] Power mode selection fail. \n");
        PM_begin_check = 0;
    }
}

/**
 * @brief      Initializes the PowerMode settings with multiple wakeup sources (bitwise).
 *             This function supports combining multiple wakeup sources using bitwise OR.
 * @param      sleep_mode: DEEPSLEEP_MODE or STANDBY_MODE
 *             wakeup_source: bitwise OR of wakeup source flags
 *                            for DEEPSLEEP_MODE: DS_AON_TIMER | DS_AON_GPIO | DS_RTC | DS_COMP
 *                            for STANDBY_MODE: SLP_AON_TIMER | SLP_AON_GPIO | SLP_RTC | etc.
 *             retention: 0: off retention, 1: on retention
 *             wakeup_settings: pointer to array of settings for each wakeup source
 *                              Index 0: DS_AON_TIMER/SLP_AON_TIMER settings (clock, duration)
 *                              Index 1: DS_AON_GPIO/SLP_AON_GPIO settings (pin number)
 *                              Index 2: DS_RTC/SLP_RTC settings (day, hour, min, sec)
 *                              Index 3: DS_COMP/SLP_COMP settings
 * @retval     none
 */
void PMClass::begin(uint32_t sleep_mode, uint32_t wakeup_source, uint32_t retention, uint32_t *wakeup_settings)
{
    PM_retention_setting = retention;
    PM_wakeup_source = wakeup_source;
    pinMode(LED_B, OUTPUT_PULLDOWN);

    // Store wakeup settings for each source
    PM_wakeup_source_count = 0;
    for (int i = 0; i < MAX_WAKEUP_SOURCES; i++) {
        PM_wakeup_settings[i] = wakeup_settings[i];
    }

    // Validate: RTC wakeup is not supported when retention is enabled
    if (retention == 1) {
        if (sleep_mode == DEEPSLEEP_MODE) {
            if (wakeup_source & DS_RTC) {
                amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] DeepSleep with retention does not support RTC wakeup. \n");
                PM_begin_check = 0;
                return;
            }
        } else if (sleep_mode == STANDBY_MODE) {
            if (wakeup_source & SLP_RTC) {
                amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] Standby with retention does not support RTC wakeup. \n");
                PM_begin_check = 0;
                return;
            }
        }
    }

    if (sleep_mode == DEEPSLEEP_MODE) {
        // Determine which pins need pull-down based on wakeup sources
        bool pull_down_pa2 = true;
        bool pull_down_pa3 = true;

        // If DS_AON_GPIO is set, check which pin is used as wakeup
        if (wakeup_source & DS_AON_GPIO) {
            uint32_t gpio_pin = wakeup_settings[1];
            if ((g_APinDescription[gpio_pin].pinname) == PA_2) {
                pull_down_pa2 = false;    // PA_2 is used as wakeup pin
            } else if ((g_APinDescription[gpio_pin].pinname) == PA_3) {
                pull_down_pa3 = false;    // PA_3 is used as wakeup pin
            } else if ((g_APinDescription[gpio_pin].pinname) == PA_1) {
                // If user needs to use SWD pins for GPIO, disable SWD debugging to free pins
                sys_jtag_off();
                // PA_1 is used, so PA_2 and PA_3 can be pulled down
            } else {
                amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] DeepSleep wakeup AON GPIO pin selection fail. \n");
                PM_begin_check = 0;
                return;
            }
            // Initialize GPIO IRQ for wakeup pin
            gpio_irq_init(&PM_GPIO_IRQ, (PinName)(g_APinDescription[gpio_pin].pinname), NULL, (uint32_t)&PM_GPIO_IRQ);
            gpio_irq_pull_ctrl(&PM_GPIO_IRQ, PullDown);
            gpio_irq_set(&PM_GPIO_IRQ, IRQ_RISE, 1);
        }

        // Apply pull-down only to pins that are not used as wakeup pins
        // PA_2 & PA_3 default pullup, need to be set according to external circuit
        if (pull_down_pa2) {
            gpio_init(&PM_GPIO_1, PA_2);
            gpio_pull_ctrl(&PM_GPIO_1, PullDown);
        }
        if (pull_down_pa3) {
            gpio_init(&PM_GPIO_2, PA_3);
            gpio_pull_ctrl(&PM_GPIO_2, PullDown);
        }

        // Process AON Timer wakeup
        if (wakeup_source & DS_AON_TIMER) {
            uint32_t *PM_Aontimer_setting = (uint32_t *)wakeup_settings[0];
            PM_clock = PM_Aontimer_setting[0];
            PM_sleep_duration = PM_Aontimer_setting[1] * 1000 * 1000;
        }

        if (wakeup_source & DS_RTC) {
            // RTC wakeup - handled in start()
            // PM_wakeup_setting = wakeup_settings[2];
        }

        if (wakeup_source & DS_COMP) {
            // COMP wakeup - handled by hardware
        }

        PM_begin_check = 1;

    } else if (sleep_mode == STANDBY_MODE) {
        // Determine which pins need pull-down based on wakeup sources
        bool pull_down_pa2 = true;
        bool pull_down_pa3 = true;

        if (wakeup_source & SLP_AON_GPIO) {
            uint32_t gpio_pin = wakeup_settings[1];
            switch (g_APinDescription[gpio_pin].pinname) {
                case PA_1:
                    sys_jtag_off();
                    break;
                case PA_2:
                    pull_down_pa2 = false;    // PA_2 is used as wakeup pin
                    break;
                case PA_3:
                    pull_down_pa3 = false;    // PA_3 is used as wakeup pin
                    break;
                default:
                    amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] Standby wakeup AON GPIO pin selection fail. \n");
                    PM_begin_check = 0;
                    return;
            }
            gpio_irq_init(&PM_GPIO_IRQ, (PinName)(g_APinDescription[gpio_pin].pinname), PM_gpio_irq_handler, (uint32_t)&PM_GPIO_IRQ);
            gpio_irq_pull_ctrl(&PM_GPIO_IRQ, PullDown);
            gpio_irq_set(&PM_GPIO_IRQ, IRQ_RISE, 1);
        }

        // Apply pull-down only to pins that are not used as wakeup pins
        // PA_2 & PA_3 default pullup, need to be set according to external circuit
        if (pull_down_pa2) {
            gpio_init(&PM_GPIO_1, PA_2);
            gpio_pull_ctrl(&PM_GPIO_1, PullDown);
        }
        if (pull_down_pa3) {
            gpio_init(&PM_GPIO_2, PA_3);
            gpio_pull_ctrl(&PM_GPIO_2, PullDown);
        }

        // Process each wakeup source bit for Standby mode
        if (wakeup_source & SLP_AON_TIMER) {
            uint32_t *PM_Aontimer_setting = (uint32_t *)wakeup_settings[0];
            PM_clock = PM_Aontimer_setting[0];
            PM_sleep_duration = PM_Aontimer_setting[1] * 1000 * 1000;
        }

        if (wakeup_source & SLP_RTC) {
            // RTC wakeup - handled in start()
        }

        if (wakeup_source & SLP_PON_GPIO) {
            uint32_t gpio_pin = wakeup_settings[1];
            switch (g_APinDescription[gpio_pin].pinname) {
                case PF_0:
                case PF_1:
                case PF_2:
                case PF_5:
                case PF_6:
                case PF_7:
                case PF_8:
                case PF_9:
                case PF_11:
                case PF_12:
                case PF_13:
                case PF_14:
                case PF_15:
                    break;
                default:
                    amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] Standby wakeup PON GPIO pin selection fail. \n");
                    PM_begin_check = 0;
                    return;
            }

            HAL_WRITE32(0x40009000, 0x18, 0x1 | HAL_READ32(0x40009000, 0x18));    // SWR 1.35V
            hal_delay_ms(5);
            gpio_irq_init(&PM_GPIO_IRQ, (PinName)(g_APinDescription[gpio_pin].pinname), PM_gpio_irq_handler, (uint32_t)&PM_GPIO_IRQ);
            gpio_irq_pull_ctrl(&PM_GPIO_IRQ, PullDown);
            gpio_irq_set(&PM_GPIO_IRQ, IRQ_RISE, 1);

            // set gpio pull control
            HAL_WRITE32(0x40009850, 0x0, 0x4f004f);
            HAL_WRITE32(0x40009854, 0x0, (((HAL_READ32(0x40009854, 0x0)) & 0xFFFF0000) | 0x4f));
            HAL_WRITE32(0x40009858, 0x0, (((HAL_READ32(0x40009858, 0x0)) & 0x0000FFFF) | 0x4f0000));
            HAL_WRITE32(0x4000985c, 0x0, 0x4f004f);
            HAL_WRITE32(0x40009860, 0x0, 0x4f004f);
            HAL_WRITE32(0x40009864, 0x0, 0x4f004f);
            HAL_WRITE32(0x40009868, 0x0, 0x4f004f);
            HAL_WRITE32(0x4000986C, 0x0, 0x4f004f);
            HAL_WRITE32(0x40009870, 0x0, 0x4f004f);
        }

        if (wakeup_source & SLP_UART) {
            PM_clock = 1;
            HAL_WRITE32(0x40009000, 0x18, 0x1 | HAL_READ32(0x40009000, 0x18));
            hal_delay_ms(5);
            Serial1.begin(115200, SERIAL_8N1, 1);
            Serial1.println("Enter Standby, wake up by Serial1");
        }

        if (wakeup_source & SLP_GTIMER) {
            PM_clock = 1;
            HAL_WRITE32(0x40009000, 0x18, 0x1 | HAL_READ32(0x40009000, 0x18));
            hal_delay_ms(5);
        }

        if (retention == 1) {
            // When retention is enabled for Standby mode, SLP_GTIMER must be added
            wakeup_source = wakeup_source | SLP_GTIMER;
            PM_wakeup_source = wakeup_source;
        }

        PM_begin_check = 2;
    } else {
        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] Power mode selection fail. \n");
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
void PMClass::start(int year, int month, int day, int hour, int min, int sec)
{
    if (PM_begin_check == 1) {
        PM_begin_check = 0;

        if (PM_retention_setting == 1) {
            SleepCG(PM_wakeup_source, PM_sleep_duration, PM_clock, PM_retention_setting);
        } else if (PM_retention_setting == 0) {
            // Check for RTC wakeup using bitwise AND (supports multiple wakeup sources)
            if (PM_wakeup_source & DS_RTC) {
                rtc.Init();
                if (year == 0) {
                    rtc.Write(0);
                } else {
                    long long initTime = rtc.SetEpoch(year, month, day, hour, min, sec);
                    rtc.Write(initTime);
                }
                // Use PM_wakeup_settings[2] if multiple wakeup sources are supported, otherwise use PM_wakeup_setting
                uint32_t rtc_setting = (PM_wakeup_settings[2] != 0) ? PM_wakeup_settings[2] : PM_wakeup_setting;
                uint32_t *PM_rtc_alarm = (uint32_t *)rtc_setting;
                rtc.EnableAlarm((PM_rtc_alarm[0] + day), (PM_rtc_alarm[1] + hour), (PM_rtc_alarm[2] + min), (PM_rtc_alarm[3] + sec), PM_rtc_handler);
            }
            DeepSleep(PM_wakeup_source, PM_sleep_duration, PM_clock);
        }
    } else if (PM_begin_check == 2) {
        PM_begin_check = 0;
        if (PM_retention_setting == 0) {
            // Check for RTC wakeup using bitwise AND (supports multiple wakeup sources)
            if (PM_wakeup_source & SLP_RTC) {
                rtc.Init();
                if (year == 0) {
                    rtc.Write(0);
                } else {
                    long long initTime = rtc.SetEpoch(year, month, day, hour, min, sec);
                    rtc.Write(initTime);
                }
                uint32_t rtc_setting = (PM_wakeup_settings[2] != 0) ? PM_wakeup_settings[2] : PM_wakeup_setting;
                uint32_t *PM_rtc_alarm = (uint32_t *)rtc_setting;
                rtc.EnableAlarm((PM_rtc_alarm[0] + day), (PM_rtc_alarm[1] + hour), (PM_rtc_alarm[2] + min), (PM_rtc_alarm[3] + sec), PM_rtc_handler);
            }
            // Check for GTimer wakeup using bitwise AND (supports multiple wakeup sources)
            if (PM_wakeup_source & SLP_GTIMER) {
                // Use the timer setting from the settings array
                uint32_t timer_duration_setting = (PM_wakeup_settings[1] != 0) ? PM_wakeup_settings[1] : PM_wakeup_setting;
                uint32_t timer_duration = timer_duration_setting;
                GTimer.begin(0, (timer_duration * 1000 * 1000), PM_Gtimer_timeout_handler, false, (uint32_t)NULL, 1);
            }
            Standby(PM_wakeup_source, PM_sleep_duration, PM_clock, PM_retention_setting);
        } else if (PM_retention_setting == 1) {
            // Check for GTimer wakeup using bitwise AND (supports multiple wakeup sources)
            if (PM_wakeup_source & SLP_GTIMER) {
                uint32_t timer_duration_setting = (PM_wakeup_settings[1] != 0) ? PM_wakeup_settings[1] : PM_wakeup_setting;
                uint32_t timer_duration = timer_duration_setting;
                GTimer.begin(0, (timer_duration * 1000 * 1000), PM_Gtimer_timeout_handler, false, (uint32_t)NULL, 1);
            }
            Standby(PM_wakeup_source, PM_sleep_duration, PM_clock, PM_retention_setting);
        }
    } else {
        amb_ard_printf(ARD_LOG_ERR, "\r\n[ERROR] Power Mode begin check fail. \n");
    }
}

void PMClass::cleanInvalidateCache(void *address, size_t size)
{
    dcache_clean_invalidate_by_addr((uint32_t *)address, size);
}

PMClass PowerMode;
