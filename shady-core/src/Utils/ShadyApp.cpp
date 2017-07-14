#include <ShadyApp.h>
#include "Win32Window.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera2D.h"
#include "Sprite.h"
#include "ShadyMath.h"
#include "Renderer2D.h"
#include "FileUtils.h"
#include "Graphics.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

namespace Shady
{
	ShadyApp* ShadyApp::sInstance = 0;

	inline ShadyApp& ShadyApp::getInstance()
	{
		if(!sInstance)
		{
			sInstance = new ShadyApp();
		}

		return *sInstance;
	}

	Texture* getGlyphTexture(c8 glyph)
	{
		BinaryFileContent fileResult = File::win32ReadBinaryFile("c:/windows/fonts/arial.ttf");
		stbtt_fontinfo fontInfo;
		stbtt_InitFont(&fontInfo, (u8*)fileResult.contents, 
						stbtt_GetFontOffsetForIndex((u8*)fileResult.contents, 0));
		int width, height, xOffset, yOffset;
		u8* monoBitmap = stbtt_GetCodepointBitmap(&fontInfo, 0, stbtt_ScaleForPixelHeight(&fontInfo, 150.0f),
													glyph, &width, &height, &xOffset, &yOffset);

		
		Bitmap goodBmp = get32bppBitmapFrom8bpp(monoBitmap, width, height);

		Texture* result = new Texture(goodBmp);
		freeBitmap(goodBmp);
		stbtt_FreeBitmap(monoBitmap, 0);
		return result;
	}

	Texture* win32GetGlyphTexture(c8 glyph)
	{
		static HDC dc = 0;
		if(!dc)
		{
			dc = CreateCompatibleDC(0);
			HBITMAP bitmap = CreateCompatibleBitmap(dc, 512, 512);
			SelectObject(dc, bitmap);
		}
		c16 cheesePoint = (c16)glyph;
		TextOutW(dc, 0, 0, &cheesePoint, 1);
		return 0;
	}	

	void ShadyApp::start()
	{
		mMainWindow = new Win32Window();
		mMouse = Mouse::getInstance();
		mKeyboard = Keyboard::getInstance();

		Texture* a = getGlyphTexture('A');
		//Texture* b = win32GetGlyphTexture('A');
		/*
		ModelLoader mdl{};
		Mesh* cube = mdl.loadObj("..\\..\\data\\cube.obj");
		
		for(u32 vertIndex = 0; vertIndex < cube->mVertices.size(); vertIndex++)
		{
			DEBUG_OUT_INFO(cube->mVertices[vertIndex].toString().cStr());
		}
		*/
		
		Texture texture("..\\..\\data\\2d_skeleton_idle.png");
		Texture texture2("..\\..\\data\\2d_skeleton_kinght_idle.png");
		
		
		Camera2D camera(Vec3f(), mMainWindow->mWidth, mMainWindow->mHeight, 2.0f);
		Renderer2D renderer(&camera);
		Sprite* sprite = new Sprite( Vec3f(20.0f, 100.0f, 0.0f) , a->getWidth(), a->getHeight(), a);
		Sprite* sprite2 = new Sprite( Vec3f(500, 200, 0.0f) , 78, 83, nullptr, Vec4f(1.0f, 0.0f, 1.0f, 1.0f));
		while (mMainWindow->isOpen())
		{
			sprite->update();
			sprite2->update();
			renderer.submit(sprite);
			renderer.submit(sprite2);
			mMainWindow->clear();
			mMainWindow->update();
			camera.update();
			//shader.setUniformMat4("viewMat", Matrix4f::lookAt(Vec3f(1.0f, 0.0f, 0.0f), 
			//												Vec3f(0.0f, 0.0f, 0.0f),
			//												Vec3f(0.0f, 1.0f, 0.0f) ));
			renderer.render();
			
			mMainWindow->swapBuffers();
		}

	}


}
