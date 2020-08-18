Rod's EEPROM Programmer, with Atmel microcontroller (Atmega 164, 324, 644, 1284)

This repository is for a simple Programmer for a 28 PDIP EEPROM (or less), using (40 PDIP) Atmel Microntrollers.

For the Microcontrollers mencioned above, how to wire the pins on the EEPROM is shown on _RodEEPROM_Programmer.h

This is still in the early stages, for now I just want to get it working, feel free to contribute.


Commands:

	- clear:  writes 0xff on all addresses to clear the EEPROM
	- read:   displays the EEPROM contents
	- write:  NOT IMPLEMENTED
	- debug!: Used to enter/exit debug mode
	- exit:	  Stops Interface

debug mode shows each character received and displays the command string contents by pressing the '`' key.
Debug mode can be exited by pressing ESC then '`' or by usinf the debug! command

Ctr+c implemented