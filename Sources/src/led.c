#include "led.h"

/* Description : This function adds delay for the value entered */
void delay(int count)
{
  for(volatile int tem=0;tem<count;tem++)
  {
    for( volatile int tem2=0;tem2<1000;tem2++)
    {

    }
  }
}

/* Description : This function initializes all the LEDS */
void LED_Init(unsigned int led)
{
    /* Set the Pin Direction as Output */
  GPIODIR |=(led);
  
  /*Select GPIO as pin Function */
  GPIOAFSEL &= ~(led);
  
  /* Configure as Digital I/O */
  GPIODEN |=(led);
}