#ifndef TIMER_J
#define TIMER_J

#include "Commons.h"
#include "ShObject.h"

namespace Shady
{

	typedef void (TimerFunc)(void*);
	
	class Timer
	{
		friend class TimerManager;
	private:
		TimerFunc* mFunc;
		void* mData;
		f32 mBoomTime;
		b8 mPaused;

		Timer(f32 boomTime, TimerFunc* func, void* data);
		Timer(const Timer&);
		Timer(Timer&& other);
		Timer& operator=(const Timer&);
		Timer& operator=(Timer&&);
		~Timer() = default;
	public:

		b8 Update(f32 dt);
		void Pause();
		void Unpause();
	};

}

#endif