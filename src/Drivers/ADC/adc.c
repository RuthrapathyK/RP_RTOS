#include "adc.h"

/**
 * @brief Gets the base address of the specified ADC module.
 *
 * Returns the memory base address for the given ADC module for register access.
 *
 * @param mod The ADC module identifier
 * @return Pointer to the ADC module's base address
 */
static ADC0_Type* ADC_getBase(ADC_Module_e mod)
{
  /* Check Preconditions */
  ASSERT(mod < ADC_Module_Max);

  ADC0_Type * retval = 0;

  /* Get Base Address of the corresponding ADC module */
  switch(mod)
  {
    case ADC_0:
        retval = (ADC0_Type *)ADC0_BASE;
        break;
    case ADC_1:
        retval = (ADC0_Type *)ADC1_BASE;
        break;
    default:
        ASSERT(0);
  }

  return retval;
}

/**
 * @brief Initializes the ADC module with default configuration.
 *
 * Configures the specified ADC module with clock settings (125 ksps sampling rate),
 * sample sequencer 0 with 8 samples from AIN5 input, processor trigger mode,
 * hardware averaging disabled, and dither enabled. Disables interrupt masking
 * for DMA-driven operation. Must be called before triggering conversions.
 *
 * @param mod The ADC module to initialize
 */
void ADC_Init(ADC_Module_e mod)
{
    /* Reset the ADC module */
    RegWrite_Bits(&SYSCTL->SRADC, 1, mod, 1);
    RegWrite_Bits(&SYSCTL->SRADC, 0, mod, 1);

    /* Enable Clock for ADC module */
    RegWrite_Bits(&SYSCTL->RCGCADC, 1, mod, 1);

    /* Wait till ADC module is Enabled */
    while(!RegRead_Bits(&SYSCTL->PRADC, mod, 1))
    ;

    /* Get the Base Address of the ADC Module */
    ADC0_Type *adc_base = ADC_getBase(mod);

    /* Configure Clock Source for ADC Module */
    RegWrite_Bits(&adc_base->CC, ADC_ClockSource_Either, 0, 4);
    
    /* Configure Sampling Rate of the ADC Module */
    RegWrite_Bits(&adc_base->PC, ADC_SampleRate_125ksps, 0, 4);

    /* Enable Dither */
    RegWrite_Bits(&adc_base->CTL, ADC_Dither_Enable, 6, 1);

    /* Set Hardware Averaging */
    RegWrite_Bits(&adc_base->SAC, ADC_HWAveraging_Disabled, 0, 4);

    /* Configure Sample Sequencer Priorities */
    RegWrite_Bits(&adc_base->SSPRI, ADC_SSPriority_0, 0, 2);

    /* Disable Sample Sequencer */
    RegWrite_Bits(&adc_base->ACTSS, 0, 0, 1);

    /* Configure Trigger Event for SS0 as Processor */
    RegWrite_Bits(&adc_base->EMUX, ADC_TriggerSelect_Always, 0, 4);

    /* Configure the No. of Samples to be 8 */
    RegWrite_Bits(&adc_base->SSCTL0, 1, 29, 1);

    /* Enable Interrupt for Samples of SS0 */
    RegWrite_Bits(&adc_base->SSCTL0, 1, 14, 1); // 4th Sample 
    RegWrite_Bits(&adc_base->SSCTL0, 1, 30, 1); // 8th Sample    

    /* Configure Trigger Source pin for SS0 samples */
    RegWrite_Bits(&adc_base->SSMUX0, ADC_SampleInput_AIN5, 0, 4); // 1st Sample
    RegWrite_Bits(&adc_base->SSMUX0, ADC_SampleInput_AIN5, 4, 4); // 2nd Sample
    RegWrite_Bits(&adc_base->SSMUX0, ADC_SampleInput_AIN5, 8, 4); // 3rd Sample
    RegWrite_Bits(&adc_base->SSMUX0, ADC_SampleInput_AIN5, 12, 4); // 4th Sample
    RegWrite_Bits(&adc_base->SSMUX0, ADC_SampleInput_AIN5, 16, 4); // 5th Sample
    RegWrite_Bits(&adc_base->SSMUX0, ADC_SampleInput_AIN5, 20, 4); // 6th Sample
    RegWrite_Bits(&adc_base->SSMUX0, ADC_SampleInput_AIN5, 24, 4); // 7th Sample
    RegWrite_Bits(&adc_base->SSMUX0, ADC_SampleInput_AIN5, 28, 4); // 8th Sample

    /* Disable ADC Interrupt Mask as DMA will generate Interrupt of this ADC peripheral */
    RegWrite_Bits(&adc_base->IM, 0, 0, 1);
}

/**
 * @brief Reads raw 12-bit ADC conversion result in blocking mode.
 *
 * Triggers ADC sample sequencer 0 conversion and waits until the conversion
 * completes. Returns the raw 12-bit conversion result from the ADC FIFO.
 *
 * @param mod The ADC module to read from
 * @return Raw 12-bit ADC conversion value (0-4095)
 */
uint16_t ADC_ReadRaw(ADC_Module_e mod)
{
    /* Get the Base Address of the ADC Module */
    ADC0_Type *adc_base = ADC_getBase(mod);

    /* Trigger SS0 in ADC module */
    RegWrite_Bits(&adc_base->PSSI, 1, 0, 1);

    /* Read the Status of Busy Bit */
    while(RegRead_Bits(&adc_base->SSFSTAT0, 8, 1))
    ;

    /* Read the Conversion Results and return */
    return RegRead_Bits(&adc_base->SSFIFO0, 0, 12);
}

/**
 * @brief Triggers ADC sample sequencer 0 conversion.
 *
 * Non-blocking trigger of ADC sample sequencer 0. Used in DMA-driven continuous
 * conversion mode to initiate conversions that transfer data via DMA instead of
 * polling. The completion can be monitored via the interrupt handler.
 *
 * @param mod The ADC module to trigger
 */
void ADC_TriggerConversion(ADC_Module_e mod)
{
    /* Get the Base Address of the ADC Module */
    ADC0_Type *adc_base = ADC_getBase(mod);

    /* Trigger SS0 in ADC module */
    RegWrite_Bits(&adc_base->PSSI, 1, 0, 1);   
}

/**
 * @brief Checks for ADC overflow and underflow conditions.
 *
 * Verifies ADC0 operation for any overflow or underflow errors that may indicate
 * data loss or synchronization issues. Triggers an assertion if either condition
 * is detected, halting execution for debugging purposes.
 */
void ADC_SynchronizationCheck(void)
{  
    /* Check for any Overflow */
    if(RegRead_Bits(&ADC0->OSTAT, 0, 1))
    {
      ASSERT(0);
    }

    /* Underflow conditions */
    if(RegRead_Bits(&ADC0->USTAT, 0, 1))
    {
     ASSERT(0);
    }
}

/**
 * @brief Flushes the FIFO of the specified ADC sample sequencer.
 *
 * Empties the FIFO buffer for the specified sample sequencer by reading and
 * discarding all pending data until the FIFO is empty. Useful for clearing
 * stale data before starting new conversions or after error conditions.
 *
 * @param seq The ADC sample sequencer FIFO to flush
 */
void ADC_FlushFIFO(ADC_SampleSequencer_e seq)
{
    volatile uint32_t *reg_stat = 0;
    uint32_t temp = 0;

    /* Get the Address of Sample Sequencer Status Register */
    switch(seq)
    {
        case ADC_SampleSequencer_0:
            reg_stat = &ADC0->SSFSTAT0;
            break;
        case ADC_SampleSequencer_1:
            reg_stat = &ADC0->SSFSTAT1;
            break;
        case ADC_SampleSequencer_2:
            reg_stat = &ADC0->SSFSTAT2;
            break;
        case ADC_SampleSequencer_3:
            reg_stat = &ADC0->SSFSTAT3;
            break;
        default:
            ASSERT(0);
            break;
    }

    /* Flush the ADC FIFO */
    while(!RegRead_Bits(reg_stat, 8, 1))
    {
      temp = ADC0->SSFIFO0;
    }

    /* Unused Variable */
    (void)temp;
}