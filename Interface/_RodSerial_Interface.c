/* GPL-2.0 License, see LICENCE_GPL-2.0.txt */
/*
 * _RodSerial_Interface.c - functions for the Serial Interface
 * Copyright (C) 2020 Rodrigo Amaral  <rodrigo_amaral01@outlook.com>
 */

#include "_RodSerial_Interface.h"
#include "_RodSerial_Interface_Internal.h"

struct termios serial_io;
struct termios stdio;
struct termios old_stdio;
int tty_FILENO = 0;

unsigned char c = 'd';

uint8_t cursor_location = 0;
uint8_t max_cursor = 0;

char* PortString = NULL;
char* FileString = NULL;
int RETURN_ERROR = 0;

void _RodSerial_Interface_Setup()
{
	memset(&stdio, 0 ,sizeof(stdio));
	memset(&serial_io,0,sizeof(serial_io));

	/* open ports with the flags specified */
	/* O_RDWR for read/write */
	tty_FILENO = open(PortString, O_RDWR | O_NONBLOCK);

	/* gets the parameters associated with the stdout object */
	/* and stores them in the referenced termios structure */
	tcgetattr(STDOUT_FILENO, &old_stdio);

	stdio.c_iflag = 0; /* ICRNL; */ /* Translate carriage return to newline on input */
	stdio.c_oflag = 0;
	stdio.c_cflag = 0;
	stdio.c_lflag = 0; /* Not using Canonical mode */
	stdio.c_cc[VMIN] = 1;
	stdio.c_cc[VTIME]= 0;

	/* sets the parameters associated with the terminal from the termios structure referred */
	/* TCSANOW applies those chnages NOW, immeaditely */
	tcsetattr(STDOUT_FILENO,TCSANOW,&stdio);

	/* Does the same above, but after all output written to stdio has been transmitted */
	/* all input that has been received but not read will be discarded before the change is made */
	tcsetattr(STDOUT_FILENO,TCSAFLUSH,&stdio);

	/* Make the reads non-blocking */
	fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);

	serial_io.c_iflag = 0;
	serial_io.c_oflag = 0;
	serial_io.c_cflag = CS8 | CREAD | CLOCAL; /* 8n1 */
	serial_io.c_lflag = 0; /* Not using Canonical mode */
	serial_io.c_cc[VMIN] = 1;	
	serial_io.c_cc[VTIME]= 5;

	/* sets the output baud rate stored in the termios structure pointed to */
	cfsetospeed(&serial_io,B57600);
	cfsetispeed(&serial_io,B57600);

	tcsetattr(tty_FILENO,TCSANOW,&serial_io);
}

void _RodSerial_Interface_Close()
{
	/* Close file used for serial comms */
	close(tty_FILENO);

	/* set stdio to old stdio parameters */
	tcsetattr(STDOUT_FILENO,TCSANOW,&old_stdio);
}

void _RodSerial_Interface_ClearIOBuffer(int FILENO)
{
	while(read(FILENO,&c,1)>0) {}
}

void _RodSerial_Interface_ConsoleClearScreen()
{
	/* Clear screen */
	c = 27; write(STDOUT_FILENO,&c,1);
	c = 91; write(STDOUT_FILENO,&c,1);
	c = 50; write(STDOUT_FILENO,&c,1);
	c = 74; write(STDOUT_FILENO,&c,1);

	/* Cursor home */ 
	c = 27; write(STDOUT_FILENO,&c,1);
	c = 91; write(STDOUT_FILENO,&c,1);
	c = 72; write(STDOUT_FILENO,&c,1);
}

uint8_t _RodSerial_Interface_EstablishComms()
{
	c = 'd';
	uint8_t attempts = 0;

	while(attempts < 20)
	{
		read(STDIN_FILENO,&c,1); if(c == 3) break;

		c = 5; write(tty_FILENO,&c,1); /* ENQ Enquiry */

		for(uint32_t i = 0; i < 320000; i++)
		{
			if(read(tty_FILENO,&c,1)>0)
				break;
		}
		if(c == 6)
			break;

		attempts++;
		puts("Trying Again.\r");
	}

	if(c == 6)
	{
		puts("Connection Established!\r");
		puts("-----------------------\r\n");
		return 0;
	}
	else
		puts("Connection Failed!\r");

	return 1;
}

/* SERIAL PORT TO CONSOLE */
uint8_t _RodSerial_Interface_SerialInput()
{
	if(read(tty_FILENO,&c,1)>0)
	{
		if(c < 32)
		{
			if(c == 8) /* BS */
			{
				#ifdef DEBUG
					printf("PC Received: -> |%i|\r\n\n",c);
				#else
					c = 8; write(STDOUT_FILENO,&c,1);
					c = ' '; write(STDOUT_FILENO,&c,1);
					c = 8; write(STDOUT_FILENO,&c,1);
				#endif
			}
			else if(c == '\r')
			{
				#ifdef DEBUG
					printf("PC Received: -> |%i|\r\n\n",c);
				#else
					write(STDOUT_FILENO,&c,1);
				#endif
			}
			else if(c == '\n')
			{
				#ifdef DEBUG
					printf("PC Received: -> |%i|\r\n\n",c);
				#else
					write(STDOUT_FILENO,&c,1);
					c = '\r'; write(STDOUT_FILENO,&c,1);
				#endif
			}
			else if(c == '\t')
			{
				#ifdef DEBUG
					printf("PC Received: -> |%i|\r\n\n",c);
				#else
					write(STDOUT_FILENO,&c,1);
				#endif
			}
			else if(c == 27) /* ESC */
			{
				#ifdef DEBUG
					printf("PC Received: -> |%i|\r\n\n",c);
				#else
					_RodSerial_Interface_ClearIOBuffer(tty_FILENO);
				#endif
			}
			else if(c == 14) /* SO Shift-out, symbolizes Right Arrow key */
			{
				#ifdef DEBUG
					printf("PC Received: -> |%i|\r\n\n",c);
				#else
					c = 27; write(STDOUT_FILENO,&c,1);
					c = 91; write(STDOUT_FILENO,&c,1);
					c = 'C'; write(STDOUT_FILENO,&c,1);
				#endif
			}
			else if(c == 15) /* SI Shift-in, symbolizes Left Arrow key */
			{
				#ifdef DEBUG
					printf("PC Received: -> |%i|\r\n\n",c);
				#else
					c = 27; write(STDOUT_FILENO,&c,1);
					c = 91; write(STDOUT_FILENO,&c,1);
					c = 'D'; write(STDOUT_FILENO,&c,1);
				#endif
			}
			else if(c == 3) /* ETX */
			{
				_RodSerial_Interface_ConsoleClearScreen();
			}
			else if(c == 4)
			{
				puts("EEPROM Programmer turned off!\r");
				return 1;
			}
			else
			{
				#ifdef DEBUG
					printf("PC Received: -> |%i|\r\n\n",c);
				#endif

				c = '\a'; write(STDOUT_FILENO,&c,1);
			}
		}
		else
		{
			if(c == 127) /* DEL */
			{
				#ifdef DEBUG
					printf("PC Received: -> |%i|\r\n\n",c);
				#else
					c = ' '; write(STDOUT_FILENO,&c,1);
					c = 8; write(STDOUT_FILENO,&c,1);
				#endif
			}
			else
			{
				#ifdef DEBUG
					printf("PC Received: -> |%i|\r\n\n",c);
				#else
					write(STDOUT_FILENO,&c,1);
				#endif
			}
		}
	}

	return 0;
}

/* CONSOLE TO SERIAL PORT */
uint8_t _RodSerial_Interface_SerialOutput()
{
	if(read(STDIN_FILENO,&c,1)>0)
	{
		if(c < 32)
		{
			if(c == '\r')
			{
				write(tty_FILENO,&c,1);
			}
			else if(c == 27) /* ESC */
			{
				read(STDIN_FILENO,&c,1);
				if(c == 91) /* if '[' */
				{
					read(STDIN_FILENO,&c,1);

					if(c == 'C') /* Right arrow key */
					{
						/* SO Shift-out, symbolizes Right Arrow key */
						c = 14; write(tty_FILENO,&c,1);
					}
					else if(c == 'D') /* Left arrow key */
					{
						/* SI Shift-in, symbolizes Left Arrow key */
						c = 15; write(tty_FILENO,&c,1);
					}
					else if(c == 51) /* '3' */
					{
						read(STDIN_FILENO,&c,1);

						if(c == 126) /* '~' */
						{ 		
							c = 127; write(tty_FILENO,&c,1); /* Delete key == ESC + [ + 3 + ~ */
						}
						else
						{
							_RodSerial_Interface_ClearIOBuffer(STDIN_FILENO);
							c = '\a'; write(STDOUT_FILENO,&c,1);
						}
					}
					else
					{
						_RodSerial_Interface_ClearIOBuffer(STDIN_FILENO);
						c = '\a'; write(STDOUT_FILENO,&c,1);
					}
				}
				else
				{
					_RodSerial_Interface_ClearIOBuffer(STDIN_FILENO);
					c = '\a'; write(STDOUT_FILENO,&c,1);
				}
			}
			else if(c == 3) /* Ctrl + C */
			{
				c = 25; write(tty_FILENO,&c,1); /* EM */

				_RodSerial_Interface_ConsoleClearScreen();

				return 1;
			}
			else
			{
				c = '\a'; write(STDOUT_FILENO,&c,1);
			}
		}
		else if(c == 127) /* DEL */
		{
			c = 8; write(tty_FILENO,&c,1); /* BS */
		}
		else if(c < 127)
		{
			write(tty_FILENO,&c,1);
		}
		else
		{
			c = '\a'; write(STDOUT_FILENO,&c,1);
		}


		#ifdef DEBUG
			printf("PC Sent:     -> |%i|\r\n",c);
		#endif
	}

	return 0;
}

uint8_t _RodSerial_Interface_Debug()
{
	if(read(STDIN_FILENO,&c,1)>0)
	{
		printf("PC Sent:     -> |%i|\r\n",c);
		write(tty_FILENO,&c,1);
	}

	if(read(tty_FILENO,&c,1)>0)
	{
		printf("PC Received: -> |%i|\r\n\n",c);
		//write(STDOUT_FILENO,&c,1);
	}

	if(c == 3)
		return 1;

	return 0;	
}