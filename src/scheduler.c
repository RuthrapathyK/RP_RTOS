
#include "scheduler.h"
#include "TM4C123GH6PM.h"

static uint8_t task_idx = 0;
static volatile uint32_t **curr_SP = 0;

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
void SysTick_handler(void)
{
    // Clear Systick Interrupt
    SysTick->STCTRL &= ~(1<<16);

  /* Save the updated current task's SP to its variable*/
  if((f_stack_1_init == true) ||(f_stack_2_init == true) || (f_stack_3_init == true))
  {
    store_TaskSP(curr_SP);
  }

  task_idx = task_idx % MAX_TASK_LIMIT;
	task_idx++;

	if(task_idx == 1)
  {
    curr_SP = &sp_1;
		__asm("LDR R7,=sp_1");
  }
	else if(task_idx == 2)
  {
    curr_SP = &sp_2;	
		__asm("LDR R7,=sp_2");
  }
	else
  {
    curr_SP = &sp_3;
		__asm("LDR R7,=sp_3");
  }

  /* Load the Register SP with Task's SP */
	__asm("LDR R7,[R7]");
	__asm("MOV SP,R7");

  if(!((f_stack_1_init == true) && (f_stack_2_init == true) && (f_stack_3_init == true)))
    __asm("BX LR");
}

