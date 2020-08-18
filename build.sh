#!/bin/bash

clear
echo "Rod's EEPROM Programmer!"
echo ""

./compile.sh
./upload.sh
../Build/Serial_Read.bin $1
