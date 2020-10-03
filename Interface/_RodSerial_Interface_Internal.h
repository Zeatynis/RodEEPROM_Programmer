/* GPL-2.0 License, see LICENCE_GPL-2.0.txt */
/* https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html */
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

extern char* PortString;

extern char* source_file_string;
extern char* output_file_string;

extern char* binary_file_string;

#endif /* _RODSERIAL_INTERFACE_INTERNAL_H */