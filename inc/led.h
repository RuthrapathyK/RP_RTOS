#ifndef __LED__H
#define __LED__H

#include "typedef.h"

#define GPIO_PORT_F_APB_BASE 0x40025000
#define RCGCGPIO        (*(uint32_t *)(0x400FE000+0x608))

#define GPIODIR         (*(uint32_t *)(GPIO_PORT_F_APB_BASE+0x400))
#define GPIOAFSEL       (*(uint32_t *)(GPIO_PORT_F_APB_BASE+0x420))
#define GPIODR4R        (*(uint32_t *)(GPIO_PORT_F_APB_BASE+0x504))
#define GPIODEN         (*(uint32_t *)(GPIO_PORT_F_APB_BASE+0x51C))

#define GPIODATA        (*(uint32_t *)(GPIO_PORT_F_APB_BASE))
#define GPIOODR         (*(uint32_t *)(GPIO_PORT_F_APB_BASE+0x50C))
#define GPIOLOCK        (*(uint32_t *)(GPIO_PORT_F_APB_BASE+0x520))
#define GPIOCR          (*(uint32_t *)(GPIO_PORT_F_APB_BASE+0x524))

#define LED_BLUE        (1<<2)
#define LED_RED         (1<<1)
#define LED_GREEN       (1<<3)

#define LED_BLUE_ON     (*(uint32_t *)(GPIO_PORT_F_APB_BASE+0x10)) = 0xFF
#define LED_BLUE_OFF    (*(uint32_t *)(GPIO_PORT_F_APB_BASE+0x10)) = 0x00
#define LED_RED_ON      (*(uint32_t *)(GPIO_PORT_F_APB_BASE+0x08)) = 0xFF
#define LED_RED_OFF     (*(uint32_t *)(GPIO_PORT_F_APB_BASE+0x08)) = 0x00
#define LED_GREEN_ON    (*(uint32_t *)(GPIO_PORT_F_APB_BASE+0x20)) = 0xFF
#define LED_GREEN_OFF   (*(uint32_t *)(GPIO_PORT_F_APB_BASE+0x20)) = 0x00

void delay(uint32_t);
void LED_Init(uint32_t);

#endif