#ifndef SH_COMMONS_H
#define SH_COMMONS_H


#include <cstdlib>
#include <intrin.h>
#include <cstdio>
#include "ShTypes.h"
#include "ConsoleOut.h"
#include "ShAssert.h"
#include "ComFuncs.h"
namespace Shady
{


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
	
	#define PROFILE_FUNC() PerfCounter profile##__func__(__func__)
	#define STARTPERFCOUNT u32 startPerf = __rdtsc()
	#define ENDPERFCOUNT(str) u32 endPerf = __rdtsc(); \
					u32 cyclesElapsed = endPerf - startPerf; \
					DEBUG_OUT_INFO("Cycles elapsed on %s: %d", #str, cyclesElapsed)
	
#else
	#define STARTPERFCOUNT
	#define ENDPERFCOUNT(str, ...)
	#define PROFILE_FUNC() 
	
#endif

	

#ifdef SHADY_DECLSPEC	
	#define SH_INTERFACE __declspec(novtable)
#else
	#define SH_INTERFACE 

#endif

}
#endif

