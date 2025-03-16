
#include "scheduler.h"
#include "TM4C123GH6PM.h"
#include <stdbool.h>
#include "tasks.h"

static uint8_t task_idx = 0;
static volatile uint32_t **curr_SP = 0;
static volatile bool f_schdInit = false;
volatile uint32_t temp = 0;
extern uint32_t Max_Task;
extern Task_type Task_Table[MAX_TASK_LIMIT];
/**
 * @brief An Inline function to store the Stack pointers for initialization
 * 
 */
inline void __attribute__((always_inline))store_TaskSP(volatile uint32_t **ptr)
{
    __asm__ volatile (
        "MOV R0, SP\n\t"      // Move the value of SP into R0 (MRS is not available in all compilers)
        "STR R0, [%0]"        // Store the value of R0 (SP) into the address of sp_value
        :                       // No output operands
        : "r" (ptr)      // Input operand: address of sp_value
        : "r0"                  // Clobbered register: R0
    );
}

/**
 * @brief The function Intializes Scheduler that uses Systick Timer as Timer source
 * 
 * @param useconds Frequency of the Systick Interrupt Generation in micro-seconds
 */
void scheduler_Init(uint32_t useconds)
{
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
 * @brief The algorithm for executing context-swtching and state saving between tasks
 * 
 */
void __attribute__ ((naked)) GPIO_Port_F_handler(void) 
{
    // Clear the interrupt
    GPIOF->ICR |= (1<<4);
    __asm__ volatile (
      "LDR R0, SP\n\t"
      "STR R0, %0"
      :"=r" (temp)
    );
    // // Clear Systick Interrupt
    // SysTick->STCTRL &= ~(1<<16);
    // /* Save the updated current task's SP to its variable*/
    // if(f_schdInit == true)
    //   store_TaskSP(curr_SP);
    // else
    //   f_schdInit = true;

    // task_idx = task_idx % Max_Task;

    // curr_SP = *(Task_Table[task_idx].stack_ptr);
    // __asm("LDR R7,=curr_SP");

    // task_idx++;

    // /* Load the Register SP with Task's SP */
    // __asm("LDR R7,[R7]");
    // __asm("MOV SP,R7");

      __asm("BX LR");
}

