#include "typedef.h"
#include "led.h"
#include "timer.h"
#include <stdbool.h>

#define MAX_TASK_LIMIT 3

uint8_t task_switch = 0;

volatile uint32_t **curr_SP = 0;

volatile uint32_t stack_1[50];
volatile uint32_t * sp_1 = 0;
volatile bool f_stack_1_init = false;

volatile uint32_t stack_2[50];
volatile uint32_t * sp_2 = 0;
volatile bool f_stack_2_init = false;

volatile uint32_t stack_3[50];
volatile uint32_t * sp_3 = 0;
volatile bool f_stack_3_init = false;

void Task_1(void)
{
  f_stack_1_init = true;
  while(1){
    LED_BLUE_OFF;
    LED_GREEN_OFF;
    LED_RED_ON;
  }
}

void Task_2(void)
{
  f_stack_2_init = true;
  while(1){
    LED_RED_OFF;
    LED_GREEN_OFF;
    LED_BLUE_ON;
    
  }
}
void Task_3(void)
{
  f_stack_3_init = true;
  while(1){
    LED_BLUE_OFF;
    LED_RED_OFF;  
    LED_GREEN_ON;
  }  
}
void Initialize_stack(void)
{
  sp_1 = &stack_1[50];
	*(--sp_1) =  0x21000000;//xPSR
	*(--sp_1) = (uint32_t)&Task_1; // Program Counter
	*(--sp_1) = (uint32_t)&Task_1; // LR
	*(--sp_1) = 0x00;//R12
	*(--sp_1) = 0x00;//R3
	*(--sp_1) = 0x00;//R2
	*(--sp_1) = 0x00;//R1
	*(--sp_1) = 0x00;//R0
	
  sp_2 = &stack_2[50];
	*(--sp_2) =  0x21000000;//xPSR
	*(--sp_2) = (uint32_t)&Task_2; // Program Counter
	*(--sp_2) = (uint32_t)&Task_2; // LR
	*(--sp_2) = 0x00;//R12
	*(--sp_2) = 0x00;//R3
	*(--sp_2) = 0x00;//R2
	*(--sp_2) = 0x00;//R1
	*(--sp_2) = 0x00;//R0
	
  sp_3 = &stack_3[50];
	*(--sp_3) =  0x21000000;//xPSR
	*(--sp_3) = (uint32_t)&Task_3; // Program Counter
	*(--sp_3) = (uint32_t)&Task_3; // LR
	*(--sp_3) = 0x00;//R12
	*(--sp_3) = 0x00;//R3
	*(--sp_3) = 0x00;//R2
	*(--sp_3) = 0x00;//R1
	*(--sp_3) = 0x00;//R0

}
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
void SysTick_handler(void)
{
  /* Clear the Counter */
  SysTick->STCURRENT = 0x00000000;

  /* Save the updated current task's SP to its variable*/
  if((f_stack_1_init == true) ||(f_stack_2_init == true) || (f_stack_3_init == true))
  {
    store_TaskSP(curr_SP);
  }

  task_switch = task_switch % MAX_TASK_LIMIT;
	task_switch++;

	if(task_switch == 1)
  {
    curr_SP = &sp_1;
		__asm("LDR R7,=sp_1");
  }
	else if(task_switch == 2)
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

void main()
{
  /* Initialize the LED */
  LED_Init(LED_RED);
  LED_Init(LED_BLUE);
  LED_Init(LED_GREEN);

  /* Initialize the Timer used for delay */
  delayTimer_Init();
  Initialize_stack();

  scheduler_Init(1000000);

  while(1)
  {

  }

}

