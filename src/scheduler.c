
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
extern Task_type Task_Table[MAX_TASK_LIMIT];
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
      ASSERT(tem_sp >= Task_Table[task_idx].stack);

      // Save the current Task's SP
      Task_Table[task_idx].stack_ptr = tem_sp;
    }
    else
    {
      // SP not saved while called for 1st time
      f_schdInit = true;
    }

    // Derive the States of all Tasks
    for(schIter = 0; schIter < Max_SchTask; schIter++)
    {
      if((Task_Table[schIter].TaskState == Task_Sleep) && (Task_Table[schIter].nxtSchedTime <= SystemTime_Count))
        Task_Table[schIter].TaskState = Task_Ready;
    }

    // Choose which task to schedule based on priority. If no task is in Ready state then schedule idleTask
    for(schIter = 0; schIter < Max_SchTask; schIter++)
    {
      if(Task_Table[schIter].TaskState == Task_Ready)
      {
       task_idx = schIter;
       break;
      }
    }

    // Get the next Task's SP
    tem_sp = Task_Table[task_idx].stack_ptr; 
    
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
  Task_Table[task_idx].nxtSchedTime = getSystemTime() + mSec; 
  
  Task_Table[task_idx].TaskState = Task_Sleep;
  
  /* Trigger the scheduler */
  //SysTick->STCURRENT = 0x00000000;
  SCB->INTCTRL |= 1 << 26;
}
