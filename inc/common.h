#ifndef __COMMON_H
#define __COMMON_H

#include <stddef.h>
#include <stdbool.h>
#include "typedef.h"
#include "arm_cortex_m4f.h"
#include "TM4C123GH6PM.h"

#define PENDSV_TRIGGER  SCB->INTCTRL |= 1<<28
#define PENDSV_CLEAR    SCB->INTCTRL |= 1<<27
#define SYSTICK_TRIGGER SCB->INTCTRL |= 1<<26
#define SYSTICK_CLEAR   SCB->INTCTRL |= 1<<25

#define ASSERT(x) { \
  if(!(x)) \
    while(1){ \
      __asm("BKPT");\
    }\
}


inline void __attribute__((always_inline))__enable_irq(void)
{
  __asm("CPSIE I");
}

inline void __attribute__((always_inline))__disable_irq(void)
{
  __asm("CPSID I");
}


#define TESTPIN_ON  GPIOB->DATA_Bits[8] = 0xFF
#define TESTPIN_OFF GPIOB->DATA_Bits[8] = 0x00

void TestPin_Init(void);

#endif