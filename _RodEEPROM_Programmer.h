#ifndef _RODEEPROM_PROGRAMMER_H
#define _RODEEPROM_PROGRAMMER_H

#include <avr/io.h>
#include <util/delay.h>

#include "_SteveUART_debug.h"

/*	
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

#define DELAY 5

#define HIGH 1
#define LOW 0

//Set control pins High or Low
void set_CE(uint8_t state);
void set_OE(uint8_t state);
void set_WE(uint8_t state);

void _RodEEPROM_ProgrammerSetup();

uint8_t _RodEEPROM_ReadData();
uint8_t _RodEEPROM_ReadContinousData();

void _RodEEPROM_OutputData(uint8_t data);
void _RodEEPROM_OutputContinousData(uint8_t data);

void _RodEEPROM_OutputAddress(uint16_t address);

//To write a byte on EEPROM, need setup function for Continous
void _RodEEPROM_WriteByte(uint16_t address, uint8_t data);
void _RodEEPROM_WriteContinousByte(uint16_t address, uint8_t data);

//Used for _RodEEPROM_WriteContinousByte
void _RodEEPROM_Set_WriteContinousByte();

//To read a byte from EEPROM, need setup function for Continous 
uint8_t _RodEEPROM_ReadByte(uint16_t address);
uint8_t _RodEEPROM_ReadContinousByte(uint16_t address);

//Used for _RodEEPROM_ReadContinousByte
void _RodEEPROM_Set_ReadContinousByte();

//Writes 0xff on all addresses of EEPROM
void _RodEEPROM_ClearEEPROM();

//Checks if clear was succsseful.
//Returns uint64_t MAX if successful, otherwise returns address where the check failed
uint64_t _RodEEPROM_ClearCheck();

//Displays EEPROM contents
void _RodEEPROM_ReadEEPROM();

#endif //_RODEEPROM_PROGRAMMER_H