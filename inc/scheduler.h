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
 * @brief This function generates Scheduler delay
 * 
 */
void OS_delay(uint32_t mSec);
#endif