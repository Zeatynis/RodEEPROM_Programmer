/* GPL-2.0 License, see LICENCE_GPL-2.0.txt */
/* https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html */
/*
 * Mini_Assembler.c - Rod's Mini Assembler main
 * Copyright (C) 2020 Rodrigo Amaral  <rodrigo_amaral01@outlook.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

#include "_RodTools_Arguments.h"
#include "_RodMiniAssembler_Translation.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wcomment"

#define _PRINT_PROGRAM_BIN_ /* */

char* source_file_string = NULL;
char* output_file_string = "NO_NAME_GIVEN.bin";

int main(int argc, char** argv)
{
	/* chekcing for Command Line Arguments */
	if(_RodTools_Arguments_ProcessArguments(argc, argv))
		return _RodTools_Arguments_ERROR();

    /* Translating and creating bin file */
    if(_RodMiniAssembler_MakeBinFile(source_file_string, output_file_string))
    	return EXIT_FAILURE;

    /* Print out .bin file onto stdout */
    puts("File Binary:\n");
    _RodMiniAssembler_PrintBinFile_Hex(output_file_string);

    #ifdef _PRINT_PROGRAM_BIN_
        puts("This Program Binary:\n");
        _RodMiniAssembler_PrintBinFile_Hex("Build/Mini_Assembler.bin");
    #endif
    

	return EXIT_SUCCESS;
}

#pragma clang diagnostic pop

/* _RodMiniAssembler_PrintBinFile_Bin(output_file_string); */