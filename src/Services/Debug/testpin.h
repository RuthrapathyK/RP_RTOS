#ifndef __TEST_PIN_H
#define __TEST_PIN_H

#define TESTPIN_ON  GPIOB->DATA_Bits[8] = 0xFF
#define TESTPIN_OFF GPIOB->DATA_Bits[8] = 0x00

/**
 * @brief Initialize Test Pin (PB3) as digital output
 */
void TestPin_Init(void);

#endif