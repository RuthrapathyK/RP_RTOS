#ifndef __QUEUE_H
#define __QUEUE_H

#include "common.h"

typedef enum{
    Queue_Empty,
    Queue_NotEmpty
}Queue_Emptyness_e;

typedef enum{
    Queue_Full,
    Queue_NotFull
}Queue_Fullness_e;

typedef enum{
    Queue_Overflow,
    Queue_NoOverflow
}Queue_OverFlowStatus_e;

typedef struct{
  volatile uint32_t eIdx;
  volatile uint32_t dIdx;
  uint8_t *QBuff;
  uint32_t QBuff_Max;
  volatile uint32_t eCount;
  volatile uint32_t dCount;
  volatile uint32_t OverFlow_DetectedCount;
  volatile uint32_t OverFlow_ResolvedCount;
  uint32_t QBuff_IdxSize;
}Queue_t;

/**
 * @brief Initializes a queue with the specified buffer and specifications.
 *
 * Configures a queue instance with a data buffer, element size, and maximum number of elements.
 * Sets all internal counters and indices to their default values.
 *
 * @param inst Pointer to the queue instance to initialize
 * @param pBuf Pointer to the data buffer to use for queue storage
 * @param IdxSize Size of each individual element in bytes
 * @param IdxMax Maximum number of elements the queue can hold
 */
void Queue_Init(Queue_t *inst, uint8_t *pBuf, uint32_t IdxSize, uint32_t IdxMax);

/**
 * @brief Adds data to the queue.
 *
 * Enqueues an element into the queue. If the queue is full, sets the overflow flag.
 * The data is copied element by element based on the configured element size.
 *
 * @param inst Pointer to the queue instance
 * @param InData Pointer to the data to enqueue
 */
void Queue_Enqueue(Queue_t *inst, uint8_t *InData);

/**
 * @brief Removes and retrieves data from the queue.
 *
 * Dequeues the first element from the queue and copies it to the output buffer.
 * The data is copied element by element based on the configured element size.
 *
 * @param inst Pointer to the queue instance
 * @param OutData Pointer to buffer where the dequeued data will be stored
 */
void Queue_Dequeue(Queue_t *inst , uint8_t *OutData);

/**
 * @brief Checks if the queue is empty.
 *
 * Determines whether the queue contains any elements.
 *
 * @param inst Pointer to the queue instance
 * @return Queue_Empty if the queue has no elements, Queue_NotEmpty otherwise
 */
Queue_Emptyness_e Queue_isEmpty(Queue_t *inst);

/**
 * @brief Checks if the queue is full.
 *
 * Determines whether the queue has reached its maximum capacity.
 *
 * @param inst Pointer to the queue instance
 * @return Queue_Full if the queue is at maximum capacity, Queue_NotFull otherwise
 */
Queue_Fullness_e Queue_isFull(Queue_t *inst);

/**
 * @brief Completely flushes the queue.
 *
 * Resets all queue indices and counters to their default values and clears all data in the buffer.
 * After this operation, the queue will be empty and ready to accept new data.
 *
 * @param inst Pointer to the queue instance
 */
void Queue_fullFlush(Queue_t *inst);

/**
 * @brief Returns the total number of filled elements in the queue.
 *
 * Calculates the difference between enqueue and dequeue counts to determine
 * how many elements are currently stored in the queue.
 *
 * @param inst Pointer to the queue instance
 * @return Number of elements currently in the queue
 */
uint32_t Queue_TotalFilledIndex(Queue_t *inst);

/**
 * @brief Retrieves the overflow state of the queue.
 *
 * Returns the current overflow flag status of the queue.
 *
 * @param inst Pointer to the queue instance
 * @return The current overflow state (Queue_Overflow or Queue_NoOverflow)
 */
Queue_OverFlowStatus_e Queue_isOverFlowed(Queue_t *inst);

#endif