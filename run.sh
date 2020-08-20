#!/bin/bash

clear	
echo "Starting Rod's EEPROM Programmer!"
echo ""

sudo avrdude -c avrispmkii -P usb -p m1284p #-U flash:w:../Build/Rod_EEPROM_Programmer.hex
../Build/Serial_Read.bin $@