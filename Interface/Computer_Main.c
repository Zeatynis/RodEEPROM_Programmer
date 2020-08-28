/* GPL-2.0 License, see LICENCE_GPL-2.0.txt */
/*
 * Computer_Main.c - Main for EEPROM Serial Interface on PC side
 * Copyright (C) 2020 Rodrigo Amaral  <rodrigo_amaral01@outlook.com>
 */

#include "_RodSerial_Interface.h"
 
int main(int argc, char** argv)
{
	if(_RodSerial_Arguments_ProcessArguments(argc, argv))
	{
		return _RodSerial_Arguments_ERROR();
	}

	_RodSerial_Interface_Setup();

	puts("Connecting...\r");

	if(_RodSerial_Interface_EstablishComms())
	{
		goto END_WITH_CLOSE;
	}

	/* Debug */
	#ifdef DEBUG
		while(1)
		{
			if(_RodSerial_Interface_Debug())
				break;
		}
	#endif

	puts("Got here\r");
	while(1)
	{
		if(_RodSerial_Interface_SerialOutput())
			break;

		if(_RodSerial_Interface_SerialInput())
			break;
	}

	END_WITH_CLOSE:
	_RodSerial_Interface_Close();

	END:
	return EXIT_SUCCESS;
}

/*
	ERROR NUMBER | ERROR DESCRIPTION
	1			 | Couldn't establish serial connection
	2			 | No Serial port specified
	3 			 | No File Name specified
	4			 | Invalid Argument
	5			 | Repeated Argument
*/