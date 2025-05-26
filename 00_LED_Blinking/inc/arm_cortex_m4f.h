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

typedef struct {
    volatile uint32_t CPUID;
    volatile uint32_t INTCTRL;
    volatile uint32_t VTABLE;
    volatile uint32_t APINT;
    volatile uint32_t SYSCTRL;
    volatile uint32_t CFGCTRL;
    volatile uint32_t SYSPRI1;
    volatile uint32_t SYSPRI2;
    volatile uint32_t SYSPRI3;
    volatile uint32_t SYSHNDCTRL;
    volatile uint32_t FAULTSTAT;
    volatile uint32_t HFAULTSTAT;
    volatile uint32_t Reserved_1;
    volatile uint32_t MMADDR;
    volatile uint32_t FAULTADDR;
}SCB_Type;
typedef struct {
    volatile uint32_t TYPE;
    volatile uint32_t CTRL;
    volatile uint32_t NUMBER;
    volatile uint32_t BASE;
    volatile uint32_t ATTR;
    volatile uint32_t BASE1;
    volatile uint32_t ATTR1;
    volatile uint32_t BASE2;
    volatile uint32_t ATTR2;
    volatile uint32_t BASE3;
    volatile uint32_t ATTR3;
} MPU_Type;

typedef struct {
    volatile uint32_t FPCC;
    volatile uint32_t FPCA;
    volatile uint32_t FPDSC;
} FPU_Type;
typedef struct {
    volatile uint32_t ACTLR;
}SCB2_Type;

typedef struct 
{
    volatile uint32_t CPAC;
}FPU2_Type;

#define CORTEX_PERIPHERAL_BASE  (0xE000E000UL)
#define SYSTICK_BASE            (CORTEX_PERIPHERAL_BASE + 0x010UL)
#define NVIC_BASE               (CORTEX_PERIPHERAL_BASE + 0x100UL)
#define SCB_BASE                (CORTEX_PERIPHERAL_BASE + 0xD00UL)
#define SCB2_BASE               (CORTEX_PERIPHERAL_BASE + 0x008UL)
#define MPU_BASE                (CORTEX_PERIPHERAL_BASE + 0xD90UL)
#define FPU_BASE                (CORTEX_PERIPHERAL_BASE + 0xF34UL)
#define FPU2_BASE               (CORTEX_PERIPHERAL_BASE + 0xD88UL)

#define SysTick ((SysTick_Type *)SYSTICK_BASE)
#define NVIC    ((NVIC_Type *)NVIC_BASE)
#define SCB     ((SCB_Type *)SCB_BASE)
#define SCB2    ((SCB2_Type *)SCB2_BASE)
#define MPU     ((MPU_Type *)MPU_BASE)
#define FPU     ((FPU_Type *)FPU_BASE)
#define FPU2    ((FPU2_Type *)FPU2_BASE)

#endif