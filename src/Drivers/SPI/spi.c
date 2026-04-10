#include "spi.h"
#include "../PinMux/pinconfig.h"
#include "TM4C123GH6PM.h"
#include "common.h"

static SSI0_Type* SPI_getBase(SPI_Module_e mod)
{
    /* Check the Preconditions */
    ASSERT(mod < SPI_Module_Max);

    SSI0_Type* retval = 0;

    /* Map the base address of SPI Module */
    switch(mod)
    {
        case SPI_0:
            retval = SSI0;
            break;
        case SPI_1:
            retval = SSI1;
            break;
        case SPI_2:
            retval = SSI2;
            break;
        case SPI_3:
            retval = SSI3;
            break;
        default:
            ASSERT(0);
            break;
    }

    return retval;
}

__INLINE__ static int32_t SPI_calcBitRate(uint32_t sys_clk, uint32_t precalar, uint32_t divider)
{
    /* Formula: SSInClk = SysClk / (CPSDVSR * (1 + SCR)) */
    return (sys_clk / (precalar * divider));
}

static int32_t SPI_getPrescalarDivider(int32_t Expected_BitRate, uint32_t *Best_CPSR, uint32_t *Best_SCR)
{
    int32_t t_BitRate = 0;
    int32_t t_Error = 0;
    int32_t Best_Error = 0x7FFFFFFF;
    int32_t Best_BitRate = 0;
    
    for(uint32_t t_cpsr = 2; t_cpsr < 255; t_cpsr += 2)
    {
        for(uint32_t t_scr = 1; t_scr <= 256; t_scr++)
        {
            /* Calculate Bit Rate */
            t_BitRate = SPI_calcBitRate(SYSTEM_CLOCK_FREQ, t_cpsr, t_scr);

            /* Calculate Error between Expected and Calculated Bit Rate */
            t_Error = Expected_BitRate - t_BitRate;
            
            /* Take Absolute Value of Error */
            if(t_Error < 0)
                t_Error = -t_Error;
            
            /* Check if Expected BitRate is found */
            if(t_Error == 0)
            {
                /* Copy Precalar and Divider Values */
                *Best_CPSR = t_cpsr;
                *Best_SCR = t_scr;
                Best_BitRate = t_BitRate;
                
                /* Exit Iteration and Return Actual BitRate */
                return Best_BitRate;
            }
            /* Check if Error between existing and Calculated Bit Rate is low */
            else if(t_Error < Best_Error)
            {
                /* Copy Prescalar, Diver, current Best BitRate and its error */ 
                *Best_CPSR = t_cpsr;
                *Best_SCR = t_scr;
                Best_BitRate = t_BitRate;                
                Best_Error = t_Error;

                /* Continue Iteration */
            }
            else
            {
                /* Continue Iteration */
            }
        }
    }

    return Best_BitRate;
}

static uint32_t SPI_setBitRate(SPI_Module_e mod, int32_t clkFreq)
{
    /* Check the Preconditions */
    ASSERT((mod < SPI_Module_Max));

    int32_t Actual_ClockFreq = 0;
    uint32_t Prescalar_val = 0;
    uint32_t Divider_val = 0;

    /* Get the Base Address of the SPI module */
    SSI0_Type* base = SPI_getBase(mod);

    /* Configure Clock source as System Clock */
    RegWrite_Bits(&base->CC, 0x0, 0, 4);

    /* Derive the Precalar and Divider values */
    Actual_ClockFreq = SPI_getPrescalarDivider(clkFreq, &Prescalar_val, &Divider_val);

    /* Configure Prescalar for SPI module */
    base->CPSR = Prescalar_val;

    /* Configure the Divider value for the Required BitRate  */
    RegWrite_Bits(&base->CR0, Divider_val - 1, 8, 8);

    return Actual_ClockFreq;
}

SPI_Return_e SPI_Init(SPI_Module_e mod, SPI_config_t cfg)
{
    /* Check the Preconditions */
    ASSERT((mod < SPI_Module_Max) && (cfg.SPI_Mode < SPI_Mode_Max) && (cfg.SPI_InterfaceOption < SPI_InterfaceOption_Max)
            && (cfg.SPI_BitRate_Hz <= 8000000) && (cfg.SPI_FrameSize_Bits > 3) && (cfg.SPI_FrameSize_Bits <= 16)
            && (cfg.SPI_Frame_Mode < SPI_FrameMode_Max) && (cfg.SPI_Loopback_State < SPI_LoopBack_Max));

    /* Enable Clock for SPI peripheral */
    SYSCTL->RCGCSSI |= 1 << mod;

    /* Wait till the SPI peripheral is ready */
    while(!((SYSCTL->PRSSI >> mod) & 0x01))
    ;

    /* Get the Base Address of the SPI module for Register Configuration */
    SSI0_Type* base = SPI_getBase(mod);

    /* Disable the SPI module */
    SPI_ModuleEnable(mod, false);

    /* Choose SPI module to be Master/Slave */
    RegWrite_Bits(&base->CR1, cfg.SPI_Mode, 2, 1);

    /* Set the SPI Serial Clock Frequency */
    if(cfg.SPI_BitRate_Hz != SPI_setBitRate(mod, cfg.SPI_BitRate_Hz))
        ASSERT(0); // Expected Clock Frequency and Best Clock Frequency are not matching

    /* Select Interface Option */
    RegWrite_Bits(&base->CR0, cfg.SPI_InterfaceOption, 4, 2);
    
    /* Select the Frame Mode (i.e CPOL and CPHA) */
    RegWrite_Bits(&base->CR0, cfg.SPI_Frame_Mode, 6, 2);

    /* Configure the Length of Data in Frame*/
    RegWrite_Bits(&base->CR0, cfg.SPI_FrameSize_Bits - 1, 0, 4);

    /* Enable/Disable LoobBack Mode */
    RegWrite_Bits(&base->CR1, cfg.SPI_Loopback_State, 0, 1);

    /* Enable SPI module */
    SPI_ModuleEnable(mod, true);

    return SPI_Pass;
}

SPI_Return_e SPI_Send(SPI_Module_e mod, uint16_t *tx_buf, uint32_t len)
{
    /* Check the Preconditions */
    ASSERT((mod < SPI_Module_Max) && (tx_buf != NULL) && (len > 0));

    /* Get the Base Address of the SPI module for Register Configuration */
    SSI0_Type* base = SPI_getBase(mod);

    /* Discard the already received value if any during previous transmission */
    volatile uint16_t junk_val;
    
    for(uint32_t iter = 0; iter < len; iter++)
    {
        /* Poll for the TX FIFO to be empty */
        while(!((base->SR) & 0x1))
        ;

        /* Write the Data to be transmitted */
        base->DR = tx_buf[iter];

        /* Poll for the RX FIFO to be non-empty */
        while(!((base->SR >> 2) & 0x1))
        ;

        /* Discard the already received value if any during previous transmission */
        junk_val = base->DR;
    }

    /* Poll till SPI is Idle after Transmission */
    while(((base->SR >> 4) & 0x01))
    ;

    (void)junk_val;

    return SPI_Pass;
}

SPI_Return_e SPI_Receive(SPI_Module_e mod, uint16_t *rx_buf, uint32_t len)
{
    /* Check the Preconditions */
    ASSERT((mod < SPI_Module_Max) && (rx_buf != NULL) && (len > 0));

    /* Get the Base Address of the SPI module for Register Configuration */
    SSI0_Type* base = SPI_getBase(mod);

    /* Discard the already received value if any during previous transmission */
    volatile uint16_t junk_val = 0;

    /* Poll for the RX FIFO to be non-empty */
    while(((base->SR >> 2) & 0x1))
    {
        /* Discard the already received value if any during previous transmission */
        junk_val = base->DR;
    }

    for(uint32_t iter = 0; iter < len; iter++)
    {
        /* Poll for the TX FIFO to be empty */
        while(!((base->SR) & 0x1))
        ;

        /* Write the Dummy Data to be transmitted */
        base->DR = 0x00;

        /* Poll for the RX FIFO to be non-empty */
        while(!((base->SR >> 2) & 0x1))
        ;

        /* Read the Data from Buffer */
        rx_buf[iter] = base->DR;
    }

    /* Poll till SPI is Idle after Transmission */
    while(((base->SR >> 4) & 0x01))
    ;

    (void)junk_val;

    return SPI_Pass;
}

SPI_Return_e SPI_SendReceive(SPI_Module_e mod, uint16_t *tx_buf, uint16_t *rx_buf, uint32_t len)
{
    /* Check the Preconditions */
    ASSERT((mod < SPI_Module_Max) && (tx_buf != NULL) && (rx_buf != NULL) && (len > 0));

    /* Get the Base Address of the SPI module for Register Configuration */
    SSI0_Type* base = SPI_getBase(mod);

    /* Discard the already received value if any during previous transmission */
    volatile uint16_t junk_val = 0;

    /* Poll for the RX FIFO to be non-empty */
    while(((base->SR >> 2) & 0x1))
    {
        /* Discard the already received value if any during previous transmission */
        junk_val = base->DR;
    }

    for(uint32_t iter = 0; iter < len; iter++)
    {
        /* Poll for the TX FIFO to be empty */
        while(!((base->SR) & 0x1))
        ;

        /* Write the Data to be transmitted */
        base->DR = tx_buf[iter];

        /* Poll for the RX FIFO to be non-empty */
        while(!((base->SR >> 2) & 0x1))
        ;

        /* Read the Data from Buffer */
        rx_buf[iter] = base->DR;
    } 
    
    /* Poll till SPI is Idle after Transmission */
    while(((base->SR >> 4) & 0x01))
    ;

    (void)junk_val;
    
    return SPI_Pass;
}

SPI_Return_e SPI_DeInit(SPI_Module_e mod)
{
    /* Reset the SPI Module */
    SPI_ModuleReset(mod);

    /* Disable the SPI Module */
    SPI_ModuleEnable(mod, false);

    return SPI_Pass;
}

SPI_Return_e SPI_ModuleReset(SPI_Module_e mod)
{
    /* Check the Preconditions */
    ASSERT((mod < SPI_Module_Max));

    /* Reset the SPI Module */
    SYSCTL->SRSSI |= 1<<mod; 
    SYSCTL->SRSSI &= ~(1<<mod); 

    /* Wait till the SPI0 peripheral is ready */
    while(!((SYSCTL->PRSSI >> mod) & 0x01))
    ;

    return SPI_Pass;
}

SPI_Return_e SPI_ModuleEnable(SPI_Module_e mod, bool status)
{
    /* Check the Preconditions */
    ASSERT(mod < SPI_Module_Max);
    
    /* Get the Base Address of the SPI module */
    SSI0_Type* base = SPI_getBase(mod);

    if(status == true)
    {
        /* Enable the SPI Module */
        base->CR1 |= (1<<1);
    }
    else if(status == false)
    {
        /* Disable the SPI Module */
        base->CR1 &= ~(1<<1);
    }
    else{
        ASSERT(0); // Undefined Parameter
    }

    return SPI_Pass;
}