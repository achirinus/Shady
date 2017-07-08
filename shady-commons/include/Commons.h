#ifndef SH_COMMONS_H
#define SH_COMMONS_H


#include <cstdlib>
#include <intrin.h>
#include <cstdio>
namespace Shady
{

#ifdef WIN32
	#ifdef  _MSC_VER
		typedef char c8;
		typedef unsigned char uc8;
		typedef unsigned char u8;
		typedef wchar_t c16;
		typedef int c32;
		typedef bool b8;
		typedef short s16;
		typedef unsigned short u16;
		typedef int b32;
		typedef int s32;
		typedef unsigned int u32;
		typedef long long s64;
		typedef unsigned long long u64;
		typedef float f32;
		typedef double f64;
		typedef int int32;
		typedef long long int64;
		typedef char int8;
		typedef short int16;
		typedef unsigned int uint32;
		typedef unsigned long long uint64;
		typedef unsigned char uint8;
		typedef unsigned short uint16;

		typedef float float32;
		typedef double float64;

		#define C8_MIN (-128)
		#define C8_MAX (127)
		#define C16_MIN (-32768)
		#define C16_MAX	(32767)
		#define C32_MIN (-2147483648)
		#define C32_MAX (2147483647)
		#define U8_MAX (255)
		#define U16_MAX (65535)
		#define U32_MAX (4294967295)
		#define U64_MAX (18446744073709551615)
		#define S8_MIN (-128)
		#define S8_MAX (127)
		#define S16_MIN (-32768)
		#define S16_MAX (32767)
		#define S32_MIN (-2147483648)
		#define S32_MAX (2147483647)
		#define S64_MIN (-9223372036854775808)
		#define S64_MAX (9223372036854775807)
	#endif



#endif
//TODO better log


enum class DebugConsoleColor
{
	BLUE,
	GREEN,
	RED,
	CYAN,
	YELLOW,
	PURPLE
};

//TODO upgrade this sometime to show file, line etc
void _sh_crazy_assert(bool cond);
void _sh_chill_assert(bool cond, const char* str, ...);

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



//Make this work with mutiple levels of functions
struct PerfCounter
{
	uint64 startPerf;
	const char* funcName;
	PerfCounter(const char* funcName)
	{
		startPerf = __rdtsc();
		this->funcName = funcName;
	}
	~PerfCounter()
	{
		uint64 endPerf = __rdtsc();
		printf("Cycles spent on func %s: %llu\n", funcName, endPerf-startPerf);
	}
};


#if defined (SHADY_DEBUG) || (SHADY_DEBUG_RELEASE)
	#if defined (_MSC_VER)
		#define DEBUG_BREAK __debugbreak()
	#else
		//TODO break for other platforms/compilers
		#define DEBUG_BREAK
	#endif
	#define PROFILE_FUNC() PerfCounter profile##__func__(__func__)

			//Chill assert just outputs to the console an error message
	#define SH_CHILL_ASSERT(exp, str, ...) _sh_chill_assert(exp, str, __VA_ARGS__)
			
	#define SH_ASSERT(exp, ...) if (!(exp))	DEBUG_BREAK
	#define STARTPERFCOUNT u32 startPerf = __rdtsc()
	#define ENDPERFCOUNT(str) u32 endPerf = __rdtsc(); \
					u32 cyclesElapsed = endPerf - startPerf; \
					DEBUG_OUT_INFO("Cycles elapsed on %s: %d", #str, cyclesElapsed)
	#define INVALID_CODE_PATH SH_ASSERT(false)
#else
	#define DEBUG_BREAK
	#define SH_ASSERT(exp, ...)
	#define PROFILE_FUNC() 
	#define STARTPERFCOUNT
	#define ENDPERFCOUNT(str, ...)
	#define INVALID_CODE_PATH
#endif

	

#ifdef SHADY_DECLSPEC	
	#define SH_INTERFACE __declspec(novtable)
#else
	#define SH_INTERFACE 

#endif

}
#endif

