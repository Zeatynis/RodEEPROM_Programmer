/* GPL-2.0 License, see LICENCE_GPL-2.0.txt */
/* https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html */
/*
 * _RodEEPROM_SerialComms.c - functions for Command Line Interface
 * Copyright (C) 2020 Rodrigo Amaral  <rodrigo_amaral01@outlook.com>
 */

#include "_RodEEPROM_SerialComms.h"

#if (FILENAME_MAX < 4096)
	#define FILENAME_PATH_MAXCHARS FILENAME_MAX
#else
	#define FILENAME_PATH_MAXCHARS 4096
#endif

#if (NAME_MAX < 255)
	#define FILENAME_MAXCHARS NAME_MAX
#else
	#define FILENAME_MAXCHARS 255
#endif

void _RodEEPROM_EstablishSerialConnection()
{
	unsigned char c = 'd';
	PORTD |= (1<<PD7);

	while(1)
	{
		c = getchar();

		PORTD ^= (1<<PD7);
		_delay_ms(500);

		if(c == 5)  /* ENQ Enquiry */
			break;
	}

	putchar(6); /* ACK Aknowledge */
	PORTD &= ~(1<<PD7);
}

void _RodEEPROM_ClearScreen()
{
	putchar(3);
}

uint8_t _RodEEPROM_CheckString(char* string1, char* string2)
{
	size_t j = 0;
	while(1)
	{
		if( string1[j] != string2[j] )
			break;
		else if ( (!string1[j]) && (!string2[j]) )
			return 0;

		j++;
	}
	return 1;
}

uint8_t _RodEEPROM_CommandExecute(char* commandToExecute)
{
	#ifdef DEBUG
		puts("\nexecuting: "); puts(commandToExecute); putchar('\n');
		getchar();
	#endif

	_RodEEPROM_ClearScreen();

	if(!_RodEEPROM_CheckString(commandToExecute, "clear"))
	{
		_RodEEPROM_ClearEEPROM();
		puts("\n\nCleared EEPROM!\n");
		uint64_t temp = _RodEEPROM_ClearCheck();

		if(temp != 0xffffffffffffffff)
		{
			printf("\n\nError! at address: 0x%4.4x\n", temp);
			printf("Byte: 0x%2.2x\n", _RodEEPROM_ReadByte(temp));
		}
		else
			puts("\n\nClear was successful!\n");

		getchar();
	}
	else if(!_RodEEPROM_CheckString(commandToExecute, "exit"))
	{
		putchar(4);
		return 1;
	}
	else if(!_RodEEPROM_CheckString(commandToExecute, "train!"))
	{
		puts("\n                 _-====-__-======-__-========-_____-============-__\n               _(                                                 _)\n            OO(           _/_ _  _  _/_   _/_ _  _  _/_           )_\n           0  (_          (__(_)(_) (__   (__(_)(_) (__            _)\n         o0     (_                                                _)\n        o         \'=-___-===-_____-========-___________-===-dwb-=\'\n      .o                                _________\n     . ______          ______________  |         |      _____\n   _()_||__|| ________ |            |  |_________|   __||___||__\n  (BNSF 1995| |      | |            | __Y______00_| |_         _| \n/-OO----OO\"\"=\"OO--OO\"=\"OO--------OO\"=\"OO-------OO\"=\"OO-------OO\"=P\n#####################################################################\n");
		getchar();
	}
	else if(!_RodEEPROM_CheckString(commandToExecute, "write"))
	{
		_RodEEPROM_GetBinFile();
		getchar();
	}
	else if(!_RodEEPROM_CheckString(commandToExecute, "read"))
	{
		_RodEEPROM_ReadEEPROM();
		puts("\n\nEEPROM has been read!\n");
		getchar();
	}
	else
	{
		puts("Invalid Command!!!\n\n");
		getchar();
	}

	_RodEEPROM_ClearScreen();
}

uint8_t _RodEEPROM_ProcessInput(char c)
{
	static unsigned char command[COMMAND_SIZE+1];
	static uint8_t char_count;
	static uint8_t max_chars;

	#ifdef DEBUG
		printf("Micro Received -> |%i|\n",c);
		printf("Prev char_count-> |%i|\n",char_count);
		printf("Prev max_chars -> |%i|\n\n",char_count);
	#endif

	if(c < 32)
	{
		if(c == '\r')
		{
			char_count = 0;
			max_chars = 0;

			_RodEEPROM_CommandExecute(command);

			for(size_t j = 0; j < COMMAND_SIZE; j++)
				command[j] = '\0';
			printf(StartString);
		}
		else if(c == 8) /* BS */ /* Symbolizes Backspace key */
		{
			if(char_count)
			{
				if(char_count == max_chars)
				{
					char_count--;
					max_chars--;
					command[char_count] = '\0';
				}
				else
				{
					char_count--;
					command[char_count] = ' ';
				}
			}
			else
				c = '\a';

			SEND(c);
		}
		else if(c == 14) /* Right Arrow Ley */
		{
			if(char_count < max_chars)
				char_count++;
			else
				c = '\a';

			SEND(c);
		}
		else if(c == 15)
		{
			if(char_count)
				char_count--;
			else
				c = '\a';

			SEND(c);
		}
		else if(c == 4) /* EOT */
		{
			return 1;
		}
		else if(c == 25) /* EM */
		{
			for(size_t j = 0; j < COMMAND_SIZE; j++)
				command[j] = '\0';
			char_count = 0;
			max_chars = 0;
			return 2;
		}
	}
	else if(c == 127) /* DEL */
	{
		if(max_chars)
		{
			if(char_count == max_chars)
				c = '\a';
			else if(char_count == max_chars -1)
			{
				max_chars--;
				command[char_count] = '\0';
			}
			else
				command[char_count] = ' ';
		}
		else
			c = '\a';

		SEND(c);
	}
	#ifdef DEBUG
		else if(c == '`')
		{
			puts(command);
		}
	#endif
	else if(c < 127) /* All other valid characters */
	{
		if(char_count < COMMAND_SIZE)
		{
			command[char_count] = c;
			++char_count;
		}
		else
			c = '\a';

		SEND(c);
	}
	else
	{
		c = '\a';
		SEND(c);
	} 

	if(char_count > max_chars)
		max_chars = char_count;

	#ifdef DEBUG
		printf("Aftr char_count-> |%i|\n",char_count);
		printf("Aftr max_chars -> |%i|\n",char_count);
		putchar('\n');
	#endif

	return 0;

	/* printf("char_count: |%i|",char_count); */
}