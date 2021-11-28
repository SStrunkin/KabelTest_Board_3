/*
 * UART.c
 *
 * Created: 08.03.2017 9:53:44
 *  Author: stepan
 */ 
#include "UART.h"

void USART_Init(uint16_t ubrr)
{													
	UBRR0H = (unsigned char)(ubrr>>8);													 // Set baud rate 
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1 << RXCIE0);										 // Enable: receiver, transmitter, RX complete interrupt
	UCSR0C = (3<<UCSZ00);																 // Set frame format: 8data, 1stop bit 
}

void USART_Transmit(uint8_t data)
{	
	while ( !( UCSR0A & (1<<UDRE0)) )													 // Wait for empty transmit buffer
	;
	UDR0 = data;																		 // Put data into buffer, sends the data
}

uint8_t USART_Receive(void)
{	
	while ( !(UCSR0A & (1<<RXC0)) )														 // Wait for data to be received
	;	
	return UDR0;																		 // Get and return received data from buffer
}

void USART_Flush(void)
{
	volatile uint8_t dummy;
	while ( UCSR0A & (1<<RXC0) ) dummy = UDR0;
}

void USART_Transmit_0(void)
{																						 // Transmit '0' to USART
	while ( !( UCSR0A & (1<<UDRE0)) );
	UDR0 = '0';
}

void USART_Transmit_1(void)
{																						 // Transmit '0' to USART
	while ( !( UCSR0A & (1<<UDRE0)) );
	UDR0 = '1';
}

void USART_Transmit_space(void)
{
	while ( !( UCSR0A & (1<<UDRE0)) );
	UDR0 = ' ';
}

void Processing_RecivedByte(uint8_t data)
{
	if (data == STNDART_PC_MODE)														 // Standart Comparing
	{
		Mode = STNDART_PC_MODE;
		Led_Indicator_OFF();
		Scan_USART_Transmit();
	}
	else if (data == STANDBY)
	{
		Mode = STNDART_PC_MODE;
		Led_Indicator_OFF();
	}
	else
	{
		uint8_t number, mode;
		number = mode = data;
		mode &= 0b00001111;
		number = number >> 4;
		LED_INDICATOR_CELL_ADDRES(number);
		if (mode == EEPROM_READ_MODE)
		{
			fromEeprom_toLongString();
		}
						
		else if(mode == EEPROM_WRITE_FROM_PC_MODE)
		{
			Timer_1_int_SHORT();
			Mode = EEPROM_WRITE_FROM_PC_MODE;
			Buttons_ints_DISABLE();
			ToEepromFromPC_cell_addres = cell_addres;
			while ( !( UCSR0A & (1<<UDRE0)) );
			UDR0 = 'r';
			while ( !( UCSR0A & (1<<UDRE0)) );
			UDR0 = 'r';
			while ( !( UCSR0A & (1<<UDRE0)) );
			UDR0 = '\n';
		}
	}
}

void UART_RX_int_DISABLE(void)
{
	UCSR0B &= ~(1 << RXCIE0);
}

void UART_RX_int_ENABLE(void)
{
	USART_Flush();
	UCSR0B |= (1 << RXCIE0);
}

