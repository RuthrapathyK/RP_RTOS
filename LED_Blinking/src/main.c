#include "typedef.h"
#include "TM4C123GH6PM.h"
#include "led.h"

void main()
{

  //Enables Clock for Port F
  SYSCTL->RCGCGPIO =(1<<5);
  
  LED_Init(LED_RED);
  LED_Init(LED_BLUE);
  LED_Init(LED_GREEN);

  while(1)
  {
    //Toggle the LEDs
    LED_RED_ON;
     delay(1000);
    LED_RED_OFF;
    delay(1000);
    
    LED_BLUE_ON;
    delay(1000);
    LED_BLUE_OFF;
    delay(1000);
    
    LED_GREEN_ON;
    delay(1000);
    LED_GREEN_OFF;
    delay(1000);
    
  }
}

