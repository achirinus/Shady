#include <ShadyApp.h>
#include "Rectangle.h"


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

	
	void onSetCursorVisible()
	{
		DEBUG_OUT_INFO("Cursor set visible");
		ShadyApp* app = ShadyApp::GetInstance();
		app->mMainWindow->SetCursorVisibility(true);
	}

	void onSetCursorInVisible()
	{
		DEBUG_OUT_INFO("Cursor set invisible");
		ShadyApp* app = ShadyApp::GetInstance();
		app->mMainWindow->SetCursorVisibility(false);
	}

	void ShadyApp::start()
	{
		mMainWindow = new Win32Window();
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
		mInputManager->MapAction("ShowCursor", InputKey::KEY_B);
		mInputManager->MapAction("HideCursor", InputKey::KEY_N);
		mInputManager->BindAction("ShowCursor", BA_RELEASED, onSetCursorVisible);
		mInputManager->BindAction("HideCursor", BA_RELEASED, onSetCursorInVisible);
		struct TestS
		{
			int a;
			int b;
			TestS(): a(0), b(0) {DEBUG_OUT_INFO("Test default constructed");}
			TestS(int aa , int bb): a(aa), b(bb) {DEBUG_OUT_INFO("Test args constructed\n");}
			TestS(const TestS& other): a{other.a}, b{other.b} {DEBUG_OUT_INFO("Test Copied\n");}
			TestS(TestS&& other): a{other.a}, b{other.b} {DEBUG_OUT_INFO("Test Moved\n");}
			TestS& operator=(const TestS& other) {DEBUG_OUT_INFO("Test = copied"); return *this;}
		};
		Array<u32> tInts{};
		u32 ss[] = { 1, 2, 3, 4, 5};
		tInts.Add(ss, ss + 5);

		tInts.RemoveFirst();
		Bitset<4> bits = "0101";
		bits.Flip();
		String bitsStr = bits.ToString();

		
		//END TEST ------------------------------------------
		mMainWindow->DisableVSync();
		setFpsLimit(60);
		setUpdateFreq(60);
		while (mMainWindow->IsOpen())
		{
			
			//IF WE LIMIT BOTH UPDAE() AND RENDER() THE TIME 
			//WE SLEEP IS ADDED AND WE WILL SLEEP MORE THAN NEEDED
			
			update(mFdt);
			
			//Do not render if window is minimized
			render(mFdt);
		}
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
		mUpdateClock.Reset();

		mMainWindow->Update();
		mFileObserver->Update();
		mInputManager->Update(dt);
		mTimerManager->Update(dt);
		renderer2d->Update(dt);
		
		camera3d->Update(dt);
		//testSprite->update();
		

		//Fps display
		
		String fpsText = String::FormatString("FPS:%d", mFps);
		Renderer2D::DrawText(*fpsText, 20.0f, 5.0f, 5.0f);
		
		String CursorPosString = String::FormatString("Cursor Position: %v2", mMouse->GetCursorPosition());
		Text2D* cursorPosText = currentFont->getText({5.0f, 30.0f, 1.0f}, *CursorPosString, 40.0f);
		Text2D* testText = currentFont->getText({ 5.0f, 90.0f, 1.0f }, "Something something 112.50", 40.0f);

		renderer2d->Submit(testText);
		
		renderer2d->Submit(cursorPosText);
		renderer3d->submit(cube);


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
		mFrameClock.Reset();
		countFps(dt);
		mMainWindow->Clear();
		
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
		mMainWindow->SetBackgroundColor(ColorVec::Cyan);
		mInputManager->MapAction("test", InputKey::MOUSE_LEFT);
		mInputManager->MapAction("cameraLock", InputKey::MOUSE_RIGHT);
		mInputManager->MapAction("ToggleConsole", InputKey::KEY_TILDA);
		mInputManager->MapAxis("moveX", InputKey::KEY_A, -1.0f);
		mInputManager->MapAxis("moveX", InputKey::KEY_D, 1.0f);
		mInputManager->MapAxis("moveY", InputKey::KEY_W, -1.0f);
		mInputManager->MapAxis("moveY", InputKey::KEY_S, 1.0f);
		mInputManager->MapAxis("yaw", InputKey::MOUSE_X, 1.0f);
		mInputManager->MapAxis("pitch", InputKey::MOUSE_Y, 1.0f);
		
		mConsole->Init();
		
		renderer2d = Renderer2D::GetInstance();
		currentFont =new Font();
		
		camera3d = new Camera3D({(f32)mMainWindow->mClientWidth, (f32)mMainWindow->mClientHeight});
		renderer3d = new Renderer3D(camera3d);

		cube = new Cube(200.0f, {0.0f, 0.0f, -50});
		testSprite = new Sprite({200.0f, 200.0f, -0.2f}, 500.0f, 500.0f, nullptr, {1.0f, 1.0f, 0.0f, 1.0f}, false);
		//renderer2d->submit(testSprite, 10000.0f);
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
