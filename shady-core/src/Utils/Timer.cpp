#include "Timer.h"


namespace Shady
{
	
	u32 Timer::getElapsedTimeS()
	{
		LARGE_INTEGER tempTime;
		QueryPerformanceCounter(&tempTime);
		return (tempTime.QuadPart - mUpateTime.QuadPart) / mFreq.QuadPart;
	}

	f32 Timer::getElapsedTimeMS()
	{
		LARGE_INTEGER tempTime;
		QueryPerformanceCounter(&tempTime);
		u64 delta = tempTime.QuadPart - mUpateTime.QuadPart; 
		delta *= 1000;
		f64 fDelta = static_cast<f64>(delta);
		f64 fFreq = static_cast<f64>(mFreq.QuadPart);
		f32 result = fDelta / fFreq;
		
		return result;
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