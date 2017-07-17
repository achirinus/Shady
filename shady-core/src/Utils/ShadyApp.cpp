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

	Texture* getGlyphTexture(c8 glyph, f32 pixelSize)
	{
		BinaryFileContent fileResult = File::win32ReadBinaryFile("c:/windows/fonts/arial.ttf");
		stbtt_fontinfo fontInfo;
		stbtt_InitFont(&fontInfo, (u8*)fileResult.contents, 
						stbtt_GetFontOffsetForIndex((u8*)fileResult.contents, 0));
		int width, height, xOffset, yOffset;
		u8* monoBitmap = stbtt_GetCodepointBitmap(&fontInfo, 0, stbtt_ScaleForPixelHeight(&fontInfo, pixelSize),
													glyph, &width, &height, &xOffset, &yOffset);

		
		Bitmap goodBmp = get32bppBitmapFrom8bpp(monoBitmap, width, height);

		Texture* result = new Texture(goodBmp);
		freeBitmap(goodBmp);
		stbtt_FreeBitmap(monoBitmap, 0);
		return result;
	}

	void ShadyApp::start()
	{
		mMainWindow = new Win32Window();
		mMouse = Mouse::getInstance();
		mKeyboard = Keyboard::getInstance();

		Texture* a = getGlyphTexture('N', 250.0f);
		Texture* b = getGlyphTexture('N', 30.0f);
		//Texture* b = win32GetGlyphTexture('A');
		/*
		ModelLoader mdl{};
		Mesh* cube = mdl.loadObj("..\\..\\data\\cube.obj");
		
		for(u32 vertIndex = 0; vertIndex < cube->mVertices.size(); vertIndex++)
		{
			DEBUG_OUT_INFO(cube->mVertices[vertIndex].toString().cStr());
		}
		*/
		
		gameState.camera2d = new Camera2D(Vec3f(-mMainWindow->mWidth/2, -mMainWindow->mHeight/2, 1.0f),
								mMainWindow->mWidth, mMainWindow->mHeight, 2.0f);
		gameState.renderer2d = new Renderer2D(gameState.camera2d);
		gameState.sprite = new Sprite( Vec3f(0.0f, 0.0f, 0.0f) , a->getWidth(), a->getHeight(),a);
		
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
		
		Sleep(targetTime - time);
		
	}

	void ShadyApp::update(f32 dt)
	{
		mUpdateTimer.update();

		mMainWindow->update();
		gameState.camera2d->update();
		gameState.sprite->update();
		gameState.renderer2d->submit(gameState.sprite);


		limit(mUpdateTimer.getElapsedTimeMS(), mUpdateLimit);
		mUdt = mUpdateTimer.getElapsedTimeMS();
	}

	void ShadyApp::render(f32 dt)
	{
		mFrameTimer.update();
		countFps(dt);
		mMainWindow->clear();
		gameState.renderer2d->render();
		mMainWindow->swapBuffers();

		limit(mFrameTimer.getElapsedTimeMS(), mFpsLimit);
		mFdt = mFrameTimer.getElapsedTimeMS();
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
