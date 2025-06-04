
#include "scheduler.h"
#include "TM4C123GH6PM.h"
#include "tasks.h"
#include "common.h"
#include "timer.h"
#include "led.h"

uint8_t CurTask_Idx = 0;
static volatile bool f_schdInit = false;
uint32_t * tem_sp = 0;
uint32_t schIter = 0;

extern uint32_t Max_SchTask;
extern Task_type PrioTask_Table[MAX_TASK_LIMIT];
extern volatile uint32_t SystemTime_Count;

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
      ASSERT(tem_sp >= PrioTask_Table[CurTask_Idx].stack);

      // Save the current Task's SP
      PrioTask_Table[CurTask_Idx].stack_ptr = tem_sp;
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
        // Check if the task is blocked due to Synchronization Primitive
        if(PrioTask_Table[schIter].syncPrim != NULL)
        {
          // Check if Synchrozination Resource is available
          if(*((uint32_t *)PrioTask_Table[schIter].syncPrim) > 0)
          {
            PrioTask_Table[schIter].syncPrim = NULL;
            PrioTask_Table[schIter].TaskState = Task_Ready;
          }
        }
        // Check if the task is blocked due to Delay
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
       CurTask_Idx = schIter;
       break;
      }
    }

    // Get the next Task's SP
    tem_sp = PrioTask_Table[CurTask_Idx].stack_ptr; 
    
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
          "MOV R11, R0\n\t"         // Move the R0 value(ie. argument) to R11 for further usage in assembly

      "lockTry:\n\t"                // Branch Label 
        "LDREX R4, [R11]\n\t"       // Load value at varObj into R4 by Exclusively tagging processor and memory
        "CMP R4, #0\n\t"            // Compare with 0
        "BEQ OS_semSleep\n\t"       // If zero, move to OS_semSleep
        "SUB R4, R4, #1\n\t"        // If not equal to Zero then take the Token (R1 = R0 - 1)
        "STREX R5, R4, [R11]\n\t"   // Try to store R4 back to varObj
        "CMP R5, #0\n\t"            // Was store successful?
        "BNE lockTry\n\t"           // If not successful retry from Branch Label
        "B SemTakeEnd\n\t"          // Branch to completion
    );

__asm volatile("OS_semSleep:"); // Start of assembly label and the following C code belongs to this

  /* Store the Address of the Semaphore Object in the corresponding Task's Priority Table*/
  PrioTask_Table[CurTask_Idx].syncPrim = varObj;

  /* Change the task state to Sleep */
  PrioTask_Table[CurTask_Idx].TaskState = Task_Sleep;

  /* Trigger the scheduler */
  SYSTICK_TRIGGER;

  __asm volatile("B lockTry"); // Retry Locking once the Semaphore is released

  __asm volatile("SemTakeEnd:"); // This is the label to execute the closing of instructions
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

  // Start of the assembly function
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
  SYSTICK_TRIGGER;
}
/**
 * @brief Delay created from Scheduler
 * 
 * @param mSec 
 */
void OS_delay(uint32_t mSec)
{
  /* Note the Wakeup time */
  PrioTask_Table[CurTask_Idx].nxtSchedTime = getSystemTime() + mSec; 
  
  /* Change the task state to Sleep */
  PrioTask_Table[CurTask_Idx].TaskState = Task_Sleep;
  
  /* Trigger the scheduler */
  SYSTICK_TRIGGER;
}
/**
 * @brief Precise Delay created from Scheduler
 *       Note: This delay will include Task Execution time also in the delay
 *       Example: If tast executes for 200ms and Task calls this delay of 1000ms then actual delay it produces is 800ms
 * 
 * @param mSec 
 */
void OS_cycleDelay(uint32_t * startStamp, uint32_t mSec)
{
  /* Update the next Time stamp */
  *startStamp += mSec;

  /* Note the Wakeup time */
  PrioTask_Table[CurTask_Idx].nxtSchedTime = *startStamp; 

  /* Check if the Timer is already expired */
  if(PrioTask_Table[CurTask_Idx].nxtSchedTime > getSystemTime())
  {
      /* Change the task state to Sleep */
      PrioTask_Table[CurTask_Idx].TaskState = Task_Sleep;
      
      /* Trigger the scheduler */
      SYSTICK_TRIGGER;
  }
  else{
    /* No context switch */
  }

}