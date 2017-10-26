#include "TimerManager.h"

namespace Shady
{
	TimerManager* TimerManager::sInstance = nullptr;

	TimerManager* TimerManager::GetInstance()
	{
		if(!sInstance)
		{
			sInstance = new TimerManager();
		}

		return sInstance;
	}

	Timer* TimerManager::CreateTimer(f32 boomTime, TimerFunc* func, void* data)
	{
		Timer* result = new Timer(boomTime, func, data);
		mTimers.PushFront(result);
		return result;
	}

	b8 TimerManager::RemoveTimer(Timer* timer)
	{
		b8 result =  mTimers.Remove(timer);
		if(result) delete timer;
		return result;
	}

	void TimerManager::Update(f32 dt)
	{
		b8 removed = false;
		
		do
		{
			removed = false;
			for(auto timer : mTimers)
			{
				removed = timer->Update(dt);
				if(removed)
				{
					RemoveTimer(timer);
					break;
				}
			}
		}while(removed);
		
	}



}