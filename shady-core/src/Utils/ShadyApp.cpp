#include <ShadyApp.h>



namespace Shady
{
	ShadyApp* ShadyApp::sInstance = 0;

	ShadyApp* ShadyApp::getInstance()
	{
		if(!sInstance)
		{
			sInstance = new ShadyApp();
		}

		return sInstance;
	}

	void testTm(void* data)
	{
		DEBUG_OUT_INFO("worked!");
	}

	void ShadyApp::testCb()
	{
		DEBUG_OUT_INFO("changed");
	}

	void ShadyApp::testKAxis(f32 value)
	{
		DEBUG_OUT_INFO("Left: %f", value);
	}

	void ShadyApp::testMAxis(f32 value)
	{
		DEBUG_OUT_INFO("X: %f", value);
	}

	void ShadyApp::start()
	{
		mMainWindow = new Win32Window();
		mMouse = Mouse::GetInstance();
		mKeyboard = Keyboard::GetInstance();
		mInputManager = InputManager::GetInstance();
		mFileObserver = FileChangeObserver::GetInstance();
		mTimerManager = TimerManager::GetInstance();
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
		//TEST STUFF!!
		f32 first = 4.0f;
		f32 res = SquareRoot(first);
		String a = "Abc";
		String b = a + 2345;
		DEBUG_OUT_INFO("%s", b.CStr());

		

		
		u64 gb = 1_GB;
		DEBUG_OUT_INFO("GB: %lld", gb);

		//END TEST
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

		camera2d->update();
		camera3d->Update(dt);
		//testSprite->update();
		

		//Fps display
		char title[250];
		sprintf_s(title, 250, "FPS: %d", mFps);
		Text2D* fpsLabel = currentFont->getText({5.0f, 5.0f, -1.0f},
												title, 20.0f);
		renderer2d->submit(fpsLabel);
		renderer3d->submit(cube);

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
		renderer2d->render(dt);
		renderer3d->render(dt);
		mMainWindow->SwapBuffers();

		//checkGlError();

		limit(mFrameClock.GetElapsedTimeMS(), mFpsLimit);
		mFdt = mFrameClock.GetElapsedTimeMS();

	}

	void ShadyApp::initGameState()
	{
		File::setCwd("..\\..\\"); //CWD = Main Shady folder
		//TODO put these in their arena and take care of cleanup
		mInputManager->MapAction("test", InputKey::MOUSE_LEFT);
		mInputManager->MapAction("cameraLock", InputKey::MOUSE_RIGHT);
		mInputManager->MapAxis("moveX", InputKey::KEY_A, -1.0f);
		mInputManager->MapAxis("moveX", InputKey::KEY_D, 1.0f);
		mInputManager->MapAxis("moveY", InputKey::KEY_W, -1.0f);
		mInputManager->MapAxis("moveY", InputKey::KEY_S, 1.0f);
		mInputManager->MapAxis("yaw", InputKey::MOUSE_X, 1.0f);
		mInputManager->MapAxis("pitch", InputKey::MOUSE_Y, 1.0f);
		
		#if 0
		mInputManager->mapAxis("left", InputKey::KEY_A, -1.0f);
		mInputManager->mapAxis("left", InputKey::KEY_D, 1.0f);
		mInputManager->mapAxis("mx", InputKey::MOUSE_X, 1.0f);
		mInputManager->bindAxis("left", this, reinterpret_cast<AxisFunc>(&ShadyApp::testKAxis));
		mInputManager->bindAxis("mx", this, reinterpret_cast<AxisFunc>(&ShadyApp::testMAxis));
		#endif

		camera2d = new Camera2D(Vec3f(0, 0, 0.0f),
								mMainWindow->mClientWidth, mMainWindow->mClientHeight, 2.0f);
		renderer2d = new Renderer2D(camera2d);
		currentFont =new Font();
		
		renderer2d->submit(new Rectangle(0.0f, 0.0f, mMainWindow->mClientWidth,
													 mMainWindow->mClientHeight,
													 false, false,
													 Vec4f(1.0f, 0.0f, 1.0f, 1.0f), 3),
													10000.0f);
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
