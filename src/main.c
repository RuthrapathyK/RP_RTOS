#include "typedef.h"
#include "led.h"
#include "timer.h"

void main()
{
  /* Initialize the LED */
  LED_Init(LED_RED);

  /* Initialize the Timer used for delay */
  delayTimer_Init();

  while(1)
  {
    LED_RED_OFF;
    delayTimer(5000);
    LED_RED_ON;
    delayTimer(5000);
  }
}

