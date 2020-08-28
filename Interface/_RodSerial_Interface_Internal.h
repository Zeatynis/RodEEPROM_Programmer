/* GPL-2.0 License, see LICENCE_GPL-2.0.txt */
/*
 * _RodSerial_Interface_Internal.h - Internal header file for _RodSerial_Interface .c files
 * Copyright (C) 2020 Rodrigo Amaral  <rodrigo_amaral01@outlook.com>
 */

#ifndef _RODSERIAL_INTERFACE_INTERNAL_H
#define _RODSERIAL_INTERFACE_INTERNAL_H

extern struct termios serial_io;
extern struct termios stdio;
extern struct termios old_stdio;
extern int tty_FILENO;

extern unsigned char c;

extern char* PortString;
extern char* FileString;
extern int RETURN_ERROR;

extern uint8_t _RodSerial_Arguments_CheckString(char* string1, char* string2); /* Checks if both input strings are the same */

#endif /* _RODSERIAL_INTERFACE_INTERNAL_H */
