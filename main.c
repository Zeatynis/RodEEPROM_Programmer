#include "_SteveUART_debug.h"
#include "_RodEEPROM_Terminal.h"
#include "_RodEEPROM_Programmer.h"

int main()
{
	//Setups
	_SteveUART_init_debug_uart0();
	_RodEEPROM_ProgrammerSetup();

	_RodEEPROM_ClearScreen();
	printf(StartString);

	while(1)
	{
		_RodEEPROM_ProcessInput(getchar());
	}
}