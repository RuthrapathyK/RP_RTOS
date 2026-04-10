#ifndef __TASK_H
#define __TASK_H

#include "common.h"

#define MAX_TASK_LIMIT 10

typedef enum{
	Task_Ready,
	Task_Sleep_Delay,
	Task_Sleep_Mutex,
	Task_Sleep_Semaphore
}task_state_e;

typedef struct {
	uint32_t * stack; // Starting address of the stack and it keeps growing down
	uint32_t * stack_ptr; // Address of the variable that acts as Stack Pointer
	uint32_t stack_size; // Total size of the Stack
	uint8_t priority;  // Priority of the task
	void (*TaskfuncPtr)(void); // Address of the Application task function
	uint32_t nxtSchedTime; // Timestamp to again make the task ready
	void * Task_Primitive; //Loaded with Address of the Task's Synchronization Primitive
	task_state_e TaskState; // Current State of the Task
} Task_type;

/**
 * @brief Initialize  and Schedule the New Task
 * 
 * @param stackAddr Starting address of the Stack pointer 
 * @param stackSize_words Total Size of Stack in Words(i.e 32 bits)
 * 						  Minimum 16 word size is required for scheduler opeartion itself. So choose >16
 * @param taskPtr Address of the Task Function
 * @param prio Priority of the Task. 1 is the highest priority and 255 is the lowest priority
 */
void OS_CreateTask(uint32_t *stackAddr, uint32_t stackSize_words, void (*taskPtr)(), uint8_t prio);

#endif