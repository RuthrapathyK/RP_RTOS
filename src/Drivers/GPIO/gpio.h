#ifndef __GPIO_H
#define __GPIO_H

#include "common.h"

typedef enum{
    PA0 = 0x00, PA1, PA2, PA3, PA4, PA5, PA6, PA7,
    PB0 = 0x10, PB1, PB2, PB3, PB4, PB5, PB6, PB7,
    PC0 = 0x20, PC1, PC2, PC3, PC4, PC5, PC6, PC7,
    PD0 = 0x30, PD1, PD2, PD3, PD4, PD5, PD6, PD7,
    PE0 = 0x40, PE1, PE2, PE3, PE4, PE5,
    PF0 = 0x50, PF1, PF2, PF3, PF4,
    PMax
}GPIO_PortPins_e;

typedef enum{
    GPIO_DigitalOutput,
    GPIO_DigitalInput,
    GPIO_Direction_Max
}GPIO_Direction_e;

typedef enum{
    GPIO_State_OFF,
    GPIO_State_ON,
    GPIO_State_Max
}GPIO_State_e;


/**
 * @brief Initializes a GPIO pin with specified direction and default state.
 *
 * Enables the clock for the GPIO port, configures the pin as either input or output,
 * and sets the initial pin state. Ensures the pin is in GPIO mode (not alternate function).
 *
 * @param[in] portPin The GPIO pin to initialize (e.g., PA0, PB5, etc.)
 * @param[in] direction The direction of the pin (GPIO_DigitalOutput or GPIO_DigitalInput)
 * @param[in] defaultState The initial state of the pin (GPIO_State_OFF or GPIO_State_ON)
 *
 * @return None
 */
void GPIO_Init(GPIO_PortPins_e portPin, GPIO_Direction_e direction, GPIO_State_e defaultState);

/**
 * @brief Sets a GPIO pin to HIGH state (logic 1).
 *
 * Writes a HIGH logic level to the specified output pin.
 *
 * @param[in] portPin The GPIO pin to set (e.g., PA0, PB5, etc.)
 *
 * @return None
 */
void GPIO_setPin(GPIO_PortPins_e portPin);

/**
 * @brief Clears a GPIO pin to LOW state (logic 0).
 *
 * Writes a LOW logic level to the specified output pin.
 *
 * @param[in] portPin The GPIO pin to clear (e.g., PA0, PB5, etc.)
 *
 * @return None
 */
void GPIO_clearPin(GPIO_PortPins_e portPin);

/**
 * @brief Toggles the current state of a GPIO pin.
 *
 * Inverts the current logic level of the specified output pin.
 *
 * @param[in] portPin The GPIO pin to toggle (e.g., PA0, PB5, etc.)
 *
 * @return None
 */
void GPIO_togglePin(GPIO_PortPins_e portPin);

/**
 * @brief Reads the current state of a GPIO pin.
 *
 * Returns the current logic level of the specified input or output pin.
 *
 * @param[in] portPin The GPIO pin to read (e.g., PA0, PB5, etc.)
 *
 * @return GPIO_State_e The current state of the pin (GPIO_State_OFF or GPIO_State_ON)
 */
GPIO_State_e GPIO_getPinState(GPIO_PortPins_e portPin);

#endif