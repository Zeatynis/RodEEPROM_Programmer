#!/bin/bash

echo "Rod's EEPROM Programmer Compiler!"
echo ""

clang Interface/Computer_Main.c Mini_Assembler/_RodMiniAssembler_Translation.c Interface/_RodTools_Arguments.c Interface/_RodSerial_Interface.c -o ../Build/Computer_Main.bin
avr-gcc -mmcu=atmega1284p -DF_CPU=16000000 -Os Micocontroller/Microcontroller_Main.c Micocontroller/_RodEEPROM_SerialComms.c Micocontroller/_RodEEPROM_Programmer.c Micocontroller/_SteveUART_debug.c -o ../Build/Rod_EEPROM_Programmer.elf
avr-objcopy -O ihex ../Build/Rod_EEPROM_Programmer.elf ../Build/Rod_EEPROM_Programmer.hex
