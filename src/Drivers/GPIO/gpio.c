/**
 * @file gpio.c
 * @brief GPIO driver implementation for TM4C123GH6PM microcontroller.
 *
 * This module provides functions to initialize and control GPIO pins on the TM4C123GH6PM
 * ARM Cortex-M4 microcontroller. It handles clock enable, pin direction configuration,
 * and digital pin state management.
 */

#include "gpio.h"
#include "../PinMux/pinconfig.h"
/**
 * @brief Retrieves the base address of a GPIO port register structure.
 *
 * Maps a port index (0-5 for ports A-F) to the corresponding GPIO port base address.
 * Asserts on invalid port index.
 *
 * @param[in] port GPIO port number (0=GPIOA, 1=GPIOB, ..., 5=GPIOF)
 *
 * @return GPIOA_Type* Pointer to the GPIO port register structure
 */
static GPIOA_Type * GPIO_getBase(uint8_t port)
{
    GPIOA_Type * ret_gpioBase = NULL;

    /* Map the Base address according to GPIO Port */
    switch(port)
    {
        case 0:
            ret_gpioBase = (GPIOA_Type *)GPIOA_BASE;
            break;
        case 1:
            ret_gpioBase = (GPIOA_Type *)GPIOB_BASE;
            break;
        case 2:
            ret_gpioBase = (GPIOA_Type *)GPIOC_BASE;
            break;
        case 3:
            ret_gpioBase = (GPIOA_Type *)GPIOD_BASE;
            break;
        case 4:
            ret_gpioBase = (GPIOA_Type *)GPIOE_BASE;
            break;
        case 5:
            ret_gpioBase = (GPIOA_Type *)GPIOF_BASE;
            break;
        default:
            ASSERT(0);
            break;
    }

    return ret_gpioBase;
}

/**
 * @brief Initializes a GPIO pin with specified direction and default state.
 *
 * Enables the clock for the GPIO port, waits for the peripheral to be ready,
 * configures the pin as either input or output, enables digital function,
 * and sets the initial pin state. Disables alternate functions for the pin.
 *
 * @param[in] portPin The GPIO pin to initialize (e.g., PA0, PB5, etc.)
 * @param[in] direction The direction of the pin (GPIO_DigitalOutput or GPIO_DigitalInput)
 * @param[in] defaultState The initial state of the pin (GPIO_State_OFF or GPIO_State_ON)
 *
 * @return None
 */
void GPIO_Init(GPIO_PortPins_e portPin, GPIO_Direction_e direction, GPIO_State_e defaultState)
{
    GPIOA_Type * gpioBase = NULL;

    uint8_t portDerived = (portPin >> 4) & 0x0F;
    uint8_t pinDerived = portPin & 0x0F;

    /* Enable Clock for that GPIO Port */
    SYSCTL->RCGCGPIO |= (1u << portDerived);

    /* Wait until the peripheral is ready (PRGPIO) */
    while(!(SYSCTL->PRGPIO & (1u << portDerived)))
    ;

    /* Get the Base Address of the GPIO based on the Port */
    gpioBase = GPIO_getBase(portDerived);

    /* Ensure alternate functions are disabled for this pin */
    gpioBase->AFSEL &= ~(1u << pinDerived);
    /* Clear port control for this pin (PCTL: 4 bits per pin) */
    gpioBase->PCTL &= ~(0xFu << (pinDerived * 4));

    /* Set the Direction of GPIO */
    if(direction == GPIO_DigitalOutput)
        gpioBase->DIR |= (1u << pinDerived);
    else
        gpioBase->DIR &= ~(1u << pinDerived);

    /* Enable digital function for this pin */
    gpioBase->DEN |= (1u << pinDerived);

    /* Set the Default value AFTER DEN is enabled */
    if(defaultState == GPIO_State_ON)
        GPIO_setPin(portPin);
    else
        GPIO_clearPin(portPin);

    /* Change the PinMux Configuration - All GPIO mode is 0*/
    Pin_Config(portDerived, pinDerived, PORTPIN_GPIO_FUNCTION);
}

/**
 * @brief Sets a GPIO pin to HIGH state (logic 1).
 *
 * Writes a HIGH logic level to the specified output pin using masked bit addressing.
 *
 * @param[in] portPin The GPIO pin to set (e.g., PA0, PB5, etc.)
 *
 * @return None
 */
void GPIO_setPin(GPIO_PortPins_e portPin)
{
    GPIOA_Type * gpioBase = NULL;

    uint8_t portDerived = (portPin >> 4) & 0x0F;
    uint8_t pinDerived = portPin & 0x0F;

    /* Get the Base Address of the GPIO based on the Port */
    gpioBase = GPIO_getBase(portDerived);
    
    /* Set the Pin */
    gpioBase->DATA_Bits[1u << pinDerived] = 0xFF;
}

/**
 * @brief Clears a GPIO pin to LOW state (logic 0).
 *
 * Writes a LOW logic level to the specified output pin using masked bit addressing.
 *
 * @param[in] portPin The GPIO pin to clear (e.g., PA0, PB5, etc.)
 *
 * @return None
 */
void GPIO_clearPin(GPIO_PortPins_e portPin)
{
    GPIOA_Type * gpioBase = NULL;

    uint8_t portDerived = (portPin >> 4) & 0x0F;
    uint8_t pinDerived = portPin & 0x0F;

    /* Get the Base Address of the GPIO based on the Port */
    gpioBase = GPIO_getBase(portDerived);

    /* Clear the Pin */
    gpioBase->DATA_Bits[1u << pinDerived] = 0x00;
}

/**
 * @brief Toggles the current state of a GPIO pin.
 *
 * Inverts the current logic level of the specified output pin using XOR operation.
 *
 * @param[in] portPin The GPIO pin to toggle (e.g., PA0, PB5, etc.)
 *
 * @return None
 */
void GPIO_togglePin(GPIO_PortPins_e portPin)
{
    GPIOA_Type * gpioBase = NULL;

    uint8_t portDerived = (portPin >> 4) & 0x0F;
    uint8_t pinDerived = portPin & 0x0F;

    /* Get the Base Address of the GPIO based on the Port */
    gpioBase = GPIO_getBase(portDerived);

    /* Toggle the Pin */
    gpioBase->DATA ^= (1<<pinDerived);
}

/**
 * @brief Reads the current state of a GPIO pin.
 *
 * Returns the current logic level of the specified input or output pin, converting
 * the hardware bit value to the GPIO_State_e enumeration.
 *
 * @param[in] portPin The GPIO pin to read (e.g., PA0, PB5, etc.)
 *
 * @return GPIO_State_e The current state of the pin (GPIO_State_OFF or GPIO_State_ON)
 */
GPIO_State_e GPIO_getPinState(GPIO_PortPins_e portPin)
{
    GPIOA_Type * gpioBase = NULL;

    uint8_t portDerived = (portPin >> 4) & 0x0F;
    uint8_t pinDerived = portPin & 0x0F;

    /* Get the Base Address of the GPIO based on the Port */
    gpioBase = GPIO_getBase(portDerived);
    /* Return enum state to match header: GPIO_State_ON / GPIO_State_OFF */
    return ((gpioBase->DATA >> pinDerived) & 0x01) ? GPIO_State_ON : GPIO_State_OFF;
}