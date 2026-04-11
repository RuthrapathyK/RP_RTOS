
#include "scheduler.h"
#include "TM4C123GH6PM.h"
#include "../src/OS/Tasks/tasks.h"
#include "common.h"
#include "../src/Drivers/Timer/timer.h"
#include "../src/OS/Semaphore/semaphores.h"
#include "../src/OS/Mutex/mutex.h"
#include "../src/Services/Debug/testpin.h"

#define IDLE_TASK_STACK_SIZE 50

static volatile uint8_t CurTask_Idx = 0;
static volatile bool f_schdInit = false;
static uint32_t * tem_sp = 0;
static volatile uint32_t schIter = 0;
static volatile Task_type temp_Task;
static volatile Mutex_Type *t_mutex = 0;
static volatile uint32_t tmp_TaskIdx = 0;
static uint32_t IdleTask_Stack[IDLE_TASK_STACK_SIZE]={0};

extern uint32_t Max_SchTask;
extern Task_type PrioTask_Table[MAX_TASK_LIMIT];
extern volatile uint32_t SystemTime_Count;

/**
 * @brief Idle task that runs when no other task is in Ready state
 *        Used to toggle test pin for debugging purposes
 */
void OS_IdleTask(void)
{
  while(1){
    TESTPIN_ON;
    TESTPIN_OFF;
  }
}

/**
 * @brief The function Intializes Scheduler that uses Systick Timer as Timer source
 * 
 * @param useconds Frequency of the Systick Interrupt Generation in micro-seconds
 *        Note: Scheduler Algorithm will take ~9.5us to complete execution. So choose useconds > 100
 *              The max value is 4194303(i.e 4.194 seconds) 
 */
void OS_SchedulerRun(uint32_t useconds)
{
  /* Check for valid range of useconds */
  ASSERT((useconds >= 100) && (useconds <= 4194303)); // 100 is decided by scheduler execution time and 4194303 * 4 is the max value that can be loaded in STRELOAD register for 24bit timer

    /* Set the Systick and PendSV to have Priority 1 (ie.Scheduler should be the Least Priority interrupt and other interrupts are High Priority) */
  SCB->SYSPRI3 &= ~(0x07 << 29);  // SysTick
  SCB->SYSPRI3 &= ~(0x07 << 21);  // PendSV

  SCB->SYSPRI3 |= (0x01 << 29); // SysTick
  SCB->SYSPRI3 |= (0x01 << 21); // PendSV

  /* Idle task should have the Least priority than any other tasks created */
  OS_CreateTask(IdleTask_Stack,IDLE_TASK_STACK_SIZE,&OS_IdleTask, 255);

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
 *      Note: This function shall not have any local variables or else Unpredictable behaviour will happen
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
        // Check if the task is blocked due to Semaphore
        if(PrioTask_Table[schIter].TaskState == Task_Sleep_Semaphore)
        {
          if(((Semaphore_Type *)PrioTask_Table[schIter].Task_Primitive) != NULL)
          {
            // Check if Synchrozination Resource is available
            if(((Semaphore_Type *)PrioTask_Table[schIter].Task_Primitive)->Current_Count > 0)
            {
              PrioTask_Table[schIter].Task_Primitive = NULL;
              PrioTask_Table[schIter].TaskState = Task_Ready;
            }
          }
          else
          {
            ASSERT(0); // Asserted to check the Task should not be moved to Task_Sleep_Semaphore state without loading the Semaphore
          }
        }
        // Check if the task is blocked due to Delay
        else if(PrioTask_Table[schIter].TaskState == Task_Sleep_Delay)
        {
            if (PrioTask_Table[schIter].nxtSchedTime <= SystemTime_Count)
            {
              PrioTask_Table[schIter].TaskState = Task_Ready;
            }
        }
        else if(PrioTask_Table[schIter].TaskState == Task_Sleep_Mutex)
        {
          if(PrioTask_Table[schIter].Task_Primitive != NULL)
          {
            t_mutex = (Mutex_Type *)PrioTask_Table[schIter].Task_Primitive;

            // Check if Priority inheritance operation is triggered
            if(t_mutex->PrioInherit_Status == Inherit_PI_BoostPriority)
            {
              // Change the Priority of Owner task to the High Priority Task which claims Mutex by Swapping
              temp_Task = PrioTask_Table[t_mutex->Owner_TaskIdx];
              PrioTask_Table[t_mutex->Owner_TaskIdx] = PrioTask_Table[t_mutex->HighPrio_TaskIdx];
              PrioTask_Table[t_mutex->HighPrio_TaskIdx] = temp_Task;

              // Update the Owner and High Priority Task Index
              tmp_TaskIdx = t_mutex->Owner_TaskIdx;
              t_mutex->Owner_TaskIdx = t_mutex->HighPrio_TaskIdx;
              t_mutex->HighPrio_TaskIdx = tmp_TaskIdx;

              // Change the status of the Priority Inheritance operation status
              t_mutex->PrioInherit_Status = Inherit_PI_NoOperation;
            }
            else if(t_mutex->PrioInherit_Status == Inherit_UnBoost_Priority)
            {
              // Change the Priority of Owner task to its original Priority by Swapping
              temp_Task = PrioTask_Table[t_mutex->Owner_TaskIdx];
              PrioTask_Table[t_mutex->Owner_TaskIdx] = PrioTask_Table[t_mutex->HighPrio_TaskIdx];
              PrioTask_Table[t_mutex->HighPrio_TaskIdx] = temp_Task;

              // Update the Owner and High Priority Task Index
              tmp_TaskIdx = t_mutex->Owner_TaskIdx;
              t_mutex->Owner_TaskIdx = t_mutex->HighPrio_TaskIdx;
              t_mutex->HighPrio_TaskIdx = tmp_TaskIdx;

              // Change the status of the Priority Inheritance operation
              t_mutex->PrioInherit_Status = Inherit_PI_NoOperation;

              // Clear the Task_Primitive to NULL
              PrioTask_Table[t_mutex->HighPrio_TaskIdx].Task_Primitive = NULL;
              
              // Change the Task State to Ready
              PrioTask_Table[t_mutex->HighPrio_TaskIdx].TaskState = Task_Ready;

              // ReInitialize the PriorityInheritance's status of the Mutex */
              t_mutex->PrioInherit_Status = Inherit_No_PI;
            }
            // Check if the Mutex is in Unlocked state
            else if(t_mutex->Mutex_State == Mutex_Unlocked)
            {
              // Clear the Task_Primitive to NULL
              PrioTask_Table[schIter].Task_Primitive = NULL;

              // Change the Task State to Ready
              PrioTask_Table[schIter].TaskState = Task_Ready;
            }
          }
          else
          {
            ASSERT(0); // Asserted to check the Task should not be moved to Task_Sleep_Mutex state without loading the Mutex
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
 * @brief Delay created from Scheduler
 * 
 * @param mSec 
 */
void OS_delay(uint32_t mSec)
{
  /* Note the Wakeup time */
  PrioTask_Table[CurTask_Idx].nxtSchedTime = getSystemTime() + mSec; 
  
  /* Change the task state to Sleep */
  PrioTask_Table[CurTask_Idx].TaskState = Task_Sleep_Delay;
  
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
  if(PrioTask_Table[CurTask_Idx].nxtSchedTime >= getSystemTime())
  {
      /* Change the task state to Sleep */
      PrioTask_Table[CurTask_Idx].TaskState = Task_Sleep_Delay;
      
      /* Trigger the scheduler */
      SYSTICK_TRIGGER;
  }
  else{
    /* No context switch */
  }

}

/**
 * @brief Returns the index of the currently running task.
 * 
 * @return uint8_t Index of the current task.
 */
uint8_t OS_getCurrent_TaskIdx(void)
{
	return CurTask_Idx;
}