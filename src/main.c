#include "typedef.h"
#include "TM4C123GH6PM.h"
#include "led.h"

void timer_delay(void)
{
    /* Ensure Timer 0 is disabled */
  if((TIMER0->CTL & 0x01) != 0)
    TIMER0->CTL &= ~(1<<0);

  /* Write 0 to configuration Register */
  TIMER0->CFG = 0x00;

  /* Configure Timer 0 as one-shot mode */
  TIMER0->TAMR |= 1;

  /* Set the Prescalar */
  TIMER0->TAPR = 159;

  /* Load the Interval Value */
  TIMER0->TAILR = 1000000;

  /* Enable Timer 0*/
  TIMER0->CTL |= (1<<0);

  /* Poll till expiry */
  while(!(TIMER0->RIS & 0x01))
  ;

  /* Clear the Interrupt status*/
  TIMER0->ICR |= 1<<0;
}
void main()
{

  //Enables Clock for Port F
  SYSCTL->RCGCGPIO =(1<<5);

  LED_Init(LED_RED);

  /* Enable clock for General Purpose Timer 0 Module */
  SYSCTL->RCGCTIMER |= 1<<0;

  while(1)
  {
    LED_RED_OFF;
    timer_delay();
    LED_RED_ON;
    timer_delay();
  }
}

