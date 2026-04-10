#include "uart.h"
#include "common.h"

Queue_t UART_RX_QHandler;
Queue_t UART_TX_QHandler;

/**
 * @brief Handles UART receive interrupt.
 *
 * Reads data from the UART receive register and enqueues it for processing.
 * Called from the UART0 interrupt handler when data is available.
 */
void UART_RxHandler(void)
{
  /* Read Data and Clear Interrupt */
  uint16_t read_val = RegRead_Bits(&UART0->DR, 0, 12);

  /* Add it to Queue for processing */
  Queue_Enqueue(&UART_RX_QHandler, (uint8_t *)&read_val);
}

/**
 * @brief Handles UART transmit interrupt.
 *
 * Dequeues data from the transmission queue and writes it to the UART transmit register.
 * Called from the UART0 interrupt handler when the transmit FIFO is ready for new data.
 */
void UART_TxHandler(void)
{
  if(Queue_isEmpty(&UART_TX_QHandler) == Queue_NotEmpty)
  {
    uint8_t ch = 0;
    
    /* Dequeue Data that needs to be sent */
    Queue_Dequeue(&UART_TX_QHandler, &ch);

    /* Send Data by writting to the Register */
    UART0->DR = ch;
  }
  else
  {
    /* No Transmission of Next Data as no data is available in Queue */
  }

}

/**
 * @brief UART0 interrupt service routine.
 *
 * Reads the UART interrupt status and dispatches to appropriate handler (receive, transmit, or error).
 * Clears the corresponding interrupt flag. Asserts on error conditions.
 */
void UART0_handler(void)
{
  /* Read the UART event which caused the Interrupt *///UART Masked Interrupt Status (UARTMIS) register
  uint16_t isr_status = RegRead_Bits(&UART0->MIS, 0, 13);

  /* Check which Event has occured and Handle accordingly */
  switch(isr_status)
  {
    case UART_ISR_EVT_RECEIVE:
          RegWrite_Bits(&UART0->ICR, 1, 4, 1); // Clear the Interrupt
          UART_RxHandler();
          break;

    case UART_ISR_EVT_TRANSMIT:
          RegWrite_Bits(&UART0->ICR, 1, 5, 1); // Clear the Interrupt
          UART_TxHandler();
          break;

    case UART_ISR_EVT_FRAME_ERROR:
          RegWrite_Bits(&UART0->ICR, 1, 7, 1); // Clear the Interrupt
          ASSERT(0);
          break;
    
    case UART_ISR_EVT_PARITY_ERROR:
          RegWrite_Bits(&UART0->ICR, 1, 8, 1); // Clear the Interrupt
          ASSERT(0);
          break;

    case UART_ISR_EVT_BREAK_ERROR:
          RegWrite_Bits(&UART0->ICR, 1, 9, 1); // Clear the Interrupt
          ASSERT(0);
          break;

    case UART_ISR_EVT_OVERRUN_ERROR:
          RegWrite_Bits(&UART0->ICR, 1, 10, 1); // Clear the Interrupt
          ASSERT(0);
          break;

    default:
          ASSERT(0);
          break;
  }
}

/**
 * @brief Gets the base address of the specified UART module.
 *
 * Returns the memory base address for the given UART module for register access.
 *
 * @param mod The UART module identifier
 * @return Pointer to the UART module's base address
 */
static UART0_Type* UART_getBase(UART_Module_e mod)
{
  /* Check Preconditions */
  ASSERT(mod < UART_Module_Max);

  UART0_Type * retval = 0;

  /* Get Base Address of the corresponding UART module */
  switch(mod)
  {
    case UART_0:
        retval = (UART0_Type *)UART0_BASE;
        break;
    case UART_1:
        retval = (UART0_Type *)UART1_BASE;
        break;
    case UART_2:
        retval = (UART0_Type *)UART2_BASE;
        break;
    case UART_3:
        retval = (UART0_Type *)UART3_BASE;
        break;
    case UART_4:
        retval = (UART0_Type *)UART4_BASE;
        break;
    case UART_5:
        retval = (UART0_Type *)UART5_BASE;
        break;
    case UART_6:
        retval = (UART0_Type *)UART6_BASE;
        break;
    case UART_7:
        retval = (UART0_Type *)UART7_BASE;
        break;
    default:
        ASSERT(0);
  }

  return retval;
}

/**
 * @brief Calculates and sets the baud rate for a UART module.
 *
 * Computes the integer and fractional parts of the baud rate divider based on the system clock
 * and desired baud rate. Configures the UART prescaler to 8.
 *
 * @param base Pointer to the UART module's base address
 * @param SystemClock System clock frequency in Hz
 * @param expectedBaudrate Desired baud rate in bps
 * @return Boolean status (unused)
 */
bool UART_setBaudRate(UART0_Type* base, uint32_t SystemClock, uint32_t expectedBaudrate)
{
  /* Calculate Baudrate */
  float Baud_Val = (float)SystemClock / (8.0f * expectedBaudrate);
  uint16_t Baud_Integer = (uint16_t)Baud_Val; // Derive the Integer part of the Value
  uint8_t Baud_Fraction = (uint8_t)((((float)Baud_Val - (float)Baud_Integer) * 64.0f) + 0.5f); // Derive the Fraction part of the Value

  /* Write the Baudrate */
  RegWrite_Bits(&base->IBRD, Baud_Integer, 0, 16);
  RegWrite_Bits(&base->FBRD, Baud_Fraction, 0, 6);

  /* Set prescaler to be 8 */
  RegWrite_Bits(&base->CTL, 1, 5, 1); // Select UART prescaler as 8

  return true;
}

/**
 * @brief Sets the UART configuration to default values.
 *
 * Configures UART settings to default values: 115200 baud rate, no parity, 1 stop bit,
 * FIFO disabled, and 8-bit word length.
 *
 * @param cfg Pointer to the UART configuration structure to populate with defaults
 */
void UART_getDefaultConfig(UART_config_t *cfg)
{
  /* Set the Most common Configuration setting */
  cfg->UART_BaudRate = 115200;
  cfg->UART_Fifo = UART_FIFO_Disabled;
  cfg->UART_Parity = UART_No_Parity;
  cfg->UART_StopBit = UART_StopBit_One;
  cfg->UART_WordLength = UART_WLen_8bits;
}

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
void UART_Init(UART_Module_e mod, UART_config_t *cfg)
{
  ASSERT((mod < UART_Module_Max) && (cfg->UART_BaudRate > 0));

  UART0_Type * uart_base = 0;

  /* Reset the UART module */
  RegWrite_Bits(&SYSCTL->SRUART, 1, mod, 1);
  RegWrite_Bits(&SYSCTL->SRUART, 0, mod, 1);

  /* Enable Clock for UART module */
  RegWrite_Bits(&SYSCTL->RCGCUART, 1, mod, 1);

  /* Wait till UART module is Enabled */
  while(!RegRead_Bits(&SYSCTL->PRUART, mod, 1))
  ;

  /* Get the Base Address based on Module */
  uart_base = UART_getBase(mod);
  
  /* Disable UART */
  RegWrite_Bits(&uart_base->CTL, 0, 0, 1);
  
  /* Set the Expected Baudrate */
  UART_setBaudRate(uart_base, SYSTEM_CLOCK_FREQ, cfg->UART_BaudRate);

  /* Configure Stopbit */
  RegWrite_Bits(&uart_base->LCRH, cfg->UART_StopBit, 3, 1);

  /* Configure Parity*/
  RegWrite_Bits(&uart_base->LCRH, cfg->UART_Parity, 1, 2);

  /* Configure FIFOs*/
  RegWrite_Bits(&uart_base->LCRH, cfg->UART_Fifo, 4, 1);

  /* Select UART module's clock source - System Clock(16MHz) */
  RegWrite_Bits(&uart_base->CC, 0, 0, 4);

  /* Configure Word Length*/
  RegWrite_Bits(&uart_base->LCRH, cfg->UART_WordLength, 5, 2);

  /* Enable EOT - Trigger Interrpt after last bit cleared the serializer */
  RegWrite_Bits(&uart_base->CTL, 1, 4, 1);

  /* Define Interrupt Masks */
  RegWrite_Bits(&uart_base->IM, 1, 4, 1);  // Receive Interrupt Mask
  RegWrite_Bits(&uart_base->IM, 1, 5, 1);  // Transmit Interrupt Mask
  RegWrite_Bits(&uart_base->IM, 1, 7, 1);  // Framing Error Interrupt Mask
  RegWrite_Bits(&uart_base->IM, 1, 8, 1);  // Parity Error Interrupt Mask
  RegWrite_Bits(&uart_base->IM, 1, 9, 1);  // Break Error Interrupt Mask
  RegWrite_Bits(&uart_base->IM, 1, 10, 1); // Overrun Error Interrupt Mask

  /* Enable UART */
  RegWrite_Bits(&uart_base->CTL, 1, 0, 1);
}

/**
 * @brief Sends a single character over UART0.
 *
 * Waits until the transmit FIFO is not full, then writes the character.
 *
 * @param ch Character to send
 */
void UART_sendChar(char ch)
{
    /* Wait till Transmission is completed */
    while(((UART0->FR >> 5) & 0x01))
    ;
    UART0->DR = ch;
}

/**
 * @brief Sends a null-terminated string over UART0.
 *
 * Sends each character in the string using UART_sendChar.
 *
 * @param str Pointer to the string to send
 */
void UART_sendString(char * str)
{
  while(*str)
  {
    UART_sendChar(*str);
    str++;
  }
}

/**
 * @brief Sends a signed 32-bit integer as ASCII characters over UART0.
 *
 * Converts the number to a string and sends it using UART_sendString.
 *
 * @param num Number to send
 */
void UART_sendNumber(int32_t num)
{
  char num_arr[20] = {0};
  uint8_t first_idx = 0, last_idx = 0;
  char temp_char = 0;

  /* Check whether the input is non-printable */
  ASSERT(num != -2147483648)  

  /* Check if the number is negative */
  if(num < 0)
  {
    UART_sendChar('-'); // Send minus character first
    num *= -1; // Make the number positive
  }

  do
  {
    num_arr[last_idx] = (num % 10)+'0'; // Store the digit as character
    num /= 10;  // Remove the digit
    last_idx++;
  }while(num);

  num_arr[last_idx] = '\0'; // Place NULL character at the end of the string array

  last_idx--; // Point the index to the last character of the num_arr

  /* Swap the Characters */
  while(last_idx > first_idx)
  {
    temp_char = num_arr[first_idx];
    num_arr[first_idx] = num_arr[last_idx];
    num_arr[last_idx] = temp_char;

    last_idx--;
    first_idx++;
  }

  /* Send the ASCII converted number String */
  UART_sendString(num_arr);
}
/**
 * @brief Sends a signed 32-bit integer as ASCII characters over UART0.
 *
 * Converts the number to a string and sends it using UART_sendString.
 *
 * @param num Number to send
 */
void UART_sendNumber_NonBlocking(Queue_t *inst, int32_t num)
{
  char num_arr[20] = {0};
  uint8_t first_idx = 0, last_idx = 0;
  char temp_char = 0;

  /* Check whether the input is non-printable */
  ASSERT(num != -2147483648)  

  /* Check if the number is negative */
  if(num < 0)
  {
    UART_sendChar('-'); // Send minus character first
    num *= -1; // Make the number positive
  }

  do
  {
    num_arr[last_idx] = (num % 10)+'0'; // Store the digit as character
    num /= 10;  // Remove the digit
    last_idx++;
  }while(num);

  num_arr[last_idx] = '\0'; // Place NULL character at the end of the string array

  last_idx--; // Point the index to the last character of the num_arr

  /* Swap the Characters */
  while(last_idx > first_idx)
  {
    temp_char = num_arr[first_idx];
    num_arr[first_idx] = num_arr[last_idx];
    num_arr[last_idx] = temp_char;

    last_idx--;
    first_idx++;
  }

  /* Send the ASCII converted number String */
  UART_sendString_NonBlocking(inst, num_arr);
}
/**
 * @brief Receives a single character from UART0.
 *
 * Waits until the receive FIFO is not empty, then returns the character.
 *
 * @return Received character
 */
uint8_t UART_receiveChar(void)
{
    /* Wait till RX buffer is not empty */
    while(((UART0->FR >> 4) & 0x01))
    ;
    return (UART0->DR & 0xFF);
}

/**
 * @brief Receives a string from UART0 until newline.
 *
 * Reads characters into strBuf until '\n' is received, then null-terminates the buffer.
 *
 * @param strBuf Pointer to buffer for received string
 */
void UART_receiveString(uint8_t * strBuf)
{
    uint8_t rChar = 0;

    /* Receive and store the data in strBuf till \n character is received */
    do{
        rChar = UART_receiveChar();
        *strBuf = rChar;
        strBuf++;
    }while(rChar != '\n');

    *strBuf = '\0';
}

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
void UART_sendString_NonBlocking(Queue_t *inst, char * str)
{

  while(*str)
  {
    /* Check if the Queue is Empty as Empty Queue needs ISR to be triggered for continuous transmission */
    if(Queue_isEmpty(inst) == Queue_Empty)
    {
      /* Send Data by writing the register */
      UART_sendChar(*str);

      /* Point to Next Data for Transmission */
      str++;
    }
    else if(Queue_isFull(inst) == Queue_NotFull)
    {
      /* Add Data to the Queue */
      Queue_Enqueue(inst, (uint8_t *)str);

      /* Point to Next Data for Transmission */
      str++;
    }
    else
    {
      /* Wait till Previous Transaction is completed or Queue has some Empty space*/
    }
  }
}