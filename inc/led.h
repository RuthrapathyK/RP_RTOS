#ifndef __LED__H
#define __LED__H

#include "common.h"
#include "TM4C123GH6PM.h"

#define LED_BLUE        (1<<2)
#define LED_RED         (1<<1)
#define LED_GREEN       (1<<3)

#define LED_RED_ON      GPIOF->DATA_Bits[2] = 0xFF
#define LED_RED_OFF     GPIOF->DATA_Bits[2] = 0x00
#define LED_RED_TOGGLE  GPIOF->DATA ^= LED_RED;
#define LED_BLUE_ON     GPIOF->DATA_Bits[4] = 0xFF 
#define LED_BLUE_OFF    GPIOF->DATA_Bits[4] = 0x00
#define LED_BLUE_TOGGLE GPIOF->DATA ^= LED_BLUE;
#define LED_GREEN_ON    GPIOF->DATA_Bits[8] = 0xFF
#define LED_GREEN_OFF   GPIOF->DATA_Bits[8] = 0x00
#define LED_GREEN_TOGGLE GPIOF->DATA ^= LED_GREEN;

void LED_Init(uint32_t);

#endif