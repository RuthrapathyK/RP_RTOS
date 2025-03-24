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
    delay(1000);
    LED_RED_OFF;
    delay(1000);
  }
}

void Task_B(void)
{
  while(1){
    LED_BLUE_ON;
    delay(2000);
    LED_BLUE_OFF;
    delay(2000);
  }
}
void Task_C(void)
{
  while(1){ 
    LED_GREEN_ON;
    delay(4000);
    LED_GREEN_OFF;
    delay(4000);
  }  
}

void main()
{
  /* Initialize the LED */
  LED_Init(LED_RED);
  LED_Init(LED_BLUE);
  LED_Init(LED_GREEN);

  /* Initialize the System Timer */
  SystemDelay_Init(1);

  /* Add Task for Scheduling */
  createTask(stack_TaskA,TASK_A_STACK_SIZE,&Task_A);
  createTask(stack_TaskB,TASK_B_STACK_SIZE,&Task_B);
  createTask(stack_TaskC,TASK_C_STACK_SIZE,&Task_C);

  /* Initialize the Scheduler */
  scheduler_Init(SCHEDULE_TIME_US);
  pushButton_Init();

  while(1)
  {
    
  }

}

