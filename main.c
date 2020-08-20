// GPL-2.0 License, see LICENCE_GPL-2.0.txt
/*
 * main.c - main for EEPROM Programmer
 * Copyright (C) 2020 Rodrigo Amaral  <rodrigo_amaral01@outlook.com>
 */

#include "_SteveUART_debug.h"
#include "_RodEEPROM_Terminal.h"
#include "_RodEEPROM_Programmer.h"

const char connectionEstablished_char = 1;

int main()
{
	/*	Setups 	*/
	_SteveUART_init_debug_uart0();
	_RodEEPROM_ProgrammerSetup();
	//PORTD ^= (1<<PD7);

	/*	Establish Serial Connection  */
	while(getchar() != connectionEstablished_char)
	{
		PORTD ^= (1<<PD7);
	}
	putchar(connectionEstablished_char);

	_RodEEPROM_ClearScreen();
	printf(StartString);

	/*	Main Loop  */
	while(1)
	{
		_RodEEPROM_ProcessInput(getchar());
	}

	return EXIT_SUCCESS;
}