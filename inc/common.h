#ifndef __COMMON_H
#define __COMMON_H

#include <stddef.h>
#include <stdbool.h>
#include "typedef.h"
#include "arm_cortex_m4f.h"

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

#endif