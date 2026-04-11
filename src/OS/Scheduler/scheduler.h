#ifndef __SCHEDULER_H
#define __SCHEDULER_H

#include "common.h"

/**
 * @brief The function Intializes Scheduler that uses Systick Timer as Timer source
 * 
 * @param useconds Frequency of the Systick Interrupt Generation in micro-seconds
 */
void OS_SchedulerRun(uint32_t useconds);

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

/**
 * @brief Returns the index of the currently running task.
 * 
 * @return uint8_t Index of the current task.
 */
uint8_t OS_getCurrent_TaskIdx(void);

#endif