#include "tasks.h"

#include "common.h"
#include "common.h"

uint32_t Max_Task = 0; 

volatile Task_type Task_Table[MAX_TASK_LIMIT] = {0,};
/**
 * @brief The function will initialize the private stack of the task with the initial values
 * 
 * @param tsk Pointer to the Task
 */
static void Init_TaskStack(Task_type * tsk)
{
	// Check for Valid Input Parameters
	ASSERT((tsk != NULL) && (tsk->stack != NULL) && (tsk->TaskfuncPtr != NULL));

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
	*(--tsk->stack_ptr) = 0x00;//R11
	*(--tsk->stack_ptr) = 0x00;//R10
	*(--tsk->stack_ptr) = 0x00;//R9
	*(--tsk->stack_ptr) = 0x00;//R8
	*(--tsk->stack_ptr) = 0x00;//R7
	*(--tsk->stack_ptr) = 0x00;//R6
	*(--tsk->stack_ptr) = 0x00;//R5
	*(--tsk->stack_ptr) = 0x00;//R4
}
/**
 * @brief Initialize  and Schedule the New Task
 * 
 * @param stackAddr Starting address of the Stack pointer 
 * @param stackSize_words Total Size of Stack in Words(i.e 32 bits)
 * 						  Minimum 16 word size is required for scheduler opeartion itself. So choose >16
 * @param taskPtr Address of the Task Function
 */
void createTask(uint32_t *stackAddr, uint32_t stackSize_words, void (*taskPtr)())
{
	// Check for valid Task Input parameters
	ASSERT((stackAddr != NULL) && (taskPtr != NULL) && (stackSize_words > 16));

	// Load the Input parameters to Temporary Task Object
	Task_type TaskObj = {
		stackAddr,
		NULL,
		stackSize_words,
		taskPtr};

	// Initialize the Stack of the Task with default register values
	Init_TaskStack(&TaskObj);

	// Load the Task config to the Table and increament the Maximum Task number
	Task_Table[Max_Task++] = TaskObj;
}