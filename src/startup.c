#include "typedef.h"

#define MAX_VECTOR 155u

// Changing these MACROS will have impact in Linker Script
#define SRAM_START_ADDRESS 0x20000000u
#define STACK_SIZE_IN_BYTES 0x400u

// Prototypes

__attribute__ ((weak)) void Reserved(void);

__attribute__ ((weak)) void Reset_handler(void);
__attribute__ ((weak)) void NMI_handler(void);
__attribute__ ((weak)) void HardFault_handler(void);
__attribute__ ((weak)) void MemManage_handler(void);
__attribute__ ((weak)) void BusFault_handler(void);
__attribute__ ((weak)) void UsageFault_handler(void);

__attribute__ ((weak)) void SVCall_handler(void);
__attribute__ ((weak)) void DebugMonitor_handler(void);

__attribute__ ((weak)) void PendSV_handler(void);
__attribute__ ((weak)) void SysTick_handler(void);
__attribute__ ((weak)) void GPIO_Port_A_handler(void);
__attribute__ ((weak)) void GPIO_Port_B_handler(void);
__attribute__ ((weak)) void GPIO_Port_C_handler(void);
__attribute__ ((weak)) void GPIO_Port_D_handler(void);
__attribute__ ((weak)) void GPIO_Port_E_handler(void);
__attribute__ ((weak)) void UART0_handler(void);
__attribute__ ((weak)) void UART1_handler(void);
__attribute__ ((weak)) void SSI0_handler(void);
__attribute__ ((weak)) void I2C0_handler(void);
__attribute__ ((weak)) void PWM0_Fault_handler(void);
__attribute__ ((weak)) void PWM0_Generator_0_handler(void);
__attribute__ ((weak)) void PWM0_Generator_1_handler(void);
__attribute__ ((weak)) void PWM0_Generator_2_handler(void);
__attribute__ ((weak)) void QEI0_handler(void);
__attribute__ ((weak)) void ADC0_Sequence_0_handler(void);
__attribute__ ((weak)) void ADC0_Sequence_1_handler(void);
__attribute__ ((weak)) void ADC0_Sequence_2_handler(void);
__attribute__ ((weak)) void ADC0_Sequence_3_handler(void);
__attribute__ ((weak)) void Watchdog_Timers_0_1_handler(void);
__attribute__ ((weak)) void Timer_0A_16_32_handler(void);
__attribute__ ((weak)) void Timer_0B_16_32_handler(void);
__attribute__ ((weak)) void Timer_1A_16_32_handler(void);
__attribute__ ((weak)) void Timer_1B_16_32_handler(void);
__attribute__ ((weak)) void Timer_2A_16_32_handler(void);
__attribute__ ((weak)) void Timer_2B_16_32_handler(void);
__attribute__ ((weak)) void Analog_Comparator_0_handler(void);
__attribute__ ((weak)) void Analog_Comparator_1_handler(void);

__attribute__ ((weak)) void System_Control_handler(void);
__attribute__ ((weak)) void Flash_and_EEPROM_Control_handler(void);
__attribute__ ((weak)) void GPIO_Port_F_handler(void);

__attribute__ ((weak)) void UART2_handler(void);
__attribute__ ((weak)) void SSI1_handler(void);
__attribute__ ((weak)) void Timer_3A_16_32_handler(void);
__attribute__ ((weak)) void Timer_3B_16_32_handler(void);
__attribute__ ((weak)) void I2C1_handler(void);
__attribute__ ((weak)) void QEI1_handler(void);
__attribute__ ((weak)) void CAN0_handler(void);
__attribute__ ((weak)) void CAN1_handler(void);

__attribute__ ((weak)) void Hibernation_Module_handler(void);
__attribute__ ((weak)) void USB_handler(void);
__attribute__ ((weak)) void PWM_Generator_3_handler(void);
__attribute__ ((weak)) void uDMA_Software_handler(void);
__attribute__ ((weak)) void uDMA_Error_handler(void);
__attribute__ ((weak)) void ADC1_Sequence_0_handler(void);
__attribute__ ((weak)) void ADC1_Sequence_1_handler(void);
__attribute__ ((weak)) void ADC1_Sequence_2_handler(void);
__attribute__ ((weak)) void ADC1_Sequence_3_handler(void);

__attribute__ ((weak)) void SSI2_handler(void);
__attribute__ ((weak)) void SSI3_handler(void);
__attribute__ ((weak)) void UART3_handler(void);
__attribute__ ((weak)) void UART4_handler(void);
__attribute__ ((weak)) void UART5_handler(void);
__attribute__ ((weak)) void UART6_handler(void);
__attribute__ ((weak)) void UART7_handler(void);

__attribute__ ((weak)) void I2C2_handler(void);
__attribute__ ((weak)) void I2C3_handler(void);
__attribute__ ((weak)) void Timer_4A_16_32_handler(void);
__attribute__ ((weak)) void Timer_4B_16_32_handler(void);

__attribute__ ((weak)) void Timer_5A_16_32_handler(void);
__attribute__ ((weak)) void Timer_5B_16_32_handler(void);
__attribute__ ((weak)) void Timer_0A_32_64_handler(void);
__attribute__ ((weak)) void Timer_0B_32_64_handler(void);
__attribute__ ((weak)) void Timer_1A_32_64_handler(void);
__attribute__ ((weak)) void Timer_1B_32_64_handler(void);
__attribute__ ((weak)) void Timer_2A_32_64_handler(void);
__attribute__ ((weak)) void Timer_2B_32_64_handler(void);
__attribute__ ((weak)) void Timer_3A_32_64_handler(void);
__attribute__ ((weak)) void Timer_3B_32_64_handler(void);
__attribute__ ((weak)) void Timer_4A_32_64_handler(void);
__attribute__ ((weak)) void Timer_4B_32_64_handler(void);
__attribute__ ((weak)) void Timer_5A_32_64_handler(void);
__attribute__ ((weak)) void Timer_5B_32_64_handler(void);
__attribute__ ((weak)) void System_Exception_handler(void);

__attribute__ ((weak)) void PWM1_Generator_0_handler(void);
__attribute__ ((weak)) void PWM1_Generator_1_handler(void);
__attribute__ ((weak)) void PWM1_Generator_2_handler(void);
__attribute__ ((weak)) void PWM1_Generator_3_handler(void);
__attribute__ ((weak)) void PWM1_Fault_handler(void);

void main(void);

extern uint8_t __s_text;
extern uint8_t __e_text;
extern uint8_t __s_data;
extern uint8_t __e_data;
extern uint8_t __s_bss;
extern uint8_t __e_bss;


__attribute__ ((section (".vector_table"))) uint32_t * vector_table[MAX_VECTOR] = {
    (uint32_t *)SRAM_START_ADDRESS+STACK_SIZE_IN_BYTES, 
    (uint32_t *)&Reset_handler,                         
    (uint32_t *)&NMI_handler,
    (uint32_t *)&HardFault_handler,
    (uint32_t *)&MemManage_handler,
    (uint32_t *)&BusFault_handler,
    (uint32_t *)&UsageFault_handler,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&SVCall_handler,
    (uint32_t *)&DebugMonitor_handler,
    (uint32_t *)&Reserved,
    (uint32_t *)&PendSV_handler,
    (uint32_t *)&SysTick_handler,
    (uint32_t *)&GPIO_Port_A_handler,
    (uint32_t *)&GPIO_Port_B_handler,
    (uint32_t *)&GPIO_Port_C_handler,
    (uint32_t *)&GPIO_Port_D_handler,
    (uint32_t *)&GPIO_Port_E_handler,
    (uint32_t *)&UART0_handler,
    (uint32_t *)&UART1_handler,
    (uint32_t *)&SSI0_handler,
    (uint32_t *)&I2C0_handler,
    (uint32_t *)&PWM0_Fault_handler,
    (uint32_t *)&PWM0_Generator_0_handler,
    (uint32_t *)&PWM0_Generator_1_handler,
    (uint32_t *)&PWM0_Generator_2_handler,
    (uint32_t *)&QEI0_handler,
    (uint32_t *)&ADC0_Sequence_0_handler,
    (uint32_t *)&ADC0_Sequence_1_handler,
    (uint32_t *)&ADC0_Sequence_2_handler,
    (uint32_t *)&ADC0_Sequence_3_handler,
    (uint32_t *)&Watchdog_Timers_0_1_handler,
    (uint32_t *)&Timer_0A_16_32_handler,
    (uint32_t *)&Timer_0B_16_32_handler,
    (uint32_t *)&Timer_1A_16_32_handler,
    (uint32_t *)&Timer_1B_16_32_handler,
    (uint32_t *)&Timer_2A_16_32_handler,
    (uint32_t *)&Timer_2B_16_32_handler,
    (uint32_t *)&Analog_Comparator_0_handler,
    (uint32_t *)&Analog_Comparator_1_handler,
    (uint32_t *)&Reserved,
    (uint32_t *)&System_Control_handler,
    (uint32_t *)&Flash_and_EEPROM_Control_handler,
    (uint32_t *)&GPIO_Port_F_handler,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&UART2_handler,
    (uint32_t *)&SSI1_handler,
    (uint32_t *)&Timer_3A_16_32_handler,
    (uint32_t *)&Timer_3B_16_32_handler,
    (uint32_t *)&I2C1_handler,
    (uint32_t *)&QEI1_handler,
    (uint32_t *)&CAN0_handler,
    (uint32_t *)&CAN1_handler,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Hibernation_Module_handler,
    (uint32_t *)&USB_handler,
    (uint32_t *)&PWM_Generator_3_handler,
    (uint32_t *)&uDMA_Software_handler,
    (uint32_t *)&uDMA_Error_handler,
    (uint32_t *)&ADC1_Sequence_0_handler,
    (uint32_t *)&ADC1_Sequence_1_handler,
    (uint32_t *)&ADC1_Sequence_2_handler,
    (uint32_t *)&ADC1_Sequence_3_handler,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&SSI2_handler,
    (uint32_t *)&SSI3_handler,
    (uint32_t *)&UART3_handler,
    (uint32_t *)&UART4_handler,
    (uint32_t *)&UART5_handler,
    (uint32_t *)&UART6_handler,
    (uint32_t *)&UART7_handler,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&I2C2_handler,
    (uint32_t *)&I2C3_handler,
    (uint32_t *)&Timer_4A_16_32_handler,
    (uint32_t *)&Timer_4B_16_32_handler,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Timer_5A_16_32_handler,
    (uint32_t *)&Timer_5B_16_32_handler,
    (uint32_t *)&Timer_0A_32_64_handler,
    (uint32_t *)&Timer_0B_32_64_handler,
    (uint32_t *)&Timer_1A_32_64_handler,
    (uint32_t *)&Timer_1B_32_64_handler,
    (uint32_t *)&Timer_2A_32_64_handler,
    (uint32_t *)&Timer_2B_32_64_handler,
    (uint32_t *)&Timer_3A_32_64_handler,
    (uint32_t *)&Timer_3B_32_64_handler,
    (uint32_t *)&Timer_4A_32_64_handler,
    (uint32_t *)&Timer_4B_32_64_handler,
    (uint32_t *)&Timer_5A_32_64_handler,
    (uint32_t *)&Timer_5B_32_64_handler,
    (uint32_t *)&System_Exception_handler,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&Reserved,
    (uint32_t *)&PWM1_Generator_0_handler,
    (uint32_t *)&PWM1_Generator_1_handler,
    (uint32_t *)&PWM1_Generator_2_handler,
    (uint32_t *)&PWM1_Generator_3_handler,
    (uint32_t *)&PWM1_Fault_handler,
};

void Reset_handler(void)
{
    //Initialize .data section with initial values at SRAM 
    for(uint32_t i = 0; i < &__e_data - &__s_data; i++)
    {
        *(&__s_data+i) =*(&__e_text+i);
    }

    //Initialize .bss section with 0 at SRAM
    for(uint32_t i = 0; i < &__e_bss - &__s_bss; i++)
    {
        *(&__s_bss+i) = 0;
    }

    //Call main
    main();
}

