
#ifndef __SEMAPHORES_H
#define __SEMAPHORES_H

#include "TM4C123GH6PM.h"
#include "common.h"
#include "tasks.h"
#include "scheduler.h"


typedef struct{
    uint32_t Max_Count;     // Maximum Value the Semaphore can Hold
    uint32_t Current_Count; // Current value of the Semaphore
    bool isInitialised;     // Checks whether it is initialized or not
}Semaphore_Type;

/**
 * @brief Initializes the semaphore object with the specified current and maximum count values.
 *
 * @param semaphore Pointer to the semaphore object to initialize.
 * @param cur_count Initial value for the semaphore's current count.
 * @param max_count Maximum value for the semaphore's count.
 */
void Sem_Init(Semaphore_Type *semaphore, uint32_t max_count, uint32_t cur_count);

/**
 * @brief Waits for a semaphore by attempting to decrement its count. If the count is zero, the calling task is put to sleep until the semaphore becomes available.
 *
 * @param semaphore Pointer to the semaphore object to wait on.
 */
void Sem_Wait(Semaphore_Type * semaphore);

/**
 * @brief Signals (releases) the semaphore, incrementing its count and potentially waking up waiting tasks.
 *
 * @param semaphore Pointer to the semaphore object to signal.
 */
void Sem_Signal(Semaphore_Type * semaphore);


#endif