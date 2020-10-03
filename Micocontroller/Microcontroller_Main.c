/* GPL-2.0 License, see LICENCE_GPL-2.0.txt */
/* https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html */
/*
 * Microcontroller_Main.c - main for EEPROM Programmer
 * Copyright (C) 2020 Rodrigo Amaral  <rodrigo_amaral01@outlook.com>
 */

#include "_SteveUART_debug.h"
#include "_RodEEPROM_SerialComms.h"
#include "_RodEEPROM_Programmer.h"

int main()
{
	/*	Setups 	*/
	_SteveUART_init_debug_uart0();
	_RodEEPROM_ProgrammerSetup();
	/* PORTD ^= (1<<PD7); /* */

	/*	Establish Serial Connection  */
	START_COMMS:
	_RodEEPROM_EstablishSerialConnection();

	_RodEEPROM_ClearScreen();
	printf(StartString);

	/*	Main Loop  */
	uint8_t val = 0;
	char ch = 'a';
	while(1)
	{
		ch = getchar();
		val = _RodEEPROM_ProcessInput(ch);
		
		if(val == 1)
			break;
		else if(val == 2)
			goto START_COMMS;
	}

	return EXIT_SUCCESS;
}