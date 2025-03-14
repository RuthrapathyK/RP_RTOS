#include <stdbool.h>
#include "typedef.h"

#define MAX_TASK_LIMIT 3

volatile uint32_t stack_1[50];
volatile uint32_t * sp_1 = 0;
volatile bool f_stack_1_init = false;

volatile uint32_t stack_2[50];
volatile uint32_t * sp_2 = 0;
volatile bool f_stack_2_init = false;

volatile uint32_t stack_3[50];
volatile uint32_t * sp_3 = 0;
volatile bool f_stack_3_init = false;

void Initialize_stack(void)
{
  sp_1 = &stack_1[50];
	*(--sp_1) =  0x21000000;//xPSR
	*(--sp_1) = (uint32_t)&Task_1; // Program Counter
	*(--sp_1) = (uint32_t)&Task_1; // LR
	*(--sp_1) = 0x00;//R12
	*(--sp_1) = 0x00;//R3
	*(--sp_1) = 0x00;//R2
	*(--sp_1) = 0x00;//R1
	*(--sp_1) = 0x00;//R0
	
  sp_2 = &stack_2[50];
	*(--sp_2) =  0x21000000;//xPSR
	*(--sp_2) = (uint32_t)&Task_2; // Program Counter
	*(--sp_2) = (uint32_t)&Task_2; // LR
	*(--sp_2) = 0x00;//R12
	*(--sp_2) = 0x00;//R3
	*(--sp_2) = 0x00;//R2
	*(--sp_2) = 0x00;//R1
	*(--sp_2) = 0x00;//R0
	
  sp_3 = &stack_3[50];
	*(--sp_3) =  0x21000000;//xPSR
	*(--sp_3) = (uint32_t)&Task_3; // Program Counter
	*(--sp_3) = (uint32_t)&Task_3; // LR
	*(--sp_3) = 0x00;//R12
	*(--sp_3) = 0x00;//R3
	*(--sp_3) = 0x00;//R2
	*(--sp_3) = 0x00;//R1
	*(--sp_3) = 0x00;//R0

}