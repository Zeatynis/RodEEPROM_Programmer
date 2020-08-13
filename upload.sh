#!/bin/bash
echo "AVR Compiling and Flashing for Rod's EEPROM Programmer"
echo ""

avr-gcc -mmcu=atmega1284 -DF_CPU=20000000 -Os main.c _RodEEPROM_Terminal.c _RodEEPROM_Programmer.c _SteveUART_debug.c -o ../Build/Rod_EEPROM_Programmer.elf
avr-objcopy -O ihex ../Build/Rod_EEPROM_Programmer.elf ../Build/Rod_EEPROM_Programmer.hex
sudo avrdude -c avrispmkii -P usb -p m1284 -U flash:w:../Build/Rod_EEPROM_Programmer.hex

#-c arduino -P /dev/ttyUSB0 -b 57600 - D -U flash:w:Build/Rod_EEPROM_Programmer.hex
#-p m1284 -c avrispmkii -P usb -U lfuse:w:0xe2:m

#sudo avrdude -c avrispmkii -P usb -p m644p -U lfuse:w:0xfe:m

# 00XXXX00