
#include "testpin.h"
#include "../src/Drivers/GPIO/gpio.h"

/**
 * @brief Initialize Test Pin (PB3) as digital output
 */
void TestPin_Init(void)
{
  GPIO_Init(PB3, GPIO_DigitalOutput, GPIO_State_OFF);
}

/**
 * @brief Set Test Pin High
 */
__INLINE__ static void TestPin_High(void)
{
    GPIO_setPin(PB3);
}

/**
 * @brief Set Test Pin Low
 */
__INLINE__ static void TestPin_Low(void)
{
    GPIO_clearPin(PB3);
}