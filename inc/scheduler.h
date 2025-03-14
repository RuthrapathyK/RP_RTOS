#ifndef __SCHEDULER_H
#define __SCHEDULER_H

#include "typedef.h"

/**
 * @brief The function Intializes Scheduler that uses Systick Timer as Timer source
 * 
 * @param useconds Frequency of the Systick Interrupt Generation in micro-seconds
 */
void scheduler_Init(uint32_t useconds);

#endif