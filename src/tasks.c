#include "tasks.h"

#include "common.h"
#include "common.h"

uint32_t Max_SchTask = 0; 

volatile Task_type PrioTask_Table[MAX_TASK_LIMIT] = {0,};
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
 * @brief The function adds the task passed and rearrage the table in ascending Priority
 * 
 * @param taskObject Task that needs to be added in the Priority Table
 */
static void Add_to_PrioTaskTable(Task_type * taskObject)
{
	Task_type tempObj_1, tempObj_2;

	// Check the input parameters are within range
	ASSERT((taskObject != NULL) && (taskObject->priority != 0));
	
	// Increament the Maximum Scheduled Task counter
	Max_SchTask++;

	// Check the Task scheduled is within the TaskTable size
	ASSERT(Max_SchTask <= MAX_TASK_LIMIT);

	for(uint32_t iter = 0; iter < Max_SchTask; iter++)
	{
		if(PrioTask_Table[iter].priority == 0)
		{
			PrioTask_Table[iter] = *taskObject;
			break;
		}
		if(taskObject->priority < PrioTask_Table[iter].priority)
		{
			tempObj_1 = PrioTask_Table[iter];
			PrioTask_Table[iter] = *taskObject;

			for(iter += 1; iter < Max_SchTask; iter++)
			{
				tempObj_2 = PrioTask_Table[iter];
				PrioTask_Table[iter] = tempObj_1;
				tempObj_1 = tempObj_2;
			}
			break;
		}
	}
}
/**
 * @brief Initialize  and Schedule the New Task
 * 
 * @param stackAddr Starting address of the Stack pointer 
 * @param stackSize_words Total Size of Stack in Words(i.e 32 bits)
 * 						  Minimum 16 word size is required for scheduler opeartion itself. So choose >16
 * @param taskPtr Address of the Task Function
 * @param prio Priority of the Task. 1 is the highest priority and 255 is the lowest priority
 */
void createTask(uint32_t *stackAddr, uint32_t stackSize_words, void (*taskPtr)(), uint8_t prio)
{
	// Check for valid Task Input parameters
	ASSERT((stackAddr != NULL) && (taskPtr != NULL) && (stackSize_words > 16) && (Max_SchTask < MAX_TASK_LIMIT));

	// Load the Input parameters to Temporary Task Object
	Task_type TaskObj = {
		.stack = stackAddr,
		.stack_ptr = NULL,
		.stack_size = stackSize_words,
		.priority = prio,
		.TaskfuncPtr = taskPtr,
		.nxtSchedTime = 0,
		.syncPrim = NULL,
		.TaskState = Task_Ready
	};

	// Initialize the Stack of the Task with default register values
	Init_TaskStack(&TaskObj);

	// Load the Task config to the Table
	Add_to_PrioTaskTable(&TaskObj);
}