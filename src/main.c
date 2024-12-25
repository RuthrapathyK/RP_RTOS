#include "typedef.h"
#include "led.h"
#include "timer.h"
#include <stdbool.h>

#define MAX_TASK_LIMIT 3

uint8_t task_switch = 0;

uint32_t stack_1[50];
uint32_t * sp_1 = 0;

uint32_t stack_2[50];
uint32_t * sp_2 = 0;

uint32_t stack_3[50];
uint32_t * sp_3 = 0;

void Task_1(void)
{
  while(1){
    LED_RED_ON;
    delayTimer(100);
    LED_RED_OFF;
    delayTimer(100);
  }
}

void Task_2(void)
{
  while(1){
    LED_BLUE_ON;
    delayTimer(250);
    LED_BLUE_OFF;
    delayTimer(250);
  }
}
void Task_3(void)
{
  while(1){
    LED_GREEN_ON;
    delayTimer(500);
    LED_GREEN_OFF;
    delayTimer(500);
  }  
}
inline void __attribute__((always_inline))Initialize_stack(void)
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

void SysTick_handler(void)
{
  /* Clear the Counter */
  SysTick->STCURRENT = 0x00000000;

  task_switch = task_switch % MAX_TASK_LIMIT;
	task_switch++;

  Initialize_stack();

	if(task_switch == 1)
		__asm("LDR R10,=sp_1");
	else if(task_switch == 2)	
		__asm("LDR R10,=sp_2");
	else
		__asm("LDR R10,=sp_3");

	__asm("LDR R10,[R10]");
	__asm("MOV SP,R10");
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
    __asm("MRS R9, IPSR");
  }

}

