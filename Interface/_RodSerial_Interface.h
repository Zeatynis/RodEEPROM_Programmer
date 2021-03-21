/* GPL-2.0 License, see LICENCE_GPL-2.0.txt */
/* https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html */
/*
 * _RodSerial_Interface.c - Header for functions for the Serial Interface
 * Copyright (C) 2020 Rodrigo Amaral  <rodrigo_amaral01@outlook.com>
 */

#ifndef _RODSERIAL_INTERFACE_H
#define _RODSERIAL_INTERFACE_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <stdint.h>

#define MAX_CHARACTERS 20

#define EEPROM_SIZE 65536

#define NO_CLEAR 0
#define CLEAR 1

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcomment"

/* #define DEBUG /* */

#pragma clang diagnostic pop

extern void    _RodSerial_Interface_Setup(); /* Sets up the io files needed for serial IO and the interface between PC and micro */
extern void    _RodSerial_Interface_Close(); /* Stops serial IO and interface */

extern void    _RodSerial_Interface_ClearIOBuffer(int FILENO);	/* Clears any IO file buffer */
extern void    _RodSerial_Interface_ConsoleClearScreen();		/* Clears PC Console */
extern uint8_t _RodSerial_Interface_EstablishComms();			/* Establishes Serial Communication, with micro */ /* Sends 20 ENQ signals, and checks for ACK signal sent by micro, returns 0 if ACK found, returns 1 otherwise */

extern uint8_t _RodSerial_Interface_SerialInput(); 	/* Reads the serial port io file for new received characters, and processes them */
extern uint8_t _RodSerial_Interface_SerialOutput(); /* Reads the console io file for new typed characters, and processes / transmits them */

extern uint8_t _RodSerial_Interface_SendBinaryFile(); /* Sends the binary data (file with name of binary_file_string) to be programmed by the EEEPROM programmer, CLEAR_OR_NOCLEAR is to choose wether or not to clear the rest of the EEPROM (CLEAR to do so, NO_CLEAR to not). Returns 1 if binary file is too big for EEPROM, returns 0 otherwise*/

#ifdef DEBUG
	extern uint8_t _RodSerial_Interface_Debug(); /* Displays Debug information about characters sent and received */
#endif

#endif /* _RODSERIAL_INTERFACE_H */

/*
	Special Characters Used, and their functionalities in this Communication Protocol

	14 : SO  : Shift-Out  			-> Symbolizes Right Arrow Key
	15 : SI  : Shift-In   			-> Symbolizes Left Arrow Key

	5  : ENQ : Enquiry    			-> Character used for PC to start communication with micro, micro waits for this character to be sent
	6  : ACK : Aknowledge 			-> Character sent by micro, to confirm start of communication with PC, after PC has sent a ENQ
	4  : EOT : End of Transmission  -> Character used by both PC and micro, to end communication and stop all processes by both. Micro will send this signal and shut off, by using the exit command
	25 : EM  : End of Medium		-> Character used by PC or micro to symbolize end of communication with micro, to start communication again the micro shall wait for another ENQ signal. PC will send this signal by using Ctrl + C.
	8  : BS  : Backspace			-> Character used to symbolize the backspace key, and its functionality.

	3  : ETX : End of Text 			-> Character used by micro, to tell the PC to clear the terminal.

	Binary file upload
	17 : DC1 : Device Control 1		-> Character used by micro, to ask for binary file to be programmed
	6  : ACK : Aknowledge			-> Character used by PC to symbolize a binary file to be uploaded has been specified, and it can start transmitting the data.
	21 : NAK : Negative Aknowledge	-> Character used by PC to symbolize a binary file has not been specified
*/