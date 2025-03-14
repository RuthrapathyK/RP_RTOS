#include "typedef.h"
#include "led.h"
#include "timer.h"
#include "button.h"
#include <stdbool.h>

volatile uint32_t counter = 0;

void Task_1(void)
{
  f_stack_1_init = true;
  while(1){
    LED_BLUE_OFF;
    LED_GREEN_OFF;
    LED_RED_ON;
  }
}

void Task_2(void)
{
  f_stack_2_init = true;
  while(1){
    LED_RED_OFF;
    LED_GREEN_OFF;
    LED_BLUE_ON;
    
  }
}
void Task_3(void)
{
  f_stack_3_init = true;
  while(1){
    LED_BLUE_OFF;
    LED_RED_OFF;  
    LED_GREEN_ON;
  }  
}

void main()
{
  /* Initialize the LED */
  LED_Init(LED_RED);
  LED_Init(LED_BLUE);
  LED_Init(LED_GREEN);

  /* Initialize the Timer used for delay */
  delayTimer_Init();
  Initialize_stack();
  //scheduler_Init(500 * 1000);

  pushButton_Init();

   while(1)
   {
    __disable_irq();
    GPIOF->DATA |= (1<<3); //Green LED
    __enable_irq();

    __disable_irq();
    GPIOF->DATA &= ~(1<<3);
    __enable_irq();
   }

}

