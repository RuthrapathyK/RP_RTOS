#ifndef __ADC_H
#define __ADC_H

#include "common.h"

#define MAX_ADC_SAMPLE_SIZE 4096

typedef enum{
    ADC_0 = 0,
    ADC_1 = 1,
    ADC_Module_Max
}ADC_Module_e;

typedef enum{
    ADC_SampleRate_125ksps = 0x1,
    ADC_SampleRate_250ksps = 0x3,
    ADC_SampleRate_500ksps = 0x5,
    ADC_SampleRate_1000ksps = 0x7,
}ADC_SampleRate_e;

typedef enum{
    ADC_HWAveraging_Disabled = 0x0,
    ADC_HWAveraging_2 = 0x1,
    ADC_HWAveraging_4 = 0x2,
    ADC_HWAveraging_8 = 0x3,
    ADC_HWAveraging_16 = 0x4,
    ADC_HWAveraging_32 = 0x5,
    ADC_HWAveraging_64 = 0x6,
}ADC_HWAveraging_e;

typedef enum{
    ADC_ClockSource_Either = 0x0,
    ADC_ClockSource_PIOSC = 0x1
}ADC_ClockSource_e;

typedef enum{
    ADC_TriggerSelect_Processor = 0x0,
    ADC_TriggerSelect_Comapartor_0 = 0x1,
    ADC_TriggerSelect_Comapartor_1 = 0x2,
    ADC_TriggerSelect_ExternalPin = 0x4,
    ADC_TriggerSelect_Timer = 0x5,
    ADC_TriggerSelect_PWM_0 = 0x6,
    ADC_TriggerSelect_PWM_1 = 0x7,
    ADC_TriggerSelect_PWM_2 = 0x8,
    ADC_TriggerSelect_PWM_3 = 0x9,
    ADC_TriggerSelect_Always = 0xF,
}ADC_TriggerSelect_e;

typedef enum{
    ADC_SSPriority_0 = 0x0,
    ADC_SSPriority_1 = 0x1,
    ADC_SSPriority_2 = 0x2,
    ADC_SSPriority_3 = 0x3,
}ADC_SSPriority_e;

typedef enum{
    ADC_SampleInput_AIN0 = 0,
    ADC_SampleInput_AIN1 = 1,
    ADC_SampleInput_AIN2 = 2,
    ADC_SampleInput_AIN3 = 3,
    ADC_SampleInput_AIN4 = 4,
    ADC_SampleInput_AIN5 = 5,
    ADC_SampleInput_AIN6 = 6,
    ADC_SampleInput_AIN7 = 7,
    ADC_SampleInput_AIN8 = 8,
    ADC_SampleInput_AIN9 = 9,
    ADC_SampleInput_AIN10 = 10,
    ADC_SampleInput_AIN11 = 11
}ADC_SampleInput_e;

typedef enum{
    ADC_SampleSequencer_0 = 0,
    ADC_SampleSequencer_1 = 1,
    ADC_SampleSequencer_2 = 2,
    ADC_SampleSequencer_3 = 3,
}ADC_SampleSequencer_e;

typedef enum{
    ADC_Dither_Disable = 0,
    ADC_Dither_Enable = 1
}ADC_DitherSetting_e;

void ADC_Init(ADC_Module_e mod);
uint16_t ADC_ReadRaw(ADC_Module_e mod);
void ADC_TriggerConversion(ADC_Module_e mod);
void ADC_SynchronizationCheck(void);
void ADC_FlushFIFO(ADC_SampleSequencer_e sequencer);

#endif