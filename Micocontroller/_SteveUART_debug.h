/*  Author: Steve Gunn
 *          https://www.ecs.soton.ac.uk/people/srg
 * Licence: This work is licensed under the Creative Commons Attribution License.
 *          View this license at http://creativecommons.org/about/licenses/
 *   Notes: F_CPU must be defined to match the clock frequency
 *   Usage: Include in your main file and call init_debug_uart0() from the beginning of main
 *          to initialise redirection of stdout, stderr and stdin to UART0.
 */

/* Some changes done to original source code (debug.h)
   See original in Originals folder*/

#ifndef _STEVEUART_DEBUG_H
#define _STEVEUART_DEBUG_H

#define __ASSERT_USE_STDERR
#include <assert.h>
#include <stdio.h>
#include <avr/io.h>

#define DEBUG_BAUD 57600ULL /* */

extern int _SteveUART_uputchar0(char c, FILE *stream);

extern int _SteveUART_ugetchar0(FILE *stream);

extern void _SteveUART_init_debug_uart0(void);

#endif /* _STEVEUART_DEBUG_H */