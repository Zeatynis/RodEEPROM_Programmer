// GPL-2.0 License, see LICENCE_GPL-2.0.txt
/*
 * _RodSerial_ProcessArguments.c - functions to Process Command line arguments
 * Copyright (C) 2020 Rodrigo Amaral  <rodrigo_amaral01@outlook.com>
 */

#include "_RodSerial_ProcessArguments.h"

int RETURN_ERROR = 0;
char* PortString = NULL;
char* FileString = NULL;

//	Checks if both input strings are the same
uint8_t _RodSerial_CheckString(char* string1, char* string2)
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

uint8_t _RodSerial_ProcessArguments(int argc, char** argv)
{
	/*	Processing arguments	*/
	uint8_t args_count = 1;
	while(argc > args_count)
	{
		//	-p to specify serial port
		if(!_RodSerial_CheckString(argv[args_count], "-p"))
		{
			static uint8_t done_p;

			if(done_p)
			{
				puts("Alredy specified Serial Port! (Repeated -p)\n");
				RETURN_ERROR = 5;
				return 1;
			}
			else
			{
				if(argc > args_count+1)
				{
					PortString = argv[args_count+1];
				}
				else
				{
					puts("\nNo Serial Port Specified! after -p");
					printf("Example: %s -p /dev/ttyUSB0\n\n",argv[0]);
					RETURN_ERROR = 2;
					return 1;
				}
				args_count += 2;
			}

			done_p = 1;
		}
		// -f to specify the file name with binary data to be uploaded to the EEPROM
		else if(!_RodSerial_CheckString(argv[args_count], "-f"))
		{
			static uint8_t done_f;

			if(done_f)
			{
				puts("Alredy specified File Name! (Repeated -f)\n");
				RETURN_ERROR = 5;
				return 1;
			}
			else
			{
				if(argc > args_count+1)
				{
					FileString = argv[args_count+1];
				}
				else
				{
					puts("\nNo File Name Specified!\n");
					RETURN_ERROR = 3;
					return 1;
				}
				args_count += 2;
			}

			done_f = 1;
		}
		else if(!_RodSerial_CheckString(argv[args_count], "--train"))
		{
			static uint8_t done_train;


			if(done_train)
			{
				puts("You alredy asked for a train! (Repeated --train)\n");
				RETURN_ERROR = 5;
				return 1;
			}
			else
			{
				puts("\n                 _-====-__-======-__-========-_____-============-__\n               _(                                                 _)\n            OO(           _/_ _  _  _/_   _/_ _  _  _/_           )_\n           0  (_          (__(_)(_) (__   (__(_)(_) (__            _)\n         o0     (_                                                _)\n        o         \'=-___-===-_____-========-___________-===-dwb-=\'\n      .o                                _________\n     . ______          ______________  |         |      _____\n   _()_||__|| ________ |            |  |_________|   __||___||__\n  (BNSF 1995| |      | |            | __Y______00_| |_         _| \n/-OO----OO\"\"=\"OO--OO\"=\"OO--------OO\"=\"OO-------OO\"=\"OO-------OO\"=P\n#####################################################################\n");
				args_count++;
			}

			done_train = 1;
		}
		else
		{
			putchar('\n');
			printf("%s",(argv[args_count]));
			puts(" | is an invalid argument!\n");
			RETURN_ERROR = 4;
			return 1;
		}
	}

	if(PortString == NULL)
	{
		puts("\nNo Serial Port Specified! Please specify the serial port after with -p\n");
		printf("Example: %s -p /dev/ttyUSB0\n\n",argv[0]);
		RETURN_ERROR = 2;
		return 1;
	}

	return 0;
}