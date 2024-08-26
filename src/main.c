#include "typedef.h"
#include "TM4C123GH6PM.h"
#include "led.h"

void timer_delay(uint32_t milliseconds)
{
  /* Ensure Timer 0 is disabled */
  TIMER0->CTL &= ~((1<<0) | (1<<8));

  /* Write Timer 0 as 32-bit to configuration Register */
  TIMER0->CFG = 0x00;

  /* Configure Timer 0 as one-shot mode */
  TIMER0->TAMR |= 1;

  /* Configure Timer 0 to Count Down */
  TIMER0->TAMR &= ~(1<<4);

  /* Load the Interval Value */
  TIMER0->TAILR = (uint32_t)16000 * milliseconds;

  /* Halt Timer counter when in Debug mode */
  TIMER0->CTL |= ((1<<1)|(1<<9));

  /* Enable Timer 0*/
  TIMER0->CTL |= ((1<<0) | (1<<8));

  /* Poll till expiry */
  while(!(TIMER0->RIS & 0x01))
  ;

  /* Clear the Interrupt status*/
  TIMER0->ICR |= 1<<0;
}

void main()
{
  LED_Init(LED_RED);

  /* Enable clock for General Purpose Timer 0 Module */
  SYSCTL->RCGCTIMER |= 1<<0;

  while(1)
  {
    LED_RED_OFF;
    timer_delay(10000);
    LED_RED_ON;
    timer_delay(10000);
  }
}

