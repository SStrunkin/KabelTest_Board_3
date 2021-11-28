/*
 * KabelTest_Board_3.h
 *
 * Created: 18.03.2017 12:53:32
 *  Author: stepan
 */ 


#ifndef KABELTEST_BOARD_3_H_
#define KABELTEST_BOARD_3_H_

#include <avr/io.h>
#include "LEDs.h"
#include "Interrupts.h"
#include "UART.h"
#include "Timer_1.h"

/* -----------------------------------------------------------------------------
*                        Define basic LEDs operations
* ------------------------------------------------------------------------------
*/
uint8_t Mode;																			 // STNDART_PC_MODE or EEPROM_READ_MODE or EEPROM_WRITE_MODE
uint16_t cell_addres;
uint16_t ToEepromFromPC_cell_addres;


#endif /* KABELTEST_BOARD_3_H_ */