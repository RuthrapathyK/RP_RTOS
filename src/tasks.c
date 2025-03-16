#include "tasks.h"

#include <stdbool.h>
#include "typedef.h"

#define MAX_TASK_LIMIT 3
static uint32_t Max_Task = 0; 

Task_type Task_Table[MAX_TASK_LIMIT] = {0,};

static void initStack(Task_type * tsk)
{
	// Initialize the Stack Pointer for the Task
  	tsk->stack_ptr = &(tsk->stack[tsk->stack_size]);

	// Load Register value to the Stack
	*(--tsk->stack_ptr) =  0x21000000;//xPSR
	*(--tsk->stack_ptr) = (uint32_t)tsk->TaskfuncPtr; // Program Counter
	*(--tsk->stack_ptr) = (uint32_t)tsk->TaskfuncPtr; // LR
	*(--tsk->stack_ptr) = 0x00;//R12
	*(--tsk->stack_ptr) = 0x00;//R3
	*(--tsk->stack_ptr) = 0x00;//R2
	*(--tsk->stack_ptr) = 0x00;//R1
	*(--tsk->stack_ptr) = 0x00;//R0
}
void createTask(uint32_t task_id, Task_type * task)
{
	// Initialize the Stack of the Task with default register values
	initStack(task);

	// Load the Task config to the Table and increament the Maximum Task number
	Task_Table[Max_Task++] = *task;

}