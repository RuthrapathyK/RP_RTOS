#ifndef __TASK_H
#define __TASK_H

#include "common.h"
#include "common.h"

#define MAX_TASK_LIMIT 10

typedef enum{
	Task_Ready,
	Task_Sleep,
}task_state_e;

typedef struct {
	uint32_t * stack; // Starting address of the stack and it keeps growing down
	uint32_t * stack_ptr; // Address of the variable that acts as Stack Pointer
	uint32_t stack_size; // Total size of the Stack
	uint8_t priority;  // Priority of the task
	void (*TaskfuncPtr)(void); // Address of the Application task function
	uint32_t nxtSchedTime; // Timestamp to again make the task ready
	void * syncPrim; //Loaded with Address of Synchronization Primitives to Unblock the Task
	task_state_e TaskState; // Current State of the Task
} Task_type;

void createTask(uint32_t *stackAddr, uint32_t stackSize_words, void (*taskPtr)(), uint8_t prio);

#endif