/* GPL-2.0 License, see LICENCE_GPL-2.0.txt */
/* https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html */
/*
 * _RodTools_Arguments.h - header for functions to Process Command line arguments
 * Copyright (C) 2020 Rodrigo Amaral  <rodrigo_amaral01@outlook.com>
 */

#ifndef _RODTOOLS_ARGUMENTS_H
#define _RODTOOLS_ARGUMENTS_H

#include <inttypes.h>
#include <stdio.h>

#if (FILENAME_MAX < 4096)
	#define FILENAME_PATH_MAXCHARS FILENAME_MAX
#else
	#define FILENAME_PATH_MAXCHARS 4096
#endif

#ifdef NAME_MAX

	#if (NAME_MAX < 255)
		#define FILENAME_MAXCHARS NAME_MAX
	#else
		#define FILENAME_MAXCHARS 255
	#endif

#else
	#define FILENAME_MAXCHARS FILENAME_PATH_MAXCHARS
#endif

extern uint8_t _RodTools_Arguments_CheckString(char* string1, char* string2); 			 	 /* Checks if both input strings are the same */
extern uint8_t _RodTools_Arguments_MaxStringSize(char* string, size_t max_length); 			 /* Checks if the string is under the max length, returns 0 if so, 1 otherwise*/ /* Doens not count '\0' */
extern uint8_t _RodTools_Arguments_wPath_MaxFileStringSize(char* string, size_t max_length); /* Checks if the File name, on a Path name stored on a string is under max_length, returns 0 i so, 1 otherwise*/
extern uint8_t _RodTools_Arguments_ProcessArguments(int argc, char** argv);   				 /* Processes argv arguments */
extern int 	   _RodTools_Arguments_ERROR();								    				 /* Returns value of RETURN_ERROR, used to indicate errors */

#endif /* _RODTOOLS_ARGUMENTS_H */