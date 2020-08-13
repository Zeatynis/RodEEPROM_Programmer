#include "_RodEEPROM_Terminal.h"

void _RodEEPROM_ClearScreen()
{
	putchar(27);    // ESC command
  	puts("[2J");    // clear screen command
  	putchar(27);
  	puts("[H");     // cursor to home command
}

//	Checks if both input strings are the same
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

void _RodEEPROM_CommandExecute(char* commandToExecute)
{
	if(!DEBUG)
	{
		puts("\nexecuting: "); puts(commandToExecute); putchar('\n');
		getchar();
	}

	_RodEEPROM_ClearScreen();

	if(!_RodEEPROM_CheckString(commandToExecute, "clear"))
	{
		_RodEEPROM_ClearEEPROM();
		uint64_t temp = _RodEEPROM_ClearCheck();

		if(temp != 0xffffffffffffffff)
		{
			printf("\nError! at address: 0x%4.4x\n", temp);
			printf("Byte: 0x%2.2x\n\n", _RodEEPROM_ReadByte(temp));
		}
		else
			puts("\nWorked!\n");

		getchar();
	}
	else if(!_RodEEPROM_CheckString(commandToExecute, "train!"))
	{
		puts("\n                 _-====-__-======-__-========-_____-============-__\n               _(                                                 _)\n            OO(           _/_ _  _  _/_   _/_ _  _  _/_           )_\n           0  (_          (__(_)(_) (__   (__(_)(_) (__            _)\n         o0     (_                                                _)\n        o         \'=-___-===-_____-========-___________-===-dwb-=\'\n      .o                                _________\n     . ______          ______________  |         |      _____\n   _()_||__|| ________ |            |  |_________|   __||___||__\n  (BNSF 1995| |      | |            | __Y______00_| |_         _| \n/-OO----OO\"\"=\"OO--OO\"=\"OO--------OO\"=\"OO-------OO\"=\"OO-------OO\"=P\n#####################################################################\n");
	}
	else if(!_RodEEPROM_CheckString(commandToExecute, "debug!"))
	{
		if(DEBUG)
			StartString = StartDebugString;
		else
			StartString = StartNormalString;

		DEBUG = !DEBUG;
	}
	else if(!_RodEEPROM_CheckString(commandToExecute, "write"))
	{
		
	}
	else if(!_RodEEPROM_CheckString(commandToExecute, "read"))
	{
		_RodEEPROM_ReadEEPROM();
		getchar();
	}
	else
	{
		puts("Invalid Command!!!\n\n");
	}

	_RodEEPROM_ClearScreen();
}

void _RodEEPROM_ProcessInput(char c)
{
	static unsigned char command[COMMAND_SIZE+1];
	static uint8_t i;

	if(c == 13) // Carriage Return
	{
		putchar('\n');
		i = 0;
		_RodEEPROM_CommandExecute(command);
		for(size_t j = 0; j < COMMAND_SIZE; j++)
			command[j] = '\0';
		printf(StartString);
	}
	else if(c == 127) // DEL
	{
		if(!DEBUG)
			printf(" %i ", c);

		if(i)
		{
			--i;
			if(DEBUG)
				putchar(127);
		}
		command[i] = '\0';
	}
	else if(c == 27) // ESC
	{
		if(!DEBUG)
			printf(" %i ", c);

		c = getchar();

		if(!DEBUG)
			printf(" %i ", c);

		if(c == 91) // '[' character, used for special commands
		{
			c = getchar();

			if(!DEBUG)
				printf(" %i ", c);

			if(c == 67 && i < 9) 		//Right key
			{
				i++;
				putchar(27);
				putchar(91);
				putchar(c);
			}
			else if(c == 68 && i > 0) 	//Left key
			{
				i--;
				putchar(27);
				putchar(91);
				putchar(c);
			}
		}
		else if(c == '`' && !DEBUG) // Used to get out of DEBUG
		{
			DEBUG = 1;
			_RodEEPROM_ClearScreen();
			StartString = StartNormalString;
			printf(StartString);
		}
	}
	else if(c == '`' && !DEBUG) // show contents of command string
	{
		putchar('\n');
		puts(command);
		for(size_t j = 0; j < COMMAND_SIZE + 1; j++)
			printf("%i ", command[j]);
		putchar('\n');
	}
	else if(c == 9) // TAB
	{
		// Nothing UwU
	}
	else if(c < 127) // All other valid characters
	{
		if(!DEBUG)
			printf(" %i ", c);

		if(i < COMMAND_SIZE)
		{
			putchar(c);
			command[i] = c;
			++i;
		}
	}
}