#include "common.h"
#include "OS/scheduler.h"
#include "OS/tasks.h"
#include "../src/Services/Debug/testpin.h"
#include "../src/Drivers/Timer/timer.h"
#include "../src/BSP/Button/button.h"
#include "../src/Drivers/NVIC/nvic.h"
#include "../src/Drivers/PinMux/pinconfig.h"

#define SCHEDULE_TIME_MS 10

#define SCHEDULE_TIME_FACTOR 1000
#define SCHEDULE_TIME_US (SCHEDULE_TIME_FACTOR * SCHEDULE_TIME_MS)

uint32_t TaskStack_1[200];
uint32_t TaskStack_2[200];
uint32_t TaskStack_3[200];
uint32_t counter_1 = 0;
uint32_t counter_2 = 0;
uint32_t counter_3 = 0;

void Task_1(void)
{
  while(1)
  {
    counter_1++;
    OS_delay(1000);
  }
}

void Task_2(void)
{
  while(1)
  {
    counter_2++;
    OS_delay(1000);
  }
}

void Task_3(void)
{
  while(1)
  {
    counter_3++;
    OS_delay(1000);
  }
}

void Peripherals_Init(void)
{
  TestPin_Init();
  PushButton_Init();
}

void Pins_Init(void)
{
  /* Enable Push Button Pin */
  Pin_Config(Port_PF, 4, PF4_GPIO);
}

void Serices_Init(void)
{
  /* Add Task for Scheduling */
  OS_CreateTask(TaskStack_1, sizeof(TaskStack_1) / 4, &Task_1, 1);
  OS_CreateTask(TaskStack_2, sizeof(TaskStack_2) / 4, &Task_2, 1);
  OS_CreateTask(TaskStack_3, sizeof(TaskStack_3) / 4, &Task_3, 1);

  /* Initialize the System Timer */
  SystemTimer_Start(1);
}

void Interrupts_Init(void)
{
  /* Disable Global Interrupt */
  __disable_irq();

  /* Enable/Disable Nested Vector Interrupts */
  NVIC_enableInterrupt(GPIO_Port_F_IRQ);

  /* Enable Global Interrupt */
  __enable_irq();
}

int main()
{

  Peripherals_Init();
  Pins_Init();
  Serices_Init();
  Interrupts_Init();

  /* Initialize and start the Scheduler */
  OS_SchedulerRun(SCHEDULE_TIME_US);

  while(1)
  {
    /* This point shall never be reached*/    
  }

  return 0;
}
