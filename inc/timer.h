#ifndef __TIMER_HH
#define __TIMER_HH
#include "common.h"

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
/**
 * @brief The function is used to create a blocking delay. It used traditional for loop
 *        Note: The maximum delay it can generate is 268435ms
 * 
 * @param mSec delay time in approximate milli-seconds
 */
void delayLoop(uint32_t mSec);
/**
 * @brief The function is used to initialize the TIMER 0 in Periodic Downcounting modes.
 *        This will also initialize the TIMER 0 in concatenation mode (ie. as a 32bit Timer)
 *        Note: Prescalar is NA when the timer is configured as 32bit
 * 
 * @param mSec Periodic counter increament time
 */
void SystemTimer_Init(uint32_t mSec);
/**
 * @brief The Function creates a delay of input time in milliseconds without blocking the Timer Peripheral
 * 
 * @param mSec Delay time in approximate milli-seconds
 */
void delay(uint32_t mSec);
/**
 * @brief An inline function that returns the system time to the task called
 * 
 */
uint32_t getSystemTime(void);
#endif