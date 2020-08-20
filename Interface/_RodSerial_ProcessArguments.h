// GPL-2.0 License, see LICENCE_GPL-2.0.txt
/*
 * _RodSerial_ProcessArguments.h - header for functions to Process Command line arguments
 * Copyright (C) 2020 Rodrigo Amaral  <rodrigo_amaral01@outlook.com>
 */

#ifndef _RODSERIAL_PROCESSARGUMENTS_H
#define _RODSERIAL_PROCESSARGUMENTS_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

extern int RETURN_ERROR;
extern char* PortString;
extern char* FileString;

//	Checks if both input strings are the same
uint8_t _RodSerial_CheckString(char* string1, char* string2);
uint8_t _RodSerial_ProcessArguments(int argc, char** argv);

#endif //_RODSERIAL_PROCESSARGUMENTS_H