#ifndef __SCHEDULER_H
#define __SCHEDULER_H

#include "common.h"

/**
 * @brief The function Intializes Scheduler that uses Systick Timer as Timer source
 * 
 * @param useconds Frequency of the Systick Interrupt Generation in micro-seconds
 */
void scheduler_Init(uint32_t useconds);

/**
 * @brief The Function gets Exclusive access to the memory passed and decreaments it by 1
 * 
 * @param varObj Address of the variable for which value needs to be decreamented
 */
void semTake(uint32_t * varObj);

/**
 * @brief The Function gets Exclusive access to the memory passed and increaments it by 1
 * 
 * @param varObj Address of the variable for which value needs to be Increamented
 */
void semGive(uint32_t * varObj);

/**
 * @brief This function generates Scheduler delay
 * 
 */
void OS_delay(uint32_t mSec);

/**
 * @brief Precise Delay created from Scheduler
 *       Note: This delay will include Task Execution time also in the delay
 *       Example: If tast executes for 200ms and Task calls this delay of 1000ms then actual delay it produces is 800ms
 * 
 * @param mSec 
 */
void OS_cycleDelay(uint32_t * startStamp, uint32_t mSec);

#endif