#ifndef SH_WINDOW
#define SH_WINDOW

#include <Commons.h>
#include "ShadyGL.h"
#include "ShString.h"
#include "Vec4.h"

#define SH_DEFAULT_WINDOW_WIDTH 1280
#define SH_DEFAULT_WINDOW_HEIGHT 720
#define SH_DEFAULT_WINDOW_TITLE "Shady"

namespace Shady
{
	

	struct SH_INTERFACE Window
	{
		Window(const c8* title = SH_DEFAULT_WINDOW_TITLE, 
				s16 width = SH_DEFAULT_WINDOW_WIDTH,
				s16 height = SH_DEFAULT_WINDOW_HEIGHT): 
				mHeight(height), mWidth(width), mXPos(0), 
				mYPos(0), mClientWidth(0),
				mClientHeight(0), mFullScreen(0), mOpenglInfo()
				{}

		s16 mWidth;
		s16 mHeight;
		s16 mXPos;
		s16 mYPos;
		s16 mClientWidth;
		s16 mClientHeight;
		b8 mFullScreen;
		OpenglInfo mOpenglInfo;
		
		virtual void Update() = 0;
		virtual void SwapBuffers() = 0;
		virtual void Clear() = 0;
		virtual b8 IsOpen() = 0;
		virtual void SetBackgroundColor(const Vec4f& col) = 0;
		virtual void Show() = 0;
		virtual void Hide() = 0;
		virtual void Minimize() = 0;
		virtual void Maximize() = 0;
		virtual void Restore() = 0;
		virtual bool IsActive() = 0;
		virtual bool IsFullScreen() = 0;
		virtual void EnableVSync() = 0;
		virtual void DisableVSync() = 0;
		virtual void SetTitle(const c8* title) = 0;
		virtual String GetTitle() = 0;
		virtual void SetCursorVisibility(b8 visible) = 0;
		virtual ~Window() {};
		virtual void* GetPlatformPointer() = 0;
	};
}

#endif