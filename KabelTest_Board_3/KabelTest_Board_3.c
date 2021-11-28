/*
 * KabelTest_Board_3.c
 *
 * Created: 27.02.2017 11:43:48
 *  Author: Strunkin Stepan
 */ 

#include "KabelTest_Board_3.h"

int main(void)
{   
	LEDs_init();
	LED_INDICATOR_init();	
	LED_INDICATOR_reset();	
	Led_Indicator_OFF();	
	Buttons_int_init();
	USART_Init( MYUBRR );	
	Mode = STNDART_PC_MODE;	
		
	sei();
	
	for (;;);			
}

