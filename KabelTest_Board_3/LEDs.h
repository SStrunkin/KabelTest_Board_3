/*
 * LEDs.h
 *
 * Created: 04.03.2017 8:40:32
 *  Author: stepan
 */ 
#ifndef LEDS_H_
#define LEDS_H_

#include <avr/io.h>
#define F_CPU 8000000UL																	 // 8 MHz
#include "EEPROM.h"
#include <util/delay.h>
#include <avr/sfr_defs.h>
#include "Timer_1.h"

extern uint8_t Mode;
extern uint16_t cell_addres;
/* -----------------------------------------------------------------------------
*                        Define basic LEDs operations
* ------------------------------------------------------------------------------
*/
#define BLUE_LED_ON								 PORTG |= 1 << 2						 // BLUE LED ON
#define BLUE_LED_OFF							 PORTG &= ~(1 << 2)						 // BLUE LED OFF

#define RED_LED_ON								 PORTG |= 1 << 3						 // RED LED ON
#define RED_LED_OFF								 PORTG &= ~(1 << 3)						 // RED LED OFF

#define GREEN_LED_ON							 PORTG |= 1 << 4						 // GREEN LED ON
#define GREEN_LED_OFF							 PORTG &= ~(1 << 4)						 // GREEN LED OFF

/* -----------------------------------------------------------------------------
*                        Define basic LED INDICATOR operations
* ------------------------------------------------------------------------------
*/
#define BLUE_LED_PIN_REGISTER					 PING									 // BLU_LED PIN REGISTER
#define BLUE_LED_PIN							 2										 // BLU_LED PIN

#define LED_INDICATOR_PIN_REGISTER				 PIND									 // LED 7-SEGMENTS INDICATOR PIN REGISTER
#define LED_INDICATOR_PIN						 3										 // LED 7-SEGMENTS INDICATOR PIN
#define RIGHT_BUTTON_PIN						 2										 // Right button PIN
#define LEFT_BUTTON_PIN							 1										 // Left button PIN

#define LED_INDICATOR_ON						 PORTD |= 1 << 3						 // LED 7-SEGMENTS INDICATOR ON
#define LED_INDICATOR_OFF						 PORTD &= ~(1 << 3)						 // LED 7-SEGMENTS INDICATOR OFF

#define LED_INDICATOR_COUNTER_PIN_TO_INPUT		 DDRG &= ~(1 << 1)						 // SET PIN 1 PORTG TO INPUT
#define LED_INDICATOR_COUNTER_PIN_HIGH			 PORTG |= 1 << 1						 // LED 7-SEGMENTS INDICATOR COUNTER PIN HIGH
#define LED_INDICATOR_COUNTER_PIN_LOW			 PORTG &= ~(1 << 1)						 // LED 7-SEGMENTS INDICATOR COUNTER PIN LOW

#define LED_INDICATOR_RESET_PIN_TO_INPUT		 DDRG &= ~(1 << 0)						 // SET PIN 0 PORTG TO INPUT
#define LED_INDICATOR_RESET						 PORTG |= 1 << 0						 // LED 7-SEGMENTS INDICATOR RESET 
#define LED_INDICATOR_RESET_PIN_LOW				 PORTG &= ~(1 << 0)						 // LED 7-SEGMENTS INDICATOR RESET PIN LOW
/* -----------------------------------------------------------------------------
*                        Define prototype LEDs functions
* ------------------------------------------------------------------------------
*/

void LEDs_init();																		 // Init LEDS RED GREEN BLUE
void LED_INDICATOR_init();															     // LED 7-SEGMENTS INDICATOR init
void LED_INDICATOR_CELL_ADDRES(uint8_t number_cell);								 // LED 7-SEGMENTS INDICATOR show number cell and return eeprom cell adders
void LED_INDICATOR_reset();																 // LED 7-SEGMENTS INDICATOR show 0
void Blink_blueLED();																	 // Blue LED blink thre time
void Toogle_blue_LED();																	 // Toogle blue LED
void Led_Indicator_OFF();
void Led_Indicator_ON();

#endif /* LEDS_H_ */
