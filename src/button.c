#include "button.h"
#include "TM4C123GH6PM.h"
#include "led.h"

extern uint8_t volatile SemObject;

void pushButton_Init(void)
{
   /* Enables Clock for Port F */
   SYSCTL->RCGCGPIO =(1<<5);

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
  NVIC->EN0 |= 1<<30;
}

void GPIO_Port_F_handler(void)
{
  // Clear the interrupt
  GPIOF->ICR |= (1<<4);
  
    // __asm volatile (
    //     "LDR R0, =SemObject\n\t"
    //     "LDREX R1, [R0]\n\t"
    //     "MOV R1, #10\n\t"
    //     "STREX R2, R1, [R0]\n\t"
    // );
}
