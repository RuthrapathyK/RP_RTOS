#include "common.h"
#include "led.h"
#include "timer.h"
#include "button.h"
#include "common.h"
#include "scheduler.h"
#include "tasks.h"

#define SCHEDULE_TIME_MS 10

#define SCHEDULE_TIME_FACTOR 1000
#define SCHEDULE_TIME_US (SCHEDULE_TIME_FACTOR * SCHEDULE_TIME_MS)

#define TASK_A_STACK_SIZE 200
#define TASK_B_STACK_SIZE 200
#define TASK_C_STACK_SIZE 200

uint32_t stack_TaskA[TASK_A_STACK_SIZE]={0};
uint32_t stack_TaskB[TASK_B_STACK_SIZE]={0};
uint32_t stack_TaskC[TASK_C_STACK_SIZE]={0};

void Task_A(void)
{
  while(1){
    LED_RED_ON;
    LED_RED_OFF;
  }
}

void Task_B(void)
{
  while(1){
    LED_BLUE_ON;
    LED_BLUE_OFF;
  }
}
void Task_C(void)
{
  while(1){
    LED_GREEN_ON;
    LED_GREEN_OFF;
  }    
}

void main()
{
  /* Initialize the LED */
  LED_Init(LED_RED);
  LED_Init(LED_BLUE);
  LED_Init(LED_GREEN);

  /* Initialize the System Timer */
  SystemTimer_Init(1);

  /* Add Task for Scheduling */
  createTask(stack_TaskA,TASK_A_STACK_SIZE,&Task_A);
  createTask(stack_TaskB,TASK_B_STACK_SIZE,&Task_B);
  createTask(stack_TaskC,TASK_C_STACK_SIZE,&Task_C);
  
  /* Set the Systick to Low Pririty than PendSV */
  SCB->SYSPRI3 &= ~(0x07 << 29);  // SysTick
  SCB->SYSPRI3 &= ~(0x07 << 21);  // PendSV

  SCB->SYSPRI3 |= (0x01 << 29); // SysTick
  SCB->SYSPRI3 |= (0x01 << 21); // PendSV

  /* Initialize the Scheduler */
  scheduler_Init(SCHEDULE_TIME_US);
  pushButton_Init();

  while(1)
  {
    
  }

}

