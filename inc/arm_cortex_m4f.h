#ifndef __ARM_CORTEX_M4F__
#define __ARM_CORTEX_M4F__

#include "typedef.h"

typedef struct{
    volatile uint32_t STCTRL;
    volatile uint32_t STRELOAD;
    volatile uint32_t STCURRENT;
}SysTick_Type;

#define CORTEX_PERIPHERAL_BASE  (0xE000E000UL)
#define SYSTICK_BASE            (CORTEX_PERIPHERAL_BASE + 0x010UL)

#define SysTick ((SysTick_Type *)SYSTICK_BASE)

#endif