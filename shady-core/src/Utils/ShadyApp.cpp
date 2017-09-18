#include <ShadyApp.h>
#include "Win32Window.h"
#include "Shader.h"
#include "Texture.h"
#include "ShadyMath.h"
#include "FileUtils.h"
#include "Graphics.h"


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
		gameState = initGameState();

		
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
		setFpsLimit(60);
		char title[250];

		
		while (mMainWindow->isOpen())
		{
			
			//IF WE LIMIT BOTH UPDAE() AND RENDER() THE TIME 
			//WE SLEEP IS ADDED AND WE WILL SLEEP MORE THAN NEEDED

			sprintf_s(title, 250, "FPS: %d", mFps);
			mMainWindow->setTitle(title);
			
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
		gameState->camera2d->update();
		gameState->renderer2d->submit(gameState->sprite);
		gameState->renderer2d->submit(gameState->line);

		limit(mUpdateTimer.getElapsedTimeMS(), mUpdateLimit);
		mUdt = mUpdateTimer.getElapsedTimeMS();
		
	}

	void ShadyApp::render(f32 dt)
	{
		mFrameTimer.update();
		countFps(dt);
		mMainWindow->clear();
		gameState->renderer2d->render();
		mMainWindow->swapBuffers();

		checkGlError();
		
		limit(mFrameTimer.getElapsedTimeMS(), mFpsLimit);
		mFdt = mFrameTimer.getElapsedTimeMS();

	}

	GameState* ShadyApp::initGameState()
	{
		File::setCwd("..\\..\\"); //CWD = Main Shady folder
		//TODO put these in their arena and take care of cleanup
		GameState* gameState = new GameState();
		gameState->currentFont =new Font();
		gameState->camera2d = new Camera2D(Vec3f(-mMainWindow->mWidth/2, -mMainWindow->mHeight/2, 1.0f),
								mMainWindow->mWidth, mMainWindow->mHeight, 2.0f);
		gameState->renderer2d = new Renderer2D(gameState->camera2d);
		gameState->sprite = new Sprite( Vec3f(0.0f, 0.0f, 0.0f), gameState->currentFont->getGlyph('A'));
		gameState->text = gameState->currentFont->getText({-500.0f, 0.0f, 0.0f}, "ALIN + Alejandra", 60.0f);
		gameState->line = new Line2D(Vec3f(0.0f, 0.0f, 0.0f), Vec3f(100.0f, 0.0f, 0.0f),
									 Vec4f(1.0f, 1.0f, 0.0f, 1.0f), 2);
		fileObserver.add("data\\abc.txt", testCb);
		return gameState;
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


}
