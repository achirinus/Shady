#ifndef SH_TIMER_MANAGER_H
#define SH_TIMER_MANAGER_H

#include "ShList.h"
#include "Timer.h"

namespace Shady
{
	class TimerManager
	{
		List<Timer*> mTimers;
		static TimerManager* sInstance;

		TimerManager() = default;

	public:
		static TimerManager* GetInstance();

		Timer* CreateTimer(f32 boomTime, TimerFunc* func, void* data = nullptr);
		b8 RemoveTimer(Timer* timer);
		void Update(f32 dt);
	};
}

#endif