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

	void testCb()
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
		mMouse = Mouse::getInstance();
		mKeyboard = Keyboard::getInstance();
		mInputManager = InputManager::getInstance();
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
		Array<u32> ar(3);
		ar.add(1);
		ar.add(2);
		ar.add(3);
		for(auto& elem : ar)
		{
			DEBUG_OUT_INFO("%d ", elem);
		}
		
		mMainWindow->disableVSync();
		setFpsLimit(60);
		
		while (mMainWindow->isOpen())
		{
			
			//IF WE LIMIT BOTH UPDAE() AND RENDER() THE TIME 
			//WE SLEEP IS ADDED AND WE WILL SLEEP MORE THAN NEEDED
			
			update(mUdt);
			
			//Do not render if window is minimized
			render(mFdt);

		}

	}

	void ShadyApp::limit(f32 time, u32 freq)
	{
		if(!freq) return;
		u32 targetTime = safeRatio((u32)1000, freq);
		if((u32)time > targetTime) return;
		
		//TODO Anything but this.
		Sleep(targetTime - time);
	}

	void ShadyApp::update(f32 dt)
	{
		mUpdateTimer.update();

		mMainWindow->update();
		mInputManager->update(dt);
		fileObserver.update();
		camera2d->update();
		//testSprite->update();
		

		//Fps display
		char title[250];
		sprintf_s(title, 250, "FPS: %d", mFps);
		Text2D* fpsLabel = currentFont->getText({5.0f, 5.0f, -1.0f},
												title, 20.0f);
		renderer2d->submit(fpsLabel);


		limit(mUpdateTimer.getElapsedTimeMS(), mUpdateLimit);
		mUdt = mUpdateTimer.getElapsedTimeMS();
		
	}

	void ShadyApp::render(f32 dt)
	{
		mFrameTimer.update();
		countFps(dt);
		mMainWindow->clear();
		renderer2d->render(dt);
		mMainWindow->swapBuffers();

		checkGlError();

		limit(mFrameTimer.getElapsedTimeMS(), mFpsLimit);
		mFdt = mFrameTimer.getElapsedTimeMS();

	}

	void ShadyApp::initGameState()
	{
		File::setCwd("..\\..\\"); //CWD = Main Shady folder
		//TODO put these in their arena and take care of cleanup
		mInputManager->mapAction("test", InputKey::MOUSE_LEFT);
		mInputManager->bindAction("test", BA_PRESSED, testCb);
		mInputManager->mapAxis("left", InputKey::KEY_A, -1.0f);
		mInputManager->mapAxis("left", InputKey::KEY_D, 1.0f);
		mInputManager->mapAxis("mx", InputKey::MOUSE_X, 1.0f);
		mInputManager->bindAxis("left", this, reinterpret_cast<AxisFunc>(&ShadyApp::testKAxis));
		mInputManager->bindAxis("mx", this, reinterpret_cast<AxisFunc>(&ShadyApp::testMAxis));
		camera2d = new Camera2D(Vec3f(0, 0, 0.0f),
								mMainWindow->mClientWidth, mMainWindow->mClientHeight, 2.0f);
		renderer2d = new Renderer2D(camera2d);
		currentFont =new Font();
		
		renderer2d->submit(new Rectangle(0.0f, 0.0f, mMainWindow->mClientWidth,
													 mMainWindow->mClientHeight,
													 false, false,
													 Vec4f(1.0f, 0.0f, 1.0f, 1.0f), 3),
													10000.0f);

		testSprite = new Sprite({200.0f, 200.0f, -0.2f}, 500.0f, 500.0f, nullptr, {1.0f, 1.0f, 0.0f, 1.0f}, false);
		renderer2d->submit(testSprite, 10000.0f);
	}

	void ShadyApp::countFps(f32 dt)
	{
		mFrameCount++;
		mFps = (u32)safeRatio(1000.0f, dt);
	}

	void ShadyApp::countUps(f32 dt)
	{
		mUps = (u32)safeRatio(1000.0f, dt);
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
