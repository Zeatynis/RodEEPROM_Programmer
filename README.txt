Rod's EEPROM Programmer, with Atmel microcontroller (Atmega 164, 324, 644, 1284)

This repository is for a simple Programmer for a 28 PDIP EEPROM (or less), using (40 PDIP) Atmel Microntrollers.

For the Microcontrollers mencioned above, how to wire the pins on the EEPROM is shown on _RodEEPROM_Programmer.h

This is still in the early stages, for now I just want to get it working, feel free to contribute.

Command Line Arguments:

	- "-p" specifies the serial port to communicate with the Programmer
	- "-s" used to specify a text file, with hex to be translated to a binary file
	- "-o" specifies the name of the binary file, translated from the source file
	- "-b" specifies a binary file to be programmed directly, if no source file to be translated has been specified

Programmer Commands:

	- clear:  writes 0xff on all addresses to clear the EEPROM
	- read:   displays the EEPROM contents
	- write:  writes the binary file, if specified, to the EEPROM
	- exit:	  Shuts off the programmer

Ctr+c implemented, used to exit the interface and stopping communication with the programmer
