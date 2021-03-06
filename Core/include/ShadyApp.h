#ifndef SHADY_APP_H
#define SHADY_APP_H

#include "Window.h"
#include "Commons.h"
#include "ShMouse.h"
#include "ShFile.h"
#include "StringUtils.h"
#include "ShKeyboard.h"
#include "FileChangeObserver.h"
#include "Sprite.h"
#include "ShClock.h"
#include "Camera2D.h"
#include "Renderer2D.h"
#include "ShFont.h"
#include "Line2D.h"
#include "Shader.h"
#include "Texture.h"
#include "ShMath.h"
#include "Graphics.h"
#include "InputManager.h"
#include "TimerManager.h"
#include "Cube.h"
#include "Renderer3D.h"
#include "ShBitset.h"
#include "ShSArray.h"
#include "Console.h"

namespace Shady
{
	class ShadyApp : public Object
	{
	private:
		static ShadyApp* sInstance;
		ShadyApp():mMainWindow(0), mMouse(0), mKeyboard(0), mFpsLimit(0),
					mUpdateLimit(0), mFps(0), mUps(0), mFrameCount(0), 
					mFrameClock(), mUpdateClock(), mUdt(0.0f), mFdt(0.0f) {}

		void initGameState();
	public:
		
		Window* mMainWindow;
		Mouse* mMouse;
		Keyboard* mKeyboard;
		InputManager* mInputManager;
		FileChangeObserver* mFileObserver;
		TimerManager* mTimerManager;
		Console* mConsole;

		Clock mFrameClock;
		Clock mUpdateClock;

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
		Camera3D* camera3d;
		Renderer3D* renderer3d;
		Font* currentFont;

		Sprite* testSprite;
		static ShadyApp* GetInstance();
		void start();
		void MainLoop();
		void update(f32 dt);
		void render(f32 dt);
		void limit(f32 time, u32 freq);
		void setFpsLimit(u32 fps);
		void setUpdateFreq(u32 ups);
		void countFps(f32 dt);
		void countUps(f32 dt);
		s32 getWindowClientWidth();
		s32 getWindowClientHeight();


		//test stuff
		Cube* cube;
		
	};	
}

#endif