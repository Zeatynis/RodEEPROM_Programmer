/* GPL-2.0 License, see LICENCE_GPL-2.0.txt */
/* https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html */
/*
 * _RodTools_Arguments.h - header for functions to Process Command line arguments
 * Copyright (C) 2020 Rodrigo Amaral  <rodrigo_amaral01@outlook.com>
 */

#ifndef _RODTOOLS_ARGUMENTS_H
#define _RODTOOLS_ARGUMENTS_H

#include <inttypes.h>
#include "../Mini_Assembler/_RodMiniAssembler_Translation.h"

extern uint8_t _RodTools_Arguments_CheckString(char* string1, char* string2); /* Checks if both input strings are the same */
extern uint8_t _RodTools_Arguments_ProcessArguments(int argc, char** argv);   /* Processes argv arguments */
extern uint8_t _RodTools_Arguments_DO_COMPILE();							  /* Returns de BINARY_SOURCE variable that tells the source of the binary file to be uploaded, if any */

#endif /* _RODTOOLS_ARGUMENTS_H */