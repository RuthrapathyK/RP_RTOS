#include "typedef.h"
#include "led.h"
#include "timer.h"
#include "button.h"
#include "common.h"
#include "scheduler.h"
#include "tasks.h"
#include <stdbool.h>
#include <stddef.h>

void Task_1(void)
{
  while(1){
    LED_BLUE_OFF;
    LED_GREEN_OFF;
    LED_RED_ON;
  }
}

void Task_2(void)
{
  while(1){
    LED_RED_OFF;
    LED_GREEN_OFF;
    LED_BLUE_ON;
    
  }
}
void Task_3(void)
{
  while(1){
    LED_BLUE_OFF;
    LED_RED_OFF;  
    LED_GREEN_ON;
  }  
}
uint32_t task_A_stack[50]={0,};
uint32_t task_B_stack[50]={0,};
uint32_t task_C_stack[50]={0,};

Task_type Task_A_Object = {
  task_A_stack,
  NULL,
  50,
  &Task_1
};
Task_type Task_B_Object = {
  task_B_stack,
  NULL,
  50,
  &Task_2
};
Task_type Task_C_Object = {
  task_C_stack,
  NULL,
  50,
  &Task_3
};
void main()
{
  /* Initialize the LED */
  LED_Init(LED_RED);
  LED_Init(LED_BLUE);
  LED_Init(LED_GREEN);

  /* Initialize the Timer used for delay */
  delayTimer_Init();
  scheduler_Init(1000 * 1000);
  pushButton_Init();
  createTask(&Task_A_Object);
  createTask(&Task_B_Object);
  createTask(&Task_C_Object);
   while(1)
   {
    // __disable_irq();
    // GPIOF->DATA |= LED_GREEN; //Green LED
    // __enable_irq();

    // __disable_irq();
    // GPIOF->DATA &= ~LED_GREEN;
    // __enable_irq();
   }

}

