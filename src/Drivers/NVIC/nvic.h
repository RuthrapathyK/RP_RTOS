#ifndef __NVIC_H
#define __NVIC_H

#include "common.h"


typedef enum {
    GPIO_Port_A_IRQ = 0,          // 16: GPIO Port A
    GPIO_Port_B_IRQ,              // 17: GPIO Port B
    GPIO_Port_C_IRQ,              // 18: GPIO Port C
    GPIO_Port_D_IRQ,              // 19: GPIO Port D
    GPIO_Port_E_IRQ,              // 20: GPIO Port E
    UART_0_IRQ,                   // 21: UART0
    UART_1_IRQ,                   // 22: UART1
    SSI_0_IRQ,                    // 23: SSI0
    I2C_0_IRQ,                    // 24: I2C0
    PWM_0_FAULT_IRQ,              // 25: PWM0 Fault
    PWM_0_GEN_0_IRQ,              // 26: PWM0 Generator 0
    PWM_0_GEN_1_IRQ,              // 27: PWM0 Generator 1
    PWM_0_GEN_2_IRQ,              // 28: PWM0 Generator 2
    QEI_0_IRQ,                    // 29: QEI0
    ADC_0_SEQ_0_IRQ,              // 30: ADC0 Sequence 0
    ADC_0_SEQ_1_IRQ,              // 31: ADC0 Sequence 1
    ADC_0_SEQ_2_IRQ,              // 32: ADC0 Sequence 2
    ADC_0_SEQ_3_IRQ,              // 33: ADC0 Sequence 3
    WATCHDOG_IRQ,                 // 34: Watchdog Timers 0 and 1
    TIMER_0A_IRQ,                 // 35: Timer 0A
    TIMER_0B_IRQ,                 // 36: Timer 0B
    TIMER_1A_IRQ,                 // 37: Timer 1A
    TIMER_1B_IRQ,                 // 38: Timer 1B
    TIMER_2A_IRQ,                 // 39: Timer 2A
    TIMER_2B_IRQ,                 // 40: Timer 2B
    ANALOG_COMP_0_IRQ,            // 41: Analog Comparator 0
    ANALOG_COMP_1_IRQ,            // 42: Analog Comparator 1
    // 43: Reserved
    SYSTEM_CTRL_IRQ = 28,         // 44: System Control (PLL, OSC, BO)
    FLASH_CTRL_IRQ,               // 45: FLASH and EEPROM Control
    GPIO_Port_F_IRQ,              // 46: GPIO Port F
    // 47: Reserved
    // 48: Reserved
    UART_2_IRQ = 33,              // 49: UART2
    SSI_1_IRQ,                    // 50: SSI1
    TIMER_3A_IRQ,                 // 51: Timer 3A
    TIMER_3B_IRQ,                 // 52: Timer 3B
    I2C_1_IRQ,                    // 53: I2C1
    QEI_1_IRQ,                    // 54: QEI1
    CAN_0_IRQ,                    // 55: CAN0
    CAN_1_IRQ,                    // 56: CAN1
    // 57: Reserved
    // 58: Reserved
    HIBERNATE_IRQ = 43,           // 59: Hibernation Module
    USB_0_IRQ,                    // 60: USB
    PWM_0_GEN_3_IRQ,              // 61: PWM0 Generator 3
    UDMA_IRQ,                     // 62: uDMA Software
    UDMA_ERR_IRQ,                 // 63: uDMA Error
    ADC_1_SEQ_0_IRQ,              // 64: ADC1 Sequence 0
    ADC_1_SEQ_1_IRQ,              // 65: ADC1 Sequence 1
    ADC_1_SEQ_2_IRQ,              // 66: ADC1 Sequence 2
    ADC_1_SEQ_3_IRQ,              // 67: ADC1 Sequence 3
    // 68: Reserved
    // 69: Reserved
    // 70: Reserved
    // 71: Reserved
    // 72: Reserved
    SSI_2_IRQ = 57,               // 73: SSI2
    SSI_3_IRQ,                    // 74: SSI3
    UART_3_IRQ,                   // 75: UART3
    UART_4_IRQ,                   // 76: UART4
    UART_5_IRQ,                   // 77: UART5
    UART_6_IRQ,                   // 78: UART6
    UART_7_IRQ,                   // 79: UART7
    // 80: Reserved
    // 81: Reserved
    // 82: Reserved
    // 83: Reserved
    I2C_2_IRQ = 68,               // 84: I2C2
    I2C_3_IRQ,                    // 85: I2C3
    TIMER_4A_IRQ,                 // 86: Timer 4A
    TIMER_4B_IRQ,                 // 87: Timer 4B
    // 88-107: Reserved
    TIMER_5A_IRQ = 92,            // 108: Timer 5A
    TIMER_5B_IRQ,                 // 109: Timer 5B
    WTIMER_0A_IRQ,                // 110: Wide Timer 0A
    WTIMER_0B_IRQ,                // 111: Wide Timer 0B
    WTIMER_1A_IRQ,                // 112: Wide Timer 1A
    WTIMER_1B_IRQ,                // 113: Wide Timer 1B
    WTIMER_2A_IRQ,                // 114: Wide Timer 2A
    WTIMER_2B_IRQ,                // 115: Wide Timer 2B
    WTIMER_3A_IRQ,                // 116: Wide Timer 3A
    WTIMER_3B_IRQ,                // 117: Wide Timer 3B
    WTIMER_4A_IRQ,                // 118: Wide Timer 4A
    WTIMER_4B_IRQ,                // 119: Wide Timer 4B
    WTIMER_5A_IRQ,                // 120: Wide Timer 5A
    WTIMER_5B_IRQ,                // 121: Wide Timer 5B
    SYSTEM_EXCEPT_IRQ,            // 122: System Exception (imprecise)
    // 123-149: Reserved
    PWM_1_GEN_0_IRQ = 134,        // 150: PWM1 Generator 0
    PWM_1_GEN_1_IRQ,              // 151: PWM1 Generator 1
    PWM_1_GEN_2_IRQ,              // 152: PWM1 Generator 2
    PWM_1_GEN_3_IRQ,              // 153: PWM1 Generator 3
    PWM_1_FAULT_IRQ,              // 154: PWM1 Fault
    NVIC_IRQ_MAX
} NVIC_Interrupt_e;

/**
 * @brief Enables the given interrupt in the NVIC.
 * 
 * This function sets the corresponding bit in the appropriate NVIC ENx register
 * to enable the interrupt specified by intr_num.
 * 
 * @param intr_num Interrupt number (see NVIC_Interrupt_e)
 */
void NVIC_enableInterrupt(NVIC_Interrupt_e intr_num);

/**
 * @brief Disables the given interrupt in the NVIC.
 * 
 * This function sets the corresponding bit in the appropriate NVIC DISx register
 * to disable the interrupt specified by intr_num.
 * 
 * @param intr_num Interrupt number (see NVIC_Interrupt_e)
 */
void NVIC_disableInterrupt(NVIC_Interrupt_e intr_num);

/**
 * @brief Enables all interrupts globally.
 * 
 * This function clears the PRIMASK register bit to enable all unmasked interrupts
 * in the processor by executing the CPSIE I instruction.
 */
__INLINE__ void __enable_irq(void)
{
  __asm("CPSIE I");
}

/**
 * @brief Disables all interrupts globally.
 * 
 * This function sets the PRIMASK register bit to disable all interrupts
 * in the processor by executing the CPSID I instruction.
 */
__INLINE__ void __disable_irq(void)
{
  __asm("CPSID I");
}

#endif