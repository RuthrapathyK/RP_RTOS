#include "queue.h"

/**
 * @brief Sets the queue to its default configuration.
 *
 * Initializes all queue indices and counters to zero and clears the overflow flag.
 * This is an internal function used during queue initialization.
 *
 * @param inst Pointer to the queue instance to configure
 */
static void Queue_getDefaultConfig(Queue_t *inst)
{
    inst->eIdx = 0;
    inst->dIdx = 0;
    inst->eCount = 0;
    inst->dCount = 0;
    inst->OverFlow_DetectedCount = 0;
    inst->OverFlow_ResolvedCount = 0;
}

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
void Queue_Init(Queue_t *inst, uint8_t *pBuf, uint32_t IdxSize, uint32_t IdxMax)
{
    /* Load Default Configuration of a Queue */
    Queue_getDefaultConfig(inst);

    /* Load Handler with Other configurations */
    inst->QBuff = pBuf;
    inst->QBuff_IdxSize = IdxSize;
    inst->QBuff_Max = IdxMax;
}

/**
 * @brief Adds data to the queue.
 *
 * Enqueues an element into the queue. If the queue is full, sets the overflow flag.
 * The data is copied element by element based on the configured element size.
 *
 * @param inst Pointer to the queue instance
 * @param InData Pointer to the data to enqueue
 */
void Queue_Enqueue(Queue_t *inst, uint8_t *InData)
{
  /* Check for Overflow */
  if(Queue_isFull(inst) == Queue_Full)
  {
    /* Increament the OverFlow Counter only if the Previous OverFlow is served */
    if(Queue_isOverFlowed(inst) == Queue_NoOverflow)
    {
        /* Increament Overflow Count */
        inst->OverFlow_DetectedCount++;
    }
    else
    {
        /* Avoid Multiple Overflow Increaments */
    }
  }

  /* Load the Queue with all Enqueued bytes */
  for(uint32_t byteIdx = 0; byteIdx < inst->QBuff_IdxSize; byteIdx++)
  {
    inst->QBuff[(inst->eIdx * inst->QBuff_IdxSize)+ byteIdx] = InData[byteIdx];
  }

  /* Increment Enqueuing Index */
  inst->eIdx = (inst->eIdx + 1) % inst->QBuff_Max;
  inst->eCount++; // Increment the Enqueuing Count also - Count will be used to detect whether the Buffer is full or empty
}

/**
 * @brief Removes and retrieves data from the queue.
 *
 * Dequeues the first element from the queue and copies it to the output buffer.
 * The data is copied element by element based on the configured element size.
 *
 * @param inst Pointer to the queue instance
 * @param OutData Pointer to buffer where the dequeued data will be stored
 */
void Queue_Dequeue(Queue_t *inst , uint8_t *OutData)
{
    if(Queue_isOverFlowed(inst) == Queue_Overflow)
    {
        /* Increament Overflow Flag */
        inst->OverFlow_ResolvedCount++;

        /* Move the Dequeue Index */
        inst->dIdx = inst->eIdx;

        /* Set the Dequeue Count to Process the Queueu index to Max */
        inst->dCount = inst->eCount - inst->QBuff_Max;
    }

    /* Load the Dequeued data to the Out Variable */
    for(uint32_t byteIdx = 0; byteIdx < inst->QBuff_IdxSize; byteIdx++)
    {
        OutData[byteIdx] = inst->QBuff[(inst->dIdx * inst->QBuff_IdxSize)+ byteIdx];
    }

    inst->dIdx = (inst->dIdx + 1) % inst->QBuff_Max; // Increament the Dequeuing Index
    inst->dCount++; // Increment the Dequeuing Count also - Count will be used to detect whether the Buffer is full or empty
}

/**
 * @brief Returns the total number of filled elements in the queue.
 *
 * Calculates the difference between enqueue and dequeue counts to determine
 * how many elements are currently stored in the queue.
 *
 * @param inst Pointer to the queue instance
 * @return Number of elements currently in the queue
 */
uint32_t Queue_TotalFilledIndex(Queue_t *inst)
{
    return (inst->eCount - inst->dCount);
}

/**
 * @brief Checks if the queue is empty.
 *
 * Determines whether the queue contains any elements.
 *
 * @param inst Pointer to the queue instance
 * @return Queue_Empty if the queue has no elements, Queue_NotEmpty otherwise
 */
Queue_Emptyness_e Queue_isEmpty(Queue_t *inst)
{
    /* Check if Queue is Empty or Not */
    return Queue_TotalFilledIndex(inst) == 0 ? Queue_Empty : Queue_NotEmpty;
}

/**
 * @brief Checks if the queue is full.
 *
 * Determines whether the queue has reached its maximum capacity.
 *
 * @param inst Pointer to the queue instance
 * @return Queue_Full if the queue is at maximum capacity, Queue_NotFull otherwise
 */
Queue_Fullness_e Queue_isFull(Queue_t *inst)
{
    /* Check if Queue is Full or Not */
    return Queue_TotalFilledIndex(inst) >= inst->QBuff_Max ? Queue_Full : Queue_NotFull;
}

/**
 * @brief Completely flushes the queue.
 *
 * Resets all queue indices and counters to their default values and clears all data in the buffer.
 * After this operation, the queue will be empty and ready to accept new data.
 *
 * @param inst Pointer to the queue instance
 */
void Queue_fullFlush(Queue_t *inst)
{
    /* Load Default Configuration of a Queue */
    Queue_getDefaultConfig(inst);

    /* Clear all Bytes in the Buffer to 0 */
    for(uint32_t iter = 0; iter < (inst->QBuff_IdxSize * inst->QBuff_Max); iter++)
    {
        inst->QBuff[iter] = 0;
    } 
}

/**
 * @brief Retrieves the overflow state of the queue.
 *
 * Returns the current overflow flag status of the queue.
 *
 * @param inst Pointer to the queue instance
 * @return The current overflow state (Queue_Overflow or Queue_NoOverflow)
 */
Queue_OverFlowStatus_e Queue_isOverFlowed(Queue_t *inst)
{
    return (inst->OverFlow_DetectedCount > inst->OverFlow_ResolvedCount) ? Queue_Overflow : Queue_NoOverflow;
}