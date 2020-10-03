/* GPL-2.0 License, see LICENCE_GPL-2.0.txt */
/* https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html */
/*
 * _RodTools_Arguments.c - functions to Process Command line arguments
 * Copyright (C) 2020 Rodrigo Amaral  <rodrigo_amaral01@outlook.com>
 */

#include "_RodTools_Arguments.h"
#include "_RodSerial_Interface.h"
#include "_RodSerial_Interface_Internal.h"

/* this variable specifies what is the source of the binary file, if any */
/* 0 for no source, 1 for when a binary file is specified, 2 for when a source file is specified */
uint8_t BINARY_SOURCE = 0; 

extern int RETURN_ERROR;

uint8_t _RodTools_Arguments_CheckString(char* string1, char* string2)
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

uint8_t _RodTools_Arguments_ProcessArguments(int argc, char** argv)
{
	/*	Processing arguments	*/
	uint8_t args_count = 1;
	while(argc > args_count)
	{
		/*	-p to specify serial port */
		if(!_RodTools_Arguments_CheckString(argv[args_count], "-p"))
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
					RETURN_ERROR = 2;
					return 1;
				}
				args_count += 2;
			}

			done_p = 1;
		}
		/* -s to specify the source file name with the hex to be converted to binary */
		else if(!_RodTools_Arguments_CheckString(argv[args_count], "-s"))
		{
			static uint8_t done_s;

			if(BINARY_SOURCE == 1)
			{
				puts("A binary file was specified alredy!\n You can only specifiy a source file (to be translated) or a binary file to upload");
				RETURN_ERROR = 6;
				return 1;
			}

			BINARY_SOURCE = 2;

			if(done_s)
			{
				puts("Alredy specified Source File Name! (Repeated -s)\n");
				RETURN_ERROR = 5;
				return 1;
			}
			else
			{
				if(argc > args_count+1)
				{
					source_file_string = argv[args_count+1];
				}
				else
				{
					puts("\nNo Source File Name Specified!\n");
					RETURN_ERROR = 3;
					return 1;
				}
				args_count += 2;
			}
			done_s = 1;
		}
		/* -b to specify the binary file name to be uploaded to the EEPROM */
		else if(!_RodTools_Arguments_CheckString(argv[args_count], "-b"))
		{
			static uint8_t done_b;

			if(BINARY_SOURCE == 2)
			{
				puts("A source file was specified alredy!\n You can only specifiy a source file (to be translated) or a binary file to upload");
				RETURN_ERROR = 6;
				return 1;
			}

			BINARY_SOURCE = 1;

			if(done_b)
			{
				puts("Alredy specified Binary File Name! (Repeated -s)\n");
				RETURN_ERROR = 5;
				return 1;
			}
			else
			{
				if(argc > args_count+1)
				{
					binary_file_string = argv[args_count+1];
				}
				else
				{
					puts("\nNo Binary File Name Specified!\n");
					RETURN_ERROR = 3;
					return 1;
				}
				args_count += 2;
			}

			done_b = 1;
		}
		/* -o to specify the binary file name to be made and uploaded to the EEPROM */
		else if(!_RodTools_Arguments_CheckString(argv[args_count], "-o"))
		{
			static uint8_t done_o;

			if(done_o)
			{
				puts("Alredy specified Output File Name! (Repeated -o)\n");
				RETURN_ERROR = 5;
				return 1;
			}
			else
			{
				if(argc > args_count+1)
				{
					output_file_string = argv[args_count+1];
				}
				else
				{
					puts("\nNo Output File Name Specified!\n");
					RETURN_ERROR = 3;
					return 1;
				}
				args_count += 2;
			}

			done_o = 1;
		}
		else if(!_RodTools_Arguments_CheckString(argv[args_count], "--train"))
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

	if(_RodTools_Arguments_DO_COMPILE() == 2)
	{
		puts("hello...\r");
		if(_RodMiniAssembler_MakeBinFile(source_file_string, output_file_string))
			return RETURN_ERROR;
		binary_file_string = output_file_string;
	}

	puts("hello...\r");

	return 0;
}

uint8_t _RodTools_Arguments_DO_COMPILE()
{
	return BINARY_SOURCE;
}