#ifndef __COMMON_H
#define __COMMON_H

#include <stddef.h>
#include <stdbool.h>
#include "typedef.h"

#define ASSERT(x) do{ \
  if(!(x)) \
    while(1){ \
      __asm("BKPT");\
    }\
}while(0)


inline void __attribute__((always_inline))__enable_irq(void)
{
  __asm("CPSIE I");
}

inline void __attribute__((always_inline))__disable_irq(void)
{
  __asm("CPSID I");
}

#endif