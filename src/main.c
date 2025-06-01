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

#define TASK_A_STACK_SIZE 250
#define TASK_B_STACK_SIZE 250
#define TASK_C_STACK_SIZE 250
#define IDLE_TASK_STACK_SIZE 50

uint32_t stack_TaskA[TASK_A_STACK_SIZE]={0};
uint32_t stack_TaskB[TASK_B_STACK_SIZE]={0};
uint32_t stack_TaskC[TASK_C_STACK_SIZE]={0};
uint32_t stack_IdleTask[IDLE_TASK_STACK_SIZE]={0};

uint32_t SemObject = 1;

void Task_A(void)
{
  while(1){

    semTake(&SemObject);

    for(uint32_t iter = 0; iter < 100 * 1000; iter++)
    {
      LED_RED_ON;
      LED_RED_OFF;
    }
    OS_delay(1000);
  }
}

void Task_B(void)
{
  while(1){

    semGive(&SemObject);
    
    for(uint32_t iter = 0; iter < 100 * 1000; iter++)
    {
      LED_BLUE_ON;
      LED_BLUE_OFF;
    }
    OS_delay(1000);
  }
}
void Task_C(void)
{
  while(1){
    for(uint32_t iter = 0; iter < 100 * 1000; iter++)
    {
      LED_GREEN_ON;
      LED_GREEN_OFF;
    }
    OS_delay(1000);
  }    
}
void IdleTask(void)
{
  while(1){
    TESTPIN_ON;
    TESTPIN_OFF;
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
  createTask(stack_TaskC,TASK_C_STACK_SIZE,&Task_C, 3);
  createTask(stack_TaskB,TASK_B_STACK_SIZE,&Task_B, 2);
  createTask(stack_TaskA,TASK_A_STACK_SIZE,&Task_A, 1);
  
  /* Set the Systick and PendSV to have Priority 1*/
  SCB->SYSPRI3 &= ~(0x07 << 29);  // SysTick
  SCB->SYSPRI3 &= ~(0x07 << 21);  // PendSV

  SCB->SYSPRI3 |= (0x01 << 29); // SysTick
  SCB->SYSPRI3 |= (0x01 << 21); // PendSV

  pushButton_Init();

  /* Idle task should have the Least priority than any other tasks created */
  createTask(stack_IdleTask,IDLE_TASK_STACK_SIZE,&IdleTask, 255);

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