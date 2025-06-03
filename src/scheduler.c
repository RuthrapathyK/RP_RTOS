
#include "scheduler.h"
#include "TM4C123GH6PM.h"
#include "tasks.h"
#include "common.h"
#include "timer.h"
#include "led.h"

uint8_t task_idx = 0;
static volatile bool f_schdInit = false;
uint32_t * tem_sp = 0;
uint32_t schIter = 0;
extern uint32_t Max_SchTask;
extern Task_type PrioTask_Table[MAX_TASK_LIMIT];
extern volatile uint32_t SystemTime_Count;
void OS_sem_IdleTrigger(void);
/**
 * @brief The function Intializes Scheduler that uses Systick Timer as Timer source
 * 
 * @param useconds Frequency of the Systick Interrupt Generation in micro-seconds
 *        Note: Scheduler Algorithm will take ~9.5us to complete execution. So choose useconds > 100
 *              The max value is 4194303(i.e 4.194 seconds) 
 */
void scheduler_Init(uint32_t useconds)
{
  /* Check for valid range of useconds */
  ASSERT((useconds >= 100) && (useconds <= 4194303)); // 100 is decided by scheduler execution time and 4194303 * 4 is the max value that can be loaded in STRELOAD register for 24bit timer

  /* Load the Reload Value */
  SysTick->STRELOAD = (useconds * 4);

  /* Clear the Counter */
  SysTick->STCURRENT = 0x00000000;

  /* Select Clock source - Internalclock / 4 */
  SysTick->STCTRL &= ~(1<<2);

  /* Enable Interrupt and Start the Timer */
  SysTick->STCTRL |= ((1<<1) | (1<<0));
}

/**
 * @brief The algorithm for executing context-swtching and State saving between tasks
 *        The time taken for execution is ~9.5us
 * 
 */
void __attribute__ ((naked))SysTick_handler(void) 
{
    // Clear Systick Interrupt
    SysTick->STCTRL &= ~(1<<16);

    if(f_schdInit != false)
    {
      // Save General Purpose Registers
      __asm("PUSH {R4-R11}");

      // Get the current SP and store it in tem_sp variable;
      __asm("MOV %0, SP":"=r" (tem_sp)::"%0");

      // Check if Stack Overflow occured for the current Task
      ASSERT(tem_sp >= PrioTask_Table[task_idx].stack);

      // Save the current Task's SP
      PrioTask_Table[task_idx].stack_ptr = tem_sp;
    }
    else
    {
      // SP not saved while called for 1st time
      f_schdInit = true;
    }

    // Derive the States of all Tasks
    for(schIter = 0; schIter < Max_SchTask; schIter++)
    {
      if(PrioTask_Table[schIter].TaskState == Task_Sleep)
      {
        if(PrioTask_Table[schIter].sync_primitive != NULL)
        {
          if(*((uint32_t *)PrioTask_Table[schIter].sync_primitive) > 0)
          {
            PrioTask_Table[schIter].sync_primitive = NULL;
            PrioTask_Table[schIter].TaskState = Task_Ready;
          }
        }
        else if (PrioTask_Table[schIter].nxtSchedTime <= SystemTime_Count)
        {
          PrioTask_Table[schIter].TaskState = Task_Ready;
        }
      }
    }

    // Choose which task to schedule based on priority. If no task is in Ready state then schedule idleTask
    for(schIter = 0; schIter < Max_SchTask; schIter++)
    {
      if(PrioTask_Table[schIter].TaskState == Task_Ready)
      {
       task_idx = schIter;
       break;
      }
    }

    // Get the next Task's SP
    tem_sp = PrioTask_Table[task_idx].stack_ptr; 
    
    // Load the next Task's SP to the SP register
    __asm("MOV SP, %0"::"r" (tem_sp) :"%0"); 

    // Retrieve the next Task's General Purpose Registers
    __asm("POP {R4-R11}");

    // Exit the ISR
    __asm("BX LR");
}

/**
 * @brief The Function gets Exclusive access to the memory passed and decreaments it by 1
 * 
 * @param varObj Address of the variable for which value needs to be decreamented
 */
void semTake(uint32_t * varObj)
{
  // The argument will be by default stored in R0 for this compiler. 
  // If it changes then next assembly codes will also change

  // Start of the assembly function(This is busy wait implementation)
  __asm volatile (
          "MOV R3, R0\n\t"         // Move the R0 value to R3 for further usage in assembly

      "lockTry:\n\t"               // Branch Label 
        "LDREX R0, [R3]\n\t"       // Load value at varObj into R0 by Exclusively tagging processor and memory
        "CMP R0, #0\n\t"           // Compare with 0
        "BEQ Copy_Idle\n\t"          // If zero, move to Copy_Idle
        "SUB R1, R0, #1\n\t"       // If not equal to Zero then take the Token (R1 = R0 - 1)
        "STREX R2, R1, [R3]\n\t"   // Try to store R1 back to varObj
        "CMP R2, #0\n\t"           // Was store successful?
        "BNE lockTry\n\t"          // If not successful retry from Branch Label

      "Copy_Idle:\n\t"
        "MOV R0, R3\n\t"    // Copy the varObj argument to R0 and move to Task to sleep state
        "BX OS_sem_IdleTrigger\n\t"
    );
}
/**
 * @brief The Function gets Exclusive access to the memory passed and increaments it by 1
 * 
 * @param varObj Address of the variable for which value needs to be Increamented
 */
void semGive(uint32_t * varObj)
{
  // The argument will be by default stored in R0 for this compiler. 
  // If it changes then next assembly codes will also change

  // Start of the assembly function(This is busy wait implementation)
  __asm volatile(
    "MOV R3, R0\n\t"                   // Move the R0 value to R3 for further usage in assembly

    "unlockTry:\n\t"                   // Branch Label 
            "LDREX R0, [R3]\n\t"       // Load value at varObj into R0 by Exclusively tagging processor and memory
            "ADD R1, R0, #1\n\t"       // Add 1 to the value
            "STREX R2, R1, [R3]\n\t"   // Try to store R1 back to varObj
            "CMP R2, #0\n\t"           // Was store successful?
            "BNE unlockTry\n\t"        // If not successful retry from Branch Label
  );

  /* Trigger the scheduler */
  SCB->INTCTRL |= 1 << 26;
}
/**
 * @brief Delay created from Scheduler
 * 
 * @param mSec 
 */
void OS_delay(uint32_t mSec)
{
  /* Note the Wakeup time */
  PrioTask_Table[task_idx].nxtSchedTime = getSystemTime() + mSec; 
  
  /* Change the task state to Sleep */
  PrioTask_Table[task_idx].TaskState = Task_Sleep;
  
  /* Trigger the scheduler */
  SCB->INTCTRL |= 1 << 26;
}

void * temp_ptr = 0;

void OS_sem_IdleTrigger(void)
{ 
 __asm volatile("LDR R1, =temp_ptr");
 __asm volatile("STR R0, [R1]");

  /* Store the Address of the Semaphore Object in the corresponding Task's Priority Table*/
  PrioTask_Table[task_idx].sync_primitive = temp_ptr;

  /* Change the task state to Sleep */
  PrioTask_Table[task_idx].TaskState = Task_Sleep;

  /* Trigger the scheduler */
  SCB->INTCTRL |= 1 << 26;
}
