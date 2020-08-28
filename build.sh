#!/bin/bash

clear
echo "Rod's EEPROM Programmer!"
echo ""

./compile.sh
./upload.sh
../Build/Computer_Main.bin $@

echo "
Return: "$?
