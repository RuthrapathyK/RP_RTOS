#include "led.h"
#include "typedef.h"

/* Description : This function adds delay for the value entered */
void delay(uint32_t count)
{
  for(volatile uint32_t tem=0;tem<count;tem++)
  {
    for( volatile uint32_t tem2=0;tem2<1000;tem2++)
    {
        __asm("NOP");
    }
  }
}

/* Description : This function initializes all the LEDS */
void LED_Init(uint32_t led)
{
    /* Set the Pin Direction as Output */
  GPIOF->DIR |=(led);
  
  /*Select GPIO as pin Function */
  GPIOF->AFSEL &= ~(led);
  
  /* Configure as Digital I/O */
  GPIOF->DEN |=(led);
}