#include "Commons.h"
#include <stdarg.h>
#include <Windows.h>

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

	void _consoleColoredOutput(DebugConsoleColor color, const char* str, ...)
	{
		va_list args;
		va_start(args, str);
		__consoleColoredOutput(color, str, args);
		va_end(args);
	}

	void __consoleColoredOutput(DebugConsoleColor color,const char* str, va_list args)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
		GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
		WORD currentColor = consoleInfo.wAttributes;
		switch (color)
		{
		case DebugConsoleColor::BLUE:
			SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			break;
		case DebugConsoleColor::RED:
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
			break;
		case DebugConsoleColor::GREEN:
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			break;
		case DebugConsoleColor::CYAN:
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN |
				FOREGROUND_INTENSITY |
				FOREGROUND_BLUE);
			break;
		case DebugConsoleColor::YELLOW:
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN |
				FOREGROUND_INTENSITY |
				FOREGROUND_RED);
			break;
		case DebugConsoleColor::PURPLE:
			SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE |
				FOREGROUND_INTENSITY |
				FOREGROUND_RED);
			break;
		}
		vprintf(str, args);
		printf("\n");
		SetConsoleTextAttribute(hConsole, currentColor);
		
	}
}

