/*
 * EEPROM.h
 *
 * Created: 11.03.2017 7:19:28
 *  Author: stepan
 */ 
#ifndef EEPROM_H_
#define EEPROM_H_

#include <avr/io.h>
#define F_CPU 8000000UL																	 // 8 MHz
#include <util/delay.h>
#include "Process.h"
#include "Interrupts.h"

extern uint16_t cell_addres;
extern uint16_t ToEepromFromPC_cell_addres;
/* -----------------------------------------------------------------------------
*                        Define basic EEPROM constants and operations
* ------------------------------------------------------------------------------
*/
#define INCREMENT_EEPOM_CELL					 10										 // This value interpreted as command of an increment

#define STANDBY									 0
#define STNDART_PC_MODE							 1
#define EEPROM_READ_MODE						 2
#define EEPROM_WRITE_MODE						 3
#define EEPROM_WRITE_FROM_PC_MODE				 4

#define CELL_LENGH								 0x00E4
#define EEPOM_CELL_ADDRES_0						 0										 // Eeprom cell adders
#define EEPOM_CELL_ADDRES_1						 0x00E4
#define EEPOM_CELL_ADDRES_2						 0x01C8
#define EEPOM_CELL_ADDRES_3						 0x02AC
#define EEPOM_CELL_ADDRES_4						 0x0390
#define EEPOM_CELL_ADDRES_5						 0x0474
#define EEPOM_CELL_ADDRES_6						 0x0558
#define EEPOM_CELL_ADDRES_7						 0x063C


/* -----------------------------------------------------------------------------
*                        Define EEPROM functions
* ------------------------------------------------------------------------------
*/
void EEPROM_write(uint16_t uiAddress, uint8_t ucData);
uint8_t EEPROM_read(uint16_t uiAddress);
void corret_bytes(void);																 // Masked not using pins
void to_EEPROM(void);
void Scan_and_write_read_EEPROM(void);
void from_EEPROM(void);
void ToEepromFromPC(uint8_t data);

#endif /* EEPROM_H_ */