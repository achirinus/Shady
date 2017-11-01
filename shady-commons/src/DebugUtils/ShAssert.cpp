#include "ShAssert.h"

namespace Shady
{
	void _sh_chill_assert(bool cond, const char* str, ...)
	{
		va_list args;
		va_start(args, str);
		if (!cond)
		{
			_consoleColoredOutput(DebugConsoleColor::PURPLE, "ASSERTION FAILED!!!-----------");
			__consoleColoredOutput(DebugConsoleColor::PURPLE, str, args);
			_consoleColoredOutput(DebugConsoleColor::PURPLE, "------------------------------");
		}

		va_end(args);
	}

	void _HandleAssertBox(const c8* mes)
	{
		s32 result = MessageBoxA(GetActiveWindow(), mes, "Asertion Failure!",
								MB_RETRYCANCEL | MB_ICONERROR | MB_DEFBUTTON2 | MB_SYSTEMMODAL);
		if(result == IDCANCEL) ExitProcess(1);
	}
}