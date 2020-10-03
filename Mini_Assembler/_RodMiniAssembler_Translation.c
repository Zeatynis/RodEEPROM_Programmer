/* GPL-2.0 License, see LICENCE_GPL-2.0.txt */
/* https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html */
/*
 * _RodMiniAssembler_Translation.c - Rod's Mini Assembler functions
 * Copyright (C) 2020 Rodrigo Amaral  <rodrigo_amaral01@outlook.com>
 */

#include "_RodMiniAssembler_Translation.h"

#ifndef N_BYTES_BIN
	#define N_BYTES_BIN 8  /* The number of binary bytes printed by PrintBinFile_Bin() */
#endif

#ifndef N_BYTES_HEX
	#define N_BYTES_HEX 32 /* The number of hex bytes printed by PrintBinFile_Hex() */
#endif

extern uint8_t RETURN_ERROR;

void _RodMiniAssembler_NibbleBinaryPrint(uint8_t num)
{
	static uint8_t shift;

	shift = 0;
	while(shift < 4)
	{
		if((num << shift) & 0b1000)
			putchar('1');
		else
			putchar('0');

		shift++;
	}
}

void _RodMiniAssembler_NibbleHexPrint(uint8_t num)
{
	if( (num&0b1111) < 0xA )
		putchar((num&0b1111) + 48);
	else
		putchar((num&0b1111) + 55);
}

void _RodMiniAssembler_ByteBinaryPrint(uint8_t num)
{
	static uint8_t shift;

	shift = 0;
	while(shift < 8)
	{
		if((num << shift) & 0b10000000)
			putchar('1');
		else
			putchar('0');

		shift++;
	}
}

void _RodMiniAssembler_ByteHexPrint(uint8_t num)
{
	_RodMiniAssembler_NibbleHexPrint(num>>4);
	_RodMiniAssembler_NibbleHexPrint(num);
}

uint8_t _RodMiniAssembler_HexToBin(char c)
{
	/* makes lower case into upper case */
	if(c >= 'a' && c <= 'f')
		c -= 32;

	/* Translates the hex into binary*/
	if(c >= '0' && c <= '9')
		c -= 48;
	else /* (c >= 'A' && c <= 'F') */
		c -= 55;

	return c;
}

uint8_t _RodMiniAssembler_HexToByte(char c1, char c2) /* Returns a byte from two hex chars. c1, MS Nibble. c2, LS Nibble.*/
{
	return ( (_RodMiniAssembler_HexToBin(c1) << 4) | _RodMiniAssembler_HexToBin(c2) );
}

uint8_t _RodMiniAssembler_InvalidCharsCheck(char* file_name)
{
	size_t line_number = 1;
	char c = '`';
	uint8_t return_value = 0;

	FILE* file = fopen(file_name, "r");

	while( (c = fgetc(file)) != EOF )
	{
		START:

		/* Count newlines */
		if(c == '\n')
		{
			line_number++;
			c = fgetc(file);
			goto START;
		}

		if(c == EOF)
			break;

		/* Checks for Invalid Chars */
		if( !( (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f') || c == ' ' || c == '\t' ) )
		{
			printf("Invalid character: |%c| at line: %zu\n", c, line_number);
			return_value = 1;
		}
	}
	fclose(file);
	return return_value;
}

void _RodMiniAssembler_PrintBinFile_Bin(char* file_name)
{
	uint64_t file_size = 0;
	uint64_t char_count = 0;
	char c = 0b00001111;
	char chars_buffer[N_BYTES_BIN];
	FILE* file = fopen(file_name, "r");

	for(size_t i = 0; i < N_BYTES_BIN; i++)
		chars_buffer[i] = 0;

	/* can read for EOF, to determine EOF, so we get the file size */
	fseek(file, 0, SEEK_END);
	file_size = ftell(file);
	rewind(file);

	/* now read file */
	while(char_count < file_size)
	{
		/* get a character of the file, store it on a buffer */
		c = fgetc(file);
		chars_buffer[char_count % N_BYTES_BIN] = c;
		char_count++;

		if( (!(char_count % N_BYTES_BIN) && char_count) )
		{
			/* Print Address */
			printf("\n%8.8lx:  ", char_count-N_BYTES_BIN);

			/* Print the buffer contents in binary form */
			for(uint8_t i = 0; i<N_BYTES_BIN ; i++)
			{
				_RodMiniAssembler_ByteBinaryPrint(chars_buffer[i]);
				if(i == (N_BYTES_BIN/2 - 1))
				{
					putchar(' '); putchar(' '); putchar(' '); putchar(' '); putchar(' ');
				}
				else
					putchar(' ');
			}

			/* Print the buffer contents in char form */
			putchar('|');
			for(uint8_t i = 0; i<N_BYTES_BIN ; i++)
			{
				if(chars_buffer[i] > 31 && chars_buffer[i] < 127)
					putchar(chars_buffer[i]);
				else
					putchar('.');

				if(i == (N_BYTES_BIN/2 - 1))
					putchar(' ');
			}
			putchar('|');
		}
	}

	if(char_count%N_BYTES_BIN)
	{
		printf("\n%8.8lx:  ", char_count - (char_count%N_BYTES_BIN));
		for(uint8_t i = 0; i<N_BYTES_BIN ; i++)
		{
			if(i < (char_count%N_BYTES_BIN))
				_RodMiniAssembler_ByteBinaryPrint(chars_buffer[i]);
			else
			{
				for(uint8_t j = 0; j < 8; j++)
					putchar(' ');
			}

			if(i == (N_BYTES_BIN/2 - 1))
			{
				putchar(' '); putchar(' '); putchar(' '); putchar(' '); putchar(' ');
			}
			else
				putchar(' ');
		}

		putchar('|');
		for(uint8_t i = 0; i<N_BYTES_BIN ; i++)
		{
			if(i < (char_count%N_BYTES_BIN))
			{
				if(chars_buffer[i] > 31 && chars_buffer[i] < 127)
					putchar(chars_buffer[i]);
				else
					putchar('.');
			}
			else
				putchar(' ');

			if(i == (N_BYTES_BIN/2 - 1))
				putchar(' ');
		}
		putchar('|');
	}

	putchar('\n');
	putchar('\n');
	fclose(file);
}

void _RodMiniAssembler_PrintBinFile_Hex(char* file_name)
{
	uint64_t file_size = 0;
	uint64_t char_count = 0;
	char c = 0b00001111;
	char chars_buffer[N_BYTES_HEX];
	FILE* file = fopen(file_name, "r");

	for(size_t i = 0; i < N_BYTES_HEX; i++)
		chars_buffer[i] = 0;

	/* can read for EOF, to determine EOF, so we get the file size */
	fseek(file, 0, SEEK_END);
	file_size = ftell(file);
	rewind(file);

	/* now read file */
	while(char_count < file_size)
	{
		/* get a character of the file, store it on a buffer */
		c = fgetc(file);
		chars_buffer[char_count % N_BYTES_HEX] = c;
		char_count++;

		if( (!(char_count % N_BYTES_HEX) && char_count) )
		{
			/* Print Address */
			printf("\n%8.8lx:  ", char_count-N_BYTES_HEX);

			/* Print the buffer contents in binary form */
			for(uint8_t i = 0; i<N_BYTES_HEX ; i++)
			{
				_RodMiniAssembler_ByteHexPrint(chars_buffer[i]);
				if(i == (N_BYTES_HEX/2 - 1))
				{
					putchar(' '); putchar(' '); putchar(' '); putchar(' '); putchar(' ');
				}
				else
					putchar(' ');
			}

			/* Print the buffer contents in char form */
			putchar('|');
			for(uint8_t i = 0; i<N_BYTES_HEX ; i++)
			{
				if(chars_buffer[i] > 31 && chars_buffer[i] < 127)
					putchar(chars_buffer[i]);
				else
					putchar('.');

				if(i == (N_BYTES_HEX/2 - 1))
					putchar(' ');
			}
			putchar('|');
		}
	}

	if(char_count%N_BYTES_HEX)
	{
		printf("\n%8.8lx:  ", char_count - (char_count%N_BYTES_HEX));
		for(uint8_t i = 0; i<N_BYTES_HEX ; i++)
		{
			if(i < (char_count%N_BYTES_HEX))
				_RodMiniAssembler_ByteHexPrint(chars_buffer[i]);
			else
			{
				putchar(' '); putchar(' ');
			}

			if(i == (N_BYTES_HEX/2 - 1))
			{
				putchar(' '); putchar(' '); putchar(' '); putchar(' '); putchar(' ');
			}
			else
				putchar(' ');
		}

		putchar('|');
		for(uint8_t i = 0; i<N_BYTES_HEX ; i++)
		{
			if(i < (char_count%N_BYTES_HEX))
			{
				if(chars_buffer[i] > 31 && chars_buffer[i] < 127)
					putchar(chars_buffer[i]);
				else
					putchar('.');
			}
			else
				putchar(' ');

			if(i == (N_BYTES_HEX/2 - 1))
				putchar(' ');
		}
		putchar('|');
	}

	putchar('\n');
	putchar('\n');
	fclose(file);
}

uint8_t _RodMiniAssembler_MakeBinFile(char* source_file_string, char* output_file_string)
{
	char c = '`';
	char c1 = '`';
	char c2 = '`';

	/* Check for invalid chars in Source File */
	if(_RodMiniAssembler_InvalidCharsCheck(source_file_string))
	{
		puts("\nSource File provided contains Invalid Characters!\n");
		return 1;
	}

	/* Open source file */
	FILE* source_file = fopen(source_file_string, "r");
	if(!source_file) 
	{
        perror("Couldn't open source file!\n");
        RETURN_ERROR = 7;
        return 1;
    }

	/* Create binary file */
	FILE* bin_file = fopen(output_file_string, "w");
	if(!bin_file) 
	{
        perror("Couldn't create bin file!\n");
        RETURN_ERROR = 8;
        return 1;
    }

    /* Translate Source file, and write to binary file */
	while((c = fgetc(source_file)) != EOF)
	{
		/* Ignore Tabs and spaces */
		while(c == ' ' || c == '\t' || c == '\n')
			c = fgetc(source_file);

		if(c == EOF)
			break;

		c1 = c;

		c = fgetc(source_file);
		while(c == ' ' || c == '\t' || c == '\n')
			c = fgetc(source_file);

		if(c == EOF)
			c2 = '0';
		else
			c2 = c;

		fputc(_RodMiniAssembler_HexToByte(c1, c2), bin_file);
	}

	if(ferror(source_file))
	{
		puts("I/O error when reading source file");
		RETURN_ERROR = 9;
		fclose(source_file);
		fclose(bin_file);
		return 1;
	}
	if(ferror(bin_file))
	{
		puts("I/O error when reading bin file");
		RETURN_ERROR = 10;
		fclose(source_file);
		fclose(bin_file);
		return 1;
	}

	fclose(source_file);
	fclose(bin_file);

	return 0;
}