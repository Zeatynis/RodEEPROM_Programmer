/* GPL-2.0 License, see LICENCE_GPL-2.0.txt */
/* https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html */
/*
 * _RodEEPROM_Programmer.c - header for functions to Program EEPROM
 * Copyright (C) 2020 Rodrigo Amaral  <rodrigo_amaral01@outlook.com>
 */

#ifndef _RODEEPROM_PROGRAMMER_H
#define _RODEEPROM_PROGRAMMER_H

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "_SteveUART_debug.h"

/* Number of shown bytes per line, when reading EEPROM */
#define N_SHOWN_BYTES 32

#define WRITE_DELAY 5 /* in ms */
#define READ_DELAY 5  /* in ms */

#define HIGH 1
#define LOW 0

//*  Set control pins High or Low */
extern void 	_RodEEPROM_set_CE(uint8_t state); /* Sets the Chip Enable pin, HIGH or LOW */
extern void 	_RodEEPROM_set_OE(uint8_t state); /* Sets the Output Enable pin, HIGH or LOW */
extern void 	_RodEEPROM_set_WE(uint8_t state); /* Sets the Write Enable pin, HIGH or LOW */

extern void 	_RodEEPROM_ProgrammerSetup(); 	  /* Sets up the Pins required and enables the EEPROM chip */

extern void 	_RodEEPROM_OutputData(uint8_t data);			/* Outputs a byte of data onto the data pins */
extern void 	_RodEEPROM_OutputContinousData(uint8_t data);	/* Intended for WriteContinousByte() */
extern uint8_t 	_RodEEPROM_ReadData(); 						 	/* Reads data from data pins */
extern uint8_t 	_RodEEPROM_ReadContinousData();					/* Intended for ReadContinousByte() */
extern void 	_RodEEPROM_OutputAddress(uint16_t address);		/* Outputs 15-bit address onto address pins */

/* To write a byte on EEPROM, setup function is required for continous writes */
extern void 	_RodEEPROM_WriteByte(uint16_t address, uint8_t data); 			/* Writes Byte on EEPROM, on specified address */
extern void 	_RodEEPROM_Set_WriteContinousByte(); 							/* Used for _RodEEPROM_WriteContinousByte */
extern void 	_RodEEPROM_WriteContinousByte(uint16_t address, uint8_t data); 	/* Same as WriteByte(), but intended for continous writes */

/* To read a byte from EEPROM, setup function is required for continous reads */
extern uint8_t 	_RodEEPROM_ReadByte(uint16_t address); 			/* Reads Byte on EEPROM, from specified address */
extern void 	_RodEEPROM_Set_ReadContinousByte(); 			/* Used for _RodEEPROM_ReadContinousByte */
extern uint8_t 	_RodEEPROM_ReadContinousByte(uint16_t address); /* Same as ReadByte(), but intended for continous reads */

extern void 	_RodEEPROM_ClearEEPROM();	/* Writes 0xff on all addresses of EEPROM */
extern uint64_t _RodEEPROM_ClearCheck(); 	/* Checks if clear was succsseful. Returns uint64_t MAX if successful, otherwise returns address where the check failed */
extern void		_RodEEPROM_ReadEEPROM(); 	/* Displays EEPROM contents */
extern uint8_t  _RodEEPROM_GetBinFile();	/* Get's binary file data and programs the EEPROM, returns 0 if successful, 1 if received NAK*/

#endif /* _RODEEPROM_PROGRAMMER_H */

/*	
	EEPROM pins, to microcontroller pins
			VCC
	PB0		PA0
	PB1		PA1
	PB2		PA2
	PB3		PA3
	PB4		PA4
	PD2		PA5
	PD3		PA6
	PD4		PA7
	PD5		PC7
	PD6		PC6
	PC2		PC5
	PC1		PC4
	PC0		PC3
	GND
*/
/*
DATA_BIT0 PC2
DATA_BIT1 PC1
DATA_BIT2 PC0
DATA_BIT3 PC3
DATA_BIT4 PC4
DATA_BIT5 PC5
DATA_BIT6 PC6
DATA_BIT7 PC7

ADDRESS_BIT0  PD6
ADDRESS_BIT1  PD5
ADDRESS_BIT2  PD4
ADDRESS_BIT3  PD3
ADDRESS_BIT4  PD2
ADDRESS_BIT5  PB4
ADDRESS_BIT6  PB3
ADDRESS_BIT7  PB2
ADDRESS_BIT8  PA2
ADDRESS_BIT9  PA3
ADDRESS_BIT10 PA6
ADDRESS_BIT11 PA4
ADDRESS_BIT12 PB1
ADDRESS_BIT13 PA1
ADDRESS_BIT14 PB0

_CE PA7
_OE PA5
_WE PA0

LED D7
*/