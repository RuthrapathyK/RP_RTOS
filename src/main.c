#include "typedef.h"
#include "led.h"
#include "timer.h"

uint8_t interrupt_call = 0;

void SysTick_handler(void)
{
  /* Clear the Counter */
  SysTick->STCURRENT = 0x00000000;

  interrupt_call = !interrupt_call;

  if(interrupt_call)
    LED_RED_OFF;
  else
    LED_RED_ON;
      
}
void main()
{
  /* Initialize the LED */
  LED_Init(LED_RED);

  /* Initialize the Timer used for delay */
  delayTimer_Init();

  scheduler_Init(1000000);

  while(1)
  {

  }
}

