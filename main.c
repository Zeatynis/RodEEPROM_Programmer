#include "_SteveUART_debug.h"
#include "_RodEEPROM_Terminal.h"
#include "_RodEEPROM_Programmer.h"

const char connectionEstablished_char = 1;

int main()
{
	//Setups
	_SteveUART_init_debug_uart0();
	_RodEEPROM_ProgrammerSetup();

	while(getchar() != connectionEstablished_char)
	{
		PORTD ^= (1<<PD7);
	}
	putchar(connectionEstablished_char);

	_RodEEPROM_ClearScreen();
	printf(StartString);

	while(1)
	{
		_RodEEPROM_ProcessInput(getchar());
	}

	return EXIT_SUCCESS;
}