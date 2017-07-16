#ifndef SHADY_APP_H
#define SHADY_APP_H

#include "Window.h"
#include "Commons.h"
#include "ShMouse.h"
#include "ShKeyboard.h"
#include "Timer.h"
#include "GameState.h"

namespace Shady
{
	class ShadyApp
	{
	private:
		static ShadyApp* sInstance;
		ShadyApp():mMainWindow(0), mMouse(0), mKeyboard(0), mFpsLimit(0),
					mUpdateLimit(0), mFps(0), mUps(0), mFrameCount(0), 
					mFrameTimer(), mUpdateTimer(), mUdt(0.0f), mFdt(0.0f) {}
	public:
		
		Window* mMainWindow;
		Mouse* mMouse;
		Keyboard* mKeyboard;
		GameState gameState;
		Timer mFrameTimer;
		Timer mUpdateTimer;

		u32 mFpsLimit;
		u32 mUpdateLimit; //This is expressed in updates/s too

		f32 mUdt;
		f32 mFdt;

		u32 mFps;
		u32 mUps;
		u32 mFrameCount;
		static ShadyApp* getInstance();
		void start();
		void update(f32 dt);
		void render(f32 dt);
		void limit(f32 time, u32 freq);
		void setFpsLimit(u32 fps);
		void setUpdateFreq(u32 ups);
		void countFps(f32 dt);
		void countUps(f32 dt);
	};	
}

#endif