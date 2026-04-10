#include "led.h"
#include "common.h"

/* Description : This function initializes all the LEDS */
void LED_Init(uint32_t led)
{
  /* Enables Clock for Port F */
  SYSCTL->RCGCGPIO |= (1<<5);

  /* Set the Pin Direction as Output */
  GPIOF->DIR |=(led);
  
  /*Select GPIO as pin Function */
  GPIOF->AFSEL &= ~(led);
  
  /* Configure as Digital I/O */
  GPIOF->DEN |=(led);
}