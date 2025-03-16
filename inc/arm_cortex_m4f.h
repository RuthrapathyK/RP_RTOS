#ifndef __ARM_CORTEX_M4F__
#define __ARM_CORTEX_M4F__

#include "typedef.h"

typedef struct{
    volatile uint32_t STCTRL;
    volatile uint32_t STRELOAD;
    volatile uint32_t STCURRENT;
}SysTick_Type;
typedef struct{
    volatile uint32_t EN0;
    volatile uint32_t EN1;
    volatile uint32_t EN2;
    volatile uint32_t EN3;
    volatile uint32_t EN4;
    volatile uint32_t Reserved_1[27];
    volatile uint32_t DIS0;
    volatile uint32_t DIS1;
    volatile uint32_t DIS2;
    volatile uint32_t DIS3;
    volatile uint32_t DIS4;
    volatile uint32_t Reserved_2[27];
    volatile uint32_t PEND0;
    volatile uint32_t PEND1;
    volatile uint32_t PEND2;
    volatile uint32_t PEND3;
    volatile uint32_t PEND4;
    volatile uint32_t Reserved_3[27];
    volatile uint32_t UNPEND0;
    volatile uint32_t UNPEND1;
    volatile uint32_t UNPEND2;
    volatile uint32_t UNPEND3;
    volatile uint32_t UNPEND4;
    volatile uint32_t Reserved_4[27];
    volatile uint32_t ACTIVE0;
    volatile uint32_t ACTIVE1;
    volatile uint32_t ACTIVE2;
    volatile uint32_t ACTIVE3;
    volatile uint32_t ACTIVE4;
    volatile uint32_t Reserved_5[59];
    volatile uint32_t PRI0;
    volatile uint32_t PRI1;
    volatile uint32_t PRI2;
    volatile uint32_t PRI3;
    volatile uint32_t PRI4;
    volatile uint32_t PRI5;
    volatile uint32_t PRI6;
    volatile uint32_t PRI7;
    volatile uint32_t PRI8;
    volatile uint32_t PRI9;
    volatile uint32_t PRI10;
    volatile uint32_t PRI11;
    volatile uint32_t PRI12;
    volatile uint32_t PRI13;
    volatile uint32_t PRI14;
    volatile uint32_t PRI15;
    volatile uint32_t PRI16;
    volatile uint32_t PRI17;
    volatile uint32_t PRI18;
    volatile uint32_t PRI19;
    volatile uint32_t PRI20;
    volatile uint32_t PRI21;
    volatile uint32_t PRI22;
    volatile uint32_t PRI23;
    volatile uint32_t PRI24;
    volatile uint32_t PRI25;
    volatile uint32_t PRI26;
    volatile uint32_t PRI27;
    volatile uint32_t PRI28;
    volatile uint32_t PRI29;
    volatile uint32_t PRI30;
    volatile uint32_t PRI31;
    volatile uint32_t PRI32;
    volatile uint32_t PRI33;
    volatile uint32_t PRI34;
    volatile uint32_t Reserved_6[669];
    volatile uint32_t SWTRIG;
} NVIC_Type;


#define CORTEX_PERIPHERAL_BASE  (0xE000E000UL)
#define SYSTICK_BASE            (CORTEX_PERIPHERAL_BASE + 0x010UL)
#define NVIC_BASE               (CORTEX_PERIPHERAL_BASE + 0x100UL)

#define SysTick ((SysTick_Type *)SYSTICK_BASE)
#define NVIC ((NVIC_Type *)NVIC_BASE)

#endif