#include "Timer.h"


namespace Shady
{
	Timer::Timer(f32 boomTime, TimerFunc* func, void* data):
		mFunc{func}, mData{data}, mBoomTime{boomTime}, mPaused{false} 
	{

	}

	Timer::Timer(const Timer& other): 
		mFunc{other.mFunc}, mData{other.mData}, mBoomTime{other.mBoomTime}, mPaused{false} 
	{

	}
	
	Timer::Timer(Timer&& other): 
		mFunc{other.mFunc}, mData{other.mData}, mBoomTime{other.mBoomTime}, mPaused{false}
	{

	}
	
	Timer& Timer::operator=(const Timer& other)
	{
		mFunc = other.mFunc;
		mData = other.mData;
		mBoomTime = other.mBoomTime;
		mPaused = other.mPaused;
		return *this;
	}

	Timer& Timer::operator=(Timer&& other)
	{
		mFunc = other.mFunc;
		mData = other.mData;
		mBoomTime = other.mBoomTime;
		mPaused = other.mPaused;
		return *this;
	}

	b8 Timer::Update(f32 dt)
	{
		static f32 timePassed = 0;
		b8 result = false;
		if(!mPaused)
		{
			timePassed += dt;
			if((timePassed / 1000.0f) >= mBoomTime)
			{
				if(mFunc) mFunc(mData);
				result = true;
			}
		}

		return result;
	}

	void Timer::Pause()
	{
		mPaused = true;
	}

	void Timer::Unpause()
	{
		mPaused = false;
	}
	

}