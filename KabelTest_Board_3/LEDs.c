/*
 * LEDs.c
 *
 * Created: 04.03.2017 8:09:01
 *  Author: stepan
 */ 
#include "LEDs.h"

void LEDs_init()
{
	DDRG |= 1 << 2;										   // Blue LED pin to output
	DDRG |= 1 << 3;										   // Red LED pin to output
	DDRG |= 1 << 4;										   // Green LED pin to output
}

void LED_INDICATOR_init()
{
	DDRD |= 1 << 3;										   // LED 7-SEGMENTS INDICATOR init		
	DDRG |= 1 << 1;										   // LED 7-SEGMENTS INDICATOR counter pin init	
	DDRG |=	1 << 0;						   				   // LED 7-SEGMENTS INDICATOR reset pin init		
	LED_INDICATOR_RESET_PIN_LOW;	
}

void LED_INDICATOR_reset() 
{
	LED_INDICATOR_RESET;
	LED_INDICATOR_RESET_PIN_LOW;
}



void LED_INDICATOR_CELL_ADDRES(uint8_t arg_cell)
{																						 // LED 7-SEGMENTS INDICATOR show number cell
	static char cell;	
		
	if (bit_is_clear(LED_INDICATOR_PIN_REGISTER, LED_INDICATOR_PIN))					 // If LED 7-SEGMENTS INDICATOR is off
	{
		if(Mode == STNDART_PC_MODE)
			Mode = EEPROM_READ_MODE;
		
		Led_Indicator_ON();
		cell = -1;
	}
	
	if (arg_cell == INCREMENT_EEPOM_CELL)
	{
		cell++;
		
		if(Mode == STNDART_PC_MODE)
			Mode = EEPROM_READ_MODE;
		
		if (cell == 8)																	 // 0 - 7 cells can write to 2 kByte Eeprom in ATMega64a
		{
			cell = 0;
			if(Mode == EEPROM_READ_MODE)
			{
				Mode = STNDART_PC_MODE;
				Led_Indicator_OFF();
				_delay_ms(500);
			}
		}
	}
			
	else
	{
		if(Mode == STNDART_PC_MODE)
			Mode = EEPROM_READ_MODE;
		
		cell = arg_cell;
	}
	
	switch(cell)
	{
		case(0):
		cell_addres = EEPOM_CELL_ADDRES_0;
		break;
		
		case(1):
		cell_addres = EEPOM_CELL_ADDRES_1;
		break;
		
		case(2):
		cell_addres = EEPOM_CELL_ADDRES_2;
		break;
		
		case(3):
		cell_addres = EEPOM_CELL_ADDRES_3;
		break;
		
		case(4):
		cell_addres = EEPOM_CELL_ADDRES_4;
		break;
		
		case(5):
		cell_addres = EEPOM_CELL_ADDRES_5;
		break;
		
		case(6):
		cell_addres = EEPOM_CELL_ADDRES_6;
		break;
		
		case(7):
		cell_addres = EEPOM_CELL_ADDRES_7;
		break;
	}
	LED_INDICATOR_reset();
	for (uint8_t i = (cell + 1); i != 0; i--)
	{																					 // Show eeprom cell with increase 1, (from 1 to 8 - eeprom addres from 0 to 0x063C)
		LED_INDICATOR_COUNTER_PIN_HIGH;
		LED_INDICATOR_COUNTER_PIN_LOW;
	}
	_delay_ms(300);	
	
	if(bit_is_clear(LED_INDICATOR_PIN_REGISTER, LEFT_BUTTON_PIN))
	{
		_delay_ms(1000);
		if(bit_is_clear(LED_INDICATOR_PIN_REGISTER, LEFT_BUTTON_PIN))
		{
			if(Mode == EEPROM_READ_MODE)
			{
				Mode = EEPROM_WRITE_MODE;
				Blink_blueLED();
				BLUE_LED_ON;
				Timer_1_int_LONG();
				UART_RX_int_DISABLE();
			}
			else if (Mode == EEPROM_WRITE_MODE)
			{
				Mode = EEPROM_READ_MODE;
				Blink_blueLED();
				BLUE_LED_OFF;
				UART_RX_int_ENABLE();
			}
		}
		while(bit_is_clear(LED_INDICATOR_PIN_REGISTER, LEFT_BUTTON_PIN) || bit_is_clear(LED_INDICATOR_PIN_REGISTER, RIGHT_BUTTON_PIN));		
		_delay_ms(1000);
	}				
}

void Blink_blueLED()
{																						 // Blue LED blink three time
	for (uint8_t i = 3; i > 0; i--)
	{
		BLUE_LED_ON;
		_delay_ms(100);
		BLUE_LED_OFF;
		_delay_ms(100);
	}
}

void Toogle_blue_LED()
{
	if (bit_is_set(BLUE_LED_PIN_REGISTER, BLUE_LED_PIN))
	{
		BLUE_LED_OFF;
	}
	else if(bit_is_clear(BLUE_LED_PIN_REGISTER, BLUE_LED_PIN))
	{
		BLUE_LED_ON;	
	}
}

void Led_Indicator_OFF()
{
	LED_INDICATOR_OFF;
	LED_INDICATOR_COUNTER_PIN_TO_INPUT;
	LED_INDICATOR_RESET_PIN_TO_INPUT;
	
	LED_INDICATOR_COUNTER_PIN_HIGH;
	LED_INDICATOR_RESET;
}

void Led_Indicator_ON()
{
	LED_INDICATOR_init();
	LED_INDICATOR_COUNTER_PIN_LOW;
	LED_INDICATOR_ON;
}
