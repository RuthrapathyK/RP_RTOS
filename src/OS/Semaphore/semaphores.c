#include "semaphores.h"


extern Task_type PrioTask_Table[MAX_TASK_LIMIT];

/**
 * @brief The Function gets Exclusive access to the memory passed and decreaments it by 1
 * 
 * @param semaphore Address of the variable for which value needs to be decreamented
 */
static void Sem_Take(uint32_t *current_count, Semaphore_Type *semaphore)
{
  // The argument will be by default stored in R0 and R1 for this compiler. 
  // If it changes then next assembly codes will also change

  // Start of the assembly function(This is sleep implementation)
  __asm volatile (
          "MOV R11, R0\n\t"        // Move the R0 value(ie. current_count) to R11 for further usage in assembly

      "Sem_TryLock:\n\t"                // Branch Label 
        "LDREX R4, [R11]\n\t"       // Load value at semaphore into R4 by Exclusively tagging processor and memory
        "CMP R4, #0\n\t"            // Compare with 0
        "BEQ Sem_Sleep\n\t"       // If zero, move to Sem_Sleep
        "SUB R4, R4, #1\n\t"        // If not equal to Zero then take the Token (R1 = R0 - 1)
        "STREX R5, R4, [R11]\n\t"   // Try to store R4 back to semaphore
        "CMP R5, #0\n\t"            // Was store successful?
        "BNE Sem_TryLock\n\t"           // If not successful retry from Branch Label
        "B Sem_TakeEnd\n\t"          // Branch to completion
    );

__asm volatile("Sem_Sleep:"); // Start of assembly label and the following C code belongs to this

  /* Store the Address of the Semaphore Object in the corresponding Task's Priority Table*/
  PrioTask_Table[OS_getCurrent_TaskIdx()].Task_Primitive = semaphore;

  /* Change the task state to Sleep */
  PrioTask_Table[OS_getCurrent_TaskIdx()].TaskState = Task_Sleep_Semaphore;

  /* Trigger the scheduler */
  SYSTICK_TRIGGER;

  __asm volatile("B Sem_TryLock"); // Retry Locking once the Task has waked up from Sleep 

  __asm volatile("Sem_TakeEnd:"); // This is the label to execute the closing of instructions

    /* Unused */
  (void)current_count;
}

/**
 * @brief The Function gets Exclusive access to the memory passed and increaments it by 1
 * 
 * @param semaphore Address of the variable for which value needs to be Increamented
 */
static void Sem_Give(uint32_t *current_count, uint32_t max_val)
{
  // The argument will be by default stored in R0  and R1 for this compiler. 
  // If it changes then next assembly codes will also change

  // Start of the assembly function
  __asm volatile(
    "MOV R10, R0\n\t"                   // Move the R0 value(i.e. current_count) to R3 for further usage in assembly
    "MOV R12, R1\n\t"                   // Move the R1(i.e. max_val) value to R4 for further usage in assembly

    "Sem_TryUnlock:\n\t"                   // Branch Label 
        "LDREX R11, [R10]\n\t"         // Load value at semaphore into R0 by Exclusively tagging processor and memory
        "ADD R11, R11, #1\n\t"         // Add 1 to the value
        "CMP R11, R12\n\t"             // Compare R11 with R12 and set the condition flags
        "IT GT\n\t"
        "MOVGT R11, R12\n\t"           //If R11 is Greater Than R12 (GT condition), then R11 = R12
        "STREX R11, R11, [R10]\n\t"    // Try to store R1 back to semaphore
        "CMP R11, #0\n\t"              // Was store successful?
        "BNE Sem_TryUnlock\n\t"        // If not successful retry from Branch Label
  );

  /* Trigger the scheduler */
  SYSTICK_TRIGGER;

  /* Unused */
  (void)current_count;
  (void)max_val;
}
/**
 * @brief Initializes the semaphore object with the specified current and maximum count values.
 *
 * @param semaphore Pointer to the semaphore object to initialize.
 * @param cur_count Initial value for the semaphore's current count.
 * @param max_count Maximum value for the semaphore's count.
 */
void Sem_Init(Semaphore_Type *semaphore, uint32_t cur_count, uint32_t max_count)
{
  /* Check the Input Parameters */
  ASSERT(semaphore != NULL);

  /* Initialize the Semaphore Object */
  semaphore->Max_Count = max_count;
  semaphore->Current_Count = cur_count;
  semaphore->isInitialised = true;
}

/**
 * @brief Waits for a semaphore by attempting to decrement its count. If the count is zero, the calling task is put to sleep until the semaphore becomes available.
 *
 * @param semaphore Pointer to the semaphore object to wait on.
 */
void Sem_Wait(Semaphore_Type * semaphore)
{
  /* Check the Input Parameters */
  ASSERT(semaphore != NULL);

  /* Check the Preconditions */
  ASSERT(semaphore->isInitialised == true);

  Sem_Take(&semaphore->Current_Count, semaphore);
}

/**
 * @brief Signals (releases) the semaphore, incrementing its count and potentially waking up waiting tasks.
 *
 * @param semaphore Pointer to the semaphore object to signal.
 */
void Sem_Signal(Semaphore_Type * semaphore)
{
  /* Check the Input Parameters */
  ASSERT(semaphore != NULL);

  /* Check the Preconditions */
  ASSERT(semaphore->isInitialised == true);

  Sem_Give(&semaphore->Current_Count, semaphore->Max_Count);

  /* Check the Post condition */
  ASSERT(semaphore->Current_Count <= semaphore->Max_Count);
}