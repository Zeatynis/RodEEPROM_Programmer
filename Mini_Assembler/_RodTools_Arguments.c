/* GPL-2.0 License, see LICENCE_GPL-2.0.txt */
/* https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html */
/*
 * _RodTools_Arguments.c - functions to Process Command line arguments
 * Copyright (C) 2020 Rodrigo Amaral  <rodrigo_amaral01@outlook.com>
 */

#include "_RodTools_Arguments.h"

extern char* source_file_string;
extern char* output_file_string;

int RETURN_ERROR = 0;
/*
	Errors and their return types:

	1: Invalid argument
	2: Repeated argument
	3: File Path too big
	4: File Name too big
	5: No File name given
*/

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

uint8_t _RodTools_Arguments_MaxStringSize(char* string, size_t max_length)
{
	size_t length = 0;
	while(string[length])
		length++;

	if(length > max_length)
		return 1;

	return 0;
}

uint8_t _RodTools_Arguments_wPath_MaxFileStringSize(char* string, size_t max_length)
{
	size_t length = 0;
	size_t fileName_length = 0;
	while(string[length])
		length++;

	while(string[length] != '/')
	{
		length--;
		fileName_length++;
	}

	if(fileName_length > max_length)
		return 1;

	return 0;
}

uint8_t _RodTools_Arguments_ProcessArguments(int argc, char** argv)
{
	/*	Processing arguments	*/
	static uint8_t args_count = 1;
	while(argc > args_count)
	{
		/*	--train to print a train */
		if(!_RodTools_Arguments_CheckString(argv[args_count], "--train"))
		{
			static uint8_t done_train;

			if(done_train)
			{
				puts("You alredy asked for a train! (Repeated --train)\n");
				RETURN_ERROR = 2;
				return 1;
			}
			else
			{
				puts("\n                 _-====-__-======-__-========-_____-============-__\n               _(                                                 _)\n            OO(           _/_ _  _  _/_   _/_ _  _  _/_           )_\n           0  (_          (__(_)(_) (__   (__(_)(_) (__            _)\n         o0     (_                                                _)\n        o         \'=-___-===-_____-========-___________-===-dwb-=\'\n      .o                                _________\n     . ______          ______________  |         |      _____\n   _()_||__|| ________ |            |  |_________|   __||___||__\n  (BNSF 1995| |      | |            | __Y______00_| |_         _| \n/-OO----OO\"\"=\"OO--OO\"=\"OO--------OO\"=\"OO-------OO\"=\"OO-------OO\"=P\n#####################################################################\n");
				args_count++;
			}

			done_train = 1;
		}
		else if(!_RodTools_Arguments_CheckString(argv[args_count], "-f")) /* -f to define the file name */
		{
			static uint8_t done_f;

			if(done_f)
			{
				puts("Alredy specified Input File! (Repeated -f)\n");
				RETURN_ERROR = 1;
				return 1;
			}
			else
			{
				if(argc > args_count+1)
				{
					if( _RodTools_Arguments_MaxStringSize(argv[args_count+1], FILENAME_PATH_MAXCHARS-1) )
					{
						puts("\nInput File Path too big!\n");
						RETURN_ERROR = 3;
						return 1;
					}
					else
					{
						if( _RodTools_Arguments_wPath_MaxFileStringSize(argv[args_count+1], FILENAME_MAXCHARS) )
						{
							puts("\nInput File Name too big\n");
							RETURN_ERROR = 4;
							return 1;
						}
						else
							source_file_string = argv[args_count+1];
					}
				}
				else
				{
					puts("\nNo Input File Specified!\n");
					RETURN_ERROR = 2;
					return 1;
				}
				args_count += 2;
			}

			done_f = 1;
		}
		else if( !_RodTools_Arguments_CheckString(argv[args_count], "-o") ) /* output file string */
		{
			static uint8_t done_o;

			if(done_o)
			{
				puts("Alredy specified Output File! (Repeated -o)\n");
				RETURN_ERROR = 1;
				return 1;
			}
			else
			{
				if(argc > args_count+1)
				{
					if( _RodTools_Arguments_MaxStringSize(argv[args_count+1], FILENAME_PATH_MAXCHARS-1) )
					{
						puts("\nOutput File Path too big!\n");
						RETURN_ERROR = 3;
						return 1;
					}
					else
					{
						if( _RodTools_Arguments_wPath_MaxFileStringSize(argv[args_count+1], FILENAME_MAXCHARS) )
						{
							puts("\nOutput File Name too big\n");
							RETURN_ERROR = 4;
							return 1;
						}
						else
							output_file_string = argv[args_count+1];
					}
				}
				else
				{
					puts("\nNo Output File Specified!\n");
					RETURN_ERROR = 2;
					return 1;
				}
				args_count += 2;
			}

			done_o = 1;
		}
		else
		{
			putchar('\n');
			printf("%s",(argv[args_count]));
			puts(" | is an invalid argument!\n");
			RETURN_ERROR = 1;
			return 1;
		}
	}

	if(source_file_string == NULL)
	{
		puts("\nAn Input File must be specified!\n");
		RETURN_ERROR = 5;
		return 1;
	}

	/* printf("File name: |%s|\n", file_string); */

	return 0;
}

int _RodTools_Arguments_ERROR()
{
	return RETURN_ERROR;
}