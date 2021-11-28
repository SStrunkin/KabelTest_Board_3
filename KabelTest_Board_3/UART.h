/*
 * UART.h
 *
 * Created: 08.03.2017 9:54:03
 *  Author: stepan
 */ 
#ifndef UART_H_
#define UART_H_

#include <avr/io.h>
#include "Process.h"
/* -----------------------------------------------------------------------------
*                        Define basic UART operations
* ------------------------------------------------------------------------------
*/
#define FOSC 8000000// Clock Speed
#define BAUD 19200
#define MYUBRR FOSC/16/BAUD-1

/* -----------------------------------------------------------------------------
*                        Define prototype UART functions
* ------------------------------------------------------------------------------
*/
void USART_Init( uint16_t ubrr );
void USART_Transmit( uint8_t data );
void USART_Transmit_0(void);
void USART_Transmit_1(void);
void USART_Transmit_space(void);
uint8_t USART_Receive( void );
void USART_Flush( void );
void Processing_RecivedByte(uint8_t data);
void UART_RX_int_DISABLE(void);
void UART_RX_int_ENABLE(void);

#endif /* UART_H_ */