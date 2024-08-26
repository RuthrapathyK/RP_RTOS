#ifndef __TIMER_HH
#define __TIMER_HH
#include "typedef.h"

/****************************************FUNCTION PROTOTYPES**********************************************/

/**
 * @brief The function is used to initialize the TIMER 0 in one-shot downcounting modes.
 *        This will also initialize the TIMER 0 in concatenation mode (ie. as a 32bit Timer)
 *        Note: Prescalar is NA when the timer is configured as 32bit
 * 
 */
void delayTimer_Init(void);
/**
 * @brief The function is used to create a blocking delay in milliseconds. For that it uses TIMER0 GPTM 
 *        in concatenation mode with system clock = 16MHz.
 *        Note: The maximum delay it can generate is 268435ms
 * 
 * @param mSec delay time in milli-seconds
 */
void delayTimer(uint32_t mSec);

#endif