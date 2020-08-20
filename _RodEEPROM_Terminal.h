// GPL-2.0 License, see LICENCE_GPL-2.0.txt
/*
 * _RodEEPROM_Terminal.c - header for functions for Command Line Interface
 * Copyright (C) 2020 Rodrigo Amaral  <rodrigo_amaral01@outlook.com>
 */

#ifndef _RODEEPROM_TEMRINAL_H
#define _RODEEPROM_TEMRINAL_H

#include "_RodEEPROM_Programmer.h"

#define COMMAND_SIZE 10

static uint8_t DEBUG = 1;

static char StartNormalString[] = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nWelcome to Rod's EEPROM programmer!\nPlease select one of the following commands:\n\nread\nwrite\nclear\nexit\n\n";
static char StartDebugString[] =  "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nWelcome to Rod's DEBUG EEPROM programmer!\nPlease select one of the following commands:\n\nread\nwrite\nclear\nexit\n\n";
static char* StartString = StartNormalString;

void _RodEEPROM_ClearScreen();

//Checks if both input strings are the same, returns 0 if successful
uint8_t _RodEEPROM_CheckString(char* string1, char* string2);

//Checks if the corresponding string is associated with a function, then executes it
void _RodEEPROM_CommandExecute(char* commandToExecute);

//Processes Serial inputs
void _RodEEPROM_ProcessInput(char c);

#endif //_RODEEPROM_TEMRINAL_H