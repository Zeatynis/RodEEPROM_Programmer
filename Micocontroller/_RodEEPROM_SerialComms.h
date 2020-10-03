/* GPL-2.0 License, see LICENCE_GPL-2.0.txt */
/* https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html */
/*
 * _RodEEPROM_SerialComms.h - header for functions for Command Line Interface
 * Copyright (C) 2020 Rodrigo Amaral  <rodrigo_amaral01@outlook.com>
 */

#ifndef _RODEEPROM_TEMRINAL_H
#define _RODEEPROM_TEMRINAL_H

#include "_RodEEPROM_Programmer.h"

#define COMMAND_SIZE 20

/* #define DEBUG /* */

#ifdef  DEBUG
	#define SEND(c); putchar(c); printf("Micro Sent     -> |%i|\n",c);
	static char StartString[] =  "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nWelcome to Rod's DEBUG EEPROM programmer!\nPlease select one of the following commands:\n\nread\nwrite\nclear\nexit\n\n";
#else
	#define SEND(c); putchar(c);
	static char StartString[] = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nWelcome to Rod's EEPROM programmer!\nPlease select one of the following commands:\n\nread\nwrite\nclear\nexit\n\n";
#endif /* DEBUG */

extern void	   _RodEEPROM_EstablishSerialConnection(); /* Establishes Serial Connection with PC*/

extern void    _RodEEPROM_ClearScreen();							 /* Sends ClearScreen command */
extern uint8_t _RodEEPROM_CheckString(char* string1, char* string2); /* Checks if both input strings are the same, returns 0 if successful */
extern uint8_t _RodEEPROM_CommandExecute(char* commandToExecute); 	 /* Checks if the corresponding string is associated with a function, then executes it, returns a non-zero value if the command executed is ment to shut-off the micro*/
extern uint8_t _RodEEPROM_ProcessInput(char c); 					 /* Processes Serial inputs, returns 1 if received EOT and 2 if received EM */

#endif /* _RODEEPROM_TEMRINAL_H */