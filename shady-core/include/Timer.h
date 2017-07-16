#ifndef TIMER_J
#define TIMER_J

#include <Windows.h>
#include "Commons.h"

namespace Shady
{
	
	class Timer
	{
		
	private:
		LARGE_INTEGER mUpateTime;
		LARGE_INTEGER mFreq;
	public:
		enum TimeUnit
		{
			MILISECONDS,
			SECONDS,
		};
		Timer();
		void update();
		u32 getElapsedTimeS();
		f32 getElapsedTimeMS();

		u64 getCurrentCPUTime();
	};

}

#endif