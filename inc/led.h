#ifndef __LED__H
#define __LED__H

#define GPIO_PORT_F_APB_BASE 0x40025000
#define RCGCGPIO        (*(unsigned int *)(0x400FE000+0x608))

#define GPIODIR         (*(unsigned int *)(GPIO_PORT_F_APB_BASE+0x400))
#define GPIOAFSEL       (*(unsigned int *)(GPIO_PORT_F_APB_BASE+0x420))
#define GPIODR4R        (*(unsigned int *)(GPIO_PORT_F_APB_BASE+0x504))
#define GPIODEN         (*(unsigned int *)(GPIO_PORT_F_APB_BASE+0x51C))

#define GPIODATA        (*(unsigned int *)(GPIO_PORT_F_APB_BASE))
#define GPIOODR         (*(unsigned int *)(GPIO_PORT_F_APB_BASE+0x50C))
#define GPIOLOCK        (*(unsigned int *)(GPIO_PORT_F_APB_BASE+0x520))
#define GPIOCR          (*(unsigned int *)(GPIO_PORT_F_APB_BASE+0x524))

#define LED_BLUE        (1<<2)
#define LED_RED         (1<<1)
#define LED_GREEN       (1<<3)

#define LED_BLUE_ON     (*(unsigned int *)(GPIO_PORT_F_APB_BASE+0x10)) = 0xFF
#define LED_BLUE_OFF    (*(unsigned int *)(GPIO_PORT_F_APB_BASE+0x10)) = 0x00
#define LED_RED_ON      (*(unsigned int *)(GPIO_PORT_F_APB_BASE+0x08)) = 0xFF
#define LED_RED_OFF     (*(unsigned int *)(GPIO_PORT_F_APB_BASE+0x08)) = 0x00
#define LED_GREEN_ON    (*(unsigned int *)(GPIO_PORT_F_APB_BASE+0x20)) = 0xFF
#define LED_GREEN_OFF   (*(unsigned int *)(GPIO_PORT_F_APB_BASE+0x20)) = 0x00

void delay(int);
void LED_Init(unsigned int);

#endif