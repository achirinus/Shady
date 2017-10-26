#include "ShClock.h"


namespace Shady
{
	Clock::Clock()
	{
		QueryPerformanceFrequency(&mFreq);
	}

	void Clock::Reset()
	{
		QueryPerformanceCounter(&mUpateTime);
	}

	u32 Clock::GetElapsedTimeS()
	{
		LARGE_INTEGER tempTime;
		QueryPerformanceCounter(&tempTime);
		return (tempTime.QuadPart - mUpateTime.QuadPart) / mFreq.QuadPart;
	}

	f32 Clock::GetElapsedTimeMS()
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

	u64 Clock::GetCurrentCPUTime()
	{
		return (uint64)(mUpateTime.QuadPart) / mFreq.QuadPart;
	}

}