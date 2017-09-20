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

	void ShadyApp::start()
	{
		mMainWindow = new Win32Window();
		mMouse = Mouse::getInstance();
		mKeyboard = Keyboard::getInstance();
		
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

		mMainWindow->disableVSync();
		setFpsLimit(0);
		
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
		fileObserver.update();
		camera2d->update();
		
		//Fps display
		char title[250];
		sprintf_s(title, 250, "FPS: %d", mFps);
		Text2D* fpsLabel = currentFont->getText({5.0f, 5.0f, 0.0f},
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
		
		camera2d = new Camera2D(Vec3f(0, 0, 0.0f),
								mMainWindow->mClientWidth, mMainWindow->mClientHeight, 2.0f);
		renderer2d = new Renderer2D(camera2d);
		currentFont =new Font();
		
		renderer2d->submit(new Rectangle(0.0f, 0.0f, mMainWindow->mClientWidth,
													 mMainWindow->mClientHeight,
													 Vec4f(1.0f, 0.0f, 0.0f, 1.0f), 3),
													10000.0f);
		
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
