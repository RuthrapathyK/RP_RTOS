#include "led.h"
#include "typedef.h"

uint32_t global_variable = 5;
const uint32_t global_const_variable = 10;
static uint8_t static_global_variable = 15;
extern uint16_t led_global_variable;
uint16_t global_uninitialized;

char array[11] = "Ruthrapathy";
char * arr = "Hello";

void main()
{
  static uint8_t static_local_variable = 20;

  //Enables Clock for Port F
  RCGCGPIO =(1<<5);
  
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

    led_global_variable++;

  }
}

