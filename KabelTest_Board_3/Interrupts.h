/*
 * Interrupts.h
 *
 * Created: 05.03.2017 9:06:48
 *  Author: stepan
 */ 
#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include "LEDs.h"
#include "EEPROM.h"
#include "Process.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Timer_1.h"
/* -----------------------------------------------------------------------------
*                        Define prototype interrupts funktions
* ------------------------------------------------------------------------------
*/
void Buttons_int_init(void);								   // Int1 and Int2 init to falling front
void Buttons_ints_ENABLE(void);
void Buttons_ints_DISABLE(void);

#endif /* INTERRUPTS_H_ */