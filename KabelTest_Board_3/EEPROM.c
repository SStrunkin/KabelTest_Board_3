/*
 * EEPROM.c
 *
 * Created: 11.03.2017 7:19:11
 *  Author: stepan
 */ 
#include "EEPROM.h"

static uint8_t F = 0;
static uint8_t E = 0;
static uint8_t B = 0;
static uint8_t D = 0;
static uint8_t C = 0;
static uint8_t A = 0;

static uint8_t F_compare = 0;
static uint8_t E_compare = 0;
static uint8_t B_compare = 0;
static uint8_t D_compare = 0;
static uint8_t C_compare = 0;
static uint8_t A_compare = 0;

static uint16_t Eeprom_addres;

void EEPROM_write(uint16_t uiAddress, uint8_t ucData)
{
																						 /* Wait for completion of previous write */
	while(EECR & (1<<EEWE))
	;
																						 /* Set up address and data registers */
	EEAR = uiAddress;
	EEDR = ucData;
																						 /* Write logical one to EEMWE */
	EECR |= (1<<EEMWE);
																						 /* Start eeprom write by setting EEWE */
	EECR |= (1<<EEWE);
}

uint8_t EEPROM_read(uint16_t uiAddress)
{
																						 /* Wait for completion of previous write */
	while(EECR & (1<<EEWE))
	;
																						 /* Set up address register */
	EEAR = uiAddress;
																						 /* Start eeprom read by writing EERE */
	EECR |= (1<<EERE);
																						 /* Return data from data register */
	return EEDR;
}

void corret_bytes(void)
{																						 // Masked not using pins
	F = PINF;
	E = PINE;
	B = PINB;
	D = PIND;
	C = PINC;
	A = PINA;
	
	F |= (1 << 7)|(1 << 6)|(1 << 5)|(1 << 4);
	E |= (1 << 0)|(1 << 1);
	D |= (1 << 1)|(1 << 2)|(1 << 3)|(1 << 4);
}

void to_EEPROM(void)
{
	EEPROM_write(Eeprom_addres, F);
	Eeprom_addres++;
	EEPROM_write(Eeprom_addres, E);
	Eeprom_addres++;
	EEPROM_write(Eeprom_addres, B);
	Eeprom_addres++;
	EEPROM_write(Eeprom_addres, D);
	Eeprom_addres++;
	EEPROM_write(Eeprom_addres, C);
	Eeprom_addres++;
	EEPROM_write(Eeprom_addres, A);
	Eeprom_addres++;
}

 void Scan_and_write_read_EEPROM(void)
{		
		CLEAR_TCNT1;			
		Eeprom_addres = cell_addres;			
	//*********************************************************************************************** ���������� 1 �� ��� 3 ����� F
		DDRF |=	1 << 3;
		PORTF |= 1 << 3;
		Toogle_blue_LED();
		_delay_ms(RC_DELAY);
		corret_bytes();
	
		if (Mode == EEPROM_READ_MODE)	from_EEPROM();
		else if(Mode == EEPROM_WRITE_MODE)	to_EEPROM();
		
		DDRF &= ~(1 << 3);			// ������� 1 � ����
		PORTF &= ~(1 << 3);
	//*********************************************************************************************** ���������� 1 �� ��� 2 ����� F	
		DDRF |=	1 << 2;
		PORTF |= 1 << 2;
		_delay_ms(RC_DELAY);
		corret_bytes();
	
		if (Mode == EEPROM_READ_MODE)	from_EEPROM();
		else if(Mode == EEPROM_WRITE_MODE)	to_EEPROM();
	
		DDRF &= ~(1 << 2);			// ������� 1 � ����
		PORTF &= ~(1 << 2);
	//*********************************************************************************************** ���������� 1 �� ��� 1 ����� F	
		DDRF |=	1 << 1;
		PORTF |= 1 << 1;
		_delay_ms(RC_DELAY);
		corret_bytes();
	
		if (Mode == EEPROM_READ_MODE)	from_EEPROM();
		else if(Mode == EEPROM_WRITE_MODE)	to_EEPROM();
	
		DDRF &= ~(1 << 1);			// ������� 1 � ����
		PORTF &= ~(1 << 1);
	
	//*********************************************************************************************** ���������� 1 �� ��� 0 ����� F	
		DDRF |=	1 << 0;
		PORTF |= 1 << 0;
		_delay_ms(RC_DELAY);
		corret_bytes();
	
		if (Mode == EEPROM_READ_MODE)	from_EEPROM();
		else if(Mode == EEPROM_WRITE_MODE)	to_EEPROM();
	
		DDRF &= ~(1 << 0);			// ������� 1 � ����
		PORTF &= ~(1 << 0);
	
	//*********************************************************************************************** ���������� 1 �� ��� 2 ����� E	
		DDRE |=	1 << 2;
		PORTE |= 1 << 2;
		Toogle_blue_LED();
		_delay_ms(RC_DELAY);
		corret_bytes();
	
		if (Mode == EEPROM_READ_MODE)	from_EEPROM();
		else if(Mode == EEPROM_WRITE_MODE)	to_EEPROM();
	
		DDRE &= ~(1 << 2);			// ������� 1 � ����
		PORTE &= ~(1 << 2);
	//*********************************************************************************************** ���������� 1 �� ��� 3 ����� E	
	
		DDRE |=	1 << 3;
		PORTE |= 1 << 3;
		_delay_ms(RC_DELAY);
		corret_bytes();
	
		if (Mode == EEPROM_READ_MODE)	from_EEPROM();
		else if(Mode == EEPROM_WRITE_MODE)	to_EEPROM();
	
		DDRE &= ~(1 << 3);			// ������� 1 � ����
		PORTE &= ~(1 << 3);
	//*********************************************************************************************** ���������� 1 �� ��� 4 ����� E	
	
		DDRE |=	1 << 4;
		PORTE |= 1 << 4;
		_delay_ms(RC_DELAY);
		corret_bytes();
	
		if (Mode == EEPROM_READ_MODE)	from_EEPROM();
		else if(Mode == EEPROM_WRITE_MODE)	to_EEPROM();
	
		DDRE &= ~(1 << 4);			// ������� 1 � ����
		PORTE &= ~(1 << 4);
	//*********************************************************************************************** ���������� 1 �� ��� 5 ����� E	
	
		DDRE |=	1 << 5;
		PORTE |= 1 << 5;
		_delay_ms(RC_DELAY);
		corret_bytes();
	
		if (Mode == EEPROM_READ_MODE)	from_EEPROM();
		else if(Mode == EEPROM_WRITE_MODE)	to_EEPROM();
	
		DDRE &= ~(1 << 5);			// ������� 1 � ����
		PORTE &= ~(1 << 5);
	//*********************************************************************************************** ���������� 1 �� ��� 6 ����� E	
	
		DDRE |=	1 << 6;
		PORTE |= 1 << 6;
		_delay_ms(RC_DELAY);
		corret_bytes();
	
		if (Mode == EEPROM_READ_MODE)	from_EEPROM();
		else if(Mode == EEPROM_WRITE_MODE)	to_EEPROM();
	
		DDRE &= ~(1 << 6);			// ������� 1 � ����
		PORTE &= ~(1 << 6);
		//*********************************************************************************************** ���������� 1 �� ��� 7 ����� E	
	
		DDRE |=	1 << 7;
		PORTE |= 1 << 7;
		_delay_ms(RC_DELAY);
		corret_bytes();
	
		if (Mode == EEPROM_READ_MODE)	from_EEPROM();
		else if(Mode == EEPROM_WRITE_MODE)	to_EEPROM();
	
		DDRE &= ~(1 << 7);			// ������� 1 � ����
		PORTE &= ~(1 << 7);
	//*********************************************************************************************** ���������� 1 �� ��� 0 ����� B	
		DDRB |=	1 << 0;
		PORTB |= 1 << 0;
		Toogle_blue_LED();
		_delay_ms(RC_DELAY);
		corret_bytes();
	
		if (Mode == EEPROM_READ_MODE)	from_EEPROM();
		else if(Mode == EEPROM_WRITE_MODE)	to_EEPROM();
	
		DDRB &= ~(1 << 0);			// ������� 1 � ����
		PORTB &= ~(1 << 0);
	//*********************************************************************************************** ���������� 1 �� ��� 1 ����� B	
		DDRB |=	1 << 1;
		PORTB |= 1 << 1;
		_delay_ms(RC_DELAY);
		corret_bytes();
	
		if (Mode == EEPROM_READ_MODE)	from_EEPROM();
		else if(Mode == EEPROM_WRITE_MODE)	to_EEPROM();
	
		DDRB &= ~(1 << 1);			// ������� 1 � ����
		PORTB &= ~(1 << 1);	
	//*********************************************************************************************** ���������� 1 �� ��� 2 ����� B	
		DDRB |=	1 << 2;
		PORTB |= 1 << 2;
		_delay_ms(RC_DELAY);
		corret_bytes();
	
		if (Mode == EEPROM_READ_MODE)	from_EEPROM();
		else if(Mode == EEPROM_WRITE_MODE)	to_EEPROM();
	
		DDRB &= ~(1 << 2);			// ������� 1 � ����
		PORTB &= ~(1 << 2);
	//*********************************************************************************************** ���������� 1 �� ��� 3 ����� B	
	
		DDRB |=	1 << 3;
		PORTB |= 1 << 3;
		_delay_ms(RC_DELAY);
		corret_bytes();
	
		if (Mode == EEPROM_READ_MODE)	from_EEPROM();
		else if(Mode == EEPROM_WRITE_MODE)	to_EEPROM();
	
		DDRB &= ~(1 << 3);			// ������� 1 � ����
		PORTB &= ~(1 << 3);
	//*********************************************************************************************** ���������� 1 �� ��� 4 ����� B	
	
		DDRB |=	1 << 4;
		PORTB |= 1 << 4;
		_delay_ms(RC_DELAY);
		corret_bytes();
	
		if (Mode == EEPROM_READ_MODE)	from_EEPROM();
		else if(Mode == EEPROM_WRITE_MODE)	to_EEPROM();
	
		DDRB &= ~(1 << 4);			// ������� 1 � ����
		PORTB &= ~(1 << 4);
	//*********************************************************************************************** ���������� 1 �� ��� 5 ����� B	
	
		DDRB |=	1 << 5;
		PORTB |= 1 << 5;
		_delay_ms(RC_DELAY);
		corret_bytes();
	
		if (Mode == EEPROM_READ_MODE)	from_EEPROM();
		else if(Mode == EEPROM_WRITE_MODE)	to_EEPROM();
	
		DDRB &= ~(1 << 5);			// ������� 1 � ����
		PORTB &= ~(1 << 5);
	//*********************************************************************************************** ���������� 1 �� ��� 6 ����� B	
	
		DDRB |=	1 << 6;
		PORTB |= 1 << 6;
		_delay_ms(RC_DELAY);
		corret_bytes();
	
		if (Mode == EEPROM_READ_MODE)	from_EEPROM();
		else if(Mode == EEPROM_WRITE_MODE)	to_EEPROM();
	
		DDRB &= ~(1 << 6);			// ������� 1 � ����
		PORTB &= ~(1 << 6);
		//*********************************************************************************************** ���������� 1 �� ��� 7 ����� B	
	
		DDRB |=	1 << 7;
		PORTB |= 1 << 7;
		_delay_ms(RC_DELAY);
		corret_bytes();
	
		if (Mode == EEPROM_READ_MODE)	from_EEPROM();
		else if(Mode == EEPROM_WRITE_MODE)	to_EEPROM();
	
		DDRB &= ~(1 << 7);			// ������� 1 � ����
		PORTB &= ~(1 << 7);
	
	//*********************************************************************************************** ���������� 1 �� ��� 0 ����� D	
		DDRD |=	1 << 0;
		PORTD |= 1 << 0;
		Toogle_blue_LED();
		_delay_ms(RC_DELAY);
		corret_bytes();
	
		if (Mode == EEPROM_READ_MODE)	from_EEPROM();
		else if(Mode == EEPROM_WRITE_MODE)	to_EEPROM();
	
		DDRD &= ~(1 << 0);			// ������� 1 � ����
		PORTD &= ~(1 << 0);

	//*********************************************************************************************** ���������� 1 �� ��� 5 ����� D	
	
		DDRD |=	1 << 5;
		PORTD |= 1 << 5;
		_delay_ms(RC_DELAY);
		corret_bytes();
	
		if (Mode == EEPROM_READ_MODE)	from_EEPROM();
		else if(Mode == EEPROM_WRITE_MODE)	to_EEPROM();
	
		DDRD &= ~(1 << 5);			// ������� 1 � ����
		PORTD &= ~(1 << 5);
	//*********************************************************************************************** ���������� 1 �� ��� 6 ����� D	
	
		DDRD |=	1 << 6;
		PORTD |= 1 << 6;
		_delay_ms(RC_DELAY);
		corret_bytes();
	
		if (Mode == EEPROM_READ_MODE)	from_EEPROM();
		else if(Mode == EEPROM_WRITE_MODE)	to_EEPROM();
	
		DDRD &= ~(1 << 6);			// ������� 1 � ����
		PORTD &= ~(1 << 6);
		//*********************************************************************************************** ���������� 1 �� ��� 7 ����� D	
	
		DDRD |=	1 << 7;
		PORTD |= 1 << 7;
		_delay_ms(RC_DELAY);
		corret_bytes();
	
		if (Mode == EEPROM_READ_MODE)	from_EEPROM();
		else if(Mode == EEPROM_WRITE_MODE)	to_EEPROM();
	
		DDRD &= ~(1 << 7);			// ������� 1 � ����
		PORTD &= ~(1 << 7);
	//*********************************************************************************************** ���������� 1 �� ��� 0 ����� C	
		DDRC |=	1 << 0;
		PORTC |= 1 << 0;
		Toogle_blue_LED();
		_delay_ms(RC_DELAY);
		corret_bytes();
	
		if (Mode == EEPROM_READ_MODE)	from_EEPROM();
		else if(Mode == EEPROM_WRITE_MODE)	to_EEPROM();
	
		DDRC &= ~(1 << 0);			// ������� 1 � ����
		PORTC &= ~(1 << 0);
	//*********************************************************************************************** ���������� 1 �� ��� 1 ����� C	
		DDRC |=	1 << 1;
		PORTC |= 1 << 1;
		_delay_ms(RC_DELAY);
		corret_bytes();
	
		if (Mode == EEPROM_READ_MODE)	from_EEPROM();
		else if(Mode == EEPROM_WRITE_MODE)	to_EEPROM();
	
		DDRC &= ~(1 << 1);			// ������� 1 � ����
		PORTC &= ~(1 << 1);	
	//*********************************************************************************************** ���������� 1 �� ��� 2 ����� C	
		DDRC |=	1 << 2;
		PORTC |= 1 << 2;
		_delay_ms(RC_DELAY);
		corret_bytes();
	
		if (Mode == EEPROM_READ_MODE)	from_EEPROM();
		else if(Mode == EEPROM_WRITE_MODE)	to_EEPROM();
	
		DDRC &= ~(1 << 2);			// ������� 1 � ����
		PORTC &= ~(1 << 2);
	//*********************************************************************************************** ���������� 1 �� ��� 3 ����� C	
		DDRC |=	1 << 3;
		PORTC |= 1 << 3;
		_delay_ms(RC_DELAY);
		corret_bytes();
	
		if (Mode == EEPROM_READ_MODE)	from_EEPROM();
		else if(Mode == EEPROM_WRITE_MODE)	to_EEPROM();
	
		DDRC &= ~(1 << 3);			// ������� 1 � ����
		PORTC &= ~(1 << 3);
	//*********************************************************************************************** ���������� 1 �� ��� 4 ����� C	
		DDRC |=	1 << 4;
		PORTC |= 1 << 4;
		_delay_ms(RC_DELAY);
		corret_bytes();
	
		if (Mode == EEPROM_READ_MODE)	from_EEPROM();
		else if(Mode == EEPROM_WRITE_MODE)	to_EEPROM();
	
		DDRC &= ~(1 << 4);			// ������� 1 � ����
		PORTC &= ~(1 << 4);
	//*********************************************************************************************** ���������� 1 �� ��� 5 ����� C	
		DDRC |=	1 << 5;
		PORTC |= 1 << 5;
		_delay_ms(RC_DELAY);
		corret_bytes();
	
		if (Mode == EEPROM_READ_MODE)	from_EEPROM();
		else if(Mode == EEPROM_WRITE_MODE)	to_EEPROM();
	
		DDRC &= ~(1 << 5);			// ������� 1 � ����
		PORTC &= ~(1 << 5);
	//*********************************************************************************************** ���������� 1 �� ��� 6 ����� C	
	
		DDRC |=	1 << 6;
		PORTC |= 1 << 6;
		_delay_ms(RC_DELAY);
		corret_bytes();
	
		if (Mode == EEPROM_READ_MODE)	from_EEPROM();
		else if(Mode == EEPROM_WRITE_MODE)	to_EEPROM();
	
		DDRC &= ~(1 << 6);			// ������� 1 � ����
		PORTC &= ~(1 << 6);
		//*********************************************************************************************** ���������� 1 �� ��� 7 ����� C	
	
		DDRC |=	1 << 7;
		PORTC |= 1 << 7;
		_delay_ms(RC_DELAY);
		corret_bytes();
	
		if (Mode == EEPROM_READ_MODE)	from_EEPROM();
		else if(Mode == EEPROM_WRITE_MODE)	to_EEPROM();
	
		DDRC &= ~(1 << 7);			// ������� 1 � ����
		PORTC &= ~(1 << 7);	
	//*********************************************************************************************** ���������� 1 �� ��� 0 ����� A	
		DDRA |=	1 << 7;
		PORTA |= 1 << 7;
		Toogle_blue_LED();
		_delay_ms(RC_DELAY);
		corret_bytes();
	
		if (Mode == EEPROM_READ_MODE)	from_EEPROM();
		else if(Mode == EEPROM_WRITE_MODE)	to_EEPROM();
	
		DDRA &= ~(1 << 7);			// ������� 1 � ����
		PORTA &= ~(1 << 7);
	//*********************************************************************************************** ���������� 1 �� ��� 1 ����� A	
		DDRA |=	1 << 6;
		PORTA |= 1 << 6;
		_delay_ms(RC_DELAY);
		corret_bytes();
	
		if (Mode == EEPROM_READ_MODE)	from_EEPROM();
		else if(Mode == EEPROM_WRITE_MODE)	to_EEPROM();
	
		DDRA &= ~(1 << 6);			// ������� 1 � ����
		PORTA &= ~(1 << 6);	
	//*********************************************************************************************** ���������� 1 �� ��� 2 ����� A	
		DDRA |=	1 << 5;
		PORTA |= 1 << 5;
		_delay_ms(RC_DELAY);
		corret_bytes();
	
		if (Mode == EEPROM_READ_MODE)	from_EEPROM();
		else if(Mode == EEPROM_WRITE_MODE)	to_EEPROM();
	
		DDRA &= ~(1 << 5);			// ������� 1 � ����
		PORTA &= ~(1 << 5);
	//*********************************************************************************************** ���������� 1 �� ��� 3 ����� A	
		DDRA |=	1 << 4;
		PORTA |= 1 << 4;
		_delay_ms(RC_DELAY);
		corret_bytes();
	
		if (Mode == EEPROM_READ_MODE)	from_EEPROM();
		else if(Mode == EEPROM_WRITE_MODE)	to_EEPROM();
	
		DDRA &= ~(1 << 4);			// ������� 1 � ����
		PORTA &= ~(1 << 4);
	//*********************************************************************************************** ���������� 1 �� ��� 4 ����� A	
	
		DDRA |=	1 << 3;
		PORTA |= 1 << 3;
		_delay_ms(RC_DELAY);
		corret_bytes();
	
		if (Mode == EEPROM_READ_MODE)	from_EEPROM();
		else if(Mode == EEPROM_WRITE_MODE)	to_EEPROM();
	
		DDRA &= ~(1 << 3);			// ������� 1 � ����
		PORTA &= ~(1 << 3);
	//*********************************************************************************************** ���������� 1 �� ��� 5 ����� A	
	
		DDRA |=	1 << 2;
		PORTA |= 1 << 2;
		_delay_ms(RC_DELAY);
		corret_bytes();
	
		if (Mode == EEPROM_READ_MODE)	from_EEPROM();
		else if(Mode == EEPROM_WRITE_MODE)	to_EEPROM();
	
		DDRA &= ~(1 << 2);			// ������� 1 � ����
		PORTA &= ~(1 << 2);
	//*********************************************************************************************** ���������� 1 �� ��� 6 ����� A	
	
		DDRA |=	1 << 1;
		PORTA |= 1 << 1;
		_delay_ms(RC_DELAY);
		corret_bytes();
	
		if (Mode == EEPROM_READ_MODE)	from_EEPROM();
		else if(Mode == EEPROM_WRITE_MODE)	to_EEPROM();
	
		DDRA &= ~(1 << 1);			// ������� 1 � ����
		PORTA &= ~(1 << 1);
		//*********************************************************************************************** ���������� 1 �� ��� 7 ����� A	
	
		DDRA |=	1 << 0;
		PORTA |= 1 << 0;
		_delay_ms(RC_DELAY);
		corret_bytes();
	
		if (Mode == EEPROM_READ_MODE)	from_EEPROM();
		else if(Mode == EEPROM_WRITE_MODE)	to_EEPROM();
	
		DDRA &= ~(1 << 0);			// ������� 1 � ����
		PORTA &= ~(1 << 0);
	
	
}

void from_EEPROM(void)
{
	while(1)
	{
		
		F_compare = EEPROM_read(Eeprom_addres);
		if (F == F_compare)
		{
			GREEN_LED_ON;										// Green LED
			Eeprom_addres++;
			
		}
		else
		{
			RED_LED_ON;										// Red LED)
			GREEN_LED_OFF;											// Off Green Led
			break;
		}
		
		E_compare = EEPROM_read(Eeprom_addres);
		if (E == E_compare)
		{
			GREEN_LED_ON;										// Green LED
			Eeprom_addres++;
			
		}
		else
		{
			RED_LED_ON;										// Red LED)
			GREEN_LED_OFF;											// Off Green Led
			break;
		}
		
		B_compare = EEPROM_read(Eeprom_addres);
		if (B == B_compare)
		{
			GREEN_LED_ON;										// Green LED
			Eeprom_addres++;
			
		}
		
		else
		{
			RED_LED_ON;										// Red LED)
			GREEN_LED_OFF;											// Off Green Led
			break;
		}
		
		D_compare = EEPROM_read(Eeprom_addres);
		if (D == D_compare)
		{
			GREEN_LED_ON;										// Green LED
			Eeprom_addres++;
			
		}
		
		else
		{
			RED_LED_ON;										// Red LED)
			GREEN_LED_OFF;											// Off Green Led
			break;
		}
		
		C_compare = EEPROM_read(Eeprom_addres);
		if (C == C_compare)
		{
			GREEN_LED_ON;										// Green LED
			Eeprom_addres++;
			
		}
		
		else
		{
			RED_LED_ON;										// Red LED)
			GREEN_LED_OFF;											// Off Green Led
			break;
		}
		
		A_compare = EEPROM_read(Eeprom_addres);
		if (A == A_compare)
		{
			GREEN_LED_ON;										// Green LED
			Eeprom_addres++;
			
		}
		else
		{
			RED_LED_ON;										// Red LED)
			GREEN_LED_OFF;											// Off Green Led
			break;
		}
		break;
	}	
}

void ToEepromFromPC(uint8_t data)
{
	EEPROM_write(ToEepromFromPC_cell_addres, data);
	ToEepromFromPC_cell_addres++;
	if (ToEepromFromPC_cell_addres - cell_addres  == CELL_LENGH)
	{
		Mode = EEPROM_READ_MODE;
		BLUE_LED_OFF;
		Buttons_ints_ENABLE();
	}
	else
	{
		CLEAR_TCNT1;
		Toogle_blue_LED();
		while ( !( UCSR0A & (1<<UDRE0)) );
		UDR0 = 'r';
		while ( !( UCSR0A & (1<<UDRE0)) );
		UDR0 = 'n';
		while ( !( UCSR0A & (1<<UDRE0)) );
		UDR0 = '\n';
	}
}




	
