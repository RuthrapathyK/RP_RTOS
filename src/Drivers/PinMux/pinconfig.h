#ifndef __PINCONFIG_H
#define __PINCONFIG_H

#include "common.h"

typedef enum{
    Port_PA,
    Port_PB,
    Port_PC,
    Port_PD,
    Port_PE,
    Port_PF,
    Port_Max
}Pincfg_Port_e;


// PA pins
#define PA0_GPIO      0   // GPIO
#define PA0_U0RX      1   // UART0 RX
#define PA0_CAN1RX    8   // CAN1 RX

#define PA1_GPIO      0   // GPIO
#define PA1_U0TX      1   // UART0 TX
#define PA1_CAN1TX    8   // CAN1 TX

#define PA2_GPIO      0   // GPIO
#define PA2_SSI0CLK   2   // SSI0 CLK

#define PA3_GPIO      0   // GPIO
#define PA3_SSI0FSS   2   // SSI0 FSS

#define PA4_GPIO      0   // GPIO
#define PA4_SSI0RX    2   // SSI0 RX

#define PA5_GPIO      0   // GPIO
#define PA5_SSI0TX    2   // SSI0 TX

#define PA6_GPIO      0   // GPIO
#define PA6_I2C1SCL   3   // I2C1 SCL
#define PA6_M1PWM2    5   // M1 PWM2

#define PA7_GPIO      0   // GPIO
#define PA7_I2C1SDA   3   // I2C1 SDA
#define PA7_M1PWM3    5   // M1 PWM3

// PB pins
#define PB0_GPIO            0   // GPIO
#define PB0_U1RX            1   // UART1 RX
#define PB0_T2CCP0          7   // Timer2 CCP0
#define PB0_ANALOG_USB0ID   16    // USB0ID

#define PB1_GPIO            0   // GPIO
#define PB1_U1TX            1   // UART1 TX
#define PB1_T2CCP1          7   // Timer2 CCP1
#define PB1_ANALOG_USB0VBUS 16    // USB0VBUS

#define PB2_GPIO      0   // GPIO
#define PB2_I2C0SCL   3   // I2C0 SCL
#define PB2_T3CCP0    7   // Timer3 CCP0

#define PB3_GPIO      0   // GPIO
#define PB3_I2C0SDA   3   // I2C0 SDA
#define PB3_T3CCP1    7   // Timer3 CCP1

#define PB4_GPIO          0   // GPIO
#define PB4_SSI2CLK       2   // SSI2 CLK
#define PB4_M0PWM2        4   // PWM Module 0 PWM2
#define PB4_T1CCP0        7   // Timer1 CCP0
#define PB4_CAN0RX        8   // CAN0RX
#define PB4_ANALOG_AIN10  16    // AIN10

#define PB5_GPIO         0   // GPIO
#define PB5_SSI2FSS      2   // SSI2 FSS
#define PB5_M0PWM3       4   // PWM Module 0 PWM3
#define PB5_T1CCP1       7   // Timer1 CCP1
#define PB5_CAN0TX       8   // CAN0TX
#define PB5_ANALOG_AIN11 16    // AIN11

#define PB6_GPIO      0   // GPIO
#define PB6_SSI2RX    2   // SSI2 RX
#define PB6_M0PWM0    4   // PWM Module 0 PWM0
#define PB6_T0CCP0    7   // Timer0 CCP0

#define PB7_GPIO      0   // GPIO
#define PB7_SSI2TX    2   // SSI2 TX
#define PB7_M0PWM1    4   // PWM Module 0 PWM1
#define PB7_T0CCP1    7   // Timer0 CCP1

// PC pins
#define PC0_GPIO        0   // GPIO
#define PC0_TCK_SWCLK   1   // TCK_SWCLK
#define PC0_T4CCP0      7   // T4CCP0

#define PC1_GPIO        0   // GPIO
#define PC1_TMS_SWDIO   1   // TMS_SWDIO
#define PC1_T4CCP1      7   // T4CCP0

#define PC2_GPIO      0   // GPIO
#define PC2_TDI       1   // TDI
#define PC2_T5CCP0    7   // T4CCP0

#define PC3_GPIO        0   // GPIO
#define PC3_TDO_SWO     1   // TDI
#define PC3_T5CCP1      7   // T4CCP0

#define PC4_GPIO         0   // GPIO
#define PC4_U4RX         1   // UART4 RX
#define PC4_U1RX         2   // UART1 RX
#define PC4_M0PWM6       4   // PWM Module 0 PWM6
#define PC4_IDX1         6   // QEI1 Index
#define PC4_WT0CCP0      7   // WT0CCP0
#define PC4_U1RTS        8   // U1RTS
#define PC4_ANALOG_C1_N  16    // C1-

#define PC5_GPIO        0   // GPIO
#define PC5_U4TX        1   // UART4 TX
#define PC5_U1TX        2   // UART1 TX
#define PC5_M0PWM7      4   // PWM Module 0 PWM7
#define PC5_PhA1        6   // QEI1 PhA
#define PC5_WT0CCP1     7   // WT0CCP0
#define PC5_U1CTS       8   // U1CTS
#define PC5_ANALOG_C1_P 16    // C1+

#define PC6_GPIO          0   // GPIO
#define PC6_U3RX          1   // UART3 RX
#define PC6_PhB1          6   // QEI1 PhB
#define PC6_WT1CCP0       7   // WT0CCP0
#define PC6_USB0EPEN      8   // USB0EPEN
#define PC6_ANALOG_C0_P   16    // C0+

#define PC7_GPIO        0   // GPIO
#define PC7_U3TX        1   // UART3 TX
#define PC7_WT1CCP1     7   // WT0CCP0
#define PC7_USB0PFLT    8   // USB0PFLT
#define PC7_ANALOG_C0_N 16    // C0+

// PD pins
#define PD0_GPIO        0   // GPIO
#define PD0_SSI3CLK     1   // SSI3 CLK
#define PD0_SSI1CLK     2   // SSI1 CLK
#define PD0_I2C3SCL     3   // I2C3 SCL
#define PD0_M0PWM6      4   // PWM Module 0 PWM6
#define PD0_M1PWM0      5   // PWM Module 1 PWM0
#define PD0_WT2CCP0     7   // WT2CCP0
#define PD0_ANALOG_AIN7 16    // AIN7

#define PD1_GPIO        0   // GPIO
#define PD1_SSI3FSS     1   // SSI3 FSS
#define PD1_SSI1FSS     2   // SSI1 FSS
#define PD1_I2C3SDA     3   // I2C3 SDA
#define PD1_M0PWM7      4   // PWM Module 0 PWM7
#define PD1_M1PWM1      5   // PWM Module 1 PWM1
#define PD1_WT2CCP1     7   // WT2CCP1
#define PD1_ANALOG_AIN6 16    // AIN6

#define PD2_GPIO        0   // GPIO
#define PD2_SSI3RX      1   // SSI3 RX
#define PD2_SSI1RX      2   // SSI3 RX
#define PD2_M0FAULT0    4   // PWM Module 0 Fault
#define PD2_WT3CCP0     7   // WT2CCP1
#define PD2_USB0EPEN    8   // WT2CCP1
#define PD2_ANALOG_AIN5 16    // AIN6

#define PD3_GPIO        0   // GPIO
#define PD3_SSI3TX      1   // SSI3 TX
#define PD3_SSI1TX      2   // SSI3 TX
#define PD3_IDX0        6   // PWM Module 1 PWM3
#define PD3_WT3CCP1     7   // WT2CCP1
#define PD3_USB0PFLT    8   // WT2CCP1
#define PD3_ANALOG_AIN4 16    

#define PD4_GPIO      0   // GPIO
#define PD4_U6RX      1   // UART6 RX
#define PD4_WT4CCP0   7   // Wide Timer0 CCP0
#define PD4_ANALOG_USB0DM 16 

#define PD5_GPIO      0   // GPIO
#define PD5_U6TX      1   // UART6 TX
#define PD5_WT4CCP1   7   // Wide Timer0 CCP1
#define PD5_ANALOG_USB0DP 16 

#define PD6_GPIO      0   // GPIO
#define PD6_U2RX      1   // UART2 RX
#define PD6_M0FAULT0  4
#define PD6_PhA0      6
#define PD6_WT5CCP0   7   // Wide Timer1 CCP0

#define PD7_GPIO      0   // GPIO
#define PD7_U2TX      1   // UART2 TX
#define PD7_PhB0      6
#define PD7_WT5CCP1   7   // Wide Timer1 CCP1
#define PD7_NMI       8

// PE pins
#define PE0_GPIO      0   // GPIO
#define PE0_U7RX      1   // UART7 RX
#define PE0_ANALOG_AIN3 16

#define PE1_GPIO      0   // GPIO
#define PE1_U7TX      1   // UART7 TX
#define PE1_ANALOG_AIN2 16

#define PE2_GPIO        0   // GPIO
#define PE2_ANALOG_AIN1 16

#define PE3_GPIO        0   // GPIO
#define PE3_ANALOG_AIN0 16

#define PE4_GPIO        0   // GPIO
#define PE4_U5RX        1   // UART5 RX
#define PE4_I2C2SCL     3
#define PE4_M0PWM4      4   // PWM Module 0 PWM4
#define PE4_M1PWM2      5
#define PE4_CAN0RX      8   
#define PE4_ANALOG_AIN9 16

#define PE5_GPIO        0   // GPIO
#define PE5_U5TX        1   // UART5 RX
#define PE5_I2C2SDA     3
#define PE5_M0PWM5      4   // PWM Module 0 PWM4
#define PE5_M1PWM3      5
#define PE5_CAN0TX      8   
#define PE5_ANALOG_AIN8 16

// PF pins
#define PF0_GPIO      0   // GPIO
#define PF0_U1RTS     1   // UART1 RTS
#define PF0_SSI1RX    2   // SSI1 RX
#define PF0_CAN0RX    3   // CAN0 RX
#define PF0_M1PWM4    5   // PWM Module 1 PWM4
#define PF0_PhA0      6
#define PF0_T0CCP0    7   // Timer0 CCP0
#define PF0_NMI       8   
#define PF0_C0o       9

#define PF1_GPIO      0   // GPIO
#define PF1_U1CTS     1   // UART1 CTS
#define PF1_SSI1TX    2   // SSI1 TX
#define PF1_M1PWM5    5   // PWM Module 1 PWM5
#define PF1_PhB0      6
#define PF1_T0CCP1    7   // Timer0 CCP1
#define PF1_C1o       9
#define PF1_TRD1      10

#define PF2_GPIO      0   // GPIO
#define PF2_SSI1CLK   2   // SSI1 CLK
#define PF2_M0FAULT0  4
#define PF2_M1PWM6    5   // PWM Module 1 PWM6
#define PF2_T1CCP0    7   // Timer1 CCP0
#define PF2_TRD0      10

#define PF3_GPIO        0   // GPIO
#define PF3_SSI1FSS     2   // SSI1 FSS
#define PF3_CAN0TX      3
#define PF3_M1PWM7      5   // PWM Module 1 PWM7
#define PF3_T1CCP1      7   // Timer1 CCP1
#define PF3_TRCLK       10

#define PF4_GPIO        0   // GPIO
#define PF4_M1FAULT0    5   // PWM Module 1 Fault
#define PF4_IDX0        6   // QEI0 Index
#define PF4_T2CCP0      7   // Timer2 CCP0
#define PF4_USB0EPEN    8


#define PORTPIN_ANALOG_FUNCTION 16
#define PORTPIN_GPIO_FUNCTION   0
#define PORTPIN_MAX_FUNCTIONALITY 17

/**
 * @brief Configures a pin's function for a given GPIO port.
 *
 * This function enables the clock for the selected port, maps the port base address,
 * and configures the pin as GPIO, analog, or alternate function according to 'func'.
 * For alternate functions, it sets the AFSEL and PCTL registers appropriately.
 *
 * @param port GPIO port (Port_PA, Port_PB, ..., Port_PF)
 * @param pin  Pin number (0-7)
 * @param func Function selector (GPIO, analog, or alternate function number)
 */
void Pin_Config(Pincfg_Port_e port, uint8_t pin, uint8_t func);

#endif