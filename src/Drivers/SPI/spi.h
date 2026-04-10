#ifndef __SPI_H
#define __SPI_H

#include "common.h"

typedef enum{
    SPI_Pass,
    SPI_Fail,
    SPI_Driver_Max
}SPI_Return_e;

typedef enum{
    SPI_cpha_0_cpol_0 = 0x0,
    SPI_cpha_0_cpol_1 = 0x1,
    SPI_cpha_1_cpol_0 = 0x2,
    SPI_cpha_1_cpol_1 = 0x3,
    SPI_FrameMode_Max,
}SPI_FrameMode_e;

typedef enum{
    SPI_Master = 0x0,
    SPI_Slave = 0x1,
    SPI_Mode_Max
}SPI_Mode_e;

typedef enum{
    SPI_0 = 0,
    SPI_1,
    SPI_2,
    SPI_3,
    SPI_Module_Max
}SPI_Module_e;

typedef enum{
    SPI_Freescale = 0x0,
    SPI_Texas_Instruments = 0x1,
    SPI_Microwire = 0x2,
    SPI_InterfaceOption_Max
}SPI_InterfaceOption_e;

typedef enum{
    SPI_LoopBack_Disable = 0x0,
    SPI_LoopBack_Enable = 0x1,
    SPI_LoopBack_Max
}SPI_Loopback_e;

typedef struct{
    SPI_Mode_e SPI_Mode;
    SPI_InterfaceOption_e SPI_InterfaceOption;
    uint32_t SPI_BitRate_Hz;
    uint8_t SPI_FrameSize_Bits;
    SPI_FrameMode_e SPI_Frame_Mode;
    SPI_Loopback_e SPI_Loopback_State;
}SPI_config_t;


SPI_Return_e SPI_Init(SPI_Module_e mod, SPI_config_t config);
SPI_Return_e SPI_Send(SPI_Module_e mod, uint16_t *tx_buf, uint32_t len);
SPI_Return_e SPI_Receive(SPI_Module_e mod, uint16_t *rx_buf, uint32_t len);
SPI_Return_e SPI_SendReceive(SPI_Module_e mod, uint16_t *tx_buf, uint16_t *rx_buf, uint32_t len);
SPI_Return_e SPI_DeInit(SPI_Module_e mod);
SPI_Return_e SPI_ModuleReset(SPI_Module_e mod);
SPI_Return_e SPI_ModuleEnable(SPI_Module_e mod, bool status);

#endif