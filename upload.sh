#!/bin/bash

echo "Rod's EEPROM Programmer Uploader!"
echo ""

sudo avrdude -c avrispmkii -P usb -p m1284p -U flash:w:../Build/Rod_EEPROM_Programmer.hex

#-c arduino -P /dev/ttyUSB0 -b 57600 - D -U flash:w:Build/Rod_EEPROM_Programmer.hex
#-p m1284 -c avrispmkii -P usb -U lfuse:w:0xe2:m

#sudo avrdude -c avrispmkii -P usb -p m644p -U lfuse:w:0xfe:m