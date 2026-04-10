
#include "common.h"

/**
 * @brief Writes bits at a specified position in a register.
 *
 * Modifies specific bits within a register by clearing the target bit range and writing
 * the provided value at the specified position. Preserves all other bits in the register.
 * Validates all parameters to ensure bit operations remain within register bounds.
 *
 * @param reg Pointer to the register to modify
 * @param reg_val Value to write at the specified bit position
 * @param start_bit Starting bit position (0-31)
 * @param bit_length Number of bits to write (1-32, must not exceed register width)
 */
void RegWrite_Bits(volatile uint32_t * reg, uint32_t reg_val, uint8_t start_bit, uint8_t bit_length)
{
    /* Check the Input Parameters */
    ASSERT((reg != NULL) && (start_bit < 32) && (bit_length > 0) && (bit_length <= 32) && (start_bit + bit_length <= 32) && ((uint64_t)reg_val < (uint64_t)((uint64_t)1UL << (uint64_t)bit_length)));
    
    uint32_t temp = *reg;

    /* Clear the Bits to 0 */
    temp &= ~(((uint32_t)0xFFFFFFFF >> (32 - bit_length)) << start_bit);

    /* Write the Value in specified bits */
    temp |= reg_val << start_bit;

    /* To avoid Unknown operation while clearing and writing new value, temp variable is used */
    *reg = temp;
}

/**
 * @brief Reads bits from a specified position in a register.
 *
 * Extracts and returns the bits at the specified position from a register, shifting them
 * to the least significant bit position. Validates parameters including bit range.
 *
 * @param reg Pointer to the register to read
 * @param start_bit Starting bit position (0-31)
 * @param bit_length Number of bits to read (1-32, must not exceed register width)
 * @return The extracted bits value, right-aligned to bit 0
 */
uint32_t RegRead_Bits(volatile uint32_t * reg, uint8_t start_bit, uint8_t bit_length)
{
    /* Check the Input Parameters */    
    ASSERT((bit_length <= 32) && (start_bit + bit_length <= 32) && (bit_length > 0));

    return ((*reg >> start_bit) & (uint32_t)(((uint64_t)1 << (uint64_t)bit_length) - (uint64_t)1));
}
/**
 * @brief Creates a blocking delay for approximate milliseconds.
 *
 * Implements a busy-wait delay using nested loops with NOP instructions. The actual delay
 * duration depends on the system clock frequency and compiler optimization settings.
 *
 * @param mSec Approximate delay duration in milliseconds
 */
void delayLoop(uint32_t mSec)
{
  for (volatile uint32_t i = 0; i < mSec ; i++)
  {
    for(volatile uint32_t j =0; j < 1000; j++)
    {
      __asm("NOP");
    }
  }
}
