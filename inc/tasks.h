#ifndef __TASK_H
#define __TASK_H

#include "typedef.h"
#include <stdbool.h>
typedef struct {
	bool f_init;  // Flag to check whether the Task is called atleast once
	uint32_t * stack; // Starting address of the stack and it keeps growing down
	uint32_t * stack_ptr; // Address of the variable that acts as Stack Pointer
	uint32_t stack_size; // Total size of the Stack
	void (*TaskfuncPtr)(void); // Address of the Application task function
} Task_type;

void createTask(uint32_t task_id, Task_type * task);
#endif