#include <ShadyApp.h>
#include "Rectangle.h"
#include "DebugHelper.h"
#include "ShQueue.h"
#include "ShStack.h"
#include "ShBiSearchTree.h"
#include "ShHashTable.h"
#include "PngImage.h"
#include "ShRandom.h"
#include "MemUtils.h"
#include "ShMinHeap.h"
#include "ShMaxHeap.h"

namespace Shady
{
	ShadyApp* ShadyApp::sInstance = 0;

	ShadyApp* ShadyApp::GetInstance()
	{
		if(!sInstance)
		{
			sInstance = new ShadyApp();
		}

		return sInstance;
	}

	u32 HashInt(const s32& num)
	{
		return num;
	}

	

	void ShadyApp::start()
	{
		AUTO_TIMED_FUNCTION();

		mMainWindow = new Window();
		mMouse = Mouse::GetInstance();
		mKeyboard = Keyboard::GetInstance();
		mInputManager = InputManager::GetInstance();
		mFileObserver = FileChangeObserver::GetInstance();
		mTimerManager = TimerManager::GetInstance();
		mConsole = Console::GetInstance();
		initGameState();
		//Texture* b = win32GetGlyphTexture('A');
		/*
		ModelLoader mdl{};
		Mesh* cube = mdl.loadObj("..\\..\\data\\cube.obj");
		
		for(u32 vertIndex = 0; vertIndex < cube->mVertices.size(); vertIndex++)
		{
			DEBUG_OUT_INFO(cube->mVertices[vertIndex].toString().cStr());
		}
		*/
		//TEST STUFF!!------------------------------------
		
		
		s32 InsertSortTest[] = { 54, 23, 72, 1, 234, 10, 39, 2 };
		MaxHeap<s32> TestHeap;
		TestHeap.Insert(29);
		TestHeap.Insert(10);
		TestHeap.Insert(30);
		TestHeap.Insert(13);
		TestHeap.Insert(2);
		TestHeap.Insert(1);

		u32 Smaller1 = TestHeap.GetMin();
		u32 Smaller2 = TestHeap.GetMin();
 		u32 Smaller3 = TestHeap.GetMin();
		u32 Smaller4 = TestHeap.GetMin();
		u32 Smaller5 = TestHeap.GetMin();

		//InsertionSort(InsertSortTest, C_ARRAY_SIZE(InsertSortTest));
		InsertionSort(InsertSortTest, InsertSortTest + C_ARRAY_SIZE(InsertSortTest), [](s32 a, s32 b) {if (a == b) return 0; return a > b ? -1 : 1; });
		File TestPng{ "image.png" };
		TestPng.Open(FileType::BINARY_FILE);
		BinaryFileContent Content = TestPng.ReadAllData();
		PngImage TestPngImage{};
		TestPngImage.InitFromData(Content);
		
		//END TEST ------------------------------------------
		mMainWindow->DisableVSync();
		//setFpsLimit(60);
		//setUpdateFreq(60);
		// 

		while (mMainWindow->IsOpen())
		{
			MainLoop();
		}
	}

	void ShadyApp::MainLoop()
	{
		DebugHelper::StartFrame();
		START_TIMED_BLOCK(MainLoop);
		//IF WE LIMIT BOTH UPDAE() AND RENDER() THE TIME 
		//WE SLEEP IS ADDED AND WE WILL SLEEP MORE THAN NEEDED

		update(mFdt);

		//Do not render if window is minimized
		render(mFdt);

		END_TIMED_BLOCK(MainLoop);
		DebugHelper::EndFrame();
	}

	void ShadyApp::limit(f32 time, u32 freq)
	{
		
		if(!freq) return;
		u32 targetTime = SafeRatio((u32)1000, freq);
		if((u32)time > targetTime) return;
		
		//TODO Anything but this.
		Sleep(targetTime - time);
	}

	void ShadyApp::update(f32 dt)
	{
		AUTO_TIMED_FUNCTION();
		mUpdateClock.Reset();

		mMainWindow->Update();
		mFileObserver->Update();
		mInputManager->Update(dt);
		mTimerManager->Update(dt);
		renderer2d->Update(dt);
		
		camera3d->Update(dt);
		//testSprite->update();
		
		String td("abcd");
		td += "10";
		td += "10";
		td = td + "20";
		td += "10";

		//Fps display
		
		String fpsText = String::FormatString("FPS:%d", mFps);
		Renderer2D::DrawText(*fpsText, 20.0f, {mMainWindow->mWidth - 200.0f, 5.0f, 1.0f}, ColorVec::White);
		Renderer2D::DrawText("Test text!", 20.0f, { (f32)(mMainWindow->mClientWidth - 20), 10.0f, 0.0f });
		String CursorPosString = String::FormatString("Cursor Position: %v2", mMouse->GetCursorPosition());
		Text2D* cursorPosText = currentFont->GetText({5.0f, 30.0f, 1.0f}, *CursorPosString, 20);
		
		Renderer2D::DrawText("Something something\nfqwfqcn112.50", 20.0f, { 5.0f, 130.0f, 1.0f });
		
		renderer2d->Submit(cursorPosText);
		renderer3d->submit(cube);
		
		f32 InfoY = 100;
		for (auto& FunctionInfo : DebugHelper::LastFrame.Functions)
		{
			String temp = String::FormatString("%s: AvgTimePerCall: %f, Calls: %d", FunctionInfo.Name, FunctionInfo.AvgTimePerCall, FunctionInfo.NumOfCalls );
			Renderer2D::DrawText(*temp, 20.0f, { 500.0f, InfoY, 0.0f });
			InfoY += 20.0f;
		}
		
		mConsole->Update(dt);
		
		//for now use mFds and limit only the render function because
		//the  ads from both limit() calls. we need separate threads
		#if 0
		limit(mUpdateClock.GetElapsedTimeMS(), mUpdateLimit);
		mUdt = mUpdateClock.GetElapsedTimeMS();
		#endif
	}

	void ShadyApp::render(f32 dt)
	{
		AUTO_TIMED_FUNCTION();
		mFrameClock.Reset();
		countFps(dt);
		mMainWindow->Clear();
		
		Renderer2D::DrawText("Time", 20.0f, { 500.0f, 10, 0.0f });

		
		renderer2d->Render();
		mConsole->Render();
		renderer3d->render(dt);

		mMainWindow->SwapBuffers();
		//checkGlError();

		limit(mFrameClock.GetElapsedTimeMS(), mFpsLimit);
		mFdt = mFrameClock.GetElapsedTimeMS();
	}

	void ShadyApp::initGameState()
	{
		AUTO_TIMED_FUNCTION();
		mMainWindow->SetBackgroundColor(ColorVec::Pink);
		mInputManager->MapAction("test", InputKey::MOUSE_LEFT);
		mInputManager->MapAction("cameraLock", InputKey::MOUSE_RIGHT);
		mInputManager->MapAction("ToggleConsole", InputKey::KEY_TILDA);
		mInputManager->MapAxis("moveX", InputKey::KEY_A, -1.0f);
		mInputManager->MapAxis("moveX", InputKey::KEY_D, 1.0f);
		mInputManager->MapAxis("moveY", InputKey::KEY_W, -1.0f);
		mInputManager->MapAxis("moveY", InputKey::KEY_S, 1.0f);
		mInputManager->MapAxis("yaw", InputKey::MOUSE_X, 1.0f);
		mInputManager->MapAxis("pitch", InputKey::MOUSE_Y, 1.0f);
		currentFont =new Font();
		
		mConsole->Init();
		
		renderer2d = Renderer2D::GetInstance();
		
		camera3d = new Camera3D({(f32)mMainWindow->mClientWidth, (f32)mMainWindow->mClientHeight});
		renderer3d = new Renderer3D(camera3d);
		Texture* Atlas = currentFont->mAtlasGlyphs[20].Atlas;
		Sprite* TestAtlas = new Sprite(Vec3f{ 400, 400, 0 }, Atlas);
		renderer2d->Submit(TestAtlas, 20.0f);
		cube = new Cube(200.0f, {0.0f, 0.0f, -50});
		
	}

	void ShadyApp::countFps(f32 dt)
	{
		mFrameCount++;
		mFps = (u32)SafeRatio(1000.0f, dt);
	}

	void ShadyApp::countUps(f32 dt)
	{
		mUps = (u32)SafeRatio(1000.0f, dt);
	}	

	void ShadyApp::setFpsLimit(u32 fps)
	{
		
		mFpsLimit = fps;
	}
	void ShadyApp::setUpdateFreq(u32 ups)
	{
		mUpdateLimit = ups;
	}

	s32 ShadyApp::getWindowClientWidth()
	{
		return mMainWindow ? mMainWindow->mClientWidth : 0;
	}
	s32 ShadyApp::getWindowClientHeight()
	{
		return mMainWindow ? mMainWindow->mClientHeight : 0;
	}

}
