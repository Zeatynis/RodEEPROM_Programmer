#include "_SteveUART_debug.h"

int _SteveUART_uputchar0(char c, FILE *stream)
{
	if (c == '\n') _SteveUART_uputchar0('\r', stream);
	while (!(UCSR0A & _BV(UDRE0)));
	UDR0 = c;
	return c;
}

int _SteveUART_ugetchar0(FILE *stream)
{
	while(!(UCSR0A & _BV(RXC0)));
	return UDR0;
}

void _SteveUART_init_debug_uart0(void)
{
	/* Configure UART0 baud rate, one start bit, 8-bit, no parity and one stop bit */
	UBRR0H = (F_CPU/(DEBUG_BAUD*16L)-1) >> 8;
	UBRR0L = (F_CPU/(DEBUG_BAUD*16L)-1);
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);
	UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);

	/* Setup new streams for input and output */
	static FILE uout = FDEV_SETUP_STREAM(_SteveUART_uputchar0, NULL, _FDEV_SETUP_WRITE);
	static FILE uin = FDEV_SETUP_STREAM(NULL, _SteveUART_ugetchar0, _FDEV_SETUP_READ);

	/* Redirect all standard streams to UART0 */
	stdout = &uout;
	stderr = &uout;
	stdin = &uin;
}