/*
 * Process.h
 *
 * Created: 12.03.2017 8:20:56
 *  Author: stepan
 */ 
#ifndef PROCESS_H_
#define PROCESS_H_

#include "UART.h"
#include "LEDs.h"
/* -----------------------------------------------------------------------------
*                        Define basic Process operations
* ------------------------------------------------------------------------------
*/
#define RC_DELAY								 20										 // Milliseconds to wait after pin go hight (waiting of distribution of a signal)
#define Pass									 38										 // Pass when pooling

/* -----------------------------------------------------------------------------
*                        Define prototype Process functions
* ------------------------------------------------------------------------------
*/

void pull_PINF( void );
void pull_PINE( void );
void pull_PINB( void );
void pull_PIND( void );
void pull_PINC( void );
void pull_PINA( void );
void Scan_USART_Transmit( void );
void fromEeprom_toLongString( void );

#endif /* PROCESS_H_ */