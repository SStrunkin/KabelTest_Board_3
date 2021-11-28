/*
 * Timer_1.h
 *
 * Created: 15.04.2017 10:25:43
 *  Author: stepan
 */ 


#ifndef TIMER_1_H_
#define TIMER_1_H_

#include <avr/io.h>
/* -----------------------------------------------------------------------------
*                        Define basic Timer1 operations
* ------------------------------------------------------------------------------
*/

#define CLEAR_TCNT1							 TCNT1 = 0


/* -----------------------------------------------------------------------------
*                        Define Timer1 functions
* ------------------------------------------------------------------------------
*/

void Timer_1_int_LONG(void);
void Timer_1_int_SHORT(void);
void Timer_1_int_DISABLE(void);


#endif /* TIMER_1_H_ */