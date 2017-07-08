#include "Timer.h"


namespace Shady
{
	namespace Utils
	{
		u32 Timer::getElapsedTimeS()
		{
			LARGE_INTEGER tempTime;
			QueryPerformanceCounter(&tempTime);
			return (tempTime.QuadPart - mUpateTime.QuadPart) / mFreq.QuadPart;
		}

		u32 Timer::getElapsedTimeMS()
		{
			LARGE_INTEGER tempTime;
			QueryPerformanceCounter(&tempTime);
			
			return ((tempTime.QuadPart - mUpateTime.QuadPart) * 1000)/ mFreq.QuadPart;
		}

		void Timer::update()
		{
			QueryPerformanceCounter(&mUpateTime);
		}

		Timer::Timer()
		{
			QueryPerformanceFrequency(&mFreq);
		}

		uint64 Timer::getCurrentCPUTime()
		{
			return (uint64)(mUpateTime.QuadPart) / mFreq.QuadPart;
		}
	}
}