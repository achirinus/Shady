#ifndef SH_CONSOLE_OUT_H
#define SH_CONSOLE_OUT_H

namespace Shady
{

	enum class DebugConsoleColor
	{
		BLUE,
		GREEN,
		RED,
		CYAN,
		YELLOW,
		PURPLE
	};
	
	void _consoleColoredOutput(DebugConsoleColor color, const char* str, ...);
	void __consoleColoredOutput(DebugConsoleColor color, const char* str, va_list args);
	#ifdef WIN32
		#if defined (SHADY_DEBUG) || (SHADY_DEBUG_RELEASE)
			#define DEBUG_OUT_INFO(str, ...) _consoleColoredOutput(DebugConsoleColor::CYAN,str , __VA_ARGS__)
			#define DEBUG_OUT_OK(str, ...)  _consoleColoredOutput(DebugConsoleColor::GREEN,str , __VA_ARGS__)
			#define DEBUG_OUT_IMP(str, ...) _consoleColoredOutput(DebugConsoleColor::YELLOW,str , __VA_ARGS__)
			#define DEBUG_OUT_ERR(str, ...) _consoleColoredOutput(DebugConsoleColor::RED,str , __VA_ARGS__)

		#else
			#define DEBUG_OUT_INFO(str, ...)
			#define DEBUG_OUT_OK(str, ...)  
			#define DEBUG_OUT_IMP(str, ...) 
			#define DEBUG_OUT_ERR(str, ...) 
		#endif
	#else
	//TODO implement DEBUG console output for other platforms
		#define DEBUG_OUT_INFO(str, ...)
		#define DEBUG_OUT_OK(str, ...)  
		#define DEBUG_OUT_IMP(str, ...) 
		#define DEBUG_OUT_ERR(str, ...) 
	#endif
}

#endif