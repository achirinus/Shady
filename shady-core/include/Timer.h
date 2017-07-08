#ifndef TIMER_J
#define TIMER_J

#include <Windows.h>
#include "Commons.h"

namespace Shady
{
	namespace Utils
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
			u32 getElapsedTimeMS();
			u64 getCurrentCPUTime();
		};
	}
}

#endif