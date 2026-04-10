#ifndef __UART_H
#define __UART_H

#include "common.h"
#include "../src/Services/Queue/queue.h"

#define UART_ISR_EVT_CTS_MODEM          0x00000002U
#define UART_ISR_EVT_RECEIVE            0x00000010U
#define UART_ISR_EVT_TRANSMIT           0x00000020U
#define UART_ISR_EVT_RECEIVE_TIMEOUT    0x00000040U
#define UART_ISR_EVT_FRAME_ERROR        0x00000080U
#define UART_ISR_EVT_PARITY_ERROR       0x00000100U
#define UART_ISR_EVT_BREAK_ERROR        0x00000200U
#define UART_ISR_EVT_OVERRUN_ERROR      0x00000400U
#define UART_ISR_EVT_9BIT_MODE          0x00001000U


typedef enum{
  UART_0 = 0,
  UART_1 = 1,
  UART_2 = 2,
  UART_3 = 3,
  UART_4 = 4,
  UART_5 = 5,
  UART_6 = 6,
  UART_7 = 7,
  UART_Module_Max
}UART_Module_e;

typedef enum{
  UART_No_Parity   = 0,
  UART_Odd_Parity  = 1,
  UART_Even_Parity = 3
}UART_Parity_e;

typedef enum{
  UART_StopBit_One = 0,
  UART_StopBit_Two = 1
}UART_StopBit_e;

typedef enum{
  UART_FIFO_Disabled = 0,
  UART_FIFO_Enabled = 1
}UART_FIFO_e;

typedef enum{
  UART_WLen_5bits = 0,
  UART_WLen_6bits = 1,
  UART_WLen_7bits = 2,
  UART_WLen_8bits = 3
}UART_WordLength_e;

typedef struct{
    uint32_t UART_BaudRate;
    UART_StopBit_e UART_StopBit;
    UART_Parity_e UART_Parity;
    UART_FIFO_e UART_Fifo;
    UART_WordLength_e UART_WordLength;
}UART_config_t;

/**
 * @brief Sets the UART configuration to default values.
 *
 * Configures UART settings to default values: 115200 baud rate, no parity, 1 stop bit,
 * FIFO disabled, and 8-bit word length.
 *
 * @param cfg Pointer to the UART configuration structure to populate with defaults
 */
void UART_getDefaultConfig(UART_config_t *cfg);

/**
 * @brief Initializes a UART module with the specified configuration.
 *
 * Configures the specified UART module with the provided settings including baud rate,
 * parity, stop bits, FIFO mode, and word length. Enables interrupts for receive, transmit,
 * and error conditions. Uses system clock as source with prescaler of 8.
 *
 * @param mod The UART module to initialize (UART_0 through UART_7)
 * @param cfg Pointer to the UART configuration structure
 */
void UART_Init(UART_Module_e mod, UART_config_t *cfg);

/**
 * @brief Sends a single character over UART0.
 *
 * Waits until the transmit FIFO is not full, then writes the character.
 *
 * @param ch Character to send
 */
void UART_sendChar(char ch);

/**
 * @brief Sends a null-terminated string over UART0.
 *
 * Sends each character in the string using UART_sendChar.
 *
 * @param str Pointer to the string to send
 */
void UART_sendString(char * str);

/**
 * @brief Sends a signed 32-bit integer as ASCII characters over UART0.
 *
 * Converts the number to a string and sends it using UART_sendString.
 *
 * @param num Number to send
 */
void UART_sendNumber(int32_t num);

/**
 * @brief Receives a single character from UART0.
 *
 * Waits until the receive FIFO is not empty, then returns the character.
 *
 * @return Received character
 */
uint8_t UART_receiveChar(void);

/**
 * @brief Receives a string from UART0 until newline.
 *
 * Reads characters into strBuf until '\n' is received, then null-terminates the buffer.
 *
 * @param strBuf Pointer to buffer for received string
 */
void UART_receiveString(uint8_t * strBuf);

/**
 * @brief Sends a null-terminated string over UART using non-blocking queue-based transmission.
 *
 * Enqueues string characters for interrupt-driven transmission. The first character is sent directly
 * if the transmission queue is empty. Subsequent characters are added to the transmission queue to be
 * sent via interrupt handler. Blocks if the queue is full.
 *
 * @param inst Pointer to the UART transmission queue instance
 * @param str Pointer to the null-terminated string to send
 */
void UART_sendString_NonBlocking(Queue_t *inst, char * str);

/**
 * @brief Sends a signed 32-bit integer as ASCII characters over UART using non-blocking transmission.
 *
 * Converts the number to an ASCII string and sends it using UART_sendString_NonBlocking.
 * The transmission is performed via interrupt-driven queue-based mechanism.
 *
 * @param inst Pointer to the UART transmission queue instance
 * @param num Number to send
 */
void UART_sendNumber_NonBlocking(Queue_t *inst, int32_t num);

#endif