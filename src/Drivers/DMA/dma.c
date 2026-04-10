#include "dma.h"

__attribute__((aligned(1024))) DMA_ChannelControl_t Channel_Control_Table[DMA_ChannelControl_Max][DMA_Channel_Max] = {0};

DMA_ControlWord_t ControlWord;

/**
 * @brief Gets the base address of the specified DMA module.
 *
 * Returns the memory base address for the given DMA module for register access.
 * Currently only DMA_0 is supported on this microcontroller.
 *
 * @param mod The DMA module identifier
 * @return Pointer to the DMA (UDMA) module's base address
 */
static UDMA_Type * DMA_getBase(DMA_Module_e mod)
{
    /* Check the Preconditions */
    ASSERT(mod < DMA_Max);

    UDMA_Type * retval = 0;

    /* Derive Base Address based on the Module Selected */
    switch (mod)
    {
        case DMA_0:
            retval = (UDMA_Type *)UDMA_BASE;
            break;
        
        default:
            ASSERT(0);
            break;
    }

    return retval;
}

void DMA_ChannelConfig(DMA_ChannelControl_e channelcontrol, DMA_Channel_e channel, uint32_t *srcPtr, uint32_t *dstPtr, DMA_ControlWord_t cntWord)
{
    Channel_Control_Table[channelcontrol][channel].Source_End_Pointer = srcPtr;
    Channel_Control_Table[channelcontrol][channel].Destination_End_Pointer = dstPtr;
    Channel_Control_Table[channelcontrol][channel].Control_Word = cntWord;
}

void DMA_Init(DMA_Module_e mod)
{
    /* Check the Preconditions */
    ASSERT(mod < DMA_Max);

    /* Reset DMA controller */
    RegWrite_Bits(&SYSCTL->SRDMA, 1, mod, 1);
    RegWrite_Bits(&SYSCTL->SRDMA, 0, mod, 1);

    /* Enable Clock for DMA controller */
    RegWrite_Bits(&SYSCTL->RCGCDMA, 1, mod, 1);

    /* Wait till DMA controller is Enabled */
    while(!RegRead_Bits(&SYSCTL->PRDMA, mod, 1))
    ;

    /* Get Base Address of DMA controller */
    UDMA_Type *dma_base = DMA_getBase(DMA_0);

    /* Enable DMA controller */
    RegWrite_Bits(&dma_base->CFG, 1, 0, 1);
    
    /* Configure Base Address of Channel Control Table */
    RegWrite_Bits(&dma_base->CTLBASE, ((uint32_t)&Channel_Control_Table) >> 10, 10, 22);

    /* Disable the Channel(i.e Channel 14) to Start the Transfer */
    RegWrite_Bits(&dma_base->ENACLR, 1, 14, 1);

    /* Configure the Channel Mapping for ADC0 SS0 (i.e. Channel 14)*/
    RegWrite_Bits(&dma_base->CHMAP1, DMA_CH14_ENC0_ADC0SS0, 24, 4);

    /* Configure the Channel Priority(i.e. Channel 14) to High */
    RegWrite_Bits(&dma_base->PRIOSET, DMA_ChannelPriority_High, 14, 1);

    /* Configue Channel (i.e. Channel 14) to accept only Burst transfer request */
    RegWrite_Bits(&dma_base->USEBURSTSET, 1, 14, 1);

    /* Configure Channel(i.e. Channel 14) to use Primary Control Structure */
    //RegWrite_Bits(&dma_base->ALTCLR, 1, 14, 1);

    /* Enable ADC0 SS0 request in Channel Mask */
    RegWrite_Bits(&dma_base->REQMASKCLR, 1, 14, 1);
}

void DMA_EnableTransfer(DMA_Module_e mod)
{
    /* Check the Preconditions */
    ASSERT(mod < DMA_Max);

    /* Get Base Address of DMA controller */
    UDMA_Type *dma_base = DMA_getBase(DMA_0);

    ControlWord.SRCINC = DMA_ChannelControl_NoInc_Res;
    ControlWord.SRCSIZE = DMA_ChannelControl_HalfWord;
    ControlWord.DSTINC = DMA_ChannelControl_HalfWord;
    ControlWord.DSTSIZE = DMA_ChannelControl_HalfWord;
    ControlWord.ARBSIZE = DMA_ChannelControl_Arbitration_4;
    ControlWord.XFERSIZE = 1024 - 1;
    ControlWord.NXTUSEBURST = 0;
    ControlWord.XFERMODE = DMA_ChannelControl_XFERMode_PingPong;

    /* Configure Control Structure of the Channel(i.e. Channel 14) */
    // DMA_ChannelConfig(DMA_ChannelControl_Primary, DMA_Channel_14, (uint32_t *)&ADC0->SSFIFO0, (uint32_t *)&adc_val[1024 - 1], ControlWord);
    // DMA_ChannelConfig(DMA_ChannelControl_Secondary, DMA_Channel_14, (uint32_t *)&ADC0->SSFIFO0, (uint32_t *)&adc_val[2048 - 1], ControlWord);

    /* Enable the Channel(i.e Channel 14) to Start the Transfer */
    RegWrite_Bits(&dma_base->ENASET, 1, 14, 1);
}