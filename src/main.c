#include "typedef.h"
#include "led.h"
#include "timer.h"

uint8_t interrupt_call = 0;

void Timer_0A_16_32_handler(void)
{
  /* Clear the Interrupt status*/
  TIMER0->ICR |= 1<<0;

  interrupt_call = 1;
}

void main()
{
  /* Initialize the LED */
  LED_Init(LED_RED);

  /* Initialize the Timer used for delay */
  delayTimer_Init();

  /* Interrupt configuration */
  TIMER0->IMR |= (1<<0);

  /* Enable NVIC interrupt */
  *((uint32_t *)(0xE000E000 + 0x100)) |= (1<<19);


  while(1)
  {
    LED_RED_OFF;
    delayTimer(5000);
    LED_RED_ON;
    delayTimer(5000);
  }
}

