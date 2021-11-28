/*
 * Timer_1.c
 *
 * Created: 15.04.2017 10:24:40
 *  Author: stepan
 */ 

#include "Timer_1.h"

void Timer_1_int_LONG(void)
{
	TIFR = 1 << TOV1;
	TCCR1B |= (1 << CS12) | (1 << CS10);
	TIMSK |= (1 << TOIE1);
	TCNT1 = 0;
}

void Timer_1_int_SHORT(void)
{
	TIFR = 1 << TOV1;
	TCCR1B |= (1 << CS12);
	TIMSK |= (1 << TOIE1);
	TCNT1 = 0;
}

void Timer_1_int_DISABLE(void)
{
	TIFR = 1 << TOV1;
	TCCR1B = 0;
	TIMSK = 0;
}
