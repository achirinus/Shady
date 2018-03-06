#ifndef SH_CLOCK_H
#define SH_CLOCK_H

#include <Windows.h>
#include "Commons.h"

namespace Shady
{
	
	class Clock
	{
		
	private:
		LARGE_INTEGER mUpateTime;
		LARGE_INTEGER mFreq;
	public:
		Clock();
		void Reset();
		u32 GetElapsedTimeS();
		f32 GetElapsedTimeMS();

		u64 GetCurrentCPUTime();
	};

}

#endif