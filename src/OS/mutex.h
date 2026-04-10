#ifndef MUTEX_H
#define MUTEX_H


#include "TM4C123GH6PM.h"
#include "common.h"
#include "tasks.h"

typedef enum{
    Mutex_Locked = 0,
    Mutex_Unlocked = 1,
    Mutex_Max_State
}Mutex_state_e;

typedef enum{
    Inherit_No_PI,              // No priority Inheritance needed
    Inherit_PI_NoOperation,     // Priority Inheritance needed but No operation needed
    Inherit_PI_BoostPriority,   // Priority Inheritance needed Priority Boost needs to be performed
    Inherit_UnBoost_Priority    // Priority Inheritance needed Priority Reverse needs to be performed
}PriorityInherit_state_e;

/**
 * Application Shall not modify any of the Members or Unknown behaviour will happen
 */
typedef struct {
    Mutex_state_e Mutex_State;  // State of the Mutex Object(ie. Whether it is Locked or Unlocked)
    uint32_t Owner_TaskIdx;        // Index of the Task which holds the Mutex's Ownership
    uint32_t HighPrio_TaskIdx;     // Index of the Swapped High Priority task if there is a need for PrioInheritance
    PriorityInherit_state_e PrioInherit_Status; // Status of the Priority Inheritance operations
    bool isInitialized; 
}Mutex_Type;
/**
 * @brief Initializes the specified mutex object.
 * 
 * Sets the mutex state to unlocked, clears ownership, and marks it as initialized.
 * 
 * @param mutex Pointer to the mutex object to initialize.
 */
void Mutex_Init(Mutex_Type *mutex);

/**
 * @brief Locks the specified mutex object.
 * 
 * Attempts to acquire the mutex for the calling task. Handles priority inheritance if required.
 * 
 * @param mutex Pointer to the mutex object to lock.
 */
void Mutex_Lock(Mutex_Type *mutex);

/**
 * @brief Unlocks the specified mutex object.
 * 
 * Releases the mutex and restores priority if priority inheritance was applied.
 * 
 * @param mutex Pointer to the mutex object to unlock.
 */
void Mutex_Unlock(Mutex_Type *mutex);

#endif