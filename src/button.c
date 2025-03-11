#include "button.h"
#include "TM4C123GH6PM.h"

extern volatile uint32_t counter;

void pushButton_Init(void)
{
   //Select GPIO as Alternate Functions
   GPIOF->AFSEL &= ~(1<<4);

   // Pull up the pin
   GPIOF->PUR |= (1<<4);
 
   // Enable Digital I/O
   GPIOF->DEN |= (1<<4);

   // Disable GPIO Interrupt 
   GPIOF->IM &= (1<<4);
  
  // Configure it as Edge sensitive
  GPIOF->IS &= ~(1<<4);

   // Configure Falling edge for Interrupt Trigger
   GPIOF->IEV &= ~(1<<4);

  // Clear if it already has a pending interrupt
  GPIOF->RIS &= ~(1<<4);

  // Enable GPIO Interrupt 
  GPIOF->IM |= (1<<4);

  // Enable NVIC interrupt for GPIO Port F
  *((uint32_t *)(0xE000E000 + 0x100)) |= 1<<30;
}
