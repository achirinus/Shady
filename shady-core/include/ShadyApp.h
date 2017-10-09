#ifndef SHADY_APP_H
#define SHADY_APP_H

#include "Win32Window.h"
#include "Commons.h"
#include "ShMouse.h"
#include "FileUtils.h"
#include "StringUtils.h"
#include "ShKeyboard.h"
#include "FileChangeObserver.h"
#include "Sprite.h"
#include "Timer.h"
#include "Camera2D.h"
#include "Renderer2D.h"
#include "ShFont.h"
#include "Line2D.h"
#include "Shader.h"
#include "Texture.h"
#include "ShMath.h"
#include "FileUtils.h"
#include "Graphics.h"
#include "InputManager.h"

namespace Shady
{
	class ShadyApp
	{
	private:
		static ShadyApp* sInstance;
		ShadyApp():mMainWindow(0), mMouse(0), mKeyboard(0), mFpsLimit(0),
					mUpdateLimit(0), mFps(0), mUps(0), mFrameCount(0), 
					mFrameTimer(), mUpdateTimer(), mUdt(0.0f), mFdt(0.0f) {}

		void initGameState();
	public:
		
		Window* mMainWindow;
		Mouse* mMouse;
		Keyboard* mKeyboard;
		InputManager* mInputManager;
		Timer mFrameTimer;
		Timer mUpdateTimer;
		FileChangeObserver fileObserver;

		u32 mFpsLimit;
		u32 mUpdateLimit; //This is expressed in updates/s too

		f32 mUdt;
		f32 mFdt;

		u32 mFps;
		u32 mUps;
		u32 mFrameCount;


		//Gamestate stuff
		Camera2D* camera2d;
		Renderer2D* renderer2d;
		Font* currentFont;

		Sprite* testSprite;
		static ShadyApp* getInstance();
		void start();
		void update(f32 dt);
		void render(f32 dt);
		void limit(f32 time, u32 freq);
		void setFpsLimit(u32 fps);
		void setUpdateFreq(u32 ups);
		void countFps(f32 dt);
		void countUps(f32 dt);
		s32 getWindowClientWidth();
		s32 getWindowClientHeight();

	};	
}

#endif