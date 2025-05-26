
#include "timer.h"
#include "TM4C123GH6PM.h"

volatile uint32_t SystemTime_Count = 0;

/**
 * @brief The function is used to initialize the TIMER 0 in one-shot downcounting modes.
 *        This will also initialize the TIMER 0 in concatenation mode (ie. as a 32bit Timer)
 *        Note: Prescalar is NA when the timer is configured as 32bit
 * 
 */
void delayTimer_Init(void)
{
  /* Enable clock for General Purpose Timer 0 Module */
  SYSCTL->RCGCTIMER |= 1<<0;

  /* Wait for 3 system clock cycle */
  __asm("NOP");__asm("NOP");__asm("NOP");

  /* Ensure Timer 0 is disabled */
  TIMER0->CTL &= ~((1<<0) | (1<<8));

  /* Write Timer 0 as 32-bit to configuration Register */
  TIMER0->CFG = 0x00;

  /* Configure Timer 0 as one-shot mode */
  TIMER0->TAMR |= 1;

  /* Configure Timer 0 to Count Down */
  TIMER0->TAMR &= ~(1<<4);  

  /* Halt Timer counter when in Debug mode */
  TIMER0->CTL |= ((1<<1)|(1<<9));  
}

/**
 * @brief The function is used to create a blocking delay in milliseconds. For that it uses TIMER0 GPTM 
 *        in concatenation mode with system clock = 16MHz.
 *        Note: The maximum delay it can generate is 268435ms
 * 
 * @param mSec delay time in milli-seconds
 */
void delayTimer(uint32_t mSec)
{
  /* Check of Preconditions */
  ASSERT(mSec <= 268435);

  /* Load the Interval Value */
  TIMER0->TAILR = (uint32_t)16000 * mSec;

  /* Enable Timer 0*/
  TIMER0->CTL |= ((1<<0) | (1<<8));

  /* Poll till expiry */
  while(!(TIMER0->RIS & 0x01))
  ;

  /* Clear the Interrupt status*/
  TIMER0->ICR |= 1<<0;

  /* Ensure Timer 0 is disabled */
  TIMER0->CTL &= ~((1<<0) | (1<<8));
}
/**
 * @brief The function is used to create a blocking delay. It used traditional for loop
 * 
 * @param mSec delay time in approximate milli-seconds
 */
void delayLoop(uint32_t mSec)
{
  for (volatile uint32_t i = 0; i < mSec ; i++)
  {
    for(volatile uint32_t j =0; j < 500; j++)
    {
      __asm("NOP");
    }
  }
}
/**
 * @brief System Timer ISR Handler. This will be called every 1ms
 * 
 */
void Timer_0A_16_32_handler(void)
{
  /* Clear the Interrupt status*/
  TIMER0->ICR |= 1<<0;
  
  /* Increament the System Timer Counter */
  ++SystemTime_Count;
}
/**
 * @brief The function is used to initialize the TIMER 0 in Periodic Downcounting modes.
 *        This will also initialize the TIMER 0 in concatenation mode (ie. as a 32bit Timer)
 *        Note: Prescalar is NA when the timer is configured as 32bit
 * 
 * @param mSec Periodic counter increament time
 */
void SystemTimer_Init(uint32_t mSec)
{
  /* Check of Preconditions */
  ASSERT(mSec <= 268435);

  /* Enable clock for General Purpose Timer 0 Module */
  SYSCTL->RCGCTIMER |= 1<<0;

  /* Wait for 3 system clock cycle */
  __asm("NOP");__asm("NOP");__asm("NOP");

  /* Ensure Timer 0 is disabled */
  TIMER0->CTL &= ~((1<<0) | (1<<8));

  /* Write Timer 0 as 32-bit to configuration Register */
  TIMER0->CFG = 0x00;

  /* Configure Timer 0 as Periodic mode */
  TIMER0->TAMR |= 1<<1;

  /* Configure Timer 0 to Count Down */
  TIMER0->TAMR &= ~(1<<4);  

  /* Halt Timer counter when in Debug mode */
  TIMER0->CTL |= ((1<<1)|(1<<9));  

  /* Enable Timer Module Interrupt */
  TIMER0->IMR |= 1<<0;

  /* Enable NVIC Interrupt */
  NVIC->EN0 |= 1<<19;

  /* Clear the Interrupt status*/
  TIMER0->ICR |= 1<<0;

  /* Load the Interval Value */
  TIMER0->TAILR = (uint32_t)16000 * mSec;

  /* Enable Timer 0*/
  TIMER0->CTL |= ((1<<0) | (1<<8));
}
/**
 * @brief The function is inlined and will return the current system time counter value
 * 
 */
inline uint32_t __attribute__((always_inline))getSystemTime(void)
{
  return SystemTime_Count;
}
/**
 * @brief The Function creates a delay of input time in milliseconds without blocking the Timer Peripheral
 * 
 * @param mSec Delay time in approximate milli-seconds
 */
void delay(uint32_t mSec)
{
  uint32_t start = getSystemTime();

  /* Wait untill delay time is elapsed */
  while((getSystemTime() - start) < mSec)
  ;
}
