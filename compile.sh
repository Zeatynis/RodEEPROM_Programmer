#!/bin/bash

echo "Rod's EEPROM Programmer Compiler!"
echo ""

gcc Interface/Serial_Read.c Interface/_RodSerial_ProcessArguments.c -o ../Build/Serial_Read.bin
avr-gcc -mmcu=atmega1284p -DF_CPU=20000000 -Os main.c _RodEEPROM_Terminal.c _RodEEPROM_Programmer.c _SteveUART_debug.c -o ../Build/Rod_EEPROM_Programmer.elf
avr-objcopy -O ihex ../Build/Rod_EEPROM_Programmer.elf ../Build/Rod_EEPROM_Programmer.hex