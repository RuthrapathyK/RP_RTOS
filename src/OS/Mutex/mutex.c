#include "mutex.h"
#include "../src/OS/Semaphore/semaphores.h"

#define DEFAULT_MUTEX_OWNER 255

extern Task_type PrioTask_Table[MAX_TASK_LIMIT];

/**
 * @brief Boosts the priority of the mutex owner if priority inheritance is required.
 *
 * Checks if the current task has a higher priority than the mutex owner and updates
 * the priority inheritance status to trigger a priority boost.
 *
 * @param mutex Pointer to the mutex object.
 */
static void Priority_Boost(Mutex_Type *mutex)
{
  uint32_t cur_idx = OS_getCurrent_TaskIdx();

  // Check if Owner Tasks's Priority(i.e Index) is greater than Current Index
  if(cur_idx < mutex->Owner_TaskIdx)
  {
    // Update the Boosted Task Index 
    mutex->HighPrio_TaskIdx = cur_idx;

    // Trigger the scheduler to Raise the priority of the Mutex's Owner Task
    mutex->PrioInherit_Status = Inherit_PI_BoostPriority;
  }
}

/**
 * @brief Reverses the priority boost applied during priority inheritance.
 *
 * If priority inheritance was previously applied, updates the status to trigger
 * a reversal of the boosted priority for the mutex owner.
 *
 * @param mutex Pointer to the mutex object.
 */
static void Priority_Reverse(Mutex_Type *mutex)
{
  if(mutex->PrioInherit_Status != Inherit_No_PI)
  {
    // Trigger the scheduler to Reverse the Raised priority of the Mutex's Owner Task
    mutex->PrioInherit_Status = Inherit_UnBoost_Priority; 
  }   
}


/**
 * @brief The Function gets Exclusive access to the memory passed and decreaments it by 1
 * 
 * @param mutex_state Address of the variable for which value needs to be decreamented
 */
static void Mutex_Take(uint32_t *mutex_state, Mutex_Type *mutex)
{
  // The argument will be by default stored in R0 for this compiler. 
  // If it changes then next assembly codes will also change

  // Start of the assembly function(This is busy wait implementation)
  __asm volatile (
          "MOV R11, R0\n\t"         // Move the R0 value(ie. argument) to R11 for further usage in assembly

      "Mutex_TryLock:\n\t"                // Branch Label 
        "LDREX R4, [R11]\n\t"       // Load value at mutex_state into R4 by Exclusively tagging processor and memory
        "CMP R4, #0\n\t"            // Compare with 0
        "BEQ Mutex_Sleep\n\t"       // If zero, move to Mutex_Sleep
        "SUB R4, R4, #1\n\t"        // If not equal to Zero then take the Token (R1 = R0 - 1)
        "STREX R5, R4, [R11]\n\t"   // Try to store R4 back to mutex_state
        "CMP R5, #0\n\t"            // Was store successful?
        "BNE Mutex_TryLock\n\t"           // If not successful retry from Branch Label
        "B Mutex_Take_End\n\t"          // Branch to completion
    );

__asm volatile("Mutex_Sleep:"); // Start of assembly label and the following C code belongs to this

  /* Priority Inheritance - Boost the Priority if needed */
  Priority_Boost(mutex);

  /* Load the Mutex in Task Primitive */
  PrioTask_Table[OS_getCurrent_TaskIdx()].Task_Primitive = mutex;

  /* Change the task state to Sleep */
  PrioTask_Table[OS_getCurrent_TaskIdx()].TaskState = Task_Sleep_Mutex;

  /* Trigger the scheduler */
  SYSTICK_TRIGGER;

  __asm volatile("B Mutex_TryLock"); // Retry Locking once the Task has waked up from Sleep 

  __asm volatile("Mutex_Take_End:"); // This is the label to execute the closing of instructions

  /* Unused */
  (void)mutex_state;
}

/**
 * @brief The Function gets Exclusive access to the memory passed and increaments it by 1
 * 
 * @param mutex_state Address of the variable for which value needs to be Increamented
 */
static void Mutex_Give(uint32_t * mutex_state, Mutex_Type *mutex)
{
  // The argument will be by default stored in R0 for this compiler. 
  // If it changes then next assembly codes will also change

  // Start of the assembly function
  __asm volatile(
    "MOV R3, R0\n\t"                   // Move the R0 value to R3 for further usage in assembly

    "Mutex_TryUnlock:\n\t"                   // Branch Label 
            "LDREX R0, [R3]\n\t"       // Load value at mutex_state into R0 by Exclusively tagging processor and memory
            "ADD R1, R0, #1\n\t"       // Add 1 to the value
            "STREX R2, R1, [R3]\n\t"   // Try to store R1 back to mutex_state
            "CMP R2, #0\n\t"           // Was store successful?
            "BNE Mutex_TryUnlock\n\t"        // If not successful retry from Branch Label
  );

  /* Priority Inheritance - UnBoost the Priority */
  Priority_Reverse(mutex);

  /* Trigger the scheduler */
  SYSTICK_TRIGGER;

  /* Unused */
  (void)mutex_state;
}

/**
 * @brief Initializes the specified mutex object.
 * 
 * Sets the mutex state to unlocked, clears ownership, and marks it as initialized.
 * 
 * @param mutex Pointer to the mutex object to initialize.
 */
void Mutex_Init(Mutex_Type *mutex)
{
    /* Check the Input Parameters */
    ASSERT(mutex != NULL);

    /* Initialize the Mutex Object */
    mutex->Mutex_State = Mutex_Unlocked;
    mutex->Owner_TaskIdx = DEFAULT_MUTEX_OWNER; // Make it as the Last Task Index
    mutex->HighPrio_TaskIdx = DEFAULT_MUTEX_OWNER; // Make it as the Last Task Index
    mutex->isInitialized = true;
    mutex->PrioInherit_Status = Inherit_No_PI;
}

/**
 * @brief Locks the specified mutex object.
 * 
 * Attempts to acquire the mutex for the calling task. Handles priority inheritance if required.
 * 
 * @param mutex Pointer to the mutex object to lock.
 */
void Mutex_Lock(Mutex_Type *mutex)
{
    /* Check the Input Parameters */
    ASSERT((mutex != NULL) && (mutex->Mutex_State < Mutex_Max_State));
    
    /* Perform Locking only when the Mutex Object is Initialized */
    ASSERT(mutex->isInitialized == true);

    /* Lock the Mutex if it is available. If not move the Task to Sleep State */
    Mutex_Take((uint32_t *) &mutex->Mutex_State, mutex);

    /* Make Current Task as the Owner of the Mutex */
    mutex->Owner_TaskIdx = OS_getCurrent_TaskIdx();

}

/**
 * @brief Unlocks the specified mutex object.
 * 
 * Releases the mutex and restores priority if priority inheritance was applied.
 * 
 * @param mutex Pointer to the mutex object to unlock.
 */
void Mutex_Unlock(Mutex_Type *mutex)
{
    /* Check the Input Parameters */
    ASSERT((mutex != NULL) && (mutex->Mutex_State < Mutex_Max_State));
    
    /* Perform Locking only when the Mutex Object is Initialized */
    ASSERT(mutex->isInitialized == true);

    /* Check if The Current Task is the Owner of the Mutex */
    if(mutex->Owner_TaskIdx == OS_getCurrent_TaskIdx())
        Mutex_Give((uint32_t *) &mutex->Mutex_State, mutex); // Unlock the Mutex
    else
        ASSERT(0); // Assert the Program and indicate that an attempt to Unlock a Mutex from Different Owner
}

