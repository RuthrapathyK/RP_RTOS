#include "common.h"

#define MAX_VECTOR 155u

// Changing these MACROS will have impact in Linker Script
#define SRAM_START_ADDRESS 0x20000000u
#define STACK_SIZE_IN_BYTES 0x400u

/**
 * @brief If there is no Handler in Application and Interrupt is hit, this will hold the processor from further execution
 * 
 */
__attribute__ ((weak)) void Reserved(void)
{
    ASSERT(0);
}

/**
 * @brief Upon the exception occurrence the Processor will be in infinite loop. This will avoid unintended execution from memory
 * 
 */
void NMI_handler(void)
{
    ASSERT(0);
}
/**
 * @brief Upon the exception occurrence the Processor will be in infinite loop. This will avoid unintended execution from memory
 * 
 */
void HardFault_handler(void)
{
    ASSERT(0);
}
/**
 * @brief Upon the exception occurrence the Processor will be in infinite loop. This will avoid unintended execution from memory
 * 
 */
void MemManage_handler(void)
{
    ASSERT(0);
}
/**
 * @brief Upon the exception occurrence the Processor will be in infinite loop. This will avoid unintended execution from memory
 * 
 */
void BusFault_handler(void)
{
    ASSERT(0);
}
/**
 * @brief Upon the exception occurrence the Processor will be in infinite loop. This will avoid unintended execution from memory
 * 
 */
void UsageFault_handler(void)
{
    ASSERT(0);
}
/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void SVCall_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void DebugMonitor_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void PendSV_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void SysTick_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void GPIO_Port_A_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void GPIO_Port_B_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void GPIO_Port_C_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void GPIO_Port_D_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void GPIO_Port_E_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void UART0_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void UART1_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void SSI0_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void I2C0_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void PWM0_Fault_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void PWM0_Generator_0_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void PWM0_Generator_1_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void PWM0_Generator_2_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void QEI0_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void ADC0_Sequence_0_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void ADC0_Sequence_1_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void ADC0_Sequence_2_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void ADC0_Sequence_3_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void Watchdog_Timers_0_1_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void Timer_0A_16_32_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void Timer_0B_16_32_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void Timer_1A_16_32_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void Timer_1B_16_32_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void Timer_2A_16_32_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void Timer_2B_16_32_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void Analog_Comparator_0_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void Analog_Comparator_1_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void System_Control_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void Flash_and_EEPROM_Control_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void GPIO_Port_F_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void UART2_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void SSI1_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void Timer_3A_16_32_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void Timer_3B_16_32_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void I2C1_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void QEI1_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void CAN0_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void CAN1_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void Hibernation_Module_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void USB_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void PWM_Generator_3_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void uDMA_Software_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void uDMA_Error_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void ADC1_Sequence_0_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void ADC1_Sequence_1_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void ADC1_Sequence_2_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void ADC1_Sequence_3_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void SSI2_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void SSI3_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void UART3_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void UART4_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void UART5_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void UART6_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void UART7_handler(void)
{
    ASSERT(0);
}
/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void I2C2_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void I2C3_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void Timer_4A_16_32_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void Timer_4B_16_32_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void Timer_5A_16_32_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void Timer_5B_16_32_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void Timer_0A_32_64_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void Timer_0B_32_64_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void Timer_1A_32_64_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void Timer_1B_32_64_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void Timer_2A_32_64_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void Timer_2B_32_64_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void Timer_3A_32_64_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void Timer_3B_32_64_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void Timer_4A_32_64_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void Timer_4B_32_64_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void Timer_5A_32_64_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void Timer_5B_32_64_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void System_Exception_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void PWM1_Generator_0_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void PWM1_Generator_1_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void PWM1_Generator_2_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void PWM1_Generator_3_handler(void)
{
    ASSERT(0);
}

/**
 * @brief If the Application doesnt redefine the Handler and Enables Interrupt
 *        then this will hold the processor from further execution upon interrupt
 * 
 */
__attribute__ ((weak)) void PWM1_Fault_handler(void)
{
    ASSERT(0);
}

void Reset_handler(void);
void main(void);

extern uint8_t __s_text;
extern uint8_t __e_text;
extern uint8_t __s_data;
extern uint8_t __e_data;
extern uint8_t __s_bss;
extern uint8_t __e_bss;

__attribute__ ((section (".stack_pointer"))) const uint32_t Stack_Pointer = SRAM_START_ADDRESS+STACK_SIZE_IN_BYTES;

__attribute__ ((section (".vector_table")))  void (*vector_table[MAX_VECTOR])(void) = { 
    &Reset_handler,                         
    &NMI_handler,
    &HardFault_handler,
    &MemManage_handler,
    &BusFault_handler,
    &UsageFault_handler,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &SVCall_handler,
    &DebugMonitor_handler,
    &Reserved,
    &PendSV_handler,
    &SysTick_handler,
    &GPIO_Port_A_handler,
    &GPIO_Port_B_handler,
    &GPIO_Port_C_handler,
    &GPIO_Port_D_handler,
    &GPIO_Port_E_handler,
    &UART0_handler,
    &UART1_handler,
    &SSI0_handler,
    &I2C0_handler,
    &PWM0_Fault_handler,
    &PWM0_Generator_0_handler,
    &PWM0_Generator_1_handler,
    &PWM0_Generator_2_handler,
    &QEI0_handler,
    &ADC0_Sequence_0_handler,
    &ADC0_Sequence_1_handler,
    &ADC0_Sequence_2_handler,
    &ADC0_Sequence_3_handler,
    &Watchdog_Timers_0_1_handler,
    &Timer_0A_16_32_handler,
    &Timer_0B_16_32_handler,
    &Timer_1A_16_32_handler,
    &Timer_1B_16_32_handler,
    &Timer_2A_16_32_handler,
    &Timer_2B_16_32_handler,
    &Analog_Comparator_0_handler,
    &Analog_Comparator_1_handler,
    &Reserved,
    &System_Control_handler,
    &Flash_and_EEPROM_Control_handler,
    &GPIO_Port_F_handler,
    &Reserved,
    &Reserved,
    &UART2_handler,
    &SSI1_handler,
    &Timer_3A_16_32_handler,
    &Timer_3B_16_32_handler,
    &I2C1_handler,
    &QEI1_handler,
    &CAN0_handler,
    &CAN1_handler,
    &Reserved,
    &Reserved,
    &Hibernation_Module_handler,
    &USB_handler,
    &PWM_Generator_3_handler,
    &uDMA_Software_handler,
    &uDMA_Error_handler,
    &ADC1_Sequence_0_handler,
    &ADC1_Sequence_1_handler,
    &ADC1_Sequence_2_handler,
    &ADC1_Sequence_3_handler,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &SSI2_handler,
    &SSI3_handler,
    &UART3_handler,
    &UART4_handler,
    &UART5_handler,
    &UART6_handler,
    &UART7_handler,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &I2C2_handler,
    &I2C3_handler,
    &Timer_4A_16_32_handler,
    &Timer_4B_16_32_handler,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Timer_5A_16_32_handler,
    &Timer_5B_16_32_handler,
    &Timer_0A_32_64_handler,
    &Timer_0B_32_64_handler,
    &Timer_1A_32_64_handler,
    &Timer_1B_32_64_handler,
    &Timer_2A_32_64_handler,
    &Timer_2B_32_64_handler,
    &Timer_3A_32_64_handler,
    &Timer_3B_32_64_handler,
    &Timer_4A_32_64_handler,
    &Timer_4B_32_64_handler,
    &Timer_5A_32_64_handler,
    &Timer_5B_32_64_handler,
    &System_Exception_handler,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &Reserved,
    &PWM1_Generator_0_handler,
    &PWM1_Generator_1_handler,
    &PWM1_Generator_2_handler,
    &PWM1_Generator_3_handler,
    &PWM1_Fault_handler
};

void Reset_handler(void)
{
    //Initialize .data section with initial values at SRAM 
    for(uint32_t i = 0; i < (uint32_t)((uint32_t)&__e_data - (uint32_t)&__s_data); i++)
    {
        *(((uint8_t *)&__s_data) + i) = *(((uint8_t *)&__e_text) + i);
    }

    //Initialize .bss section with 0 at SRAM
    for(uint32_t i = 0; i < (uint32_t)((uint32_t)&__e_bss - (uint32_t)&__s_bss); i++)
    {
        *(((uint8_t *)&__s_bss) + i) = 0;
    }

    // Enable Hardware Floating Point Unit
    __asm("LDR.W R0, =0xE000ED88"); //CPACR is located at address 0xE000ED88
    __asm("LDR R1, [R0]"); //Read CPACR
    __asm("ORR R1, R1, #(0xF << 20)"); //Set bits 20-23 to enable CP10 and CP11 coprocessors
    __asm("STR R1, [R0]");
    __asm("DSB");
    __asm("ISB");

    // Call main
    main();
}