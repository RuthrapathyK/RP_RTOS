#include "typedef.h"
#include "led.h"
#include "timer.h"

uint8_t task_switch = 0;
uint32_t * sp = 0x0;

void Led_On(void)
{
  while(1)
    LED_RED_ON;
}

void Led_Off(void)
{
  while(1){
    LED_BLUE_ON;
    delayTimer(100);
    LED_BLUE_OFF;
    delayTimer(100);
  }
}
void SysTick_handler(void)
{
  /* Clear the Counter */
  SysTick->STCURRENT = 0x00000000;

  task_switch = !task_switch;

   if(task_switch){
    __asm("add	r9, sp, #0x18"); // Locate the LR in Stack frame and store that address in R9
    __asm("MOV r10, #0x26c"); // Load the Led On function address in  R10
    __asm("STR r10,[r9]"); // Store the Led On function address in LR of stack frame

    __asm("add r9, #4");
    __asm("SUB r10, #1"); // Load the Led On function address in  R10
    __asm("STR r10,[r9]"); // Store the Led On function address in PC of stack frame

     //*(uint32_t *)0x20000FDC = &Led_On; // Load LR register
     //*(uint32_t *)0x20000FE0 = &Led_On - 1; // Load PC register
     }

   else{
    __asm("add	r9, sp, #0x18"); // Locate the LR in Stack frame and store that address in R9
    __asm("MOV r10, #0x27c"); // Load the Led On function address in  R10
    __asm("STR r10,[r9]"); // Store the Led On function address in LR of stack frame

    __asm("add r9, #4");
    __asm("SUB r10, #1"); // Load the Led On function address in  R10
    __asm("STR r10,[r9]"); // Store the Led On function address in PC of stack frame

     //*(uint32_t *)0x20000FDC = &Led_Off; // Load LR register
     //*(uint32_t *)0x20000FE0 = &Led_Off - 1; // Load PC register
     }      
}

void main()
{
  /* Initialize the LED */
  LED_Init(LED_RED);
  LED_Init(LED_BLUE);
  /* Initialize the Timer used for delay */
  delayTimer_Init();

  scheduler_Init(1000000);

  while(1);

}

