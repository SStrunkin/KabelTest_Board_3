/*
 * Interrupts.c
 *
 * Created: 05.03.2017 9:06:16
 *  Author: stepan
 */ 
#include "Interrupts.h"

void Buttons_int_init()
{														   // Int1 and Int2 init to falling front
	PORTD |= 1 << 1;									   // Interrupt pins PULL UP
	PORTD |= 1 << 2;
	
	EICRA |= (1 << ISC01);								   // Int1 and Int2 to falling front
	EIMSK |= (1 << INT1)|(1 << INT2);					   // Int1 and Int2 enable
	
}

void Buttons_ints_DISABLE(void)
{
	EIMSK &= ~(1 << INT1);
	EIMSK &= ~(1 << INT2);											  
}

void Buttons_ints_ENABLE(void)
{
	EIFR |= (1 << INTF1) | (1 << INTF2);
	EIMSK |= (1 << INT1)|(1 << INT2);					   // Int1 and Int2 enable
}

ISR(INT1_vect)
{														   // Button 1(left button) interrupt vector
	GREEN_LED_OFF;
	RED_LED_OFF;
	
	switch(Mode)
	{
		case(STNDART_PC_MODE):
		Scan_USART_Transmit();		
		break;													   
		
		case(EEPROM_READ_MODE):		
		Scan_and_write_read_EEPROM();				
		break;	
		
		case(EEPROM_WRITE_MODE):			
		for (uint8_t i = 10; i != 0; i--)
		{
			if(bit_is_clear(LED_INDICATOR_PIN_REGISTER, LEFT_BUTTON_PIN))
			_delay_ms(200);
			else break;
		}
											
		if(bit_is_clear(LED_INDICATOR_PIN_REGISTER, LEFT_BUTTON_PIN))	
		Scan_and_write_read_EEPROM();
		break;
	}
}

ISR(INT2_vect)
{														   // Button 2(right button) interrupt vector
	GREEN_LED_OFF;
	RED_LED_OFF;
	
	LED_INDICATOR_CELL_ADDRES(INCREMENT_EEPOM_CELL);	
}

ISR(USART0_RX_vect)
{		
	if (Mode == EEPROM_WRITE_FROM_PC_MODE)
	{
		ToEepromFromPC(USART_Receive());		
	}
	
	else
	{													  // USART RX complete interrupt vector
		Processing_RecivedByte(USART_Receive());
		USART_Flush();
	}
}

ISR (TIMER1_OVF_vect)
{
	static uint8_t count;			
	count++;
	if (count == 3)
	{
		Mode = STNDART_PC_MODE;
		BLUE_LED_OFF;
		UART_RX_int_ENABLE();
		Timer_1_int_DISABLE();
		Buttons_ints_ENABLE();	
		Led_Indicator_OFF();
		count = 0;
	}
	
}


