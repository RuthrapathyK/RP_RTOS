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
    OS_delay(1000);
    LED_RED_OFF;
    OS_delay(1000);
  }
}

void Task_B(void)
{
  while(1){
    LED_BLUE_ON;
    OS_delay(2000);
    LED_BLUE_OFF;
    OS_delay(2000);
  }
}
void Task_C(void)
{
  while(1){
    LED_GREEN_ON;
    OS_delay(4000);
    LED_GREEN_OFF;
    OS_delay(4000);
  }    
}

void main()
{
  /* Initialize the LED */
  LED_Init(LED_RED);
  LED_Init(LED_BLUE);
  LED_Init(LED_GREEN);
  TestPin_Init();
  /* Initialize the System Timer */
  SystemTimer_Init(1);

  /* Add Task for Scheduling */
  createTask(stack_TaskA,TASK_A_STACK_SIZE,&Task_A);
  createTask(stack_TaskB,TASK_B_STACK_SIZE,&Task_B);
  createTask(stack_TaskC,TASK_C_STACK_SIZE,&Task_C);
  
  /* Set the Systick and PendSV to have Priority 1*/
  SCB->SYSPRI3 &= ~(0x07 << 29);  // SysTick
  SCB->SYSPRI3 &= ~(0x07 << 21);  // PendSV

  SCB->SYSPRI3 |= (0x01 << 29); // SysTick
  SCB->SYSPRI3 |= (0x01 << 21); // PendSV

  pushButton_Init();

  /* Initialize and start the Scheduler */
  scheduler_Init(SCHEDULE_TIME_US);

  while(1)
  {
    /* This point shall never be reached*/    
  }
}

/**
 * @brief PB3 is the Test Pin
 * 
 */
void TestPin_Init(void)
{
  /* Enables Clock for Port F */
  SYSCTL->RCGCGPIO |=(1<<1);

  /* Set the Pin Direction as Output */
  GPIOB->DIR |=(1<<3);
  
  /*Select GPIO as pin Function */
  GPIOB->AFSEL &= ~(1<<3);
  
  /* Configure as Digital I/O */
  GPIOB->DEN |=(1<<3);
}