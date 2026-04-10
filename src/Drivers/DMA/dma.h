#ifndef __DMA_H
#define __DMA_H

#include "common.h"

/* Channel 0 Encodings */
#define DMA_CH0_ENC0_USB0EP1RX  0
#define DMA_CH0_ENC1_UART2RX    1
#define DMA_CH0_ENC2_SOFTWARE   2
#define DMA_CH0_ENC3_GPTIMER4A  3
#define DMA_CH0_ENC4_SOFTWARE   4

/* Channel 1 Encodings */
#define DMA_CH1_ENC0_USB0EP1TX  0
#define DMA_CH1_ENC1_UART2TX    1
#define DMA_CH1_ENC2_SOFTWARE   2
#define DMA_CH1_ENC3_GPTIMER4B  3
#define DMA_CH1_ENC4_SOFTWARE   4

/* Channel 2 Encodings */
#define DMA_CH2_ENC0_USB0EP2RX  0
#define DMA_CH2_ENC1_GPTIMER3A  1
#define DMA_CH2_ENC2_SOFTWARE   2
#define DMA_CH2_ENC3_SOFTWARE   3
#define DMA_CH2_ENC4_SOFTWARE   4

/* Channel 3 Encodings */
#define DMA_CH3_ENC0_USB0EP2TX  0
#define DMA_CH3_ENC1_GPTIMER3B  1
#define DMA_CH3_ENC2_SOFTWARE   2
#define DMA_CH3_ENC3_SOFTWARE   3
#define DMA_CH3_ENC4_SOFTWARE   4

/* Channel 4 Encodings */
#define DMA_CH4_ENC0_USB0EP3RX  0
#define DMA_CH4_ENC1_GPTIMER2A  1
#define DMA_CH4_ENC2_GPIO_A     2
#define DMA_CH4_ENC3_GPIO_A     3
#define DMA_CH4_ENC4_SOFTWARE   4

/* Channel 5 Encodings */
#define DMA_CH5_ENC0_USB0EP3TX  0
#define DMA_CH5_ENC1_GPTIMER2B  1
#define DMA_CH5_ENC2_GPIO_B     2
#define DMA_CH5_ENC3_GPIO_B     3
#define DMA_CH5_ENC4_SOFTWARE   4

/* Channel 6 Encodings */
#define DMA_CH6_ENC0_SOFTWARE   0
#define DMA_CH6_ENC1_GPTIMER2A  1
#define DMA_CH6_ENC2_UART5RX    2
#define DMA_CH6_ENC3_GPIO_C     3
#define DMA_CH6_ENC4_SOFTWARE   4

/* Channel 7 Encodings */
#define DMA_CH7_ENC0_SOFTWARE   0
#define DMA_CH7_ENC1_GPTIMER2B  1
#define DMA_CH7_ENC2_UART5TX    2
#define DMA_CH7_ENC3_GPIO_D     3
#define DMA_CH7_ENC4_SOFTWARE   4

/* Channel 8 Encodings */
#define DMA_CH8_ENC0_UART0RX    0
#define DMA_CH8_ENC1_UART1RX    1
#define DMA_CH8_ENC2_SOFTWARE   2
#define DMA_CH8_ENC3_GPTIMER5A  3
#define DMA_CH8_ENC4_SOFTWARE   4

/* Channel 9 Encodings */
#define DMA_CH9_ENC0_UART0TX    0
#define DMA_CH9_ENC1_UART1TX    1
#define DMA_CH9_ENC2_SOFTWARE   2
#define DMA_CH9_ENC3_GPTIMER5B  3
#define DMA_CH9_ENC4_SOFTWARE   4

/* Channel 10 Encodings */
#define DMA_CH10_ENC0_SSI0RX    0
#define DMA_CH10_ENC1_SSI1RX    1
#define DMA_CH10_ENC2_UART6RX   2
#define DMA_CH10_ENC3_GPWTIMER0A 3
#define DMA_CH10_ENC4_SOFTWARE  4

/* Channel 11 Encodings */
#define DMA_CH11_ENC0_SSI0TX    0
#define DMA_CH11_ENC1_SSI1TX    1
#define DMA_CH11_ENC2_UART6TX   2
#define DMA_CH11_ENC3_GPWTIMER0B 3
#define DMA_CH11_ENC4_SOFTWARE  4

/* Channel 12 Encodings */
#define DMA_CH12_ENC0_SOFTWARE  0
#define DMA_CH12_ENC1_UART2RX   1
#define DMA_CH12_ENC2_SSI2RX    2
#define DMA_CH12_ENC3_GPWTIMER1A 3
#define DMA_CH12_ENC4_SOFTWARE  4

/* Channel 13 Encodings */
#define DMA_CH13_ENC0_SOFTWARE  0
#define DMA_CH13_ENC1_UART2TX   1
#define DMA_CH13_ENC2_SSI2TX    2
#define DMA_CH13_ENC3_GPWTIMER1B 3
#define DMA_CH13_ENC4_SOFTWARE  4

/* Channel 14 Encodings */
#define DMA_CH14_ENC0_ADC0SS0   0
#define DMA_CH14_ENC1_GPTIMER2A 1
#define DMA_CH14_ENC2_SSI3RX    2
#define DMA_CH14_ENC3_GPIO_E    3
#define DMA_CH14_ENC4_SOFTWARE  4

/* Channel 15 Encodings */
#define DMA_CH15_ENC0_ADC0SS1   0
#define DMA_CH15_ENC1_GPTIMER2B 1
#define DMA_CH15_ENC2_SSI3TX    2
#define DMA_CH15_ENC3_GPIO_F    3
#define DMA_CH15_ENC4_SOFTWARE  4

/* Channel 16 Encodings */
#define DMA_CH16_ENC0_ADC0SS2   0
#define DMA_CH16_ENC1_SOFTWARE  1
#define DMA_CH16_ENC2_UART3RX   2
#define DMA_CH16_ENC3_GPWTIMER2A 3
#define DMA_CH16_ENC4_SOFTWARE  4

/* Channel 17 Encodings */
#define DMA_CH17_ENC0_ADC0SS3   0
#define DMA_CH17_ENC1_SOFTWARE  1
#define DMA_CH17_ENC2_UART3TX   2
#define DMA_CH17_ENC3_GPWTIMER2B 3
#define DMA_CH17_ENC4_SOFTWARE  4

/* Channel 18 Encodings */
#define DMA_CH18_ENC0_GPTIMER0A 0
#define DMA_CH18_ENC1_GPTIMER1A 1
#define DMA_CH18_ENC2_UART4RX   2
#define DMA_CH18_ENC3_GPIO_B    3
#define DMA_CH18_ENC4_SOFTWARE  4

/* Channel 19 Encodings */
#define DMA_CH19_ENC0_GPTIMER0B 0
#define DMA_CH19_ENC1_GPTIMER1B 1
#define DMA_CH19_ENC2_UART4TX   2
#define DMA_CH19_ENC3_SOFTWARE  3
#define DMA_CH19_ENC4_SOFTWARE  4

/* Channel 20 Encodings */
#define DMA_CH20_ENC0_GPTIMER1A 0
#define DMA_CH20_ENC1_SOFTWARE  1
#define DMA_CH20_ENC2_UART7RX   2
#define DMA_CH20_ENC3_SOFTWARE  3
#define DMA_CH20_ENC4_SOFTWARE  4

/* Channel 21 Encodings */
#define DMA_CH21_ENC0_GPTIMER1B 0
#define DMA_CH21_ENC1_SOFTWARE  1
#define DMA_CH21_ENC2_UART7TX   2
#define DMA_CH21_ENC3_SOFTWARE  3
#define DMA_CH21_ENC4_SOFTWARE  4

/* Channel 22 Encodings */
#define DMA_CH22_ENC0_UART1RX   0
#define DMA_CH22_ENC1_SOFTWARE  1
#define DMA_CH22_ENC2_SOFTWARE  2
#define DMA_CH22_ENC3_SOFTWARE  3
#define DMA_CH22_ENC4_SOFTWARE  4

/* Channel 23 Encodings */
#define DMA_CH23_ENC0_UART1TX   0
#define DMA_CH23_ENC1_SOFTWARE  1
#define DMA_CH23_ENC2_SOFTWARE  2
#define DMA_CH23_ENC3_SOFTWARE  3
#define DMA_CH23_ENC4_SOFTWARE  4

/* Channel 24 Encodings */
#define DMA_CH24_ENC0_SSI1RX    0
#define DMA_CH24_ENC1_ADC1SS0   1
#define DMA_CH24_ENC2_SOFTWARE  2
#define DMA_CH24_ENC3_GPWTIMER3A 3
#define DMA_CH24_ENC4_SOFTWARE  4

/* Channel 25 Encodings */
#define DMA_CH25_ENC0_SSI1TX    0
#define DMA_CH25_ENC1_ADC1SS1   1
#define DMA_CH25_ENC2_SOFTWARE  2
#define DMA_CH25_ENC3_GPWTIMER3B 3
#define DMA_CH25_ENC4_SOFTWARE  4

/* Channel 26 Encodings */
#define DMA_CH26_ENC0_SOFTWARE  0
#define DMA_CH26_ENC1_ADC1SS2   1
#define DMA_CH26_ENC2_SOFTWARE  2
#define DMA_CH26_ENC3_GPWTIMER4A 3
#define DMA_CH26_ENC4_SOFTWARE  4

/* Channel 27 Encodings */
#define DMA_CH27_ENC0_SOFTWARE  0
#define DMA_CH27_ENC1_ADC1SS3   1
#define DMA_CH27_ENC2_SOFTWARE  2
#define DMA_CH27_ENC3_GPWTIMER4B 3
#define DMA_CH27_ENC4_SOFTWARE  4

/* Channel 28 Encodings */
#define DMA_CH28_ENC0_SOFTWARE  0
#define DMA_CH28_ENC1_SOFTWARE  1
#define DMA_CH28_ENC2_SOFTWARE  2
#define DMA_CH28_ENC3_GPWTIMER5A 3
#define DMA_CH28_ENC4_SOFTWARE  4

/* Channel 29 Encodings */
#define DMA_CH29_ENC0_SOFTWARE  0
#define DMA_CH29_ENC1_SOFTWARE  1
#define DMA_CH29_ENC2_SOFTWARE  2
#define DMA_CH29_ENC3_GPWTIMER5B 3
#define DMA_CH29_ENC4_SOFTWARE  4

/* Channel 30 Encodings */
#define DMA_CH30_ENC0_SOFTWARE  0
#define DMA_CH30_ENC1_SOFTWARE  1
#define DMA_CH30_ENC2_SOFTWARE  2
#define DMA_CH30_ENC3_SOFTWARE  3
#define DMA_CH30_ENC4_SOFTWARE  4

/* Channel 31 Encodings */
#define DMA_CH31_ENC0_RESERVED  0
#define DMA_CH31_ENC1_RESERVED  1
#define DMA_CH31_ENC2_RESERVED  2
#define DMA_CH31_ENC3_RESERVED  3
#define DMA_CH31_ENC4_RESERVED  4

typedef enum{
    DMA_0 = 0,
    DMA_Max
}DMA_Module_e;

typedef enum{
    DMA_ChannelControl_Primary = 0,
    DMA_ChannelControl_Secondary = 1,
    DMA_ChannelControl_Max,
}DMA_ChannelControl_e;

typedef enum{
    DMA_Channel_0 = 0,
    DMA_Channel_1 = 1,
    DMA_Channel_2 = 2,
    DMA_Channel_3 = 3,
    DMA_Channel_4 = 4,
    DMA_Channel_5 = 5,
    DMA_Channel_6 = 6,
    DMA_Channel_7 = 7,
    DMA_Channel_8 = 8,
    DMA_Channel_9 = 9,
    DMA_Channel_10 = 10,
    DMA_Channel_11 = 11,
    DMA_Channel_12 = 12,
    DMA_Channel_13 = 13,
    DMA_Channel_14 = 14,
    DMA_Channel_15 = 15,
    DMA_Channel_16 = 16,
    DMA_Channel_17 = 17,
    DMA_Channel_18 = 18,
    DMA_Channel_19 = 19,
    DMA_Channel_20 = 20,
    DMA_Channel_21 = 21,
    DMA_Channel_22 = 22,
    DMA_Channel_23 = 23,
    DMA_Channel_24 = 24,
    DMA_Channel_25 = 25,
    DMA_Channel_26 = 26,
    DMA_Channel_27 = 27,
    DMA_Channel_28 = 28,
    DMA_Channel_29 = 29,
    DMA_Channel_30 = 30,
    DMA_Channel_31 = 31,
    DMA_Channel_Max
}DMA_Channel_e;

typedef enum{
    DMA_ChannelPriority_Default = 0,
    DMA_ChannelPriority_High = 1
}DMA_ChannelPriority_e;

typedef enum{
    DMA_ChannelControl_Byte = 0,
    DMA_ChannelControl_HalfWord = 1,
    DMA_ChannelControl_Word = 2,
    DMA_ChannelControl_NoInc_Res = 3
}DMA_ChannelControl_Size_e;

typedef enum{
    DMA_ChannelControl_Arbitration_1 = 0,
    DMA_ChannelControl_Arbitration_2 = 1,
    DMA_ChannelControl_Arbitration_4 = 2,
    DMA_ChannelControl_Arbitration_8 = 3,
    DMA_ChannelControl_Arbitration_16 = 4,
    DMA_ChannelControl_Arbitration_32 = 5,
    DMA_ChannelControl_Arbitration_64 = 6,
    DMA_ChannelControl_Arbitration_128 = 7,
    DMA_ChannelControl_Arbitration_256 = 8,
    DMA_ChannelControl_Arbitration_512 = 9,
    DMA_ChannelControl_Arbitration_1024 = 10,
}DMA_ChannelControl_Arbitration_e;

typedef enum{
    DMA_ChannelControl_XFERMode_Stop = 0,
    DMA_ChannelControl_XFERMode_Basic = 1,
    DMA_ChannelControl_XFERMode_Auto = 2,
    DMA_ChannelControl_XFERMode_PingPong = 3,
    DMA_ChannelControl_XFERMode_MemoryScatterGather = 4,
    DMA_ChannelControl_XFERMode_AlternateMemoryScatterGather = 5,
    DMA_ChannelControl_XFERMode_PeripheralScatterGather = 6,
    DMA_ChannelControl_XFERMode_AlternatePeripheralScatterGather = 7,
}DMA_ChannelControl_XFERMode_e;

typedef struct __attribute__((packed)) {
    uint32_t XFERMODE:3;
    uint32_t NXTUSEBURST:1;
    uint32_t XFERSIZE:10;
    uint32_t ARBSIZE:4;
    uint32_t Reserved:6;
    uint32_t SRCSIZE:2;
    uint32_t SRCINC:2;
    uint32_t DSTSIZE:2;
    uint32_t DSTINC:2;
} DMA_ControlWord_t;

typedef struct{
    uint32_t *Source_End_Pointer;
    uint32_t *Destination_End_Pointer;
    DMA_ControlWord_t Control_Word;
    uint32_t Reserved;
}DMA_ChannelControl_t;


void DMA_Init(DMA_Module_e mod);
void DMA_EnableTransfer(DMA_Module_e mod);
void DMA_ChannelConfig(DMA_ChannelControl_e channelcontrol, DMA_Channel_e channel, uint32_t *srcPtr, uint32_t *dstPtr, DMA_ControlWord_t cntWord);
#endif